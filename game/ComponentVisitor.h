#ifndef _COMPONENTVISITOR_H_
#define _COMPONENTVISITOR_H_

#include "af/Types.h"
#include <boost/shared_ptr.hpp>

namespace af
{
    class Component;
    class PhasedComponent;
    class PlayerComponent;
    class SpriteComponent;
    class PhysicsComponent;
    class PhysicsBallComponent;
    class PhysicsPolygonComponent;
    class PhysicsTerrainComponent;
    class RenderComponent;
    class RenderImageComponent;
    class RenderPolygonComponent;
    class RenderTerrainComponent;

    typedef boost::shared_ptr<Component> ComponentPtr;
    typedef boost::shared_ptr<PhasedComponent> PhasedComponentPtr;
    typedef boost::shared_ptr<PlayerComponent> PlayerComponentPtr;
    typedef boost::shared_ptr<SpriteComponent> SpriteComponentPtr;
    typedef boost::shared_ptr<PhysicsComponent> PhysicsComponentPtr;
    typedef boost::shared_ptr<PhysicsBallComponent> PhysicsBallComponentPtr;
    typedef boost::shared_ptr<PhysicsPolygonComponent> PhysicsPolygonComponentPtr;
    typedef boost::shared_ptr<PhysicsTerrainComponent> PhysicsTerrainComponentPtr;
    typedef boost::shared_ptr<RenderComponent> RenderComponentPtr;
    typedef boost::shared_ptr<RenderImageComponent> RenderImageComponentPtr;
    typedef boost::shared_ptr<RenderPolygonComponent> RenderPolygonComponentPtr;
    typedef boost::shared_ptr<RenderTerrainComponent> RenderTerrainComponentPtr;

    class ComponentVisitor
    {
    public:
        ComponentVisitor();
        virtual ~ComponentVisitor();

        virtual void visitPhasedComponent(const PhasedComponentPtr& component) = 0;
        virtual void visitPlayerComponent(const PlayerComponentPtr& component);
        virtual void visitSpriteComponent(const SpriteComponentPtr& component);
        virtual void visitPhysicsComponent(const PhysicsComponentPtr& component) = 0;
        virtual void visitPhysicsBallComponent(const PhysicsBallComponentPtr& component);
        virtual void visitPhysicsPolygonComponent(const PhysicsPolygonComponentPtr& component);
        virtual void visitPhysicsTerrainComponent(const PhysicsTerrainComponentPtr& component);
        virtual void visitRenderComponent(const RenderComponentPtr& component) = 0;
        virtual void visitRenderImageComponent(const RenderImageComponentPtr& component);
        virtual void visitRenderPolygonComponent(const RenderPolygonComponentPtr& component);
        virtual void visitRenderTerrainComponent(const RenderTerrainComponentPtr& component);
    };
}

#endif
