#include "sm64.h"
#include "types.h"

f32 sm64_to_radians(s16 sm64Angle) {
    return sm64Angle * M_PI / 0x8000;
}

s16 radians_to_sm64(f32 radiansAngle) {
    return radiansAngle * 0x8000 / M_PI;
}

f32 sm64_to_degrees(s16 sm64Angle) {
    return sm64Angle * 180.0f / 0x8000;
}

s16 degrees_to_sm64(f32 degreesAngle) {
    return degreesAngle * 0x8000 / 180.0f;
}

f32 hypotf(f32 a, f32 b) {
    return sqrtf(a * a + b * b);
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
