/* THIS FILE IS AUTO-GENERATED */
/*   DO NOT EDIT IT MANUALLY   */

#pragma once

/* |description|
Sets the components of the 2D short integer vector `v` to 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_zero(OUT Vec2s v) {
    memset(v, 0, sizeof(Vec2s));
    return v;
}

/* |description|
Copies the contents of a 2D short integer vector (`src`) into another 2D short integer vector (`dest`)
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_copy(OUT Vec2s dest, Vec2s src) {
    dest[0] = src[0];
    dest[1] = src[1];
    return dest;
}

/* |description|
Sets the values of the 2D short integer vector `dest` to the given x and y values
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_set(OUT Vec2s dest, s16 x, s16 y) {
    dest[0] = x;
    dest[1] = y;
    return dest;
}

/* |description|
Adds the components of the 2D short integer vector `a` to `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_add(OUT Vec2s dest, Vec2s a) {
    dest[0] += a[0];
    dest[1] += a[1];
    return dest;
}

/* |description|
Adds the components of two 2D short integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_sum(OUT Vec2s dest, Vec2s a, Vec2s b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    return dest;
}

/* |description|
Subtracts the components of the 2D short integer vector `a` from `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_sub(OUT Vec2s dest, Vec2s a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    return dest;
}

/* |description|
Subtracts the components of the 2D short integer vector `b` from the components of `a` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_dif(OUT Vec2s dest, Vec2s a, Vec2s b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    return dest;
}

/* |description|
Multiplies each component of the 2D short integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_mul(OUT Vec2s dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    return dest;
}

/* |description|
Multiplies the components of the 2D short integer vector `dest` with the components of `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_mult(OUT Vec2s dest, Vec2s a) {
    dest[0] *= a[0];
    dest[1] *= a[1];
    return dest;
}

/* |description|
Multiplies the components of two 2D short integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_prod(OUT Vec2s dest, Vec2s a, Vec2s b) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
    return dest;
}

/* |description|
Divides each component of the 2D short integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_div(OUT Vec2s dest, f32 a) {
    if (a == 0) { return dest; }
    dest[0] /= a;
    dest[1] /= a;
    return dest;
}

/* |description|
Calculates the length (magnitude) of the 2D short integer vector `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2s_length(Vec2s a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1]);
}

/* |description|
Normalizes the 2D short integer vector `v` so that its length (magnitude) becomes 1, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_normalize(OUT Vec2s v) {
    f32 mag = vec2s_length(v);
    vec2s_div(v, mag);
    return v;
}

/* |description|
Sets the length (magnitude) of 2D short integer vector `v`, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_set_magnitude(OUT Vec2s v, f32 mag) {
    vec2s_normalize(v);
    vec2s_mul(v, mag);
    return v;
}

/* |description|
Computes the dot product of the two 2D short integer vectors `a` and `b`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2s_dot(Vec2s a, Vec2s b) {
    return (f32) (a[0] * b[0] + a[1] * b[1]);
}

/* |description|
Takes two 2D short integer vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, adds the scaled vectors together and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2s_combine(OUT Vec2s dest, Vec2s vecA, Vec2s vecB, f32 sclA, f32 sclB) {
    dest[0] = vecA[0] * sclA + vecB[0] * sclB;
    dest[1] = vecA[1] * sclA + vecB[1] * sclB;
    return dest;
}

/* |description|
Calculates the distance between two 2D short integer vectors `v1` and `v2`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2s_dist(Vec2s v1, Vec2s v2) {
    Vec2s diff;
    vec2s_dif(diff, v1, v2);
    return vec2s_length(diff);
}

/* |description|
Returns `true` if all components of the 2D short integer vector `v` are zero
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool vec2s_is_zero(Vec2s v) {
    return memcmp(v, gVec2sZero, sizeof(Vec2s)) == 0;
}

/* |description|
Converts a 2D short integer vector `a` into a 2D floating-point vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2s_to_vec2f(OUT Vec2f dest, Vec2s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    return dest;
}

/* |description|
Converts a 2D short integer vector `a` into a 2D integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2s_to_vec2i(OUT Vec2i dest, Vec2s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    return dest;
}
