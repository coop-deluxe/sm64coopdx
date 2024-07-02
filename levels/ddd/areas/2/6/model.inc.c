#include "pc/rom_assets.h"
// 0x0700BB50 - 0x0700BB68
static const Lights1 ddd_seg7_lights_0700BB50 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700BB68 - 0x0700BC58
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700BB68, 0x0048d930, 33063, 0x0000bb68, 240);

// 0x0700BC58 - 0x0700BC98
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700BC58, 0x0048d930, 33063, 0x0000bc58, 64);

// 0x0700BC98 - 0x0700BD88
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700BC98, 0x0048d930, 33063, 0x0000bc98, 240);

// 0x0700BD88 - 0x0700BE78
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700BD88, 0x0048d930, 33063, 0x0000bd88, 240);

// 0x0700BE78 - 0x0700BF68
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700BE78, 0x0048d930, 33063, 0x0000be78, 240);

// 0x0700BF68 - 0x0700C058
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700BF68, 0x0048d930, 33063, 0x0000bf68, 240);

// 0x0700C058 - 0x0700C148
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C058, 0x0048d930, 33063, 0x0000c058, 240);

// 0x0700C148 - 0x0700C238
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C148, 0x0048d930, 33063, 0x0000c148, 240);

// 0x0700C238 - 0x0700C328
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C238, 0x0048d930, 33063, 0x0000c238, 240);

// 0x0700C328 - 0x0700C398
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C328, 0x0048d930, 33063, 0x0000c328, 112);

// 0x0700C398 - 0x0700C488
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C398, 0x0048d930, 33063, 0x0000c398, 240);

// 0x0700C488 - 0x0700C578
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C488, 0x0048d930, 33063, 0x0000c488, 240);

// 0x0700C578 - 0x0700C668
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C578, 0x0048d930, 33063, 0x0000c578, 240);

// 0x0700C668 - 0x0700C768
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C668, 0x0048d930, 33063, 0x0000c668, 256);

// 0x0700C768 - 0x0700C858
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C768, 0x0048d930, 33063, 0x0000c768, 240);

// 0x0700C858 - 0x0700C958
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C858, 0x0048d930, 33063, 0x0000c858, 256);

// 0x0700C958 - 0x0700C9D8
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700C958, 0x0048d930, 33063, 0x0000c958, 128);

// 0x0700C9D8 - 0x0700CA70
static const Gfx ddd_seg7_dl_0700C9D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_0700BB50.l, 1),
    gsSPLight(&ddd_seg7_lights_0700BB50.a, 2),
    gsSPVertex(ddd_seg7_vertex_0700BB68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 13,  0,  2, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700BC58, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CA70 - 0x0700CC70
static const Gfx ddd_seg7_dl_0700CA70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ddd_seg7_texture_07001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ddd_seg7_vertex_0700BC98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700BD88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700BE78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700BF68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C058, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C148, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C238, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C328, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CC70 - 0x0700CE48
static const Gfx ddd_seg7_dl_0700CC70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ddd_seg7_vertex_0700C398, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C488, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C578, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C668, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0,  6,  8, 11, 0x0),
    gsSP2Triangles( 2, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C768, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C858, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 3,  4,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 11, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700C958, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CE48 - 0x0700CEE0
const Gfx ddd_seg7_dl_0700CE48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_0700C9D8),
    gsSPDisplayList(ddd_seg7_dl_0700CA70),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_0700CC70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
