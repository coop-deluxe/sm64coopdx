#include "pc/rom_assets.h"
// 0x07004BE0 - 0x07004BF8
static const Lights1 ssl_seg7_lights_07004BE0 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07004BF8 - 0x07004C10
static const Lights1 ssl_seg7_lights_07004BF8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07004C10 - 0x07004C28
static const Lights1 ssl_seg7_lights_07004C10 = gdSPDefLights1(
    0x0c, 0x0c, 0x0c,
    0x32, 0x32, 0x32, 0x28, 0x28, 0x28
);

// 0x07004C28 - 0x07004C40
static const Lights1 ssl_seg7_lights_07004C28 = gdSPDefLights1(
    0x19, 0x19, 0x19,
    0x64, 0x64, 0x64, 0x28, 0x28, 0x28
);

// 0x07004C40 - 0x07004C80
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07004C40, 0x003e76b0, 82641, 0x00004c40, 64);

// 0x07004C80 - 0x07004D70
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07004C80, 0x003e76b0, 82641, 0x00004c80, 240);

// 0x07004D70 - 0x07004E60
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07004D70, 0x003e76b0, 82641, 0x00004d70, 240);

// 0x07004E60 - 0x07004F60
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07004E60, 0x003e76b0, 82641, 0x00004e60, 256);

// 0x07004F60 - 0x07004FA0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07004F60, 0x003e76b0, 82641, 0x00004f60, 64);

// 0x07004FA0 - 0x07004FE0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07004FA0, 0x003e76b0, 82641, 0x00004fa0, 64);

// 0x07004FE0 - 0x070050D0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07004FE0, 0x003e76b0, 82641, 0x00004fe0, 240);

// 0x070050D0 - 0x070051C0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070050D0, 0x003e76b0, 82641, 0x000050d0, 240);

// 0x070051C0 - 0x070052B0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070051C0, 0x003e76b0, 82641, 0x000051c0, 240);

// 0x070052B0 - 0x070053A0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070052B0, 0x003e76b0, 82641, 0x000052b0, 240);

// 0x070053A0 - 0x07005490
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070053A0, 0x003e76b0, 82641, 0x000053a0, 240);

// 0x07005490 - 0x07005580
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005490, 0x003e76b0, 82641, 0x00005490, 240);

// 0x07005580 - 0x07005670
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005580, 0x003e76b0, 82641, 0x00005580, 240);

// 0x07005670 - 0x07005760
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005670, 0x003e76b0, 82641, 0x00005670, 240);

// 0x07005760 - 0x07005850
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005760, 0x003e76b0, 82641, 0x00005760, 240);

// 0x07005850 - 0x07005940
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005850, 0x003e76b0, 82641, 0x00005850, 240);

// 0x07005940 - 0x07005A30
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005940, 0x003e76b0, 82641, 0x00005940, 240);

// 0x07005A30 - 0x07005B20
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005A30, 0x003e76b0, 82641, 0x00005a30, 240);

// 0x07005B20 - 0x07005C10
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005B20, 0x003e76b0, 82641, 0x00005b20, 240);

// 0x07005C10 - 0x07005C80
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005C10, 0x003e76b0, 82641, 0x00005c10, 112);

// 0x07005C80 - 0x07005D60
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005C80, 0x003e76b0, 82641, 0x00005c80, 224);

// 0x07005D60 - 0x07005E60
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005D60, 0x003e76b0, 82641, 0x00005d60, 256);

// 0x07005E60 - 0x07005F50
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005E60, 0x003e76b0, 82641, 0x00005e60, 240);

// 0x07005F50 - 0x07006030
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07005F50, 0x003e76b0, 82641, 0x00005f50, 224);

// 0x07006030 - 0x07006120
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006030, 0x003e76b0, 82641, 0x00006030, 240);

// 0x07006120 - 0x07006220
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006120, 0x003e76b0, 82641, 0x00006120, 256);

// 0x07006220 - 0x07006310
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006220, 0x003e76b0, 82641, 0x00006220, 240);

// 0x07006310 - 0x070063F0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006310, 0x003e76b0, 82641, 0x00006310, 224);

// 0x070063F0 - 0x07006470
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070063F0, 0x003e76b0, 82641, 0x000063f0, 128);

// 0x07006470 - 0x07006560
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006470, 0x003e76b0, 82641, 0x00006470, 240);

// 0x07006560 - 0x070065D0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006560, 0x003e76b0, 82641, 0x00006560, 112);

// 0x070065D0 - 0x070066C0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070065D0, 0x003e76b0, 82641, 0x000065d0, 240);

// 0x070066C0 - 0x070067B0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070066C0, 0x003e76b0, 82641, 0x000066c0, 240);

// 0x070067B0 - 0x070068B0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070067B0, 0x003e76b0, 82641, 0x000067b0, 256);

// 0x070068B0 - 0x07006990
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070068B0, 0x003e76b0, 82641, 0x000068b0, 224);

// 0x07006990 - 0x07006A80
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006990, 0x003e76b0, 82641, 0x00006990, 240);

// 0x07006A80 - 0x07006B60
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006A80, 0x003e76b0, 82641, 0x00006a80, 224);

// 0x07006B60 - 0x07006C50
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006B60, 0x003e76b0, 82641, 0x00006b60, 240);

// 0x07006C50 - 0x07006D50
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006C50, 0x003e76b0, 82641, 0x00006c50, 256);

// 0x07006D50 - 0x07006E40
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006D50, 0x003e76b0, 82641, 0x00006d50, 240);

// 0x07006E40 - 0x07006F20
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006E40, 0x003e76b0, 82641, 0x00006e40, 224);

// 0x07006F20 - 0x07007010
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07006F20, 0x003e76b0, 82641, 0x00006f20, 240);

// 0x07007010 - 0x07007100
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007010, 0x003e76b0, 82641, 0x00007010, 240);

// 0x07007100 - 0x070071F0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007100, 0x003e76b0, 82641, 0x00007100, 240);

// 0x070071F0 - 0x070072E0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070071F0, 0x003e76b0, 82641, 0x000071f0, 240);

// 0x070072E0 - 0x070073D0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070072E0, 0x003e76b0, 82641, 0x000072e0, 240);

// 0x070073D0 - 0x070074C0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070073D0, 0x003e76b0, 82641, 0x000073d0, 240);

// 0x070074C0 - 0x070075B0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070074C0, 0x003e76b0, 82641, 0x000074c0, 240);

// 0x070075B0 - 0x070076A0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070075B0, 0x003e76b0, 82641, 0x000075b0, 240);

// 0x070076A0 - 0x07007790
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070076A0, 0x003e76b0, 82641, 0x000076a0, 240);

// 0x07007790 - 0x07007880
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007790, 0x003e76b0, 82641, 0x00007790, 240);

// 0x07007880 - 0x07007900
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007880, 0x003e76b0, 82641, 0x00007880, 128);

// 0x07007900 - 0x07007A00
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007900, 0x003e76b0, 82641, 0x00007900, 256);

// 0x07007A00 - 0x07007AF0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007A00, 0x003e76b0, 82641, 0x00007a00, 240);

// 0x07007AF0 - 0x07007BE0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007AF0, 0x003e76b0, 82641, 0x00007af0, 240);

// 0x07007BE0 - 0x07007C80
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007BE0, 0x003e76b0, 82641, 0x00007be0, 160);

// 0x07007C80 - 0x07007D70
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007C80, 0x003e76b0, 82641, 0x00007c80, 240);

// 0x07007D70 - 0x07007E60
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007D70, 0x003e76b0, 82641, 0x00007d70, 240);

// 0x07007E60 - 0x07007F50
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007E60, 0x003e76b0, 82641, 0x00007e60, 240);

// 0x07007F50 - 0x07008040
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07007F50, 0x003e76b0, 82641, 0x00007f50, 240);

// 0x07008040 - 0x07008130
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07008040, 0x003e76b0, 82641, 0x00008040, 240);

// 0x07008130 - 0x07008220
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07008130, 0x003e76b0, 82641, 0x00008130, 240);

// 0x07008220 - 0x07008310
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07008220, 0x003e76b0, 82641, 0x00008220, 240);

// 0x07008310 - 0x07008400
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07008310, 0x003e76b0, 82641, 0x00008310, 240);

// 0x07008400 - 0x070084F0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07008400, 0x003e76b0, 82641, 0x00008400, 240);

// 0x070084F0 - 0x070085E0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070084F0, 0x003e76b0, 82641, 0x000084f0, 240);

// 0x070085E0 - 0x070086C0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070085E0, 0x003e76b0, 82641, 0x000085e0, 224);

// 0x070086C0 - 0x070087C0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070086C0, 0x003e76b0, 82641, 0x000086c0, 256);

// 0x070087C0 - 0x070088A0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070087C0, 0x003e76b0, 82641, 0x000087c0, 224);

// 0x070088A0 - 0x070089A0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070088A0, 0x003e76b0, 82641, 0x000088a0, 256);

// 0x070089A0 - 0x07008AA0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070089A0, 0x003e76b0, 82641, 0x000089a0, 256);

// 0x07008AA0 - 0x07008BA0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07008AA0, 0x003e76b0, 82641, 0x00008aa0, 256);

// 0x07008BA0 - 0x07008C40
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07008BA0, 0x003e76b0, 82641, 0x00008ba0, 160);

// 0x07008C40 - 0x07008DE0
static const Gfx ssl_seg7_dl_07008C40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_07004BE0.l, 1),
    gsSPLight(&ssl_seg7_lights_07004BE0.a, 2),
    gsSPVertex(ssl_seg7_vertex_07004C40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ssl_seg7_lights_07004BF8.l, 1),
    gsSPLight(&ssl_seg7_lights_07004BF8.a, 2),
    gsSPVertex(ssl_seg7_vertex_07004C80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07004D70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07004E60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 4,  2,  6, 0x0,  2,  7,  5, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  3,  9,  1, 0x0),
    gsSP2Triangles(10,  9,  3, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles(10, 11,  5, 0x0,  7, 10,  5, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPLight(&ssl_seg7_lights_07004C10.l, 1),
    gsSPLight(&ssl_seg7_lights_07004C10.a, 2),
    gsSPVertex(ssl_seg7_vertex_07004F60, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ssl_seg7_lights_07004C28.l, 1),
    gsSPLight(&ssl_seg7_lights_07004C28.a, 2),
    gsSPVertex(ssl_seg7_vertex_07004FA0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008DE0 - 0x07009170
static const Gfx ssl_seg7_dl_07008DE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_07004BF8.l, 1),
    gsSPLight(&ssl_seg7_lights_07004BF8.a, 2),
    gsSPVertex(ssl_seg7_vertex_07004FE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070050D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_070051C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070052B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_070053A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005490, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005580, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005670, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005760, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005850, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005940, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005A30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005B20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005C10, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009170 - 0x07009410
static const Gfx ssl_seg7_dl_07009170[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07005C80, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005D60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005E60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07005F50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006030, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006120, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  0, 11,  1, 0x0),
    gsSP2Triangles( 0, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006220, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles(11,  7, 10, 0x0,  8, 13,  9, 0x0),
    gsSP1Triangle( 8, 14, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006310, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ssl_seg7_vertex_070063F0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ssl_seg7_lights_07004C10.l, 1),
    gsSPLight(&ssl_seg7_lights_07004C10.a, 2),
    gsSPVertex(ssl_seg7_vertex_07006470, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006560, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009410 - 0x07009950
static const Gfx ssl_seg7_dl_07009410[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_07004BF8.l, 1),
    gsSPLight(&ssl_seg7_lights_07004BF8.a, 2),
    gsSPVertex(ssl_seg7_vertex_070065D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070066C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070067B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_070068B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006990, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006A80, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006B60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006C50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006D50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006E40, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07006F20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007010, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007100, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070071F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_070072E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070073D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_070074C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070075B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_070076A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007790, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007880, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009950 - 0x07009A40
static const Gfx ssl_seg7_dl_07009950[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07007900, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007A00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007AF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007BE0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009A40 - 0x07009C60
static const Gfx ssl_seg7_dl_07009A40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07007C80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007D70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007E60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07007F50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07008040, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07008130, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07008220, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07008310, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009C60 - 0x07009E90
static const Gfx ssl_seg7_dl_07009C60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07008400, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles(10, 11,  5, 0x0, 10,  5,  9, 0x0),
    gsSP2Triangles( 8, 12, 10, 0x0,  8, 13, 12, 0x0),
    gsSP2Triangles( 7,  8, 10, 0x0, 10, 14, 11, 0x0),
    gsSP1Triangle(10,  9,  7, 0x0),
    gsSPVertex(ssl_seg7_vertex_070084F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  8, 0x0,  0,  8,  1, 0x0),
    gsSP2Triangles( 8,  7,  1, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14,  0,  2, 0x0),
    gsSP1Triangle(14,  2, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070085E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0, 11,  1, 13, 0x0),
    gsSP1Triangle(11, 13,  9, 0x0),
    gsSPVertex(ssl_seg7_vertex_070086C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  3,  9,  7, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  8, 10,  4, 0x0),
    gsSP2Triangles( 1, 11,  2, 0x0,  6, 12,  1, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_070087C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_070088A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009E90 - 0x07009F48
static const Gfx ssl_seg7_dl_07009E90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_070089A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07008AA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07008BA0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009F48 - 0x0700A020
const Gfx ssl_seg7_dl_07009F48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_07008C40),
    gsSPDisplayList(ssl_seg7_dl_07008DE0),
    gsSPDisplayList(ssl_seg7_dl_07009170),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_07009410),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_07009950),
    gsSPDisplayList(ssl_seg7_dl_07009A40),
    gsSPDisplayList(ssl_seg7_dl_07009C60),
    gsSPDisplayList(ssl_seg7_dl_07009E90),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
