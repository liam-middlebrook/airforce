#include "SceneObject.h"
#include "Scene.h"

namespace af
{
    SceneObject::SceneObject()
    : body_(NULL)
    {
    }

    SceneObject::~SceneObject()
    {
        while (!components_.empty()) {
            ComponentPtr component = *components_.begin();

            removeComponent(component);
        }
    }

    void SceneObject::addComponent(const ComponentPtr& component)
    {
        if (locked()) {
            componentsToAdd_.insert(component);
        } else {
            component->setParent(this, components_.insert(components_.end(), component));

            if (scene()) {
                scene()->registerComponent(component);
            }
        }
    }

    void SceneObject::removeComponent(const ComponentPtr& component)
    {
        if (locked()) {
            componentsToRemove_.insert(component);
        } else {
            if (scene()) {
                scene()->unregisterComponent(component);
            }

            components_.erase(component->parentCookie());
            component->setParent(NULL);
        }
    }

    void SceneObject::doUnlock()
    {
        for (std::set<ComponentPtr>::iterator it = componentsToAdd_.begin();
             it != componentsToAdd_.end();
             ++it ) {
            addComponent(*it);
        }

        for (std::set<ComponentPtr>::iterator it = componentsToRemove_.begin();
             it != componentsToRemove_.end();
             ++it ) {
            removeComponent(*it);
        }

        componentsToAdd_.clear();
        componentsToRemove_.clear();
    }
}
