#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "SceneObjectManager.h"
#include "Component.h"
#include <Box2D/Box2D.h>
#include <list>
#include <set>

namespace af
{
    class SceneObject : public SceneObjectManager
    {
    public:
        SceneObject();
        virtual ~SceneObject();

        void addComponent(const ComponentPtr& component);

        void removeComponent(const ComponentPtr& component);

        inline std::list<ComponentPtr>& components() { return components_; }

    private:
        virtual void doUnlock();

        b2BodyDef bodyDef_;
        b2Body* body_;

        std::list<ComponentPtr> components_;

        std::set<ComponentPtr> componentsToAdd_;
        std::set<ComponentPtr> componentsToRemove_;
    };
}

#endif
