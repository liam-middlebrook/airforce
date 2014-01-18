#include "SceneObjectFactory.h"
#include "Player.h"
#include "Rock.h"
#include "TextureManager.h"
#include <boost/make_shared.hpp>

namespace af
{
    SceneObjectFactory sceneObjectFactory;

    template <>
    Single<SceneObjectFactory>* Single<SceneObjectFactory>::single = NULL;

    SceneObjectFactory::SceneObjectFactory()
    {
    }

    SceneObjectFactory::~SceneObjectFactory()
    {
    }

    bool SceneObjectFactory::init()
    {
        return true;
    }

    void SceneObjectFactory::shutdown()
    {
    }

    SceneObjectPtr SceneObjectFactory::createPlayer(const b2Vec2& pos)
    {
        return boost::make_shared<Player>(pos, 10.0f,
                   Image(textureManager.loadTexture("common.png"), 0, 0, 64, 64));
    }

    SceneObjectPtr SceneObjectFactory::createRock(const b2Vec2& pos,
                                                  const std::vector<b2Vec2>& points)
    {
        return boost::make_shared<Rock>(pos, points,
                   Image(textureManager.loadTexture("common.png"), 64, 0, 64, 64));
    }
}
