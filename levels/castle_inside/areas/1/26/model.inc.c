#include "pc/rom_assets.h"
// 0x0703A878 - 0x0703A890
static const Lights1 inside_castle_seg7_lights_0703A878 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xcc, 0xcc, 0xcc, 0x28, 0x28, 0x28
);

// 0x0703A890 - 0x0703A8A8
static const Lights1 inside_castle_seg7_lights_0703A890 = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0703A8A8 - 0x0703A998
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703A8A8, 0x00396340, 232834, 0x0003a8a8, 240);

// 0x0703A998 - 0x0703AA98
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703A998, 0x00396340, 232834, 0x0003a998, 256);

// 0x0703AA98 - 0x0703AB88
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703AA98, 0x00396340, 232834, 0x0003aa98, 240);

// 0x0703AB88 - 0x0703ABC8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703AB88, 0x00396340, 232834, 0x0003ab88, 64);

// 0x0703ABC8 - 0x0703ACC8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703ABC8, 0x00396340, 232834, 0x0003abc8, 256);

// 0x0703ACC8 - 0x0703ADB8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703ACC8, 0x00396340, 232834, 0x0003acc8, 240);

// 0x0703ADB8 - 0x0703AEB8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703ADB8, 0x00396340, 232834, 0x0003adb8, 256);

// 0x0703AEB8 - 0x0703AFA8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703AEB8, 0x00396340, 232834, 0x0003aeb8, 240);

// 0x0703AFA8 - 0x0703B0A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703AFA8, 0x00396340, 232834, 0x0003afa8, 256);

// 0x0703B0A8 - 0x0703B1A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703B0A8, 0x00396340, 232834, 0x0003b0a8, 256);

// 0x0703B1A8 - 0x0703B298
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703B1A8, 0x00396340, 232834, 0x0003b1a8, 240);

// 0x0703B298 - 0x0703B398
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703B298, 0x00396340, 232834, 0x0003b298, 256);

// 0x0703B398 - 0x0703B458
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703B398, 0x00396340, 232834, 0x0003b398, 192);

// 0x0703B458 - 0x0703B548
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703B458, 0x00396340, 232834, 0x0003b458, 240);

// 0x0703B548 - 0x0703B5B8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_0703B548, 0x00396340, 232834, 0x0003b548, 112);

// 0x0703B5B8 - 0x0703B6C8
static const Gfx inside_castle_seg7_dl_0703B5B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_0703A878.l, 1),
    gsSPLight(&inside_castle_seg7_lights_0703A878.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_0703A8A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  4,  6, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703A998, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703AA98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPLight(&inside_castle_seg7_lights_0703A890.l, 1),
    gsSPLight(&inside_castle_seg7_lights_0703A890.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_0703AB88, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703B6C8 - 0x0703B740
static const Gfx inside_castle_seg7_dl_0703B6C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_0703ABC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  1,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 12, 15, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703B740 - 0x0703B808
static const Gfx inside_castle_seg7_dl_0703B740[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_0703ACC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703ADB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703AEB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703B808 - 0x0703B988
static const Gfx inside_castle_seg7_dl_0703B808[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_0703AFA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 10,  1, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703B0A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703B1A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703B298, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703B398, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703B988 - 0x0703BA08
static const Gfx inside_castle_seg7_dl_0703B988[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_0703B458, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_0703B548, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703BA08 - 0x0703BAB0
const Gfx inside_castle_seg7_dl_0703BA08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_0703B5B8),
    gsSPDisplayList(inside_castle_seg7_dl_0703B6C8),
    gsSPDisplayList(inside_castle_seg7_dl_0703B740),
    gsSPDisplayList(inside_castle_seg7_dl_0703B808),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_0703B988),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
