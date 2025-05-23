// Basic Window functions
//====================================================================

fn void wl_window_open(Str8 title, U32 win_width, U32 win_height)
{
    Arena *arena = arena_alloc();
    wl_handle = arena_push(arena, Wl_Handle, 1);
    wl_handle->arena = arena;
    wl_handle->win_close_status = false;

    wl_linux_state = arena_push(arena, Wl_Linux_State, 1);
    wl_linux_state->display = XOpenDisplay(NULL);
    wl_linux_state->screen = DefaultScreen(wl_linux_state->display);

    // Xlib get window property
    XVisualInfo visual_info = ZERO_STRUCT;
    render_set_wl_linux_visual_info(&visual_info);
    // TODO:=============
    // wl_linux_state->visual_info = visual_info;
    //===================

    XSetWindowAttributes set_window_attributes;
    set_window_attributes.colormap = XCreateColormap(
        wl_linux_state->display,
        RootWindow(wl_linux_state->display, visual_info.screen),
        visual_info.visual, AllocNone
    );

	set_window_attributes.event_mask =
	    ExposureMask|
	    PointerMotionMask|
        ButtonPressMask|
        ButtonReleaseMask|
        KeyPressMask|
        KeyReleaseMask|
        FocusChangeMask|
        StructureNotifyMask;

    wl_linux_state->window = XCreateWindow(
        wl_linux_state->display,
        RootWindow(wl_linux_state->display, visual_info.screen),
        0, 0, win_width, win_height, 0,
        visual_info.depth, InputOutput, visual_info.visual,
        CWColormap|CWEventMask, &set_window_attributes
    );

    // Map the window to the screen
    XMapWindow(wl_linux_state->display, wl_linux_state->window);
    XSync(wl_linux_state->display, false);

    // Tell the window manager we want to handle the delete window message
    wl_linux_state->wm_delete_window = XInternAtom(
        wl_linux_state->display, "WM_DELETE_WINDOW", false
    );
    wl_linux_state->wm_sync_request = XInternAtom(
        wl_linux_state->display, "_NET_WM_SYNC_REQUEST", false
    );
    Atom protocols[] = {
        wl_linux_state->wm_delete_window, wl_linux_state->wm_sync_request
    };
    XSetWMProtocols(
        wl_linux_state->display, wl_linux_state->window,
        protocols, ArrayCount(protocols)
    );

    // Set window title
    XStoreName(wl_linux_state->display, wl_linux_state->window,
        cast(const char *)title.str
    );
}

fn void wl_window_close(void)
{
    XDestroyWindow(wl_linux_state->display, wl_linux_state->window);
    XCloseDisplay(wl_linux_state->display);
    arena_free(wl_handle->arena);
}

fn void wl_update_events(void)
{
    XFlush(wl_linux_state->display);
    Wl_Event event = wl_get_event();
    wl_handle->event = event;
    if (wl_handle->event.type == Wl_EventType_WindowClose) {
        wl_set_window_close();
    }
}

// Window close helper functions
//====================================================================

fn void wl_set_window_close(void)
{
    wl_handle->win_close_status = true;
}

fn Bool wl_should_window_close(void)
{
    return wl_handle->win_close_status;
}

// Event functions
//====================================================================

fn Wl_Event wl_get_event(void)
{
    Display *display = wl_linux_state->display;

    Wl_Event event = ZERO_STRUCT;
    while (XPending(display)) {
        XEvent xevent = ZERO_STRUCT;
        XNextEvent(display, &xevent);

        switch(xevent.type)
        {
            default: {}break;
            case KeyPress:
            case KeyRelease:
            {
                // Determine mod_key
                Wl_ModKey mod_key = cast(Wl_ModKey)0;
                if(xevent.xkey.state & ShiftMask)   {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Shift);
                }
                if(xevent.xkey.state & ControlMask) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Ctrl);
                }
                if(xevent.xkey.state & Mod1Mask) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Alt);
                }

                // Map Keycode -> keysym
                U32 keysym = XLookupKeysym(&xevent.xkey, 0);

                // Map keysym -> Wl_Key
                Wl_Key key = Wl_Key_Null;
                switch(keysym)
                {
                    default:
                    {
                        if(XK_F1 <= keysym && keysym <= XK_F24) {
                            key = (Wl_Key)(Wl_Key_F1 + (keysym - XK_F1));
                        }
                        else if('0' <= keysym && keysym <= '9') {
                            key = (Wl_Key)(Wl_Key_0 + (keysym-'0'));
                        }
                        break;
                    }

                    case XK_Escape:{key = Wl_Key_Esc;};break;
                    case '-':{key = Wl_Key_Minus;}break;
                    case '=':{key = Wl_Key_Equal;}break;
                    case '[':{key = Wl_Key_LeftBracket;}break;
                    case ']':{key = Wl_Key_RightBracket;}break;
                    case ';':{key = Wl_Key_Semicolon;}break;
                    case '\'':{key = Wl_Key_Quote;}break;
                    case '.':{key = Wl_Key_Period;}break;
                    case ',':{key = Wl_Key_Comma;}break;
                    case '/':{key = Wl_Key_Slash;}break;
                    case '\\':{key = Wl_Key_BackSlash;}break;
                    case 'a':case 'A':{key = Wl_Key_A;}break;
                    case 'b':case 'B':{key = Wl_Key_B;}break;
                    case 'c':case 'C':{key = Wl_Key_C;}break;
                    case 'd':case 'D':{key = Wl_Key_D;}break;
                    case 'e':case 'E':{key = Wl_Key_E;}break;
                    case 'f':case 'F':{key = Wl_Key_F;}break;
                    case 'g':case 'G':{key = Wl_Key_G;}break;
                    case 'h':case 'H':{key = Wl_Key_H;}break;
                    case 'i':case 'I':{key = Wl_Key_I;}break;
                    case 'j':case 'J':{key = Wl_Key_J;}break;
                    case 'k':case 'K':{key = Wl_Key_K;}break;
                    case 'l':case 'L':{key = Wl_Key_L;}break;
                    case 'm':case 'M':{key = Wl_Key_M;}break;
                    case 'n':case 'N':{key = Wl_Key_N;}break;
                    case 'o':case 'O':{key = Wl_Key_O;}break;
                    case 'p':case 'P':{key = Wl_Key_P;}break;
                    case 'q':case 'Q':{key = Wl_Key_Q;}break;
                    case 'r':case 'R':{key = Wl_Key_R;}break;
                    case 's':case 'S':{key = Wl_Key_S;}break;
                    case 't':case 'T':{key = Wl_Key_T;}break;
                    case 'u':case 'U':{key = Wl_Key_U;}break;
                    case 'v':case 'V':{key = Wl_Key_V;}break;
                    case 'w':case 'W':{key = Wl_Key_W;}break;
                    case 'x':case 'X':{key = Wl_Key_X;}break;
                    case 'y':case 'Y':{key = Wl_Key_Y;}break;
                    case 'z':case 'Z':{key = Wl_Key_Z;}break;
                    case ' ':{key = Wl_Key_Space;}break;
                }

                if (xevent.type == KeyPress) {
                    event.type = Wl_EventType_Press;
                } else {
                    event.type = Wl_EventType_Release;
                }

                event.mod_key = mod_key;
                event.key = key;
            }break;

            // Mouse button presses/releases
            case ButtonPress:
            case ButtonRelease:
            {
                // Determine mod_key
                Wl_ModKey mod_key = cast(Wl_ModKey)0;
                if(xevent.xkey.state & ShiftMask)   {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Shift);
                }
                if(xevent.xkey.state & ControlMask) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Ctrl);
                }
                if(xevent.xkey.state & Mod1Mask) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Alt);
                }

                // rjf: map button -> Wl_Key
                Wl_Key key = Wl_Key_Null;
                switch(xevent.xbutton.button)
                {
                    default:{}break;
                    case Button1:{key = Wl_Key_LeftMouseButton;}break;
                    case Button2:{key = Wl_Key_MiddleMouseButton;}break;
                    case Button3:{key = Wl_Key_RightMouseButton;}break;
                }
                if (xevent.type == ButtonPress) {
                    event.type = Wl_EventType_Press;
                } else {
                    event.type = Wl_EventType_Release;
                }
                event.mod_key = mod_key;
                event.key = key;
            }break;

            // Mouse Motion
            case MotionNotify:
            {
                event.type = Wl_EventType_MouseMove;
                event.pos.x = (F32)xevent.xmotion.x;
                event.pos.y = (F32)xevent.xmotion.y;
            }break;

            //- rjf: window focus/unfocus
            case FocusIn: break;
            case FocusOut:
            {
                event.type = Wl_EventType_WindowLoseFocus;
            }break;

            // Client messages
            case ClientMessage:
            {
                if((Atom)xevent.xclient.data.l[0] == wl_linux_state->wm_delete_window)
                {
                    event.type = Wl_EventType_WindowClose;
                }
                else if((Atom)xevent.xclient.data.l[0] == wl_linux_state->wm_sync_request)
                {
                }
            }break;
            case ConfigureNotify:
            {
                wl_handle->win_size.x = xevent.xconfigure.width;
                wl_handle->win_size.y = xevent.xconfigure.height;
                event.type = Wl_EventType_WindowResize;
            }break;
        } // Switch
    } // While

    return event;
}

fn Bool wl_is_key_pressed(Wl_Key key)
{
    return wl_handle->event.key == key;
}

// Get Window Info
//====================================================================

fn U32 wl_get_display_width(void)
{
    return DisplayWidth(wl_linux_state->display, wl_linux_state->screen);
}

fn U32 wl_get_display_height(void)
{
    return DisplayHeight(wl_linux_state->display, wl_linux_state->screen);
}

fn U32 wl_get_window_width(void)
{
   return (U32)wl_handle->win_size.x;
}

fn U32 wl_get_window_height(void)
{
    return (U32)wl_handle->win_size.y;
}

fn F32 wl_get_monitor_refresh_rate(void)
{
    F32 result = 0;
    XRRScreenResources *screen_res = XRRGetScreenResources(
        wl_linux_state->display, DefaultRootWindow(wl_linux_state->display)
    );

        XRRCrtcInfo *crtc_info = XRRGetCrtcInfo(
            wl_linux_state->display, screen_res, screen_res->crtcs[0]
        );
        if (crtc_info) {
            if (cast(F32)crtc_info->mode != 0) {
                F32 dot_clock = cast(F32)screen_res->modes[crtc_info->mode].dotClock;
                F32 h_pixels = screen_res->modes[crtc_info->mode].hTotal;
                F32 v_pixels = screen_res->modes[crtc_info->mode].vTotal;
                result = dot_clock / (h_pixels * v_pixels);
            }
            XRRFreeCrtcInfo(crtc_info);
        }

    XRRFreeScreenResources(screen_res);
    return result;
}


// Set Window Info
//====================================================================

fn void wl_set_window_icon(const U8 *icon)
{
    Atom wm_icon = XInternAtom(wl_linux_state->display, "_NET_WM_ICON", False);
    XChangeProperty(
        wl_linux_state->display, wl_linux_state->window, wm_icon,
        XA_CARDINAL, 32, PropModeReplace,
        icon, sizeof(*icon) / sizeof(long));
}
