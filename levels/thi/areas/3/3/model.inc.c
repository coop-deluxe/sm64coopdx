#include "pc/rom_assets.h"
// 0x07009740 - 0x07009820
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07009740, 0x004246d0, 32780, 0x00009740, 224);

// 0x07009820 - 0x070098D0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07009820, 0x004246d0, 32780, 0x00009820, 176);

// 0x070098D0 - 0x070099C0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070098D0, 0x004246d0, 32780, 0x000098d0, 240);

// 0x070099C0 - 0x07009AB0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070099C0, 0x004246d0, 32780, 0x000099c0, 240);

// 0x07009AB0 - 0x07009AF0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07009AB0, 0x004246d0, 32780, 0x00009ab0, 64);

// 0x07009AF0 - 0x07009B30
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07009AF0, 0x004246d0, 32780, 0x00009af0, 64);

// 0x07009B30 - 0x07009B70
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07009B30, 0x004246d0, 32780, 0x00009b30, 64);

// 0x07009B70 - 0x07009C40
static const Gfx thi_seg7_dl_07009B70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_0900B800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_07009740, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  9, 0x0,  9,  7,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11,  0, 12, 0x0),
    gsSP2Triangles(12,  0, 13, 0x0, 11,  1,  0, 0x0),
    gsSP1Triangle( 0,  2, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07009820, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  3, 0x0,  9,  8,  7, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009C40 - 0x07009CF8
static const Gfx thi_seg7_dl_07009C40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, thi_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_070098D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_070099C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07009AB0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009CF8 - 0x07009D30
static const Gfx thi_seg7_dl_07009CF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_07009AF0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009D30 - 0x07009D50
static const Gfx thi_seg7_dl_07009D30[] = {
    gsSPVertex(thi_seg7_vertex_07009B30, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009D50 - 0x07009DF0
const Gfx thi_seg7_dl_07009D50[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07009B70),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07009C40),
    gsSPDisplayList(thi_seg7_dl_07009CF8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(thi_seg7_dl_07009D30),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
