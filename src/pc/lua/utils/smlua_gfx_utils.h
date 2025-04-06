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
void gfx_parse(Gfx *cmd, LuaFunction func);
/* |description|Gets the display list from a display list command if it has the op `G_DL`|descriptionEnd| */
Gfx *gfx_get_display_list(Gfx *cmd);
/* |description|Gets the vertex buffer from a display list command if it has the op `G_VTX`|descriptionEnd| */
Vtx *gfx_get_vertex_buffer(Gfx *cmd);
/* |description|Gets the number of vertices from a display list command if it has the op `G_VTX`|descriptionEnd| */
u16 gfx_get_vertex_count(Gfx *cmd);

/* |description|Gets a command from a display list at position `offset`|descriptionEnd| */
Gfx *gfx_get_command(Gfx *gfx, u32 offset);
/* |description|Gets a vertex from a vertex buffer at position `offset`|descriptionEnd| */
Vtx *vtx_get_vertex(Vtx *vtx, u32 offset);

#endif
