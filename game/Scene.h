#ifndef _SCENE_H_
#define _SCENE_H_

#include "SceneObjectManager.h"
#include "Component.h"

namespace af
{
    class Scene : public SceneObjectManager
    {
    public:
        Scene(float cameraWidth, float cameraHeight);
        ~Scene();

        void registerComponent(const ComponentPtr& component);

        void unregisterComponent(const ComponentPtr& component);

        void update(float dt);

        SceneObjectPtr& camera();

    private:
        virtual void doUnlock();

        class Impl;
        Impl* impl_;
    };

    typedef boost::shared_ptr<Scene> ScenePtr;
}

#endif
