#ifndef _SCENE_H_
#define _SCENE_H_

#include "af/Types.h"
#include "SceneObject.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <Box2D/Box2D.h>

namespace af
{
    class Scene : boost::noncopyable
    {
    public:
        Scene();
        ~Scene();

        void add(const SceneObjectPtr& object);

        SceneObjectPtr findPlayer();

        void update(float dt);

        void render();

        inline b2World& world() { return world_; }

    private:
        /*
         * Physics will step with this rate.
         */
        static const float fixedTimestep_ = 1.0f / 60.0f;

        /*
         * Maximum number of physics steps to avoid "spiral of death".
         */
        static const UInt32 maxSteps_ = 5;

        b2World world_;

        std::vector<SceneObjectPtr> objects_;

        float fixedTimestepAccumulator_;
    };

    typedef boost::shared_ptr<Scene> ScenePtr;
}

#endif
