#include "pc/rom_assets.h"
// 0x07006670 - 0x07006770
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006670, 0x00454e00, 29021, 0x00006670, 256);

// 0x07006770 - 0x07006870
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006770, 0x00454e00, 29021, 0x00006770, 256);

// 0x07006870 - 0x07006970
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006870, 0x00454e00, 29021, 0x00006870, 256);

// 0x07006970 - 0x07006A70
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006970, 0x00454e00, 29021, 0x00006970, 256);

// 0x07006A70 - 0x07006B70
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006A70, 0x00454e00, 29021, 0x00006a70, 256);

// 0x07006B70 - 0x07006C70
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006B70, 0x00454e00, 29021, 0x00006b70, 256);

// 0x07006C70 - 0x07006D70
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006C70, 0x00454e00, 29021, 0x00006c70, 256);

// 0x07006D70 - 0x07006E50
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006D70, 0x00454e00, 29021, 0x00006d70, 224);

// 0x07006E50 - 0x07006F50
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006E50, 0x00454e00, 29021, 0x00006e50, 256);

// 0x07006F50 - 0x07007050
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07006F50, 0x00454e00, 29021, 0x00006f50, 256);

// 0x07007050 - 0x07007150
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007050, 0x00454e00, 29021, 0x00007050, 256);

// 0x07007150 - 0x07007210
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007150, 0x00454e00, 29021, 0x00007150, 192);

// 0x07007210 - 0x07007300
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007210, 0x00454e00, 29021, 0x00007210, 240);

// 0x07007300 - 0x070073F0
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007300, 0x00454e00, 29021, 0x00007300, 240);

// 0x070073F0 - 0x07007430
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_070073F0, 0x00454e00, 29021, 0x000073f0, 64);

// 0x07007430 - 0x07007530
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007430, 0x00454e00, 29021, 0x00007430, 256);

// 0x07007530 - 0x070075B0
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007530, 0x00454e00, 29021, 0x00007530, 128);

// 0x070075B0 - 0x07007810
static const Gfx bitdw_seg7_dl_070075B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bitdw_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07006670, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006770, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006870, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006970, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  6,  8, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006A70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles( 7, 12,  8, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006B70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  5,  7, 13, 0x0),
    gsSP2Triangles( 5, 13, 14, 0x0,  5, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006C70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006D70, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007810 - 0x07007940
static const Gfx bitdw_seg7_dl_07007810[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07006E50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07006F50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007050, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007150, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007940 - 0x07007A18
static const Gfx bitdw_seg7_dl_07007940[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07007210, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0,  9, 14, 10, 0x0),
    gsSP1Triangle( 9, 11, 12, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007300, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  2,  9,  0, 0x0),
    gsSP2Triangles( 0, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_070073F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007A18 - 0x07007AA8
static const Gfx bitdw_seg7_dl_07007A18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07007430, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007530, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007AA8 - 0x07007B30
const Gfx bitdw_seg7_dl_07007AA8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitdw_seg7_dl_070075B0),
    gsSPDisplayList(bitdw_seg7_dl_07007810),
    gsSPDisplayList(bitdw_seg7_dl_07007940),
    gsSPDisplayList(bitdw_seg7_dl_07007A18),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
