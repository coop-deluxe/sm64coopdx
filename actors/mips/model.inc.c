#include "pc/rom_assets.h"
// Mips

// 0x0600FB80
ROM_ASSET_LOAD_TEXTURE(mips_seg6_texture_0600FB80, "actors/mips/mips_eyes.rgba16.inc.c", 0x001d8310, 51422, 0x0000fc70, 2048);

// 0x06010380
static const Lights1 mips_seg6_lights_06010380 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06010398
static const Lights1 mips_seg6_lights_06010398 = gdSPDefLights1(
    0x0f, 0x0d, 0x04,
    0x27, 0x21, 0x0b, 0x28, 0x28, 0x28
);

// 0x060103B0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_060103B0, 0x001d8310, 51422, 0x000104a0, 256);

// 0x060104B0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_060104B0, 0x001d8310, 51422, 0x000105a0, 208);

// 0x06010580
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010580, 0x001d8310, 51422, 0x00010670, 64);

// 0x060105C0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_060105C0, 0x001d8310, 51422, 0x000106b0, 64);

// 0x06010600 - 0x06010748
const Gfx mips_seg6_dl_06010600[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06010380.l, 1),
    gsSPLight(&mips_seg6_lights_06010380.a, 2),
    gsSPVertex(mips_seg6_vertex_060103B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 2,  6,  5, 0x0,  2,  4,  6, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  3,  5, 0x0),
    gsSP2Triangles( 5,  9,  8, 0x0,  9,  5,  7, 0x0),
    gsSP2Triangles( 3, 10,  0, 0x0,  8, 10,  3, 0x0),
    gsSP2Triangles( 6, 11,  7, 0x0,  4, 11,  6, 0x0),
    gsSP2Triangles(12, 11,  4, 0x0,  4,  1, 12, 0x0),
    gsSP2Triangles( 8,  9, 13, 0x0, 14, 10,  8, 0x0),
    gsSP2Triangles( 8, 15, 14, 0x0, 13, 15,  8, 0x0),
    gsSPVertex(mips_seg6_vertex_060104B0, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  5,  6,  1, 0x0),
    gsSP2Triangles( 5,  1,  7, 0x0,  7,  1,  3, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  6,  9,  2, 0x0),
    gsSP2Triangles( 2,  9, 10, 0x0,  2, 10,  4, 0x0),
    gsSP2Triangles(11,  5,  7, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle( 6,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x06010748 - 0x060107B8
const Gfx mips_seg6_dl_06010748[] = {
    gsSPLight(&mips_seg6_lights_06010398.l, 1),
    gsSPLight(&mips_seg6_lights_06010398.a, 2),
    gsSPVertex(mips_seg6_vertex_06010580, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 3,  2,  1, 0x0),
    gsSPLight(&mips_seg6_lights_06010380.l, 1),
    gsSPLight(&mips_seg6_lights_06010380.a, 2),
    gsSPVertex(mips_seg6_vertex_060105C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  0, 0x0,  2,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x060107B8 - 0x06010820
const Gfx mips_seg6_dl_060107B8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06010600),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(mips_seg6_dl_06010748),
    gsSPEndDisplayList(),
};

// 0x06010820
static const Lights1 mips_seg6_lights_06010820 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06010838
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010838, 0x001d8310, 51422, 0x00010928, 240);

// 0x06010928
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010928, 0x001d8310, 51422, 0x00010a18, 240);

// 0x06010A18
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010A18, 0x001d8310, 51422, 0x00010b08, 128);

// 0x06010A98 - 0x06010C40
const Gfx mips_seg6_dl_06010A98[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06010820.l, 1),
    gsSPLight(&mips_seg6_lights_06010820.a, 2),
    gsSPVertex(mips_seg6_vertex_06010838, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0,  1,  6,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  7,  1,  5, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 5,  9,  6, 0x0,  8,  3,  6, 0x0),
    gsSP2Triangles( 7, 10,  6, 0x0,  5,  6, 10, 0x0),
    gsSP2Triangles( 8, 11,  3, 0x0, 11,  4,  3, 0x0),
    gsSP2Triangles( 9,  5, 12, 0x0,  8,  9, 13, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0, 11,  2,  4, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(mips_seg6_vertex_06010928, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles( 8, 13, 11, 0x0, 13,  8, 10, 0x0),
    gsSP2Triangles(13,  1,  3, 0x0, 10,  2, 13, 0x0),
    gsSP2Triangles( 3, 11, 13, 0x0,  2,  1, 13, 0x0),
    gsSP2Triangles(10,  9,  5, 0x0,  5,  4, 10, 0x0),
    gsSP2Triangles(10,  4,  2, 0x0,  5, 14,  7, 0x0),
    gsSP1Triangle(12, 14,  9, 0x0),
    gsSPVertex(mips_seg6_vertex_06010A18, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  2,  7,  3, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  3,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06010C40 - 0x06010CA0
const Gfx mips_seg6_dl_06010C40[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06010A98),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06010CA0
static const Lights1 mips_seg6_lights_06010CA0 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x06010CB8
static const Lights1 mips_seg6_lights_06010CB8 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06010CD0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010CD0, 0x001d8310, 51422, 0x00010dc0, 96);

// 0x06010D30
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010D30, 0x001d8310, 51422, 0x00010e20, 128);

// 0x06010DB0 - 0x06010E60
const Gfx mips_seg6_dl_06010DB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06010CA0.l, 1),
    gsSPLight(&mips_seg6_lights_06010CA0.a, 2),
    gsSPVertex(mips_seg6_vertex_06010CD0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  4,  0,  5, 0x0),
    gsSPLight(&mips_seg6_lights_06010CB8.l, 1),
    gsSPLight(&mips_seg6_lights_06010CB8.a, 2),
    gsSPVertex(mips_seg6_vertex_06010D30, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 0,  6,  3, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 2,  7,  4, 0x0,  7,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x06010E60 - 0x06010EC0
const Gfx mips_seg6_dl_06010E60[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06010DB0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06010EC0
static const Lights1 mips_seg6_lights_06010EC0 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x06010ED8
static const Lights1 mips_seg6_lights_06010ED8 = gdSPDefLights1(
    0x35, 0x38, 0x00,
    0x85, 0x8e, 0x00, 0x28, 0x28, 0x28
);

// 0x06010EF0
static const Lights1 mips_seg6_lights_06010EF0 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06010F08
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010F08, 0x001d8310, 51422, 0x00010ff8, 80);

// 0x06010F58
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010F58, 0x001d8310, 51422, 0x00011048, 48);

// 0x06010F88
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06010F88, 0x001d8310, 51422, 0x00011078, 112);

// 0x06010FF8 - 0x060110B0
const Gfx mips_seg6_dl_06010FF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06010EC0.l, 1),
    gsSPLight(&mips_seg6_lights_06010EC0.a, 2),
    gsSPVertex(mips_seg6_vertex_06010F08, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 3,  2,  4, 0x0),
    gsSPLight(&mips_seg6_lights_06010ED8.l, 1),
    gsSPLight(&mips_seg6_lights_06010ED8.a, 2),
    gsSPVertex(mips_seg6_vertex_06010F58, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&mips_seg6_lights_06010EF0.l, 1),
    gsSPLight(&mips_seg6_lights_06010EF0.a, 2),
    gsSPVertex(mips_seg6_vertex_06010F88, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0,  3,  6,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x060110B0 - 0x06011110
const Gfx mips_seg6_dl_060110B0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06010FF8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06011110
static const Lights1 mips_seg6_lights_06011110 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x06011128
static const Lights1 mips_seg6_lights_06011128 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06011140
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011140, 0x001d8310, 51422, 0x00011230, 96);

// 0x060111A0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_060111A0, 0x001d8310, 51422, 0x00011290, 160);

// 0x06011240 - 0x06011310
const Gfx mips_seg6_dl_06011240[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06011110.l, 1),
    gsSPLight(&mips_seg6_lights_06011110.a, 2),
    gsSPVertex(mips_seg6_vertex_06011140, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&mips_seg6_lights_06011128.l, 1),
    gsSPLight(&mips_seg6_lights_06011128.a, 2),
    gsSPVertex(mips_seg6_vertex_060111A0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  6,  1, 0x0),
    gsSP2Triangles( 1,  3,  5, 0x0,  2,  1,  6, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  5,  3,  4, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  8,  9,  5, 0x0),
    gsSP2Triangles( 9,  6,  5, 0x0,  9,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011310 - 0x06011370
const Gfx mips_seg6_dl_06011310[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06011240),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06011370
static const Lights1 mips_seg6_lights_06011370 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x06011388
static const Lights1 mips_seg6_lights_06011388 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060113A0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_060113A0, 0x001d8310, 51422, 0x00011490, 80);

// 0x060113F0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_060113F0, 0x001d8310, 51422, 0x000114e0, 128);

// 0x06011470 - 0x06011520
const Gfx mips_seg6_dl_06011470[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06011370.l, 1),
    gsSPLight(&mips_seg6_lights_06011370.a, 2),
    gsSPVertex(mips_seg6_vertex_060113A0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP1Triangle( 3,  4,  1, 0x0),
    gsSPLight(&mips_seg6_lights_06011388.l, 1),
    gsSPLight(&mips_seg6_lights_06011388.a, 2),
    gsSPVertex(mips_seg6_vertex_060113F0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  1,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  4,  7,  0, 0x0),
    gsSP1Triangle( 0,  2,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011520 - 0x06011580
const Gfx mips_seg6_dl_06011520[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06011470),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06011580
static const Lights1 mips_seg6_lights_06011580 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x06011598
static const Lights1 mips_seg6_lights_06011598 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060115B0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_060115B0, 0x001d8310, 51422, 0x000116a0, 96);

// 0x06011610
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011610, 0x001d8310, 51422, 0x00011700, 160);

// 0x060116B0 - 0x06011780
const Gfx mips_seg6_dl_060116B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06011580.l, 1),
    gsSPLight(&mips_seg6_lights_06011580.a, 2),
    gsSPVertex(mips_seg6_vertex_060115B0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  3,  1, 0x0,  2,  5,  0, 0x0),
    gsSPLight(&mips_seg6_lights_06011598.l, 1),
    gsSPLight(&mips_seg6_lights_06011598.a, 2),
    gsSPVertex(mips_seg6_vertex_06011610, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 2,  3,  0, 0x0,  3,  2,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  5,  6,  3, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles( 5,  2,  9, 0x0,  2,  1,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011780 - 0x060117E0
const Gfx mips_seg6_dl_06011780[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_060116B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x060117E0
static const Lights1 mips_seg6_lights_060117E0 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x060117F8
static const Lights1 mips_seg6_lights_060117F8 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06011810
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011810, 0x001d8310, 51422, 0x00011900, 80);

// 0x06011860
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011860, 0x001d8310, 51422, 0x00011950, 128);

// 0x060118E0 - 0x06011990
const Gfx mips_seg6_dl_060118E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_060117E0.l, 1),
    gsSPLight(&mips_seg6_lights_060117E0.a, 2),
    gsSPVertex(mips_seg6_vertex_06011810, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP1Triangle( 1,  4,  3, 0x0),
    gsSPLight(&mips_seg6_lights_060117F8.l, 1),
    gsSPLight(&mips_seg6_lights_060117F8.a, 2),
    gsSPVertex(mips_seg6_vertex_06011860, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 5,  4,  1, 0x0,  6,  5,  0, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  2,  7,  6, 0x0),
    gsSP1Triangle( 6,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011990 - 0x060119F0
const Gfx mips_seg6_dl_06011990[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_060118E0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x060119F0
static const Lights1 mips_seg6_lights_060119F0 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x06011A08
static const Lights1 mips_seg6_lights_06011A08 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06011A20
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011A20, 0x001d8310, 51422, 0x00011b10, 96);

// 0x06011A80
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011A80, 0x001d8310, 51422, 0x00011b70, 128);

// 0x06011B00 - 0x06011BB0
const Gfx mips_seg6_dl_06011B00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_060119F0.l, 1),
    gsSPLight(&mips_seg6_lights_060119F0.a, 2),
    gsSPVertex(mips_seg6_vertex_06011A20, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  2,  4, 0x0),
    gsSPLight(&mips_seg6_lights_06011A08.l, 1),
    gsSPLight(&mips_seg6_lights_06011A08.a, 2),
    gsSPVertex(mips_seg6_vertex_06011A80, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  1,  3,  6, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  6,  4,  1, 0x0),
    gsSP2Triangles( 4,  7,  5, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011BB0 - 0x06011C10
const Gfx mips_seg6_dl_06011BB0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06011B00),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06011C10
static const Lights1 mips_seg6_lights_06011C10 = gdSPDefLights1(
    0x3c, 0x3c, 0x00,
    0x96, 0x96, 0x00, 0x28, 0x28, 0x28
);

// 0x06011C28
static const Lights1 mips_seg6_lights_06011C28 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06011C40
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011C40, 0x001d8310, 51422, 0x00011d30, 96);

// 0x06011CA0
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011CA0, 0x001d8310, 51422, 0x00011d90, 112);

// 0x06011D10 - 0x06011DB0
const Gfx mips_seg6_dl_06011D10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mips_seg6_texture_0600FB80),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mips_seg6_lights_06011C10.l, 1),
    gsSPLight(&mips_seg6_lights_06011C10.a, 2),
    gsSPVertex(mips_seg6_vertex_06011C40, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&mips_seg6_lights_06011C28.l, 1),
    gsSPLight(&mips_seg6_lights_06011C28.a, 2),
    gsSPVertex(mips_seg6_vertex_06011CA0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  1,  3,  5, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  5,  6,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011DB0 - 0x06011E10
const Gfx mips_seg6_dl_06011DB0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mips_seg6_dl_06011D10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06011E10
static const Lights1 mips_seg6_lights_06011E10 = gdSPDefLights1(
    0x34, 0x2c, 0x0f,
    0x82, 0x6e, 0x26, 0x28, 0x28, 0x28
);

// 0x06011E28
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011E28, 0x001d8310, 51422, 0x00011f18, 96);

// 0x06011E88 - 0x06011ED8
const Gfx mips_seg6_dl_06011E88[] = {
    gsSPLight(&mips_seg6_lights_06011E10.l, 1),
    gsSPLight(&mips_seg6_lights_06011E10.a, 2),
    gsSPVertex(mips_seg6_vertex_06011E28, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  1,  4,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011ED8 - 0x06011EF8
const Gfx mips_seg6_dl_06011ED8[] = {
    gsDPPipeSync(),
    gsSPDisplayList(mips_seg6_dl_06011E88),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x06011EF8
static const Lights1 mips_seg6_lights_06011EF8 = gdSPDefLights1(
    0x34, 0x2c, 0x0f,
    0x82, 0x6e, 0x26, 0x28, 0x28, 0x28
);

// 0x06011F10
ROM_ASSET_LOAD_VTX(mips_seg6_vertex_06011F10, 0x001d8310, 51422, 0x00012000, 96);

// 0x06011F70 - 0x06011FC0
const Gfx mips_seg6_dl_06011F70[] = {
    gsSPLight(&mips_seg6_lights_06011EF8.l, 1),
    gsSPLight(&mips_seg6_lights_06011EF8.a, 2),
    gsSPVertex(mips_seg6_vertex_06011F10, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  4,  0,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011FC0 - 0x06011FE0
const Gfx mips_seg6_dl_06011FC0[] = {
    gsDPPipeSync(),
    gsSPDisplayList(mips_seg6_dl_06011F70),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
