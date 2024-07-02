#include "pc/rom_assets.h"
// 0x0700CAB8 - 0x0700CBA8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700CAB8, 0x00437870, 75979, 0x0000cab8, 240);

// 0x0700CBA8 - 0x0700CCA8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700CBA8, 0x00437870, 75979, 0x0000cba8, 256);

// 0x0700CCA8 - 0x0700CD88
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700CCA8, 0x00437870, 75979, 0x0000cca8, 224);

// 0x0700CD88 - 0x0700CE88
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700CD88, 0x00437870, 75979, 0x0000cd88, 256);

// 0x0700CE88 - 0x0700CF88
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700CE88, 0x00437870, 75979, 0x0000ce88, 256);

// 0x0700CF88 - 0x0700D078
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700CF88, 0x00437870, 75979, 0x0000cf88, 240);

// 0x0700D078 - 0x0700D178
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D078, 0x00437870, 75979, 0x0000d078, 256);

// 0x0700D178 - 0x0700D268
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D178, 0x00437870, 75979, 0x0000d178, 240);

// 0x0700D268 - 0x0700D358
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D268, 0x00437870, 75979, 0x0000d268, 240);

// 0x0700D358 - 0x0700D448
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D358, 0x00437870, 75979, 0x0000d358, 240);

// 0x0700D448 - 0x0700D488
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D448, 0x00437870, 75979, 0x0000d448, 64);

// 0x0700D488 - 0x0700D588
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D488, 0x00437870, 75979, 0x0000d488, 256);

// 0x0700D588 - 0x0700D688
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D588, 0x00437870, 75979, 0x0000d588, 256);

// 0x0700D688 - 0x0700D708
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D688, 0x00437870, 75979, 0x0000d688, 128);

// 0x0700D708 - 0x0700D768
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0700D708, 0x00437870, 75979, 0x0000d708, 96);

// 0x0700D768 - 0x0700DAD8
static const Gfx rr_seg7_dl_0700D768[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_0700CAB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0, 11, 10, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_0700CBA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 14, 0x0),
    gsSP2Triangles(11, 10, 13, 0x0, 15, 10, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_0700CCA8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  8,  0,  9, 0x0),
    gsSP2Triangles( 0,  2,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_0700CD88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 13, 14, 11, 0x0),
    gsSP2Triangles(13, 15, 14, 0x0,  9, 12, 11, 0x0),
    gsSPVertex(rr_seg7_vertex_0700CE88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 3,  8,  2, 0x0,  4,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_0700CF88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 3, 12,  1, 0x0, 13, 14,  3, 0x0),
    gsSP2Triangles(14, 12,  3, 0x0,  9,  8, 10, 0x0),
    gsSPVertex(rr_seg7_vertex_0700D078, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_0700D178, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_0700D268, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  8,  6, 10, 0x0),
    gsSP2Triangles( 7, 11, 12, 0x0, 13,  8, 10, 0x0),
    gsSP1Triangle(13, 10, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_0700D358, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  6, 11,  8, 0x0),
    gsSP2Triangles(12, 10,  9, 0x0, 12,  9, 13, 0x0),
    gsSP2Triangles( 9, 14, 13, 0x0,  6, 14, 11, 0x0),
    gsSP1Triangle( 6, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_0700D448, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DAD8 - 0x0700DBA8
static const Gfx rr_seg7_dl_0700DAD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_0700D488, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_0700D588, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_0700D688, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DBA8 - 0x0700DBD8
static const Gfx rr_seg7_dl_0700DBA8[] = {
    gsSPVertex(rr_seg7_vertex_0700D708, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  0,  5,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DBD8 - 0x0700DC58
const Gfx rr_seg7_dl_0700DBD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(rr_seg7_dl_0700D768),
    gsSPDisplayList(rr_seg7_dl_0700DAD8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(rr_seg7_dl_0700DBA8),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
