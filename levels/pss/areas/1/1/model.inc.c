#include "pc/rom_assets.h"
// 0x07001800 - 0x07001818
static const Lights1 pss_seg7_lights_07001800 = gdSPDefLights1(
    0x23, 0x23, 0x23,
    0x8c, 0x8c, 0x8c, 0x28, 0x28, 0x28
);

// 0x07001818 - 0x07001830
static const Lights1 pss_seg7_lights_07001818 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07001830 - 0x07001930
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001830, 0x004af930, 34262, 0x00001830, 256);

// 0x07001930 - 0x07001A30
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001930, 0x004af930, 34262, 0x00001930, 256);

// 0x07001A30 - 0x07001A80
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001A30, 0x004af930, 34262, 0x00001a30, 80);

// 0x07001A80 - 0x07001B80
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001A80, 0x004af930, 34262, 0x00001a80, 256);

// 0x07001B80 - 0x07001C60
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001B80, 0x004af930, 34262, 0x00001b80, 224);

// 0x07001C60 - 0x07001D60
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001C60, 0x004af930, 34262, 0x00001c60, 256);

// 0x07001D60 - 0x07001E60
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001D60, 0x004af930, 34262, 0x00001d60, 256);

// 0x07001E60 - 0x07001F50
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001E60, 0x004af930, 34262, 0x00001e60, 240);

// 0x07001F50 - 0x07002050
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07001F50, 0x004af930, 34262, 0x00001f50, 256);

// 0x07002050 - 0x07002150
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002050, 0x004af930, 34262, 0x00002050, 256);

// 0x07002150 - 0x07002250
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002150, 0x004af930, 34262, 0x00002150, 256);

// 0x07002250 - 0x07002340
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002250, 0x004af930, 34262, 0x00002250, 240);

// 0x07002340 - 0x07002440
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002340, 0x004af930, 34262, 0x00002340, 256);

// 0x07002440 - 0x07002520
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002440, 0x004af930, 34262, 0x00002440, 224);

// 0x07002520 - 0x07002620
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002520, 0x004af930, 34262, 0x00002520, 256);

// 0x07002620 - 0x07002720
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002620, 0x004af930, 34262, 0x00002620, 256);

// 0x07002720 - 0x07002810
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002720, 0x004af930, 34262, 0x00002720, 240);

// 0x07002810 - 0x07002900
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002810, 0x004af930, 34262, 0x00002810, 240);

// 0x07002900 - 0x07002A00
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002900, 0x004af930, 34262, 0x00002900, 256);

// 0x07002A00 - 0x07002B00
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002A00, 0x004af930, 34262, 0x00002a00, 256);

// 0x07002B00 - 0x07002BE0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002B00, 0x004af930, 34262, 0x00002b00, 224);

// 0x07002BE0 - 0x07002CE0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002BE0, 0x004af930, 34262, 0x00002be0, 256);

// 0x07002CE0 - 0x07002DE0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002CE0, 0x004af930, 34262, 0x00002ce0, 256);

// 0x07002DE0 - 0x07002E90
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002DE0, 0x004af930, 34262, 0x00002de0, 176);

// 0x07002E90 - 0x07002F90
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002E90, 0x004af930, 34262, 0x00002e90, 256);

// 0x07002F90 - 0x07002FD0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002F90, 0x004af930, 34262, 0x00002f90, 64);

// 0x07002FD0 - 0x070030C0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07002FD0, 0x004af930, 34262, 0x00002fd0, 240);

// 0x070030C0 - 0x070031C0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070030C0, 0x004af930, 34262, 0x000030c0, 256);

// 0x070031C0 - 0x070032B0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070031C0, 0x004af930, 34262, 0x000031c0, 240);

// 0x070032B0 - 0x070033A0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070032B0, 0x004af930, 34262, 0x000032b0, 240);

// 0x070033A0 - 0x070034A0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070033A0, 0x004af930, 34262, 0x000033a0, 256);

// 0x070034A0 - 0x07003590
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070034A0, 0x004af930, 34262, 0x000034a0, 240);

// 0x07003590 - 0x07003690
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003590, 0x004af930, 34262, 0x00003590, 256);

// 0x07003690 - 0x07003770
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003690, 0x004af930, 34262, 0x00003690, 224);

// 0x07003770 - 0x07003860
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003770, 0x004af930, 34262, 0x00003770, 240);

// 0x07003860 - 0x07003940
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003860, 0x004af930, 34262, 0x00003860, 224);

// 0x07003940 - 0x07003A40
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003940, 0x004af930, 34262, 0x00003940, 256);

// 0x07003A40 - 0x07003B30
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003A40, 0x004af930, 34262, 0x00003a40, 240);

// 0x07003B30 - 0x07003C20
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003B30, 0x004af930, 34262, 0x00003b30, 240);

// 0x07003C20 - 0x07003D00
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003C20, 0x004af930, 34262, 0x00003c20, 224);

// 0x07003D00 - 0x07003DF0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003D00, 0x004af930, 34262, 0x00003d00, 240);

// 0x07003DF0 - 0x07003EE0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003DF0, 0x004af930, 34262, 0x00003df0, 240);

// 0x07003EE0 - 0x07003FD0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003EE0, 0x004af930, 34262, 0x00003ee0, 240);

// 0x07003FD0 - 0x070040C0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07003FD0, 0x004af930, 34262, 0x00003fd0, 240);

// 0x070040C0 - 0x070041B0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070040C0, 0x004af930, 34262, 0x000040c0, 240);

// 0x070041B0 - 0x070042A0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070041B0, 0x004af930, 34262, 0x000041b0, 240);

// 0x070042A0 - 0x07004340
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070042A0, 0x004af930, 34262, 0x000042a0, 160);

// 0x07004340 - 0x07004430
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004340, 0x004af930, 34262, 0x00004340, 240);

// 0x07004430 - 0x07004520
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004430, 0x004af930, 34262, 0x00004430, 240);

// 0x07004520 - 0x07004610
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004520, 0x004af930, 34262, 0x00004520, 240);

// 0x07004610 - 0x07004700
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004610, 0x004af930, 34262, 0x00004610, 240);

// 0x07004700 - 0x07004800
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004700, 0x004af930, 34262, 0x00004700, 256);

// 0x07004800 - 0x070048E0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004800, 0x004af930, 34262, 0x00004800, 224);

// 0x070048E0 - 0x070049D0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070048E0, 0x004af930, 34262, 0x000048e0, 240);

// 0x070049D0 - 0x07004AC0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070049D0, 0x004af930, 34262, 0x000049d0, 240);

// 0x07004AC0 - 0x07004BB0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004AC0, 0x004af930, 34262, 0x00004ac0, 240);

// 0x07004BB0 - 0x07004CA0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004BB0, 0x004af930, 34262, 0x00004bb0, 240);

// 0x07004CA0 - 0x07004D90
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004CA0, 0x004af930, 34262, 0x00004ca0, 240);

// 0x07004D90 - 0x07004E80
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004D90, 0x004af930, 34262, 0x00004d90, 240);

// 0x07004E80 - 0x07004F70
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004E80, 0x004af930, 34262, 0x00004e80, 240);

// 0x07004F70 - 0x07005060
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07004F70, 0x004af930, 34262, 0x00004f70, 240);

// 0x07005060 - 0x07005150
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005060, 0x004af930, 34262, 0x00005060, 240);

// 0x07005150 - 0x07005240
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005150, 0x004af930, 34262, 0x00005150, 240);

// 0x07005240 - 0x07005330
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005240, 0x004af930, 34262, 0x00005240, 240);

// 0x07005330 - 0x07005420
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005330, 0x004af930, 34262, 0x00005330, 240);

// 0x07005420 - 0x07005510
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005420, 0x004af930, 34262, 0x00005420, 240);

// 0x07005510 - 0x07005600
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005510, 0x004af930, 34262, 0x00005510, 240);

// 0x07005600 - 0x07005700
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005600, 0x004af930, 34262, 0x00005600, 256);

// 0x07005700 - 0x070057F0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005700, 0x004af930, 34262, 0x00005700, 240);

// 0x070057F0 - 0x070058D0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070057F0, 0x004af930, 34262, 0x000057f0, 224);

// 0x070058D0 - 0x070059C0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070058D0, 0x004af930, 34262, 0x000058d0, 240);

// 0x070059C0 - 0x07005AA0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070059C0, 0x004af930, 34262, 0x000059c0, 224);

// 0x07005AA0 - 0x07005B80
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005AA0, 0x004af930, 34262, 0x00005aa0, 224);

// 0x07005B80 - 0x07005C70
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005B80, 0x004af930, 34262, 0x00005b80, 240);

// 0x07005C70 - 0x07005D60
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005C70, 0x004af930, 34262, 0x00005c70, 240);

// 0x07005D60 - 0x07005E50
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005D60, 0x004af930, 34262, 0x00005d60, 240);

// 0x07005E50 - 0x07005F40
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005E50, 0x004af930, 34262, 0x00005e50, 240);

// 0x07005F40 - 0x07006030
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07005F40, 0x004af930, 34262, 0x00005f40, 240);

// 0x07006030 - 0x07006120
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006030, 0x004af930, 34262, 0x00006030, 240);

// 0x07006120 - 0x07006220
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006120, 0x004af930, 34262, 0x00006120, 256);

// 0x07006220 - 0x07006320
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006220, 0x004af930, 34262, 0x00006220, 256);

// 0x07006320 - 0x07006420
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006320, 0x004af930, 34262, 0x00006320, 256);

// 0x07006420 - 0x07006500
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006420, 0x004af930, 34262, 0x00006420, 224);

// 0x07006500 - 0x070065F0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006500, 0x004af930, 34262, 0x00006500, 240);

// 0x070065F0 - 0x070066E0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070065F0, 0x004af930, 34262, 0x000065f0, 240);

// 0x070066E0 - 0x070067D0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070066E0, 0x004af930, 34262, 0x000066e0, 240);

// 0x070067D0 - 0x070068C0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070067D0, 0x004af930, 34262, 0x000067d0, 240);

// 0x070068C0 - 0x070069B0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070068C0, 0x004af930, 34262, 0x000068c0, 240);

// 0x070069B0 - 0x07006AA0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070069B0, 0x004af930, 34262, 0x000069b0, 240);

// 0x07006AA0 - 0x07006B90
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006AA0, 0x004af930, 34262, 0x00006aa0, 240);

// 0x07006B90 - 0x07006C80
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006B90, 0x004af930, 34262, 0x00006b90, 240);

// 0x07006C80 - 0x07006D70
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006C80, 0x004af930, 34262, 0x00006c80, 240);

// 0x07006D70 - 0x07006E60
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006D70, 0x004af930, 34262, 0x00006d70, 240);

// 0x07006E60 - 0x07006F50
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006E60, 0x004af930, 34262, 0x00006e60, 240);

// 0x07006F50 - 0x07007040
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07006F50, 0x004af930, 34262, 0x00006f50, 240);

// 0x07007040 - 0x07007130
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007040, 0x004af930, 34262, 0x00007040, 240);

// 0x07007130 - 0x07007220
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007130, 0x004af930, 34262, 0x00007130, 240);

// 0x07007220 - 0x07007310
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007220, 0x004af930, 34262, 0x00007220, 240);

// 0x07007310 - 0x07007400
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007310, 0x004af930, 34262, 0x00007310, 240);

// 0x07007400 - 0x070074F0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007400, 0x004af930, 34262, 0x00007400, 240);

// 0x070074F0 - 0x070075E0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070074F0, 0x004af930, 34262, 0x000074f0, 240);

// 0x070075E0 - 0x070076D0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070075E0, 0x004af930, 34262, 0x000075e0, 240);

// 0x070076D0 - 0x070077C0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070076D0, 0x004af930, 34262, 0x000076d0, 240);

// 0x070077C0 - 0x070078B0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070077C0, 0x004af930, 34262, 0x000077c0, 240);

// 0x070078B0 - 0x070079A0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070078B0, 0x004af930, 34262, 0x000078b0, 240);

// 0x070079A0 - 0x07007A90
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_070079A0, 0x004af930, 34262, 0x000079a0, 240);

// 0x07007A90 - 0x07007B80
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007A90, 0x004af930, 34262, 0x00007a90, 240);

// 0x07007B80 - 0x07007C70
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007B80, 0x004af930, 34262, 0x00007b80, 240);

// 0x07007C70 - 0x07007D60
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007C70, 0x004af930, 34262, 0x00007c70, 240);

// 0x07007D60 - 0x07007E50
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007D60, 0x004af930, 34262, 0x00007d60, 240);

// 0x07007E50 - 0x07007F40
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007E50, 0x004af930, 34262, 0x00007e50, 240);

// 0x07007F40 - 0x07008030
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07007F40, 0x004af930, 34262, 0x00007f40, 240);

// 0x07008030 - 0x07008120
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07008030, 0x004af930, 34262, 0x00008030, 240);

// 0x07008120 - 0x07008210
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07008120, 0x004af930, 34262, 0x00008120, 240);

// 0x07008210 - 0x07008300
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07008210, 0x004af930, 34262, 0x00008210, 240);

// 0x07008300 - 0x070083B0
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_07008300, 0x004af930, 34262, 0x00008300, 176);

// 0x070083B0 - 0x07008E20
static const Gfx pss_seg7_dl_070083B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_0900C000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&pss_seg7_lights_07001800.l, 1),
    gsSPLight(&pss_seg7_lights_07001800.a, 2),
    gsSPVertex(pss_seg7_vertex_07001830, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11,  1, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07001930, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07001A30, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP1Triangle( 2,  3,  4, 0x0),
    gsSPLight(&pss_seg7_lights_07001818.l, 1),
    gsSPLight(&pss_seg7_lights_07001818.a, 2),
    gsSPVertex(pss_seg7_vertex_07001A80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  4,  0,  6, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 4,  8,  0, 0x0,  8,  1,  0, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  9,  5,  6, 0x0),
    gsSP2Triangles( 5, 10,  3, 0x0, 10,  5,  9, 0x0),
    gsSP2Triangles(11,  3, 10, 0x0, 12,  7,  3, 0x0),
    gsSP2Triangles(11, 12,  3, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07001B80, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  5,  6,  2, 0x0),
    gsSP2Triangles( 1,  8,  5, 0x0,  9,  1,  3, 0x0),
    gsSP2Triangles( 8,  1,  9, 0x0, 10,  5,  8, 0x0),
    gsSP2Triangles(11,  6,  5, 0x0, 10, 11,  5, 0x0),
    gsSP2Triangles( 8, 12, 10, 0x0, 13,  8,  9, 0x0),
    gsSPVertex(pss_seg7_vertex_07001C60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  6,  4, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  7,  3, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 8,  5,  9, 0x0,  2,  3, 10, 0x0),
    gsSP2Triangles(11,  3,  7, 0x0, 11, 10,  3, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0,  0, 10, 12, 0x0),
    gsSP2Triangles(13, 12, 10, 0x0, 13, 10, 11, 0x0),
    gsSP2Triangles(12, 14,  0, 0x0, 14,  1,  0, 0x0),
    gsSP1Triangle(15, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07001D60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  8,  1,  9, 0x0),
    gsSP2Triangles( 1,  0,  9, 0x0,  4,  1,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  4,  8, 13, 0x0),
    gsSP2Triangles( 4, 14,  6, 0x0, 13, 14,  4, 0x0),
    gsSP1Triangle(13,  8, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07001E60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  4,  1,  8, 0x0),
    gsSP2Triangles( 9,  8,  1, 0x0,  9,  1,  0, 0x0),
    gsSP2Triangles( 8, 10,  4, 0x0, 10, 11,  4, 0x0),
    gsSP2Triangles( 8, 12, 10, 0x0, 13, 12,  8, 0x0),
    gsSP2Triangles(13,  8,  9, 0x0, 12, 14, 10, 0x0),
    gsSPVertex(pss_seg7_vertex_07001F50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  6,  3, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 8,  5,  2, 0x0,  7,  8,  2, 0x0),
    gsSP2Triangles( 1,  9,  7, 0x0,  9,  1,  4, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles(10,  9, 12, 0x0, 13,  8,  7, 0x0),
    gsSP2Triangles(11, 13,  7, 0x0, 10, 14, 11, 0x0),
    gsSP2Triangles(15, 13, 11, 0x0, 14, 15, 11, 0x0),
    gsSPVertex(pss_seg7_vertex_07002050, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  2,  1, 0x0),
    gsSP2Triangles(10, 11,  2, 0x0, 11, 12,  2, 0x0),
    gsSP2Triangles( 1, 13, 10, 0x0, 14,  1,  3, 0x0),
    gsSP2Triangles(13,  1, 14, 0x0,  9, 10, 13, 0x0),
    gsSP2Triangles( 9, 15, 10, 0x0, 15, 11, 10, 0x0),
    gsSPVertex(pss_seg7_vertex_07002150, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 5,  2, 11, 0x0, 12,  2,  3, 0x0),
    gsSP2Triangles(11,  2, 12, 0x0, 13,  5, 11, 0x0),
    gsSP2Triangles(14, 13, 11, 0x0,  8, 10, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07002250, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  3,  2,  8, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0, 10,  4,  3, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0, 12, 13,  9, 0x0),
    gsSP2Triangles(13, 10,  9, 0x0, 12, 11, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07002340, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  5,  6,  3, 0x0),
    gsSP2Triangles( 5,  4,  8, 0x0,  9,  5,  8, 0x0),
    gsSP2Triangles(10,  6,  5, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  2,  9, 11, 0x0),
    gsSP2Triangles(12, 10,  9, 0x0,  2, 12,  9, 0x0),
    gsSP2Triangles( 2, 11, 13, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0,  0, 13, 14, 0x0),
    gsSP1Triangle( 0, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07002440, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 7,  1,  0, 0x0,  6,  7,  0, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0,  8, 10,  6, 0x0),
    gsSP2Triangles(10,  8, 11, 0x0, 12, 10, 11, 0x0),
    gsSP1Triangle(13, 12, 11, 0x0),
    gsSPVertex(pss_seg7_vertex_07002520, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 3,  6,  5, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 2,  7,  4, 0x0,  9,  5,  6, 0x0),
    gsSP2Triangles( 9,  6, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13,  8, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12, 14, 15, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_07002620, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 7,  5, 10, 0x0, 11,  7, 10, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07002720, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 3,  7,  4, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 4,  9,  1, 0x0,  1, 10, 11, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0,  1,  9, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07002810, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  9,  8,  3, 0x0),
    gsSP2Triangles( 5,  4, 10, 0x0,  4,  6, 11, 0x0),
    gsSP2Triangles( 6,  7, 12, 0x0,  6, 12, 13, 0x0),
    gsSP2Triangles( 6, 13, 11, 0x0,  4, 11, 14, 0x0),
    gsSP1Triangle(10,  4, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07002900, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  6,  2,  7, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  8,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0, 10,  8,  9, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 12, 10, 11, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07002A00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  5,  3,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07002B00, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  4,  0,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 11, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_07002BE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  0,  6, 0x0,  0,  7,  6, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  7,  2,  8, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 6,  7, 10, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 5,  6, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 5, 10, 14, 0x0,  9,  8, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07002CE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  4, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  2,  3,  7, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  4,  2,  8, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  6,  4,  9, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0, 10,  9, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0,  8, 11, 12, 0x0),
    gsSP1Triangle(12, 11, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07002DE0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 3,  2,  5, 0x0,  2,  1,  7, 0x0),
    gsSP1Triangle( 8,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008E20 - 0x07008EB0
static const Gfx pss_seg7_dl_07008E20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pss_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(pss_seg7_vertex_07002E90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  8,  6, 0x0),
    gsSP2Triangles( 3,  7,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  9, 13, 12, 0x0),
    gsSP2Triangles( 9, 14, 13, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07002F90, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008EB0 - 0x070095E8
static const Gfx pss_seg7_dl_07008EB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(pss_seg7_vertex_07002FD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  8,  9,  0, 0x0),
    gsSP2Triangles( 0,  9,  1, 0x0,  0,  5,  8, 0x0),
    gsSP2Triangles( 3, 10,  6, 0x0, 11,  8,  5, 0x0),
    gsSP2Triangles( 5,  7, 12, 0x0,  5, 12, 11, 0x0),
    gsSP2Triangles(10,  1,  9, 0x0, 10,  9,  6, 0x0),
    gsSP1Triangle(13, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_070030C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  0,  4, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  5,  9,  0, 0x0),
    gsSP2Triangles( 9,  8,  0, 0x0, 10,  9,  5, 0x0),
    gsSP2Triangles( 5,  7, 11, 0x0,  5, 11, 10, 0x0),
    gsSP2Triangles(10, 12,  9, 0x0, 12, 13,  9, 0x0),
    gsSP2Triangles( 9, 13,  8, 0x0, 13,  6,  8, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 15,  3,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_070031C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070032B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  2,  5, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  1, 10,  3, 0x0),
    gsSP2Triangles( 5, 11, 12, 0x0,  5,  4, 11, 0x0),
    gsSP2Triangles(12,  7,  5, 0x0, 10,  9,  8, 0x0),
    gsSP1Triangle(13, 14, 11, 0x0),
    gsSPVertex(pss_seg7_vertex_070033A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 4,  7,  5, 0x0,  6,  0,  4, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles( 6,  8,  0, 0x0,  6,  5, 10, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0, 11,  8,  6, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0,  8, 13,  9, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 13,  7,  9, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 15,  3,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_070034A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07003590, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  4, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles( 3,  4,  7, 0x0,  1, 10,  5, 0x0),
    gsSP2Triangles(11,  7,  4, 0x0,  4,  6, 12, 0x0),
    gsSP2Triangles( 4, 12, 11, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles(13, 14, 12, 0x0, 11, 15,  7, 0x0),
    gsSPVertex(pss_seg7_vertex_07003690, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  4, 0x0,  4,  8,  0, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(10,  8,  4, 0x0,  4,  7, 11, 0x0),
    gsSP2Triangles( 4, 11, 10, 0x0, 10, 12,  8, 0x0),
    gsSP2Triangles( 8, 13,  9, 0x0, 12, 13,  8, 0x0),
    gsSP1Triangle(13,  6,  9, 0x0),
    gsSPVertex(pss_seg7_vertex_07003770, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 4, 12,  5, 0x0,  4, 13, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07003860, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0,  8, 13, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07003940, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles( 1,  0, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07003A40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07003B30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07003C20, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_07003D00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07003DF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07003EE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07003FD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_070040C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070041B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070042A0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070095E8 - 0x07009750
static const Gfx pss_seg7_dl_070095E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(pss_seg7_vertex_07004340, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07004430, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07004520, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_07004610, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07004700, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009750 - 0x0700A7C0
static const Gfx pss_seg7_dl_07009750[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(pss_seg7_vertex_07004800, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8, 12, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_070048E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070049D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07004AC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07004BB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07004CA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07004D90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07004E80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07004F70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07005060, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07005150, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07005240, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07005330, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07005420, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07005510, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07005600, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(pss_seg7_vertex_07005700, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPVertex(pss_seg7_vertex_070057F0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_070058D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070059C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_07005AA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11,  3, 12, 0x0),
    gsSP1Triangle(11, 13,  3, 0x0),
    gsSPVertex(pss_seg7_vertex_07005B80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07005C70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07005D60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07005E50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07005F40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07006030, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13,  1, 12, 0x0),
    gsSP1Triangle(13, 12, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07006120, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_07006220, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(13, 14, 11, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07006320, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_07006420, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(pss_seg7_vertex_07006500, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_070065F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070066E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_070067D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_070068C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_070069B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07006AA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07006B90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07006C80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07006D70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07006E60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07006F50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07007040, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07007130, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07007220, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07007310, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07007400, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070074F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_070075E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_070076D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_070077C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_070078B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_070079A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07007A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07007B80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07007C70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07007D60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07007E50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07007F40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07008030, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_07008120, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_07008210, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_07008300, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A7C0 - 0x0700A8B8
const Gfx pss_seg7_dl_0700A7C0[] = {
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
    gsSPDisplayList(pss_seg7_dl_070083B0),
    gsSPDisplayList(pss_seg7_dl_07008E20),
    gsSPDisplayList(pss_seg7_dl_07008EB0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(pss_seg7_dl_070095E8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(pss_seg7_dl_07009750),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
