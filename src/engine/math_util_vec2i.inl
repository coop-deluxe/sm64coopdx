/* THIS FILE IS AUTO-GENERATED */
/*   DO NOT EDIT IT MANUALLY   */

#pragma once

/* |description|
Sets the components of the 2D integer vector `v` to 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_zero(OUT Vec2i v) {
    memset(v, 0, sizeof(Vec2i));
    return v;
}

/* |description|
Copies the contents of a 2D integer vector (`src`) into another 2D integer vector (`dest`)
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_copy(OUT Vec2i dest, Vec2i src) {
    dest[0] = src[0];
    dest[1] = src[1];
    return dest;
}

/* |description|
Sets the values of the 2D integer vector `dest` to the given x and y values
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_set(OUT Vec2i dest, s32 x, s32 y) {
    dest[0] = x;
    dest[1] = y;
    return dest;
}

/* |description|
Adds the components of the 2D integer vector `a` to `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_add(OUT Vec2i dest, Vec2i a) {
    dest[0] += a[0];
    dest[1] += a[1];
    return dest;
}

/* |description|
Adds the components of two 2D integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_sum(OUT Vec2i dest, Vec2i a, Vec2i b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    return dest;
}

/* |description|
Subtracts the components of the 2D integer vector `a` from `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_sub(OUT Vec2i dest, Vec2i a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    return dest;
}

/* |description|
Subtracts the components of the 2D integer vector `b` from the components of `a` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_dif(OUT Vec2i dest, Vec2i a, Vec2i b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    return dest;
}

/* |description|
Multiplies each component of the 2D integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_mul(OUT Vec2i dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    return dest;
}

/* |description|
Multiplies the components of the 2D integer vector `dest` with the components of `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_mult(OUT Vec2i dest, Vec2i a) {
    dest[0] *= a[0];
    dest[1] *= a[1];
    return dest;
}

/* |description|
Multiplies the components of two 2D integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_prod(OUT Vec2i dest, Vec2i a, Vec2i b) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
    return dest;
}

/* |description|
Divides each component of the 2D integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_div(OUT Vec2i dest, f32 a) {
    if (a == 0) { return dest; }
    dest[0] /= a;
    dest[1] /= a;
    return dest;
}

/* |description|
Calculates the length (magnitude) of the 2D integer vector `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2i_length(Vec2i a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1]);
}

/* |description|
Normalizes the 2D integer vector `v` so that its length (magnitude) becomes 1, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_normalize(OUT Vec2i v) {
    f32 mag = vec2i_length(v);
    vec2i_div(v, mag);
    return v;
}

/* |description|
Sets the length (magnitude) of 2D integer vector `v`, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_set_magnitude(OUT Vec2i v, f32 mag) {
    vec2i_normalize(v);
    vec2i_mul(v, mag);
    return v;
}

/* |description|
Computes the dot product of the two 2D integer vectors `a` and `b`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2i_dot(Vec2i a, Vec2i b) {
    return (f32) (a[0] * b[0] + a[1] * b[1]);
}

/* |description|
Takes two 2D integer vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, adds the scaled vectors together and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2ip vec2i_combine(OUT Vec2i dest, Vec2i vecA, Vec2i vecB, f32 sclA, f32 sclB) {
    dest[0] = vecA[0] * sclA + vecB[0] * sclB;
    dest[1] = vecA[1] * sclA + vecB[1] * sclB;
    return dest;
}

/* |description|
Calculates the distance between two 2D integer vectors `v1` and `v2`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec2i_dist(Vec2i v1, Vec2i v2) {
    Vec2i diff;
    vec2i_dif(diff, v1, v2);
    return vec2i_length(diff);
}

/* |description|
Returns `true` if all components of the 2D integer vector `v` are zero
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool vec2i_is_zero(Vec2i v) {
    return memcmp(v, gVec2iZero, sizeof(Vec2i)) == 0;
}

/* |description|
Converts a 2D integer vector `a` into a 2D floating-point vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2fp vec2i_to_vec2f(OUT Vec2f dest, Vec2i a) {
    dest[0] = a[0];
    dest[1] = a[1];
    return dest;
}

/* |description|
Converts a 2D integer vector `a` into a 2D short integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec2sp vec2i_to_vec2s(OUT Vec2s dest, Vec2i a) {
    dest[0] = a[0];
    dest[1] = a[1];
    return dest;
}
