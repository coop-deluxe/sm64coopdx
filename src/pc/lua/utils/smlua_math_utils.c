#include "sm64.h"
#include "types.h"

f32 sm64_to_radians(s16 sm64_angle) {
    return sm64_angle * M_PI / 0x8000;
}

s16 radians_to_sm64(f32 radians_angle) {
    return radians_angle * 0x8000 / M_PI;
}

f32 sm64_to_degrees(s16 sm64_angle) {
    return sm64_angle * 180.0f / 0x8000;
}

s16 degrees_to_sm64(f32 degrees_angle) {
    return degrees_angle * 0x8000 / 180.0f;
}

f32 fast_hypot(f32 a, f32 b) {
    f32 sum = a * a + b * b; // Fast sqrt derived from fast invsqrt
    u32 i = *(u32 *)&sum; // Bit-level manipulation of float
    i = (i + 0x3f76cf62) >> 1; // Magic number and bit-shift
    f32 result = *(f32 *)&i;
    // Optional: Two iterations of Newton's method for better accuracy
    result = 0.5f * (result + sum / result);
    result = 0.5f * (result + sum / result);
    return result;
}

s32 clamp(s32 a, s32 b, s32 c) {
    if (a < b) { return b; }
    if (a > c) { return c; }
    return a;
}

f32 clampf(f32 a, f32 b, f32 c) {
    if (a < b) { return b; }
    if (a > c) { return c; }
    return a;
}
