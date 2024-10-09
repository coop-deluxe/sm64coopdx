#include "pc/rom_assets.h"
// 0x0700D3A8 - 0x0700D498
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700D3A8, 0x004af930, 34262, 0x0000d3a8, 240);

// 0x0700D498 - 0x0700D588
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700D498, 0x004af930, 34262, 0x0000d498, 240);

// 0x0700D588 - 0x0700D688
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700D588, 0x004af930, 34262, 0x0000d588, 256);

// 0x0700D688 - 0x0700D768
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700D688, 0x004af930, 34262, 0x0000d688, 224);

// 0x0700D768 - 0x0700D858
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700D768, 0x004af930, 34262, 0x0000d768, 240);

// 0x0700D858 - 0x0700D928
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700D858, 0x004af930, 34262, 0x0000d858, 208);

// 0x0700D928 - 0x0700DAD8
static const Gfx pss_seg7_dl_0700D928[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, pss_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(pss_seg7_vertex_0700D3A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700D498, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700D588, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11,  7, 10, 0x0),
    gsSP2Triangles(11, 12,  7, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(pss_seg7_vertex_0700D688, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 3,  0,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 10,  6,  8, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_0700D768, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14,  6, 0x0),
    gsSPVertex(pss_seg7_vertex_0700D858, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 9, 12, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DAD8 - 0x0700DB48
const Gfx pss_seg7_dl_0700DAD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(pss_seg7_dl_0700D928),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
