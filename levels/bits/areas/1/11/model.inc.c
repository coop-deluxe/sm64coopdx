#include "pc/rom_assets.h"
// 0x07009700 - 0x070097E0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009700, 0x0046c3a0, 47442, 0x00009700, 224);

// 0x070097E0 - 0x070098E0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070097E0, 0x0046c3a0, 47442, 0x000097e0, 256);

// 0x070098E0 - 0x070099C0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070098E0, 0x0046c3a0, 47442, 0x000098e0, 224);

// 0x070099C0 - 0x07009AA0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070099C0, 0x0046c3a0, 47442, 0x000099c0, 224);

// 0x07009AA0 - 0x07009AE0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009AA0, 0x0046c3a0, 47442, 0x00009aa0, 64);

// 0x07009AE0 - 0x07009BD0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009AE0, 0x0046c3a0, 47442, 0x00009ae0, 240);

// 0x07009BD0 - 0x07009CD0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009BD0, 0x0046c3a0, 47442, 0x00009bd0, 256);

// 0x07009CD0 - 0x07009DC0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009CD0, 0x0046c3a0, 47442, 0x00009cd0, 240);

// 0x07009DC0 - 0x07009EC0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009DC0, 0x0046c3a0, 47442, 0x00009dc0, 256);

// 0x07009EC0 - 0x07009FB0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009EC0, 0x0046c3a0, 47442, 0x00009ec0, 240);

// 0x07009FB0 - 0x0700A090
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07009FB0, 0x0046c3a0, 47442, 0x00009fb0, 224);

// 0x0700A090 - 0x0700A170
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A090, 0x0046c3a0, 47442, 0x0000a090, 224);

// 0x0700A170 - 0x0700A250
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A170, 0x0046c3a0, 47442, 0x0000a170, 224);

// 0x0700A250 - 0x0700A2C0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A250, 0x0046c3a0, 47442, 0x0000a250, 112);

// 0x0700A2C0 - 0x0700A3A0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A2C0, 0x0046c3a0, 47442, 0x0000a2c0, 224);

// 0x0700A3A0 - 0x0700A4A0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A3A0, 0x0046c3a0, 47442, 0x0000a3a0, 256);

// 0x0700A4A0 - 0x0700A580
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A4A0, 0x0046c3a0, 47442, 0x0000a4a0, 224);

// 0x0700A580 - 0x0700A680
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A580, 0x0046c3a0, 47442, 0x0000a580, 256);

// 0x0700A680 - 0x0700A780
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A680, 0x0046c3a0, 47442, 0x0000a680, 256);

// 0x0700A780 - 0x0700A880
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A780, 0x0046c3a0, 47442, 0x0000a780, 256);

// 0x0700A880 - 0x0700A970
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A880, 0x0046c3a0, 47442, 0x0000a880, 240);

// 0x0700A970 - 0x0700AA70
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700A970, 0x0046c3a0, 47442, 0x0000a970, 256);

// 0x0700AA70 - 0x0700AB70
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700AA70, 0x0046c3a0, 47442, 0x0000aa70, 256);

// 0x0700AB70 - 0x0700AC20
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700AB70, 0x0046c3a0, 47442, 0x0000ab70, 176);

// 0x0700AC20 - 0x0700AD20
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700AC20, 0x0046c3a0, 47442, 0x0000ac20, 256);

// 0x0700AD20 - 0x0700AD60
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700AD20, 0x0046c3a0, 47442, 0x0000ad20, 64);

// 0x0700AD60 - 0x0700AE98
static const Gfx bits_seg7_dl_0700AD60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07009700, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bits_seg7_vertex_070097E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_070098E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070099C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_07009AA0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AE98 - 0x0700B0E0
static const Gfx bits_seg7_dl_0700AE98[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07009AE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07009BD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  0,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  4, 13,  2, 0x0),
    gsSP1Triangle(10, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07009CD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 3, 12, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07009DC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  0, 10, 11, 0x0),
    gsSP2Triangles( 4,  9,  2, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07009EC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07009FB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A090, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A170, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A250, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B0E0 - 0x0700B420
static const Gfx bits_seg7_dl_0700B0E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700A2C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A3A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 10,  7,  6, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A4A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A580, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A680, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 3, 11, 10, 0x0,  3,  2, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A780, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  4,  3,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(14, 15, 10, 0x0, 15, 11, 10, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A880, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  1,  0, 11, 0x0),
    gsSP2Triangles( 1, 11, 12, 0x0, 13,  6,  5, 0x0),
    gsSP1Triangle(13, 14,  6, 0x0),
    gsSPVertex(bits_seg7_vertex_0700A970, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 11, 15, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_0700AA70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9,  6,  4, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0,  9,  4, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700AB70, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  7,  9,  8, 0x0),
    gsSP1Triangle( 7, 10,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B420 - 0x0700B4A0
static const Gfx bits_seg7_dl_0700B420[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700AC20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700AD20, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B4A0 - 0x0700B528
const Gfx bits_seg7_dl_0700B4A0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_0700AD60),
    gsSPDisplayList(bits_seg7_dl_0700AE98),
    gsSPDisplayList(bits_seg7_dl_0700B0E0),
    gsSPDisplayList(bits_seg7_dl_0700B420),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
