#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include "Types.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace af
{
    class Scene;

    class Script : boost::noncopyable
    {
    public:
        Script(const std::string& path,
               const std::string& modulePath,
               Scene* scene);
        ~Script();

        bool init();

        bool run();

    private:
        class Impl;
        Impl* impl_;
    };

    typedef boost::shared_ptr<Script> ScriptPtr;
}

#endif
