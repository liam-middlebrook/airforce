#include "PhasedComponentManager.h"
#include "PhasedComponent.h"

namespace af
{
    PhasedComponentManager::PhasedComponentManager()
    {
    }

    PhasedComponentManager::~PhasedComponentManager()
    {
        assert(components_.empty());
    }

    void PhasedComponentManager::addComponent(const ComponentPtr& component)
    {
        PhasedComponentPtr phasedComponent = boost::dynamic_pointer_cast<PhasedComponent>(component);
        assert(phasedComponent);

        assert(!component->manager());

        components_.insert(phasedComponent);
        phasedComponent->setManager(this);
    }

    void PhasedComponentManager::removeComponent(const ComponentPtr& component)
    {
        PhasedComponentPtr phasedComponent = boost::dynamic_pointer_cast<PhasedComponent>(component);
        assert(phasedComponent);

        if (components_.erase(phasedComponent)) {
            phasedComponent->setManager(NULL);
        }
    }

    void PhasedComponentManager::update(float dt)
    {
        for (std::set<PhasedComponentPtr>::iterator it = components_.begin();
             it != components_.end();
             ++it ) {
            (*it)->update(dt);
        }
    }
}
