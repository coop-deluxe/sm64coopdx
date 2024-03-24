#include "pc/rom_assets.h"
// 0x0700B488 - 0x0700B578
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700B488, 0x00371c40, 68724, 0x0000b488, 240);

// 0x0700B578 - 0x0700B678
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700B578, 0x00371c40, 68724, 0x0000b578, 256);

// 0x0700B678 - 0x0700B768
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700B678, 0x00371c40, 68724, 0x0000b678, 240);

// 0x0700B768 - 0x0700B848
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700B768, 0x00371c40, 68724, 0x0000b768, 224);

// 0x0700B848 - 0x0700B8A8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700B848, 0x00371c40, 68724, 0x0000b848, 96);

// 0x0700B8A8 - 0x0700B9E0
static const Gfx bbh_seg7_dl_0700B8A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertexNonGlobal(bbh_seg7_vertex_0700B488, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  5,  1, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertexNonGlobal(bbh_seg7_vertex_0700B578, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  4,  8, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 14, 13, 15, 0x0),
    gsSPVertexNonGlobal(bbh_seg7_vertex_0700B678, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertexNonGlobal(bbh_seg7_vertex_0700B768, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7, 10,  8, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 13, 10, 0x0),
    gsSPVertexNonGlobal(bbh_seg7_vertex_0700B848, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B9E0 - 0x0700BA50
const Gfx bbh_seg7_dl_0700B9E0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700B8A8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
