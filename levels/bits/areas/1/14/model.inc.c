#include "pc/rom_assets.h"
// 0x0700BA88 - 0x0700BB88
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BA88, 0x0046c3a0, 47442, 0x0000ba88, 256);

// 0x0700BB88 - 0x0700BC08
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BB88, 0x0046c3a0, 47442, 0x0000bb88, 128);

// 0x0700BC08 - 0x0700BD08
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BC08, 0x0046c3a0, 47442, 0x0000bc08, 256);

// 0x0700BD08 - 0x0700BE08
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BD08, 0x0046c3a0, 47442, 0x0000bd08, 256);

// 0x0700BE08 - 0x0700BE48
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BE08, 0x0046c3a0, 47442, 0x0000be08, 64);

// 0x0700BE48 - 0x0700BF48
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BE48, 0x0046c3a0, 47442, 0x0000be48, 256);

// 0x0700BF48 - 0x0700BF88
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BF48, 0x0046c3a0, 47442, 0x0000bf48, 64);

// 0x0700BF88 - 0x0700C088
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700BF88, 0x0046c3a0, 47442, 0x0000bf88, 256);

// 0x0700C088 - 0x0700C188
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C088, 0x0046c3a0, 47442, 0x0000c088, 256);

// 0x0700C188 - 0x0700C288
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C188, 0x0046c3a0, 47442, 0x0000c188, 256);

// 0x0700C288 - 0x0700C378
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C288, 0x0046c3a0, 47442, 0x0000c288, 240);

// 0x0700C378 - 0x0700C468
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C378, 0x0046c3a0, 47442, 0x0000c378, 240);

// 0x0700C468 - 0x0700C558
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C468, 0x0046c3a0, 47442, 0x0000c468, 240);

// 0x0700C558 - 0x0700C648
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C558, 0x0046c3a0, 47442, 0x0000c558, 240);

// 0x0700C648 - 0x0700C738
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C648, 0x0046c3a0, 47442, 0x0000c648, 240);

// 0x0700C738 - 0x0700C828
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C738, 0x0046c3a0, 47442, 0x0000c738, 240);

// 0x0700C828 - 0x0700C8C8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C828, 0x0046c3a0, 47442, 0x0000c828, 160);

// 0x0700C8C8 - 0x0700C908
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700C8C8, 0x0046c3a0, 47442, 0x0000c8c8, 64);

// 0x0700C908 - 0x0700C998
static const Gfx bits_seg7_dl_0700C908[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700BA88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700BB88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C998 - 0x0700CA70
static const Gfx bits_seg7_dl_0700C998[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700BC08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 11, 10,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700BD08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700BE08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CA70 - 0x0700CAF0
static const Gfx bits_seg7_dl_0700CA70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700BE48, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700BF48, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CAF0 - 0x0700CDA0
static const Gfx bits_seg7_dl_0700CAF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700BF88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C088, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C188, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C288, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C378, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C468, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C558, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 4,  6, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C648, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  9,  6, 0x0, 10, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C738, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700C828, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CDA0 - 0x0700CDC0
static const Gfx bits_seg7_dl_0700CDA0[] = {
    gsSPVertex(bits_seg7_vertex_0700C8C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CDC0 - 0x0700CE50
const Gfx bits_seg7_dl_0700CDC0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_0700C908),
    gsSPDisplayList(bits_seg7_dl_0700C998),
    gsSPDisplayList(bits_seg7_dl_0700CA70),
    gsSPDisplayList(bits_seg7_dl_0700CAF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bits_seg7_dl_0700CDA0),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
