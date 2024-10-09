#include "pc/rom_assets.h"
// Breakable Box

// 0x08011A78
static const Lights1 breakable_box_seg8_lights_08011A80 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08011A90
ROM_ASSET_LOAD_TEXTURE(breakable_box_seg8_texture_08011A90, "actors/breakable_box/crazy_box_surface.rgba16.inc.c", 0x001f2200, 59076, 0x00011a90, 2048);

// 0x08012290
ROM_ASSET_LOAD_TEXTURE(breakable_box_seg8_texture_08012290, "actors/breakable_box/cork_box_surface.rgba16.inc.c", 0x001f2200, 59076, 0x00012290, 2048);

// 0x08012A90
ROM_ASSET_LOAD_VTX(breakable_box_seg8_vertex_08012A90, 0x001f2200, 59076, 0x00012a90, 240);

// 0x08012B80
ROM_ASSET_LOAD_VTX(breakable_box_seg8_vertex_08012B80, 0x001f2200, 59076, 0x00012b80, 176);

// 0x08012C30 - 0x08012CD8
const Gfx breakable_box_seg8_dl_08012C30[] = {
    gsSPLight(&breakable_box_seg8_lights_08011A80.l, 1),
    gsSPLight(&breakable_box_seg8_lights_08011A80.a, 2),
    gsSPVertex(breakable_box_seg8_vertex_08012A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(breakable_box_seg8_vertex_08012B80, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP1Triangle( 8,  9, 10, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x08012CD8 - 0x08012D20
const Gfx breakable_box_seg8_dl_08012CD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x08012D20 - 0x08012D48
const Gfx breakable_box_seg8_dl_08012D20[] = {
    gsSPDisplayList(breakable_box_seg8_dl_08012CD8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, breakable_box_seg8_texture_08011A90),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(breakable_box_seg8_dl_08012C30),
};

// 0x08012D20 - 0x08012D70
const Gfx breakable_box_seg8_dl_08012D48[] = {
    gsSPDisplayList(breakable_box_seg8_dl_08012CD8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, breakable_box_seg8_texture_08012290),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(breakable_box_seg8_dl_08012C30),
};
