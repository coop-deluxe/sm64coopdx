#include "pc/rom_assets.h"
// 0x07025648 - 0x07025708
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07025648, 0x004784a0, 83204, 0x000255b8, 192);

// 0x07025708 - 0x07025808
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07025708, 0x004784a0, 83204, 0x00025678, 256);

// 0x07025808 - 0x070258F8
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07025808, 0x004784a0, 83204, 0x00025778, 240);

// 0x070258F8 - 0x07025970
static const Gfx lll_seg7_dl_070258F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_07025648, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 0,  6,  4, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  0, 10,  7, 0x0),
    gsSP2Triangles( 0, 11, 10, 0x0,  0,  2, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07025970 - 0x07025A48
static const Gfx lll_seg7_dl_07025970[] = {
    gsSPVertex(lll_seg7_vertex_07025708, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0, 11,  9, 10, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(lll_seg7_vertex_07025808, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  3,  4, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  5,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9,  7,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11,  9, 10, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07025A48 - 0x07025AC0
const Gfx lll_seg7_dl_07025A48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_dl_070258F8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(lll_seg7_dl_07025970),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
