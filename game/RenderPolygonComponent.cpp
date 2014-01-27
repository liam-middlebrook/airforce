#include "RenderPolygonComponent.h"
#include "SceneObject.h"
#include "Renderer.h"
#include "Utils.h"

namespace af
{
    std::vector<b2Vec2> RenderPolygonComponent::tmp_;

    RenderPolygonComponent::RenderPolygonComponent(const std::vector<b2Vec2>& points,
                                                   const Image& image,
                                                   int zOrder)
    : RenderComponent(zOrder),
      points_(points),
      image_(image),
      prevAngle_(0.0f),
      cookie_(0)
    {
        b2AABB aabb = computeAABB(&points_[0], points_.size());

        b2Vec2 aabbSize = aabb.upperBound - aabb.lowerBound;

        texCoords_.resize(points_.size() * 2);

        for (size_t i = 0; i < points_.size(); ++i) {
            b2Vec2 p = points_[i] - aabb.lowerBound;

            /*
             * Texture coordinates need to be rotated by
             * -90 degrees since we're texturing 0 degree
             * rotated object.
             */

            texCoords_[i * 2 + 0] = p.y / aabbSize.y;
            texCoords_[i * 2 + 1] = p.x / aabbSize.x;
        }
    }

    RenderPolygonComponent::~RenderPolygonComponent()
    {
    }

    void RenderPolygonComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitRenderPolygonComponent(shared_from_this());
    }

    void RenderPolygonComponent::update(float dt)
    {
        if ((parent()->pos() == prevPos_) &&
            (parent()->angle() == prevAngle_)) {
            return;
        }

        b2AABB aabb = updateVertices();

        b2AABB combinedAABB;

        combinedAABB.Combine(prevAABB_, aabb);

        b2Vec2 displacement = parent()->pos() - prevPos_;

        manager()->moveAABB(cookie_, combinedAABB, displacement);

        prevPos_ = parent()->pos();
        prevAngle_ = parent()->angle();
        prevAABB_ = aabb;
    }

    void RenderPolygonComponent::render(float dt, const std::vector<void*>& parts)
    {
        renderer.renderPolygon(&vertices_[0], &texCoords_[0], points_.size(), image_);
    }

    void RenderPolygonComponent::onRegister()
    {
        prevPos_ = parent()->pos();
        prevAngle_ = parent()->angle();
        prevAABB_ = updateVertices();
        cookie_ = manager()->addAABB(this, prevAABB_, NULL);
    }

    void RenderPolygonComponent::onUnregister()
    {
        manager()->removeAABB(cookie_);
    }

    b2AABB RenderPolygonComponent::updateVertices()
    {
        const b2Transform& xf = parent()->getTransform();

        tmp_.resize(points_.size());
        vertices_.resize(points_.size() * 2);

        for (size_t i = 0; i < points_.size(); ++i) {
            tmp_[i] = b2Mul(xf, points_[i]);
            vertices_[i * 2 + 0] = tmp_[i].x;
            vertices_[i * 2 + 1] = tmp_[i].y;
        }

        return computeAABB(&tmp_[0], tmp_.size());
    }
}
