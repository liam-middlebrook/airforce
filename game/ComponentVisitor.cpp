#include "ComponentVisitor.h"
#include "PhasedComponent.h"
#include "CameraComponent.h"
#include "PlayerComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsBallComponent.h"
#include "PhysicsPolygonComponent.h"
#include "PhysicsTerrainComponent.h"
#include "RenderComponent.h"
#include "RenderPolygonComponent.h"
#include "RenderTerrainComponent.h"

namespace af
{
    ComponentVisitor::ComponentVisitor()
    {
    }

    ComponentVisitor::~ComponentVisitor()
    {
    }

    void ComponentVisitor::visitCameraComponent(const CameraComponentPtr& component)
    {
        visitPhasedComponent(component);
    }

    void ComponentVisitor::visitPlayerComponent(const PlayerComponentPtr& component)
    {
        visitPhasedComponent(component);
    }

    void ComponentVisitor::visitPhysicsBallComponent(const PhysicsBallComponentPtr& component)
    {
        visitPhysicsComponent(component);
    }

    void ComponentVisitor::visitPhysicsPolygonComponent(const PhysicsPolygonComponentPtr& component)
    {
        visitPhysicsComponent(component);
    }

    void ComponentVisitor::visitPhysicsTerrainComponent(const PhysicsTerrainComponentPtr& component)
    {
        visitPhysicsComponent(component);
    }

    void ComponentVisitor::visitRenderPolygonComponent(const RenderPolygonComponentPtr& component)
    {
        visitRenderComponent(component);
    }

    void ComponentVisitor::visitRenderTerrainComponent(const RenderTerrainComponentPtr& component)
    {
        visitRenderComponent(component);
    }
}
