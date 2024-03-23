#include "pc/rom_assets.h"
// 0x070141E8 - 0x070142E8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070141E8, 0x0046c3a0, 47442, 0x000141e8, 256);

// 0x070142E8 - 0x070143D8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070142E8, 0x0046c3a0, 47442, 0x000142e8, 240);

// 0x070143D8 - 0x070144B8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070143D8, 0x0046c3a0, 47442, 0x000143d8, 224);

// 0x070144B8 - 0x070145A8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070144B8, 0x0046c3a0, 47442, 0x000144b8, 240);

// 0x070145A8 - 0x070146A8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070145A8, 0x0046c3a0, 47442, 0x000145a8, 256);

// 0x070146A8 - 0x07014788
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070146A8, 0x0046c3a0, 47442, 0x000146a8, 224);

// 0x07014788 - 0x07014878
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07014788, 0x0046c3a0, 47442, 0x00014788, 240);

// 0x07014878 - 0x07014968
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07014878, 0x0046c3a0, 47442, 0x00014878, 240);

// 0x07014968 - 0x070149A8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07014968, 0x0046c3a0, 47442, 0x00014968, 64);

// 0x070149A8 - 0x07014C28
static const Gfx bits_seg7_dl_070149A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_070141E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  5,  9, 0x0,  8,  3,  5, 0x0),
    gsSP2Triangles( 5, 10,  9, 0x0,  9,  0, 11, 0x0),
    gsSP2Triangles( 9, 11,  8, 0x0,  0,  2, 12, 0x0),
    gsSP2Triangles( 0, 12, 11, 0x0, 12, 13, 11, 0x0),
    gsSP2Triangles( 2, 14, 12, 0x0,  2, 15, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070142E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  9,  7, 0x0,  4,  6, 10, 0x0),
    gsSP2Triangles( 6, 11, 10, 0x0, 12,  4, 10, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_070143D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles( 0, 10,  3, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070144B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070145A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_070146A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07014788, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07014878, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07014968, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014C28 - 0x07014C98
const Gfx bits_seg7_dl_07014C28[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_070149A8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
