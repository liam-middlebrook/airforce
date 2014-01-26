#ifndef _SCENEOBJECTMANAGER_H_
#define _SCENEOBJECTMANAGER_H_

#include "af/Types.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <set>

namespace af
{
    class Scene;

    class SceneObject;
    typedef boost::shared_ptr<SceneObject> SceneObjectPtr;

    class SceneObjectManager : boost::noncopyable
    {
    public:
        typedef std::list<SceneObjectPtr>::iterator ParentCookie;

        SceneObjectManager();
        virtual ~SceneObjectManager();

        void addObject(const SceneObjectPtr& obj);

        void removeObject(const SceneObjectPtr& obj);

        void lock();

        void unlock();

        inline SceneObjectManager* parent() { return parent_; }
        inline void setParent(SceneObjectManager* value,
                              const ParentCookie& cookie = ParentCookie())
        {
            parent_ = value;
            parentCookie_ = cookie;
        }

        inline ParentCookie parentCookie() { return parentCookie_; }

        inline Scene* scene() { return scene_; }
        inline void setScene(Scene* value) { scene_ = value; }

        inline bool locked() const { return locked_; }

    private:
        virtual void doUnlock() = 0;

        void registerObject(const SceneObjectPtr& obj);

        void unregisterObject(const SceneObjectPtr& obj);

        SceneObjectManager* parent_;
        ParentCookie parentCookie_;

        Scene* scene_;

        bool locked_;

        std::list<SceneObjectPtr> objects_;

        std::set<SceneObjectPtr> objectsToAdd_;
        std::set<SceneObjectPtr> objectsToRemove_;
    };
}

#endif
