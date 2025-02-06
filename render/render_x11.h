#ifndef RENDER_X11_H
#define RENDER_X11_H

typedef struct Render_X11_State Render_X11_State;
struct Render_X11_State
{
  Arena *arena;
  XImage *image;
};

global Render_X11_State *render_x11_state = 0;

fn Gfx_Canvas render_init(void)
{
    Display *display = os_wl_linux_state->display;
    U16 screen = os_wl_linux_state->screen;
    Arena *arena = arena_alloc();

    I16 width = os_get_display_width();
    I16 height = os_get_display_height();
    I16 bytes_per_pixel = 4;
    void *pixels = arena_push_size(arena, (width * height) * bytes_per_pixel, 1);

    XImage *image = XCreateImage(
        display, DefaultVisual(display, screen),
        24, ZPixmap, 0, cast(char *)pixels,
        width , height, 32, width * 4);

    render_x11_state = arena_push(arena, Render_X11_State, 1);
    render_x11_state->arena = arena;
    render_x11_state->image = image;

    Gfx_Canvas canvas = zero_struct;
    canvas.pixels = pixels;
    canvas.width = width;
    canvas.height = height;
    canvas.bytes_per_pixel = bytes_per_pixel;

    return canvas;
}

fn void render_draw(void)
{
    XImage *image = render_x11_state->image;
    I16 width = os_get_window_width();
    I16 height = os_get_window_height();
    Display *display = os_wl_linux_state->display;
    Window window = os_wl_linux_state->window;
    GC gc = os_wl_linux_state->gc;
    XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);
}

#include <stdlib.h>
fn void render_close(void)
{
    free(render_x11_state->image);
    arena_free(render_x11_state->arena);
}

#endif // RENDER_X11_H
