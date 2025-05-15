/*
.inl files are for inlined functions and function templates.

It's best to put them in this file so they can be recompiled if needed.

Credit to PeachyPeach, Isaac0, Blockyyy, and others for suggestions
optimizations and bug reports.
*/

#ifndef MATH_UTIL_INL
#define MATH_UTIL_INL

/*
Vec3f Functions
*/

/**
 * Copy vector 'src' to 'dest'.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_copy(Vec3f dest, Vec3f src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}

/**
 * Set vector 'dest' to (x, y, z).
 */
INLINE OPTIMIZE_O3 f32 *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return dest;
}

/**
 * Add vector 'a' to 'dest'.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_add(Vec3f dest, Vec3f a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return dest;
}

/**
 * Make 'dest' the sum of vectors a and b.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return dest;
}

/**
 * Subtracts vector a from 'dest'.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_sub(Vec3f dest, Vec3f a) {
    if (!dest || !a) { return NULL; }
    dest[0] -= a[0];
    dest[1] -= a[1];
    dest[2] -= a[2];
    return dest;
}

/**
 * Make 'dest' the difference of vectors a and b.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_dif(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    return dest;
}

/**
 * Multiply vector 'dest' by a.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_mul(Vec3f dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    dest[2] *= a;
    return dest;
}

/**
 * Divides vector 'dest' by a.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_div(Vec3f dest, f32 a) {
    dest[0] /= a;
    dest[1] /= a;
    dest[2] /= a;
    return dest;
}

/**
 * Make vector 'dest' the cross product of vectors a and b.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[1] * b[2] - b[1] * a[2];
    dest[1] = a[2] * b[0] - b[2] * a[0];
    dest[2] = a[0] * b[1] - b[0] * a[1];
    return dest;
}

/**
 * Normalizes each component of the 3D floating-point vector 'v'.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_normalize2(Vec3f v) {
    float s = vec3f_length(v);
    vec3f_div(v, s);
    return v;
}

/**
 * Get length of vector 'a'.
 */
INLINE OPTIMIZE_O3 f32 vec3f_length(Vec3f a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

/**
 * Get dot product of vectors 'a' and 'b'.
 */
INLINE OPTIMIZE_O3 f32 vec3f_dot(Vec3f a, Vec3f b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

/**
 * Takes respective scales of vecA and vecB, and sums them.
 */
INLINE OPTIMIZE_O3 f32 *vec3f_combine(Vec3f dest, Vec3f vecA, Vec3f vecB, f32 sclA, f32 sclB) {
    for (s32 i = 0; i < 3; ++i) {
        dest[i] = vecA[i] * sclA + vecB[i] * sclB;
    }
    return dest;
}

/**
 * Calculates the distance between point 'v1' and 'v2'.
 */
INLINE OPTIMIZE_O3 f32 vec3f_dist(Vec3f v1, Vec3f v2) {
    Vec3f diff;
    vec3f_dif(diff, v1, v2);
    return vec3f_length(diff);
}

INLINE OPTIMIZE_O3 f32 *vec3f_zero(Vec3f v) {
    return vec3f_set(v, 0, 0, 0);
}

/**
 * Convert float vector a to a short vector 'dest' by rounding the components
 * to the nearest integer.
 */
INLINE OPTIMIZE_O3 s16 *vec3f_to_vec3s(Vec3s dest, Vec3f a) {
    // add/subtract 0.5 in order to round to the nearest s32 instead of truncating
    dest[0] = a[0] + ((a[0] > 0) ? 0.5f : -0.5f);
    dest[1] = a[1] + ((a[1] > 0) ? 0.5f : -0.5f);
    dest[2] = a[2] + ((a[2] > 0) ? 0.5f : -0.5f);
    return dest;
}

/*
Vec3s Functions
*/

/**
 * Copy vector src to dest.
 */
INLINE OPTIMIZE_O3 s16 *vec3s_copy(Vec3s dest, Vec3s src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}

/**
 * Set vector 'dest' to (x, y, z).
 */
INLINE OPTIMIZE_O3 s16 *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return dest;
}

/**
 * Add vector a to 'dest'.
 */
INLINE OPTIMIZE_O3 s16 *vec3s_add(Vec3s dest, Vec3s a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return dest;
}

/**
 * Make 'dest' the sum of vectors a and b.
 */
INLINE OPTIMIZE_O3 s16 *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return dest;
}

/**
 * Subtracts vector a from 'dest'.
 */
INLINE OPTIMIZE_O3 s16 *vec3s_sub(Vec3s dest, Vec3s a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    dest[2] -= a[2];
    return dest;
}

/**
 * Make 'dest' the difference of vectors a and b.
 */
INLINE OPTIMIZE_O3 s16 *vec3s_dif(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    return dest;
}

/**
 * Multiply vector 'dest' by a.
 */
INLINE OPTIMIZE_O3 s16 *vec3s_mul(Vec3s dest, s16 a) {
    dest[0] *= a;
    dest[1] *= a;
    dest[2] *= a;
    return dest;
}

/**
 * Divides vector 'dest' by a.
 */
INLINE OPTIMIZE_O3 s16 *vec3s_div(Vec3s dest, s16 a) {
    dest[0] /= a;
    dest[1] /= a;
    dest[2] /= a;
    return dest;
}

/**
 * Get length of vector 'a'.
 */
INLINE OPTIMIZE_O3 s32 vec3s_length(Vec3s a) {
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

/**
 * Calculates the distance between point 'v1' and 'v2'.
 */
INLINE OPTIMIZE_O3 s32 vec3s_dist(Vec3s v1, Vec3s v2) {
    Vec3s diff;
    vec3s_dif(diff, v1, v2);
    return vec3s_length(diff);
}

INLINE OPTIMIZE_O3 s16 *vec3s_zero(Vec3s v) {
    return vec3s_set(v, 0, 0, 0);
}

/**
 * Convert short vector a to float vector 'dest'.
 */
INLINE OPTIMIZE_O3 f32 *vec3s_to_vec3f(Vec3f dest, Vec3s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
    return dest;
}

/*
Mat4 Functions
*/

/**
 * Copy matrix 'src' to 'dest'.
 */
INLINE OPTIMIZE_O3 void mtxf_copy(Mat4 dest, Mat4 src) {
#ifdef __SSE__
   __m128 r1 = _mm_load_ps(src[0]); // Load floats into 128-bits
   __m128 r2 = _mm_load_ps(src[1]);
   __m128 r3 = _mm_load_ps(src[2]);
   __m128 r4 = _mm_load_ps(src[3]);
   _mm_store_ps(dest[0], r1); // Stores 128 bits into a float[4].
   _mm_store_ps(dest[1], r2);
   _mm_store_ps(dest[2], r3);
   _mm_store_ps(dest[3], r4);
#else
    u32 *d = (u32 *) dest;
    u32 *s = (u32 *) src;

    for (s32 i = 0; i < 16; i++) {
        *d++ = *s++;
    }
#endif
}

/**
 * Set mtx to the identity matrix
 */
INLINE OPTIMIZE_O3 void mtxf_identity(Mat4 mtx) {
    mtxf_copy(mtx, gMat4Identity);
}

/**
 * Set dest to a translation matrix of vector b
 */
INLINE OPTIMIZE_O3 void mtxf_translate(Mat4 dest, Vec3f b) {
    mtxf_identity(dest);
    vec3f_copy(dest[3], b);
}

/**
 * Set matrix 'dest' to 'mtx' scaled by vector s
 */
INLINE OPTIMIZE_O3 void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s) {
    mtxf_copy(dest, mtx);
    vec3f_mul(dest[0], s[0]);
    vec3f_mul(dest[1], s[1]);
    vec3f_mul(dest[2], s[2]);
}

/**
 * Set mtx to all zeros.
 */
INLINE OPTIMIZE_O3 void mtxf_zero(Mat4 mtx) {
    mtxf_copy(mtx, gMat4Zero);
}

#endif // MATH_UTIL_INL