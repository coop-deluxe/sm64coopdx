#include "pc/rom_assets.h"
// 0x07057FD8 - 0x07057FF0
static const Lights1 inside_castle_seg7_lights_07057FD8 = gdSPDefLights1(
    0x3f, 0x33, 0x19,
    0xff, 0xcc, 0x65, 0x28, 0x28, 0x28
);

// 0x07057FF0 - 0x07058008
static const Lights1 inside_castle_seg7_lights_07057FF0 = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07058008 - 0x07058108
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058008, 0x00396340, 232834, 0x00058008, 256);

// 0x07058108 - 0x070581F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058108, 0x00396340, 232834, 0x00058108, 240);

// 0x070581F8 - 0x070582F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070581F8, 0x00396340, 232834, 0x000581f8, 256);

// 0x070582F8 - 0x070583E8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070582F8, 0x00396340, 232834, 0x000582f8, 240);

// 0x070583E8 - 0x070584E8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070583E8, 0x00396340, 232834, 0x000583e8, 256);

// 0x070584E8 - 0x070585A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070584E8, 0x00396340, 232834, 0x000584e8, 192);

// 0x070585A8 - 0x07058698
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070585A8, 0x00396340, 232834, 0x000585a8, 240);

// 0x07058698 - 0x07058718
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058698, 0x00396340, 232834, 0x00058698, 128);

// 0x07058718 - 0x07058950
static const Gfx inside_castle_seg7_dl_07058718[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07057FD8.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07057FD8.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07058008, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07058108, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070581F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12,  1, 0x0),
    gsSP2Triangles(11,  1,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070582F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070583E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070584E8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0,  7, 11,  8, 0x0),
    gsSPLight(&inside_castle_seg7_lights_07057FF0.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07057FF0.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070585A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07058698, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07058950 - 0x070589C0
const Gfx inside_castle_seg7_dl_07058950[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07058718),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
