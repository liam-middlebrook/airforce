#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "ComponentVisitor.h"
#include <boost/noncopyable.hpp>

namespace af
{
    class SceneObject;
    class ComponentManager;

    class Component : boost::noncopyable
    {
    public:
        Component()
        : parent_(NULL)
        {
        }

        virtual ~Component() {}

        virtual void accept(ComponentVisitor& visitor) = 0;

        virtual ComponentManager* manager() = 0;

        inline SceneObject* parent() { return parent_; }
        inline const SceneObject* parent() const { return parent_; }
        inline void setParent(SceneObject* value) { parent_ = value; }

    private:
        SceneObject* parent_;
    };
}

#endif
