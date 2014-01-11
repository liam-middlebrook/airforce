#include "SceneObject.h"
#include "Scene.h"

namespace af
{
    SceneObject::SceneObject()
    {
    }

    SceneObject::~SceneObject()
    {
        if (body_) {
            scene_->world().DestroyBody(body_);
        }
    }

    void SceneObject::onAdd(Scene* scene)
    {
        scene_ = scene;
        body_ = init();
    }
}
