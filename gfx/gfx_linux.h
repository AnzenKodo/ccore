#ifndef GFX_LINUX_H
#define GFX_LINUX_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#undef Bool
#define Bool _Bool

typedef struct Gfx_Linux_State Gfx_Linux_State;
struct Gfx_Linux_State {
    Display *display;
    Window window;
    int screen;
    GC gc;
    Atom wm_delete_window;
    Atom wm_sync_request;
};

fn void gfx_init(void) {
}

fn Gfx_Handle *gfx_win_open(Str8 title, Vec2F32 resolution)
{
    Display *display = XOpenDisplay(NULL);
    I16 screen = DefaultScreen(display);

    // Create the window
    Window window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        10, 10, resolution.x, resolution.y, 1,
        0, 0
    );

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

    Arena *arena = arena_alloc();
    Gfx_Handle *gfx_handle = 0;
    gfx_handle = arena_push(arena, Gfx_Handle, 1);
    gfx_handle->arena = arena;
    gfx_handle->win_close_status = false;

    Gfx_Linux_State *state = 0;
    state = arena_push(arena, Gfx_Linux_State, 1);
    state->display = display;
    state->screen = screen;
    state->window = window;
    state->gc = gc;
    state->wm_delete_window = wm_delete_window;
    state->wm_sync_request = wm_sync_request;

    Gfx_Os_Handle os_handle = {{(U64)state}};
    gfx_handle->os_handle = os_handle;

    return gfx_handle;
}

fn void gfx_win_close(Gfx_Handle *gfx_handle)
{
    Gfx_Linux_State *state = cast(Gfx_Linux_State *)gfx_handle->os_handle.u64[0];
    XFreeGC(state->display, state->gc);
    XDestroyWindow(state->display, state->window);
    XCloseDisplay(state->display);
    arena_free(gfx_handle->arena);
}

fn void gfx_begin_draw(Gfx_Handle *gfx_handle)
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
    Gfx_Linux_State *state = cast(Gfx_Linux_State *)gfx_handle->os_handle.u64[0];
    Display *display = state->display;

    XEvent xevent;
    XNextEvent(display, &xevent);
    Gfx_Event event = {0};

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
            if((Atom)xevent.xclient.data.l[0] == state->wm_delete_window)
            {
                event.type = Gfx_EventType_WindowClose;
            }
            else if((Atom)xevent.xclient.data.l[0] == state->wm_sync_request)
            {
            }
        }break;
        case ConfigureNotify:
        {
            win_size.x = xevent.xconfigure.width;
            win_size.y = xevent.xconfigure.height;
        }break;
    }

    return event;
}

fn Bool gfx_is_key_pressed(Gfx_Handle *gfx_handle, Gfx_Key key)
{
    return gfx_handle->event.key == key;
}

fn I16 gfx_get_display_width(Gfx_Handle *gfx_handle) {
    Gfx_Linux_State *state = cast(Gfx_Linux_State *)gfx_handle->os_handle.u64[0];
    return DisplayWidth(state->display, state->screen);
}

fn I16 gfx_get_display_height(Gfx_Handle *gfx_handle) {
    Gfx_Linux_State *state = cast(Gfx_Linux_State *)gfx_handle->os_handle.u64[0];
    return DisplayHeight(state->display, state->screen);
}

fn I16 gfx_get_display_width(Gfx_Handle *gfx_handle) {
   return gfx_handle->event.win_size.x;
}

fn I16 gfx_get_display_height(Gfx_Handle *gfx_handle) {
    return gfx_handle->event.win_size.y;
}


#endif // GFX_LINUX_H
