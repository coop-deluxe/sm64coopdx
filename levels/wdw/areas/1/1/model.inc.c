#include "pc/rom_assets.h"
// 0x07002800 - 0x07002818
static const Lights1 wdw_seg7_lights_07002800 = gdSPDefLights1(
    0x99, 0x99, 0x99,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07002818 - 0x07002830
static const Lights1 wdw_seg7_lights_07002818 = gdSPDefLights1(
    0x3c, 0x3c, 0x3c,
    0x64, 0x64, 0x64, 0x28, 0x28, 0x28
);

// 0x07002830 - 0x07002920
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002830, 0x0040ed70, 45590, 0x00002830, 240);

// 0x07002920 - 0x07002A20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002920, 0x0040ed70, 45590, 0x00002920, 256);

// 0x07002A20 - 0x07002B20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002A20, 0x0040ed70, 45590, 0x00002a20, 256);

// 0x07002B20 - 0x07002C20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002B20, 0x0040ed70, 45590, 0x00002b20, 256);

// 0x07002C20 - 0x07002D20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002C20, 0x0040ed70, 45590, 0x00002c20, 256);

// 0x07002D20 - 0x07002E00
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002D20, 0x0040ed70, 45590, 0x00002d20, 224);

// 0x07002E00 - 0x07002F00
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002E00, 0x0040ed70, 45590, 0x00002e00, 256);

// 0x07002F00 - 0x07002FE0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002F00, 0x0040ed70, 45590, 0x00002f00, 224);

// 0x07002FE0 - 0x070030C0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07002FE0, 0x0040ed70, 45590, 0x00002fe0, 224);

// 0x070030C0 - 0x070031A0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070030C0, 0x0040ed70, 45590, 0x000030c0, 224);

// 0x070031A0 - 0x07003290
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070031A0, 0x0040ed70, 45590, 0x000031a0, 240);

// 0x07003290 - 0x07003380
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003290, 0x0040ed70, 45590, 0x00003290, 240);

// 0x07003380 - 0x07003460
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003380, 0x0040ed70, 45590, 0x00003380, 224);

// 0x07003460 - 0x07003550
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003460, 0x0040ed70, 45590, 0x00003460, 240);

// 0x07003550 - 0x07003630
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003550, 0x0040ed70, 45590, 0x00003550, 224);

// 0x07003630 - 0x07003720
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003630, 0x0040ed70, 45590, 0x00003630, 240);

// 0x07003720 - 0x070037D0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003720, 0x0040ed70, 45590, 0x00003720, 176);

// 0x070037D0 - 0x070038C0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070037D0, 0x0040ed70, 45590, 0x000037d0, 240);

// 0x070038C0 - 0x070039C0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070038C0, 0x0040ed70, 45590, 0x000038c0, 256);

// 0x070039C0 - 0x07003AB0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070039C0, 0x0040ed70, 45590, 0x000039c0, 240);

// 0x07003AB0 - 0x07003BB0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003AB0, 0x0040ed70, 45590, 0x00003ab0, 256);

// 0x07003BB0 - 0x07003CB0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003BB0, 0x0040ed70, 45590, 0x00003bb0, 256);

// 0x07003CB0 - 0x07003D70
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003CB0, 0x0040ed70, 45590, 0x00003cb0, 192);

// 0x07003D70 - 0x07003E30
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003D70, 0x0040ed70, 45590, 0x00003d70, 192);

// 0x07003E30 - 0x07003F20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003E30, 0x0040ed70, 45590, 0x00003e30, 240);

// 0x07003F20 - 0x07004010
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07003F20, 0x0040ed70, 45590, 0x00003f20, 240);

// 0x07004010 - 0x07004100
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004010, 0x0040ed70, 45590, 0x00004010, 240);

// 0x07004100 - 0x070041F0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004100, 0x0040ed70, 45590, 0x00004100, 240);

// 0x070041F0 - 0x07004270
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070041F0, 0x0040ed70, 45590, 0x000041f0, 128);

// 0x07004270 - 0x07004360
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004270, 0x0040ed70, 45590, 0x00004270, 240);

// 0x07004360 - 0x07004440
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004360, 0x0040ed70, 45590, 0x00004360, 224);

// 0x07004440 - 0x07004530
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004440, 0x0040ed70, 45590, 0x00004440, 240);

// 0x07004530 - 0x07004620
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004530, 0x0040ed70, 45590, 0x00004530, 240);

// 0x07004620 - 0x07004710
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004620, 0x0040ed70, 45590, 0x00004620, 240);

// 0x07004710 - 0x070047D0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004710, 0x0040ed70, 45590, 0x00004710, 192);

// 0x070047D0 - 0x070048D0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070047D0, 0x0040ed70, 45590, 0x000047d0, 256);

// 0x070048D0 - 0x070049B0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070048D0, 0x0040ed70, 45590, 0x000048d0, 224);

// 0x070049B0 - 0x07004AA0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070049B0, 0x0040ed70, 45590, 0x000049b0, 240);

// 0x07004AA0 - 0x07004B40
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004AA0, 0x0040ed70, 45590, 0x00004aa0, 160);

// 0x07004B40 - 0x07004C30
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004B40, 0x0040ed70, 45590, 0x00004b40, 240);

// 0x07004C30 - 0x07004D20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004C30, 0x0040ed70, 45590, 0x00004c30, 240);

// 0x07004D20 - 0x07004E00
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004D20, 0x0040ed70, 45590, 0x00004d20, 224);

// 0x07004E00 - 0x07004EF0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004E00, 0x0040ed70, 45590, 0x00004e00, 240);

// 0x07004EF0 - 0x07004FF0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004EF0, 0x0040ed70, 45590, 0x00004ef0, 256);

// 0x07004FF0 - 0x070050D0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07004FF0, 0x0040ed70, 45590, 0x00004ff0, 224);

// 0x070050D0 - 0x070051C0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070050D0, 0x0040ed70, 45590, 0x000050d0, 240);

// 0x070051C0 - 0x070052A0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070051C0, 0x0040ed70, 45590, 0x000051c0, 224);

// 0x070052A0 - 0x07005390
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070052A0, 0x0040ed70, 45590, 0x000052a0, 240);

// 0x07005390 - 0x07005490
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005390, 0x0040ed70, 45590, 0x00005390, 256);

// 0x07005490 - 0x07005580
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005490, 0x0040ed70, 45590, 0x00005490, 240);

// 0x07005580 - 0x07005670
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005580, 0x0040ed70, 45590, 0x00005580, 240);

// 0x07005670 - 0x07005770
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005670, 0x0040ed70, 45590, 0x00005670, 256);

// 0x07005770 - 0x07005870
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005770, 0x0040ed70, 45590, 0x00005770, 256);

// 0x07005870 - 0x07005960
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005870, 0x0040ed70, 45590, 0x00005870, 240);

// 0x07005960 - 0x07005A60
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005960, 0x0040ed70, 45590, 0x00005960, 256);

// 0x07005A60 - 0x07005B60
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005A60, 0x0040ed70, 45590, 0x00005a60, 256);

// 0x07005B60 - 0x07005C60
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005B60, 0x0040ed70, 45590, 0x00005b60, 256);

// 0x07005C60 - 0x07005D60
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005C60, 0x0040ed70, 45590, 0x00005c60, 256);

// 0x07005D60 - 0x07005E40
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005D60, 0x0040ed70, 45590, 0x00005d60, 224);

// 0x07005E40 - 0x07005F30
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005E40, 0x0040ed70, 45590, 0x00005e40, 240);

// 0x07005F30 - 0x07006020
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07005F30, 0x0040ed70, 45590, 0x00005f30, 240);

// 0x07006020 - 0x07006110
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006020, 0x0040ed70, 45590, 0x00006020, 240);

// 0x07006110 - 0x07006210
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006110, 0x0040ed70, 45590, 0x00006110, 256);

// 0x07006210 - 0x070062C0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006210, 0x0040ed70, 45590, 0x00006210, 176);

// 0x070062C0 - 0x070063B0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070062C0, 0x0040ed70, 45590, 0x000062c0, 240);

// 0x070063B0 - 0x070064A0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070063B0, 0x0040ed70, 45590, 0x000063b0, 240);

// 0x070064A0 - 0x07006580
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070064A0, 0x0040ed70, 45590, 0x000064a0, 224);

// 0x07006580 - 0x070065B0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006580, 0x0040ed70, 45590, 0x00006580, 48);

// 0x070065B0 - 0x070066A0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070065B0, 0x0040ed70, 45590, 0x000065b0, 240);

// 0x070066A0 - 0x07006790
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070066A0, 0x0040ed70, 45590, 0x000066a0, 240);

// 0x07006790 - 0x07006880
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006790, 0x0040ed70, 45590, 0x00006790, 240);

// 0x07006880 - 0x07006970
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006880, 0x0040ed70, 45590, 0x00006880, 240);

// 0x07006970 - 0x07006A50
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006970, 0x0040ed70, 45590, 0x00006970, 224);

// 0x07006A50 - 0x07006B40
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006A50, 0x0040ed70, 45590, 0x00006a50, 240);

// 0x07006B40 - 0x07006C20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006B40, 0x0040ed70, 45590, 0x00006b40, 224);

// 0x07006C20 - 0x07006D10
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006C20, 0x0040ed70, 45590, 0x00006c20, 240);

// 0x07006D10 - 0x07006E00
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006D10, 0x0040ed70, 45590, 0x00006d10, 240);

// 0x07006E00 - 0x07006EF0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006E00, 0x0040ed70, 45590, 0x00006e00, 240);

// 0x07006EF0 - 0x07006FD0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006EF0, 0x0040ed70, 45590, 0x00006ef0, 224);

// 0x07006FD0 - 0x070070D0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07006FD0, 0x0040ed70, 45590, 0x00006fd0, 256);

// 0x070070D0 - 0x070071D0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070070D0, 0x0040ed70, 45590, 0x000070d0, 256);

// 0x070071D0 - 0x070072D0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070071D0, 0x0040ed70, 45590, 0x000071d0, 256);

// 0x070072D0 - 0x070073C0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070072D0, 0x0040ed70, 45590, 0x000072d0, 240);

// 0x070073C0 - 0x070074C0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070073C0, 0x0040ed70, 45590, 0x000073c0, 256);

// 0x070074C0 - 0x070075B0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070074C0, 0x0040ed70, 45590, 0x000074c0, 240);

// 0x070075B0 - 0x070076B0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070075B0, 0x0040ed70, 45590, 0x000075b0, 256);

// 0x070076B0 - 0x070077B0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070076B0, 0x0040ed70, 45590, 0x000076b0, 256);

// 0x070077B0 - 0x07007840
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070077B0, 0x0040ed70, 45590, 0x000077b0, 144);

// 0x07007840 - 0x07007930
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007840, 0x0040ed70, 45590, 0x00007840, 240);

// 0x07007930 - 0x07007A20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007930, 0x0040ed70, 45590, 0x00007930, 240);

// 0x07007A20 - 0x07007B10
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007A20, 0x0040ed70, 45590, 0x00007a20, 240);

// 0x07007B10 - 0x07007C00
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007B10, 0x0040ed70, 45590, 0x00007b10, 240);

// 0x07007C00 - 0x07007CF0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007C00, 0x0040ed70, 45590, 0x00007c00, 240);

// 0x07007CF0 - 0x07007DF0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007CF0, 0x0040ed70, 45590, 0x00007cf0, 256);

// 0x07007DF0 - 0x07007E20
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007DF0, 0x0040ed70, 45590, 0x00007df0, 48);

// 0x07007E20 - 0x07007F00
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007E20, 0x0040ed70, 45590, 0x00007e20, 224);

// 0x07007F00 - 0x07007FF0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007F00, 0x0040ed70, 45590, 0x00007f00, 240);

// 0x07007FF0 - 0x070080F0
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07007FF0, 0x0040ed70, 45590, 0x00007ff0, 256);

// 0x070080F0 - 0x07008120
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070080F0, 0x0040ed70, 45590, 0x000080f0, 48);

// 0x07008120 - 0x07008160
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07008120, 0x0040ed70, 45590, 0x00008120, 64);

// 0x07008160 - 0x07008598
static const Gfx wdw_seg7_dl_07008160[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wdw_seg7_lights_07002800.l, 1),
    gsSPLight(&wdw_seg7_lights_07002800.a, 2),
    gsSPVertex(wdw_seg7_vertex_07002830, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002920, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 10,  4,  6, 0x0),
    gsSP2Triangles(10, 12,  4, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002A20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002B20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002C20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  0, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002D20, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002E00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002F00, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(wdw_seg7_vertex_07002FE0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_070030C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_070031A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003290, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003380, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003460, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003550, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPLight(&wdw_seg7_lights_07002818.l, 1),
    gsSPLight(&wdw_seg7_lights_07002818.a, 2),
    gsSPVertex(wdw_seg7_vertex_07003630, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003720, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP1Triangle( 8,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008598 - 0x070087B8
static const Gfx wdw_seg7_dl_07008598[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wdw_seg7_lights_07002800.l, 1),
    gsSPLight(&wdw_seg7_lights_07002800.a, 2),
    gsSPVertex(wdw_seg7_vertex_070037D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 8, 11, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_070038C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_070039C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003AB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003BB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  4,  8,  5, 0x0),
    gsSP2Triangles( 4,  9,  8, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003CB0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPLight(&wdw_seg7_lights_07002818.l, 1),
    gsSPLight(&wdw_seg7_lights_07002818.a, 2),
    gsSPVertex(wdw_seg7_vertex_07003D70, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x070087B8 - 0x07008910
static const Gfx wdw_seg7_dl_070087B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wdw_seg7_lights_07002800.l, 1),
    gsSPLight(&wdw_seg7_lights_07002800.a, 2),
    gsSPVertex(wdw_seg7_vertex_07003E30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07003F20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004010, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004100, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wdw_seg7_vertex_070041F0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008910 - 0x07008B00
static const Gfx wdw_seg7_dl_07008910[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_07004270, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004360, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 2, 10, 11, 0x0,  0, 12, 13, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004440, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004530, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004620, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004710, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  3,  7,  0, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPLight(&wdw_seg7_lights_07002818.l, 1),
    gsSPLight(&wdw_seg7_lights_07002818.a, 2),
    gsSPVertex(wdw_seg7_vertex_070047D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008B00 - 0x07008C00
static const Gfx wdw_seg7_dl_07008B00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wdw_seg7_lights_07002800.l, 1),
    gsSPLight(&wdw_seg7_lights_07002800.a, 2),
    gsSPVertex(wdw_seg7_vertex_070048D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 10, 0x0),
    gsSPVertex(wdw_seg7_vertex_070049B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  1, 0x0,  0, 14,  1, 0x0),
    gsSP1Triangle( 1, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004AA0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008C00 - 0x07008CA0
static const Gfx wdw_seg7_dl_07008C00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_07004B40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004C30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008CA0 - 0x07008E08
static const Gfx wdw_seg7_dl_07008CA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wdw_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_07004D20, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12,  8, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004E00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0,  8, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004EF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(wdw_seg7_vertex_07004FF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_070050D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008E08 - 0x07009268
static const Gfx wdw_seg7_dl_07008E08[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_070051C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_070052A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005390, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005490, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005580, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005670, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005770, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 3, 12,  4, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005870, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005960, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14,  8, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005A60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005B60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005C60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  3, 15,  4, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005D60, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  4,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005E40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07005F30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006020, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006110, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  9, 15,  7, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006210, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009268 - 0x07009358
static const Gfx wdw_seg7_dl_07009268[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_070062C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_070063B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wdw_seg7_vertex_070064A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  7, 11, 12, 0x0),
    gsSP1Triangle( 0,  2, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006580, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009358 - 0x07009850
static const Gfx wdw_seg7_dl_07009358[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_070065B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_070066A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 8, 14,  9, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006790, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 8, 10, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006880, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006970, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006A50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006B40, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006C20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006D10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006E00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006EF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(wdw_seg7_vertex_07006FD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 10, 15, 11, 0x0),
    gsSPVertex(wdw_seg7_vertex_070070D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_070071D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_070072D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_070073C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  1,  8,  2, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_070074C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_070075B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  2,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_070076B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  0, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  0,  5,  8, 0x0),
    gsSP2Triangles( 0,  8,  6, 0x0,  7,  9,  0, 0x0),
    gsSP2Triangles( 5, 10,  8, 0x0,  5, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  7, 15,  9, 0x0),
    gsSPVertex(wdw_seg7_vertex_070077B0, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009850 - 0x070099B0
static const Gfx wdw_seg7_dl_07009850[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_07007840, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007930, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007A20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007B10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007C00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007CF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  6, 13, 14, 0x0),
    gsSP1Triangle( 6, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007DF0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070099B0 - 0x07009AB0
static const Gfx wdw_seg7_dl_070099B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_07007E20, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007F00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wdw_seg7_vertex_07007FF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  9, 12, 13, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_070080F0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&wdw_seg7_lights_07002818.l, 1),
    gsSPLight(&wdw_seg7_lights_07002818.a, 2),
    gsSPVertex(wdw_seg7_vertex_07008120, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009AB0 - 0x07009B78
const Gfx wdw_seg7_dl_07009AB0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wdw_seg7_dl_07008160),
    gsSPDisplayList(wdw_seg7_dl_07008598),
    gsSPDisplayList(wdw_seg7_dl_070087B8),
    gsSPDisplayList(wdw_seg7_dl_07008910),
    gsSPDisplayList(wdw_seg7_dl_07008B00),
    gsSPDisplayList(wdw_seg7_dl_07008C00),
    gsSPDisplayList(wdw_seg7_dl_07008CA0),
    gsSPDisplayList(wdw_seg7_dl_07008E08),
    gsSPDisplayList(wdw_seg7_dl_07009268),
    gsSPDisplayList(wdw_seg7_dl_07009358),
    gsSPDisplayList(wdw_seg7_dl_07009850),
    gsSPDisplayList(wdw_seg7_dl_070099B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
