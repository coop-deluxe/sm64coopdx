#include "pc/rom_assets.h"
// 0x070331C8 - 0x070331E0
static const Lights1 inside_castle_seg7_lights_070331C8 = gdSPDefLights1(
    0x52, 0x52, 0x52,
    0xdd, 0xdd, 0xdd, 0x28, 0x28, 0x28
);

// 0x070331E0 - 0x070331F8
static const Lights1 inside_castle_seg7_lights_070331E0 = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070331F8 - 0x070332F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070331F8, 0x00396340, 232834, 0x000331f8, 256);

// 0x070332F8 - 0x070333F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070332F8, 0x00396340, 232834, 0x000332f8, 256);

// 0x070333F8 - 0x070334F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070333F8, 0x00396340, 232834, 0x000333f8, 256);

// 0x070334F8 - 0x070335D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070334F8, 0x00396340, 232834, 0x000334f8, 224);

// 0x070335D8 - 0x070336C8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070335D8, 0x00396340, 232834, 0x000335d8, 240);

// 0x070336C8 - 0x07033748
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070336C8, 0x00396340, 232834, 0x000336c8, 128);

// 0x07033748 - 0x07033838
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033748, 0x00396340, 232834, 0x00033748, 240);

// 0x07033838 - 0x07033928
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033838, 0x00396340, 232834, 0x00033838, 240);

// 0x07033928 - 0x07033A18
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033928, 0x00396340, 232834, 0x00033928, 240);

// 0x07033A18 - 0x07033AF8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033A18, 0x00396340, 232834, 0x00033a18, 224);

// 0x07033AF8 - 0x07033BE8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033AF8, 0x00396340, 232834, 0x00033af8, 240);

// 0x07033BE8 - 0x07033CD8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033BE8, 0x00396340, 232834, 0x00033be8, 240);

// 0x07033CD8 - 0x07033DC8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033CD8, 0x00396340, 232834, 0x00033cd8, 240);

// 0x07033DC8 - 0x07033EB8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033DC8, 0x00396340, 232834, 0x00033dc8, 240);

// 0x07033EB8 - 0x07033FA8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033EB8, 0x00396340, 232834, 0x00033eb8, 240);

// 0x07033FA8 - 0x07033FE8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033FA8, 0x00396340, 232834, 0x00033fa8, 64);

// 0x07033FE8 - 0x070340E8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07033FE8, 0x00396340, 232834, 0x00033fe8, 256);

// 0x070340E8 - 0x070341D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070340E8, 0x00396340, 232834, 0x000340e8, 240);

// 0x070341D8 - 0x070342B8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070341D8, 0x00396340, 232834, 0x000341d8, 224);

// 0x070342B8 - 0x070343A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070342B8, 0x00396340, 232834, 0x000342b8, 240);

// 0x070343A8 - 0x07034428
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070343A8, 0x00396340, 232834, 0x000343a8, 128);

// 0x07034428 - 0x07034528
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07034428, 0x00396340, 232834, 0x00034428, 256);

// 0x07034528 - 0x07034628
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07034528, 0x00396340, 232834, 0x00034528, 256);

// 0x07034628 - 0x07034688
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07034628, 0x00396340, 232834, 0x00034628, 96);

// 0x07034688 - 0x070347D8
static const Gfx inside_castle_seg7_dl_07034688[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_070331C8.l, 1),
    gsSPLight(&inside_castle_seg7_lights_070331C8.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070331F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPLight(&inside_castle_seg7_lights_070331E0.l, 1),
    gsSPLight(&inside_castle_seg7_lights_070331E0.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070332F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070333F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11,  7, 10, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070334F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 10,  9, 0x0,  3,  5, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x070347D8 - 0x07034888
static const Gfx inside_castle_seg7_dl_070347D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070335D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  8,  6, 0x0),
    gsSP2Triangles( 3,  7,  9, 0x0,  3,  5,  8, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070336C8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  1, 0x0),
    gsSP2Triangles( 4,  6,  3, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 0,  5,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07034888 - 0x07034B28
static const Gfx inside_castle_seg7_dl_07034888[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07033748, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033838, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles( 5, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033928, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4,  6, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 7, 14,  8, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033A18, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033AF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033BE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 2,  6,  0, 0x0,  2,  7,  6, 0x0),
    gsSP2Triangles( 2,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033CD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033DC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033EB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07033FA8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07034B28 - 0x07034B90
static const Gfx inside_castle_seg7_dl_07034B28[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07033FE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07034B90 - 0x07034C90
static const Gfx inside_castle_seg7_dl_07034B90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070340E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070341D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070342B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070343A8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07034C90 - 0x07034D88
static const Gfx inside_castle_seg7_dl_07034C90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07034428, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 7,  4,  6, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07034528, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  3,  2,  7, 0x0),
    gsSP2Triangles( 5,  3,  7, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14,  8, 10, 0x0, 14, 10, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07034628, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07034D88 - 0x07034E50
const Gfx inside_castle_seg7_dl_07034D88[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07034688),
    gsSPDisplayList(inside_castle_seg7_dl_070347D8),
    gsSPDisplayList(inside_castle_seg7_dl_07034888),
    gsSPDisplayList(inside_castle_seg7_dl_07034B28),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07034B90),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07034C90),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
