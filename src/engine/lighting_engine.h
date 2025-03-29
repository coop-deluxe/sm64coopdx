#ifndef LIGHTING_ENGINE_H
#define LIGHTING_ENGINE_H

#include "types.h"

struct LELight
{
    f32 posX;
    f32 posY;
    f32 posZ;
    u8 colorR;
    u8 colorG;
    u8 colorB;
    f32 radius;
    f32 intensity;
};

void le_calculate_vertex_lighting(Vtx_t* v, Color out);
/* |description|Calculates the lighting with `lightIntensityScalar` at a position and outputs the color in `out`|descriptionEnd|*/
void le_calculate_lighting_color(Vec3f pos, Color out, f32 lightIntensityScalar);
/* |description|Calculates the lighting direction from a position and outputs the result in `out`|descriptionEnd| */
void le_calculate_lighting_dir(Vec3f pos, Vec3f out);
/* |description|Adds a lighting engine point light at `x`, `y`, `z` with color `r`, `g`, `b` and `radius` with `intensity`|descriptionEnd| */
s32 le_add_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius, f32 intensity);
/* |description|Removes a lighting engine point light corresponding to `id`|descriptionEnd| */
void le_remove_light(s32 id);
/* |description|Gets the total number of lights currently loaded in the lighting engine|descriptionEnd| */
s32 le_get_light_count(void);
/* |description|Sets the lighting engine ambient color|descriptionEnd| */
void le_set_ambient_color(u8 r, u8 g, u8 b);
/* |description|Sets a lighting engine point light's position to `x`, `y`, `z`|descriptionEnd| */
void le_set_light_pos(s32 id, f32 x, f32 y, f32 z);
/* |description|Sets a lighting engine point light's color to `r`, `g`, `b`|descriptionEnd| */
void le_set_light_color(s32 id, u8 r, u8 g, u8 b);
/* |description|Sets a lighting engine point light's `radius`|descriptionEnd| */
void le_set_light_radius(s32 id, f32 radius);
/* |description|Sets a lighting engine point light's `intensity`|descriptionEnd| */
void le_set_light_intensity(s32 id, f32 intensity);
void le_clear(void);
void le_shutdown(void);

#endif // LIGHTING_ENGINE_H
