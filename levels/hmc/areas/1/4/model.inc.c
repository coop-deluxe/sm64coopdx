#include "pc/rom_assets.h"
// 0x07008158 - 0x07008258
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008158, 0x003d0dc0, 89137, 0x00008158, 256);

// 0x07008258 - 0x07008358
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008258, 0x003d0dc0, 89137, 0x00008258, 256);

// 0x07008358 - 0x07008448
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008358, 0x003d0dc0, 89137, 0x00008358, 240);

// 0x07008448 - 0x07008538
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008448, 0x003d0dc0, 89137, 0x00008448, 240);

// 0x07008538 - 0x07008638
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008538, 0x003d0dc0, 89137, 0x00008538, 256);

// 0x07008638 - 0x07008718
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008638, 0x003d0dc0, 89137, 0x00008638, 224);

// 0x07008718 - 0x07008818
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008718, 0x003d0dc0, 89137, 0x00008718, 256);

// 0x07008818 - 0x07008918
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008818, 0x003d0dc0, 89137, 0x00008818, 256);

// 0x07008918 - 0x070089F8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008918, 0x003d0dc0, 89137, 0x00008918, 224);

// 0x070089F8 - 0x07008AD8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070089F8, 0x003d0dc0, 89137, 0x000089f8, 224);

// 0x07008AD8 - 0x07008BD8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008AD8, 0x003d0dc0, 89137, 0x00008ad8, 256);

// 0x07008BD8 - 0x07008CB8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008BD8, 0x003d0dc0, 89137, 0x00008bd8, 224);

// 0x07008CB8 - 0x07008DB8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008CB8, 0x003d0dc0, 89137, 0x00008cb8, 256);

// 0x07008DB8 - 0x07008EB8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008DB8, 0x003d0dc0, 89137, 0x00008db8, 256);

// 0x07008EB8 - 0x07008F98
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07008EB8, 0x003d0dc0, 89137, 0x00008eb8, 224);

// 0x07008F98 - 0x070093F0
static const Gfx hmc_seg7_dl_07008F98[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07008158, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle( 0,  2,  4, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008258, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  6,  4, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13,  8, 14, 0x0, 13, 15,  8, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008358, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles( 1, 13,  3, 0x0,  1, 14, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008448, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles( 3, 13,  1, 0x0,  3, 14, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008538, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  2,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(13, 10, 14, 0x0, 13, 11, 10, 0x0),
    gsSP1Triangle( 4,  6, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008638, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  9,  7, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 13, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008718, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  2,  1, 0x0, 10,  1, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008818, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6, 10,  8, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  3, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008918, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0,  8,  7, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_070089F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 10, 13, 0x0, 12, 11, 10, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008AD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 10, 12,  9, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 13,  9, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008BD8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008CB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  5, 11, 0x0, 10, 12,  5, 0x0),
    gsSP2Triangles( 2, 13, 14, 0x0,  2, 15, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008DB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  3, 11, 0x0, 10, 12,  3, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 13,  3, 14, 0x0),
    gsSP1Triangle( 4,  6,  7, 0x0),
    gsSPVertex(hmc_seg7_vertex_07008EB8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 12,  9, 0x0,  0, 13,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070093F0 - 0x07009460
const Gfx hmc_seg7_dl_070093F0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07008F98),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
