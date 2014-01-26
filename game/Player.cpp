#include "Player.h"
#include "Scene.h"
#include "Renderer.h"
#include "Logger.h"
#include "InputManager.h"
#include <limits>

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
    }

    void Player::update(float dt)
    {
        /*if (inputManager.leftPressed()) {
            body()->SetTransform(body()->GetPosition(), body()->GetAngle() + rotateSpeed_ * dt);
        } else if (inputManager.rightPressed()) {
            body()->SetTransform(body()->GetPosition(), body()->GetAngle() - rotateSpeed_ * dt);
        }

        body()->SetLinearVelocity(b2Mul(body()->GetTransform().q, b2Vec2(moveSpeed_, 0.0f)));*/
    }

    void Player::render()
    {
        /*const b2Transform& xf = body()->GetTransform();

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

        renderer.renderPolygon(&vertices[0], &texCoords[0], 4, image_);*/
    }

    b2Body* Player::init()
    {
        return NULL;
        /*b2BodyDef bodyDef;

        bodyDef.type = b2_dynamicBody;
        bodyDef.position = startPos_;
        bodyDef.fixedRotation = true;

        b2Body* body = scene()->world().CreateBody(&bodyDef);

        b2CircleShape shape;

        shape.m_radius = size_ / 2;

        b2FixtureDef fixtureDef;

        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;

        fixture_ = body->CreateFixture(&fixtureDef);

        return body;*/
    }

    void Player::destroy()
    {
        //body()->DestroyFixture(fixture_);
    }
}
