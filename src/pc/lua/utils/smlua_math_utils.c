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
    return __builtin_sqrtf(a * a + b * b);
}

f32 minf(f32 a, f32 b) { 
    return __builtin_fminf(a, b); 
}

f32 maxf(f32 a, f32 b) { 
    return __builtin_fmaxf(a, b);
}

s32 min(s32 a, s32 b){
    return ((a) <= (b) ? (a) : (b));
}

s32 max(s32 a, s32 b){
    return ((a) >= (b) ? (a) : (b));
}

s32 sqr(s32 x) {
    return x * x;
}

f32 sqrf(f32 x) {
    return x * x;
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
