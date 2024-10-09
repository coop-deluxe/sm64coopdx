#include "pc/rom_assets.h"
// Whirlpool

// 0x05012848
ROM_ASSET_LOAD_TEXTURE(whirlpool_seg5_texture_05012848, "actors/whirlpool/whirlpool.ia16.inc.c", 0x0013b910, 41727, 0x00012848, 4096);

// 0x05013848
ROM_ASSET_LOAD_VTX(whirlpool_seg5_vertex_05013848, 0x0013b910, 41727, 0x00013848, 224);

// 0x05013928
ROM_ASSET_LOAD_VTX(whirlpool_seg5_vertex_05013928, 0x0013b910, 41727, 0x00013928, 256);

// 0x05013A28
ROM_ASSET_LOAD_VTX(whirlpool_seg5_vertex_05013A28, 0x0013b910, 41727, 0x00013a28, 224);

// 0x05013B08
ROM_ASSET_LOAD_VTX(whirlpool_seg5_vertex_05013B08, 0x0013b910, 41727, 0x00013b08, 80);

// 0x05013B58 - 0x05013CB8
const Gfx whirlpool_seg5_dl_05013B58[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, whirlpool_seg5_texture_05012848),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(whirlpool_seg5_vertex_05013848, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  3,  7,  5, 0x0),
    gsSP2Triangles( 1,  6,  8, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 1,  8, 10, 0x0, 11,  3, 12, 0x0),
    gsSP2Triangles(11, 13,  3, 0x0, 13,  7,  3, 0x0),
    gsSPVertex(whirlpool_seg5_vertex_05013928, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  8,  6,  3, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles( 2, 10,  8, 0x0, 11,  2,  8, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(whirlpool_seg5_vertex_05013A28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  3,  6,  5, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  9,  6,  3, 0x0),
    gsSP2Triangles( 7,  9,  3, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 13, 11, 0x0),
    gsSPVertex(whirlpool_seg5_vertex_05013B08, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 3,  2,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05013CB8 - 0x05013D28
const Gfx whirlpool_seg5_dl_05013CB8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(whirlpool_seg5_dl_05013B58),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
