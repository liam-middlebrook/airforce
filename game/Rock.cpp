#include "Rock.h"
#include "Scene.h"
#include "Renderer.h"

namespace af
{
    Rock::Rock(const b2Vec2& pos,
               const std::vector<b2Vec2>& points,
               const Image& image)
    : startPos_(pos),
      points_(points),
      image_(image)
    {
    }

    Rock::~Rock()
    {
    }

    void Rock::update(float dt)
    {
    }

    void Rock::render()
    {
        /*b2PolygonShape* poly = (b2PolygonShape*)fixture_->GetShape();
        const b2Transform& xf = body()->GetTransform();

        GLfloat vertices[b2_maxPolygonVertices * 2];

        for (int32 i = 0; i < poly->m_count; ++i) {
            b2Vec2 v = b2Mul(xf, poly->m_vertices[i]);
            vertices[i * 2 + 0] = v.x;
            vertices[i * 2 + 1] = v.y;
        }

        renderer.renderPolygon(&vertices[0], &texCoords_[0], poly->m_count, image_);*/
    }

    b2Body* Rock::init()
    {
        return NULL;
        /*b2BodyDef bodyDef;

        bodyDef.type = b2_dynamicBody;
        bodyDef.position = startPos_;

        b2Body* body = scene()->world().CreateBody(&bodyDef);

        body->SetLinearDamping(1.0f);
        body->SetAngularDamping(1.0f);

        b2PolygonShape shape;

        shape.Set(&points_[0], points_.size());

        b2Transform t;
        t.SetIdentity();

        b2AABB aabb;

        shape.ComputeAABB(&aabb, t, 0);

        b2Vec2 aabbSize = aabb.upperBound - aabb.lowerBound;

        for (int32 i = 0; i < shape.m_count; ++i) {
            b2Vec2 p = shape.m_vertices[i] - aabb.lowerBound;

            texCoords_[i * 2 + 0] = p.x / aabbSize.x;
            texCoords_[i * 2 + 1] = p.y / aabbSize.y;
        }

        b2FixtureDef fixtureDef;

        fixtureDef.shape = &shape;
        fixtureDef.density = 100.0f;

        fixture_ = body->CreateFixture(&fixtureDef);

        return body;*/
    }

    void Rock::destroy()
    {
        //body()->DestroyFixture(fixture_);
    }
}
