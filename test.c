#include "ccore/base/base_include.h"
#include "ccore/os/os_include.h"
#include "ccore/core_fmt.h"

#include "ccore/base/base_include.c"
#include "ccore/os/os_include.c"

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
    fmt_printf_str8(            str8_lit("printf_str8  69: %d\n"), 69);
    fmt_printf(                          "printf       69: %d\n",  69);

    // fn void fmt_eprintv_str8(Str8 fmt, va_list vlist)
    fmt_eprintf_str8(           str8_lit("eprintf_str8 69: %d\n"), 69);
    fmt_eprintf(                         "eprintf      69: %d\n",  69);

    temp_end(temp);
}

void test_check(Bool value, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (value) {
        fmt_printv_str8(str8_lit(fmt), args);
        fmt_printf("\n");
    } else {
        fmt_eprintf("Error: expeded ");
        fmt_eprintv_str8(str8_lit(fmt), args);
        fmt_eprintf("\n");
    }

    va_end(args);
}

void test_math(void)
{
    test_check(69 == 69, "69 == 69 got %d", 69);
    test_check(69 == 68, "69 == 68 got %s", "Error");
    test_check(sqrt_f32(36) == 6, "sqrt(36) == 6 got %f", sqrt_f32(36));
}

int main(void) {
    TCTX tctx;
    tctx_init_and_equip(&tctx);

    test_fmt();
    test_math();

    tctx_release();
    return 0;
}
