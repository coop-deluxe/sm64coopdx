#include "pc/rom_assets.h"
// 0x07003000 - 0x07003018
static const Lights1 cotmc_seg7_lights_07003000 = gdSPDefLights1(
    0x4b, 0x78, 0x70,
    0x96, 0xf0, 0xe1, 0x28, 0x28, 0x28
);

// 0x07003018 - 0x07003030
static const Lights1 cotmc_seg7_lights_07003018 = gdSPDefLights1(
    0x44, 0x44, 0x44,
    0x88, 0x88, 0x88, 0x28, 0x28, 0x28
);

// 0x07003030 - 0x07003048
static const Lights1 cotmc_seg7_lights_07003030 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07003048 - 0x07003060
static const Lights1 cotmc_seg7_lights_07003048 = gdSPDefLights1(
    0x00, 0x3c, 0x3c,
    0x00, 0x78, 0x78, 0x28, 0x28, 0x28
);

// 0x07003060 - 0x07003078
static const Lights1 cotmc_seg7_lights_07003060 = gdSPDefLights1(
    0x3b, 0x3b, 0x3b,
    0x77, 0x77, 0x77, 0x28, 0x28, 0x28
);

// 0x07003078 - 0x07003090
static const Lights1 cotmc_seg7_lights_07003078 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07003090 - 0x070030A8
static const Lights1 cotmc_seg7_lights_07003090 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x070030A8 - 0x070031A8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070030A8, 0x004b80d0, 26886, 0x000030a8, 256);

// 0x070031A8 - 0x070032A8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070031A8, 0x004b80d0, 26886, 0x000031a8, 256);

// 0x070032A8 - 0x070033A8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070032A8, 0x004b80d0, 26886, 0x000032a8, 256);

// 0x070033A8 - 0x070034A8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070033A8, 0x004b80d0, 26886, 0x000033a8, 256);

// 0x070034A8 - 0x07003598
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070034A8, 0x004b80d0, 26886, 0x000034a8, 240);

// 0x07003598 - 0x07003688
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003598, 0x004b80d0, 26886, 0x00003598, 240);

// 0x07003688 - 0x07003768
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003688, 0x004b80d0, 26886, 0x00003688, 224);

// 0x07003768 - 0x07003868
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003768, 0x004b80d0, 26886, 0x00003768, 256);

// 0x07003868 - 0x07003968
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003868, 0x004b80d0, 26886, 0x00003868, 256);

// 0x07003968 - 0x07003A48
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003968, 0x004b80d0, 26886, 0x00003968, 224);

// 0x07003A48 - 0x07003B08
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003A48, 0x004b80d0, 26886, 0x00003a48, 192);

// 0x07003B08 - 0x07003B78
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003B08, 0x004b80d0, 26886, 0x00003b08, 112);

// 0x07003B78 - 0x07003C38
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003B78, 0x004b80d0, 26886, 0x00003b78, 192);

// 0x07003C38 - 0x07003CD8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003C38, 0x004b80d0, 26886, 0x00003c38, 160);

// 0x07003CD8 - 0x07003D78
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003CD8, 0x004b80d0, 26886, 0x00003cd8, 160);

// 0x07003D78 - 0x07003E68
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003D78, 0x004b80d0, 26886, 0x00003d78, 240);

// 0x07003E68 - 0x07003F58
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003E68, 0x004b80d0, 26886, 0x00003e68, 240);

// 0x07003F58 - 0x07004048
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07003F58, 0x004b80d0, 26886, 0x00003f58, 240);

// 0x07004048 - 0x07004148
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004048, 0x004b80d0, 26886, 0x00004048, 256);

// 0x07004148 - 0x07004248
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004148, 0x004b80d0, 26886, 0x00004148, 256);

// 0x07004248 - 0x07004348
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004248, 0x004b80d0, 26886, 0x00004248, 256);

// 0x07004348 - 0x070043E8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004348, 0x004b80d0, 26886, 0x00004348, 160);

// 0x070043E8 - 0x070044E8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070043E8, 0x004b80d0, 26886, 0x000043e8, 256);

// 0x070044E8 - 0x07004548
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070044E8, 0x004b80d0, 26886, 0x000044e8, 96);

// 0x07004548 - 0x07004648
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004548, 0x004b80d0, 26886, 0x00004548, 256);

// 0x07004648 - 0x07004738
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004648, 0x004b80d0, 26886, 0x00004648, 240);

// 0x07004738 - 0x07004838
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004738, 0x004b80d0, 26886, 0x00004738, 256);

// 0x07004838 - 0x070048B8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004838, 0x004b80d0, 26886, 0x00004838, 128);

// 0x070048B8 - 0x070049B8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070048B8, 0x004b80d0, 26886, 0x000048b8, 256);

// 0x070049B8 - 0x07004AA8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070049B8, 0x004b80d0, 26886, 0x000049b8, 240);

// 0x07004AA8 - 0x07004BA8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004AA8, 0x004b80d0, 26886, 0x00004aa8, 256);

// 0x07004BA8 - 0x07004C98
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004BA8, 0x004b80d0, 26886, 0x00004ba8, 240);

// 0x07004C98 - 0x07004D98
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004C98, 0x004b80d0, 26886, 0x00004c98, 256);

// 0x07004D98 - 0x07004E98
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004D98, 0x004b80d0, 26886, 0x00004d98, 256);

// 0x07004E98 - 0x07004F78
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004E98, 0x004b80d0, 26886, 0x00004e98, 224);

// 0x07004F78 - 0x07005058
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07004F78, 0x004b80d0, 26886, 0x00004f78, 224);

// 0x07005058 - 0x07005118
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005058, 0x004b80d0, 26886, 0x00005058, 192);

// 0x07005118 - 0x070051D8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005118, 0x004b80d0, 26886, 0x00005118, 192);

// 0x070051D8 - 0x070052D8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070051D8, 0x004b80d0, 26886, 0x000051d8, 256);

// 0x070052D8 - 0x070053C8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070052D8, 0x004b80d0, 26886, 0x000052d8, 240);

// 0x070053C8 - 0x070054B8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070053C8, 0x004b80d0, 26886, 0x000053c8, 240);

// 0x070054B8 - 0x070055B8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070054B8, 0x004b80d0, 26886, 0x000054b8, 256);

// 0x070055B8 - 0x07005668
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070055B8, 0x004b80d0, 26886, 0x000055b8, 176);

// 0x07005668 - 0x07005758
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005668, 0x004b80d0, 26886, 0x00005668, 240);

// 0x07005758 - 0x07005848
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005758, 0x004b80d0, 26886, 0x00005758, 240);

// 0x07005848 - 0x070058C8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005848, 0x004b80d0, 26886, 0x00005848, 128);

// 0x070058C8 - 0x070059A8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070058C8, 0x004b80d0, 26886, 0x000058c8, 224);

// 0x070059A8 - 0x07005A98
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070059A8, 0x004b80d0, 26886, 0x000059a8, 240);

// 0x07005A98 - 0x07005B88
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005A98, 0x004b80d0, 26886, 0x00005a98, 240);

// 0x07005B88 - 0x07005C48
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005B88, 0x004b80d0, 26886, 0x00005b88, 192);

// 0x07005C48 - 0x07005D08
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005C48, 0x004b80d0, 26886, 0x00005c48, 192);

// 0x07005D08 - 0x07005DA8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005D08, 0x004b80d0, 26886, 0x00005d08, 160);

// 0x07005DA8 - 0x07005DE8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005DA8, 0x004b80d0, 26886, 0x00005da8, 64);

// 0x07005DE8 - 0x07005ED8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005DE8, 0x004b80d0, 26886, 0x00005de8, 240);

// 0x07005ED8 - 0x07005FD8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005ED8, 0x004b80d0, 26886, 0x00005ed8, 256);

// 0x07005FD8 - 0x070060C8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07005FD8, 0x004b80d0, 26886, 0x00005fd8, 240);

// 0x070060C8 - 0x070061B8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070060C8, 0x004b80d0, 26886, 0x000060c8, 240);

// 0x070061B8 - 0x070062A8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070061B8, 0x004b80d0, 26886, 0x000061b8, 240);

// 0x070062A8 - 0x07006358
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070062A8, 0x004b80d0, 26886, 0x000062a8, 176);

// 0x07006358 - 0x07006438
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07006358, 0x004b80d0, 26886, 0x00006358, 224);

// 0x07006438 - 0x07006538
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07006438, 0x004b80d0, 26886, 0x00006438, 256);

// 0x07006538 - 0x07006638
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07006538, 0x004b80d0, 26886, 0x00006538, 256);

// 0x07006638 - 0x070066A8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_07006638, 0x004b80d0, 26886, 0x00006638, 112);

// 0x070066A8 - 0x070066E8
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_070066A8, 0x004b80d0, 26886, 0x000066a8, 64);

// 0x070066E8 - 0x07006C18
static const Gfx cotmc_seg7_dl_070066E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cotmc_seg7_lights_07003000.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003000.a, 2),
    gsSPVertex(cotmc_seg7_vertex_070030A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 11,  4, 10, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070031A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  6,  3,  7, 0x0),
    gsSP2Triangles( 4,  7,  3, 0x0,  8,  4,  5, 0x0),
    gsSP2Triangles( 1,  8,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0,  8, 11,  4, 0x0),
    gsSP2Triangles( 4, 12,  7, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070032A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 9,  3,  8, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070033A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  3,  5,  0, 0x0),
    gsSP2Triangles( 5,  8,  0, 0x0,  9,  0,  8, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0,  0, 10,  3, 0x0),
    gsSP2Triangles( 2, 10,  0, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070034A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  4,  0,  3, 0x0),
    gsSP2Triangles( 5,  6,  0, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 8,  2,  1, 0x0,  2,  9, 10, 0x0),
    gsSP2Triangles( 2,  8, 11, 0x0,  2, 10, 12, 0x0),
    gsSP2Triangles(12,  3,  2, 0x0, 12,  4,  3, 0x0),
    gsSP2Triangles(13, 12, 10, 0x0, 13, 10, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07003598, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07003688, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  4,  3,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  8,  7,  3, 0x0),
    gsSP2Triangles( 3,  6, 10, 0x0,  9,  3, 10, 0x0),
    gsSP2Triangles( 4, 11,  5, 0x0, 12,  4, 13, 0x0),
    gsSP2Triangles(12, 11,  4, 0x0,  7, 13,  4, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07003768, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  1,  4, 0x0,  3,  1,  6, 0x0),
    gsSP2Triangles( 2,  1,  7, 0x0,  5,  7,  1, 0x0),
    gsSP2Triangles( 8,  9,  2, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 10, 12, 0x0,  8,  2,  7, 0x0),
    gsSP1Triangle(14,  5, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07003868, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  1,  3, 0x0),
    gsSP2Triangles( 6,  5,  3, 0x0,  6,  3,  7, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  5,  6,  8, 0x0),
    gsSP2Triangles( 2,  5,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 10, 13, 0x0, 14, 15, 10, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07003968, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003018.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003018.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07003A48, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  3,  7,  1, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(11, 10,  7, 0x0, 11,  7,  3, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003030.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003030.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07003B08, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  6,  4, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003048.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003048.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07003B78, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11,  2,  4, 0x0),
    gsSP2Triangles(11,  4,  6, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0,  9, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006C18 - 0x07006F88
static const Gfx cotmc_seg7_dl_07006C18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cotmc_seg7_texture_07002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cotmc_seg7_lights_07003060.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003060.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07003C38, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  4,  9, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0,  4,  3,  9, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003018.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003018.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07003CD8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  8,  9,  4, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003030.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003030.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07003D78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0, 10,  6, 11, 0x0),
    gsSP2Triangles(10,  3,  6, 0x0,  1,  8,  2, 0x0),
    gsSP2Triangles( 0, 12, 13, 0x0, 13, 14,  0, 0x0),
    gsSP1Triangle( 0,  2, 12, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07003E68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  8,  6, 0x0),
    gsSP2Triangles( 3,  9,  8, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles(10, 11,  3, 0x0, 12,  1,  0, 0x0),
    gsSP2Triangles( 0,  2, 13, 0x0, 12, 14,  1, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07003F58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  4,  2,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  6,  8, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles(10,  8, 13, 0x0, 11,  9, 14, 0x0),
    gsSP1Triangle(11,  7,  9, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004048, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 6, 11,  7, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004148, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSP1Triangle( 8, 15, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004248, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  8,  7,  4, 0x0),
    gsSP2Triangles( 9,  4, 10, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles(11,  7,  8, 0x0,  7, 13,  5, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0, 12, 11, 14, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle(13, 15,  5, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004348, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  0,  3,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  4,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006F88 - 0x07007248
static const Gfx cotmc_seg7_dl_07006F88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cotmc_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cotmc_seg7_lights_07003018.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003018.a, 2),
    gsSPVertex(cotmc_seg7_vertex_070043E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 7, 11,  9, 0x0,  7,  6, 11, 0x0),
    gsSP2Triangles( 3, 12,  4, 0x0,  9,  1,  0, 0x0),
    gsSP2Triangles( 9, 11,  1, 0x0, 13, 12,  3, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0, 14,  2, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070044E8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003030.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003030.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07004548, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  3,  5, 0x0,  2,  6,  3, 0x0),
    gsSP2Triangles( 5,  4,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 9,  2,  5, 0x0, 10,  0,  2, 0x0),
    gsSP2Triangles( 9, 11,  2, 0x0,  2, 12, 13, 0x0),
    gsSP2Triangles(11, 14,  2, 0x0, 15, 10,  2, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004648, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 2,  6,  0, 0x0,  6,  7,  0, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles( 8, 10, 12, 0x0, 13,  2, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004738, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  4,  8,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  1,  9, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0, 11, 10, 14, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004838, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003048.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003048.a, 2),
    gsSPVertex(cotmc_seg7_vertex_070048B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  6,  2,  1, 0x0),
    gsSP2Triangles( 8,  9,  4, 0x0,  5,  8,  4, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 10, 13, 12, 0x0),
    gsSP2Triangles(13, 14, 12, 0x0, 13, 15, 14, 0x0),
    gsSP2Triangles(15,  7, 14, 0x0, 15,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007248 - 0x07007498
static const Gfx cotmc_seg7_dl_07007248[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cotmc_seg7_lights_07003030.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003030.a, 2),
    gsSPVertex(cotmc_seg7_vertex_070049B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  6,  8, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004AA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  6,  8, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004BA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 10, 13, 12, 0x0),
    gsSP1Triangle( 9, 11, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004C98, 16, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSP1Triangle( 0,  3,  1, 0x0),
    gsSP1Triangle( 1,  4,  2, 0x0),
    gsSP1Triangle( 4,  5,  2, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSP1Triangle( 9, 10, 11, 0x0),
    gsSP1Triangle( 6, 12,  7, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004D98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004E98, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07004F78, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07005058, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007498 - 0x070074F0
static const Gfx cotmc_seg7_dl_07007498[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(cotmc_seg7_vertex_07005118, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x070074F0 - 0x07007688
static const Gfx cotmc_seg7_dl_070074F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(cotmc_seg7_vertex_070051D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  7,  5,  9, 0x0),
    gsSP2Triangles( 6, 10,  8, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0, 13, 14,  7, 0x0),
    gsSP2Triangles(13,  7,  9, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070052D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  4,  3, 0x0,  8,  9,  4, 0x0),
    gsSP2Triangles( 7, 10,  1, 0x0,  7, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070053C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070054B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070055B8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007688 - 0x07007920
static const Gfx cotmc_seg7_dl_07007688[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cotmc_seg7_texture_07002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 16 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cotmc_seg7_lights_07003000.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003000.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07005668, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07005758, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07005848, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003060.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003060.a, 2),
    gsSPVertex(cotmc_seg7_vertex_070058C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070059A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07005A98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07005B88, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  5,  9,  7, 0x0),
    gsSP2Triangles(10, 11,  2, 0x0,  3, 10,  2, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003018.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003018.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07005C48, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  9, 11, 10, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003078.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003078.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07005D08, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007920 - 0x07007B90
static const Gfx cotmc_seg7_dl_07007920[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cotmc_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cotmc_seg7_lights_07003090.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003090.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07005DA8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003018.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003018.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07005DE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 6,  5,  2, 0x0,  5,  7,  4, 0x0),
    gsSP2Triangles( 8,  5,  9, 0x0, 10, 11,  5, 0x0),
    gsSP2Triangles( 5, 11,  7, 0x0,  8, 10,  5, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 10, 12, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07005ED8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 7,  4,  1, 0x0,  0, 12,  3, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 14, 15, 10, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07005FD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles(11,  8,  7, 0x0,  9, 12, 10, 0x0),
    gsSP2Triangles( 7, 13, 11, 0x0, 14, 11, 13, 0x0),
    gsSP2Triangles(14, 12, 11, 0x0, 12, 14, 10, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003030.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003030.a, 2),
    gsSPVertex(cotmc_seg7_vertex_070060C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  4,  3,  7, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10,  0, 11, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 13, 12, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070061B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(cotmc_seg7_vertex_070062A8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007B90 - 0x07007D48
static const Gfx cotmc_seg7_dl_07007B90[] = {
    gsSPLight(&cotmc_seg7_lights_07003090.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003090.a, 2),
    gsSPVertex(cotmc_seg7_vertex_07006358, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0,  5, 11, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 10, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07006438, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  2,  3, 0x0),
    gsSP2Triangles( 6,  5,  3, 0x0,  5,  7,  2, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  8,  0,  9, 0x0),
    gsSP2Triangles( 0,  7,  9, 0x0,  5, 10,  7, 0x0),
    gsSP2Triangles(10,  9,  7, 0x0, 11,  8,  9, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 10, 11,  9, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07006538, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  1,  0, 0x0),
    gsSP2Triangles( 7,  8,  1, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 15, 12, 11, 0x0),
    gsSP1Triangle(15, 14, 12, 0x0),
    gsSPVertex(cotmc_seg7_vertex_07006638, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  4,  3, 0x0),
    gsSP1Triangle( 5,  6,  4, 0x0),
    gsSPLight(&cotmc_seg7_lights_07003030.l, 1),
    gsSPLight(&cotmc_seg7_lights_07003030.a, 2),
    gsSPVertex(cotmc_seg7_vertex_070066A8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007D48 - 0x07007E88
const Gfx cotmc_seg7_dl_07007D48[] = {
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
    gsSPDisplayList(cotmc_seg7_dl_070066E8),
    gsSPDisplayList(cotmc_seg7_dl_07006C18),
    gsSPDisplayList(cotmc_seg7_dl_07006F88),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cotmc_seg7_dl_07007248),
    gsSPDisplayList(cotmc_seg7_dl_07007498),
    gsSPDisplayList(cotmc_seg7_dl_070074F0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cotmc_seg7_dl_07007688),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cotmc_seg7_dl_07007920),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(cotmc_seg7_dl_07007B90),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
