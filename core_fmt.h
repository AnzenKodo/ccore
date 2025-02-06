#ifndef CORE_FMT_T
#define CORE_FMT_T

#define STB_SPRINTF_IMPLEMENTATION
#include "ccore/external/stb_sprintf.h"

#define fmt_vsnprintf stbsp_vsnprintf

fn Str8 fmt_sprintv(Arena *arena, const char *fmt, va_list args){
    va_list args2;
    va_copy(args2, args);
        U32 needed_bytes = fmt_vsnprintf(0, 0, fmt, args) + 1;
        Str8 result = zero_struct;
        result.str = arena_push_no_zero(arena, U8, needed_bytes);
        result.size = fmt_vsnprintf((char*)result.str, needed_bytes, fmt, args2);
        result.str[result.size] = 0;
    va_end(args2);
    return(result);
}

fn Str8 fmt_sprintf(Arena *arena, const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
        Str8 result = fmt_sprintv(arena, fmt, args);
    va_end(args);
    return(result);
}

fn void fmt_fprintf(Os_File fd, const char *fmt, ...) {
    Temp temp = temp_begin(0, 0);

    va_list args;
    va_start(args, fmt);
        Str8 result = fmt_sprintv(temp.arena, fmt, args);
    va_end(args);
    os_write_str8(fd, result);

    temp_end(temp);
}

#endif // CORE_FMT_T
