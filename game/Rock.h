#ifndef _ROCK_H_
#define _ROCK_H_

#include "SceneObject.h"
#include "Image.h"
#include <vector>

namespace af
{
    class Rock : public SceneObject
    {
    public:
        Rock(const b2Vec2& pos,
             const std::vector<b2Vec2>& points,
             const Image& image);
        ~Rock();

        virtual void update(float dt);

        virtual void render();

    private:
        virtual b2Body* init();

        virtual void destroy();

        b2Vec2 startPos_;
        std::vector<b2Vec2> points_;

        Image image_;

        float texCoords_[b2_maxPolygonVertices * 2];

        b2Fixture* fixture_;
    };
}

#endif
