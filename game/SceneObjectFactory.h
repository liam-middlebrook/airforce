#ifndef _SCENEOBJECTFACTORY_H_
#define _SCENEOBJECTFACTORY_H_

#include "Single.h"
#include "SceneObject.h"
#include "af/Types.h"
#include <Box2D/Box2D.h>
#include <vector>

namespace af
{
    class SceneObjectFactory : public Single<SceneObjectFactory>
    {
    public:
        SceneObjectFactory();
        ~SceneObjectFactory();

        bool init();

        void shutdown();

        SceneObjectPtr createPlayer(const b2Vec2& pos);

        SceneObjectPtr createRock(const b2Vec2& pos,
                                  const std::vector<b2Vec2>& points);
    };

    extern SceneObjectFactory sceneObjectFactory;
}

#endif
