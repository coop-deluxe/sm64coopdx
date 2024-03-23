#include "pc/rom_assets.h"
// Possible Removed Actor File
// It's possible that bubba and bub used to be 2 "actors" in
// one actor file.

// Bin ID? What is this?
UNUSED static const u64 bubba_unused_1 = 0;

// Bubba

// 0x05000008
ROM_ASSET_LOAD_TEXTURE(bubba_seg5_texture_05000008, "actors/bubba/bubba_sunglasses.rgba16.inc.c", 0x00180bb0, 29674, 0x00000008, 1024);

// unused eye texture, assumed leftover from when actor file was copied from bub
// 0x05000408
ROM_ASSET_LOAD_TEXTURE(bubba_seg5_texture_05000408, "actors/bubba/bubba_eyes_unused.rgba16.inc.c", 0x00180bb0, 29674, 0x00000408, 4096);

// 0x05001408
ROM_ASSET_LOAD_TEXTURE(bubba_seg5_texture_05001408, "actors/bubba/bubba_eye_border.rgba16.inc.c", 0x00180bb0, 29674, 0x00001408, 2048);

// 0x05001C08
ROM_ASSET_LOAD_TEXTURE(bubba_seg5_texture_05001C08, "actors/bubba/bubba_fins.rgba16.inc.c", 0x00180bb0, 29674, 0x00001c08, 2048);

// 0x05002408
ROM_ASSET_LOAD_TEXTURE(bubba_seg5_texture_05002408, "actors/bubba/bubba_scales.rgba16.inc.c", 0x00180bb0, 29674, 0x00002408, 8192);

// 0x05004408
static const Lights1 bubba_seg5_lights_05004408 = gdSPDefLights1(
    0x48, 0x31, 0x2a,
    0xf1, 0xa6, 0x8c, 0x28, 0x28, 0x28
);

// 0x05004420
static const Lights1 bubba_seg5_lights_05004420 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004438
static const Lights1 bubba_seg5_lights_05004438 = gdSPDefLights1(
    0x10, 0x07, 0x08,
    0x36, 0x1a, 0x1c, 0x28, 0x28, 0x28
);

// 0x05004450
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004450, 0x00180bb0, 29674, 0x00004450, 112);

// 0x050044C0
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_050044C0, 0x00180bb0, 29674, 0x000044c0, 240);

// 0x050045B0
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_050045B0, 0x00180bb0, 29674, 0x000045b0, 112);

// 0x05004620
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004620, 0x00180bb0, 29674, 0x00004620, 96);

// 0x05004680
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004680, 0x00180bb0, 29674, 0x00004680, 256);

// 0x05004780
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004780, 0x00180bb0, 29674, 0x00004780, 240);

// 0x05004870
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004870, 0x00180bb0, 29674, 0x00004870, 208);

// 0x05004940
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004940, 0x00180bb0, 29674, 0x00004940, 144);

// 0x050049D0
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_050049D0, 0x00180bb0, 29674, 0x000049d0, 112);

// 0x05004A40 - 0x05004AA8
const Gfx bubba_seg5_dl_05004A40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05000008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bubba_seg5_lights_05004408.l, 1),
    gsSPLight(&bubba_seg5_lights_05004408.a, 2),
    gsSPVertex(bubba_seg5_vertex_05004450, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  5,  1,  4, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  5,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004AA8 - 0x05004BE8
const Gfx bubba_seg5_dl_05004AA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05001408),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bubba_seg5_lights_05004420.l, 1),
    gsSPLight(&bubba_seg5_lights_05004420.a, 2),
    gsSPVertex(bubba_seg5_vertex_050044C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  5,  0,  4, 0x0),
    gsSP2Triangles( 5,  6,  0, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 6,  4,  1, 0x0,  1,  4,  3, 0x0),
    gsSP2Triangles( 1,  3,  2, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles( 9, 11,  7, 0x0, 10,  7, 11, 0x0),
    gsSP2Triangles( 9,  8, 12, 0x0, 12,  8, 10, 0x0),
    gsSP2Triangles(13,  9, 14, 0x0,  9, 12, 14, 0x0),
    gsSP2Triangles(13, 11,  9, 0x0, 12, 10, 14, 0x0),
    gsSP2Triangles(13, 14, 10, 0x0, 10, 11, 13, 0x0),
    gsSPVertex(bubba_seg5_vertex_050045B0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 6,  2,  5, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 6,  3,  2, 0x0,  3,  6,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004BE8 - 0x05004C40
const Gfx bubba_seg5_dl_05004BE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05001C08),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bubba_seg5_vertex_05004620, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  1,  0,  4, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  4,  0,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004C40 - 0x05004D48
const Gfx bubba_seg5_dl_05004C40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05002408),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bubba_seg5_vertex_05004680, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9,  8,  5, 0x0),
    gsSP2Triangles( 9,  5,  7, 0x0,  2,  4,  3, 0x0),
    gsSP2Triangles(10,  4, 11, 0x0,  7,  4, 10, 0x0),
    gsSP2Triangles(11,  4,  2, 0x0,  9,  7, 12, 0x0),
    gsSP2Triangles( 2,  3,  6, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0,  1, 13, 14, 0x0),
    gsSP1Triangle( 0,  6, 15, 0x0),
    gsSPVertex(bubba_seg5_vertex_05004780, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 2,  3,  0, 0x0,  5,  2,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(11,  4, 10, 0x0, 10,  4,  3, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0,  5,  6, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004D48 - 0x05004E80
const Gfx bubba_seg5_dl_05004D48[] = {
    gsSPLight(&bubba_seg5_lights_05004408.l, 1),
    gsSPLight(&bubba_seg5_lights_05004408.a, 2),
    gsSPVertex(bubba_seg5_vertex_05004870, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8,  7,  3, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 11,  0, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0,  3,  7,  0, 0x0),
    gsSP2Triangles( 0, 11,  1, 0x0,  6, 10,  9, 0x0),
    gsSP2Triangles(12, 10,  6, 0x0, 12, 11, 10, 0x0),
    gsSPLight(&bubba_seg5_lights_05004438.l, 1),
    gsSPLight(&bubba_seg5_lights_05004438.a, 2),
    gsSPVertex(bubba_seg5_vertex_05004940, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  5,  6,  3, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 8,  2,  1, 0x0,  8,  1,  0, 0x0),
    gsSP1Triangle( 4,  8,  0, 0x0),
    gsSPLight(&bubba_seg5_lights_05004420.l, 1),
    gsSPLight(&bubba_seg5_lights_05004420.a, 2),
    gsSPVertex(bubba_seg5_vertex_050049D0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 2,  6,  0, 0x0,  6,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004E80 - 0x05004F30
const Gfx bubba_seg5_dl_05004E80[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bubba_seg5_dl_05004A40),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bubba_seg5_dl_05004AA8),
    gsSPDisplayList(bubba_seg5_dl_05004BE8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bubba_seg5_dl_05004C40),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bubba_seg5_dl_05004D48),
    gsSPEndDisplayList(),
};

// 0x05004F30
static const Lights1 bubba_seg5_lights_05004F30 = gdSPDefLights1(
    0x48, 0x31, 0x2a,
    0xf1, 0xa6, 0x8c, 0x28, 0x28, 0x28
);

// 0x05004F48
static const Lights1 bubba_seg5_lights_05004F50 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004F60
static const Lights1 bubba_seg5_lights_05004F60 = gdSPDefLights1(
    0x0a, 0x07, 0x08,
    0x22, 0x1a, 0x1c, 0x28, 0x28, 0x28
);

// 0x05004F78
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004F78, 0x00180bb0, 29674, 0x00004f78, 112);

// 0x05004FE8
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05004FE8, 0x00180bb0, 29674, 0x00004fe8, 240);

// 0x050050D8
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_050050D8, 0x00180bb0, 29674, 0x000050d8, 112);

// 0x05005148
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05005148, 0x00180bb0, 29674, 0x00005148, 96);

// 0x050051A8
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_050051A8, 0x00180bb0, 29674, 0x000051a8, 256);

// 0x050052A8
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_050052A8, 0x00180bb0, 29674, 0x000052a8, 192);

// 0x05005368
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05005368, 0x00180bb0, 29674, 0x00005368, 208);

// 0x05005438
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_05005438, 0x00180bb0, 29674, 0x00005438, 144);

// 0x050054C8
ROM_ASSET_LOAD_VTX(bubba_seg5_vertex_050054C8, 0x00180bb0, 29674, 0x000054c8, 112);

// 0x05005538 - 0x050055A0
const Gfx bubba_seg5_dl_05005538[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05000008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bubba_seg5_lights_05004F30.l, 1),
    gsSPLight(&bubba_seg5_lights_05004F30.a, 2),
    gsSPVertex(bubba_seg5_vertex_05004F78, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 6,  0,  3, 0x0,  1,  0,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x050055A0 - 0x050056E0
const Gfx bubba_seg5_dl_050055A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05001408),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bubba_seg5_lights_05004F50.l, 1),
    gsSPLight(&bubba_seg5_lights_05004F50.a, 2),
    gsSPVertex(bubba_seg5_vertex_05004FE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  6,  5,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  5,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 9,  8, 12, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles( 9, 13, 10, 0x0,  9, 12, 13, 0x0),
    gsSP2Triangles(12,  8, 14, 0x0, 14, 13, 12, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 11, 0x0),
    gsSP2Triangles(14,  8,  7, 0x0, 14,  7, 11, 0x0),
    gsSPVertex(bubba_seg5_vertex_050050D8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  3,  2, 0x0),
    gsSP2Triangles( 5,  0,  3, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 0,  6,  4, 0x0,  5,  6,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x050056E0 - 0x05005738
const Gfx bubba_seg5_dl_050056E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05001C08),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bubba_seg5_vertex_05005148, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  2,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005738 - 0x05005840
const Gfx bubba_seg5_dl_05005738[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bubba_seg5_texture_05002408),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bubba_seg5_vertex_050051A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  0,  4,  6, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 5,  3,  9, 0x0,  8,  3,  2, 0x0),
    gsSP2Triangles( 9,  3,  7, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles( 7, 11,  9, 0x0, 12,  1,  0, 0x0),
    gsSP2Triangles(12,  0,  6, 0x0, 13, 14,  1, 0x0),
    gsSP2Triangles( 2,  1, 14, 0x0,  1, 15, 13, 0x0),
    gsSP1Triangle(14,  8,  2, 0x0),
    gsSPVertex(bubba_seg5_vertex_050052A8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 3,  4,  6, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 3,  6,  8, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0, 10,  9, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005840 - 0x05005978
const Gfx bubba_seg5_dl_05005840[] = {
    gsSPLight(&bubba_seg5_lights_05004F30.l, 1),
    gsSPLight(&bubba_seg5_lights_05004F30.a, 2),
    gsSPVertex(bubba_seg5_vertex_05005368, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 5,  7,  2, 0x0,  8,  3,  4, 0x0),
    gsSP2Triangles( 9,  6, 10, 0x0,  5,  6,  9, 0x0),
    gsSP2Triangles(11,  6,  1, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles(12,  5,  9, 0x0,  7,  5, 12, 0x0),
    gsSP2Triangles( 9,  8, 12, 0x0,  0, 11,  1, 0x0),
    gsSPLight(&bubba_seg5_lights_05004F60.l, 1),
    gsSPLight(&bubba_seg5_lights_05004F60.a, 2),
    gsSPVertex(bubba_seg5_vertex_05005438, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 3,  7,  6, 0x0,  3,  8,  7, 0x0),
    gsSP2Triangles( 7,  8,  0, 0x0,  8,  1,  0, 0x0),
    gsSP1Triangle( 8,  2,  1, 0x0),
    gsSPLight(&bubba_seg5_lights_05004F50.l, 1),
    gsSPLight(&bubba_seg5_lights_05004F50.a, 2),
    gsSPVertex(bubba_seg5_vertex_050054C8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  0,  6,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005978 - 0x05005A28
const Gfx bubba_seg5_dl_05005978[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bubba_seg5_dl_05005538),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bubba_seg5_dl_050055A0),
    gsSPDisplayList(bubba_seg5_dl_050056E0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bubba_seg5_dl_05005738),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bubba_seg5_dl_05005840),
    gsSPEndDisplayList(),
};
