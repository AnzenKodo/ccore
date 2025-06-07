#ifndef BASE_MATH_H
#define BASE_MATH_H

// Vector Types
//====================================================================

// 2-Vectors ==================================================================

typedef union Vec2F32 Vec2F32;
union Vec2F32
{
    struct
    {
        F32 x;
        F32 y;
    };
    F32 v[2];
};

typedef union Vec2I64 Vec2I64;
union Vec2I64
{
    struct
    {
        I64 x;
        I64 y;
    };
    I64 v[2];
};

typedef union Vec2I32 Vec2I32;
union Vec2I32
{
    struct
    {
        I32 x;
        I32 y;
    };
    I32 v[2];
};

typedef union Vec2I16 Vec2I16;
union Vec2I16
{
    struct
    {
        I16 x;
        I16 y;
    };
    I16 v[2];
};

// 3-Vectors ==================================================================

typedef union Vec3F32 Vec3F32;
union Vec3F32
{
    struct
    {
        F32 x;
        F32 y;
        F32 z;
    };
    struct
    {
        Vec2F32 xy;
        F32 _z0;
    };
    struct
    {
        F32 _x0;
        Vec2F32 yz;
    };
    F32 v[3];
};

typedef union Vec3I32 Vec3I32;
union Vec3I32
{
    struct
    {
        I32 x;
        I32 y;
        I32 z;
    };
    struct
    {
        Vec2I32 xy;
        I32 _z0;
    };
    struct
    {
        I32 _x0;
        Vec2I32 yz;
    };
    I32 v[3];
};

// 4-vectors ==================================================================

typedef union Vec4F32 Vec4F32;
union Vec4F32
{
    struct
    {
        F32 x;
        F32 y;
        F32 z;
        F32 w;
    };
    struct
    {
        Vec2F32 xy;
        Vec2F32 zw;
    };
    struct
    {
        Vec3F32 xyz;
        F32 _z0;
    };
    struct
    {
        F32 _x0;
        Vec3F32 yzw;
    };
    F32 v[4];
};

typedef union Vec4I32 Vec4I32;
union Vec4I32
{
    struct
    {
        I32 x;
        I32 y;
        I32 z;
        I32 w;
    };
    struct
    {
        Vec2I32 xy;
        Vec2I32 zw;
    };
    struct
    {
        Vec3I32 xyz;
        I32 _z0;
    };
    struct
    {
        I32 _x0;
        Vec3I32 yzw;
    };
    I32 v[4];
};

// Units
//=============================================================================

// Numerical Units
#define Thousand(n)   ((n)*1000)
#define Million(n)    ((n)*1000000)
#define Billion(n)    ((n)*1000000000)

// Unit of Information
#define KB(n)  (((U64)(n)) << 10)
#define MB(n)  (((U64)(n)) << 20)
#define GB(n)  (((U64)(n)) << 30)
#define TB(n)  (((U64)(n)) << 40)

// Constants
//=============================================================================

#define MATH_RANDOM_MAX   max_i32
#define MATH_PI           3.14159265358979323846264338327950288f

// Vector Ops
//=============================================================================

// 2-Vectors ==================================================================

internal Vec2F32 vec2f32(F32 x, F32 y);
internal Vec2I64 vec2i64(I64 x, I64 y);
internal Vec2I32 vec2i32(I32 x, I32 y);
internal Vec2I16 vec2i16(I16 x, I16 y);

// 3-Vectors ==================================================================

internal Vec3F32 vec3f32(F32 x, F32 y, F32 z);
internal Vec3I32 vec3i32(I32 x, I32 y, I32 z);

// 4-vectors ==================================================================

internal Vec4F32 vec4f32(F32 x, F32 y, F32 z, F32 w);
internal Vec4I32 vec4i32(I32 x, I32 y, I32 z, I32 w);

// Random Number
//=============================================================================

internal U32 math_random_u32(U32 seed);

#endif // BASE_MATH_H
