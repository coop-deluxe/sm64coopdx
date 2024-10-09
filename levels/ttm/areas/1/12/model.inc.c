#include "pc/rom_assets.h"
// 0x0700CD88 - 0x0700CDA0
static const Lights1 ttm_seg7_lights_0700CD88 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700CDA0 - 0x0700CDB8
static const Lights1 ttm_seg7_lights_0700CDA0 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700CDB8 - 0x0700CDD0
static const Lights1 ttm_seg7_lights_0700CDB8 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700CDD0 - 0x0700CEC0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700CDD0, 0x004d1910, 104662, 0x0000cdd0, 240);

// 0x0700CEC0 - 0x0700CF00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700CEC0, 0x004d1910, 104662, 0x0000cec0, 64);

// 0x0700CF00 - 0x0700D000
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700CF00, 0x004d1910, 104662, 0x0000cf00, 256);

// 0x0700D000 - 0x0700D030
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D000, 0x004d1910, 104662, 0x0000d000, 48);

// 0x0700D030 - 0x0700D090
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D030, 0x004d1910, 104662, 0x0000d030, 96);

// 0x0700D090 - 0x0700D180
static const Gfx ttm_seg7_dl_0700D090[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700CD88.l, 1),
    gsSPLight(&ttm_seg7_lights_0700CD88.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700CDD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPLight(&ttm_seg7_lights_0700CDA0.l, 1),
    gsSPLight(&ttm_seg7_lights_0700CDA0.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700CEC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_0700CDB8.l, 1),
    gsSPLight(&ttm_seg7_lights_0700CDB8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700CF00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700D000, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D180 - 0x0700D1D8
static const Gfx ttm_seg7_dl_0700D180[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700CD88.l, 1),
    gsSPLight(&ttm_seg7_lights_0700CD88.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700D030, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  5,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D1D8 - 0x0700D250
const Gfx ttm_seg7_dl_0700D1D8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700D090),
    gsSPDisplayList(ttm_seg7_dl_0700D180),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
