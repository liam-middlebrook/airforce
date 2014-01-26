#ifndef _COMPONENTMANAGER_H_
#define _COMPONENTMANAGER_H_

#include "Component.h"

namespace af
{
    class Scene;

    class ComponentManager : boost::noncopyable
    {
    public:
        ComponentManager()
        : scene_(NULL)
        {
        }

        virtual ~ComponentManager() {}

        virtual void addComponent(const ComponentPtr& component) = 0;

        virtual void removeComponent(const ComponentPtr& component) = 0;

        virtual void update(float dt) = 0;

        inline Scene* scene() { return scene_; }
        inline void setScene(Scene* value) { scene_ = value; }

    private:
        Scene* scene_;
    };

    typedef boost::shared_ptr<ComponentManager> ComponentManagerPtr;
}

#endif
