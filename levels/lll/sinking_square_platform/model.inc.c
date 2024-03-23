#include "pc/rom_assets.h"
// 0x07019C80 - 0x07019D20
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07019C80, 0x004784a0, 83204, 0x00019c80, 160);

// 0x07019D20 - 0x07019E20
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07019D20, 0x004784a0, 83204, 0x00019d20, 256);

// 0x07019E20 - 0x07019E80
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07019E20, 0x004784a0, 83204, 0x00019e20, 96);

// 0x07019E80 - 0x07019F20
ROM_ASSET_LOAD_VTX(lll_seg7_vertex_07019E80, 0x004784a0, 83204, 0x00019e80, 160);

// 0x07019F20 - 0x0701A010
static const Gfx lll_seg7_dl_07019F20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_0700FC48.l, 1),
    gsSPLight(&lll_seg7_lights_0700FC48.a, 2),
    gsSPVertex(lll_seg7_vertex_07019C80, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  2,  8,  9, 0x0),
    gsSPLight(&lll_seg7_lights_0700FC60.l, 1),
    gsSPLight(&lll_seg7_lights_0700FC60.a, 2),
    gsSPVertex(lll_seg7_vertex_07019D20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(lll_seg7_vertex_07019E20, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&lll_seg7_lights_0700FC00.l, 1),
    gsSPLight(&lll_seg7_lights_0700FC00.a, 2),
    gsSPVertex(lll_seg7_vertex_07019E80, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701A010 - 0x0701A080
const Gfx lll_seg7_dl_0701A010[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_dl_07019F20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
