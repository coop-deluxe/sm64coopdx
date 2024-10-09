#include "pc/rom_assets.h"
// 0x0700A020 - 0x0700A038
static const Lights1 ssl_seg7_lights_0700A020 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700A038 - 0x0700A138
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A038, 0x003e76b0, 82641, 0x0000a038, 256);

// 0x0700A138 - 0x0700A238
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A138, 0x003e76b0, 82641, 0x0000a138, 256);

// 0x0700A238 - 0x0700A328
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A238, 0x003e76b0, 82641, 0x0000a238, 240);

// 0x0700A328 - 0x0700A408
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A328, 0x003e76b0, 82641, 0x0000a328, 224);

// 0x0700A408 - 0x0700A4F8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A408, 0x003e76b0, 82641, 0x0000a408, 240);

// 0x0700A4F8 - 0x0700A5E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A4F8, 0x003e76b0, 82641, 0x0000a4f8, 240);

// 0x0700A5E8 - 0x0700A6E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A5E8, 0x003e76b0, 82641, 0x0000a5e8, 256);

// 0x0700A6E8 - 0x0700A7E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A6E8, 0x003e76b0, 82641, 0x0000a6e8, 256);

// 0x0700A7E8 - 0x0700A8E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A7E8, 0x003e76b0, 82641, 0x0000a7e8, 256);

// 0x0700A8E8 - 0x0700A9E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A8E8, 0x003e76b0, 82641, 0x0000a8e8, 256);

// 0x0700A9E8 - 0x0700AAD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700A9E8, 0x003e76b0, 82641, 0x0000a9e8, 240);

// 0x0700AAD8 - 0x0700ABD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700AAD8, 0x003e76b0, 82641, 0x0000aad8, 256);

// 0x0700ABD8 - 0x0700ACC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700ABD8, 0x003e76b0, 82641, 0x0000abd8, 240);

// 0x0700ACC8 - 0x0700ADB8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700ACC8, 0x003e76b0, 82641, 0x0000acc8, 240);

// 0x0700ADB8 - 0x0700AEA8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700ADB8, 0x003e76b0, 82641, 0x0000adb8, 240);

// 0x0700AEA8 - 0x0700AF98
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700AEA8, 0x003e76b0, 82641, 0x0000aea8, 240);

// 0x0700AF98 - 0x0700B098
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700AF98, 0x003e76b0, 82641, 0x0000af98, 256);

// 0x0700B098 - 0x0700B178
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700B098, 0x003e76b0, 82641, 0x0000b098, 224);

// 0x0700B178 - 0x0700B278
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700B178, 0x003e76b0, 82641, 0x0000b178, 256);

// 0x0700B278 - 0x0700B2E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0700B278, 0x003e76b0, 82641, 0x0000b278, 112);

// 0x0700B2E8 - 0x0700BA78
static const Gfx ssl_seg7_dl_0700B2E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_0700A020.l, 1),
    gsSPLight(&ssl_seg7_lights_0700A020.a, 2),
    gsSPVertex(ssl_seg7_vertex_0700A038, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 1,  3, 10, 0x0, 11,  1, 12, 0x0),
    gsSP2Triangles( 3,  5, 13, 0x0, 11, 12, 14, 0x0),
    gsSP2Triangles(13, 15, 14, 0x0, 13, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A138, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0, 10,  8,  5, 0x0),
    gsSP2Triangles( 5,  4, 11, 0x0, 10,  5, 11, 0x0),
    gsSP2Triangles( 5, 12,  6, 0x0,  5, 13, 12, 0x0),
    gsSP2Triangles( 5,  9, 13, 0x0,  7,  6, 14, 0x0),
    gsSP2Triangles( 6, 12, 14, 0x0,  7, 14, 12, 0x0),
    gsSP1Triangle(15,  7, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A238, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 10, 13, 12, 0x0),
    gsSP2Triangles( 3, 12,  4, 0x0, 12, 14,  4, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  4, 14,  9, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A328, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles( 4,  9,  8, 0x0,  3,  5, 10, 0x0),
    gsSP2Triangles( 5, 11, 10, 0x0,  5, 12, 11, 0x0),
    gsSP1Triangle( 3, 10, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A408, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 8,  3,  7, 0x0,  7,  5,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8, 12, 10, 0x0),
    gsSP2Triangles( 8,  7, 12, 0x0, 13, 10, 12, 0x0),
    gsSP2Triangles(12,  9, 14, 0x0, 12,  7,  9, 0x0),
    gsSP1Triangle(13, 12, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A4F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 7,  5,  0, 0x0,  2,  8,  0, 0x0),
    gsSP2Triangles( 8,  7,  0, 0x0,  4,  0,  9, 0x0),
    gsSP2Triangles( 0,  6,  9, 0x0, 10,  1, 11, 0x0),
    gsSP2Triangles(10,  2,  1, 0x0, 11,  1,  3, 0x0),
    gsSP2Triangles( 8,  2, 10, 0x0, 12,  3, 13, 0x0),
    gsSP2Triangles(14, 11,  3, 0x0, 14,  3, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A5E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  6,  0,  5, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  0,  6, 10, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles(11,  6,  9, 0x0, 10,  6, 12, 0x0),
    gsSP2Triangles(13,  1, 10, 0x0, 13, 10, 12, 0x0),
    gsSP2Triangles( 1, 14, 15, 0x0,  2,  1, 15, 0x0),
    gsSP2Triangles(13, 14,  1, 0x0, 14,  2, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A6E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  0, 0x0, 12, 10,  0, 0x0),
    gsSP2Triangles( 0,  7, 13, 0x0,  0, 14,  7, 0x0),
    gsSP2Triangles(14,  0, 11, 0x0,  0, 13,  1, 0x0),
    gsSP2Triangles( 9,  1, 13, 0x0,  1,  9, 15, 0x0),
    gsSP1Triangle( 1, 15,  3, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A7E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 4, 11,  1, 0x0, 11, 12,  1, 0x0),
    gsSP2Triangles( 4, 13, 14, 0x0, 14, 15,  4, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A8E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700A9E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0, 12,  6, 11, 0x0),
    gsSP2Triangles( 7, 13,  8, 0x0, 14,  4,  3, 0x0),
    gsSP1Triangle(12, 14,  3, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700AAD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  8,  6,  3, 0x0),
    gsSP2Triangles( 7,  9,  3, 0x0,  9,  2,  3, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 14,  8, 0x0, 14,  6,  8, 0x0),
    gsSP1Triangle(15, 10, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700ABD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(12, 11,  9, 0x0, 13, 12,  9, 0x0),
    gsSP2Triangles(14, 13,  9, 0x0,  8, 14,  9, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700ACC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700ADB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 2,  6,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 4, 12, 13, 0x0,  4, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700AEA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700AF98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700B098, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 2,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles(12, 10,  7, 0x0, 12, 13,  2, 0x0),
    gsSP1Triangle(13,  6,  2, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700B178, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12,  5, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles( 4, 11,  5, 0x0,  5, 12,  2, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0700B278, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  6,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BA78 - 0x0700BAD8
const Gfx ssl_seg7_dl_0700BA78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_0700B2E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
