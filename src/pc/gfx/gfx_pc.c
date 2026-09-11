#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef __SSE__
#include <xmmintrin.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#ifndef _LANGUAGE_C
#define _LANGUAGE_C
#endif
#include <PR/gbi.h>

#include "config.h"
#include "macros.h"

#include "engine/lighting_engine.h"
#include "engine/math_util.h"

#include "game/object_helpers.h"
#include "game/rendering_graph_node.h"

#include "pc/configfile.h"
#include "pc/debug_context.h"
#include "pc/pc_main.h"
#include "pc/platform.h"

#include "pc/fs/fs.h"

#include "pc/gfx/gfx_cc.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/gfx/gfx_rendering_api.h"
#include "pc/gfx/gfx_screen_config.h"
#include "pc/gfx/gfx_window_manager.h"

#include "pc/lua/smlua.h"

#include "pc/debuglog.h"

#define G_TX_LOADTILE_6_UNKNOWN 6

u8 gGfxPcResetTex1 = 0;

static struct TextureCache gfx_texture_cache = { 0 };
static struct ColorCombiner color_combiner_pool[CC_MAX_SHADERS] = { 0 };
static uint8_t color_combiner_pool_size = 0;
static uint8_t color_combiner_pool_index = 0;

static struct ColorCombiner *sPrevCombinerForLookup = NULL;

struct RSP rsp = { 0 };
struct FramePass gDefaultGeoFramePass = { 0 };
struct FramePass gFramePasses[MAX_CUSTOM_FRAME_PASSES] = { 0 };
int gCurrentFramePassIndex = -1;

struct RDP {
    const uint8_t *palette[2];
    struct UnloadedTex texture_to_load;
    struct TextureTile texture_tile[MAX_TILES];
    struct GfxTexture loaded_texture[MAX_TEXTURES];
    bool textures_changed[MAX_TEXTURES];

    uint32_t other_mode_l, other_mode_h;
    struct CombineMode combine_mode;

    struct RGBA env_color, prim_color, fog_color, fill_color;
    struct Box viewport, scissor;
    bool viewport_or_scissor_changed;
    void *z_buf_address;
    void *color_image_address;
};
static struct RDP rdp;

struct GfxState {
    struct RSP rsp;
    struct RDP rdp;
};
static struct GfxState gfx_states[MAX_GFX_STATES];
static size_t num_gfx_states;

static struct RenderingState {
    bool depth_test;
    bool depth_mask;
    bool decal_mode;
    bool alpha_blend;
    bool fog_enabled;
    f32 depth_z_sub;
    f32 depth_z_mult;
    f32 depth_z_add;
    s16 fog_mul;
    f32 fog_intensity;
    s16 fog_offset;
    u8 fog_color_r;
    u8 fog_color_g;
    u8 fog_color_b;
    u8 rdp_fog_color_r;
    u8 rdp_fog_color_g;
    u8 rdp_fog_color_b;
    struct Box viewport, scissor;
    struct ShaderProgram *shader_program;
    struct TextureHashmapNode *textures[2];
    ALIGNED16 Mat4 mvp_matrix;
    ALIGNED16 Mat4 mv_matrix;
    ALIGNED16 Mat4 m_matrix;
    ALIGNED16 Mat4 v_matrix;
    ALIGNED16 Mat4 p_matrix;
    u32 x_adjust_4by3;
    u32 y_adjust_4by3;
} sRenderingState;

struct GfxDimensions gfx_current_dimensions = { 0 };

static bool sDroppedFrame = false;

static float buf_vbo[VERTEX_STRIDE] = { 0.0f };
static size_t buf_vbo_len = 0;
static size_t buf_vbo_num_tris = 0;

static struct GfxRenderingAPI *gfx_rapi = NULL;

static f32 sDepthZAdd = 0;
static f32 sDepthZMult = 1;
static f32 sDepthZSub = 0;

Vec3f gLightingDir = { 0.0f, 0.0f, 0.0f };
Color gLightingColor[2] = { { 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF } };
Color gVertexColor = { 0xFF, 0xFF, 0xFF };
Color gFogColor = { 0xFF, 0xFF, 0xFF };
f32 gFogIntensity = 1.0f;
bool gCullingEnabled = true;

bool gFullbright = false;

int gShaderFlags[SHADER_FLAG_MAX] = { 0 };
f32 gDefaultShaderFlagValues[SHADER_FLAG_MAX] = {
    [SHADER_FLAG_HUE] = 0.0f,
    [SHADER_FLAG_SATURATION] = 1.0f,
    [SHADER_FLAG_BRIGHTNESS] = 1.0f,
    [SHADER_FLAG_CONTRAST] = 1.0f,
    [SHADER_FLAG_EXPOSURE] = 1.0f,
    [SHADER_FLAG_DITHERING] = 0.0f,
    [SHADER_FLAG_POSTERIZATION] = 8.0f,
    [SHADER_FLAG_SCANLINES] = 1.0f
};
f32 gShaderFlagValues[SHADER_FLAG_MAX] = { 0 };
bool gShaderFlagsEnabled = true;

int gSelectedVertexUniformBuffer = 0;
int gSelectedFragmentUniformBuffer = 0;

enum ShaderStage gSelectedShaderStage = SHADER_STAGE_ANY;

static u32 sFrameCount = 0;

// 4x4 pink-black checkerboard texture to indicate missing textures
#define MISSING_W 4
#define MISSING_H 4
UNUSED static const uint8_t missing_texture[MISSING_W * MISSING_H * 4] = {
    0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,
};

static bool sOnlyTextureChangeOnAddrChange = false;
static void gfx_update_loaded_texture(uint8_t tile_number, uint32_t size_bytes, const uint8_t* addr) {
    if (tile_number >= MAX_TILES) { return; }
    tile_number = rdp.texture_tile[tile_number].index;
    if (!sOnlyTextureChangeOnAddrChange) {
        rdp.textures_changed[tile_number] = true;
    } else if (!rdp.textures_changed[tile_number]) {
        rdp.textures_changed[tile_number] = rdp.loaded_texture[tile_number].addr != addr;
    }
    rdp.loaded_texture[tile_number].size_bytes = size_bytes;
    rdp.loaded_texture[tile_number].addr = addr;
}

//////////////////////////
// forward declaration //
////////////////////////
void ext_gfx_run_dl(Gfx* cmd);

//////////////////////////////////

/*static unsigned long get_time(void) {
    return 0;
}*/
static void gfx_flush(void) {
    if (buf_vbo_len > 0) {
        gfx_rapi->draw_triangles(buf_vbo, buf_vbo_len, buf_vbo_num_tris);
        buf_vbo_len = 0;
        buf_vbo_num_tris = 0;
    }
}

static void combine_mode_update_hash(struct CombineMode* cm) {
    uint64_t hash = 5381;

    cm->hash = 0;

    hash = (hash << 5) + hash + ((u64)cm->rgb1 << 32);
    if (cm->use_alpha) {
        hash = (hash << 5) + hash + ((u64)cm->alpha1);
    }

    if (cm->use_2cycle) {
        hash = (hash << 5) + hash + ((u64)cm->rgb2 << 32);
        if (cm->use_alpha) {
            hash = (hash << 5) + hash + ((u64)cm->alpha2);
        }
    }

    hash = (hash << 5) + hash + cm->flags;

    cm->hash = hash;
}

static void color_combiner_update_hash(struct ColorCombiner* cc) {
    uint64_t hash = cc->cm.hash;

    for (int i = 0; i < 8; i++) {
        hash = (hash << 5) + hash + cc->shader_input_mapping_as_u64[i];
        hash = (hash << 5) + hash + cc->shader_commands_as_u64[i];
    }

    cc->hash = hash;
}

static struct ShaderProgram *gfx_lookup_or_create_shader_program(struct ColorCombiner* cc) {
    struct ShaderProgram *prg = gfx_rapi->lookup_shader(cc);
    if (prg == NULL) {
        gfx_rapi->unload_shader(sRenderingState.shader_program);
        prg = gfx_rapi->create_and_load_new_shader(cc);
        sRenderingState.shader_program = prg;
    }
    return prg;
}

static void gfx_generate_cc(struct ColorCombiner *cc) {
    u8 next_input_number = 0;
    u8 input_number[CCS_COUNT] = { 0 };

    for  (int i = 0; i < SHADER_CMD_LENGTH; i++) {
        u8 cm_cmd = cc->cm.all_values[i];
        u8 shader_cmd = 0;
        switch (cm_cmd) {
            case CCS_0:
                shader_cmd = SHADER_0;
                break;
            case CCS_1:
                shader_cmd = SHADER_1;
                break;
            case CCS_TEXEL0:
                shader_cmd = SHADER_TEXEL0;
                break;
            case CCS_TEXEL1:
                shader_cmd = SHADER_TEXEL1;
                break;
            case CCS_TEXEL0A:
                shader_cmd = SHADER_TEXEL0A;
                break;
            case CCS_TEXEL1A:
                shader_cmd = SHADER_TEXEL1A;
                break;
            case CCS_COMBINED:
                shader_cmd = cc->cm.use_2cycle ? SHADER_COMBINED : SHADER_0;
                break;
            case CCS_COMBINEDA:
                shader_cmd = cc->cm.use_2cycle ? SHADER_COMBINEDA : SHADER_0;
                break;
            case CCS_NOISE:
                shader_cmd = SHADER_NOISE;
                break;
            case CCS_PRIM:
            case CCS_PRIMA:
            case CCS_SHADE:
            case CCS_SHADEA:
            case CCS_ENV:
            case CCS_ENVA:
            case CCS_LOD:
                if (input_number[cm_cmd] == 0) {
                    cc->shader_input_mapping[next_input_number] = cm_cmd;
                    input_number[cm_cmd] = SHADER_INPUT_1 + next_input_number;
                    next_input_number++;
                }
                shader_cmd = input_number[cm_cmd];
                break;
            default:
                shader_cmd = SHADER_0;
                break;
        }
        cc->shader_commands[i] = shader_cmd;
    }

    color_combiner_update_hash(cc);
    cc->prg = gfx_lookup_or_create_shader_program(cc);
    gfx_cc_print(cc);
}

static struct ColorCombiner *gfx_lookup_or_create_color_combiner(struct CombineMode* cm) {
    combine_mode_update_hash(cm);

    if (sPrevCombinerForLookup != NULL && sPrevCombinerForLookup->cm.hash == cm->hash) {
        return sPrevCombinerForLookup;
    }

    for (size_t i = 0; i < color_combiner_pool_size; i++) {
        if (color_combiner_pool[i].cm.hash == cm->hash) {
            if (color_combiner_pool[i].prg == NULL) {
                color_combiner_pool[i].prg = gfx_lookup_or_create_shader_program(&color_combiner_pool[i]);
            }
            return sPrevCombinerForLookup = &color_combiner_pool[i];
        }
    }

    gfx_flush();

    struct ColorCombiner *comb = &color_combiner_pool[color_combiner_pool_index];
    color_combiner_pool_index = (color_combiner_pool_index + 1) % CC_MAX_SHADERS;
    if (color_combiner_pool_size < CC_MAX_SHADERS) { color_combiner_pool_size++; }

    memcpy(&comb->cm, cm, sizeof(struct CombineMode));
    gfx_generate_cc(comb);

    return sPrevCombinerForLookup = comb;
}

void gfx_texture_cache_clear(void) {
    memset(&gfx_texture_cache, 0, sizeof(gfx_texture_cache));
}

static bool gfx_texture_cache_lookup(int tile, struct TextureHashmapNode **n, const uint8_t *orig_addr, uint32_t fmt, uint32_t siz) {
    size_t hash = (uintptr_t)orig_addr;
#define CMPADDR(x, y) x == y

    hash = (hash >> HASH_SHIFT) & HASH_MASK;

    struct TextureHashmapNode **node = &gfx_texture_cache.hashmap[hash];
    while (node != NULL && *node != NULL && *node - gfx_texture_cache.pool < (int)gfx_texture_cache.pool_pos) {
        if (CMPADDR((*node)->texture_addr, orig_addr) && (*node)->fmt == fmt && (*node)->siz == siz) {
            gfx_rapi->select_texture(tile, (*node)->texture_id);
            *n = *node;
            return true;
        }
        node = &(*node)->next;
    }
    if (gfx_texture_cache.pool_pos >= sizeof(gfx_texture_cache.pool) / sizeof(struct TextureHashmapNode)) {
        // Pool is full. We just invalidate everything and start over.
        gfx_texture_cache.pool_pos = 0;
        node = &gfx_texture_cache.hashmap[hash];
        // puts("Clearing texture cache");
    }
    if (!node) { return false; }
    *node = &gfx_texture_cache.pool[gfx_texture_cache.pool_pos++];
    if ((*node)->texture_addr == NULL) {
        (*node)->texture_id = gfx_rapi->new_texture();
    }
    gfx_rapi->select_texture(tile, (*node)->texture_id);
    gfx_rapi->set_sampler_parameters(tile, false, 0, 0);
    (*node)->next = NULL;
    (*node)->texture_addr = orig_addr;
    (*node)->fmt = fmt;
    (*node)->siz = siz;
    (*node)->cms = 0;
    (*node)->cmt = 0;
    (*node)->linear_filter = false;
    *n = *node;
    return false;
    #undef CMPADDR
}

static void import_texture_rgba32(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    uint32_t width = rdp.texture_tile[tile].line_size_bytes / 2;
    uint32_t height = (rdp.loaded_texture[tile].size_bytes / 2) / rdp.texture_tile[tile].line_size_bytes;
    gfx_rapi->upload_texture(rdp.loaded_texture[tile].addr, width, height);
}

static void import_texture_rgba16(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 2 > 0x2000) { return; }
    uint8_t rgba32_buf[0x2000];

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes / 2; i++) {
        uint16_t col16 = (rdp.loaded_texture[tile].addr[2 * i] << 8) | rdp.loaded_texture[tile].addr[2 * i + 1];
        uint8_t a = col16 & 1;
        uint8_t r = col16 >> 11;
        uint8_t g = (col16 >> 6) & 0x1f;
        uint8_t b = (col16 >> 1) & 0x1f;
        rgba32_buf[4*i + 0] = SCALE_5_8(r);
        rgba32_buf[4*i + 1] = SCALE_5_8(g);
        rgba32_buf[4*i + 2] = SCALE_5_8(b);
        rgba32_buf[4*i + 3] = a ? 255 : 0;
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes / 2;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture_ia4(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 8 > 0x8000) { return; }
    uint8_t rgba32_buf[0x8000];

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes * 2; i++) {
        uint8_t byte = rdp.loaded_texture[tile].addr[i / 2];
        uint8_t part = (byte >> (4 - (i % 2) * 4)) & 0xf;
        uint8_t intensity = part >> 1;
        uint8_t alpha = part & 1;
        uint8_t r = intensity;
        uint8_t g = intensity;
        uint8_t b = intensity;
        rgba32_buf[4*i + 0] = SCALE_3_8(r);
        rgba32_buf[4*i + 1] = SCALE_3_8(g);
        rgba32_buf[4*i + 2] = SCALE_3_8(b);
        rgba32_buf[4*i + 3] = alpha ? 255 : 0;
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes * 2;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture_ia8(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 4 > 0x4000) { return; }
    uint8_t rgba32_buf[0x4000];

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes; i++) {
        uint8_t intensity = rdp.loaded_texture[tile].addr[i] >> 4;
        uint8_t alpha = rdp.loaded_texture[tile].addr[i] & 0xf;
        uint8_t r = intensity;
        uint8_t g = intensity;
        uint8_t b = intensity;
        rgba32_buf[4*i + 0] = SCALE_4_8(r);
        rgba32_buf[4*i + 1] = SCALE_4_8(g);
        rgba32_buf[4*i + 2] = SCALE_4_8(b);
        rgba32_buf[4*i + 3] = SCALE_4_8(alpha);
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture_ia16(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 2 > 0x2000) { return; }
    uint8_t rgba32_buf[0x2000];

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes / 2; i++) {
        uint8_t intensity = rdp.loaded_texture[tile].addr[2 * i];
        uint8_t alpha = rdp.loaded_texture[tile].addr[2 * i + 1];
        uint8_t r = intensity;
        uint8_t g = intensity;
        uint8_t b = intensity;
        rgba32_buf[4*i + 0] = r;
        rgba32_buf[4*i + 1] = g;
        rgba32_buf[4*i + 2] = b;
        rgba32_buf[4*i + 3] = alpha;
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes / 2;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture_i4(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 8 > 0x8000) { return; }
    uint8_t rgba32_buf[0x8000];

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes * 2; i++) {
        uint8_t byte = rdp.loaded_texture[tile].addr[i / 2];
        uint8_t intensity = (byte >> (4 - (i % 2) * 4)) & 0xf;
        rgba32_buf[4*i + 0] = SCALE_4_8(intensity);
        rgba32_buf[4*i + 1] = SCALE_4_8(intensity);
        rgba32_buf[4*i + 2] = SCALE_4_8(intensity);
        rgba32_buf[4*i + 3] = 255;
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes * 2;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture_i8(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 4 > 0x4000) { return; }
    uint8_t rgba32_buf[0x4000];

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes; i++) {
        uint8_t intensity = rdp.loaded_texture[tile].addr[i];
        rgba32_buf[4*i + 0] = intensity;
        rgba32_buf[4*i + 1] = intensity;
        rgba32_buf[4*i + 2] = intensity;
        rgba32_buf[4*i + 3] = 255;
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture_ci4(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 8 > 0x8000) { return; }
    uint8_t rgba32_buf[0x8000];

    uint32_t palIndex = rdp.texture_tile[tile].palette;
    const uint8_t* palette;
    if (palIndex > 7)
        palette = rdp.palette[palIndex / 8];
    else
        palette = rdp.palette[palIndex / 8] + (palIndex % 8) * 16 * 2;

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes * 2; i++) {
        uint8_t byte = rdp.loaded_texture[tile].addr[i / 2];
        uint8_t idx = (byte >> (4 - (i % 2) * 4)) & 0xf;
        uint16_t col16 = (palette[idx * 2] << 8) | palette[idx * 2 + 1]; // Big endian load
        uint8_t a = col16 & 1;
        uint8_t r = col16 >> 11;
        uint8_t g = (col16 >> 6) & 0x1f;
        uint8_t b = (col16 >> 1) & 0x1f;
        rgba32_buf[4*i + 0] = SCALE_5_8(r);
        rgba32_buf[4*i + 1] = SCALE_5_8(g);
        rgba32_buf[4*i + 2] = SCALE_5_8(b);
        rgba32_buf[4*i + 3] = a ? 255 : 0;
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes * 2;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture_ci8(int tile) {
    tile = tile % MAX_TILES;
    if (!rdp.loaded_texture[tile].addr) { return; }
    if (rdp.loaded_texture[tile].size_bytes * 4 > 0x4000) { return; }
    uint8_t rgba32_buf[0x4000];

    for (uint32_t i = 0; i < rdp.loaded_texture[tile].size_bytes; i++) {
        uint8_t idx = rdp.loaded_texture[tile].addr[i];
        const uint8_t *palette = rdp.palette[idx / 128];
        uint16_t col16 = (palette[idx * 2] << 8) | palette[idx * 2 + 1]; // Big endian load
        uint8_t a = col16 & 1;
        uint8_t r = col16 >> 11;
        uint8_t g = (col16 >> 6) & 0x1f;
        uint8_t b = (col16 >> 1) & 0x1f;
        rgba32_buf[4*i + 0] = SCALE_5_8(r);
        rgba32_buf[4*i + 1] = SCALE_5_8(g);
        rgba32_buf[4*i + 2] = SCALE_5_8(b);
        rgba32_buf[4*i + 3] = a ? 255 : 0;
    }

    uint32_t width = rdp.texture_tile[tile].line_size_bytes;
    uint32_t height = rdp.loaded_texture[tile].size_bytes / rdp.texture_tile[tile].line_size_bytes;

    gfx_rapi->upload_texture(rgba32_buf, width, height);
}

static void import_texture(int tile) {
    tile = tile % MAX_TILES;
    extern s32 dynos_tex_import(void **output, void *ptr, s32 tile, void *grapi, void **hashmap, void *pool, s32 *poolpos, s32 poolsize);
    if (dynos_tex_import((void **) &sRenderingState.textures[tile], (void *) rdp.loaded_texture[tile].addr, tile, gfx_rapi, (void **) gfx_texture_cache.hashmap, (void *) gfx_texture_cache.pool, (int *) &gfx_texture_cache.pool_pos, MAX_CACHED_TEXTURES)) { return; }
    uint8_t fmt = rdp.texture_tile[tile].fmt;
    uint8_t siz = rdp.texture_tile[tile].siz;

    if (!rdp.loaded_texture[tile].addr) {
#ifdef DEVELOPMENT
/*
        fprintf(stderr, "NULL texture: tile %d, format %d/%d, size %d\n",
                tile, (int)fmt, (int)siz, (int)rdp.loaded_texture[tile].size_bytes);
*/
#endif
        return;
    }

    if (gfx_texture_cache_lookup(tile, &sRenderingState.textures[tile], rdp.loaded_texture[tile].addr, fmt, siz)) {
        return;
    }

    // the texture data is actual texture data
    //int t0 = get_time();
    if (fmt == G_IM_FMT_RGBA) {
        if (siz == G_IM_SIZ_32b) {
            import_texture_rgba32(tile);
        }
        else if (siz == G_IM_SIZ_16b) {
            import_texture_rgba16(tile);
        } else {
            sys_fatal("unsupported RGBA texture size: %u", siz);
        }
    } else if (fmt == G_IM_FMT_IA) {
        if (siz == G_IM_SIZ_4b) {
            import_texture_ia4(tile);
        } else if (siz == G_IM_SIZ_8b) {
            import_texture_ia8(tile);
        } else if (siz == G_IM_SIZ_16b) {
            import_texture_ia16(tile);
        } else {
            sys_fatal("unsupported IA texture size: %u", siz);
        }
    } else if (fmt == G_IM_FMT_CI) {
        if (siz == G_IM_SIZ_4b) {
            import_texture_ci4(tile);
        } else if (siz == G_IM_SIZ_8b) {
            import_texture_ci8(tile);
        } else {
            sys_fatal("unsupported CI texture size: %u", siz);
        }
    } else if (fmt == G_IM_FMT_I) {
        if (siz == G_IM_SIZ_4b) {
            import_texture_i4(tile);
        } else if (siz == G_IM_SIZ_8b) {
            import_texture_i8(tile);
        } else {
            sys_fatal("unsupported I texture size: %u", siz);
        }
    } else {
        sys_fatal("unsupported texture format: %u", fmt);
    }
    //int t1 = get_time();
    //printf("Time diff: %d\n", t1 - t0);
}

static void OPTIMIZE_O3 gfx_transposed_matrix_mul(VEC_OUT Vec3f res, const Vec3f a, const Mat4 b) {
    res[0] = a[0] * b[0][0] + a[1] * b[0][1] + a[2] * b[0][2];
    res[1] = a[0] * b[1][0] + a[1] * b[1][1] + a[2] * b[1][2];
    res[2] = a[0] * b[2][0] + a[1] * b[2][1] + a[2] * b[2][2];
}

static void calculate_normal_dir(const Light_t *light, Vec3f coeffs, bool applyLightingDir) {
    float light_dir[3] = {
        light->dir[0] / 127.0f,
        light->dir[1] / 127.0f,
        light->dir[2] / 127.0f
    };

    if (applyLightingDir) {
        light_dir[0] += gLightingDir[0];
        light_dir[1] += gLightingDir[1];
        light_dir[2] += gLightingDir[2];
    }

    gfx_transposed_matrix_mul(coeffs, light_dir, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1]);
    vec3f_normalize(coeffs);
}

static void OPTIMIZE_O3 gfx_sp_matrix(uint8_t parameters, const int32_t *addr) {

    Mat4 matrix;

#if 0
    // Original code when fixed point matrices were used
    for (int32_t i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j += 2) {
            int32_t int_part = addr[i * 2 + j / 2];
            uint32_t frac_part = addr[8 + i * 2 + j / 2];
            matrix[i][j] = (int32_t)((int_part & 0xffff0000) | (frac_part >> 16)) / 65536.0f;
            matrix[i][j + 1] = (int32_t)((int_part << 16) | (frac_part & 0xffff)) / 65536.0f;
        }
    }
#else
    memcpy(matrix, addr, sizeof(matrix));
#endif

    gfx_flush();

    if (parameters & G_MTX_PROJECTION) {
        if (parameters & G_MTX_LOAD) {
            mtxf_copy(rsp.P_matrix, matrix);
        } else {
            mtxf_mul(rsp.P_matrix, matrix, rsp.P_matrix);
        }
    } else { // G_MTX_MODELVIEW
        if ((parameters & G_MTX_PUSH) && rsp.modelview_matrix_stack_size < MAX_MATRIX_STACK_SIZE) {
            ++rsp.modelview_matrix_stack_size;
            mtxf_copy(rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 2]);
        }
        if (parameters & G_MTX_LOAD) {
            mtxf_copy(rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], matrix);
        } else {
            mtxf_mul(rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1]);
        }
        rsp.lights_changed = 1;
    }
    mtxf_inverse(rsp.V_matrix, gInverseCameraMatrix.m);
    mtxf_mul(rsp.M_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], gInverseCameraMatrix.m);
    mtxf_mul(rsp.MVP_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], rsp.P_matrix);
}

static void gfx_sp_pop_matrix(uint32_t count) {
    gfx_flush();
    while (count--) {
        if (rsp.modelview_matrix_stack_size > 0) {
            --rsp.modelview_matrix_stack_size;
            if (rsp.modelview_matrix_stack_size > 0) {
                mtxf_mul(rsp.M_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], gInverseCameraMatrix.m);
                mtxf_mul(rsp.MVP_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], rsp.P_matrix);
            }
        }
    }
}

static float gfx_adjust_x_for_aspect_ratio(float x) {
    float adjusted = x * gfx_current_dimensions.x_adjust_ratio;

    // Force 2D coordinates to be aligned perfectly on the nearest pixel
    // This prevents MSAA sub-pixel gaps (e.g. on vanilla dialog boxes)
    // Skip DJUI coords (sOnlyTextureChangeOnAddrChange).
    if (!sOnlyTextureChangeOnAddrChange && rsp.P_matrix[3][3] > 0.5f && rdp.viewport.width > 0.0f) {
        float pixelX = rdp.viewport.x + (adjusted + 1.0f) * 0.5f * rdp.viewport.width;
        pixelX = floorf(pixelX + 0.5f);
        adjusted = ((pixelX - rdp.viewport.x) / rdp.viewport.width) * 2.0f - 1.0f;
    }

    return adjusted;
}

static OPTIMIZE_O3 void gfx_local_to_world_space(VEC_OUT Vec3f pos, VEC_OUT Vec3f normal) {
    // strip view matrix off of the model-view matrix
    Mat4 model;
    mtxf_mul(model, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size-1], gInverseCameraMatrix.m);

    // transform position to world
    Vec3f worldPos;
    worldPos[0] = pos[0] * model[0][0] + pos[1] * model[1][0] + pos[2] * model[2][0] + model[3][0];
    worldPos[1] = pos[0] * model[0][1] + pos[1] * model[1][1] + pos[2] * model[2][1] + model[3][1];
    worldPos[2] = pos[0] * model[0][2] + pos[1] * model[1][2] + pos[2] * model[2][2] + model[3][2];

    pos[0] = worldPos[0];
    pos[1] = worldPos[1];
    pos[2] = worldPos[2];

    // transform normal to world
    if (normal) {
        Vec3f worldNormal;
        worldNormal[0] = normal[0] * model[0][0] + normal[1] * model[1][0] + normal[2] * model[2][0];
        worldNormal[1] = normal[0] * model[0][1] + normal[1] * model[1][1] + normal[2] * model[2][1];
        worldNormal[2] = normal[0] * model[0][2] + normal[1] * model[1][2] + normal[2] * model[2][2];

        normal[0] = worldNormal[0];
        normal[1] = worldNormal[1];
        normal[2] = worldNormal[2];
    }
}

static void OPTIMIZE_O3 gfx_sp_vertex(size_t n_vertices, size_t dest_index, const Vtx *vertices, bool worldGeometry) {
    if (!vertices) { return; }

    Vec3f globalLightCached[2] = { { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f } };
    Vec3f vertexColorCached;
    if ((rsp.geometry_mode & G_LIGHTING) && !(rsp.geometry_mode & G_LIGHT_MAP_EXT)) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                globalLightCached[i][j] = gLightingColor[i][j] / 255.0f;
            }
        }
    }

    if (worldGeometry) {
        if (!(rsp.geometry_mode & G_LIGHTING)) {
            for (int i = 0; i < 3; i ++) {
                vertexColorCached[i] = gVertexColor[i] / 255.0f;
            }
        }
    }

#ifdef __SSE__
    __m128 mat0 = _mm_load_ps(rsp.MVP_matrix[0]);
    __m128 mat1 = _mm_load_ps(rsp.MVP_matrix[1]);
    __m128 mat2 = _mm_load_ps(rsp.MVP_matrix[2]);
    __m128 mat3 = _mm_load_ps(rsp.MVP_matrix[3]);
#endif

    for (size_t i = 0; i < n_vertices; i++, dest_index++) {
        const Vtx_t *v = &vertices[i].v;
        const Vtx_tn *vn = &vertices[i].n;
        struct GfxVertex *d = &rsp.loaded_vertices[dest_index];

#ifdef __SSE__
        __m128 ob0 = _mm_set1_ps(v->ob[0]);
        __m128 ob1 = _mm_set1_ps(v->ob[1]);
        __m128 ob2 = _mm_set1_ps(v->ob[2]);

        __m128 pos = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(ob0, mat0), _mm_mul_ps(ob1, mat1)), _mm_mul_ps(ob2, mat2)), mat3);
        float x = pos[0];
        float y = pos[1];
        float z = pos[2];
        float w = pos[3];
#else
        float x = v->ob[0] * rsp.MVP_matrix[0][0] + v->ob[1] * rsp.MVP_matrix[1][0] + v->ob[2] * rsp.MVP_matrix[2][0] + rsp.MVP_matrix[3][0];
        float y = v->ob[0] * rsp.MVP_matrix[0][1] + v->ob[1] * rsp.MVP_matrix[1][1] + v->ob[2] * rsp.MVP_matrix[2][1] + rsp.MVP_matrix[3][1];
        float z = v->ob[0] * rsp.MVP_matrix[0][2] + v->ob[1] * rsp.MVP_matrix[1][2] + v->ob[2] * rsp.MVP_matrix[2][2] + rsp.MVP_matrix[3][2];
        float w = v->ob[0] * rsp.MVP_matrix[0][3] + v->ob[1] * rsp.MVP_matrix[1][3] + v->ob[2] * rsp.MVP_matrix[2][3] + rsp.MVP_matrix[3][3];
#endif

        x = gfx_adjust_x_for_aspect_ratio(x);

        short U = v->tc[0] * rsp.texture_scaling_factor.s >> 16;
        short V = v->tc[1] * rsp.texture_scaling_factor.t >> 16;

        // are we on affect all shaded surfaces mode and on a vertex colorable surface
        bool leAffectAllVertexColored = (le_get_mode() == LE_MODE_AFFECT_ALL_SHADED_AND_COLORED && worldGeometry);

        if (rsp.geometry_mode & G_LIGHTING) {
            if (rsp.lights_changed) {
                bool applyLightingDir = !(rsp.geometry_mode & G_TEXTURE_GEN);
                for (int32_t i = 0; i < rsp.current_num_lights - 1; i++) {
                    calculate_normal_dir(&rsp.current_lights[i], rsp.current_lights_coeffs[i], applyLightingDir);
                }
                static const Light_t lookat_x = {{0, 0, 0}, 0, {0, 0, 0}, 0, {0, 127, 0}, 0};
                static const Light_t lookat_y = {{0, 0, 0}, 0, {0, 0, 0}, 0, {127, 0, 0}, 0};
                calculate_normal_dir(&lookat_x, rsp.current_lookat_coeffs[0], applyLightingDir);
                calculate_normal_dir(&lookat_y, rsp.current_lookat_coeffs[1], applyLightingDir);
                rsp.lights_changed = false;
            }

            bool useShade = rsp.current_num_lights > 1 &&
                rsp.current_lights[rsp.current_num_lights - 2].col[0] == 0 &&
                rsp.current_lights[rsp.current_num_lights - 2].col[1] == 0 &&
                rsp.current_lights[rsp.current_num_lights - 2].col[2] == 0;
            float r = 0;
            float g = 0;
            float b = 0;
            if (gFullbright) {
                int32_t shadeIndex = rsp.current_num_lights > 1 ? rsp.current_num_lights - (useShade ? 1 : 2) : 0;
                r = rsp.current_lights[shadeIndex].col[0];
                g = rsp.current_lights[shadeIndex].col[1];
                b = rsp.current_lights[shadeIndex].col[2];
            } else {
                int32_t lightIndex = rsp.current_num_lights > 0 ? rsp.current_num_lights - 1 : 0;
                r = rsp.current_lights[lightIndex].col[0] * globalLightCached[1][0];
                g = rsp.current_lights[lightIndex].col[1] * globalLightCached[1][1];
                b = rsp.current_lights[lightIndex].col[2] * globalLightCached[1][2];
            }

            signed char nx = vn->n[0];
            signed char ny = vn->n[1];
            signed char nz = vn->n[2];

            if (rsp.geometry_mode & G_PACKED_NORMALS_EXT) {
                unsigned short packedNormal = vn->flag;
                int xo = packedNormal >> 8;
                int yo = packedNormal & 0xFF;

                nx = xo & 0x7F;
                ny = yo & 0x7F;
                nz = (nx + ny) ^ 0x7F;

                if (nz & 0x80) {
                    nx ^= 0x7F;
                    ny ^= 0x7F;
                }

                nx = (xo & 0x80) ? -nx : nx;
                ny = (yo & 0x80) ? -ny : ny;

                SUPPORT_CHECK(absi(nx) + absi(ny) + absi(nz) == 127);
            }

            if (!gFullbright) {
                for (int32_t i = 0; i < rsp.current_num_lights - 1; i++) {
                    float intensity = 0;

                    intensity += nx * rsp.current_lights_coeffs[i][0];
                    intensity += ny * rsp.current_lights_coeffs[i][1];
                    intensity += nz * rsp.current_lights_coeffs[i][2];

                    intensity /= 127.0f;
                    if (intensity > 0.0f) {
                        r += intensity * rsp.current_lights[i].col[0] * globalLightCached[0][0];
                        g += intensity * rsp.current_lights[i].col[1] * globalLightCached[0][1];
                        b += intensity * rsp.current_lights[i].col[2] * globalLightCached[0][2];
                    }
                }
            }

            d->color.r = r > 255.0f ? 255 : (uint8_t)r;
            d->color.g = g > 255.0f ? 255 : (uint8_t)g;
            d->color.b = b > 255.0f ? 255 : (uint8_t)b;

            if (rsp.geometry_mode & G_PACKED_NORMALS_EXT) {
                float vtxR = (v->cn[0] / 255.0f);
                float vtxG = (v->cn[1] / 255.0f);
                float vtxB = (v->cn[2] / 255.0f);
                d->color.r *= vtxR;
                d->color.g *= vtxG;
                d->color.b *= vtxB;
            }

            if (rsp.geometry_mode & (G_FRESNEL_COLOR_EXT | G_FRESNEL_ALPHA_EXT)) {
                Vec3f vpos    = { v->ob[0], v->ob[1], v->ob[2] };
                Vec3f vnormal = { nx / 255.0f, ny / 255.0f, nz / 255.0f };
                // transform vpos and vnormal to world space
                gfx_local_to_world_space(vpos, vnormal);

                Vec3f viewDir = {
                    gInverseCameraMatrix.m[3][0] - vpos[0],
                    gInverseCameraMatrix.m[3][1] - vpos[1],
                    gInverseCameraMatrix.m[3][2] - vpos[2]
                };
                vec3f_normalize(viewDir);
                vec3f_normalize(vnormal);

                int32_t dot = (int32_t) (fabsf(vec3f_dot(vnormal, viewDir)) * 32767.0f);
                int32_t factor = ((rsp.fresnel_scale * dot) >> 15) + rsp.fresnel_offset;
                int32_t fresnel = clamp(factor << 8, 0, 0x7FFF);
                uint8_t result = (uint8_t) (fresnel >> 7);

                if (rsp.geometry_mode & G_FRESNEL_COLOR_EXT) {
                    d->color.r = d->color.g = d->color.b = result;
                }
                if (rsp.geometry_mode & G_FRESNEL_ALPHA_EXT) {
                    d->color.a = result;
                }
            }

            if (rsp.geometry_mode & G_TEXTURE_GEN) {
                float dotx = 0, doty = 0;
                dotx += nx * rsp.current_lookat_coeffs[0][0];
                dotx += ny * rsp.current_lookat_coeffs[0][1];
                dotx += nz * rsp.current_lookat_coeffs[0][2];
                doty += nx * rsp.current_lookat_coeffs[1][0];
                doty += ny * rsp.current_lookat_coeffs[1][1];
                doty += nz * rsp.current_lookat_coeffs[1][2];

                U = (int32_t)((dotx / 127.0f + 1.0f) / 4.0f * rsp.texture_scaling_factor.s);
                V = (int32_t)((doty / 127.0f + 1.0f) / 4.0f * rsp.texture_scaling_factor.t);
            }

            // if lighting engine is enabled and either we want to affect all shaded surfaces or the lighting engine geometry mode is on
            if (le_is_enabled() && worldGeometry && ((le_get_mode() != LE_MODE_AFFECT_ONLY_GEOMETRY_MODE) || (rsp.geometry_mode & G_LIGHTING_ENGINE_EXT))) {
                Color color = { gLEAmbientColor[0], gLEAmbientColor[1], gLEAmbientColor[2] };

                Vec3f vpos    = { v->ob[0], v->ob[1], v->ob[2] };
                Vec3f vnormal = { nx, ny, nz };

                CTX_BEGIN(CTX_LIGHTING);

                // transform vpos and vnormal to world space
                gfx_local_to_world_space(vpos, vnormal);

                le_calculate_lighting_color_with_normal(vpos, vnormal, color, 1.0f);

                CTX_END(CTX_LIGHTING);

                d->color.r *= color[0] / 255.0f;
                d->color.g *= color[1] / 255.0f;
                d->color.b *= color[2] / 255.0f;
            }

            d->nx = nx;
            d->ny = ny;
            d->nz = nz;
        // if lighting engine is enabled and we should affect all vertex colored surfaces or the lighting engine geometry mode is on
        } else if (le_is_enabled() && !(rsp.geometry_mode & G_LIGHT_MAP_EXT) && (leAffectAllVertexColored || (rsp.geometry_mode & G_LIGHTING_ENGINE_EXT))) {
            Color color = { gLEAmbientColor[0], gLEAmbientColor[1], gLEAmbientColor[2] };

            Vec3f vpos = { v->ob[0], v->ob[1], v->ob[2] };

            CTX_BEGIN(CTX_LIGHTING);

            // transform vpos to world space
            gfx_local_to_world_space(vpos, NULL);

            le_calculate_lighting_color(vpos, color, 1.0f);

            CTX_END(CTX_LIGHTING);

            // combine the colors
            if (leAffectAllVertexColored && !(rsp.geometry_mode & G_LIGHTING_ENGINE_EXT)) {
                d->color.r = (v->cn[0] * color[0] / 255.0f) * vertexColorCached[0];
                d->color.g = (v->cn[1] * color[1] / 255.0f) * vertexColorCached[1];
                d->color.b = (v->cn[2] * color[2] / 255.0f) * vertexColorCached[2];
            } else {
                if (worldGeometry) {
                    d->color.r = color[0] * vertexColorCached[0];
                    d->color.g = color[1] * vertexColorCached[1];
                    d->color.b = color[2] * vertexColorCached[2];
                } else {
                    d->color.r = color[0];
                    d->color.g = color[1];
                    d->color.b = color[2];
                }
            }
        } else {
            if (!(rsp.geometry_mode & G_LIGHT_MAP_EXT) && worldGeometry) {
                d->color.r = v->cn[0] * vertexColorCached[0];
                d->color.g = v->cn[1] * vertexColorCached[1];
                d->color.b = v->cn[2] * vertexColorCached[2];
            } else {
                d->color.r = v->cn[0];
                d->color.g = v->cn[1];
                d->color.b = v->cn[2];
            }
        }

        d->u = U;
        d->v = V;

        d->clip_rej = 0;
        if (x < -w) d->clip_rej |= 1;
        if (x > w) d->clip_rej |= 2;
        if (y < -w) d->clip_rej |= 4;
        if (y > w) d->clip_rej |= 8;
        if (z < -w) d->clip_rej |= 16;
        if (z > w) d->clip_rej |= 32;

        d->x = x;
        d->y = y;
        d->z = z;
        d->w = w;

        d->localX = v->ob[0];
        d->localY = v->ob[1];
        d->localZ = v->ob[2];
        d->localW = 1.0;

        if (!(rsp.geometry_mode & G_FRESNEL_ALPHA_EXT)) {
            d->color.a = v->cn[3];
        }

        d->world_geometry = worldGeometry;
    }
}

static void OPTIMIZE_O3 gfx_sp_tri1(uint8_t vtx1_idx, uint8_t vtx2_idx, uint8_t vtx3_idx) {
    struct GfxVertex *v1 = &rsp.loaded_vertices[vtx1_idx];
    struct GfxVertex *v2 = &rsp.loaded_vertices[vtx2_idx];
    struct GfxVertex *v3 = &rsp.loaded_vertices[vtx3_idx];
    struct GfxVertex *v_arr[3] = { v1, v2, v3 };

    if (v1->clip_rej & v2->clip_rej & v3->clip_rej && gCullingEnabled) {
        // The whole triangle lies outside the visible area
        return;
    }

    if ((rsp.geometry_mode & G_CULL_BOTH) != 0 && gCullingEnabled) {
        float dx1 = v1->x / (v1->w) - v2->x / (v2->w);
        float dy1 = v1->y / (v1->w) - v2->y / (v2->w);
        float dx2 = v3->x / (v3->w) - v2->x / (v2->w);
        float dy2 = v3->y / (v3->w) - v2->y / (v2->w);
        float cross = dx1 * dy2 - dy1 * dx2;

        if ((v1->w < 0) ^ (v2->w < 0) ^ (v3->w < 0)) {
            // If one vertex lies behind the eye, negating cross will give the correct result.
            // If all vertices lie behind the eye, the triangle will be rejected anyway.
            cross = -cross;
        }

        // Invert culling: back becomes front and front becomes back
        if (rsp.geometry_mode & G_CULL_INVERT_EXT) {
            cross = -cross;
        }

        switch (rsp.geometry_mode & G_CULL_BOTH) {
            case G_CULL_FRONT:
                if (cross <= 0) { return; }
                break;
            case G_CULL_BACK:
                if (cross >= 0) { return; }
                break;
            case G_CULL_BOTH:
                // Why is this even an option?
                // HACK: Instead of culling both sides and displaying nothing, cull nothing and display everything
                // this is needed because of the mirror room... some custom models will set/clear cull values resulting in cull both
                break;
        }
    }

    bool depth_test = (rsp.geometry_mode & G_ZBUFFER) == G_ZBUFFER;
    if (depth_test != sRenderingState.depth_test) {
        gfx_flush();
        gfx_rapi->set_depth_test(depth_test);
        sRenderingState.depth_test = depth_test;
    }

    bool z_upd = (rdp.other_mode_l & Z_UPD) == Z_UPD;
    if (z_upd != sRenderingState.depth_mask) {
        gfx_flush();
        gfx_rapi->set_depth_mask(z_upd);
        sRenderingState.depth_mask = z_upd;
    }

    bool zmode_decal = (rdp.other_mode_l & ZMODE_DEC) == ZMODE_DEC;
    if (zmode_decal != sRenderingState.decal_mode) {
        gfx_flush();
        gfx_rapi->set_zmode_decal(zmode_decal);
        sRenderingState.decal_mode = zmode_decal;
    }

    bool fog_enabled = (rsp.geometry_mode & G_FOG) == G_FOG;
    if (fog_enabled != sRenderingState.fog_enabled) {
        gfx_flush();
        sRenderingState.fog_enabled = fog_enabled;
    }

    if (sDepthZAdd != sRenderingState.depth_z_add) {
        gfx_flush();
        sRenderingState.depth_z_add = sDepthZAdd;
    }

    if (sDepthZMult != sRenderingState.depth_z_mult) {
        gfx_flush();
        sRenderingState.depth_z_mult = sDepthZMult;
    }

    if (sDepthZSub != sRenderingState.depth_z_sub) {
        gfx_flush();
        sRenderingState.depth_z_sub = sDepthZSub;
    }

    if (rsp.fog_mul != sRenderingState.fog_mul) {
        gfx_flush();
        sRenderingState.fog_mul = rsp.fog_mul;
    }

    if (gFogIntensity != sRenderingState.fog_intensity) {
        gfx_flush();
        sRenderingState.fog_intensity = gFogIntensity;
    }

    if (rsp.fog_offset != sRenderingState.fog_offset) {
        gfx_flush();
        sRenderingState.fog_offset = rsp.fog_offset;
    }

    if (gFogColor[0] != sRenderingState.fog_color_r ||
        gFogColor[1] != sRenderingState.fog_color_g ||
        gFogColor[2] != sRenderingState.fog_color_b ||
        rdp.fog_color.r != sRenderingState.rdp_fog_color_r ||
        rdp.fog_color.g != sRenderingState.rdp_fog_color_g ||
        rdp.fog_color.b != sRenderingState.rdp_fog_color_b) {

        gfx_flush();

        sRenderingState.fog_color_r = gFogColor[0];
        sRenderingState.fog_color_g = gFogColor[1];
        sRenderingState.fog_color_b = gFogColor[2];
        sRenderingState.rdp_fog_color_r = rdp.fog_color.r;
        sRenderingState.rdp_fog_color_g = rdp.fog_color.g;
        sRenderingState.rdp_fog_color_b = rdp.fog_color.b;
    }

    if (rdp.viewport_or_scissor_changed) {
        if (memcmp(&rdp.viewport, &sRenderingState.viewport, sizeof(rdp.viewport)) != 0
            || sRenderingState.x_adjust_4by3 != gfx_current_dimensions.x_adjust_4by3
            || sRenderingState.y_adjust_4by3 != gfx_current_dimensions.y_adjust_4by3) {
            gfx_flush();
            gfx_rapi->set_viewport(rdp.viewport.x + gfx_current_dimensions.x_adjust_4by3, rdp.viewport.y + gfx_current_dimensions.y_adjust_4by3, rdp.viewport.width - gfx_current_dimensions.x_adjust_4by3 * 2, rdp.viewport.height - + gfx_current_dimensions.y_adjust_4by3 * 2);
            sRenderingState.viewport = rdp.viewport;
        }

        if (memcmp(&rdp.scissor, &sRenderingState.scissor, sizeof(rdp.scissor)) != 0
            || sRenderingState.x_adjust_4by3 != gfx_current_dimensions.x_adjust_4by3
            || sRenderingState.y_adjust_4by3 != gfx_current_dimensions.y_adjust_4by3) {
            gfx_flush();
            gfx_rapi->set_scissor(rdp.scissor.x + gfx_current_dimensions.x_adjust_4by3, rdp.scissor.y + gfx_current_dimensions.y_adjust_4by3, rdp.scissor.width, rdp.scissor.height);
            sRenderingState.scissor = rdp.scissor;
        }


        rdp.viewport_or_scissor_changed = false;
        sRenderingState.x_adjust_4by3 = gfx_current_dimensions.x_adjust_4by3;
        sRenderingState.y_adjust_4by3 = gfx_current_dimensions.x_adjust_4by3;
    }

    struct CombineMode *cm = &rdp.combine_mode;

    cm->use_alpha      = (rdp.other_mode_l  & (G_BL_A_MEM << 18))        == 0;
    cm->texture_edge   = (rdp.other_mode_l  & CVG_X_ALPHA)               == CVG_X_ALPHA;
    cm->use_dither     = (rdp.other_mode_l  & G_AC_DITHER)               == G_AC_DITHER;
    cm->use_2cycle     = (rdp.other_mode_h  & (3U << G_MDSFT_CYCLETYPE)) == G_CYC_2CYCLE;
    cm->use_fog        = (rdp.other_mode_l  >> 30)                       == G_BL_CLR_FOG;
    cm->light_map      = (rsp.geometry_mode & G_LIGHT_MAP_EXT)           == G_LIGHT_MAP_EXT;
    cm->tex_persp      = (rdp.other_mode_h  & G_TP_PERSP)                == G_TP_PERSP;
    cm->world_geometry = (v1->world_geometry && v2->world_geometry && v3->world_geometry);
    cm->geometry_mode  = rsp.geometry_mode; // pass in all the bits for shaders to mess with

    if (cm->texture_edge) {
        cm->use_alpha = true;
    }

    // hack: disable 2cycle if it uses a second texture that doesn't exist
    // this is because old rom hacks were ported assuming that 2cycle didn't exist
    // and were ported incorrectly
    if (!rdp.loaded_texture[1].addr && cm->use_2cycle && gfx_cm_uses_second_texture(cm)) {
        cm->use_2cycle = false;
    }

    struct ColorCombiner *comb = gfx_lookup_or_create_color_combiner(cm);
    cm = &comb->cm;

    struct ShaderProgram *prg = comb->prg;
    if (prg != sRenderingState.shader_program) {
        gfx_flush();
        gfx_rapi->unload_shader(sRenderingState.shader_program);
        gfx_rapi->load_shader(prg);
        sRenderingState.shader_program = prg;
        gfx_set_builtin_uniforms();
        smlua_call_event_hooks(HOOK_ON_SET_SHADER_PROGRAM);
    }
    if (cm->use_alpha != sRenderingState.alpha_blend) {
        gfx_flush();
        gfx_rapi->set_use_alpha(cm->use_alpha);
        sRenderingState.alpha_blend = cm->use_alpha;
    }
    uint8_t num_inputs;
    bool used_textures[2];
    gfx_rapi->shader_get_info(prg, &num_inputs, used_textures);

    for (int32_t i = 0; i < 2; i++) {
        if (used_textures[i]) {
            if (rdp.textures_changed[i]) {
                gfx_flush();
                import_texture(i);
                rdp.textures_changed[i] = false;
            }
            bool linear_filter = configFiltering && ((rdp.other_mode_h & (3U << G_MDSFT_TEXTFILT)) != G_TF_POINT);
            struct TextureHashmapNode* tex = sRenderingState.textures[i];
            if (tex) {
                if (linear_filter != tex->linear_filter || rdp.texture_tile[i].cms != tex->cms || rdp.texture_tile[i].cmt != sRenderingState.textures[i]->cmt) {
                    gfx_flush();
                    gfx_rapi->set_sampler_parameters(i, linear_filter, rdp.texture_tile[i].cms, rdp.texture_tile[i].cmt);
                    tex->linear_filter = linear_filter;
                    tex->cms = rdp.texture_tile[i].cms;
                    tex->cmt = rdp.texture_tile[i].cmt;
                }
            }
        }
    }

    for (int32_t i = 0; i < 3; i++) {
        // send position in clip space
        buf_vbo[buf_vbo_len++] = v_arr[i]->x;
        buf_vbo[buf_vbo_len++] = v_arr[i]->y;
        buf_vbo[buf_vbo_len++] = v_arr[i]->z;
        buf_vbo[buf_vbo_len++] = v_arr[i]->w;

        // send position in local space
        buf_vbo[buf_vbo_len++] = v_arr[i]->localX;
        buf_vbo[buf_vbo_len++] = v_arr[i]->localY;
        buf_vbo[buf_vbo_len++] = v_arr[i]->localZ;
        buf_vbo[buf_vbo_len++] = v_arr[i]->localW;

        // send texture data
        for (int32_t j = 0; j < 2; j++) {
            uint32_t tex_width = (rdp.texture_tile[j].lrs - rdp.texture_tile[j].uls + 4) / 4;
            uint32_t tex_height = (rdp.texture_tile[j].lrt - rdp.texture_tile[j].ult + 4) / 4;
            float u = (v_arr[i]->u - rdp.texture_tile[j].uls * 8) / 32.0f;
            float v = (v_arr[i]->v - rdp.texture_tile[j].ult * 8) / 32.0f;

            int shifts = rdp.texture_tile[j].shifts;
            int shiftt = rdp.texture_tile[j].shiftt;
            if (shifts != 0) {
                if (shifts <= 10) {
                    u /= 1 << shifts;
                } else {
                    u *= 1 << (16 - shifts);
                }
            }
            if (shiftt != 0) {
                if (shiftt <= 10) {
                    v /= 1 << shiftt;
                } else {
                    v *= 1 << (16 - shiftt);
                }
            }

            if ((rdp.other_mode_h & (3U << G_MDSFT_TEXTFILT)) != G_TF_POINT) {
                // Linear filter adds 0.5f to the coordinates (why?)
                u += 0.5f;
                v += 0.5f;
            }

            buf_vbo[buf_vbo_len++] = u / tex_width;
            buf_vbo[buf_vbo_len++] = v / tex_height;
        }

        // send lightmap info
        struct RGBA *col = &v_arr[i]->color;
        buf_vbo[buf_vbo_len++] = ( (((uint16_t)col->g) << 8) | ((uint16_t)col->r) ) / 65535.0f;
        buf_vbo[buf_vbo_len++] = 1.0f - (( (((uint16_t)col->a) << 8) | ((uint16_t)col->b) ) / 65535.0f);

        for (int j = 0; j < CC_MAX_INPUTS; j++) {
            struct RGBA *color = NULL;
            struct RGBA tmp = { 0 };

            u8 mapping = (j < num_inputs) ? comb->shader_input_mapping[j] : 255;

            switch (mapping) {
                case CCS_PRIM:   color = &rdp.prim_color; break;
                case CCS_SHADE:  color = &v_arr[i]->color; break;
                case CCS_ENV:    color = &rdp.env_color; break;
                case CCS_PRIMA:
                    memset(&tmp, rdp.prim_color.a, sizeof(tmp));
                    color = &tmp;
                    break;
                case CCS_SHADEA:
                    memset(&tmp, v_arr[i]->color.a, sizeof(tmp));
                    color = &tmp;
                    break;
                case CCS_ENVA:
                    memset(&tmp, rdp.env_color.a, sizeof(tmp));
                    color = &tmp;
                    break;
                case CCS_LOD: {
                    float distance_frac = (v_arr[i]->w - 3000.0f) / 3000.0f;
                    if (distance_frac < 0.0f) { distance_frac = 0.0f; }
                    if (distance_frac > 1.0f) { distance_frac = 1.0f; }
                    tmp.r = tmp.g = tmp.b = tmp.a = distance_frac * 255.0f;
                    color = &tmp;
                    break;
                }
                default:
                    memset(&tmp, 0, sizeof(tmp));
                    color = &tmp;
                    break;
            }

            // send over input colors
            buf_vbo[buf_vbo_len++] = color->r / 255.0f;
            buf_vbo[buf_vbo_len++] = color->g / 255.0f;
            buf_vbo[buf_vbo_len++] = color->b / 255.0f;

            if (cm->use_alpha) {
                if (cm->use_fog && (color == &v_arr[i]->color || cm->light_map)) {
                    buf_vbo[buf_vbo_len++] = 1.0f;
                } else {
                    buf_vbo[buf_vbo_len++] = color->a / 255.0f;
                }
            } else {
                buf_vbo[buf_vbo_len++] = 1.0f;
            }
        }

        // calculate normal
        f32 nx = 0.0f;
        f32 ny = 0.0f;
        f32 nz = 0.0f;

        if (rsp.geometry_mode & G_LIGHTING) {
            struct GfxVertex *v;

            switch (i) {
                case 0: v = v1; break;
                case 1: v = v2; break;
                case 2: v = v3; break;
            }

            nx = v->nx;
            ny = v->ny;
            nz = v->nz;
        } else {
            // it's faster if we let the shader normalize them
            f32 ux = v2->localX - v1->localX;
            f32 uy = v2->localY - v1->localY;
            f32 uz = v2->localZ - v1->localZ;

            f32 vx = v3->localX - v1->localX;
            f32 vy = v3->localY - v1->localY;
            f32 vz = v3->localZ - v1->localZ;

            nx = uy * vz - uz * vy;
            ny = uz * vx - ux * vz;
            nz = ux * vy - uy * vx;
        }

        // send normal
        buf_vbo[buf_vbo_len++] = nx;
        buf_vbo[buf_vbo_len++] = ny;
        buf_vbo[buf_vbo_len++] = nz;

        // send barycentric coords
        buf_vbo[buf_vbo_len++] = i == 0 ? 1.0f : 0.0f;
        buf_vbo[buf_vbo_len++] = i == 1 ? 1.0f : 0.0f;
        buf_vbo[buf_vbo_len++] = i == 2 ? 1.0f : 0.0f;
    }
    if (++buf_vbo_num_tris == MAX_BUFFERED) {
        gfx_flush();
    }
}

static void gfx_sp_geometry_mode(uint32_t clear, uint32_t set) {
    rsp.geometry_mode &= ~clear;
    rsp.geometry_mode |= set;
}

static void gfx_calc_and_set_viewport(const Vp_t *viewport) {
    // 2 bits fraction
    float width = 2.0f * viewport->vscale[0] / 4.0f;
    float height = 2.0f * viewport->vscale[1] / 4.0f;
    float x = (viewport->vtrans[0] / 4.0f) - width / 2.0f;
    float y = SCREEN_HEIGHT - ((viewport->vtrans[1] / 4.0f) + height / 2.0f);

    // get ratios
    u32 viewportWidth, viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(gfx_get_current_frame_pass(), &viewportWidth, &viewportHeight);
    float ratioX = viewportWidth / (2.0f * HALF_SCREEN_WIDTH);
    float ratioY = viewportHeight / (2.0f * HALF_SCREEN_HEIGHT);

    width *= ratioX;
    height *= ratioY;
    x *= ratioX;
    y *= ratioY;

    rdp.viewport.x = x;
    rdp.viewport.y = y;
    rdp.viewport.width = width;
    rdp.viewport.height = height;

    rdp.viewport_or_scissor_changed = true;
}

static void gfx_sp_movemem(uint8_t index, uint16_t offset, const void* data) {
    if (!data) { return; }
    switch (index) {
        case G_MV_VIEWPORT:
            gfx_calc_and_set_viewport((const Vp_t *) data);
            break;
#if 0
        case G_MV_LOOKATY:
        case G_MV_LOOKATX:
            memcpy(rsp.current_lookat + (index - G_MV_LOOKATY) / 2, data, sizeof(Light_t));
            //rsp.lights_changed = 1;
            break;
#endif
#ifdef F3DEX_GBI_2
        case G_MV_LIGHT: {
            int lightidx = offset / 24 - 2;
            if (lightidx >= 0 && lightidx <= MAX_LIGHTS) { // skip lookat
                // NOTE: reads out of bounds if it is an ambient light
                memcpy(rsp.current_lights + lightidx, data, sizeof(Light_t));
            }
            break;
        }
#else
        case G_MV_L0:
        case G_MV_L1:
        case G_MV_L2:
        case G_MV_L3:
        case G_MV_L4:
        case G_MV_L5:
        case G_MV_L6:
            // NOTE: reads out of bounds if it is an ambient light
            memcpy(rsp.current_lights + (index - G_MV_L0) / 2, data, sizeof(Light_t));
            break;
#endif
    }
}

#ifdef F3DEX_GBI_2E
static void gfx_sp_copymem(uint8_t idx, uint16_t dstofs, uint16_t srcofs, UNUSED uint8_t words) {
    if (idx == G_MV_LIGHT) {
        const int srcidx = srcofs / 24 - 2;
        const int dstidx = dstofs / 24 - 2;
        if (srcidx <= MAX_LIGHTS && dstidx <= MAX_LIGHTS) {
            memcpy(rsp.current_lights + dstidx, rsp.current_lights + srcidx, sizeof(Light_t));
        }
    }
}
#endif

static void gfx_sp_moveword(uint8_t index, uint16_t offset, uint32_t data) {
    switch (index) {
        case G_MW_NUMLIGHT:
#ifdef F3DEX_GBI_2
            rsp.current_num_lights = data / 24 + 1; // add ambient light
#else
            // Ambient light is included
            // The 31th bit is a flag that lights should be recalculated
            rsp.current_num_lights = (data - 0x80000000U) / 32;
#endif
            rsp.lights_changed = 1;
            break;
        case G_MW_FOG:
            rsp.fog_mul = (int16_t)(data >> 16);
            rsp.fog_offset = (int16_t)data;

            // Alter depth buffer to deal with new near plane
            sDepthZAdd = (gProjectionMaxNearValue - gProjectionVanillaNearValue) + gProjectionMaxNearValue;
            sDepthZMult = (gProjectionVanillaFarValue - gProjectionMaxNearValue) / (gProjectionVanillaFarValue - gProjectionVanillaNearValue);
            sDepthZSub = gProjectionVanillaNearValue;

            break;
        case G_MW_FX:
            if (offset == G_MWO_FRESNEL) {
                rsp.fresnel_scale = (int16_t)(data >> 16);
                rsp.fresnel_offset = (int16_t)data;
            }
            break;
        case G_MW_LIGHTCOL: {
            int light_num = offset / 24;
            // data = packed color
            if (light_num >= 0 && light_num <= MAX_LIGHTS) {
                rsp.current_lights[light_num].col[0] = (uint8_t)(data >> 24);
                rsp.current_lights[light_num].col[1] = (uint8_t)(data >> 16);
                rsp.current_lights[light_num].col[2] = (uint8_t)(data >> 8);
            }
            break;
        }
    }
}

static void gfx_sp_texture(uint16_t sc, uint16_t tc, UNUSED uint8_t level, UNUSED uint8_t tile, UNUSED uint8_t on) {
    rsp.texture_scaling_factor.s = sc;
    rsp.texture_scaling_factor.t = tc;
}

static void gfx_dp_set_scissor(UNUSED uint32_t mode, uint32_t ulx, uint32_t uly, uint32_t lrx, uint32_t lry) {
    u32 viewportWidth, viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(gfx_get_current_frame_pass(), &viewportWidth, &viewportHeight);

    float passRatioX = (float)viewportWidth / SCREEN_WIDTH;
    float passRatioY = (float)viewportHeight / SCREEN_HEIGHT;

    float x = ulx / 4.0f * passRatioX;
    float y = (SCREEN_HEIGHT - lry / 4.0f) * passRatioY;
    float width = (lrx - ulx) / 4.0f * passRatioX;
    float height = (lry - uly) / 4.0f * passRatioY;

    rdp.scissor.x = x;
    rdp.scissor.y = y;
    rdp.scissor.width = width;
    rdp.scissor.height = height;

    rdp.viewport_or_scissor_changed = true;
}

static void gfx_dp_set_texture_image(UNUSED uint32_t format, uint32_t size, UNUSED uint32_t width, const void* addr) {
    rdp.texture_to_load.addr = addr;
    rdp.texture_to_load.siz = size;
}

static void gfx_dp_set_tile(uint8_t fmt, uint32_t siz, uint32_t line, uint32_t tmem, uint8_t tile, uint32_t palette, uint32_t cmt, uint32_t maskt, uint32_t shiftt, uint32_t cms, uint32_t masks, uint32_t shifts) {
    rdp.texture_tile[tile].fmt = fmt;
    rdp.texture_tile[tile].siz = siz;
    rdp.texture_tile[tile].cms = cms;
    rdp.texture_tile[tile].cmt = cmt;
    rdp.texture_tile[tile].shifts = shifts;
    rdp.texture_tile[tile].shiftt = shiftt;
    rdp.texture_tile[tile].masks = masks;
    rdp.texture_tile[tile].maskt = maskt;
    rdp.texture_tile[tile].line_size_bytes = line * 8;
    rdp.texture_tile[tile].tmem = tmem;
    rdp.texture_tile[tile].palette = palette;
    // For some reason toad player's face breaks without this line, everything else is fine though
    rdp.texture_tile[tile].index = (tile == G_TX_LOADTILE ? tmem/256 : (tile == G_TX_LOADTILE_6_UNKNOWN ? 1 : 0));
    if (!sOnlyTextureChangeOnAddrChange) {
        rdp.textures_changed[0] = true;
        rdp.textures_changed[1] = true;
    }
}

static void gfx_dp_set_tile_size(uint8_t tile, uint16_t uls, uint16_t ult, uint16_t lrs, uint16_t lrt) {
    rdp.texture_tile[tile].uls = uls;
    rdp.texture_tile[tile].ult = ult;
    rdp.texture_tile[tile].lrs = lrs;
    rdp.texture_tile[tile].lrt = lrt;
    if (!sOnlyTextureChangeOnAddrChange) {
        rdp.textures_changed[0] = true;
        rdp.textures_changed[1] = true;
    }
}

static void gfx_dp_load_tlut(uint8_t tile, uint32_t high_index) {
    SUPPORT_CHECK(rdp.texture_to_load.siz == G_IM_SIZ_16b);
    if (rdp.texture_tile[tile].tmem == 256) {
        rdp.palette[0] = rdp.texture_to_load.addr;
        if (high_index == 255) {
            rdp.palette[1] = rdp.texture_to_load.addr + 256;
        }
    } else {
        rdp.palette[1] = rdp.texture_to_load.addr;
    }
}

static void gfx_dp_load_block(uint8_t tile, uint32_t uls, uint32_t ult, uint32_t lrs, UNUSED uint32_t dxt) {
    //if (tile == 1) return;
    SUPPORT_CHECK(uls == 0);
    SUPPORT_CHECK(ult == 0);

    // The lrs field rather seems to be number of pixels to load
    uint32_t word_size_shift = 0;
    switch (rdp.texture_to_load.siz) {
        case G_IM_SIZ_4b:
            word_size_shift = 0; // Or -1? It's unused in SM64 anyway.
            break;
        case G_IM_SIZ_8b:
            word_size_shift = 0;
            break;
        case G_IM_SIZ_16b:
            word_size_shift = 1;
            break;
        case G_IM_SIZ_32b:
            word_size_shift = 2;
            break;
    }
    uint32_t size_bytes = (lrs + 1) << word_size_shift;
    gfx_update_loaded_texture(tile, size_bytes, rdp.texture_to_load.addr);
}

static void gfx_dp_load_tile(uint8_t tile, uint32_t uls, uint32_t ult, uint32_t lrs, uint32_t lrt) {
    SUPPORT_CHECK(uls == 0);
    SUPPORT_CHECK(ult == 0);

    uint32_t word_size_shift = 0;
    switch (rdp.texture_to_load.siz) {
        case G_IM_SIZ_4b:
            word_size_shift = 0; // Or -1? It's unused in SM64 anyway.
            break;
        case G_IM_SIZ_8b:
            word_size_shift = 0;
            break;
        case G_IM_SIZ_16b:
            word_size_shift = 1;
            break;
        case G_IM_SIZ_32b:
            word_size_shift = 2;
            break;
    }

    uint32_t size_bytes = (((lrs >> G_TEXTURE_IMAGE_FRAC) + 1) * ((lrt >> G_TEXTURE_IMAGE_FRAC) + 1)) << word_size_shift;
    gfx_update_loaded_texture(tile, size_bytes, rdp.texture_to_load.addr);
    rdp.texture_tile[tile].uls = uls;
    rdp.texture_tile[tile].ult = ult;
    rdp.texture_tile[tile].lrs = lrs;
    rdp.texture_tile[tile].lrt = lrt;
}

static void gfx_dp_set_combine_mode(uint32_t rgb1, uint32_t alpha1, uint32_t rgb2, uint32_t alpha2) {
    //printf(">>> combine: %08x %08x %08x %08x\n", rgb1, alpha1, rgb2, alpha2);
    memset(&rdp.combine_mode, 0, sizeof(struct CombineMode));

    rdp.combine_mode.rgb1 = rgb1;
    rdp.combine_mode.alpha1 = alpha1;

    rdp.combine_mode.rgb2 = rgb2;
    rdp.combine_mode.alpha2 = alpha2;

    rdp.combine_mode.flags = 0;
}

static void gfx_dp_set_env_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    rdp.env_color.r = r;
    rdp.env_color.g = g;
    rdp.env_color.b = b;
    rdp.env_color.a = a;
}

static void gfx_dp_set_env_rgb(uint8_t r, uint8_t g, uint8_t b) {
    rdp.env_color.r = r;
    rdp.env_color.g = g;
    rdp.env_color.b = b;
}

static void gfx_dp_set_prim_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    rdp.prim_color.r = r;
    rdp.prim_color.g = g;
    rdp.prim_color.b = b;
    rdp.prim_color.a = a;
}

static void gfx_dp_set_fog_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    rdp.fog_color.r = r;
    rdp.fog_color.g = g;
    rdp.fog_color.b = b;
    rdp.fog_color.a = a;
}

static void gfx_dp_set_fill_color(uint32_t packed_color) {
    uint16_t col16 = (uint16_t)packed_color;
    uint32_t r = col16 >> 11;
    uint32_t g = (col16 >> 6) & 0x1f;
    uint32_t b = (col16 >> 1) & 0x1f;
    uint32_t a = col16 & 1;
    rdp.fill_color.r = SCALE_5_8(r);
    rdp.fill_color.g = SCALE_5_8(g);
    rdp.fill_color.b = SCALE_5_8(b);
    rdp.fill_color.a = a * 255;
}

static void gfx_draw_rectangle(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry) {
    uint32_t saved_other_mode_h = rdp.other_mode_h;
    uint32_t cycle_type = (rdp.other_mode_h & (3U << G_MDSFT_CYCLETYPE));

    if (cycle_type == G_CYC_COPY) {
        rdp.other_mode_h = (rdp.other_mode_h & ~(3U << G_MDSFT_TEXTFILT)) | G_TF_POINT;
    }

    // U10.2 coordinates
    float ulxf = ulx;
    float ulyf = uly;
    float lrxf = lrx;
    float lryf = lry;

    ulxf = ulxf / (4.0f * HALF_SCREEN_WIDTH) - 1.0f;
    ulyf = -(ulyf / (4.0f * HALF_SCREEN_HEIGHT)) + 1.0f;
    lrxf = lrxf / (4.0f * HALF_SCREEN_WIDTH) - 1.0f;
    lryf = -(lryf / (4.0f * HALF_SCREEN_HEIGHT)) + 1.0f;

    ulxf = gfx_adjust_x_for_aspect_ratio(ulxf);
    lrxf = gfx_adjust_x_for_aspect_ratio(lrxf);

    struct GfxVertex* ul = &rsp.loaded_vertices[MAX_VERTICES + 0];
    struct GfxVertex* ll = &rsp.loaded_vertices[MAX_VERTICES + 1];
    struct GfxVertex* lr = &rsp.loaded_vertices[MAX_VERTICES + 2];
    struct GfxVertex* ur = &rsp.loaded_vertices[MAX_VERTICES + 3];

    ul->x = ulxf;
    ul->y = ulyf;
    ul->z = 0.0f;
    ul->w = 1.0f;

    ll->x = ulxf;
    ll->y = lryf;
    ll->z = 0.0f;
    ll->w = 1.0f;

    lr->x = lrxf;
    lr->y = lryf;
    lr->z = 0.0f;
    lr->w = 1.0f;

    ur->x = lrxf;
    ur->y = ulyf;
    ur->z = 0.0f;
    ur->w = 1.0f;

    // The coordinates for texture rectangle shall bypass the viewport setting
    Mat4 oldMatrixMVP;
    Mat4 oldMatrixM;
    Mat4 oldMatrixV;
    Mat4 oldMatrixP;
    mtxf_copy(oldMatrixMVP, rsp.MVP_matrix);
    mtxf_copy(oldMatrixM, rsp.M_matrix);
    mtxf_copy(oldMatrixV, rsp.V_matrix);
    mtxf_copy(oldMatrixP, rsp.P_matrix);

    mtxf_identity(rsp.MVP_matrix);
    mtxf_identity(rsp.M_matrix);
    mtxf_identity(rsp.V_matrix);
    mtxf_identity(rsp.P_matrix);

    u32 viewportWidth, viewportHeight;
    gfx_get_frame_pass_viewport_dimensions(gfx_get_current_frame_pass(), &viewportWidth, &viewportHeight);

    struct Box default_viewport = {0, 0, viewportWidth, viewportHeight};
    struct Box viewport_saved = rdp.viewport;
    uint32_t geometry_mode_saved = rsp.geometry_mode;

    rdp.viewport = default_viewport;
    rdp.viewport_or_scissor_changed = true;
    rsp.geometry_mode = 0;

    gfx_sp_tri1(MAX_VERTICES + 0, MAX_VERTICES + 1, MAX_VERTICES + 3);
    gfx_sp_tri1(MAX_VERTICES + 1, MAX_VERTICES + 2, MAX_VERTICES + 3);

    mtxf_copy(rsp.MVP_matrix, oldMatrixMVP);
    mtxf_copy(rsp.M_matrix, oldMatrixM);
    mtxf_copy(rsp.V_matrix, oldMatrixV);
    mtxf_copy(rsp.P_matrix, oldMatrixP);

    rsp.geometry_mode = geometry_mode_saved;
    rdp.viewport = viewport_saved;
    rdp.viewport_or_scissor_changed = true;

    if (cycle_type == G_CYC_COPY) {
        rdp.other_mode_h = saved_other_mode_h;
    }
}

static void gfx_draw_fullscreen_quad() {
    float quadVertices[] = {
        -1.0f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f,   1.0f, 0.0f,

        -1.0f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f,   1.0f, 1.0f
    };

#if defined(WIN32) || defined(OSX_BUILD)
#if defined(WIN32)
    if (gRenderApi == &gfx_direct3d11_api) {
#else
    if (gRenderApi == &gfx_metal_api) {
#endif
        // flip y coordinates
        for (int i = 0; i < 6; i++) {
            quadVertices[i * 6 + 5] = 1.0f - quadVertices[i * 6 + 5];
        }
    }
#endif

    gfx_rapi->create_or_load_post_process_shader();

    gfx_rapi->set_use_alpha(false);
    sRenderingState.alpha_blend = false;
    gfx_rapi->set_depth_test(false);
    sRenderingState.depth_test = false;

    gfx_set_builtin_uniforms();
    smlua_call_event_hooks(HOOK_ON_SET_SHADER_PROGRAM);

    gfx_rapi->draw_triangles(quadVertices, sizeof(quadVertices) / sizeof(float), 2);

    sRenderingState.shader_program = NULL; // reset shader program to sync state with render api
}

static void gfx_dp_texture_rectangle(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry, UNUSED uint8_t tile, int16_t uls, int16_t ult, int16_t dsdx, int16_t dtdy, bool flip) {
    struct CombineMode saved_combine_mode = rdp.combine_mode;
    if ((rdp.other_mode_h & (3U << G_MDSFT_CYCLETYPE)) == G_CYC_COPY) {
        // Per RDP Command Summary Set Tile's shift s and this dsdx should be set to 4 texels
        // Divide by 4 to get 1 instead
        dsdx >>= 2;

        // Color combiner is turned off in copy mode
        gfx_dp_set_combine_mode(
            color_comb_rgb  (G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_CCMUX_TEXEL0, 0),
            color_comb_alpha(G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_ACMUX_TEXEL0, 0),
            color_comb_rgb  (G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_CCMUX_TEXEL0, 1),
            color_comb_alpha(G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_ACMUX_TEXEL0, 1));

        // Per documentation one extra pixel is added in this modes to each edge
        lrx += 1 << 2;
        lry += 1 << 2;
    }

    // uls and ult are S10.5
    // dsdx and dtdy are S5.10
    // lrx, lry, ulx, uly are U10.2
    // lrs, lrt are S10.5
    if (flip) {
        dsdx = -dsdx;
        dtdy = -dtdy;
    }
    int16_t width = !flip ? lrx - ulx : lry - uly;
    int16_t height = !flip ? lry - uly : lrx - ulx;
    float lrs = ((uls << 7) + dsdx * width) >> 7;
    float lrt = ((ult << 7) + dtdy * height) >> 7;

    struct GfxVertex* ul = &rsp.loaded_vertices[MAX_VERTICES + 0];
    struct GfxVertex* ll = &rsp.loaded_vertices[MAX_VERTICES + 1];
    struct GfxVertex* lr = &rsp.loaded_vertices[MAX_VERTICES + 2];
    struct GfxVertex* ur = &rsp.loaded_vertices[MAX_VERTICES + 3];
    ul->u = uls;
    ul->v = ult;
    lr->u = lrs;
    lr->v = lrt;
    if (!flip) {
        ll->u = uls;
        ll->v = lrt;
        ur->u = lrs;
        ur->v = ult;
    } else {
        ll->u = lrs;
        ll->v = ult;
        ur->u = uls;
        ur->v = lrt;
    }

    gfx_draw_rectangle(ulx, uly, lrx, lry);

    u32 cflags = rdp.combine_mode.flags;
    rdp.combine_mode = saved_combine_mode;
    rdp.combine_mode.flags = cflags;
}

static void gfx_dp_fill_rectangle(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry) {
    if (rdp.color_image_address == rdp.z_buf_address) {
        // Don't clear Z buffer here since we already did it with glClear
        return;
    }
    uint32_t mode = (rdp.other_mode_h & (3U << G_MDSFT_CYCLETYPE));

    if (mode == G_CYC_COPY || mode == G_CYC_FILL) {
        // Per documentation one extra pixel is added in this modes to each edge
        lrx += 1 << 2;
        lry += 1 << 2;
    }

    for (int32_t i = MAX_VERTICES; i < MAX_VERTICES + 4; i++) {
        struct GfxVertex* v = &rsp.loaded_vertices[i];
        v->color = rdp.fill_color;
    }

    struct CombineMode saved_combine_mode = rdp.combine_mode;
    gfx_dp_set_combine_mode(
        color_comb_rgb  (G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_CCMUX_SHADE, 0),
        color_comb_alpha(G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_ACMUX_SHADE, 0),
        color_comb_rgb  (G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_CCMUX_SHADE, 1),
        color_comb_alpha(G_CCMUX_0, G_CCMUX_0, G_CCMUX_0, G_ACMUX_SHADE, 1));
    gfx_draw_rectangle(ulx, uly, lrx, lry);

    u32 cflags = rdp.combine_mode.flags;
    rdp.combine_mode = saved_combine_mode;
    rdp.combine_mode.flags = cflags;
}

static void gfx_dp_set_z_image(void *z_buf_address) {
    rdp.z_buf_address = z_buf_address;
}

static void gfx_dp_set_color_image(UNUSED uint32_t format, UNUSED uint32_t size, UNUSED uint32_t width, void* address) {
    rdp.color_image_address = address;
}

static void gfx_sp_set_other_mode(uint32_t shift, uint32_t num_bits, uint64_t mode) {
    uint64_t mask = (((uint64_t)1 << num_bits) - 1) << shift;
    uint64_t om = rdp.other_mode_l | ((uint64_t)rdp.other_mode_h << 32);
    om = (om & ~mask) | mode;
    rdp.other_mode_l = (uint32_t)om;
    rdp.other_mode_h = (uint32_t)(om >> 32);
}

static inline void *seg_addr(uintptr_t w1) {
    return (void *) w1;
}

#define C0(pos, width) ((cmd->words.w0 >> (pos)) & ((1U << width) - 1))
#define C1(pos, width) ((cmd->words.w1 >> (pos)) & ((1U << width) - 1))

static void OPTIMIZE_O3 gfx_run_dl(Gfx* cmd) {
    if (!cmd) { return; }

    for (;;) {
        uint32_t opcode = cmd->words.w0 >> 24;

        switch (opcode) {
            // RSP commands:
            case G_MTX:
#ifdef F3DEX_GBI_2
                gfx_sp_matrix(C0(0, 8) ^ G_MTX_PUSH, (const int32_t *) seg_addr(cmd->words.w1));
#else
                gfx_sp_matrix(C0(16, 8), (const int32_t *) seg_addr(cmd->words.w1));
#endif
                break;
            case (uint8_t)G_POPMTX:
#ifdef F3DEX_GBI_2
                gfx_sp_pop_matrix(cmd->words.w1 / 64);
#else
                gfx_sp_pop_matrix(1);
#endif
                break;
            case G_MOVEMEM:
#ifdef F3DEX_GBI_2
                gfx_sp_movemem(C0(0, 8), C0(8, 8) * 8, seg_addr(cmd->words.w1));
#else
                gfx_sp_movemem(C0(16, 8), 0, seg_addr(cmd->words.w1));
#endif
                break;
            case (uint8_t)G_MOVEWORD:
#ifdef F3DEX_GBI_2
                gfx_sp_moveword(C0(16, 8), C0(0, 16), cmd->words.w1);
#else
                gfx_sp_moveword(C0(0, 8), C0(8, 16), cmd->words.w1);
#endif
                break;
#ifdef F3DEX_GBI_2E
            case (uint8_t)G_COPYMEM:
                gfx_sp_copymem(C0(0, 8), C0(8, 8) * 8, C0(16, 8) * 8, C1(0, 8));
                break;
#endif
            case (uint8_t)G_TEXTURE:
#ifdef F3DEX_GBI_2
                gfx_sp_texture(C1(16, 16), C1(0, 16), C0(11, 3), C0(8, 3), C0(1, 7));
#else
                gfx_sp_texture(C1(16, 16), C1(0, 16), C0(11, 3), C0(8, 3), C0(0, 8));
#endif
                break;
            case G_VTX:
#ifdef F3DEX_GBI_2
                gfx_sp_vertex(C0(12, 8), C0(1, 7) - C0(12, 8), seg_addr(cmd->words.w1), true);
#elif defined(F3DEX_GBI) || defined(F3DLP_GBI)
                gfx_sp_vertex(C0(10, 6), C0(16, 8) / 2, seg_addr(cmd->words.w1), true);
#else
                gfx_sp_vertex((C0(0, 16)) / sizeof(Vtx), C0(16, 4), seg_addr(cmd->words.w1), true);
#endif
                break;
            case G_DL:
                if (C0(16, 1) == 0) {
                    // Push return address
                    gfx_run_dl((Gfx *)seg_addr(cmd->words.w1));
                } else {
                    cmd = (Gfx *)seg_addr(cmd->words.w1);
                    --cmd; // increase after break
                }
                break;
            case (uint8_t)G_ENDDL:
                return;
#ifdef F3DEX_GBI_2
            case G_GEOMETRYMODE:
                gfx_sp_geometry_mode(~C0(0, 24), cmd->words.w1);
                break;
#else
            case (uint8_t)G_SETGEOMETRYMODE:
                gfx_sp_geometry_mode(0, cmd->words.w1);
                break;
            case (uint8_t)G_CLEARGEOMETRYMODE:
                gfx_sp_geometry_mode(cmd->words.w1, 0);
                break;
#endif
            case (uint8_t)G_TRI1:
#ifdef F3DEX_GBI_2
                gfx_sp_tri1(C0(16, 8) / 2, C0(8, 8) / 2, C0(0, 8) / 2);
#elif defined(F3DEX_GBI) || defined(F3DLP_GBI)
                gfx_sp_tri1(C1(16, 8) / 2, C1(8, 8) / 2, C1(0, 8) / 2);
#else
                gfx_sp_tri1(C1(16, 8) / 10, C1(8, 8) / 10, C1(0, 8) / 10);
#endif
                break;
#if defined(F3DEX_GBI) || defined(F3DLP_GBI)
            case (uint8_t)G_TRI2:
                gfx_sp_tri1(C0(16, 8) / 2, C0(8, 8) / 2, C0(0, 8) / 2);
                gfx_sp_tri1(C1(16, 8) / 2, C1(8, 8) / 2, C1(0, 8) / 2);
                break;
#endif
            case (uint8_t)G_SETOTHERMODE_L:
#ifdef F3DEX_GBI_2
                gfx_sp_set_other_mode(31 - C0(8, 8) - C0(0, 8), C0(0, 8) + 1, cmd->words.w1);
#else
                gfx_sp_set_other_mode(C0(8, 8), C0(0, 8), cmd->words.w1);
#endif
                break;
            case (uint8_t)G_SETOTHERMODE_H:
#ifdef F3DEX_GBI_2
                gfx_sp_set_other_mode(63 - C0(8, 8) - C0(0, 8), C0(0, 8) + 1, (uint64_t) cmd->words.w1 << 32);
#else
                gfx_sp_set_other_mode(C0(8, 8) + 32, C0(0, 8), (uint64_t) cmd->words.w1 << 32);
#endif
                break;

            // RDP Commands:
            case G_SETTIMG:
                gfx_dp_set_texture_image(C0(21, 3), C0(19, 2), C0(0, 10), seg_addr(cmd->words.w1));
                break;
            case G_LOADBLOCK:
                gfx_dp_load_block(C1(24, 3), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_LOADTILE:
                gfx_dp_load_tile(C1(24, 3), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_SETTILE:
                gfx_dp_set_tile(C0(21, 3), C0(19, 2), C0(9, 9), C0(0, 9), C1(24, 3), C1(20, 4), C1(18, 2), C1(14, 4), C1(10, 4), C1(8, 2), C1(4, 4), C1(0, 4));
                break;
            case G_SETTILESIZE:
                gfx_dp_set_tile_size(C1(24, 3), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_LOADTLUT:
                gfx_dp_load_tlut(C1(24, 3), C1(14, 10));
                break;
            case G_SETENVCOLOR:
                gfx_dp_set_env_color(C1(24, 8), C1(16, 8), C1(8, 8), C1(0, 8));
                break;
            case G_SETENVRGB:
                gfx_dp_set_env_rgb(C1(24, 8), C1(16, 8), C1(8, 8));
                break;
            case G_SETPRIMCOLOR:
                gfx_dp_set_prim_color(C1(24, 8), C1(16, 8), C1(8, 8), C1(0, 8));
                break;
            case G_SETFOGCOLOR:
                gfx_dp_set_fog_color(C1(24, 8), C1(16, 8), C1(8, 8), C1(0, 8));
                break;
            case G_SETFILLCOLOR:
                gfx_dp_set_fill_color(cmd->words.w1);
                break;
            case G_SETCOMBINE:
                gfx_dp_set_combine_mode(
                    color_comb_rgb  (C0(20, 4), C1(28, 4), C0(15, 5), C1(15, 3), 0),
                    color_comb_alpha(C0(12, 3), C1(12, 3), C0(9, 3),  C1(9, 3),  0),
                    color_comb_rgb  (C0(5, 4),  C1(24, 4), C0(0, 5),  C1(6, 3),  1),
                    color_comb_alpha(C1(21, 3), C1(3, 3),  C1(18, 3), C1(0, 3),  1));
                break;
            // G_SETPRIMCOLOR, G_CCMUX_PRIMITIVE, G_ACMUX_PRIMITIVE, is used by Goddard
            // G_CCMUX_TEXEL1, LOD_FRACTION is used in Bowser room 1
            case G_TEXRECT:
            case G_TEXRECTFLIP:
            {
                int32_t lrx, lry, tile, ulx, uly;
                uint32_t uls, ult, dsdx, dtdy;
                tile = 0;
#ifdef GBI_NO_MULTI_COMMANDS
                lrx = (int32_t) (C0(13, 11) << 21) >> 19;
                lry = (int32_t) (C0(4, 9) << 23) >> 21;
                ulx = (int32_t) (C1(21, 11) << 21) >> 19;
                uly = (int32_t) (C1(12, 9) << 23) >> 21;
                uls = 0;
                ult = 0;
                dsdx = C1(4, 8) << 6;
                dtdy = (C1(0, 4) << 10) | (C0(0, 4) << 6);
#else
#ifdef F3DEX_GBI_2E
                lrx = (int32_t)(C0(0, 24) << 8) >> 8;
                lry = (int32_t)(C1(0, 24) << 8) >> 8;
                ++cmd;
                ulx = (int32_t)(C0(0, 24) << 8) >> 8;
                uly = (int32_t)(C1(0, 24) << 8) >> 8;
                ++cmd;
                uls = C0(16, 16);
                ult = C0(0, 16);
                dsdx = C1(16, 16);
                dtdy = C1(0, 16);
#else
                lrx = C0(12, 12);
                lry = C0(0, 12);
                tile = C1(24, 3);
                ulx = C1(12, 12);
                uly = C1(0, 12);
                ++cmd;
                uls = C1(16, 16);
                ult = C1(0, 16);
                ++cmd;
                dsdx = C1(16, 16);
                dtdy = C1(0, 16);
#endif
#endif
                gfx_dp_texture_rectangle(ulx, uly, lrx, lry, tile, uls, ult, dsdx, dtdy, opcode == G_TEXRECTFLIP);
                break;
            }
            case G_FILLRECT:
#ifdef GBI_NO_MULTI_COMMANDS
            {
                int32_t lrx, lry, ulx, uly;
                uly = (int32_t) (C0(12, 12) << 20) >> 18;
                lry = (int32_t) (C0(0, 12) << 20) >> 18;
                ulx = (int32_t) (C1(16, 16) << 16) >> 14;
                lrx = (int32_t) (C1(0, 16) << 16) >> 14;
                gfx_dp_fill_rectangle(ulx, uly, lrx, lry);
                break;
            }
#else
#ifdef F3DEX_GBI_2E
            {
                int32_t lrx, lry, ulx, uly;
                lrx = (int32_t)(C0(0, 24) << 8) >> 8;
                lry = (int32_t)(C1(0, 24) << 8) >> 8;
                ++cmd;
                ulx = (int32_t)(C0(0, 24) << 8) >> 8;
                uly = (int32_t)(C1(0, 24) << 8) >> 8;
                gfx_dp_fill_rectangle(ulx, uly, lrx, lry);
                break;
            }
#else
                gfx_dp_fill_rectangle(C1(12, 12), C1(0, 12), C0(12, 12), C0(0, 12));
                break;
#endif
#endif
            case G_SETSCISSOR:
                gfx_dp_set_scissor(C1(24, 2), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_SETZIMG:
                gfx_dp_set_z_image(seg_addr(cmd->words.w1));
                break;
            case G_SETCIMG:
                gfx_dp_set_color_image(C0(21, 3), C0(19, 2), C0(0, 11), seg_addr(cmd->words.w1));
                break;
            default:
                ext_gfx_run_dl(cmd);
                break;
        }
        ++cmd;
    }
}

static void gfx_sp_reset(void) {
    rsp.modelview_matrix_stack_size = 1;
    rsp.current_num_lights = 2;
    rsp.lights_changed = true;
    num_gfx_states = 0;
    sRenderingState.x_adjust_4by3 = 0;
    rdp.viewport_or_scissor_changed = true;
}

void gfx_get_dimensions(u32 *width, u32 *height) {
    gfx_wm_get_dimensions(width, height);
}

void gfx_get_adjusted_dimensions(u32 *width, u32 *height) {
    gfx_wm_get_dimensions(width, height);
    if (configForce4By3) {
        if (((4.0f / 3.0f) * *height) < *width) {
            *width = (4.0f / 3.0f) * *height;
        } else {
            *height = (3.0f / 4.0f) * *width;
        }
    }
    // Avoid division by zero in callers
    if (*width  == 0) { *width  = 1; }
    if (*height == 0) { *height = 1; }
}

void gfx_init(struct GfxRenderingAPI *rapi, const char *window_title) {
    gfx_wm_init(window_title);
    gfx_rapi = rapi;
    gfx_rapi->init();

    gfx_init_shaders();
    gfx_cc_precomp();

    gGfxInited = true;
}

struct GfxRenderingAPI *gfx_get_current_rendering_api(void) {
    return gfx_rapi;
}

bool gfx_shader_stage_is(enum ShaderStage stage) {
    return (gSelectedShaderStage == stage || gSelectedShaderStage == SHADER_STAGE_ANY);
}

void gfx_start_frame(void) {
    sFrameCount += 1;
    if (gGfxPcResetTex1 > 0) {
        gGfxPcResetTex1--;
        rdp.loaded_texture[1].addr = NULL;
        rdp.loaded_texture[1].size_bytes = 0;
    }
    gfx_wm_handle_events();
    gfx_wm_get_dimensions(&gfx_current_dimensions.width, &gfx_current_dimensions.height);
    if (gfx_current_dimensions.width == 0) {
        // Avoid division by zero
        gfx_current_dimensions.width = 1;
    }
    if (gfx_current_dimensions.height == 0) {
        // Avoid division by zero
        gfx_current_dimensions.height = 1;
    }

    if (configForce4By3) {
        if (((4.0f / 3.0f) * gfx_current_dimensions.height) < gfx_current_dimensions.width) {
            uint32_t width4by3 = (4.0f / 3.0f) * gfx_current_dimensions.height;
            if (width4by3 == 0) { width4by3 = 1; }
            gfx_current_dimensions.x_adjust_4by3 = (gfx_current_dimensions.width - width4by3) / 2;
            gfx_current_dimensions.y_adjust_4by3 = 0;
            gfx_current_dimensions.width = width4by3;
        } else {
            uint32_t height4by3 = (3.0f / 4.0f) * gfx_current_dimensions.width;
            if (height4by3 == 0) { height4by3 = 1; }
            gfx_current_dimensions.x_adjust_4by3 = 0;
            gfx_current_dimensions.y_adjust_4by3 = (gfx_current_dimensions.height - height4by3) / 2;
            gfx_current_dimensions.height = height4by3;
        }
    } else {
        gfx_current_dimensions.x_adjust_4by3 = 0;
        gfx_current_dimensions.y_adjust_4by3 = 0;
    }
    gfx_current_dimensions.aspect_ratio = ((float)gfx_current_dimensions.width / (float)gfx_current_dimensions.height);
    gfx_current_dimensions.x_adjust_ratio = (4.0f / 3.0f) / gfx_current_dimensions.aspect_ratio;
}

void gfx_get_frame_pass_viewport_dimensions(struct FramePass *framePass, u32 *width, u32 *height) {
    if (width) {
        *width = framePass->width;
        if (*width == 0) {
            gfx_get_dimensions(width, NULL);
        }
    }

    if (height) {
        *height = framePass->height;
        if (*height == 0) {
            gfx_get_dimensions(NULL, height);
        }
    }
}

struct FramePass *gfx_get_current_frame_pass(void) {
    if (gCurrentFramePassIndex < 0) {
        return &gDefaultGeoFramePass;
    } else {
        return &gFramePasses[gCurrentFramePassIndex];
    }
}

static void gfx_process_lua_passes(Gfx *commands, bool *isLuaPassesActive) {
    for (int i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
        struct FramePass *framePass = &gFramePasses[i];
        if (!framePass->active) { continue; }
        *isLuaPassesActive = true;

        // remove default frame pass if we have lua frame pass
        if (gDefaultGeoFramePass.active) {
            gfx_rapi->delete_framebuffer(&gDefaultGeoFramePass);
            memset(&gDefaultGeoFramePass, 0, sizeof(struct FramePass));
        }

        gCurrentFramePassIndex = i;

        // setup framebuffer
        if (framePass->fbo == 0 || framePass->width != framePass->lastWidth || framePass->height != framePass->lastHeight) {
            if (framePass->fbo != 0) {
                gfx_rapi->delete_framebuffer(framePass);
            }
            gfx_rapi->create_framebuffer(framePass);
            framePass->lastWidth = framePass->width;
            framePass->lastHeight = framePass->height;
        }
        gfx_rapi->set_framebuffer(framePass);

        gfx_rapi->start_frame(); // resets color and depth

        gfx_sp_reset(); // resets the rsp

        // bind pass textures if they exist
        if (i > 0) {
            int textureSlotOffset = 10;
            uintptr_t lastValidPassTexture = 0;

            for (int j = 0; j < i; j++) {
                if (gFramePasses[j].active && gFramePasses[j].passTexture != 0) {
                    gfx_rapi->bind_texture_raw(textureSlotOffset + j, gFramePasses[j].passTexture);
                    lastValidPassTexture = gFramePasses[j].passTexture;
                }
            }

            // make the last valid pass texture always bind to slot 10
            if (lastValidPassTexture != 0) {
                gfx_rapi->bind_texture_raw(textureSlotOffset, lastValidPassTexture);
            }
        }

        if (framePass->drawWorldGeometry) {
            // reset color combiner programs
            for (int j = 0; j < CC_MAX_SHADERS; j++) {
                color_combiner_pool[j].prg = NULL;
            }

            // render world
            smlua_call_event_hooks(HOOK_BEFORE_DRAW_GEOMETRY);
            gfx_run_dl(commands);
            gfx_end_frame_render();
            smlua_call_event_hooks(HOOK_ON_DRAW_GEOMETRY);
        } else {
            // render quad
            gfx_draw_fullscreen_quad();
            gfx_end_frame_render();
        }
    }
}

// a helper function when porting over new render apis to not deal with framebuffers
// in one go
/*void gfx_run_basic(Gfx *commands) {
    gfx_sp_reset();

    if (!gfx_wm_start_frame()) {
        sDroppedFrame = true;
        return;
    }
    sDroppedFrame = false;

    gfx_rapi->reset_framebuffer();
    gfx_rapi->start_frame();
    gfx_run_dl(commands);
}*/

void gfx_run(Gfx *commands) {
    if (!gfx_wm_start_frame()) {
        sDroppedFrame = true;
        return;
    }
    sDroppedFrame = false;

    bool isLuaPassesActive = false;
    gfx_process_lua_passes(commands, &isLuaPassesActive);

    gCurrentFramePassIndex = -1;

    // run default draw world frame pass first if lua frame passes don't exist
    if (!isLuaPassesActive) {
        // activate and configure default frame pass
        if (!gDefaultGeoFramePass.active) {
            memset(&gDefaultGeoFramePass, 0, sizeof(struct FramePass));
            gDefaultGeoFramePass.active = true;
            gDefaultGeoFramePass.drawWorldGeometry = true;
            gDefaultGeoFramePass.clearColor[3] = 255;
        }

        // create/update fbo
        if (gDefaultGeoFramePass.fbo == 0 || gDefaultGeoFramePass.width != gfx_current_dimensions.width || gDefaultGeoFramePass.height != gfx_current_dimensions.height) {
            gfx_rapi->delete_framebuffer(&gDefaultGeoFramePass);
            gfx_get_dimensions(&gDefaultGeoFramePass.width, &gDefaultGeoFramePass.height);
            gfx_rapi->create_framebuffer(&gDefaultGeoFramePass);
        }

        gfx_rapi->set_framebuffer(&gDefaultGeoFramePass);

        gfx_sp_reset(); // resets the rsp

        gfx_rapi->start_frame(); // resets color and depth

        // draw world into frame buffer
        smlua_call_event_hooks(HOOK_BEFORE_DRAW_GEOMETRY);
        gfx_run_dl(commands);
        gfx_end_frame_render();
        smlua_call_event_hooks(HOOK_ON_DRAW_GEOMETRY);
    }

    gfx_sp_reset(); // resets the rsp

    gfx_rapi->reset_framebuffer();
    gfx_rapi->start_frame(); // resets color and depth

    int textureSlotOffset = 10;

    if (gDefaultGeoFramePass.active) {
        if (gDefaultGeoFramePass.passTexture != 0) {
            gfx_rapi->bind_texture_raw(textureSlotOffset, gDefaultGeoFramePass.passTexture);
        }
    } else {
        for (int i = 0; i < MAX_CUSTOM_FRAME_PASSES; i++) {
            if (gFramePasses[i].active && gFramePasses[i].passTexture != 0) {
                gfx_rapi->bind_texture_raw(textureSlotOffset + i, gFramePasses[i].passTexture);
            }
        }

        uintptr_t lastValidPassTexture = 0;
        for (int i = MAX_CUSTOM_FRAME_PASSES - 1; i >= 0; i--) {
            if (gFramePasses[i].active && gFramePasses[i].passTexture != 0) {
                lastValidPassTexture = gFramePasses[i].passTexture;
                break;
            }
        }

        if (lastValidPassTexture != 0) {
            gfx_rapi->bind_texture_raw(textureSlotOffset, lastValidPassTexture);
        }
    }

    gfx_draw_fullscreen_quad();
}

void gfx_end_frame_render(void) {
    gfx_flush();
    gfx_rapi->end_frame();
}

void gfx_display_frame(void) {
    gfx_wm_swap_buffers_begin();
    if (!sDroppedFrame) {
        gfx_rapi->finish_render();
        gfx_wm_swap_buffers_end();
    }
}

void gfx_end_frame(void) {
    gfx_end_frame_render();
    gfx_display_frame();
}

void gfx_shutdown(void) {
    if (gfx_rapi) {
        if (gfx_rapi->shutdown) gfx_rapi->shutdown();
        gfx_rapi = NULL;
    }
    gfx_wm_shutdown();
    gGfxInited = false;
}

void gfx_update_fog_uniforms(void) {
    gSelectedShaderStage = SHADER_STAGE_ANY;
    gSelectedVertexUniformBuffer = 0;
    gSelectedFragmentUniformBuffer = 0;
    float fog_mul = (float)sRenderingState.fog_mul;
    gfx_rapi->set_uniform(NULL, "uFogMul", SHADER_UNIFORM_TYPE_FLOAT, &fog_mul, 1);

    gfx_rapi->set_uniform(NULL, "uFogIntensity", SHADER_UNIFORM_TYPE_FLOAT, &sRenderingState.fog_intensity, 1);

    float fog_offset = (float)sRenderingState.fog_offset;
    gfx_rapi->set_uniform(NULL, "uFogOffset", SHADER_UNIFORM_TYPE_FLOAT, &fog_offset, 1);

    float fogColor[3] = {
        (sRenderingState.rdp_fog_color_r / 255.0f) * (sRenderingState.fog_color_r / 255.0f),
        (sRenderingState.rdp_fog_color_g / 255.0f) * (sRenderingState.fog_color_g / 255.0f),
        (sRenderingState.rdp_fog_color_b / 255.0f) * (sRenderingState.fog_color_b / 255.0f),
    };
    gfx_rapi->set_uniform(NULL, "uFogColor", SHADER_UNIFORM_TYPE_VEC3, &fogColor, 1);

    gfx_rapi->set_uniform(NULL, "uDepthZSub", SHADER_UNIFORM_TYPE_FLOAT, &sRenderingState.depth_z_sub, 1);
    gfx_rapi->set_uniform(NULL, "uDepthZMult", SHADER_UNIFORM_TYPE_FLOAT, &sRenderingState.depth_z_mult, 1);
    gfx_rapi->set_uniform(NULL, "uDepthZAdd", SHADER_UNIFORM_TYPE_FLOAT, &sRenderingState.depth_z_add, 1);

    gfx_rapi->set_uniform(NULL, "uFogEnabled", SHADER_UNIFORM_TYPE_BOOL, &sRenderingState.fog_enabled, 1);
}

void gfx_update_matrices(void) {
    gSelectedShaderStage = SHADER_STAGE_ANY;
    gSelectedVertexUniformBuffer = 0;
    gSelectedFragmentUniformBuffer = 0;
    gfx_rapi->set_uniform(NULL, "uModelViewProjectionMatrix", SHADER_UNIFORM_TYPE_MAT4, rsp.MVP_matrix, 1);
    if (rsp.modelview_matrix_stack_size > 0) {
        gfx_rapi->set_uniform(NULL, "uModelViewMatrix", SHADER_UNIFORM_TYPE_MAT4, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], 1);
    }
    gfx_rapi->set_uniform(NULL, "uModelMatrix", SHADER_UNIFORM_TYPE_MAT4, rsp.M_matrix, 1);
    gfx_rapi->set_uniform(NULL, "uViewMatrix", SHADER_UNIFORM_TYPE_MAT4, rsp.V_matrix, 1);
    gfx_rapi->set_uniform(NULL, "uProjectionMatrix", SHADER_UNIFORM_TYPE_MAT4, rsp.P_matrix, 1);
}

void gfx_set_builtin_uniforms(void) {
    gSelectedShaderStage = SHADER_STAGE_ANY;
    gSelectedVertexUniformBuffer = 0;
    gSelectedFragmentUniformBuffer = 0;

    gfx_rapi->set_uniform(NULL, "uFrameCount", SHADER_UNIFORM_TYPE_INT, &sFrameCount, 1);

    float lightmapColor[3] = {
        gVertexColor[0] / 255.0f,
        gVertexColor[1] / 255.0f,
        gVertexColor[2] / 255.0f
    };
    gfx_rapi->set_uniform(NULL, "uLightmapColor", SHADER_UNIFORM_TYPE_VEC3, lightmapColor, 1);

    gfx_rapi->set_uniform(NULL, "uFilter", SHADER_UNIFORM_TYPE_INT, &configFiltering, 1);

    float aspectRatio = (float)gfx_current_dimensions.aspect_ratio;
    float xAdjustRatio = (float)gfx_current_dimensions.x_adjust_ratio;
    gfx_rapi->set_uniform(NULL, "uAspectRatio", SHADER_UNIFORM_TYPE_FLOAT, &aspectRatio, 1);
    gfx_rapi->set_uniform(NULL, "uXAdjustRatio", SHADER_UNIFORM_TYPE_FLOAT, &xAdjustRatio, 1);

    float screenWidth = (float)gfx_current_dimensions.width;
    float screenHeight = (float)gfx_current_dimensions.height;
    gfx_rapi->set_uniform(NULL, "uScreenWidth", SHADER_UNIFORM_TYPE_FLOAT, &screenWidth, 1);
    gfx_rapi->set_uniform(NULL, "uScreenHeight", SHADER_UNIFORM_TYPE_FLOAT, &screenHeight, 1);

    int shaderFlagEnabled = gShaderFlagsEnabled ? 1 : 0;
    gfx_rapi->set_uniform(NULL, "uShaderFlagsEnabled", SHADER_UNIFORM_TYPE_BOOL, &shaderFlagEnabled, 1);
    gfx_rapi->set_uniform(NULL, "uShaderFlags", SHADER_UNIFORM_TYPE_INT, gShaderFlags, SHADER_FLAG_MAX);
    gfx_rapi->set_uniform(NULL, "uShaderFlagValues", SHADER_UNIFORM_TYPE_FLOAT, gShaderFlagValues, SHADER_FLAG_MAX);
    gfx_update_matrices();
    gfx_update_fog_uniforms();
}

void gfx_remove_all_color_combiners(void) {
    for (int i = 0; i < CC_MAX_SHADERS; i++) {
        memset(&color_combiner_pool[i], 0, sizeof(color_combiner_pool[i]));
    }

    color_combiner_pool_index = 0;
    color_combiner_pool_size = 0;
    sPrevCombinerForLookup = NULL;
}

  /////////////////////////
 // v custom for djui v //
/////////////////////////

static const struct {
    uint8_t LOAD_BLOCK;
    uint8_t SHIFT;
    uint8_t INCR;
    uint8_t LINE_NIBBLES;
} G_IM_SIZ_[] = {
    [G_IM_SIZ_4b]  = { G_IM_SIZ_4b_LOAD_BLOCK,  G_IM_SIZ_4b_SHIFT,  G_IM_SIZ_4b_INCR,  1                           },
    [G_IM_SIZ_8b]  = { G_IM_SIZ_8b_LOAD_BLOCK,  G_IM_SIZ_8b_SHIFT,  G_IM_SIZ_8b_INCR,  2 * G_IM_SIZ_8b_LINE_BYTES  },
    [G_IM_SIZ_16b] = { G_IM_SIZ_16b_LOAD_BLOCK, G_IM_SIZ_16b_SHIFT, G_IM_SIZ_16b_INCR, 2 * G_IM_SIZ_16b_LINE_BYTES },
    [G_IM_SIZ_32b] = { G_IM_SIZ_32b_LOAD_BLOCK, G_IM_SIZ_32b_SHIFT, G_IM_SIZ_32b_INCR, 2 * G_IM_SIZ_32b_LINE_BYTES },
};

static bool    sDjuiClip   = 0;
static uint8_t sDjuiClipX1 = 0;
static uint8_t sDjuiClipY1 = 0;
static uint8_t sDjuiClipX2 = 0;
static uint8_t sDjuiClipY2 = 0;

static bool sDjuiOverride = false;
static struct TextureInfo sDjuiOverrideTexture;

static void OPTIMIZE_O3 djui_gfx_dp_execute_clipping(void) {
    if (!sDjuiClip) { return; }
    sDjuiClip = false;

    size_t start_index = 0;
    size_t dest_index = 4;

    float minX = rsp.loaded_vertices[start_index].x;
    float maxX = rsp.loaded_vertices[start_index].x;
    float minY = rsp.loaded_vertices[start_index].y;
    float maxY = rsp.loaded_vertices[start_index].y;

    float minU = rsp.loaded_vertices[start_index].u;
    float maxU = rsp.loaded_vertices[start_index].u;
    float minV = rsp.loaded_vertices[start_index].v;
    float maxV = rsp.loaded_vertices[start_index].v;

    for (size_t i = start_index; i < dest_index; i++) {
        struct GfxVertex* d = &rsp.loaded_vertices[i];
        minX = fmin(minX, d->x);
        maxX = fmax(maxX, d->x);
        minY = fmin(minY, d->y);
        maxY = fmax(maxY, d->y);

        minU = fmin(minU, d->u);
        maxU = fmax(maxU, d->u);
        minV = fmin(minV, d->v);
        maxV = fmax(maxV, d->v);
    }

    float midY = (minY + maxY) / 2.0f;
    float midX = (minX + maxX) / 2.0f;
    float midU = (minU + maxU) / 2.0f;
    float midV = (minV + maxV) / 2.0f;
    for (size_t i = start_index; i < dest_index; i++) {
        struct GfxVertex* d = &rsp.loaded_vertices[i];
        if (d->x <= midX) {
            d->x += (maxX - minX) * (sDjuiClipX1 / 255.0f);
        } else {
            d->x -= (maxX - minX) * (sDjuiClipX2 / 255.0f);
        }
        if (d->y <= midY) {
            d->y += (maxY - minY) * (sDjuiClipY2 / 255.0f);
        } else {
            d->y -= (maxY - minY) * (sDjuiClipY1 / 255.0f);
        }

        if (d->u <= midU) {
            d->u += (maxU - minU) * (sDjuiClipX1 / 255.0f);
        } else {
            d->u -= (maxU - minU) * (sDjuiClipX2 / 255.0f);
        }
        if (d->v <= midV) {
            d->v += (maxV - minV) * (sDjuiClipY1 / 255.0f);
        } else {
            d->v -= (maxV - minV) * (sDjuiClipY2 / 255.0f);
        }
    }
}

static void OPTIMIZE_O3 djui_gfx_dp_execute_override(void) {
    if (!sDjuiOverride) { return; }
    sDjuiOverride = false;

    const Texture *texture = sDjuiOverrideTexture.texture;
    uint32_t width = sDjuiOverrideTexture.width;
    uint32_t height = sDjuiOverrideTexture.height;
    uint8_t fmt = sDjuiOverrideTexture.format;
    uint8_t siz = sDjuiOverrideTexture.size;

    if (siz > G_IM_SIZ_32b) { return; }

    // This is gDPLoadTextureBlock, but with some shortcuts and without texture size limitations
    gfx_dp_set_texture_image(fmt, G_IM_SIZ_[siz].LOAD_BLOCK, width, texture);
    gfx_dp_set_tile(fmt, siz, 0, 0, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);
    gfx_dp_load_block(0, 0, 0, ((width * height + G_IM_SIZ_[siz].INCR) >> G_IM_SIZ_[siz].SHIFT) - 1, 0);
    gfx_dp_set_tile(fmt, siz, (((width * G_IM_SIZ_[siz].LINE_NIBBLES) + 15) >> 4), 0, G_TX_RENDERTILE, 0, rdp.texture_tile[0].cmt, 0, 0, rdp.texture_tile[0].cms, 0, 0);
}

static void OPTIMIZE_O3 djui_gfx_dp_execute_djui(uint32_t opcode) {
    switch (opcode) {
        case G_TEXOVERRIDE_DJUI: djui_gfx_dp_execute_override(); break;
        case G_TEXCLIP_DJUI:     djui_gfx_dp_execute_clipping(); break;
    }
}

static void gfx_sp_copy_playerpart_to_color(uint8_t color, uint32_t idx) {
    SUPPORT_CHECK(color == G_COL_PRIM || color == G_COL_ENV);

    if (idx >= 1 && idx <= MAX_LIGHTS) {
        Light_t *l = (rsp.current_lights + (idx - 1));
        struct RGBA *target_color = NULL;
        switch (color) {
            case G_COL_PRIM: target_color = &rdp.prim_color; break;
            case G_COL_ENV:  target_color = &rdp.env_color;  break;
        }

        target_color->r = l->col[0];
        target_color->g = l->col[1];
        target_color->b = l->col[2];
    }
}

static void OPTIMIZE_O3 djui_gfx_dp_set_clipping(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    sDjuiClipX1 = x1;
    sDjuiClipY1 = y1;
    sDjuiClipX2 = x2;
    sDjuiClipY2 = y2;
    sDjuiClip   = true;
}

static void OPTIMIZE_O3 djui_gfx_dp_set_override(void* texture, uint32_t w, uint32_t h, uint8_t fmt, uint8_t siz) {
    sDjuiOverrideTexture.texture = texture;
    sDjuiOverrideTexture.width = w;
    sDjuiOverrideTexture.height = h;
    sDjuiOverrideTexture.format = fmt;
    sDjuiOverrideTexture.size = siz;
    sDjuiOverride = (texture != NULL);
}

/*static void OPTIMIZE_O3 djui_gfx_sp_simple_vertex(size_t n_vertices, size_t dest_index, const Vtx *vertices) {
    gfx_sp_vertex(n_vertices, dest_index, vertices, false);
    return;
}*/

static void OPTIMIZE_O3 djui_gfx_sp_simple_tri1(uint8_t vtx1_idx, uint8_t vtx2_idx, uint8_t vtx3_idx) {
    gfx_sp_tri1(vtx1_idx, vtx2_idx, vtx3_idx);
    return;
}

static void gfx_sp_load_or_save_state(uint8_t cmd, uint32_t state) {

    // Load state
    if (cmd == G_STATE_LOAD) {
        if (num_gfx_states == 0) {
            return;
        }

        num_gfx_states--;
        struct GfxState *gfx_state = &gfx_states[num_gfx_states];

        if (state & G_STATE_GEOMETRY_MODE) {
            rsp.geometry_mode = gfx_state->rsp.geometry_mode;
        }
        if (state & G_STATE_COMBINE_MODE) {
            gfx_dp_set_combine_mode(
                gfx_state->rdp.combine_mode.rgb1,
                gfx_state->rdp.combine_mode.alpha1,
                gfx_state->rdp.combine_mode.rgb2,
                gfx_state->rdp.combine_mode.alpha2
            );
        }
        if (state & G_STATE_OTHER_MODE_L) {
            rdp.other_mode_l = gfx_state->rdp.other_mode_l;
        }
        if (state & G_STATE_OTHER_MODE_H) {
            rdp.other_mode_h = gfx_state->rdp.other_mode_h;
        }
        if (state & G_STATE_ENV_COLOR) {
            rdp.env_color = gfx_state->rdp.env_color;
        }
        if (state & G_STATE_PRIM_COLOR) {
            rdp.prim_color = gfx_state->rdp.prim_color;
        }
        if (state & G_STATE_FOG_COLOR) {
            rdp.fog_color = gfx_state->rdp.fog_color;
            rsp.fog_mul = gfx_state->rsp.fog_mul;
            rsp.fog_offset = gfx_state->rsp.fog_offset;
        }
        if (state & G_STATE_FILL_COLOR) {
            rdp.fill_color = gfx_state->rdp.fill_color;
        }
        if (state & G_STATE_FRESNEL) {
            rsp.fresnel_scale = gfx_state->rsp.fresnel_scale;
            rsp.fresnel_offset = gfx_state->rsp.fresnel_offset;
        }
        if (state & G_STATE_TEXTURES) {
            rsp.texture_scaling_factor = gfx_state->rsp.texture_scaling_factor;
            rdp.texture_to_load = gfx_state->rdp.texture_to_load;
            memcpy(rdp.palette, gfx_state->rdp.palette, sizeof(rdp.palette));
            memcpy(rdp.texture_tile, gfx_state->rdp.texture_tile, sizeof(rdp.texture_tile));
            memcpy(rdp.loaded_texture, gfx_state->rdp.loaded_texture, sizeof(rdp.loaded_texture));
            for (s32 i = 0; i != ARRAY_COUNT(rdp.textures_changed); ++i) {
                rdp.textures_changed[i] = true;
            }
        }
        if (state & G_STATE_LIGHTS) {
            rsp.current_num_lights = gfx_state->rsp.current_num_lights;
            memcpy(rsp.current_lights, gfx_state->rsp.current_lights, sizeof(rsp.current_lights));
            rsp.lights_changed = true;
        }
        if (state & G_STATE_VIEWPORT) {
            rdp.viewport = gfx_state->rdp.viewport;
            rdp.viewport_or_scissor_changed = true;
        }
        if (state & G_STATE_SCISSOR) {
            rdp.scissor = gfx_state->rdp.scissor;
            rdp.viewport_or_scissor_changed = true;
        }
        if (state & G_STATE_Z_BUFFER) {
            rdp.z_buf_address = gfx_state->rdp.z_buf_address;
        }
        if (state & G_STATE_COLOR_IMAGE) {
            rdp.color_image_address = gfx_state->rdp.color_image_address;
        }
        return;
    }

    // Save state
    if (cmd == G_STATE_SAVE) {
        if (num_gfx_states == MAX_GFX_STATES) {
            return;
        }

        struct GfxState *gfx_state = &gfx_states[num_gfx_states];
        num_gfx_states++;

        if (state & G_STATE_GEOMETRY_MODE) {
            gfx_state->rsp.geometry_mode = rsp.geometry_mode;
        }
        if (state & G_STATE_COMBINE_MODE) {
            gfx_state->rdp.combine_mode = rdp.combine_mode;
        }
        if (state & G_STATE_OTHER_MODE_L) {
            gfx_state->rdp.other_mode_l = rdp.other_mode_l;
        }
        if (state & G_STATE_OTHER_MODE_H) {
            gfx_state->rdp.other_mode_h = rdp.other_mode_h;
        }
        if (state & G_STATE_ENV_COLOR) {
            gfx_state->rdp.env_color = rdp.env_color;
        }
        if (state & G_STATE_PRIM_COLOR) {
            gfx_state->rdp.prim_color = rdp.prim_color;
        }
        if (state & G_STATE_FOG_COLOR) {
            gfx_state->rdp.fog_color = rdp.fog_color;
            gfx_state->rsp.fog_mul = rsp.fog_mul;
            gfx_state->rsp.fog_offset = rsp.fog_offset;
        }
        if (state & G_STATE_FILL_COLOR) {
            gfx_state->rdp.fill_color = rdp.fill_color;
        }
        if (state & G_STATE_FRESNEL) {
            gfx_state->rsp.fresnel_scale = rsp.fresnel_scale;
            gfx_state->rsp.fresnel_offset = rsp.fresnel_offset;
        }
        if (state & G_STATE_TEXTURES) {
            gfx_state->rsp.texture_scaling_factor = rsp.texture_scaling_factor;
            gfx_state->rdp.texture_to_load = rdp.texture_to_load;
            memcpy(gfx_state->rdp.palette, rdp.palette, sizeof(rdp.palette));
            memcpy(gfx_state->rdp.texture_tile, rdp.texture_tile, sizeof(rdp.texture_tile));
            memcpy(gfx_state->rdp.loaded_texture, rdp.loaded_texture, sizeof(rdp.loaded_texture));
        }
        if (state & G_STATE_LIGHTS) {
            gfx_state->rsp.current_num_lights = rsp.current_num_lights;
            memcpy(gfx_state->rsp.current_lights, rsp.current_lights, sizeof(rsp.current_lights));
        }
        if (state & G_STATE_VIEWPORT) {
            gfx_state->rdp.viewport = rdp.viewport;
        }
        if (state & G_STATE_SCISSOR) {
            gfx_state->rdp.scissor = rdp.scissor;
        }
        if (state & G_STATE_Z_BUFFER) {
            gfx_state->rdp.z_buf_address = rdp.z_buf_address;
        }
        if (state & G_STATE_COLOR_IMAGE) {
            gfx_state->rdp.color_image_address = rdp.color_image_address;
        }
        return;
    }
}

void gfx_pc_precomp_shader(uint32_t rgb1, uint32_t alpha1, uint32_t rgb2, uint32_t alpha2, uint32_t flags) {
    gfx_dp_set_combine_mode(rgb1, alpha1, rgb2, alpha2);

    struct CombineMode* cm = &rdp.combine_mode;
    cm->flags = flags;

    gfx_lookup_or_create_color_combiner(cm);
}

void OPTIMIZE_O3 ext_gfx_run_dl(Gfx* cmd) {
    uint32_t opcode = cmd->words.w0 >> 24;
    switch (opcode) {
        case G_TEXCLIP_DJUI:
            djui_gfx_dp_set_clipping(C0(16, 8), C0(8, 8), C1(16, 8), C1(8, 8));
            break;
        case G_TEXOVERRIDE_DJUI:
            djui_gfx_dp_set_override(seg_addr(cmd->words.w1), 1 << C0(16, 8), 1 << C0(8, 8), C0(4, 4), C0(0, 4));
            break;
        case G_VTX_EXT:
#ifdef F3DEX_GBI_2
            gfx_sp_vertex(C0(12, 8), C0(1, 7) - C0(12, 8), seg_addr(cmd->words.w1), false);
#elif defined(F3DEX_GBI) || defined(F3DLP_GBI)
            gfx_sp_vertex(C0(10, 6), C0(16, 8) / 2, seg_addr(cmd->words.w1), false);
#else
            gfx_sp_vertex((C0(0, 16)) / sizeof(Vtx), C0(16, 4), seg_addr(cmd->words.w1), false);
#endif
            break;
        case G_TRI2_EXT:
            djui_gfx_sp_simple_tri1(C0(16, 8) / 2, C0(8, 8) / 2, C0(0, 8) / 2);
            djui_gfx_sp_simple_tri1(C1(16, 8) / 2, C1(8, 8) / 2, C1(0, 8) / 2);
            break;
        case G_TEXADDR_DJUI:
            sOnlyTextureChangeOnAddrChange = !(C0(0, 24) & 0x01);
            break;
        case G_EXECUTE_DJUI:
            djui_gfx_dp_execute_djui(cmd->words.w1);
            break;
        case G_PPARTTOCOLOR:
            gfx_sp_copy_playerpart_to_color(C0(16, 8), cmd->words.w1);
            break;
        case G_STATE_EXT:
            gfx_sp_load_or_save_state(C0(16, 8), cmd->words.w1);
            break;
    }
}
