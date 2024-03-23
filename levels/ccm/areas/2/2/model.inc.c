#include "pc/rom_assets.h"
// 0x0701CED8 - 0x0701CEF0
static const Lights1 ccm_seg7_lights_0701CED8 = gdSPDefLights1(
    0x15, 0x15, 0x15,
    0x55, 0x55, 0x55, 0x28, 0x28, 0x28
);

// 0x0701CEF0 - 0x0701CF08
static const Lights1 ccm_seg7_lights_0701CEF0 = gdSPDefLights1(
    0x26, 0x26, 0x26,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0701CF08 - 0x0701CF20
static const Lights1 ccm_seg7_lights_0701CF08 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0xcc, 0xcc, 0xcc, 0x28, 0x28, 0x28
);

// 0x0701CF20 - 0x0701CF38
static const Lights1 ccm_seg7_lights_0701CF20 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701CF38 - 0x0701D028
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701CF38, 0x00383950, 74560, 0x0001cf38, 240);

// 0x0701D028 - 0x0701D118
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D028, 0x00383950, 74560, 0x0001d028, 240);

// 0x0701D118 - 0x0701D208
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D118, 0x00383950, 74560, 0x0001d118, 240);

// 0x0701D208 - 0x0701D308
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D208, 0x00383950, 74560, 0x0001d208, 256);

// 0x0701D308 - 0x0701D408
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D308, 0x00383950, 74560, 0x0001d308, 256);

// 0x0701D408 - 0x0701D4F8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D408, 0x00383950, 74560, 0x0001d408, 240);

// 0x0701D4F8 - 0x0701D5E8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D4F8, 0x00383950, 74560, 0x0001d4f8, 240);

// 0x0701D5E8 - 0x0701D6E8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D5E8, 0x00383950, 74560, 0x0001d5e8, 256);

// 0x0701D6E8 - 0x0701D7D8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D6E8, 0x00383950, 74560, 0x0001d6e8, 240);

// 0x0701D7D8 - 0x0701D8B8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D7D8, 0x00383950, 74560, 0x0001d7d8, 224);

// 0x0701D8B8 - 0x0701D9A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D8B8, 0x00383950, 74560, 0x0001d8b8, 240);

// 0x0701D9A8 - 0x0701DA58
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701D9A8, 0x00383950, 74560, 0x0001d9a8, 176);

// 0x0701DA58 - 0x0701DAD8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DA58, 0x00383950, 74560, 0x0001da58, 128);

// 0x0701DAD8 - 0x0701DBC8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DAD8, 0x00383950, 74560, 0x0001dad8, 240);

// 0x0701DBC8 - 0x0701DC78
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DBC8, 0x00383950, 74560, 0x0001dbc8, 176);

// 0x0701DC78 - 0x0701DD38
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DC78, 0x00383950, 74560, 0x0001dc78, 192);

// 0x0701DD38 - 0x0701DE38
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DD38, 0x00383950, 74560, 0x0001dd38, 256);

// 0x0701DE38 - 0x0701DEE8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DE38, 0x00383950, 74560, 0x0001de38, 176);

// 0x0701DEE8 - 0x0701DF28
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DEE8, 0x00383950, 74560, 0x0001dee8, 64);

// 0x0701DF28 - 0x0701DF68
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701DF28, 0x00383950, 74560, 0x0001df28, 64);

// 0x0701DF68 - 0x0701E3F8
static const Gfx ccm_seg7_dl_0701DF68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0701CED8.l, 1),
    gsSPLight(&ccm_seg7_lights_0701CED8.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701CF38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D028, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPLight(&ccm_seg7_lights_0701CEF0.l, 1),
    gsSPLight(&ccm_seg7_lights_0701CEF0.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701D118, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  9,  7, 0x0,  4,  6,  9, 0x0),
    gsSP2Triangles( 8, 10,  4, 0x0, 10, 11,  4, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D208, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D308, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  6, 11,  4, 0x0),
    gsSP2Triangles( 5,  2, 11, 0x0,  5, 11,  6, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D408, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  2,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  3, 14,  4, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D4F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D5E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  1,  0, 0x0, 10,  0, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D6E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  9,  8,  6, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0,  5,  7, 11, 0x0),
    gsSP2Triangles(11,  7, 10, 0x0, 11, 10,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D7D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D8B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701D9A8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP1Triangle(10,  0,  2, 0x0),
    gsSPLight(&ccm_seg7_lights_0701CF08.l, 1),
    gsSPLight(&ccm_seg7_lights_0701CF08.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701DA58, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  6,  3,  5, 0x0),
    gsSPLight(&ccm_seg7_lights_0701CF20.l, 1),
    gsSPLight(&ccm_seg7_lights_0701CF20.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701DAD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701DBC8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 2,  9, 10, 0x0,  2,  8,  9, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E3F8 - 0x0701E4E8
static const Gfx ccm_seg7_dl_0701E3F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0701CEF0.l, 1),
    gsSPLight(&ccm_seg7_lights_0701CEF0.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701DC78, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPLight(&ccm_seg7_lights_0701CF20.l, 1),
    gsSPLight(&ccm_seg7_lights_0701CF20.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701DD38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0,  0, 12, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701DE38, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E4E8 - 0x0701E520
static const Gfx ccm_seg7_dl_0701E4E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ccm_seg7_texture_07004300),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_0701DEE8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E520 - 0x0701E558
static const Gfx ccm_seg7_dl_0701E520[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_0701DF28, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E558 - 0x0701E610
const Gfx ccm_seg7_dl_0701E558[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0701DF68),
    gsSPDisplayList(ccm_seg7_dl_0701E3F8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0701E4E8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0701E520),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
