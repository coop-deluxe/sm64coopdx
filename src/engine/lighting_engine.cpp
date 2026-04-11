#include "lighting_engine.h"
extern "C" {
#include "math_util.h"
#include "pc/lua/smlua.h"
}
#undef clamp
#undef min
#undef max
#include <vector>
#include <algorithm>
#ifdef __SSE__
#include <xmmintrin.h>
#endif

#define C_FIELD extern "C"

struct LELight
{
    s16 id;
    Vec3f pos;
    Color color;
    f32 radius;
    f32 intensity;
    bool useSurfaceNormals;
};

Color gLEAmbientColor = { 127, 127, 127 };
static std::vector<LELight> sLightPool;
static std::vector<LELight*> sActiveLights;
static s16 sLightID = -1;
static enum LEMode sMode = LE_MODE_AFFECT_ALL_SHADED_AND_COLORED;
static enum LEToneMapping sToneMapping = LE_TONE_MAPPING_WEIGHTED;
static bool sEnabled = false;
static u8 sMaxLightsPerVertex = 4;

static inline f32 rsqrt(f32 value) {
#ifdef __SSE__
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(value)));
#else
    return 1.0f / sqrtf(value);
#endif
}

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

static inline u8 clamp_u8(f32 value) {
    s32 v = (s32)value;
    v = v < 0 ? 0 : v;
    v = v > 255 ? 255 : v;
    return (u8)v;
}

C_FIELD bool le_is_enabled(void) {
    // this is needed because we don't want to make vanilla darker,
    // and we don't want to set the ambient color to { 255, 255, 255 }
    // because then no one could see the effect of their lights
    return sEnabled;
}

C_FIELD void le_set_mode(enum LEMode mode) {
    sMode = mode;
}

C_FIELD enum LEMode le_get_mode(void) {
    return sMode;
}

C_FIELD void le_set_tone_mapping(enum LEToneMapping toneMapping) {
    sToneMapping = toneMapping;
}

C_FIELD void le_get_ambient_color(VEC_OUT Color out) {
    color_copy(out, gLEAmbientColor);
}

C_FIELD void le_set_ambient_color(u8 r, u8 g, u8 b) {
    color_set(gLEAmbientColor, r, g, b);
    sEnabled = true;
}

C_FIELD void le_set_max_lights_per_vertex(u8 count) {
    sMaxLightsPerVertex = count;
}

C_FIELD void le_set_enabled(bool value) {
    sEnabled = value;
}

static inline void le_tone_map_total_weighted(Color out, Color inAmbient, Vec3f inColor, f32 weight) {
    out[0] = clamp_u8((inAmbient[0] + inColor[0]) / weight);
    out[1] = clamp_u8((inAmbient[1] + inColor[1]) / weight);
    out[2] = clamp_u8((inAmbient[2] + inColor[2]) / weight);
}

static inline void le_tone_map_weighted(Color out, Color inAmbient, Vec3f inColor, f32 weight) {
    out[0] = clamp_u8(inAmbient[0] + (inColor[0] / weight));
    out[1] = clamp_u8(inAmbient[1] + (inColor[1] / weight));
    out[2] = clamp_u8(inAmbient[2] + (inColor[2] / weight));
}

static inline void le_tone_map_clamp(Color out, Color inAmbient, Vec3f inColor) {
    out[0] = clamp_u8(inAmbient[0] + inColor[0]);
    out[1] = clamp_u8(inAmbient[1] + inColor[1]);
    out[2] = clamp_u8(inAmbient[2] + inColor[2]);
}

static inline void le_tone_map_reinhard(Color out, Color inAmbient, Vec3f inColor) {
    inColor[0] += inAmbient[0];
    inColor[1] += inAmbient[1];
    inColor[2] += inAmbient[2];

    out[0] = clamp_u8((inColor[0] / (inColor[0] + 255.0f)) * 255.0f);
    out[1] = clamp_u8((inColor[1] / (inColor[1] + 255.0f)) * 255.0f);
    out[2] = clamp_u8((inColor[2] / (inColor[2] + 255.0f)) * 255.0f);
}

static void le_tone_map(Color out, Color inAmbient, Vec3f inColor, f32 weight) {
    switch (sToneMapping) {
        case LE_TONE_MAPPING_TOTAL_WEIGHTED: le_tone_map_total_weighted(out, inAmbient, inColor, weight); break;
        case LE_TONE_MAPPING_WEIGHTED:       le_tone_map_weighted(out, inAmbient, inColor, weight);       break;
        case LE_TONE_MAPPING_CLAMP:          le_tone_map_clamp(out, inAmbient, inColor);                  break;
        case LE_TONE_MAPPING_REINHARD:       le_tone_map_reinhard(out, inAmbient, inColor);               break;
    }
}

static void le_update_active_lights() {
    sActiveLights.clear();
    for (auto& light : sLightPool) {
        if (light.intensity > 0.0f && light.radius > 0.0f) {
            sActiveLights.push_back(&light);
        }
    }
}

static inline OPTIMIZE_O3 void le_calculate_light_contribution(const LELight& light, Vec3f pos, Vec3f normal, f32 lightIntensityScalar, Vec3f outColor, f32& weight, u8& contribution) {
    // vector to light
    f32 diffX = light.pos[0] - pos[0];
    f32 diffY = light.pos[1] - pos[1];
    f32 diffZ = light.pos[2] - pos[2];

    // squared distance check
    f32 dist2 = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);
    f32 radius2 = light.radius * light.radius;
    if (dist2 > radius2 || dist2 <= 0) { return; }

    // attenuation & intensity
    f32 att = 1.0f - (dist2 / radius2);
    f32 brightness = att * light.intensity * lightIntensityScalar;

    if (light.useSurfaceNormals && normal) {
        // normalize diff
        f32 invLen = rsqrt(dist2);
        diffX *= invLen;
        diffY *= invLen;
        diffZ *= invLen;

        // lambert term
        f32 nl = (normal[0] * diffX) + (normal[1] * diffY) + (normal[2] * diffZ);
        if (nl <= 0.0f) { return; }

        // modulate by normal
        brightness *= nl;
    }

    // accumulate
    outColor[0] += light.color[0] * brightness;
    outColor[1] += light.color[1] * brightness;
    outColor[2] += light.color[2] * brightness;
    weight += brightness;
    contribution++;
}

C_FIELD OPTIMIZE_O3 void le_calculate_vertex_lighting(const Vtx_t* v, Vec3f pos, VEC_OUT Color out) {
    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    u8 contribution = 0;
    for (LELight* light : sActiveLights) {
        le_calculate_light_contribution(*light, pos, NULL, 1.0f, color, weight, contribution);
        if (contribution == sMaxLightsPerVertex) { break; }
    }

    // tone map and output
    Color vtxAmbient = {
        (u8)(v->cn[0] * (gLEAmbientColor[0] / 255.0f)),
        (u8)(v->cn[1] * (gLEAmbientColor[1] / 255.0f)),
        (u8)(v->cn[2] * (gLEAmbientColor[2] / 255.0f)),
    };
    le_tone_map(out, vtxAmbient, color, weight);
}

C_FIELD OPTIMIZE_O3 void le_calculate_lighting_color(Vec3f pos, VEC_OUT Color out, f32 lightIntensityScalar) {
    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    u8 contribution = 0;
    for (LELight* light : sActiveLights) {
        le_calculate_light_contribution(*light, pos, NULL, lightIntensityScalar, color, weight, contribution);
        if (contribution == sMaxLightsPerVertex) { break; }
    }

    // tone map and output
    le_tone_map(out, gLEAmbientColor, color, weight);
}

C_FIELD OPTIMIZE_O3 void le_calculate_lighting_color_with_normal(Vec3f pos, Vec3f normal, VEC_OUT Color out, f32 lightIntensityScalar) {
    // normalize normal
    if (normal) { vec3f_normalize(normal); }

    // clear color
    Vec3f color = { 0 };

    // accumulate lighting
    f32 weight = 1.0f;
    u8 contribution = 0;
    for (LELight* light : sActiveLights) {
        le_calculate_light_contribution(*light, pos, normal, lightIntensityScalar, color, weight, contribution);
        if (contribution == sMaxLightsPerVertex) { break; }
    }

    // tone map and output
    le_tone_map(out, gLEAmbientColor, color, weight);
}

C_FIELD void le_calculate_lighting_dir(Vec3f pos, VEC_OUT Vec3f out) {
    Vec3f lightingDir = { 0, 0, 0 };
    s16 count = 1;

    for (LELight* light : sActiveLights) {
        f32 diffX = light->pos[0] - pos[0];
        f32 diffY = light->pos[1] - pos[1];
        f32 diffZ = light->pos[2] - pos[2];
        f32 dist = (diffX * diffX) + (diffY * diffY) + (diffZ * diffZ);
        f32 radius = light->radius * light->radius;
        if (dist > radius) { continue; }

        Vec3f dir = {
            pos[0] - light->pos[0],
            pos[1] - light->pos[1],
            pos[2] - light->pos[2],
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

C_FIELD s16 le_add_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius, f32 intensity) {
    if (sLightPool.size() >= LE_MAX_LIGHTS) {
        LOG_LUA_LINE("LE light count cannot exceed %d lights!", LE_MAX_LIGHTS);
        return -1;
    }

    LELight newLight;
    newLight.id = ++sLightID;
    newLight.pos[0] = x;
    newLight.pos[1] = y;
    newLight.pos[2] = z;
    newLight.color[0] = r;
    newLight.color[1] = g;
    newLight.color[2] = b;
    newLight.radius = radius;
    newLight.intensity = intensity;
    newLight.useSurfaceNormals = true;

    sLightPool.push_back(newLight);

    le_update_active_lights();

    sEnabled = true;
    return sLightID;
}

C_FIELD void le_remove_light(s16 id) {
    if (id < 0) { return; }

    auto it = std::find_if(sLightPool.begin(), sLightPool.end(),
        [id](const LELight& light) {
            return light.id == id;
        }
    );

    if (it != sLightPool.end()) {
        sLightPool.erase(it);
    }

    le_update_active_lights();
}

C_FIELD s16 le_get_light_count(void) {
    return sLightPool.size();
}

C_FIELD bool le_light_exists(s16 id) {
    if (id < 0) { return false; }

    return std::any_of(sLightPool.begin(), sLightPool.end(),
        [id](const LELight& light) {
            return light.id == id;
        }
    );
}

static LELight* le_find_light(s16 id) {
    if (id < 0) { return nullptr; }

    auto it = std::find_if(sLightPool.begin(), sLightPool.end(),
        [id](const LELight& light) {
            return light.id == id;
        }
    );

    // kinda cursed syntax but it works
    return (it != sLightPool.end()) ? &(*it) : nullptr;
}

C_FIELD void le_get_light_pos(s16 id, VEC_OUT Vec3f out) {
    if (id < 0) { return; }

    if (auto* light = le_find_light(id)) {
        vec3f_set(out, light->pos[0], light->pos[1], light->pos[2]);
    }
}

C_FIELD void le_set_light_pos(s16 id, f32 x, f32 y, f32 z) {
    if (id < 0) { return; }

    if (auto* light = le_find_light(id)) {
        light->pos[0] = x;
        light->pos[1] = y;
        light->pos[2] = z;
    }
}

C_FIELD void le_get_light_color(s16 id, VEC_OUT Color out) {
    if (id < 0) { return; }

    if (auto* light = le_find_light(id)) {
        color_set(out, light->color[0], light->color[1], light->color[2]);
    }
}

C_FIELD void le_set_light_color(s16 id, u8 r, u8 g, u8 b) {
    if (id < 0) { return; }

    if (auto* light = le_find_light(id)) {
        light->color[0] = r;
        light->color[1] = g;
        light->color[2] = b;
    }
}

C_FIELD f32 le_get_light_radius(s16 id) {
    if (id < 0) { return 0.0f; }

    if (auto* light = le_find_light(id)) {
        return light->radius;
    }

    return 0.0f;
}

C_FIELD void le_set_light_radius(s16 id, f32 radius) {
    if (id < 0) { return; }

    if (auto* light = le_find_light(id)) {
        light->radius = radius;
    }

    le_update_active_lights();
}

C_FIELD f32 le_get_light_intensity(s16 id) {
    if (id < 0) { return 0.0f; }

    if (auto* light = le_find_light(id)) {
        return light->intensity;
    }

    return 0.0f;
}

C_FIELD void le_set_light_intensity(s16 id, f32 intensity) {
    if (id < 0) { return; }

    if (auto* light = le_find_light(id)) {
        light->intensity = intensity;
    }

    le_update_active_lights();
}

C_FIELD bool le_get_light_use_surface_normals(s16 id) {
    if (id < 0) { return false; }

    if (auto* light = le_find_light(id)) {
        return light->useSurfaceNormals;
    }

    return false;
}

C_FIELD void le_set_light_use_surface_normals(s16 id, bool useSurfaceNormals) {
    if (id < 0) { return; }

    if (auto* light = le_find_light(id)) {
        light->useSurfaceNormals = useSurfaceNormals;
    }
}

void le_clear(void) {
    sLightPool.clear();
    sLightID = -1;

    color_set(gLEAmbientColor, 127, 127, 127);
}

void le_shutdown(void) {
    sEnabled = false;
    sMode = LE_MODE_AFFECT_ALL_SHADED_AND_COLORED;
    sToneMapping = LE_TONE_MAPPING_WEIGHTED;
    sMaxLightsPerVertex = 4;
    le_clear();
}
