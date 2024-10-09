#include "pc/rom_assets.h"
// 0x07025FF0 - 0x07026008
static const Lights1 ttm_seg7_lights_07025FF0 = gdSPDefLights1(
    0x15, 0x15, 0x15,
    0x55, 0x55, 0x55, 0x28, 0x28, 0x28
);

// 0x07026008 - 0x07026020
static const Lights1 ttm_seg7_lights_07026008 = gdSPDefLights1(
    0x19, 0x19, 0x19,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07026020 - 0x07026038
static const Lights1 ttm_seg7_lights_07026020 = gdSPDefLights1(
    0x1d, 0x1d, 0x1d,
    0x77, 0x77, 0x77, 0x28, 0x28, 0x28
);

// 0x07026038 - 0x07026050
static const Lights1 ttm_seg7_lights_07026038 = gdSPDefLights1(
    0x22, 0x22, 0x22,
    0x88, 0x88, 0x88, 0x28, 0x28, 0x28
);

// 0x07026050 - 0x07026068
static const Lights1 ttm_seg7_lights_07026050 = gdSPDefLights1(
    0x26, 0x26, 0x26,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07026068 - 0x07026080
static const Lights1 ttm_seg7_lights_07026068 = gdSPDefLights1(
    0x2a, 0x2a, 0x2a,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x07026080 - 0x07026098
static const Lights1 ttm_seg7_lights_07026080 = gdSPDefLights1(
    0x2e, 0x2e, 0x2e,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x07026098 - 0x070260B0
static const Lights1 ttm_seg7_lights_07026098 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0xcc, 0xcc, 0xcc, 0x28, 0x28, 0x28
);

// 0x070260B0 - 0x070260C8
static const Lights1 ttm_seg7_lights_070260B0 = gdSPDefLights1(
    0x37, 0x37, 0x37,
    0xdd, 0xdd, 0xdd, 0x28, 0x28, 0x28
);

// 0x070260C8 - 0x070260E0
static const Lights1 ttm_seg7_lights_070260C8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070260E0 - 0x070260F8
static const Lights1 ttm_seg7_lights_070260E0 = gdSPDefLights1(
    0x11, 0x11, 0x11,
    0x44, 0x44, 0x44, 0x28, 0x28, 0x28
);

// 0x070260F8 - 0x07026110
static const Lights1 ttm_seg7_lights_070260F8 = gdSPDefLights1(
    0x3b, 0x3b, 0x3b,
    0xee, 0xee, 0xee, 0x28, 0x28, 0x28
);

// 0x07026110 - 0x07026128
static const Lights1 ttm_seg7_lights_07026110 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07026128 - 0x07026228
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026128, 0x004d1910, 104662, 0x00026128, 256);

// 0x07026228 - 0x07026328
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026228, 0x004d1910, 104662, 0x00026228, 256);

// 0x07026328 - 0x07026428
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026328, 0x004d1910, 104662, 0x00026328, 256);

// 0x07026428 - 0x070264A8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026428, 0x004d1910, 104662, 0x00026428, 128);

// 0x070264A8 - 0x07026568
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070264A8, 0x004d1910, 104662, 0x000264a8, 192);

// 0x07026568 - 0x07026668
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026568, 0x004d1910, 104662, 0x00026568, 256);

// 0x07026668 - 0x07026758
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026668, 0x004d1910, 104662, 0x00026668, 240);

// 0x07026758 - 0x07026848
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026758, 0x004d1910, 104662, 0x00026758, 240);

// 0x07026848 - 0x07026928
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026848, 0x004d1910, 104662, 0x00026848, 224);

// 0x07026928 - 0x07026998
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026928, 0x004d1910, 104662, 0x00026928, 112);

// 0x07026998 - 0x07026A38
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026998, 0x004d1910, 104662, 0x00026998, 160);

// 0x07026A38 - 0x07026AB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026A38, 0x004d1910, 104662, 0x00026a38, 128);

// 0x07026AB8 - 0x07026BA8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026AB8, 0x004d1910, 104662, 0x00026ab8, 240);

// 0x07026BA8 - 0x07026C98
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026BA8, 0x004d1910, 104662, 0x00026ba8, 240);

// 0x07026C98 - 0x07026D98
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026C98, 0x004d1910, 104662, 0x00026c98, 256);

// 0x07026D98 - 0x07026E78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026D98, 0x004d1910, 104662, 0x00026d98, 224);

// 0x07026E78 - 0x07026EB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026E78, 0x004d1910, 104662, 0x00026e78, 64);

// 0x07026EB8 - 0x07026FB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026EB8, 0x004d1910, 104662, 0x00026eb8, 256);

// 0x07026FB8 - 0x070270B8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07026FB8, 0x004d1910, 104662, 0x00026fb8, 256);

// 0x070270B8 - 0x070271A8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070270B8, 0x004d1910, 104662, 0x000270b8, 240);

// 0x070271A8 - 0x07027288
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070271A8, 0x004d1910, 104662, 0x000271a8, 224);

// 0x07027288 - 0x07027388
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027288, 0x004d1910, 104662, 0x00027288, 256);

// 0x07027388 - 0x07027488
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027388, 0x004d1910, 104662, 0x00027388, 256);

// 0x07027488 - 0x07027588
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027488, 0x004d1910, 104662, 0x00027488, 256);

// 0x07027588 - 0x07027668
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027588, 0x004d1910, 104662, 0x00027588, 224);

// 0x07027668 - 0x07027758
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027668, 0x004d1910, 104662, 0x00027668, 240);

// 0x07027758 - 0x07027838
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027758, 0x004d1910, 104662, 0x00027758, 224);

// 0x07027838 - 0x07027928
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027838, 0x004d1910, 104662, 0x00027838, 240);

// 0x07027928 - 0x07027A08
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027928, 0x004d1910, 104662, 0x00027928, 224);

// 0x07027A08 - 0x07027AF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027A08, 0x004d1910, 104662, 0x00027a08, 240);

// 0x07027AF8 - 0x07027BA8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027AF8, 0x004d1910, 104662, 0x00027af8, 176);

// 0x07027BA8 - 0x07027BE8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027BA8, 0x004d1910, 104662, 0x00027ba8, 64);

// 0x07027BE8 - 0x07027CD8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027BE8, 0x004d1910, 104662, 0x00027be8, 240);

// 0x07027CD8 - 0x07027DC8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027CD8, 0x004d1910, 104662, 0x00027cd8, 240);

// 0x07027DC8 - 0x07027E38
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027DC8, 0x004d1910, 104662, 0x00027dc8, 112);

// 0x07027E38 - 0x07027EB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027E38, 0x004d1910, 104662, 0x00027e38, 128);

// 0x07027EB8 - 0x07027FB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027EB8, 0x004d1910, 104662, 0x00027eb8, 256);

// 0x07027FB8 - 0x070280A8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07027FB8, 0x004d1910, 104662, 0x00027fb8, 240);

// 0x070280A8 - 0x07028148
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070280A8, 0x004d1910, 104662, 0x000280a8, 160);

// 0x07028148 - 0x07028248
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028148, 0x004d1910, 104662, 0x00028148, 256);

// 0x07028248 - 0x07028328
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028248, 0x004d1910, 104662, 0x00028248, 224);

// 0x07028328 - 0x07028408
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028328, 0x004d1910, 104662, 0x00028328, 224);

// 0x07028408 - 0x07028508
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028408, 0x004d1910, 104662, 0x00028408, 256);

// 0x07028508 - 0x07028578
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028508, 0x004d1910, 104662, 0x00028508, 112);

// 0x07028578 - 0x07028668
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028578, 0x004d1910, 104662, 0x00028578, 240);

// 0x07028668 - 0x07028718
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028668, 0x004d1910, 104662, 0x00028668, 176);

// 0x07028718 - 0x07028818
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028718, 0x004d1910, 104662, 0x00028718, 256);

// 0x07028818 - 0x07028918
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028818, 0x004d1910, 104662, 0x00028818, 256);

// 0x07028918 - 0x07028A08
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028918, 0x004d1910, 104662, 0x00028918, 240);

// 0x07028A08 - 0x07028AF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028A08, 0x004d1910, 104662, 0x00028a08, 240);

// 0x07028AF8 - 0x07028BF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028AF8, 0x004d1910, 104662, 0x00028af8, 256);

// 0x07028BF8 - 0x07028C78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028BF8, 0x004d1910, 104662, 0x00028bf8, 128);

// 0x07028C78 - 0x07028D78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028C78, 0x004d1910, 104662, 0x00028c78, 256);

// 0x07028D78 - 0x07028E78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028D78, 0x004d1910, 104662, 0x00028d78, 256);

// 0x07028E78 - 0x07028F68
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028E78, 0x004d1910, 104662, 0x00028e78, 240);

// 0x07028F68 - 0x07029028
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07028F68, 0x004d1910, 104662, 0x00028f68, 192);

// 0x07029028 - 0x07029128
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07029028, 0x004d1910, 104662, 0x00029028, 256);

// 0x07029128 - 0x070291B8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07029128, 0x004d1910, 104662, 0x00029128, 144);

// 0x070291B8 - 0x070299D0
static const Gfx ttm_seg7_dl_070291B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_0900B800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07025FF0.l, 1),
    gsSPLight(&ttm_seg7_lights_07025FF0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07026128, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0,  2,  1, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026228, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026328, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026428, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  7,  3,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_07026008.l, 1),
    gsSPLight(&ttm_seg7_lights_07026008.a, 2),
    gsSPVertex(ttm_seg7_vertex_070264A8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSPLight(&ttm_seg7_lights_07026020.l, 1),
    gsSPLight(&ttm_seg7_lights_07026020.a, 2),
    gsSPVertex(ttm_seg7_vertex_07026568, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  2,  1, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026668, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026758, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPLight(&ttm_seg7_lights_07026038.l, 1),
    gsSPLight(&ttm_seg7_lights_07026038.a, 2),
    gsSPVertex(ttm_seg7_vertex_07026848, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026928, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 1,  6,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_07026050.l, 1),
    gsSPLight(&ttm_seg7_lights_07026050.a, 2),
    gsSPVertex(ttm_seg7_vertex_07026998, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSPLight(&ttm_seg7_lights_07026068.l, 1),
    gsSPLight(&ttm_seg7_lights_07026068.a, 2),
    gsSPVertex(ttm_seg7_vertex_07026A38, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_07026080.l, 1),
    gsSPLight(&ttm_seg7_lights_07026080.a, 2),
    gsSPVertex(ttm_seg7_vertex_07026AB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026BA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026C98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 15,  0,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026D98, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026E78, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07026098.l, 1),
    gsSPLight(&ttm_seg7_lights_07026098.a, 2),
    gsSPVertex(ttm_seg7_vertex_07026EB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07026FB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070270B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070271A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPLight(&ttm_seg7_lights_070260B0.l, 1),
    gsSPLight(&ttm_seg7_lights_070260B0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07027288, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027388, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027488, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027588, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_070260C8.l, 1),
    gsSPLight(&ttm_seg7_lights_070260C8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07027668, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027758, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9,  0, 10, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027838, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027928, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027AF8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070299D0 - 0x07029A18
static const Gfx ttm_seg7_dl_070299D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07026080.l, 1),
    gsSPLight(&ttm_seg7_lights_07026080.a, 2),
    gsSPVertex(ttm_seg7_vertex_07027BA8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07029A18 - 0x0702A0D8
static const Gfx ttm_seg7_dl_07029A18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_070260E0.l, 1),
    gsSPLight(&ttm_seg7_lights_070260E0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07027BE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027CD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9,  6,  8, 0x0,  6, 10,  7, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07027DC8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07025FF0.l, 1),
    gsSPLight(&ttm_seg7_lights_07025FF0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07027E38, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_07026008.l, 1),
    gsSPLight(&ttm_seg7_lights_07026008.a, 2),
    gsSPVertex(ttm_seg7_vertex_07027EB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07026020.l, 1),
    gsSPLight(&ttm_seg7_lights_07026020.a, 2),
    gsSPVertex(ttm_seg7_vertex_07027FB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_070280A8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  2,  8,  0, 0x0),
    gsSP1Triangle( 0,  9,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07026038.l, 1),
    gsSPLight(&ttm_seg7_lights_07026038.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028148, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 12, 11, 0x0, 15,  1,  0, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028248, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028328, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  4,  7, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028408, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11,  2, 12, 0x0),
    gsSP2Triangles(11,  0,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028508, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  6,  4, 0x0),
    gsSPLight(&ttm_seg7_lights_07026050.l, 1),
    gsSPLight(&ttm_seg7_lights_07026050.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028578, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028668, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07026068.l, 1),
    gsSPLight(&ttm_seg7_lights_07026068.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028718, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  1, 15,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_07026080.l, 1),
    gsSPLight(&ttm_seg7_lights_07026080.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028818, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07026098.l, 1),
    gsSPLight(&ttm_seg7_lights_07026098.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028AF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 1,  9, 12, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028BF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_070260B0.l, 1),
    gsSPLight(&ttm_seg7_lights_070260B0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028C78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPLight(&ttm_seg7_lights_070260F8.l, 1),
    gsSPLight(&ttm_seg7_lights_070260F8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028D78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_070260C8.l, 1),
    gsSPLight(&ttm_seg7_lights_070260C8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07028E78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07028F68, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0702A0D8 - 0x0702A1B8
static const Gfx ttm_seg7_dl_0702A0D8[] = {
    gsSPLight(&ttm_seg7_lights_07026110.l, 1),
    gsSPLight(&ttm_seg7_lights_07026110.a, 2),
    gsSPVertex(ttm_seg7_vertex_07029028, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0,  3, 11, 12, 0x0),
    gsSP2Triangles( 3, 12, 13, 0x0,  3, 13,  4, 0x0),
    gsSP2Triangles(14, 12, 11, 0x0,  8,  9, 15, 0x0),
    gsSP2Triangles( 8, 15, 14, 0x0, 14, 11,  8, 0x0),
    gsSPVertex(ttm_seg7_vertex_07029128, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  1,  3,  5, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  2,  7,  4, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  5,  3,  8, 0x0),
    gsSP1Triangle( 5,  8,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0702A1B8 - 0x0702A2A0
const Gfx ttm_seg7_dl_0702A1B8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(980, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_070291B8),
    gsSPDisplayList(ttm_seg7_dl_070299D0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07029A18),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(ttm_seg7_dl_0702A0D8),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
