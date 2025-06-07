// Vector Ops
//=============================================================================

// 2-Vectors ==================================================================

internal Vec2F32 vec2f32(F32 x, F32 y)
{
    Vec2F32 v = {x, y};
    return v;
}

internal Vec2I64 vec2i64(I64 x, I64 y)
{
    Vec2I64 v = {x, y};
    return v;
}

internal Vec2I32 vec2i32(I32 x, I32 y)
{
    Vec2I32 v = {x, y};
    return v;
}

internal Vec2I16 vec2i16(I16 x, I16 y)
{
    Vec2I16 v = {x, y};
    return v;
}

// 3-Vectors ==================================================================

internal Vec3F32 vec3f32(F32 x, F32 y, F32 z)
{
    Vec3F32 v = {x, y, z};
    return v;
}

internal Vec3I32 vec3i32(I32 x, I32 y, I32 z)
{
    Vec3I32 v = {x, y, z};
    return v;
}


// 4-vectors ==================================================================

internal Vec4F32 vec4f32(F32 x, F32 y, F32 z, F32 w)
{
    Vec4F32 v = {x, y, z, w};
    return v;
}
internal Vec4I32 vec4i32(I32 x, I32 y, I32 z, I32 w)
{
    Vec4I32 v = {x, y, z, w};
    return v;
}

// Random Number
//=============================================================================

internal U32 math_random_u32(U32 seed) {
    seed = (seed << 13) ^ seed;
    return ((seed * (seed * seed * 15731 + 789221) + 1376312589) & 0x7fffffff);
}
