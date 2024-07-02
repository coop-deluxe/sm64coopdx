#include "pc/rom_assets.h"
// Heart

// 0x0800D7A0
ROM_ASSET_LOAD_VTX(heart_seg8_vertex_0800D7A0, 0x001f2200, 59076, 0x0000d7a0, 64);

// 0x0800D7E0
ROM_ASSET_LOAD_TEXTURE(heart_seg8_texture_0800D7E0, "actors/heart/spinning_heart.rgba16.inc.c", 0x001f2200, 59076, 0x0000d7e0, 2048);

// 0x0800DFE0 - 0x0800E078
const Gfx heart_seg8_dl_0800DFE0[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPLoadTextureBlock(heart_seg8_texture_0800D7E0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(heart_seg8_vertex_0800D7A0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
