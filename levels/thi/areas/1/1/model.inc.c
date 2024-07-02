#include "pc/rom_assets.h"
// 0x07001000 - 0x07001018
static const Lights1 thi_seg7_lights_07001000 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07001018 - 0x07001030
static const Lights1 thi_seg7_lights_07001018 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07001030 - 0x07001048
static const Lights1 thi_seg7_lights_07001030 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x07001048 - 0x07001060
static const Lights1 thi_seg7_lights_07001048 = gdSPDefLights1(
    0x7f, 0x7f, 0x3c,
    0xff, 0xff, 0x78, 0x28, 0x28, 0x28
);

// 0x07001060 - 0x07001140
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001060, 0x004246d0, 32780, 0x00001060, 224);

// 0x07001140 - 0x07001220
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001140, 0x004246d0, 32780, 0x00001140, 224);

// 0x07001220 - 0x07001310
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001220, 0x004246d0, 32780, 0x00001220, 240);

// 0x07001310 - 0x070013F0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001310, 0x004246d0, 32780, 0x00001310, 224);

// 0x070013F0 - 0x070014F0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070013F0, 0x004246d0, 32780, 0x000013f0, 256);

// 0x070014F0 - 0x070015E0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070014F0, 0x004246d0, 32780, 0x000014f0, 240);

// 0x070015E0 - 0x070016D0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070015E0, 0x004246d0, 32780, 0x000015e0, 240);

// 0x070016D0 - 0x070017D0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070016D0, 0x004246d0, 32780, 0x000016d0, 256);

// 0x070017D0 - 0x07001830
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070017D0, 0x004246d0, 32780, 0x000017d0, 96);

// 0x07001830 - 0x07001920
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001830, 0x004246d0, 32780, 0x00001830, 240);

// 0x07001920 - 0x07001960
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001920, 0x004246d0, 32780, 0x00001920, 64);

// 0x07001960 - 0x070019F0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001960, 0x004246d0, 32780, 0x00001960, 144);

// 0x070019F0 - 0x07001A50
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070019F0, 0x004246d0, 32780, 0x000019f0, 96);

// 0x07001A50 - 0x07001B30
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001A50, 0x004246d0, 32780, 0x00001a50, 224);

// 0x07001B30 - 0x07001C10
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001B30, 0x004246d0, 32780, 0x00001b30, 224);

// 0x07001C10 - 0x07001D10
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001C10, 0x004246d0, 32780, 0x00001c10, 256);

// 0x07001D10 - 0x07001E10
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001D10, 0x004246d0, 32780, 0x00001d10, 256);

// 0x07001E10 - 0x07001EF0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001E10, 0x004246d0, 32780, 0x00001e10, 224);

// 0x07001EF0 - 0x07001FF0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001EF0, 0x004246d0, 32780, 0x00001ef0, 256);

// 0x07001FF0 - 0x070020D0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07001FF0, 0x004246d0, 32780, 0x00001ff0, 224);

// 0x070020D0 - 0x070021C0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070020D0, 0x004246d0, 32780, 0x000020d0, 240);

// 0x070021C0 - 0x07002220
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070021C0, 0x004246d0, 32780, 0x000021c0, 96);

// 0x07002220 - 0x07002260
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002220, 0x004246d0, 32780, 0x00002220, 64);

// 0x07002260 - 0x07002360
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002260, 0x004246d0, 32780, 0x00002260, 256);

// 0x07002360 - 0x07002440
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002360, 0x004246d0, 32780, 0x00002360, 224);

// 0x07002440 - 0x07002530
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002440, 0x004246d0, 32780, 0x00002440, 240);

// 0x07002530 - 0x07002630
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002530, 0x004246d0, 32780, 0x00002530, 256);

// 0x07002630 - 0x07002720
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002630, 0x004246d0, 32780, 0x00002630, 240);

// 0x07002720 - 0x07002820
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002720, 0x004246d0, 32780, 0x00002720, 256);

// 0x07002820 - 0x07002920
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002820, 0x004246d0, 32780, 0x00002820, 256);

// 0x07002920 - 0x07002A20
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002920, 0x004246d0, 32780, 0x00002920, 256);

// 0x07002A20 - 0x07002B20
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002A20, 0x004246d0, 32780, 0x00002a20, 256);

// 0x07002B20 - 0x07002C00
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002B20, 0x004246d0, 32780, 0x00002b20, 224);

// 0x07002C00 - 0x07002D00
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002C00, 0x004246d0, 32780, 0x00002c00, 256);

// 0x07002D00 - 0x07002E00
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002D00, 0x004246d0, 32780, 0x00002d00, 256);

// 0x07002E00 - 0x07002F00
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002E00, 0x004246d0, 32780, 0x00002e00, 256);

// 0x07002F00 - 0x07002F40
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002F00, 0x004246d0, 32780, 0x00002f00, 64);

// 0x07002F40 - 0x07002F80
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002F40, 0x004246d0, 32780, 0x00002f40, 64);

// 0x07002F80 - 0x07003080
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07002F80, 0x004246d0, 32780, 0x00002f80, 256);

// 0x07003080 - 0x07003180
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003080, 0x004246d0, 32780, 0x00003080, 256);

// 0x07003180 - 0x07003270
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003180, 0x004246d0, 32780, 0x00003180, 240);

// 0x07003270 - 0x07003370
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003270, 0x004246d0, 32780, 0x00003270, 256);

// 0x07003370 - 0x07003470
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003370, 0x004246d0, 32780, 0x00003370, 256);

// 0x07003470 - 0x07003570
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003470, 0x004246d0, 32780, 0x00003470, 256);

// 0x07003570 - 0x07003650
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003570, 0x004246d0, 32780, 0x00003570, 224);

// 0x07003650 - 0x07003750
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003650, 0x004246d0, 32780, 0x00003650, 256);

// 0x07003750 - 0x07003850
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003750, 0x004246d0, 32780, 0x00003750, 256);

// 0x07003850 - 0x07003930
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003850, 0x004246d0, 32780, 0x00003850, 224);

// 0x07003930 - 0x07003A20
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003930, 0x004246d0, 32780, 0x00003930, 240);

// 0x07003A20 - 0x07003B20
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003A20, 0x004246d0, 32780, 0x00003a20, 256);

// 0x07003B20 - 0x07003C00
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003B20, 0x004246d0, 32780, 0x00003b20, 224);

// 0x07003C00 - 0x07003D00
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003C00, 0x004246d0, 32780, 0x00003c00, 256);

// 0x07003D00 - 0x07003D60
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003D00, 0x004246d0, 32780, 0x00003d00, 96);

// 0x07003D60 - 0x07003E50
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003D60, 0x004246d0, 32780, 0x00003d60, 240);

// 0x07003E50 - 0x07003EE0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003E50, 0x004246d0, 32780, 0x00003e50, 144);

// 0x07003EE0 - 0x07003FA0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003EE0, 0x004246d0, 32780, 0x00003ee0, 192);

// 0x07003FA0 - 0x07004090
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07003FA0, 0x004246d0, 32780, 0x00003fa0, 240);

// 0x07004090 - 0x070040F0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07004090, 0x004246d0, 32780, 0x00004090, 96);

// 0x070040F0 - 0x07004130
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070040F0, 0x004246d0, 32780, 0x000040f0, 64);

// 0x07004130 - 0x07004440
static const Gfx thi_seg7_dl_07004130[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07001000.l, 1),
    gsSPLight(&thi_seg7_lights_07001000.a, 2),
    gsSPVertex(thi_seg7_vertex_07001060, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07001140, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  4,  3,  6, 0x0),
    gsSP2Triangles( 5,  8,  3, 0x0,  4,  6,  9, 0x0),
    gsSP2Triangles(10, 11,  2, 0x0, 11,  0,  2, 0x0),
    gsSP2Triangles(11, 12,  0, 0x0,  2,  1, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07001220, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07001310, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0, 12, 13,  9, 0x0),
    gsSPVertex(thi_seg7_vertex_070013F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 14, 11, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_070014F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 3,  2,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_070015E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles(12, 11,  8, 0x0, 11, 13,  9, 0x0),
    gsSP1Triangle( 9, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_070016D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4,  6, 10, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(12,  4, 10, 0x0, 13, 14, 11, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 11, 10, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_070017D0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&thi_seg7_lights_07001018.l, 1),
    gsSPLight(&thi_seg7_lights_07001018.a, 2),
    gsSPVertex(thi_seg7_vertex_07001830, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  1,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004440 - 0x070044F0
static const Gfx thi_seg7_dl_07004440[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07001000.l, 1),
    gsSPLight(&thi_seg7_lights_07001000.a, 2),
    gsSPVertex(thi_seg7_vertex_07001920, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPLight(&thi_seg7_lights_07001018.l, 1),
    gsSPLight(&thi_seg7_lights_07001018.a, 2),
    gsSPVertex(thi_seg7_vertex_07001960, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  4, 0x0),
    gsSP1Triangle( 0,  2,  8, 0x0),
    gsSPLight(&thi_seg7_lights_07001030.l, 1),
    gsSPLight(&thi_seg7_lights_07001030.a, 2),
    gsSPVertex(thi_seg7_vertex_070019F0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070044F0 - 0x07004788
static const Gfx thi_seg7_dl_070044F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07001000.l, 1),
    gsSPLight(&thi_seg7_lights_07001000.a, 2),
    gsSPVertex(thi_seg7_vertex_07001A50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07001B30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13,  9, 0x0, 11,  9,  8, 0x0),
    gsSPVertex(thi_seg7_vertex_07001C10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07001D10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07001E10, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07001EF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07001FF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(thi_seg7_vertex_070020D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 8, 10, 14, 0x0),
    gsSPLight(&thi_seg7_lights_07001018.l, 1),
    gsSPLight(&thi_seg7_lights_07001018.a, 2),
    gsSPVertex(thi_seg7_vertex_070021C0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  4,  2, 0x0),
    gsSPLight(&thi_seg7_lights_07001030.l, 1),
    gsSPLight(&thi_seg7_lights_07001030.a, 2),
    gsSPVertex(thi_seg7_vertex_07002220, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};



// 0x07004788 - 0x07004BF0
static const Gfx thi_seg7_dl_07004788[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07001000.l, 1),
    gsSPLight(&thi_seg7_lights_07001000.a, 2),
    gsSPVertex(thi_seg7_vertex_07002260, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  1, 13, 0x0, 14, 10, 15, 0x0),
    gsSP2Triangles(10,  9, 15, 0x0,  1,  0, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07002360, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0, 11, 10, 12, 0x0),
    gsSP1Triangle( 4, 13,  5, 0x0),
    gsSPVertex(thi_seg7_vertex_07002440, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0, 13, 14, 12, 0x0),
    gsSPVertex(thi_seg7_vertex_07002530, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  6,  7,  1, 0x0),
    gsSP2Triangles( 1,  7,  4, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  2, 0x0, 12,  3,  2, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07002630, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  8, 12, 11, 0x0),
    gsSP2Triangles(12,  8, 13, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07002720, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  6, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0,  8, 13,  9, 0x0),
    gsSP2Triangles(10, 14, 11, 0x0,  1, 14,  4, 0x0),
    gsSP2Triangles( 1, 11, 14, 0x0, 12, 11, 15, 0x0),
    gsSP1Triangle(11,  1, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07002820, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12,  9, 11, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0,  0, 14,  1, 0x0),
    gsSP1Triangle( 0,  2, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07002920, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07002A20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  7, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07002B20, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 6,  3,  2, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07002C00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  6, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07002D00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles( 7, 11, 15, 0x0,  7, 15,  8, 0x0),
    gsSPVertex(thi_seg7_vertex_07002E00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07002F00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPLight(&thi_seg7_lights_07001018.l, 1),
    gsSPLight(&thi_seg7_lights_07001018.a, 2),
    gsSPVertex(thi_seg7_vertex_07002F40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};



// 0x07004BF0 - 0x070050C0
static const Gfx thi_seg7_dl_07004BF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07001000.l, 1),
    gsSPLight(&thi_seg7_lights_07001000.a, 2),
    gsSPVertex(thi_seg7_vertex_07002F80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles( 5, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(thi_seg7_vertex_07003080, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 6,  1,  0, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  4, 10,  5, 0x0),
    gsSP2Triangles( 6,  8,  1, 0x0,  4, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07003180, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  5, 12,  6, 0x0),
    gsSP2Triangles(13, 14,  5, 0x0, 13,  5, 12, 0x0),
    gsSPVertex(thi_seg7_vertex_07003270, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP1Triangle(10, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07003370, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07003470, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  5, 11,  6, 0x0),
    gsSP2Triangles( 4, 12,  7, 0x0,  4, 13, 12, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  5,  7, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07003570, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  7,  9, 0x0),
    gsSP2Triangles( 9, 12, 11, 0x0, 13,  3,  5, 0x0),
    gsSPVertex(thi_seg7_vertex_07003650, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  3, 15,  4, 0x0),
    gsSPVertex(thi_seg7_vertex_07003750, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  6,  3,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07003850, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(thi_seg7_vertex_07003930, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  9, 13, 12, 0x0),
    gsSP1Triangle(14,  1,  0, 0x0),
    gsSPVertex(thi_seg7_vertex_07003A20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07003B20, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07003C00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0, 11,  0,  2, 0x0),
    gsSP2Triangles(11, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07003D00, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&thi_seg7_lights_07001018.l, 1),
    gsSPLight(&thi_seg7_lights_07001018.a, 2),
    gsSPVertex(thi_seg7_vertex_07003D60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07003E50, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  6,  7,  8, 0x0),
    gsSP1Triangle( 1,  6,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070050C0 - 0x07005178
static const Gfx thi_seg7_dl_070050C0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, thi_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07001000.l, 1),
    gsSPLight(&thi_seg7_lights_07001000.a, 2),
    gsSPVertex(thi_seg7_vertex_07003EE0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  0,  6,  3, 0x0),
    gsSP2Triangles( 7,  3,  6, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 8,  4,  3, 0x0,  2,  5,  9, 0x0),
    gsSP2Triangles(10,  2,  7, 0x0,  0,  2, 10, 0x0),
    gsSP2Triangles( 7,  2,  9, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0,  7,  6, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005178 - 0x070051E8
static const Gfx thi_seg7_dl_07005178[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_07003FA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle(10, 14, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x070051E8 - 0x07005240
static const Gfx thi_seg7_dl_070051E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07001048.l, 1),
    gsSPLight(&thi_seg7_lights_07001048.a, 2),
    gsSPVertex(thi_seg7_vertex_07004090, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  3,  5,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005240 - 0x07005260
static const Gfx thi_seg7_dl_07005240[] = {
    gsSPVertex(thi_seg7_vertex_070040F0, 4, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSP1Triangle( 0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005260 - 0x07005330
const Gfx thi_seg7_dl_07005260[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07004130),
    gsSPDisplayList(thi_seg7_dl_07004440),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_070044F0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07004788),
    gsSPDisplayList(thi_seg7_dl_07004BF0),
    gsSPDisplayList(thi_seg7_dl_070050C0),
    gsSPDisplayList(thi_seg7_dl_07005178),
    gsSPDisplayList(thi_seg7_dl_070051E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(thi_seg7_dl_07005240),
    gsSPEndDisplayList(),
};
