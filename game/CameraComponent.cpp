#include "CameraComponent.h"
#include "SceneObject.h"
#include "Renderer.h"
#include <cmath>

namespace af
{
    CameraComponent::CameraComponent(float width, float height)
    : PhasedComponent(PhasePreRender),
      sizeD2_(width / 2, height / 2),
      followD2_(sizeD2_)
    {
    }

    CameraComponent::~CameraComponent()
    {
    }

    void CameraComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitCameraComponent(shared_from_this());
    }

    void CameraComponent::update(float dt)
    {
        if (target_) {
            b2Vec2 relPos = target_->pos() - parent()->pos();

            if ((std::fabs(relPos.x) > followD2_.x) ||
                (std::fabs(relPos.y) > followD2_.y)) {
                parent()->setPos(parent()->pos() + target_->pos() - targetPrevPos_);
            }

            targetPrevPos_ = target_->pos();
        }

        renderer.lookAt(parent()->pos());
    }

    b2AABB CameraComponent::getAABB() const
    {
        b2Vec2 pos(0.0f, 0.0f);

        if (parent()) {
            pos = parent()->pos();
        }

        b2AABB aabb;

        aabb.lowerBound = pos - sizeD2_;
        aabb.upperBound = pos + sizeD2_;

        return aabb;
    }

    void CameraComponent::setTarget(const SceneObjectPtr& target)
    {
        target_ = target;
        targetPrevPos_ = target->pos();
    }
}
