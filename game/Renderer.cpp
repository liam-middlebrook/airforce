#include "Renderer.h"

namespace af
{
    Renderer renderer;

    template <>
    Single<Renderer>* Single<Renderer>::single = NULL;

    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
    }

    bool Renderer::init(UInt32 viewWidth, UInt32 viewHeight,
                        float gameWidth, float gameHeight)
    {
        return true;
    }

    void Renderer::shutdown()
    {
    }

    void Renderer::clear()
    {
    }

    void Renderer::renderPoint(const b2Vec2& pos, const b2Color& color, float size)
    {
    }

    void Renderer::renderPolygon(const b2Vec2* vertices,
                                 const b2Vec2* texCoords,
                                 size_t count,
                                 const Image& image)
    {
    }

    void Renderer::swapBuffers()
    {
    }
}
