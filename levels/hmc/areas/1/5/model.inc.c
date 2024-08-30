#include "pc/rom_assets.h"
// 0x07009460 - 0x07009478
static const Lights1 hmc_seg7_lights_07009460 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07009478 - 0x07009490
static const Lights1 hmc_seg7_lights_07009478 = gdSPDefLights1(
    0x79, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07009490 - 0x070094A8
static const Lights1 hmc_seg7_lights_07009490 = gdSPDefLights1(
    0x50, 0x50, 0x50,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x070094A8 - 0x07009588
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070094A8, 0x003d0dc0, 89137, 0x000094a8, 224);

// 0x07009588 - 0x07009678
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009588, 0x003d0dc0, 89137, 0x00009588, 240);

// 0x07009678 - 0x07009768
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009678, 0x003d0dc0, 89137, 0x00009678, 240);

// 0x07009768 - 0x07009868
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009768, 0x003d0dc0, 89137, 0x00009768, 256);

// 0x07009868 - 0x07009948
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009868, 0x003d0dc0, 89137, 0x00009868, 224);

// 0x07009948 - 0x07009A38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009948, 0x003d0dc0, 89137, 0x00009948, 240);

// 0x07009A38 - 0x07009B28
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009A38, 0x003d0dc0, 89137, 0x00009a38, 240);

// 0x07009B28 - 0x07009C08
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009B28, 0x003d0dc0, 89137, 0x00009b28, 224);

// 0x07009C08 - 0x07009D08
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009C08, 0x003d0dc0, 89137, 0x00009c08, 256);

// 0x07009D08 - 0x07009DE8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009D08, 0x003d0dc0, 89137, 0x00009d08, 224);

// 0x07009DE8 - 0x07009ED8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009DE8, 0x003d0dc0, 89137, 0x00009de8, 240);

// 0x07009ED8 - 0x07009FC8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009ED8, 0x003d0dc0, 89137, 0x00009ed8, 240);

// 0x07009FC8 - 0x0700A0B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07009FC8, 0x003d0dc0, 89137, 0x00009fc8, 240);

// 0x0700A0B8 - 0x0700A148
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A0B8, 0x003d0dc0, 89137, 0x0000a0b8, 144);

// 0x0700A148 - 0x0700A1B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A148, 0x003d0dc0, 89137, 0x0000a148, 112);

// 0x0700A1B8 - 0x0700A2A8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A1B8, 0x003d0dc0, 89137, 0x0000a1b8, 240);

// 0x0700A2A8 - 0x0700A358
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A2A8, 0x003d0dc0, 89137, 0x0000a2a8, 176);

// 0x0700A358 - 0x0700A448
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A358, 0x003d0dc0, 89137, 0x0000a358, 240);

// 0x0700A448 - 0x0700A548
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A448, 0x003d0dc0, 89137, 0x0000a448, 256);

// 0x0700A548 - 0x0700A628
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A548, 0x003d0dc0, 89137, 0x0000a548, 224);

// 0x0700A628 - 0x0700A718
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A628, 0x003d0dc0, 89137, 0x0000a628, 240);

// 0x0700A718 - 0x0700A818
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A718, 0x003d0dc0, 89137, 0x0000a718, 256);

// 0x0700A818 - 0x0700A918
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A818, 0x003d0dc0, 89137, 0x0000a818, 256);

// 0x0700A918 - 0x0700A9F8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A918, 0x003d0dc0, 89137, 0x0000a918, 224);

// 0x0700A9F8 - 0x0700AAE8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700A9F8, 0x003d0dc0, 89137, 0x0000a9f8, 240);

// 0x0700AAE8 - 0x0700ABE8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700AAE8, 0x003d0dc0, 89137, 0x0000aae8, 256);

// 0x0700ABE8 - 0x0700ACC8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700ABE8, 0x003d0dc0, 89137, 0x0000abe8, 224);

// 0x0700ACC8 - 0x0700ADA8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700ACC8, 0x003d0dc0, 89137, 0x0000acc8, 224);

// 0x0700ADA8 - 0x0700ADD8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700ADA8, 0x003d0dc0, 89137, 0x0000ada8, 48);

// 0x0700ADD8 - 0x0700AED8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700ADD8, 0x003d0dc0, 89137, 0x0000add8, 256);

// 0x0700AED8 - 0x0700AF58
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700AED8, 0x003d0dc0, 89137, 0x0000aed8, 128);

// 0x0700AF58 - 0x0700B058
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700AF58, 0x003d0dc0, 89137, 0x0000af58, 256);

// 0x0700B058 - 0x0700B158
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B058, 0x003d0dc0, 89137, 0x0000b058, 256);

// 0x0700B158 - 0x0700B248
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B158, 0x003d0dc0, 89137, 0x0000b158, 240);

// 0x0700B248 - 0x0700B338
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B248, 0x003d0dc0, 89137, 0x0000b248, 240);

// 0x0700B338 - 0x0700B438
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B338, 0x003d0dc0, 89137, 0x0000b338, 256);

// 0x0700B438 - 0x0700B528
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B438, 0x003d0dc0, 89137, 0x0000b438, 240);

// 0x0700B528 - 0x0700B628
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B528, 0x003d0dc0, 89137, 0x0000b528, 256);

// 0x0700B628 - 0x0700B728
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B628, 0x003d0dc0, 89137, 0x0000b628, 256);

// 0x0700B728 - 0x0700B808
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B728, 0x003d0dc0, 89137, 0x0000b728, 224);

// 0x0700B808 - 0x0700B908
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B808, 0x003d0dc0, 89137, 0x0000b808, 256);

// 0x0700B908 - 0x0700BA08
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700B908, 0x003d0dc0, 89137, 0x0000b908, 256);

// 0x0700BA08 - 0x0700BA38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BA08, 0x003d0dc0, 89137, 0x0000ba08, 48);

// 0x0700BA38 - 0x0700BB38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BA38, 0x003d0dc0, 89137, 0x0000ba38, 256);

// 0x0700BB38 - 0x0700BC28
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BB38, 0x003d0dc0, 89137, 0x0000bb38, 240);

// 0x0700BC28 - 0x0700BD18
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BC28, 0x003d0dc0, 89137, 0x0000bc28, 240);

// 0x0700BD18 - 0x0700BDF8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BD18, 0x003d0dc0, 89137, 0x0000bd18, 224);

// 0x0700BDF8 - 0x0700BE78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BDF8, 0x003d0dc0, 89137, 0x0000bdf8, 128);

// 0x0700BE78 - 0x0700BEB8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BE78, 0x003d0dc0, 89137, 0x0000be78, 64);

// 0x0700BEB8 - 0x0700BEF8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BEB8, 0x003d0dc0, 89137, 0x0000beb8, 64);

// 0x0700BEF8 - 0x0700BFE8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BEF8, 0x003d0dc0, 89137, 0x0000bef8, 240);

// 0x0700BFE8 - 0x0700C0E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700BFE8, 0x003d0dc0, 89137, 0x0000bfe8, 256);

// 0x0700C0E8 - 0x0700C1D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C0E8, 0x003d0dc0, 89137, 0x0000c0e8, 240);

// 0x0700C1D8 - 0x0700C2B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C1D8, 0x003d0dc0, 89137, 0x0000c1d8, 224);

// 0x0700C2B8 - 0x0700C398
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C2B8, 0x003d0dc0, 89137, 0x0000c2b8, 224);

// 0x0700C398 - 0x0700C488
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C398, 0x003d0dc0, 89137, 0x0000c398, 240);

// 0x0700C488 - 0x0700C588
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C488, 0x003d0dc0, 89137, 0x0000c488, 256);

// 0x0700C588 - 0x0700C668
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C588, 0x003d0dc0, 89137, 0x0000c588, 224);

// 0x0700C668 - 0x0700C758
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C668, 0x003d0dc0, 89137, 0x0000c668, 240);

// 0x0700C758 - 0x0700C848
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C758, 0x003d0dc0, 89137, 0x0000c758, 240);

// 0x0700C848 - 0x0700C948
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C848, 0x003d0dc0, 89137, 0x0000c848, 256);

// 0x0700C948 - 0x0700CA38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700C948, 0x003d0dc0, 89137, 0x0000c948, 240);

// 0x0700CA38 - 0x0700CB18
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700CA38, 0x003d0dc0, 89137, 0x0000ca38, 224);

// 0x0700CB18 - 0x0700CC08
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700CB18, 0x003d0dc0, 89137, 0x0000cb18, 240);

// 0x0700CC08 - 0x0700CC78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700CC08, 0x003d0dc0, 89137, 0x0000cc08, 112);

// 0x0700CC78 - 0x0700CD78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700CC78, 0x003d0dc0, 89137, 0x0000cc78, 256);

// 0x0700CD78 - 0x0700CE78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700CD78, 0x003d0dc0, 89137, 0x0000cd78, 256);

// 0x0700CE78 - 0x0700CF38
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700CE78, 0x003d0dc0, 89137, 0x0000ce78, 192);

// 0x0700CF38 - 0x0700CF78
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0700CF38, 0x003d0dc0, 89137, 0x0000cf38, 64);

// 0x0700CF78 - 0x0700D1C8
static const Gfx hmc_seg7_dl_0700CF78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07009460.l, 1),
    gsSPLight(&hmc_seg7_lights_07009460.a, 2),
    gsSPVertex(hmc_seg7_vertex_070094A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009588, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009678, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009768, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  2,  1, 0x0),
    gsSP2Triangles(11, 12,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009868, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009948, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  6,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 10, 11, 0x0, 13, 12, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009A38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  8, 13, 14, 0x0),
    gsSP1Triangle( 8, 14,  7, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009B28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D1C8 - 0x0700D3D8
static const Gfx hmc_seg7_dl_0700D1C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07009C08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009D08, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009DE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009ED8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  6, 11,  7, 0x0),
    gsSP2Triangles( 7, 11, 12, 0x0,  7, 12,  9, 0x0),
    gsSP2Triangles(10,  9, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 13, 11,  6, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_07009FC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  5, 11,  6, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 14, 12, 10, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A0B8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  6,  7,  8, 0x0),
    gsSP1Triangle( 0,  7,  1, 0x0),
    gsSPLight(&hmc_seg7_lights_07009478.l, 1),
    gsSPLight(&hmc_seg7_lights_07009478.a, 2),
    gsSPVertex(hmc_seg7_vertex_0700A148, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D3D8 - 0x0700D8D8
static const Gfx hmc_seg7_dl_0700D3D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07009490.l, 1),
    gsSPLight(&hmc_seg7_lights_07009490.a, 2),
    gsSPVertex(hmc_seg7_vertex_0700A1B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A2A8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPLight(&hmc_seg7_lights_07009460.l, 1),
    gsSPLight(&hmc_seg7_lights_07009460.a, 2),
    gsSPVertex(hmc_seg7_vertex_0700A358, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  3,  6, 0x0,  8,  4,  3, 0x0),
    gsSP2Triangles( 9,  4,  8, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles(10,  5,  9, 0x0, 10,  7,  5, 0x0),
    gsSP2Triangles( 6,  7, 10, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0, 12, 13, 0x0, 14,  0,  2, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A448, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0,  3, 10,  4, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A548, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  4,  6,  1, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  1,  6,  8, 0x0),
    gsSP2Triangles( 1,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 10, 13, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A628, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12,  5,  0, 0x0),
    gsSP2Triangles(12, 13,  5, 0x0,  6, 14,  7, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A718, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  6,  3, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles( 8, 14, 15, 0x0,  8, 15,  9, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A818, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 4,  6,  0, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 1, 12, 14, 0x0,  1,  3, 12, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  3, 15, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A918, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 8,  2,  9, 0x0, 10,  8,  9, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700A9F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700AAE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles( 9, 10,  6, 0x0,  8,  7, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0, 12, 10,  9, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0,  2, 13,  4, 0x0),
    gsSP2Triangles( 0, 14,  1, 0x0,  2,  1, 13, 0x0),
    gsSP2Triangles( 4, 13, 15, 0x0,  4, 15,  3, 0x0),
    gsSP2Triangles( 3, 14,  0, 0x0,  3, 15, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700ABE8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  2,  1,  9, 0x0),
    gsSP2Triangles( 2,  9, 10, 0x0, 10,  8,  3, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 11,  7, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  5,  7, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700ACC8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  9, 10,  1, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 13,  2, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700ADA8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D8D8 - 0x0700D9A8
static const Gfx hmc_seg7_dl_0700D8D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0700ADD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  8,  2,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 2, 10,  9, 0x0,  2,  1, 10, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700AED8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  1,  0, 0x0),
    gsSP1Triangle( 7,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D9A8 - 0x0700DD30
static const Gfx hmc_seg7_dl_0700D9A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0700AF58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  5,  6,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 7,  9, 11, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles(11,  6,  5, 0x0, 11,  5, 14, 0x0),
    gsSP2Triangles(15, 13, 12, 0x0, 15, 12,  3, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B058, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  4,  8,  0, 0x0),
    gsSP2Triangles( 0,  9,  1, 0x0,  0, 10,  9, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(15, 13, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B158, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B248, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles(11,  7, 10, 0x0,  0, 13,  1, 0x0),
    gsSP1Triangle( 0, 14, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B338, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B438, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B528, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  4,  8, 0x0,  9,  7,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles(14,  0, 13, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B628, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  6,  8, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B728, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle(12, 13, 10, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B808, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700B908, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700BA08, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DD30 - 0x0700DED8
static const Gfx hmc_seg7_dl_0700DD30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0700BA38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700BB38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 11, 10,  5, 0x0),
    gsSP1Triangle(11,  5,  4, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700BC28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700BD18, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 1,  8,  9, 0x0,  1,  9,  2, 0x0),
    gsSP2Triangles(10,  1,  0, 0x0, 10, 11,  1, 0x0),
    gsSP2Triangles(10,  0, 12, 0x0,  0,  4, 12, 0x0),
    gsSP2Triangles(11, 13,  1, 0x0, 13,  8,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700BDF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  0,  5,  1, 0x0),
    gsSP1Triangle( 1,  7,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DED8 - 0x0700DF10
static const Gfx hmc_seg7_dl_0700DED8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0700BE78, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DF10 - 0x0700DF48
static const Gfx hmc_seg7_dl_0700DF10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0700BEB8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DF48 - 0x0700E330
static const Gfx hmc_seg7_dl_0700DF48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0700BEF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700BFE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C0E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C1D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C2B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  1, 12, 0x0),
    gsSP1Triangle(11, 13,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C398, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C488, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  2,  7,  8, 0x0),
    gsSP2Triangles( 2,  9,  7, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10,  1, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C588, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C668, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C758, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C848, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700C948, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 10,  7, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700CA38, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700CB18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  2, 13, 14, 0x0),
    gsSP1Triangle( 2,  1, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700CC08, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  0, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E330 - 0x0700E428
static const Gfx hmc_seg7_dl_0700E330[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0700CC78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0,  2,  1, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700CD78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0700CE78, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E428 - 0x0700E448
static const Gfx hmc_seg7_dl_0700E428[] = {
    gsSPVertex(hmc_seg7_vertex_0700CF38, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E448 - 0x0700E5B0
const Gfx hmc_seg7_dl_0700E448[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(960, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0700CF78),
    gsSPDisplayList(hmc_seg7_dl_0700D1C8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0700D3D8),
    gsSPDisplayList(hmc_seg7_dl_0700D8D8),
    gsSPDisplayList(hmc_seg7_dl_0700D9A8),
    gsSPDisplayList(hmc_seg7_dl_0700DD30),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0700DED8),
    gsSPDisplayList(hmc_seg7_dl_0700DF10),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0700DF48),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0700E330),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(hmc_seg7_dl_0700E428),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
