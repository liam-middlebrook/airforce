#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SceneObject.h"
#include "Image.h"

namespace af
{
    class Player : public SceneObject
    {
    public:
        Player(const b2Vec2& pos, float size, const Image& image);
        ~Player();

    private:
        virtual b2Body* init();

        b2Vec2 startPos_;
        float size_;

        Image image_;

        b2Fixture* fixture_;
    };
}

#endif
