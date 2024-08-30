#include "pc/rom_assets.h"
// Lakitu Enemy

// Unreferenced light group
UNUSED static const Lights1 lakitu_enemy_lights_unused1 = gdSPDefLights1(
    0x33, 0x1f, 0x0c,
    0xcc, 0x7f, 0x33, 0x28, 0x28, 0x28
);

// 0x0500ECB0
static const Lights1 lakitu_enemy_seg5_lights_0500ECB0 = gdSPDefLights1(
    0x29, 0x13, 0x06,
    0xa5, 0x4f, 0x1b, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 lakitu_enemy_lights_unused2 = gdSPDefLights1(
    0x0d, 0x2c, 0x0b,
    0x34, 0xb2, 0x2c, 0x28, 0x28, 0x28
);

// Unreferenced texture
// 0x0500ECE0
ROM_ASSET_LOAD_TEXTURE(lakitu_enemy_seg5_texture_0500ECE0, "actors/lakitu_enemy/lakitu_enemy_cloud_face_unused.rgba16.inc.c", 0x00180bb0, 29674, 0x0000ece0, 2048);

// 0x0500F4E0
ROM_ASSET_LOAD_TEXTURE(lakitu_enemy_seg5_texture_0500F4E0, "actors/lakitu_enemy/lakitu_enemy_eyes_open.rgba16.inc.c", 0x00180bb0, 29674, 0x0000f4e0, 4096);

// 0x050104E0
ROM_ASSET_LOAD_TEXTURE(lakitu_enemy_seg5_texture_050104E0, "actors/lakitu_enemy/lakitu_enemy_eyes_closed.rgba16.inc.c", 0x00180bb0, 29674, 0x000104e0, 4096);

// 0x050114E0
ROM_ASSET_LOAD_TEXTURE(lakitu_enemy_seg5_texture_050114E0, "actors/lakitu_enemy/lakitu_enemy_shell.rgba16.inc.c", 0x00180bb0, 29674, 0x000114e0, 2048);

// 0x05011CE0
ROM_ASSET_LOAD_TEXTURE(lakitu_enemy_seg5_texture_05011CE0, "actors/lakitu_enemy/lakitu_enemy_frown.rgba16.inc.c", 0x00180bb0, 29674, 0x00011ce0, 2048);

// 0x050124E0
static const Lights1 lakitu_enemy_seg5_lights_050124E0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x050124F8
static const Lights1 lakitu_enemy_seg5_lights_050124F8 = gdSPDefLights1(
    0x79, 0x55, 0x00,
    0xf2, 0xab, 0x00, 0x28, 0x28, 0x28
);

// 0x05012510
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012510, 0x00180bb0, 29674, 0x00012510, 256);

// 0x05012610
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012610, 0x00180bb0, 29674, 0x00012610, 160);

// 0x050126B0
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_050126B0, 0x00180bb0, 29674, 0x000126b0, 176);

// 0x05012760 - 0x05012890
const Gfx lakitu_enemy_seg5_dl_05012760[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_enemy_seg5_texture_050114E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lakitu_enemy_seg5_lights_050124E0.l, 1),
    gsSPLight(&lakitu_enemy_seg5_lights_050124E0.a, 2),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012510, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  8,  7,  1, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0,  3,  5, 10, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0,  8,  1, 12, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0, 13, 11, 12, 0x0),
    gsSP2Triangles(13, 12,  0, 0x0, 14, 13,  0, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012610, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 4,  5,  7, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 8,  5,  6, 0x0,  8,  6,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x05012890 - 0x05012910
const Gfx lakitu_enemy_seg5_dl_05012890[] = {
    gsSPLight(&lakitu_enemy_seg5_lights_050124F8.l, 1),
    gsSPLight(&lakitu_enemy_seg5_lights_050124F8.a, 2),
    gsSPVertex(lakitu_enemy_seg5_vertex_050126B0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 5,  3,  2, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 7,  8,  1, 0x0,  9,  7,  0, 0x0),
    gsSP2Triangles( 1,  0,  7, 0x0,  8, 10,  1, 0x0),
    gsSP2Triangles( 1, 10,  5, 0x0,  0,  6,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x05012910 - 0x05012978
const Gfx lakitu_enemy_seg5_dl_05012910[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lakitu_enemy_seg5_dl_05012760),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(lakitu_enemy_seg5_dl_05012890),
    gsSPEndDisplayList(),
};

// 0x05012978
static const Lights1 lakitu_enemy_seg5_lights_05012978 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05012990
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012990, 0x00180bb0, 29674, 0x00012990, 256);

// 0x05012A90
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012A90, 0x00180bb0, 29674, 0x00012a90, 240);

// 0x05012B80
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012B80, 0x00180bb0, 29674, 0x00012b80, 256);

// 0x05012C80
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012C80, 0x00180bb0, 29674, 0x00012c80, 240);

// 0x05012D70
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012D70, 0x00180bb0, 29674, 0x00012d70, 256);

// 0x05012E70
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05012E70, 0x00180bb0, 29674, 0x00012e70, 128);

// 0x05012EF0 - 0x05013160
const Gfx lakitu_enemy_seg5_dl_05012EF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_enemy_seg5_texture_05011CE0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lakitu_enemy_seg5_lights_05012978.l, 1),
    gsSPLight(&lakitu_enemy_seg5_lights_05012978.a, 2),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012990, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 3,  5,  1, 0x0,  1,  6,  7, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  1,  0,  4, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 9,  7,  8, 0x0,  2,  7,  9, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0,  2, 11, 10, 0x0),
    gsSP2Triangles( 2, 12, 11, 0x0,  2,  9, 12, 0x0),
    gsSP2Triangles( 9, 13, 12, 0x0,  9,  8, 13, 0x0),
    gsSP2Triangles(14,  5,  3, 0x0,  5, 15,  6, 0x0),
    gsSP1Triangle( 5, 14, 15, 0x0),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  6,  0,  3, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 11,  6,  3, 0x0),
    gsSP2Triangles( 2, 11,  3, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012B80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  4,  6,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  7, 12,  8, 0x0),
    gsSP2Triangles(13,  8, 12, 0x0,  9,  8, 14, 0x0),
    gsSP1Triangle(15,  8, 13, 0x0),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012C80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  6,  4, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(14, 10, 13, 0x0),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012D70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 3,  7, 10, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles( 3, 10, 12, 0x0,  1, 14,  2, 0x0),
    gsSP1Triangle(13,  9, 15, 0x0),
    gsSPVertex(lakitu_enemy_seg5_vertex_05012E70, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05013160 - 0x050131C0
const Gfx lakitu_enemy_seg5_dl_05013160[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lakitu_enemy_seg5_dl_05012EF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x050131C0
static const Lights1 lakitu_enemy_seg5_lights_050131C0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x050131D8
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_050131D8, 0x00180bb0, 29674, 0x000131d8, 192);

// 0x05013298 - 0x050132D8
const Gfx lakitu_enemy_seg5_dl_05013298[] = {
    gsSPLight(&lakitu_enemy_seg5_lights_050131C0.l, 1),
    gsSPLight(&lakitu_enemy_seg5_lights_050131C0.a, 2),
    gsSPVertex(lakitu_enemy_seg5_vertex_050131D8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x050132D8 - 0x05013320
const Gfx lakitu_enemy_seg5_dl_050132D8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x05013320 - 0x05013350
const Gfx lakitu_enemy_seg5_dl_05013320[] = {
    gsSPDisplayList(lakitu_enemy_seg5_dl_05013298),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x05013350 - 0x05013378
const Gfx lakitu_enemy_seg5_dl_05013350[] = {
    gsSPDisplayList(lakitu_enemy_seg5_dl_050132D8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_enemy_seg5_texture_0500F4E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(lakitu_enemy_seg5_dl_05013320),
};

// 0x05013378 - 0x050133A0
const Gfx lakitu_enemy_seg5_dl_05013378[] = {
    gsSPDisplayList(lakitu_enemy_seg5_dl_050132D8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_enemy_seg5_texture_050104E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(lakitu_enemy_seg5_dl_05013320),
};

// 0x050133A0
static const Lights1 lakitu_enemy_seg5_lights_050133A0 = gdSPDefLights1(
    0x79, 0x55, 0x00,
    0xf2, 0xab, 0x00, 0x28, 0x28, 0x28
);

// 0x050133B8
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_050133B8, 0x00180bb0, 29674, 0x000133b8, 240);

// 0x050134A8 - 0x05013598
const Gfx lakitu_enemy_seg5_dl_050134A8[] = {
    gsSPLight(&lakitu_enemy_seg5_lights_050133A0.l, 1),
    gsSPLight(&lakitu_enemy_seg5_lights_050133A0.a, 2),
    gsSPVertex(lakitu_enemy_seg5_vertex_050133B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 6,  1,  3, 0x0,  1,  7,  3, 0x0),
    gsSP2Triangles( 8,  7,  0, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 0,  7,  1, 0x0,  9,  4,  8, 0x0),
    gsSP2Triangles( 4,  9,  5, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11,  8,  0, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0,  2, 12, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 12,  5, 0x0),
    gsSP2Triangles( 9, 10, 13, 0x0,  9, 13,  5, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0,  1, 14,  2, 0x0),
    gsSP2Triangles( 2, 14, 12, 0x0,  6, 14,  1, 0x0),
    gsSP2Triangles( 5, 14,  6, 0x0,  5, 12, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05013598
static const Lights1 lakitu_enemy_seg5_lights_05013598 = gdSPDefLights1(
    0x79, 0x55, 0x00,
    0xf2, 0xab, 0x00, 0x28, 0x28, 0x28
);

// 0x050135B0
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_050135B0, 0x00180bb0, 29674, 0x000135b0, 240);

// 0x050136A0 - 0x05013790
const Gfx lakitu_enemy_seg5_dl_050136A0[] = {
    gsSPLight(&lakitu_enemy_seg5_lights_05013598.l, 1),
    gsSPLight(&lakitu_enemy_seg5_lights_05013598.a, 2),
    gsSPVertex(lakitu_enemy_seg5_vertex_050135B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  4,  8, 0x0,  3,  8,  4, 0x0),
    gsSP2Triangles( 9,  7,  6, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles( 5,  7, 10, 0x0,  3,  5, 11, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  1,  6,  2, 0x0),
    gsSP2Triangles( 2,  6,  8, 0x0,  9,  6,  1, 0x0),
    gsSP2Triangles( 1, 12,  9, 0x0, 12, 10,  9, 0x0),
    gsSP2Triangles( 1,  0, 12, 0x0, 11, 13,  3, 0x0),
    gsSP2Triangles(14,  0,  2, 0x0, 14,  2,  8, 0x0),
    gsSP2Triangles( 3, 14,  8, 0x0, 13,  0,  3, 0x0),
    gsSP2Triangles( 3,  0, 14, 0x0,  0, 13, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 12, 13, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x05013790
ROM_ASSET_LOAD_VTX(lakitu_enemy_seg5_vertex_05013790, 0x00180bb0, 29674, 0x00013790, 208);

// 0x05013860 - 0x050138B0
const Gfx lakitu_enemy_seg5_dl_05013860[] = {
    gsSPLight(&lakitu_enemy_seg5_lights_0500ECB0.l, 1),
    gsSPLight(&lakitu_enemy_seg5_lights_0500ECB0.a, 2),
    gsSPVertex(lakitu_enemy_seg5_vertex_05013790, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0, 10, 11, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x050138B0 - 0x050138C0
const Gfx lakitu_enemy_seg5_dl_050138B0[] = {
    gsSPNumLights(NUMLIGHTS_1),
    gsSPEndDisplayList(),
};
