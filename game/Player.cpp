#include "Player.h"
#include "Scene.h"
#include "Renderer.h"
#include "Logger.h"

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

    void Player::render()
    {
        const b2Transform& xf = body()->GetTransform();

        b2Vec2 p1 = b2Mul(xf, b2Vec2(-size_ / 2, size_ / 2));
        b2Vec2 p2 = b2Mul(xf, b2Vec2(-size_ / 2, -size_ / 2));
        b2Vec2 p3 = b2Mul(xf, b2Vec2(size_ / 2, -size_ / 2));
        b2Vec2 p4 = b2Mul(xf, b2Vec2(size_ / 2, size_ / 2));

        GLfloat vertices[4 * 2] =
        {
            p1.x, p1.y,
            p2.x, p2.y,
            p3.x, p3.y,
            p4.x, p4.y,
        };

        GLfloat texCoords[4 * 2] =
        {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
        };

        renderer.renderPolygon(&vertices[0], &texCoords[0], 4, image_);
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
