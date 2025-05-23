/*
.inl files are for inlined functions and function templates.

It's best to put them in this file so they can be recompiled if needed.

Credit to PeachyPeach, Isaac0, Blockyyy, and others for suggestions
optimizations and bug reports.
*/

#ifndef MATH_UTIL_INL
#define MATH_UTIL_INL

/* |description|
Returns `replacement` if `replacement` is not zero. Otherwise, returns `value`
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 replace_value_if_not_zero(f32 value, f32 replacement) {
    if (replacement != 0) {
        return replacement;
    }
    return value;
}

/* |description|
Converts an angle from SM64 format to radians
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 sm64_to_radians(s16 sm64Angle) {
    return sm64Angle * M_PI / 0x8000;
}

/* |description|
Converts an angle from radians to SM64 format
|descriptionEnd| */
INLINE OPTIMIZE_O3 s16 radians_to_sm64(f32 radiansAngle) {
    return radiansAngle * 0x8000 / M_PI;
}

/* |description|
Converts an angle from SM64 format to degrees
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 sm64_to_degrees(s16 sm64Angle) {
    return sm64Angle * 180.0f / 0x8000;
}

/* |description|
Converts an angle from degrees to SM64 format
|descriptionEnd| */
INLINE OPTIMIZE_O3 s16 degrees_to_sm64(f32 degreesAngle) {
    return degreesAngle * 0x8000 / 180.0f;
}

#endif // MATH_UTIL_INL