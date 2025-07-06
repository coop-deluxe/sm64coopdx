/* THIS FILE IS AUTO-GENERATED */
/*   DO NOT EDIT IT MANUALLY   */

#pragma once

/* |description|
Sets the components of the 2D floating-point vector `v` to 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_zero(OUT Vec2f v) {
    memset(v, 0, sizeof(Vec2f));
    return v;
}

/* |description|
Copies the contents of a 2D floating-point vector (`src`) into another 2D floating-point vector (`dest`)
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_copy(OUT Vec2f dest, Vec2f src) {
    dest[0] = src[0];
    dest[1] = src[1];
    return dest;
}

/* |description|
Sets the values of the 2D floating-point vector `dest` to the given x and y values
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_set(OUT Vec2f dest, f32 x, f32 y) {
    dest[0] = x;
    dest[1] = y;
    return dest;
}

/* |description|
Adds the components of the 2D floating-point vector `a` to `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_add(OUT Vec2f dest, Vec2f a) {
    dest[0] += a[0];
    dest[1] += a[1];
    return dest;
}

/* |description|
Adds the components of two 2D floating-point vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_sum(OUT Vec2f dest, Vec2f a, Vec2f b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    return dest;
}

/* |description|
Subtracts the components of the 2D floating-point vector `a` from `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_sub(OUT Vec2f dest, Vec2f a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    return dest;
}

/* |description|
Subtracts the components of the 2D floating-point vector `b` from the components of `a` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_dif(OUT Vec2f dest, Vec2f a, Vec2f b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    return dest;
}

/* |description|
Multiplies each component of the 2D floating-point vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_mul(OUT Vec2f dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    return dest;
}

/* |description|
Multiplies the components of the 2D floating-point vector `dest` with the components of `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_mult(OUT Vec2f dest, Vec2f a) {
    dest[0] *= a[0];
    dest[1] *= a[1];
    return dest;
}

/* |description|
Multiplies the components of two 2D floating-point vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_prod(OUT Vec2f dest, Vec2f a, Vec2f b) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
    return dest;
}

/* |description|
Divides each component of the 2D floating-point vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_div(OUT Vec2f dest, f32 a) {
    if (a == 0) { return dest; }
    dest[0] /= a;
    dest[1] /= a;
    return dest;
}

/* |description|
Calculates the length (magnitude) of the 2D floating-point vector `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2f_length(Vec2f a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1]);
}

/* |description|
Normalizes the 2D floating-point vector `v` so that its length (magnitude) becomes 1, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_normalize(OUT Vec2f v) {
    f32 mag = vec2f_length(v);
    vec2f_div(v, mag);
    return v;
}

/* |description|
Sets the length (magnitude) of 2D floating-point vector `v`, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_set_magnitude(OUT Vec2f v, f32 mag) {
    vec2f_normalize(v);
    vec2f_mul(v, mag);
    return v;
}

/* |description|
Computes the dot product of the two 2D floating-point vectors `a` and `b`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2f_dot(Vec2f a, Vec2f b) {
    return (f32) (a[0] * b[0] + a[1] * b[1]);
}

/* |description|
Takes two 2D floating-point vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, adds the scaled vectors together and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2f_combine(OUT Vec2f dest, Vec2f vecA, Vec2f vecB, f32 sclA, f32 sclB) {
    dest[0] = vecA[0] * sclA + vecB[0] * sclB;
    dest[1] = vecA[1] * sclA + vecB[1] * sclB;
    return dest;
}

/* |description|
Calculates the distance between two 2D floating-point vectors `v1` and `v2`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2f_dist(Vec2f v1, Vec2f v2) {
    Vec2f diff;
    vec2f_dif(diff, v1, v2);
    return vec2f_length(diff);
}

/* |description|
Returns `true` if all components of the 2D floating-point vector `v` are zero
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool vec2f_is_zero(Vec2f v) {
    return memcmp(v, gVec2fZero, sizeof(Vec2f)) == 0;
}

/* |description|
Converts a 2D floating-point vector `a` into a 2D integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2f_to_vec2i(OUT Vec2i dest, Vec2f a) {
    dest[0] = a[0] + ((a[0] > 0) ? 0.5f : -0.5f);
    dest[1] = a[1] + ((a[1] > 0) ? 0.5f : -0.5f);
    return dest;
}

/* |description|
Converts a 2D floating-point vector `a` into a 2D short integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2f_to_vec2s(OUT Vec2s dest, Vec2f a) {
    dest[0] = a[0] + ((a[0] > 0) ? 0.5f : -0.5f);
    dest[1] = a[1] + ((a[1] > 0) ? 0.5f : -0.5f);
    return dest;
}
