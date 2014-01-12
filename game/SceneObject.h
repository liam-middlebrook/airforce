#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "af/Types.h"
#include <boost/noncopyable.hpp>
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

        virtual void render() = 0;

    private:
        virtual b2Body* init() = 0;

        Scene* scene_;

        b2Body* body_;
    };
}

#endif
