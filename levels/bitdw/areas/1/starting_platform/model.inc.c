#include "pc/rom_assets.h"
// 0x07002138 - 0x07002238
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07002138, 0x00454e00, 29021, 0x00002138, 256);

// 0x07002238 - 0x070022F8
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07002238, 0x00454e00, 29021, 0x00002238, 192);

// 0x070022F8 - 0x070023F8
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_070022F8, 0x00454e00, 29021, 0x000022f8, 256);

// 0x070023F8 - 0x070024F8
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_070023F8, 0x00454e00, 29021, 0x000023f8, 256);

// 0x070024F8 - 0x070025D8
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_070024F8, 0x00454e00, 29021, 0x000024f8, 224);

// 0x070025D8 - 0x07002658
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_070025D8, 0x00454e00, 29021, 0x000025d8, 128);

// 0x07002658 - 0x07002698
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07002658, 0x00454e00, 29021, 0x00002658, 64);

// 0x07002698 - 0x07002700
static const Gfx bitdw_seg7_dl_07002698[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07002138, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002700 - 0x07002758
static const Gfx bitdw_seg7_dl_07002700[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07002238, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002758 - 0x07002868
static const Gfx bitdw_seg7_dl_07002758[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_070022F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(13,  9, 14, 0x0,  9, 13, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_070023F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 6, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(14, 11, 15, 0x0, 11,  6, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_070024F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bitdw_seg7_vertex_070025D8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002868 - 0x070028A0
static const Gfx bitdw_seg7_dl_07002868[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07002658, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070028A0 - 0x07002928
const Gfx bitdw_seg7_dl_070028A0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitdw_seg7_dl_07002698),
    gsSPDisplayList(bitdw_seg7_dl_07002700),
    gsSPDisplayList(bitdw_seg7_dl_07002758),
    gsSPDisplayList(bitdw_seg7_dl_07002868),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
