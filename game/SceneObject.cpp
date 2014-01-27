#include "SceneObject.h"
#include "Scene.h"

namespace af
{
    SceneObject::SceneObject(SceneObjectType type, const b2Vec2& pos, float angle)
    : type_(type),
      body_(NULL)
    {
        bodyDef_.position = pos;
        bodyDef_.angle = angle;
    }

    SceneObject::~SceneObject()
    {
        while (!components_.empty()) {
            ComponentPtr component = *components_.begin();

            removeComponent(component);
        }
    }

    void SceneObject::addComponent(const ComponentPtr& component)
    {
        if (locked()) {
            componentsToAdd_.insert(component);
        } else {
            assert(!component->parent());

            components_.insert(component);
            component->setParent(this);

            if (scene()) {
                scene()->registerComponent(component);
            }
        }
    }

    void SceneObject::removeComponent(const ComponentPtr& component)
    {
        if (locked()) {
            componentsToRemove_.insert(component);
        } else if (components_.erase(component)) {
            if (scene()) {
                scene()->unregisterComponent(component);
            }

            component->setParent(NULL);
        }
    }

    void SceneObject::setBody(b2Body* value)
    {
        if (value || !body_) {
            body_ = value;
            return;
        }

        bodyDef_ = b2BodyDef();

        bodyDef_.position = body_->GetPosition();
        bodyDef_.angle = body_->GetAngle();
        bodyDef_.linearVelocity = body_->GetLinearVelocity();
        bodyDef_.angularVelocity = body_->GetAngularVelocity();
        bodyDef_.linearDamping = body_->GetLinearDamping();
        bodyDef_.angularDamping = body_->GetAngularDamping();
        bodyDef_.allowSleep = body_->IsSleepingAllowed();
        bodyDef_.awake = body_->IsAwake();
        bodyDef_.fixedRotation = body_->IsFixedRotation();
        bodyDef_.bullet = body_->IsBullet();
        bodyDef_.type = body_->GetType();
        bodyDef_.active = body_->IsActive();
        bodyDef_.gravityScale = body_->GetGravityScale();

        body_ = NULL;
    }

    b2Transform SceneObject::getTransform() const
    {
        if (body_) {
            return body_->GetTransform();
        } else {
            return b2Transform(bodyDef_.position, b2Rot(bodyDef_.angle));
        }
    }

    void SceneObject::setTransform(const b2Vec2& pos, float32 angle)
    {
        if (body_) {
            body_->SetTransform(pos, angle);
        } else {
            bodyDef_.position = pos;
            bodyDef_.angle = angle;
        }
    }

    const b2Vec2& SceneObject::pos() const
    {
        if (body_) {
            return body_->GetPosition();
        } else {
            return bodyDef_.position;
        }
    }

    void SceneObject::setPos(const b2Vec2& value)
    {
        if (body_) {
            body_->SetTransform(value, body_->GetAngle());
        } else {
            bodyDef_.position = value;
        }
    }

    float SceneObject::angle() const
    {
        if (body_) {
            return body_->GetAngle();
        } else {
            return bodyDef_.angle;
        }
    }

    void SceneObject::setAngle(float value)
    {
        if (body_) {
            body_->SetTransform(body_->GetPosition(), value);
        } else {
            bodyDef_.angle = value;
        }
    }

    const b2Vec2& SceneObject::linearVelocity() const
    {
        if (body_) {
            return body_->GetLinearVelocity();
        } else {
            return bodyDef_.linearVelocity;
        }
    }

    void SceneObject::setLinearVelocity(const b2Vec2& value)
    {
        if (body_) {
            body_->SetLinearVelocity(value);
        } else {
            bodyDef_.linearVelocity = value;
        }
    }

    float SceneObject::angularVelocity() const
    {
        if (body_) {
            return body_->GetAngularVelocity();
        } else {
            return bodyDef_.angularVelocity;
        }
    }

    void SceneObject::setAngularVelocity(float value)
    {
        if (body_) {
            body_->SetAngularVelocity(value);
        } else {
            bodyDef_.angularVelocity = value;
        }
    }

    float SceneObject::linearDamping() const
    {
        if (body_) {
            return body_->GetLinearDamping();
        } else {
            return bodyDef_.linearDamping;
        }
    }

    void SceneObject::setLinearDamping(float value)
    {
        if (body_) {
            body_->SetLinearDamping(value);
        } else {
            bodyDef_.linearDamping = value;
        }
    }

    float SceneObject::angularDamping() const
    {
        if (body_) {
            return body_->GetAngularDamping();
        } else {
            return bodyDef_.angularDamping;
        }
    }

    void SceneObject::setAngularDamping(float value)
    {
        if (body_) {
            body_->SetAngularDamping(value);
        } else {
            bodyDef_.angularDamping = value;
        }
    }

    void SceneObject::doUnlock()
    {
        for (std::set<ComponentPtr>::iterator it = componentsToAdd_.begin();
             it != componentsToAdd_.end();
             ++it ) {
            addComponent(*it);
        }

        for (std::set<ComponentPtr>::iterator it = componentsToRemove_.begin();
             it != componentsToRemove_.end();
             ++it ) {
            removeComponent(*it);
        }

        componentsToAdd_.clear();
        componentsToRemove_.clear();
    }
}
