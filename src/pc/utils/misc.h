#ifndef UTILS_MISC_H
#define UTILS_MISC_H

#include <stdio.h>
#include "types.h"
#include "PR/gbi.h"

float smoothstep(float edge0, float edge1, float x);
/* |description|Updates every Mario state's star count with the save file total star count|descriptionEnd| */
void update_all_mario_stars(void);

f32 clock_elapsed(void);
f64 clock_elapsed_f64(void);
u32 clock_elapsed_ticks(void);

void file_get_line(char* buffer, size_t maxLength, FILE* fp);

f32 delta_interpolate_f32(f32 start, f32 end, f32 delta);
s32 delta_interpolate_s32(s32 a, s32 b, f32 delta);
void delta_interpolate_vec3f(Vec3f res, Vec3f a, Vec3f b, f32 delta);
void delta_interpolate_vec3s(Vec3s res, Vec3s a, Vec3s b, f32 delta);
void delta_interpolate_normal(s8* res, s8* a, s8* b, f32 delta);
void delta_interpolate_rgba(u8* res, u8* a, u8* b, f32 delta);
void delta_interpolate_mtx(Mtx* out, Mtx* a, Mtx* b, f32 delta);
void detect_and_skip_mtx_interpolation(Mtx** mtxPrev, Mtx** mtx);

void str_seperator_concat(char *output_buffer, int buffer_size, char** strings, int num_strings, char* seperator);

#endif