#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <PR/ultratypes.h>

#include "types.h"

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

#else

// Fallback to the original implementation for iDO
#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)
#define sqr(x) (x * x)
#define absx(x) ((x) < 0 ? -(x) : (x))

#endif

/* |description|
Calculates the sine of the given angle, where the angle is specified as a signed 16-bit integer representing a fixed-point "SM64 angle". This function returns a floating-point result corresponding to sin(angle)
|descriptionEnd| */
f32 sins(s16 sm64Angle);

/* |description|
Calculates the cosine of the given angle, where the angle is specified as a signed 16-bit integer representing a fixed-point "SM64 angle". The function returns a floating-point value corresponding to cos(angle)
|descriptionEnd| */
f32 coss(s16 sm64Angle);

#include "../../include/libc/stdlib.h"

/* |description|
Copies the contents of a 3D floating-point vector (`src`) into another 3D floating-point vector (`dest`). After this operation, `dest` will have the same x, y, and z values as `src`
|descriptionEnd| */
void *vec3f_copy(Vec3f dest, Vec3f src);

/* |description|
Sets the values of the 3D floating-point vector `dest` to the given x, y, and z values. After this function, `dest` will have values (x, y, z)
|descriptionEnd| */
void *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z);

/* |description|
Adds the components of the 3D floating-point vector `a` to `dest`. After this operation, `dest.x` will be `dest.x + a.x`, and similarly for the y and z components
|descriptionEnd| */
void *vec3f_add(Vec3f dest, Vec3f a);

/* |description|
Adds the corresponding components of two 3D floating-point vectors `a` and `b`, and stores the result in `dest`. For example, `dest.x = a.x + b.x`, `dest.y = a.y + b.y`, and `dest.z = a.z + b.z`
|descriptionEnd| */
void *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b);

/* |description|
Subtracts the components of the 3D floating-point vector `b` from the components of `a` and stores the result in `dest`. For example, `dest.x = a.x - b.x`
This results in a vector that represents the difference between `a` and `b`.
|descriptionEnd| */
void *vec3f_dif(Vec3f dest, Vec3f a, Vec3f b);

/* |description|
Multiplies each component of the 3D floating-point vector `dest` by the scalar value `a`. For instance, `dest.x = dest.x * a`, and similarly for y and z. This scales the vector `dest` by `a`
|descriptionEnd| */
void *vec3f_mul(Vec3f dest, f32 a);

/* |description|
Copies the components of one 3D signed-integer vector (`src`) to another (`dest`). After this function, `dest` will have the same x, y, and z integer values as `src`
|descriptionEnd| */
void *vec3s_copy(Vec3s dest, Vec3s src);

/* |description|
Sets the 3D signed-integer vector `dest` to the specified integer values (x, y, z), so that `dest` becomes (x, y, z).
|descriptionEnd| */
void *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z);

/* |description|
Adds the components of a 3D signed-integer vector `a` to the corresponding components of `dest`. After this operation, each component of `dest` is increased by the corresponding component in `a`
|descriptionEnd| */
void *vec3s_add(Vec3s dest, Vec3s a);

/* |description|
Adds the components of two 3D signed-integer vectors `a` and `b` together and stores the resulting vector in `dest`. For example, `dest.x = a.x + b.x`, and similarly for y and z
|descriptionEnd| */
void *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b);

/* |description|
Subtracts the components of a 3D signed-integer vector `b` from the components of `a` and stores the result in `dest`. This gives a vector representing the difference `a - b`
|descriptionEnd| */
void *vec3s_sub(Vec3s dest, Vec3s a);

/* |description|
Converts a 3D signed-integer vector `a` (vec3s) into a 3D floating-point vector and stores it in `dest`. After this operation, `dest` will contain the floating-point equivalents of `a`'s integer components
|descriptionEnd| */
void *vec3s_to_vec3f(Vec3f dest, Vec3s a);

/* |description|
Converts a 3D floating-point vector `a` (Vec3f) into a 3D signed-integer vector and stores it in `dest`. After this operation, `dest` will contain the integer versions of `a`'s floating-point components
|descriptionEnd| */
void *vec3f_to_vec3s(Vec3s dest, Vec3f a);

/* |description|
Determines a vector that is perpendicular (normal) to the plane defined by three given 3D floating-point points `a`, `b`, and `c`. The resulting perpendicular vector is stored in `dest`
|descriptionEnd| */
void *find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);

/* |description|
Computes the cross product of two 3D floating-point vectors `a` and `b`. The cross product is a vector perpendicular to both `a` and `b`. The result is stored in `dest`
|descriptionEnd| */
void *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b);

/* |description|
Normalizes the 3D floating-point vector `dest` so that its length (magnitude) becomes 1, while retaining its direction. This effectively scales `dest` so that it lies on the unit sphere
|descriptionEnd| */
void *vec3f_normalize(Vec3f dest);

/* |description|
Calculates the length (magnitude) of the 3D floating-point vector `a`. The length is defined as sqrt(x² + y² + z²) for the vector components (x, y, z)
|descriptionEnd| */
f32 vec3f_length(Vec3f a);

/* |description|
Computes the dot product of the two 3D floating-point vectors `a` and `b`. The dot product is a scalar value defined by (a.x * b.x + a.y * b.y + a.z * b.z), representing how aligned the two vectors are
|descriptionEnd| */
f32 vec3f_dot(Vec3f a, Vec3f b);

/* |description|
Takes two 3D floating-point vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, and then adds the scaled vectors together. The final combined vector is stored in `dest`
|descriptionEnd| */
void vec3f_combine(Vec3f dest, Vec3f vecA, Vec3f vecB, f32 sclA, f32 sclB);

/* |description|
Rotates the 3D floating-point vector `v` by the angles specified in the 3D signed-integer vector `rotate`, applying the rotations in the order Z, then X, then Y. The rotated vector replaces `v`
|descriptionEnd| */
void *vec3f_rotate_zxy(Vec3f v, Vec3s rotate);

/* |description|
Copies the 4x4 floating-point matrix `src` into `dest`. After this operation, `dest` contains the same matrix values as `src`
|descriptionEnd| */
void mtxf_copy(Mat4 dest, Mat4 src);

/* |description|
Sets the 4x4 floating-point matrix `mtx` to the identity matrix. The identity matrix leaves points unchanged when they are transformed by it which is useful for matrix math
|descriptionEnd| */
void mtxf_identity(Mat4 mtx);

/* |description|
Applies a translation to the 4x4 floating-point matrix `dest` by adding the coordinates in the 3D floating-point vector `b`. This shifts any transformed point by `b`
|descriptionEnd| */
void mtxf_translate(Mat4 dest, Vec3f b);

/* |description|
Adjusts the 4x4 floating-point matrix `mtx` so that it represents a viewing transformation looking from the point `from` toward the point `to`, with a given roll angle. This creates a view matrix oriented toward `to`
|descriptionEnd| */
void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll);

/* |description|
Rotates `dest` according to the angles in `rotate` using ZXY order, and then translates it by the 3D floating-point vector `translate`. This effectively positions and orients `dest` in 3D space
|descriptionEnd| */
void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate);

/* |description|
Rotates `dest` using angles in XYZ order, and then translates it by the 3D floating-point vector `b` and applies the rotations described by `c`. This sets up `dest` with a specific orientation and position in space
|descriptionEnd| */
void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c);

/* |description|
Transforms a 4x4 floating-point matrix `mtx` into a "billboard" oriented toward the camera or a given direction. The billboard is placed at `position` and rotated by `angle`. This is useful for objects that should always face the viewer
|descriptionEnd| */
void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);

/* |description|
Creates a "cylindrical billboard" transformation from the 4x4 matrix `mtx` placed at `position` with a given `angle`. Unlike a full billboard, this might allow rotation around one axis while still facing the viewer on others
|descriptionEnd| */
void mtxf_cylboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);

/* |description|
Aligns `dest` so that it fits the orientation of a terrain surface defined by its normal vector `upDir`. The transformation is positioned at `pos` and oriented with a given `yaw`. This is often used to make objects sit naturally on uneven ground
|descriptionEnd| */
void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);

/* |description|
Aligns `mtx` to fit onto a terrain triangle at `pos`, applying a given `yaw` and scaling by `radius`. This helps position objects so they match the orientation of the terrain's surface
|descriptionEnd| */
void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);

/* |description|
Multiplies two 4x4 floating-point matrices `a` and `b` (in that order), storing the product in `dest`. This can be used for combining multiple transformations into one
|descriptionEnd| */
void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b);

/* |description|
Scales the 4x4 floating-point matrix `mtx` by the scaling factors found in the 3D floating-point vector `s`, and stores the result in `dest`. This enlarges or shrinks objects in 3D space
|descriptionEnd| */
void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s);

/* |description|
Multiplies the 4x4 floating-point matrix `mtx` by a 3D signed-integer vector `b`, potentially interpreting `b` as angles or translations depending on usage, and modifies `mtx` accordingly
|descriptionEnd| */
void mtxf_mul_vec3s(Mat4 mtx, Vec3s b);

/* |description|
Converts the floating-point matrix `src` into a fixed-point (integer-based) matrix suitable for the `Mtx` format, and stores the result in `dest`
|descriptionEnd| */
void mtxf_to_mtx(Mtx *dest, Mat4 src);

/* |description|
Rotates the matrix `mtx` in the XY plane by the given `angle`. Rotating in the XY plane typically means pivoting around the Z axis
|descriptionEnd| */
void mtxf_rotate_xy(Mtx *mtx, s16 angle);

/* |description|
Inverts the 4x4 floating-point matrix `src` and stores the inverse in `dest`. Applying the inverse transformation undoes whatever `src` did, returning points back to their original coordinate space
|descriptionEnd| */
void mtxf_inverse(Mat4 dest, Mat4 src);

/* |description|
Extracts the position (translation component) from the transformation matrix `objMtx` relative to the coordinate system defined by `camMtx` and stores that 3D position in `dest`. This can be used to get the object's coordinates in camera space
|descriptionEnd| */
void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx);

/* |description|
Calculates the distance between two points in 3D space (`from` and `to`), as well as the pitch and yaw angles that describe the direction from `from` to `to`. The results are stored in `dist`, `pitch`, and `yaw`
|descriptionEnd| */
void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);

/* |description|
Positions the point `to` at a given `dist`, `pitch`, and `yaw` relative to the point `from`. This can be used to place objects around a reference point at specific angles and distances
|descriptionEnd| */
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32  dist, s16  pitch, s16  yaw);

/* |description|
Gradually moves an integer `current` value toward a `target` value, increasing it by `inc` if it is too low, or decreasing it by `dec` if it is too high. This is often used for smooth transitions or animations
|descriptionEnd| */
s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);

/* |description|
Similar to `approach_s32`, but operates on floating-point numbers. It moves `current` toward `target` by increasing it by `inc` if below target, or decreasing it by `dec` if above target, creating a smooth interpolation
|descriptionEnd| */
f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);

/* |description|
Computes the arctangent of y/x and returns the angle as a signed 16-bit integer, typically representing a direction in the SM64 fixed-point angle format. This can be used to find an angle between x and y coordinates
|descriptionEnd| */
s16 atan2s(f32 y, f32 x);

/* |description|
Computes the arctangent of a/b and returns it as a floating-point angle in radians. This is the floating-point equivalent of `atan2s`, allowing more precise angle calculations
|descriptionEnd| */
f32 atan2f(f32 a, f32 b);

/* |description|
Computes spline interpolation weights for a given parameter `t` and stores these weights in `result`. This is used in spline-based animations to find intermediate positions between keyframes
|descriptionEnd| */
void spline_get_weights(struct MarioState* m, Vec4f result, f32 t, UNUSED s32 c);

/* |description|
Initializes a spline-based animation for the `MarioState` structure `m` using the provided array of 3D signed-integer vectors `keyFrames`. This sets up the animation so that it can be advanced by polling
|descriptionEnd| */
void anim_spline_init(struct MarioState* m, Vec4s *keyFrames);

/* |description|
Advances the spline-based animation associated with `m` and stores the current interpolated position in `result`. It returns the animation's status, allowing the caller to determine if the animation is ongoing or has completed
|descriptionEnd| */
s32 anim_spline_poll(struct MarioState* m, Vec3f result);

/* |description|
Checks if `value` is zero. If not, it returns `value`. If it is zero, it returns the `replacement` value. This function ensures that a zero value can be substituted with a fallback value if needed
|descriptionEnd| */
f32 not_zero(f32 value, f32 replacement);

/* |description|
Projects the 3D floating-point vector `vec` onto another 3D floating-point vector `onto`. The resulting projection, stored in `out`, represents how much of `vec` lies along the direction of `onto`
|descriptionEnd| */
void vec3f_project(Vec3f vec, Vec3f onto, Vec3f out);

/* |description|
Calculates the distance between two 3D floating-point points `v1` and `v2`. The distance is the length of the vector `v2 - v1`, i.e., sqrt((v2.x - v1.x)² + (v2.y - v1.y)² + (v2.z - v1.z)²)
|descriptionEnd| */
f32 vec3f_dist(Vec3f v1, Vec3f v2);

#endif // MATH_UTIL_H

