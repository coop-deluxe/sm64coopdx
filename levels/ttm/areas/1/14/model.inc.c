#include "pc/rom_assets.h"
// 0x0700D700 - 0x0700D718
static const Lights1 ttm_seg7_lights_0700D700 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700D718 - 0x0700D730
static const Lights1 ttm_seg7_lights_0700D718 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700D730 - 0x0700D748
static const Lights1 ttm_seg7_lights_0700D730 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700D748 - 0x0700D848
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D748, 0x004d1910, 104662, 0x0000d748, 256);

// 0x0700D848 - 0x0700D938
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D848, 0x004d1910, 104662, 0x0000d848, 240);

// 0x0700D938 - 0x0700D9F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D938, 0x004d1910, 104662, 0x0000d938, 192);

// 0x0700D9F8 - 0x0700DAE8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700D9F8, 0x004d1910, 104662, 0x0000d9f8, 240);

// 0x0700DAE8 - 0x0700DBD8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700DAE8, 0x004d1910, 104662, 0x0000dae8, 240);

// 0x0700DBD8 - 0x0700DCC8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700DBD8, 0x004d1910, 104662, 0x0000dbd8, 240);

// 0x0700DCC8 - 0x0700DD28
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700DCC8, 0x004d1910, 104662, 0x0000dcc8, 96);

// 0x0700DD28 - 0x0700DD88
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700DD28, 0x004d1910, 104662, 0x0000dd28, 96);

// 0x0700DD88 - 0x0700DDB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700DD88, 0x004d1910, 104662, 0x0000dd88, 48);

// 0x0700DDB8 - 0x0700DF78
static const Gfx ttm_seg7_dl_0700DDB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700D700.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D700.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700D748, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700D848, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700D938, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_0700D718.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D718.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700D9F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700DAE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700DBD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700DCC8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0700D730.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D730.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700DD28, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0700D700.l, 1),
    gsSPLight(&ttm_seg7_lights_0700D700.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700DD88, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DF78 - 0x0700DFE8
const Gfx ttm_seg7_dl_0700DF78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700DDB8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
