#include "pc/rom_assets.h"
// 0x0700B130 - 0x0700B148
static const Lights1 ttm_seg7_lights_0700B130 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x49, 0x49, 0x49
);

// 0x0700B148 - 0x0700B248
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700B148, 0x004d1910, 104662, 0x0000b148, 256);

// 0x0700B248 - 0x0700B338
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700B248, 0x004d1910, 104662, 0x0000b248, 240);

// 0x0700B338 - 0x0700B3F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700B338, 0x004d1910, 104662, 0x0000b338, 192);

// 0x0700B3F8 - 0x0700B530
static const Gfx ttm_seg7_dl_0700B3F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700B130.l, 1),
    gsSPLight(&ttm_seg7_lights_0700B130.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700B148, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700B248, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700B338, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  0,  6,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 2,  7,  6, 0x0,  2,  1,  8, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  6, 10,  5, 0x0),
    gsSP2Triangles( 6,  7,  9, 0x0,  5, 11,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B530 - 0x0700B590
const Gfx ttm_seg7_dl_0700B530[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700B3F8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
