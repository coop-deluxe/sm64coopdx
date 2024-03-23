#include "pc/rom_assets.h"
// 0x07004630 - 0x07004720
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004630, 0x00454e00, 29021, 0x00004630, 240);

// 0x07004720 - 0x07004810
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004720, 0x00454e00, 29021, 0x00004720, 240);

// 0x07004810 - 0x07004910
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004810, 0x00454e00, 29021, 0x00004810, 256);

// 0x07004910 - 0x07004A00
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004910, 0x00454e00, 29021, 0x00004910, 240);

// 0x07004A00 - 0x07004B00
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004A00, 0x00454e00, 29021, 0x00004a00, 256);

// 0x07004B00 - 0x07004B80
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004B00, 0x00454e00, 29021, 0x00004b00, 128);

// 0x07004B80 - 0x07004C80
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004B80, 0x00454e00, 29021, 0x00004b80, 256);

// 0x07004C80 - 0x07004D80
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004C80, 0x00454e00, 29021, 0x00004c80, 256);

// 0x07004D80 - 0x07004DC0
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07004D80, 0x00454e00, 29021, 0x00004d80, 64);

// 0x07004DC0 - 0x07004F70
static const Gfx bitdw_seg7_dl_07004DC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bitdw_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07004630, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07004720, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07004810, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07004910, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07004A00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  8, 11, 10, 0x0),
    gsSP2Triangles(11,  8,  7, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07004B00, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  3,  7,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004F70 - 0x07004FF8
static const Gfx bitdw_seg7_dl_07004F70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07004B80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 11, 14, 10, 0x0),
    gsSP2Triangles(14, 12, 10, 0x0, 13, 15, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004FF8 - 0x07005078
static const Gfx bitdw_seg7_dl_07004FF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07004C80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07004D80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005078 - 0x070050F8
const Gfx bitdw_seg7_dl_07005078[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitdw_seg7_dl_07004DC0),
    gsSPDisplayList(bitdw_seg7_dl_07004F70),
    gsSPDisplayList(bitdw_seg7_dl_07004FF8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
