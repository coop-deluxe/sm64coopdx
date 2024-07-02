#include "pc/rom_assets.h"
// 0x070096F8 - 0x070097F8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070096F8, 0x0044abc0, 39442, 0x000096f8, 256);

// 0x070097F8 - 0x070098D8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070097F8, 0x0044abc0, 39442, 0x000097f8, 224);

// 0x070098D8 - 0x070099B8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070098D8, 0x0044abc0, 39442, 0x000098d8, 224);

// 0x070099B8 - 0x07009AA8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070099B8, 0x0044abc0, 39442, 0x000099b8, 240);

// 0x07009AA8 - 0x07009B98
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07009AA8, 0x0044abc0, 39442, 0x00009aa8, 240);

// 0x07009B98 - 0x07009BC8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07009B98, 0x0044abc0, 39442, 0x00009b98, 48);

// 0x07009BC8 - 0x07009CB8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07009BC8, 0x0044abc0, 39442, 0x00009bc8, 240);

// 0x07009CB8 - 0x07009DA8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07009CB8, 0x0044abc0, 39442, 0x00009cb8, 240);

// 0x07009DA8 - 0x07009E98
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07009DA8, 0x0044abc0, 39442, 0x00009da8, 240);

// 0x07009E98 - 0x07009F88
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07009E98, 0x0044abc0, 39442, 0x00009e98, 240);

// 0x07009F88 - 0x07009FD8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07009F88, 0x0044abc0, 39442, 0x00009f88, 80);

// 0x07009FD8 - 0x0700A140
static const Gfx castle_grounds_seg7_dl_07009FD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_070096F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0,  2,  1, 15, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_070097F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_070098D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_070099B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07009AA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07009B98, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A140 - 0x0700A260
static const Gfx castle_grounds_seg7_dl_0700A140[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_07009BC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 12, 14, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07009CB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 12, 11, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07009DA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 12, 14, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07009E98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 12, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A260 - 0x0700A290
static const Gfx castle_grounds_seg7_dl_0700A260[] = {
    gsSPVertex(castle_grounds_seg7_vertex_07009F88, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  4,  1,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A290 - 0x0700A328
const Gfx castle_grounds_seg7_dl_0700A290[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_07009FD8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_0700A140),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(castle_grounds_seg7_dl_0700A260),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
