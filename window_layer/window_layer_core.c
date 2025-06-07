// Window Close Functions
//=============================================================================

internal void
wl_set_window_close(void)
{
    wl_state.win_should_close = true;
}

internal bool
wl_should_window_close(void)
{
    return wl_state.win_should_close;
}

// Event Functions
//=============================================================================

internal void
wl_update_events(void)
{
    // Update Event ===========================================================
    wl_state.event = wl_get_event();

    // Update FPS =============================================================
    wl_state.frame_count++;
    U64 frame_current_time = os_now_microsec();
    U64 delta = frame_current_time - wl_state.frame_prev_time;
    if (delta >= Million(1)) {
        wl_state.fps = wl_state.frame_count;
        wl_state.frame_count = 0;
        wl_state.frame_prev_time = frame_current_time;
    }
}

internal bool
wl_is_key_pressed(Wl_Key key)
{
    return wl_state.event.key == key;
}

internal bool
wl_is_event_happen(Wl_EventType type)
{
    return wl_state.event.type == type;
}

// Get Window Information
//=============================================================================

internal U32
wl_get_display_width(void)
{
    return (U32)wl_state.display_size.x;
}

internal U32
wl_get_display_height(void)
{
    return (U32)wl_state.display_size.y;
}

internal U32
wl_get_window_width(void)
{
   return (U32)wl_state.win_size.x;
}

internal U32
wl_get_window_height(void)
{
    return (U32)wl_state.win_size.y;
}

// FPS
//=============================================================================

internal U32
wl_get_fps(void)
{
    return wl_state.fps;
}

internal void
wl_set_fps(U32 fps)
{
    os_sleep_microsec(Million(1)/fps);
}
