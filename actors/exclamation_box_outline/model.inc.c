#include "pc/rom_assets.h"
// Exclamation Box Outline

// 0x08024CB8
static const Lights1 exclamation_box_outline_seg8_lights_08024CB8 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x08024CD0
static const Lights1 exclamation_box_outline_seg8_lights_08024CD0 = gdSPDefLights1(
    0x00, 0x7f, 0x00,
    0x00, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x08024CE8
static const Lights1 exclamation_box_outline_seg8_lights_08024CE8 = gdSPDefLights1(
    0x00, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// 0x08024D00
static const Lights1 exclamation_box_outline_seg8_lights_08024D00 = gdSPDefLights1(
    0x7f, 0x6a, 0x00,
    0xff, 0xd4, 0x00, 0x28, 0x28, 0x28
);

// 0x08024D18
ROM_ASSET_LOAD_VTX(exclamation_box_outline_seg8_vertex_08024D18, 0x001f2200, 59076, 0x00024d18, 240);

// 0x08024E08
ROM_ASSET_LOAD_VTX(exclamation_box_outline_seg8_vertex_08024E08, 0x001f2200, 59076, 0x00024e08, 176);

// 0x08024EB8 - 0x08024F30
const Gfx exclamation_box_outline_seg8_dl_08024EB8[] = {
    gsSPVertex(exclamation_box_outline_seg8_vertex_08024D18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(exclamation_box_outline_seg8_vertex_08024E08, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x08024F30 - 0x08024F58
const Gfx exclamation_box_outline_seg8_dl_08024F30[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 80),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPEndDisplayList(),
};

// 0x08024F58 - 0x08024F88
const Gfx exclamation_box_outline_seg8_dl_08024F58[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_08024EB8),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x08024F88 - 0x08024FA8
const Gfx exclamation_box_outline_seg8_dl_08024F88[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_08024F30),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024CB8.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024CB8.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_08024F58),
};

// 0x08024FA8 - 0x08024FC8
const Gfx exclamation_box_outline_seg8_dl_08024FA8[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_08024F30),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024CD0.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024CD0.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_08024F58),
};

// 0x08024FC8 - 0x08024FE8
const Gfx exclamation_box_outline_seg8_dl_08024FC8[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_08024F30),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024CE8.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024CE8.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_08024F58),
};

// 0x08024FE8 - 0x08025008
const Gfx exclamation_box_outline_seg8_dl_08024FE8[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_08024F30),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024D00.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_08024D00.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_08024F58),
};

// 0x08025008
ROM_ASSET_LOAD_VTX(exclamation_box_outline_seg8_vertex_08025008, 0x001f2200, 59076, 0x00025008, 224);

// 0x080250E8
ROM_ASSET_LOAD_VTX(exclamation_box_outline_seg8_vertex_080250E8, 0x001f2200, 59076, 0x000250e8, 128);

// 0x08025168
ROM_ASSET_LOAD_TEXTURE(exclamation_box_outline_seg8_texture_08025168, "actors/exclamation_box_outline/exclamation_box_outline.rgba16.inc.c", 0x001f2200, 59076, 0x00025168, 2048);

// 0x08025968 - 0x080259F8
const Gfx exclamation_box_outline_seg8_dl_08025968[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, exclamation_box_outline_seg8_texture_08025168),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(exclamation_box_outline_seg8_vertex_08025008, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11,  8, 12, 0x0, 11, 13,  8, 0x0),
    gsSPVertex(exclamation_box_outline_seg8_vertex_080250E8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x080259F8 - 0x08025A68
const Gfx exclamation_box_outline_seg8_dl_080259F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(exclamation_box_outline_seg8_dl_08025968),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x08025A68
static const Lights1 exclamation_box_outline_seg8_lights_08025A68 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08025A80
ROM_ASSET_LOAD_TEXTURE(exclamation_box_outline_seg8_texture_08025A80, "actors/exclamation_box_outline/exclamation_point.rgba16.inc.c", 0x001f2200, 59076, 0x00025a80, 1024);

// 0x08025E80
ROM_ASSET_LOAD_VTX(exclamation_box_outline_seg8_vertex_08025E80, 0x001f2200, 59076, 0x00025e80, 64);

// 0x08025EC0 - 0x08025F08
const Gfx exclamation_box_outline_seg8_dl_08025EC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, exclamation_box_outline_seg8_texture_08025A80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&exclamation_box_outline_seg8_lights_08025A68.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_08025A68.a, 2),
    gsSPVertex(exclamation_box_outline_seg8_vertex_08025E80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x08025F08 - 0x08025F78
const Gfx exclamation_box_outline_seg8_dl_08025F08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(exclamation_box_outline_seg8_dl_08025EC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
