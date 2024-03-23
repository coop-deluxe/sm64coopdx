#include "pc/rom_assets.h"
// 0x0700E378 - 0x0700E390
static const Lights1 ttm_seg7_lights_0700E378 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700E390 - 0x0700E3A8
static const Lights1 ttm_seg7_lights_0700E390 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700E3A8 - 0x0700E3C0
static const Lights1 ttm_seg7_lights_0700E3A8 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0700E3C0 - 0x0700E4B0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E3C0, 0x004d1910, 104662, 0x0000e3c0, 240);

// 0x0700E4B0 - 0x0700E590
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E4B0, 0x004d1910, 104662, 0x0000e4b0, 224);

// 0x0700E590 - 0x0700E680
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E590, 0x004d1910, 104662, 0x0000e590, 240);

// 0x0700E680 - 0x0700E6E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E680, 0x004d1910, 104662, 0x0000e680, 96);

// 0x0700E6E0 - 0x0700E720
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E6E0, 0x004d1910, 104662, 0x0000e6e0, 64);

// 0x0700E720 - 0x0700E820
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E720, 0x004d1910, 104662, 0x0000e720, 256);

// 0x0700E820 - 0x0700E8B0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E820, 0x004d1910, 104662, 0x0000e820, 144);

// 0x0700E8B0 - 0x0700E910
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700E8B0, 0x004d1910, 104662, 0x0000e8b0, 96);

// 0x0700E910 - 0x0700EA28
static const Gfx ttm_seg7_dl_0700E910[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700E378.l, 1),
    gsSPLight(&ttm_seg7_lights_0700E378.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700E3C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700E4B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700E590, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPLight(&ttm_seg7_lights_0700E390.l, 1),
    gsSPLight(&ttm_seg7_lights_0700E390.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700E680, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0700E378.l, 1),
    gsSPLight(&ttm_seg7_lights_0700E378.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700E6E0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EA28 - 0x0700EAC8
static const Gfx ttm_seg7_dl_0700EA28[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_0700E720, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  4,  3,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700E820, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPLight(&ttm_seg7_lights_0700E3A8.l, 1),
    gsSPLight(&ttm_seg7_lights_0700E3A8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700E8B0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EAC8 - 0x0700EB40
const Gfx ttm_seg7_dl_0700EAC8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700E910),
    gsSPDisplayList(ttm_seg7_dl_0700EA28),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
