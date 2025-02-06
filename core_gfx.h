#ifndef CORE_GFX_H
#define CORE_GFX_H

typedef struct Rectangle Rectangle;
struct Rectangle {
    I32 x;
    I32 y;
    I32 width;
    I32 height;
};

typedef struct RGBA RGBA;
struct RGBA {
    U8 red;
    U8 green;
    U8 blue;
    U8 alpha;
};

typedef struct Gfx_Canvas Gfx_Canvas;
struct Gfx_Canvas {
    void *pixels;
    I16 width;
    I16 height;
    I16 bytes_per_pixel;
};

typedef struct Gfx_Context Gfx_Context;
struct Gfx_Context {
    Arena *arena;
};

global Gfx_Context *gfx_context;

fn U32 gfx_rgba_to_hex(const RGBA color)
{
    U32 result = 0;

    result = (U32)(
        (color.red << 24) |
        (color.green << 16) |
        (color.blue << 8) |
        (color.alpha)
    );

    return result;
}

fn U32 gfx_rgba_to_hex_argb(const RGBA color)
{
    U32 result = 0;

    result = (U32)(
        (color.alpha << 24) |
        (color.red << 16) |
        (color.green << 8) |
        (color.blue)
    );

    return result;
}

fn Gfx_Canvas gfx_create_canvas_context(
    I16 width, I16 height, I16 bytes_per_pixel
) {
    Arena *arena = arena_alloc();
    gfx_context = arena_push(arena, Gfx_Context, 1);
    void *pixels = arena_push_size(arena, (width*height) * bytes_per_pixel, 1);
    gfx_context->arena = arena;

    Gfx_Canvas canvas = zero_struct;
    canvas.pixels = pixels;
    canvas.width = width;
    canvas.height = height;
    canvas.bytes_per_pixel = bytes_per_pixel;
    return canvas;
}

fn void gfx_free_canvas_context() {
    arena_free(gfx_context->arena);
}

fn void gfx_create_gradient_grid(
    Gfx_Canvas canvas, I16 blue_offset, I16 green_offset
) {
    I16 bytes_per_pixel = canvas.bytes_per_pixel;
    I16 height = canvas.height;
    I16 width = canvas.width;

    I32 pitch = width * bytes_per_pixel;
    U8 *row = cast(U8 *)canvas.pixels;
    for (int y = 0; y < height; y++) {
        U32 *pixel = cast(U32 *)row;
        for (int x = 0; x < width; x++) {
            U8 blue = (x + blue_offset);
            U8 green = (y + green_offset);
            *pixel++ = ((green << 8) | blue);
        }
        row += pitch;
    }
}

fn void gfx_create_square(Gfx_Canvas canvas, Rectangle rect, RGBA color) {
    U32 *row = cast(U32 *)canvas.pixels;
    for (I32 y = 0; y < rect.height; y++) {
        for (I32 x = 0; x < rect.width; x++) {
            U32 *pixel = (U32 *)(row + y * canvas.width + x);
            *pixel = gfx_rgba_to_hex_argb(color);
        }
    }
}

#endif // CORE_GFX_H
