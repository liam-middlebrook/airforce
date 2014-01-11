#include "Scene.h"
#include "SceneObject.h"
#include <cmath>

namespace af
{
    Scene::Scene()
    : world_(b2Vec2(0.0f, 0.0f)),
      fixedTimestepAccumulator_(0.0f)
    {
        world_.SetAutoClearForces(false);
    }

    Scene::~Scene()
    {
    }

    void Scene::add(SceneObject* object)
    {
        object->onAdd(this);

        objects_.push_back(object);
    }

    void Scene::update(float dt)
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
