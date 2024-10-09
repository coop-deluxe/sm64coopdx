#include "pc/rom_assets.h"
// Sand

// 0x0302BA90
ROM_ASSET_LOAD_VTX(sand_seg3_vertex_0302BA90, 0x00201410, 96653, 0x0002ba90, 64);

// 0x0302BAD0
ROM_ASSET_LOAD_TEXTURE(sand_seg3_texture_0302BAD0, "actors/sand/sand_particle.rgba16.inc.c", 0x00201410, 96653, 0x0002bad0, 512);

// 0x0302BCD0 - 0x0302BD60
const Gfx sand_seg3_dl_0302BCD0[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPLoadTextureBlock(sand_seg3_texture_0302BAD0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_CLAMP, G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(sand_seg3_vertex_0302BA90, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
