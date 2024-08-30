#include "pc/rom_assets.h"
// 0x0700B4F0 - 0x0700B508
static const Lights1 bitdw_seg7_lights_0700B4F0 = gdSPDefLights1(
    0x39, 0x6f, 0x5d,
    0x79, 0xeb, 0xc5, 0x28, 0x28, 0x28
);

// 0x0700B508 - 0x0700B5F8
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_0700B508, 0x00454e00, 29021, 0x0000b508, 240);

// 0x0700B5F8 - 0x0700B6E8
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_0700B5F8, 0x00454e00, 29021, 0x0000b5f8, 240);

// 0x0700B6E8 - 0x0700B7D8
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_0700B6E8, 0x00454e00, 29021, 0x0000b6e8, 240);

// 0x0700B7D8 - 0x0700B808
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_0700B7D8, 0x00454e00, 29021, 0x0000b7d8, 48);

// 0x0700B808 - 0x0700B8D8
static const Gfx bitdw_seg7_dl_0700B808[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bitdw_seg7_lights_0700B4F0.l, 1),
    gsSPLight(&bitdw_seg7_lights_0700B4F0.a, 2),
    gsSPVertex(bitdw_seg7_vertex_0700B508, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_0700B5F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_0700B6E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_0700B7D8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B8D8 - 0x0700B948
const Gfx bitdw_seg7_dl_0700B8D8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitdw_seg7_dl_0700B808),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
