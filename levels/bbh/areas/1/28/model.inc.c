#include "pc/rom_assets.h"
// 0x07015A90 - 0x07015AA8
static const Lights1 bbh_seg7_lights_07015A90 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07015AA8 - 0x07015B98
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07015AA8, 0x00371c40, 68724, 0x00015aa8, 240);

// 0x07015B98 - 0x07015C08
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07015B98, 0x00371c40, 68724, 0x00015b98, 112);

// 0x07015C08 - 0x07015C78
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07015C08, 0x00371c40, 68724, 0x00015c08, 112);

// 0x07015C78 - 0x07015D68
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07015C78, 0x00371c40, 68724, 0x00015c78, 240);

// 0x07015D68 - 0x07015E58
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07015D68, 0x00371c40, 68724, 0x00015d68, 240);

// 0x07015E58 - 0x07015F58
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07015E58, 0x00371c40, 68724, 0x00015e58, 256);

// 0x07015F58 - 0x07016038
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07015F58, 0x00371c40, 68724, 0x00015f58, 224);

// 0x07016038 - 0x07016118
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016038, 0x00371c40, 68724, 0x00016038, 224);

// 0x07016118 - 0x07016208
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016118, 0x00371c40, 68724, 0x00016118, 240);

// 0x07016208 - 0x070162F8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016208, 0x00371c40, 68724, 0x00016208, 240);

// 0x070162F8 - 0x070163F8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070162F8, 0x00371c40, 68724, 0x000162f8, 256);

// 0x070163F8 - 0x070164D8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070163F8, 0x00371c40, 68724, 0x000163f8, 224);

// 0x070164D8 - 0x07016558
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070164D8, 0x00371c40, 68724, 0x000164d8, 128);

// 0x07016558 - 0x070165D8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016558, 0x00371c40, 68724, 0x00016558, 128);

// 0x070165D8 - 0x070166B8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070165D8, 0x00371c40, 68724, 0x000165d8, 224);

// 0x070166B8 - 0x070167A8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070166B8, 0x00371c40, 68724, 0x000166b8, 240);

// 0x070167A8 - 0x07016888
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070167A8, 0x00371c40, 68724, 0x000167a8, 224);

// 0x07016888 - 0x07016968
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016888, 0x00371c40, 68724, 0x00016888, 224);

// 0x07016968 - 0x07016A58
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016968, 0x00371c40, 68724, 0x00016968, 240);

// 0x07016A58 - 0x07016B58
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016A58, 0x00371c40, 68724, 0x00016a58, 256);

// 0x07016B58 - 0x07016C58
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016B58, 0x00371c40, 68724, 0x00016b58, 256);

// 0x07016C58 - 0x07016D38
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07016C58, 0x00371c40, 68724, 0x00016c58, 224);

// 0x07016D38 - 0x07016DC8
static const Gfx bbh_seg7_dl_07016D38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07015A90.l, 1),
    gsSPLight(&bbh_seg7_lights_07015A90.a, 2),
    gsSPVertex(bbh_seg7_vertex_07015AA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07015B98, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016DC8 - 0x07016E10
static const Gfx bbh_seg7_dl_07016DC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07015C08, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016E10 - 0x07016FE8
static const Gfx bbh_seg7_dl_07016E10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07015C78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07015D68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07015E58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_07015F58, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016038, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016118, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016208, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 8, 10, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016FE8 - 0x07017050
static const Gfx bbh_seg7_dl_07016FE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070162F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017050 - 0x070170B8
static const Gfx bbh_seg7_dl_07017050[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070163F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x070170B8 - 0x07017100
static const Gfx bbh_seg7_dl_070170B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_07002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070164D8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017100 - 0x07017148
static const Gfx bbh_seg7_dl_07017100[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07016558, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017148 - 0x07017378
static const Gfx bbh_seg7_dl_07017148[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070165D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 12,  7,  9, 0x0),
    gsSP2Triangles(12, 13,  7, 0x0, 13, 11,  7, 0x0),
    gsSPVertex(bbh_seg7_vertex_070166B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0,  4, 13,  5, 0x0),
    gsSP1Triangle( 4, 14, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070167A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8, 13,  9, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016888, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 13, 11, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016968, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016A58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016B58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  3,  5, 0x0),
    gsSP2Triangles(11, 12,  3, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07016C58, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  7, 13,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017378 - 0x07017480
const Gfx bbh_seg7_dl_07017378[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07016D38),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07016DC8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07016E10),
    gsSPDisplayList(bbh_seg7_dl_07016FE8),
    gsSPDisplayList(bbh_seg7_dl_07017050),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070170B8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07017100),
    gsSPDisplayList(bbh_seg7_dl_07017148),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
