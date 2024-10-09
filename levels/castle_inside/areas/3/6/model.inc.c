#include "pc/rom_assets.h"
// 0x07061C90 - 0x07061CA8
static const Lights1 inside_castle_seg7_lights_07061C90 = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07061CA8 - 0x07061CC0
static const Lights1 inside_castle_seg7_lights_07061CA8 = gdSPDefLights1(
    0x52, 0x52, 0x52,
    0xdd, 0xdd, 0xdd, 0x28, 0x28, 0x28
);

// 0x07061CC0 - 0x07061CD8
static const Lights1 inside_castle_seg7_lights_07061CC0 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07061CD8 - 0x07061DC8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07061CD8, 0x00396340, 232834, 0x00061cd8, 240);

// 0x07061DC8 - 0x07061EC8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07061DC8, 0x00396340, 232834, 0x00061dc8, 256);

// 0x07061EC8 - 0x07061F68
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07061EC8, 0x00396340, 232834, 0x00061ec8, 160);

// 0x07061F68 - 0x07062058
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07061F68, 0x00396340, 232834, 0x00061f68, 240);

// 0x07062058 - 0x07062148
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062058, 0x00396340, 232834, 0x00062058, 240);

// 0x07062148 - 0x07062238
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062148, 0x00396340, 232834, 0x00062148, 240);

// 0x07062238 - 0x07062318
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062238, 0x00396340, 232834, 0x00062238, 224);

// 0x07062318 - 0x070623F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062318, 0x00396340, 232834, 0x00062318, 224);

// 0x070623F8 - 0x070624D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070623F8, 0x00396340, 232834, 0x000623f8, 224);

// 0x070624D8 - 0x070625D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070624D8, 0x00396340, 232834, 0x000624d8, 256);

// 0x070625D8 - 0x070626D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070625D8, 0x00396340, 232834, 0x000625d8, 256);

// 0x070626D8 - 0x070627D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070626D8, 0x00396340, 232834, 0x000626d8, 256);

// 0x070627D8 - 0x070628D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070627D8, 0x00396340, 232834, 0x000627d8, 256);

// 0x070628D8 - 0x070629C8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070628D8, 0x00396340, 232834, 0x000628d8, 240);

// 0x070629C8 - 0x07062AA8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070629C8, 0x00396340, 232834, 0x000629c8, 224);

// 0x07062AA8 - 0x07062B98
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062AA8, 0x00396340, 232834, 0x00062aa8, 240);

// 0x07062B98 - 0x07062C88
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062B98, 0x00396340, 232834, 0x00062b98, 240);

// 0x07062C88 - 0x07062D68
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062C88, 0x00396340, 232834, 0x00062c88, 224);

// 0x07062D68 - 0x07062E58
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062D68, 0x00396340, 232834, 0x00062d68, 240);

// 0x07062E58 - 0x07062ED8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062E58, 0x00396340, 232834, 0x00062e58, 128);

// 0x07062ED8 - 0x07062FC8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062ED8, 0x00396340, 232834, 0x00062ed8, 240);

// 0x07062FC8 - 0x070630B8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07062FC8, 0x00396340, 232834, 0x00062fc8, 240);

// 0x070630B8 - 0x070630F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070630B8, 0x00396340, 232834, 0x000630b8, 64);

// 0x070630F8 - 0x070631E8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070630F8, 0x00396340, 232834, 0x000630f8, 240);

// 0x070631E8 - 0x070632C8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070631E8, 0x00396340, 232834, 0x000631e8, 224);

// 0x070632C8 - 0x070633A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070632C8, 0x00396340, 232834, 0x000632c8, 224);

// 0x070633A8 - 0x070634A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070633A8, 0x00396340, 232834, 0x000633a8, 256);

// 0x070634A8 - 0x07063588
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070634A8, 0x00396340, 232834, 0x000634a8, 224);

// 0x07063588 - 0x07063668
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063588, 0x00396340, 232834, 0x00063588, 224);

// 0x07063668 - 0x07063758
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063668, 0x00396340, 232834, 0x00063668, 240);

// 0x07063758 - 0x07063848
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063758, 0x00396340, 232834, 0x00063758, 240);

// 0x07063848 - 0x07063928
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063848, 0x00396340, 232834, 0x00063848, 224);

// 0x07063928 - 0x07063A28
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063928, 0x00396340, 232834, 0x00063928, 256);

// 0x07063A28 - 0x07063B08
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063A28, 0x00396340, 232834, 0x00063a28, 224);

// 0x07063B08 - 0x07063BF8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063B08, 0x00396340, 232834, 0x00063b08, 240);

// 0x07063BF8 - 0x07063CE8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063BF8, 0x00396340, 232834, 0x00063bf8, 240);

// 0x07063CE8 - 0x07063DD8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063CE8, 0x00396340, 232834, 0x00063ce8, 240);

// 0x07063DD8 - 0x07063E18
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063DD8, 0x00396340, 232834, 0x00063dd8, 64);

// 0x07063E18 - 0x07063F08
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063E18, 0x00396340, 232834, 0x00063e18, 240);

// 0x07063F08 - 0x07063FF8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063F08, 0x00396340, 232834, 0x00063f08, 240);

// 0x07063FF8 - 0x07064078
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07063FF8, 0x00396340, 232834, 0x00063ff8, 128);

// 0x07064078 - 0x07064180
static const Gfx inside_castle_seg7_dl_07064078[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07061C90.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07061C90.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07061CD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles( 2, 12, 13, 0x0,  2, 13, 14, 0x0),
    gsSP1Triangle( 1, 12,  2, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07061DC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 10,  9,  6, 0x0),
    gsSP2Triangles(11, 10,  6, 0x0,  4, 11,  6, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0,  2, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07061EC8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07064180 - 0x07064618
static const Gfx inside_castle_seg7_dl_07064180[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07061F68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 10, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062058, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0,  7, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062148, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0, 13, 11, 0x0,  0,  2, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062238, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062318, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070623F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070624D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 9,  6,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070625D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 4, 10,  5, 0x0,  8,  7, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070626D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  6,  2,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070627D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070628D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070629C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062AA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062B98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062C88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062D68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062E58, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07064618 - 0x07064A50
static const Gfx inside_castle_seg7_dl_07064618[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07061CA8.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07061CA8.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07062ED8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07062FC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070630B8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&inside_castle_seg7_lights_07061C90.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07061C90.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070630F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070631E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070632C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070633A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070634A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063588, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063668, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063758, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063848, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 11, 10, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063928, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 13, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063A28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063B08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063BF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 12, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063CE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(10,  9, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07064A50 - 0x07064A88
static const Gfx inside_castle_seg7_dl_07064A50[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07063DD8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07064A88 - 0x07064B28
static const Gfx inside_castle_seg7_dl_07064A88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07063E18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07063F08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07064B28 - 0x07064B78
static const Gfx inside_castle_seg7_dl_07064B28[] = {
    gsSPLight(&inside_castle_seg7_lights_07061CC0.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07061CC0.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07063FF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  4,  6, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07064B78 - 0x07064C40
const Gfx inside_castle_seg7_dl_07064B78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07064078),
    gsSPDisplayList(inside_castle_seg7_dl_07064180),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07064618),
    gsSPDisplayList(inside_castle_seg7_dl_07064A50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07064A88),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(inside_castle_seg7_dl_07064B28),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
