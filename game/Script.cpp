#include "Script.h"
#include "Logger.h"
#include "Scene.h"
#include "SceneObjectFactory.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <luabind/luabind.hpp>
#include <libgen.h>

namespace luabind
{
    template <>
    struct default_converter<b2Vec2> : native_converter_base<b2Vec2>
    {
        static int compute_score(lua_State* L, int index)
        {
            return ::lua_type(L, index) == LUA_TTABLE ? 0 : -1;
        }

        b2Vec2 from(lua_State* L, int index)
        {
            luabind::object tmp(luabind::from_stack(L, index));
            return b2Vec2(luabind::object_cast<float>(tmp["x"]),
                          luabind::object_cast<float>(tmp["y"]));
        }

        void to(lua_State* L, const b2Vec2& value)
        {
            throw luabind::cast_failed(L, typeid(value));
        }
    };

    template <>
    struct default_converter<const b2Vec2&> : default_converter<b2Vec2>
    {};

    template <>
    struct default_converter< std::vector<b2Vec2> > : native_converter_base< std::vector<b2Vec2> >
    {
        static int compute_score(lua_State* L, int index)
        {
            return ::lua_type(L, index) == LUA_TTABLE ? 0 : -1;
        }

        std::vector<b2Vec2> from(lua_State* L, int index)
        {
            std::vector<b2Vec2> list;

            for (luabind::iterator it(luabind::object(luabind::from_stack(L, index))), end;
                 it != end; ++it) {
                list.push_back(b2Vec2(luabind::object_cast<float>((*it)["x"]),
                                      luabind::object_cast<float>((*it)["y"])));
            }

            return list;
        }

        void to(lua_State* L, const std::vector<b2Vec2>& value)
        {
            throw luabind::cast_failed(L, typeid(value));
        }
    };

    template <>
    struct default_converter<const std::vector<b2Vec2>&> : default_converter< std::vector<b2Vec2> >
    {};
}

namespace af
{
    static int errorHandler(lua_State* L)
    {
        lua_Debug d;

        ::lua_getstack(L, 1, &d);
        ::lua_getinfo(L, "Sln", &d);

        std::string err = ::lua_tostring(L, -1);

        ::lua_pop(L, 1);

        std::ostringstream os;

        os << d.short_src << ": " << d.currentline;

        if (d.name != 0) {
            os << " (" << d.namewhat << " " << d.name << ")";
        }

        os << " - " << err;

        ::lua_pushstring(L, os.str().c_str());

        LOG4CPLUS_ERROR(logger(), os.str());

        return 1;
    }

    class Script::Impl
    {
    public:
        Impl(const std::string& path,
             const std::string& modulePath,
             Scene* scene)
        : path_(path),
          modulePath_(modulePath),
          scene_(scene),
          L_(NULL)
        {
        }

        ~Impl()
        {
            if (L_) {
                ::lua_close(L_);
            }
        }

        void bind()
        {
            luabind::module(L_)
            [
                luabind::class_<Scene>("Scene")
                    .def("add", &Scene::add),

                luabind::class_<SceneObjectFactory>("SceneObjectFactory")
                    .def("createPlayer", &SceneObjectFactory::createPlayer)
                    .def("createRock", &SceneObjectFactory::createRock),

                luabind::class_< SceneObject, boost::shared_ptr<SceneObject> >("SceneObject")
                    .def("scene", &SceneObject::scene)
            ];
        }

        void setPackagePaths()
        {
            std::ostringstream os, osc;

            os << modulePath_ << "/?.lua;";
            osc << modulePath_ << "/?.so;";

            char scriptPath[PATH_MAX];

            if (::realpath(path_.c_str(), scriptPath) != NULL) {
                char* sDir = ::dirname(scriptPath);

                os << sDir << "/?.lua;";
                osc << sDir << "/?.so;";
            }

            os << "./?.lua;?.lua";
            osc << "./?.so;?.so";

            luabind::globals(L_)["package"]["path"] = os.str();
            luabind::globals(L_)["package"]["cpath"] = osc.str();
        }

        void require(const std::string& name)
        {
            luabind::call_function<void>(L_, "require", name);
        }

        void createGlobalObjects()
        {
            luabind::globals(L_)["scene"] = scene_;
            luabind::globals(L_)["factory"] = &sceneObjectFactory;
        }

        void loadFile()
        {
            if (::luaL_loadfile(L_, path_.c_str()) != 0) {
                const char* errText = ::lua_tostring(L_, -1);

                std::string text;

                if (errText) {
                    text = errText;
                } else {
                    text = std::string("Cannot load lua chunk from file \"") +
                                        path_ + "\"";
                }

                ::lua_pop(L_, 1);

                throw std::runtime_error(text);
            }
        }

        std::string path_;
        std::string modulePath_;
        Scene* scene_;

        lua_State* L_;
    };

    Script::Script(const std::string& path,
                   const std::string& modulePath,
                   Scene* scene)
    : impl_(new Impl(path, modulePath, scene))
    {
    }

    Script::~Script()
    {
        delete impl_;
    }

    bool Script::init()
    {
        impl_->L_ = ::lua_open();

        if (!impl_->L_) {
            LOG4CPLUS_ERROR(logger(), "Unable to create lua_State");

            return false;
        }

        luaL_openlibs(impl_->L_);

        try
        {
            luabind::open(impl_->L_);

            luabind::set_pcall_callback(&errorHandler);

            impl_->bind();

            impl_->setPackagePaths();

            impl_->require("strict");

            impl_->require("vec2");

            impl_->createGlobalObjects();

            impl_->loadFile();
        }
        catch (const std::exception& e)
        {
            LOG4CPLUS_ERROR(logger(), e.what());

            return false;
        }

        return true;
    }

    bool Script::run()
    {
        int base = ::lua_gettop(impl_->L_);

        ::lua_pushcfunction(impl_->L_, &errorHandler);
        ::lua_insert(impl_->L_, base);

        int result = ::lua_pcall(impl_->L_, 0, 0, base);

        ::lua_remove(impl_->L_, base);

        if (result != 0) {
            ::lua_pop(impl_->L_, 1);
        }

        return (result == 0);
    }
}
