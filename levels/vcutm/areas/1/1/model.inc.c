#include "pc/rom_assets.h"
// 0x07003000 - 0x07003018
static const Lights1 vcutm_seg7_lights_07003000 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07003018 - 0x07003030
static const Lights1 vcutm_seg7_lights_07003018 = gdSPDefLights1(
    0x32, 0x3f, 0x37,
    0xc8, 0xff, 0xdc, 0x28, 0x28, 0x28
);

// 0x07003030 - 0x07003048
static const Lights1 vcutm_seg7_lights_07003030 = gdSPDefLights1(
    0x2a, 0x2a, 0x2a,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x07003048 - 0x07003128
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003048, 0x0045c600, 19475, 0x00003048, 224);

// 0x07003128 - 0x07003228
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003128, 0x0045c600, 19475, 0x00003128, 256);

// 0x07003228 - 0x07003308
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003228, 0x0045c600, 19475, 0x00003228, 224);

// 0x07003308 - 0x070033E8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003308, 0x0045c600, 19475, 0x00003308, 224);

// 0x070033E8 - 0x070034D8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070033E8, 0x0045c600, 19475, 0x000033e8, 240);

// 0x070034D8 - 0x070035D8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070034D8, 0x0045c600, 19475, 0x000034d8, 256);

// 0x070035D8 - 0x070036D8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070035D8, 0x0045c600, 19475, 0x000035d8, 256);

// 0x070036D8 - 0x070037D8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070036D8, 0x0045c600, 19475, 0x000036d8, 256);

// 0x070037D8 - 0x070038D8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070037D8, 0x0045c600, 19475, 0x000037d8, 256);

// 0x070038D8 - 0x070039D8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070038D8, 0x0045c600, 19475, 0x000038d8, 256);

// 0x070039D8 - 0x07003AD8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070039D8, 0x0045c600, 19475, 0x000039d8, 256);

// 0x07003AD8 - 0x07003BD8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003AD8, 0x0045c600, 19475, 0x00003ad8, 256);

// 0x07003BD8 - 0x07003CC8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003BD8, 0x0045c600, 19475, 0x00003bd8, 240);

// 0x07003CC8 - 0x07003DC8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003CC8, 0x0045c600, 19475, 0x00003cc8, 256);

// 0x07003DC8 - 0x07003EC8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003DC8, 0x0045c600, 19475, 0x00003dc8, 256);

// 0x07003EC8 - 0x07003FC8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003EC8, 0x0045c600, 19475, 0x00003ec8, 256);

// 0x07003FC8 - 0x070040C8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07003FC8, 0x0045c600, 19475, 0x00003fc8, 256);

// 0x070040C8 - 0x070041B8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070040C8, 0x0045c600, 19475, 0x000040c8, 240);

// 0x070041B8 - 0x070042B8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070041B8, 0x0045c600, 19475, 0x000041b8, 256);

// 0x070042B8 - 0x070043B8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070042B8, 0x0045c600, 19475, 0x000042b8, 256);

// 0x070043B8 - 0x070044B8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070043B8, 0x0045c600, 19475, 0x000043b8, 256);

// 0x070044B8 - 0x07004598
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070044B8, 0x0045c600, 19475, 0x000044b8, 224);

// 0x07004598 - 0x07004688
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004598, 0x0045c600, 19475, 0x00004598, 240);

// 0x07004688 - 0x07004778
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004688, 0x0045c600, 19475, 0x00004688, 240);

// 0x07004778 - 0x07004858
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004778, 0x0045c600, 19475, 0x00004778, 224);

// 0x07004858 - 0x07004938
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004858, 0x0045c600, 19475, 0x00004858, 224);

// 0x07004938 - 0x07004A38
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004938, 0x0045c600, 19475, 0x00004938, 256);

// 0x07004A38 - 0x07004B38
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004A38, 0x0045c600, 19475, 0x00004a38, 256);

// 0x07004B38 - 0x07004C38
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004B38, 0x0045c600, 19475, 0x00004b38, 256);

// 0x07004C38 - 0x07004D38
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004C38, 0x0045c600, 19475, 0x00004c38, 256);

// 0x07004D38 - 0x07004E38
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004D38, 0x0045c600, 19475, 0x00004d38, 256);

// 0x07004E38 - 0x07004F18
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004E38, 0x0045c600, 19475, 0x00004e38, 224);

// 0x07004F18 - 0x07004FB8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004F18, 0x0045c600, 19475, 0x00004f18, 160);

// 0x07004FB8 - 0x070050A8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07004FB8, 0x0045c600, 19475, 0x00004fb8, 240);

// 0x070050A8 - 0x07005198
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070050A8, 0x0045c600, 19475, 0x000050a8, 240);

// 0x07005198 - 0x07005288
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005198, 0x0045c600, 19475, 0x00005198, 240);

// 0x07005288 - 0x07005378
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005288, 0x0045c600, 19475, 0x00005288, 240);

// 0x07005378 - 0x07005468
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005378, 0x0045c600, 19475, 0x00005378, 240);

// 0x07005468 - 0x07005558
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005468, 0x0045c600, 19475, 0x00005468, 240);

// 0x07005558 - 0x07005648
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005558, 0x0045c600, 19475, 0x00005558, 240);

// 0x07005648 - 0x07005738
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005648, 0x0045c600, 19475, 0x00005648, 240);

// 0x07005738 - 0x07005828
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005738, 0x0045c600, 19475, 0x00005738, 240);

// 0x07005828 - 0x07005918
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005828, 0x0045c600, 19475, 0x00005828, 240);

// 0x07005918 - 0x07005A18
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005918, 0x0045c600, 19475, 0x00005918, 256);

// 0x07005A18 - 0x07005B18
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005A18, 0x0045c600, 19475, 0x00005a18, 256);

// 0x07005B18 - 0x07005C18
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005B18, 0x0045c600, 19475, 0x00005b18, 256);

// 0x07005C18 - 0x07005D18
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005C18, 0x0045c600, 19475, 0x00005c18, 256);

// 0x07005D18 - 0x07005E18
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005D18, 0x0045c600, 19475, 0x00005d18, 256);

// 0x07005E18 - 0x07005F18
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005E18, 0x0045c600, 19475, 0x00005e18, 256);

// 0x07005F18 - 0x07006018
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07005F18, 0x0045c600, 19475, 0x00005f18, 256);

// 0x07006018 - 0x07006118
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006018, 0x0045c600, 19475, 0x00006018, 256);

// 0x07006118 - 0x07006198
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006118, 0x0045c600, 19475, 0x00006118, 128);

// 0x07006198 - 0x07006298
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006198, 0x0045c600, 19475, 0x00006198, 256);

// 0x07006298 - 0x07006388
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006298, 0x0045c600, 19475, 0x00006298, 240);

// 0x07006388 - 0x07006468
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006388, 0x0045c600, 19475, 0x00006388, 224);

// 0x07006468 - 0x07006548
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006468, 0x0045c600, 19475, 0x00006468, 224);

// 0x07006548 - 0x07006648
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006548, 0x0045c600, 19475, 0x00006548, 256);

// 0x07006648 - 0x07006728
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006648, 0x0045c600, 19475, 0x00006648, 224);

// 0x07006728 - 0x070067D8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006728, 0x0045c600, 19475, 0x00006728, 176);

// 0x070067D8 - 0x070068B8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070067D8, 0x0045c600, 19475, 0x000067d8, 224);

// 0x070068B8 - 0x070069B8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070068B8, 0x0045c600, 19475, 0x000068b8, 256);

// 0x070069B8 - 0x07006A98
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070069B8, 0x0045c600, 19475, 0x000069b8, 224);

// 0x07006A98 - 0x07006AD8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006A98, 0x0045c600, 19475, 0x00006a98, 64);

// 0x07006AD8 - 0x07006BC8
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006AD8, 0x0045c600, 19475, 0x00006ad8, 240);

// 0x07006BC8 - 0x07006C48
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07006BC8, 0x0045c600, 19475, 0x00006bc8, 128);

// 0x07006C48 - 0x070074A0
static const Gfx vcutm_seg7_dl_07006C48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 16 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&vcutm_seg7_lights_07003000.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003000.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07003048, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003128, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003228, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003308, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  3, 11, 12, 0x0),
    gsSP2Triangles( 3,  6, 11, 0x0,  0,  2, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070033E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070034D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070035D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles( 7, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070036D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070037D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070038D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 6, 12,  7, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070039D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  6, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003AD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003BD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003CC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  4, 15,  8, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003DC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003EC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07003FC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070040C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070041B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070042B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070043B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 6,  8, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070044B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004598, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004688, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  0, 13,  1, 0x0),
    gsSP1Triangle(10, 12, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004778, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004858, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004938, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4, 10,  5, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  7,  9, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004A38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004B38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004C38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004D38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4,  6, 10, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004E38, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07004F18, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x070074A0 - 0x07007660
static const Gfx vcutm_seg7_dl_070074A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&vcutm_seg7_lights_07003018.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003018.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07004FB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070050A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPLight(&vcutm_seg7_lights_07003000.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003000.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07005198, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005288, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005378, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005468, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007660 - 0x07007940
static const Gfx vcutm_seg7_dl_07007660[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&vcutm_seg7_lights_07003030.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003030.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07005558, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005648, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPLight(&vcutm_seg7_lights_07003000.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003000.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07005738, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  3,  6,  5, 0x0),
    gsSP2Triangles( 7,  3,  1, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 9,  5,  6, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles(11,  1,  4, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 0,  7,  1, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005828, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  4,  0,  5, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  5,  9,  7, 0x0),
    gsSP2Triangles(10,  9,  5, 0x0,  9, 11,  7, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005918, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005A18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2,  1, 13, 0x0,  2, 13, 14, 0x0),
    gsSP2Triangles(14, 11,  2, 0x0,  1,  3,  5, 0x0),
    gsSP1Triangle( 1,  5, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005B18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 7,  4,  6, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005C18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0,  9, 12,  4, 0x0),
    gsSP2Triangles( 2,  7,  6, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles( 6, 11, 14, 0x0,  8, 11,  6, 0x0),
    gsSP1Triangle( 6, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007940 - 0x07007AD8
static const Gfx vcutm_seg7_dl_07007940[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, vcutm_seg7_texture_07002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&vcutm_seg7_lights_07003030.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003030.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07005D18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  4, 11,  5, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPLight(&vcutm_seg7_lights_07003000.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003000.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07005E18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07005F18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(14, 13, 12, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006018, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006118, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  0, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 4,  3,  7, 0x0,  4,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007AD8 - 0x07007CA0
static const Gfx vcutm_seg7_dl_07007AD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(vcutm_seg7_vertex_07006198, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006298, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006388, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  7,  9, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006468, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006548, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006648, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006728, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  2,  9, 0x0),
    gsSP1Triangle( 6, 10,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007CA0 - 0x07007D80
static const Gfx vcutm_seg7_dl_07007CA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(vcutm_seg7_vertex_070067D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 1, 10,  2, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 2, 10, 12, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles(12, 11,  6, 0x0,  8,  9, 13, 0x0),
    gsSP2Triangles(11,  4,  6, 0x0,  9,  0, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070068B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  3,  5, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007D80 - 0x07007E00
static const Gfx vcutm_seg7_dl_07007D80[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, vcutm_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(vcutm_seg7_vertex_070069B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006A98, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007E00 - 0x07007E88
static const Gfx vcutm_seg7_dl_07007E00[] = {
    gsSPLight(&vcutm_seg7_lights_07003030.l, 1),
    gsSPLight(&vcutm_seg7_lights_07003030.a, 2),
    gsSPVertex(vcutm_seg7_vertex_07006AD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07006BC8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  0, 0x0,  6,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  1, 0x0,  4,  1,  7, 0x0),
    gsSP1Triangle( 0,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007E88 - 0x07007F90
const Gfx vcutm_seg7_dl_07007E88[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(vcutm_seg7_dl_07006C48),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(vcutm_seg7_dl_070074A0),
    gsSPDisplayList(vcutm_seg7_dl_07007660),
    gsSPDisplayList(vcutm_seg7_dl_07007940),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(vcutm_seg7_dl_07007AD8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(vcutm_seg7_dl_07007CA0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(vcutm_seg7_dl_07007D80),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(vcutm_seg7_dl_07007E00),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
