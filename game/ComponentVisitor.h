#ifndef _COMPONENTVISITOR_H_
#define _COMPONENTVISITOR_H_

#include "af/Types.h"
#include <boost/shared_ptr.hpp>

namespace af
{
    class Component;
    class PhasedComponent;
    class CameraComponent;
    class PlayerComponent;
    class PhysicsComponent;
    class PhysicsBallComponent;
    class PhysicsPolygonComponent;
    class RenderComponent;
    class RenderPolygonComponent;

    typedef boost::shared_ptr<Component> ComponentPtr;
    typedef boost::shared_ptr<PhasedComponent> PhasedComponentPtr;
    typedef boost::shared_ptr<CameraComponent> CameraComponentPtr;
    typedef boost::shared_ptr<PlayerComponent> PlayerComponentPtr;
    typedef boost::shared_ptr<PhysicsComponent> PhysicsComponentPtr;
    typedef boost::shared_ptr<PhysicsBallComponent> PhysicsBallComponentPtr;
    typedef boost::shared_ptr<PhysicsPolygonComponent> PhysicsPolygonComponentPtr;
    typedef boost::shared_ptr<RenderComponent> RenderComponentPtr;
    typedef boost::shared_ptr<RenderPolygonComponent> RenderPolygonComponentPtr;

    class ComponentVisitor
    {
    public:
        ComponentVisitor();
        virtual ~ComponentVisitor();

        virtual void visitPhasedComponent(const PhasedComponentPtr& component) = 0;
        virtual void visitCameraComponent(const CameraComponentPtr& component);
        virtual void visitPlayerComponent(const PlayerComponentPtr& component);
        virtual void visitPhysicsComponent(const PhysicsComponentPtr& component) = 0;
        virtual void visitPhysicsBallComponent(const PhysicsBallComponentPtr& component);
        virtual void visitPhysicsPolygonComponent(const PhysicsPolygonComponentPtr& component);
        virtual void visitRenderComponent(const RenderComponentPtr& component) = 0;
        virtual void visitRenderPolygonComponent(const RenderPolygonComponentPtr& component);
    };
}

#endif
