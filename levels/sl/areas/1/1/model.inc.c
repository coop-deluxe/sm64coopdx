#include "pc/rom_assets.h"
// 0x07002800 - 0x07002818
static const Lights1 sl_seg7_lights_07002800 = gdSPDefLights1(
    0x59, 0x59, 0x59,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07002818 - 0x07002830
static const Lights1 sl_seg7_lights_07002818 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07002830 - 0x07002910
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002830, 0x00405fb0, 34952, 0x00002830, 224);

// 0x07002910 - 0x07002A10
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002910, 0x00405fb0, 34952, 0x00002910, 256);

// 0x07002A10 - 0x07002B10
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002A10, 0x00405fb0, 34952, 0x00002a10, 256);

// 0x07002B10 - 0x07002C00
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002B10, 0x00405fb0, 34952, 0x00002b10, 240);

// 0x07002C00 - 0x07002D00
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002C00, 0x00405fb0, 34952, 0x00002c00, 256);

// 0x07002D00 - 0x07002DF0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002D00, 0x00405fb0, 34952, 0x00002d00, 240);

// 0x07002DF0 - 0x07002EE0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002DF0, 0x00405fb0, 34952, 0x00002df0, 240);

// 0x07002EE0 - 0x07002FE0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002EE0, 0x00405fb0, 34952, 0x00002ee0, 256);

// 0x07002FE0 - 0x070030E0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07002FE0, 0x00405fb0, 34952, 0x00002fe0, 256);

// 0x070030E0 - 0x070031C0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070030E0, 0x00405fb0, 34952, 0x000030e0, 224);

// 0x070031C0 - 0x070032C0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070031C0, 0x00405fb0, 34952, 0x000031c0, 256);

// 0x070032C0 - 0x070033C0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070032C0, 0x00405fb0, 34952, 0x000032c0, 256);

// 0x070033C0 - 0x070034B0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070033C0, 0x00405fb0, 34952, 0x000033c0, 240);

// 0x070034B0 - 0x070035A0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070034B0, 0x00405fb0, 34952, 0x000034b0, 240);

// 0x070035A0 - 0x07003680
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070035A0, 0x00405fb0, 34952, 0x000035a0, 224);

// 0x07003680 - 0x07003780
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003680, 0x00405fb0, 34952, 0x00003680, 256);

// 0x07003780 - 0x07003860
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003780, 0x00405fb0, 34952, 0x00003780, 224);

// 0x07003860 - 0x07003960
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003860, 0x00405fb0, 34952, 0x00003860, 256);

// 0x07003960 - 0x07003A60
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003960, 0x00405fb0, 34952, 0x00003960, 256);

// 0x07003A60 - 0x07003B60
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003A60, 0x00405fb0, 34952, 0x00003a60, 256);

// 0x07003B60 - 0x07003C40
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003B60, 0x00405fb0, 34952, 0x00003b60, 224);

// 0x07003C40 - 0x07003D30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003C40, 0x00405fb0, 34952, 0x00003c40, 240);

// 0x07003D30 - 0x07003E10
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003D30, 0x00405fb0, 34952, 0x00003d30, 224);

// 0x07003E10 - 0x07003EF0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003E10, 0x00405fb0, 34952, 0x00003e10, 224);

// 0x07003EF0 - 0x07003FE0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003EF0, 0x00405fb0, 34952, 0x00003ef0, 240);

// 0x07003FE0 - 0x070040E0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07003FE0, 0x00405fb0, 34952, 0x00003fe0, 256);

// 0x070040E0 - 0x070041D0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070040E0, 0x00405fb0, 34952, 0x000040e0, 240);

// 0x070041D0 - 0x070042B0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070041D0, 0x00405fb0, 34952, 0x000041d0, 224);

// 0x070042B0 - 0x07004390
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070042B0, 0x00405fb0, 34952, 0x000042b0, 224);

// 0x07004390 - 0x07004490
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07004390, 0x00405fb0, 34952, 0x00004390, 256);

// 0x07004490 - 0x07004590
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07004490, 0x00405fb0, 34952, 0x00004490, 256);

// 0x07004590 - 0x07004620
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07004590, 0x00405fb0, 34952, 0x00004590, 144);

// 0x07004620 - 0x07004670
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07004620, 0x00405fb0, 34952, 0x00004620, 80);

// 0x07004670 - 0x070046F0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07004670, 0x00405fb0, 34952, 0x00004670, 128);

// 0x070046F0 - 0x07004750
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070046F0, 0x00405fb0, 34952, 0x000046f0, 96);

// 0x07004750 - 0x07004830
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07004750, 0x00405fb0, 34952, 0x00004750, 224);

// 0x07004830 - 0x07005370
static const Gfx sl_seg7_dl_07004830[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sl_seg7_lights_07002800.l, 1),
    gsSPLight(&sl_seg7_lights_07002800.a, 2),
    gsSPVertex(sl_seg7_vertex_07002830, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  1,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0,  9,  1, 11, 0x0),
    gsSP1Triangle( 2,  1, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07002910, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 5,  8,  3, 0x0,  9,  3, 10, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0,  0, 12, 13, 0x0),
    gsSP2Triangles( 0, 14, 12, 0x0,  1,  0, 13, 0x0),
    gsSP1Triangle(15,  1, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07002A10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 10, 13, 14, 0x0),
    gsSP2Triangles(10, 14, 15, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 8, 12, 10, 0x0, 15, 11, 10, 0x0),
    gsSPVertex(sl_seg7_vertex_07002B10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  5,  6,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  1, 10, 12, 0x0),
    gsSP1Triangle(13, 14,  8, 0x0),
    gsSPVertex(sl_seg7_vertex_07002C00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0,  1,  3, 12, 0x0),
    gsSP2Triangles( 7,  6, 13, 0x0,  7, 13, 14, 0x0),
    gsSP1Triangle(15, 13,  6, 0x0),
    gsSPVertex(sl_seg7_vertex_07002D00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP2Triangles(10, 14, 13, 0x0,  9,  7, 12, 0x0),
    gsSPVertex(sl_seg7_vertex_07002DF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  9, 0x0,  0, 10,  9, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07002EE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 8,  6, 12, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07002FE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0,  8, 10, 12, 0x0),
    gsSP2Triangles(10,  9, 14, 0x0, 15, 12, 10, 0x0),
    gsSPVertex(sl_seg7_vertex_070030E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle( 9, 13, 10, 0x0),
    gsSPVertex(sl_seg7_vertex_070031C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 8,  3,  2, 0x0,  8,  2,  9, 0x0),
    gsSP2Triangles( 8, 10,  3, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_070032C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  9,  8, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_070033C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_070034B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0,  6, 11, 10, 0x0),
    gsSP2Triangles( 9,  8, 12, 0x0,  8, 13, 12, 0x0),
    gsSP1Triangle(14, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_070035A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  3,  5, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  6,  2,  4, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  7, 11, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles(13,  8, 10, 0x0, 13, 12,  8, 0x0),
    gsSPVertex(sl_seg7_vertex_07003680, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11,  9,  8, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(13,  9, 11, 0x0, 10,  9, 14, 0x0),
    gsSP2Triangles(13, 14,  9, 0x0, 15,  2,  1, 0x0),
    gsSPVertex(sl_seg7_vertex_07003780, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  6,  4,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 13, 11, 0x0),
    gsSPVertex(sl_seg7_vertex_07003860, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9,  2, 10, 0x0,  2, 12, 10, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07003960, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9,  8,  5, 0x0,  5, 10,  9, 0x0),
    gsSP2Triangles( 8,  9, 11, 0x0,  8, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07003A60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 5, 11, 12, 0x0,  5, 10, 11, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07003B60, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  4,  3,  6, 0x0),
    gsSP2Triangles( 5,  7,  3, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 4,  8, 10, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(13, 10,  9, 0x0,  4, 10,  5, 0x0),
    gsSPVertex(sl_seg7_vertex_07003C40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 10,  8, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07003D30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  4,  5,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07003E10, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9,  5, 10, 0x0),
    gsSP2Triangles( 5,  7, 10, 0x0, 11, 10,  7, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0,  7,  6, 12, 0x0),
    gsSP1Triangle(11,  7, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07003EF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8, 11, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13,  0, 14, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07003FE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  0,  9, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0,  0, 10, 11, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0,  5, 13, 14, 0x0),
    gsSP1Triangle( 6, 15,  7, 0x0),
    gsSPVertex(sl_seg7_vertex_070040E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12,  8, 13, 0x0),
    gsSP1Triangle( 8, 14, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_070041D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_070042B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 3,  6,  2, 0x0,  6,  5,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles( 7, 12, 11, 0x0, 12,  7,  9, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 13, 10, 11, 0x0),
    gsSP2Triangles(10, 13,  9, 0x0, 13, 12,  9, 0x0),
    gsSPVertex(sl_seg7_vertex_07004390, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 4,  7,  6, 0x0,  6,  8,  5, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10,  3, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0,  9,  7, 11, 0x0),
    gsSP2Triangles( 3, 10, 11, 0x0,  3, 11,  4, 0x0),
    gsSP2Triangles( 4, 11,  7, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(15,  0,  2, 0x0),
    gsSPVertex(sl_seg7_vertex_07004490, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  1,  6,  2, 0x0),
    gsSP2Triangles( 6,  5,  2, 0x0,  5,  3,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles(12,  7,  9, 0x0,  7, 12, 11, 0x0),
    gsSP2Triangles(12, 10, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07004590, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  5,  4,  7, 0x0),
    gsSP1Triangle( 4,  8,  7, 0x0),
    gsSPLight(&sl_seg7_lights_07002818.l, 1),
    gsSPLight(&sl_seg7_lights_07002818.a, 2),
    gsSPVertex(sl_seg7_vertex_07004620, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 3,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005370 - 0x070053C8
static const Gfx sl_seg7_dl_07005370[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sl_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sl_seg7_lights_07002800.l, 1),
    gsSPLight(&sl_seg7_lights_07002800.a, 2),
    gsSPVertex(sl_seg7_vertex_07004670, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070053C8 - 0x07005410
static const Gfx sl_seg7_dl_070053C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sl_seg7_texture_07001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_070046F0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  1,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005410 - 0x07005478
static const Gfx sl_seg7_dl_07005410[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07004750, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005478 - 0x07005520
const Gfx sl_seg7_dl_07005478[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_07004830),
    gsSPDisplayList(sl_seg7_dl_07005370),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_070053C8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_07005410),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
