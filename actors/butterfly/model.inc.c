#include "pc/rom_assets.h"
// Butterfly

// 0x03004348
ROM_ASSET_LOAD_VTX(butterfly_seg3_vertex_03004348, 0x00201410, 96653, 0x00004348, 96);

// 0x030043A8
ROM_ASSET_LOAD_TEXTURE(butterfly_seg3_texture_030043A8, "actors/butterfly/butterfly_wing.rgba16.inc.c", 0x00201410, 96653, 0x000043a8, 4096);

// 0x030053A8
ROM_ASSET_LOAD_VTX(butterfly_seg3_vertex_030053A8, 0x00201410, 96653, 0x000053a8, 96);

// 0x03005408 - 0x030054A0
const Gfx butterfly_seg3_dl_03005408[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(butterfly_seg3_texture_030043A8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(butterfly_seg3_vertex_03004348, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x030054A0 - 0x03005538
const Gfx butterfly_seg3_dl_030054A0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(butterfly_seg3_texture_030043A8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(butterfly_seg3_vertex_030053A8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
