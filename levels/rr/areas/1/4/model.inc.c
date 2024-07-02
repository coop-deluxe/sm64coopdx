#include "pc/rom_assets.h"
// 0x07002EF8 - 0x07002FD8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07002EF8, 0x00437870, 75979, 0x00002ef8, 224);

// 0x07002FD8 - 0x070030D8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07002FD8, 0x00437870, 75979, 0x00002fd8, 256);

// 0x070030D8 - 0x070031D8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070030D8, 0x00437870, 75979, 0x000030d8, 256);

// 0x070031D8 - 0x070032B8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070031D8, 0x00437870, 75979, 0x000031d8, 224);

// 0x070032B8 - 0x070033A8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070032B8, 0x00437870, 75979, 0x000032b8, 240);

// 0x070033A8 - 0x07003488
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070033A8, 0x00437870, 75979, 0x000033a8, 224);

// 0x07003488 - 0x07003568
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003488, 0x00437870, 75979, 0x00003488, 224);

// 0x07003568 - 0x07003668
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003568, 0x00437870, 75979, 0x00003568, 256);

// 0x07003668 - 0x07003758
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003668, 0x00437870, 75979, 0x00003668, 240);

// 0x07003758 - 0x07003858
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003758, 0x00437870, 75979, 0x00003758, 256);

// 0x07003858 - 0x07003948
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003858, 0x00437870, 75979, 0x00003858, 240);

// 0x07003948 - 0x07003A28
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003948, 0x00437870, 75979, 0x00003948, 224);

// 0x07003A28 - 0x07003B08
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003A28, 0x00437870, 75979, 0x00003a28, 224);

// 0x07003B08 - 0x07003BF8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003B08, 0x00437870, 75979, 0x00003b08, 240);

// 0x07003BF8 - 0x07003CF8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003BF8, 0x00437870, 75979, 0x00003bf8, 256);

// 0x07003CF8 - 0x07003DE8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003CF8, 0x00437870, 75979, 0x00003cf8, 240);

// 0x07003DE8 - 0x07003EE8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003DE8, 0x00437870, 75979, 0x00003de8, 256);

// 0x07003EE8 - 0x07003FE8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003EE8, 0x00437870, 75979, 0x00003ee8, 256);

// 0x07003FE8 - 0x07004058
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07003FE8, 0x00437870, 75979, 0x00003fe8, 112);

// 0x07004058 - 0x07004148
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07004058, 0x00437870, 75979, 0x00004058, 240);

// 0x07004148 - 0x07004248
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07004148, 0x00437870, 75979, 0x00004148, 256);

// 0x07004248 - 0x07004338
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07004248, 0x00437870, 75979, 0x00004248, 240);

// 0x07004338 - 0x07004428
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07004338, 0x00437870, 75979, 0x00004338, 240);

// 0x07004428 - 0x07004468
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07004428, 0x00437870, 75979, 0x00004428, 64);

// 0x07004468 - 0x07004950
static const Gfx rr_seg7_dl_07004468[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_07002EF8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07002FD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_070030D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_070031D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(rr_seg7_vertex_070032B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_070033A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07003488, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07003568, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  0,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  4, 13,  2, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07003668, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  0, 0x0),
    gsSP2Triangles( 5,  9,  2, 0x0,  9, 10,  2, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07003758, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9,  4, 0x0,  4,  6,  8, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  8, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07003858, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07003948, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_07003A28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07003B08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07003BF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(rr_seg7_vertex_07003CF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0,  9, 13, 10, 0x0),
    gsSP1Triangle( 9, 11, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07003DE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  0,  8,  9, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07003EE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_07003FE8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004950 - 0x07004A98
static const Gfx rr_seg7_dl_07004950[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_07004058, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_07004148, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 4,  9,  5, 0x0,  4,  6, 10, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07004248, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07004338, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_07004428, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004A98 - 0x07004B10
const Gfx rr_seg7_dl_07004A98[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(rr_seg7_dl_07004468),
    gsSPDisplayList(rr_seg7_dl_07004950),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
