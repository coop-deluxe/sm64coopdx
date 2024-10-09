#include "pc/rom_assets.h"
// 0x07004800 - 0x07004818
static const Lights1 bbh_seg7_lights_07004800 = gdSPDefLights1(
    0x20, 0x20, 0x20,
    0x50, 0x50, 0x50, 0x28, 0x28, 0x28
);

// 0x07004818 - 0x07004830
static const Lights1 bbh_seg7_lights_07004818 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07004830 - 0x07004920
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004830, 0x00371c40, 68724, 0x00004830, 240);

// 0x07004920 - 0x070049D0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004920, 0x00371c40, 68724, 0x00004920, 176);

// 0x070049D0 - 0x07004AC0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070049D0, 0x00371c40, 68724, 0x000049d0, 240);

// 0x07004AC0 - 0x07004BA0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004AC0, 0x00371c40, 68724, 0x00004ac0, 224);

// 0x07004BA0 - 0x07004C80
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004BA0, 0x00371c40, 68724, 0x00004ba0, 224);

// 0x07004C80 - 0x07004D70
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004C80, 0x00371c40, 68724, 0x00004c80, 240);

// 0x07004D70 - 0x07004E50
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004D70, 0x00371c40, 68724, 0x00004d70, 224);

// 0x07004E50 - 0x07004F40
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004E50, 0x00371c40, 68724, 0x00004e50, 240);

// 0x07004F40 - 0x07005030
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07004F40, 0x00371c40, 68724, 0x00004f40, 240);

// 0x07005030 - 0x07005120
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005030, 0x00371c40, 68724, 0x00005030, 240);

// 0x07005120 - 0x07005220
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005120, 0x00371c40, 68724, 0x00005120, 256);

// 0x07005220 - 0x07005310
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005220, 0x00371c40, 68724, 0x00005220, 240);

// 0x07005310 - 0x070053C0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005310, 0x00371c40, 68724, 0x00005310, 176);

// 0x070053C0 - 0x07005440
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070053C0, 0x00371c40, 68724, 0x000053c0, 128);

// 0x07005440 - 0x07005530
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005440, 0x00371c40, 68724, 0x00005440, 240);

// 0x07005530 - 0x07005620
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005530, 0x00371c40, 68724, 0x00005530, 240);

// 0x07005620 - 0x07005710
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005620, 0x00371c40, 68724, 0x00005620, 240);

// 0x07005710 - 0x07005800
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005710, 0x00371c40, 68724, 0x00005710, 240);

// 0x07005800 - 0x07005900
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005800, 0x00371c40, 68724, 0x00005800, 256);

// 0x07005900 - 0x070059E0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005900, 0x00371c40, 68724, 0x00005900, 224);

// 0x070059E0 - 0x07005AC0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070059E0, 0x00371c40, 68724, 0x000059e0, 224);

// 0x07005AC0 - 0x07005BB0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005AC0, 0x00371c40, 68724, 0x00005ac0, 240);

// 0x07005BB0 - 0x07005CA0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005BB0, 0x00371c40, 68724, 0x00005bb0, 240);

// 0x07005CA0 - 0x07005D90
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005CA0, 0x00371c40, 68724, 0x00005ca0, 240);

// 0x07005D90 - 0x07005E80
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005D90, 0x00371c40, 68724, 0x00005d90, 240);

// 0x07005E80 - 0x07005F80
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005E80, 0x00371c40, 68724, 0x00005e80, 256);

// 0x07005F80 - 0x07006080
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07005F80, 0x00371c40, 68724, 0x00005f80, 256);

// 0x07006080 - 0x07006180
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006080, 0x00371c40, 68724, 0x00006080, 256);

// 0x07006180 - 0x07006260
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006180, 0x00371c40, 68724, 0x00006180, 224);

// 0x07006260 - 0x07006350
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006260, 0x00371c40, 68724, 0x00006260, 240);

// 0x07006350 - 0x07006430
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006350, 0x00371c40, 68724, 0x00006350, 224);

// 0x07006430 - 0x07006510
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006430, 0x00371c40, 68724, 0x00006430, 224);

// 0x07006510 - 0x07006610
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006510, 0x00371c40, 68724, 0x00006510, 256);

// 0x07006610 - 0x070066F0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006610, 0x00371c40, 68724, 0x00006610, 224);

// 0x070066F0 - 0x07006760
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070066F0, 0x00371c40, 68724, 0x000066f0, 112);

// 0x07006760 - 0x07006850
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006760, 0x00371c40, 68724, 0x00006760, 240);

// 0x07006850 - 0x070068D0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006850, 0x00371c40, 68724, 0x00006850, 128);

// 0x070068D0 - 0x070069C0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070068D0, 0x00371c40, 68724, 0x000068d0, 240);

// 0x070069C0 - 0x07006AC0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070069C0, 0x00371c40, 68724, 0x000069c0, 256);

// 0x07006AC0 - 0x07006AF0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07006AC0, 0x00371c40, 68724, 0x00006ac0, 48);

// 0x07006AF0 - 0x07006DF8
static const Gfx bbh_seg7_dl_07006AF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07004800.l, 1),
    gsSPLight(&bbh_seg7_lights_07004800.a, 2),
    gsSPVertex(bbh_seg7_vertex_07004830, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07004920, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPLight(&bbh_seg7_lights_07004818.l, 1),
    gsSPLight(&bbh_seg7_lights_07004818.a, 2),
    gsSPVertex(bbh_seg7_vertex_070049D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  6,  5,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07004AC0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07004BA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07004C80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07004D70, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07004E50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07004F40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005030, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005120, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  3, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006DF8 - 0x07006E88
static const Gfx bbh_seg7_dl_07006DF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07005220, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005310, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006E88 - 0x07006EE0
static const Gfx bbh_seg7_dl_07006E88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070053C0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 5,  0,  6, 0x0,  5,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006EE0 - 0x070072F8
static const Gfx bbh_seg7_dl_07006EE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07005440, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005530, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005620, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005710, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005800, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  4,  3,  9, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0,  6, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005900, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 2,  7,  3, 0x0,  2,  4,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070059E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13,  5, 0x0,  3,  5, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005AC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  8, 11, 10, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 7,  9, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005BB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 11, 14, 0x0),
    gsSP1Triangle(10, 11, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005CA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  5,  9, 0x0,  8,  6,  5, 0x0),
    gsSP2Triangles(10,  8,  9, 0x0, 10, 11,  8, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005D90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005E80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07005F80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006080, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006180, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x070072F8 - 0x07007468
static const Gfx bbh_seg7_dl_070072F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07006260, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 6, 14,  7, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006350, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006430, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006510, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006610, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070066F0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007468 - 0x070074F0
static const Gfx bbh_seg7_dl_07007468[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07006760, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006850, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070074F0 - 0x070075A8
static const Gfx bbh_seg7_dl_070074F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070068D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_070069C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0,  6, 11, 10, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07006AC0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070075A8 - 0x070076C0
const Gfx bbh_seg7_dl_070075A8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07006AF0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07006DF8),
    gsSPDisplayList(bbh_seg7_dl_07006E88),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07006EE0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070072F8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07007468),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070074F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
