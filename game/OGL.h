#ifndef _OGL_H_
#define _OGL_H_

#include "Single.h"
#include <GL/gl.h>
#include <GL/glext.h>

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
        void (GLAPIENTRY* ClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
        void (GLAPIENTRY* Clear)(GLbitfield mask);
        void (GLAPIENTRY* Viewport)(GLint x, GLint y,
                                    GLsizei width, GLsizei height);
        void (GLAPIENTRY* AttachShader)(GLuint program, GLuint shader);
        void (GLAPIENTRY* BindAttribLocation)(GLuint program, GLuint index, const GLchar* name);
        void (GLAPIENTRY* CompileShader)(GLuint shader);
        GLuint (GLAPIENTRY* CreateProgram)();
        GLuint (GLAPIENTRY* CreateShader)(GLenum type);
        void (GLAPIENTRY* DeleteProgram)(GLuint program);
        void (GLAPIENTRY* DeleteShader)(GLuint shader);
        void (GLAPIENTRY* DetachShader)(GLuint program, GLuint shader);
        void (GLAPIENTRY* DisableVertexAttribArray)(GLuint index);
        void (GLAPIENTRY* EnableVertexAttribArray)(GLuint index);
        void (GLAPIENTRY* LinkProgram)(GLuint program);
        void (GLAPIENTRY* ShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
        void (GLAPIENTRY* UseProgram)(GLuint program);
        void (GLAPIENTRY* GetProgramiv)(GLuint program, GLenum pname, GLint* params);
        void (GLAPIENTRY* GetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
        void (GLAPIENTRY* GetShaderiv)(GLuint shader, GLenum pname, GLint* params);
        void (GLAPIENTRY* GetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
        GLint (GLAPIENTRY* GetAttribLocation)(GLuint program, const GLchar* name);
        GLint (GLAPIENTRY* GetUniformLocation)(GLuint program, const GLchar* name);
        void (GLAPIENTRY* VertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
        void (GLAPIENTRY* DrawArrays)(GLenum mode, GLint first, GLsizei count);
        void (GLAPIENTRY* Uniform4fv)(GLint location, GLsizei count, const GLfloat* value);
        void (GLAPIENTRY* Enable)(GLenum cap);
        void (GLAPIENTRY* Disable)(GLenum cap);
        void (GLAPIENTRY* BlendFunc)(GLenum sfactor, GLenum dfactor);
        void (GLAPIENTRY* UniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
        void (GLAPIENTRY* Uniform1i)(GLint location, GLint v0);

        void swapBuffers();
    };

    extern OGL ogl;
}

#endif
