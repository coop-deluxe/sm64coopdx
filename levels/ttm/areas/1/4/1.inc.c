#include "pc/rom_assets.h"
// 0x0700AB70 - 0x0700AB88
static const Lights1 ttm_seg7_lights_0700AB70 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700AB88 - 0x0700AC78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700AB88, 0x004d1910, 104662, 0x0000ab88, 240);

// 0x0700AC78 - 0x0700AD78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700AC78, 0x004d1910, 104662, 0x0000ac78, 256);

// 0x0700AD78 - 0x0700AE58
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700AD78, 0x004d1910, 104662, 0x0000ad78, 224);

// 0x0700AE58 - 0x0700AF90
static const Gfx ttm_seg7_dl_0700AE58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700AB70.l, 1),
    gsSPLight(&ttm_seg7_lights_0700AB70.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700AB88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 12,  0, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 10,  0, 0x0, 13,  8, 10, 0x0),
    gsSP2Triangles( 0,  2, 13, 0x0, 13,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700AC78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 1,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700AD78, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AF90 - 0x0700AFF0
const Gfx ttm_seg7_dl_0700AF90[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700AE58),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
