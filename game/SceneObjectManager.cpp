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
        while (!objects_.empty()) {
            SceneObjectPtr obj = *objects_.begin();

            removeObject(obj);
        }
    }

    void SceneObjectManager::addObject(const SceneObjectPtr& obj)
    {
        if (locked_) {
            objectsToAdd_.insert(obj);
        } else {
            obj->setParent(this, objects_.insert(objects_.end(), obj));

            if (scene()) {
                registerObject(obj);
            }
        }
    }

    void SceneObjectManager::removeObject(const SceneObjectPtr& obj)
    {
        if (locked_) {
            objectsToRemove_.insert(obj);
        } else {
            if (scene()) {
                unregisterObject(obj);
            }

            objects_.erase(obj->parentCookie());
            obj->setParent(NULL);
        }
    }

    void SceneObjectManager::lock()
    {
        locked_ = true;

        for (std::list<SceneObjectPtr>::iterator it = objects_.begin();
             it != objects_.end();
             ++it ) {
            (*it)->lock();
        }
    }

    void SceneObjectManager::unlock()
    {
        for (std::list<SceneObjectPtr>::reverse_iterator it = objects_.rbegin();
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

        for (std::list<SceneObjectPtr>::iterator it = obj->objects_.begin();
             it != obj->objects_.end();
             ++it) {
            registerObject(*it);
        }

        for (std::list<ComponentPtr>::iterator it = obj->components().begin();
             it != obj->components().end();
             ++it) {
            scene()->registerComponent(*it);
        }
    }

    void SceneObjectManager::unregisterObject(const SceneObjectPtr& obj)
    {
        for (std::list<ComponentPtr>::iterator it = obj->components().begin();
             it != obj->components().end();
             ++it) {
            scene()->unregisterComponent(*it);
        }

        for (std::list<SceneObjectPtr>::iterator it = obj->objects_.begin();
             it != obj->objects_.end();
             ++it) {
            unregisterObject(*it);
        }

        obj->setScene(NULL);
    }
}
