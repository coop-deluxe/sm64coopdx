#include "pc/rom_assets.h"
// 0x07011808 - 0x07011908
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07011808, 0x004614d0, 37742, 0x00011808, 256);

// 0x07011908 - 0x07011988
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07011908, 0x004614d0, 37742, 0x00011908, 128);

// 0x07011988 - 0x07011A68
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07011988, 0x004614d0, 37742, 0x00011988, 224);

// 0x07011A68 - 0x07011AB8
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07011A68, 0x004614d0, 37742, 0x00011a68, 80);

// 0x07011AB8 - 0x07011B48
static const Gfx bitfs_seg7_dl_07011AB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitfs_seg7_vertex_07011808, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07011908, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011B48 - 0x07011BA0
static const Gfx bitfs_seg7_dl_07011B48[] = {
    gsSPVertex(bitfs_seg7_vertex_07011988, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  2, 12, 13, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07011A68, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011BA0 - 0x07011C18
const Gfx bitfs_seg7_dl_07011BA0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitfs_seg7_dl_07011AB8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bitfs_seg7_dl_07011B48),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
