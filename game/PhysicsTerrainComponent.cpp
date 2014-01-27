#include "PhysicsTerrainComponent.h"
#include "SceneObject.h"

namespace af
{
    PhysicsTerrainComponent::PhysicsTerrainComponent(const std::vector<Points>& chains)
    : chains_(chains)
    {
    }

    PhysicsTerrainComponent::~PhysicsTerrainComponent()
    {
    }

    void PhysicsTerrainComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitPhysicsTerrainComponent(shared_from_this());
    }

    void PhysicsTerrainComponent::onRegister()
    {
        b2BodyDef bodyDef = parent()->bodyDef();

        bodyDef.type = b2_staticBody;

        body_ = manager()->world().CreateBody(&bodyDef);

        for (std::vector<Points>::const_iterator it = chains_.begin();
             it != chains_.end();
             ++it) {
            b2ChainShape shape;

            shape.CreateLoop(&(*it)[0], it->size());

            b2FixtureDef fixtureDef;

            fixtureDef.shape = &shape;
            fixtureDef.density = 1.0f;

            fixtures_.push_back(body_->CreateFixture(&fixtureDef));
        }

        parent()->setBody(body_);
    }

    void PhysicsTerrainComponent::onUnregister()
    {
        for (std::vector<b2Fixture*>::const_iterator it = fixtures_.begin();
             it != fixtures_.end();
             ++it) {
            body_->DestroyFixture(*it);
        }

        fixtures_.clear();

        manager()->world().DestroyBody(body_);

        body_ = NULL;

        parent()->setBody(NULL);
    }
}
