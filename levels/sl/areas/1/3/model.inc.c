#include "pc/rom_assets.h"
// 0x07005730 - 0x07005748
static const Lights1 sl_seg7_lights_07005730 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07005748 - 0x07005760
static const Lights1 sl_seg7_lights_07005748 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07005760 - 0x070057D0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005760, 0x00405fb0, 34952, 0x00005760, 112);

// 0x070057D0 - 0x07005810
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070057D0, 0x00405fb0, 34952, 0x000057d0, 64);

// 0x07005810 - 0x07005900
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005810, 0x00405fb0, 34952, 0x00005810, 240);

// 0x07005900 - 0x07005A00
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005900, 0x00405fb0, 34952, 0x00005900, 256);

// 0x07005A00 - 0x07005A30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005A00, 0x00405fb0, 34952, 0x00005a00, 48);

// 0x07005A30 - 0x07005B30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005A30, 0x00405fb0, 34952, 0x00005a30, 256);

// 0x07005B30 - 0x07005C30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005B30, 0x00405fb0, 34952, 0x00005b30, 256);

// 0x07005C30 - 0x07005D30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005C30, 0x00405fb0, 34952, 0x00005c30, 256);

// 0x07005D30 - 0x07005E10
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005D30, 0x00405fb0, 34952, 0x00005d30, 224);

// 0x07005E10 - 0x07005EF0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005E10, 0x00405fb0, 34952, 0x00005e10, 224);

// 0x07005EF0 - 0x07005FF0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005EF0, 0x00405fb0, 34952, 0x00005ef0, 256);

// 0x07005FF0 - 0x070060E0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07005FF0, 0x00405fb0, 34952, 0x00005ff0, 240);

// 0x070060E0 - 0x070061E0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070060E0, 0x00405fb0, 34952, 0x000060e0, 256);

// 0x070061E0 - 0x07006250
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070061E0, 0x00405fb0, 34952, 0x000061e0, 112);

// 0x07006250 - 0x07006350
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006250, 0x00405fb0, 34952, 0x00006250, 256);

// 0x07006350 - 0x070063B0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006350, 0x00405fb0, 34952, 0x00006350, 96);

// 0x070063B0 - 0x070064B0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070063B0, 0x00405fb0, 34952, 0x000063b0, 256);

// 0x070064B0 - 0x07006590
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070064B0, 0x00405fb0, 34952, 0x000064b0, 224);

// 0x07006590 - 0x07006690
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006590, 0x00405fb0, 34952, 0x00006590, 256);

// 0x07006690 - 0x07006790
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006690, 0x00405fb0, 34952, 0x00006690, 256);

// 0x07006790 - 0x07006870
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006790, 0x00405fb0, 34952, 0x00006790, 224);

// 0x07006870 - 0x07006950
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006870, 0x00405fb0, 34952, 0x00006870, 224);

// 0x07006950 - 0x07006A40
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006950, 0x00405fb0, 34952, 0x00006950, 240);

// 0x07006A40 - 0x07006B30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006A40, 0x00405fb0, 34952, 0x00006a40, 240);

// 0x07006B30 - 0x07006C30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006B30, 0x00405fb0, 34952, 0x00006b30, 256);

// 0x07006C30 - 0x07006C70
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006C30, 0x00405fb0, 34952, 0x00006c30, 64);

// 0x07006C70 - 0x07006D70
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07006C70, 0x00405fb0, 34952, 0x00006c70, 256);

// 0x07006D70 - 0x07006DE8
static const Gfx sl_seg7_dl_07006D70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sl_seg7_lights_07005730.l, 1),
    gsSPLight(&sl_seg7_lights_07005730.a, 2),
    gsSPVertex(sl_seg7_vertex_07005760, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  6,  4, 0x0),
    gsSPLight(&sl_seg7_lights_07005748.l, 1),
    gsSPLight(&sl_seg7_lights_07005748.a, 2),
    gsSPVertex(sl_seg7_vertex_070057D0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006DE8 - 0x07006EB0
static const Gfx sl_seg7_dl_07006DE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sl_seg7_lights_07005730.l, 1),
    gsSPLight(&sl_seg7_lights_07005730.a, 2),
    gsSPVertex(sl_seg7_vertex_07005810, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07005900, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP2Triangles( 0, 14,  1, 0x0,  0, 15, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07005A00, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006EB0 - 0x070070A8
static const Gfx sl_seg7_dl_07006EB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07005A30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07005B30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07005C30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07005D30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07005E10, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07005EF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07005FF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_070060E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_070061E0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x070070A8 - 0x07007118
static const Gfx sl_seg7_dl_070070A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07006250, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07006350, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007118 - 0x07007368
static const Gfx sl_seg7_dl_07007118[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_070063B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_070064B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(sl_seg7_vertex_07006590, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07006690, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07006790, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07006870, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07006950, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(sl_seg7_vertex_07006A40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(sl_seg7_vertex_07006B30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07006C30, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007368 - 0x070073D0
static const Gfx sl_seg7_dl_07007368[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07006C70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x070073D0 - 0x07007480
const Gfx sl_seg7_dl_070073D0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_07006D70),
    gsSPDisplayList(sl_seg7_dl_07006DE8),
    gsSPDisplayList(sl_seg7_dl_07006EB0),
    gsSPDisplayList(sl_seg7_dl_070070A8),
    gsSPDisplayList(sl_seg7_dl_07007118),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_07007368),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
