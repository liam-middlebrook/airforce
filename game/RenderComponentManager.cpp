#include "RenderComponentManager.h"
#include "RenderComponent.h"

namespace af
{
    RenderComponentManager::RenderComponentManager()
    {
    }

    RenderComponentManager::~RenderComponentManager()
    {
    }

    void RenderComponentManager::addComponent(const RenderComponentPtr& component)
    {
        component->setManager(this, components_.insert(components_.end(), component));
    }

    void RenderComponentManager::removeComponent(const RenderComponentPtr& component)
    {
        components_.erase(component->managerCookie());
        component->setManager(NULL);
    }

    void RenderComponentManager::update(float dt)
    {
        for (std::list<RenderComponentPtr>::iterator it = components_.begin();
             it != components_.end();
             ++it ) {
            (*it)->update(dt);
        }

        /*
         * TODO: query world, pick objects to render and call 'render'.
         */
    }
}
