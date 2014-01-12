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

        virtual void update(float dt);

        virtual void render();

    private:
        static const float moveSpeed_ = 30.0f;
        static const float rotateSpeed_ = M_PI;

        virtual b2Body* init();

        b2Vec2 startPos_;
        float size_;

        Image image_;

        b2Fixture* fixture_;
    };
}

#endif
