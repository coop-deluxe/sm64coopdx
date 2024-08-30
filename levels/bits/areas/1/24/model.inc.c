#include "pc/rom_assets.h"
// 0x07013890 - 0x070138A8
static const Lights1 bits_seg7_lights_07013890 = gdSPDefLights1(
    0x14, 0x2f, 0x29,
    0x50, 0xbf, 0xa7, 0x28, 0x28, 0x28
);

// 0x070138A8 - 0x07013998
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070138A8, 0x0046c3a0, 47442, 0x000138a8, 240);

// 0x07013998 - 0x07013A88
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07013998, 0x0046c3a0, 47442, 0x00013998, 240);

// 0x07013A88 - 0x07013B78
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07013A88, 0x0046c3a0, 47442, 0x00013a88, 240);

// 0x07013B78 - 0x07013BA8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07013B78, 0x0046c3a0, 47442, 0x00013b78, 48);

// 0x07013BA8 - 0x07013C78
static const Gfx bits_seg7_dl_07013BA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bits_seg7_lights_07013890.l, 1),
    gsSPLight(&bits_seg7_lights_07013890.a, 2),
    gsSPVertex(bits_seg7_vertex_070138A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07013998, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07013A88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07013B78, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013C78 - 0x07013CE8
const Gfx bits_seg7_dl_07013C78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_07013BA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
