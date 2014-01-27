#ifndef _PHYSICSBALLCOMPONENT_H_
#define _PHYSICSBALLCOMPONENT_H_

#include "PhysicsComponent.h"
#include <boost/enable_shared_from_this.hpp>

namespace af
{
    class PhysicsBallComponent : public boost::enable_shared_from_this<PhysicsBallComponent>,
                                 public PhysicsComponent
    {
    public:
        PhysicsBallComponent(const b2Vec2& pos,
                             float size,
                             bool fixedRotation = false);
        ~PhysicsBallComponent();

        virtual void accept(ComponentVisitor& visitor);

    private:
        virtual void onRegister();

        virtual void onUnregister();

        b2Vec2 pos_;
        float size_;
        bool fixedRotation_;

        b2Body* body_;
        b2Fixture* fixture_;
    };
}

#endif
