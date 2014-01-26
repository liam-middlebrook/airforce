#ifndef _PHYSICSCOMPONENTMANAGER_H_
#define _PHYSICSCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include <Box2D/Box2D.h>
#include <list>

namespace af
{
    class PhysicsComponentManager : public ComponentManager
    {
    public:
        PhysicsComponentManager();
        ~PhysicsComponentManager();

        virtual void addComponent(const PhysicsComponentPtr& component);

        virtual void removeComponent(const PhysicsComponentPtr& component);

        virtual void update(float dt);

        inline b2World& world() { return world_; }

    private:
        /*
         * Physics will step with this rate.
         */
        static const float fixedTimestep_ = 1.0f / 60.0f;

        /*
         * Maximum number of physics steps to avoid "spiral of death".
         */
        static const UInt32 maxSteps_ = 5;

        b2World world_;

        float fixedTimestepAccumulator_;

        std::list<PhysicsComponentPtr> components_;
    };
}

#endif
