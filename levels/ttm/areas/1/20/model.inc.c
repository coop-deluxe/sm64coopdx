#include "pc/rom_assets.h"
// 0x070111A0 - 0x070111B8
static const Lights1 ttm_seg7_lights_070111A0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070111B8 - 0x070111D0
static const Lights1 ttm_seg7_lights_070111B8 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x070111D0 - 0x070111E8
static const Lights1 ttm_seg7_lights_070111D0 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x070111E8 - 0x07011228
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070111E8, 0x004d1910, 104662, 0x000111e8, 64);

// 0x07011228 - 0x070112F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011228, 0x004d1910, 104662, 0x00011228, 208);

// 0x070112F8 - 0x07011378
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070112F8, 0x004d1910, 104662, 0x000112f8, 128);

// 0x07011378 - 0x070113F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011378, 0x004d1910, 104662, 0x00011378, 128);

// 0x070113F8 - 0x070114B8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070113F8, 0x004d1910, 104662, 0x000113f8, 192);

// 0x070114B8 - 0x070115B0
static const Gfx ttm_seg7_dl_070114B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_070111A0.l, 1),
    gsSPLight(&ttm_seg7_lights_070111A0.a, 2),
    gsSPVertex(ttm_seg7_vertex_070111E8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_070111B8.l, 1),
    gsSPLight(&ttm_seg7_lights_070111B8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07011228, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 0,  2, 12, 0x0),
    gsSPLight(&ttm_seg7_lights_070111D0.l, 1),
    gsSPLight(&ttm_seg7_lights_070111D0.a, 2),
    gsSPVertex(ttm_seg7_vertex_070112F8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_070111A0.l, 1),
    gsSPLight(&ttm_seg7_lights_070111A0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07011378, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070115B0 - 0x07011608
static const Gfx ttm_seg7_dl_070115B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_070113F8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011608 - 0x07011680
const Gfx ttm_seg7_dl_07011608[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_070114B8),
    gsSPDisplayList(ttm_seg7_dl_070115B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
