#include <stdlib.h>
#include <string.h>

#include <PR/ultratypes.h>

#if defined(_WIN32) || defined(OSX_BUILD)
# define GLEW_STATIC
# include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#include <SDL2/SDL.h>
#ifdef USE_GLES
#include <SDL2/SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

#include "gfx_pc.h"
#include "gfx_shader.h"

#include "pc/pc_main.h"
#include "pc/lua/smlua.h"
#include "pc/debuglog.h"

#define MAX_UNIFORM_CODE 65536

struct ShaderInput *gShaderInputs = NULL;
struct ShaderInput *gPostProcessShaderInputs = NULL;
struct ShaderBinding *gShaderBindings = NULL;
struct ShaderBinding *gPostProcessShaderBindings = NULL;

const char *gDefaultPostProcessVertexShader = ""
    "in vec4 aVtxPos;\n"
    "out vec4 vVtxPos;\n" // exists for convenience of mods
    "in vec2 aTexCoord;\n"
    "out vec2 vTexCoord;\n"
    "void main() {\n"
    "    vVtxPos = aVtxPos;\n"
    "    vTexCoord = aTexCoord;\n"
    "    gl_Position = aVtxPos;\n"
    "}\n";

const char *gDefaultPostProcessFragmentShader = ""
    "uniform sampler2D uPassTex;\n"
    "in vec4 vVtxPos;\n" // exists for convenience of mods
    "in vec2 vTexCoord;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = texture(uPassTex, vTexCoord);\n"
    "}\n";

static int sShaderInputCount = 0;
static int sShaderOutputCount = 0;
static int sShaderUniformBlockCount = 0;
static bool sShaderInsideCustomUniformBlock = false;
static bool sShaderHasVersion = false;

static char sShaderUniformCode[MAX_UNIFORM_CODE] = { 0 };

static const char *defaultUniformBlockName = "DefaultUniformBufferObject";

static void append_str(char *buf, size_t len, const char *str) {
    if (!buf) { return; }
    size_t currentLength = strlen(buf);
    if (len > currentLength + 1) {
        strncat(buf, str, len - currentLength - 1);
    }
}

static void append_and_realloc_str(char **buf, size_t *len, const char *str) {
    size_t requiredLength = strlen(str) + strlen(*buf) + 1; // get required length
    if (requiredLength >= *len) { // if we aren't at capacity, increase capacity
        // grab new length
        size_t newLength = (*len == 0 ? requiredLength : *len * 2);
        if (newLength < requiredLength) {
            newLength = requiredLength; // make sure we hit the required length always
        }

        char *reallocatedBuffer = realloc(*buf, newLength); // reallocate to temp buffer
        if (reallocatedBuffer) {
            *len = newLength; // set length
            *buf = reallocatedBuffer; // set buffer on success to reallocated buffer
        }
    }
    append_str(*buf, *len, str);
}

static void append_line(char *buf, size_t len, const char *str) {
    append_str(buf, len, str);
    append_str(buf, len, "\n");
}

static const char *shader_item_to_str(uint32_t item, bool with_alpha, bool only_alpha, bool hint_single_element) {
    if (!only_alpha) {
        switch (item) {
            case SHADER_0:
                return with_alpha ? "vec4(0.0, 0.0, 0.0, 0.0)" : "vec3(0.0, 0.0, 0.0)";
            case SHADER_1:
                return with_alpha ? "vec4(1.0, 1.0, 1.0, 1.0)" : "vec3(1.0, 1.0, 1.0)";
            case SHADER_INPUT_1:
                return with_alpha ? "vInput1" : "vInput1.rgb";
            case SHADER_INPUT_2:
                return with_alpha ? "vInput2" : "vInput2.rgb";
            case SHADER_INPUT_3:
                return with_alpha ? "vInput3" : "vInput3.rgb";
            case SHADER_INPUT_4:
                return with_alpha ? "vInput4" : "vInput4.rgb";
            case SHADER_INPUT_5:
                return with_alpha ? "vInput5" : "vInput5.rgb";
            case SHADER_INPUT_6:
                return with_alpha ? "vInput6" : "vInput6.rgb";
            case SHADER_INPUT_7:
                return with_alpha ? "vInput7" : "vInput7.rgb";
            case SHADER_INPUT_8:
                return with_alpha ? "vInput8" : "vInput8.rgb";
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
            case SHADER_0:
                return "0.0";
            case SHADER_1:
                return "1.0";
            case SHADER_INPUT_1:
                return "vInput1.a";
            case SHADER_INPUT_2:
                return "vInput2.a";
            case SHADER_INPUT_3:
                return "vInput3.a";
            case SHADER_INPUT_4:
                return "vInput4.a";
            case SHADER_INPUT_5:
                return "vInput5.a";
            case SHADER_INPUT_6:
                return "vInput6.a";
            case SHADER_INPUT_7:
                return "vInput7.a";
            case SHADER_INPUT_8:
                return "vInput8.a";
            case SHADER_TEXEL0:
                return "texVal0.a";
            case SHADER_TEXEL0A:
                return "texVal0.a";
            case SHADER_TEXEL1:
                return "texVal1.a";
            case SHADER_TEXEL1A:
                return "texVal1.a";
            case SHADER_COMBINED:
                return "texel.a";
            case SHADER_COMBINEDA:
                return "texel.a";
            case SHADER_NOISE:
                return "noise";
        }
    }
    return "unknown";
}

static void append_formula(char *buf, size_t len, uint8_t* cmd, bool do_single, bool do_multiply, bool do_mix, bool with_alpha, bool only_alpha) {
    if (do_single) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, false));
    } else if (do_multiply) {
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, false));
        append_str(buf, len, " * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, true));
    } else if (do_mix) {
        append_str(buf, len, "mix(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, true));
        append_str(buf, len, ")");
    } else {
        append_str(buf, len, "(");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 0], with_alpha, only_alpha, false));
        append_str(buf, len, " - ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 1], with_alpha, only_alpha, false));
        append_str(buf, len, ") * ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 2], with_alpha, only_alpha, true));
        append_str(buf, len, " + ");
        append_str(buf, len, shader_item_to_str(cmd[only_alpha * 4 + 3], with_alpha, only_alpha, false));
    }
}

char *gfx_get_default_vertex_shader_from_cc(struct ColorCombiner *cc) {
    struct CCFeatures ccf = { 0 };
    gfx_cc_get_features(cc, &ccf);

    bool optFog = cc->cm.use_fog;
    bool optTexPersp = cc->cm.tex_persp;

    static char sVsBuf[8192] = { 0 };
    sVsBuf[0] = '\0';
    size_t vsLen = sizeof(sVsBuf);

    append_line(sVsBuf, vsLen, "in vec4 aVtxPos;");
    append_line(sVsBuf, vsLen, "in vec4 aLocalPos;");
    for (int t = 0; t < 2; t++) {
        char texCoordBuf[128] = { 0 };
        snprintf(texCoordBuf, sizeof(texCoordBuf), "in vec2 aTexCoord%d;\n%sout vec2 vTexCoord%d;\n", t, optTexPersp ? "" : "noperspective ", t);
        append_str(sVsBuf, vsLen, texCoordBuf);
    }
    append_line(sVsBuf, vsLen, "in vec2 aLightMap;");
    append_line(sVsBuf, vsLen, "out vec2 vLightMap;");
    for (int i = 0; i < CC_MAX_INPUTS; i++) {
        char inputBuf[128] = { 0 };
        snprintf(inputBuf, sizeof(inputBuf), "in vec4 aInput%d;\nout vec4 vInput%d;\n", i + 1, i + 1);
        append_str(sVsBuf, vsLen, inputBuf);
    }
    append_line(sVsBuf, vsLen, "in vec3 aNormal;");
    append_line(sVsBuf, vsLen, "in vec3 aBarycentric;");
    if (optFog) {
        append_line(sVsBuf, vsLen, "out float vFogZ;");
        append_line(sVsBuf, vsLen, "uniform float uFogMul;");
        append_line(sVsBuf, vsLen, "uniform float uFogIntensity;");
        append_line(sVsBuf, vsLen, "uniform float uFogOffset;");
        append_line(sVsBuf, vsLen, "uniform float uDepthZSub;");
        append_line(sVsBuf, vsLen, "uniform float uDepthZMult;");
        append_line(sVsBuf, vsLen, "uniform float uDepthZAdd;");
    }
    append_line(sVsBuf, vsLen, "void main() {");
    for (int t = 0; t < 2; t++) {
        char texCoordBuf[128] = { 0 };
        snprintf(texCoordBuf, sizeof(texCoordBuf), "vTexCoord%d = aTexCoord%d;\n", t, t);
        append_str(sVsBuf, vsLen, texCoordBuf);
    }

    append_line(sVsBuf, vsLen, "vLightMap = aLightMap;");
    for (int i = 0; i < CC_MAX_INPUTS; i++) {
        char inputBuf[128] = { 0 };
        snprintf(inputBuf, sizeof(inputBuf), "vInput%d = aInput%d;\n", i + 1, i + 1);
        append_str(sVsBuf, vsLen, inputBuf);
    }
    append_line(sVsBuf, vsLen, "gl_Position = aVtxPos;");

    if (optFog) {
        append_line(sVsBuf, vsLen, "float w = max(abs(aVtxPos.w), 0.001);");
        append_line(sVsBuf, vsLen, "float winv = 1.0 / w;");
        append_line(sVsBuf, vsLen, "float adjClipZ = aVtxPos.z;");
        append_line(sVsBuf, vsLen, "adjClipZ -= uDepthZSub;");
        append_line(sVsBuf, vsLen, "adjClipZ *= uDepthZMult;");
        append_line(sVsBuf, vsLen, "adjClipZ += uDepthZAdd;");
        append_line(sVsBuf, vsLen, "float fog_z = (adjClipZ * winv * uFogMul * uFogIntensity) + uFogOffset;");
        append_line(sVsBuf, vsLen, "vFogZ = clamp(fog_z / 255.0, 0.0, 1.0);");
    }

    append_line(sVsBuf, vsLen, "}");

    sVsBuf[vsLen-1] = '\0';

    return sVsBuf;
}

char *gfx_get_default_fragment_shader_from_cc(struct ColorCombiner *cc) {
    struct CCFeatures ccf = { 0 };
    gfx_cc_get_features(cc, &ccf);

    bool optAlpha = cc->cm.use_alpha;
    bool optFog = cc->cm.use_fog;
    bool optTextureEdge = cc->cm.texture_edge;
    bool opt2Cycle = cc->cm.use_2cycle;
    bool optLightMap = cc->cm.light_map;
    bool optTexPersp = cc->cm.tex_persp;
    bool optWorldGeometry = cc->cm.world_geometry;
    bool optDither = cc->cm.use_dither;

    static char sFsBuf[8192] = { 0 };
    sFsBuf[0] = '\0';
    size_t fsLen = sizeof(sFsBuf);

    append_line(sFsBuf, fsLen, "out vec4 fragColor;");
    for (int t = 0; t < 2; t++) {
        char texCoordBuf[128] = { 0 };
        snprintf(texCoordBuf, sizeof(texCoordBuf), "%sin vec2 vTexCoord%d;\n", optTexPersp ? "" : "noperspective ", t);
        append_str(sFsBuf, fsLen, texCoordBuf);
    }
    append_line(sFsBuf, fsLen, "in vec2 vLightMap;");
    for (int i = 0; i < CC_MAX_INPUTS; i++) {
        char inputBuf[128] = { 0 };
        snprintf(inputBuf, sizeof(inputBuf), "in vec4 vInput%d;\n", i + 1);
        append_str(sFsBuf, fsLen, inputBuf);
    }

    if (optFog) {
        append_line(sFsBuf, fsLen, "in float vFogZ;");
    }
    append_line(sFsBuf, fsLen, "uniform float uFogMul;");
    append_line(sFsBuf, fsLen, "uniform float uFogIntensity;");
    append_line(sFsBuf, fsLen, "uniform float uFogOffset;");
    append_line(sFsBuf, fsLen, "uniform float uDepthZSub;");
    append_line(sFsBuf, fsLen, "uniform float uDepthZMult;");
    append_line(sFsBuf, fsLen, "uniform float uDepthZAdd;");

    for (int t = 0; t < 2; t++) {
        if (ccf.used_textures[t]) {
            char texUniforms[128] = { 0 };
            snprintf(texUniforms, sizeof(texUniforms), "uniform sampler2D uTex%d;\nuniform vec2 uTex%dSize;\nuniform bool uTex%dFilter;\n", t, t, t);
            append_str(sFsBuf, fsLen, texUniforms);
        }
    }

    // 3 point texture filtering
    // Original author: ArthurCarvalho
    // Modified GLSL implementation by twinaphex, mupen64plus-libretro project.
    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_line(sFsBuf, fsLen, "#define TEX_OFFSET(off) texture(tex, texCoord - (off)/texSize)");
        append_line(sFsBuf, fsLen, "vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {");
        append_line(sFsBuf, fsLen, "    vec2 offset = fract(texCoord*texSize - vec2(0.5));");
        append_line(sFsBuf, fsLen, "    offset -= step(1.0, offset.x + offset.y);");
        append_line(sFsBuf, fsLen, "    vec4 c0 = TEX_OFFSET(offset);");
        append_line(sFsBuf, fsLen, "    vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));");
        append_line(sFsBuf, fsLen, "    vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));");
        append_line(sFsBuf, fsLen, "    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);");
        append_line(sFsBuf, fsLen, "}");
        append_line(sFsBuf, fsLen, "vec4 sampleTex(in sampler2D tex, in vec2 uv, in vec2 texSize, in bool dofilter, in int filterType) {");
        append_line(sFsBuf, fsLen, "    if (dofilter && filterType == 2)");
        append_line(sFsBuf, fsLen, "        return filter3point(tex, uv, texSize);");
        append_line(sFsBuf, fsLen, "    else");
        append_line(sFsBuf, fsLen, "        return texture(tex, uv);");
        append_line(sFsBuf, fsLen, "}");
    }

    if (optWorldGeometry) {
        append_line(sFsBuf, fsLen, "float dither4x4(vec2 position, float brightness) {");
        append_line(sFsBuf, fsLen, "    int x = int(mod(position.x, 4.0));");
        append_line(sFsBuf, fsLen, "    int y = int(mod(position.y, 4.0));");
        append_line(sFsBuf, fsLen, "    int index = x + y * 4;");
        append_line(sFsBuf, fsLen, "    float limit = 0.0;");
        append_line(sFsBuf, fsLen, "    if (x < 8) {");
        append_line(sFsBuf, fsLen, "        if (index == 0) limit = 0.0625;");
        append_line(sFsBuf, fsLen, "        if (index == 1) limit = 0.5625;");
        append_line(sFsBuf, fsLen, "        if (index == 2) limit = 0.1875;");
        append_line(sFsBuf, fsLen, "        if (index == 3) limit = 0.6875;");
        append_line(sFsBuf, fsLen, "        if (index == 4) limit = 0.8125;");
        append_line(sFsBuf, fsLen, "        if (index == 5) limit = 0.3125;");
        append_line(sFsBuf, fsLen, "        if (index == 6) limit = 0.9375;");
        append_line(sFsBuf, fsLen, "        if (index == 7) limit = 0.4375;");
        append_line(sFsBuf, fsLen, "        if (index == 8) limit = 0.25;");
        append_line(sFsBuf, fsLen, "        if (index == 9) limit = 0.75;");
        append_line(sFsBuf, fsLen, "        if (index == 10) limit = 0.125;");
        append_line(sFsBuf, fsLen, "        if (index == 11) limit = 0.625;");
        append_line(sFsBuf, fsLen, "        if (index == 12) limit = 1.0;");
        append_line(sFsBuf, fsLen, "        if (index == 13) limit = 0.5;");
        append_line(sFsBuf, fsLen, "        if (index == 14) limit = 0.875;");
        append_line(sFsBuf, fsLen, "        if (index == 15) limit = 0.375;");
        append_line(sFsBuf, fsLen, "    }");
        append_line(sFsBuf, fsLen, "    return brightness < limit ? 0.0 : 1.0;");
        append_line(sFsBuf, fsLen, "}");

        append_line(sFsBuf, fsLen, "vec3 rgb2hsv(vec3 c) {");
        append_line(sFsBuf, fsLen, "    vec4 K = vec4(0.0, -1.0/3.0, 2.0/3.0, -1.0);");
        append_line(sFsBuf, fsLen, "    vec4 p = mix(vec4(c.bg, K.wz),");
        append_line(sFsBuf, fsLen, "                 vec4(c.gb, K.xy),");
        append_line(sFsBuf, fsLen, "                 step(c.b, c.g));");
        append_line(sFsBuf, fsLen, "    vec4 q = mix(vec4(p.xyw, c.r),");
        append_line(sFsBuf, fsLen, "                 vec4(c.r, p.yzx),");
        append_line(sFsBuf, fsLen, "                 step(p.x, c.r));");
        append_line(sFsBuf, fsLen, "    float d = q.x - min(q.w, q.y);");
        append_line(sFsBuf, fsLen, "    float e = 1.0e-10;");
        append_line(sFsBuf, fsLen, "    return vec3(");
        append_line(sFsBuf, fsLen, "        abs(q.z + (q.w - q.y) / (6.0 * d + e)), // hue");
        append_line(sFsBuf, fsLen, "        d / (q.x + e),                          // saturation");
        append_line(sFsBuf, fsLen, "        q.x                                     // value");
        append_line(sFsBuf, fsLen, "    );");
        append_line(sFsBuf, fsLen, "}");
        append_line(sFsBuf, fsLen, "");
        append_line(sFsBuf, fsLen, "vec3 hsv2rgb(vec3 c) {");
        append_line(sFsBuf, fsLen, "    vec3 p = abs(fract(c.xxx + vec3(0.0, 2.0/3.0, 1.0/3.0)) * 6.0 - 3.0);");
        append_line(sFsBuf, fsLen, "    return c.z * mix(vec3(1.0), clamp(p - 1.0, 0.0, 1.0), c.y);");
        append_line(sFsBuf, fsLen, "}");
    }

    if ((optAlpha && optDither) || ccf.do_noise) {
        append_line(sFsBuf, fsLen, "uniform uint uFrameCount;");

        append_line(sFsBuf, fsLen, "float random(in vec3 value) {");
        append_line(sFsBuf, fsLen, "    float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));");
        append_line(sFsBuf, fsLen, "    return fract(sin(random) * 143758.5453);");
        append_line(sFsBuf, fsLen, "}");
    }

    if (optLightMap) {
        append_line(sFsBuf, fsLen, "uniform vec3 uLightmapColor;");
    }

    if (optWorldGeometry) {
        append_line(sFsBuf, fsLen, "uniform bool uShaderFlagsEnabled;");

        char shaderFlagsBuf[128] = { 0 };
        snprintf(shaderFlagsBuf, sizeof(shaderFlagsBuf), "uniform int uShaderFlags[%d];\nuniform float uShaderFlagValues[%d];\n", SHADER_FLAG_MAX, SHADER_FLAG_MAX);
        append_str(sFsBuf, fsLen, shaderFlagsBuf);
    }

    append_line(sFsBuf, fsLen, "uniform int uFilter;");

    if (optFog) {
        append_line(sFsBuf, fsLen, "uniform vec3 uFogColor;");
    }

    append_line(sFsBuf, fsLen, "void main() {");

    if ((optAlpha && optDither) || ccf.do_noise) {
        append_line(sFsBuf, fsLen, "float noise = floor(random(floor(vec3(gl_FragCoord.xy, uFrameCount))) + 0.5);");
    }

    if (ccf.used_textures[0]) {
        append_line(sFsBuf, fsLen, "vec4 texVal0 = sampleTex(uTex0, vTexCoord0, uTex0Size, uTex0Filter, uFilter);");
    }
    if (ccf.used_textures[1]) {
        if (optLightMap) {
            append_line(sFsBuf, fsLen, "vec4 texVal1 = sampleTex(uTex1, vLightMap, uTex1Size, uTex1Filter, uFilter);");
            append_line(sFsBuf, fsLen, "texVal0.rgb *= uLightmapColor.rgb;");
            append_line(sFsBuf, fsLen, "texVal1.rgb = texVal1.rgb * texVal1.rgb + texVal1.rgb;");
        } else {
            append_line(sFsBuf, fsLen, "vec4 texVal1 = sampleTex(uTex1, vTexCoord1, uTex1Size, uTex1Filter, uFilter);");
        }
    }

    append_str(sFsBuf, fsLen, (optAlpha) ? "vec4 texel = vec4(0.0);" : "vec3 texel = vec3(0.0);");
    for (int i = 0; i < (opt2Cycle + 1); i++) {
        u8 *cmd = &cc->shader_commands[i * 8];
        append_str(sFsBuf, fsLen, "texel = ");
        if (!ccf.color_alpha_same[i] && optAlpha) {
            append_str(sFsBuf, fsLen, "vec4(");
            append_formula(sFsBuf, fsLen, cmd, ccf.do_single[i*2+0], ccf.do_multiply[i*2+0], ccf.do_mix[i*2+0], false, false);
            append_str(sFsBuf, fsLen, ", ");
            append_formula(sFsBuf, fsLen, cmd, ccf.do_single[i*2+1], ccf.do_multiply[i*2+1], ccf.do_mix[i*2+1], true, true);
            append_str(sFsBuf, fsLen, ")");
        } else {
            append_formula(sFsBuf, fsLen, cmd, ccf.do_single[i*2+0], ccf.do_multiply[i*2+0], ccf.do_mix[i*2+0], optAlpha, false);
        }
        append_line(sFsBuf, fsLen, ";");

        if (i == 0) {
            append_line(sFsBuf, fsLen, "texel = mod(texel + 0.5, 2.0) - 0.5;");
        }
    }

    append_line(sFsBuf, fsLen, "texel = clamp(mod(texel + 0.5, 2.0) - 0.5, 0.0, 1.0);");

    if (optTextureEdge && optAlpha) {
        append_line(sFsBuf, fsLen, "if (texel.a > 0.3) texel.a = 1.0; else discard;");
    }

    // TODO discard if alpha is 0?

    if (optWorldGeometry) {
        append_line(sFsBuf, fsLen, "if (uShaderFlagsEnabled == true) {");

        // hue
        append_line(sFsBuf, fsLen, "if (uShaderFlags[0] == 1) {");
        append_line(sFsBuf, fsLen, "vec3 hsv = rgb2hsv(texel.rgb);");
        append_line(sFsBuf, fsLen, "hsv.x = fract(hsv.x + uShaderFlagValues[0]);");
        append_line(sFsBuf, fsLen, "vec3 finalColor = hsv2rgb(hsv);");
        append_line(sFsBuf, fsLen, "texel.rgb = finalColor;");
        append_line(sFsBuf, fsLen, "}");

        // saturation
        append_line(sFsBuf, fsLen, "if (uShaderFlags[1] == 1) {");
        append_line(sFsBuf, fsLen, "const vec3 w = vec3(0.2125, 0.7154, 0.0721);");
        append_line(sFsBuf, fsLen, "vec3 intensity = vec3(dot(texel.rgb, w));");
        append_line(sFsBuf, fsLen, "texel.rgb = mix(intensity, texel.rgb, uShaderFlagValues[1]);");
        append_line(sFsBuf, fsLen, "}");

        // brightness
        append_line(sFsBuf, fsLen, "if (uShaderFlags[2] == 1) {");
        append_line(sFsBuf, fsLen, "texel.rgb *= uShaderFlagValues[2];");
        append_line(sFsBuf, fsLen, "}");

        // contrast
        append_line(sFsBuf, fsLen, "if (uShaderFlags[3] == 1) {");
        append_line(sFsBuf, fsLen, "texel.rgb = 0.5 + uShaderFlagValues[3] * (texel.rgb - 0.5);");
        append_line(sFsBuf, fsLen, "}");

        // exposure
        append_line(sFsBuf, fsLen, "if (uShaderFlags[4] == 1) {");
        append_line(sFsBuf, fsLen, "texel.rgb = texel.rgb + (uShaderFlagValues[4] - 2) * texel.rgb + texel.rgb;");
        append_line(sFsBuf, fsLen, "}");

        // dithering
        append_line(sFsBuf, fsLen, "if (uShaderFlags[5] == 1) {");
        append_line(sFsBuf, fsLen, "texel.rgb *= dither4x4(gl_FragCoord.xy, dot(texel.rgb, vec3(0.299, 0.587, 0.114)));");
        append_line(sFsBuf, fsLen, "}");

        // posterization
        append_line(sFsBuf, fsLen, "if (uShaderFlags[6] == 1) {");
        append_line(sFsBuf, fsLen, "int levels = int(max(1.0, uShaderFlagValues[6]));");
        append_line(sFsBuf, fsLen, "texel.rgb = floor(texel.rgb * levels) / levels;");
        append_line(sFsBuf, fsLen, "}");

        // scan lines
        append_line(sFsBuf, fsLen, "if (uShaderFlags[7] == 1) {");
        append_line(sFsBuf, fsLen, "float scan = sin(gl_FragCoord.y * 1.5) * 0.04;");
        append_line(sFsBuf, fsLen, "texel.rgb -= scan * uShaderFlagValues[7];");
        append_line(sFsBuf, fsLen, "}");

        append_line(sFsBuf, fsLen, "}");
    }

    if (optFog) {
        if (optAlpha) {
            append_line(sFsBuf, fsLen, "texel = vec4(mix(texel.rgb, uFogColor, vFogZ), texel.a);");
        } else {
            append_line(sFsBuf, fsLen, "texel = mix(texel, uFogColor, vFogZ);");
        }
    }

    if (optAlpha && optDither) {
        append_line(sFsBuf, fsLen, "texel.a *= noise;");
    }

    if (optAlpha) {
        append_line(sFsBuf, fsLen, "fragColor = texel;");
    } else {
        append_line(sFsBuf, fsLen, "fragColor = vec4(texel, 1.0);");
    }
    append_line(sFsBuf, fsLen, "}");

    sFsBuf[fsLen-1] = '\0';

    return sFsBuf;
}

static void gfx_init_shader_inputs() {
    gShaderInputs = calloc(MAX_SHADER_INPUTS, sizeof(struct ShaderInput));
    if (!gShaderInputs) {
        sys_fatal("Failed to allocate shader inputs, ran out of memory!");
    }

    gPostProcessShaderInputs = calloc(MAX_SHADER_INPUTS, sizeof(struct ShaderInput));
    if (!gPostProcessShaderInputs) {
        free(gShaderInputs);
        gShaderInputs = NULL;
        sys_fatal("Failed to allocate post process shader inputs, ran out of memory!");
    }

    int cnt = 0;

    snprintf(gShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aVtxPos");
    gShaderInputs[cnt].location = cnt;
    gShaderInputs[cnt].size = 4;
    cnt++;

    snprintf(gShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aLocalPos");
    gShaderInputs[cnt].location = cnt;
    gShaderInputs[cnt].size = 4;
    cnt++;

    for (int t = 0; t < 2; t++) {
        snprintf(gShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aTexCoord%d", t);
        gShaderInputs[cnt].location = cnt;
        gShaderInputs[cnt].size = 2;
        ++cnt;
    }

    snprintf(gShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aLightMap");
    gShaderInputs[cnt].location = cnt;
    gShaderInputs[cnt].size = 2;
    ++cnt;

    for (int i = 0; i < CC_MAX_INPUTS; i++) {
        snprintf(gShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aInput%d", i + 1);
        gShaderInputs[cnt].location = cnt;
        gShaderInputs[cnt].size = 4;
        ++cnt;
    }

    snprintf(gShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aNormal");
    gShaderInputs[cnt].location = cnt;
    gShaderInputs[cnt].size = 3;
    ++cnt;

    snprintf(gShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aBarycentric");
    gShaderInputs[cnt].location = cnt;
    gShaderInputs[cnt].size = 3;
    ++cnt;

    // post process shader inputs
    cnt = 0;

    snprintf(gPostProcessShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aVtxPos");
    gPostProcessShaderInputs[cnt].location = cnt;
    gPostProcessShaderInputs[cnt].size = 4;
    ++cnt;

    snprintf(gPostProcessShaderInputs[cnt].name, MAX_SHADER_VARIABLE_NAME, "aTexCoord");
    gPostProcessShaderInputs[cnt].location = cnt;
    gPostProcessShaderInputs[cnt].size = 2;
    ++cnt;
}

static void gfx_init_shader_bindings() {
    gShaderBindings = calloc(MAX_SHADER_BINDINGS, sizeof(struct ShaderBinding));
    if (!gShaderBindings) {
        sys_fatal("Failed to allocate shader bindings, ran out of memory!");
    }

    gPostProcessShaderBindings = calloc(MAX_SHADER_BINDINGS, sizeof(struct ShaderBinding));
    if (!gPostProcessShaderBindings) {
        free(gShaderBindings);
        gShaderBindings = NULL;
        sys_fatal("Failed to allocate post process shader bindings, ran out of memory!");
    }

    int cnt = 0;

    for (int t = 0; t < 2; t++) {
        snprintf(gShaderBindings[cnt].name, MAX_SHADER_VARIABLE_NAME, "uTex%d", t);
        gShaderBindings[cnt].binding = t;
        cnt++;
    }

    snprintf(gShaderBindings[cnt].name, MAX_SHADER_VARIABLE_NAME, "uPassTex");
    gShaderBindings[cnt].binding = 10;
    cnt++;

    for (int i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
        if (cnt >= MAX_SHADER_BINDINGS) { break; }
        snprintf(gShaderBindings[cnt].name, MAX_SHADER_VARIABLE_NAME, "uPassTex%d", i);
        gShaderBindings[cnt].binding = 10 + i;
        cnt++;
    }

    cnt = 0;

    snprintf(gPostProcessShaderBindings[cnt].name, MAX_SHADER_VARIABLE_NAME, "uPassTex");
    gPostProcessShaderBindings[cnt].binding = 10;
    cnt++;

    for (int i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
        if (cnt >= MAX_SHADER_BINDINGS) { break; }
        snprintf(gPostProcessShaderBindings[cnt].name, MAX_SHADER_VARIABLE_NAME, "uPassTex%d", i);
        gPostProcessShaderBindings[cnt].binding = 10 + i;
        cnt++;
    }
}

void gfx_init_shaders() {
    gfx_init_shader_inputs();
    gfx_init_shader_bindings();
}

static void strip_array_from_name(char *name) {
    char *bracket = strchr(name, '[');
    if (bracket) {
        *bracket = '\0';
    }
}

static bool process_shader_line(struct Shader *shader, struct ShaderInput *referenceInputs, struct ShaderBinding *referenceBindings, char **output, size_t *outputSize, const char *line) {
    char qualifier[32] = { 0 }, storageQualifier[32] = { 0 }, type[32] = { 0 }, name[MAX_SHADER_VARIABLE_NAME] = { 0 };

    // parse and update uniform blocks
    // scan brace because sscanf does scanning from left to right and will succeed even if the
    // brace is not there
    char brace = 0;
    if (!sShaderInsideCustomUniformBlock && (sscanf(line, " uniform %127s %c", name, &brace) == 2 || sscanf(line, "uniform %127s %c", name, &brace) == 2) && brace == '{') {
        sShaderInsideCustomUniformBlock = true;
        char layoutLine[128];
        snprintf(layoutLine, sizeof(layoutLine), "layout(std140, set = 0, binding = %d) uniform %s {\n", sShaderUniformBlockCount++, name);
        append_and_realloc_str(output, outputSize, layoutLine);
        return true;
    }

    // exit uniform block when needed
    if (sShaderInsideCustomUniformBlock && strchr(line, '}')) {
        sShaderInsideCustomUniformBlock = false;
        append_and_realloc_str(output, outputSize, line);
        return true;
    } else if (sShaderInsideCustomUniformBlock) {
        // we're in a uniform block, no parsing needed here
        append_and_realloc_str(output, outputSize, line);
        return true;
    }

    // parse inputs for inputs equivalent to reference inputs
    if (sscanf(line, "%31s %31s %31s %31[^; \t\n]", qualifier, storageQualifier, type, name) == 4 && strcmp(storageQualifier, "in") == 0) {
        strip_array_from_name(name);
        for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
            if (referenceInputs[i].name[0] != '\0' && strcmp(referenceInputs[i].name, name) == 0) {
                char layoutLine[sizeof(type) + MAX_SHADER_VARIABLE_NAME + 64];
                snprintf(layoutLine, sizeof(layoutLine), "layout(location=%d) %s in %s %s", referenceInputs[i].location, qualifier, type, name);
                append_and_realloc_str(output, outputSize, layoutLine);
                if (shader) {
                    snprintf(shader->shaderInputs[sShaderInputCount].name, MAX_SHADER_VARIABLE_NAME, "%s", referenceInputs[i].name);
                    shader->shaderInputs[sShaderInputCount].location = referenceInputs[i].location;
                    shader->shaderInputs[sShaderInputCount].size = referenceInputs[i].size;

                    if (sShaderInputCount < MAX_SHADER_INPUTS - 1) { sShaderInputCount++; }
                }
                return true;
            }
        }
    }

    if (sscanf(line, " %31s %31s %31[^; \t\n]", storageQualifier, type, name) == 3 && strcmp(storageQualifier, "in") == 0) {
        strip_array_from_name(name);
        for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
            if (referenceInputs[i].name[0] != '\0' && strcmp(referenceInputs[i].name, name) == 0) {
                char layoutLine[sizeof(type) + MAX_SHADER_VARIABLE_NAME + 64];
                snprintf(layoutLine, sizeof(layoutLine), "layout(location=%d) in %s %s", referenceInputs[i].location, type, name);
                append_and_realloc_str(output, outputSize, layoutLine);
                if (shader) {
                    snprintf(shader->shaderInputs[sShaderInputCount].name, MAX_SHADER_VARIABLE_NAME, "%s", referenceInputs[i].name);
                    shader->shaderInputs[sShaderInputCount].location = referenceInputs[i].location;
                    shader->shaderInputs[sShaderInputCount].size = referenceInputs[i].size;

                    if (sShaderInputCount < MAX_SHADER_INPUTS - 1) { sShaderInputCount++; }
                }
                return true;
            }
        }
    }

    // look for and parse outputs
    if (sscanf(line, "%31s %31s %31s %31[^; \t\n]", qualifier, storageQualifier, type, name) == 4 && strcmp(storageQualifier, "out") == 0) {
        strip_array_from_name(name);
        // add name to our shader outputs
        if (shader) {
            snprintf(shader->shaderOutputs[sShaderOutputCount].name, MAX_SHADER_VARIABLE_NAME, "%s", name);
            shader->shaderOutputs[sShaderOutputCount].location = sShaderOutputCount;
        }
        char layoutLine[sizeof(type) + MAX_SHADER_VARIABLE_NAME + 64];
        snprintf(layoutLine, sizeof(layoutLine), "layout(location=%d) %s out %s %s", sShaderOutputCount, qualifier, type, name);
        append_and_realloc_str(output, outputSize, layoutLine);
        if (sShaderOutputCount < MAX_SHADER_OUTPUTS - 1) { sShaderOutputCount++; }
        return true;
    }

    if (sscanf(line, " %31s %31s %31[^; \t\n]", storageQualifier, type, name) == 3 && strcmp(storageQualifier, "out") == 0) {
        strip_array_from_name(name);
        // add name to our shader outputs
        if (shader) {
            snprintf(shader->shaderOutputs[sShaderOutputCount].name, MAX_SHADER_VARIABLE_NAME, "%s", name);
            shader->shaderOutputs[sShaderOutputCount].location = sShaderOutputCount;
        }
        char layoutLine[sizeof(type) + MAX_SHADER_VARIABLE_NAME + 64];
        snprintf(layoutLine, sizeof(layoutLine), "layout(location=%d) out %s %s", sShaderOutputCount, type, name);
        append_and_realloc_str(output, outputSize, layoutLine);
        if (sShaderOutputCount < MAX_SHADER_OUTPUTS - 1) { sShaderOutputCount++; }
        return true;
    }

    // convert sampler, image, or stray uniforms
    if (sscanf(line, " uniform %31s %31[^; \t\n]", type, name) == 2 || sscanf(line, "uniform %31s %31[^; \t\n]", type, name) == 2) {
        if (strncmp(type, "sampler", 7) == 0 || strncmp(type, "image", 5) == 0) {
            strip_array_from_name(name);
            for (int i = 0; i < MAX_SHADER_BINDINGS; i++) {
                if (referenceBindings[i].name[0] != '\0' && strcmp(referenceBindings[i].name, name) == 0) {
                    char layoutLine[sizeof(type) + MAX_SHADER_VARIABLE_NAME + 64];
                    snprintf(layoutLine, sizeof(layoutLine), "layout(binding=%d) uniform %s %s", referenceBindings[i].binding, type, name);
                    append_and_realloc_str(output, outputSize, layoutLine);
                    return true;
                }
            }
        } else {
            // add uniform to uniform code for inserting into default uniform block
            char uniformLine[sizeof(type) + MAX_SHADER_VARIABLE_NAME + 64];
            snprintf(uniformLine, sizeof(uniformLine), "    %s %s;\n", type, name);
            append_str(sShaderUniformCode, MAX_UNIFORM_CODE, uniformLine);
            return false;
        }
    }

    // look for and override version number
    if (sscanf(line, "#version %31s %31s", type, name) == 2
    ||  sscanf(line, " #version %31s %31s", type, name) == 2
    ||  sscanf(line, "#version %31s", type) == 1
    ||  sscanf(line, " #version %31s", type) == 1) {
        char versionLine[32] = { 0 };
        snprintf(versionLine, sizeof(versionLine), "#version 450 core");
        append_and_realloc_str(output, outputSize, versionLine);
        sShaderHasVersion = true;
        return true;
    }

    append_and_realloc_str(output, outputSize, line);
    return true;
}

static void gfx_sanitize_shader(struct Shader *shader, struct ShaderInput *referenceInputs, struct ShaderBinding *referenceBindings, char **shaderCode) {
    if (!shaderCode || !*shaderCode) { return; }

    size_t sizeofShaderCode = strlen(*shaderCode) + 1; // +1 for null terminator

    // as a buffer area to try avoiding reallocation, for added layout specifiers,
    // uniform blocks, etc.. a good guess is 256 extra characters to allocate, but
    // reallocation will probably be necessary
    sizeofShaderCode += 256;

    char *sanitized = calloc(1, sizeofShaderCode); // allocate sanitized str
    if (!sanitized) { return; }

    char *sourceCopy = strdup(*shaderCode); // copy shader code
    char *line = sourceCopy;

    // reset state variables
    sShaderInputCount = 0;
    sShaderOutputCount = 0;
    sShaderInsideCustomUniformBlock = false;
    sShaderHasVersion = false;

    memset(sShaderUniformCode, 0, sizeof(char) * MAX_UNIFORM_CODE);

    while (line && *line) {
        char *lineEnd = strpbrk(line, "\n;");

        // if no delimiter was found, process the final line and exit
        if (lineEnd == 0) {
            process_shader_line(shader, referenceInputs, referenceBindings, &sanitized, &sizeofShaderCode, line);
            break;
        }

        // save delimiter
        char delimiter = *lineEnd;
        *lineEnd = '\0';

        // process line
        if (process_shader_line(shader, referenceInputs, referenceBindings, &sanitized, &sizeofShaderCode, line)) {
            char delimiterString[2] = { 0 };
            snprintf(delimiterString, sizeof(delimiterString), "%c", delimiter);
            append_and_realloc_str(&sanitized, &sizeofShaderCode, delimiterString);
        }

        line = lineEnd + 1;
    }

    // add in the version text if necessary
    if (!sShaderHasVersion) {
        char *sanitizedSource = strdup(sanitized);
        if (!sanitizedSource) {
            free(sourceCopy);
            free(sanitized);
            return;
        }

        memset(sanitized, 0, sizeof(char) * sizeofShaderCode);

        append_and_realloc_str(&sanitized, &sizeofShaderCode, "#version 450 core\n");
        append_and_realloc_str(&sanitized, &sizeofShaderCode, sanitizedSource);
        free(sanitizedSource);
    }

    // readd the global uniforms into a global uniform block
    if (sShaderUniformCode[0] != '\0') {
        char *sanitizedSource = strdup(sanitized);
        if (!sanitizedSource) {
            free(sourceCopy);
            free(sanitized);
            return;
        }

        // zero out sanitized string
        memset(sanitized, 0, sizeof(char) * sizeofShaderCode);

        // append version string
        append_and_realloc_str(&sanitized, &sizeofShaderCode, "#version 450 core\n");

        // append block
        char defaultUniformBlockString[MAX_SHADER_VARIABLE_NAME + 128];
        snprintf(defaultUniformBlockString, sizeof(defaultUniformBlockString), "layout(std140, set = 0, binding = %d) uniform %s {\n", sShaderUniformBlockCount++, defaultUniformBlockName);
        append_and_realloc_str(&sanitized, &sizeofShaderCode, defaultUniformBlockString);

        // append uniform code
        append_and_realloc_str(&sanitized, &sizeofShaderCode, sShaderUniformCode);

        // cleanup block
        append_and_realloc_str(&sanitized, &sizeofShaderCode, "};\n");

        // append rest of code
        append_and_realloc_str(&sanitized, &sizeofShaderCode, sanitizedSource + 17);  // 17 is length of version text, which by this point is guranteed to exist

        // cleanup
        free(sanitizedSource);
    }

    free(sourceCopy);
    free(*shaderCode);
    *shaderCode = sanitized;
}

static bool gfx_sanitize_vertex_shader(struct Shader *shader, struct ShaderInput *referenceInputs, struct ShaderBinding *referenceBindings, char **shaderCode) {
    gfx_sanitize_shader(shader, referenceInputs, referenceBindings, shaderCode);
    // double check we are not missing any inputs, if we are, error out since it can cause
    // issues in certain render apis
    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        if (strncmp(referenceInputs[i].name, shader->shaderInputs[i].name, MAX_SHADER_VARIABLE_NAME) != 0 || referenceInputs[i].location != shader->shaderInputs[i].location) {
            // mismatched! tell the shader code this is not a valid shader
            LOG_ERROR("Failed to sanitize vertex shader! Mismatch between expected inputs and inputs in the vertex shader! Index is %d, expected output is %s, vertex output is %s", i, referenceInputs[i].name, shader->shaderInputs[i].name);
            return false;
        }
    }
    return true;
}

static bool gfx_sanitize_fragment_shader(struct Shader *shader, struct ShaderOutput *outputsFromVertexShader, struct ShaderBinding *referenceBindings, char **shaderCode) {
    // convert outputs to inputs for fragment shader
    struct ShaderInput inputs[MAX_SHADER_INPUTS] = { 0 };
    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        strncpy(inputs[i].name, outputsFromVertexShader[i].name, MAX_SHADER_VARIABLE_NAME - 1);
        inputs[i].location = outputsFromVertexShader[i].location;
    }
    gfx_sanitize_shader(shader, inputs, referenceBindings, shaderCode);
    // double check we are not missing any inputs, if we are, error out since it can cause
    // issues in certain render apis
    for (int i = 0; i < MAX_SHADER_INPUTS; i++) {
        if (strncmp(inputs[i].name, shader->shaderInputs[i].name, MAX_SHADER_VARIABLE_NAME) != 0 || inputs[i].location != shader->shaderInputs[i].location) {
            // mismatched! tell the shader code this is not a valid shader
            LOG_ERROR("Failed to sanitize fragment shader! Mismatch between vertex outputs and fragment inputs! Index is %d, vertex output is %s, fragment input is %s", i, inputs[i].name, shader->shaderInputs[i].name);
            return false;
        }
    }
    return true;
}

bool gfx_compile_shader_to_spirv(glslang_stage_t stage, const char *shaderCode, struct Shader *shader) {
    // convert shader to version 450
    char *shaderCode450 = strdup(shaderCode);
    if (!shaderCode450) {
        LOG_ERROR("Failed to convert shader code to version 450, ran out of memory!");
        return false;
    }

    // target vulkan as it's a bit more stingy then modern opengl
    const glslang_input_t input = {
        .language = GLSLANG_SOURCE_GLSL,
        .stage = stage,
        .client = GLSLANG_CLIENT_VULKAN,
        .client_version = GLSLANG_TARGET_VULKAN_1_3,
        .target_language = GLSLANG_TARGET_SPV,
        .target_language_version = GLSLANG_TARGET_SPV_1_5,
        .code = shaderCode450,
        // target #version 450 core
        .default_version = 450,
        .default_profile = GLSLANG_CORE_PROFILE,
        .force_default_version_and_profile = false,
        .forward_compatible = false,
        .messages = GLSLANG_MSG_DEFAULT_BIT,
        .resource = glslang_default_resource(),
    };

    glslang_shader_t *slangShader = glslang_shader_create(&input);

    SpirVShader spirvShader = {
        .words = NULL,
        .size = 0,
    };
    if (!glslang_shader_preprocess(slangShader, &input)) {
        LOG_ERROR("GLSL preprocessing failed!\n%s\n%s\n%s",
            glslang_shader_get_info_log(slangShader),
            glslang_shader_get_info_debug_log(slangShader),
            input.code);
        glslang_shader_delete(slangShader);
        free(shaderCode450);
        return false;
    }

    if (!glslang_shader_parse(slangShader, &input)) {
        LOG_ERROR("GLSL parsing failed!\n%s\n%s\n%s",
            glslang_shader_get_info_log(slangShader),
            glslang_shader_get_info_debug_log(slangShader),
            glslang_shader_get_preprocessed_code(slangShader));
        glslang_shader_delete(slangShader);
        free(shaderCode450);
        return false;
    }

    glslang_program_t *program = glslang_program_create();
    glslang_program_add_shader(program, slangShader);

    if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT)) {
        LOG_ERROR("GLSL linking failed!\n%s\n%s",
            glslang_shader_get_info_log(slangShader),
            glslang_shader_get_info_debug_log(slangShader));
        glslang_program_delete(program);
        glslang_shader_delete(slangShader);
        free(shaderCode450);
        return false;
    }

    glslang_program_SPIRV_generate(program, stage);

    spirvShader.size = glslang_program_SPIRV_get_size(program);
    // must be freed later or there will be a leak
    spirvShader.words = malloc(spirvShader.size * sizeof(uint32_t));
    glslang_program_SPIRV_get(program, spirvShader.words);

    const char *spirv_messages = glslang_program_SPIRV_get_messages(program);
    if (spirv_messages) {
        LOG_INFO("%s\b", spirv_messages);
    }

    glslang_program_delete(program);
    glslang_shader_delete(slangShader);

    free(shader->spirVShader.words);
    shader->spirVShader = spirvShader;

    free(shaderCode450);

    return true;
}

#define SPVC_CHECK(x) \
    do { \
        spvc_result result = (x); \
        if (result != SPVC_SUCCESS) { \
            LOG_ERROR("SPIRV-Cross Error: %d at %s:%d", result, __FILE__, __LINE__); \
            if (context) { spvc_context_destroy(context); } \
            return; \
        } \
    } while(0)

static void reflect_uniform_data(struct Shader *shader, spvc_context context, spvc_compiler compiler) {
    spvc_resources resources;
    spvc_compiler_create_shader_resources(compiler, &resources);

    const spvc_reflected_resource *list;
    size_t count;
    SPVC_CHECK(spvc_resources_get_resource_list_for_type(resources, SPVC_RESOURCE_TYPE_UNIFORM_BUFFER, &list, &count));

    shader->uniformBlockCount = 0;

    for (size_t i = 0; i < count; i++) {
        if (shader->uniformBlockCount >= MAX_UNIFORM_BLOCKS) {
            LOG_ERROR("Ran out of space for uniform blocks!\n");
            break;
        }

        spvc_type type = spvc_compiler_get_type_handle(compiler, list[i].type_id);

        if (spvc_type_get_basetype(type) != SPVC_BASETYPE_STRUCT) {
            continue;
        }

        int currentBlockIndex = shader->uniformBlockCount;
        struct ShaderUniformBlock *block = &shader->uniformBlocks[currentBlockIndex];
        block->uniformCount = 0;

        const char *blockName = list[i].name;
        if (blockName == NULL || strlen(blockName) == 0) {
            blockName = spvc_compiler_get_name(compiler, list[i].base_type_id);
        }

        // see if it's the default global uniform block
        if (strcmp(blockName, defaultUniformBlockName) == 0) {
            block->isGlobalBlock = true;
        } else {
            block->isGlobalBlock = false;
        }

        // prepend stage to uniform name
        char uniqueName[MAX_SHADER_VARIABLE_NAME];

        if (shader->stage == SHADER_STAGE_VERTEX) {
            snprintf(uniqueName, sizeof(uniqueName), "_VS_%s", blockName);
        } else {
            snprintf(uniqueName, sizeof(uniqueName), "_FS_%s", blockName);
        }
        strncpy(block->name, uniqueName, sizeof(block->name) - 1);

        spvc_compiler_set_name(compiler, list[i].base_type_id, uniqueName);

        if (spvc_compiler_has_decoration(compiler, list[i].id, SpvDecorationBinding)) {
            block->location = spvc_compiler_get_decoration(compiler, list[i].id, SpvDecorationBinding);
        } else {
            block->location = UNIFORM_BINDING_SLOT_OFFSET;
        }

        size_t block_size = 0;
        spvc_compiler_get_declared_struct_size(compiler, type, &block_size);

        // align to 16 bytes
        block->size = (block_size + 15) & ~15;

        block->buffer = (uint8_t *)malloc(block->size);
        if (block->buffer == NULL) {
            sys_fatal("Failed to allocate memory for uniform block: %s", block->name);
        }
        memset(block->buffer, 0, block->size);

#ifdef _WIN32
        if (gRenderApi == &gfx_direct3d11_api) {
            d3d11_create_buffer_for_block(block);
        }
#endif

        // bind the buffer in opengl
        if (gRenderApi == &gfx_opengl_api) {
            glGenBuffers(1, &block->glBufferId);
            glBindBuffer(GL_UNIFORM_BUFFER, block->glBufferId);
            glBufferData(GL_UNIFORM_BUFFER, block->size, NULL, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        shader->uniformBlockCount++;

        // get uniforms inside block
        u32 memberCount = spvc_type_get_num_member_types(type);
        for (u32 m = 0; m < memberCount; m++) {
            if (block->uniformCount >= MAX_SHADER_UNIFORMS) {
                printf("Warning: Ran out of uniform space inside block %s!\n", block->name);
                break;
            }

            struct ShaderUniform *uniform = &block->uniforms[block->uniformCount];

            const char *memberName = spvc_compiler_get_member_name(compiler, list[i].base_type_id, m);

            size_t memberSize = 0;
            spvc_compiler_get_declared_struct_member_size(compiler, type, m, &memberSize);

            u32 memberOffset = 0;
            spvc_compiler_type_struct_member_offset(compiler, type, m, &memberOffset);

            spvc_type memberType = spvc_compiler_get_type_handle(compiler, spvc_type_get_member_type(type, m));

            u32 arrayLength = 1;
            u32 arrayStride = 0;

            if (spvc_type_get_num_array_dimensions(memberType) > 0) {
                arrayLength = spvc_type_get_array_dimension(memberType, 0);
                SPVC_CHECK(spvc_compiler_type_struct_member_array_stride(compiler, type, m, &arrayStride));
            }

            u32 width = spvc_type_get_bit_width(memberType) / 8;
            u32 columns = spvc_type_get_columns(memberType);
            u32 vectorSize = spvc_type_get_vector_size(memberType);
            u32 elementSize = width * columns * vectorSize;

            strncpy(uniform->name, memberName, MAX_SHADER_VARIABLE_NAME - 1);
            uniform->location = memberOffset;
            uniform->size = memberSize;
            uniform->arrayStride = arrayStride;
            uniform->elementSize = elementSize;
            uniform->arrayLength = arrayLength;

            block->uniformCount++;
        }
    }

    // reorder uniform blocks so the global block is at the bottom for ease of access
    if (shader->uniformBlockCount > 1 && !shader->uniformBlocks[0].isGlobalBlock) {
        for (int i = 1; i < shader->uniformBlockCount; i++) {
            if (shader->uniformBlocks[i].isGlobalBlock) {
                struct ShaderUniformBlock temp = shader->uniformBlocks[0];
                shader->uniformBlocks[0] = shader->uniformBlocks[i];
                shader->uniformBlocks[i] = temp;
                break;
            }
        }
    }
}

void gfx_convert_spirv_to_glsl_410(char **shaderCode, struct Shader *shader) {
    spvc_context context = NULL;
    spvc_compiler compiler = NULL;
    spvc_parsed_ir ir = NULL;
    const char *glsl_code = NULL;

    SpirVShader *spirvShader = &shader->spirVShader;

    SPVC_CHECK(spvc_context_create(&context));
    SPVC_CHECK(spvc_context_parse_spirv(context, spirvShader->words, spirvShader->size, &ir));
    SPVC_CHECK(spvc_context_create_compiler(context, SPVC_BACKEND_GLSL, ir, SPVC_CAPTURE_MODE_TAKE_OWNERSHIP, &compiler));

    spvc_resources resources;
    spvc_compiler_create_shader_resources(compiler, &resources);

    reflect_uniform_data(shader, context, compiler);

    spvc_compiler_options options;
    spvc_compiler_create_compiler_options(compiler, &options);
    spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_GLSL_VERSION, 410);
    spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_GLSL_ES, false);
    spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_GLSL_ENABLE_420PACK_EXTENSION, false);
    spvc_compiler_install_compiler_options(compiler, options);

    spvc_compiler_compile(compiler, &glsl_code);

    *shaderCode = strdup(glsl_code);

    spvc_context_destroy(context);
}

void gfx_convert_spirv_to_hlsl(char **shaderCode, struct Shader *shader) {
    spvc_context context = NULL;
    spvc_compiler compiler = NULL;
    spvc_parsed_ir ir = NULL;
    const char *hlsl_code = NULL;

    SpirVShader *spirvShader = &shader->spirVShader;

    SPVC_CHECK(spvc_context_create(&context));
    SPVC_CHECK(spvc_context_parse_spirv(context, spirvShader->words, spirvShader->size, &ir));
    SPVC_CHECK(spvc_context_create_compiler(context, SPVC_BACKEND_HLSL, ir, SPVC_CAPTURE_MODE_TAKE_OWNERSHIP, &compiler));

    reflect_uniform_data(shader, context, compiler);

    spvc_compiler_options options;
    spvc_compiler_create_compiler_options(compiler, &options);
    spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_HLSL_SHADER_MODEL, 50);
    spvc_compiler_install_compiler_options(compiler, options);

    spvc_compiler_compile(compiler, &hlsl_code);

    *shaderCode = strdup(hlsl_code);

    spvc_context_destroy(context);
}

void gfx_convert_spirv_to_msl(char **shaderCode, struct Shader *shader) {
    spvc_context context = NULL;
    spvc_compiler compiler = NULL;
    spvc_parsed_ir ir = NULL;
    const char *msl_code = NULL;

    SpirVShader *spirvShader = &shader->spirVShader;

    SPVC_CHECK(spvc_context_create(&context));
    SPVC_CHECK(spvc_context_parse_spirv(context, spirvShader->words, spirvShader->size, &ir));
    SPVC_CHECK(spvc_context_create_compiler(context, SPVC_BACKEND_MSL, ir, SPVC_CAPTURE_MODE_TAKE_OWNERSHIP, &compiler));

    spvc_resources resources;
    spvc_compiler_create_shader_resources(compiler, &resources);

    reflect_uniform_data(shader, context, compiler);

    // set compilations options
    spvc_compiler_options options;
    spvc_compiler_create_compiler_options(compiler, &options);
    spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_MSL_VERSION, 20100); // 2.1
    spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_MSL_PAD_FRAGMENT_OUTPUT_COMPONENTS, true);
    spvc_compiler_options_set_bool(options, SPVC_COMPILER_OPTION_MSL_ENABLE_DECORATION_BINDING, true);

    SPVC_CHECK(spvc_compiler_install_compiler_options(compiler, options));

    SPVC_CHECK(spvc_compiler_compile(compiler, &msl_code));

    *shaderCode = strdup(msl_code);

    spvc_context_destroy(context);
    return;
}

#undef SPVC_CHECK

static bool gfx_generate_vertex_and_fragment_shader_no_fallback(struct Shader *vertexShader, struct Shader *fragmentShader, struct ShaderInput *shaderInputs, struct ShaderBinding *shaderBindings, char **vsCode, char **fsCode, bool isCustom)  {
    vertexShader->stage = SHADER_STAGE_VERTEX;
    fragmentShader->stage = SHADER_STAGE_FRAGMENT;

    sShaderUniformBlockCount = UNIFORM_BINDING_SLOT_OFFSET;

    if (!gfx_sanitize_vertex_shader(vertexShader, shaderInputs, shaderBindings, vsCode)) {
        if (isCustom) {
            LOG_LUA_LINE("Failed to sanitize vertex shader!");
            return false;
        } else {
            sys_fatal("Failed to sanitize vertex shader!");
            return false;
        }
    }

    if (!gfx_sanitize_fragment_shader(fragmentShader, vertexShader->shaderOutputs, shaderBindings, fsCode)) {
        if (isCustom) {
            LOG_LUA_LINE("Failed to sanitize fragment shader!");
            return false;
        } else {
            sys_fatal("Failed to sanitize fragment shader!");
            return false;
        }
    }

    if (!gfx_compile_shader_to_spirv(GLSLANG_STAGE_VERTEX, *vsCode, vertexShader)) {
        if (isCustom) {
            LOG_LUA_LINE("Failed to compile custom vertex shader to SPIR-V!");
            return false;
        } else {
            sys_fatal("Failed to compile vertex shader to SPIR-V!");
            return false;
        }
    }

    if (!gfx_compile_shader_to_spirv(GLSLANG_STAGE_FRAGMENT, *fsCode, fragmentShader)) {
        if (isCustom) {
            LOG_LUA_LINE("Failed to compile custom fragment shader to SPIR-V!");
            return false;
        } else {
            sys_fatal("Failed to compile fragment shader to SPIR-V!");
            return false;
        }
    }

    return true;
}

static bool gfx_generate_vertex_and_fragment_shader(struct Shader *vertexShader, struct Shader *fragmentShader, struct ShaderInput *shaderInputs, struct ShaderBinding *shaderBindings, char *vsCode, char *fsCode, char *fallbackVsCode, char *fallbackFsCode, char **outVertShader, char **outFragShader) {
    // clear shader contents
    gfx_destroy_shader_contents(vertexShader);
    gfx_destroy_shader_contents(fragmentShader);

    bool isCustom = (strcmp(vsCode, fallbackVsCode) != 0 || strcmp(fsCode, fallbackFsCode) != 0);

    if (!gfx_generate_vertex_and_fragment_shader_no_fallback(vertexShader, fragmentShader, shaderInputs, shaderBindings, &vsCode, &fsCode, isCustom)) {
        if (isCustom) {
            // clear shader contents of old garbage data and try again with fallback
            gfx_destroy_shader_contents(vertexShader);
            gfx_destroy_shader_contents(fragmentShader);

            // setup fallback code
            free(vsCode);
            free(fsCode);
            vsCode = fallbackVsCode;
            fsCode = fallbackFsCode;
            fallbackVsCode = NULL;
            fallbackFsCode = NULL;
            if (!gfx_generate_vertex_and_fragment_shader_no_fallback(vertexShader, fragmentShader, shaderInputs, shaderBindings, &vsCode, &fsCode, false)) {
                sys_fatal("Failed to generate vertex and fragment shader!"); // should technically never be reached
                return false;
            }
        } else {
            sys_fatal("Failed to generate vertex and fragment shader!"); // should technically never be reached
            return false;
        }
    }


    if (outVertShader) {
        *outVertShader = vsCode;
    } else {
        free(vsCode);
        vsCode = NULL;
    }
    free(fallbackVsCode);
    fallbackVsCode = NULL;

    if (outFragShader) {
        *outFragShader = fsCode;
    } else {
        free(fsCode);
        fsCode = NULL;
    }
    free(fallbackFsCode);
    fallbackFsCode = NULL;

    return true;
}

bool gfx_generate_vertex_and_fragment_shader_from_cc(struct Shader *vertexShader, struct Shader *fragmentShader, struct ColorCombiner *cc, char **outVertShader, char **outFragShader) {
    char *defaultVsCode = gfx_get_default_vertex_shader_from_cc(cc);
    char *defaultFsCode = gfx_get_default_fragment_shader_from_cc(cc);

    char *fallbackVsCode = strdup(defaultVsCode);
    char *fallbackFsCode = strdup(defaultFsCode);
    char *vsShaderCode = NULL;
    char *fsShaderCode = NULL;
    if (!fallbackVsCode || !fallbackFsCode) {
        sys_fatal("Failed to generate vertex and fragment shader, ran out of memory!");
    }

    smlua_call_event_hooks(HOOK_ON_VERTEX_SHADER_CREATE, cc, (const char **)&vsShaderCode);

    if (!vsShaderCode) {
        vsShaderCode = strdup(fallbackVsCode);
    } else {
        vsShaderCode = strdup(vsShaderCode); // lua handles its own memory, we need to escape it
    }

    smlua_call_event_hooks(HOOK_ON_FRAGMENT_SHADER_CREATE, cc, (const char **)&fsShaderCode);

    if (!fsShaderCode) {
        fsShaderCode = strdup(fallbackFsCode);
    } else {
        fsShaderCode = strdup(fsShaderCode); // lua handles its own memory, we need to escape it
    }

    if (!vsShaderCode || !fsShaderCode) {
        sys_fatal("Failed to generate vertex and fragment shader, ran out of memory!");
    }

    return gfx_generate_vertex_and_fragment_shader(vertexShader, fragmentShader, gShaderInputs, gShaderBindings, vsShaderCode, fsShaderCode, fallbackVsCode, fallbackFsCode, outVertShader, outFragShader);
}

bool gfx_generate_post_process_vertex_and_fragment_shader(struct Shader *vertexShader, struct Shader *fragmentShader, char **outVertShader, char **outFragShader) {
    char *fallbackVsCode = strdup(gDefaultPostProcessVertexShader);
    char *fallbackFsCode = strdup(gDefaultPostProcessFragmentShader);
    char *vsShaderCode = NULL;
    char *fsShaderCode = NULL;
    if (!fallbackVsCode || !fallbackFsCode) {
        sys_fatal("Failed to generate vertex and fragment shader, ran out of memory!");
    }

    smlua_call_event_hooks(HOOK_ON_POST_PROCESS_VERTEX_SHADER_CREATE, (const char **)&vsShaderCode);

    if (!vsShaderCode) {
        vsShaderCode = strdup(fallbackVsCode);
    } else {
        vsShaderCode = strdup(vsShaderCode); // lua handles its own memory, we need to escape it
    }

    smlua_call_event_hooks(HOOK_ON_POST_PROCESS_FRAGMENT_SHADER_CREATE, (const char **)&fsShaderCode);

    if (!fsShaderCode) {
        fsShaderCode = strdup(fallbackFsCode);
    } else {
        fsShaderCode = strdup(fsShaderCode); // lua handles its own memory, we need to escape it
    }

    return gfx_generate_vertex_and_fragment_shader(vertexShader, fragmentShader, gPostProcessShaderInputs, gPostProcessShaderBindings, vsShaderCode, fsShaderCode, fallbackVsCode, fallbackFsCode, outVertShader, outFragShader);
}

void gfx_destroy_shader_contents(struct Shader *shader) {
    if (!shader) { return; }

    // cleanup uniform blocks
    for (int i = 0; i < shader->uniformBlockCount; i++) {
        struct ShaderUniformBlock *block = &shader->uniformBlocks[i];
        free(block->buffer);
        block->buffer = NULL;

#ifdef _WIN32
        if (gRenderApi == &gfx_direct3d11_api) {
            ID3D11Buffer_Release(block->dxConstantBuffer);
        }
#endif

        if (gRenderApi == &gfx_opengl_api) {
            glDeleteBuffers(1, &block->glBufferId);
        }
    }

    free(shader->spirVShader.words);
    shader->spirVShader.words = NULL;

    memset(shader, 0, sizeof(struct Shader));
}

void gfx_destroy_shader(struct Shader *shader) {
    if (!shader) { return; }
    gfx_destroy_shader_contents(shader);
    free(shader);
}
