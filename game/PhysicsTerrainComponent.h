#ifndef _PHYSICSTERRAINCOMPONENT_H_
#define _PHYSICSTERRAINCOMPONENT_H_

#include "PhysicsComponent.h"
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace af
{
    class PhysicsTerrainComponent : public boost::enable_shared_from_this<PhysicsTerrainComponent>,
                                    public PhysicsComponent
    {
    public:
        PhysicsTerrainComponent(const std::vector<Points>& chains);
        ~PhysicsTerrainComponent();

        virtual void accept(ComponentVisitor& visitor);

    private:
        virtual void onRegister();

        virtual void onUnregister();

        std::vector<Points> chains_;

        b2Body* body_;
        std::vector<b2Fixture*> fixtures_;
    };
}

#endif
