#include "ComponentVisitor.h"
#include "PhasedComponent.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsBallComponent.h"
#include "PhysicsPolygonComponent.h"
#include "PhysicsTerrainComponent.h"
#include "RenderComponent.h"
#include "RenderImageComponent.h"
#include "RenderPolygonComponent.h"
#include "RenderTerrainComponent.h"

namespace af
{
    /*
     * TODO: fix.
     */


    ComponentVisitor::ComponentVisitor()
    {
    }

    ComponentVisitor::~ComponentVisitor()
    {
    }

    void ComponentVisitor::visitPlayerComponent(const PlayerComponentPtr& component)
    {
        //visitPhasedComponent(component);
    }

    void ComponentVisitor::visitSpriteComponent(const SpriteComponentPtr& component)
    {
        //visitPhasedComponent(component);
    }

    void ComponentVisitor::visitPhysicsBallComponent(const PhysicsBallComponentPtr& component)
    {
        //visitPhysicsComponent(component);
    }

    void ComponentVisitor::visitPhysicsPolygonComponent(const PhysicsPolygonComponentPtr& component)
    {
        //visitPhysicsComponent(component);
    }

    void ComponentVisitor::visitPhysicsTerrainComponent(const PhysicsTerrainComponentPtr& component)
    {
        //visitPhysicsComponent(component);
    }

    void ComponentVisitor::visitRenderImageComponent(const RenderImageComponentPtr& component)
    {
        //visitRenderComponent(component);
    }

    void ComponentVisitor::visitRenderPolygonComponent(const RenderPolygonComponentPtr& component)
    {
        //visitRenderComponent(component);
    }

    void ComponentVisitor::visitRenderTerrainComponent(const RenderTerrainComponentPtr& component)
    {
        //visitRenderComponent(component);
    }
}
