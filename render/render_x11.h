#ifndef RENDER_X11_H
#define RENDER_X11_H

typedef struct Render_X11_State Render_X11_State;
struct Render_X11_State
{
  Arena *arena;
  XImage *image;
};

typedef struct Render_Backbuffer Render_Backbuffer;
struct Render_Backbuffer {
    void *memory;
    I16 width;
    I16 height;
    I16 bytes_per_pixel;
};

global Render_X11_State *render_x11_state = 0;

fn Render_Backbuffer render_init(void)
{
    Display *display = gfx_linux_state->display;
    U16 screen = gfx_linux_state->screen;
    Arena *arena = arena_alloc();

    I16 width = gfx_get_display_width();
    I16 height = gfx_get_display_height();
    I16 bytes_per_pixel = 4;
    void *memory = arena_push_(arena, (width * height) * bytes_per_pixel, 1);

    XImage *image = XCreateImage(
        display, DefaultVisual(display, screen),
        24, ZPixmap, 0, memory,
        width , height, 32, width * 4);

    render_x11_state = arena_push(arena, Render_X11_State, 1);
    render_x11_state->arena = arena;
    render_x11_state->image = image;

    Render_Backbuffer buffer = {0};
    buffer.memory = memory;
    buffer.width = width;
    buffer.height = height;
    buffer.bytes_per_pixel = bytes_per_pixel;

    return buffer;
}

fn void render_draw(void)
{
    XImage *image = render_x11_state->image;
    I16 width = gfx_get_win_width();
    I16 height = gfx_get_win_height();
    Display *display = gfx_linux_state->display;
    Window window = gfx_linux_state->window;
    GC gc = gfx_linux_state->gc;
    XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);
}

fn void render_close(void)
{
    arena_free(render_x11_state->arena);
}

#endif // RENDER_X11_H
