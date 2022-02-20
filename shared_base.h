#pragma once

#include <math.h>
#include <assert.h>

#ifndef MA_COINIT_VALUE
#define MA_COINIT_VALUE    0   /* 0 = COINIT_MULTITHREADED */
#endif


#ifndef MA_FLT_MAX
    #ifdef FLT_MAX
        #define MA_FLT_MAX FLT_MAX
    #else
        #define MA_FLT_MAX 3.402823466e+38F
    #endif
#endif


#ifndef MA_PI
#define MA_PI      3.14159265358979323846264f
#endif
#ifndef MA_PI_D
#define MA_PI_D    3.14159265358979323846264
#endif
#ifndef MA_TAU
#define MA_TAU     6.28318530717958647693f
#endif
#ifndef MA_TAU_D
#define MA_TAU_D   6.28318530717958647693
#endif


/* The default format when ma_format_unknown (0) is requested when initializing a device. */
#ifndef MA_DEFAULT_FORMAT
#define MA_DEFAULT_FORMAT                                   ma_format_f32
#endif

/* The default channel count to use when 0 is used when initializing a device. */
#ifndef MA_DEFAULT_CHANNELS
#define MA_DEFAULT_CHANNELS                                 2
#endif

/* The default sample rate to use when 0 is used when initializing a device. */
#ifndef MA_DEFAULT_SAMPLE_RATE
#define MA_DEFAULT_SAMPLE_RATE                              48000
#endif

/* Default periods when none is specified in ma_device_init(). More periods means more work on the CPU. */
#ifndef MA_DEFAULT_PERIODS
#define MA_DEFAULT_PERIODS                                  3
#endif

/* The default period size in milliseconds for low latency mode. */
#ifndef MA_DEFAULT_PERIOD_SIZE_IN_MILLISECONDS_LOW_LATENCY
#define MA_DEFAULT_PERIOD_SIZE_IN_MILLISECONDS_LOW_LATENCY  10
#endif

/* The default buffer size in milliseconds for conservative mode. */
#ifndef MA_DEFAULT_PERIOD_SIZE_IN_MILLISECONDS_CONSERVATIVE
#define MA_DEFAULT_PERIOD_SIZE_IN_MILLISECONDS_CONSERVATIVE 100
#endif

/* The default LPF filter order for linear resampling. Note that this is clamped to MA_MAX_FILTER_ORDER. */
#ifndef MA_DEFAULT_RESAMPLER_LPF_ORDER
    #if MA_MAX_FILTER_ORDER >= 4
        #define MA_DEFAULT_RESAMPLER_LPF_ORDER  4
    #else
        #define MA_DEFAULT_RESAMPLER_LPF_ORDER  MA_MAX_FILTER_ORDER
    #endif
#endif


#if defined(__clang__) || (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
#endif

/******************************************************************************

Standard Library Stuff

******************************************************************************/
#ifndef MA_MALLOC
#ifdef MA_WIN32
#define MA_MALLOC(sz) HeapAlloc(GetProcessHeap(), 0, (sz))
#else
#define MA_MALLOC(sz) malloc((sz))
#endif
#endif

#ifndef MA_REALLOC
#ifdef MA_WIN32
#define MA_REALLOC(p, sz) (((sz) > 0) ? ((p) ? HeapReAlloc(GetProcessHeap(), 0, (p), (sz)) : HeapAlloc(GetProcessHeap(), 0, (sz))) : ((VOID*)(size_t)(HeapFree(GetProcessHeap(), 0, (p)) & 0)))
#else
#define MA_REALLOC(p, sz) realloc((p), (sz))
#endif
#endif

#ifndef MA_FREE
#ifdef MA_WIN32
#define MA_FREE(p) HeapFree(GetProcessHeap(), 0, (p))
#else
#define MA_FREE(p) free((p))
#endif
#endif

#ifndef MA_ZERO_MEMORY
#ifdef MA_WIN32
#define MA_ZERO_MEMORY(p, sz) ZeroMemory((p), (sz))
#else
#define MA_ZERO_MEMORY(p, sz) memset((p), 0, (sz))
#endif
#endif

#ifndef MA_COPY_MEMORY
#ifdef MA_WIN32
#define MA_COPY_MEMORY(dst, src, sz) CopyMemory((dst), (src), (sz))
#else
#define MA_COPY_MEMORY(dst, src, sz) memcpy((dst), (src), (sz))
#endif
#endif

#ifndef MA_MOVE_MEMORY
#ifdef MA_WIN32
#define MA_MOVE_MEMORY(dst, src, sz) MoveMemory((dst), (src), (sz))
#else
#define MA_MOVE_MEMORY(dst, src, sz) memmove((dst), (src), (sz))
#endif
#endif

#ifndef MA_ASSERT
#ifdef MA_WIN32
#define MA_ASSERT(condition) assert(condition)
#else
#define MA_ASSERT(condition) assert(condition)
#endif
#endif

#define MA_ZERO_OBJECT(p) MA_ZERO_MEMORY((p), sizeof(*(p)))

#define ma_countof(x)               (sizeof(x) / sizeof(x[0]))
#define ma_max(x, y)                (((x) > (y)) ? (x) : (y))
#define ma_min(x, y)                (((x) < (y)) ? (x) : (y))
#define ma_abs(x)                   (((x) > 0) ? (x) : -(x))
#define ma_clamp(x, lo, hi)         (ma_max(lo, ma_min(x, hi)))
#define ma_offset_ptr(p, offset)    (((ma_uint8*)(p)) + (offset))
#define ma_align(x, a)              ((x + (a-1)) & ~(a-1))
#define ma_align_64(x)              ma_align(x, 8)

#define ma_buffer_frame_capacity(buffer, channels, format) (sizeof(buffer) / ma_get_bytes_per_sample(format) / (channels))

static MA_INLINE double ma_sind(double x)
{
    /* TODO: Implement custom sin(x). */
    return sin(x);
}

static MA_INLINE double ma_expd(double x)
{
    /* TODO: Implement custom exp(x). */
    return exp(x);
}

static MA_INLINE double ma_logd(double x)
{
    /* TODO: Implement custom log(x). */
    return log(x);
}

static MA_INLINE double ma_powd(double x, double y)
{
    /* TODO: Implement custom pow(x, y). */
    return pow(x, y);
}

static MA_INLINE double ma_sqrtd(double x)
{
    /* TODO: Implement custom sqrt(x). */
    return sqrt(x);
}


static MA_INLINE float ma_sinf(float x)
{
    return (float)ma_sind((float)x);
}

static MA_INLINE double ma_cosd(double x)
{
    return ma_sind((MA_PI_D*0.5) - x);
}

static MA_INLINE float ma_cosf(float x)
{
    return (float)ma_cosd((float)x);
}

static MA_INLINE double ma_log10d(double x)
{
    return ma_logd(x) * 0.43429448190325182765;
}

static MA_INLINE float ma_powf(float x, float y)
{
    return (float)ma_powd((double)x, (double)y);
}

static MA_INLINE float ma_log10f(float x)
{
    return (float)ma_log10d((double)x);
}


static MA_INLINE double ma_degrees_to_radians(double degrees)
{
    return degrees * 0.01745329252;
}

static MA_INLINE double ma_radians_to_degrees(double radians)
{
    return radians * 57.295779512896;
}

static MA_INLINE float ma_degrees_to_radians_f(float degrees)
{
    return degrees * 0.01745329252f;
}

static MA_INLINE float ma_radians_to_degrees_f(float radians)
{
    return radians * 57.295779512896f;
}