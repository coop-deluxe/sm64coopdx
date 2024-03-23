#include "pc/rom_assets.h"
// 0x070318A0 - 0x070318B8
static const Lights1 inside_castle_seg7_lights_070318A0 = gdSPDefLights1(
    0x52, 0x52, 0x52,
    0xdd, 0xdd, 0xdd, 0x28, 0x28, 0x28
);

// 0x070318B8 - 0x070318D0
static const Lights1 inside_castle_seg7_lights_070318B8 = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070318D0 - 0x070319D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070318D0, 0x00396340, 232834, 0x000318d0, 256);

// 0x070319D0 - 0x07031AB0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070319D0, 0x00396340, 232834, 0x000319d0, 224);

// 0x07031AB0 - 0x07031B70
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07031AB0, 0x00396340, 232834, 0x00031ab0, 192);

// 0x07031B70 - 0x07031C70
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07031B70, 0x00396340, 232834, 0x00031b70, 256);

// 0x07031C70 - 0x07031D70
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07031C70, 0x00396340, 232834, 0x00031c70, 256);

// 0x07031D70 - 0x07031E60
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07031D70, 0x00396340, 232834, 0x00031d70, 240);

// 0x07031E60 - 0x07031F10
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07031E60, 0x00396340, 232834, 0x00031e60, 176);

// 0x07031F10 - 0x07032000
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07031F10, 0x00396340, 232834, 0x00031f10, 240);

// 0x07032000 - 0x070320F0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07032000, 0x00396340, 232834, 0x00032000, 240);

// 0x070320F0 - 0x070321F0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070320F0, 0x00396340, 232834, 0x000320f0, 256);

// 0x070321F0 - 0x070322F0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070321F0, 0x00396340, 232834, 0x000321f0, 256);

// 0x070322F0 - 0x070323F0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070322F0, 0x00396340, 232834, 0x000322f0, 256);

// 0x070323F0 - 0x07032430
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070323F0, 0x00396340, 232834, 0x000323f0, 64);

// 0x07032430 - 0x07032530
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07032430, 0x00396340, 232834, 0x00032430, 256);

// 0x07032530 - 0x07032630
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07032530, 0x00396340, 232834, 0x00032530, 256);

// 0x07032630 - 0x070326E0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07032630, 0x00396340, 232834, 0x00032630, 176);

// 0x070326E0 - 0x070327E0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070326E0, 0x00396340, 232834, 0x000326e0, 256);

// 0x070327E0 - 0x070328D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070327E0, 0x00396340, 232834, 0x000327e0, 240);

// 0x070328D0 - 0x070329C0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070328D0, 0x00396340, 232834, 0x000328d0, 240);

// 0x070329C0 - 0x07032A00
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070329C0, 0x00396340, 232834, 0x000329c0, 64);

// 0x07032A00 - 0x07032B18
static const Gfx inside_castle_seg7_dl_07032A00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_070318A0.l, 1),
    gsSPLight(&inside_castle_seg7_lights_070318A0.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070318D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPLight(&inside_castle_seg7_lights_070318B8.l, 1),
    gsSPLight(&inside_castle_seg7_lights_070318B8.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070319D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  3,  4, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07031AB0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07032B18 - 0x07032C18
static const Gfx inside_castle_seg7_dl_07032B18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07031B70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles( 7, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07031C70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07031D70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07031E60, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7, 10,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07032C18 - 0x07032DC8
static const Gfx inside_castle_seg7_dl_07032C18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07031F10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0,  9, 11, 14, 0x0),
    gsSP1Triangle( 9, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07032000, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0,  8, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070320F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070321F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  6,  5, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070322F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070323F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07032DC8 - 0x07032EC0
static const Gfx inside_castle_seg7_dl_07032DC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07032430, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07032530, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(10,  9, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07032630, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  3,  5,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07032EC0 - 0x07032FC0
static const Gfx inside_castle_seg7_dl_07032EC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070326E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070327E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070328D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070329C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07032FC0 - 0x07033068
const Gfx inside_castle_seg7_dl_07032FC0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07032A00),
    gsSPDisplayList(inside_castle_seg7_dl_07032B18),
    gsSPDisplayList(inside_castle_seg7_dl_07032C18),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07032DC8),
    gsSPDisplayList(inside_castle_seg7_dl_07032EC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
