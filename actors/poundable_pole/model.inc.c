#include "pc/rom_assets.h"
// Poundable Pole

// 0x06001038
static const Lights1 poundable_pole_seg6_lights_06001038 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06001050
ROM_ASSET_LOAD_TEXTURE(poundable_pole_seg6_texture_06001050, "actors/poundable_pole/poundable_pole_top.rgba16.inc.c", 0x001c4230, 80474, 0x00001050, 2048);

// 0x06001850
ROM_ASSET_LOAD_TEXTURE(poundable_pole_seg6_texture_06001850, "actors/poundable_pole/poundable_pole_side.rgba16.inc.c", 0x001c4230, 80474, 0x00001850, 2048);

// 0x06002050
ROM_ASSET_LOAD_VTX(poundable_pole_seg6_vertex_06002050, 0x001c4230, 80474, 0x00002050, 128);

// 0x060020D0
ROM_ASSET_LOAD_VTX(poundable_pole_seg6_vertex_060020D0, 0x001c4230, 80474, 0x000020d0, 240);

// 0x060021C0
ROM_ASSET_LOAD_VTX(poundable_pole_seg6_vertex_060021C0, 0x001c4230, 80474, 0x000021c0, 240);

// 0x060022B0
ROM_ASSET_LOAD_VTX(poundable_pole_seg6_vertex_060022B0, 0x001c4230, 80474, 0x000022b0, 64);

// 0x060022F0 - 0x06002358
const Gfx poundable_pole_seg6_dl_060022F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, poundable_pole_seg6_texture_06001050),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&poundable_pole_seg6_lights_06001038.l, 1),
    gsSPLight(&poundable_pole_seg6_lights_06001038.a, 2),
    gsSPVertex(poundable_pole_seg6_vertex_06002050, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  2,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x06002358 - 0x06002410
const Gfx poundable_pole_seg6_dl_06002358[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, poundable_pole_seg6_texture_06001850),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(poundable_pole_seg6_vertex_060020D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 11, 14, 0x0),
    gsSPVertex(poundable_pole_seg6_vertex_060021C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP1Triangle( 1,  0, 14, 0x0),
    gsSPVertex(poundable_pole_seg6_vertex_060022B0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06002410 - 0x06002490
const Gfx poundable_pole_seg6_dl_06002410[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(poundable_pole_seg6_dl_060022F0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(poundable_pole_seg6_dl_06002358),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
