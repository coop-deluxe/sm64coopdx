#ifndef UTILS_MISC_H
#define UTILS_MISC_H

#include <stdio.h>
#include "types.h"
#include "PR/gbi.h"

/* |description|Smoothly steps between `edge0` and `edge1` with `x` as delta|descriptionEnd| */
float smooth_step(float edge0, float edge1, float x);
/* |description|Updates every Mario state's star count with the save file total star count|descriptionEnd| */
void update_all_mario_stars(void);

/* |description|Gets the current clock elapsed time|descriptionEnd| */
f32 clock_elapsed(void);
/* |description|Gets the current clock elapsed time with double precision|descriptionEnd| */
f64 clock_elapsed_f64(void);
/* |description|Gets the current clock elapsed time in frames|descriptionEnd| */
u32 clock_elapsed_ticks(void);
/* |description|Checks whether it is the day given|descriptionEnd| */
bool clock_is_date(u8 month, u8 day);

void file_get_line(char* buffer, size_t maxLength, FILE* fp);

/* |description|Linearly interpolates between `a` and `b` with `delta`|descriptionEnd| */
f32 delta_interpolate_f32(f32 a, f32 b, f32 delta);
/* |description|Linearly interpolates between `a` and `b` with `delta`|descriptionEnd| */
s32 delta_interpolate_s32(s32 a, s32 b, f32 delta);
/* |description|Linearly interpolates `res` between `a` and `b` with `delta`|descriptionEnd| */
void delta_interpolate_vec3f(Vec3f res, Vec3f a, Vec3f b, f32 delta);
/* |description|Linearly interpolates `res` between `a` and `b` with `delta`|descriptionEnd| */
void delta_interpolate_vec3s(Vec3s res, Vec3s a, Vec3s b, f32 delta);
void delta_interpolate_normal(s8* res, s8* a, s8* b, f32 delta);
void delta_interpolate_rgba(u8* res, u8* a, u8* b, f32 delta);
void delta_interpolate_mtx(Mtx* out, Mtx* a, Mtx* b, f32 delta);
void detect_and_skip_mtx_interpolation(Mtx** mtxPrev, Mtx** mtx);

void str_seperator_concat(char *output_buffer, int buffer_size, char** strings, int num_strings, char* seperator);
char *str_remove_color_codes(const char *str);

#endif