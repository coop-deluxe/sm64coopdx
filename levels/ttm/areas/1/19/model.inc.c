#include "pc/rom_assets.h"
// 0x07010AD8 - 0x07010AF0
static const Lights1 ttm_seg7_lights_07010AD8 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07010AF0 - 0x07010B08
static const Lights1 ttm_seg7_lights_07010AF0 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x07010B08 - 0x07010B20
static const Lights1 ttm_seg7_lights_07010B08 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07010B20 - 0x07010C10
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010B20, 0x004d1910, 104662, 0x00010b20, 240);

// 0x07010C10 - 0x07010C40
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010C10, 0x004d1910, 104662, 0x00010c10, 48);

// 0x07010C40 - 0x07010D30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010C40, 0x004d1910, 104662, 0x00010c40, 240);

// 0x07010D30 - 0x07010D60
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010D30, 0x004d1910, 104662, 0x00010d30, 48);

// 0x07010D60 - 0x07010DA0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010D60, 0x004d1910, 104662, 0x00010d60, 64);

// 0x07010DA0 - 0x07010E00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010DA0, 0x004d1910, 104662, 0x00010da0, 96);

// 0x07010E00 - 0x07010F00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010E00, 0x004d1910, 104662, 0x00010e00, 256);

// 0x07010F00 - 0x07010F90
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010F00, 0x004d1910, 104662, 0x00010f00, 144);

// 0x07010F90 - 0x07011078
static const Gfx ttm_seg7_dl_07010F90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07010AD8.l, 1),
    gsSPLight(&ttm_seg7_lights_07010AD8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07010B20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07010C10, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_07010AF0.l, 1),
    gsSPLight(&ttm_seg7_lights_07010AF0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07010C40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07010D30, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_07010B08.l, 1),
    gsSPLight(&ttm_seg7_lights_07010B08.a, 2),
    gsSPVertex(ttm_seg7_vertex_07010D60, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011078 - 0x07011128
static const Gfx ttm_seg7_dl_07011078[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07010AD8.l, 1),
    gsSPLight(&ttm_seg7_lights_07010AD8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07010DA0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_07010B08.l, 1),
    gsSPLight(&ttm_seg7_lights_07010B08.a, 2),
    gsSPVertex(ttm_seg7_vertex_07010E00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  6,  8, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07010F00, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011128 - 0x070111A0
const Gfx ttm_seg7_dl_07011128[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07010F90),
    gsSPDisplayList(ttm_seg7_dl_07011078),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
