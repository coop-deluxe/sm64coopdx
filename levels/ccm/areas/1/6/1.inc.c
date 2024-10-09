#include "pc/rom_assets.h"
// 0x0700DE68 - 0x0700DE80
static const Lights1 ccm_seg7_lights_0700DE68 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700DE80 - 0x0700DE98
static const Lights1 ccm_seg7_lights_0700DE80 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700DE98 - 0x0700DEB0
static const Lights1 ccm_seg7_lights_0700DE98 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700DEB0 - 0x0700DEC8
static const Lights1 ccm_seg7_lights_0700DEB0 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0700DEC8 - 0x0700DF88
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700DEC8, 0x00383950, 74560, 0x0000dec8, 192);

// 0x0700DF88 - 0x0700E068
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700DF88, 0x00383950, 74560, 0x0000df88, 224);

// 0x0700E068 - 0x0700E168
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700E068, 0x00383950, 74560, 0x0000e068, 256);

// 0x0700E168 - 0x0700E268
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700E168, 0x00383950, 74560, 0x0000e168, 256);

// 0x0700E268 - 0x0700E2C8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700E268, 0x00383950, 74560, 0x0000e268, 96);

// 0x0700E2C8 - 0x0700E3A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700E2C8, 0x00383950, 74560, 0x0000e2c8, 224);

// 0x0700E3A8 - 0x0700E428
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700E3A8, 0x00383950, 74560, 0x0000e3a8, 128);

// 0x0700E428 - 0x0700E468
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700E428, 0x00383950, 74560, 0x0000e428, 64);

// 0x0700E468 - 0x0700E4A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700E468, 0x00383950, 74560, 0x0000e468, 64);

// 0x0700E4A8 - 0x0700E530
static const Gfx ccm_seg7_dl_0700E4A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0700DE68.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE68.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700DEC8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles(11, 10,  4, 0x0, 10,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E530 - 0x0700E668
static const Gfx ccm_seg7_dl_0700E530[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_0700DF88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPLight(&ccm_seg7_lights_0700DE80.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE80.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700E068, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700E168, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700E268, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ccm_seg7_lights_0700DE98.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE98.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700E2C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E668 - 0x0700E6C0
static const Gfx ccm_seg7_dl_0700E668[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0700DE68.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE68.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700E3A8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E6C0 - 0x0700E708
static const Gfx ccm_seg7_dl_0700E6C0[] = {
    gsSPVertex(ccm_seg7_vertex_0700E428, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPLight(&ccm_seg7_lights_0700DEB0.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DEB0.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700E468, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E708 - 0x0700E790
const Gfx ccm_seg7_dl_0700E708[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0700E4A8),
    gsSPDisplayList(ccm_seg7_dl_0700E530),
    gsSPDisplayList(ccm_seg7_dl_0700E668),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(ccm_seg7_dl_0700E6C0),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
