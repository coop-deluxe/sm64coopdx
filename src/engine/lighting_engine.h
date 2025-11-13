#ifndef LIGHTING_ENGINE_H
#define LIGHTING_ENGINE_H

#include "types.h"

#define LE_MAX_LIGHTS 256

enum LEMode {
    LE_MODE_AFFECT_ALL_SHADED_AND_COLORED,
    LE_MODE_AFFECT_ALL_SHADED,
    LE_MODE_AFFECT_ONLY_GEOMETRY_MODE,
};

enum LEToneMapping {
    LE_TONE_MAPPING_TOTAL_WEIGHTED,
    LE_TONE_MAPPING_WEIGHTED,
    LE_TONE_MAPPING_CLAMP,
    LE_TONE_MAPPING_REINHARD,
};

extern Color gLEAmbientColor;

/* |description|Gets whether the lighting engine has been enabled or not. It becomes enabled once a light is added or the ambient color is set|descriptionEnd|*/
bool le_is_enabled(void);
/* |description|Sets the lighting engine mode to `mode`|descriptionEnd|*/
void le_set_mode(enum LEMode mode);
/* |description|Gets the lighting engine mode|descriptionEnd|*/
enum LEMode le_get_mode(void);
/* |description|Sets the lighting engine's tone mapping mode to `toneMapping`|descriptionEnd|*/
void le_set_tone_mapping(enum LEToneMapping toneMapping);
/* |description|Outputs the lighting engine's ambient color to `out`|descriptionEnd| */
void le_get_ambient_color(OUT Color out);
/* |description|Sets the lighting engine ambient color|descriptionEnd| */
void le_set_ambient_color(u8 r, u8 g, u8 b);

void le_calculate_vertex_lighting(Vtx_t* v, Vec3f pos, OUT Color out);
/* |description|Calculates the lighting with `lightIntensityScalar` at a position and outputs the color in `out`|descriptionEnd|*/
void le_calculate_lighting_color(Vec3f pos, OUT Color out, f32 lightIntensityScalar);
/* |description|Calculates the lighting with `lightIntensityScalar` at a position and with a normal and outputs the color in `out`|descriptionEnd|*/
void le_calculate_lighting_color_with_normal(Vec3f pos, Vec3f normal, OUT Color out, f32 lightIntensityScalar);
/* |description|Calculates the lighting direction from a position and outputs the result in `out`|descriptionEnd| */
void le_calculate_lighting_dir(Vec3f pos, OUT Vec3f out);
/* |description|Adds a lighting engine point light at `x`, `y`, `z` with color `r`, `g`, `b` and `radius` with `intensity`|descriptionEnd| */
s16 le_add_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius, f32 intensity);
/* |description|Removes a lighting engine point light corresponding to `id`|descriptionEnd| */
void le_remove_light(s16 id);
/* |description|Gets the total number of lights currently loaded in the lighting engine|descriptionEnd| */
s16 le_get_light_count(void);
/* |description|Checks if a lighting engine point light corresponding to `id` exists|descriptionEnd| */
bool le_light_exists(s16 id);
/* |description|Outputs a lighting engine point light's position to `out`|descriptionEnd| */
void le_get_light_pos(s16 id, OUT Vec3f out);
/* |description|Sets a lighting engine point light's position to `x`, `y`, `z`|descriptionEnd| */
void le_set_light_pos(s16 id, f32 x, f32 y, f32 z);
/* |description|Outputs a lighting engine point light's color to `out`|descriptionEnd| */
void le_get_light_color(s16 id, OUT Color out);
/* |description|Sets a lighting engine point light's color to `r`, `g`, `b`|descriptionEnd| */
void le_set_light_color(s16 id, u8 r, u8 g, u8 b);
/* |description|Gets a lighting engine point light's `radius`|descriptionEnd| */
f32 le_get_light_radius(s16 id);
/* |description|Sets a lighting engine point light's `radius`|descriptionEnd| */
void le_set_light_radius(s16 id, f32 radius);
/* |description|Gets a lighting engine point light's `intensity`|descriptionEnd| */
f32 le_get_light_intensity(s16 id);
/* |description|Sets a lighting engine point light's `intensity`|descriptionEnd| */
void le_set_light_intensity(s16 id, f32 intensity);
/* |description|Gets whether a lighting engine point light will use a surface's normals to determine its brightness with `useSurfaceNormals`|descriptionEnd| */
bool le_get_light_use_surface_normals(s16 id);
/* |description|Sets whether a lighting engine point light will use a surface's normals to determine its brightness with `useSurfaceNormals`|descriptionEnd| */
void le_set_light_use_surface_normals(s16 id, bool useSurfaceNormals);
void le_clear(void);
void le_shutdown(void);

#endif // LIGHTING_ENGINE_H
