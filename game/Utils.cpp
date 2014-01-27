#include "Utils.h"

namespace af
{
    b2AABB computeAABB(const b2Vec2* vertices, size_t numVertices)
    {
        b2Vec2 lower = vertices[0];
        b2Vec2 upper = lower;

        for (size_t i = 1; i < numVertices; ++i) {
            b2Vec2 v = vertices[i];
            lower = b2Min(lower, v);
            upper = b2Max(upper, v);
        }

        b2AABB aabb;

        aabb.lowerBound = lower;
        aabb.upperBound = upper;

        return aabb;
    }
}
