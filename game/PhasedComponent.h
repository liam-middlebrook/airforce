#ifndef _PHASEDCOMPONENT_H_
#define _PHASEDCOMPONENT_H_

#include "PhasedComponentManager.h"

namespace af
{
    enum Phase
    {
        PhaseThink = 0,
        /*PhasePhysics,*/ /* Handled by PhysicsComponent */
        PhasePostPhysics,
        PhasePreRender,
        /*PhaseRender,*/ /* Handled by RenderComponent */
    };

    static const int PhaseMax = PhasePreRender;

    class PhasedComponent : public Component
    {
    public:
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
        inline void setManager(PhasedComponentManager* value) { manager_ = value; }

        virtual void update(float dt) = 0;

    private:
        Phase phase_;

        PhasedComponentManager* manager_;
    };
}

#endif
