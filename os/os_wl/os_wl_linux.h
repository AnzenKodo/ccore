#ifndef OS_WL_LINUX_H
#define OS_WL_LINUX_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#undef Bool
#if LANG_C
    #define Bool  _Bool
#else
    #define Bool  bool
#endif

typedef struct Os_Wl_Linux_State Os_Wl_Linux_State;
struct Os_Wl_Linux_State {
    Display *display;
    Window window;
    U16 screen;
    GC gc;
    Atom wm_delete_window;
    Atom wm_sync_request;
    Os_Event event;
};

global Os_Wl_Linux_State *os_wl_linux_state = 0;

fn void os_init(void)
{
}

fn Os_Wl_Handle *os_window_open(Str8 title, Vec2F32 resolution)
{
    Display *display = XOpenDisplay(NULL);
    U16 screen = DefaultScreen(display);

    // Create the window
    // Window window = XCreateSimpleWindow(
    //     display,
    //     RootWindow(display, screen),
    //     10, 10, resolution.x, resolution.y, 1,
    //     0, 0
    // );

    Window window = XCreateWindow(
        display, XDefaultRootWindow(display),
        0, 0, resolution.x, resolution.y, 0,
        CopyFromParent, InputOutput, CopyFromParent,
        0, 0);

    // Select kind of events we are interested in
    XSelectInput(
        display, window,
        ExposureMask|
        PointerMotionMask|
        ButtonPressMask|
        ButtonReleaseMask|
        KeyPressMask|
        KeyReleaseMask|
        FocusChangeMask|
        StructureNotifyMask
    );

    // Map the window to the screen
    XMapWindow(display, window);

    XSync(display, false);

    // Tell the window manager we want to handle the delete window message
    Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", false);
    Atom wm_sync_request = XInternAtom(display, "_NET_WM_SYNC_REQUEST", false);

    Atom protocols[] = { wm_delete_window, wm_sync_request };
    XSetWMProtocols(display, window, protocols, ArrayCount(protocols));

    // Create a Graphics Context
    GC gc = XCreateGC(display, window, 0, NULL);

    // Set window title
    XStoreName(display, window, cast(const char *)title.str);

    Arena *arena = arena_alloc();
    Os_Wl_Handle *os_wl_handle = 0;
    os_wl_handle = arena_push(arena, Os_Wl_Handle, 1);
    os_wl_handle->arena = arena;
    os_wl_handle->win_close_status = false;

    os_wl_linux_state = arena_push(arena, Os_Wl_Linux_State, 1);
    os_wl_linux_state->display = display;
    os_wl_linux_state->screen = screen;
    os_wl_linux_state->window = window;
    os_wl_linux_state->gc = gc;
    os_wl_linux_state->wm_delete_window = wm_delete_window;
    os_wl_linux_state->wm_sync_request = wm_sync_request;

    //========================================
    os_event_get();
    //========================================

    return os_wl_handle;
}

fn void os_window_close(Os_Wl_Handle *os_wl_handle)
{
    XFreeGC(os_wl_linux_state->display, os_wl_linux_state->gc);
    XDestroyWindow(os_wl_linux_state->display, os_wl_linux_state->window);
    XCloseDisplay(os_wl_linux_state->display);
    arena_free(os_wl_handle->arena);
}

fn void os_wl_begin(Os_Wl_Handle *os_wl_handle)
{
    Os_Event event = os_event_get();
    os_wl_handle->event = event;
    if (event.type == Os_EventType_WindowClose) {
        os_set_window_close(os_wl_handle);
    }
}

fn void os_set_window_close(Os_Wl_Handle *os_wl_handle)
{
    os_wl_handle->win_close_status = true;
}

fn Bool os_should_window_close(Os_Wl_Handle *os_wl_handle)
{
    return os_wl_handle->win_close_status;
}

fn Os_Event os_event_get(void)
{
    Display *display = os_wl_linux_state->display;

    Os_Event event = zero_struct;
    while (XPending(display)) {
        XEvent xevent = zero_struct;
        XNextEvent(display, &xevent);

        switch(xevent.type)
        {
            default: {}break;
            case KeyPress:
            case KeyRelease:
            {
                // Determine mod_key
                Os_ModKey mod_key = cast(Os_ModKey)0;
                if(xevent.xkey.state & ShiftMask)   { mod_key = cast(Os_ModKey)(mod_key | Os_ModKey_Shift); }
                if(xevent.xkey.state & ControlMask) { mod_key = cast(Os_ModKey)(mod_key | Os_ModKey_Ctrl); }
                if(xevent.xkey.state & Mod1Mask)    { mod_key = cast(Os_ModKey)(mod_key | Os_ModKey_Alt); }

                // Map Keycode -> keysym
                U32 keysym = XLookupKeysym(&xevent.xkey, 0);

                // Map keysym -> Os_Key
                Os_Key key = Os_Key_Null;
                switch(keysym)
                {
                    default:
                    {
                        if(XK_F1 <= keysym && keysym <= XK_F24) {
                            key = (Os_Key)(Os_Key_F1 + (keysym - XK_F1));
                        }
                        else if('0' <= keysym && keysym <= '9') {
                            key = (Os_Key)(Os_Key_0 + (keysym-'0'));
                        }
                        break;
                    }

                    case XK_Escape:{key = Os_Key_Esc;};break;
                    case '-':{key = Os_Key_Minus;}break;
                    case '=':{key = Os_Key_Equal;}break;
                    case '[':{key = Os_Key_LeftBracket;}break;
                    case ']':{key = Os_Key_RightBracket;}break;
                    case ';':{key = Os_Key_Semicolon;}break;
                    case '\'':{key = Os_Key_Quote;}break;
                    case '.':{key = Os_Key_Period;}break;
                    case ',':{key = Os_Key_Comma;}break;
                    case '/':{key = Os_Key_Slash;}break;
                    case '\\':{key = Os_Key_BackSlash;}break;
                    case 'a':case 'A':{key = Os_Key_A;}break;
                    case 'b':case 'B':{key = Os_Key_B;}break;
                    case 'c':case 'C':{key = Os_Key_C;}break;
                    case 'd':case 'D':{key = Os_Key_D;}break;
                    case 'e':case 'E':{key = Os_Key_E;}break;
                    case 'f':case 'F':{key = Os_Key_F;}break;
                    case 'g':case 'G':{key = Os_Key_G;}break;
                    case 'h':case 'H':{key = Os_Key_H;}break;
                    case 'i':case 'I':{key = Os_Key_I;}break;
                    case 'j':case 'J':{key = Os_Key_J;}break;
                    case 'k':case 'K':{key = Os_Key_K;}break;
                    case 'l':case 'L':{key = Os_Key_L;}break;
                    case 'm':case 'M':{key = Os_Key_M;}break;
                    case 'n':case 'N':{key = Os_Key_N;}break;
                    case 'o':case 'O':{key = Os_Key_O;}break;
                    case 'p':case 'P':{key = Os_Key_P;}break;
                    case 'q':case 'Q':{key = Os_Key_Q;}break;
                    case 'r':case 'R':{key = Os_Key_R;}break;
                    case 's':case 'S':{key = Os_Key_S;}break;
                    case 't':case 'T':{key = Os_Key_T;}break;
                    case 'u':case 'U':{key = Os_Key_U;}break;
                    case 'v':case 'V':{key = Os_Key_V;}break;
                    case 'w':case 'W':{key = Os_Key_W;}break;
                    case 'x':case 'X':{key = Os_Key_X;}break;
                    case 'y':case 'Y':{key = Os_Key_Y;}break;
                    case 'z':case 'Z':{key = Os_Key_Z;}break;
                    case ' ':{key = Os_Key_Space;}break;
                }
                event.type = xevent.type == KeyPress ? Os_EventType_Press : Os_EventType_Release;
                event.mod_key = mod_key;
                event.key = key;
            }break;

            // Mouse button presses/releases
            case ButtonPress:
            case ButtonRelease:
            {
                // Determine mod_key
                Os_ModKey mod_key = cast(Os_ModKey)0;
                if(xevent.xkey.state & ShiftMask)   { mod_key = cast(Os_ModKey)(mod_key | Os_ModKey_Shift); }
                if(xevent.xkey.state & ControlMask) { mod_key = cast(Os_ModKey)(mod_key | Os_ModKey_Ctrl); }
                if(xevent.xkey.state & Mod1Mask)    { mod_key = cast(Os_ModKey)(mod_key | Os_ModKey_Alt); }

                // rjf: map button -> Os_Key
                Os_Key key = Os_Key_Null;
                switch(xevent.xbutton.button)
                {
                    default:{}break;
                    case Button1:{key = Os_Key_LeftMouseButton;}break;
                    case Button2:{key = Os_Key_MiddleMouseButton;}break;
                    case Button3:{key = Os_Key_RightMouseButton;}break;
                }
                event.type = xevent.type == ButtonPress ? Os_EventType_Press : Os_EventType_Release;
                event.mod_key = mod_key;
                event.key = key;
            }break;

            // Mouse Motion
            case MotionNotify:
            {
                event.type = Os_EventType_MouseMove;
                event.pos.x = (F32)xevent.xmotion.x;
                event.pos.y = (F32)xevent.xmotion.y;
            }break;

            //- rjf: window focus/unfocus
            case FocusIn: break;
            case FocusOut:
            {
                    event.type = Os_EventType_WindowLoseFocus;
            }break;

            // Client messages
            case ClientMessage:
            {
                if((Atom)xevent.xclient.data.l[0] == os_wl_linux_state->wm_delete_window)
                {
                    event.type = Os_EventType_WindowClose;
                }
                else if((Atom)xevent.xclient.data.l[0] == os_wl_linux_state->wm_sync_request)
                {
                }
                XFlush(os_wl_linux_state->display);
            }break;
            case ConfigureNotify:
            {
                os_wl_linux_state->event.win_size.x = xevent.xconfigure.width;
                os_wl_linux_state->event.win_size.y = xevent.xconfigure.height;
                event.win_size.x = xevent.xconfigure.width;
                event.win_size.y = xevent.xconfigure.height;
                XFlush(os_wl_linux_state->display);
            }break;
        }
    }
    return event;
}

fn Bool os_is_key_pressed(Os_Wl_Handle *os_wl_handle, Os_Key key)
{
    return os_wl_handle->event.key == key;
}

fn I16 os_get_display_width(void) {
    return DisplayWidth(os_wl_linux_state->display, os_wl_linux_state->screen);
}

fn I16 os_get_display_height(void) {
    return DisplayHeight(os_wl_linux_state->display, os_wl_linux_state->screen);
}

fn F32 os_get_window_width(void) {
   return os_wl_linux_state->event.win_size.x;
}

fn F32 os_get_window_height(void) {
    return os_wl_linux_state->event.win_size.y;
}

#include "icon.h"
fn void os_set_window_icon(void) {
    Atom wm_icon = XInternAtom(os_wl_linux_state->display, "_NET_WM_ICON", False);
    XChangeProperty(
        os_wl_linux_state->display, os_wl_linux_state->window, wm_icon,
        XA_CARDINAL, 32, PropModeReplace,
        (const U8*)ScuttleIcon, sizeof(ScuttleIcon) / sizeof(long));
}

#endif // OS_WL_LINUX_H
