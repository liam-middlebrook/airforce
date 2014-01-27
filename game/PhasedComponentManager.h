#ifndef _PHASEDCOMPONENTMANAGER_H_
#define _PHASEDCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include <set>

namespace af
{
    class PhasedComponentManager : public ComponentManager
    {
    public:
        PhasedComponentManager();
        ~PhasedComponentManager();

        virtual void addComponent(const ComponentPtr& component);

        virtual void removeComponent(const ComponentPtr& component);

        virtual void update(float dt);

    private:
        std::set<PhasedComponentPtr> components_;
    };
}

#endif
