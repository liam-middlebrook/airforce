#include "RenderTerrainComponent.h"
#include "SceneObject.h"
#include "Utils.h"
#include "Renderer.h"
#include "poly2tri.h"

namespace af
{
    std::vector<float> RenderTerrainComponent::tmpVertices_;
    std::vector<float> RenderTerrainComponent::tmpTexCoords_;

    RenderTerrainComponent::RenderTerrainComponent(const Points& points,
                                                   const std::vector<Points>& holes,
                                                   const Image& image,
                                                   float imageWidth, float imageHeight,
                                                   int zOrder)
    : RenderComponent(zOrder),
      image_(image)
    {
        size_t totalSize = points.size();

        for (size_t i = 0; i < holes.size(); ++i) {
            totalSize += holes[i].size();
        }

        std::vector<p2t::Point> tessPoints;
        std::vector<p2t::Point*> tessPointPtrs;

        tessPoints.resize(totalSize);
        tessPointPtrs.resize(points.size());

        size_t cur = 0;

        for (size_t i = 0; i < points.size(); ++i, ++cur) {
            tessPoints[cur] = p2t::Point(points[i].x, points[i].y);
            tessPointPtrs[i] = &tessPoints[cur];
        }

        p2t::CDT cdt(tessPointPtrs);

        for (size_t i = 0; i < holes.size(); ++i) {
            const Points& hole = holes[i];

            if (hole.size() == 1) {
                /*
                 * Steiner point.
                 */
                tessPoints[cur] = p2t::Point(hole[0].x, hole[0].y);

                cdt.AddPoint(&tessPoints[cur++]);
            } else {
                /*
                 * Hole.
                 */
                tessPointPtrs.resize(hole.size());

                for (size_t j = 0; j < hole.size(); ++j, ++cur) {
                    tessPoints[cur] = p2t::Point(hole[j].x, hole[j].y);
                    tessPointPtrs[j] = &tessPoints[cur];
                }

                cdt.AddHole(tessPointPtrs);
            }
        }

        cdt.Triangulate();

        std::vector<p2t::Triangle*> triangles = cdt.GetTriangles();

        vertices_.resize(triangles.size() * 6);
        texCoords_.resize(triangles.size() * 6);

        b2AABB aabb = computeAABB(&points[0], points.size());

        b2Vec2 aabbSize = aabb.upperBound - aabb.lowerBound;

        for (size_t i = 0; i < triangles.size(); ++i) {
            vertices_[i * 6 + 0] = triangles[i]->GetPoint(0)->x;
            vertices_[i * 6 + 1] = triangles[i]->GetPoint(0)->y;
            vertices_[i * 6 + 2] = triangles[i]->GetPoint(1)->x;
            vertices_[i * 6 + 3] = triangles[i]->GetPoint(1)->y;
            vertices_[i * 6 + 4] = triangles[i]->GetPoint(2)->x;
            vertices_[i * 6 + 5] = triangles[i]->GetPoint(2)->y;

            b2Vec2 tp0 = b2Vec2(triangles[i]->GetPoint(0)->x,
                                triangles[i]->GetPoint(0)->y) - aabb.lowerBound;
            b2Vec2 tp1 = b2Vec2(triangles[i]->GetPoint(1)->x,
                                triangles[i]->GetPoint(1)->y) - aabb.lowerBound;
            b2Vec2 tp2 = b2Vec2(triangles[i]->GetPoint(2)->x,
                                triangles[i]->GetPoint(2)->y) - aabb.lowerBound;

            texCoords_[i * 6 + 0] = tp0.y / imageHeight;
            texCoords_[i * 6 + 1] = tp0.x / imageWidth;
            texCoords_[i * 6 + 2] = tp1.y / imageHeight;
            texCoords_[i * 6 + 3] = tp1.x / imageWidth;
            texCoords_[i * 6 + 4] = tp2.y / imageHeight;
            texCoords_[i * 6 + 5] = tp2.x / imageWidth;
        }
    }

    RenderTerrainComponent::~RenderTerrainComponent()
    {
    }

    void RenderTerrainComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitRenderTerrainComponent(shared_from_this());
    }

    void RenderTerrainComponent::update(float dt)
    {
    }

    void RenderTerrainComponent::render(float dt, const std::vector<void*>& parts)
    {
        tmpVertices_.resize(parts.size() * 6);
        tmpTexCoords_.resize(parts.size() * 6);

        for (size_t i = 0; i < parts.size(); ++i) {
            size_t j = reinterpret_cast<size_t>(parts[i]);

            tmpVertices_[i * 6 + 0] = vertices_[j + 0];
            tmpVertices_[i * 6 + 1] = vertices_[j + 1];
            tmpVertices_[i * 6 + 2] = vertices_[j + 2];
            tmpVertices_[i * 6 + 3] = vertices_[j + 3];
            tmpVertices_[i * 6 + 4] = vertices_[j + 4];
            tmpVertices_[i * 6 + 5] = vertices_[j + 5];

            tmpTexCoords_[i * 6 + 0] = texCoords_[j + 0];
            tmpTexCoords_[i * 6 + 1] = texCoords_[j + 1];
            tmpTexCoords_[i * 6 + 2] = texCoords_[j + 2];
            tmpTexCoords_[i * 6 + 3] = texCoords_[j + 3];
            tmpTexCoords_[i * 6 + 4] = texCoords_[j + 4];
            tmpTexCoords_[i * 6 + 5] = texCoords_[j + 5];
        }

        renderer.renderPolygon(GL_TRIANGLES,
                               &tmpVertices_[0], &tmpTexCoords_[0],
                               parts.size() * 3, image_);
    }

    void RenderTerrainComponent::onRegister()
    {
        const b2Transform& xf = parent()->getTransform();

        cookies_.reserve(vertices_.size() / 6);

        b2Vec2 p[3];

        for (size_t i = 0; i < vertices_.size(); i += 6) {
            p[0].x = vertices_[i + 0];
            p[0].y = vertices_[i + 1];
            p[1].x = vertices_[i + 2];
            p[1].y = vertices_[i + 3];
            p[2].x = vertices_[i + 4];
            p[2].y = vertices_[i + 5];

            p[0] = b2Mul(xf, p[0]);
            p[1] = b2Mul(xf, p[1]);
            p[2] = b2Mul(xf, p[2]);

            vertices_[i + 0] = p[0].x;
            vertices_[i + 1] = p[0].y;
            vertices_[i + 2] = p[1].x;
            vertices_[i + 3] = p[1].y;
            vertices_[i + 4] = p[2].x;
            vertices_[i + 5] = p[2].y;

            b2AABB aabb = computeAABB(&p[0], 3);

            cookies_.push_back(manager()->addAABB(this, aabb, reinterpret_cast<void*>(i)));
        }
    }

    void RenderTerrainComponent::onUnregister()
    {
        for (size_t i = 0; i < cookies_.size(); ++i) {
            manager()->removeAABB(cookies_[i]);
        }

        cookies_.resize(0);
    }
}
