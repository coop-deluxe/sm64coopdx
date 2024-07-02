#include "pc/rom_assets.h"
// 0x07013C58 - 0x07013C70
static const Lights1 bbh_seg7_lights_07013C58 = gdSPDefLights1(
    0x20, 0x20, 0x20,
    0x50, 0x50, 0x50, 0x28, 0x28, 0x28
);

// 0x07013C70 - 0x07013C88
static const Lights1 bbh_seg7_lights_07013C70 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07013C88 - 0x07013D08
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07013C88, 0x00371c40, 68724, 0x00013c88, 128);

// 0x07013D08 - 0x07013DC8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07013D08, 0x00371c40, 68724, 0x00013d08, 192);

// 0x07013DC8 - 0x07013E08
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07013DC8, 0x00371c40, 68724, 0x00013dc8, 64);

// 0x07013E08 - 0x07013E48
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07013E08, 0x00371c40, 68724, 0x00013e08, 64);

// 0x07013E48 - 0x07013F38
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07013E48, 0x00371c40, 68724, 0x00013e48, 240);

// 0x07013F38 - 0x07014028
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07013F38, 0x00371c40, 68724, 0x00013f38, 240);

// 0x07014028 - 0x07014088
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014028, 0x00371c40, 68724, 0x00014028, 96);

// 0x07014088 - 0x07014178
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014088, 0x00371c40, 68724, 0x00014088, 240);

// 0x07014178 - 0x07014268
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014178, 0x00371c40, 68724, 0x00014178, 240);

// 0x07014268 - 0x07014368
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014268, 0x00371c40, 68724, 0x00014268, 256);

// 0x07014368 - 0x07014458
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014368, 0x00371c40, 68724, 0x00014368, 240);

// 0x07014458 - 0x07014538
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014458, 0x00371c40, 68724, 0x00014458, 224);

// 0x07014538 - 0x07014638
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014538, 0x00371c40, 68724, 0x00014538, 256);

// 0x07014638 - 0x07014738
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014638, 0x00371c40, 68724, 0x00014638, 256);

// 0x07014738 - 0x07014838
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014738, 0x00371c40, 68724, 0x00014738, 256);

// 0x07014838 - 0x07014938
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014838, 0x00371c40, 68724, 0x00014838, 256);

// 0x07014938 - 0x07014A28
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014938, 0x00371c40, 68724, 0x00014938, 240);

// 0x07014A28 - 0x07014B28
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07014A28, 0x00371c40, 68724, 0x00014a28, 256);

// 0x07014B28 - 0x07014BC8
static const Gfx bbh_seg7_dl_07014B28[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07013C58.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C58.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013C88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&bbh_seg7_lights_07013C70.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C70.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013D08, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014BC8 - 0x07014C10
static const Gfx bbh_seg7_dl_07014BC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07013C58.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C58.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013DC8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014C10 - 0x07014C58
static const Gfx bbh_seg7_dl_07014C10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07013C70.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C70.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013E08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014C58 - 0x07014D10
static const Gfx bbh_seg7_dl_07014C58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07013E48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07013F38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014028, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014D10 - 0x07014FD8
static const Gfx bbh_seg7_dl_07014D10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07014088, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014178, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014268, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014368, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014458, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014538, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014638, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  9, 11, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014738, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014838, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  9, 15, 10, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014938, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  0,  2, 13, 0x0),
    gsSP1Triangle(10, 12, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014A28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014FD8 - 0x07015098
const Gfx bbh_seg7_dl_07014FD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07014B28),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07014BC8),
    gsSPDisplayList(bbh_seg7_dl_07014C10),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07014C58),
    gsSPDisplayList(bbh_seg7_dl_07014D10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
