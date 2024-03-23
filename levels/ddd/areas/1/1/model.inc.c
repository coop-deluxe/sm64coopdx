#include "pc/rom_assets.h"
// 0x07003800 - 0x07003818
static const Lights1 ddd_seg7_lights_07003800 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07003818 - 0x07003830
static const Lights1 ddd_seg7_lights_07003818 = gdSPDefLights1(
    0x1a, 0x1a, 0x3f,
    0x69, 0x69, 0xfe, 0x28, 0x28, 0x28
);

// 0x07003830 - 0x07003848
static const Lights1 ddd_seg7_lights_07003830 = gdSPDefLights1(
    0x26, 0x26, 0x3f,
    0x9b, 0x9b, 0xff, 0x28, 0x28, 0x28
);

// 0x07003848 - 0x07003860
static const Lights1 ddd_seg7_lights_07003848 = gdSPDefLights1(
    0x32, 0x32, 0x3f,
    0xc8, 0xc8, 0xff, 0x28, 0x28, 0x28
);

// 0x07003860 - 0x07003960
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003860, 0x0048d930, 33063, 0x00003860, 256);

// 0x07003960 - 0x07003A60
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003960, 0x0048d930, 33063, 0x00003960, 256);

// 0x07003A60 - 0x07003AF0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003A60, 0x0048d930, 33063, 0x00003a60, 144);

// 0x07003AF0 - 0x07003B30
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003AF0, 0x0048d930, 33063, 0x00003af0, 64);

// 0x07003B30 - 0x07003C30
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003B30, 0x0048d930, 33063, 0x00003b30, 256);

// 0x07003C30 - 0x07003D30
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003C30, 0x0048d930, 33063, 0x00003c30, 256);

// 0x07003D30 - 0x07003E30
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003D30, 0x0048d930, 33063, 0x00003d30, 256);

// 0x07003E30 - 0x07003F30
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003E30, 0x0048d930, 33063, 0x00003e30, 256);

// 0x07003F30 - 0x07004030
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07003F30, 0x0048d930, 33063, 0x00003f30, 256);

// 0x07004030 - 0x07004130
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07004030, 0x0048d930, 33063, 0x00004030, 256);

// 0x07004130 - 0x070041C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07004130, 0x0048d930, 33063, 0x00004130, 144);

// 0x070041C0 - 0x070042C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070041C0, 0x0048d930, 33063, 0x000041c0, 256);

// 0x070042C0 - 0x070043C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070042C0, 0x0048d930, 33063, 0x000042c0, 256);

// 0x070043C0 - 0x070044C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070043C0, 0x0048d930, 33063, 0x000043c0, 256);

// 0x070044C0 - 0x070045C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070044C0, 0x0048d930, 33063, 0x000044c0, 256);

// 0x070045C0 - 0x070046B0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070045C0, 0x0048d930, 33063, 0x000045c0, 240);

// 0x070046B0 - 0x07004700
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070046B0, 0x0048d930, 33063, 0x000046b0, 80);

// 0x07004700 - 0x07004D48
static const Gfx ddd_seg7_dl_07004700[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_07003800.l, 1),
    gsSPLight(&ddd_seg7_lights_07003800.a, 2),
    gsSPVertex(ddd_seg7_vertex_07003860, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0, 11, 12,  1, 0x0),
    gsSP2Triangles(11,  1,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07003960, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07003A60, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP1Triangle( 5,  8,  7, 0x0),
    gsSPLight(&ddd_seg7_lights_07003818.l, 1),
    gsSPLight(&ddd_seg7_lights_07003818.a, 2),
    gsSPVertex(ddd_seg7_vertex_07003AF0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ddd_seg7_lights_07003830.l, 1),
    gsSPLight(&ddd_seg7_lights_07003830.a, 2),
    gsSPVertex(ddd_seg7_vertex_07003B30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 8, 10, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07003C30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07003D30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07003E30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  2,  6,  7, 0x0),
    gsSP2Triangles( 8,  4,  3, 0x0,  8,  9,  4, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 13, 11, 0x0),
    gsSP2Triangles(14, 13, 12, 0x0, 15, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_07003F30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0,  1, 12, 11, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0,  0, 13,  1, 0x0),
    gsSP2Triangles(14, 15,  0, 0x0, 15, 13,  0, 0x0),
    gsSPVertex(ddd_seg7_vertex_07004030, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 9, 10, 14, 0x0,  9, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07004130, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  3, 0x0),
    gsSP2Triangles( 5,  7,  6, 0x0,  6,  7,  8, 0x0),
    gsSPLight(&ddd_seg7_lights_07003848.l, 1),
    gsSPLight(&ddd_seg7_lights_07003848.a, 2),
    gsSPVertex(ddd_seg7_vertex_070041C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  4,  1,  6, 0x0),
    gsSP2Triangles( 6,  1,  3, 0x0,  7,  1,  5, 0x0),
    gsSP2Triangles( 2,  1,  8, 0x0,  8,  1,  7, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12,  9, 13, 0x0),
    gsSP2Triangles( 9, 11, 13, 0x0, 10, 14, 11, 0x0),
    gsSP1Triangle(12, 13, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_070042C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 7,  6, 12, 0x0,  7, 12, 13, 0x0),
    gsSP2Triangles( 8, 14,  5, 0x0, 13, 12, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_070043C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_070044C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_070045C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  3,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 0,  8, 11, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0, 13,  1, 0x0,  0, 12, 13, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(ddd_seg7_vertex_070046B0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004D48 - 0x07004DA8
const Gfx ddd_seg7_dl_07004D48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_07004700),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
