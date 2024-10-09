#include "pc/rom_assets.h"
// Sparkles Animation

// 0x04032A48
ROM_ASSET_LOAD_VTX(sparkles_animation_seg4_vertex_04032A48, 0x00114750, 78432, 0x00032a48, 64);

// 0x04032A88
ROM_ASSET_LOAD_TEXTURE(sparkles_animation_seg4_texture_04032A88, "actors/sparkle_animation/sparkle_animation_0.ia16.inc.c", 0x00114750, 78432, 0x00032a88, 2048);

// 0x04033288
ROM_ASSET_LOAD_TEXTURE(sparkles_animation_seg4_texture_04033288, "actors/sparkle_animation/sparkle_animation_1.ia16.inc.c", 0x00114750, 78432, 0x00033288, 2048);

// 0x04033A88
ROM_ASSET_LOAD_TEXTURE(sparkles_animation_seg4_texture_04033A88, "actors/sparkle_animation/sparkle_animation_2.ia16.inc.c", 0x00114750, 78432, 0x00033a88, 2048);

// 0x04034288
ROM_ASSET_LOAD_TEXTURE(sparkles_animation_seg4_texture_04034288, "actors/sparkle_animation/sparkle_animation_3.ia16.inc.c", 0x00114750, 78432, 0x00034288, 2048);

// 0x04034A88
ROM_ASSET_LOAD_TEXTURE(sparkles_animation_seg4_texture_04034A88, "actors/sparkle_animation/sparkle_animation_4.ia16.inc.c", 0x00114750, 78432, 0x00034a88, 2048);

// 0x04035288 - 0x04035300
const Gfx sparkles_animation_seg4_dl_04035288[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertexNonGlobal(sparkles_animation_seg4_vertex_04032A48, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x04035300 - 0x04035318
const Gfx sparkles_animation_seg4_dl_04035300[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04032A88),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288),
};

// 0x04035318 - 0x04035330
const Gfx sparkles_animation_seg4_dl_04035318[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04033288),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288),
};

// 0x04035330 - 0x04035348
const Gfx sparkles_animation_seg4_dl_04035330[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04033A88),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288),
};

// 0x04035348 - 0x04035360
const Gfx sparkles_animation_seg4_dl_04035348[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04034288),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288),
};

// 0x04035360 - 0x04035378
const Gfx sparkles_animation_seg4_dl_04035360[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_04034A88),
    gsSPBranchList(sparkles_animation_seg4_dl_04035288),
};
