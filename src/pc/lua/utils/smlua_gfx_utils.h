#ifndef SMLUA_GFX_UTILS_H
#define SMLUA_GFX_UTILS_H

#include "pc/lua/smlua.h"
#include "types.h"

/* |description|Sets the override FOV|descriptionEnd| */
void set_override_fov(f32 fov);
/* |description|Sets the override near plane|descriptionEnd| */
void set_override_near(f32 near);
/* |description|Sets the override far plane|descriptionEnd| */
void set_override_far(f32 far);

/* |description|Gets a value of the global lighting direction|descriptionEnd| */
f32 get_lighting_dir(u8 index);
/* |description|Sets a value of the global lighting direction|descriptionEnd| */
void set_lighting_dir(u8 index, f32 value);

/* |description|Gets a value of the global lighting color|descriptionEnd| */
u8 get_lighting_color(u8 index);
/* |description|Gets a value of the global ambient lighting color|descriptionEnd| */
u8 get_lighting_color_ambient(u8 index);
/* |description|Sets a value of the global lighting color|descriptionEnd| */
void set_lighting_color(u8 index, u8 value);
/* |description|Sets a value of the global lighting color (run this after `set_lighting_color` for the ambient color to not be overriden)|descriptionEnd| */
void set_lighting_color_ambient(u8 index, u8 value);

/* |description|Gets a value of the global vertex shading color|descriptionEnd| */
u8 get_vertex_color(u8 index);
/* |description|Sets a value of the global vertex shading color|descriptionEnd| */
void set_vertex_color(u8 index, u8 value);

/* |description|Gets a value of the global fog color|descriptionEnd| */
u8 get_fog_color(u8 index);
/* |description|Sets a value of the global fog color|descriptionEnd| */
void set_fog_color(u8 index, u8 value);
/* |description|Gets the intensity of the fog|descriptionEnd| */
f32 get_fog_intensity(void);
/* |description|Sets the intensity of the fog (this value scales very quickly, 1.0 to 1.1 is a desirable range)|descriptionEnd| */
void set_fog_intensity(f32 intensity);

/* |description|Gets the current skybox|descriptionEnd| */
s8 get_skybox(void);
/* |description|Sets the override skybox|descriptionEnd| */
void set_override_skybox(s8 background);
/* |description|Gets a value of the global skybox color|descriptionEnd| */
u8 get_skybox_color(u8 index);
/* |description|Sets a value of the global skybox color|descriptionEnd| */
void set_skybox_color(u8 index, u8 value);

/* |description|Traverses a display list. Takes a Lua function as a parameter, which is called back for each command in the display list with the parameters `cmd` (display list pointer), and `op`|descriptionEnd| */
void gfx_parse(Gfx* cmd, LuaFunction func);
/* |description|Gets a vertex from a display list command if it has the correct op. Intended to be used with `gfx_parse`|descriptionEnd| */
Vtx *gfx_get_vtx(Gfx* gfx, u16 offset);
/* |description|Gets the number of vertices from a display list command if it has the correct op|descriptionEnd| */
u16 gfx_get_vtx_count(Gfx* cmd);
/* |description|Sets the display list combine mode. you can fill this function with G_CCMUX_* and G_ACMUX_* constants|descriptionEnd| */
void gfx_set_combine_lerp(Gfx* gfx, u32 a0, u32 b0, u32 c0, u32 d0, u32 Aa0, u32 Ab0, u32 Ac0, u32 Ad0, u32 a1, u32 b1, u32 c1, u32 d1,	u32 Aa1, u32 Ab1, u32 Ac1, u32 Ad1);
/* |description|Sets the display list texture image. Pass in textureInfo.texture as `texture`|descriptionEnd| */
void gfx_set_texture_image(Gfx* gfx, u32 format, u32 size, u32 width, u8* texture);

#endif
