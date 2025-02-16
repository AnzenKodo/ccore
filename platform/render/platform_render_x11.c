fn void render_set_wl_linux_visual_info(XVisualInfo *visual_info)
{
    Display *display = wl_linux_state->display;
    int nitems;
    XVisualInfo *xvisual_info = XGetVisualInfo(
        wl_linux_state->display, VisualScreenMask, visual_info, &nitems
    );
    *visual_info = *xvisual_info;
    XFree(xvisual_info);
}

fn Draw_Canvas render_init(void)
{
    Display *display = wl_linux_state->display;
    U16 screen = wl_linux_state->screen;
    Arena *arena = arena_alloc();

    I16 width = wl_get_display_width();
    I16 height = wl_get_display_height();
    I16 bytes_per_pixel = 4;
    void *pixels = arena_push_size(arena, (width * height) * bytes_per_pixel, 1);

    XImage *image = XCreateImage(
        display, DefaultVisual(display, screen),
        24, ZPixmap, 0, cast(char *)pixels,
        width , height, 32, width * 4
    );

    // Create a Graphics Context
    GC gc = XCreateGC(
        wl_linux_state->display, wl_linux_state->window, 0, NULL
    );

    render_x11_state = arena_push(arena, Render_X11_State, 1);
    render_x11_state->arena = arena;
    render_x11_state->image = image;
    render_x11_state->gc = gc;

    Draw_Canvas canvas = ZERO_STRUCT;
    canvas.pixels = cast(U32*)pixels;
    canvas.width = width;
    canvas.height = height;
    canvas.bytes_per_pixel = bytes_per_pixel;
    canvas.pitch = width * bytes_per_pixel;

    return canvas;
}

fn void render_close(void)
{
    XFree(render_x11_state->image);
    XFreeGC(wl_linux_state->display, render_x11_state->gc);
    arena_free(render_x11_state->arena);
}

fn void render_begin(void)
{
    I16 width = wl_get_window_width();
    I16 height = wl_get_window_height();
    XPutImage(
        wl_linux_state->display, wl_linux_state->window,
        render_x11_state->gc, render_x11_state->image,
        0, 0, 0, 0, width, height
    );
}

fn void render_end(void)
{
}
