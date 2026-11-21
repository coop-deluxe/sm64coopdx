#ifndef GFX_CC_H
#define GFX_CC_H

#include <stdint.h>
#include <stdbool.h>

enum ColorCombinerSource {
    CCS_0,
    CCS_1,
    CCS_TEXEL0,
    CCS_TEXEL1,
    CCS_PRIM,
    CCS_SHADE,
    CCS_ENV,
    CCS_COMBINED,
    CCS_TEXEL0A,
    CCS_TEXEL1A,
    CCS_PRIMA,
    CCS_SHADEA,
    CCS_ENVA,
    CCS_COMBINEDA,
    CCS_LOD,
    CCS_NOISE,
    CCS_COUNT,
};

enum {
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

#pragma pack(1)
struct CombineMode {
    union {
        struct {
            uint32_t rgb1;
            uint32_t alpha1;
            uint32_t rgb2;
            uint32_t alpha2;
        };
        uint8_t all_values[16];
    };
    union {
        struct {
            uint8_t use_alpha      : 1;
            uint8_t use_fog        : 1;
            uint8_t texture_edge   : 1;
            uint8_t use_dither     : 1;
            uint8_t use_2cycle     : 1;
            uint8_t light_map      : 1;
            uint8_t world_geometry : 1;
        };
        uint32_t flags;
    };
    uint64_t hash;
};
#pragma pack()

#define SHADER_CMD_LENGTH 16
#define CC_MAX_SHADERS 64

struct ColorCombiner {
    struct CombineMode cm;
    struct ShaderProgram *prg;
    union {
        uint8_t shader_input_mapping[16];
        uint64_t shader_input_mapping_as_u64[8];
    };
    union {
        uint8_t shader_commands[16];
        uint64_t shader_commands_as_u64[8];
    };
    uint64_t hash;
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
