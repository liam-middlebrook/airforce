#ifndef _PHYSICSPOLYGONCOMPONENT_H_
#define _PHYSICSPOLYGONCOMPONENT_H_

#include "PhysicsComponent.h"
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace af
{
    class PhysicsPolygonComponent : public boost::enable_shared_from_this<PhysicsPolygonComponent>,
                                    public PhysicsComponent
    {
    public:
        PhysicsPolygonComponent(const Points& points);
        ~PhysicsPolygonComponent();

        virtual void accept(ComponentVisitor& visitor);

    private:
        virtual void onRegister();

        virtual void onUnregister();

        Points points_;

        b2Body* body_;
        b2Fixture* fixture_;
    };
}

#endif
