#include "SceneObjectFactory.h"
#include "TextureManager.h"
#include "PlayerComponent.h"
#include "PhysicsBallComponent.h"
#include "PhysicsPolygonComponent.h"
#include "RenderPolygonComponent.h"
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
        static const float size = 10.0f;

        SceneObjectPtr obj =
            boost::make_shared<SceneObject>(SceneObjectTypePlayer, pos);

        {
            ComponentPtr component = boost::make_shared<PlayerComponent>();

            obj->addComponent(component);
        }

        {
            ComponentPtr component =
                boost::make_shared<PhysicsBallComponent>(b2Vec2(0.0f, 0.0f),
                                                         size,
                                                         true);

            obj->addComponent(component);
        }

        {
            std::vector<b2Vec2> points;

            points.push_back(b2Vec2(-size / 2, size / 2));
            points.push_back(b2Vec2(-size / 2, -size / 2));
            points.push_back(b2Vec2(size / 2, -size / 2));
            points.push_back(b2Vec2(size / 2, size / 2));

            ComponentPtr component =
                boost::make_shared<RenderPolygonComponent>(points,
                    Image(textureManager.loadTexture("common.png"), 0, 0, 64, 64));

            obj->addComponent(component);
        }

        return obj;
    }

    SceneObjectPtr SceneObjectFactory::createRock(const b2Vec2& pos,
                                                  const std::vector<b2Vec2>& points)
    {
        SceneObjectPtr obj =
            boost::make_shared<SceneObject>(SceneObjectTypeOther, pos);

        {
            ComponentPtr component =
                boost::make_shared<PhysicsPolygonComponent>(points);

            obj->addComponent(component);

            obj->setLinearDamping(1.0f);
            obj->setAngularDamping(1.0f);
        }

        {
            ComponentPtr component =
                boost::make_shared<RenderPolygonComponent>(points,
                    Image(textureManager.loadTexture("common.png"), 64, 0, 64, 64));

            obj->addComponent(component);
        }

        return obj;
    }
}
