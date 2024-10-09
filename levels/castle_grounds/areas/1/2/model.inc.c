#include "pc/rom_assets.h"
// 0x07006ED8 - 0x07006EF0
static const Lights1 castle_grounds_seg7_lights_07006ED8 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07006EF0 - 0x07006F08
static const Lights1 castle_grounds_seg7_lights_07006EF0 = gdSPDefLights1(
    0x4e, 0x4e, 0x53,
    0xc4, 0xc4, 0xd0, 0x28, 0x28, 0x28
);

// 0x07006F08 - 0x07006F20
static const Lights1 castle_grounds_seg7_lights_07006F08 = gdSPDefLights1(
    0x36, 0x36, 0x37,
    0x89, 0x89, 0x8a, 0x28, 0x28, 0x28
);

// 0x07006F20 - 0x07006F38
static const Lights1 castle_grounds_seg7_lights_07006F20 = gdSPDefLights1(
    0x2d, 0x2d, 0x38,
    0x72, 0x72, 0x8c, 0x28, 0x28, 0x28
);

// 0x07006F38 - 0x07006F50
static const Lights1 castle_grounds_seg7_lights_07006F38 = gdSPDefLights1(
    0x29, 0x29, 0x2a,
    0x67, 0x67, 0x69, 0x28, 0x28, 0x28
);

// 0x07006F50 - 0x07006F68
static const Lights1 castle_grounds_seg7_lights_07006F50 = gdSPDefLights1(
    0x56, 0x56, 0x56,
    0xd8, 0xd8, 0xd8, 0x28, 0x28, 0x28
);

// 0x07006F68 - 0x07006F80
static const Lights1 castle_grounds_seg7_lights_07006F68 = gdSPDefLights1(
    0x23, 0x23, 0x27,
    0x58, 0x58, 0x62, 0x28, 0x28, 0x28
);

// 0x07006F80 - 0x07006F98
static const Lights1 castle_grounds_seg7_lights_07006F80 = gdSPDefLights1(
#ifdef ENHANCE_LEVEL_TEXTURES
    0x55, 0x55, 0x55,
    0xff, 0xff, 0x0ff, 0x28, 0x28, 0x28
#else
    0x13, 0x57, 0x00,
    0x30, 0xdb, 0x02, 0x28, 0x28, 0x28
#endif
);

// 0x07006F98 - 0x07006FD8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07006F98, 0x0044abc0, 39442, 0x00006f98, 64);

// 0x07006FD8 - 0x07007018
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07006FD8, 0x0044abc0, 39442, 0x00006fd8, 64);

// 0x07007018 - 0x07007118
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007018, 0x0044abc0, 39442, 0x00007018, 256);

// 0x07007118 - 0x07007208
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007118, 0x0044abc0, 39442, 0x00007118, 240);

// 0x07007208 - 0x07007308
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007208, 0x0044abc0, 39442, 0x00007208, 256);

// 0x07007308 - 0x07007388
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007308, 0x0044abc0, 39442, 0x00007308, 128);

// 0x07007388 - 0x07007488
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007388, 0x0044abc0, 39442, 0x00007388, 256);

// 0x07007488 - 0x07007588
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007488, 0x0044abc0, 39442, 0x00007488, 256);

// 0x07007588 - 0x07007688
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007588, 0x0044abc0, 39442, 0x00007588, 256);

// 0x07007688 - 0x07007788
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007688, 0x0044abc0, 39442, 0x00007688, 256);

// 0x07007788 - 0x070077B8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007788, 0x0044abc0, 39442, 0x00007788, 48);

// 0x070077B8 - 0x07007858
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070077B8, 0x0044abc0, 39442, 0x000077b8, 160);

// 0x07007858 - 0x07007928
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007858, 0x0044abc0, 39442, 0x00007858, 208);

// 0x07007928 - 0x07007968
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007928, 0x0044abc0, 39442, 0x00007928, 64);

// 0x07007968 - 0x070079C8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007968, 0x0044abc0, 39442, 0x00007968, 96);

// 0x070079C8 - 0x07007A08
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070079C8, 0x0044abc0, 39442, 0x000079c8, 64);

// 0x07007A08 - 0x07007A48
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007A08, 0x0044abc0, 39442, 0x00007a08, 64);

// 0x07007A48 - 0x07007B38
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007A48, 0x0044abc0, 39442, 0x00007a48, 240);

// 0x07007B38 - 0x07007BC8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007B38, 0x0044abc0, 39442, 0x00007b38, 144);

// 0x07007BC8 - 0x07007C98
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007BC8, 0x0044abc0, 39442, 0x00007bc8, 208);

// 0x07007C98 - 0x07007D58
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007C98, 0x0044abc0, 39442, 0x00007c98, 192);

// 0x07007D58 - 0x07007D98
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007D58, 0x0044abc0, 39442, 0x00007d58, 64);

// 0x07007D98 - 0x07007E78
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007D98, 0x0044abc0, 39442, 0x00007d98, 224);

// 0x07007E78 - 0x07007F78
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007E78, 0x0044abc0, 39442, 0x00007e78, 256);

// 0x07007F78 - 0x07008078
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07007F78, 0x0044abc0, 39442, 0x00007f78, 256);

// 0x07008078 - 0x07008178
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008078, 0x0044abc0, 39442, 0x00008078, 256);

// 0x07008178 - 0x07008268
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008178, 0x0044abc0, 39442, 0x00008178, 240);

// 0x07008268 - 0x070082C8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008268, 0x0044abc0, 39442, 0x00008268, 96);

// 0x070082C8 - 0x07008338
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070082C8, 0x0044abc0, 39442, 0x000082c8, 112);

// 0x07008338 - 0x07008368
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008338, 0x0044abc0, 39442, 0x00008338, 48);

// 0x07008368 - 0x07008458
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008368, 0x0044abc0, 39442, 0x00008368, 240);

// 0x07008458 - 0x07008558
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008458, 0x0044abc0, 39442, 0x00008458, 256);

// 0x07008558 - 0x07008638
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008558, 0x0044abc0, 39442, 0x00008558, 224);

// 0x07008638 - 0x07008738
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008638, 0x0044abc0, 39442, 0x00008638, 256);

// 0x07008738 - 0x07008818
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008738, 0x0044abc0, 39442, 0x00008738, 224);

// 0x07008818 - 0x07008908
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008818, 0x0044abc0, 39442, 0x00008818, 240);

// 0x07008908 - 0x070089B8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_07008908, 0x0044abc0, 39442, 0x00008908, 176);

// 0x070089B8 - 0x070089F8
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_070089B8, 0x0044abc0, 39442, 0x000089b8, 64);

// 0x070089F8 - 0x07008A68
static const Gfx castle_grounds_seg7_dl_070089F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 16 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07006F98, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006EF0.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006EF0.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07006FD8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008A68 - 0x07008BF0
static const Gfx castle_grounds_seg7_dl_07008A68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007018, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12,  8, 11, 0x0, 13, 12, 11, 0x0),
    gsSP2Triangles(11, 14, 13, 0x0, 13, 14,  4, 0x0),
    gsSP2Triangles(15,  4, 14, 0x0, 15,  5,  4, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007118, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0,  9,  0, 10, 0x0),
    gsSP2Triangles(11, 10,  0, 0x0, 12, 13,  0, 0x0),
    gsSP2Triangles( 0, 13, 11, 0x0,  2, 14,  0, 0x0),
    gsSP1Triangle(12,  0, 14, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007208, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  5,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 1, 10,  5, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles(12,  9,  7, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007308, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  3,  7,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008BF0 - 0x07008D70
static const Gfx castle_grounds_seg7_dl_07008BF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_07007388, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11,  8, 12, 0x0, 10, 12,  8, 0x0),
    gsSP2Triangles( 9, 13, 10, 0x0,  9, 14, 13, 0x0),
    gsSP1Triangle(11, 12, 15, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007488, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 11, 10, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 15, 13, 14, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007588, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 13, 12, 0x0),
    gsSP1Triangle(15, 10,  9, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007688, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 2,  6,  0, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 12, 11,  9, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007788, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008D70 - 0x07008DE8
static const Gfx castle_grounds_seg7_dl_07008D70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_070077B8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9,  6,  8, 0x0,  7,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008DE8 - 0x07008EE8
static const Gfx castle_grounds_seg7_dl_07008DE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007858, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  1,  3,  5, 0x0),
    gsSP2Triangles( 4,  2,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  7,  5,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11,  3, 0x0),
    gsSP2Triangles( 3,  8, 10, 0x0,  8,  3,  0, 0x0),
    gsSP1Triangle( 4,  7, 12, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007928, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007968, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008EE8 - 0x07008F48
static const Gfx castle_grounds_seg7_dl_07008EE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_0900B400),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_070079C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006F20.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F20.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007A08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008F48 - 0x07009010
static const Gfx castle_grounds_seg7_dl_07008F48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007A48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 13, 14,  9, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007B38, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 4,  7,  5, 0x0,  6,  7,  4, 0x0),
    gsSP1Triangle( 7,  8,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009010 - 0x07009330
static const Gfx castle_grounds_seg7_dl_07009010[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_07007BC8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(10, 12, 11, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006F38.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F38.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007C98, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0,  8,  9, 11, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006F50.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F50.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007D58, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07007D98, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  5,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10,  1, 13, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007E78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles( 2,  8, 11, 0x0,  2,  9,  8, 0x0),
    gsSP2Triangles( 9,  2,  1, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles(12,  0,  2, 0x0, 13, 14,  0, 0x0),
    gsSP1Triangle(15, 11, 10, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07007F78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12,  6, 13, 0x0),
    gsSP1Triangle( 6, 15, 13, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07008078, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  4,  1,  3, 0x0),
    gsSP2Triangles( 9,  4,  3, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07008178, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 8, 14, 13, 0x0, 12,  8, 13, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006F68.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F68.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07008268, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_070082C8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 5,  4,  6, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006ED8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07008338, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009330 - 0x07009568
static const Gfx castle_grounds_seg7_dl_07009330[] = {
#ifdef ENHANCE_LEVEL_TEXTURES
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, castle_grounds_seg7_texture_07003000),
#else
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09004800),
#endif
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&castle_grounds_seg7_lights_07006F80.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F80.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07008368, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0,  6,  5, 11, 0x0),
    gsSP2Triangles( 6, 11, 12, 0x0,  2, 13,  0, 0x0),
    gsSP1Triangle( 0, 13, 14, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07008458, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  4,  3, 0x0,  9,  1, 10, 0x0),
    gsSP2Triangles( 3, 11,  8, 0x0, 12, 11,  3, 0x0),
    gsSP2Triangles( 9,  2,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07008558, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  5, 11, 10, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0, 11, 13,  9, 0x0),
    gsSP1Triangle( 5,  4, 11, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07008638, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11,  9, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles(14,  0, 13, 0x0,  1,  0, 15, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07008738, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 6,  0,  5, 0x0,  1,  0,  6, 0x0),
    gsSP2Triangles( 4,  7,  5, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(castle_grounds_seg7_vertex_07008818, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009568 - 0x070095F0
static const Gfx castle_grounds_seg7_dl_07009568[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&castle_grounds_seg7_lights_07006F38.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F38.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_07008908, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_07006F08.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_070089B8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070095F0 - 0x070096F8
const Gfx castle_grounds_seg7_dl_070095F0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_070089F8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_07008A68),
    gsSPDisplayList(castle_grounds_seg7_dl_07008BF0),
    gsSPDisplayList(castle_grounds_seg7_dl_07008D70),
    gsSPDisplayList(castle_grounds_seg7_dl_07008DE8),
    gsSPDisplayList(castle_grounds_seg7_dl_07008EE8),
    gsSPDisplayList(castle_grounds_seg7_dl_07008F48),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_07009010),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_07009330),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_07009568),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
