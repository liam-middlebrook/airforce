#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "af/Types.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>

namespace af
{
    class Scene;

    class SceneObject : boost::noncopyable
    {
    public:
        SceneObject();
        virtual ~SceneObject();

        inline Scene* scene() const { return scene_; }

        inline b2Body* body() const { return body_; }

        /*
         * Called by 'Scene::add'.
         */
        void onAdd(Scene* scene);

        /*
         * Called when removed from scene.
         */
        void onRemove();

        virtual void update(float dt) = 0;

        virtual void render() = 0;

    private:
        virtual b2Body* init() = 0;

        virtual void destroy() = 0;

        Scene* scene_;

        b2Body* body_;
    };

    typedef boost::shared_ptr<SceneObject> SceneObjectPtr;
}

#endif
