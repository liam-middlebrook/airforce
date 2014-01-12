#include "OGL.h"
#include "Logger.h"
#include <GL/glx.h>
#include <dlfcn.h>

#define GLX_GET_PROC(func, sym) \
    do { \
        *(void**)(&func) = (void*)getProcAddress((const GLubyte*)#sym); \
        if (!func) { \
            LOG4CPLUS_ERROR(logger(), "Unable to load symbol: " << ::dlerror()); \
            return false; \
        } \
    } while (0)

#define GL_GET_PROC(func, sym) \
    do { \
        *(void**)(&func) = (void*)getProcAddress((const GLubyte*)#sym); \
        if (!func) { \
            *(void**)(&func) = ::dlsym(handle, #sym); \
            if (!func) { \
                LOG4CPLUS_ERROR(logger(), "Unable to load symbol: " << ::dlerror()); \
                return false; \
            } \
        } \
    } while (0)

typedef void (*PFNGLXSWAPBUFFERSPROC)(Display* dpy, GLXDrawable drawable);
typedef void (*PFNGLXDESTROYCONTEXTPROC)(Display* dpy, GLXContext ctx);
typedef Bool (*PFNGLXMAKECURRENTPROC)(Display* dpy, GLXDrawable drawable, GLXContext ctx);

namespace af
{
    OGL ogl;

    static PFNGLXGETPROCADDRESSPROC getProcAddress = NULL;
    static PFNGLXCHOOSEFBCONFIGPROC chooseFBConfig = NULL;
    static PFNGLXCREATECONTEXTATTRIBSARBPROC createContextAttribsARB = NULL;
    static PFNGLXMAKECURRENTPROC makeCurrent = NULL;
    static PFNGLXSWAPBUFFERSPROC swapBuffersFunc = NULL;
    static PFNGLXDESTROYCONTEXTPROC destroyContext = NULL;

    static const int ctxAttribs[] =
    {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 2,
        GLX_CONTEXT_MINOR_VERSION_ARB, 1,
        GLX_RENDER_TYPE, GLX_RGBA_TYPE,
        None
    };

    static const int configAttribs[] =
    {
        GLX_DOUBLEBUFFER, True,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        None
    };

    static Display* dpy = NULL;
    static Window surface = 0;
    static GLXContext context = NULL;

    template <>
    Single<OGL>* Single<OGL>::single = NULL;

    OGL::OGL()
    {
    }

    OGL::~OGL()
    {
    }

    bool OGL::init(void* display, void* window)
    {
        LOG4CPLUS_INFO(logger(), "Initializing OpenGL...");

        dpy = reinterpret_cast<Display*>(display);
        surface = reinterpret_cast<Window>(window);

        void* handle = ::dlopen("libGL.so.1", RTLD_NOW | RTLD_GLOBAL);

        if (!handle) {
            LOG4CPLUS_ERROR(logger(), "Unable to load libGL.so.1");
            return false;
        }

        getProcAddress = (PFNGLXGETPROCADDRESSPROC)::dlsym(handle, "glXGetProcAddress");

        if (!getProcAddress) {
            getProcAddress = (PFNGLXGETPROCADDRESSPROC)::dlsym(handle, "glXGetProcAddressARB");
        }

        if (!getProcAddress) {
            LOG4CPLUS_ERROR(logger(), "Unable to load symbol: " << ::dlerror());
            return false;
        }

        GLX_GET_PROC(chooseFBConfig, glXChooseFBConfig);
        GLX_GET_PROC(createContextAttribsARB, glXCreateContextAttribsARB);
        GLX_GET_PROC(makeCurrent, glXMakeCurrent);
        GLX_GET_PROC(swapBuffersFunc, glXSwapBuffers);
        GLX_GET_PROC(destroyContext, glXDestroyContext);

        GL_GET_PROC(GenTextures, glGenTextures);
        GL_GET_PROC(DeleteTextures, glDeleteTextures);
        GL_GET_PROC(BindTexture, glBindTexture);
        GL_GET_PROC(TexImage2D, glTexImage2D);
        GL_GET_PROC(TexParameteri, glTexParameteri);
        GL_GET_PROC(ClearColor, glClearColor);
        GL_GET_PROC(Clear, glClear);
        GL_GET_PROC(Viewport, glViewport);
        GL_GET_PROC(AttachShader, glAttachShader);
        GL_GET_PROC(BindAttribLocation, glBindAttribLocation);
        GL_GET_PROC(CompileShader, glCompileShader);
        GL_GET_PROC(CreateProgram, glCreateProgram);
        GL_GET_PROC(CreateShader, glCreateShader);
        GL_GET_PROC(DeleteProgram, glDeleteProgram);
        GL_GET_PROC(DeleteShader, glDeleteShader);
        GL_GET_PROC(DetachShader, glDetachShader);
        GL_GET_PROC(DisableVertexAttribArray, glDisableVertexAttribArray);
        GL_GET_PROC(EnableVertexAttribArray, glEnableVertexAttribArray);
        GL_GET_PROC(LinkProgram, glLinkProgram);
        GL_GET_PROC(ShaderSource, glShaderSource);
        GL_GET_PROC(UseProgram, glUseProgram);
        GL_GET_PROC(GetProgramiv, glGetProgramiv);
        GL_GET_PROC(GetProgramInfoLog, glGetProgramInfoLog);
        GL_GET_PROC(GetShaderiv, glGetShaderiv);
        GL_GET_PROC(GetShaderInfoLog, glGetShaderInfoLog);
        GL_GET_PROC(GetAttribLocation, glGetAttribLocation);
        GL_GET_PROC(GetUniformLocation, glGetUniformLocation);
        GL_GET_PROC(VertexAttribPointer, glVertexAttribPointer);
        GL_GET_PROC(DrawArrays, glDrawArrays);
        GL_GET_PROC(Uniform4fv, glUniform4fv);
        GL_GET_PROC(Enable, glEnable);
        GL_GET_PROC(Disable, glDisable);
        GL_GET_PROC(BlendFunc, glBlendFunc);
        GL_GET_PROC(UniformMatrix4fv, glUniformMatrix4fv);
        GL_GET_PROC(Uniform1i, glUniform1i);

        int n = 0;

        GLXFBConfig* configs = chooseFBConfig(dpy,
                                              DefaultScreen(dpy),
                                              configAttribs,
                                              &n);

        if (n <= 0) {
            LOG4CPLUS_ERROR(logger(), "Unable to choose config");
            return false;
        }

        GLXFBConfig config = configs[0];

        ::XFree(configs);

        context = createContextAttribsARB(dpy,
                                          config,
                                          NULL,
                                          True,
                                          ctxAttribs);

        if (!context) {
            LOG4CPLUS_ERROR(logger(), "Unable to create context");
            return false;
        }

        if (!makeCurrent(dpy, surface, context)) {
            LOG4CPLUS_ERROR(logger(), "Unable to make context current");
            return false;
        }

        LOG4CPLUS_INFO(logger(), "OpenGL initialized");

        return true;
    }

    void OGL::shutdown()
    {
        LOG4CPLUS_INFO(logger(), "Shutting down OpenGL..");

        if (!makeCurrent(dpy, None, NULL)) {
            LOG4CPLUS_WARN(logger(), "Unable to release current context");
        }

        destroyContext(dpy, context);

        LOG4CPLUS_INFO(logger(), "OpenGL shut down");
    }

    void OGL::swapBuffers()
    {
        swapBuffersFunc(dpy, surface);
    }
}
