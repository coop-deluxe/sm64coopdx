#ifndef UTILS_MISC_H
#define UTILS_MISC_H

#include <stdio.h>
#include "types.h"
#include "PR/gbi.h"

float smoothstep(float edge0, float edge1, float x);
void update_all_mario_stars(void);

f32 clock_elapsed(void);
f64 clock_elapsed_f64(void);
u32 clock_elapsed_ticks(void);

void file_get_line(char* buffer, size_t maxLength, FILE* fp);

f32 delta_interpolate_f32(f32 start, f32 end, f32 delta);
void delta_interpolate_vectors_s16(Vec3s res, Vec3s a, Vec3s b, f32 delta);
void delta_interpolate_mtx(Mtx* out, Mtx* a, Mtx* b, f32 delta);

#endif