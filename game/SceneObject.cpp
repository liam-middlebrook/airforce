#include "SceneObject.h"
#include "Scene.h"

namespace af
{
    SceneObject::SceneObject()
    {
    }

    SceneObject::~SceneObject()
    {
    }

    void SceneObject::onAdd(Scene* scene)
    {
        scene_ = scene;
        body_ = init();
    }

    void SceneObject::onRemove()
    {
        if (body_) {
            destroy();
            scene_->world().DestroyBody(body_);
            body_ = NULL;
            scene_ = NULL;
        }
    }
}
