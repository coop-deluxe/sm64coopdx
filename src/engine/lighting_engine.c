#include "lighting_engine.h"
#include "math_util.h"
#include "surface_collision.h"
#include "pc/lua/utils/smlua_math_utils.h"
#include "data/dynos_cmap.cpp.h"

static Color sAmbientColor;
static void* sLights = NULL;
static s16 sLightID = -1;

static inline void color_set(Color color, u8 r, u8 g, u8 b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void le_calculate_vertex_lighting(Vtx_t* v, Color out) {
    if (sLights == NULL) { return; }

    f32 r = 0;
    f32 g = 0;
    f32 b = 0;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        f32 dist = vec3f_dist(light->pos, v->ob);
        if (dist > light->radius) { continue; }
        dist = 1 - minf(dist / light->radius, 1);

        r += light->color[0] * dist * light->intensity;
        g += light->color[1] * dist * light->intensity;
        b += light->color[2] * dist * light->intensity;
    }

    out[0] = min((v->cn[0] * (sAmbientColor[0] / 255.0f)) + r, 255);
    out[1] = min((v->cn[1] * (sAmbientColor[1] / 255.0f)) + g, 255);
    out[2] = min((v->cn[2] * (sAmbientColor[2] / 255.0f)) + b, 255);
}

void le_calculate_lighting_color(Vec3f pos, Color out, f32 lightIntensityScalar) {
    if (sLights == NULL) { return; }

    f32 r = 0;
    f32 g = 0;
    f32 b = 0;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        f32 dist = vec3f_dist(light->pos, pos);
        if (dist > light->radius) { continue; }
        dist = 1 - minf(dist / light->radius, 1);

        r += light->color[0] * dist * light->intensity * lightIntensityScalar;
        g += light->color[1] * dist * light->intensity * lightIntensityScalar;
        b += light->color[2] * dist * light->intensity * lightIntensityScalar;
    }

    out[0] = min(sAmbientColor[0] + r, 255);
    out[1] = min(sAmbientColor[1] + g, 255);
    out[2] = min(sAmbientColor[2] + b, 255);
}

void le_calculate_lighting_dir(Vec3f pos, Vec3f out) {
    if (sLights == NULL) { return; }

    Vec3f lightingDir = { 0, 0, 0 };
    s16 count = 0;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        f32 dist = vec3f_dist(light->pos, pos);
        if (dist > light->radius) { continue; }
        dist = 1 - minf(dist / light->radius, 1);

        Vec3f dir = {
            pos[0] - light->pos[0],
            pos[1] - light->pos[1],
            pos[2] - light->pos[2],
        };
        vec3f_normalize(dir);

        lightingDir[0] += dir[0] * dist * light->intensity;
        lightingDir[1] += dir[1] * dist * light->intensity;
        lightingDir[2] += dir[2] * dist * light->intensity;

        count++;
    }

    count++; // additional increment
    out[0] = lightingDir[0] / (f32)(count);
    out[1] = lightingDir[1] / (f32)(count);
    out[2] = lightingDir[2] / (f32)(count);
    vec3f_normalize(out);
}

s16 le_add_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius, f32 intensity) {
    if (sLights == NULL) {
        sLights = hmap_create(true);
    }

    struct LELight* light = calloc(1, sizeof(struct LELight));
    vec3f_set(light->pos, x, y, z);
    color_set(light->color, r, g, b);
    light->radius = radius;
    light->intensity = intensity;
    hmap_put(sLights, ++sLightID, light);
    return sLightID;
}

void le_remove_light(s16 id) {
    free(hmap_get(sLights, id));
    hmap_del(sLights, id);
}

s16 le_get_light_count(void) {
    if (sLights == NULL) { return 0; }
    return hmap_len(sLights);
}

void le_set_ambient_color(u8 r, u8 g, u8 b) {
    color_set(sAmbientColor, r, g, b);
}

void le_set_light_pos(s16 id, f32 x, f32 y, f32 z) {
    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    vec3f_set(light->pos, x, y, z);
}

void le_set_light_color(s16 id, u8 r, u8 g, u8 b) {
    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    color_set(light->color, r, g, b);
}

void le_set_light_radius(s16 id, f32 radius) {
    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    light->radius = radius;
}

void le_set_light_intensity(s16 id, f32 intensity) {
    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    light->intensity = intensity;
}

void le_clear(void) {
    if (sLights == NULL) { return; }

    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        free(light);
    }
    hmap_clear(sLights);
    sLightID = -1;
    sAmbientColor[0] = 0;
    sAmbientColor[1] = 0;
    sAmbientColor[2] = 0;
}

void le_shutdown(void) {
    if (sLights == NULL) { return; }

    le_clear();
    hmap_destroy(sLights);
    sLights = NULL;
}
