#include "pc/rom_assets.h"
// Power Meter HUD

UNUSED static const u64 power_meter_unused_1 = 0;

// 0x030233E0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_left_side, "actors/power_meter/power_meter_left_side.rgba16.inc.c", 0x00201410, 96653, 0x000233e0, 4096);

// 0x030243E0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_right_side, "actors/power_meter/power_meter_right_side.rgba16.inc.c", 0x00201410, 96653, 0x000243e0, 4096);

// 0x030253E0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_full, "actors/power_meter/power_meter_full.rgba16.inc.c", 0x00201410, 96653, 0x000253e0, 2048);

// 0x03025BE0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_seven_segments, "actors/power_meter/power_meter_seven_segments.rgba16.inc.c", 0x00201410, 96653, 0x00025be0, 2048);

// 0x030263E0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_six_segments, "actors/power_meter/power_meter_six_segments.rgba16.inc.c", 0x00201410, 96653, 0x000263e0, 2048);

// 0x03026BE0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_five_segments, "actors/power_meter/power_meter_five_segments.rgba16.inc.c", 0x00201410, 96653, 0x00026be0, 2048);

// 0x030273E0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_four_segments, "actors/power_meter/power_meter_four_segments.rgba16.inc.c", 0x00201410, 96653, 0x000273e0, 2048);

// 0x03027BE0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_three_segments, "actors/power_meter/power_meter_three_segments.rgba16.inc.c", 0x00201410, 96653, 0x00027be0, 2048);

// 0x030283E0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_two_segments, "actors/power_meter/power_meter_two_segments.rgba16.inc.c", 0x00201410, 96653, 0x000283e0, 2048);

// 0x03028BE0
ROM_ASSET_LOAD_TEXTURE(texture_power_meter_one_segments, "actors/power_meter/power_meter_one_segment.rgba16.inc.c", 0x00201410, 96653, 0x00028be0, 2048);

// 0x030293E0
const Texture *const power_meter_health_segments_lut[] = {
    texture_power_meter_one_segments,
    texture_power_meter_two_segments,
    texture_power_meter_three_segments,
    texture_power_meter_four_segments,
    texture_power_meter_five_segments,
    texture_power_meter_six_segments,
    texture_power_meter_seven_segments,
    texture_power_meter_full,
};

// 0x03029400
ROM_ASSET_LOAD_VTX(vertex_power_meter_base, 0x00201410, 96653, 0x00029400, 128);

// 0x03029480 - 0x03029530
const Gfx dl_power_meter_base[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_TEX_EDGE, G_RM_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(vertex_power_meter_base, 8, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_power_meter_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_power_meter_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x03029530
ROM_ASSET_LOAD_VTX(vertex_power_meter_health_segments, 0x00201410, 96653, 0x00029530, 64);

// 0x03029570 - 0x030295A0
const Gfx dl_power_meter_health_segments_begin[] = {
    gsDPPipeSync(),
    gsSPVertex(vertex_power_meter_health_segments, 4, 0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x030295A0 - 0x030295D8
const Gfx dl_power_meter_health_segments_end[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};
