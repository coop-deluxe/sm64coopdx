#include "lighting_engine.h"
#include "math_util.h"

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
    bool added;
    bool useSurfaceNormals;
};

Color gLEAmbientColor = { 127, 127, 127 };
static struct LELight sLights[LE_MAX_LIGHTS] = { 0 };
static enum LEMode sMode = LE_MODE_AFFECT_ALL_SHADED_AND_COLORED;
static enum LEToneMapping sToneMapping = LE_TONE_MAPPING_WEIGHTED;
static bool sEnabled = false;

static inline void color_set(Color color, u8 r, u8 g, u8 b) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

static inline void color_copy(Color dest, Color src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
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

void le_get_ambient_color(OUT Color out) {
    color_copy(out, gLEAmbientColor);
}

void le_set_ambient_color(u8 r, u8 g, u8 b) {
    color_set(gLEAmbientColor, r, g, b);
    sEnabled = true;
}

static inline void le_tone_map_total_weighted(Color out, Color inAmbient, Vec3f inColor, float weight) {
    out[0] = clamp((inAmbient[0] + inColor[0]) / weight, 0, 255);
    out[1] = clamp((inAmbient[1] + inColor[1]) / weight, 0, 255);
    out[2] = clamp((inAmbient[2] + inColor[2]) / weight, 0, 255);
}

static inline void le_tone_map_weighted(Color out, Color inAmbient, Vec3f inColor, float weight) {
    out[0] = clamp(inAmbient[0] + (inColor[0] / weight), 0, 255);
    out[1] = clamp(inAmbient[1] + (inColor[1] / weight), 0, 255);
    out[2] = clamp(inAmbient[2] + (inColor[2] / weight), 0, 255);
}

static inline void le_tone_map_clamp(Color out, Color inAmbient, Vec3f inColor) {
    out[0] = clamp(inAmbient[0] + inColor[0], 0, 255);
    out[1] = clamp(inAmbient[1] + inColor[1], 0, 255);
    out[2] = clamp(inAmbient[2] + inColor[2], 0, 255);
}

static inline void le_tone_map_reinhard(Color out, Color inAmbient, Vec3f inColor) {
    inColor[0] += inAmbient[0];
    inColor[1] += inAmbient[1];
    inColor[2] += inAmbient[2];

    out[0] = clamp((inColor[0] / (inColor[0] + 255.0f)) * 255.0f, 0, 255);
    out[1] = clamp((inColor[1] / (inColor[1] + 255.0f)) * 255.0f, 0, 255);
    out[2] = clamp((inColor[2] / (inColor[2] + 255.0f)) * 255.0f, 0, 255);
}

static inline void le_tone_map(Color out, Color inAmbient, Vec3f inColor, float weight) {
    switch (sToneMapping) {
        case LE_TONE_MAPPING_TOTAL_WEIGHTED: le_tone_map_total_weighted(out, inAmbient, inColor, weight); break;
        case LE_TONE_MAPPING_WEIGHTED:       le_tone_map_weighted(out, inAmbient, inColor, weight);       break;
        case LE_TONE_MAPPING_CLAMP:          le_tone_map_clamp(out, inAmbient, inColor);                  break;
        case LE_TONE_MAPPING_REINHARD:       le_tone_map_reinhard(out, inAmbient, inColor);               break;
    }
}

static inline void le_calculate_light_contribution(struct LELight* light, Vec3f pos, Vec3f normal, f32 lightIntensityScalar, Vec3f out_color, f32* weight) {
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

void le_calculate_vertex_lighting(Vtx_t* v, Vec3f pos, Color out) {
    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    for (s16 i = 0; i < LE_MAX_LIGHTS; i++) {
        struct LELight* light = &sLights[i];
        if (!light->added) { continue; }

        le_calculate_light_contribution(light, pos, NULL, 1.0f, color, &weight);
    }

    // tone map and output
    Color vtxAmbient = {
        v->cn[0] * (gLEAmbientColor[0] / 255.0f),
        v->cn[1] * (gLEAmbientColor[1] / 255.0f),
        v->cn[2] * (gLEAmbientColor[2] / 255.0f),
    };
    le_tone_map(out, vtxAmbient, color, weight);
}

void le_calculate_lighting_color(Vec3f pos, Color out, f32 lightIntensityScalar) {
    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    for (s16 i = 0; i < LE_MAX_LIGHTS; i++) {
        struct LELight* light = &sLights[i];
        if (!light->added) { continue; }

        le_calculate_light_contribution(light, pos, NULL, lightIntensityScalar, color, &weight);
    }

    // tone map and output
    le_tone_map(out, gLEAmbientColor, color, weight);
}

void le_calculate_lighting_color_with_normal(Vec3f pos, Vec3f normal, Color out, f32 lightIntensityScalar) {
    // normalize normal
    if (normal) { vec3f_normalize(normal); }

    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    for (s16 i = 0; i < LE_MAX_LIGHTS; i++) {
        struct LELight* light = &sLights[i];
        if (!light->added) { continue; }

        le_calculate_light_contribution(light, pos, normal, lightIntensityScalar, color, &weight);
    }

    // tone map and output
    le_tone_map(out, gLEAmbientColor, color, weight);
}

void le_calculate_lighting_dir(Vec3f pos, Vec3f out) {
    Vec3f lightingDir = { 0, 0, 0 };
    s16 count = 1;

    for (s16 i = 0; i < LE_MAX_LIGHTS; i++) {
        struct LELight* light = &sLights[i];
        if (!light->added) { continue; }

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

s16 le_add_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius, f32 intensity) {
    struct LELight* newLight = NULL;
    s16 lightID = -1;

    for (s16 i = 0; i < LE_MAX_LIGHTS; i++) {
        struct LELight* light = &sLights[i];
        if (!light->added) {
            newLight = light;
            lightID = i;
            break;
        }
    }
    if (newLight == NULL) { return -1; }

    newLight->posX = x;
    newLight->posY = y;
    newLight->posZ = z;
    newLight->colorR = r;
    newLight->colorG = g;
    newLight->colorB = b;
    newLight->radius = radius;
    newLight->intensity = intensity;
    newLight->added = true;
    newLight->useSurfaceNormals = true;

    sEnabled = true;
    return lightID;
}

void le_remove_light(s16 id) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    memset(&sLights[id], 0, sizeof(struct LELight));
}

s16 le_get_light_count(void) {
    s16 count = 0;
    for (s16 i = 0; i < LE_MAX_LIGHTS; i++) {
        if (sLights[i].added) { count++; }
    }

    return count;
}

bool le_light_exists(s16 id) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return false; }
    return sLights[id].added;
}

void le_get_light_pos(s16 id, OUT Vec3f out) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return; }
    vec3f_set(out, light->posX, light->posY, light->posZ);
}

void le_set_light_pos(s16 id, f32 x, f32 y, f32 z) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return; }
    light->posX = x;
    light->posY = y;
    light->posZ = z;
}

void le_get_light_color(s16 id, OUT Color out) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return; }
    color_set(out, light->colorR, light->colorG, light->colorB);
}

void le_set_light_color(s16 id, u8 r, u8 g, u8 b) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return; }
    light->colorR = r;
    light->colorG = g;
    light->colorB = b;
}

f32 le_get_light_radius(s16 id) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return 0.0f; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return 0.0f; }
    return light->radius;
}

void le_set_light_radius(s16 id, f32 radius) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return; }
    light->radius = radius;
}

f32 le_get_light_intensity(s16 id) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return 0.0f; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return 0.0f; }
    return light->intensity;
}

void le_set_light_intensity(s16 id, f32 intensity) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return; }
    light->intensity = intensity;
}

bool le_get_light_use_surface_normals(s16 id) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return false; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return false; }
    return light->useSurfaceNormals;
}

void le_set_light_use_surface_normals(s16 id, bool useSurfaceNormals) {
    if (id < 0 || id >= LE_MAX_LIGHTS) { return; }

    struct LELight* light = &sLights[id];
    if (!light->added) { return; }
    light->useSurfaceNormals = useSurfaceNormals;
}

void le_clear(void) {
    memset(&sLights, 0, sizeof(struct LELight) * LE_MAX_LIGHTS);

    gLEAmbientColor[0] = 127;
    gLEAmbientColor[1] = 127;
    gLEAmbientColor[2] = 127;
}

void le_shutdown(void) {
    sEnabled = false;
    sMode = LE_MODE_AFFECT_ALL_SHADED_AND_COLORED;
    sToneMapping = LE_TONE_MAPPING_WEIGHTED;
    le_clear();
}
