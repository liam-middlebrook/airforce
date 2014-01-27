#ifndef _RENDERTERRAINCOMPONENT_H_
#define _RENDERTERRAINCOMPONENT_H_

#include "RenderComponent.h"
#include "Image.h"
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace af
{
    /*
     * Renders simple polygon 'points' (not necessarily convex) with
     * simple polygon (not necessarily convex) holes in it - 'holes'.
     * 'image' is stretched to 'imageWidth' x 'imageHeight' and repeated.
     *
     * Note! Do not move object around, this component is optimized for
     * static objects and doesn't recalculate AABB.
     */
    class RenderTerrainComponent : public boost::enable_shared_from_this<RenderTerrainComponent>,
                                   public RenderComponent
    {
    public:
        RenderTerrainComponent(const Points& points,
                               const std::vector<Points>& holes,
                               const Image& image,
                               float imageWidth, float imageHeight,
                               int zOrder = 0);
        ~RenderTerrainComponent();

        virtual void accept(ComponentVisitor& visitor);

        virtual void update(float dt);

        virtual void render(float dt, const std::vector<void*>& parts);

    private:
        virtual void onRegister();

        virtual void onUnregister();

        static std::vector<float> tmpVertices_;
        static std::vector<float> tmpTexCoords_;

        std::vector<float> vertices_;
        std::vector<float> texCoords_;

        Image image_;

        std::vector<SInt32> cookies_;
    };
}

#endif
