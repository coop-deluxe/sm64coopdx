#include "pc/rom_assets.h"
// Monty Mole

// Unreferenced light group
UNUSED static const Lights1 monty_mole_lights_unused1 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 monty_mole_lights_unused2 = gdSPDefLights1(
    0x30, 0x1f, 0x00,
    0xc3, 0x7e, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 monty_mole_lights_unused3 = gdSPDefLights1(
    0x05, 0x04, 0x05,
    0x16, 0x13, 0x14, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 monty_mole_lights_unused4 = gdSPDefLights1(
    0x07, 0x08, 0x07,
    0x1f, 0x20, 0x1f, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 monty_mole_lights_unused5 = gdSPDefLights1(
    0x14, 0x0b, 0x0a,
    0x53, 0x2e, 0x28, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 monty_mole_lights_unused6 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05000970
ROM_ASSET_LOAD_TEXTURE(monty_mole_seg5_texture_05000970, "actors/monty_mole/monty_mole_cheek.rgba16.inc.c", 0x001521d0, 57608, 0x00000970, 2048);

// 0x05001170
ROM_ASSET_LOAD_TEXTURE(monty_mole_seg5_texture_05001170, "actors/monty_mole/monty_mole_eye.rgba16.inc.c", 0x001521d0, 57608, 0x00001170, 2048);

// 0x05001970
ROM_ASSET_LOAD_TEXTURE(monty_mole_seg5_texture_05001970, "actors/monty_mole/monty_mole_nose.rgba16.inc.c", 0x001521d0, 57608, 0x00001970, 2048);

// 0x05002170
ROM_ASSET_LOAD_TEXTURE(monty_mole_seg5_texture_05002170, "actors/monty_mole/monty_mole_tooth.rgba16.inc.c", 0x001521d0, 57608, 0x00002170, 2048);

// 0x05002970
ROM_ASSET_LOAD_TEXTURE(monty_mole_seg5_texture_05002970, "actors/monty_mole/monty_mole_claw.rgba16.inc.c", 0x001521d0, 57608, 0x00002970, 2048);

// 0x05003170
static const Lights1 monty_mole_seg5_lights_05003170 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05003188
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003188, 0x001521d0, 57608, 0x00003188, 128);

// 0x05003208 - 0x050032A0
const Gfx monty_mole_seg5_dl_05003208[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05003170.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05003170.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_05003188, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  6,  3,  1, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 5,  6,  0, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x050032A0 - 0x05003300
const Gfx monty_mole_seg5_dl_050032A0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003208),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003300
static const Lights1 monty_mole_seg5_lights_05003300 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05003318
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003318, 0x001521d0, 57608, 0x00003318, 160);

// 0x050033B8
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_050033B8, 0x001521d0, 57608, 0x000033b8, 128);

// 0x05003438 - 0x050034A0
const Gfx monty_mole_seg5_dl_05003438[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05002970),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05003300.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05003300.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_05003318, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x050034A0 - 0x05003518
const Gfx monty_mole_seg5_dl_050034A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(monty_mole_seg5_vertex_050033B8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  6,  0, 0x0,  7,  6,  4, 0x0),
    gsSP2Triangles( 5,  7,  4, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 0,  7,  1, 0x0,  5,  1,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003518 - 0x05003598
const Gfx monty_mole_seg5_dl_05003518[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003438),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_050034A0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003598
static const Lights1 monty_mole_seg5_lights_05003598 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x050035B0
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_050035B0, 0x001521d0, 57608, 0x000035b0, 192);

// 0x05003670
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003670, 0x001521d0, 57608, 0x00003670, 192);

// 0x05003730 - 0x050037A8
const Gfx monty_mole_seg5_dl_05003730[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05002970),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05003598.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05003598.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_050035B0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0,  2, 11,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x050037A8 - 0x05003820
const Gfx monty_mole_seg5_dl_050037A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(monty_mole_seg5_vertex_05003670, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  3,  1, 0x0,  5,  4,  1, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  4,  6,  3, 0x0),
    gsSP2Triangles( 7,  4,  5, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003820 - 0x050038A0
const Gfx monty_mole_seg5_dl_05003820[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003730),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_050037A8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x050038A0
static const Lights1 monty_mole_seg5_lights_050038A0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x050038B8
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_050038B8, 0x001521d0, 57608, 0x000038b8, 128);

// 0x05003938 - 0x050039D0
const Gfx monty_mole_seg5_dl_05003938[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_050038A0.l, 1),
    gsSPLight(&monty_mole_seg5_lights_050038A0.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_050038B8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 3,  0,  6, 0x0,  4,  3,  7, 0x0),
    gsSP2Triangles( 4,  7,  5, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x050039D0 - 0x05003A30
const Gfx monty_mole_seg5_dl_050039D0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003938),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003A30
static const Lights1 monty_mole_seg5_lights_05003A30 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05003A48
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003A48, 0x001521d0, 57608, 0x00003a48, 160);

// 0x05003AE8
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003AE8, 0x001521d0, 57608, 0x00003ae8, 128);

// 0x05003B68 - 0x05003BD0
const Gfx monty_mole_seg5_dl_05003B68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05002970),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05003A30.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05003A30.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_05003A48, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003BD0 - 0x05003C48
const Gfx monty_mole_seg5_dl_05003BD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(monty_mole_seg5_vertex_05003AE8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 2,  3,  6, 0x0,  6,  4,  2, 0x0),
    gsSP2Triangles( 5,  7,  0, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 7,  3,  0, 0x0,  3,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003C48 - 0x05003CC8
const Gfx monty_mole_seg5_dl_05003C48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003B68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003BD0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003CC8
static const Lights1 monty_mole_seg5_lights_05003CC8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05003CE0
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003CE0, 0x001521d0, 57608, 0x00003ce0, 192);

// 0x05003DA0
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003DA0, 0x001521d0, 57608, 0x00003da0, 192);

// 0x05003E60 - 0x05003ED8
const Gfx monty_mole_seg5_dl_05003E60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05002970),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05003CC8.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05003CC8.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_05003CE0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  5, 11,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003ED8 - 0x05003F50
const Gfx monty_mole_seg5_dl_05003ED8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(monty_mole_seg5_vertex_05003DA0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 3,  2,  6, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  7,  2,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003F50 - 0x05003FD0
const Gfx monty_mole_seg5_dl_05003F50[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003E60),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05003ED8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003FD0
static const Lights1 monty_mole_seg5_lights_05003FD0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05003FE8
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05003FE8, 0x001521d0, 57608, 0x00003fe8, 208);

// 0x050040B8
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_050040B8, 0x001521d0, 57608, 0x000040b8, 256);

// 0x050041B8
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_050041B8, 0x001521d0, 57608, 0x000041b8, 256);

// 0x050042B8 - 0x05004368
const Gfx monty_mole_seg5_dl_050042B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05000970),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05003FD0.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05003FD0.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_05003FE8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 3,  6,  8, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  8, 0x0,  3,  1,  9, 0x0),
    gsSP2Triangles( 3,  9,  4, 0x0,  4, 10,  7, 0x0),
    gsSP2Triangles(10,  4,  9, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(12, 10,  9, 0x0, 11,  9,  1, 0x0),
    gsSP1Triangle(11,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004368 - 0x050044B0
const Gfx monty_mole_seg5_dl_05004368[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(monty_mole_seg5_vertex_050040B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  4,  3,  8, 0x0),
    gsSP2Triangles( 8,  7,  4, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0,  5,  9,  3, 0x0),
    gsSP2Triangles( 7,  1,  6, 0x0,  7, 11,  1, 0x0),
    gsSP2Triangles(12,  2,  1, 0x0, 12,  1, 11, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0, 13, 14, 0x0),
    gsSP2Triangles(15,  6,  0, 0x0, 15,  5,  6, 0x0),
    gsSPVertex(monty_mole_seg5_vertex_050041B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  0,  8,  5, 0x0),
    gsSP2Triangles( 2,  9, 10, 0x0, 10,  6,  2, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0, 11,  7,  6, 0x0),
    gsSP2Triangles( 7, 12,  8, 0x0, 13, 14, 11, 0x0),
    gsSP2Triangles(11,  9, 13, 0x0, 15, 14, 13, 0x0),
    gsSP2Triangles( 7, 14, 12, 0x0, 11, 14,  7, 0x0),
    gsSP1Triangle(15, 12, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x050044B0 - 0x05004518
const Gfx monty_mole_seg5_dl_050044B0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_050042B8),
    gsSPDisplayList(monty_mole_seg5_dl_05004368),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05004518
static const Lights1 monty_mole_seg5_lights_05004518 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004530
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004530, 0x001521d0, 57608, 0x00004530, 96);

// 0x05004590
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004590, 0x001521d0, 57608, 0x00004590, 256);

// 0x05004690
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004690, 0x001521d0, 57608, 0x00004690, 256);

// 0x05004790
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004790, 0x001521d0, 57608, 0x00004790, 160);

// 0x05004830
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004830, 0x001521d0, 57608, 0x00004830, 256);

// 0x05004930
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004930, 0x001521d0, 57608, 0x00004930, 64);

// 0x05004970
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004970, 0x001521d0, 57608, 0x00004970, 64);

// 0x050049B0 - 0x05004A10
const Gfx monty_mole_seg5_dl_050049B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001970),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05004518.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05004518.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_05004530, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  3,  5, 0x0,  5,  1,  0, 0x0),
    gsSP1Triangle( 2,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004A10 - 0x05004B50
const Gfx monty_mole_seg5_dl_05004A10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05001170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(monty_mole_seg5_vertex_05004590, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(12,  8, 13, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles(14,  9, 11, 0x0, 11, 12, 15, 0x0),
    gsSPVertex(monty_mole_seg5_vertex_05004690, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  8,  4, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0,  8, 11,  4, 0x0),
    gsSP2Triangles( 4, 11,  1, 0x0, 10,  4,  6, 0x0),
    gsSP2Triangles(12, 13,  3, 0x0,  7, 14, 11, 0x0),
    gsSP2Triangles( 1, 11, 14, 0x0,  7, 15, 14, 0x0),
    gsSPVertex(monty_mole_seg5_vertex_05004790, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 7,  5,  1, 0x0,  8,  6,  7, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0,  7,  1,  9, 0x0),
    gsSP1Triangle( 9,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004B50 - 0x05004BE0
const Gfx monty_mole_seg5_dl_05004B50[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05000970),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(monty_mole_seg5_vertex_05004830, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  3,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 11, 15, 14, 0x0),
    gsSPVertex(monty_mole_seg5_vertex_05004930, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004BE0 - 0x05004C00
const Gfx monty_mole_seg5_dl_05004BE0[] = {
    gsSPVertex(monty_mole_seg5_vertex_05004970, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004C00 - 0x05004C90
const Gfx monty_mole_seg5_dl_05004C00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_050049B0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05004A10),
    gsSPDisplayList(monty_mole_seg5_dl_05004B50),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(monty_mole_seg5_dl_05004BE0),
    gsSPEndDisplayList(),
};

// 0x05004C90
static const Lights1 monty_mole_seg5_lights_05004C90 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004CA8
ROM_ASSET_LOAD_VTX(monty_mole_seg5_vertex_05004CA8, 0x001521d0, 57608, 0x00004ca8, 64);

// 0x05004CE8 - 0x05004D30
const Gfx monty_mole_seg5_dl_05004CE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, monty_mole_seg5_texture_05002170),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&monty_mole_seg5_lights_05004C90.l, 1),
    gsSPLight(&monty_mole_seg5_lights_05004C90.a, 2),
    gsSPVertex(monty_mole_seg5_vertex_05004CA8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004D30 - 0x05004DA0
const Gfx monty_mole_seg5_dl_05004D30[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(monty_mole_seg5_dl_05004CE8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
