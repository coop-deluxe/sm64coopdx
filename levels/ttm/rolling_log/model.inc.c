#include "pc/rom_assets.h"
// 0x07011DE8 - 0x07011E00
static const Lights1 ttm_seg7_lights_07011DE8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07011E00 - 0x07011F00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011E00, 0x004d1910, 104662, 0x00011e00, 256);

// 0x07011F00 - 0x07011FF0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011F00, 0x004d1910, 104662, 0x00011f00, 240);

// 0x07011FF0 - 0x070120E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011FF0, 0x004d1910, 104662, 0x00011ff0, 240);

// 0x070120E0 - 0x07012120
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070120E0, 0x004d1910, 104662, 0x000120e0, 64);

// 0x07012120 - 0x070121B8
static const Gfx ttm_seg7_dl_07012120[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttm_seg7_texture_07002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07011DE8.l, 1),
    gsSPLight(&ttm_seg7_lights_07011DE8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07011E00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  9, 10, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0, 13, 11, 0x0,  0, 14, 13, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  0, 12, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x070121B8 - 0x07012270
static const Gfx ttm_seg7_dl_070121B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_07011F00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07011FF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_070120E0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012270 - 0x070122F0
const Gfx ttm_seg7_dl_07012270[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07012120),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_070121B8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
