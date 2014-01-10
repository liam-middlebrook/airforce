#ifndef _OGL_H_
#define _OGL_H_

#include <boost/noncopyable.hpp>
#include <GL/gl.h>

namespace af
{
    class OGL : boost::noncopyable
    {
    public:
        OGL();
        ~OGL();

        bool init(void* display, void* window);
        void shutdown();

        void (GLAPIENTRY* GenTextures)(GLsizei n, GLuint* textures);
        void (GLAPIENTRY* DeleteTextures)(GLsizei n, const GLuint* textures);
        void (GLAPIENTRY* BindTexture)(GLenum target, GLuint texture);
    };

    extern OGL ogl;
}

#endif
