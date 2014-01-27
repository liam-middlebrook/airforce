#include "PhysicsPolygonComponent.h"
#include "SceneObject.h"

namespace af
{
    PhysicsPolygonComponent::PhysicsPolygonComponent(const Points& points)
    : points_(points),
      body_(NULL),
      fixture_(NULL)
    {
    }

    PhysicsPolygonComponent::~PhysicsPolygonComponent()
    {
    }

    void PhysicsPolygonComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitPhysicsPolygonComponent(shared_from_this());
    }

    void PhysicsPolygonComponent::onRegister()
    {
        b2BodyDef bodyDef = parent()->bodyDef();

        bodyDef.type = b2_dynamicBody;

        body_ = manager()->world().CreateBody(&bodyDef);

        b2PolygonShape shape;

        shape.Set(&points_[0], points_.size());

        b2FixtureDef fixtureDef;

        fixtureDef.shape = &shape;
        fixtureDef.density = 10.0f;

        fixture_ = body_->CreateFixture(&fixtureDef);

        parent()->setBody(body_);
    }

    void PhysicsPolygonComponent::onUnregister()
    {
        body_->DestroyFixture(fixture_);
        manager()->world().DestroyBody(body_);

        fixture_ = NULL;
        body_ = NULL;

        parent()->setBody(NULL);
    }
}
