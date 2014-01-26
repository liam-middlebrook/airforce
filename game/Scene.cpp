#include "Scene.h"
#include "SceneObject.h"
#include "Renderer.h"
#include "Player.h"
#include <cmath>

namespace af
{
    Scene::Scene()
    {
        /*
         * TODO: create ComponentManager list here.
         */
    }

    Scene::~Scene()
    {

    }

    void Scene::registerComponent(const ComponentPtr& component)
    {
        /*
         * TODO: add to apropriate component manager.
         */
    }

    void Scene::unregisterComponent(const ComponentPtr& component)
    {
        /*
         * TODO: remove from component manager;
         */
    }

    void Scene::update(float dt)
    {
        /*
         * TODO: lock() , call all componentmanagers, unlock()
         */
    }

    void Scene::doUnlock()
    {
    }
}
