#include "pc/rom_assets.h"
// Wiggler Body

// 0x05005A30
ROM_ASSET_LOAD_TEXTURE(wiggler_seg5_texture_05005A30, "actors/wiggler/wiggler_segment_left_side.rgba16.inc.c", 0x00180bb0, 29674, 0x00005a30, 4096);

// 0x05006A30
ROM_ASSET_LOAD_TEXTURE(wiggler_seg5_texture_05006A30, "actors/wiggler/wiggler_segment_right_side.rgba16.inc.c", 0x00180bb0, 29674, 0x00006a30, 4096);

// 0x05007A30
ROM_ASSET_LOAD_TEXTURE(wiggler_seg5_texture_05007A30, "actors/wiggler/wiggler_eye.rgba16.inc.c", 0x00180bb0, 29674, 0x00007a30, 2048);

// 0x05008230
ROM_ASSET_LOAD_TEXTURE(wiggler_seg5_texture_05008230, "actors/wiggler/wiggler_flower.rgba16.inc.c", 0x00180bb0, 29674, 0x00008230, 2048);

// 0x05008A30
ROM_ASSET_LOAD_TEXTURE(wiggler_seg5_texture_05008A30, "actors/wiggler/wiggler_frown.rgba16.inc.c", 0x00180bb0, 29674, 0x00008a30, 2048);

// 0x05009230
ROM_ASSET_LOAD_TEXTURE(wiggler_seg5_texture_05009230, "actors/wiggler/wiggler_nose_left_side.rgba16.inc.c", 0x00180bb0, 29674, 0x00009230, 4096);

// 0x0500A230
ROM_ASSET_LOAD_TEXTURE(wiggler_seg5_texture_0500A230, "actors/wiggler/wiggler_nose_right_side.rgba16.inc.c", 0x00180bb0, 29674, 0x0000a230, 4096);

// 0x0500B230
static const Lights1 wiggler_seg5_lights_0500B230 = gdSPDefLights1(
    0x37, 0x00, 0x00,
    0xdf, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0500B248
static const Lights1 wiggler_seg5_lights_0500B248 = gdSPDefLights1(
    0x39, 0x11, 0x00,
    0xe7, 0x47, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 wiggler_body_lights_unused = gdSPDefLights1(
    0x3a, 0x22, 0x05,
    0xea, 0x8b, 0x16, 0x28, 0x28, 0x28
);

// 0x0500B278
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B278, 0x00180bb0, 29674, 0x0000b278, 256);

// 0x0500B378
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B378, 0x00180bb0, 29674, 0x0000b378, 256);

// 0x0500B478
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B478, 0x00180bb0, 29674, 0x0000b478, 256);

// 0x0500B578
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B578, 0x00180bb0, 29674, 0x0000b578, 64);

// 0x0500B5B8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B5B8, 0x00180bb0, 29674, 0x0000b5b8, 240);

// 0x0500B6A8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B6A8, 0x00180bb0, 29674, 0x0000b6a8, 240);

// 0x0500B798
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B798, 0x00180bb0, 29674, 0x0000b798, 256);

// 0x0500B898
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B898, 0x00180bb0, 29674, 0x0000b898, 256);

// 0x0500B998
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500B998, 0x00180bb0, 29674, 0x0000b998, 256);

// 0x0500BA98
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500BA98, 0x00180bb0, 29674, 0x0000b578, 64);

// 0x0500BAD8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500BAD8, 0x00180bb0, 29674, 0x0000bad8, 240);

// 0x0500BBC8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500BBC8, 0x00180bb0, 29674, 0x0000bbc8, 240);

// 0x0500BCB8 - 0x0500BE10
const Gfx wiggler_seg5_dl_0500BCB8[] = {
    gsSPLight(&wiggler_seg5_lights_0500B230.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500B230.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500B278, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500B378, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  6,  2,  5, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12,  8, 0x0),
    gsSP2Triangles( 9, 13,  7, 0x0, 10,  8,  6, 0x0),
    gsSP2Triangles(14, 13,  9, 0x0, 14,  9, 15, 0x0),
    gsSP2Triangles( 2,  7, 13, 0x0,  2, 13,  0, 0x0),
    gsSP2Triangles( 6,  4, 10, 0x0,  6,  5,  4, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500B478, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500B578, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BE10 - 0x0500BE98
const Gfx wiggler_seg5_dl_0500BE10[] = {
    gsSPLight(&wiggler_seg5_lights_0500B248.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500B248.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500B5B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BE98 - 0x0500BF20
const Gfx wiggler_seg5_dl_0500BE98[] = {
    gsSPLight(&wiggler_seg5_lights_0500B248.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500B248.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500B6A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BF20 - 0x0500C078
const Gfx wiggler_seg5_dl_0500BF20[] = {
    gsSPLight(&wiggler_seg5_lights_0500B230.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500B230.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500B798, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500B898, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  0,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 6, 13,  8, 0x0,  7,  9, 12, 0x0),
    gsSP2Triangles(14,  8, 13, 0x0, 14, 13, 15, 0x0),
    gsSP2Triangles( 2, 13,  6, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles(12,  3,  7, 0x0, 12,  4,  3, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500B998, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500BA98, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C078 - 0x0500C100
const Gfx wiggler_seg5_dl_0500C078[] = {
    gsSPLight(&wiggler_seg5_lights_0500B248.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500B248.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500BAD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C100 - 0x0500C188
const Gfx wiggler_seg5_dl_0500C100[] = {
    gsSPLight(&wiggler_seg5_lights_0500B248.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500B248.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500BBC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C188
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500C188, 0x00180bb0, 29674, 0x0000c188, 64);

// 0x0500C1C8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500C1C8, 0x00180bb0, 29674, 0x0000c1c8, 64);

// 0x0500C208 - 0x0500C240
const Gfx wiggler_seg5_dl_0500C208[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05005A30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500C188, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C240 - 0x0500C278
const Gfx wiggler_seg5_dl_0500C240[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05006A30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500C1C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C278 - 0x0500C2F0
const Gfx wiggler_seg5_dl_0500C278[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wiggler_seg5_dl_0500C208),
    gsSPDisplayList(wiggler_seg5_dl_0500C240),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
