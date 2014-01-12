#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Texture.h"

namespace af
{
    class Image
    {
    public:
        Image(const TexturePtr& texture,
              UInt32 x, UInt32 y,
              UInt32 width, UInt32 height);
        ~Image();

        inline const TexturePtr& texture() const { return texture_; }

        inline const float* rect() const { return rect_; }

    private:
        TexturePtr texture_;
        float rect_[4];
    };
}

#endif
