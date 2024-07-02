#include "pc/rom_assets.h"
// 0x07050A78 - 0x07050A90
static const Lights1 inside_castle_seg7_lights_07050A78 = gdSPDefLights1(
    0x40, 0x2f, 0x1e,
    0xac, 0x7f, 0x52, 0x28, 0x28, 0x28
);

// 0x07050A90 - 0x07050AA8
static const Lights1 inside_castle_seg7_lights_07050A90 = gdSPDefLights1(
    0x40, 0x3a, 0x1e,
    0xac, 0x9d, 0x52, 0x28, 0x28, 0x28
);

// 0x07050AA8 - 0x07050B68
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07050AA8, 0x00396340, 232834, 0x00050aa8, 192);

// 0x07050B68 - 0x07050C58
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07050B68, 0x00396340, 232834, 0x00050b68, 240);

// 0x07050C58 - 0x07050D58
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07050C58, 0x00396340, 232834, 0x00050c58, 256);

// 0x07050D58 - 0x07050E58
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07050D58, 0x00396340, 232834, 0x00050d58, 256);

// 0x07050E58 - 0x07050F58
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07050E58, 0x00396340, 232834, 0x00050e58, 256);

// 0x07050F58 - 0x07051048
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07050F58, 0x00396340, 232834, 0x00050f58, 240);

// 0x07051048 - 0x07051108
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07051048, 0x00396340, 232834, 0x00051048, 192);

// 0x07051108 - 0x07051170
static const Gfx inside_castle_seg7_dl_07051108[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07050A78.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07050A78.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07050AA8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07051170 - 0x070512F8
static const Gfx inside_castle_seg7_dl_07051170[] = {
    gsSPLight(&inside_castle_seg7_lights_07050A90.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07050A90.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07050B68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  2,  8, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles( 0, 10,  6, 0x0,  3,  5, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07050C58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07050D58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07050E58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  6, 15,  7, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07050F58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07051048, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x070512F8 - 0x07051370
const Gfx inside_castle_seg7_dl_070512F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07051108),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(inside_castle_seg7_dl_07051170),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
