#include "pc/rom_assets.h"
// Blue Coin Switch

// 0x08000000
static const Lights1 blue_coin_switch_seg8_lights_08000000 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x49, 0x49, 0x49
);

// 0x08000018
ROM_ASSET_LOAD_TEXTURE(blue_coin_switch_seg8_texture_08000018, "actors/blue_coin_switch/blue_coin_switch_side.rgba16.inc.c", 0x001f2200, 59076, 0x00000018, 1024);

// 0x08000418
ROM_ASSET_LOAD_TEXTURE(blue_coin_switch_seg8_texture_08000418, "actors/blue_coin_switch/blue_coin_switch_top.rgba16.inc.c", 0x001f2200, 59076, 0x00000418, 2048);

// 0x08000C18
ROM_ASSET_LOAD_VTX(blue_coin_switch_seg8_vertex_08000C18, 0x001f2200, 59076, 0x00000c18, 256);

// 0x08000D18
ROM_ASSET_LOAD_VTX(blue_coin_switch_seg8_vertex_08000D18, 0x001f2200, 59076, 0x00000d18, 64);

// 0x08000D58 - 0x08000DD0
const Gfx blue_coin_switch_seg8_dl_08000D58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, blue_coin_switch_seg8_texture_08000018),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&blue_coin_switch_seg8_lights_08000000.l, 1),
    gsSPLight(&blue_coin_switch_seg8_lights_08000000.a, 2),
    gsSPVertex(blue_coin_switch_seg8_vertex_08000C18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x08000DD0 - 0x08000E08
const Gfx blue_coin_switch_seg8_dl_08000DD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, blue_coin_switch_seg8_texture_08000418),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(blue_coin_switch_seg8_vertex_08000D18, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08000E08 - 0x08000E98
const Gfx blue_coin_switch_seg8_dl_08000E08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(blue_coin_switch_seg8_dl_08000D58),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(blue_coin_switch_seg8_dl_08000DD0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
