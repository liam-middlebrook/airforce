#ifndef _PLAYERCOMPONENT_H_
#define _PLAYERCOMPONENT_H_

#include "PhasedComponent.h"
#include <boost/enable_shared_from_this.hpp>
#include <cmath>

namespace af
{
    class PlayerComponent : public boost::enable_shared_from_this<PlayerComponent>,
                            public PhasedComponent
    {
    public:
        PlayerComponent();
        ~PlayerComponent();

        virtual void accept(ComponentVisitor& visitor);

        virtual void update(float dt);

    private:
        static const float moveSpeed_ = 30.0f;
        static const float rotateSpeed_ = M_PI;
    };
}

#endif
