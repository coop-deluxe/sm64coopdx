/*
.inl files are for inlined functions and function templates.

It's best to put them in this file so they can be recompiled if needed.

Credit to PeachyPeach, Isaac0, Blockyyy, and others for suggestions
optimizations and bug reports.
*/

#ifndef MATH_UTIL_MAT4_INL
#define MATH_UTIL_MAT4_INL

/* |description|
Sets the 4x4 floating-point matrix `mtx` to all zeros.
Unless you really need this-It's reccomended to use mtxf_identity instead.
|descriptionEnd| */
INLINE OPTIMIZE_O3 void mtxf_zero(Mat4 mtx) {
    memset(mtx, 0, sizeof(Mat4));
}

/* |description|
Copies the 4x4 floating-point matrix `src` into `dest`. After this operation, `dest` contains the same matrix values as `src`
|descriptionEnd| */
INLINE OPTIMIZE_O3 void mtxf_copy(Mat4 dest, Mat4 src) {
    memcpy(dest, src, sizeof(Mat4));
}

/* |description|
Sets the 4x4 floating-point matrix `mtx` to the identity matrix. The identity matrix leaves points unchanged when they are transformed by it which is useful for matrix math
|descriptionEnd| */
INLINE OPTIMIZE_O3 void mtxf_identity(Mat4 mtx) {
    mtxf_copy(mtx, gMat4Identity);
}

/* |description|
Applies a translation to the 4x4 floating-point matrix `dest` by adding the coordinates in the 3D floating-point vector `b`. This shifts any transformed point by `b`
|descriptionEnd| */
INLINE OPTIMIZE_O3 void mtxf_translate(Mat4 dest, Vec3f b) {
    mtxf_identity(dest);
    vec3f_copy(dest[3], b);
}

/* |description|
Scales the 4x4 floating-point matrix `mtx` by the scaling factors found in the 3D floating-point vector `s`, and stores the result in `dest`. This enlarges or shrinks objects in 3D space
|descriptionEnd| */
INLINE OPTIMIZE_O3 void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s) {
    mtxf_copy(dest, mtx);
    vec3f_mul(dest[0], s[0]);
    vec3f_mul(dest[1], s[1]);
    vec3f_mul(dest[2], s[2]);
}

/* |description|
Converts the floating-point matrix `src` into a fixed-point (integer-based) matrix suitable for the `Mtx` format, and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 void mtxf_to_mtx(Mtx *dest, Mat4 src) {
    mtxf_copy(dest->m, src);
}

#endif // MATH_UTIL_MAT4_INL
