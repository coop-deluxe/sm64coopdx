#include "pc/rom_assets.h"
// 0x0701A8E8 - 0x0701A900
static const Lights1 lll_seg7_lights_0701A8E8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xfe, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701A900 - 0x0701A9F0
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_0701A900, 0x004784a0, 83204, 0x0001a900, 240);

// 0x0701A9F0 - 0x0701AAE0
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_0701A9F0, 0x004784a0, 83204, 0x0001a9f0, 240);

// 0x0701AAE0 - 0x0701AB20
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_0701AAE0, 0x004784a0, 83204, 0x0001aae0, 64);

// 0x0701AB20 - 0x0701AC20
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_0701AB20, 0x004784a0, 83204, 0x0001ab20, 256);

// 0x0701AC20 - 0x0701ACE8
static const Gfx lll_seg7_dl_0701AC20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_0701A8E8.l, 1),
    gsSPLight(&lll_seg7_lights_0701A8E8.a, 2),
    gsSPVertex(lll_seg7_vertex_0701A900, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(lll_seg7_vertex_0701A9F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(lll_seg7_vertex_0701AAE0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701ACE8 - 0x0701AD70
static const Gfx lll_seg7_dl_0701ACE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_0701AB20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0,  0, 11,  1, 0x0),
    gsSP2Triangles( 0, 12, 13, 0x0,  0, 14, 12, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  0, 15, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701AD70 - 0x0701ADE8
const Gfx lll_seg7_dl_0701AD70[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_dl_0701AC20),
    gsSPDisplayList(lll_seg7_dl_0701ACE8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
