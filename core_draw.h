#ifndef CORE_DRAW_H
#define CORE_DRAW_H

// Types
//====================================================================

typedef struct Rect Rect;
struct Rect {
    F32 x;
    F32 y;
    F32 width;
    F32 height;
};

typedef struct Rgba Rgba;
struct Rgba {
    U8 red;
    U8 green;
    U8 blue;
    U8 alpha;
};

typedef struct Draw_Canvas Draw_Canvas;
struct Draw_Canvas {
    void *pixels;
    U32 width;
    U32 height;
    I32 bytes_per_pixel;
    I32 pitch;
};

typedef struct Draw_Context Draw_Context;
struct Draw_Context {
    Arena *arena;
};

// Globals
//====================================================================

global Draw_Context *draw_context;

//// Colors
////==================================================================

#define LIGHTGRAY  (Rgba){ 200, 200, 200, 255 }   // Light Gray
#define GRAY       (Rgba){ 130, 130, 130, 255 }   // Gray
#define DARKGRAY   (Rgba){ 80, 80, 80, 255 }      // Dark Gray
#define YELLOW     (Rgba){ 253, 249, 0, 255 }     // Yellow
#define GOLD       (Rgba){ 255, 203, 0, 255 }     // Gold
#define ORANGE     (Rgba){ 255, 161, 0, 255 }     // Orange
#define PINK       (Rgba){ 255, 109, 194, 255 }   // Pink
#define RED        (Rgba){ 230, 41, 55, 255 }     // Red
#define MAROON     (Rgba){ 190, 33, 55, 255 }     // Maroon
#define GREEN      (Rgba){ 0, 228, 48, 255 }      // Green
#define LIME       (Rgba){ 0, 158, 47, 255 }      // Lime
#define DARKGREEN  (Rgba){ 0, 117, 44, 255 }      // Dark Green
#define SKYBLUE    (Rgba){ 102, 191, 255, 255 }   // Sky Blue
#define BLUE       (Rgba){ 0, 121, 241, 255 }     // Blue
#define DARKBLUE   (Rgba){ 0, 82, 172, 255 }      // Dark Blue
#define PURPLE     (Rgba){ 200, 122, 255, 255 }   // Purple
#define VIOLET     (Rgba){ 135, 60, 190, 255 }    // Violet
#define DARKPURPLE (Rgba){ 112, 31, 126, 255 }    // Dark Purple
#define BEIGE      (Rgba){ 211, 176, 131, 255 }   // Beige
#define BROWN      (Rgba){ 127, 106, 79, 255 }    // Brown
#define DARKBROWN  (Rgba){ 76, 63, 47, 255 }      // Dark Brown
#define MAGENTA    (Rgba){ 255, 0, 255, 255 }     // Magenta
#define WHITE      (Rgba){ 255, 255, 255, 255 }   // White
#define BLACK      (Rgba){ 0, 0, 0, 255 }         // Black
#define TRANSPARENT(Rgba){ 0, 0, 0, 0 }           // Blank

// Functions
//====================================================================

//// Helper functions
////==================================================================

fn U32 draw_rgba_to_hex(const Rgba color)
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

fn U32 draw_rgba_to_hex_argb(const Rgba color)
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

fn Rect draw_center_rect(Draw_Canvas canvas, F32 height, F32 width)
{
    F32 x = canvas.height/2 - height/2;
    F32 y = canvas.width/2 - width/2;
    Rect rect = { x, y, height, width };
    return rect;
}

//// Canvas context
////==================================================================

fn Draw_Canvas *draw_create_canvas(
    U16 width, U16 height, I16 bytes_per_pixel
) {
    Arena *arena = arena_alloc();
    draw_context = arena_push(arena, Draw_Context, 1);
    void *pixels = arena_push(arena, U32, (width*height) * bytes_per_pixel);
    draw_context->arena = arena;

    Draw_Canvas *canvas = 0;
    canvas = arena_push(arena, Draw_Canvas, 1);
    canvas->pixels = pixels;
    canvas->width = width;
    canvas->height = height;
    canvas->bytes_per_pixel = bytes_per_pixel;
    canvas->pitch = width * bytes_per_pixel;
    return canvas;
}

fn void draw_free_canvas()
{
    arena_free(draw_context->arena);
}

//// Shapes
////==================================================================

fn void draw_fill_canvas(Draw_Canvas canvas, Rgba color)
{
    for (F32 y = 0; y < canvas.height; y++)
    {
        for (F32 x = 0; x < canvas.width; x++)
        {
            U32 *pixel = (U32 *)canvas.pixels + cast(U32)(y * canvas.width + x);
            *pixel = draw_rgba_to_hex_argb(color);
        }
    }
}

fn void draw_rect(Draw_Canvas canvas, Rect rect, Rgba color)
{
    I32 rect_x = round_f32_to_i32(rect.x);
    I32 rect_y = round_f32_to_i32(rect.y);
    I32 width = round_f32_to_i32(rect.width);
    I32 height = round_f32_to_i32(rect.height);

    if (width > (I32)canvas.width) width = canvas.width;
    if (height > (I32)canvas.height) height = canvas.height;
    if (rect_y < 0) rect_y = 0;
    if (rect_x < 0) rect_x = 0;

    U8 *row = ((U8 *)canvas.pixels) + rect_x*canvas.bytes_per_pixel + rect_y*canvas.pitch;
    for (I32 y = rect_y; y < height; ++y)
    {
        U32 *pixel = (U32 *)row;
        for (I32 x = rect_x; x < width; ++x) {
            *pixel++ = draw_rgba_to_hex_argb(color);
        }
        row += canvas.pitch;
    }

    // for (I32 y = 0; y < height; y++)
    // {
    //     for (I32 x = 0; x < width; x++)
    //     {
    //         I32 dy = y + rect_y;
    //         I32 dx = x + rect_x;
    //         U32 *pixel = (U32 *)canvas.pixels + dy * canvas.width + dx;
    //         *pixel = draw_rgba_to_hex_argb(color);
    //     }
    // }
}

fn void draw_pixel(Draw_Canvas canvas, I32 x, I32 y, Rgba color) {
    I32 width = canvas.width;
    I32 height = canvas.height;

    if (x >= 0 && x < width && y >= 0 && y < height) {
        U32 *pixel = (U32 *)canvas.pixels + (U32)(y * width + x);
        *pixel = draw_rgba_to_hex_argb(color);
    }
}

fn void draw_circle2(Draw_Canvas canvas, I32 xc, I32 yc, U32 radius, Rgba color) {
    I32 r2 = radius * radius;
    for (I32 x = -radius; x <= cast(I32)radius; x++) {
        I32 y = cast(I32)(sqrt_f32(r2 - x*x) + 0.5);
        draw_pixel(canvas, xc + x, yc + y, color);
        draw_pixel(canvas, xc + x, yc - y, color);
    }
}

void draw_circle(Draw_Canvas canvas, I32 cx, I32 cy, U32 radius, Rgba color) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        // Plot points in all eight octants
        draw_pixel(canvas, cx + x, cy + y, color);
        draw_pixel(canvas, cx + y, cy + x, color);
        draw_pixel(canvas, cx - y, cy + x, color);
        draw_pixel(canvas, cx - x, cy + y, color);
        draw_pixel(canvas, cx - x, cy - y, color);
        draw_pixel(canvas, cx - y, cy - x, color);
        draw_pixel(canvas, cx + y, cy - x, color);
        draw_pixel(canvas, cx + x, cy - y, color);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0) {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}

// TODO:
//  - Lines
//  - Triangle
//  - Poly
//  - OpenGL

#endif // CORE_DRAW_H
