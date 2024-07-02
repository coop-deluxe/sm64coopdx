#include "pc/rom_assets.h"
// 0x07014EB8 - 0x07014ED0
static const Lights1 hmc_seg7_lights_07014EB8 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07014ED0 - 0x07014EE8
static const Lights1 hmc_seg7_lights_07014ED0 = gdSPDefLights1(
    0x79, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07014EE8 - 0x07014FE8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07014EE8, 0x003d0dc0, 89137, 0x00014ee8, 256);

// 0x07014FE8 - 0x070150E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07014FE8, 0x003d0dc0, 89137, 0x00014fe8, 256);

// 0x070150E8 - 0x070151E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070150E8, 0x003d0dc0, 89137, 0x000150e8, 256);

// 0x070151E8 - 0x070152D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070151E8, 0x003d0dc0, 89137, 0x000151e8, 240);

// 0x070152D8 - 0x070153D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070152D8, 0x003d0dc0, 89137, 0x000152d8, 256);

// 0x070153D8 - 0x070154B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070153D8, 0x003d0dc0, 89137, 0x000153d8, 224);

// 0x070154B8 - 0x07015558
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070154B8, 0x003d0dc0, 89137, 0x000154b8, 160);

// 0x07015558 - 0x070155C8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07015558, 0x003d0dc0, 89137, 0x00015558, 112);

// 0x070155C8 - 0x070156C8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070155C8, 0x003d0dc0, 89137, 0x000155c8, 256);

// 0x070156C8 - 0x070157B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070156C8, 0x003d0dc0, 89137, 0x000156c8, 240);

// 0x070157B8 - 0x070158A8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070157B8, 0x003d0dc0, 89137, 0x000157b8, 240);

// 0x070158A8 - 0x070159A8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070158A8, 0x003d0dc0, 89137, 0x000158a8, 256);

// 0x070159A8 - 0x07015AA8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070159A8, 0x003d0dc0, 89137, 0x000159a8, 256);

// 0x07015AA8 - 0x07015BA8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07015AA8, 0x003d0dc0, 89137, 0x00015aa8, 256);

// 0x07015BA8 - 0x07015C28
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07015BA8, 0x003d0dc0, 89137, 0x00015ba8, 128);

// 0x07015C28 - 0x07015D28
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07015C28, 0x003d0dc0, 89137, 0x00015c28, 256);

// 0x07015D28 - 0x07015E18
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07015D28, 0x003d0dc0, 89137, 0x00015d28, 240);

// 0x07015E18 - 0x07015F18
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07015E18, 0x003d0dc0, 89137, 0x00015e18, 256);

// 0x07015F18 - 0x07016018
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07015F18, 0x003d0dc0, 89137, 0x00015f18, 256);

// 0x07016018 - 0x07016118
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016018, 0x003d0dc0, 89137, 0x00016018, 256);

// 0x07016118 - 0x07016218
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016118, 0x003d0dc0, 89137, 0x00016118, 256);

// 0x07016218 - 0x07016308
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016218, 0x003d0dc0, 89137, 0x00016218, 240);

// 0x07016308 - 0x07016408
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016308, 0x003d0dc0, 89137, 0x00016308, 256);

// 0x07016408 - 0x07016508
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016408, 0x003d0dc0, 89137, 0x00016408, 256);

// 0x07016508 - 0x07016608
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016508, 0x003d0dc0, 89137, 0x00016508, 256);

// 0x07016608 - 0x070166F8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016608, 0x003d0dc0, 89137, 0x00016608, 240);

// 0x070166F8 - 0x070167F8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070166F8, 0x003d0dc0, 89137, 0x000166f8, 256);

// 0x070167F8 - 0x07016898
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070167F8, 0x003d0dc0, 89137, 0x000167f8, 160);

// 0x07016898 - 0x070168D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07016898, 0x003d0dc0, 89137, 0x00016898, 64);

// 0x070168D8 - 0x07016918
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070168D8, 0x003d0dc0, 89137, 0x000168d8, 64);

// 0x07016918 - 0x07016A90
static const Gfx hmc_seg7_dl_07016918[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07014EB8.l, 1),
    gsSPLight(&hmc_seg7_lights_07014EB8.a, 2),
    gsSPVertex(hmc_seg7_vertex_07014EE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 12, 10,  0, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles(12,  7, 10, 0x0, 11,  1, 10, 0x0),
    gsSPVertex(hmc_seg7_vertex_07014FE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  6,  1,  7, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  7,  1,  8, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(10, 12, 15, 0x0, 10, 15,  3, 0x0),
    gsSPVertex(hmc_seg7_vertex_070150E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  1, 0x0),
    gsSP2Triangles(11,  1,  3, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070151E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016A90 - 0x07016BA8
static const Gfx hmc_seg7_dl_07016A90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070152D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 12, 11,  1, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070153D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_070154B8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4,  6,  8, 0x0),
    gsSPLight(&hmc_seg7_lights_07014ED0.l, 1),
    gsSPLight(&hmc_seg7_lights_07014ED0.a, 2),
    gsSPVertex(hmc_seg7_vertex_07015558, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016BA8 - 0x07016C60
static const Gfx hmc_seg7_dl_07016BA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07014EB8.l, 1),
    gsSPLight(&hmc_seg7_lights_07014EB8.a, 2),
    gsSPVertex(hmc_seg7_vertex_070155C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0,  2,  1, 11, 0x0),
    gsSP2Triangles( 2, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles( 0, 15,  1, 0x0, 12, 11, 14, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 13, 15,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016C60 - 0x07016E40
static const Gfx hmc_seg7_dl_07016C60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070156C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_070157B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_070158A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 8, 14, 11, 0x0, 13, 12, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070159A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07015AA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  8, 15,  9, 0x0),
    gsSPVertex(hmc_seg7_vertex_07015BA8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  6,  0, 0x0),
    gsSP1Triangle( 7,  0,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07016E40 - 0x07017338
static const Gfx hmc_seg7_dl_07016E40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07015C28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07015D28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07015E18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0, 12, 10,  6, 0x0),
    gsSP2Triangles( 6, 11, 13, 0x0,  4,  2, 14, 0x0),
    gsSP1Triangle(15,  4, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07015F18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  2,  8, 0x0),
    gsSP2Triangles( 9,  5,  4, 0x0, 10,  5, 11, 0x0),
    gsSP2Triangles(12,  6,  5, 0x0, 12,  5, 10, 0x0),
    gsSP2Triangles( 4,  6, 13, 0x0, 14,  6, 12, 0x0),
    gsSP1Triangle(13,  6, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07016018, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 13, 11, 0x0),
    gsSP2Triangles(14, 15, 13, 0x0, 14, 13, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_07016118, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  1, 0x0),
    gsSP2Triangles( 8,  6,  3, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 1,  3,  5, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 9,  0,  6, 0x0,  4,  2, 10, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0,  5, 11, 12, 0x0),
    gsSP2Triangles( 5, 12, 13, 0x0,  1, 14,  2, 0x0),
    gsSP2Triangles( 7,  1, 15, 0x0, 15,  1,  0, 0x0),
    gsSP2Triangles( 1,  5, 14, 0x0, 15,  0,  9, 0x0),
    gsSPVertex(hmc_seg7_vertex_07016218, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 4,  7,  3, 0x0,  2,  1,  8, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  2,  8,  9, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0,  9,  7,  4, 0x0),
    gsSP2Triangles( 4,  0,  6, 0x0, 10,  9,  4, 0x0),
    gsSP2Triangles( 4,  6, 11, 0x0, 10,  4, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07016308, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07016408, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0,  2, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07016508, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  4,  8, 0x0),
    gsSP2Triangles( 7,  5,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSP2Triangles(12, 15, 14, 0x0, 12, 11, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07016608, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  2,  6,  8, 0x0),
    gsSP2Triangles( 2,  3,  7, 0x0,  3,  4,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  6,  7, 13, 0x0),
    gsSP1Triangle( 7, 14, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_070166F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 10,  8, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070167F8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017338 - 0x07017370
static const Gfx hmc_seg7_dl_07017338[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07016898, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017370 - 0x070173A8
static const Gfx hmc_seg7_dl_07017370[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070168D8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070173A8 - 0x070174B0
const Gfx hmc_seg7_dl_070173A8[] = {
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
    gsSPDisplayList(hmc_seg7_dl_07016918),
    gsSPDisplayList(hmc_seg7_dl_07016A90),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07016BA8),
    gsSPDisplayList(hmc_seg7_dl_07016C60),
    gsSPDisplayList(hmc_seg7_dl_07016E40),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07017338),
    gsSPDisplayList(hmc_seg7_dl_07017370),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
