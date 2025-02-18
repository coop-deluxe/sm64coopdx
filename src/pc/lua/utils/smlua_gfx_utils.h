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

void gfx_parse(Gfx* cmd, LuaFunction func);
Vtx *gfx_get_vtx(Gfx* gfx, u16 offset);
void gfx_set_geometrymode(Gfx* gfx, u32 mode);
void gfx_clear_geometrymode(Gfx* gfx, u32 mode);
void gfx_set_cycle_type(Gfx* gfx, u32 type);
void gfx_set_render_mode(Gfx* gfx, u32 c0, u32 c1);
void gfx_set_prim_color(Gfx* gfx, u8 m, u8 l, u8 r, u8 g, u8 b, u8 a);
void gfx_set_env_color(Gfx* gfx, u8 r, u8 g, u8 b, u8 a);
void gfx_set_fog_color(Gfx* gfx, u8 r, u8 g, u8 b, u8 a);
void gfx_copy_lights_player_part(Gfx* gfx, u8 part);

#endif
