#include "pc/rom_assets.h"
// 0x07009288 - 0x070092A0
static const Lights1 ddd_seg7_lights_07009288 = gdSPDefLights1(
    0x3f, 0x1f, 0x19,
    0xff, 0x7f, 0x65, 0x28, 0x28, 0x28
);

// 0x070092A0 - 0x070092B8
static const Lights1 ddd_seg7_lights_070092A0 = gdSPDefLights1(
    0x2f, 0x1a, 0x0f,
    0xbf, 0x6a, 0x3f, 0x28, 0x28, 0x28
);

// 0x070092B8 - 0x070092D0
static const Lights1 ddd_seg7_lights_070092B8 = gdSPDefLights1(
    0x0c, 0x0c, 0x0c,
    0x33, 0x33, 0x33, 0x28, 0x28, 0x28
);

// 0x070092D0 - 0x070092E8
static const Lights1 ddd_seg7_lights_070092D0 = gdSPDefLights1(
    0x1d, 0x1d, 0x1d,
    0x77, 0x77, 0x77, 0x28, 0x28, 0x28
);

// 0x070092E8 - 0x07009300
static const Lights1 ddd_seg7_lights_070092E8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07009300 - 0x07009400
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009300, 0x0048d930, 33063, 0x00009300, 256);

// 0x07009400 - 0x07009490
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009400, 0x0048d930, 33063, 0x00009400, 144);

// 0x07009490 - 0x07009590
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009490, 0x0048d930, 33063, 0x00009490, 256);

// 0x07009590 - 0x070095E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009590, 0x0048d930, 33063, 0x00009590, 80);

// 0x070095E0 - 0x07009660
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070095E0, 0x0048d930, 33063, 0x000095e0, 128);

// 0x07009660 - 0x07009750
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009660, 0x0048d930, 33063, 0x00009660, 240);

// 0x07009750 - 0x07009800
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009750, 0x0048d930, 33063, 0x00009750, 176);

// 0x07009800 - 0x070098E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009800, 0x0048d930, 33063, 0x00009800, 224);

// 0x070098E0 - 0x070099E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070098E0, 0x0048d930, 33063, 0x000098e0, 256);

// 0x070099E0 - 0x07009AD0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070099E0, 0x0048d930, 33063, 0x000099e0, 240);

// 0x07009AD0 - 0x07009BD0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009AD0, 0x0048d930, 33063, 0x00009ad0, 256);

// 0x07009BD0 - 0x07009CD0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009BD0, 0x0048d930, 33063, 0x00009bd0, 256);

// 0x07009CD0 - 0x07009DD0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009CD0, 0x0048d930, 33063, 0x00009cd0, 256);

// 0x07009DD0 - 0x07009ED0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009DD0, 0x0048d930, 33063, 0x00009dd0, 256);

// 0x07009ED0 - 0x07009FD0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009ED0, 0x0048d930, 33063, 0x00009ed0, 256);

// 0x07009FD0 - 0x0700A0D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07009FD0, 0x0048d930, 33063, 0x00009fd0, 256);

// 0x0700A0D0 - 0x0700A1D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700A0D0, 0x0048d930, 33063, 0x0000a0d0, 256);

// 0x0700A1D0 - 0x0700A2D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700A1D0, 0x0048d930, 33063, 0x0000a1d0, 256);

// 0x0700A2D0 - 0x0700A3C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700A2D0, 0x0048d930, 33063, 0x0000a2d0, 240);

// 0x0700A3C0 - 0x0700A4C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700A3C0, 0x0048d930, 33063, 0x0000a3c0, 256);

// 0x0700A4C0 - 0x0700A580
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700A4C0, 0x0048d930, 33063, 0x0000a4c0, 192);

// 0x0700A580 - 0x0700A600
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700A580, 0x0048d930, 33063, 0x0000a580, 128);

// 0x0700A600 - 0x0700AEB8
static const Gfx ddd_seg7_dl_0700A600[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ddd_seg7_texture_07001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_07009288.l, 1),
    gsSPLight(&ddd_seg7_lights_07009288.a, 2),
    gsSPVertex(ddd_seg7_vertex_07009300, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 4,  1,  7, 0x0,  8,  7,  1, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  9,  8,  0, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13,  9,  0, 0x0,  9, 13, 14, 0x0),
    gsSP2Triangles(13,  0,  2, 0x0, 15, 13,  2, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009400, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 1,  3,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  4,  7,  6, 0x0),
    gsSP1Triangle( 8,  7,  4, 0x0),
    gsSPLight(&ddd_seg7_lights_070092A0.l, 1),
    gsSPLight(&ddd_seg7_lights_070092A0.a, 2),
    gsSPVertex(ddd_seg7_vertex_07009490, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  5,  3,  0, 0x0),
    gsSP2Triangles( 6,  4,  5, 0x0,  0,  4,  6, 0x0),
    gsSP2Triangles( 6,  5,  0, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  0, 10,  7, 0x0),
    gsSP2Triangles( 9, 10,  0, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14,  1,  0, 0x0,  2,  1, 14, 0x0),
    gsSP2Triangles(15,  2, 14, 0x0,  0,  2, 15, 0x0),
    gsSP1Triangle(15, 14,  0, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009590, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  4,  1,  0, 0x0),
    gsSP1Triangle( 2,  1,  3, 0x0),
    gsSPLight(&ddd_seg7_lights_070092B8.l, 1),
    gsSPLight(&ddd_seg7_lights_070092B8.a, 2),
    gsSPVertex(ddd_seg7_vertex_070095E0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0,  4,  7, 0x0),
    gsSPLight(&ddd_seg7_lights_070092D0.l, 1),
    gsSPLight(&ddd_seg7_lights_070092D0.a, 2),
    gsSPVertex(ddd_seg7_vertex_07009660, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 9,  7,  5, 0x0, 10,  9,  5, 0x0),
    gsSP2Triangles( 6, 10,  5, 0x0, 11, 12,  2, 0x0),
    gsSP2Triangles(12, 13,  2, 0x0, 13, 14,  2, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009750, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  7,  8,  2, 0x0),
    gsSP2Triangles( 8,  9,  2, 0x0,  9, 10,  2, 0x0),
    gsSP1Triangle(10,  0,  2, 0x0),
    gsSPLight(&ddd_seg7_lights_070092E8.l, 1),
    gsSPLight(&ddd_seg7_lights_070092E8.a, 2),
    gsSPVertex(ddd_seg7_vertex_07009800, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  6,  0,  2, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8, 12, 13, 0x0),
    gsSPVertex(ddd_seg7_vertex_070098E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0, 11,  2,  5, 0x0),
    gsSP2Triangles( 1, 13,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles(13, 14,  5, 0x0, 13, 15, 14, 0x0),
    gsSP2Triangles(15,  3, 14, 0x0, 14,  3,  5, 0x0),
    gsSP2Triangles(15,  6,  3, 0x0,  8, 11,  5, 0x0),
    gsSPVertex(ddd_seg7_vertex_070099E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  0, 11,  1, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0, 13, 12, 14, 0x0),
    gsSP1Triangle(12, 11, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009AD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  3,  2,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8, 13,  9, 0x0),
    gsSP2Triangles( 8, 14, 13, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009BD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 3,  0,  5, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 6,  2,  8, 0x0,  2,  9,  8, 0x0),
    gsSP2Triangles( 9,  2,  7, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 10, 14, 0x0, 10, 12, 14, 0x0),
    gsSP1Triangle(11, 15, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009CD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  0, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  8,  6,  5, 0x0),
    gsSP2Triangles( 5,  4,  0, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 9, 10,  6, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles( 9,  6,  8, 0x0, 10,  4,  6, 0x0),
    gsSP2Triangles( 8,  7, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009DD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 7,  0,  2, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 12,  5, 13, 0x0),
    gsSP1Triangle( 6, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009ED0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles( 9,  3, 11, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(12,  0, 13, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles( 3,  0, 12, 0x0, 14,  8, 10, 0x0),
    gsSP1Triangle(13,  2, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07009FD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 0,  3,  8, 0x0,  3,  9,  8, 0x0),
    gsSP2Triangles( 5, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(10, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700A0D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  2,  3, 0x0,  5,  6,  2, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9,  5, 10, 0x0),
    gsSP2Triangles( 9,  8,  5, 0x0, 10,  5,  4, 0x0),
    gsSP2Triangles(11,  8,  9, 0x0, 11,  7,  8, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 13, 11,  9, 0x0),
    gsSP2Triangles(11, 12,  7, 0x0, 14, 12, 13, 0x0),
    gsSP1Triangle(15, 12, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700A1D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles(11, 13, 12, 0x0, 14,  4,  6, 0x0),
    gsSP2Triangles(14,  7,  4, 0x0, 14, 15,  7, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700A2D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  8,  3,  4, 0x0),
    gsSP2Triangles( 8,  9,  3, 0x0,  9,  0,  3, 0x0),
    gsSP2Triangles(10,  7,  6, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 12,  9,  8, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0, 13, 10, 14, 0x0),
    gsSP2Triangles(10,  6, 14, 0x0, 13, 11, 10, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700A3C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  0, 11,  1, 0x0),
    gsSP2Triangles( 0, 12, 11, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles(14,  2, 13, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700A4C0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  5,  1,  3, 0x0),
    gsSP2Triangles( 8,  6,  9, 0x0, 10,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0,  5,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AEB8 - 0x0700AF10
static const Gfx ddd_seg7_dl_0700AEB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ddd_seg7_vertex_0700A580, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  3,  6,  2, 0x0),
    gsSP2Triangles( 6,  4,  2, 0x0,  5,  7,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AF10 - 0x0700AF78
const Gfx ddd_seg7_dl_0700AF10[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_0700A600),
    gsSPDisplayList(ddd_seg7_dl_0700AEB8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
