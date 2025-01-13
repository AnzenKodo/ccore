#ifndef CORE_MATH_H
#define CORE_MATH_H

// Vector Types
//=============

//// 2-Vectors
////==========

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

//// 3-vectors
////==========

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

//// 4-vectors
////==========

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

//// Matrix Types
////=============

typedef struct Mat3x3F32 Mat3x3F32;
struct Mat3x3F32
{
  F32 v[3][3];
};

typedef struct Mat4x4F32 Mat4x4F32;
struct Mat4x4F32
{
  F32 v[4][4];
};

// Constants
//==========

#define MATH_TAU_OVER_2   3.14159265358979323846264338327950288f
#define MATH_TAU_OVER_4   1.570796326794896619231321691639751442f

// Micros
//=======

#define ABS(x) ((x) > 0 ? (x) : -(x))

// Function Define
//================

fn F32 sqrt_f32(F32 number);
fn F64 sqrt_f64(F64 number);

// Function Implimation
//=====================

//// Scalar Ops
////===========

fn F64 mix_1f64(F64 a, F64 b, F64 t) { F64 c = (a + (b-a) * Clamp(0.0, t, 1.0)); return c; }
fn F32 mix_1f32(F32 a, F32 b, F32 t) { F32 c = (a + (b-a) * Clamp(0.f, t, 1.f)); return c; }

//// Vector Ops
////===========

fn Vec2F32 vec_2f32(F32 x, F32 y)                {Vec2F32 v = {x, y}; return v;}
fn Vec2F32 add_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x+b.x, a.y+b.y}; return c;}
fn Vec2F32 sub_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x-b.x, a.y-b.y}; return c;}
fn Vec2F32 mul_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x*b.x, a.y*b.y}; return c;}
fn Vec2F32 div_2f32(Vec2F32 a, Vec2F32 b)        {Vec2F32 c = {a.x/b.x, a.y/b.y}; return c;}
fn Vec2F32 scale_2f32(Vec2F32 v, F32 s)          {Vec2F32 c = {v.x*s, v.y*s}; return c;}
fn F32 dot_2f32(Vec2F32 a, Vec2F32 b)            {F32 c = a.x*b.x + a.y*b.y; return c;}
fn F32 length_squared_2f32(Vec2F32 v)            {F32 c = v.x*v.x + v.y*v.y; return c;}
fn F32 length_2f32(Vec2F32 v)                    {F32 c = sqrt_f32(v.x*v.x + v.y*v.y); return c;}
fn Vec2F32 normalize_2f32(Vec2F32 v)             {v = scale_2f32(v, 1.f/length_2f32(v)); return v;}
fn Vec2F32 mix_2f32(Vec2F32 a, Vec2F32 b, F32 t) {Vec2F32 c = {mix_1f32(a.x, b.x, t), mix_1f32(a.y, b.y, t)}; return c;}

fn Vec2I64 vec_2i64(I64 x, I64 y)                {Vec2I64 v = {x, y}; return v;}
fn Vec2I64 add_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x+b.x, a.y+b.y}; return c;}
fn Vec2I64 sub_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x-b.x, a.y-b.y}; return c;}
fn Vec2I64 mul_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x*b.x, a.y*b.y}; return c;}
fn Vec2I64 div_2i64(Vec2I64 a, Vec2I64 b)        {Vec2I64 c = {a.x/b.x, a.y/b.y}; return c;}
fn Vec2I64 scale_2i64(Vec2I64 v, I64 s)          {Vec2I64 c = {v.x*s, v.y*s}; return c;}
fn I64 dot_2i64(Vec2I64 a, Vec2I64 b)            {I64 c = a.x*b.x + a.y*b.y; return c;}
fn I64 length_squared_2i64(Vec2I64 v)            {I64 c = v.x*v.x + v.y*v.y; return c;}
fn I64 length_2i64(Vec2I64 v)                    {I64 c = (I64)sqrt_f64((F64)(v.x*v.x + v.y*v.y)); return c;}
fn Vec2I64 normalize_2i64(Vec2I64 v)             {v = scale_2i64(v, (I64)(1.f/length_2i64(v))); return v;}
fn Vec2I64 mix_2i64(Vec2I64 a, Vec2I64 b, F32 t) {Vec2I64 c = {(I64)mix_1f32((F32)a.x, (F32)b.x, t), (I64)mix_1f32((F32)a.y, (F32)b.y, t)}; return c;}

fn Vec2I32 vec_2i32(I32 x, I32 y)                {Vec2I32 v = {x, y}; return v;}
fn Vec2I32 add_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x+b.x, a.y+b.y}; return c;}
fn Vec2I32 sub_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x-b.x, a.y-b.y}; return c;}
fn Vec2I32 mul_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x*b.x, a.y*b.y}; return c;}
fn Vec2I32 div_2i32(Vec2I32 a, Vec2I32 b)        {Vec2I32 c = {a.x/b.x, a.y/b.y}; return c;}
fn Vec2I32 scale_2i32(Vec2I32 v, I32 s)          {Vec2I32 c = {v.x*s, v.y*s}; return c;}
fn I32 dot_2i32(Vec2I32 a, Vec2I32 b)            {I32 c = a.x*b.x + a.y*b.y; return c;}
fn I32 length_squared_2i32(Vec2I32 v)            {I32 c = v.x*v.x + v.y*v.y; return c;}
fn I32 length_2i32(Vec2I32 v)                    {I32 c = (I32)sqrt_f32((F32)v.x*(F32)v.x + (F32)v.y*(F32)v.y); return c;}
fn Vec2I32 normalize_2i32(Vec2I32 v)             {v = scale_2i32(v, (I32)(1.f/length_2i32(v))); return v;}
fn Vec2I32 mix_2i32(Vec2I32 a, Vec2I32 b, F32 t) {Vec2I32 c = {(I32)mix_1f32((F32)a.x, (F32)b.x, t), (I32)mix_1f32((F32)a.y, (F32)b.y, t)}; return c;}

fn Vec2I16 vec_2I16(I16 x, I16 y)                {Vec2I16 v = {x, y}; return v;}
fn Vec2I16 add_2I16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x+b.x), (I16)(a.y+b.y)}; return c;}
fn Vec2I16 sub_2I16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x-b.x), (I16)(a.y-b.y)}; return c;}
fn Vec2I16 mul_2I16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x*b.x), (I16)(a.y*b.y)}; return c;}
fn Vec2I16 div_2I16(Vec2I16 a, Vec2I16 b)        {Vec2I16 c = {(I16)(a.x/b.x), (I16)(a.y/b.y)}; return c;}
fn Vec2I16 scale_2I16(Vec2I16 v, I16 s)          {Vec2I16 c = {(I16)(v.x*s), (I16)(v.y*s)}; return c;}
fn I16 dot_2I16(Vec2I16 a, Vec2I16 b)            {I16 c = a.x*b.x + a.y*b.y; return c;}
fn I16 length_squared_2I16(Vec2I16 v)            {I16 c = v.x*v.x + v.y*v.y; return c;}
fn I16 length_2I16(Vec2I16 v)                    {I16 c = (I16)sqrt_f32((F32)(v.x*v.x + v.y*v.y)); return c;}
fn Vec2I16 normalize_2I16(Vec2I16 v)             {v = scale_2I16(v, (I16)(1.f/length_2I16(v))); return v;}
fn Vec2I16 mix_2I16(Vec2I16 a, Vec2I16 b, F32 t) {Vec2I16 c = {(I16)mix_1f32((F32)a.x, (F32)b.x, t), (I16)mix_1f32((F32)a.y, (F32)b.y, t)}; return c;}

fn Vec3F32 vec_3f32(F32 x, F32 y, F32 z)         {Vec3F32 v = {x, y, z}; return v;}
fn Vec3F32 add_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x+b.x, a.y+b.y, a.z+b.z}; return c;}
fn Vec3F32 sub_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x-b.x, a.y-b.y, a.z-b.z}; return c;}
fn Vec3F32 mul_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x*b.x, a.y*b.y, a.z*b.z}; return c;}
fn Vec3F32 div_3f32(Vec3F32 a, Vec3F32 b)        {Vec3F32 c = {a.x/b.x, a.y/b.y, a.z/b.z}; return c;}
fn Vec3F32 scale_3f32(Vec3F32 v, F32 s)          {Vec3F32 c = {v.x*s, v.y*s, v.z*s}; return c;}
fn F32 dot_3f32(Vec3F32 a, Vec3F32 b)            {F32 c = a.x*b.x + a.y*b.y + a.z*b.z; return c;}
fn F32 length_squared_3f32(Vec3F32 v)            {F32 c = v.x*v.x + v.y*v.y + v.z*v.z; return c;}
fn F32 length_3f32(Vec3F32 v)                    {F32 c = sqrt_f32(v.x*v.x + v.y*v.y + v.z*v.z); return c;}
fn Vec3F32 normalize_3f32(Vec3F32 v)             {v = scale_3f32(v, 1.f/length_3f32(v)); return v;}
fn Vec3F32 mix_3f32(Vec3F32 a, Vec3F32 b, F32 t) {Vec3F32 c = {mix_1f32(a.x, b.x, t), mix_1f32(a.y, b.y, t), mix_1f32(a.z, b.z, t)}; return c;}
fn Vec3F32 cross_3f32(Vec3F32 a, Vec3F32 b)      {Vec3F32 c = {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; return c;}

fn Vec3I32 vec_3i32(I32 x, I32 y, I32 z)         {Vec3I32 v = {x, y, z}; return v;}
fn Vec3I32 add_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x+b.x, a.y+b.y, a.z+b.z}; return c;}
fn Vec3I32 sub_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x-b.x, a.y-b.y, a.z-b.z}; return c;}
fn Vec3I32 mul_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x*b.x, a.y*b.y, a.z*b.z}; return c;}
fn Vec3I32 div_3i32(Vec3I32 a, Vec3I32 b)        {Vec3I32 c = {a.x/b.x, a.y/b.y, a.z/b.z}; return c;}
fn Vec3I32 scale_3i32(Vec3I32 v, I32 s)          {Vec3I32 c = {v.x*s, v.y*s, v.z*s}; return c;}
fn I32 dot_3i32(Vec3I32 a, Vec3I32 b)            {I32 c = a.x*b.x + a.y*b.y + a.z*b.z; return c;}
fn I32 length_squared_3i32(Vec3I32 v)            {I32 c = v.x*v.x + v.y*v.y + v.z*v.z; return c;}
fn I32 length_3i32(Vec3I32 v)                    {I32 c = (I32)sqrt_f32((F32)(v.x*v.x + v.y*v.y + v.z*v.z)); return c;}
fn Vec3I32 normalize_3i32(Vec3I32 v)             {v = scale_3i32(v, (I32)(1.f/length_3i32(v))); return v;}
fn Vec3I32 mix_3i32(Vec3I32 a, Vec3I32 b, F32 t) {Vec3I32 c = {(I32)mix_1f32((F32)a.x, (F32)b.x, t), (I32)mix_1f32((F32)a.y, (F32)b.y, t), (I32)mix_1f32((F32)a.z, (F32)b.z, t)}; return c;}
fn Vec3I32 cross_3i32(Vec3I32 a, Vec3I32 b)      {Vec3I32 c = {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; return c;}

fn Vec4F32 vec_4f32(F32 x, F32 y, F32 z, F32 w)  {Vec4F32 v = {x, y, z, w}; return v;}
fn Vec4F32 add_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w}; return c;}
fn Vec4F32 sub_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w}; return c;}
fn Vec4F32 mul_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return c;}
fn Vec4F32 div_4f32(Vec4F32 a, Vec4F32 b)        {Vec4F32 c = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return c;}
fn Vec4F32 scale_4f32(Vec4F32 v, F32 s)          {Vec4F32 c = {v.x*s, v.y*s, v.z*s, v.w*s}; return c;}
fn F32 dot_4f32(Vec4F32 a, Vec4F32 b)            {F32 c = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; return c;}
fn F32 length_squared_4f32(Vec4F32 v)            {F32 c = v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w; return c;}
fn F32 length_4f32(Vec4F32 v)                    {F32 c = sqrt_f32(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); return c;}
fn Vec4F32 normalize_4f32(Vec4F32 v)             {v = scale_4f32(v, 1.f/length_4f32(v)); return v;}
fn Vec4F32 mix_4f32(Vec4F32 a, Vec4F32 b, F32 t) {Vec4F32 c = {mix_1f32(a.x, b.x, t), mix_1f32(a.y, b.y, t), mix_1f32(a.z, b.z, t), mix_1f32(a.w, b.w, t)}; return c;}

fn Vec4I32 vec_4i32(I32 x, I32 y, I32 z, I32 w)  {Vec4I32 v = {x, y, z, w}; return v;}
fn Vec4I32 add_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w}; return c;}
fn Vec4I32 sub_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w}; return c;}
fn Vec4I32 mul_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return c;}
fn Vec4I32 div_4i32(Vec4I32 a, Vec4I32 b)        {Vec4I32 c = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return c;}
fn Vec4I32 scale_4i32(Vec4I32 v, I32 s)          {Vec4I32 c = {v.x*s, v.y*s, v.z*s, v.w*s}; return c;}
fn I32 dot_4i32(Vec4I32 a, Vec4I32 b)            {I32 c = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; return c;}
fn I32 length_squared_4i32(Vec4I32 v)            {I32 c = v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w; return c;}
fn I32 length_4i32(Vec4I32 v)                    {I32 c = (I32)sqrt_f32((F32)(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w)); return c;}
fn Vec4I32 normalize_4i32(Vec4I32 v)             {v = scale_4i32(v, (I32)(1.f/length_4i32(v))); return v;}
fn Vec4I32 mix_4i32(Vec4I32 a, Vec4I32 b, F32 t) {Vec4I32 c = {(I32)mix_1f32((F32)a.x, (F32)b.x, t), (I32)mix_1f32((F32)a.y, (F32)b.y, t), (I32)mix_1f32((F32)a.z, (F32)b.z, t), (I32)mix_1f32((F32)a.w, (F32)b.w, t)}; return c;}

fn F32 sqrt_f32(F32 number)
{
    I32 i;
    F32 x, y;
    x = number * 0.5;
    y = number;
    i = * (I32 *) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(I32 *) &i;
    y = y * (1.5 - (x * y * y));
    y = y * (1.5 - (x * y * y));
    return number * y;
}

fn F64 sqrt_f64(F64 number)
{
    I64 i;
    F64 x, y;
    x = number * 0.5;
    y = number;
    i = * (I64 *) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(I64 *) &i;
    y = y * (1.5 - (x * y * y));
    y = y * (1.5 - (x * y * y));
    return number * y;
}

F32 sin_f32(F32 a)
{
    local_persist F32 const a0 = +1.91059300966915117e-31f;
    local_persist F32 const a1 = +1.00086760103908896f;
    local_persist F32 const a2 = -1.21276126894734565e-2f;
    local_persist F32 const a3 = -1.38078780785773762e-1f;
    local_persist F32 const a4 = -2.67353392911981221e-2f;
    local_persist F32 const a5 = +2.08026600266304389e-2f;
    local_persist F32 const a6 = -3.03996055049204407e-3f;
    local_persist F32 const a7 = +1.38235642404333740e-4f;
    return a0 + a*(a1 + a*(a2 + a*(a3 + a*(a4 + a*(a5 + a*(a6 + a*a7))))));
}

F32 cos_f32(F32 a)
{
    local_persist F32 const a0 = +1.00238601909309722f;
    local_persist F32 const a1 = -3.81919947353040024e-2f;
    local_persist F32 const a2 = -3.94382342128062756e-1f;
    local_persist F32 const a3 = -1.18134036025221444e-1f;
    local_persist F32 const a4 = +1.07123798512170878e-1f;
    local_persist F32 const a5 = -1.86637164165180873e-2f;
    local_persist F32 const a6 = +9.90140908664079833e-4f;
    local_persist F32 const a7 = -5.23022132118824778e-14f;
    return a0 + a*(a1 + a*(a2 + a*(a3 + a*(a4 + a*(a5 + a*(a6 + a*a7))))));
}

F32 tan_f32(F32 radians)
{
    F32 rr = radians*radians;
    F32 a = 9.5168091e-03f;
    a *= rr;
    a += 2.900525e-03f;
    a *= rr;
    a += 2.45650893e-02f;
    a *= rr;
    a += 5.33740603e-02f;
    a *= rr;
    a += 1.333923995e-01f;
    a *= rr;
    a += 3.333314036e-01f;
    a *= rr;
    a += 1.0f;
    a *= radians;
    return a;
}

F32 exp_f32(F32 a)
{
	union { F32 f; I32 i; } u, v;
	u.i = (I32)(6051102 * a + 1056478197);
	v.i = (I32)(1056478197 - 6051102 * a);
	return u.f / v.f;
}

F32 pow_f32(F32 a, F32 b)
{
	I32 flipped = 0, e;
	F32 f, r = 1.0f;
	if (b < 0) {
		flipped = 1;
		b = -b;
	}

	e = (I32)b;
	f = exp_f32(b - e);

	while (e) {
		if (e & 1) r *= a;
		a *= a;
		e >>= 1;
	}

	r *= f;
	return flipped ? 1.0f/r : r;
}

F32 log_f32(F32 a)
{
	union { F32 f; I32 i; } u = {a};
	return (u.i - 1064866805) * 8.262958405176314e-8f; /* 1 / 12102203.0; */
}

F32 arctan_f32(F32 a)
{
	F32 u  = a*a;
	F32 u2 = u*u;
	F32 u3 = u2*u;
	F32 u4 = u3*u;
	F32 f  = 1.0f+0.33288950512027f*u-0.08467922817644f*u2+0.03252232640125f*u3-0.00749305860992f*u4;
	return a/f;
}

F32 arctan2_f32(F32 y, F32 x)
{
	if (ABS(x) > ABS(y)) {
		F32 a = arctan_f32(y/x);
		if (x > 0.0f) {
			return a;
		} else {
			return y > 0.0f ? a+MATH_TAU_OVER_2:a-MATH_TAU_OVER_2;
		}
	} else {
		F32 a = arctan_f32(x/y);
		if (x > 0.0f) {
			return y > 0.0f ? MATH_TAU_OVER_4-a:-MATH_TAU_OVER_4-a;
		} else {
			return y > 0.0f ? MATH_TAU_OVER_4+a:-MATH_TAU_OVER_4+a;
		}
	}
}

F32 arcsin_f32(F32 a) { return arctan2_f32(a, sqrt_f32((1.0f + a) * (1.0f - a))); }
F32 arccos_f32(F32 a) { return arctan2_f32(sqrt_f32((1.0f + a) * (1.0 - a)), a); }


#endif // CORE_MATH_H
