#include "pc/rom_assets.h"
// 0x0700F8B8 - 0x0700F8D0
static const Lights1 bbh_seg7_lights_0700F8B8 = gdSPDefLights1(
    0x65, 0x65, 0x38,
    0xfe, 0xfe, 0x8c, 0x28, 0x28, 0x28
);

// 0x0700F8D0 - 0x0700F8E8
static const Lights1 bbh_seg7_lights_0700F8D0 = gdSPDefLights1(
    0x20, 0x20, 0x20,
    0x50, 0x50, 0x50, 0x28, 0x28, 0x28
);

// 0x0700F8E8 - 0x0700F900
static const Lights1 bbh_seg7_lights_0700F8E8 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700F900 - 0x0700F918
static const Lights1 bbh_seg7_lights_0700F900 = gdSPDefLights1(
    0x33, 0x2c, 0x20,
    0x80, 0x70, 0x52, 0x28, 0x28, 0x28
);

// 0x0700F918 - 0x0700F9F8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700F918, 0x00371c40, 68724, 0x0000f918, 224);

// 0x0700F9F8 - 0x0700FA68
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700F9F8, 0x00371c40, 68724, 0x0000f9f8, 112);

// 0x0700FA68 - 0x0700FAE8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FA68, 0x00371c40, 68724, 0x0000fa68, 128);

// 0x0700FAE8 - 0x0700FBA8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FAE8, 0x00371c40, 68724, 0x0000fae8, 192);

// 0x0700FBA8 - 0x0700FBE8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FBA8, 0x00371c40, 68724, 0x0000fba8, 64);

// 0x0700FBE8 - 0x0700FCA8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FBE8, 0x00371c40, 68724, 0x0000fbe8, 192);

// 0x0700FCA8 - 0x0700FD68
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FCA8, 0x00371c40, 68724, 0x0000fca8, 192);

// 0x0700FD68 - 0x0700FE28
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FD68, 0x00371c40, 68724, 0x0000fd68, 192);

// 0x0700FE28 - 0x0700FF28
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FE28, 0x00371c40, 68724, 0x0000fe28, 256);

// 0x0700FF28 - 0x07010018
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700FF28, 0x00371c40, 68724, 0x0000ff28, 240);

// 0x07010018 - 0x070100C8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010018, 0x00371c40, 68724, 0x00010018, 176);

// 0x070100C8 - 0x070101A8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070100C8, 0x00371c40, 68724, 0x000100c8, 224);

// 0x070101A8 - 0x07010298
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070101A8, 0x00371c40, 68724, 0x000101a8, 240);

// 0x07010298 - 0x07010388
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010298, 0x00371c40, 68724, 0x00010298, 240);

// 0x07010388 - 0x07010478
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010388, 0x00371c40, 68724, 0x00010388, 240);

// 0x07010478 - 0x07010568
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010478, 0x00371c40, 68724, 0x00010478, 240);

// 0x07010568 - 0x07010668
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010568, 0x00371c40, 68724, 0x00010568, 256);

// 0x07010668 - 0x07010768
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010668, 0x00371c40, 68724, 0x00010668, 256);

// 0x07010768 - 0x07010858
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010768, 0x00371c40, 68724, 0x00010768, 240);

// 0x07010858 - 0x07010908
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010858, 0x00371c40, 68724, 0x00010858, 176);

// 0x07010908 - 0x07010988
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010908, 0x00371c40, 68724, 0x00010908, 128);

// 0x07010988 - 0x07010A08
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010988, 0x00371c40, 68724, 0x00010988, 128);

// 0x07010A08 - 0x07010A48
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07010A08, 0x00371c40, 68724, 0x00010a08, 64);

// 0x07010A48 - 0x07010B58
static const Gfx bbh_seg7_dl_07010A48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0700F8B8.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F8B8.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700F918, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  9,  7, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 13, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700F9F8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPLight(&bbh_seg7_lights_0700F8D0.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F8D0.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700FA68, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&bbh_seg7_lights_0700F8E8.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F8E8.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700FAE8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010B58 - 0x07010C30
static const Gfx bbh_seg7_dl_07010B58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0700F8B8.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F8B8.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700FBA8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&bbh_seg7_lights_0700F8E8.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F8E8.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700FBE8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPLight(&bbh_seg7_lights_0700F900.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F900.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700FCA8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010C30 - 0x07010D00
static const Gfx bbh_seg7_dl_07010C30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0700F8B8.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F8B8.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700FD68, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPLight(&bbh_seg7_lights_0700F8E8.l, 1),
    gsSPLight(&bbh_seg7_lights_0700F8E8.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700FE28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0,  6,  8, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010D00 - 0x07010D90
static const Gfx bbh_seg7_dl_07010D00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700FF28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010018, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010D90 - 0x07011058
static const Gfx bbh_seg7_dl_07010D90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070100C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 6,  1,  3, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12,  8, 11, 0x0, 12, 13,  8, 0x0),
    gsSPVertex(bbh_seg7_vertex_070101A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010298, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles(12, 10, 11, 0x0, 12, 11, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010388, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010478, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010568, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010668, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  9,  4,  6, 0x0),
    gsSP2Triangles( 9, 10,  4, 0x0, 11,  5, 12, 0x0),
    gsSP2Triangles(11,  8,  5, 0x0, 13, 11, 12, 0x0),
    gsSP2Triangles(13, 12, 10, 0x0,  9, 13, 10, 0x0),
    gsSP2Triangles( 9, 14, 13, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010768, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 8, 10, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07010858, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011058 - 0x070110A0
static const Gfx bbh_seg7_dl_07011058[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07010908, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070110A0 - 0x070110E8
static const Gfx bbh_seg7_dl_070110A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_07002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07010988, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070110E8 - 0x07011120
static const Gfx bbh_seg7_dl_070110E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07010A08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011120 - 0x07011228
const Gfx bbh_seg7_dl_07011120[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07010A48),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07010B58),
    gsSPDisplayList(bbh_seg7_dl_07010C30),
    gsSPDisplayList(bbh_seg7_dl_07010D00),
    gsSPDisplayList(bbh_seg7_dl_07010D90),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07011058),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070110A0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070110E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
