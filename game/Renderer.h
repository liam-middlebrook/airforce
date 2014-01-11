#ifndef _RENDER_H_
#define _RENDER_H_

#include "Single.h"
#include "Image.h"
#include <Box2D/Box2D.h>

namespace af
{
    class Renderer : public Single<Renderer>
    {
    public:
        Renderer();
        ~Renderer();

        bool init(UInt32 viewWidth, UInt32 viewHeight,
                  float gameWidth, float gameHeight);
        void shutdown();

        void clear();

        void renderPoint(const b2Vec2& pos, const b2Color& color, float size);

        void renderPolygon(const b2Vec2* vertices,
                           const b2Vec2* texCoords,
                           size_t count,
                           const Image& image);

        void swapBuffers();
    };

    extern Renderer renderer;
}

#endif
