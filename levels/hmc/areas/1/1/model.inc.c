#include "pc/rom_assets.h"
// 0x07005800 - 0x07005818
static const Lights1 hmc_seg7_lights_07005800 = gdSPDefLights1(
    0x48, 0x48, 0x48,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07005818 - 0x07005830
static const Lights1 hmc_seg7_lights_07005818 = gdSPDefLights1(
    0x79, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07005830 - 0x07005848
static const Lights1 hmc_seg7_lights_07005830 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07005848 - 0x070058A8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005848, 0x003d0dc0, 89137, 0x00005848, 96);

// 0x070058A8 - 0x07005918
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070058A8, 0x003d0dc0, 89137, 0x000058a8, 112);

// 0x07005918 - 0x07005A08
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005918, 0x003d0dc0, 89137, 0x00005918, 240);

// 0x07005A08 - 0x07005AF8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005A08, 0x003d0dc0, 89137, 0x00005a08, 240);

// 0x07005AF8 - 0x07005BF8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005AF8, 0x003d0dc0, 89137, 0x00005af8, 256);

// 0x07005BF8 - 0x07005CF8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005BF8, 0x003d0dc0, 89137, 0x00005bf8, 256);

// 0x07005CF8 - 0x07005DE8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005CF8, 0x003d0dc0, 89137, 0x00005cf8, 240);

// 0x07005DE8 - 0x07005E88
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005DE8, 0x003d0dc0, 89137, 0x00005de8, 160);

// 0x07005E88 - 0x07005F88
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005E88, 0x003d0dc0, 89137, 0x00005e88, 256);

// 0x07005F88 - 0x07006068
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07005F88, 0x003d0dc0, 89137, 0x00005f88, 224);

// 0x07006068 - 0x07006148
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006068, 0x003d0dc0, 89137, 0x00006068, 224);

// 0x07006148 - 0x07006228
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006148, 0x003d0dc0, 89137, 0x00006148, 224);

// 0x07006228 - 0x07006328
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006228, 0x003d0dc0, 89137, 0x00006228, 256);

// 0x07006328 - 0x07006428
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006328, 0x003d0dc0, 89137, 0x00006328, 256);

// 0x07006428 - 0x07006458
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006428, 0x003d0dc0, 89137, 0x00006428, 48);

// 0x07006458 - 0x07006498
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006458, 0x003d0dc0, 89137, 0x00006458, 64);

// 0x07006498 - 0x070064D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006498, 0x003d0dc0, 89137, 0x00006498, 64);

// 0x070064D8 - 0x070065C8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070064D8, 0x003d0dc0, 89137, 0x000064d8, 240);

// 0x070065C8 - 0x070066B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070065C8, 0x003d0dc0, 89137, 0x000065c8, 240);

// 0x070066B8 - 0x070067B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070066B8, 0x003d0dc0, 89137, 0x000066b8, 256);

// 0x070067B8 - 0x07006878
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070067B8, 0x003d0dc0, 89137, 0x000067b8, 192);

// 0x07006878 - 0x07006978
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006878, 0x003d0dc0, 89137, 0x00006878, 256);

// 0x07006978 - 0x07006A78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006978, 0x003d0dc0, 89137, 0x00006978, 256);

// 0x07006A78 - 0x07006B68
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006A78, 0x003d0dc0, 89137, 0x00006a78, 240);

// 0x07006B68 - 0x07006C58
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006B68, 0x003d0dc0, 89137, 0x00006b68, 240);

// 0x07006C58 - 0x07006D38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006C58, 0x003d0dc0, 89137, 0x00006c58, 224);

// 0x07006D38 - 0x07006E38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006D38, 0x003d0dc0, 89137, 0x00006d38, 256);

// 0x07006E38 - 0x07006F18
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006E38, 0x003d0dc0, 89137, 0x00006e38, 224);

// 0x07006F18 - 0x07006FF8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07006F18, 0x003d0dc0, 89137, 0x00006f18, 224);

// 0x07006FF8 - 0x07007080
static const Gfx hmc_seg7_dl_07006FF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07005800.l, 1),
    gsSPLight(&hmc_seg7_lights_07005800.a, 2),
    gsSPVertex(hmc_seg7_vertex_07005848, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  4,  5, 0x0),
    gsSPLight(&hmc_seg7_lights_07005818.l, 1),
    gsSPLight(&hmc_seg7_lights_07005818.a, 2),
    gsSPVertex(hmc_seg7_vertex_070058A8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007080 - 0x07007278
static const Gfx hmc_seg7_dl_07007080[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07005830.l, 1),
    gsSPLight(&hmc_seg7_lights_07005830.a, 2),
    gsSPVertex(hmc_seg7_vertex_07005918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12,  1, 0x0),
    gsSP2Triangles(12,  2,  1, 0x0, 13,  0,  2, 0x0),
    gsSP1Triangle(13,  2, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07005A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 4,  0, 12, 0x0,  4, 12,  5, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 12, 0x0),
    gsSP1Triangle( 2, 13, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_07005AF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles( 9, 11,  6, 0x0, 11,  7,  6, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15,  9, 10, 0x0),
    gsSPVertex(hmc_seg7_vertex_07005BF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  9, 13, 14, 0x0),
    gsSP1Triangle(15,  8, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07005CF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  9,  7, 0x0,  4, 10,  9, 0x0),
    gsSP2Triangles( 4, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07005DE8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007278 - 0x07007490
static const Gfx hmc_seg7_dl_07007278[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07005E88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 5,  4,  8, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles( 7,  5, 10, 0x0,  5, 11, 10, 0x0),
    gsSP2Triangles( 5,  9, 11, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles( 9, 13, 14, 0x0,  9, 12, 13, 0x0),
    gsSP2Triangles( 9, 14, 11, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_07005F88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  7,  6,  0, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9,  7,  0, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0,  9,  0, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006068, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006148, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 10, 12,  7, 0x0),
    gsSP1Triangle( 0,  2, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006228, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006328, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006428, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007490 - 0x070074C8
static const Gfx hmc_seg7_dl_07007490[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07006458, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070074C8 - 0x07007500
static const Gfx hmc_seg7_dl_070074C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07006498, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007500 - 0x07007630
static const Gfx hmc_seg7_dl_07007500[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070064D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_070065C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_070066B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070067B8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007630 - 0x070078B0
static const Gfx hmc_seg7_dl_07007630[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07006878, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006978, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  6, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(10, 14,  7, 0x0,  5,  4, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006A78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  9,  6,  3, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8,  7, 13, 0x0),
    gsSP1Triangle( 8, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006B68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  3,  0, 0x0,  8,  9,  3, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  7, 12, 11, 0x0),
    gsSP2Triangles(13,  9,  8, 0x0, 13, 14,  9, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006C58, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006D38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006E38, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07006F18, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  9,  6, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles( 7, 12, 11, 0x0, 12, 10, 13, 0x0),
    gsSP2Triangles(10,  6, 13, 0x0, 12, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x070078B0 - 0x070079E8
const Gfx hmc_seg7_dl_070078B0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(960, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07006FF8),
    gsSPDisplayList(hmc_seg7_dl_07007080),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07007278),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07007490),
    gsSPDisplayList(hmc_seg7_dl_070074C8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07007500),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07007630),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
