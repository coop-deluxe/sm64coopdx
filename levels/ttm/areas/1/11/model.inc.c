#include "pc/rom_assets.h"
// 0x0700CB60 - 0x0700CB78
static const Lights1 ttm_seg7_lights_0700CB60 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700CB78 - 0x0700CB90
static const Lights1 ttm_seg7_lights_0700CB78 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700CB90 - 0x0700CBF0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700CB90, 0x004d1910, 104662, 0x0000cb90, 96);

// 0x0700CBF0 - 0x0700CC20
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700CBF0, 0x004d1910, 104662, 0x0000cbf0, 48);

// 0x0700CC20 - 0x0700CC60
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700CC20, 0x004d1910, 104662, 0x0000cc20, 64);

// 0x0700CC60 - 0x0700CCC8
static const Gfx ttm_seg7_dl_0700CC60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700CB60.l, 1),
    gsSPLight(&ttm_seg7_lights_0700CB60.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700CB90, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0700CB78.l, 1),
    gsSPLight(&ttm_seg7_lights_0700CB78.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700CBF0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CCC8 - 0x0700CD10
static const Gfx ttm_seg7_dl_0700CCC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700CB60.l, 1),
    gsSPLight(&ttm_seg7_lights_0700CB60.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700CC20, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CD10 - 0x0700CD88
const Gfx ttm_seg7_dl_0700CD10[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700CC60),
    gsSPDisplayList(ttm_seg7_dl_0700CCC8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
