#ifndef DRAW_CORE_H
#define DRAW_CORE_H

typedef struct Draw_Buffer Draw_Buffer;
struct Draw_Buffer {
    void *memory;
    U32 width;
    U32 height;
    I32 bytes_per_pixel;
    I32 pitch;
};

typedef struct Draw_Rgba Draw_Rgba;
struct Draw_Rgba {
    U8 red;
    U8 green;
    U8 blue;
    U8 alpha;
};

typedef struct Draw_Rect Draw_Rect;
struct Draw_Rect {
    F32 x;
    F32 y;
    F32 width;
    F32 height;
};

//// Colors
////==================================================================

#define DRAW_LIGHTGRAY  (Draw_Rgba){ 200, 200, 200, 255 }   // Light Gray
#define DRAW_GRAY       (Draw_Rgba){ 130, 130, 130, 255 }   // Gray
#define DRAW_DARKGRAY   (Draw_Rgba){ 80, 80, 80, 255 }      // Dark Gray
#define DRAW_YELLOW     (Draw_Rgba){ 253, 249, 0, 255 }     // Yellow
#define DRAW_GOLD       (Draw_Rgba){ 255, 203, 0, 255 }     // Gold
#define DRAW_ORANGE     (Draw_Rgba){ 255, 161, 0, 255 }     // Orange
#define DRAW_PINK       (Draw_Rgba){ 255, 109, 194, 255 }   // Pink
#define DRAW_RED        (Draw_Rgba){ 230, 41, 55, 255 }     // Red
#define DRAW_MAROON     (Draw_Rgba){ 190, 33, 55, 255 }     // Maroon
#define DRAW_GREEN      (Draw_Rgba){ 0, 228, 48, 255 }      // Green
#define DRAW_LIME       (Draw_Rgba){ 0, 158, 47, 255 }      // Lime
#define DRAW_DARKGREEN  (Draw_Rgba){ 0, 117, 44, 255 }      // Dark Green
#define DRAW_SKYBLUE    (Draw_Rgba){ 102, 191, 255, 255 }   // Sky Blue
#define DRAW_BLUE       (Draw_Rgba){ 0, 121, 241, 255 }     // Blue
#define DRAW_DARKBLUE   (Draw_Rgba){ 0, 82, 172, 255 }      // Dark Blue
#define DRAW_PURPLE     (Draw_Rgba){ 200, 122, 255, 255 }   // Purple
#define DRAW_VIOLET     (Draw_Rgba){ 135, 60, 190, 255 }    // Violet
#define DRAW_DARKPURPLE (Draw_Rgba){ 112, 31, 126, 255 }    // Dark Purple
#define DRAW_BEIGE      (Draw_Rgba){ 211, 176, 131, 255 }   // Beige
#define DRAW_BROWN      (Draw_Rgba){ 127, 106, 79, 255 }    // Brown
#define DRAW_DARKBROWN  (Draw_Rgba){ 76, 63, 47, 255 }      // Dark Brown
#define DRAW_MAGENTA    (Draw_Rgba){ 255, 0, 255, 255 }     // Magenta
#define DRAW_WHITE      (Draw_Rgba){ 255, 255, 255, 255 }   // White
#define DRAW_BLACK      (Draw_Rgba){ 0, 0, 0, 255 }         // Black
#define DRAW_TRANSPARENT(Draw_Rgba){ 0, 0, 0, 0 }           // Blank


#endif // DRAW_CORE_H
