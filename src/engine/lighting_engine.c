#include "lighting_engine.h"
#include "math_util.h"
#include "surface_collision.h"
#include "pc/lua/utils/smlua_math_utils.h"
#include "pc/debuglog.h"
#include "data/dynos_cmap.cpp.h"

#define LE_MAX_LIGHTS 256
#define LE_TOTAL_WEIGHTED_LIGHTING

static Color sAmbientColor;
static void* sLights = NULL;
static s32 sLightID = 0;

static inline void color_set(Color color, u8 r, u8 g, u8 b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void le_calculate_vertex_lighting(Vtx_t* v, Color out) {
    if (sLights == NULL) { return; }

#ifdef LE_TOTAL_WEIGHTED_LIGHTING
    f32 r = v->cn[0] * (sAmbientColor[0] / 255.0f);
    f32 g = v->cn[1] * (sAmbientColor[1] / 255.0f);
    f32 b = v->cn[2] * (sAmbientColor[2] / 255.0f);
#else
    f32 r = 0;
    f32 g = 0;
    f32 b = 0;
#endif
    f32 weight = 1.0f;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        f32 diffX = light->posX - v->ob[0];
        f32 diffY = light->posY - v->ob[1];
        f32 diffZ = light->posZ - v->ob[2];
        f32 dist = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);
        f32 radius = light->radius * light->radius;
        if (dist > radius) { continue; }

        f32 brightness = (1 - (dist / radius)) * light->intensity;
        r += light->colorR * brightness;
        g += light->colorG * brightness;
        b += light->colorB * brightness;
        weight += brightness;
    }

#ifdef LE_TOTAL_WEIGHTED_LIGHTING
    out[0] = min(r / weight, 255);
    out[1] = min(g / weight, 255);
    out[2] = min(b / weight, 255);
#else
    out[0] = min((v->cn[0] * (sAmbientColor[0] / 255.0f)) + (r / weight), 255);
    out[1] = min((v->cn[1] * (sAmbientColor[1] / 255.0f)) + (g / weight), 255);
    out[2] = min((v->cn[2] * (sAmbientColor[2] / 255.0f)) + (b / weight), 255);
#endif
}

void le_calculate_lighting_color(Vec3f pos, Color out, f32 lightIntensityScalar) {
    if (sLights == NULL) { return; }

    f32 r = sAmbientColor[0];
    f32 g = sAmbientColor[1];
    f32 b = sAmbientColor[2];
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        f32 diffX = light->posX - pos[0];
        f32 diffY = light->posY - pos[1];
        f32 diffZ = light->posZ - pos[2];
        f32 dist = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);
        f32 radius = light->radius * light->radius;
        if (dist > radius) { continue; }

        f32 brightness = (1 - (dist / radius)) * light->intensity * lightIntensityScalar;
        r += light->colorR * brightness;
        g += light->colorG * brightness;
        b += light->colorB * brightness;
    }

    out[0] = min(r, 255);
    out[1] = min(g, 255);
    out[2] = min(b, 255);
}

void le_calculate_lighting_dir(Vec3f pos, Vec3f out) {
    if (sLights == NULL) { return; }

    Vec3f lightingDir = { 0, 0, 0 };
    s32 count = 1;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        f32 diffX = light->posX - pos[0];
        f32 diffY = light->posY - pos[1];
        f32 diffZ = light->posZ - pos[2];
        f32 dist = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);
        f32 radius = light->radius * light->radius;
        if (dist > radius) { continue; }

        Vec3f dir = {
            pos[0] - light->posX,
            pos[1] - light->posY,
            pos[2] - light->posZ,
        };
        vec3f_normalize(dir);

        f32 intensity = (1 - (dist / radius)) * light->intensity;
        lightingDir[0] += dir[0] * intensity;
        lightingDir[1] += dir[1] * intensity;
        lightingDir[2] += dir[2] * intensity;

        count++;
    }

    out[0] = lightingDir[0] / (f32)(count);
    out[1] = lightingDir[1] / (f32)(count);
    out[2] = lightingDir[2] / (f32)(count);
    vec3f_normalize(out);
}

s32 le_add_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius, f32 intensity) {
    if (sLights == NULL) {
        sLights = hmap_create(true);
    } else if (hmap_len(sLights) >= LE_MAX_LIGHTS) {
        return 0;
    }

    struct LELight* light = calloc(1, sizeof(struct LELight));
    light->posX = x;
    light->posY = y;
    light->posZ = z;
    light->colorR = r;
    light->colorG = g;
    light->colorB = b;
    light->radius = radius;
    light->intensity = intensity;
    hmap_put(sLights, ++sLightID, light);
    return sLightID;
}

void le_remove_light(s32 id) {
    if (sLights == NULL || id <= 0) { return; }

    free(hmap_get(sLights, id));
    hmap_del(sLights, id);
}

s32 le_get_light_count(void) {
    if (sLights == NULL) { return 0; }
    return hmap_len(sLights);
}

void le_set_ambient_color(u8 r, u8 g, u8 b) {
    color_set(sAmbientColor, r, g, b);
}

void le_set_light_pos(s32 id, f32 x, f32 y, f32 z) {
    if (sLights == NULL || id <= 0) { return; }

    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    light->posX = x;
    light->posY = y;
    light->posZ = z;
}

void le_set_light_color(s32 id, u8 r, u8 g, u8 b) {
    if (sLights == NULL || id <= 0) { return; }

    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    light->colorR = r;
    light->colorG = g;
    light->colorB = b;
}

void le_set_light_radius(s32 id, f32 radius) {
    if (sLights == NULL || id <= 0) { return; }

    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    light->radius = radius;
}

void le_set_light_intensity(s32 id, f32 intensity) {
    if (sLights == NULL || id <= 0) { return; }

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
    sLightID = 0;
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
