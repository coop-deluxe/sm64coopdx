#ifdef RAPI_D3D11

#include <cstdio>

#include "gfx_direct3d_common.h"
#include "gfx_cc.h"

static void append_str(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
}

static void append_line(char *buf, size_t *len, const char *str) {
    while (*str != '\0') buf[(*len)++] = *str++;
    buf[(*len)++] = '\r';
    buf[(*len)++] = '\n';
}

static const char *shader_item_to_str(int32_t item, bool with_alpha, bool only_alpha, bool inputs_have_alpha, bool hint_single_element) {
    if (!only_alpha) {
        switch (item) {
            default:
            case SHADER_0:
                return with_alpha ? "float4(0.0, 0.0, 0.0, 0.0)" : "float3(0.0, 0.0, 0.0)";
            case SHADER_1:
                return with_alpha ? "float4(1.0, 1.0, 1.0, 1.0)" : "float3(1.0, 1.0, 1.0)";
            case SHADER_INPUT_1:
                return with_alpha || !inputs_have_alpha ? "input.input1" : "input.input1.rgb";
            case SHADER_INPUT_2:
                return with_alpha || !inputs_have_alpha ? "input.input2" : "input.input2.rgb";
            case SHADER_INPUT_3:
                return with_alpha || !inputs_have_alpha ? "input.input3" : "input.input3.rgb";
            case SHADER_INPUT_4:
                return with_alpha || !inputs_have_alpha ? "input.input4" : "input.input4.rgb";
            case SHADER_INPUT_5:
                return with_alpha || !inputs_have_alpha ? "input.input5" : "input.input5.rgb";
            case SHADER_INPUT_6:
                return with_alpha || !inputs_have_alpha ? "input.input6" : "input.input6.rgb";
            case SHADER_INPUT_7:
                return with_alpha || !inputs_have_alpha ? "input.input7" : "input.input7.rgb";
            case SHADER_INPUT_8:
                return with_alpha || !inputs_have_alpha ? "input.input8" : "input.input8.rgb";
            case SHADER_TEXEL0:
                return with_alpha ? "texVal0" : "texVal0.rgb";
            case SHADER_TEXEL0A:
                return hint_single_element ? "texVal0.a" : (with_alpha ? "float4(texVal0.a, texVal0.a, texVal0.a, texVal0.a)" : "float3(texVal0.a, texVal0.a, texVal0.a)");
            case SHADER_TEXEL1:
                return with_alpha ? "texVal1" : "texVal1.rgb";
            case SHADER_TEXEL1A:
                return hint_single_element ? "texVal1.a" : (with_alpha ? "float4(texVal1.a, texVal1.a, texVal1.a, texVal1.a)" : "float3(texVal1.a, texVal1.a, texVal1.a)");
            case SHADER_COMBINED:
                return with_alpha ? "texel" : "texel.rgb";
            case SHADER_COMBINEDA:
                return hint_single_element ? "texel.a" : (with_alpha ? "float4(texel.a, texel.a, texel.a, texel.a)" : "float3(texel.a, texel.a, texel.a)");
            case SHADER_NOISE:
                return with_alpha ? "float4(noise, noise, noise, noise)" : "float3(noise, noise, noise)";
        }
    } else {
        switch (item) {
            default:
            case SHADER_0:
                return "0.0";
            case SHADER_1:
                return "1.0";
            case SHADER_INPUT_1:
                return "input.input1.a";
            case SHADER_INPUT_2:
                return "input.input2.a";
            case SHADER_INPUT_3:
                return "input.input3.a";
            case SHADER_INPUT_4:
                return "input.input4.a";
            case SHADER_INPUT_5:
                return "input.input5.a";
            case SHADER_INPUT_6:
                return "input.input6.a";
            case SHADER_INPUT_7:
                return "input.input7.a";
            case SHADER_INPUT_8:
                return "input.input8.a";
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
}

static void append_formula(char *buf, size_t *len, const uint8_t* c, bool do_single, bool do_multiply, bool do_mix, bool with_alpha, bool only_alpha, bool opt_alpha) {
    if (do_single) {
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    } else if (do_multiply) {
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " * ");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
    } else if (do_mix) {
        append_str(buf, len, "lerp(");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ", ");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, ")");
    } else {
        append_str(buf, len, "(");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 0], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, " - ");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 1], with_alpha, only_alpha, opt_alpha, false));
        append_str(buf, len, ") * ");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 2], with_alpha, only_alpha, opt_alpha, true));
        append_str(buf, len, " + ");
        append_str(buf, len, shader_item_to_str(c[only_alpha * 4 + 3], with_alpha, only_alpha, opt_alpha, false));
    }
}

void gfx_direct3d_common_build_shader(char buf[4096], size_t& len, size_t& num_floats, struct ColorCombiner& cc, const CCFeatures& ccf, bool include_root_signature, bool three_point_filtering) {
    len = 0;
    num_floats = 4;

    // Pixel shader input struct

    if (include_root_signature) {
        append_str(buf, &len, "#define RS \"RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | DENY_VERTEX_SHADER_ROOT_ACCESS)");
        if ((cc.cm.use_alpha && cc.cm.use_dither) || ccf.do_noise) {
            append_str(buf, &len, ",CBV(b0, visibility = SHADER_VISIBILITY_PIXEL)");
        }
        if (ccf.used_textures[0]) {
            append_str(buf, &len, ",DescriptorTable(SRV(t0), visibility = SHADER_VISIBILITY_PIXEL)");
            append_str(buf, &len, ",DescriptorTable(Sampler(s0), visibility = SHADER_VISIBILITY_PIXEL)");
        }
        if (ccf.used_textures[1]) {
            append_str(buf, &len, ",DescriptorTable(SRV(t1), visibility = SHADER_VISIBILITY_PIXEL)");
            append_str(buf, &len, ",DescriptorTable(Sampler(s1), visibility = SHADER_VISIBILITY_PIXEL)");
        }
        append_line(buf, &len, "\"");
    }

    append_line(buf, &len, "struct PSInput {");
    append_line(buf, &len, "    float4 position : SV_POSITION;");
    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_line(buf, &len, "    float2 uv : TEXCOORD;");
        num_floats += 2;
    }
    if ((cc.cm.use_alpha && cc.cm.use_dither) || ccf.do_noise) {
        append_line(buf, &len, "    float4 screenPos : TEXCOORD1;");
    }
    if (cc.cm.use_fog) {
        append_line(buf, &len, "    float4 fog : FOG;");
        num_floats += 4;
    }
    if (cc.cm.light_map) {
        append_line(buf, &len, "    float2 lightmap : LIGHTMAP;");
        num_floats += 2;
    }
    for (int32_t i = 0; i < ccf.num_inputs; i++) {
        len += sprintf(buf + len, "    float%d input%d : INPUT%d;\r\n", cc.cm.use_alpha ? 4 : 3, i + 1, i);
        num_floats += cc.cm.use_alpha ? 4 : 3;
    }
    append_line(buf, &len, "};");

    // Textures and samplers

    if (ccf.used_textures[0]) {
        append_line(buf, &len, "Texture2D g_texture0 : register(t0);");
        append_line(buf, &len, "SamplerState g_sampler0 : register(s0);");
    }
    if (ccf.used_textures[1]) {
        append_line(buf, &len, "Texture2D g_texture1 : register(t1);");
        append_line(buf, &len, "SamplerState g_sampler1 : register(s1);");
    }

    // Constant buffer and random function

    if ((cc.cm.use_alpha && cc.cm.use_dither) || ccf.do_noise) {
        append_line(buf, &len, "cbuffer PerFrameCB : register(b0) {");
        append_line(buf, &len, "    uint noise_frame;");
        append_line(buf, &len, "    float2 noise_scale;");
        append_line(buf, &len, "}");

        append_line(buf, &len, "float random(in float3 value) {");
        append_line(buf, &len, "    float random = dot(value, float3(12.9898, 78.233, 37.719));");
        append_line(buf, &len, "    return frac(sin(random) * 143758.5453);");
        append_line(buf, &len, "}");
    }

    // 3 point texture filtering
    // Original author: ArthurCarvalho
    // Based on GLSL implementation by twinaphex, mupen64plus-libretro project.

    if (three_point_filtering && (ccf.used_textures[0] || ccf.used_textures[1])) {
        append_line(buf, &len, "cbuffer PerDrawCB : register(b1) {");
        append_line(buf, &len, "    struct {");
        append_line(buf, &len, "        uint width;");
        append_line(buf, &len, "        uint height;");
        append_line(buf, &len, "        bool linear_filtering;");
        append_line(buf, &len, "    } textures[2];");
        append_line(buf, &len, "}");
        append_line(buf, &len, "#define TEX_OFFSET(tex, tSampler, texCoord, off, texSize) tex.Sample(tSampler, texCoord - off / texSize)");
        append_line(buf, &len, "float4 tex2D3PointFilter(in Texture2D tex, in SamplerState tSampler, in float2 texCoord, in float2 texSize) {");
        append_line(buf, &len, "    float2 offset = frac(texCoord * texSize - float2(0.5, 0.5));");
        append_line(buf, &len, "    offset -= step(1.0, offset.x + offset.y);");
        append_line(buf, &len, "    float4 c0 = TEX_OFFSET(tex, tSampler, texCoord, offset, texSize);");
        append_line(buf, &len, "    float4 c1 = TEX_OFFSET(tex, tSampler, texCoord, float2(offset.x - sign(offset.x), offset.y), texSize);");
        append_line(buf, &len, "    float4 c2 = TEX_OFFSET(tex, tSampler, texCoord, float2(offset.x, offset.y - sign(offset.y)), texSize);");
        append_line(buf, &len, "    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);");
        append_line(buf, &len, "}");
    }

    // Vertex shader

    append_str(buf, &len, "PSInput VSMain(float4 position : POSITION");
    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_str(buf, &len, ", float2 uv : TEXCOORD");
    }
    if (cc.cm.use_fog) {
        append_str(buf, &len, ", float4 fog : FOG");
    }
    if (cc.cm.light_map) {
        append_str(buf, &len, ", float2 lightmap : LIGHTMAP");
    }
    for (int32_t i = 0; i < ccf.num_inputs; i++) {
        len += sprintf(buf + len, ", float%d input%d : INPUT%d", cc.cm.use_alpha ? 4 : 3, i + 1, i);
    }
    append_line(buf, &len, ") {");
    append_line(buf, &len, "    PSInput result;");
    append_line(buf, &len, "    result.position = position;");
    if ((cc.cm.use_alpha && cc.cm.use_dither) || ccf.do_noise) {
        append_line(buf, &len, "    result.screenPos = position;");
    }
    if (ccf.used_textures[0] || ccf.used_textures[1]) {
        append_line(buf, &len, "    result.uv = uv;");
    }
    if (cc.cm.use_fog) {
        append_line(buf, &len, "    result.fog = fog;");
    }
    if (cc.cm.light_map) {
        append_line(buf, &len, "    result.lightmap = lightmap;");
    }
    for (int32_t i = 0; i < ccf.num_inputs; i++) {
        len += sprintf(buf + len, "    result.input%d = input%d;\r\n", i + 1, i + 1);
    }
    append_line(buf, &len, "    return result;");
    append_line(buf, &len, "}");

    // Pixel shader
    if (include_root_signature) {
        append_line(buf, &len, "[RootSignature(RS)]");
    }
    append_line(buf, &len, "float4 PSMain(PSInput input) : SV_TARGET {");

    if ((cc.cm.use_alpha && cc.cm.use_dither) || ccf.do_noise) {
        append_line(buf, &len, "    float2 coords = (input.screenPos.xy / input.screenPos.w) * noise_scale;");
        append_line(buf, &len, "    float noise = round(random(float3(floor(coords), noise_frame)));");
    }

    if (ccf.used_textures[0]) {
        if (three_point_filtering) {
            append_line(buf, &len, "    float4 texVal0;");
            append_line(buf, &len, "    if (textures[0].linear_filtering)");
            append_line(buf, &len, "        texVal0 = tex2D3PointFilter(g_texture0, g_sampler0, input.uv, float2(textures[0].width, textures[0].height));");
            append_line(buf, &len, "    else");
            append_line(buf, &len, "        texVal0 = g_texture0.Sample(g_sampler0, input.uv);");
        } else {
            append_line(buf, &len, "    float4 texVal0 = g_texture0.Sample(g_sampler0, input.uv);");
        }
    }
    if (ccf.used_textures[1]) {
        if (cc.cm.light_map) {
            if (three_point_filtering) {
                append_line(buf, &len, "    float4 texVal1;");
                append_line(buf, &len, "    if (textures[1].linear_filtering)");
                append_line(buf, &len, "        texVal1 = tex2D3PointFilter(g_texture1, g_sampler1, input.lightmap, float2(textures[1].width, textures[1].height));");
                append_line(buf, &len, "    else");
                append_line(buf, &len, "        texVal1 = g_texture1.Sample(g_sampler1, input.lightmap);");
            } else {
                append_line(buf, &len, "    float4 texVal1 = g_texture1.Sample(g_sampler1, input.lightmap);");
            }
            append_line(buf, &len, "    texVal1.rgb = texVal1.rgb * texVal1.rgb + texVal1.rgb;");
        } else {
            if (three_point_filtering) {
                append_line(buf, &len, "    float4 texVal1;");
                append_line(buf, &len, "    if (textures[1].linear_filtering)");
                append_line(buf, &len, "        texVal1 = tex2D3PointFilter(g_texture1, g_sampler1, input.uv, float2(textures[1].width, textures[1].height));");
                append_line(buf, &len, "    else");
                append_line(buf, &len, "        texVal1 = g_texture1.Sample(g_sampler1, input.uv);");
            } else {
                append_line(buf, &len, "    float4 texVal1 = g_texture1.Sample(g_sampler1, input.uv);");
            }
        }
    }

    append_str(buf, &len, cc.cm.use_alpha ? "    float4 texel = " : "    float3 texel = ");
    for (int i = 0; i < (cc.cm.use_2cycle + 1); i++) {
        uint8_t* cmd = &cc.shader_commands[i * 8];
        if (!ccf.color_alpha_same[i] && cc.cm.use_alpha) {
            append_str(buf, &len, "float4(");
            append_formula(buf, &len, cmd, ccf.do_single[i*2+0], ccf.do_multiply[i*2+0], ccf.do_mix[i*2+0], false, false, true);
            append_str(buf, &len, ", ");
            append_formula(buf, &len, cmd, ccf.do_single[i*2+1], ccf.do_multiply[i*2+1], ccf.do_mix[i*2+1], true, true, true);
            append_str(buf, &len, ")");
        } else {
            append_formula(buf, &len, cmd, ccf.do_single[i*2+0], ccf.do_multiply[i*2+0], ccf.do_mix[i*2+0], cc.cm.use_alpha, false, cc.cm.use_alpha);
        }
        append_line(buf, &len, ";");

        if (i == 0 && cc.cm.use_2cycle) {
            append_str(buf, &len, "texel = ");
        }
    }

    if (cc.cm.texture_edge && cc.cm.use_alpha) {
        append_line(buf, &len, "    if (texel.a > 0.3) texel.a = 1.0; else discard;");
    }
    // TODO discard if alpha is 0?
    if (cc.cm.use_fog) {
        if (cc.cm.use_alpha) {
            append_line(buf, &len, "    texel = float4(lerp(texel.rgb, input.fog.rgb, input.fog.a), texel.a);");
        } else {
            append_line(buf, &len, "    texel = lerp(texel, input.fog.rgb, input.fog.a);");
        }
    }

    if (cc.cm.use_alpha && cc.cm.use_dither) {
        append_line(buf, &len, "    texel.a *= noise;");
    }

    if (cc.cm.use_alpha) {
        append_line(buf, &len, "    return texel;");
    } else {
        append_line(buf, &len, "    return float4(texel, 1.0);");
    }
    append_line(buf, &len, "}");
}

#endif
