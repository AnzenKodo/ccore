#ifndef WINDOW_LAYER_LINUX_H
#define WINDOW_LAYER_LINUX_H

// External Includes
//====================================================================

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

// Redefine Internal Macros
//====================================================================

#undef Bool
#if LANG_C
    #define Bool  _Bool
#else
    #define Bool  bool
#endif

// Types
//====================================================================

typedef struct Wl_Linux_State Wl_Linux_State;
struct Wl_Linux_State {
    Display *display;
    Window window;
    U16 screen;
    Atom wm_delete_window;
    Atom wm_sync_request;
    Wl_Event event;
    XVisualInfo visual_info;
};

// Globals
//====================================================================

global Wl_Linux_State *wl_linux_state = 0;

#endif // WINDOW_LAYER_LINUX_H
