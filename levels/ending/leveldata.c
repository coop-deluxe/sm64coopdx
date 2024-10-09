#include "pc/rom_assets.h"
#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "macros.h"
#include "types.h"

#include "make_const_nonconst.h"

#ifdef VERSION_EU
#include "levels/ending/cake_eu.inc.c"

// 0x07023000 - 0x07023FFF
ALIGNED8 const Texture cake_end_texture_eu_35[] = {
#include "levels/ending/eu_023000.rgba16.inc.c"
};

// 0x07024000 - 0x07024FFF
ALIGNED8 const Texture cake_end_texture_eu_36[] = {
#include "levels/ending/eu_024000.rgba16.inc.c"
};

// 0x07025000 - 0x07025FFF
ALIGNED8 const Texture cake_end_texture_eu_37[] = {
#include "levels/ending/eu_025000.rgba16.inc.c"
};

// 0x07026000 - 0x07026FFF
ALIGNED8 const Texture cake_end_texture_eu_38[] = {
#include "levels/ending/eu_026000.rgba16.inc.c"
};

// 0x07027000 - 0x07027FFF
ALIGNED8 const Texture cake_end_texture_eu_39[] = {
#include "levels/ending/eu_027000.rgba16.inc.c"
};

// 0x07028000 - 0x07028FFF
ALIGNED8 const Texture cake_end_texture_eu_40[] = {
#include "levels/ending/eu_028000.rgba16.inc.c"
};

// 0x07029000 - 0x070296D8
const Gfx dl_cake_end_screen[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(0 << 2, 8 << 2, (0 + 63) << 2, (8 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(64 << 2, 8 << 2, (64 + 63) << 2, (8 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 8 << 2, (128 + 63) << 2, (8 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_3),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(192 << 2, 8 << 2, (192 + 63) << 2, (8 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_4),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(256 << 2, 8 << 2, (256 + 63) << 2, (8 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_5),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(0 << 2, 40 << 2, (0 + 63) << 2, (40 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_6),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(64 << 2, 40 << 2, (64 + 63) << 2, (40 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_7),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 40 << 2, (128 + 63) << 2, (40 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(192 << 2, 40 << 2, (192 + 63) << 2, (40 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_9),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(256 << 2, 40 << 2, (256 + 63) << 2, (40 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(0 << 2, 72 << 2, (0 + 63) << 2, (72 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_11),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(64 << 2, 72 << 2, (64 + 63) << 2, (72 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_12),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 72 << 2, (128 + 63) << 2, (72 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_13),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(192 << 2, 72 << 2, (192 + 63) << 2, (72 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_14),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(256 << 2, 72 << 2, (256 + 63) << 2, (72 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_15),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(0 << 2, 104 << 2, (0 + 63) << 2, (104 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_16),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(64 << 2, 104 << 2, (64 + 63) << 2, (104 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_17),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 104 << 2, (128 + 63) << 2, (104 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_18),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(192 << 2, 104 << 2, (192 + 63) << 2, (104 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_19),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(256 << 2, 104 << 2, (256 + 63) << 2, (104 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_20),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(0 << 2, 136 << 2, (0 + 63) << 2, (136 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_21),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(64 << 2, 136 << 2, (64 + 63) << 2, (136 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_22),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 136 << 2, (128 + 63) << 2, (136 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_23),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(192 << 2, 136 << 2, (192 + 63) << 2, (136 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_24),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(256 << 2, 136 << 2, (256 + 63) << 2, (136 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_25),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(0 << 2, 168 << 2, (0 + 63) << 2, (168 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_26),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(64 << 2, 168 << 2, (64 + 63) << 2, (168 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_27),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 168 << 2, (128 + 63) << 2, (168 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(192 << 2, 168 << 2, (192 + 63) << 2, (168 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_29),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(256 << 2, 168 << 2, (256 + 63) << 2, (168 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(0 << 2, 200 << 2, (0 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_31),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(64 << 2, 200 << 2, (64 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_32),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 200 << 2, (128 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_33),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(192 << 2, 200 << 2, (192 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_34),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(256 << 2, 200 << 2, (256 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsSPEndDisplayList(),
};

// 0x070296D8 - 0x070296F8
static const Gfx dl_cake_end_eu_070296D8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};

// 0x070296F8 - 0x07029768
const Gfx dl_cake_end_screen_eu_070296F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_38),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 200 << 2, (128 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_35),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 125 << 2, (128 + 63) << 2, (125 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsSPDisplayList(dl_cake_end_eu_070296D8),
    gsSPEndDisplayList(),
};

// 0x07029768 - 0x070297D8
const Gfx dl_cake_end_screen_eu_07029768[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_39),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 200 << 2, (128 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_36),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 125 << 2, (128 + 63) << 2, (125 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsSPDisplayList(dl_cake_end_eu_070296D8),
    gsSPEndDisplayList(),
};

// 0x070297D8 - 0x07029848
const Gfx dl_cake_end_screen_eu_070297D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_40),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 200 << 2, (128 + 63) << 2, (200 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cake_end_texture_eu_37),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPTextureRectangle(128 << 2, 125 << 2, (128 + 63) << 2, (125 + 31) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10),
    gsSPDisplayList(dl_cake_end_eu_070296D8),
    gsSPEndDisplayList(),
};

// VERSION_EU
#else
ROM_ASSET_LOAD_TEXTURE(cake_end_texture_0, "cake_end_texture_0", 0x0049e710, 56736, 0x00000000, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_1, "cake_end_texture_1", 0x0049e710, 56736, 0x00000c80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_2, "cake_end_texture_2", 0x0049e710, 56736, 0x00000c80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_3, "cake_end_texture_3", 0x0049e710, 56736, 0x00002580, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_4, "cake_end_texture_4", 0x0049e710, 56736, 0x00003200, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_5, "cake_end_texture_5", 0x0049e710, 56736, 0x00003e80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_6, "cake_end_texture_6", 0x0049e710, 56736, 0x00004b00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_7, "cake_end_texture_7", 0x0049e710, 56736, 0x00005780, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_8, "cake_end_texture_8", 0x0049e710, 56736, 0x00006400, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_9, "cake_end_texture_9", 0x0049e710, 56736, 0x00007080, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_10, "cake_end_texture_10", 0x0049e710, 56736, 0x00007d00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_11, "cake_end_texture_11", 0x0049e710, 56736, 0x00008980, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_12, "cake_end_texture_12", 0x0049e710, 56736, 0x00009600, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_13, "cake_end_texture_13", 0x0049e710, 56736, 0x0000a280, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_14, "cake_end_texture_14", 0x0049e710, 56736, 0x0000af00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_15, "cake_end_texture_15", 0x0049e710, 56736, 0x0000bb80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_16, "cake_end_texture_16", 0x0049e710, 56736, 0x0000c800, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_17, "cake_end_texture_17", 0x0049e710, 56736, 0x0000d480, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_18, "cake_end_texture_18", 0x0049e710, 56736, 0x0000e100, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_19, "cake_end_texture_19", 0x0049e710, 56736, 0x0000ed80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_20, "cake_end_texture_20", 0x0049e710, 56736, 0x0000fa00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_21, "cake_end_texture_21", 0x0049e710, 56736, 0x00010680, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_22, "cake_end_texture_22", 0x0049e710, 56736, 0x00011300, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_23, "cake_end_texture_23", 0x0049e710, 56736, 0x00011f80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_24, "cake_end_texture_24", 0x0049e710, 56736, 0x00012c00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_25, "cake_end_texture_25", 0x0049e710, 56736, 0x00013880, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_26, "cake_end_texture_26", 0x0049e710, 56736, 0x00014500, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_27, "cake_end_texture_27", 0x0049e710, 56736, 0x00015180, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_28, "cake_end_texture_28", 0x0049e710, 56736, 0x00015e00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_29, "cake_end_texture_29", 0x0049e710, 56736, 0x00016a80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_30, "cake_end_texture_30", 0x0049e710, 56736, 0x00017700, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_31, "cake_end_texture_31", 0x0049e710, 56736, 0x00018380, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_32, "cake_end_texture_32", 0x0049e710, 56736, 0x00019000, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_33, "cake_end_texture_33", 0x0049e710, 56736, 0x00019c80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_34, "cake_end_texture_34", 0x0049e710, 56736, 0x0001a900, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_35, "cake_end_texture_35", 0x0049e710, 56736, 0x0001b580, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_36, "cake_end_texture_36", 0x0049e710, 56736, 0x0001c200, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_37, "cake_end_texture_37", 0x0049e710, 56736, 0x0001ce80, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_38, "cake_end_texture_38", 0x0049e710, 56736, 0x0001db00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_39, "cake_end_texture_39", 0x0049e710, 56736, 0x0001e780, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_40, "cake_end_texture_40", 0x0049e710, 56736, 0x0001f400, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_41, "cake_end_texture_41", 0x0049e710, 56736, 0x00020080, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_42, "cake_end_texture_42", 0x0049e710, 56736, 0x00020d00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_43, "cake_end_texture_43", 0x0049e710, 56736, 0x00021980, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_44, "cake_end_texture_44", 0x002d0040, 25776, 0x00017a40, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_45, "cake_end_texture_45", 0x0049e710, 56736, 0x00023280, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_46, "cake_end_texture_46", 0x0049e710, 56736, 0x00023f00, 3200);

ROM_ASSET_LOAD_TEXTURE(cake_end_texture_47, "cake_end_texture_47", 0x002d0040, 25776, 0x00017a40, 3200);

// 0x07025800 - 0x07025840
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025800, 0x0049e710, 56736, 0x00025800, 64);

// 0x07025840 - 0x07025880
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025840, 0x0049e710, 56736, 0x00025840, 64);

// 0x07025880 - 0x070258C0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025880, 0x0049e710, 56736, 0x00025880, 64);

// 0x070258C0 - 0x07025900
ROM_ASSET_LOAD_VTX(cake_end_vertex_070258C0, 0x0049e710, 56736, 0x000258c0, 64);

// 0x07025900 - 0x07025940
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025900, 0x0049e710, 56736, 0x00025900, 64);

// 0x07025940 - 0x07025980
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025940, 0x0049e710, 56736, 0x00025940, 64);

// 0x07025980 - 0x070259C0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025980, 0x0049e710, 56736, 0x00025980, 64);

// 0x070259C0 - 0x07025A00
ROM_ASSET_LOAD_VTX(cake_end_vertex_070259C0, 0x0049e710, 56736, 0x000259c0, 64);

// 0x07025A00 - 0x07025A40
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025A00, 0x0049e710, 56736, 0x00025a00, 64);

// 0x07025A40 - 0x07025A80
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025A40, 0x0049e710, 56736, 0x00025a40, 64);

// 0x07025A80 - 0x07025AC0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025A80, 0x0049e710, 56736, 0x00025a80, 64);

// 0x07025AC0 - 0x07025B00
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025AC0, 0x0049e710, 56736, 0x00025ac0, 64);

// 0x07025B00 - 0x07025B40
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025B00, 0x0049e710, 56736, 0x00025b00, 64);

// 0x07025B40 - 0x07025B80
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025B40, 0x0049e710, 56736, 0x00025b40, 64);

// 0x07025B80 - 0x07025BC0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025B80, 0x0049e710, 56736, 0x00025b80, 64);

// 0x07025BC0 - 0x07025C00
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025BC0, 0x0049e710, 56736, 0x00025bc0, 64);

// 0x07025C00 - 0x07025C40
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025C00, 0x0049e710, 56736, 0x00025c00, 64);

// 0x07025C40 - 0x07025C80
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025C40, 0x0049e710, 56736, 0x00025c40, 64);

// 0x07025C80 - 0x07025CC0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025C80, 0x0049e710, 56736, 0x00025c80, 64);

// 0x07025CC0 - 0x07025D00
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025CC0, 0x0049e710, 56736, 0x00025cc0, 64);

// 0x07025D00 - 0x07025D40
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025D00, 0x0049e710, 56736, 0x00025d00, 64);

// 0x07025D40 - 0x07025D80
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025D40, 0x0049e710, 56736, 0x00025d40, 64);

// 0x07025D80 - 0x07025DC0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025D80, 0x0049e710, 56736, 0x00025d80, 64);

// 0x07025DC0 - 0x07025E00
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025DC0, 0x0049e710, 56736, 0x00025dc0, 64);

// 0x07025E00 - 0x07025E40
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025E00, 0x0049e710, 56736, 0x00025e00, 64);

// 0x07025E40 - 0x07025E80
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025E40, 0x0049e710, 56736, 0x00025e40, 64);

// 0x07025E80 - 0x07025EC0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025E80, 0x0049e710, 56736, 0x00025e80, 64);

// 0x07025EC0 - 0x07025F00
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025EC0, 0x0049e710, 56736, 0x00025ec0, 64);

// 0x07025F00 - 0x07025F40
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025F00, 0x0049e710, 56736, 0x00025f00, 64);

// 0x07025F40 - 0x07025F80
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025F40, 0x0049e710, 56736, 0x00025f40, 64);

// 0x07025F80 - 0x07025FC0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025F80, 0x0049e710, 56736, 0x00025f80, 64);

// 0x07025FC0 - 0x07026000
ROM_ASSET_LOAD_VTX(cake_end_vertex_07025FC0, 0x0049e710, 56736, 0x00025fc0, 64);

// 0x07026000 - 0x07026040
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026000, 0x002708c0, 12510, 0x00000000, 64);

// 0x07026040 - 0x07026080
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026040, 0x0049e710, 56736, 0x00026040, 64);

// 0x07026080 - 0x070260C0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026080, 0x0049e710, 56736, 0x00026080, 64);

// 0x070260C0 - 0x07026100
ROM_ASSET_LOAD_VTX(cake_end_vertex_070260C0, 0x0049e710, 56736, 0x000260c0, 64);

// 0x07026100 - 0x07026140
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026100, 0x002708c0, 12510, 0x00000040, 64);

// 0x07026140 - 0x07026180
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026140, 0x0049e710, 56736, 0x00026140, 64);

// 0x07026180 - 0x070261C0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026180, 0x0049e710, 56736, 0x00026180, 64);

// 0x070261C0 - 0x07026200
ROM_ASSET_LOAD_VTX(cake_end_vertex_070261C0, 0x0049e710, 56736, 0x000261c0, 64);

// 0x07026200 - 0x07026240
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026200, 0x002708c0, 12510, 0x00000080, 64);

// 0x07026240 - 0x07026280
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026240, 0x0049e710, 56736, 0x00026240, 64);

// 0x07026280 - 0x070262C0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026280, 0x0049e710, 56736, 0x00026280, 64);

// 0x070262C0 - 0x07026300
ROM_ASSET_LOAD_VTX(cake_end_vertex_070262C0, 0x0049e710, 56736, 0x000262c0, 64);

// 0x07026300 - 0x07026340
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026300, 0x002708c0, 12510, 0x000000c0, 64);

// 0x07026340 - 0x07026380
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026340, 0x0049e710, 56736, 0x00026340, 64);

// 0x07026380 - 0x070263C0
ROM_ASSET_LOAD_VTX(cake_end_vertex_07026380, 0x0049e710, 56736, 0x00026380, 64);

// 0x070263C0 - 0x07026400
ROM_ASSET_LOAD_VTX(cake_end_vertex_070263C0, 0x0049e710, 56736, 0x000263c0, 64);

// 0x07026400 - 0x07027350
const Gfx dl_cake_end_screen[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),

    gsDPLoadTextureBlock(cake_end_texture_0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025800, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025840, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025880, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_070258C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025900, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_5, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025940, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_6, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025980, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_7, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_070259C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025A00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_9, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025A40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_10, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025A80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_11, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025AC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_12, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025B00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_13, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025B40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_14, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025B80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_15, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025BC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_16, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025C00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_17, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025C40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_18, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025C80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_19, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025CC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_20, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025D00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_21, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025D40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_22, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025D80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_23, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025DC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_24, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025E00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_25, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025E40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_26, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025E80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_27, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025EC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_28, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025F00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_29, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025F40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_30, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025F80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_31, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07025FC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_32, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026000, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_33, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026040, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_34, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026080, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_35, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_070260C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_36, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026100, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_37, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026140, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_38, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026180, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_39, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_070261C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_40, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026200, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_41, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026240, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_42, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026280, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_43, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_070262C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_44, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026300, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_45, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026340, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_46, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_07026380, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPLoadTextureBlock(cake_end_texture_47, G_IM_FMT_RGBA, G_IM_SIZ_16b, 80, 20, 0, G_TX_CLAMP, G_TX_CLAMP, 7, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(cake_end_vertex_070263C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),

    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};
#endif
