#include "PlayerComponent.h"
#include "InputManager.h"
#include "SceneObject.h"

namespace af
{
    PlayerComponent::PlayerComponent()
    : PhasedComponent(PhaseThink)
    {
    }

    PlayerComponent::~PlayerComponent()
    {
    }

    void PlayerComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitPlayerComponent(shared_from_this());
    }

    void PlayerComponent::update(float dt)
    {
        if (inputManager.leftPressed()) {
            parent()->setAngle(parent()->angle() + rotateSpeed_ * dt);
        } else if (inputManager.rightPressed()) {
            parent()->setAngle(parent()->angle() - rotateSpeed_ * dt);
        }

        parent()->setLinearVelocity(b2Mul(parent()->getTransform().q, b2Vec2(moveSpeed_, 0.0f)));
    }
}
