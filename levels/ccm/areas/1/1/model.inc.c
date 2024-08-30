#include "pc/rom_assets.h"
// 0x07005300 - 0x07005318
static const Lights1 ccm_seg7_lights_07005300 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07005318 - 0x07005330
static const Lights1 ccm_seg7_lights_07005318 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07005330 - 0x07005348
static const Lights1 ccm_seg7_lights_07005330 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x07005348 - 0x07005360
static const Lights1 ccm_seg7_lights_07005348 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07005360 - 0x07005460
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005360, 0x00383950, 74560, 0x00005360, 256);

// 0x07005460 - 0x07005560
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005460, 0x00383950, 74560, 0x00005460, 256);

// 0x07005560 - 0x07005660
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005560, 0x00383950, 74560, 0x00005560, 256);

// 0x07005660 - 0x07005750
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005660, 0x00383950, 74560, 0x00005660, 240);

// 0x07005750 - 0x07005840
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005750, 0x00383950, 74560, 0x00005750, 240);

// 0x07005840 - 0x07005920
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005840, 0x00383950, 74560, 0x00005840, 224);

// 0x07005920 - 0x07005A00
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005920, 0x00383950, 74560, 0x00005920, 224);

// 0x07005A00 - 0x07005B00
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005A00, 0x00383950, 74560, 0x00005a00, 256);

// 0x07005B00 - 0x07005BF0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005B00, 0x00383950, 74560, 0x00005b00, 240);

// 0x07005BF0 - 0x07005CE0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005BF0, 0x00383950, 74560, 0x00005bf0, 240);

// 0x07005CE0 - 0x07005DE0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005CE0, 0x00383950, 74560, 0x00005ce0, 256);

// 0x07005DE0 - 0x07005EE0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005DE0, 0x00383950, 74560, 0x00005de0, 256);

// 0x07005EE0 - 0x07005FC0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005EE0, 0x00383950, 74560, 0x00005ee0, 224);

// 0x07005FC0 - 0x070060C0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07005FC0, 0x00383950, 74560, 0x00005fc0, 256);

// 0x070060C0 - 0x070061C0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070060C0, 0x00383950, 74560, 0x000060c0, 256);

// 0x070061C0 - 0x07006250
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070061C0, 0x00383950, 74560, 0x000061c0, 144);

// 0x07006250 - 0x070062B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006250, 0x00383950, 74560, 0x00006250, 96);

// 0x070062B0 - 0x070063A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070062B0, 0x00383950, 74560, 0x000062b0, 240);

// 0x070063A0 - 0x07006410
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070063A0, 0x00383950, 74560, 0x000063a0, 112);

// 0x07006410 - 0x07006510
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006410, 0x00383950, 74560, 0x00006410, 256);

// 0x07006510 - 0x070065B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006510, 0x00383950, 74560, 0x00006510, 160);

// 0x070065B0 - 0x070066B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070065B0, 0x00383950, 74560, 0x000065b0, 256);

// 0x070066B0 - 0x070067B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070066B0, 0x00383950, 74560, 0x000066b0, 256);

// 0x070067B0 - 0x070068B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070067B0, 0x00383950, 74560, 0x000067b0, 256);

// 0x070068B0 - 0x070069B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070068B0, 0x00383950, 74560, 0x000068b0, 256);

// 0x070069B0 - 0x07006AA0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070069B0, 0x00383950, 74560, 0x000069b0, 240);

// 0x07006AA0 - 0x07006B70
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006AA0, 0x00383950, 74560, 0x00006aa0, 208);

// 0x07006B70 - 0x07006C70
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006B70, 0x00383950, 74560, 0x00006b70, 256);

// 0x07006C70 - 0x07006D50
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006C70, 0x00383950, 74560, 0x00006c70, 224);

// 0x07006D50 - 0x07006E30
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006D50, 0x00383950, 74560, 0x00006d50, 224);

// 0x07006E30 - 0x07006F10
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006E30, 0x00383950, 74560, 0x00006e30, 224);

// 0x07006F10 - 0x07007010
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07006F10, 0x00383950, 74560, 0x00006f10, 256);

// 0x07007010 - 0x070070F0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07007010, 0x00383950, 74560, 0x00007010, 224);

// 0x070070F0 - 0x070071F0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070070F0, 0x00383950, 74560, 0x000070f0, 256);

// 0x070071F0 - 0x070072E0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070071F0, 0x00383950, 74560, 0x000071f0, 240);

// 0x070072E0 - 0x070073E0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070072E0, 0x00383950, 74560, 0x000072e0, 256);

// 0x070073E0 - 0x070074D0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070073E0, 0x00383950, 74560, 0x000073e0, 240);

// 0x070074D0 - 0x070075D0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070074D0, 0x00383950, 74560, 0x000074d0, 256);

// 0x070075D0 - 0x070076B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070075D0, 0x00383950, 74560, 0x000075d0, 224);

// 0x070076B0 - 0x070077A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070076B0, 0x00383950, 74560, 0x000076b0, 240);

// 0x070077A0 - 0x070078A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070077A0, 0x00383950, 74560, 0x000077a0, 256);

// 0x070078A0 - 0x070079A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070078A0, 0x00383950, 74560, 0x000078a0, 256);

// 0x070079A0 - 0x07007A90
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070079A0, 0x00383950, 74560, 0x000079a0, 240);

// 0x07007A90 - 0x07007B80
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07007A90, 0x00383950, 74560, 0x00007a90, 240);

// 0x07007B80 - 0x07007C70
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07007B80, 0x00383950, 74560, 0x00007b80, 240);

// 0x07007C70 - 0x07007D50
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07007C70, 0x00383950, 74560, 0x00007c70, 224);

// 0x07007D50 - 0x07007E30
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07007D50, 0x00383950, 74560, 0x00007d50, 224);

// 0x07007E30 - 0x07007F30
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07007E30, 0x00383950, 74560, 0x00007e30, 256);

// 0x07007F30 - 0x07008030
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07007F30, 0x00383950, 74560, 0x00007f30, 256);

// 0x07008030 - 0x07008130
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008030, 0x00383950, 74560, 0x00008030, 256);

// 0x07008130 - 0x07008230
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008130, 0x00383950, 74560, 0x00008130, 256);

// 0x07008230 - 0x07008260
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008230, 0x00383950, 74560, 0x00008230, 48);

// 0x07008260 - 0x07008350
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008260, 0x00383950, 74560, 0x00008260, 240);

// 0x07008350 - 0x07008430
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008350, 0x00383950, 74560, 0x00008350, 224);

// 0x07008430 - 0x07008530
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008430, 0x00383950, 74560, 0x00008430, 256);

// 0x07008530 - 0x07008630
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008530, 0x00383950, 74560, 0x00008530, 256);

// 0x07008630 - 0x070086A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008630, 0x00383950, 74560, 0x00008630, 112);

// 0x070086A0 - 0x07008780
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070086A0, 0x00383950, 74560, 0x000086a0, 224);

// 0x07008780 - 0x07008880
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008780, 0x00383950, 74560, 0x00008780, 256);

// 0x07008880 - 0x07008980
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008880, 0x00383950, 74560, 0x00008880, 256);

// 0x07008980 - 0x07008A20
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008980, 0x00383950, 74560, 0x00008980, 160);

// 0x07008A20 - 0x07008B00
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008A20, 0x00383950, 74560, 0x00008a20, 224);

// 0x07008B00 - 0x07008B80
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008B00, 0x00383950, 74560, 0x00008b00, 128);

// 0x07008B80 - 0x07008BF0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008B80, 0x00383950, 74560, 0x00008b80, 112);

// 0x07008BF0 - 0x07008CF0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008BF0, 0x00383950, 74560, 0x00008bf0, 256);

// 0x07008CF0 - 0x07008DD0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008CF0, 0x00383950, 74560, 0x00008cf0, 224);

// 0x07008DD0 - 0x07008ED0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008DD0, 0x00383950, 74560, 0x00008dd0, 256);

// 0x07008ED0 - 0x07008FD0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008ED0, 0x00383950, 74560, 0x00008ed0, 256);

// 0x07008FD0 - 0x070090B0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_07008FD0, 0x00383950, 74560, 0x00008fd0, 224);

// 0x070090B0 - 0x070091A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070090B0, 0x00383950, 74560, 0x000090b0, 240);

// 0x070091A0 - 0x070092A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070091A0, 0x00383950, 74560, 0x000091a0, 256);

// 0x070092A0 - 0x070093A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070092A0, 0x00383950, 74560, 0x000092a0, 256);

// 0x070093A0 - 0x070094A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070093A0, 0x00383950, 74560, 0x000093a0, 256);

// 0x070094A0 - 0x070095A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070094A0, 0x00383950, 74560, 0x000094a0, 256);

// 0x070095A0 - 0x070096A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070095A0, 0x00383950, 74560, 0x000095a0, 256);

// 0x070096A0 - 0x070097A0
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070096A0, 0x00383950, 74560, 0x000096a0, 256);

// 0x070097A0 - 0x07009820
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_070097A0, 0x00383950, 74560, 0x000097a0, 128);

// 0x07009820 - 0x07009DD0
static const Gfx ccm_seg7_dl_07009820[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_07005300.l, 1),
    gsSPLight(&ccm_seg7_lights_07005300.a, 2),
    gsSPVertex(ccm_seg7_vertex_07005360, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles(11,  2,  1, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle( 1,  0, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005460, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 10,  9, 13, 0x0),
    gsSP1Triangle(14,  9, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005560, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  5,  7, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  4, 12, 15, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005660, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  1, 0x0),
    gsSP2Triangles( 7,  1,  3, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0,  4, 12, 13, 0x0),
    gsSP1Triangle( 4, 14,  5, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005750, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 10,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005840, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  2,  1,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005920, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 9,  5,  6, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(12, 13, 10, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005A00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  0, 0x0),
    gsSP2Triangles(11, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005B00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0,  7,  9, 12, 0x0),
    gsSP2Triangles( 9,  8, 13, 0x0,  2, 14,  0, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005BF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6,  5, 10, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles(11,  5,  4, 0x0, 12,  7, 10, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 13, 12, 11, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0,  5, 12, 10, 0x0),
    gsSP2Triangles(14,  8,  7, 0x0, 14,  7, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005CE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  9,  0,  7, 0x0),
    gsSP2Triangles( 7,  2,  8, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 12,  1, 0x0,  1, 12,  2, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005DE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  6,  3,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  9, 13, 10, 0x0),
    gsSP2Triangles(13, 14, 10, 0x0, 14, 15, 10, 0x0),
    gsSP2Triangles(15, 11, 10, 0x0,  6,  7, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005EE0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  1, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0,  8, 12,  9, 0x0),
    gsSP1Triangle( 3, 13,  4, 0x0),
    gsSPVertex(ccm_seg7_vertex_07005FC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  2,  1, 13, 0x0),
    gsSP2Triangles( 1, 14, 13, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070060C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 7,  0,  8, 0x0,  0,  2,  8, 0x0),
    gsSP2Triangles( 0,  7,  6, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles( 6, 11,  5, 0x0,  2, 12,  8, 0x0),
    gsSP2Triangles(13, 12,  2, 0x0, 13,  2, 14, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 11, 14, 0x0),
    gsSP1Triangle(11, 15,  5, 0x0),
    gsSPVertex(ccm_seg7_vertex_070061C0, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  5,  8, 0x0),
    gsSP2Triangles( 4,  5,  7, 0x0,  8,  3,  2, 0x0),
    gsSPLight(&ccm_seg7_lights_07005318.l, 1),
    gsSPLight(&ccm_seg7_lights_07005318.a, 2),
    gsSPVertex(ccm_seg7_vertex_07006250, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009DD0 - 0x07009F28
static const Gfx ccm_seg7_dl_07009DD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_07005300.l, 1),
    gsSPLight(&ccm_seg7_lights_07005300.a, 2),
    gsSPVertex(ccm_seg7_vertex_070062B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  2, 10,  7, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13,  2, 0x0),
    gsSP2Triangles( 2, 13, 10, 0x0,  0, 14,  1, 0x0),
    gsSPVertex(ccm_seg7_vertex_070063A0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 4,  6,  5, 0x0),
    gsSPLight(&ccm_seg7_lights_07005330.l, 1),
    gsSPLight(&ccm_seg7_lights_07005330.a, 2),
    gsSPVertex(ccm_seg7_vertex_07006410, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  0,  3, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  4,  2,  8, 0x0),
    gsSP2Triangles( 8,  2,  1, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07006510, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  1,  3,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009F28 - 0x0700A248
static const Gfx ccm_seg7_dl_07009F28[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_07005300.l, 1),
    gsSPLight(&ccm_seg7_lights_07005300.a, 2),
    gsSPVertex(ccm_seg7_vertex_070065B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles( 7,  8,  0, 0x0,  0,  8,  9, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  3,  0, 11, 0x0),
    gsSP2Triangles(12,  7,  0, 0x0,  0,  6, 12, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070066B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0, 10,  7, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070067B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070068B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  5,  7, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 10, 11,  7, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(15, 12, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_070069B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_07006AA0, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP1Triangle(12, 11, 10, 0x0),
    gsSPLight(&ccm_seg7_lights_07005318.l, 1),
    gsSPLight(&ccm_seg7_lights_07005318.a, 2),
    gsSPVertex(ccm_seg7_vertex_07006B70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  2, 12,  9, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07006C70, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 10, 12, 13, 0x0),
    gsSPLight(&ccm_seg7_lights_07005330.l, 1),
    gsSPLight(&ccm_seg7_lights_07005330.a, 2),
    gsSPVertex(ccm_seg7_vertex_07006D50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07006E30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A248 - 0x0700AB00
static const Gfx ccm_seg7_dl_0700A248[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_07005300.l, 1),
    gsSPLight(&ccm_seg7_lights_07005300.a, 2),
    gsSPVertex(ccm_seg7_vertex_07006F10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11,  2, 12, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07007010, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 7,  3,  5, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  9, 12, 10, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_070070F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  1,  0, 0x0),
    gsSP2Triangles( 5,  4,  1, 0x0,  6,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  4,  7,  3, 0x0),
    gsSP2Triangles( 7,  2,  3, 0x0,  2,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070071F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 0,  7,  4, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_070072E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070073E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(11,  8, 12, 0x0, 13, 11, 12, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 14,  9, 11, 0x0),
    gsSPVertex(ccm_seg7_vertex_070074D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  4,  6, 11, 0x0),
    gsSP2Triangles(12,  5,  7, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070075D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  7,  9,  3, 0x0),
    gsSP2Triangles( 4,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_070076B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_070077A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 10,  8, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070078A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070079A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  6,  5,  9, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0, 11,  8,  7, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07007A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07007B80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14,  8, 10, 0x0),
    gsSPVertex(ccm_seg7_vertex_07007C70, 14, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSP1Triangle( 3,  4,  5, 0x0),
    gsSP1Triangle( 3,  6,  4, 0x0),
    gsSP1Triangle( 7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSP1Triangle( 0,  2, 11, 0x0),
    gsSP1Triangle( 0, 11, 12, 0x0),
    gsSP1Triangle( 0, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07007D50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  3,  5, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07007E30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12,  7,  6, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07007F30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 3,  2,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008030, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(11,  8, 10, 0x0, 13, 14, 15, 0x0),
    gsSPLight(&ccm_seg7_lights_07005348.l, 1),
    gsSPLight(&ccm_seg7_lights_07005348.a, 2),
    gsSPVertex(ccm_seg7_vertex_07008130, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  5,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14,  7, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008230, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&ccm_seg7_lights_07005318.l, 1),
    gsSPLight(&ccm_seg7_lights_07005318.a, 2),
    gsSPVertex(ccm_seg7_vertex_07008260, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 5,  7,  3, 0x0,  9,  2, 10, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  0, 13,  1, 0x0),
    gsSP1Triangle( 1, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008350, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008430, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 4,  3,  9, 0x0,  5, 11,  3, 0x0),
    gsSP2Triangles( 9,  3, 11, 0x0, 12, 10,  9, 0x0),
    gsSP2Triangles(13,  4, 10, 0x0, 14, 15,  6, 0x0),
    gsSP1Triangle( 6, 15,  7, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008530, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008630, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  5,  6, 0x0),
    gsSPLight(&ccm_seg7_lights_07005330.l, 1),
    gsSPLight(&ccm_seg7_lights_07005330.a, 2),
    gsSPVertex(ccm_seg7_vertex_070086A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles(11,  1, 13, 0x0,  2,  1, 12, 0x0),
    gsSP1Triangle( 1,  0, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008780, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0, 11,  8,  9, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0,  0,  2, 12, 0x0),
    gsSP2Triangles(11,  0, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008880, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0,  5,  4, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008980, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AB00 - 0x0700ABF8
static const Gfx ccm_seg7_dl_0700AB00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_07005300.l, 1),
    gsSPLight(&ccm_seg7_lights_07005300.a, 2),
    gsSPVertex(ccm_seg7_vertex_07008A20, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  3, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0,  7, 11,  9, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0,  7, 13, 11, 0x0),
    gsSPLight(&ccm_seg7_lights_07005318.l, 1),
    gsSPLight(&ccm_seg7_lights_07005318.a, 2),
    gsSPVertex(ccm_seg7_vertex_07008B00, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  0,  6,  7, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPLight(&ccm_seg7_lights_07005330.l, 1),
    gsSPLight(&ccm_seg7_lights_07005330.a, 2),
    gsSPVertex(ccm_seg7_vertex_07008B80, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 2,  6,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700ABF8 - 0x0700B090
static const Gfx ccm_seg7_dl_0700ABF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_07005300.l, 1),
    gsSPLight(&ccm_seg7_lights_07005300.a, 2),
    gsSPVertex(ccm_seg7_vertex_07008BF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  2,  4,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 12,  9,  8, 0x0),
    gsSP2Triangles( 0,  7,  1, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(12, 14,  9, 0x0, 11, 10, 15, 0x0),
    gsSP1Triangle(11, 15, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008CF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0,  2, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008DD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 3,  2,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 12, 13,  9, 0x0),
    gsSP2Triangles(12,  9,  8, 0x0, 11, 10, 14, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008ED0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10,  4, 0x0),
    gsSP2Triangles( 4, 10,  1, 0x0,  3,  2, 11, 0x0),
    gsSP2Triangles( 3, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_07008FD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_070090B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  2,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  8, 10, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_070091A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 8,  7, 12, 0x0,  8, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070092A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  3,  2,  6, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 8, 13,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070093A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10,  0, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0,  4,  3, 11, 0x0),
    gsSP2Triangles( 4, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070094A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0,  2, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070095A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  3,  2,  6, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 8, 13,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070096A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles( 4,  3, 10, 0x0,  4, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_070097A0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  2,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B090 - 0x0700B118
const Gfx ccm_seg7_dl_0700B090[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_07009820),
    gsSPDisplayList(ccm_seg7_dl_07009DD0),
    gsSPDisplayList(ccm_seg7_dl_07009F28),
    gsSPDisplayList(ccm_seg7_dl_0700A248),
    gsSPDisplayList(ccm_seg7_dl_0700AB00),
    gsSPDisplayList(ccm_seg7_dl_0700ABF8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
