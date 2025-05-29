/* THIS FILE IS AUTO-GENERATED */
/*   DO NOT EDIT IT MANUALLY   */

#pragma once

/* |description|
Sets the components of the 3D integer vector `v` to 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_zero(Vec3i v) {
    memset(v, 0, sizeof(Vec3i));
    return v;
}

/* |description|
Copies the contents of a 3D integer vector (`src`) into another 3D integer vector (`dest`)
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_copy(Vec3i dest, Vec3i src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}

/* |description|
Sets the values of the 3D integer vector `dest` to the given x, y, and z values
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_set(Vec3i dest, s32 x, s32 y, s32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return dest;
}

/* |description|
Adds the components of the 3D integer vector `a` to `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_add(Vec3i dest, Vec3i a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return dest;
}

/* |description|
Adds the components of two 3D integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_sum(Vec3i dest, Vec3i a, Vec3i b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return dest;
}

/* |description|
Subtracts the components of the 3D integer vector `a` from `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_sub(Vec3i dest, Vec3i a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    dest[2] -= a[2];
    return dest;
}

/* |description|
Subtracts the components of the 3D integer vector `b` from the components of `a` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_dif(Vec3i dest, Vec3i a, Vec3i b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    return dest;
}

/* |description|
Multiplies each component of the 3D integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_mul(Vec3i dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    dest[2] *= a;
    return dest;
}

/* |description|
Multiplies the components of the 3D integer vector `dest` with the components of `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_mult(Vec3i dest, Vec3i a) {
    dest[0] *= a[0];
    dest[1] *= a[1];
    dest[2] *= a[2];
    return dest;
}

/* |description|
Multiplies the components of two 3D integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_prod(Vec3i dest, Vec3i a, Vec3i b) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
    dest[2] = a[2] * b[2];
    return dest;
}

/* |description|
Divides each component of the 3D integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_div(Vec3i dest, f32 a) {
    if (a == 0) { return dest; }
    dest[0] /= a;
    dest[1] /= a;
    dest[2] /= a;
    return dest;
}

/* |description|
Calculates the length (magnitude) of the 3D integer vector `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3i_length(Vec3i a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

/* |description|
Normalizes the 3D integer vector `v` so that its length (magnitude) becomes 1, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_normalize(Vec3i v) {
    f32 mag = vec3i_length(v);
    vec3i_div(v, mag);
    return v;
}

/* |description|
Sets the length (magnitude) of 3D integer vector `v`, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_set_magnitude(Vec3i v, f32 mag) {
    vec3i_normalize(v);
    vec3i_mul(v, mag);
    return v;
}

/* |description|
Computes the dot product of the two 3D integer vectors `a` and `b`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3i_dot(Vec3i a, Vec3i b) {
    return (f32) (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/* |description|
Computes the cross product of two 3D integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_cross(Vec3i dest, Vec3i a, Vec3i b) {
    dest[0] = a[1] * b[2] - b[1] * a[2];
    dest[1] = a[2] * b[0] - b[2] * a[0];
    dest[2] = a[0] * b[1] - b[0] * a[1];
    return dest;
}

/* |description|
Takes two 3D integer vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, adds the scaled vectors together and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3i_combine(Vec3i dest, Vec3i vecA, Vec3i vecB, f32 sclA, f32 sclB) {
    dest[0] = vecA[0] * sclA + vecB[0] * sclB;
    dest[1] = vecA[1] * sclA + vecB[1] * sclB;
    dest[2] = vecA[2] * sclA + vecB[2] * sclB;
    return dest;
}

/* |description|
Calculates the distance between two 3D integer vectors `v1` and `v2`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3i_dist(Vec3i v1, Vec3i v2) {
    Vec3i diff;
    vec3i_dif(diff, v1, v2);
    return vec3i_length(diff);
}

/* |description|
Calculates the horizontal distance between two 3D integer vectors `v1` and `v2`, as if their y component was 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3i_hdist(Vec3i v1, Vec3i v2) {
    Vec3i hdiff = { (s32) (v2[0] - v1[0]), 0, (s32) (v2[2] - v1[2]) };
    return vec3i_length(hdiff);
}

/* |description|
Returns `true` if all components of the 3D integer vector `v` are zero
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool vec3i_is_zero(Vec3i v) {
    return memcmp(v, gVec3iZero, sizeof(Vec3i)) == 0;
}

/* |description|
Converts a 3D integer vector `a` into a 3D floating-point vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3i_to_vec3f(Vec3f dest, Vec3i a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
    return dest;
}

/* |description|
Converts a 3D integer vector `a` into a 3D short integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3i_to_vec3s(Vec3s dest, Vec3i a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
    return dest;
}
