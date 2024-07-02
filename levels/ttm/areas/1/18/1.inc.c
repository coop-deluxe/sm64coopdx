#include "pc/rom_assets.h"
// 0x0700FA90 - 0x0700FAA8
static const Lights1 ttm_seg7_lights_0700FA90 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700FAA8 - 0x0700FAC0
static const Lights1 ttm_seg7_lights_0700FAA8 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700FAC0 - 0x0700FAD8
static const Lights1 ttm_seg7_lights_0700FAC0 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700FAD8 - 0x0700FBB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700FAD8, 0x004d1910, 104662, 0x0000fad8, 224);

// 0x0700FBB8 - 0x0700FCB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700FBB8, 0x004d1910, 104662, 0x0000fbb8, 256);

// 0x0700FCB8 - 0x0700FD48
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700FCB8, 0x004d1910, 104662, 0x0000fcb8, 144);

// 0x0700FD48 - 0x0700FE38
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700FD48, 0x004d1910, 104662, 0x0000fd48, 240);

// 0x0700FE38 - 0x0700FF38
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700FE38, 0x004d1910, 104662, 0x0000fe38, 256);

// 0x0700FF38 - 0x0700FFF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700FF38, 0x004d1910, 104662, 0x0000ff38, 192);

// 0x0700FFF8 - 0x070100F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700FFF8, 0x004d1910, 104662, 0x0000fff8, 256);

// 0x070100F8 - 0x070101E8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070100F8, 0x004d1910, 104662, 0x000100f8, 240);

// 0x070101E8 - 0x07010278
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070101E8, 0x004d1910, 104662, 0x000101e8, 144);

// 0x07010278 - 0x07010378
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010278, 0x004d1910, 104662, 0x00010278, 256);

// 0x07010378 - 0x07010468
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010378, 0x004d1910, 104662, 0x00010378, 240);

// 0x07010468 - 0x070104A8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010468, 0x004d1910, 104662, 0x00010468, 64);

// 0x070104A8 - 0x07010568
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070104A8, 0x004d1910, 104662, 0x000104a8, 192);

// 0x07010568 - 0x07010638
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07010568, 0x004d1910, 104662, 0x00010568, 208);

// 0x07010638 - 0x07010830
static const Gfx ttm_seg7_dl_07010638[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700FA90.l, 1),
    gsSPLight(&ttm_seg7_lights_0700FA90.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700FAD8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700FBB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700FCB8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPLight(&ttm_seg7_lights_0700FAA8.l, 1),
    gsSPLight(&ttm_seg7_lights_0700FAA8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700FD48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700FE38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700FF38, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_0700FAC0.l, 1),
    gsSPLight(&ttm_seg7_lights_0700FAC0.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700FFF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_070100F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070101E8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010830 - 0x07010978
static const Gfx ttm_seg7_dl_07010830[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700FA90.l, 1),
    gsSPLight(&ttm_seg7_lights_0700FA90.a, 2),
    gsSPVertex(ttm_seg7_vertex_07010278, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07010378, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07010468, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_0700FAA8.l, 1),
    gsSPLight(&ttm_seg7_lights_0700FAA8.a, 2),
    gsSPVertex(ttm_seg7_vertex_070104A8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_0700FAC0.l, 1),
    gsSPLight(&ttm_seg7_lights_0700FAC0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07010568, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 0,  2, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010978 - 0x070109F0
const Gfx ttm_seg7_dl_07010978[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07010638),
    gsSPDisplayList(ttm_seg7_dl_07010830),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
