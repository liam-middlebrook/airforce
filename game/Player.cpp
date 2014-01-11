#include "Player.h"
#include "Scene.h"

namespace af
{
    Player::Player(const b2Vec2& pos, float size, const Image& image)
    : startPos_(pos),
      size_(size),
      image_(image)
    {
    }

    Player::~Player()
    {
        if (fixture_) {
            body()->DestroyFixture(fixture_);
        }
    }

    b2Body* Player::init()
    {
        b2BodyDef bodyDef;

        bodyDef.type = b2_dynamicBody;
        bodyDef.position = startPos_;

        b2Body* body = scene()->world().CreateBody(&bodyDef);

        b2CircleShape shape;

        shape.m_radius = size_ / 2;

        b2FixtureDef fixtureDef;

        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;

        fixture_ = body->CreateFixture(&fixtureDef);

        return body;
    }
}
