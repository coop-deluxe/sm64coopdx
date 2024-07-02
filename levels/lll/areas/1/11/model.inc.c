#include "pc/rom_assets.h"
// 0x07016658 - 0x07016670
static const Lights1 lll_seg7_lights_07016658 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07016670 - 0x07016770
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07016670, 0x004784a0, 83204, 0x00016670, 256);

// 0x07016770 - 0x070167F0
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07016770, 0x004784a0, 83204, 0x00016770, 128);

// 0x070167F0 - 0x07016850
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_070167F0, 0x004784a0, 83204, 0x000167f0, 96);

// 0x07016850 - 0x07016930
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07016850, 0x004784a0, 83204, 0x00016850, 224);

// 0x07016930 - 0x07016A30
static const Gfx lll_seg7_dl_07016930[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_07016658.l, 1),
    gsSPLight(&lll_seg7_lights_07016658.a, 2),
    gsSPVertex(lll_seg7_vertex_07016670, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  5,  2,  6, 0x0),
    gsSP2Triangles( 1,  3,  2, 0x0,  2,  4,  7, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 4,  9, 10, 0x0,  3,  8,  4, 0x0),
    gsSP2Triangles( 7,  4, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  0, 0x0, 12,  0,  5, 0x0),
    gsSP2Triangles( 0, 14,  1, 0x0,  0, 13, 14, 0x0),
    gsSP2Triangles(13, 15, 14, 0x0, 15, 13, 12, 0x0),
    gsSPVertex(lll_seg7_vertex_07016770, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  6,  1, 0x0,  7,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016A30 - 0x07016A78
static const Gfx lll_seg7_dl_07016A30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_070167F0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016A78 - 0x07016B00
static const Gfx lll_seg7_dl_07016A78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_07016850, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 3,  2,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(12, 11,  5, 0x0, 12,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016B00 - 0x07016B70
const Gfx lll_seg7_dl_07016B00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_dl_07016930),
    gsSPDisplayList(lll_seg7_dl_07016A30),
    gsSPDisplayList(lll_seg7_dl_07016A78),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
