#include "pc/rom_assets.h"
// 0x07010118 - 0x07010130
static const Lights1 hmc_seg7_lights_07010118 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07010130 - 0x07010148
static const Lights1 hmc_seg7_lights_07010130 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07010148 - 0x07010248
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010148, 0x003d0dc0, 89137, 0x00010148, 256);

// 0x07010248 - 0x07010348
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010248, 0x003d0dc0, 89137, 0x00010248, 256);

// 0x07010348 - 0x07010448
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010348, 0x003d0dc0, 89137, 0x00010348, 256);

// 0x07010448 - 0x07010548
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010448, 0x003d0dc0, 89137, 0x00010448, 256);

// 0x07010548 - 0x07010628
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010548, 0x003d0dc0, 89137, 0x00010548, 224);

// 0x07010628 - 0x07010728
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010628, 0x003d0dc0, 89137, 0x00010628, 256);

// 0x07010728 - 0x07010808
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010728, 0x003d0dc0, 89137, 0x00010728, 224);

// 0x07010808 - 0x070108F8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010808, 0x003d0dc0, 89137, 0x00010808, 240);

// 0x070108F8 - 0x070109F8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070108F8, 0x003d0dc0, 89137, 0x000108f8, 256);

// 0x070109F8 - 0x07010AF8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070109F8, 0x003d0dc0, 89137, 0x000109f8, 256);

// 0x07010AF8 - 0x07010B78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010AF8, 0x003d0dc0, 89137, 0x00010af8, 128);

// 0x07010B78 - 0x07010C68
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010B78, 0x003d0dc0, 89137, 0x00010b78, 240);

// 0x07010C68 - 0x07010D68
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010C68, 0x003d0dc0, 89137, 0x00010c68, 256);

// 0x07010D68 - 0x07010E38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010D68, 0x003d0dc0, 89137, 0x00010d68, 208);

// 0x07010E38 - 0x07010F38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010E38, 0x003d0dc0, 89137, 0x00010e38, 256);

// 0x07010F38 - 0x07011028
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07010F38, 0x003d0dc0, 89137, 0x00010f38, 240);

// 0x07011028 - 0x07011118
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011028, 0x003d0dc0, 89137, 0x00011028, 240);

// 0x07011118 - 0x07011208
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011118, 0x003d0dc0, 89137, 0x00011118, 240);

// 0x07011208 - 0x07011308
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011208, 0x003d0dc0, 89137, 0x00011208, 256);

// 0x07011308 - 0x07011408
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011308, 0x003d0dc0, 89137, 0x00011308, 256);

// 0x07011408 - 0x070114E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011408, 0x003d0dc0, 89137, 0x00011408, 224);

// 0x070114E8 - 0x070115C8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070114E8, 0x003d0dc0, 89137, 0x000114e8, 224);

// 0x070115C8 - 0x070116B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070115C8, 0x003d0dc0, 89137, 0x000115c8, 240);

// 0x070116B8 - 0x070117B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070116B8, 0x003d0dc0, 89137, 0x000116b8, 256);

// 0x070117B8 - 0x07011898
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070117B8, 0x003d0dc0, 89137, 0x000117b8, 224);

// 0x07011898 - 0x07011988
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011898, 0x003d0dc0, 89137, 0x00011898, 240);

// 0x07011988 - 0x07011A88
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011988, 0x003d0dc0, 89137, 0x00011988, 256);

// 0x07011A88 - 0x07011B68
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011A88, 0x003d0dc0, 89137, 0x00011a88, 224);

// 0x07011B68 - 0x07011C68
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011B68, 0x003d0dc0, 89137, 0x00011b68, 256);

// 0x07011C68 - 0x07011D58
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011C68, 0x003d0dc0, 89137, 0x00011c68, 240);

// 0x07011D58 - 0x07011E58
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011D58, 0x003d0dc0, 89137, 0x00011d58, 256);

// 0x07011E58 - 0x07011F58
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011E58, 0x003d0dc0, 89137, 0x00011e58, 256);

// 0x07011F58 - 0x07012048
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07011F58, 0x003d0dc0, 89137, 0x00011f58, 240);

// 0x07012048 - 0x07012148
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012048, 0x003d0dc0, 89137, 0x00012048, 256);

// 0x07012148 - 0x07012188
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012148, 0x003d0dc0, 89137, 0x00012148, 64);

// 0x07012188 - 0x07012278
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012188, 0x003d0dc0, 89137, 0x00012188, 240);

// 0x07012278 - 0x07012328
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012278, 0x003d0dc0, 89137, 0x00012278, 176);

// 0x07012328 - 0x07012418
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012328, 0x003d0dc0, 89137, 0x00012328, 240);

// 0x07012418 - 0x070124F8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012418, 0x003d0dc0, 89137, 0x00012418, 224);

// 0x070124F8 - 0x070125E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070124F8, 0x003d0dc0, 89137, 0x000124f8, 240);

// 0x070125E8 - 0x070126E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070125E8, 0x003d0dc0, 89137, 0x000125e8, 256);

// 0x070126E8 - 0x070127C8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070126E8, 0x003d0dc0, 89137, 0x000126e8, 224);

// 0x070127C8 - 0x070128B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070127C8, 0x003d0dc0, 89137, 0x000127c8, 240);

// 0x070128B8 - 0x07012958
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070128B8, 0x003d0dc0, 89137, 0x000128b8, 160);

// 0x07012958 - 0x07012A58
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012958, 0x003d0dc0, 89137, 0x00012958, 256);

// 0x07012A58 - 0x07012AB8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012A58, 0x003d0dc0, 89137, 0x00012a58, 96);

// 0x07012AB8 - 0x07012BA8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012AB8, 0x003d0dc0, 89137, 0x00012ab8, 240);

// 0x07012BA8 - 0x07012C38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012BA8, 0x003d0dc0, 89137, 0x00012ba8, 144);

// 0x07012C38 - 0x07012C78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07012C38, 0x003d0dc0, 89137, 0x00012c38, 64);

// 0x07012C78 - 0x07013080
static const Gfx hmc_seg7_dl_07012C78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07010118.l, 1),
    gsSPLight(&hmc_seg7_lights_07010118.a, 2),
    gsSPVertex(hmc_seg7_vertex_07010148, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 5,  4,  8, 0x0,  9, 10,  0, 0x0),
    gsSP2Triangles(11,  9,  0, 0x0, 11, 12,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010248, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 3, 14,  4, 0x0, 15,  4, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010348, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 3,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0, 11, 10, 14, 0x0),
    gsSP2Triangles(11, 15,  0, 0x0, 11, 14, 15, 0x0),
    gsSP1Triangle(12, 10,  9, 0x0),
    gsSPLight(&hmc_seg7_lights_07010130.l, 1),
    gsSPLight(&hmc_seg7_lights_07010130.a, 2),
    gsSPVertex(hmc_seg7_vertex_07010448, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0, 10,  9,  3, 0x0),
    gsSP2Triangles( 9,  8,  3, 0x0,  1,  0, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010548, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9,  3, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010628, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  4,  0,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010728, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010808, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_070108F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4, 11,  1, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles(12,  5, 13, 0x0, 12,  6,  5, 0x0),
    gsSP2Triangles(14,  7,  6, 0x0, 10, 15, 14, 0x0),
    gsSP1Triangle(10,  9, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070109F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  1, 0x0,  1,  8,  2, 0x0),
    gsSP2Triangles( 1,  7,  8, 0x0,  1,  9,  6, 0x0),
    gsSP2Triangles( 6,  9,  5, 0x0,  4, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 13, 14,  6, 0x0),
    gsSP2Triangles( 6, 14,  7, 0x0, 13,  6,  5, 0x0),
    gsSP2Triangles( 2, 15, 13, 0x0,  2,  8, 15, 0x0),
    gsSP2Triangles( 2, 13,  5, 0x0, 13, 15, 14, 0x0),
    gsSP2Triangles(15,  7, 14, 0x0, 15,  8,  7, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010AF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013080 - 0x07013168
static const Gfx hmc_seg7_dl_07013080[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07010B78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010C68, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  6, 11,  7, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010D68, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9,  4, 0x0),
    gsSP1Triangle(10, 11, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013168 - 0x07013840
static const Gfx hmc_seg7_dl_07013168[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07010E38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  5,  0, 0x0),
    gsSP2Triangles( 4,  3,  7, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  5, 12, 0x0),
    gsSP2Triangles(11,  1,  5, 0x0,  5,  7, 13, 0x0),
    gsSP2Triangles( 5, 13, 12, 0x0,  7, 14, 13, 0x0),
    gsSP2Triangles( 7,  3, 14, 0x0, 15,  9,  8, 0x0),
    gsSPVertex(hmc_seg7_vertex_07010F38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011028, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 2,  6,  8, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  3, 11,  4, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011118, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011208, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011308, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011408, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 9,  3,  5, 0x0,  9,  5,  7, 0x0),
    gsSPVertex(hmc_seg7_vertex_070114E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  5,  0, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_070115C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_070116B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070117B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  7,  9, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011898, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011988, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 12, 11, 0x0, 11, 13, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011A88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011B68, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10, 11,  5, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 13, 11, 0x0),
    gsSP2Triangles( 5, 14,  8, 0x0,  5, 11, 14, 0x0),
    gsSP2Triangles(15, 14, 11, 0x0, 15, 11, 13, 0x0),
    gsSP1Triangle( 6,  5,  8, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011C68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  8,  6,  4, 0x0),
    gsSP2Triangles( 9,  2,  6, 0x0,  9, 10,  2, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  3, 10, 14, 0x0),
    gsSP2Triangles( 3,  2, 10, 0x0, 14,  4,  3, 0x0),
    gsSP1Triangle(14,  8,  4, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011D58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles(10,  9,  7, 0x0,  0,  8,  1, 0x0),
    gsSP2Triangles( 0, 12,  8, 0x0,  1,  8,  9, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0,  1,  9,  2, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011E58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 12, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 14, 11, 15, 0x0),
    gsSP1Triangle(14, 10, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07011F58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07012048, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(13, 14,  4, 0x0, 13, 15, 14, 0x0),
    gsSP1Triangle(13,  4,  6, 0x0),
    gsSPVertex(hmc_seg7_vertex_07012148, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013840 - 0x070138E0
static const Gfx hmc_seg7_dl_07013840[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07012188, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07012278, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070138E0 - 0x07013A78
static const Gfx hmc_seg7_dl_070138E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07012328, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  8,  2,  7, 0x0),
    gsSP2Triangles( 8,  5,  2, 0x0,  2,  1,  6, 0x0),
    gsSP2Triangles( 9, 10,  5, 0x0,  8,  9,  5, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  5, 14,  4, 0x0),
    gsSP1Triangle( 5, 10, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07012418, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_070124F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_070125E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070126E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 4,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013A78 - 0x07013B48
static const Gfx hmc_seg7_dl_07013A78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070127C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  9,  5,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles(13, 14, 12, 0x0, 14, 10, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_070128B8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  4,  3,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  9,  5,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013B48 - 0x07013BC8
static const Gfx hmc_seg7_dl_07013B48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07012958, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07012A58, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013BC8 - 0x07013C78
static const Gfx hmc_seg7_dl_07013BC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07012AB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  6, 11, 10, 0x0),
    gsSP2Triangles(11,  9, 12, 0x0,  0, 13,  1, 0x0),
    gsSP1Triangle( 0, 14, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07012BA8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  4,  0,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013C78 - 0x07013CA8
static const Gfx hmc_seg7_dl_07013C78[] = {
    gsSPLight(&hmc_seg7_lights_07010118.l, 1),
    gsSPLight(&hmc_seg7_lights_07010118.a, 2),
    gsSPVertex(hmc_seg7_vertex_07012C38, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013CA8 - 0x07013DB8
const Gfx hmc_seg7_dl_07013CA8[] = {
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
    gsSPDisplayList(hmc_seg7_dl_07012C78),
    gsSPDisplayList(hmc_seg7_dl_07013080),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07013168),
    gsSPDisplayList(hmc_seg7_dl_07013840),
    gsSPDisplayList(hmc_seg7_dl_070138E0),
    gsSPDisplayList(hmc_seg7_dl_07013A78),
    gsSPDisplayList(hmc_seg7_dl_07013B48),
    gsSPDisplayList(hmc_seg7_dl_07013BC8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(hmc_seg7_dl_07013C78),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
