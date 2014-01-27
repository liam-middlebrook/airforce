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
        assert(components_.empty());
    }

    void PhysicsComponentManager::addComponent(const ComponentPtr& component)
    {
        PhysicsComponentPtr physicsComponent = boost::dynamic_pointer_cast<PhysicsComponent>(component);
        assert(physicsComponent);

        assert(!component->manager());

        components_.insert(physicsComponent);
        physicsComponent->setManager(this);
    }

    void PhysicsComponentManager::removeComponent(const ComponentPtr& component)
    {
        PhysicsComponentPtr physicsComponent = boost::dynamic_pointer_cast<PhysicsComponent>(component);
        assert(physicsComponent);

        if (components_.erase(physicsComponent)) {
            physicsComponent->setManager(NULL);
        }
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
