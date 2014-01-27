#include "SceneObjectManager.h"
#include "SceneObject.h"
#include "Scene.h"

namespace af
{
    SceneObjectManager::SceneObjectManager()
    : parent_(NULL),
      scene_(NULL),
      locked_(false)
    {
    }

    SceneObjectManager::~SceneObjectManager()
    {
        removeAllObjects();
    }

    void SceneObjectManager::addObject(const SceneObjectPtr& obj)
    {
        if (locked_) {
            objectsToAdd_.insert(obj);
        } else {
            assert(!obj->parent());

            objects_.insert(obj);
            obj->setParent(this);

            if (scene()) {
                registerObject(obj);
            }
        }
    }

    void SceneObjectManager::removeObject(const SceneObjectPtr& obj)
    {
        if (locked_) {
            objectsToRemove_.insert(obj);
        } else if (objects_.erase(obj)) {
            if (scene()) {
                unregisterObject(obj);
            }

            obj->setParent(NULL);
        }
    }

    void SceneObjectManager::removeAllObjects()
    {
        while (!objects_.empty()) {
            SceneObjectPtr obj = *objects_.begin();

            removeObject(obj);
        }
    }

    SceneObjectPtr SceneObjectManager::findObject(SceneObjectType type)
    {
        for (std::set<SceneObjectPtr>::iterator it = objects_.begin();
             it != objects_.end();
             ++it ) {
            if ((*it)->type() == type) {
                return *it;
            }
        }
        return SceneObjectPtr();
    }

    void SceneObjectManager::lock()
    {
        locked_ = true;

        for (std::set<SceneObjectPtr>::iterator it = objects_.begin();
             it != objects_.end();
             ++it ) {
            (*it)->lock();
        }
    }

    void SceneObjectManager::unlock()
    {
        for (std::set<SceneObjectPtr>::reverse_iterator it = objects_.rbegin();
             it != objects_.rend();
             ++it ) {
            (*it)->unlock();
        }

        locked_ = false;

        for (std::set<SceneObjectPtr>::iterator it = objectsToAdd_.begin();
             it != objectsToAdd_.end();
             ++it ) {
            addObject(*it);
        }

        for (std::set<SceneObjectPtr>::iterator it = objectsToRemove_.begin();
             it != objectsToRemove_.end();
             ++it ) {
            removeObject(*it);
        }

        objectsToAdd_.clear();
        objectsToRemove_.clear();

        doUnlock();
    }

    void SceneObjectManager::registerObject(const SceneObjectPtr& obj)
    {
        obj->setScene(scene());

        for (std::set<SceneObjectPtr>::iterator it = obj->objects_.begin();
             it != obj->objects_.end();
             ++it) {
            registerObject(*it);
        }

        for (std::set<ComponentPtr>::iterator it = obj->components().begin();
             it != obj->components().end();
             ++it) {
            scene()->registerComponent(*it);
        }
    }

    void SceneObjectManager::unregisterObject(const SceneObjectPtr& obj)
    {
        for (std::set<ComponentPtr>::iterator it = obj->components().begin();
             it != obj->components().end();
             ++it) {
            scene()->unregisterComponent(*it);
        }

        for (std::set<SceneObjectPtr>::iterator it = obj->objects_.begin();
             it != obj->objects_.end();
             ++it) {
            unregisterObject(*it);
        }

        obj->setScene(NULL);
    }
}
