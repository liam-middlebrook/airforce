#ifndef _PHASEDCOMPONENT_H_
#define _PHASEDCOMPONENT_H_

#include "PhasedComponentManager.h"
#include <list>

namespace af
{
    enum Phase
    {
        PhaseThink,
        /*PhasePhysics,*/ /* Handled by PhysicsComponent */
        PhasePreRender,
        /*PhaseRender,*/ /* Handled by RenderComponent */
    };

    class PhasedComponent : public Component
    {
    public:
        typedef std::list<PhasedComponentPtr>::iterator ManagerCookie;

        explicit PhasedComponent(Phase phase)
        : phase_(phase),
          manager_(NULL)
        {
        }

        virtual ~PhasedComponent()
        {
        }

        inline Phase phase() const { return phase_; }

        virtual PhasedComponentManager* manager() { return manager_; }
        inline void setManager(PhasedComponentManager* value,
                               const ManagerCookie& cookie = ManagerCookie())
        {
            manager_ = value;
            managerCookie_ = cookie;
        }

        inline ManagerCookie managerCookie() const { return managerCookie_; }

        virtual void update(float dt) = 0;

    private:
        Phase phase_;

        PhasedComponentManager* manager_;
        ManagerCookie managerCookie_;
    };
}

#endif
