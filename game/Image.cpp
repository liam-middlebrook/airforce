#include "Image.h"

namespace af
{
    Image::Image(const TexturePtr& texture,
                 UInt32 x, UInt32 y,
                 UInt32 width, UInt32 height)
    : texture_(texture)
    {
        float xf = x;
        float yf = y;

        rect_[0] = xf / texture->width();
        rect_[1] = (xf + width) / texture->width();
        rect_[2] = 1.0f - (yf + height) / texture->height();
        rect_[3] = 1.0f - yf / texture->height();
    }

    Image::~Image()
    {
    }
}
