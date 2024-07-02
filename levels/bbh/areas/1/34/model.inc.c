#include "pc/rom_assets.h"
// 0x0701A920 - 0x0701A938
static const Lights1 bbh_seg7_lights_0701A920 = gdSPDefLights1(
    0x10, 0x11, 0x16,
    0x2a, 0x2c, 0x37, 0x28, 0x28, 0x28
);

// 0x0701A938 - 0x0701A950
static const Lights1 bbh_seg7_lights_0701A938 = gdSPDefLights1(
    0x3c, 0x3c, 0x3c,
    0x96, 0x96, 0x96, 0x28, 0x28, 0x28
);

// 0x0701A950 - 0x0701A968
static const Lights1 bbh_seg7_lights_0701A950 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701A968 - 0x0701A9C8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701A968, 0x00371c40, 68724, 0x0001a968, 96);

// 0x0701A9C8 - 0x0701AA08
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701A9C8, 0x00371c40, 68724, 0x0001a9c8, 64);

// 0x0701AA08 - 0x0701AB08
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701AA08, 0x00371c40, 68724, 0x0001aa08, 256);

// 0x0701AB08 - 0x0701ABE8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701AB08, 0x00371c40, 68724, 0x0001ab08, 224);

// 0x0701ABE8 - 0x0701ACD8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701ABE8, 0x00371c40, 68724, 0x0001abe8, 240);

// 0x0701ACD8 - 0x0701ADD8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701ACD8, 0x00371c40, 68724, 0x0001acd8, 256);

// 0x0701ADD8 - 0x0701AED8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701ADD8, 0x00371c40, 68724, 0x0001add8, 256);

// 0x0701AED8 - 0x0701AF48
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701AED8, 0x00371c40, 68724, 0x0001aed8, 112);

// 0x0701AF48 - 0x0701B048
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701AF48, 0x00371c40, 68724, 0x0001af48, 256);

// 0x0701B048 - 0x0701B148
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701B048, 0x00371c40, 68724, 0x0001b048, 256);

// 0x0701B148 - 0x0701B1E8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701B148, 0x00371c40, 68724, 0x0001b148, 160);

// 0x0701B1E8 - 0x0701B2A8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701B1E8, 0x00371c40, 68724, 0x0001b1e8, 192);

// 0x0701B2A8 - 0x0701B328
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701B2A8, 0x00371c40, 68724, 0x0001b2a8, 128);

// 0x0701B328 - 0x0701B380
static const Gfx bbh_seg7_dl_0701B328[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0701A920.l, 1),
    gsSPLight(&bbh_seg7_lights_0701A920.a, 2),
    gsSPVertex(bbh_seg7_vertex_0701A968, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701B380 - 0x0701B558
static const Gfx bbh_seg7_dl_0701B380[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0701A938.l, 1),
    gsSPLight(&bbh_seg7_lights_0701A938.a, 2),
    gsSPVertex(bbh_seg7_vertex_0701A9C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&bbh_seg7_lights_0701A950.l, 1),
    gsSPLight(&bbh_seg7_lights_0701A950.a, 2),
    gsSPVertex(bbh_seg7_vertex_0701AA08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  2, 11,  0, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701AB08, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701ABE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 12,  7, 0x0,  7, 13,  8, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701ACD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0,  8, 12, 11, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701ADD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4, 10,  3, 0x0, 11, 10,  4, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 11,  4,  6, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701AED8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701B558 - 0x0701B620
static const Gfx bbh_seg7_dl_0701B558[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0701AF48, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701B048, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701B148, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701B620 - 0x0701B678
static const Gfx bbh_seg7_dl_0701B620[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0701B1E8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701B678 - 0x0701B6D0
static const Gfx bbh_seg7_dl_0701B678[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0701B2A8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  2,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701B6D0 - 0x0701B7A8
const Gfx bbh_seg7_dl_0701B6D0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701B328),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701B380),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701B558),
    gsSPDisplayList(bbh_seg7_dl_0701B620),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701B678),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
