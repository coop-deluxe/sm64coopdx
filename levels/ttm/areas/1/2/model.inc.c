#include "pc/rom_assets.h"
// 0x0700A1B0 - 0x0700A1C8
static const Lights1 ttm_seg7_lights_0700A1B0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700A1C8 - 0x0700A268
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700A1C8, 0x004d1910, 104662, 0x0000a1c8, 160);

// 0x0700A268 - 0x0700A2E0
static const Gfx ttm_seg7_dl_0700A268[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700A1B0.l, 1),
    gsSPLight(&ttm_seg7_lights_0700A1B0.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700A1C8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  4,  8, 0x0,  9,  8,  1, 0x0),
    gsSP2Triangles( 9,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A2E0 - 0x0700A340
const Gfx ttm_seg7_dl_0700A2E0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700A268),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
