#include "pc/rom_assets.h"
// 0x07011680 - 0x07011698
static const Lights1 ttm_seg7_lights_07011680 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07011698 - 0x070116B0
static const Lights1 ttm_seg7_lights_07011698 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x070116B0 - 0x070116C8
static const Lights1 ttm_seg7_lights_070116B0 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x070116C8 - 0x070117C8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070116C8, 0x004d1910, 104662, 0x000116c8, 256);

// 0x070117C8 - 0x07011808
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070117C8, 0x004d1910, 104662, 0x000117c8, 64);

// 0x07011808 - 0x070118F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011808, 0x004d1910, 104662, 0x00011808, 240);

// 0x070118F8 - 0x070119F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070118F8, 0x004d1910, 104662, 0x000118f8, 256);

// 0x070119F8 - 0x07011A28
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070119F8, 0x004d1910, 104662, 0x000119f8, 48);

// 0x07011A28 - 0x07011A68
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011A28, 0x004d1910, 104662, 0x00011a28, 64);

// 0x07011A68 - 0x07011AA8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07011A68, 0x004d1910, 104662, 0x00011a68, 64);

// 0x07011AA8 - 0x07011B20
static const Gfx ttm_seg7_dl_07011AA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07011680.l, 1),
    gsSPLight(&ttm_seg7_lights_07011680.a, 2),
    gsSPVertex(ttm_seg7_vertex_070116C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011B20 - 0x07011C10
static const Gfx ttm_seg7_dl_07011B20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_070117C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07011698.l, 1),
    gsSPLight(&ttm_seg7_lights_07011698.a, 2),
    gsSPVertex(ttm_seg7_vertex_07011808, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  7, 11, 12, 0x0),
    gsSP2Triangles( 7, 12, 10, 0x0,  8, 13,  9, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070118F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 10,  7, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070119F8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011C10 - 0x07011C48
static const Gfx ttm_seg7_dl_07011C10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_07011A28, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011C48 - 0x07011C78
static const Gfx ttm_seg7_dl_07011C48[] = {
    gsSPLight(&ttm_seg7_lights_070116B0.l, 1),
    gsSPLight(&ttm_seg7_lights_070116B0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07011A68, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011C78 - 0x07011D00
const Gfx ttm_seg7_dl_07011C78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07011AA8),
    gsSPDisplayList(ttm_seg7_dl_07011B20),
    gsSPDisplayList(ttm_seg7_dl_07011C10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(ttm_seg7_dl_07011C48),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
