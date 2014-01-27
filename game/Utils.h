#ifndef _UTILS_H_
#define _UTILS_H_

#include "af/Types.h"
#include <Box2D/Box2D.h>

namespace af
{
    b2AABB computeAABB(const b2Vec2* vertices, size_t numVertices);
}

#endif
