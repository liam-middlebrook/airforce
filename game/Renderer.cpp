#include "Renderer.h"
#include "Logger.h"

namespace af
{
    static const std::string vertexShaderSource =
        "attribute vec4 pos;\n"
        "uniform mat4 proj;\n"
        "uniform vec4 rect;\n"
        "attribute vec2 texCoord;\n"
        "varying vec2 v_texCoord;\n"
        "void main()\n"
        "{\n"
        "    v_texCoord = vec2(mix(rect[0], rect[1], fract(texCoord.x)), mix(rect[2], rect[3], fract(texCoord.y)));\n"
        "    gl_Position = proj * pos;\n"
        "}\n";

    static const std::string fragmentShaderSource =
        "uniform sampler2D tex;\n"
        "varying vec2 v_texCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = texture2D(tex, v_texCoord);\n"
        "}\n";

    Renderer renderer;

    template <>
    Single<Renderer>* Single<Renderer>::single = NULL;

    Renderer::Renderer()
    : gameWidth_(0.0f),
      gameHeight_(0.0f),
      vertexShaderId_(0),
      fragmentShaderId_(0),
      programId_(0),
      posLocation_(-1),
      texCoordLocation_(-1),
      rectLocation_(-1)
    {
    }

    Renderer::~Renderer()
    {
    }

    bool Renderer::init(UInt32 viewWidth, UInt32 viewHeight,
                        float gameWidth, float gameHeight)
    {
        gameWidth_ = gameWidth;
        gameHeight_ = gameHeight;

        ogl.Viewport(0, 0, viewWidth, viewHeight);
        ogl.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        ogl.Enable(GL_BLEND);
        ogl.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        ogl.Enable(GL_TEXTURE_2D);
        ogl.Disable(GL_DEPTH_TEST);
        ogl.Disable(GL_CULL_FACE);

        vertexShaderId_ = createShader(vertexShaderSource, GL_VERTEX_SHADER);

        if (!vertexShaderId_) {
            return false;
        }

        fragmentShaderId_ = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        if (!fragmentShaderId_) {
            return false;
        }

        programId_ = createProgram(vertexShaderId_, fragmentShaderId_);

        if (!programId_) {
            return false;
        }

        ogl.UseProgram(programId_);

        posLocation_ = ogl.GetAttribLocation(programId_, "pos");
        assert(posLocation_ >= 0);
        texCoordLocation_ = ogl.GetAttribLocation(programId_, "texCoord");
        assert(texCoordLocation_ >= 0);
        rectLocation_ = ogl.GetUniformLocation(programId_, "rect");
        assert(rectLocation_ >= 0);

        return true;
    }

    void Renderer::shutdown()
    {
        ogl.UseProgram(0);

        ogl.DetachShader(programId_, vertexShaderId_);
        ogl.DetachShader(programId_, fragmentShaderId_);
        ogl.DeleteShader(vertexShaderId_);
        ogl.DeleteShader(fragmentShaderId_);
        ogl.DeleteProgram(programId_);
    }

    void Renderer::lookAt(const b2Vec2& pos)
    {
        applyOrtho(pos.x - (gameWidth_ / 2),
                   pos.x + (gameWidth_ / 2),
                   pos.y - (gameHeight_ / 2),
                   pos.y + (gameHeight_ / 2),
                   0.0f, 1.0f);
    }

    void Renderer::clear()
    {
        ogl.Clear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::renderPoint(const b2Vec2& pos, const b2Color& color, float size)
    {
    }

    void Renderer::renderPolygon(GLenum mode,
                                 const GLfloat* vertices,
                                 const GLfloat* texCoords,
                                 GLsizei count,
                                 const Image& image)
    {
        ogl.VertexAttribPointer(posLocation_, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        ogl.VertexAttribPointer(texCoordLocation_, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
        ogl.Uniform4fv(rectLocation_, 1, image.rect());

        ogl.BindTexture(GL_TEXTURE_2D, image.texture()->id());

        ogl.EnableVertexAttribArray(posLocation_);
        ogl.EnableVertexAttribArray(texCoordLocation_);

        ogl.DrawArrays(mode, 0, count);

        ogl.DisableVertexAttribArray(posLocation_);
        ogl.DisableVertexAttribArray(texCoordLocation_);

        ogl.BindTexture(GL_TEXTURE_2D, 0);
    }

    void Renderer::swapBuffers()
    {
        ogl.swapBuffers();
    }

    GLuint Renderer::createShader(const std::string& source,
                                  GLenum type)
    {
        GLuint shader = ogl.CreateShader(type);

        if (!shader) {
            LOG4CPLUS_ERROR(logger(), "Unable to create shader type = " << type);
            return 0;
        }

        const char* str = source.c_str();

        ogl.ShaderSource(shader, 1, &str, NULL);
        ogl.CompileShader(shader);

        GLint tmp = 0;

        ogl.GetShaderiv(shader, GL_COMPILE_STATUS, &tmp);

        if (!tmp) {
            tmp = 0;
            ogl.GetShaderiv(shader, GL_INFO_LOG_LENGTH, &tmp);

            std::string buff(tmp, 0);

            ogl.GetShaderInfoLog(shader, buff.size(), NULL, &buff[0]);

            LOG4CPLUS_ERROR(logger(), "Unable to compile shader (type = " << type << ") - " << buff);

            ogl.DeleteShader(shader);

            return 0;
        }

        return shader;
    }

    GLuint Renderer::createProgram(GLuint vertexShaderId,
                                   GLuint fragmentShaderId)
    {
        GLuint program = ogl.CreateProgram();

        if (!program) {
            LOG4CPLUS_ERROR(logger(), "Unable to create program");
            return 0;
        }

        ogl.AttachShader(program, vertexShaderId);
        ogl.AttachShader(program, fragmentShaderId);
        ogl.LinkProgram(program);

        GLint tmp = 0;

        ogl.GetProgramiv(program, GL_LINK_STATUS, &tmp);

        if (!tmp) {
            tmp = 0;
            ogl.GetProgramiv(program, GL_INFO_LOG_LENGTH, &tmp);

            std::string buff(tmp, 0);

            ogl.GetProgramInfoLog(program, buff.size(), NULL, &buff[0]);

            LOG4CPLUS_ERROR(logger(), "Unable to link program - " << buff);

            ogl.DeleteProgram(program);

            return 0;
        }

        return program;
    }

    void Renderer::applyOrtho(GLfloat left, GLfloat right,
                              GLfloat bottom, GLfloat top,
                              GLfloat near, GLfloat far)
    {
        float a = 2.0f / (right - left);
        float b = 2.0f / (top - bottom);
        float c = -2.0f / (far - near);

        float tx = -(right + left) / (right - left);
        float ty = -(top + bottom) / (top - bottom);
        float tz = -(far + near) / (far - near);

        float ortho[16] =
        {
            a, 0, 0, 0,
            0, b, 0, 0,
            0, 0, c, 0,
            tx, ty, tz, 1
        };

        GLint projLocation = ogl.GetUniformLocation(programId_, "proj");
        assert(projLocation >= 0);

        ogl.UniformMatrix4fv(projLocation, 1, GL_FALSE, &ortho[0]);
    }
}
