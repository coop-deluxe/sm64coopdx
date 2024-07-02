#include "pc/rom_assets.h"
// 0x0701FEE0 - 0x0701FEF8
static const Lights1 ccm_seg7_lights_0701FEE0 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0701FEF8 - 0x0701FF10
static const Lights1 ccm_seg7_lights_0701FEF8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701FF10 - 0x0701FF70
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701FF10, 0x00383950, 74560, 0x0001ff10, 96);

// 0x0701FF70 - 0x07020070
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701FF70, 0x00383950, 74560, 0x0001ff70, 256);

// 0x07020070 - 0x07020170
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07020070, 0x00383950, 74560, 0x00020070, 256);

// 0x07020170 - 0x07020270
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07020170, 0x00383950, 74560, 0x00020170, 256);

// 0x07020270 - 0x07020360
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07020270, 0x00383950, 74560, 0x00020270, 240);

// 0x07020360 - 0x07020450
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07020360, 0x00383950, 74560, 0x00020360, 240);

// 0x07020450 - 0x07020540
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07020450, 0x00383950, 74560, 0x00020450, 240);

// 0x07020540 - 0x07020590
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07020540, 0x00383950, 74560, 0x00020540, 80);

// 0x07020590 - 0x070205E8
static const Gfx ccm_seg7_dl_07020590[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, ccm_seg7_texture_07003900),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0701FEE0.l, 1),
    gsSPLight(&ccm_seg7_lights_0701FEE0.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701FF10, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x070205E8 - 0x070207F0
static const Gfx ccm_seg7_dl_070205E8[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, ccm_seg7_texture_07003B00),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0701FEF8.l, 1),
    gsSPLight(&ccm_seg7_lights_0701FEF8.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701FF70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9,  2, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 10, 14, 13, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0, 11, 15, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_07020070, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07020170, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 8, 10,  5, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07020270, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07020360, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07020450, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07020540, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 3,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x070207F0 - 0x07020880
const Gfx ccm_seg7_dl_070207F0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_07020590),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_070205E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
