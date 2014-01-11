#ifndef _OGL_H_
#define _OGL_H_

#include "Single.h"
#include <GL/gl.h>

namespace af
{
    class OGL : public Single<OGL>
    {
    public:
        OGL();
        ~OGL();

        bool init(void* display, void* window);
        void shutdown();

        void (GLAPIENTRY* GenTextures)(GLsizei n, GLuint* textures);
        void (GLAPIENTRY* DeleteTextures)(GLsizei n, const GLuint* textures);
        void (GLAPIENTRY* BindTexture)(GLenum target, GLuint texture);
        void (GLAPIENTRY* TexImage2D)(GLenum target, GLint level,
                                      GLint internalFormat,
                                      GLsizei width, GLsizei height,
                                      GLint border, GLenum format, GLenum type,
                                      const GLvoid* pixels);
        void (GLAPIENTRY* TexParameteri)(GLenum target, GLenum pname, GLint param);
    };

    extern OGL ogl;
}

#endif
