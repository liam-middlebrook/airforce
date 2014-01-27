#ifndef _RENDERPOLYGONCOMPONENT_H_
#define _RENDERPOLYGONCOMPONENT_H_

#include "RenderComponent.h"
#include "Image.h"
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace af
{
    /*
     * Renders simple convex polygon. 'image' is stretched upon
     * entire polygon.
     */

    class RenderPolygonComponent : public boost::enable_shared_from_this<RenderPolygonComponent>,
                                   public RenderComponent
    {
    public:
        RenderPolygonComponent(const std::vector<b2Vec2>& points,
                               const Image& image,
                               int zOrder = 0);
        ~RenderPolygonComponent();

        virtual void accept(ComponentVisitor& visitor);

        virtual void update(float dt);

        virtual void render(float dt, const std::vector<void*>& parts);

    private:
        virtual void onRegister();

        virtual void onUnregister();

        static std::vector<b2Vec2> tmp_;

        b2AABB updateVertices();

        std::vector<b2Vec2> points_;
        Image image_;

        std::vector<float> vertices_;
        std::vector<float> texCoords_;

        b2Vec2 prevPos_;
        float prevAngle_;
        b2AABB prevAABB_;
        SInt32 cookie_;
    };
}

#endif
