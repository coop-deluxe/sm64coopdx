#include "pc/rom_assets.h"
// 0x07057380 - 0x07057398
static const Lights1 inside_castle_seg7_lights_07057380 = gdSPDefLights1(
    0x51, 0x34, 0x42,
    0xd8, 0x8c, 0xb2, 0x28, 0x28, 0x28
);

// 0x07057398 - 0x070573B0
static const Lights1 inside_castle_seg7_lights_07057398 = gdSPDefLights1(
    0x40, 0x24, 0x1e,
    0xac, 0x61, 0x52, 0x28, 0x28, 0x28
);

// 0x070573B0 - 0x070573F0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070573B0, 0x00396340, 232834, 0x000573b0, 64);

// 0x070573F0 - 0x070574B0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070573F0, 0x00396340, 232834, 0x000573f0, 192);

// 0x070574B0 - 0x070575A0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070574B0, 0x00396340, 232834, 0x000574b0, 240);

// 0x070575A0 - 0x070576A0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070575A0, 0x00396340, 232834, 0x000575a0, 256);

// 0x070576A0 - 0x07057790
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070576A0, 0x00396340, 232834, 0x000576a0, 240);

// 0x07057790 - 0x070577D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07057790, 0x00396340, 232834, 0x00057790, 64);

// 0x070577D0 - 0x07057850
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070577D0, 0x00396340, 232834, 0x000577d0, 128);

// 0x07057850 - 0x070578D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07057850, 0x00396340, 232834, 0x00057850, 128);

// 0x070578D0 - 0x07057950
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070578D0, 0x00396340, 232834, 0x000578d0, 128);

// 0x07057950 - 0x070579D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07057950, 0x00396340, 232834, 0x00057950, 128);

// 0x070579D0 - 0x07057AC0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070579D0, 0x00396340, 232834, 0x000579d0, 240);

// 0x07057AC0 - 0x07057B70
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07057AC0, 0x00396340, 232834, 0x00057ac0, 176);

// 0x07057B70 - 0x07057BB8
static const Gfx inside_castle_seg7_dl_07057B70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07057380.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07057380.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070573B0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057BB8 - 0x07057C20
static const Gfx inside_castle_seg7_dl_07057BB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070573F0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  0, 10,  3, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0, 10, 11,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057C20 - 0x07057D30
static const Gfx inside_castle_seg7_dl_07057C20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070574B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0, 12, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070575A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070576A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07057790, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057D30 - 0x07057D88
static const Gfx inside_castle_seg7_dl_07057D30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_07008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07057398.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07057398.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070577D0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057D88 - 0x07057DD0
static const Gfx inside_castle_seg7_dl_07057D88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_07008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07057850, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057DD0 - 0x07057E18
static const Gfx inside_castle_seg7_dl_07057DD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_07009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070578D0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057E18 - 0x07057E60
static const Gfx inside_castle_seg7_dl_07057E18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_07009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07057950, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057E60 - 0x07057F00
static const Gfx inside_castle_seg7_dl_07057E60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07057380.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07057380.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070579D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07057AC0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07057F00 - 0x07057FD8
const Gfx inside_castle_seg7_dl_07057F00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07057B70),
    gsSPDisplayList(inside_castle_seg7_dl_07057BB8),
    gsSPDisplayList(inside_castle_seg7_dl_07057C20),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07057D30),
    gsSPDisplayList(inside_castle_seg7_dl_07057D88),
    gsSPDisplayList(inside_castle_seg7_dl_07057DD0),
    gsSPDisplayList(inside_castle_seg7_dl_07057E18),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07057E60),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
