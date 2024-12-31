#ifndef GFX_LINUX_H
#define GFX_LINUX_H

#include <X11/Xlib.h>

// Window State
//=============

typedef struct Gfx_Linux_State {
    Display *display;
} Gfx_Linux_State;

global Gfx_Linux_State *gfx_linxu_state = 0;

fn void gfx_init(void) {

    gfx_linxu_state->display = XOpenDisplay(NULL);
}

fn void gfx_window_open(Str8 title) {
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    int screen = DefaultScreen(display);

    Window window = XCreateSimpleWindow(display, RootWindow(display, screen),
                        10, 10, 400, 300, 1,
                        BlackPixel(display, screen),
                        WhitePixel(display, screen)
                    );

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);

        // Handle the window exposure
        if (event.type == Expose) {
            XDrawString(display, window, DefaultGC(display, screen), 10, 50,
                        title.str, title.len);
        }
        // Handle key press
        if (event.type == KeyPress) {
            break;
        }
    }

    XCloseDisplay(display);
}

#endif // GFX_LINUX_H
