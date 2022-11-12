#include "sm64.h"
#include "types.h"

s32 min(s32 a, s32 b) {
    return ((a) <= (b) ? (a) : (b));
}

f32 minf(f32 a, f32 b) {
    return ((a) <= (b) ? (a) : (b));
}

s32 max(s32 a, s32 b) {
    return ((a) > (b) ? (a) : (b));
}

f32 maxf(f32 a, f32 b) {
    return ((a) > (b) ? (a) : (b));
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