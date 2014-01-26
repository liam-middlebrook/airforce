#ifndef _RENDERCOMPONENTMANAGER_H_
#define _RENDERCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include <list>

namespace af
{
    class RenderComponentManager : public ComponentManager
    {
    public:
        RenderComponentManager();
        ~RenderComponentManager();

        virtual void addComponent(const RenderComponentPtr& component);

        virtual void removeComponent(const RenderComponentPtr& component);

        virtual void update(float dt);

    private:
        std::list<RenderComponentPtr> components_;
    };
}

#endif
