#ifndef BASE_CORE_H
#define BASE_CORE_H

// External Includes
//=============================================================================

#include <stdint.h>
// #include <stddef.h>

// Base Types
//=============================================================================

#if LANG_C
    #define bool _Bool
    #define true  1
    #define false 0
#endif

typedef uint8_t   U8;
typedef int8_t    I8;
typedef uint16_t  U16;
typedef int16_t   I16;
typedef uint32_t  U32;
typedef int32_t   I32;
typedef uint64_t  U64;
typedef int64_t   I64;

typedef float    F32;
typedef double   F64;

// Code Keywords
//=============================================================================

#define internal        static
#define global          static
#define local_persist   static

// Constants
//=============================================================================

global U64 max_u64 = 0xffffffffffffffffull;
global U32 max_u32 = 0xffffffff;
global U16 max_u16 = 0xffff;
global U8  max_u8  = 0xff;

global I64 max_i64 = (I64)0x7fffffffffffffffull;
global I32 max_i32 = (I32)0x7fffffff;
global I16 max_i16 = (I16)0x7fff;
global I8  max_i8  =  (I8)0x7f;

global I64 min_i64 = (I64)0xffffffffffffffffull;
global I32 min_i32 = (I32)0xffffffff;
global I16 min_i16 = (I16)0xffff;
global I8  min_i8  =  (I8)0xff;

// Misc. Macros
//=============================================================================

#define cast(Type)    (Type)
#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))

#define Min(A,B)     (((A)<(B))?(A):(B))
#define Max(A,B)     (((A)>(B))?(A):(B))
#define Clamp(A,X,B) (((X)<(A))?(A):((X)>(B))?(B):(X))

#define IsPow2(x)       ((x != 0) && ((x & (x - 1)) == 0))
#define AlignPow2(x,b)  (((x) + (b) - 1)&(~((b) - 1)))

#if ARCH_64BIT
#   define IntFromPtr(ptr) ((U64)(ptr))
#elif ARCH_32BIT
#   define IntFromPtr(ptr) ((U32)(ptr))
#else
#   error Missing pointer-to-integer cast for this architecture.
#endif
#define PtrFromInt(i) (void*)((U8*)0 + (i))

#if LANG_CPP
# define ZERO_STRUCT {}
#else
# define ZERO_STRUCT {0}
#endif

// Alignment
//=============================================================================

#if COMPILER_MSVC
# define AlignOf(T) __alignof(T)
#elif COMPILER_CLANG
# define AlignOf(T) __alignof(T)
#elif COMPILER_GCC
# define AlignOf(T) __alignof__(T)
#else
# error AlignOf not defined for this compiler.
#endif

// Asserts
//=============================================================================

#if COMPILER_MSVC
#   define Trap() __debugbreak()
#elif COMPILER_CLANG || COMPILER_GCC
#   define Trap() __builtin_trap()
#elif COMPILER_TCC
#   define Trap() asm volatile("ud2");
#else
#   error Unknown trap intrinsic for this compiler.
#endif

#define AssertAlways(x) do{if(!(x)) {Trap();}}while(0)
#if BUILD_DEBUG
#   define Assert(x) AssertAlways(x)
#else
#   define Assert(x) (void)(x)
#endif
#define NotImplemented     Assert(!"Not Implemented!")

// Functions
//=============================================================================

internal I32 round_f32_to_i32(F32 a) { I32 result = (I32)(a + 0.5f); return result; }
internal U32 round_f32_to_u32(F32 a) { U32 result = (U32)(a + 0.5f); return result; }

#endif // BASE_CORE_H
