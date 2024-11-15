#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <PR/ultratypes.h>

#include "types.h"

/**
 * Converts an angle in degrees to sm64's s16 angle units. For example, DEGREES(90) == 0x4000
 * This should be used mainly to make camera code clearer at first glance.
 */
// #define DEGREES(x) ((x) * 0x10000 / 360)
#define DEGREES(x) ((x) * 0x2000 / 45)

/*
 * The sine and cosine tables overlap, but "#define gCosineTable (gSineTable +
 * 0x400)" doesn't give expected codegen; gSineTable and gCosineTable need to
 * be different symbols for code to match. Most likely the tables were placed
 * adjacent to each other, and gSineTable cut short, such that reads overflow
 * into gCosineTable.
 *
 * These kinds of out of bounds reads are undefined behavior, and break on
 * e.g. GCC (which doesn't place the tables next to each other, and probably
 * exploits array sizes for range analysis-based optimizations as well).
 * Thus, for non-IDO compilers we use the standard-compliant version.
 */
extern f32 gSineTable[];
#ifdef AVOID_UB
#define gCosineTable (gSineTable + 0x400)
#else
extern f32 gCosineTable[];
#endif

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

// Inline Function prototypes
f32 minf(f32 a, f32 b);
s16 min(s16 a, s16 b);
f32 maxf(f32 a, f32 b);
s16 max(s16 a, s16 b);
f32 sqrf(f32 x);
s16 sqr(s16 x);
f32 sins(s16 sm64Angle);
f32 coss(s16 sm64Angle);

#define min(a, b) _Generic((a), \
    f32: minf, \
    default: min \
)(a, b)

#define max(a, b) _Generic((a), \
    f32: maxf, \
    default: max \
)(a, b)

#define sqr(x) _Generic((x), \
    f32: sqrf, \
    default: sqr \
)(x)

#if defined(__clang__) || defined(__GNUC__)

#define absx(x) _Generic((x), \
    f32: __builtin_fabsf, \
    double: __builtin_fabs, \
    default: __builtin_abs \
)(x)

#else

#define absx(x) ((x) < 0 ? -(x) : (x))

#endif

#include "../../include/libc/stdlib.h"

void *vec3f_copy(Vec3f dest, Vec3f src);
void *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z);
void *vec3f_add(Vec3f dest, Vec3f a);
void *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b);
void *vec3f_dif(Vec3f dest, Vec3f a, Vec3f b);
void *vec3f_mul(Vec3f dest, f32 a);
void *vec3s_copy(Vec3s dest, Vec3s src);
void *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z);
void *vec3s_add(Vec3s dest, Vec3s a);
void *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b);
void *vec3s_sub(Vec3s dest, Vec3s a);
void *vec3s_to_vec3f(Vec3f dest, Vec3s a);
void *vec3f_to_vec3s(Vec3s dest, Vec3f a);
void *find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);
void *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b);
void *vec3f_normalize(Vec3f dest);
f32 vec3f_length(Vec3f a);
f32 vec3f_dot(Vec3f a, Vec3f b);
void vec3f_combine(Vec3f dest, Vec3f vecA, Vec3f vecB, f32 sclA, f32 sclB);
void *vec3f_rotate_zxy(Vec3f v, Vec3s rotate);
void mtxf_copy(Mat4 dest, Mat4 src);
void mtxf_identity(Mat4 mtx);
void mtxf_translate(Mat4 dest, Vec3f b);
void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll);
void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate);
void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c);
void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);
void mtxf_cylboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);
void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);
void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);
void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b);
void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s);
void mtxf_mul_vec3s(Mat4 mtx, Vec3s b);
void mtxf_to_mtx(Mtx *dest, Mat4 src);
void mtxf_rotate_xy(Mtx *mtx, s16 angle);
void mtxf_inverse(Mat4 dest, Mat4 src);
void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx);
void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32  dist, s16  pitch, s16  yaw);
s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);
f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);
s16 atan2s(f32 y, f32 x);
f32 atan2f(f32 a, f32 b);
void spline_get_weights(struct MarioState* m, Vec4f result, f32 t, UNUSED s32 c);
void anim_spline_init(struct MarioState* m, Vec4s *keyFrames);
s32 anim_spline_poll(struct MarioState* m, Vec3f result);

f32 not_zero(f32 value, f32 replacement);

void vec3f_project(Vec3f vec, Vec3f onto, Vec3f out);
f32 vec3f_dist(Vec3f v1, Vec3f v2);

#endif // MATH_UTIL_H
