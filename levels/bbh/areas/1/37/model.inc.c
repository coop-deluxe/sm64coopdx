#include "pc/rom_assets.h"
// 0x0701E948 - 0x0701E960

// 0x0701E960 - 0x0701E978

// 0x0701E978 - 0x0701E9F8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701E978, 0x00371c40, 68724, 0x0001e978, 128);

// 0x0701E9F8 - 0x0701EAE8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701E9F8, 0x00371c40, 68724, 0x0001e9f8, 240);

// 0x0701EAE8 - 0x0701EBD8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701EAE8, 0x00371c40, 68724, 0x0001eae8, 240);

// 0x0701EBD8 - 0x0701EC18
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0701EBD8, 0x00371c40, 68724, 0x0001ebd8, 64);

// 0x0701EC18 - 0x0701ED18
static const Gfx bbh_seg7_dl_0701EC18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0701E948.l, 1),
    gsSPLight(&bbh_seg7_lights_0701E948.a, 2),
    gsSPVertex(bbh_seg7_vertex_0701E978, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&bbh_seg7_lights_0701E960.l, 1),
    gsSPLight(&bbh_seg7_lights_0701E960.a, 2),
    gsSPVertex(bbh_seg7_vertex_0701E9F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701EAE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701EBD8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701ED18 - 0x0701ED88
const Gfx bbh_seg7_dl_0701ED18[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701EC18),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
