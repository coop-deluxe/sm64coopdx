#ifndef SMLUA_GFX_UTILS_H
#define SMLUA_GFX_UTILS_H

#include "types.h"

void set_override_fov(f32 fov);
void set_override_near(f32 near);
void set_override_far(f32 far);

f32 get_lighting_dir(u8 index);
void set_lighting_dir(u8 index, f32 value);

u8 get_lighting_color(u8 index);
u8 get_lighting_color_ambient(u8 index);
void set_lighting_color(u8 index, u8 value);
void set_lighting_color_ambient(u8 index, u8 value);

u8 get_vertex_color(u8 index);
void set_vertex_color(u8 index, u8 value);

u8 get_fog_color(u8 index);
void set_fog_color(u8 index, u8 value);
f32 get_fog_intensity(void);
void set_fog_intensity(f32 intensity);

s8 get_skybox(void);
void set_override_skybox(s8 background);
u8 get_skybox_color(u8 index);
void set_skybox_color(u8 index, u8 value);

#endif
