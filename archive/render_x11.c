internal void render_set_wl_linux_visual_info(XVisualInfo *visual_info, Display *display)
{
    int nitems;
    XVisualInfo *xvisual_info = XGetVisualInfo(
        display, VisualScreenMask, visual_info, &nitems
    );
    *visual_info = *xvisual_info;
    XFree(xvisual_info);
}

internal Draw_Buffer render_init(Alloc alloc) {
    Display *display = wl_linux_state.display;
    Window window = wl_linux_state.window;

    I16 width = wl_get_display_width();
    I16 height = wl_get_display_height();
    I32 bytes_per_pixel = 4;
    U16 *memory = alloc_make(alloc, U16, (width * height) * bytes_per_pixel);

    // Initialize Image =======================================================
    XImage *image = XCreateImage(
        display, DefaultVisual(display, XDefaultScreen(display)),
        24, ZPixmap, 0, memory,
        width , height, 32, width * bytes_per_pixel
    );
    render_x11_state.image = *image;
    XFree(image);

    // Initialize States ======================================================

    Draw_Buffer draw_buffer = ZERO_STRUCT;
    draw_buffer.memory = memory;
    draw_buffer.width = width;
    draw_buffer.height = height;
    draw_buffer.bytes_per_pixel = bytes_per_pixel;
    draw_buffer.pitch = draw_buffer.width * draw_buffer.bytes_per_pixel;

    return draw_buffer;
}

internal void render_begin(void) {
    U32 width = wl_get_window_width();
    U32 height = wl_get_window_height();
    XPutImage(
        wl_linux_state.display, wl_linux_state.window,
        DefaultGC(wl_linux_state.display, 0), &render_x11_state.image,
        0, 0, 0, 0, width, height
    );
}

internal void render_end(void) { }
