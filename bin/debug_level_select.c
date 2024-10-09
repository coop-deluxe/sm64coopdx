#include "pc/rom_assets.h"
#include <ultra64.h>
#include "sm64.h"

#include "make_const_nonconst.h"

// 0x07000000 - 0x07000018
static const Lights1 debug_level_select_lights_07000000 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x50
);

// 0x07000018 - 0x07000108
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000018, 0x0026f420, 5278, 0x00000018, 240);

// 0x07000108 - 0x070001F8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000108, 0x0026f420, 5278, 0x00000108, 240);

// 0x070001F8 - 0x070002E8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070001F8, 0x0026f420, 5278, 0x000001f8, 240);

// 0x070002E8 - 0x070003D8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070002E8, 0x0026f420, 5278, 0x000002e8, 240);

// 0x070003D8 - 0x070004C8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070003D8, 0x0026f420, 5278, 0x000003d8, 240);

// 0x070004C8 - 0x070005B8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070004C8, 0x0026f420, 5278, 0x000004c8, 240);

// 0x070005B8 - 0x070006A8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070005B8, 0x0026f420, 5278, 0x000005b8, 240);

// 0x070006A8 - 0x07000798
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070006A8, 0x0026f420, 5278, 0x000006a8, 240);

// 0x07000798 - 0x07000858
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000798, 0x0026f420, 5278, 0x00000798, 192);

// 0x07000858 - 0x07000A28
const Gfx debug_level_select_dl_07000858[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_07000000),
    gsSPVertex(debug_level_select_vertex_07000018, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000108, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070001F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070002E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070003D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070004C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070005B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070006A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000798, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07000A28 - 0x07000A40
static const Lights1 debug_level_select_lights_07000A28 = gdSPDefLights1(
    0x00, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x00, 0x00, 0x50
);

// 0x07000A40 - 0x07000B30
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000A40, 0x0026f420, 5278, 0x00000a40, 240);

// 0x07000B30 - 0x07000C20
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000B30, 0x0026f420, 5278, 0x00000b30, 240);

// 0x07000C20 - 0x07000D10
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000C20, 0x0026f420, 5278, 0x00000c20, 240);

// 0x07000D10 - 0x07000E00
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000D10, 0x0026f420, 5278, 0x00000d10, 240);

// 0x07000E00 - 0x07000EF0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000E00, 0x0026f420, 5278, 0x00000e00, 240);

// 0x07000EF0 - 0x07000FE0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000EF0, 0x0026f420, 5278, 0x00000ef0, 240);

// 0x07000FE0 - 0x070010D0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07000FE0, 0x0026f420, 5278, 0x00000fe0, 240);

// 0x070010D0 - 0x07001100
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070010D0, 0x0026f420, 5278, 0x000010d0, 48);

// 0x07001100 - 0x07001288
const Gfx debug_level_select_dl_07001100[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_07000A28),
    gsSPVertex(debug_level_select_vertex_07000A40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000B30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000C20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000D10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000E00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000EF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07000FE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070010D0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07001288 - 0x070012A0
static const Lights1 debug_level_select_lights_07001288 = gdSPDefLights1(
    0x00, 0x56, 0x00,
    0x00, 0xad, 0x00, 0x00, 0x00, 0x50
);

// 0x070012A0 - 0x07001390
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070012A0, 0x0026f420, 5278, 0x000012a0, 240);

// 0x07001390 - 0x07001480
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001390, 0x0026f420, 5278, 0x00001390, 240);

// 0x07001480 - 0x07001570
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001480, 0x0026f420, 5278, 0x00001480, 240);

// 0x07001570 - 0x07001660
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001570, 0x0026f420, 5278, 0x00001570, 240);

// 0x07001660 - 0x07001750
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001660, 0x0026f420, 5278, 0x00001660, 240);

// 0x07001750 - 0x07001840
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001750, 0x0026f420, 5278, 0x00001750, 240);

// 0x07001840 - 0x07001930
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001840, 0x0026f420, 5278, 0x00001840, 240);

// 0x07001930 - 0x07001A20
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001930, 0x0026f420, 5278, 0x00001930, 240);

// 0x07001A20 - 0x07001B10
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001A20, 0x0026f420, 5278, 0x00001a20, 240);

// 0x07001B10 - 0x07001BA0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001B10, 0x0026f420, 5278, 0x00001b10, 144);

// 0x07001BA0 - 0x07001D98
const Gfx debug_level_select_dl_07001BA0[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_07001288),
    gsSPVertex(debug_level_select_vertex_070012A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001390, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001480, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001570, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001660, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001750, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001840, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001930, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001A20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001B10, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07001D98 - 0x07001DB0
static const Lights1 debug_level_select_lights_07001D98 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x50
);

// 0x07001DB0 - 0x07001EA0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001DB0, 0x0026f420, 5278, 0x00001db0, 240);

// 0x07001EA0 - 0x07001F90
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001EA0, 0x0026f420, 5278, 0x00001ea0, 240);

// 0x07001F90 - 0x07002080
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07001F90, 0x0026f420, 5278, 0x00001f90, 240);

// 0x07002080 - 0x07002170
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002080, 0x0026f420, 5278, 0x00002080, 240);

// 0x07002170 - 0x07002260
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002170, 0x0026f420, 5278, 0x00002170, 240);

// 0x07002260 - 0x07002350
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002260, 0x0026f420, 5278, 0x00002260, 240);

// 0x07002350 - 0x07002440
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002350, 0x0026f420, 5278, 0x00002350, 240);

// 0x07002440 - 0x07002530
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002440, 0x0026f420, 5278, 0x00002440, 240);

// 0x07002530 - 0x070025F0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002530, 0x0026f420, 5278, 0x00002530, 192);

// 0x070025F0 - 0x070027C0
const Gfx debug_level_select_dl_070025F0[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_07001D98),
    gsSPVertex(debug_level_select_vertex_07001DB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001EA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07001F90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002080, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002170, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002260, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002350, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002440, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002530, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x070027C0 - 0x070027D8
static const Lights1 debug_level_select_lights_070027C0 = gdSPDefLights1(
    0x00, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x00, 0x00, 0x50
);

// 0x070027D8 - 0x070028C8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070027D8, 0x0026f420, 5278, 0x000027d8, 240);

// 0x070028C8 - 0x070029B8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070028C8, 0x0026f420, 5278, 0x000028c8, 240);

// 0x070029B8 - 0x07002AA8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070029B8, 0x0026f420, 5278, 0x000029b8, 240);

// 0x07002AA8 - 0x07002B98
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002AA8, 0x0026f420, 5278, 0x00002aa8, 240);

// 0x07002B98 - 0x07002C88
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002B98, 0x0026f420, 5278, 0x00002b98, 240);

// 0x07002C88 - 0x07002D78
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002C88, 0x0026f420, 5278, 0x00002c88, 240);

// 0x07002D78 - 0x07002E68
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002D78, 0x0026f420, 5278, 0x00002d78, 240);

// 0x07002E68 - 0x07002F58
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002E68, 0x0026f420, 5278, 0x00002e68, 240);

// 0x07002F58 - 0x07003048
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07002F58, 0x0026f420, 5278, 0x00002f58, 240);

// 0x07003048 - 0x07003138
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003048, 0x0026f420, 5278, 0x00003048, 240);

// 0x07003138 - 0x07003228
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003138, 0x0026f420, 5278, 0x00003138, 240);

// 0x07003228 - 0x07003258
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003228, 0x0026f420, 5278, 0x00003228, 48);

// 0x07003258 - 0x070034A0
const Gfx debug_level_select_dl_07003258[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_070027C0),
    gsSPVertex(debug_level_select_vertex_070027D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070028C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070029B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002AA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002B98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002C88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002D78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002E68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07002F58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003048, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003138, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003228, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070034A0 - 0x070034B8
static const Lights1 debug_level_select_lights_070034A0 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x50
);

// 0x070034B8 - 0x070035A8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070034B8, 0x0026f420, 5278, 0x000034b8, 240);

// 0x070035A8 - 0x07003698
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070035A8, 0x0026f420, 5278, 0x000035a8, 240);

// 0x07003698 - 0x07003788
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003698, 0x0026f420, 5278, 0x00003698, 240);

// 0x07003788 - 0x07003878
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003788, 0x0026f420, 5278, 0x00003788, 240);

// 0x07003878 - 0x07003968
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003878, 0x0026f420, 5278, 0x00003878, 240);

// 0x07003968 - 0x07003A58
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003968, 0x0026f420, 5278, 0x00003968, 240);

// 0x07003A58 - 0x07003B48
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003A58, 0x0026f420, 5278, 0x00003a58, 240);

// 0x07003B48 - 0x07003C38
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003B48, 0x0026f420, 5278, 0x00003b48, 240);

// 0x07003C38 - 0x07003D28
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003C38, 0x0026f420, 5278, 0x00003c38, 240);

// 0x07003D28 - 0x07003DB8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003D28, 0x0026f420, 5278, 0x00003d28, 144);

// 0x07003DB8 - 0x07003FB0
const Gfx debug_level_select_dl_07003DB8[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_070034A0),
    gsSPVertex(debug_level_select_vertex_070034B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070035A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003698, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003788, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003878, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003968, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003A58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003B48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003C38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07003D28, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07003FB0 - 0x07003FC8
static const Lights1 debug_level_select_lights_07003FB0 = gdSPDefLights1(
    0x00, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x00, 0x00, 0x50
);

// 0x07003FC8 - 0x070040B8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07003FC8, 0x0026f420, 5278, 0x00003fc8, 240);

// 0x070040B8 - 0x070041A8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070040B8, 0x0026f420, 5278, 0x000040b8, 240);

// 0x070041A8 - 0x07004298
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070041A8, 0x0026f420, 5278, 0x000041a8, 240);

// 0x07004298 - 0x07004388
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004298, 0x0026f420, 5278, 0x00004298, 240);

// 0x07004388 - 0x07004478
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004388, 0x0026f420, 5278, 0x00004388, 240);

// 0x07004478 - 0x07004568
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004478, 0x0026f420, 5278, 0x00004478, 240);

// 0x07004568 - 0x07004658
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004568, 0x0026f420, 5278, 0x00004568, 240);

// 0x07004658 - 0x07004748
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004658, 0x0026f420, 5278, 0x00004658, 240);

// 0x07004748 - 0x07004838
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004748, 0x0026f420, 5278, 0x00004748, 240);

// 0x07004838 - 0x070048C8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004838, 0x0026f420, 5278, 0x00004838, 144);

// 0x070048C8 - 0x07004AC0
const Gfx debug_level_select_dl_070048C8[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_07003FB0),
    gsSPVertex(debug_level_select_vertex_07003FC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070040B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070041A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004298, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004388, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004478, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004568, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004658, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004748, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004838, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004AC0 - 0x07004AD8
static const Lights1 debug_level_select_lights_07004AC0 = gdSPDefLights1(
    0x00, 0x59, 0x00,
    0x00, 0xb2, 0x00, 0x00, 0x00, 0x50
);

// 0x07004AD8 - 0x07004BC8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004AD8, 0x0026f420, 5278, 0x00004ad8, 240);

// 0x07004BC8 - 0x07004CB8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004BC8, 0x0026f420, 5278, 0x00004bc8, 240);

// 0x07004CB8 - 0x07004DA8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004CB8, 0x0026f420, 5278, 0x00004cb8, 240);

// 0x07004DA8 - 0x07004E98
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004DA8, 0x0026f420, 5278, 0x00004da8, 240);

// 0x07004E98 - 0x07004F88
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004E98, 0x0026f420, 5278, 0x00004e98, 240);

// 0x07004F88 - 0x07005078
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07004F88, 0x0026f420, 5278, 0x00004f88, 240);

// 0x07005078 - 0x07005168
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005078, 0x0026f420, 5278, 0x00005078, 240);

// 0x07005168 - 0x07005258
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005168, 0x0026f420, 5278, 0x00005168, 240);

// 0x07005258 - 0x07005348
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005258, 0x0026f420, 5278, 0x00005258, 240);

// 0x07005348 - 0x07005438
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005348, 0x0026f420, 5278, 0x00005348, 240);

// 0x07005438 - 0x07005528
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005438, 0x0026f420, 5278, 0x00005438, 240);

// 0x07005528 - 0x07005558
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005528, 0x0026f420, 5278, 0x00005528, 48);

// 0x07005558 - 0x070057A0
const Gfx debug_level_select_dl_07005558[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_07004AC0),
    gsSPVertex(debug_level_select_vertex_07004AD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004BC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004CB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004DA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004E98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07004F88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005078, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005168, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005258, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005348, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005438, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005528, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070057A0 - 0x070057B8
static const Lights1 debug_level_select_lights_070057A0 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x50
);

// 0x070057B8 - 0x070058A8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070057B8, 0x0026f420, 5278, 0x000057b8, 240);

// 0x070058A8 - 0x07005998
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_070058A8, 0x0026f420, 5278, 0x000058a8, 240);

// 0x07005998 - 0x070059F8
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005998, 0x0026f420, 5278, 0x00005998, 96);

// 0x070059F8 - 0x07005A98
const Gfx debug_level_select_dl_070059F8[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_070057A0),
    gsSPVertex(debug_level_select_vertex_070057B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_070058A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005998, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005A98 - 0x07005AB0
static const Lights1 debug_level_select_lights_07005A98 = gdSPDefLights1(
    0x00, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x00, 0x00, 0x50
);

// 0x07005AB0 - 0x07005BA0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005AB0, 0x0026f420, 5278, 0x00005ab0, 240);

// 0x07005BA0 - 0x07005C90
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005BA0, 0x0026f420, 5278, 0x00005ba0, 240);

// 0x07005C90 - 0x07005D80
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005C90, 0x0026f420, 5278, 0x00005c90, 240);

// 0x07005D80 - 0x07005E70
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005D80, 0x0026f420, 5278, 0x00005d80, 240);

// 0x07005E70 - 0x07005F60
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005E70, 0x0026f420, 5278, 0x00005e70, 240);

// 0x07005F60 - 0x07006050
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07005F60, 0x0026f420, 5278, 0x00005f60, 240);

// 0x07006050 - 0x07006140
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07006050, 0x0026f420, 5278, 0x00006050, 240);

// 0x07006140 - 0x07006230
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07006140, 0x0026f420, 5278, 0x00006140, 240);

// 0x07006230 - 0x07006320
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07006230, 0x0026f420, 5278, 0x00006230, 240);

// 0x07006320 - 0x070063B0
ROM_ASSET_LOAD_VTX(debug_level_select_vertex_07006320, 0x0026f420, 5278, 0x00006320, 144);

// 0x070063B0 - 0x070065A8
const Gfx debug_level_select_dl_070063B0[] = {
    gsDPPipeSync(),
    gsSPSetLights1(debug_level_select_lights_07005A98),
    gsSPVertex(debug_level_select_vertex_07005AB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005BA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005C90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005D80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005E70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07005F60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07006050, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07006140, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07006230, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(debug_level_select_vertex_07006320, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

