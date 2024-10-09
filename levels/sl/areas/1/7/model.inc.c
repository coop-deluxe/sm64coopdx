#include "pc/rom_assets.h"
// 0x07008DE8 - 0x07008E00
static const Lights1 sl_seg7_lights_07008DE8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07008E00 - 0x07008F00
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07008E00, 0x00405fb0, 34952, 0x00008e00, 256);

// 0x07008F00 - 0x07008F40
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07008F00, 0x00405fb0, 34952, 0x00008f00, 64);

// 0x07008F40 - 0x07009020
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07008F40, 0x00405fb0, 34952, 0x00008f40, 224);

// 0x07009020 - 0x07009120
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009020, 0x00405fb0, 34952, 0x00009020, 256);

// 0x07009120 - 0x07009220
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009120, 0x00405fb0, 34952, 0x00009120, 256);

// 0x07009220 - 0x07009320
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009220, 0x00405fb0, 34952, 0x00009220, 256);

// 0x07009320 - 0x07009410
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009320, 0x00405fb0, 34952, 0x00009320, 240);

// 0x07009410 - 0x07009510
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009410, 0x00405fb0, 34952, 0x00009410, 256);

// 0x07009510 - 0x07009600
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009510, 0x00405fb0, 34952, 0x00009510, 240);

// 0x07009600 - 0x070096F0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009600, 0x00405fb0, 34952, 0x00009600, 240);

// 0x070096F0 - 0x070097D0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070096F0, 0x00405fb0, 34952, 0x000096f0, 224);

// 0x070097D0 - 0x070098D0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070097D0, 0x00405fb0, 34952, 0x000097d0, 256);

// 0x070098D0 - 0x070099D0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070098D0, 0x00405fb0, 34952, 0x000098d0, 256);

// 0x070099D0 - 0x07009AB0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_070099D0, 0x00405fb0, 34952, 0x000099d0, 224);

// 0x07009AB0 - 0x07009B60
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009AB0, 0x00405fb0, 34952, 0x00009ab0, 176);

// 0x07009B60 - 0x07009BA0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009B60, 0x00405fb0, 34952, 0x00009b60, 64);

// 0x07009BA0 - 0x07009CA0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009BA0, 0x00405fb0, 34952, 0x00009ba0, 256);

// 0x07009CA0 - 0x07009DA0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009CA0, 0x00405fb0, 34952, 0x00009ca0, 256);

// 0x07009DA0 - 0x07009E80
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009DA0, 0x00405fb0, 34952, 0x00009da0, 224);

// 0x07009E80 - 0x07009F30
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_07009E80, 0x00405fb0, 34952, 0x00009e80, 176);

// 0x07009F30 - 0x07009FE0
static const Gfx sl_seg7_dl_07009F30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sl_seg7_lights_07008DE8.l, 1),
    gsSPLight(&sl_seg7_lights_07008DE8.a, 2),
    gsSPVertex(sl_seg7_vertex_07008E00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  6,  1,  5, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  8,  9,  7, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 12, 15, 0x0, 12, 14, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07008F00, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009FE0 - 0x0700A058
static const Gfx sl_seg7_dl_07009FE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07008F40, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 9,  0, 11, 0x0,  9,  1,  0, 0x0),
    gsSP2Triangles(11,  0, 12, 0x0,  1, 13,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A058 - 0x0700A418
static const Gfx sl_seg7_dl_0700A058[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07009020, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  3,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07009120, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07009220, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13,  6, 14, 0x0),
    gsSP2Triangles(15,  6, 13, 0x0,  6,  3, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07009320, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07009410, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0,  9,  7, 11, 0x0),
    gsSP2Triangles(11,  7, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_07009510, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 11, 10, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07009600, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 7,  5,  0, 0x0,  7,  0,  8, 0x0),
    gsSP2Triangles( 0,  4,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 13, 10, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_070096F0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  2, 11, 0x0, 10,  0,  2, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0,  2,  1, 13, 0x0),
    gsSP1Triangle(11,  2, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_070097D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 4,  7,  3, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_070098D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  1, 0x0),
    gsSP2Triangles( 9,  1,  8, 0x0, 10, 11,  1, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_070099D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_07009AB0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6, 10, 0x0),
    gsSP1Triangle( 6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A418 - 0x0700A450
static const Gfx sl_seg7_dl_0700A418[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sl_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07009B60, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A450 - 0x0700A5A0
static const Gfx sl_seg7_dl_0700A450[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sl_seg7_texture_07002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sl_seg7_vertex_07009BA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles( 2, 11, 10, 0x0,  9, 14,  5, 0x0),
    gsSP1Triangle( 9, 15, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_07009CA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  2,  3, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 7,  4,  6, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 15, 0x0),
    gsSP1Triangle(15, 12, 11, 0x0),
    gsSPVertex(sl_seg7_vertex_07009DA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13,  8, 0x0),
    gsSPVertex(sl_seg7_vertex_07009E80, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 9,  3,  2, 0x0,  9, 10,  3, 0x0),
    gsSP1Triangle( 9,  5, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A5A0 - 0x0700A620
const Gfx sl_seg7_dl_0700A5A0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_07009F30),
    gsSPDisplayList(sl_seg7_dl_07009FE0),
    gsSPDisplayList(sl_seg7_dl_0700A058),
    gsSPDisplayList(sl_seg7_dl_0700A418),
    gsSPDisplayList(sl_seg7_dl_0700A450),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
