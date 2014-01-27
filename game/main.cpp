#include "Logger.h"
#include "AirForceGame.h"
#include "Types.h"
#include <log4cplus/configurator.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

static Display* dpy = NULL;
static Window window = 0;
static Atom deleteMessage = 0;

static bool createWindow(af::UInt32 width, af::UInt32 height)
{
    LOG4CPLUS_INFO(af::logger(), "Creating window " << width << "x" << height << "...");

    dpy = ::XOpenDisplay(NULL);

    if (!dpy) {
        LOG4CPLUS_ERROR(af::logger(), "Cannot open display");
        return false;
    }

    XSetWindowAttributes wa;

    wa.background_pixel = 0;
    wa.border_pixel = 0;
    wa.event_mask = StructureNotifyMask | ExposureMask;

    window = ::XCreateWindow(dpy,
                             RootWindow(dpy, DefaultScreen(dpy)),
                             0,
                             0,
                             width,
                             height,
                             0,
                             24,
                             InputOutput,
                             CopyFromParent,
                             CWBackPixel | CWBorderPixel | CWEventMask,
                             &wa);

    if (!window) {
        LOG4CPLUS_ERROR(af::logger(), "Cannot create window");
        return false;
    }

    XSetStandardProperties(dpy,
                           window,
                           "AirForce",
                           "AirForce",
                           None,
                           0,
                           0,
                           NULL);

    XSizeHints sizeHints;

    sizeHints.flags = PMinSize | PMaxSize;
    sizeHints.min_width = sizeHints.max_width = width;
    sizeHints.min_height = sizeHints.max_height = height;

   ::XSetWMNormalHints(dpy, window, &sizeHints);

    XMapWindow(dpy, window);

    deleteMessage = ::XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    ::XSetWMProtocols(dpy, window, &deleteMessage, 1);

    XSync(dpy, False);

    LOG4CPLUS_INFO(af::logger(), "Window created");

    return true;
}

static void destroyWindow()
{
    LOG4CPLUS_INFO(af::logger(), "Destroying window...");

    XDestroyWindow(dpy, window);
    XCloseDisplay(dpy);

    LOG4CPLUS_INFO(af::logger(), "Window destroyed");
}

int main(int argc, char *argv[])
{
    log4cplus::helpers::Properties props;

    props.setProperty("log4cplus.rootLogger", "TRACE, console");
    props.setProperty("log4cplus.appender.console", "log4cplus::ConsoleAppender");
    props.setProperty("log4cplus.appender.console.layout", "log4cplus::PatternLayout");
    props.setProperty("log4cplus.appender.console.layout.ConversionPattern", "%-5p %c - %m%n");

    log4cplus::PropertyConfigurator propConf(props);
    propConf.configure();

    LOG4CPLUS_INFO(af::logger(), "Starting...");

    if (!createWindow(800, 600)) {
        return 1;
    }

    af::AirForceGame game;

    if (!game.init(dpy, reinterpret_cast<void*>(window), 800, 600, 100.0f)) {
        return 1;
    }

    bool running = true;
    XEvent event;

    ::XSelectInput(dpy, window, KeyPressMask | KeyReleaseMask);

    ::XkbSetDetectableAutoRepeat(dpy, True, NULL);

    KeySym keysym;

    while (running) {
        while (::XPending(dpy) > 0) {
            ::XNextEvent(dpy, &event);
            switch (event.type) {
            case ClientMessage:
                if (event.xclient.data.l[0] == static_cast<long>(deleteMessage)) {
                    running = false;
                }
                break;
            case KeyPress:
                XLookupString(&event.xkey, NULL, 0, &keysym, NULL);
                game.inputKeyDown(keysym);
                break;
            case KeyRelease:
                XLookupString(&event.xkey, NULL, 0, &keysym, NULL);
                game.inputKeyUp(keysym);
                break;
            default:
                break;
            }
        }

        game.update();
    }

    game.shutdown();

    destroyWindow();

    return 0;
}
