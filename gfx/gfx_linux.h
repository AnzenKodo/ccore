#ifndef GFX_LINUX_H
#define GFX_LINUX_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#undef Bool
#define Bool _Bool

typedef struct Gfx_Linux_State Gfx_Linux_State;
struct Gfx_Linux_State {
    Display *display;
    Window window;
    U16 screen;
    GC gc;
    Atom wm_delete_window;
    Atom wm_sync_request;
    Gfx_Event event;
};

global Gfx_Linux_State *gfx_linux_state = 0;

fn void gfx_init(void)
{
}

fn Gfx_Handle *gfx_win_open(Str8 title, Vec2F32 resolution)
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
    XSetWMProtocols(display, window, &protocols, ArrayCount(protocols));

    // Create a Graphics Context
    GC gc = XCreateGC(display, window, 0, NULL);

    // Set window title
    XStoreName(display, window, cast(const char *)title.str);

    Arena *arena = arena_alloc();
    Gfx_Handle *gfx_handle = 0;
    gfx_handle = arena_push(arena, Gfx_Handle, 1);
    gfx_handle->arena = arena;
    gfx_handle->win_close_status = false;

    gfx_linux_state = arena_push(arena, Gfx_Linux_State, 1);
    gfx_linux_state->display = display;
    gfx_linux_state->screen = screen;
    gfx_linux_state->window = window;
    gfx_linux_state->gc = gc;
    gfx_linux_state->wm_delete_window = wm_delete_window;
    gfx_linux_state->wm_sync_request = wm_sync_request;

    //========================================
    gfx_event_get(gfx_handle);
    //========================================

    return gfx_handle;
}

fn void gfx_win_close(Gfx_Handle *gfx_handle)
{
    XFreeGC(gfx_linux_state->display, gfx_linux_state->gc);
    XDestroyWindow(gfx_linux_state->display, gfx_linux_state->window);
    XCloseDisplay(gfx_linux_state->display);
    arena_free(gfx_handle->arena);
}

fn void gfx_begin(Gfx_Handle *gfx_handle)
{
    Gfx_Event event = gfx_event_get(gfx_handle);
    gfx_handle->event = event;
    if (event.type == Gfx_EventType_WindowClose) {
        gfx_set_win_close(gfx_handle);
    }
}

fn void gfx_set_win_close(Gfx_Handle *gfx_handle)
{
    gfx_handle->win_close_status = true;
}

fn Bool gfx_should_win_close(Gfx_Handle *gfx_handle)
{
    return gfx_handle->win_close_status;
}

fn Gfx_Event gfx_event_get(Gfx_Handle *gfx_handle)
{
    Display *display = gfx_linux_state->display;

    Gfx_Event event = {0};
    while (XPending(display)) {
        XEvent xevent = {0};
        XNextEvent(display, &xevent);

        switch(xevent.type)
        {
            default: {}break;
            case KeyPress:
            case KeyRelease:
            {
                // Determine mod_key
                Gfx_ModKey mod_key = 0;
                if(xevent.xkey.state & ShiftMask)   { mod_key |= Gfx_ModKey_Shift; }
                if(xevent.xkey.state & ControlMask) { mod_key |= Gfx_ModKey_Ctrl; }
                if(xevent.xkey.state & Mod1Mask)    { mod_key |= Gfx_ModKey_Alt; }

                // Map Keycode -> keysym
                U32 keysym = XLookupKeysym(&xevent.xkey, 0);

                // Map keysym -> Gfx_Key
                Gfx_Key key = Gfx_Key_Null;
                switch(keysym)
                {
                    default:
                    {
                        if(XK_F1 <= keysym && keysym <= XK_F24) {
                            key = (Gfx_Key)(Gfx_Key_F1 + (keysym - XK_F1));
                        }
                        else if('0' <= keysym && keysym <= '9') {
                            key = Gfx_Key_0 + (keysym-'0');
                        }
                        break;
                    }

                    case XK_Escape:{key = Gfx_Key_Esc;};break;
                    case '-':{key = Gfx_Key_Minus;}break;
                    case '=':{key = Gfx_Key_Equal;}break;
                    case '[':{key = Gfx_Key_LeftBracket;}break;
                    case ']':{key = Gfx_Key_RightBracket;}break;
                    case ';':{key = Gfx_Key_Semicolon;}break;
                    case '\'':{key = Gfx_Key_Quote;}break;
                    case '.':{key = Gfx_Key_Period;}break;
                    case ',':{key = Gfx_Key_Comma;}break;
                    case '/':{key = Gfx_Key_Slash;}break;
                    case '\\':{key = Gfx_Key_BackSlash;}break;
                    case 'a':case 'A':{key = Gfx_Key_A;}break;
                    case 'b':case 'B':{key = Gfx_Key_B;}break;
                    case 'c':case 'C':{key = Gfx_Key_C;}break;
                    case 'd':case 'D':{key = Gfx_Key_D;}break;
                    case 'e':case 'E':{key = Gfx_Key_E;}break;
                    case 'f':case 'F':{key = Gfx_Key_F;}break;
                    case 'g':case 'G':{key = Gfx_Key_G;}break;
                    case 'h':case 'H':{key = Gfx_Key_H;}break;
                    case 'i':case 'I':{key = Gfx_Key_I;}break;
                    case 'j':case 'J':{key = Gfx_Key_J;}break;
                    case 'k':case 'K':{key = Gfx_Key_K;}break;
                    case 'l':case 'L':{key = Gfx_Key_L;}break;
                    case 'm':case 'M':{key = Gfx_Key_M;}break;
                    case 'n':case 'N':{key = Gfx_Key_N;}break;
                    case 'o':case 'O':{key = Gfx_Key_O;}break;
                    case 'p':case 'P':{key = Gfx_Key_P;}break;
                    case 'q':case 'Q':{key = Gfx_Key_Q;}break;
                    case 'r':case 'R':{key = Gfx_Key_R;}break;
                    case 's':case 'S':{key = Gfx_Key_S;}break;
                    case 't':case 'T':{key = Gfx_Key_T;}break;
                    case 'u':case 'U':{key = Gfx_Key_U;}break;
                    case 'v':case 'V':{key = Gfx_Key_V;}break;
                    case 'w':case 'W':{key = Gfx_Key_W;}break;
                    case 'x':case 'X':{key = Gfx_Key_X;}break;
                    case 'y':case 'Y':{key = Gfx_Key_Y;}break;
                    case 'z':case 'Z':{key = Gfx_Key_Z;}break;
                    case ' ':{key = Gfx_Key_Space;}break;
                }
                event.type = xevent.type == KeyPress ? Gfx_EventType_Press : Gfx_EventType_Release;
                event.mod_key = mod_key;
                event.key = key;
            }break;

            // Mouse button presses/releases
            case ButtonPress:
            case ButtonRelease:
            {
                // Determine mod_key
                Gfx_ModKey mod_key = 0;
                if(xevent.xkey.state & ShiftMask)   { mod_key |= Gfx_ModKey_Shift; }
                if(xevent.xkey.state & ControlMask) { mod_key |= Gfx_ModKey_Ctrl; }
                if(xevent.xkey.state & Mod1Mask)    { mod_key |= Gfx_ModKey_Alt; }

                // rjf: map button -> Gfx_Key
                Gfx_Key key = Gfx_Key_Null;
                switch(xevent.xbutton.button)
                {
                    default:{}break;
                    case Button1:{key = Gfx_Key_LeftMouseButton;}break;
                    case Button2:{key = Gfx_Key_MiddleMouseButton;}break;
                    case Button3:{key = Gfx_Key_RightMouseButton;}break;
                }
                event.type = xevent.type == ButtonPress ? Gfx_EventType_Press : Gfx_EventType_Release;
                event.mod_key = mod_key;
                event.key = key;
            }break;

            // Mouse Motion
            case MotionNotify:
            {
                event.type = Gfx_EventType_MouseMove;
                event.pos.x = (F32)xevent.xmotion.x;
                event.pos.y = (F32)xevent.xmotion.y;
            }break;

            //- rjf: window focus/unfocus
            case FocusIn: break;
            case FocusOut:
            {
                    event.type = Gfx_EventType_WindowLoseFocus;
            }break;

            // Client messages
            case ClientMessage:
            {
                if((Atom)xevent.xclient.data.l[0] == gfx_linux_state->wm_delete_window)
                {
                    event.type = Gfx_EventType_WindowClose;
                }
                else if((Atom)xevent.xclient.data.l[0] == gfx_linux_state->wm_sync_request)
                {
                }
                XFlush(gfx_linux_state->display);
            }break;
            case ConfigureNotify:
            {
                gfx_linux_state->event.win_size.x = xevent.xconfigure.width;
                gfx_linux_state->event.win_size.y = xevent.xconfigure.height;
                event.win_size.x = xevent.xconfigure.width;
                event.win_size.y = xevent.xconfigure.height;
                XFlush(gfx_linux_state->display);
            }break;
        }
    }
    return event;
}

fn Bool gfx_is_key_pressed(Gfx_Handle *gfx_handle, Gfx_Key key)
{
    return gfx_handle->event.key == key;
}

fn I16 gfx_get_display_width(void) {
    return DisplayWidth(gfx_linux_state->display, gfx_linux_state->screen);
}

fn I16 gfx_get_display_height(void) {
    return DisplayHeight(gfx_linux_state->display, gfx_linux_state->screen);
}

fn F32 gfx_get_win_width(void) {
   return gfx_linux_state->event.win_size.x;
}

fn F32 gfx_get_win_height(void) {
    return gfx_linux_state->event.win_size.y;
}

#include "icon.h"
fn void gfx_set_icon(void) {
    Atom wm_icon = XInternAtom(gfx_linux_state->display, "_NET_WM_ICON", False);
    XChangeProperty(
        gfx_linux_state->display, gfx_linux_state->window, wm_icon,
        XA_CARDINAL, 32, PropModeReplace,
        (U16*)ScuttleIcon, sizeof(ScuttleIcon) / sizeof(long));
}

#endif // GFX_LINUX_H
