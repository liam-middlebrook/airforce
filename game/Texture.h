#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Types.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace af
{
    class Texture : boost::noncopyable
    {
    public:
        Texture(UInt32 id, UInt32 width, UInt32 height)
        : id_(id),
          width_(width),
          height_(height)
        {
        }

        ~Texture()
        {
        }

        inline UInt32 id() const { return id_; }

        inline UInt32 width() const { return width_; }

        inline UInt32 height() const { return height_; }

    private:
        UInt32 id_;
        UInt32 width_;
        UInt32 height_;
    };

    typedef boost::shared_ptr<Texture> TexturePtr;
}

#endif
