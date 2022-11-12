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

s32 min(s32 a, s32 b);
f32 minf(f32 a, f32 b);

s32 max(s32 a, s32 b);
f32 maxf(f32 a, f32 b);

s32 sqr(s32 x);
f32 sqrf(f32 x);

s32 clamp(s32 a, s32 b, s32 c);
f32 clampf(f32 a, f32 b, f32 c);

#endif
