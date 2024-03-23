#include "pc/rom_assets.h"
// Capswitch

// 0x05001BB8
static const Lights1 capswitch_seg5_lights_05001BB8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05001BD0
static const Lights1 capswitch_seg5_lights_05001BD0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05001BE8
static const Lights1 capswitch_seg5_lights_05001BE8 = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05001C00
static const Lights1 capswitch_seg5_lights_05001C00 = gdSPDefLights1(
    0x01, 0x2a, 0x09,
    0x07, 0xa9, 0x25, 0x28, 0x28, 0x28
);

// 0x05001C18
static const Lights1 capswitch_seg5_lights_05001C18 = gdSPDefLights1(
    0x00, 0x00, 0x3f,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// 0x05001C30
static const Lights1 capswitch_seg5_lights_05001C30 = gdSPDefLights1(
    0x3f, 0x25, 0x02,
    0xff, 0x96, 0x08, 0x28, 0x28, 0x28
);

// 0x05001C48
ROM_ASSET_LOAD_TEXTURE(capswitch_seg5_texture_05001C48, "actors/capswitch/cap_switch_head.ia16.inc.c", 0x00165a50, 4471, 0x00001c48, 4096);

// 0x05002C48
ROM_ASSET_LOAD_TEXTURE(capswitch_seg5_texture_05002C48, "actors/capswitch/cap_switch_base.rgba16.inc.c", 0x00165a50, 4471, 0x00002c48, 128);

// 0x05002CC8
ROM_ASSET_LOAD_VTX(capswitch_seg5_vertex_05002CC8, 0x00165a50, 4471, 0x00002cc8, 192);

// 0x05002D88 - 0x05002E00
const Gfx capswitch_seg5_dl_05002D88[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, capswitch_seg5_texture_05001C48),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&capswitch_seg5_lights_05001BB8.l, 1),
    gsSPLight(&capswitch_seg5_lights_05001BB8.a, 2),
    gsSPVertex(capswitch_seg5_vertex_05002CC8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0, 11,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05002E00 - 0x05002E60
const Gfx cap_switch_exclamation_seg5_dl_05002E00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(capswitch_seg5_dl_05002D88),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05002E60
ROM_ASSET_LOAD_VTX(capswitch_seg5_vertex_05002E60, 0x00165a50, 4471, 0x00002e60, 256);

// 0x05002F60
ROM_ASSET_LOAD_VTX(capswitch_seg5_vertex_05002F60, 0x00165a50, 4471, 0x00002f60, 192);

// 0x05003020 - 0x05003120
const Gfx capswitch_seg5_dl_05003020[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, capswitch_seg5_texture_05002C48),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 4 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&capswitch_seg5_lights_05001BD0.l, 1),
    gsSPLight(&capswitch_seg5_lights_05001BD0.a, 2),
    gsSPVertex(capswitch_seg5_vertex_05002E60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  5,  6, 10, 0x0),
    gsSP2Triangles(11,  5, 12, 0x0,  3,  5, 11, 0x0),
    gsSP2Triangles( 5, 10, 12, 0x0,  7,  0,  8, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle( 1, 13,  2, 0x0),
    gsSPVertex(capswitch_seg5_vertex_05002F60, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  2,  6, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 1,  8,  2, 0x0,  1, 11,  8, 0x0),
    gsSP1Triangle( 2,  8, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003120 - 0x05003180
const Gfx cap_switch_base_seg5_dl_05003120[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (4 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(capswitch_seg5_dl_05003020),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

//0x05003180
ROM_ASSET_LOAD_VTX(capswitch_seg5_vertex_05003180, 0x00165a50, 4471, 0x00003180, 256);

// 0x05003280 - 0x05003350
const Gfx capswitch_seg5_dl_05003280[] = {
    gsSPVertex(capswitch_seg5_vertex_05003180, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  7,  3,  0, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles(11,  6,  5, 0x0,  5, 10, 11, 0x0),
    gsSP2Triangles( 5,  2,  9, 0x0, 10,  9, 12, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles( 6, 11, 14, 0x0, 14, 11, 13, 0x0),
    gsSP2Triangles( 6, 14,  7, 0x0, 15,  8, 13, 0x0),
    gsSP2Triangles(13,  8, 14, 0x0, 13, 12, 15, 0x0),
    gsSP2Triangles( 8, 15,  4, 0x0,  7, 14,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003350 - 0x05003370
const Gfx capswitch_seg5_dl_05003350[] = {
    gsSPLight(&capswitch_seg5_lights_05001BE8.l, 1),
    gsSPLight(&capswitch_seg5_lights_05001BE8.a, 2),
    gsSPDisplayList(capswitch_seg5_dl_05003280),
    gsSPEndDisplayList(),
};

// 0x05003370 - 0x05003390
const Gfx capswitch_seg5_dl_05003370[] = {
    gsSPLight(&capswitch_seg5_lights_05001C00.l, 1),
    gsSPLight(&capswitch_seg5_lights_05001C00.a, 2),
    gsSPDisplayList(capswitch_seg5_dl_05003280),
    gsSPEndDisplayList(),
};

// 0x05003390 - 0x050033B0
const Gfx capswitch_seg5_dl_05003390[] = {
    gsSPLight(&capswitch_seg5_lights_05001C18.l, 1),
    gsSPLight(&capswitch_seg5_lights_05001C18.a, 2),
    gsSPDisplayList(capswitch_seg5_dl_05003280),
    gsSPEndDisplayList(),
};

// 0x050033B0 - 0x050033D0
const Gfx capswitch_seg5_dl_050033B0[] = {
    gsSPLight(&capswitch_seg5_lights_05001C30.l, 1),
    gsSPLight(&capswitch_seg5_lights_05001C30.a, 2),
    gsSPDisplayList(capswitch_seg5_dl_05003280),
    gsSPEndDisplayList(),
};
