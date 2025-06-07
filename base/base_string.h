#ifndef BASE_STRING_H
#define BASE_STRING_H

// String Types
//====================================================================

typedef struct Str8 {
    U8 *str;
    U64 size;
} Str8;

// String Constructors
//====================================================================

#define str8(S)  str8_init((U8*)(S), sizeof(S) - 1)
internal Str8 str8_init(U8 *str, U64 size);
internal Str8 str8_from_cstr(char *c);

// String Matching
//====================================================================

internal bool str8_match(Str8 a, Str8 b);
internal bool str8_ends_with(Str8 string, Str8 end);

// String Slicing
//====================================================================

internal Str8 str8_postfix(Str8 str, U64 size);

// C-String Measurement
//====================================================================

internal U64 cstr8_length(U8 *c);

#endif // BASE_STRING_H
