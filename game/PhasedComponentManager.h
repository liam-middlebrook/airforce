#ifndef _PHASEDCOMPONENTMANAGER_H_
#define _PHASEDCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include <list>

namespace af
{
    class PhasedComponentManager : public ComponentManager
    {
    public:
        PhasedComponentManager();
        ~PhasedComponentManager();

        virtual void addComponent(const PhasedComponentPtr& component);

        virtual void removeComponent(const PhasedComponentPtr& component);

        virtual void update(float dt);

    private:
        std::list<PhasedComponentPtr> components_;
    };
}

#endif
