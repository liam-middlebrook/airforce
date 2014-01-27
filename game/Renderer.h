#ifndef _RENDER_H_
#define _RENDER_H_

#include "Single.h"
#include "Image.h"
#include "OGL.h"
#include <Box2D/Box2D.h>

namespace af
{
    class Renderer : public Single<Renderer>
    {
    public:
        Renderer();
        ~Renderer();

        bool init(UInt32 viewWidth, UInt32 viewHeight,
                  float gameWidth, float gameHeight);
        void shutdown();

        void lookAt(const b2Vec2& pos);

        void clear();

        void renderPoint(const b2Vec2& pos, const b2Color& color, float size);

        void renderPolygon(GLenum mode,
                           const GLfloat* vertices,
                           const GLfloat* texCoords,
                           GLsizei count,
                           const Image& image);

        void swapBuffers();

    private:
        static GLuint createShader(const std::string& source,
                                   GLenum type);

        static GLuint createProgram(GLuint vertexShaderId,
                                    GLuint fragmentShaderId);

        void applyOrtho(GLfloat left, GLfloat right,
                        GLfloat bottom, GLfloat top,
                        GLfloat near, GLfloat far);

        float gameWidth_;
        float gameHeight_;

        GLuint vertexShaderId_;
        GLuint fragmentShaderId_;
        GLuint programId_;

        GLint posLocation_;
        GLint texCoordLocation_;
        GLint rectLocation_;
    };

    extern Renderer renderer;
}

#endif
