#include "pc/rom_assets.h"
// 0x07005D00 - 0x07005DF0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07005D00, 0x00437870, 75979, 0x00005d00, 240);

// 0x07005DF0 - 0x07005EF0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07005DF0, 0x00437870, 75979, 0x00005df0, 256);

// 0x07005EF0 - 0x07005FF0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07005EF0, 0x00437870, 75979, 0x00005ef0, 256);

// 0x07005FF0 - 0x070060F0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07005FF0, 0x00437870, 75979, 0x00005ff0, 256);

// 0x070060F0 - 0x070061E0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070060F0, 0x00437870, 75979, 0x000060f0, 240);

// 0x070061E0 - 0x070062D0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070061E0, 0x00437870, 75979, 0x000061e0, 240);

// 0x070062D0 - 0x070063B0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070062D0, 0x00437870, 75979, 0x000062d0, 224);

// 0x070063B0 - 0x070064A0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070063B0, 0x00437870, 75979, 0x000063b0, 240);

// 0x070064A0 - 0x07006590
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070064A0, 0x00437870, 75979, 0x000064a0, 240);

// 0x07006590 - 0x07006690
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006590, 0x00437870, 75979, 0x00006590, 256);

// 0x07006690 - 0x070066D0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006690, 0x00437870, 75979, 0x00006690, 64);

// 0x070066D0 - 0x070067C0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070066D0, 0x00437870, 75979, 0x000066d0, 240);

// 0x070067C0 - 0x070068B0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070067C0, 0x00437870, 75979, 0x000067c0, 240);

// 0x070068B0 - 0x070069A0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070068B0, 0x00437870, 75979, 0x000068b0, 240);

// 0x070069A0 - 0x07006AA0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070069A0, 0x00437870, 75979, 0x000069a0, 256);

// 0x07006AA0 - 0x07006B80
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006AA0, 0x00437870, 75979, 0x00006aa0, 224);

// 0x07006B80 - 0x07006C60
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006B80, 0x00437870, 75979, 0x00006b80, 224);

// 0x07006C60 - 0x07006D50
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006C60, 0x00437870, 75979, 0x00006c60, 240);

// 0x07006D50 - 0x07006E50
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006D50, 0x00437870, 75979, 0x00006d50, 256);

// 0x07006E50 - 0x07006F30
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006E50, 0x00437870, 75979, 0x00006e50, 224);

// 0x07006F30 - 0x07007020
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07006F30, 0x00437870, 75979, 0x00006f30, 240);

// 0x07007020 - 0x07007110
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07007020, 0x00437870, 75979, 0x00007020, 240);

// 0x07007110 - 0x07007150
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07007110, 0x00437870, 75979, 0x00007110, 64);

// 0x07007150 - 0x07007250
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07007150, 0x00437870, 75979, 0x00007150, 256);

// 0x07007250 - 0x07007350
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07007250, 0x00437870, 75979, 0x00007250, 256);

// 0x07007350 - 0x070073D0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07007350, 0x00437870, 75979, 0x00007350, 128);

// 0x070073D0 - 0x070074D0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070073D0, 0x00437870, 75979, 0x000073d0, 256);

// 0x070074D0 - 0x070075C0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070074D0, 0x00437870, 75979, 0x000074d0, 240);

// 0x070075C0 - 0x070076B0
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070075C0, 0x00437870, 75979, 0x000075c0, 240);

// 0x070076B0 - 0x07007868
static const Gfx rr_seg7_dl_070076B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_07005D00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07005DF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 11, 13, 0x0, 14, 15, 11, 0x0),
    gsSPVertex(rr_seg7_vertex_07005EF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07005FF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  6, 10,  7, 0x0),
    gsSP2Triangles( 6,  8, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_070060F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_070061E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007868 - 0x070079B0
static const Gfx rr_seg7_dl_07007868[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_070062D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_070063B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_070064A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07006590, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07006690, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070079B0 - 0x07007CB0
static const Gfx rr_seg7_dl_070079B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_070066D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_070067C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_070068B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_070069A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 15, 0x0, 11, 15, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_07006AA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(rr_seg7_vertex_07006B80, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07006C60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07006D50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  3,  2,  5, 0x0),
    gsSP2Triangles( 2,  6,  5, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(10, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07006E50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  0,  4,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7, 10,  8, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07006F30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07007020, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07007110, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007CB0 - 0x07007D88
static const Gfx rr_seg7_dl_07007CB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_07007150, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07007250, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07007350, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007D88 - 0x07007E60
static const Gfx rr_seg7_dl_07007D88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_070073D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_070074D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_070075C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007E60 - 0x07007EF0
const Gfx rr_seg7_dl_07007E60[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(rr_seg7_dl_070076B0),
    gsSPDisplayList(rr_seg7_dl_07007868),
    gsSPDisplayList(rr_seg7_dl_070079B0),
    gsSPDisplayList(rr_seg7_dl_07007CB0),
    gsSPDisplayList(rr_seg7_dl_07007D88),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
