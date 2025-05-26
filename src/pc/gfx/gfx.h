#ifndef GFX_H
#define GFX_H

#include <math.h>
#include <assert.h>

#define SUPPORT_CHECK(x) assert(x)

// SCALE_M_N: upscale/downscale M-bit integer to N-bit
#define SCALE_5_8(VAL_) (((VAL_) * 0xFF) / 0x1F)
#define SCALE_8_5(VAL_) ((((VAL_) + 4) * 0x1F) / 0xFF)
#define SCALE_4_8(VAL_) ((VAL_) * 0x11)
#define SCALE_8_4(VAL_) ((VAL_) / 0x11)
#define SCALE_3_8(VAL_) ((VAL_) * 0x24)
#define SCALE_8_3(VAL_) ((VAL_) / 0x24)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define HALF_SCREEN_WIDTH (SCREEN_WIDTH / 2)
#define HALF_SCREEN_HEIGHT (SCREEN_HEIGHT / 2)

#define MAX_BUFFERED 256
#define MAX_MATRIX_STACK_SIZE 11
#define MAX_LIGHTS 18
#define MAX_VERTICES 64
#define MAX_CACHED_TEXTURES 4096 // for preloading purposes

#define HASH_SHIFT 0
#define HASHMAP_LEN (MAX_CACHED_TEXTURES * 2)
#define HASH_MASK (HASHMAP_LEN - 1)

struct RGBA {
    uint8_t r, g, b, a;
};

struct Box {
    uint16_t x, y, width, height;
};

struct GfxVertex {
    float x, y, z, w;
    float u, v;
    struct RGBA color;
    uint8_t fog_z;
    uint8_t clip_rej;
};

struct GfxDimensions {
    uint32_t width, height;
    float aspect_ratio;
    float x_adjust_ratio;
    uint32_t x_adjust_4by3;
};

struct GfxTexture {
    const uint8_t *addr;
    uint32_t size_bytes;
};

struct UnloadedTex {
    const uint8_t *addr;
    uint8_t siz;
    uint8_t tile_number;
};

struct TextureTile {
    uint8_t fmt;
    uint8_t siz;
    uint8_t cms, cmt;
    uint16_t uls, ult, lrs, lrt; // U10.2
    uint32_t line_size_bytes;
};

struct TextureHashmapNode {
    struct TextureHashmapNode *next;
    const void *texture_addr;
    uint32_t texture_id;
    uint8_t fmt, siz;
    uint8_t cms, cmt;
    bool linear_filter;
};

struct TextureCache {
    struct TextureHashmapNode *hashmap[HASHMAP_LEN];
    struct TextureHashmapNode pool[MAX_CACHED_TEXTURES];
    uint32_t pool_pos;
};

extern struct GfxDimensions gfx_current_dimensions;
#define RATIO_X (gfx_current_dimensions.width / (2.0f * HALF_SCREEN_WIDTH))
#define RATIO_Y (gfx_current_dimensions.height / (2.0f * HALF_SCREEN_HEIGHT))

#endif // GFX_H