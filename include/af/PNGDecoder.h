#ifndef _AF_PNGDECODER_H_
#define _AF_PNGDECODER_H_

#include "af/Types.h"
#include <boost/noncopyable.hpp>
#include <vector>

namespace af
{
    /*
     * RGBA8 PNG decoder, if PNG file is not RGBA8
     * then 'init' will return false.
     */
    class PNGDecoder : boost::noncopyable
    {
    public:
        explicit PNGDecoder(const std::string& path);
        ~PNGDecoder();

        bool init();

        bool decode(std::vector<Byte>& data);

        UInt32 width() const;

        UInt32 height() const;

    private:
        class Impl;
        Impl* impl_;
    };
}

#endif
