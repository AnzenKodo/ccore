#ifndef STD_STR_H
#define STD_STR_H

// String Types
//=============

typedef struct Str8 {
	U8 *str;
	U64 len;
} Str8;

typedef struct Str16 {
	U16 *str;
	U64 len;
} Str16;

typedef struct str32 {
	U32 *str;
	U64 len;
} Str32;

// Functions Pre-definition
//=========================

#define str8_lit(S)  str8((U8*)(S), sizeof(S) - 1)
#define str8_lit_comp(S) {(U8*)(S), sizeof(S) - 1,}
#define str8_varg(S) (int)((S).len), ((S).str)

fn U64 cstr8_len(U8 *c);
fn U64 cstr16_len(U16 *c);
fn U64 cstr32_len(U32 *c);

fn Str8 str8(U8 *str, U64 len);
fn Str8 str8_zero(void);
fn Str16 str16(U16 *str, U64 size);
fn Str16 str16_zero(void);
fn Str32 str32(U32 *str, U64 size);
fn Str32 str32_zero(void);
fn Str8 str8_cstr(char *c);
fn Str16 str16_cstr(U16 *c);
fn Str32 str32_cstr(U32 *c);

// C-String Measurement
//=====================

fn U64 cstr8_len(U8 *c){
  U8 *p = c;
  for (;*p != 0; p += 1);
  return(p - c);
}

fn U64 cstr16_len(U16 *c){
  U16 *p = c;
  for (;*p != 0; p += 1);
  return(p - c);
}

fn U64 cstr32_len(U32 *c){
  U32 *p = c;
  for (;*p != 0; p += 1);
  return(p - c);
}

// String Constructors
//====================

fn Str8 str8(U8 *str, U64 len) {
  Str8 result = {str, len};
  return(result);
}

fn Str8 str8_zero(void) {
  Str8 result = {0};
  return(result);
}

fn Str16 str16(U16 *str, U64 size) {
  Str16 result = {str, size};
  return(result);
}

fn Str16 str16_zero(void) {
  Str16 result = {0};
  return(result);
}

fn Str32 str32(U32 *str, U64 size) {
  Str32 result = {str, size};
  return(result);
}

fn Str32 str32_zero(void) {
  Str32 result = {0};
  return(result);
}

fn Str8 str8_cstr(char *c) {
  Str8 result = {(U8*)c, cstr8_len((U8*)c)};
  return(result);
}

fn Str16 str16_cstr(U16 *c) {
  Str16 result = {(U16*)c, cstr16_len((U16*)c)};
  return(result);
}

fn Str32 str32_cstr(U32 *c) {
  Str32 result = {(U32*)c, cstr32_len((U32*)c)};
  return(result);
}

#endif // STD_STR_H
