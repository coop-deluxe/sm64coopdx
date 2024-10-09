#include "pc/rom_assets.h"
// 0x07067010 - 0x07067028
static const Lights1 inside_castle_seg7_lights_07067010 = gdSPDefLights1(
    0x39, 0x39, 0x39,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07067028 - 0x07067040
static const Lights1 inside_castle_seg7_lights_07067028 = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07067040 - 0x07067058
static const Lights1 inside_castle_seg7_lights_07067040 = gdSPDefLights1(
    0x4c, 0x42, 0x38,
    0xcd, 0xb2, 0x97, 0x28, 0x28, 0x28
);

// 0x07067058 - 0x07067070
static const Lights1 inside_castle_seg7_lights_07067058 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07067070 - 0x070670F0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067070, 0x00396340, 232834, 0x00067070, 128);

// 0x070670F0 - 0x07067190
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070670F0, 0x00396340, 232834, 0x000670f0, 160);

// 0x07067190 - 0x07067280
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067190, 0x00396340, 232834, 0x00067190, 240);

// 0x07067280 - 0x07067370
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067280, 0x00396340, 232834, 0x00067280, 240);

// 0x07067370 - 0x07067460
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067370, 0x00396340, 232834, 0x00067370, 240);

// 0x07067460 - 0x070674D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067460, 0x00396340, 232834, 0x00067460, 112);

// 0x070674D0 - 0x070675D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070674D0, 0x00396340, 232834, 0x000674d0, 256);

// 0x070675D0 - 0x070676D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070675D0, 0x00396340, 232834, 0x000675d0, 256);

// 0x070676D0 - 0x070677B0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070676D0, 0x00396340, 232834, 0x000676d0, 224);

// 0x070677B0 - 0x070678B0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070677B0, 0x00396340, 232834, 0x000677b0, 256);

// 0x070678B0 - 0x070679B0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070678B0, 0x00396340, 232834, 0x000678b0, 256);

// 0x070679B0 - 0x07067AB0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070679B0, 0x00396340, 232834, 0x000679b0, 256);

// 0x07067AB0 - 0x07067BA0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067AB0, 0x00396340, 232834, 0x00067ab0, 240);

// 0x07067BA0 - 0x07067C90
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067BA0, 0x00396340, 232834, 0x00067ba0, 240);

// 0x07067C90 - 0x07067D90
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067C90, 0x00396340, 232834, 0x00067c90, 256);

// 0x07067D90 - 0x07067E90
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067D90, 0x00396340, 232834, 0x00067d90, 256);

// 0x07067E90 - 0x07067F90
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067E90, 0x00396340, 232834, 0x00067e90, 256);

// 0x07067F90 - 0x07068090
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07067F90, 0x00396340, 232834, 0x00067f90, 256);

// 0x07068090 - 0x070680D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07068090, 0x00396340, 232834, 0x00068090, 64);

// 0x070680D0 - 0x070681D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070680D0, 0x00396340, 232834, 0x000680d0, 256);

// 0x070681D0 - 0x07068210
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070681D0, 0x00396340, 232834, 0x000681d0, 64);

// 0x07068210 - 0x07068288
static const Gfx inside_castle_seg7_dl_07068210[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07067010.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07067010.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07067070, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  5,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07068288 - 0x070682F0
static const Gfx inside_castle_seg7_dl_07068288[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07067028.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07067028.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070670F0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  9,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070682F0 - 0x070683F0
static const Gfx inside_castle_seg7_dl_070682F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07067190, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067280, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067370, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067460, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070683F0 - 0x070684E8
static const Gfx inside_castle_seg7_dl_070683F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070674D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  4,  5, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070675D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  0,  2, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070676D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x070684E8 - 0x070687A8
static const Gfx inside_castle_seg7_dl_070684E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07067040.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07067040.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070677B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  4, 11,  5, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070678B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070679B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067AB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067BA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4, 10,  5, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067C90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067D90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067E90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07067F90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07068090, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070687A8 - 0x07068820
static const Gfx inside_castle_seg7_dl_070687A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07067028.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07067028.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070680D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07068820 - 0x07068850
static const Gfx inside_castle_seg7_dl_07068820[] = {
    gsSPLight(&inside_castle_seg7_lights_07067058.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07067058.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070681D0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07068850 - 0x07068908
const Gfx inside_castle_seg7_dl_07068850[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07068210),
    gsSPDisplayList(inside_castle_seg7_dl_07068288),
    gsSPDisplayList(inside_castle_seg7_dl_070682F0),
    gsSPDisplayList(inside_castle_seg7_dl_070683F0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_070684E8),
    gsSPDisplayList(inside_castle_seg7_dl_070687A8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(inside_castle_seg7_dl_07068820),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
