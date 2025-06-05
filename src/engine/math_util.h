#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <PR/ultratypes.h>

#include "types.h"
#include "pc/platform.h"

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
#if defined(__clang__) || defined(__GNUC__)

// These macros allow for type safe comparisons that expand without recursion in complex calls, also will use the faster fminf for f32 values
#define min(a, b) ({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _Generic((_a), \
        f32: _Generic((_b), \
            f32: __builtin_fminf(_a, _b), \
            default: (_a) < (_b) ? (_a) : (_b) \
        ), \
        default: (_a) < (_b) ? (_a) : (_b) \
    ); \
})

#define max(a, b) ({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _Generic((_a), \
        f32: _Generic((_b), \
            f32: __builtin_fmaxf(a, b), \
            default: (_a) > (_b) ? (_a) : (_b) \
        ), \
        default: (_a) > (_b) ? (_a) : (_b) \
    ); \
})

#define sqr(x) ({ \
    __typeof__(x) _x = (x); \
    _x * _x; \
})

#define absx(x) _Generic((x), \
    f32: __builtin_fabsf, \
    double: __builtin_fabs, \
    default: __builtin_abs \
)(x)

#define clamp(x, a, b) ( \
    min(max(x, a), b) \
)

#else

// Fallback to the original implementation for iDO
#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)
#define sqr(x) (x * x)
#define absx(x) ((x) < 0 ? -(x) : (x))
#define clamp(x, a, b) (min(max(x, a), b))

#endif

extern Vec3f gVec3fZero;
extern Vec3i gVec3iZero;
extern Vec3s gVec3sZero;
extern Vec3f gVec3fOne;
extern Vec3i gVec3iOne;
extern Vec3s gVec3sOne;
extern Mat4 gMat4Identity;
extern Mat4 gMat4Zero;

#include "math_util.inl"

/* |description|
Calculates the sine of the given angle, where the angle is specified as a signed 16-bit integer representing a fixed-point "SM64 angle". This function returns a floating-point result corresponding to sin(angle)
|descriptionEnd| */
f32 sins(s16 sm64Angle);

/* |description|
Calculates the cosine of the given angle, where the angle is specified as a signed 16-bit integer representing a fixed-point "SM64 angle". The function returns a floating-point value corresponding to cos(angle)
|descriptionEnd| */
f32 coss(s16 sm64Angle);

/* |description|
Computes the arctangent of y/x and returns the angle as a signed 16-bit integer, typically representing a direction in the SM64 fixed-point angle format. This can be used to find an angle between x and y coordinates
|descriptionEnd| */
s16 atan2s(f32 y, f32 x);

/* |description|
Computes the arctangent of a/b and returns it as a floating-point angle in radians. This is the floating-point equivalent of `atan2s`, allowing more precise angle calculations
|descriptionEnd| */
f32 atan2f(f32 a, f32 b);

/* |description|
Gradually moves an integer `current` value toward a `target` value, increasing it by `inc` if it is too low, or decreasing it by `dec` if it is too high. This is often used for smooth transitions or animations
|descriptionEnd| */
OPTIMIZE_O3 s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);

/* |description|
Similar to `approach_s32`, but operates on floating-point numbers. It moves `current` toward `target` by increasing it by `inc` if below target, or decreasing it by `dec` if above target, creating a smooth interpolation
|descriptionEnd| */
OPTIMIZE_O3 f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);

/* |description|
Computes spline interpolation weights for a given parameter `t` and stores these weights in `result`. This is used in spline-based animations to find intermediate positions between keyframes
|descriptionEnd| */
OPTIMIZE_O3 void spline_get_weights(struct MarioState* m, Vec4f result, f32 t, UNUSED s32 c);

/* |description|
Initializes a spline-based animation for the `MarioState` structure `m` using the provided array of 3D signed-integer vectors `keyFrames`. This sets up the animation so that it can be advanced by polling
|descriptionEnd| */
OPTIMIZE_O3 void anim_spline_init(struct MarioState* m, Vec4s *keyFrames);

/* |description|
Advances the spline-based animation associated with `m` and stores the current interpolated position in `result`. It returns the animation's status, allowing the caller to determine if the animation is ongoing or has completed
|descriptionEnd| */
OPTIMIZE_O3 s32 anim_spline_poll(struct MarioState* m, Vec3f result);

  ///////////
 // Vec3f //
///////////

#include "math_util_vec3f.inl"

/* |description|
Rotates the 3D floating-point vector `v` by the angles specified in the 3D signed-integer vector `rotate`, applying the rotations in the order Z, then X, then Y. The rotated vector replaces `v`
|descriptionEnd| */
OPTIMIZE_O3 Vec3fp vec3f_rotate_zxy(Vec3f v, Vec3s rotate);

/* |description|
Rotates the 3D floating-point vector `v` around the vector `n`, given a rotation `r` (in sm64 angle units), and stores the result in `dest`
|descriptionEnd| */
OPTIMIZE_O3 Vec3fp vec3f_rotate_around_n(Vec3f dest, Vec3f v, Vec3f n, s16 r);

/* |description|
Projects the 3D floating-point vector `v` onto another 3D floating-point vector `onto`. The resulting projection, stored in `dest`, represents how much of `v` lies along the direction of `onto`
|descriptionEnd| */
OPTIMIZE_O3 Vec3fp vec3f_project(Vec3f dest, Vec3f v, Vec3f onto);

/* |description|
Scales the 3D floating-point vector `v` by the vector `scale`, then rotates it by the rotation vector `rotation`, and finally translates it by the vector `translation`. The resulting vector is stored in `dest`
|descriptionEnd| */
OPTIMIZE_O3 Vec3fp vec3f_transform(Vec3f dest, Vec3f v, Vec3f translation, Vec3s rotation, Vec3f scale);

/* |description|
Calculates the distance between two points in 3D space (`from` and `to`), as well as the pitch and yaw angles that describe the direction from `from` to `to`. The results are stored in `dist`, `pitch`, and `yaw`
|descriptionEnd| */
OPTIMIZE_O3 void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);

/* |description|
Positions the point `to` at a given `dist`, `pitch`, and `yaw` relative to the point `from`. This can be used to place objects around a reference point at specific angles and distances
|descriptionEnd| */
OPTIMIZE_O3 void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, s16 pitch, s16 yaw);

/* |description|
Determines a vector that is perpendicular (normal) to the plane defined by three given 3D floating-point points `a`, `b`, and `c`. The resulting perpendicular vector is stored in `dest`
|descriptionEnd| */
OPTIMIZE_O3 Vec3fp find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);

  ///////////
 // Vec3i //
///////////

#include "math_util_vec3i.inl"

  ///////////
 // Vec3s //
///////////

#include "math_util_vec3s.inl"

  //////////
 // Mat4 //
//////////

#include "math_util_mat4.inl"

/* |description|
Adjusts the 4x4 floating-point matrix `mtx` so that it represents a viewing transformation looking from the point `from` toward the point `to`, with a given roll angle. This creates a view matrix oriented toward `to`
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll);

/* |description|
Rotates `dest` according to the angles in `rotate` using ZXY order, and then translates it by the 3D floating-point vector `translate`. This effectively positions and orients `dest` in 3D space
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate);

/* |description|
Rotates `dest` using angles in XYZ order, and then translates it by the 3D floating-point vector `b` and applies the rotations described by `c`. This sets up `dest` with a specific orientation and position in space
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c);

/* |description|
Transforms a 4x4 floating-point matrix `mtx` into a "billboard" oriented toward the camera or a given direction. The billboard is placed at `position` and rotated by `angle`. This is useful for objects that should always face the viewer
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);

/* |description|
Creates a "cylindrical billboard" transformation from the 4x4 matrix `mtx` placed at `position` with a given `angle`. Unlike a full billboard, this might allow rotation around one axis while still facing the viewer on others
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_cylboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);

/* |description|
Aligns `dest` so that it fits the orientation of a terrain surface defined by its normal vector `upDir`. The transformation is positioned at `pos` and oriented with a given `yaw`. This is often used to make objects sit naturally on uneven ground
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);

/* |description|
Aligns `mtx` to fit onto a terrain triangle at `pos`, applying a given `yaw` and scaling by `radius`. This helps position objects so they match the orientation of the terrain's surface
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);

/* |description|
Multiplies two 4x4 floating-point matrices `a` and `b` (in that order), storing the product in `dest`. This can be used for combining multiple transformations into one
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b);

/* |description|
Multiplies the 3D signed-integer vector `b` with the 4x4 floating-point matrix `mtx`, which applies the transformation to the point
|descriptionEnd| */
OPTIMIZE_O3 s16 *mtxf_mul_vec3s(Mat4 mtx, Vec3s b);

/* |description|
Rotates the matrix `mtx` in the XY plane by the given `angle`. Rotating in the XY plane typically means pivoting around the Z axis
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_rotate_xy(Mat4 mtx, s16 angle);

/* |description|
Inverts the 4x4 floating-point matrix `src` and stores the inverse in `dest`. Applying the inverse transformation undoes whatever `src` did, returning points back to their original coordinate space
|descriptionEnd| */
OPTIMIZE_O3 void mtxf_inverse(Mat4 dest, Mat4 src);

/* |description|
Extracts the position (translation component) from the transformation matrix `objMtx` relative to the coordinate system defined by `camMtx` and stores that 3D position in `dest`. This can be used to get the object's coordinates in camera space
|descriptionEnd| */
OPTIMIZE_O3 Vec3fp get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx);

#endif // MATH_UTIL_H

