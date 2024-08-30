#include "pc/rom_assets.h"
// Bobomb

// 0x0801DA60
ROM_ASSET_LOAD_TEXTURE(bobomb_seg8_texture_0801DA60, "actors/bobomb/bob-omb_left_side.rgba16.inc.c", 0x001f2200, 59076, 0x0001da60, 4096);

// 0x0801EA60
ROM_ASSET_LOAD_TEXTURE(bobomb_seg8_texture_0801EA60, "actors/bobomb/bob-omb_right_side.rgba16.inc.c", 0x001f2200, 59076, 0x0001ea60, 4096);

// 0x0801FA60
ROM_ASSET_LOAD_TEXTURE(bobomb_seg8_texture_0801FA60, "actors/bobomb/bob-omb_buddy_left_side.rgba16.inc.c", 0x00134d20, 26785, 0x00000078, 4096);

// 0x08020A60
ROM_ASSET_LOAD_TEXTURE(bobomb_seg8_texture_08020A60, "actors/bobomb/bob-omb_buddy_right_side.rgba16.inc.c", 0x00134d20, 26785, 0x00001078, 4096);

// 0x08021A60
ROM_ASSET_LOAD_TEXTURE(bobomb_seg8_texture_08021A60, "actors/bobomb/bob-omb_eyes.rgba16.inc.c", 0x00134d20, 26785, 0x00004878, 2048);

// 0x08022260
ROM_ASSET_LOAD_TEXTURE(bobomb_seg8_texture_08022260, "actors/bobomb/bob-omb_eyes_blink.rgba16.inc.c", 0x00134d20, 26785, 0x00005078, 2048);

// 0x08022A60
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08022A60, 0x001f2200, 59076, 0x00022a60, 96);

// 0x08022AC0 - 0x08022B08
const Gfx bobomb_seg8_dl_08022AC0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x08022B08 - 0x08022B58
const Gfx bobomb_seg8_dl_08022B08[] = {
    gsSPVertex(bobomb_seg8_vertex_08022A60, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  3,  5,  1, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08022B58 - 0x08022B88
const Gfx bobomb_seg8_dl_08022B58[] = {
    gsSPDisplayList(bobomb_seg8_dl_08022AC0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_08021A60),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(bobomb_seg8_dl_08022B08),
    gsSPEndDisplayList(),
};

// 0x08022B88 - 0x08022BB8
const Gfx bobomb_seg8_dl_08022B88[] = {
    gsSPDisplayList(bobomb_seg8_dl_08022AC0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_08022260),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(bobomb_seg8_dl_08022B08),
    gsSPEndDisplayList(),
};

// 0x08022BB8
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08022BB8, 0x001f2200, 59076, 0x00022bb8, 64);

// 0x08022BF8
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08022BF8, 0x001f2200, 59076, 0x00022bf8, 64);

// 0x08022C38 - 0x08022CA0
const Gfx bobomb_seg8_dl_08022C38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_0801DA60),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bobomb_seg8_vertex_08022BB8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_0801EA60),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bobomb_seg8_vertex_08022BF8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08022CA0 - 0x08022D08
const Gfx bobomb_seg8_dl_08022CA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_0801FA60),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bobomb_seg8_vertex_08022BB8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_08020A60),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bobomb_seg8_vertex_08022BF8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08022D08 - 0x08022D78
const Gfx bobomb_seg8_dl_08022D08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bobomb_seg8_dl_08022C38),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08022D78 - 0x08022DE8
const Gfx bobomb_seg8_dl_08022D78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bobomb_seg8_dl_08022CA0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08022DE8
static const Lights1 bobomb_seg8_lights_08022DE8 = gdSPDefLights1(
    0x3f, 0x26, 0x04,
    0xff, 0x99, 0x12, 0x28, 0x28, 0x28
);

// 0x08022E00
static const Lights1 bobomb_seg8_lights_08022E00 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// Unreferenced light group
static const Lights1 bobomb_lights_unused = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x08022E30
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08022E30, 0x001f2200, 59076, 0x00022e30, 256);

// 0x08022F30
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08022F30, 0x001f2200, 59076, 0x00022f30, 64);

// 0x08022F70
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08022F70, 0x001f2200, 59076, 0x00022f70, 256);

// 0x08023070
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08023070, 0x001f2200, 59076, 0x00023070, 64);

// 0x080230B0
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_080230B0, 0x001f2200, 59076, 0x000230b0, 224);

// 0x08023190
ROM_ASSET_LOAD_VTX(bobomb_seg8_vertex_08023190, 0x001f2200, 59076, 0x00023190, 224);

// 0x08023270 - 0x08023378
const Gfx bobomb_seg8_dl_08023270[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPLight(&bobomb_seg8_lights_08022DE8.l, 1),
    gsSPLight(&bobomb_seg8_lights_08022DE8.a, 2),
    gsSPVertex(bobomb_seg8_vertex_08022E30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(11,  8,  7, 0x0,  6, 13, 14, 0x0),
    gsSP2Triangles( 6, 14,  3, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles( 9, 12,  1, 0x0, 10,  9, 15, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0,  2, 12, 11, 0x0),
    gsSP2Triangles(10,  6,  5, 0x0, 10,  5,  7, 0x0),
    gsSP2Triangles( 0, 14, 13, 0x0,  0, 13, 15, 0x0),
    gsSP2Triangles(11,  4,  3, 0x0, 11,  3,  2, 0x0),
    gsSP2Triangles( 2,  3, 14, 0x0,  2, 14,  0, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  7,  4, 11, 0x0),
    gsSP2Triangles(15, 13,  6, 0x0, 15,  6, 10, 0x0),
    gsSPVertex(bobomb_seg8_vertex_08022F30, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x08023378 - 0x08023480
const Gfx bobomb_seg8_dl_08023378[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPLight(&bobomb_seg8_lights_08022DE8.l, 1),
    gsSPLight(&bobomb_seg8_lights_08022DE8.a, 2),
    gsSPVertex(bobomb_seg8_vertex_08022F70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  6, 13, 14, 0x0),
    gsSP2Triangles( 6, 14,  3, 0x0,  1, 11,  9, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0, 15,  8,  7, 0x0),
    gsSP2Triangles(12, 11,  1, 0x0, 12,  1,  0, 0x0),
    gsSP2Triangles(10,  4,  3, 0x0, 10,  3,  7, 0x0),
    gsSP2Triangles(15, 14, 13, 0x0, 15, 13,  2, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  0,  5, 12, 0x0),
    gsSP2Triangles( 2, 13,  6, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles(12,  5,  4, 0x0, 12,  4, 10, 0x0),
    gsSP2Triangles( 7,  3, 14, 0x0,  7, 14, 15, 0x0),
    gsSPVertex(bobomb_seg8_vertex_08023070, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x08023480 - 0x08023528
const Gfx bobomb_seg8_dl_08023480[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPLight(&bobomb_seg8_lights_08022E00.l, 1),
    gsSPLight(&bobomb_seg8_lights_08022E00.a, 2),
    gsSPVertex(bobomb_seg8_vertex_080230B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bobomb_seg8_vertex_08023190, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8, 12, 13, 0x0),
    gsSPEndDisplayList(),
};
