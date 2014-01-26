#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "ComponentVisitor.h"
#include <boost/noncopyable.hpp>
#include <list>

namespace af
{
    class SceneObject;
    class ComponentManager;

    class Component : boost::noncopyable
    {
    public:
        typedef std::list<ComponentPtr>::iterator ParentCookie;

        Component()
        : parent_(NULL)
        {
        }

        virtual ~Component() {}

        virtual void accept(ComponentVisitor& visitor) = 0;

        virtual ComponentManager* manager() = 0;

        inline SceneObject* parent() { return parent_; }
        inline void setParent(SceneObject* value,
                              const ParentCookie& cookie = ParentCookie())
        {
            parent_ = value;
            parentCookie_ = cookie;
        }

        inline ParentCookie parentCookie() { return parentCookie_; }

    private:
        SceneObject* parent_;
        ParentCookie parentCookie_;
    };
}

#endif
