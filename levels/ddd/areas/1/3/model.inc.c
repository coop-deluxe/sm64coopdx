#include "pc/rom_assets.h"
// 0x07005850 - 0x07005868
static const Lights1 ddd_seg7_lights_07005850 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07005868 - 0x07005968
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07005868, 0x0048d930, 33063, 0x00005868, 256);

// 0x07005968 - 0x07005A68
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07005968, 0x0048d930, 33063, 0x00005968, 256);

// 0x07005A68 - 0x07005AF8
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07005A68, 0x0048d930, 33063, 0x00005a68, 144);

// 0x07005AF8 - 0x07005C40
static const Gfx ddd_seg7_dl_07005AF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900B800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_07005850.l, 1),
    gsSPLight(&ddd_seg7_lights_07005850.a, 2),
    gsSPVertex(ddd_seg7_vertex_07005868, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11,  8,  3, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0,  2, 12, 11, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07005968, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 12, 14, 13, 0x0),
    gsSP1Triangle(15, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_07005A68, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  6,  5, 0x0),
    gsSP1Triangle( 7,  8,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005C40 - 0x07005CB0
const Gfx ddd_seg7_dl_07005C40[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_07005AF8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
