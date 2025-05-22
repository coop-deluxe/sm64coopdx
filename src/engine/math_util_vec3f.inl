/* THIS FILE IS AUTO-GENERATED */
/*   DO NOT EDIT IT MANUALLY   */

#pragma once

/* |description|
Sets the components of the 3D floating-point vector `v` to 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_zero(Vec3f v) {
    memset(v, 0, sizeof(Vec3f));
    return v;
}

/* |description|
Copies the contents of a 3D floating-point vector (`src`) into another 3D floating-point vector (`dest`)
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_copy(Vec3f dest, Vec3f src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return dest;
}

/* |description|
Sets the values of the 3D floating-point vector `dest` to the given x, y, and z values
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_set(Vec3f dest, f32 x, f32 y, f32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return dest;
}

/* |description|
Adds the components of the 3D floating-point vector `a` to `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_add(Vec3f dest, Vec3f a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return dest;
}

/* |description|
Adds the components of two 3D floating-point vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_sum(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return dest;
}

/* |description|
Subtracts the components of the 3D floating-point vector `a` from `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_sub(Vec3f dest, Vec3f a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    dest[2] -= a[2];
    return dest;
}

/* |description|
Subtracts the components of the 3D floating-point vector `b` from the components of `a` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_dif(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    return dest;
}

/* |description|
Multiplies each component of the 3D floating-point vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_mul(Vec3f dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    dest[2] *= a;
    return dest;
}

/* |description|
Multiplies the components of the 3D floating-point vector `dest` with the components of `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_mult(Vec3f dest, Vec3f a) {
    dest[0] *= a[0];
    dest[1] *= a[1];
    dest[2] *= a[2];
    return dest;
}

/* |description|
Multiplies the components of two 3D floating-point vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_prod(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
    dest[2] = a[2] * b[2];
    return dest;
}

/* |description|
Divides each component of the 3D floating-point vector `dest` by the scalar value `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_div(Vec3f dest, f32 a) {
    if (a == 0) { return dest; }
    dest[0] /= a;
    dest[1] /= a;
    dest[2] /= a;
    return dest;
}

/* |description|
Calculates the length (magnitude) of the 3D floating-point vector `a`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3f_length(Vec3f a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

/* |description|
Normalizes the 3D floating-point vector `v` so that its length (magnitude) becomes 1, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_normalize(Vec3f v) {
    f32 mag = vec3f_length(v);
    vec3f_div(v, mag);
    return v;
}

/* |description|
Sets the length (magnitude) of 3D floating-point vector `v`, while retaining its direction
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_set_magnitude(Vec3f v, f32 mag) {
    vec3f_normalize(v);
    vec3f_mul(v, mag);
    return v;
}

/* |description|
Computes the dot product of the two 3D floating-point vectors `a` and `b`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3f_dot(Vec3f a, Vec3f b) {
    return (f32) (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/* |description|
Computes the cross product of two 3D floating-point vectors `a` and `b` and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_cross(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[1] * b[2] - b[1] * a[2];
    dest[1] = a[2] * b[0] - b[2] * a[0];
    dest[2] = a[0] * b[1] - b[0] * a[1];
    return dest;
}

/* |description|
Takes two 3D floating-point vectors `vecA` and `vecB`, multiplies them by `sclA` and `sclB` respectively, adds the scaled vectors together and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3fp vec3f_combine(Vec3f dest, Vec3f vecA, Vec3f vecB, f32 sclA, f32 sclB) {
    dest[0] = vecA[0] * sclA + vecB[0] * sclB;
    dest[1] = vecA[1] * sclA + vecB[1] * sclB;
    dest[2] = vecA[2] * sclA + vecB[2] * sclB;
    return dest;
}

/* |description|
Calculates the distance between two 3D floating-point vectors `v1` and `v2`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3f_dist(Vec3f v1, Vec3f v2) {
    Vec3f diff;
    vec3f_dif(diff, v1, v2);
    return vec3f_length(diff);
}

/* |description|
Calculates the horizontal distance between two 3D floating-point vectors `v1` and `v2`, as if their y component was 0
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 vec3f_hdist(Vec3f v1, Vec3f v2) {
    Vec3f hdiff = { (f32) (v2[0] - v1[0]), 0, (f32) (v2[2] - v1[2]) };
    return vec3f_length(hdiff);
}

/* |description|
Returns `true` if all components of the 3D floating-point vector `v` are zero
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool vec3f_is_zero(Vec3f v) {
    return memcmp(v, gVec3fZero, sizeof(Vec3f)) == 0;
}

/* |description|
Converts a 3D floating-point vector `a` into a 3D integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3ip vec3f_to_vec3i(Vec3i dest, Vec3f a) {
    dest[0] = a[0] + ((a[0] > 0) ? 0.5f : -0.5f);
    dest[1] = a[1] + ((a[1] > 0) ? 0.5f : -0.5f);
    dest[2] = a[2] + ((a[2] > 0) ? 0.5f : -0.5f);
    return dest;
}

/* |description|
Converts a 3D floating-point vector `a` into a 3D short integer vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec3sp vec3f_to_vec3s(Vec3s dest, Vec3f a) {
    dest[0] = a[0] + ((a[0] > 0) ? 0.5f : -0.5f);
    dest[1] = a[1] + ((a[1] > 0) ? 0.5f : -0.5f);
    dest[2] = a[2] + ((a[2] > 0) ? 0.5f : -0.5f);
    return dest;
}
