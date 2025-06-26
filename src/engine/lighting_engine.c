#include "lighting_engine.h"
#include "math_util.h"
#include "surface_collision.h"
#include "pc/debuglog.h"
#include "data/dynos_cmap.cpp.h"

#define LE_MAX_LIGHTS 256

static Color sAmbientColor = { 127, 127, 127 };
static void* sLights = NULL;
static s32 sLightID = 0;
static enum LEMode sMode = LE_MODE_AFFECT_ALL_SHADED;
static enum LEToneMapping sToneMapping = LE_TONE_MAPPING_TOTAL_WEIGHTED;
static bool sEnabled = false;

static inline void color_set(Color color, u8 r, u8 g, u8 b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

bool le_is_enabled(void) {
    // this is needed because we don't want to make vanilla darker,
    // and we don't want to set the ambient color to { 255, 255, 255 }
    // because then no one could see the effect of their lights
    return sEnabled;
}

void le_set_mode(enum LEMode mode) {
    sMode = mode;
}

enum LEMode le_get_mode(void) {
    return sMode;
}

void le_set_tone_mapping(enum LEToneMapping toneMapping) {
    sToneMapping = toneMapping;
}

static inline void le_tone_map_total_weighted(OUT Color out, Color in_ambient, Vec3f in_color, float weight) {
    out[0] = clamp((in_ambient[0] + in_color[0]) / weight, 0, 255);
    out[1] = clamp((in_ambient[1] + in_color[1]) / weight, 0, 255);
    out[2] = clamp((in_ambient[2] + in_color[2]) / weight, 0, 255);
}

static inline void le_tone_map_weighted(OUT Color out, Color in_ambient, Vec3f in_color, float weight) {
    out[0] = clamp(in_ambient[0] + (in_color[0] / weight), 0, 255);
    out[1] = clamp(in_ambient[1] + (in_color[1] / weight), 0, 255);
    out[2] = clamp(in_ambient[2] + (in_color[2] / weight), 0, 255);
}

static inline void le_tone_map_clamp(OUT Color out, Color in_ambient, Vec3f in_color) {
    out[0] = clamp(in_ambient[0] + in_color[0], 0, 255);
    out[1] = clamp(in_ambient[1] + in_color[1], 0, 255);
    out[2] = clamp(in_ambient[2] + in_color[2], 0, 255);
}

static inline void le_tone_map_reinhard(OUT Color out, Color in_ambient, Vec3f in_color) {
    in_color[0] += in_ambient[0];
    in_color[1] += in_ambient[1];
    in_color[2] += in_ambient[2];

    out[0] = clamp((in_color[0] / (in_color[0] + 255.0f)) * 255.0f, 0, 255);
    out[1] = clamp((in_color[1] / (in_color[1] + 255.0f)) * 255.0f, 0, 255);
    out[2] = clamp((in_color[2] / (in_color[2] + 255.0f)) * 255.0f, 0, 255);
}

static inline void le_tone_map(OUT Color out, Color in_ambient, Vec3f in_color, float weight) {
    switch (sToneMapping) {
        case LE_TONE_MAPPING_TOTAL_WEIGHTED: le_tone_map_total_weighted(out, in_ambient, in_color, weight); break;
        case LE_TONE_MAPPING_WEIGHTED:       le_tone_map_weighted(out, in_ambient, in_color, weight);       break;
        case LE_TONE_MAPPING_CLAMP:          le_tone_map_clamp(out, in_ambient, in_color);                  break;
        case LE_TONE_MAPPING_REINHARD:       le_tone_map_reinhard(out, in_ambient, in_color);               break;
    }
}

static inline void le_calculate_light_contribution(struct LELight* light, Vec3f pos, Vec3f normal, f32 lightIntensityScalar, OUT Vec3f out_color, OUT f32* weight) {
    // skip 'inactive' lights
    if (light->intensity <= 0 || light->radius <= 0) { return; }

    // vector to light
    f32 diffX = light->posX - pos[0];
    f32 diffY = light->posY - pos[1];
    f32 diffZ = light->posZ - pos[2];

    // squared distance check
    f32 dist2 = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);
    f32 radius2 = light->radius * light->radius;
    if (dist2 > radius2 || dist2 <= 0) { return; }

    // attenuation & intensity
    f32 att = 1.0f - (dist2 / radius2);
    f32 brightness = att * light->intensity * lightIntensityScalar;

    // normalize diff
    f32 invLen = 1.0f / sqrtf(dist2);
    diffX *= invLen;
    diffY *= invLen;
    diffZ *= invLen;

    if (light->useSurfaceNormals && normal) {
        // lambert term
        f32 nl = (normal[0] * diffX) + (normal[1] * diffY) + (normal[2] * diffZ);
        if (nl <= 0.0f) { return; }

        // modulate by normal
        brightness *= nl;
    }

    // accumulate
    out_color[0] += light->colorR * brightness;
    out_color[1] += light->colorG * brightness;
    out_color[2] += light->colorB * brightness;
    *weight += brightness;
}

void le_calculate_vertex_lighting(Vtx_t* v, Vec3f pos, OUT Color out) {
    if (sLights == NULL) { return; }

    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        le_calculate_light_contribution(light, pos, NULL, 1, color, &weight);
    }

    // tone map and output
    Color vtxAmbient = {
        v->cn[0] * (sAmbientColor[0] / 255.0f),
        v->cn[1] * (sAmbientColor[1] / 255.0f),
        v->cn[2] * (sAmbientColor[2] / 255.0f),
    };
    le_tone_map(out, vtxAmbient, color, weight);
}

void le_calculate_lighting_color(Vec3f pos, OUT Color out, f32 lightIntensityScalar) {
    if (sLights == NULL) { return; }

    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        le_calculate_light_contribution(light, pos, NULL, lightIntensityScalar, color, &weight);
    }

    // tone map and output
    le_tone_map(out, sAmbientColor, color, weight);
}

void le_calculate_lighting_color_with_normal(Vec3f pos, Vec3f normal, OUT Color out, f32 lightIntensityScalar) {
    if (sLights == NULL) { return; }

    // normalize normal
    if (normal) { vec3f_normalize(normal); }

    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        le_calculate_light_contribution(light, pos, normal, lightIntensityScalar, color, &weight);
    }

    // tone map and output
    le_tone_map(out, sAmbientColor, color, weight);
}

void le_calculate_lighting_dir(Vec3f pos, OUT Vec3f out) {
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
    light->useSurfaceNormals = true;
    hmap_put(sLights, ++sLightID, light);

    sEnabled = true;
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

void le_set_light_use_surface_normals(s32 id, bool useSurfaceNormals) {
    if (sLights == NULL || id <= 0) { return; }

    struct LELight* light = hmap_get(sLights, id);
    if (light == NULL) { return; }
    light->useSurfaceNormals = useSurfaceNormals;
}

void le_clear(void) {
    if (sLights == NULL) { return; }

    for (struct LELight* light = hmap_begin(sLights); light != NULL; light = hmap_next(sLights)) {
        free(light);
    }
    hmap_clear(sLights);
    sLightID = 0;
    sAmbientColor[0] = 127;
    sAmbientColor[1] = 127;
    sAmbientColor[2] = 127;
}

void le_shutdown(void) {
    if (sLights == NULL) { return; }

    sEnabled = false;
    sMode = LE_MODE_AFFECT_ALL_SHADED;
    sToneMapping = LE_TONE_MAPPING_TOTAL_WEIGHTED;
    le_clear();
    hmap_destroy(sLights);
    sLights = NULL;
}
