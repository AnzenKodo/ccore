#ifndef CORE_UI_H
#define CORE_UI_H

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

fn U32 rgba_to_hex(const RGBA color)
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

fn U32 rgba_to_hex_argb(const RGBA color)
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

fn void ui_gradiant_grid(Render_Backbuffer buff, I16 blue_offset, I16 green_offset)
{
    I16 bytes_per_pixel = buff.bytes_per_pixel;
    I16 height = buff.height;
    I16 width = buff.width;

    I32 pitch = width * bytes_per_pixel;
    U8 *row = cast(U8 *)buff.memory;
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

fn void ui_square(Render_Backbuffer buff, Rectangle rect, RGBA color, F32 rotation, F32 radius)
{
    // Calculate center of the rectangle
    F32 centerX = rect.x + rect.width / 2.0;
    F32 centerY = rect.y + rect.height / 2.0;

    // Calculate corner positions before rotation
    F32 halfWidth = rect.width / 2.0;
    F32 halfHeight = rect.height / 2.0;

    // Store rotated corner positions
    XPoint corners[4];

    // Define original corners (before rotation)
    XPoint originalCorners[8] = {
        { -halfWidth + radius, -halfHeight },
        { halfWidth - radius, -halfHeight },
        { halfWidth, -halfHeight + radius },
        { halfWidth, halfHeight - radius },
        { halfWidth - radius, halfHeight },
        { -halfWidth + radius, halfHeight },
        { -halfWidth, halfHeight - radius },
        { -halfWidth, -halfHeight }
    };

    // Apply rotation to each corner
    for (int i = 0; i < 8; i++) {
        F32 x = originalCorners[i].x;
        F32 y = originalCorners[i].y;

        // Rotate around center
        corners[i].x = (F32)(centerX + (x * cos_f32(rotation) - y * sin_f32(rotation)));
        corners[i].y = (F32)(centerY + (x * sin_f32(rotation) + y * cos_f32(rotation)));
    }

    // Clip and draw pixels
    U32 *row = cast(U32 *)buff.memory;

    for (I32 y = 0; y < rect.height; y++) {
        for (I32 x = 0; x < rect.width; x++) {
            // Check if pixel is inside the rounded square using point-in-polygon or distance checks
            // if (point_in_rounded_square(x, y, corners, radius)) {
                U32 *pixel = (U32 *)(row + y * buff.width + x);
                *pixel = rgba_to_hex_argb(color);
            // }
        }
    }
}

#endif // CORE_UI_H
