void log_vprint_str8(LogLevel level, Str8 str, va_list vlist) {
    U8 std_level = OS_STDIN;
    Bool print_msg_info = true;
    char *msg_info = "";

    if (level >= LOG_LEVEL) {
        switch (level) {
            case LogLevel_Debug: {
                if (print_msg_info) { msg_info = "[Debug] "; };
                std_level = OS_STDIN;
                break;
            }
            case LogLevel_Info: {
                if (print_msg_info) { msg_info = "[Info] "; };
                std_level = OS_STDIN;
                break;
            }
            case LogLevel_Warn: {
                if (print_msg_info) { msg_info = "[Warning] "; };
                std_level = OS_STDIN;
                break;
            }
            case LogLevel_Err: {
                if (print_msg_info) { msg_info = "[Error] "; };
                std_level = OS_STDIN;
                break;
            }
        }
    }

    fmt_vfprintf_str8(std_level, str, vlist);
}

void log_printf(LogLevel level, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
        log_vprint_str8(level, str8_lit(fmt), args);
    va_end(args);
}
