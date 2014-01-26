#include "PhysicsComponentManager.h"
#include "PhysicsComponent.h"
#include <cmath>

namespace af
{
    PhysicsComponentManager::PhysicsComponentManager()
    : world_(b2Vec2(0.0f, 0.0f)),
      fixedTimestepAccumulator_(0.0f)
    {
        world_.SetAutoClearForces(false);
    }

    PhysicsComponentManager::~PhysicsComponentManager()
    {
    }

    void PhysicsComponentManager::addComponent(const PhysicsComponentPtr& component)
    {
        component->setManager(this, components_.insert(components_.end(), component));
    }

    void PhysicsComponentManager::removeComponent(const PhysicsComponentPtr& component)
    {
        components_.erase(component->managerCookie());
        component->setManager(NULL);
    }

    void PhysicsComponentManager::update(float dt)
    {
        fixedTimestepAccumulator_ += dt;

        UInt32 numSteps = std::floor(fixedTimestepAccumulator_ / fixedTimestep_);

        if (numSteps > 0) {
            fixedTimestepAccumulator_ -= fixedTimestep_ * numSteps;
        }

        /*
         * static_cast<UInt32> is needed because of some stupid gcc bug.
         */
        UInt32 numStepsClamped = (std::min)(numSteps, static_cast<UInt32>(maxSteps_));

        for (UInt32 i = 0; i < numStepsClamped; ++i) {
            world_.Step(fixedTimestep_, 6, 2);
        }

        world_.ClearForces();
    }
}
