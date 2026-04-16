#ifndef GFX_CC_H
#define GFX_CC_H

#include <PR/ultratypes.h>
#include <stdint.h>
#include <stdbool.h>

enum ColorCombinerSource {
    CC_0,
    CC_TEXEL0,
    CC_TEXEL1,
    CC_PRIM,
    CC_SHADE,
    CC_ENV,
    CC_TEXEL0A,
    CC_LOD,
    CC_1,
    CC_TEXEL1A,
    CC_COMBINED,
    CC_COMBINEDA,
    CC_PRIMA,
    CC_SHADEA,
    CC_ENVA,
    CC_NOISE,
    CC_ENUM_MAX,
};

enum ShaderInput {
    SHADER_0,
    SHADER_INPUT_1,
    SHADER_INPUT_2,
    SHADER_INPUT_3,
    SHADER_INPUT_4,
    SHADER_INPUT_5,
    SHADER_INPUT_6,
    SHADER_INPUT_7,
    SHADER_INPUT_8,
    SHADER_TEXEL0,
    SHADER_TEXEL0A,
    SHADER_TEXEL1,
    SHADER_TEXEL1A,
    SHADER_1,
    SHADER_COMBINED,
    SHADER_COMBINEDA,
    SHADER_NOISE,
};

#define SHADER_OPT_ALPHA (1 << 24)
#define SHADER_OPT_FOG (1 << 25)
#define SHADER_OPT_TEXTURE_EDGE (1 << 26)
#define SHADER_OPT_NOISE (1 << 27)

struct CCFeatures {
    bool used_textures[2];
    int num_inputs;
    bool do_single[4];
    bool do_multiply[4];
    bool do_mix[4];
    bool color_alpha_same[2];
    bool do_noise;
};

enum CombineModeFlags {
    USE_ALPHA    = 1 << 0,
    USE_FOG      = 1 << 1,
    TEXTURE_EDGE = 1 << 2,
    USE_DITHER   = 1 << 3,
    USE_2CYCLE   = 1 << 4,
    LIGHT_MAP    = 1 << 5
};

#pragma pack(1)
struct CombineMode {
    union {
        struct {
            u32 rgb1;
            u32 alpha1;
            u32 rgb2;
            u32 alpha2;
        };
        u8 all_values[16];
    };
    union {
        struct {
            u8 use_alpha    : 1;
            u8 use_fog      : 1;
            u8 texture_edge : 1;
            u8 use_dither   : 1;
            u8 use_2cycle   : 1;
            u8 light_map    : 1;
        };
        u32 flags;
    };
    s64 hash;
};
#pragma pack()

#define SHADER_CMD_LENGTH 16
#define CC_MAX_SHADERS 64
#define CC_MAX_INPUTS 8

struct ColorCombiner {
    struct CombineMode cm;
    struct ShaderProgram *prg;
    union {
        u8 shader_input_mapping[16];
        u64 shader_input_mapping_as_u64[8];
    };
    union {
        u8 shader_commands[16];
        u64 shader_commands_as_u64[8];
    };
    u64 hash;
};

#ifdef __cplusplus
extern "C" {
#endif

bool gfx_cm_uses_second_texture(struct CombineMode* cm);
void gfx_cc_get_features(struct ColorCombiner* cc, struct CCFeatures *cc_features);
void gfx_cc_print(struct ColorCombiner *cc);
void gfx_cc_precomp(void);
uint32_t color_comb_rgb(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint8_t cycle);
uint32_t color_comb_alpha(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint8_t cycle);

#ifdef __cplusplus
}
#endif

#endif
