#include "PhasedComponentManager.h"
#include "PhasedComponent.h"

namespace af
{
    PhasedComponentManager::PhasedComponentManager()
    {
    }

    PhasedComponentManager::~PhasedComponentManager()
    {
    }

    void PhasedComponentManager::addComponent(const PhasedComponentPtr& component)
    {
        component->setManager(this, components_.insert(components_.end(), component));
    }

    void PhasedComponentManager::removeComponent(const PhasedComponentPtr& component)
    {
        components_.erase(component->managerCookie());
        component->setManager(NULL);
    }

    void PhasedComponentManager::update(float dt)
    {
        for (std::list<PhasedComponentPtr>::iterator it = components_.begin();
             it != components_.end();
             ++it ) {
            (*it)->update(dt);
        }
    }
}
