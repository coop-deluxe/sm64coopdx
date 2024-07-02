#include "pc/rom_assets.h"
// 0x070193F0 - 0x070194F0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070193F0, 0x00437870, 75979, 0x00019228, 256);

// 0x070194F0 - 0x070195F0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070194F0, 0x00437870, 75979, 0x00019328, 256);

// 0x070195F0 - 0x070196F0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070195F0, 0x00437870, 75979, 0x00019428, 256);

// 0x070196F0 - 0x07019730
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070196F0, 0x00437870, 75979, 0x00019528, 64);

// 0x07019730 - 0x070197B0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07019730, 0x00437870, 75979, 0x00019568, 128);

// 0x070197B0 - 0x070198B0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070197B0, 0x00437870, 75979, 0x000195e8, 256);

// 0x070198B0 - 0x070198F0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070198B0, 0x00437870, 75979, 0x000196e8, 64);

// 0x070198F0 - 0x07019A10
static const Gfx rr_seg7_dl_070198F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_070193F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_070194F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_070195F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  4,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(10, 14, 13, 0x0, 10, 15, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_070196F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019A10 - 0x07019A58
static const Gfx rr_seg7_dl_07019A10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_07019730, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019A58 - 0x07019AC0
static const Gfx rr_seg7_dl_07019A58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_070197B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019AC0 - 0x07019AE0
static const Gfx rr_seg7_dl_07019AC0[] = {
    gsSPVertex(rr_seg7_vertex_070198B0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019AE0 - 0x07019B68
const Gfx rr_seg7_dl_07019AE0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(rr_seg7_dl_070198F0),
    gsSPDisplayList(rr_seg7_dl_07019A10),
    gsSPDisplayList(rr_seg7_dl_07019A58),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(rr_seg7_dl_07019AC0),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
