#include "pc/rom_assets.h"
// 0x07009670 - 0x07009770
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009670, 0x004614d0, 37742, 0x00009670, 256);

// 0x07009770 - 0x07009870
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009770, 0x004614d0, 37742, 0x00009770, 256);

// 0x07009870 - 0x07009960
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009870, 0x004614d0, 37742, 0x00009870, 240);

// 0x07009960 - 0x07009A60
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009960, 0x004614d0, 37742, 0x00009960, 256);

// 0x07009A60 - 0x07009B50
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009A60, 0x004614d0, 37742, 0x00009a60, 240);

// 0x07009B50 - 0x07009C40
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009B50, 0x004614d0, 37742, 0x00009b50, 240);

// 0x07009C40 - 0x07009D30
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009C40, 0x004614d0, 37742, 0x00009c40, 240);

// 0x07009D30 - 0x07009E30
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009D30, 0x004614d0, 37742, 0x00009d30, 256);

// 0x07009E30 - 0x07009F30
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009E30, 0x004614d0, 37742, 0x00009e30, 256);

// 0x07009F30 - 0x0700A010
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_07009F30, 0x004614d0, 37742, 0x00009f30, 224);

// 0x0700A010 - 0x0700A100
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_0700A010, 0x004614d0, 37742, 0x0000a010, 240);

// 0x0700A100 - 0x0700A1F0
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_0700A100, 0x004614d0, 37742, 0x0000a100, 240);

// 0x0700A1F0 - 0x0700A2E0
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_0700A1F0, 0x004614d0, 37742, 0x0000a1f0, 240);

// 0x0700A2E0 - 0x0700A3E0
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_0700A2E0, 0x004614d0, 37742, 0x0000a2e0, 256);

// 0x0700A3E0 - 0x0700A4A0
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_0700A3E0, 0x004614d0, 37742, 0x0000a3e0, 192);

// 0x0700A4A0 - 0x0700A520
ROM_ASSET_LOAD_VTX(bitfs_seg7_vertex_0700A4A0, 0x004614d0, 37742, 0x0000a4a0, 128);

// 0x0700A520 - 0x0700A9D0
static const Gfx bitfs_seg7_dl_0700A520[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitfs_seg7_vertex_07009670, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  6,  4, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(12, 11, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009770, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles(10,  9, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(14, 13, 12, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009870, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009960, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  4,  2,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  5, 11, 12, 0x0),
    gsSP2Triangles( 8, 13, 14, 0x0, 15,  8, 14, 0x0),
    gsSP1Triangle( 6,  8, 15, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009A60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  2,  3, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  5,  8, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009B50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 10, 12, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009C40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  4,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 12,  9, 13, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009D30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009E30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitfs_seg7_vertex_07009F30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  5,  6,  1, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(11, 13, 12, 0x0),
    gsSPVertex(bitfs_seg7_vertex_0700A010, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitfs_seg7_vertex_0700A100, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitfs_seg7_vertex_0700A1F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(bitfs_seg7_vertex_0700A2E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitfs_seg7_vertex_0700A3E0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A9D0 - 0x0700AA00
static const Gfx bitfs_seg7_dl_0700A9D0[] = {
    gsSPVertex(bitfs_seg7_vertex_0700A4A0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AA00 - 0x0700AA78
const Gfx bitfs_seg7_dl_0700AA00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitfs_seg7_dl_0700A520),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bitfs_seg7_dl_0700A9D0),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
