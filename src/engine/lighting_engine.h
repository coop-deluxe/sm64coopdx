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
    bool useSurfaceNormals;
};

enum LEMode {
    LE_MODE_DEFAULT,
    LE_MODE_AFFECT_ALL_SHADED,
};

enum LEToneMapping {
    LE_TONE_MAPPING_TOTAL_WEIGHTED,
    LE_TONE_MAPPING_WEIGHTED,
    LE_TONE_MAPPING_CLAMP,
    LE_TONE_MAPPING_REINHARD,
};

/* |description|Sets the lighting engine mode to `mode`|descriptionEnd|*/
void le_set_mode(enum LEMode mode);
/* |description|Gets the lighting engine mode|descriptionEnd|*/
enum LEMode le_get_mode(void);
/* |description|Sets the lighting engine's tone mapping mode to `toneMapping`|descriptionEnd|*/
void le_set_tone_mapping(enum LEToneMapping toneMapping);

void le_calculate_vertex_lighting(Vtx_t* v, Vec3f pos, OUT Color out);
/* |description|Calculates the lighting with `lightIntensityScalar` at a position and outputs the color in `out`|descriptionEnd|*/
void le_calculate_lighting_color(Vec3f pos, OUT Color out, f32 lightIntensityScalar);
/* |description|Calculates the lighting with `lightIntensityScalar` at a position and with a normal and outputs the color in `out`|descriptionEnd|*/
void le_calculate_lighting_color_with_normal(Vec3f pos, Vec3f normal, OUT Color out, f32 lightIntensityScalar);
/* |description|Calculates the lighting direction from a position and outputs the result in `out`|descriptionEnd| */
void le_calculate_lighting_dir(Vec3f pos, OUT Vec3f out);
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
/* |description|Sets whether a lighting engine point light will use a surface's normals to determine its brightness with `useSurfaceNormals`|descriptionEnd| */
void le_set_light_use_surface_normals(s32 id, bool useSurfaceNormals);
void le_clear(void);
void le_shutdown(void);

#endif // LIGHTING_ENGINE_H
