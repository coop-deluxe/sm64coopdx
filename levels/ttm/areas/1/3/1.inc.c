#include "pc/rom_assets.h"
// 0x0700A340 - 0x0700A358
static const Lights1 ttm_seg7_lights_0700A340 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700A358 - 0x0700A370
static const Lights1 ttm_seg7_lights_0700A358 = gdSPDefLights1(
    0x7f, 0x7f, 0x64,
    0xff, 0xff, 0xc9, 0x28, 0x28, 0x28
);

// 0x0700A370 - 0x0700A460
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700A370, 0x004d1910, 104662, 0x0000a370, 240);

// 0x0700A460 - 0x0700A560
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700A460, 0x004d1910, 104662, 0x0000a460, 256);

// 0x0700A560 - 0x0700A640
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700A560, 0x004d1910, 104662, 0x0000a560, 224);

// 0x0700A640 - 0x0700A710
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700A640, 0x004d1910, 104662, 0x0000a640, 208);

// 0x0700A710 - 0x0700A848
static const Gfx ttm_seg7_dl_0700A710[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700A340.l, 1),
    gsSPLight(&ttm_seg7_lights_0700A340.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700A370, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 13,  0, 0x0,  9, 12, 13, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  8,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700A460, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  6,  1,  5, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700A560, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A848 - 0x0700A8C0
static const Gfx ttm_seg7_dl_0700A848[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttm_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700A358.l, 1),
    gsSPLight(&ttm_seg7_lights_0700A358.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700A640, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 0,  8,  6, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles(11,  9,  0, 0x0,  0,  2, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A8C0 - 0x0700A928
const Gfx ttm_seg7_dl_0700A8C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700A710),
    gsSPDisplayList(ttm_seg7_dl_0700A848),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
