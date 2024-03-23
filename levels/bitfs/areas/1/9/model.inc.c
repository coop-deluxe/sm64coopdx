#include "pc/rom_assets.h"
// 0x070070E8 - 0x070071C8
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_070070E8, 0x004614d0, 37742, 0x000070e8, 224);

// 0x070071C8 - 0x070072A8
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_070071C8, 0x004614d0, 37742, 0x000071c8, 224);

// 0x070072A8 - 0x070073A8
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_070072A8, 0x004614d0, 37742, 0x000072a8, 256);

// 0x070073A8 - 0x07007488
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_070073A8, 0x004614d0, 37742, 0x000073a8, 224);

// 0x07007488 - 0x07007538
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07007488, 0x004614d0, 37742, 0x00007488, 176);

// 0x07007538 - 0x07007578
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07007538, 0x004614d0, 37742, 0x00007538, 64);

// 0x07007578 - 0x07007700
static const Gfx bitfs_seg7_dl_07007578[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitfs_seg7_vertex_070070E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  4,  6,  2, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  8,  5,  1, 0x0),
    gsSP2Triangles( 8,  7,  5, 0x0,  2,  6,  9, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0,  0,  8,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bitfs_seg7_vertex_070071C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bitfs_seg7_vertex_070072A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bitfs_seg7_vertex_070073A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  5, 0x0),
    gsSP1Triangle(11, 13, 12, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07007488, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP1Triangle( 8,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007700 - 0x07007720
static const Gfx bitfs_seg7_dl_07007700[] = {
    gsSPVertex(bitfs_seg7_vertex_07007538, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007720 - 0x07007798
const Gfx bitfs_seg7_dl_07007720[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitfs_seg7_dl_07007578),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bitfs_seg7_dl_07007700),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
