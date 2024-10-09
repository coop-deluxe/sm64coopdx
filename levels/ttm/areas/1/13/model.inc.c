#include "pc/rom_assets.h"
// 0x0700D250 - 0x0700D268
static const Lights1 ttm_seg7_lights_0700D250 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700D268 - 0x0700D280
static const Lights1 ttm_seg7_lights_0700D268 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700D280 - 0x0700D298
static const Lights1 ttm_seg7_lights_0700D280 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700D298 - 0x0700D398
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D298, 0x004d1910, 104662, 0x0000d298, 256);

// 0x0700D398 - 0x0700D438
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D398, 0x004d1910, 104662, 0x0000d398, 160);

// 0x0700D438 - 0x0700D498
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D438, 0x004d1910, 104662, 0x0000d438, 96);

// 0x0700D498 - 0x0700D508
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D498, 0x004d1910, 104662, 0x0000d498, 112);

// 0x0700D508 - 0x0700D548
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D508, 0x004d1910, 104662, 0x0000d508, 64);

// 0x0700D548 - 0x0700D640
static const Gfx ttm_seg7_dl_0700D548[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700D250.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D250.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700D298, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700D398, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  5,  9, 0x0),
    gsSPLight(&ttm_seg7_lights_0700D268.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D268.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700D438, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  0,  2,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0700D280.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D280.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700D498, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D640 - 0x0700D688
static const Gfx ttm_seg7_dl_0700D640[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700D250.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D250.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700D508, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D688 - 0x0700D700
const Gfx ttm_seg7_dl_0700D688[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700D548),
    gsSPDisplayList(ttm_seg7_dl_0700D640),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
