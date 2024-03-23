#include "pc/rom_assets.h"
// 0x070049E8 - 0x07004AC8
ROM_ASSET_LOAD_VTX(castle_courtyard_seg7_vertex_070049E8, 0x004ac570, 12537, 0x000049e8, 224);

// 0x07004AC8 - 0x07004BB8
ROM_ASSET_LOAD_VTX(castle_courtyard_seg7_vertex_07004AC8, 0x004ac570, 12537, 0x00004ac8, 240);

// 0x07004BB8 - 0x07004CA8
ROM_ASSET_LOAD_VTX(castle_courtyard_seg7_vertex_07004BB8, 0x004ac570, 12537, 0x00004bb8, 240);

// 0x07004CA8 - 0x07004DA8
ROM_ASSET_LOAD_VTX(castle_courtyard_seg7_vertex_07004CA8, 0x004ac570, 12537, 0x00004ca8, 256);

// 0x07004DA8 - 0x07004EA8
ROM_ASSET_LOAD_VTX(castle_courtyard_seg7_vertex_07004DA8, 0x004ac570, 12537, 0x00004da8, 256);

// 0x07004EA8 - 0x07004ED8
ROM_ASSET_LOAD_VTX(castle_courtyard_seg7_vertex_07004EA8, 0x004ac570, 12537, 0x00004ea8, 48);

// 0x07004ED8 - 0x07004FB0
static const Gfx castle_courtyard_seg7_dl_07004ED8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_courtyard_seg7_vertex_070049E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(castle_courtyard_seg7_vertex_07004AC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(castle_courtyard_seg7_vertex_07004BB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004FB0 - 0x07005060
static const Gfx castle_courtyard_seg7_dl_07004FB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_courtyard_seg7_vertex_07004CA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(castle_courtyard_seg7_vertex_07004DA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005060 - 0x07005078
static const Gfx castle_courtyard_seg7_dl_07005060[] = {
    gsSPVertex(castle_courtyard_seg7_vertex_07004EA8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005078 - 0x07005110
const Gfx castle_courtyard_seg7_dl_07005078[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_courtyard_seg7_dl_07004ED8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_courtyard_seg7_dl_07004FB0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(castle_courtyard_seg7_dl_07005060),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
