#ifndef SMLUA_MATH_UTILS_H
#define SMLUA_MATH_UTILS_H

f32 sm64_to_radians(s16 sm64_angle);
s16 radians_to_sm64(f32 radians_angle);
f32 sm64_to_degrees(s16 sm64_angle);
s16 degrees_to_sm64(f32 degrees_angle);
f32 fast_hypot(f32 a, f32 b);
s32 clamp(s32 a, s32 b, s32 c);
f32 clampf(f32 a, f32 b, f32 c);

#endif // SMLUA_MATH_UTILS_H

