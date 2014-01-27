#include "PhysicsBallComponent.h"
#include "SceneObject.h"

namespace af
{
    PhysicsBallComponent::PhysicsBallComponent(const b2Vec2& pos,
                                               float size,
                                               bool fixedRotation)
    : pos_(pos),
      size_(size),
      fixedRotation_(fixedRotation),
      body_(NULL),
      fixture_(NULL)
    {
    }

    PhysicsBallComponent::~PhysicsBallComponent()
    {
    }

    void PhysicsBallComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitPhysicsBallComponent(shared_from_this());
    }

    void PhysicsBallComponent::onRegister()
    {
        b2BodyDef bodyDef = parent()->bodyDef();

        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = fixedRotation_;

        body_ = manager()->world().CreateBody(&bodyDef);

        b2CircleShape shape;

        shape.m_p = pos_;
        shape.m_radius = size_ / 2;

        b2FixtureDef fixtureDef;

        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;

        fixture_ = body_->CreateFixture(&fixtureDef);

        parent()->setBody(body_);
    }

    void PhysicsBallComponent::onUnregister()
    {
        body_->DestroyFixture(fixture_);
        manager()->world().DestroyBody(body_);

        fixture_ = NULL;
        body_ = NULL;

        parent()->setBody(NULL);
    }
}
