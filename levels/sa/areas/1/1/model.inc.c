#include "pc/rom_assets.h"
// 0x07000000 - 0x07000018
static const Lights1 sa_lights = gdSPDefLights1(
    0x00, 0x7f, 0x99,
    0x00, 0xd4, 0xff, 0x28, 0x28, 0x28
);

// 0x07000018 - 0x070000D8
ROM_ASSET_LOAD_VTX(sa_vertex_07000018, 0x0046b090, 4364, 0x00000018, 192);

// 0x070000D8 - 0x070001C8
ROM_ASSET_LOAD_VTX(sa_vertex_070000D8, 0x0046b090, 4364, 0x000000d8, 240);

// 0x070001C8 - 0x070002C8
ROM_ASSET_LOAD_VTX(sa_vertex_070001C8, 0x0046b090, 4364, 0x000001c8, 256);

// 0x070002C8 - 0x070003C8
ROM_ASSET_LOAD_VTX(sa_vertex_070002C8, 0x0046b090, 4364, 0x000002c8, 256);

// 0x070003C8 - 0x070004B8
ROM_ASSET_LOAD_VTX(sa_vertex_070003C8, 0x0046b090, 4364, 0x000003c8, 240);

// 0x070004B8 - 0x070005B8
ROM_ASSET_LOAD_VTX(sa_vertex_070004B8, 0x0046b090, 4364, 0x000004b8, 256);

// 0x070005B8 - 0x07000698
ROM_ASSET_LOAD_VTX(sa_vertex_070005B8, 0x0046b090, 4364, 0x000005b8, 224);

// 0x07000698 - 0x07000798
ROM_ASSET_LOAD_VTX(sa_vertex_07000698, 0x0046b090, 4364, 0x00000698, 256);

// 0x07000798 - 0x07000898
ROM_ASSET_LOAD_VTX(sa_vertex_07000798, 0x0046b090, 4364, 0x00000798, 256);

// 0x07000898 - 0x07000998
ROM_ASSET_LOAD_VTX(sa_vertex_07000898, 0x0046b090, 4364, 0x00000898, 256);

// 0x07000998 - 0x07000A88
ROM_ASSET_LOAD_VTX(sa_vertex_07000998, 0x0046b090, 4364, 0x00000998, 240);

// 0x07000A88 - 0x07000B68
ROM_ASSET_LOAD_VTX(sa_vertex_07000A88, 0x0046b090, 4364, 0x00000a88, 224);

// 0x07000B68 - 0x07000C58
ROM_ASSET_LOAD_VTX(sa_vertex_07000B68, 0x0046b090, 4364, 0x00000b68, 240);

// 0x07000C58 - 0x07000D58
ROM_ASSET_LOAD_VTX(sa_vertex_07000C58, 0x0046b090, 4364, 0x00000c58, 256);

// 0x07000D58 - 0x07000E48
ROM_ASSET_LOAD_VTX(sa_vertex_07000D58, 0x0046b090, 4364, 0x00000d58, 240);

// 0x07000E48 - 0x07000F48
ROM_ASSET_LOAD_VTX(sa_vertex_07000E48, 0x0046b090, 4364, 0x00000e48, 256);

// 0x07000F48 - 0x07001048
ROM_ASSET_LOAD_VTX(sa_vertex_07000F48, 0x0046b090, 4364, 0x00000f48, 256);

// 0x07001048 - 0x07001128
ROM_ASSET_LOAD_VTX(sa_vertex_07001048, 0x0046b090, 4364, 0x00001048, 224);

// 0x07001128 - 0x07001218
ROM_ASSET_LOAD_VTX(sa_vertex_07001128, 0x0046b090, 4364, 0x00001128, 240);

// 0x07001218 - 0x07001308
ROM_ASSET_LOAD_VTX(sa_vertex_07001218, 0x0046b090, 4364, 0x00001218, 240);

// 0x07001308 - 0x070013E8
ROM_ASSET_LOAD_VTX(sa_vertex_07001308, 0x0046b090, 4364, 0x00001308, 224);

// 0x070013E8 - 0x070014C8
ROM_ASSET_LOAD_VTX(sa_vertex_070013E8, 0x0046b090, 4364, 0x000013e8, 224);

// 0x070014C8 - 0x070015B8
ROM_ASSET_LOAD_VTX(sa_vertex_070014C8, 0x0046b090, 4364, 0x000014c8, 240);

// 0x070015B8 - 0x070016B8
ROM_ASSET_LOAD_VTX(sa_vertex_070015B8, 0x0046b090, 4364, 0x000015b8, 256);

// 0x070016B8 - 0x070017B8
ROM_ASSET_LOAD_VTX(sa_vertex_070016B8, 0x0046b090, 4364, 0x000016b8, 256);

// 0x070017B8 - 0x070018A8
ROM_ASSET_LOAD_VTX(sa_vertex_070017B8, 0x0046b090, 4364, 0x000017b8, 240);

// 0x070018A8 - 0x070019A8
ROM_ASSET_LOAD_VTX(sa_vertex_070018A8, 0x0046b090, 4364, 0x000018a8, 256);

// 0x070019A8 - 0x07001AA8
ROM_ASSET_LOAD_VTX(sa_vertex_070019A8, 0x0046b090, 4364, 0x000019a8, 256);

// 0x07001AA8 - 0x07001B98
ROM_ASSET_LOAD_VTX(sa_vertex_07001AA8, 0x0046b090, 4364, 0x00001aa8, 240);

// 0x07001B98 - 0x07001C78
ROM_ASSET_LOAD_VTX(sa_vertex_07001B98, 0x0046b090, 4364, 0x00001b98, 224);

// 0x07001C78 - 0x07001D78
ROM_ASSET_LOAD_VTX(sa_vertex_07001C78, 0x0046b090, 4364, 0x00001c78, 256);

// 0x07001D78 - 0x07001E78
ROM_ASSET_LOAD_VTX(sa_vertex_07001D78, 0x0046b090, 4364, 0x00001d78, 256);

// 0x07001E78 - 0x07001F78
ROM_ASSET_LOAD_VTX(sa_vertex_07001E78, 0x0046b090, 4364, 0x00001e78, 256);

// 0x07001F78 - 0x07002078
ROM_ASSET_LOAD_VTX(sa_vertex_07001F78, 0x0046b090, 4364, 0x00001f78, 256);

// 0x07002078 - 0x07002168
ROM_ASSET_LOAD_VTX(sa_vertex_07002078, 0x0046b090, 4364, 0x00002078, 240);

// 0x07002168 - 0x07002268
ROM_ASSET_LOAD_VTX(sa_vertex_07002168, 0x0046b090, 4364, 0x00002168, 256);

// 0x07002268 - 0x07002368
ROM_ASSET_LOAD_VTX(sa_vertex_07002268, 0x0046b090, 4364, 0x00002268, 256);

// 0x07002368 - 0x070023E8
ROM_ASSET_LOAD_VTX(sa_vertex_07002368, 0x0046b090, 4364, 0x00002368, 128);

// 0x070023E8 - 0x07002470
static const Gfx sa_dl_070023E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sa_lights.l, 1),
    gsSPLight(&sa_lights.a, 2),
    gsSPVertex(sa_vertex_07000018, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  2,  7,  3, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002470 - 0x070028F0
static const Gfx sa_dl_07002470[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sa_vertex_070000D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12,  3, 10, 0x0, 12, 13,  3, 0x0),
    gsSP1Triangle( 3, 14,  4, 0x0),
    gsSPVertex(sa_vertex_070001C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_070002C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_070003C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(sa_vertex_070004B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_070005B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sa_vertex_07000698, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_07000798, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13,  1, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0, 14,  0,  2, 0x0),
    gsSP1Triangle(14,  2, 15, 0x0),
    gsSPVertex(sa_vertex_07000898, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6, 10, 11, 0x0),
    gsSP2Triangles( 6, 11, 12, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(sa_vertex_07000998, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(sa_vertex_07000A88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sa_vertex_07000B68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(sa_vertex_07000C58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(sa_vertex_07000D58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(sa_vertex_07000E48, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_07000F48, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(sa_vertex_07001048, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  4,  6,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(sa_vertex_07001128, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x070028F0 - 0x07002DE8
static const Gfx sa_dl_070028F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sa_vertex_07001218, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(sa_vertex_07001308, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(sa_vertex_070013E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sa_vertex_070014C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(sa_vertex_070015B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  6, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_070016B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 5, 14,  6, 0x0,  5, 15, 14, 0x0),
    gsSPVertex(sa_vertex_070017B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(sa_vertex_070018A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_070019A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 2,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 1, 13, 14, 0x0,  1, 15,  2, 0x0),
    gsSP1Triangle( 1, 14, 15, 0x0),
    gsSPVertex(sa_vertex_07001AA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(sa_vertex_07001B98, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  7,  3, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(sa_vertex_07001C78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  0, 14, 15, 0x0),
    gsSPVertex(sa_vertex_07001D78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(sa_vertex_07001E78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 2,  9, 10, 0x0,  2, 11,  9, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(sa_vertex_07001F78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(sa_vertex_07002078, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 8, 14,  9, 0x0),
    gsSPVertex(sa_vertex_07002168, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sa_vertex_07002268, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(sa_vertex_07002368,  8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002DE8 - 0x07002E80
const Gfx sa_seg7_dl_07002DE8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sa_dl_070023E8),
    gsSPDisplayList(sa_dl_07002470),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sa_dl_070028F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
