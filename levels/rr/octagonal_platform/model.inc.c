#include "pc/rom_assets.h"
// 0x0701A6F0 - 0x0701A708
static const Lights1 rr_seg7_lights_0701A6F0 = gdSPDefLights1(
    0x55, 0x5f, 0x53,
    0xe3, 0xfe, 0xdf, 0x28, 0x28, 0x28
);

// 0x0701A708 - 0x0701A7F8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0701A708, 0x00437870, 75979, 0x0001a540, 240);

// 0x0701A7F8 - 0x0701A8E8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0701A7F8, 0x00437870, 75979, 0x0001a630, 240);

// 0x0701A8E8 - 0x0701A9D8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0701A8E8, 0x00437870, 75979, 0x0001a720, 240);

// 0x0701A9D8 - 0x0701AA48
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_0701A9D8, 0x00437870, 75979, 0x0001a810, 112);

// 0x0701AA48 - 0x0701AB78
static const Gfx rr_seg7_dl_0701AA48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&rr_seg7_lights_0701A6F0.l, 1),
    gsSPLight(&rr_seg7_lights_0701A6F0.a, 2),
    gsSPVertex(rr_seg7_vertex_0701A708, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_0701A7F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0,  0, 11,  1, 0x0),
    gsSP2Triangles( 0, 12, 11, 0x0,  0, 13, 12, 0x0),
    gsSP1Triangle( 0, 14, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_0701A8E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  3,  9,  8, 0x0),
    gsSP2Triangles( 3, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_0701A9D8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701AB78 - 0x0701ABE8
const Gfx rr_seg7_dl_0701AB78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(rr_seg7_dl_0701AA48),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
