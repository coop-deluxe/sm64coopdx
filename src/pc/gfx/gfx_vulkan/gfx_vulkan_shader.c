#if defined(ENABLE_VULKAN)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#ifndef _LANGUAGE_C
# define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#include "../gfx_cc.h"
#include "../gfx_pc.h"
#include "gfx_vulkan_context.h"
#include "gfx_vulkan_pipeline.h"
#include "gfx_vulkan_shader.h"

#include <volk.h>
#include "glslang/Include/glslang_c_interface.h"
#include "glslang/Public/resource_limits_c.h"

// Same pool/reuse policy as gfx_opengl.c's shader_program_pool - one CC/shader
// combination is retired (its VkPipeline destroyed) whenever the ring buffer
// wraps around and reclaims its slot.
static struct ShaderProgram sShaderPool[CC_MAX_SHADERS];
static uint8_t sShaderPoolSize = 0;
static uint8_t sShaderPoolIndex = 0;

bool gfx_vulkan_shader_init(void) {
    return glslang_initialize_process() != 0;
}

// Destroys every pooled pipeline, then matches gfx_vulkan_shader_init()'s
// glslang_initialize_process() with glslang_finalize_process().
void gfx_vulkan_shader_destroy(void) {
    for (uint8_t i = 0; i < sShaderPoolSize; i++) {
        if (sShaderPool[i].pipeline != VK_NULL_HANDLE) {
            vkDestroyPipeline(gfxVkDevice, sShaderPool[i].pipeline, NULL);
        }
    }
    memset(sShaderPool, 0, sizeof(sShaderPool));
    sShaderPoolSize = 0;
    sShaderPoolIndex = 0;

    glslang_finalize_process();
}

// Finds an already-compiled pipeline for cc's exact hash, if any.
struct ShaderProgram *gfx_vulkan_shader_lookup(struct ColorCombiner *cc) {
    for (uint8_t i = 0; i < sShaderPoolSize; i++) {
        if (sShaderPool[i].hash == cc->hash) {
            return &sShaderPool[i];
        }
    }
    return NULL;
}

// See gfx_vulkan_shader.h.
void gfx_vulkan_shader_get_info(struct ShaderProgram *prg, uint8_t *num_inputs, bool used_textures[2]) {
    *num_inputs = prg->num_inputs;
    used_textures[0] = prg->used_textures[0];
    used_textures[1] = prg->used_textures[1];
}

//////////////////////////////////////////////////////////////////////////////
// GLSL generator - ported from gfx_opengl.c's shader generator. Same
// algorithm/formula logic (shader_item_to_str/append_formula operate on the
// same cc->shader_commands the GL backend reads), adapted to explicit
// layout(location=)/layout(set=,binding=) qualifiers, an in/out varying
// interface instead of attribute/varying, and moving GL's loose per-shader
// uniforms into the shared FrameUBO (set 0) and push-constant blocks
// gfx_vulkan_pipeline.c binds identically for every ColorCombiner pipeline.
//////////////////////////////////////////////////////////////////////////////

// Appends str to buf without a trailing newline, advancing *len.
static void append_str(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
}

// Appends str to buf followed by a newline, advancing *len.
static void append_line(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
    buf[(*len)++] = '\n';
}

// Maps one Color Combiner formula operand to its GLSL expression.
static const char *shader_item_to_str(uint32_t item, bool with_alpha, bool only_alpha, bool inputs_have_alpha, bool hint_single_element) {
    if (!only_alpha) {
        switch (item) {
            case SHADER_0:
                return with_alpha ? "vec4(0.0, 0.0, 0.0, 0.0)" : "vec3(0.0, 0.0, 0.0)";
            case SHADER_1:
                return with_alpha ? "vec4(1.0, 1.0, 1.0, 1.0)" : "vec3(1.0, 1.0, 1.0)";
            case SHADER_INPUT_1:
                return with_alpha || !inputs_have_alpha ? "vInput1" : "vInput1.rgb";
            case SHADER_INPUT_2:
                return with_alpha || !inputs_have_alpha ? "vInput2" : "vInput2.rgb";
            case SHADER_INPUT_3:
                return with_alpha || !inputs_have_alpha ? "vInput3" : "vInput3.rgb";
            case SHADER_INPUT_4:
                return with_alpha || !inputs_have_alpha ? "vInput4" : "vInput4.rgb";
            case SHADER_INPUT_5:
                return with_alpha || !inputs_have_alpha ? "vInput5" : "vInput5.rgb";
            case SHADER_INPUT_6:
                return with_alpha || !inputs_have_alpha ? "vInput6" : "vInput6.rgb";
            case SHADER_INPUT_7:
                return with_alpha || !inputs_have_alpha ? "vInput7" : "vInput7.rgb";
            case SHADER_INPUT_8:
                return with_alpha || !inputs_have_alpha ? "vInput8" : "vInput8.rgb";
            case SHADER_TEXEL0:
                return with_alpha ? "texVal0" : "texVal0.rgb";
            case SHADER_TEXEL0A:
                return hint_single_element ? "texVal0.a" :
                    (with_alpha ? "vec4(texVal0.a, texVal0.a, texVal0.a, texVal0.a)" : "vec3(texVal0.a, texVal0.a, texVal0.a)");
            case SHADER_TEXEL1:
                return with_alpha ? "texVal1" : "texVal1.rgb";
            case SHADER_TEXEL1A:
                return hint_single_element ? "texVal1.a" :
                    (with_alpha ? "vec4(texVal1.a, texVal1.a, texVal1.a, texVal1.a)" : "vec3(texVal1.a, texVal1.a, texVal1.a)");
            case SHADER_COMBINED:
                return with_alpha ? "texel" : "texel.rgb";
            case SHADER_COMBINEDA:
                return hint_single_element ? "texel.a" :
                    (with_alpha ? "vec4(texel.a, texel.a, texel.a, texel.a)" : "vec3(texel.a, texel.a, texel.a)");
            case SHADER_NOISE:
                return with_alpha ? "vec4(noise)" : "vec3(noise)";
        }
    } else {
        switch (item) {
            case SHADER_0: return "0.0";
            case SHADER_1: return "1.0";
            case SHADER_INPUT_1: return "vInput1.a";
            case SHADER_INPUT_2: return "vInput2.a";
            case SHADER_INPUT_3: return "vInput3.a";
            case SHADER_INPUT_4: return "vInput4.a";
            case SHADER_INPUT_5: return "vInput5.a";
            case SHADER_INPUT_6: return "vInput6.a";
            case SHADER_INPUT_7: return "vInput7.a";
            case SHADER_INPUT_8: return "vInput8.a";
            case SHADER_TEXEL0: return "texVal0.a";
            case SHADER_TEXEL0A: return "texVal0.a";
            case SHADER_TEXEL1: return "texVal1.a";
            case SHADER_TEXEL1A: return "texVal1.a";
            case SHADER_COMBINED: return "texel.a";
            case SHADER_COMBINEDA: return "texel.a";
            case SHADER_NOISE: return "noise";
        }
    }
    return "unknown";
}

// Emits one RDP Color Combiner formula (single/multiply/mix/general form) as
// a GLSL expression.
static void append_formula(char *buf, size_t *len, uint8_t *cmd, bool do_single, bool do_multiply, bool do_mix, bool with_alpha, bool only_alpha, bool opt_alpha) {
    if (do_single) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    } else if (do_multiply) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
    } else if (do_mix) {
        append_str(buf, len, "mix(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, ")");
    } else {
        append_str(buf, len, "(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " - ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ") * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, " + ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    }
}

// Identical text in every fragment shader variant - matches the single
// shared pipeline layout gfx_vulkan_pipeline.c binds for every CC. std140/
// std430 layouts are spelled out explicitly since SPIR-V, unlike desktop GL,
// has no implicit default.
static const char *kFrameUboBlock =
    "layout(std140, set = 0, binding = 0) uniform FrameUBO {\n"
    "    float uFrameCount;\n"
    "    vec3 uLightmapColor;\n"
    "    int uShaderFlags[8];\n"
    "    float uShaderFlagValues[8];\n"
    "    int uFilter;\n"
    "} frameUbo;\n";

static const char *kPushConstantBlock =
    "layout(push_constant, std430) uniform PushConstants {\n"
    "    vec2 uTex0Size;\n"
    "    int uTex0Filter;\n"
    "    vec2 uTex1Size;\n"
    "    int uTex1Filter;\n"
    "} pc;\n";

// Builds the vertex shader source for one Color Combiner: a passthrough that
// forwards position/texcoords/fog/lightmap/CC-input attributes to varyings.
static void generate_vertex_shader(char *vs_buf, size_t *vs_len, struct CCFeatures *ccf, bool opt_fog, bool opt_light_map, bool opt_alpha) {
    int loc = 0;

    append_line(vs_buf, vs_len, "#version 450");
    *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec4 aVtxPos;\n", loc++);

    int varying = 0;
    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec2 aTexCoord%d;\n", loc++, t);
            *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec2 vTexCoord%d;\n", varying++, t);
        }
    }
    if (opt_fog) {
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec4 aFog;\n", loc++);
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec4 vFog;\n", varying++);
    }
    if (opt_light_map) {
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec2 aLightMap;\n", loc++);
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec2 vLightMap;\n", varying++);
    }
    for (int i = 0; i < ccf->num_inputs; i++) {
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) in vec%d aInput%d;\n", loc++, opt_alpha ? 4 : 3, i + 1);
        *vs_len += sprintf(vs_buf + *vs_len, "layout(location = %d) out vec%d vInput%d;\n", varying++, opt_alpha ? 4 : 3, i + 1);
    }

    append_line(vs_buf, vs_len, "void main() {");
    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *vs_len += sprintf(vs_buf + *vs_len, "vTexCoord%d = aTexCoord%d;\n", t, t);
        }
    }
    if (opt_fog) { append_line(vs_buf, vs_len, "vFog = aFog;"); }
    if (opt_light_map) { append_line(vs_buf, vs_len, "vLightMap = aLightMap;"); }
    for (int i = 0; i < ccf->num_inputs; i++) {
        *vs_len += sprintf(vs_buf + *vs_len, "vInput%d = aInput%d;\n", i + 1, i + 1);
    }
    append_line(vs_buf, vs_len, "gl_Position = aVtxPos;");
    append_line(vs_buf, vs_len, "}");
}

// Builds the fragment shader source for one Color Combiner: samples up to 2
// textures, evaluates the CC formula stages, then applies optional fog/
// dither/world-geometry post-processing.
static void generate_fragment_shader(char *fs_buf, size_t *fs_len, struct ColorCombiner *cc, struct CCFeatures *ccf,
                                      bool opt_alpha, bool opt_fog, bool opt_texture_edge, bool opt_2cycle,
                                      bool opt_light_map, bool opt_dither, bool world_geometry) {
    append_line(fs_buf, fs_len, "#version 450");

    int varying = 0;
    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec2 vTexCoord%d;\n", varying++, t);
        }
    }
    if (opt_fog) {
        *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec4 vFog;\n", varying++);
    }
    if (opt_light_map) {
        *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec2 vLightMap;\n", varying++);
    }
    for (int i = 0; i < ccf->num_inputs; i++) {
        *fs_len += sprintf(fs_buf + *fs_len, "layout(location = %d) in vec%d vInput%d;\n", varying++, opt_alpha ? 4 : 3, i + 1);
    }

    append_line(fs_buf, fs_len, "layout(location = 0) out vec4 fragColor;");

    for (int t = 0; t < 2; t++) {
        if (ccf->used_textures[t]) {
            *fs_len += sprintf(fs_buf + *fs_len, "layout(set = 1, binding = %d) uniform sampler2D uTex%d;\n", t, t);
        }
    }

    // 3-point texture filtering (ArthurCarvalho / twinaphex, mupen64plus-libretro) -
    // ported from gfx_opengl.c, texture2D() -> texture() for GLSL 450/SPIR-V.
    if (ccf->used_textures[0] || ccf->used_textures[1]) {
        append_line(fs_buf, fs_len, "#define TEX_OFFSET(off) texture(tex, texCoord - (off)/texSize)");
        append_line(fs_buf, fs_len, "vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {");
        append_line(fs_buf, fs_len, "    vec2 offset = fract(texCoord*texSize - vec2(0.5));");
        append_line(fs_buf, fs_len, "    offset -= step(1.0, offset.x + offset.y);");
        append_line(fs_buf, fs_len, "    vec4 c0 = TEX_OFFSET(offset);");
        append_line(fs_buf, fs_len, "    vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));");
        append_line(fs_buf, fs_len, "    vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));");
        append_line(fs_buf, fs_len, "    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);");
        append_line(fs_buf, fs_len, "}");
        // `filter` is a GLSL reserved word for SPIR-V targets (unlike desktop
        // GL/GLSL ES, where gfx_opengl.c's identical parameter name compiles
        // fine) - renamed to filterMode here to avoid glslang rejecting it.
        append_line(fs_buf, fs_len, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter, in int filterMode) {");
        append_line(fs_buf, fs_len, "    if (dofilter && filterMode == 2)");
        append_line(fs_buf, fs_len, "        return filter3point(tex, uv, texSize);");
        append_line(fs_buf, fs_len, "    else");
        append_line(fs_buf, fs_len, "        return texture(tex, uv);");
        append_line(fs_buf, fs_len, "}");
    }

    // world_geometry post-process helpers - ported from gfx_opengl.c (pure
    // math, no GL-specific calls). gl_FragCoord's origin is top-left in
    // Vulkan vs. bottom-left in GL, so dither4x4/scanlines end up mirrored
    // vertically relative to the OpenGL backend - both are periodic patterns
    // so this isn't visually distinguishable.
    if (world_geometry) {
        append_line(fs_buf, fs_len, "float dither4x4(vec2 position, float brightness) {");
        append_line(fs_buf, fs_len, "    int x = int(mod(position.x, 4.0));");
        append_line(fs_buf, fs_len, "    int y = int(mod(position.y, 4.0));");
        append_line(fs_buf, fs_len, "    int index = x + y * 4;");
        append_line(fs_buf, fs_len, "    float limit = 0.0;");
        append_line(fs_buf, fs_len, "    if (x < 8) {");
        append_line(fs_buf, fs_len, "        if (index == 0) limit = 0.0625;");
        append_line(fs_buf, fs_len, "        if (index == 1) limit = 0.5625;");
        append_line(fs_buf, fs_len, "        if (index == 2) limit = 0.1875;");
        append_line(fs_buf, fs_len, "        if (index == 3) limit = 0.6875;");
        append_line(fs_buf, fs_len, "        if (index == 4) limit = 0.8125;");
        append_line(fs_buf, fs_len, "        if (index == 5) limit = 0.3125;");
        append_line(fs_buf, fs_len, "        if (index == 6) limit = 0.9375;");
        append_line(fs_buf, fs_len, "        if (index == 7) limit = 0.4375;");
        append_line(fs_buf, fs_len, "        if (index == 8) limit = 0.25;");
        append_line(fs_buf, fs_len, "        if (index == 9) limit = 0.75;");
        append_line(fs_buf, fs_len, "        if (index == 10) limit = 0.125;");
        append_line(fs_buf, fs_len, "        if (index == 11) limit = 0.625;");
        append_line(fs_buf, fs_len, "        if (index == 12) limit = 1.0;");
        append_line(fs_buf, fs_len, "        if (index == 13) limit = 0.5;");
        append_line(fs_buf, fs_len, "        if (index == 14) limit = 0.875;");
        append_line(fs_buf, fs_len, "        if (index == 15) limit = 0.375;");
        append_line(fs_buf, fs_len, "    }");
        append_line(fs_buf, fs_len, "    return brightness < limit ? 0.0 : 1.0;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "vec3 rgb2hsv(vec3 c) {");
        append_line(fs_buf, fs_len, "    vec4 K = vec4(0.0, -1.0/3.0, 2.0/3.0, -1.0);");
        append_line(fs_buf, fs_len, "    vec4 p = mix(vec4(c.bg, K.wz),");
        append_line(fs_buf, fs_len, "                 vec4(c.gb, K.xy),");
        append_line(fs_buf, fs_len, "                 step(c.b, c.g));");
        append_line(fs_buf, fs_len, "    vec4 q = mix(vec4(p.xyw, c.r),");
        append_line(fs_buf, fs_len, "                 vec4(c.r, p.yzx),");
        append_line(fs_buf, fs_len, "                 step(p.x, c.r));");
        append_line(fs_buf, fs_len, "    float d = q.x - min(q.w, q.y);");
        append_line(fs_buf, fs_len, "    float e = 1.0e-10;");
        append_line(fs_buf, fs_len, "    return vec3(");
        append_line(fs_buf, fs_len, "        abs(q.z + (q.w - q.y) / (6.0 * d + e)),");
        append_line(fs_buf, fs_len, "        d / (q.x + e),");
        append_line(fs_buf, fs_len, "        q.x");
        append_line(fs_buf, fs_len, "    );");
        append_line(fs_buf, fs_len, "}");
        append_line(fs_buf, fs_len, "");
        append_line(fs_buf, fs_len, "vec3 hsv2rgb(vec3 c) {");
        append_line(fs_buf, fs_len, "    vec3 p = abs(fract(c.xxx + vec3(0.0, 2.0/3.0, 1.0/3.0)) * 6.0 - 3.0);");
        append_line(fs_buf, fs_len, "    return c.z * mix(vec3(1.0), clamp(p - 1.0, 0.0, 1.0), c.y);");
        append_line(fs_buf, fs_len, "}");
    }

    if ((opt_alpha && opt_dither) || ccf->do_noise) {
        append_line(fs_buf, fs_len, "float random(in vec3 value) {");
        append_line(fs_buf, fs_len, "    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));");
        append_line(fs_buf, fs_len, "    return fract(sin(random) * 143758.5453);");
        append_line(fs_buf, fs_len, "}");
    }

    append_line(fs_buf, fs_len, kFrameUboBlock);
    append_line(fs_buf, fs_len, kPushConstantBlock);

    append_line(fs_buf, fs_len, "void main() {");

    if ((opt_alpha && opt_dither) || ccf->do_noise) {
        append_line(fs_buf, fs_len, "float noise = random(floor(vec3(gl_FragCoord.xy, frameUbo.uFrameCount)));");
    }

    if (ccf->used_textures[0]) {
        append_line(fs_buf, fs_len, "vec4 texVal0 = sampleTex(uTex0, vTexCoord0, pc.uTex0Size, pc.uTex0Filter != 0, frameUbo.uFilter);");
    }
    if (ccf->used_textures[1]) {
        if (opt_light_map) {
            append_line(fs_buf, fs_len, "vec4 texVal1 = sampleTex(uTex1, vLightMap, pc.uTex1Size, pc.uTex1Filter != 0, frameUbo.uFilter);");
            append_line(fs_buf, fs_len, "texVal0.rgb *= frameUbo.uLightmapColor.rgb;");
            append_line(fs_buf, fs_len, "texVal1.rgb = texVal1.rgb * texVal1.rgb + texVal1.rgb;");
        } else {
            append_line(fs_buf, fs_len, "vec4 texVal1 = sampleTex(uTex1, vTexCoord1, pc.uTex1Size, pc.uTex1Filter != 0, frameUbo.uFilter);");
        }
    }

    append_line(fs_buf, fs_len, opt_alpha ? "vec4 texel = vec4(0.0, 0.0, 0.0, 0.0);" : "vec3 texel = vec3(0.0, 0.0, 0.0);");

    for (int i = 0; i < (opt_2cycle + 1); i++) {
        uint8_t *cmd = &cc->shader_commands[i * 8];
        append_str(fs_buf, fs_len, "texel = ");
        if (!ccf->color_alpha_same[i] && opt_alpha) {
            append_str(fs_buf, fs_len, "vec4(");
            append_formula(fs_buf, fs_len, cmd, ccf->do_single[i*2+0], ccf->do_multiply[i*2+0], ccf->do_mix[i*2+0], false, false, true);
            append_str(fs_buf, fs_len, ", ");
            append_formula(fs_buf, fs_len, cmd, ccf->do_single[i*2+1], ccf->do_multiply[i*2+1], ccf->do_mix[i*2+1], true, true, true);
            append_str(fs_buf, fs_len, ")");
        } else {
            append_formula(fs_buf, fs_len, cmd, ccf->do_single[i*2+0], ccf->do_multiply[i*2+0], ccf->do_mix[i*2+0], opt_alpha, false, opt_alpha);
        }
        append_line(fs_buf, fs_len, ";");

        if (i == 0) {
            append_line(fs_buf, fs_len, "texel = mod(texel + 0.5, 2.0) - 0.5;");
        }
    }

    append_line(fs_buf, fs_len, "texel = clamp(mod(texel + 0.5, 2.0) - 0.5, 0.0, 1.0);");

    if (opt_texture_edge && opt_alpha) {
        append_line(fs_buf, fs_len, "if (texel.a > 0.3) texel.a = 1.0; else discard;");
    }

    if (world_geometry) {
        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[0] == 1) {");
        append_line(fs_buf, fs_len, "vec3 hsv = rgb2hsv(texel.rgb);");
        append_line(fs_buf, fs_len, "hsv.x = fract(hsv.x + frameUbo.uShaderFlagValues[0]);");
        append_line(fs_buf, fs_len, "vec3 finalColor = hsv2rgb(hsv);");
        append_line(fs_buf, fs_len, "texel.rgb = finalColor;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[1] == 1) {");
        append_line(fs_buf, fs_len, "const vec3 w = vec3(0.2125, 0.7154, 0.0721);");
        append_line(fs_buf, fs_len, "vec3 intensity = vec3(dot(texel.rgb, w));");
        append_line(fs_buf, fs_len, "texel.rgb = mix(intensity, texel.rgb, frameUbo.uShaderFlagValues[1]);");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[2] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb *= frameUbo.uShaderFlagValues[2];");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[3] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb = 0.5 + frameUbo.uShaderFlagValues[3] * (texel.rgb - 0.5);");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[4] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb = texel.rgb + (frameUbo.uShaderFlagValues[4] - 2) * texel.rgb + texel.rgb;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[5] == 1) {");
        append_line(fs_buf, fs_len, "texel.rgb *= dither4x4(gl_FragCoord.xy, dot(texel.rgb, vec3(0.299, 0.587, 0.114)));");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[6] == 1) {");
        append_line(fs_buf, fs_len, "int levels = int(max(1.0, frameUbo.uShaderFlagValues[6]));");
        append_line(fs_buf, fs_len, "texel.rgb = floor(texel.rgb * levels) / levels;");
        append_line(fs_buf, fs_len, "}");

        append_line(fs_buf, fs_len, "if (frameUbo.uShaderFlags[7] == 1) {");
        append_line(fs_buf, fs_len, "float scan = sin(gl_FragCoord.y * 1.5) * 0.04;");
        append_line(fs_buf, fs_len, "texel.rgb -= scan * frameUbo.uShaderFlagValues[7];");
        append_line(fs_buf, fs_len, "}");
    }

    if (opt_fog) {
        if (opt_alpha) {
            append_line(fs_buf, fs_len, "texel = vec4(mix(texel.rgb, vFog.rgb, vFog.a), texel.a);");
        } else {
            append_line(fs_buf, fs_len, "texel = mix(texel, vFog.rgb, vFog.a);");
        }
    }

    if (opt_alpha && opt_dither) {
        append_line(fs_buf, fs_len, "texel.a = noise < texel.a ? 1.0 : 0.0;");
    }

    append_line(fs_buf, fs_len, opt_alpha ? "fragColor = texel;" : "fragColor = vec4(texel, 1.0);");
    append_line(fs_buf, fs_len, "}");
}

// Preprocesses/parses/links `source` and generates SPIR-V; *outWords is
// caller-owned (malloc'd).
static bool compile_stage(const char *source, glslang_stage_t stage, const char *stageName, uint32_t **outWords, size_t *outWordCount) {
    glslang_input_t input = {
        .language = GLSLANG_SOURCE_GLSL,
        .stage = stage,
        .client = GLSLANG_CLIENT_VULKAN,
        .client_version = GLSLANG_TARGET_VULKAN_1_3,
        .target_language = GLSLANG_TARGET_SPV,
        .target_language_version = GLSLANG_TARGET_SPV_1_6,
        .code = source,
        .default_version = 450,
        .default_profile = GLSLANG_NO_PROFILE,
        .messages = GLSLANG_MSG_DEFAULT_BIT,
        .resource = glslang_default_resource(),
    };

    glslang_shader_t *shader = glslang_shader_create(&input);
    if (!glslang_shader_preprocess(shader, &input)) {
        fprintf(stderr, "[vulkan] %s shader preprocess failed:\n%s\n--- source ---\n%s\n", stageName, glslang_shader_get_info_log(shader), source);
        glslang_shader_delete(shader);
        return false;
    }
    if (!glslang_shader_parse(shader, &input)) {
        fprintf(stderr, "[vulkan] %s shader parse failed:\n%s\n--- source ---\n%s\n", stageName, glslang_shader_get_info_log(shader), source);
        glslang_shader_delete(shader);
        return false;
    }

    glslang_program_t *program = glslang_program_create();
    glslang_program_add_shader(program, shader);
    if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT)) {
        fprintf(stderr, "[vulkan] %s shader link failed:\n%s\n", stageName, glslang_program_get_info_log(program));
        glslang_program_delete(program);
        glslang_shader_delete(shader);
        return false;
    }

    glslang_program_SPIRV_generate(program, stage);
    size_t wordCount = glslang_program_SPIRV_get_size(program);
    uint32_t *words = malloc(wordCount * sizeof(uint32_t));
    if (words) {
        memcpy(words, glslang_program_SPIRV_get_ptr(program), wordCount * sizeof(uint32_t));
    }

    glslang_program_delete(program);
    glslang_shader_delete(shader);

    if (!words) { return false; }
    *outWords = words;
    *outWordCount = wordCount;
    return true;
}

// Wraps a SPIR-V word array in a VkShaderModule.
static VkShaderModule create_shader_module(const uint32_t *words, size_t wordCount) {
    VkShaderModuleCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = wordCount * sizeof(uint32_t),
        .pCode = words,
    };
    VkShaderModule module = VK_NULL_HANDLE;
    vkCreateShaderModule(gfxVkDevice, &createInfo, NULL, &module);
    return module;
}

// Generates GLSL, compiles it to SPIR-V, builds a VkPipeline for this Color
// Combiner, and stores it in the ring-buffer shader pool. This is the one
// point in the frame where the CPU can stall - compiling GLSL->SPIR-V plus
// vkCreateGraphicsPipelines for a CC combination never seen before -
// gfx_vulkan_pipeline.c's disk-persisted VkPipelineCache makes repeat runs
// cheap once a combination has been compiled once anywhere on this machine,
// but a first encounter within a single run still pays the full cost
// (measured under VULKAN_DEBUG, not yet mitigated).
struct ShaderProgram *gfx_vulkan_shader_create_and_load(struct ColorCombiner *cc) {
#if defined(VULKAN_DEBUG)
    uint64_t perfFreq = SDL_GetPerformanceFrequency();
    uint64_t tStart = SDL_GetPerformanceCounter();
#endif

    struct CCFeatures ccf = { 0 };
    gfx_cc_get_features(cc, &ccf);

    bool opt_alpha = cc->cm.use_alpha;
    bool opt_fog = cc->cm.use_fog;
    bool opt_texture_edge = cc->cm.texture_edge;
    bool opt_2cycle = cc->cm.use_2cycle;
    bool opt_light_map = cc->cm.light_map;
    bool world_geometry = cc->cm.world_geometry;
    bool opt_dither = cc->cm.use_dither;

    // Fixed-size scratch buffers for the generated GLSL text - same pattern
    // gfx_opengl.c uses (8192 bytes there; doubled here since explicit
    // layout()/set qualifiers make the Vulkan variant longer). Not bounds-
    // checked against overflow, matching the existing GL backend's risk
    // tolerance for this code path.
    char *vs_buf = malloc(16384);
    char *fs_buf = malloc(16384);
    size_t vs_len = 0, fs_len = 0;
    if (!vs_buf || !fs_buf) {
        free(vs_buf);
        free(fs_buf);
        return NULL;
    }

    generate_vertex_shader(vs_buf, &vs_len, &ccf, opt_fog, opt_light_map, opt_alpha);
    generate_fragment_shader(fs_buf, &fs_len, cc, &ccf, opt_alpha, opt_fog, opt_texture_edge, opt_2cycle, opt_light_map, opt_dither, world_geometry);
    vs_buf[vs_len] = '\0';
    fs_buf[fs_len] = '\0';

#if defined(VULKAN_DEBUG)
    uint64_t tAfterGen = SDL_GetPerformanceCounter();
#endif

    uint32_t *vsWords = NULL, *fsWords = NULL;
    size_t vsWordCount = 0, fsWordCount = 0;
    bool ok = compile_stage(vs_buf, GLSLANG_STAGE_VERTEX, "vertex", &vsWords, &vsWordCount) &&
              compile_stage(fs_buf, GLSLANG_STAGE_FRAGMENT, "fragment", &fsWords, &fsWordCount);
    free(vs_buf);
    free(fs_buf);
    if (!ok) {
        free(vsWords);
        free(fsWords);
        return NULL;
    }

#if defined(VULKAN_DEBUG)
    uint64_t tAfterSpirv = SDL_GetPerformanceCounter();
#endif

    VkShaderModule vertModule = create_shader_module(vsWords, vsWordCount);
    VkShaderModule fragModule = create_shader_module(fsWords, fsWordCount);
    free(vsWords);
    free(fsWords);
    if (vertModule == VK_NULL_HANDLE || fragModule == VK_NULL_HANDLE) {
        vkDestroyShaderModule(gfxVkDevice, vertModule, NULL);
        vkDestroyShaderModule(gfxVkDevice, fragModule, NULL);
        return NULL;
    }

    struct ShaderProgram *prg = &sShaderPool[sShaderPoolIndex];
    if (prg->pipeline != VK_NULL_HANDLE) {
        // Ring buffer wrapped around - this slot's old pipeline is being
        // retired. Safe without a device-idle wait: gfx_pc.c only reaches
        // here after a gfx_flush() of anything using the previous
        // occupant's pipeline, and gfx_vulkan_frame_start() already waited
        // out the frame-in-flight slot whose command buffer might reference it.
        vkDestroyPipeline(gfxVkDevice, prg->pipeline, NULL);
    }
    sShaderPoolIndex = (sShaderPoolIndex + 1) % CC_MAX_SHADERS;
    if (sShaderPoolSize < CC_MAX_SHADERS) { sShaderPoolSize++; }

    memset(prg, 0, sizeof(*prg));
    prg->hash = cc->hash;
    prg->num_inputs = (uint8_t)ccf.num_inputs;
    prg->used_textures[0] = ccf.used_textures[0];
    prg->used_textures[1] = ccf.used_textures[1];
    prg->opt_alpha = opt_alpha;
    prg->used_noise = (opt_alpha && opt_dither) || ccf.do_noise;
    prg->used_lightmap = opt_light_map;
    prg->world_geometry = world_geometry;

    // Vertex layout, baked as fixed pipeline state - same incremental
    // computation as gfx_opengl.c's equivalent loop.
    size_t cnt = 0;
    size_t num_floats = 4;
    prg->attrib_sizes[cnt++] = 4; // aVtxPos
    for (int t = 0; t < 2; t++) {
        if (ccf.used_textures[t]) {
            prg->attrib_sizes[cnt++] = 2;
            num_floats += 2;
        }
    }
    if (opt_fog) {
        prg->attrib_sizes[cnt++] = 4;
        num_floats += 4;
    }
    if (opt_light_map) {
        prg->attrib_sizes[cnt++] = 2;
        num_floats += 2;
    }
    for (int i = 0; i < ccf.num_inputs; i++) {
        prg->attrib_sizes[cnt++] = opt_alpha ? 4 : 3;
        num_floats += opt_alpha ? 4 : 3;
    }
    prg->num_attribs = (uint8_t)cnt;
    prg->num_floats = (uint8_t)num_floats;

    prg->pipeline = gfx_vulkan_pipeline_create(vertModule, fragModule, prg);

    vkDestroyShaderModule(gfxVkDevice, vertModule, NULL);
    vkDestroyShaderModule(gfxVkDevice, fragModule, NULL);

#if defined(VULKAN_DEBUG)
    uint64_t tEnd = SDL_GetPerformanceCounter();
    double toMs = 1000.0 / (double)perfFreq;
    fprintf(stderr, "[vulkan] new pipeline for CC 0x%016llx: %.2fms total (glsl=%.2fms spirv=%.2fms pipeline=%.2fms)\n",
            (unsigned long long)cc->hash, (double)(tEnd - tStart) * toMs,
            (double)(tAfterGen - tStart) * toMs, (double)(tAfterSpirv - tAfterGen) * toMs,
            (double)(tEnd - tAfterSpirv) * toMs);
#endif

    if (prg->pipeline == VK_NULL_HANDLE) {
        memset(prg, 0, sizeof(*prg));
        return NULL;
    }

    return prg;
}

#endif // ENABLE_VULKAN
