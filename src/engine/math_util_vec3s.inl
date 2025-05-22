/* THIS FILE IS AUTO-GENERATED */
/*   DO NOT EDIT IT MANUALLY   */

#pragma once

/* |description|
Sets the components of the 3D short integer vector `v` to 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_zero(Vec3s v) {
    memset(v, 0, sizeof(Vec3s));
    return v;
}

/* |description|
Copies the contents of a 3D short integer vector (`src`) into another 3D short integer vector (`dest`)
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_copy(Vec3s dest, Vec3s src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}

/* |description|
Sets the values of the 3D short integer vector `dest` to the given x, y, and z values
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_set(Vec3s dest, s16 x, s16 y, s16 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return dest;
}

/* |description|
Adds the components of the 3D short integer vector `a` to `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_add(Vec3s dest, Vec3s a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return dest;
}

/* |description|
Adds the components of two 3D short integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_sum(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return dest;
}

/* |description|
Subtracts the components of the 3D short integer vector `a` from `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_sub(Vec3s dest, Vec3s a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    dest[2] -= a[2];
    return dest;
}

/* |description|
Subtracts the components of the 3D short integer vector `b` from the components of `a` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_dif(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    return dest;
}

/* |description|
Multiplies each component of the 3D short integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_mul(Vec3s dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    dest[2] *= a;
    return dest;
}

/* |description|
Multiplies the components of the 3D short integer vector `dest` with the components of `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_mult(Vec3s dest, Vec3s a) {
    dest[0] *= a[0];
    dest[1] *= a[1];
    dest[2] *= a[2];
    return dest;
}

/* |description|
Multiplies the components of two 3D short integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_prod(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
    dest[2] = a[2] * b[2];
    return dest;
}

/* |description|
Divides each component of the 3D short integer vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_div(Vec3s dest, f32 a) {
    if (a == 0) { return dest; }
    dest[0] /= a;
    dest[1] /= a;
    dest[2] /= a;
    return dest;
}

/* |description|
Calculates the length (magnitude) of the 3D short integer vector `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3s_length(Vec3s a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

/* |description|
Normalizes the 3D short integer vector `v` so that its length (magnitude) becomes 1, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_normalize(Vec3s v) {
    f32 mag = vec3s_length(v);
    vec3s_div(v, mag);
    return v;
}

/* |description|
Sets the length (magnitude) of 3D short integer vector `v`, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_set_magnitude(Vec3s v, f32 mag) {
    vec3s_normalize(v);
    vec3s_mul(v, mag);
    return v;
}

/* |description|
Computes the dot product of the two 3D short integer vectors `a` and `b`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3s_dot(Vec3s a, Vec3s b) {
    return (f32) (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/* |description|
Computes the cross product of two 3D short integer vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_cross(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[1] * b[2] - b[1] * a[2];
    dest[1] = a[2] * b[0] - b[2] * a[0];
    dest[2] = a[0] * b[1] - b[0] * a[1];
    return dest;
}

/* |description|
Takes two 3D short integer vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, adds the scaled vectors together and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3s_combine(Vec3s dest, Vec3s vecA, Vec3s vecB, f32 sclA, f32 sclB) {
    dest[0] = vecA[0] * sclA + vecB[0] * sclB;
    dest[1] = vecA[1] * sclA + vecB[1] * sclB;
    dest[2] = vecA[2] * sclA + vecB[2] * sclB;
    return dest;
}

/* |description|
Calculates the distance between two 3D short integer vectors `v1` and `v2`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3s_dist(Vec3s v1, Vec3s v2) {
    Vec3s diff;
    vec3s_dif(diff, v1, v2);
    return vec3s_length(diff);
}

/* |description|
Calculates the horizontal distance between two 3D short integer vectors `v1` and `v2`, as if their y component was 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3s_hdist(Vec3s v1, Vec3s v2) {
    Vec3s hdiff = { (s16) (v2[0] - v1[0]), 0, (s16) (v2[2] - v1[2]) };
    return vec3s_length(hdiff);
}

/* |description|
Returns `true` if all components of the 3D short integer vector `v` are zero
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool vec3s_is_zero(Vec3s v) {
    return memcmp(v, gVec3sZero, sizeof(Vec3s)) == 0;
}

/* |description|
Converts a 3D short integer vector `a` into a 3D floating-point vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3s_to_vec3f(Vec3f dest, Vec3s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
    return dest;
}

/* |description|
Converts a 3D short integer vector `a` into a 3D integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3s_to_vec3i(Vec3i dest, Vec3s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
    return dest;
}
