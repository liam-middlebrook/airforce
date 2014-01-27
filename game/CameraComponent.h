#ifndef _CAMERACOMPONENT_H_
#define _CAMERACOMPONENT_H_

#include "PhasedComponent.h"
#include "SceneObject.h"
#include <Box2D/Box2D.h>
#include <boost/enable_shared_from_this.hpp>

namespace af
{
    class CameraComponent : public boost::enable_shared_from_this<CameraComponent>,
                            public PhasedComponent
    {
    public:
        CameraComponent(float width, float height);
        ~CameraComponent();

        virtual void accept(ComponentVisitor& visitor);

        virtual void update(float dt);

        b2AABB getAABB() const;

        void setTarget(const SceneObjectPtr& target);

    private:
        b2Vec2 sizeD2_;
        b2Vec2 followD2_;

        SceneObjectPtr target_;

        b2Vec2 targetPrevPos_;
    };
}

#endif
