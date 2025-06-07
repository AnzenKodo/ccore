// Basic Window functions
//=============================================================================

internal void
wl_window_open(Str8 title, Vec2I32 win_size)
{
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    xcb_window_t window = xcb_generate_id(connection);
    xcb_screen_t *screen = xcb_setup_roots_iterator(
        xcb_get_setup(connection)
    ).data;

    // Create Window ==========================================================
    U32 mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t value_list[] = {
        screen->black_pixel,
		XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS |
		XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
		XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_LEAVE_WINDOW |
		XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
		XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_FOCUS_CHANGE |
        XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
    };
    xcb_create_window(
        connection, XCB_COPY_FROM_PARENT, window, screen->root,
        0, 0, win_size.x, win_size.y, 0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, mask, value_list
    );

    // Set Window Title =======================================================
    xcb_change_property(
        connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING, 8, title.size, title.str
    );
    xcb_change_property(
        connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_ICON_NAME,
        XCB_ATOM_STRING, 8, title.size, title.str
    );
    // xcb_change_property(
    //     connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_CLASS,
    //     XCB_ATOM_STRING, 8, sizeof("title""\0""Title"), "title\0Title"
    // );

    // Handle Close Event =====================================================
    xcb_intern_atom_reply_t* wm_protocols_reply = xcb_intern_atom_reply(
        connection, xcb_intern_atom(connection, 1, 12, "WM_PROTOCOLS"), NULL
    );
    xcb_intern_atom_reply_t* wm_delete_window_reply = xcb_intern_atom_reply(
        connection, xcb_intern_atom(connection, 1, 16,"WM_DELETE_WINDOW"), NULL
    );
    xcb_change_property(
        connection, XCB_PROP_MODE_REPLACE, window, wm_protocols_reply->atom,
        XCB_ATOM_ATOM, 32, 1, &wm_delete_window_reply->atom
    );

    // Handle Window Icon =====================================================
    xcb_intern_atom_reply_t* wm_icon_reply = xcb_intern_atom_reply(
        connection, xcb_intern_atom(connection, 1, 12, "_NET_WM_ICON"), NULL
    );

    // Map Window =============================================================
    xcb_map_window(connection, window);

    // Get Size ===============================================================
    wl_state.display_size.x = screen->width_in_pixels;
    wl_state.display_size.y = screen->height_in_pixels;
    wl_state.win_size.x = win_size.x;
    wl_state.win_size.y = win_size.y;
    wl_state.frame_prev_time = os_now_microsec();

    // Window Layer State =====================================================
    wl_linux_state.conn = connection;
    wl_linux_state.screen = screen;
    wl_linux_state.window = window;
    wl_linux_state.wm_delete_window = wm_delete_window_reply->atom;
    wl_linux_state.wm_icon = wm_icon_reply->atom;

    // Free ===================================================================
    free(wm_delete_window_reply);
    free(wm_protocols_reply);
    free(wm_icon_reply);
}

internal void wl_window_icon_set(U32 *icon_data, U32 width, U32 height) {
    U32 data[2 + width * height];
    data[0] = width;
    data[1] = height;
    mem_copy(data + 2, icon_data, width * height * sizeof(U32));
    xcb_change_property(
        wl_linux_state.conn, XCB_PROP_MODE_REPLACE, wl_linux_state.window,
        wl_linux_state.wm_icon, XCB_ATOM_CARDINAL, 32,
        2 + width * height, data
    );
}

internal void
wl_window_close(void)
{
    xcb_disconnect(wl_linux_state.conn);
}

// Event Functions
//=============================================================================

internal Wl_Event wl_get_event(void)
{
    Wl_Event event = ZERO_STRUCT;
    xcb_generic_event_t *xcb_event;

    while ((xcb_event = xcb_poll_for_event(wl_linux_state.conn)))
    {
        switch (xcb_event->response_type & ~0x80)
        {
            // Keyboard key presses/releases ==================================
            case XCB_KEY_PRESS:
            case XCB_KEY_RELEASE:
            {
                xcb_key_release_event_t *key_event = cast(xcb_key_release_event_t *)xcb_event;

                // Determine mod_key
                Wl_ModKey mod_key = cast(Wl_ModKey)0;
                if(key_event->state & XCB_MOD_MASK_SHIFT)   {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Shift);
                }
                if(key_event->state & XCB_MOD_MASK_CONTROL) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Ctrl);
                }
                if(key_event->state & XCB_MOD_MASK_1) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Alt);
                }

                // Assign keys
                Wl_Key key = Wl_Key_Null;
                switch(key_event->detail)
                {
                    // NOTE(ak): to get keycodes run `xmodmap -pk`
                    case 9:{key = Wl_Key_Esc;};break;
                    case 10:{key = Wl_Key_1;}break;
                    case 11:{key = Wl_Key_2;}break;
                    case 12:{key = Wl_Key_3;}break;
                    case 13:{key = Wl_Key_4;}break;
                    case 14:{key = Wl_Key_5;}break;
                    case 15:{key = Wl_Key_6;}break;
                    case 16:{key = Wl_Key_7;}break;
                    case 17:{key = Wl_Key_8;}break;
                    case 18:{key = Wl_Key_9;}break;
                    case 19:{key = Wl_Key_0;}break;
                    case 20:{key = Wl_Key_Minus;}break;
                    case 21:{key = Wl_Key_Equal;}break;
                    case 22:{key = Wl_Key_Backspace;}break;
                    case 23:{key = Wl_Key_Tab;}break;
                    case 24:{key = Wl_Key_Q;}break;
                    case 25:{key = Wl_Key_W;}break;
                    case 26:{key = Wl_Key_E;}break;
                    case 27:{key = Wl_Key_R;}break;
                    case 28:{key = Wl_Key_T;}break;
                    case 29:{key = Wl_Key_Y;}break;
                    case 30:{key = Wl_Key_U;}break;
                    case 31:{key = Wl_Key_I;}break;
                    case 32:{key = Wl_Key_O;}break;
                    case 33:{key = Wl_Key_P;}break;
                    case 34:{key = Wl_Key_LeftBracket;}break;
                    case 35:{key = Wl_Key_RightBracket;}break;
                    case 36:{key = Wl_Key_Return;}break;
                    case 37:{key = Wl_Key_CtrlLeft;}break;
                    case 38:{key = Wl_Key_A;}break;
                    case 39:{key = Wl_Key_S;}break;
                    case 40:{key = Wl_Key_D;}break;
                    case 41:{key = Wl_Key_F;}break;
                    case 42:{key = Wl_Key_G;}break;
                    case 43:{key = Wl_Key_H;}break;
                    case 44:{key = Wl_Key_J;}break;
                    case 45:{key = Wl_Key_K;}break;
                    case 46:{key = Wl_Key_L;}break;
                    case 47:{key = Wl_Key_Semicolon;}break;
                    case 48:{key = Wl_Key_Quote;}break;
                    case 49:{key = Wl_Key_Tick;}break;
                    case 50:{key = Wl_Key_ShiftLeft;}break;
                    case 51:{key = Wl_Key_BackSlash;}break;
                    case 52:{key = Wl_Key_Z;}break;
                    case 53:{key = Wl_Key_X;}break;
                    case 54:{key = Wl_Key_C;}break;
                    case 55:{key = Wl_Key_V;}break;
                    case 56:{key = Wl_Key_B;}break;
                    case 57:{key = Wl_Key_N;}break;
                    case 58:{key = Wl_Key_M;}break;
                    case 59:{key = Wl_Key_Comma;}break;
                    case 60:{key = Wl_Key_Period;}break;
                    case 61:{key = Wl_Key_Slash;}break;
                    case 62:{key = Wl_Key_ShiftRight;}break;
                    case 63:{key = Wl_Key_NumStar;}break;
                    case 64:{key = Wl_Key_AltLeft;}break;
                    case 65:{key = Wl_Key_Space;}break;
                    case 66:{key = Wl_Key_CapsLock;}break;
                    case 67:{key = Wl_Key_F1;}break;
                    case 68:{key = Wl_Key_F2;}break;
                    case 69:{key = Wl_Key_F3;}break;
                    case 70:{key = Wl_Key_F4;}break;
                    case 71:{key = Wl_Key_F5;}break;
                    case 72:{key = Wl_Key_F6;}break;
                    case 73:{key = Wl_Key_F7;}break;
                    case 74:{key = Wl_Key_F8;}break;
                    case 75:{key = Wl_Key_F9;}break;
                    case 76:{key = Wl_Key_F10;}break;
                    case 77:{key = Wl_Key_NumLock;}break;
                    case 78:{key = Wl_Key_ScrollLock;}break;
                    case 79:{key = Wl_Key_Num7;}break;
                    case 80:{key = Wl_Key_Num8;}break;
                    case 81:{key = Wl_Key_Num9;}break;
                    case 82:{key = Wl_Key_NumMinus;}break;
                    case 83:{key = Wl_Key_Num4;}break;
                    case 84:{key = Wl_Key_Num5;}break;
                    case 85:{key = Wl_Key_Num6;}break;
                    case 86:{key = Wl_Key_NumPlus;}break;
                    case 87:{key = Wl_Key_Num1;}break;
                    case 88:{key = Wl_Key_Num2;}break;
                    case 89:{key = Wl_Key_Num3;}break;
                    case 90:{key = Wl_Key_Num0;}break;
                    case 91:{key = Wl_Key_NumPeriod;}break;
                    // 92 ISO_Level3_Shift
                    // 93
                    // 94 less
                    case 95:{key = Wl_Key_F11;}break;
                    case 96:{key = Wl_Key_F12;}break;
                    // 97
                    // 98 Katakana
                    // 99 Hiragana
                    // 100 Henkan_Mode
                    // 101 Hiragana_Katakana
                    // 102 Muhenkan
                    // 103
                    case 104:{key = Wl_Key_NumReturn;}break;
                    case 105:{key = Wl_Key_CtrlRight;}break;
                    case 106:{key = Wl_Key_NumSlash;}break;
                    case 107:{key = Wl_Key_Print;}break;
                    case 108:{key = Wl_Key_AltRight;}break;
                    // 109 Linefeed
                    case 110:{key = Wl_Key_Home;}break;
                    case 111:{key = Wl_Key_Up;}break;
                    case 112:{key = Wl_Key_PageUp;}break;
                    case 113:{key = Wl_Key_Left;}break;
                    case 114:{key = Wl_Key_Right;}break;
                    case 115:{key = Wl_Key_End;}break;
                    case 116:{key = Wl_Key_Down;}break;
                    case 117:{key = Wl_Key_PageDown;}break;
                    case 118:{key = Wl_Key_Insert;}break;
                    case 119:{key = Wl_Key_Delete;}break;
                    // 120
                    // case 121:{key = Wl_Key_AudioMute;}break;
                    // case 122:{key = Wl_Key_AudioLowerVolume;}break;
                    // case 123:{key = Wl_Key_AudioRaiseVolume;}break;
                    // 124 XF86PowerOff
                    // 125 KP_Equal
                    // 126 plusminus
                    case 127:{key = Wl_Key_Pause;}break;
                    // 128 XF86LaunchA
                    // 129 KP_Decimal
                    // 130 Hangul
                    // 131 Hangul_Hanja
                    // 132
                    case 133:{key = Wl_Key_SuperLeft;}break;
                    case 134:{key = Wl_Key_SuperRight;}break;
                    case 135:{key = Wl_Key_Menu;}break;
                    default:{}break;
                }

                // Add to Event Variable
                if (key_event->response_type == XCB_KEY_PRESS)
                {
                    event.type = Wl_EventType_Press;
                } else {
                    event.type = Wl_EventType_Release;
                }
                event.key = key;
                event.mod_key = mod_key;
            } break;

            // Mouse button presses/releases ==================================
            case XCB_BUTTON_PRESS:
            case XCB_BUTTON_RELEASE:
            {
                xcb_button_release_event_t *button_event = cast(xcb_button_release_event_t *)xcb_event;

                // Determine mod_key
                Wl_ModKey mod_key = cast(Wl_ModKey)0;
                if(button_event->state & XCB_MOD_MASK_SHIFT)   {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Shift);
                }
                if(button_event->state & XCB_MOD_MASK_CONTROL) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Ctrl);
                }
                if(button_event->state & XCB_MOD_MASK_1) {
                    mod_key = cast(Wl_ModKey)(mod_key | Wl_ModKey_Alt);
                }

                // Assign button
                Wl_Key key = Wl_Key_Null;
                switch(button_event->detail)
                {
                    case 1:{key = Wl_Key_LeftMouseButton;}break;
                    case 2:{key = Wl_Key_MiddleMouseButton;}break;
                    case 3:{key = Wl_Key_RightMouseButton;}break;
                    default:{}
                }

                // Add to Event Variable
                if (button_event->response_type == XCB_BUTTON_PRESS) {
                    event.type = Wl_EventType_Press;
                } else {
                    event.type = Wl_EventType_Release;
                }

                event.mod_key = mod_key;
                event.key = key;
            } break;

            // Mouse Motion ===================================================
    		case XCB_MOTION_NOTIFY:
    		{
                xcb_button_release_event_t *motion_event = cast(xcb_button_release_event_t *)xcb_event;

                // Add to Event Variable
                event.type = Wl_EventType_MouseMove;
                event.pos.x = (F32)motion_event->event_x;
                event.pos.y = (F32)motion_event->event_x;
            } break;

            // Window focus/unfocus ===========================================
            case XCB_FOCUS_IN: break;
            case XCB_FOCUS_OUT:
            {
                event.type = Wl_EventType_WindowLoseFocus;
            }break;

            // Client messages ================================================
            case XCB_CLIENT_MESSAGE:
            {
                xcb_client_message_event_t *message = cast(xcb_client_message_event_t *)xcb_event;
                if (message->data.data32[0] == wl_linux_state.wm_delete_window)
                {
                    event.type = Wl_EventType_WindowClose;
                }
            }break;

            // Window Resize ==================================================
            case XCB_CONFIGURE_NOTIFY:
            {
                xcb_configure_notify_event_t *resize_event = cast(xcb_configure_notify_event_t *)xcb_event;

                // Add to Event Variable
                wl_state.win_size.x = resize_event->width;
                wl_state.win_size.y = resize_event->height;
                event.type = Wl_EventType_WindowResize;
            }break;

            case XCB_EXPOSE:{
            }break;
        } // switch
        free(xcb_event);
    } // while

    // free(xcb_event);
    return event;
}
