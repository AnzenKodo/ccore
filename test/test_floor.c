// By Mārtiņš Možeiko
// Source: https://gist.github.com/mmozeiko/56db3df14ab380152d6875383d0f4afd
// floor function for floats with SSE1 or SSE2

#include <emmintrin.h>
#include <smmintrin.h>

#ifdef _MSC_VER
#include <intrin.h>
#else
#define __rdtsc() __builtin_ia32_rdtsc()
#endif

#include <math.h>
#include <stdio.h>
#include <string.h>

#if _M_FP_FAST || __FAST_MATH__
#error Please do not use /fp:fast or -ffast-math
#endif

static float std_floor(float x)
{
    // when compiled with -msse4.1 or with /arch:AVX this
    // will actually produce "roundss" instruction
    return floorf(x);
}

// full float range, with INFs & NANs
static float sse_floor(float x)
{
    __m128 kSignBit = _mm_set1_ps(-0.f);
    __m128 kOne = _mm_set1_ps(1.f);
    __m128 kNoFraction = _mm_set1_ps(8388608.f);

    __m128 f = _mm_set_ss(x);
    __m128 r = f;

    // r = (float)(int)f;
    r = _mm_add_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);
    r = _mm_add_ss(r, kNoFraction);

    // if (f < r) r -= 1;
    r = _mm_sub_ss(r, _mm_and_ps(kOne, _mm_cmplt_ss(f, r)));

    // if (!(2**23 > abs(f))) r = f;
    __m128 m = _mm_cmpgt_ss(kNoFraction, _mm_andnot_ps(kSignBit, f));
    r = _mm_or_ps(_mm_and_ps(m, r), _mm_andnot_ps(m, f));

    return _mm_cvtss_f32(r);
}

// only non-negative floats (x >= 0.f)
static float sse_floor_pos(float x)
{
    __m128 kOne = _mm_set1_ps(1.f);
    __m128 kNoFraction = _mm_set1_ps(8388608.f);

    __m128 f = _mm_set_ss(x);
    __m128 r = f;

    r = _mm_add_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);

    r = _mm_sub_ss(r, _mm_and_ps(kOne, _mm_cmplt_ss(f, r)));

    __m128 m = _mm_cmpgt_ss(kNoFraction, f);
    r = _mm_or_ps(_mm_and_ps(m, r), _mm_andnot_ps(m, f));

    return _mm_cvtss_f32(r);
}

// only non-positive floats (x <= 0.f)
static float sse_floor_neg(float x)
{
    __m128 kOne = _mm_set1_ps(1.f);
    __m128 kNoFraction = _mm_set1_ps(-8388608.f);

    __m128 f = _mm_set_ss(x);
    __m128 r = f;

    r = _mm_add_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);

    r = _mm_sub_ss(r, _mm_and_ps(kOne, _mm_cmplt_ss(f, r)));

    __m128 m = _mm_cmpgt_ss(f, kNoFraction);
    r = _mm_or_ps(_mm_and_ps(m, r), _mm_andnot_ps(m, f));

    return _mm_cvtss_f32(r);
}

// only [-8388608 .. +8388608] range
static float sse_floor_small(float x)
{
    __m128 kOne = _mm_set1_ps(1.f);
    __m128 kNoFraction = _mm_set1_ps(8388608.f);

    __m128 f = _mm_set_ss(x);
    __m128 r = f;

    r = _mm_add_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);
    r = _mm_add_ss(r, kNoFraction);

    r = _mm_sub_ss(r, _mm_and_ps(kOne, _mm_cmplt_ss(f, r)));

    return _mm_cvtss_f32(r);
}

// only [0 .. +8388608] range
static float sse_floor_small_pos(float x)
{
    __m128 kOne = _mm_set1_ps(1.f);
    __m128 kNoFraction = _mm_set1_ps(8388608.f);

    __m128 f = _mm_set_ss(x);
    __m128 r = f;

    r = _mm_add_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);

    r = _mm_sub_ss(r, _mm_and_ps(kOne, _mm_cmplt_ss(f, r)));

    return _mm_cvtss_f32(r);
}

// only [-8388608 .. 0] range
static float sse_floor_small_neg(float x)
{
    __m128 kOne = _mm_set1_ps(1.f);
    __m128 kNoFraction = _mm_set1_ps(-8388608.f);

    __m128 f = _mm_set_ss(x);
    __m128 r = f;

    r = _mm_add_ss(r, kNoFraction);
    r = _mm_sub_ss(r, kNoFraction);

    r = _mm_sub_ss(r, _mm_and_ps(kOne, _mm_cmplt_ss(f, r)));

    return _mm_cvtss_f32(r);
}

// full float range, including INFs & NANs
static float sse2_floor(float x)
{
    __m128 kSignBit = _mm_set1_ps(-0.f);
    __m128 kOne = _mm_set1_ps(1.f);
    __m128 kMaxValue = _mm_set1_ps(2147483648.f); // this could be 8388608.f

    // r = (float)(int)f;
    __m128 f = _mm_set_ss(x);
    __m128 r = _mm_cvtepi32_ps(_mm_cvttps_epi32(f));

    // if (f < r) r -= 1;
    r = _mm_sub_ss(r, _mm_and_ps(_mm_cmplt_ss(f, r), kOne));

    // if (!(2**31 > abs(f))) r = f;
    __m128 m = _mm_cmpgt_ss(kMaxValue, _mm_andnot_ps(kSignBit, f));
    r = _mm_or_ps(_mm_and_ps(m, r), _mm_andnot_ps(m, f));

    return _mm_cvtss_f32(r);
}

// only [-2147483648 .. +2147483648) range, if floor(x) fits into int32_t, then result will be correct
static float sse2_floor_small(float x)
{
    __m128 kOne = _mm_set_ss(1.f);

    __m128 f = _mm_set_ss(x);
    __m128 r = _mm_cvtepi32_ps(_mm_cvttps_epi32(f));

    r = _mm_sub_ss(r, _mm_and_ps(_mm_cmplt_ss(f, r), kOne));

    return _mm_cvtss_f32(r);
}

// only [0 .. +2147483648) range, same as above, but only for non-negative values
static float sse2_floor_small_pos(float x)
{
    __m128 f = _mm_set_ss(x);
    __m128 r = _mm_cvtepi32_ps(_mm_cvttps_epi32(f));

    return _mm_cvtss_f32(r);
}

#if defined(__clang__) || defined(__GNUC__)
__attribute__((target("sse4.1")))
#endif
// full float range, with INFs & NANs
static float sse4_floor(float x)
{
    __m128 f = _mm_set_ss(x);
    __m128 r = _mm_floor_ss(f, f);
    return _mm_cvtss_f32(r);
}

#define CHECK(f, x, expected, func) do \
{                                                                                                  \
    float actual = func(f);                                                                        \
    if (fpclassify(actual) == FP_NAN && fpclassify(expected) == FP_NAN) {} /* OK, both are NaNs */ \
    else if (actual != expected)                                                                   \
    {                                                                                              \
        printf("ERROR: f=%1.8e (0x%08x) floorf=%1.8e %s=%1.8e\n", f, x, expected, #func, actual);  \
        return 0;                                                                                  \
    }                                                                                              \
} while (0)

#if defined(_MSC_VER) && !defined(__clang__)
#define DO_NOT_OPTIMIZE(x) volatile float temp = x
#else
#define DO_NOT_OPTIMIZE(x) __asm__ __volatile__("" : "+x"(x) : : "memory")
#endif

#define BENCH_ITERS 65536
#define BENCH_COUNT 4096

#define BENCH(func) do                                         \
{                                                              \
    unsigned long long best = ~0ULL;                           \
    for (int k=0; k<BENCH_ITERS; k++)                          \
    {                                                          \
        volatile float f = 0;                                  \
        unsigned long long t1 = __rdtsc();                     \
        for (int i=0; i<BENCH_COUNT; i++)                      \
        {                                                      \
            float r = func(f);                                 \
            DO_NOT_OPTIMIZE(r);                                \
        }                                                      \
        unsigned long long t2 = __rdtsc();                     \
        if (t2 - t1 < best) best = t2 - t1;                    \
    }                                                          \
    printf("%-23s%5.2f\n", #func, (double)best / BENCH_COUNT); \
} while (0)

int main()
{
    volatile unsigned int x = 0;
    do
    {
        if ((x % (1<<26) == 0))
        {
            printf(".");
            fflush(stdout);
        }

        float f;
        memcpy((void*)&f, (void*)&x, 4);

        float expected = std_floor(f);

        CHECK(f, x, expected, sse_floor);

        if (f >= 0.f)
        {
            CHECK(f, x, expected, sse_floor_pos);
        }
        if (f <= 0.f)
        {
            CHECK(f, x, expected, sse_floor_neg);
        }
        if (f >= -8388608.f && f <= 8388608.f)
        {
            CHECK(f, x, expected, sse_floor_small);
        }
        if (f >= 0.f && f <= 8388608.f)
        {
            CHECK(f, x, expected, sse_floor_small_pos);
        }
        if (f >= -8388608.f && f <= 0.f)
        {
            CHECK(f, x, expected, sse_floor_small_neg);
        }

        CHECK(f, x, expected, sse2_floor);

        if (f >= -2147483648.f && f < +2147483648.f)
        {
            CHECK(f, x, expected, sse2_floor_small);
        }
        if (f >= 0.f && f < +2147483648.f)
        {
            CHECK(f, x, expected, sse2_floor_small_pos);
        }

        CHECK(f, x, expected, sse4_floor);

        x++;
    }
    while (x != 0);

    printf(" OK!\n");

    BENCH(std_floor);
    BENCH(sse_floor);
    BENCH(sse_floor_pos);
    BENCH(sse_floor_neg);
    BENCH(sse_floor_small);
    BENCH(sse_floor_small_pos);
    BENCH(sse_floor_small_neg);
    BENCH(sse2_floor);
    BENCH(sse2_floor_small);
    BENCH(sse2_floor_small_pos);
    BENCH(sse4_floor);
}
