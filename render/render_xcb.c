internal Draw_Buffer
render_init(Alloc alloc)
{
    I16 width = wl_get_display_width();
    I16 height = wl_get_display_height();
    I32 bytes_per_pixel = 4;
    U64 memory_size = (width * height) * bytes_per_pixel;
    U8 *memory = alloc_make(alloc, U8, memory_size);

    // Create pixmap format ===================================================
    xcb_pixmap_t pixmap = xcb_generate_id(wl_linux_state.conn);
    xcb_format_t *pixmap_format = xcb_setup_pixmap_formats(
        xcb_get_setup(wl_linux_state.conn)
    );
    I32 pixmap_format_length = xcb_setup_pixmap_formats_length(
        xcb_get_setup(wl_linux_state.conn)
    );
    for (int i = 0; i < pixmap_format_length; i++) {
        if (
            pixmap_format[i].depth==24 && pixmap_format[i].bits_per_pixel==32
        ) {
            pixmap_format += i;
        }
    }

    // Create pixmap ==========================================================
    xcb_create_pixmap(
        wl_linux_state.conn, wl_linux_state.screen->root_depth,
        pixmap, wl_linux_state.window,
        width, height
    );

    // Create graphics context ================================================
    xcb_gcontext_t gc = xcb_generate_id(wl_linux_state.conn);
    uint32_t gc_mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
    uint32_t gc_values[] = {
        wl_linux_state.screen->white_pixel, wl_linux_state.screen->black_pixel
    };
    xcb_create_gc(
        wl_linux_state.conn, gc, pixmap, gc_mask, gc_values
    );

    // Create image ================================================
    xcb_image_t *image = xcb_image_create(
        width, height, XCB_IMAGE_FORMAT_Z_PIXMAP,
        pixmap_format->scanline_pad, pixmap_format->depth,
        pixmap_format->bits_per_pixel, 0,
        xcb_get_setup(wl_linux_state.conn)->image_byte_order,
        XCB_IMAGE_ORDER_LSB_FIRST,
        memory, memory_size, memory
    );
    xcb_flush(wl_linux_state.conn);

    // Initialize States ======================================================
    render_xcb_state.pixmap = pixmap;
    render_xcb_state.gc = gc;
    render_xcb_state.image = image;

    Draw_Buffer draw_buffer = ZERO_STRUCT;
    draw_buffer.memory = memory;
    draw_buffer.width = width;
    draw_buffer.height = height;
    draw_buffer.bytes_per_pixel = bytes_per_pixel;
    draw_buffer.pitch = draw_buffer.width * draw_buffer.bytes_per_pixel;

    return draw_buffer;
}

internal void
render_deinit(void)
{
    xcb_free_pixmap(wl_linux_state.conn, render_xcb_state.pixmap);
    xcb_free_gc(wl_linux_state.conn, render_xcb_state.gc);
}

internal void
render_begin()
{
}

void render_end()
{
    U32 width = wl_get_window_width();
    U32 height = wl_get_window_height();

    xcb_image_put(
        wl_linux_state.conn, render_xcb_state.pixmap,
        render_xcb_state.gc, render_xcb_state.image, 0, 0, 0
    );
    xcb_copy_area(
        wl_linux_state.conn, render_xcb_state.pixmap, wl_linux_state.window,
        render_xcb_state.gc, 0, 0, 0, 0, width, height
    );
}
