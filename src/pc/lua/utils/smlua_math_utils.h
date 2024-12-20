#ifndef SMLUA_MATH_UTILS_H
#define SMLUA_MATH_UTILS_H

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

#if defined(sqr)
#undef sqr
#endif

// these are also defined in math_util.h as macros

/* |description|Finds the minimum of two signed 32-bit integers|descriptionEnd| */
s32 min(s32 a, s32 b);

/* |description|Finds the maximum of two signed 32-bit integers|descriptionEnd| */
s32 max(s32 a, s32 b);

/* |description|Computes the square of a signed 32-bit integer|descriptionEnd| */
s32 sqr(s32 x);

/* |description|Finds the minimum of two floating-point numbers|descriptionEnd| */
f32 minf(f32 a, f32 b);

/* |description|Finds the maximum of two floating-point numbers|descriptionEnd| */
f32 maxf(f32 a, f32 b);

/* |description|Computes the square of a floating-point number|descriptionEnd| */
f32 sqrf(f32 x);

/* |description|Converts an angle from SM64 format to radians|descriptionEnd| */
f32 sm64_to_radians(s16 sm64Angle);

/* |description|Converts an angle from radians to SM64 format|descriptionEnd| */
s16 radians_to_sm64(f32 radiansAngle);

/* |description|Converts an angle from SM64 format to degrees|descriptionEnd| */
f32 sm64_to_degrees(s16 sm64Angle);

/* |description|Converts an angle from degrees to SM64 format|descriptionEnd| */
s16 degrees_to_sm64(f32 degreesAngle);

/* |description|Computes the hypotenuse of a right triangle given sides `a` and `b` using the Pythagorean theorem|descriptionEnd| */
f32 hypotf(f32 a, f32 b);

/* |description|Clamps a signed 32-bit integer `a` between bounds `b` (minimum) and `c` (maximum)|descriptionEnd| */
s32 clamp(s32 a, s32 b, s32 c);

/* |description|Clamps a floating-point number `a` between bounds `b` (minimum) and `c` (maximum)|descriptionEnd| */
f32 clampf(f32 a, f32 b, f32 c);

#endif // SMLUA_MATH_UTILS_H

