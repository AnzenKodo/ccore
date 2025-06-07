internal U32 draw_rgba_to_hex(const Draw_Rgba color)
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

internal U32 draw_rgba_to_hex_argb(const Draw_Rgba color)
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

internal void draw_fill(Draw_Buffer draw_buffer, Draw_Rgba color)
{
    U32 color_in_hex = draw_rgba_to_hex_argb(color);

    for (F32 y = 0; y < draw_buffer.height; y++)
    {
        for (F32 x = 0; x < draw_buffer.width; x++)
        {
            U32 *pixel = (U32 *)draw_buffer.memory + cast(U32)(y * draw_buffer.width + x);
            *pixel++ = color_in_hex;
        }
    }
}

internal void draw_rect(Draw_Buffer draw_buffer, Draw_Rect rect, Draw_Rgba color)
{
    I32 rect_x = round_f32_to_i32(rect.x);
    I32 rect_y = round_f32_to_i32(rect.y);
    I32 width = round_f32_to_i32(rect.width);
    I32 height = round_f32_to_i32(rect.height);
    U32 color_in_hex = draw_rgba_to_hex_argb(color);

    if (width > (I32)draw_buffer.width) width = draw_buffer.width;
    if (height > (I32)draw_buffer.height) height = draw_buffer.height;
    if (rect_y < 0) rect_y = 0;
    if (rect_x < 0) rect_x = 0;

    U8 *row = ((U8 *)draw_buffer.memory) + rect_x*draw_buffer.bytes_per_pixel + rect_y*draw_buffer.pitch;

    for (I32 y = rect_y; y < height; ++y)
    {
        U32 *pixel = (U32 *)row;
        for (I32 x = rect_x; x < width; ++x) {
            *pixel++ = color_in_hex;
        }
        row += draw_buffer.pitch;
    }
}
