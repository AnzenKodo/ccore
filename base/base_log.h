#ifndef CORE_LOG_H
#define CORE_LOG_H

typedef enum LogLevel LogLevel;
enum LogLevel
{
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warn,
    LogLevel_Err,
    LogLevel_Count
};

void log_vprint_str8(LogLevel level, Str8 str, va_list vlist);
void log_printf(LogLevel level, char *fmt, ...);

#define log_debug_printf(fmt, ...) log_printf(LogLevel_Debug, fmt, ##__VA_ARGS__)
#define log_info_printf(fmt, ...)  log_printf(LogLevel_Info,  fmt, ##__VA_ARGS__)
#define log_warn_printf(fmt, ...)  log_printf(LogLevel_Warn,  fmt, ##__VA_ARGS__)
#define log_err_printf(fmt, ...)   log_printf(LogLevel_Err,   fmt, ##__VA_ARGS__)

#if defined(BUILD_DEBUG) && !defined(LOG_LEVEL)
    #define LOG_LEVEL LogLevel_Debug
#elif !defined(BUILD_DEBUG) && !defined(LOG_LEVEL)
    #define LOG_LEVEL LogLevel_Info
#endif

#ifndef LOG_LEVEL
    #define LOG_LEVEL LogLevel_Debug
#endif

#endif // CORE_LOG_H
