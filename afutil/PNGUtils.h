#ifndef _PNGUTILS_H_
#define _PNGUTILS_H_

#include "af/Types.h"
#include "png.h"
#include <setjmp.h>

#define PNGCatch(pngPtr) \
    if (::setjmp(reinterpret_cast<af::PNGError*>(png_get_error_ptr(pngPtr))->setjmp_buffer))

namespace af
{
    struct PNGError
    {
        jmp_buf setjmp_buffer;
    };

    png_structp PNGCreateReadStruct(PNGError& pngError);

    void PNGThrow(png_structp pngPtr);
}

#endif
