#ifndef STD_PRINT_H
#define STD_PRINT_H

void print_err(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void print_ln(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    put("\n");
}

#endif // STD_PRINT_H
