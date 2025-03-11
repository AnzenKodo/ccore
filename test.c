#define ENABLE_WINDOW_LAYER

#include "ccore/base/base_include.h"
#include "ccore/core_draw.h"
#include "ccore/platform/platform_include.h"

#include "ccore/base/base_include.c"
#include "ccore/platform/platform_include.c"

void test_check(Bool value, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (value) {
        fmt_printv_str8(str8_lit(fmt), args);
    } else {
        fmt_eprintf("Error: expeded ");
        fmt_eprintv_str8(str8_lit(fmt), args);
    }

    va_end(args);
}

void test_fmt(void)
{
    Temp temp = temp_begin(0, 0);

    // fn Str8 fmt_sprintv_str8(Arena *arena, Str8 fmt, va_list vlist)
    Str8 str = fmt_sprintf_str8(temp.arena, str8_lit("fmt_sprintf_str8: %d\n"), 69);
    AssertAlways(str8_match(str, str8_lit("fmt_sprintf_str8: 69\n"), 0));

    // fn void fmt_vfprintf_str8(Os_File fd, Str8 fmt, va_list vlist)
    fmt_fprintf_str8(OS_STDERR, str8_lit("fprintf_str8 69: %d\n"), 69);
    fmt_fprintf(OS_STDERR,               "fprintf      69: %d\n",  69);

    // fn void fmt_printv_str8(Str8 fmt, va_list vlist)
    fmt_printf_str8(str8_lit("printf_str8  69: %d\n"), 69);
    fmt_printf(              "printf       69: %d\n",  69);

    // fn void fmt_eprintv_str8(Str8 fmt, va_list vlist)
    fmt_eprintf_str8(str8_lit("eprintf_str8 69: %d\n"), 69);
    fmt_eprintf(              "eprintf      69: %d\n",  69);

    temp_end(temp);
}

void test_math(void)
{
    test_check(69 == 69, "69 == 69 got %d\n", 69);
    test_check(69 == 68, "69 == 68 got %s\n", "Error");
    test_check(sqrt_f32(36) == 6, "sqrt(36) == 6 got %f\n", sqrt_f32(36));
}

void test_wl(void)
{
    wl_window_open(str8_lit("Scuttle"), 960, 540);
    wl_set_window_icon();

    fmt_printf("Display Width: %d\n", wl_get_display_width());
    fmt_printf("Display Height: %d\n", wl_get_display_height());
    
    Draw_Buffer *buffer = render_init();
    U32 i = 0;
    while (!wl_should_window_close()) {
        wl_update_events();
        if (wl_is_key_pressed(Wl_Key_Esc)) {
            wl_set_window_close();
        }

        render_begin();
            draw_fill(buffer, RED);
        render_end();

        if (i == 2) {
            test_check(
                wl_get_window_width() == 960, "Window Width == 950 got %d\n",
                wl_get_window_width()
            );
            test_check(
                wl_get_window_height() == 540, "Window Height == 540 got %d\n",
                wl_get_window_height()
            );
        }
            i++;
    }

    render_close();
    wl_window_close();
}

int main(void) {
    TCTX tctx;
    tctx_init_and_equip(&tctx);

    test_fmt();
    test_math();
    test_wl();

    tctx_release();
    return 0;
}
