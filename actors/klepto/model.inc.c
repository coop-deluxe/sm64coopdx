#include "pc/rom_assets.h"
// Possible Removed Actor File

// Bin ID? What is this?
UNUSED static const u64 klepto_unused_1 = 0;

// Klepto

// 0x05000008
ROM_ASSET_LOAD_TEXTURE(klepto_seg5_texture_05000008, "actors/klepto/klepto_chest_tuft.rgba16.inc.c", 0x00145e90, 48337, 0x00000008, 2048);

// 0x05000808
ROM_ASSET_LOAD_TEXTURE(klepto_seg5_texture_05000808, "actors/klepto/klepto_eye.rgba16.inc.c", 0x00145e90, 48337, 0x00000808, 2048);

// 0x05001008
ROM_ASSET_LOAD_TEXTURE(klepto_seg5_texture_05001008, "actors/klepto/klepto_beak.rgba16.inc.c", 0x00145e90, 48337, 0x00001008, 4096);

// 0x05002008
ROM_ASSET_LOAD_TEXTURE(klepto_seg5_texture_05002008, "actors/klepto/klepto_wing.rgba16.inc.c", 0x00145e90, 48337, 0x00002008, 4096);

// 0x05003008
ROM_ASSET_LOAD_TEXTURE(klepto_seg5_texture_05003008, "actors/klepto/klepto_wing_flap.rgba16.inc.c", 0x00145e90, 48337, 0x00003008, 2048);

// 0x05003808
static const Lights1 klepto_seg5_lights_05003808 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05003820
static const Lights1 klepto_seg5_lights_05003820 = gdSPDefLights1(
    0x3f, 0x1d, 0x08,
    0xff, 0x75, 0x21, 0x28, 0x28, 0x28
);

// 0x05003838
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05003838, 0x00145e90, 48337, 0x00003838, 96);

// 0x05003898
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05003898, 0x00145e90, 48337, 0x00003898, 240);

// 0x05003988
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05003988, 0x00145e90, 48337, 0x00003988, 48);

// 0x050039B8
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_050039B8, 0x00145e90, 48337, 0x000039b8, 176);

// 0x05003A68 - 0x05003AC0
const Gfx klepto_seg5_dl_05003A68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05000808),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05003808.l, 1),
    gsSPLight(&klepto_seg5_lights_05003808.a, 2),
    gsSPVertex(klepto_seg5_vertex_05003838, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  4,  5,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003AC0 - 0x05003B40
const Gfx klepto_seg5_dl_05003AC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05001008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(klepto_seg5_vertex_05003898, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(13, 14, 10, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 14,  8, 0x0),
    gsSPVertex(klepto_seg5_vertex_05003988, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003B40 - 0x05003BD0
const Gfx klepto_seg5_dl_05003B40[] = {
    gsSPLight(&klepto_seg5_lights_05003820.l, 1),
    gsSPLight(&klepto_seg5_lights_05003820.a, 2),
    gsSPVertex(klepto_seg5_vertex_050039B8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 3,  5,  2, 0x0,  2,  5,  7, 0x0),
    gsSP2Triangles( 7,  0,  2, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  8,  7,  5, 0x0),
    gsSP2Triangles(10,  8,  4, 0x0,  4,  8,  5, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 10,  4,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003BD0 - 0x05003C58
const Gfx klepto_seg5_dl_05003BD0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05003A68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05003AC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(klepto_seg5_dl_05003B40),
    gsSPEndDisplayList(),
};

// 0x05003C58
static const Lights1 klepto_seg5_lights_05003C58 = gdSPDefLights1(
    0x3f, 0x1d, 0x08,
    0xff, 0x75, 0x21, 0x28, 0x28, 0x28
);

// 0x05003C70
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05003C70, 0x00145e90, 48337, 0x00003c70, 144);

// 0x05003D00 - 0x05003D80
const Gfx klepto_seg5_dl_05003D00[] = {
    gsSPLight(&klepto_seg5_lights_05003C58.l, 1),
    gsSPLight(&klepto_seg5_lights_05003C58.a, 2),
    gsSPVertex(klepto_seg5_vertex_05003C70, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  2,  4,  3, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  6,  0,  3, 0x0),
    gsSP2Triangles( 3,  7,  6, 0x0,  4,  7,  3, 0x0),
    gsSP2Triangles( 7,  4,  5, 0x0,  1,  8,  5, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  8,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003D80 - 0x05003DB0
const Gfx klepto_seg5_dl_05003D80[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(klepto_seg5_dl_05003D00),
    gsSPEndDisplayList(),
};

// 0x05003DB0
static const Lights1 klepto_seg5_lights_05003DB0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05003DC8
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05003DC8, 0x00145e90, 48337, 0x00003dc8, 160);

// 0x05003E68 - 0x05003F20
const Gfx klepto_seg5_dl_05003E68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05000008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05003DB0.l, 1),
    gsSPLight(&klepto_seg5_lights_05003DB0.a, 2),
    gsSPVertex(klepto_seg5_vertex_05003DC8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 1,  6,  5, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 1,  0,  9, 0x0,  6,  1,  9, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 8,  9,  4, 0x0,  0,  4,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003F20 - 0x05003F80
const Gfx klepto_seg5_dl_05003F20[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05003E68),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003F80
static const Lights1 klepto_seg5_lights_05003F80 = gdSPDefLights1(
    0x07, 0x01, 0x01,
    0x1e, 0x05, 0x04, 0x28, 0x28, 0x28
);

// 0x05003F98
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05003F98, 0x00145e90, 48337, 0x00003f98, 192);

// 0x05004058 - 0x05004118
const Gfx klepto_seg5_dl_05004058[] = {
    gsSPLight(&klepto_seg5_lights_05003F80.l, 1),
    gsSPLight(&klepto_seg5_lights_05003F80.a, 2),
    gsSPVertex(klepto_seg5_vertex_05003F98, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 4,  7,  5, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 8,  1,  0, 0x0,  8,  0,  6, 0x0),
    gsSP2Triangles( 7,  4,  9, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  8, 11, 10, 0x0),
    gsSP2Triangles( 6, 11,  8, 0x0,  3,  1,  8, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0,  7, 11,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004118 - 0x05004148
const Gfx klepto_seg5_dl_05004118[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(klepto_seg5_dl_05004058),
    gsSPEndDisplayList(),
};

// 0x05004148
static const Lights1 klepto_seg5_lights_05004148 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004160
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004160, 0x00145e90, 48337, 0x00004160, 64);

// 0x050041A0 - 0x050041E8
const Gfx klepto_seg5_dl_050041A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05003008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05004148.l, 1),
    gsSPLight(&klepto_seg5_lights_05004148.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004160, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x050041E8 - 0x05004258
const Gfx klepto_seg5_dl_050041E8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_050041A0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05004258
static const Lights1 klepto_seg5_lights_05004258 = gdSPDefLights1(
    0x3f, 0x1d, 0x08,
    0xff, 0x75, 0x21, 0x28, 0x28, 0x28
);

// 0x05004270
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004270, 0x00145e90, 48337, 0x00004270, 96);

// 0x050042D0 - 0x05004330
const Gfx klepto_seg5_dl_050042D0[] = {
    gsSPLight(&klepto_seg5_lights_05004258.l, 1),
    gsSPLight(&klepto_seg5_lights_05004258.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004270, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  0,  4,  3, 0x0),
    gsSP2Triangles( 5,  1,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 5,  4,  2, 0x0,  4,  5,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004330 - 0x05004360
const Gfx klepto_seg5_dl_05004330[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(klepto_seg5_dl_050042D0),
    gsSPEndDisplayList(),
};

// 0x05004360
static const Lights1 klepto_seg5_lights_05004360 = gdSPDefLights1(
    0x3f, 0x1d, 0x08,
    0xff, 0x75, 0x21, 0x28, 0x28, 0x28
);

// 0x05004378
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004378, 0x00145e90, 48337, 0x00004270, 96);

// 0x050043D8 - 0x05004438
const Gfx klepto_seg5_dl_050043D8[] = {
    gsSPLight(&klepto_seg5_lights_05004360.l, 1),
    gsSPLight(&klepto_seg5_lights_05004360.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004378, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  0,  4,  3, 0x0),
    gsSP2Triangles( 5,  1,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 5,  4,  2, 0x0,  4,  5,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004438 - 0x05004468
const Gfx klepto_seg5_dl_05004438[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(klepto_seg5_dl_050043D8),
    gsSPEndDisplayList(),
};

// 0x05004468
static const Lights1 klepto_seg5_lights_05004468 = gdSPDefLights1(
    0x02, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05004480
static const Lights1 klepto_seg5_lights_05004480 = gdSPDefLights1(
    0x3f, 0x1d, 0x08,
    0xff, 0x75, 0x21, 0x28, 0x28, 0x28
);

// 0x05004498
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004498, 0x00145e90, 48337, 0x00004498, 192);

// 0x05004558
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004558, 0x00145e90, 48337, 0x00004558, 240);

// 0x05004648
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004648, 0x00145e90, 48337, 0x00004648, 80);

// 0x05004698 - 0x050047C8
const Gfx klepto_seg5_dl_05004698[] = {
    gsSPLight(&klepto_seg5_lights_05004468.l, 1),
    gsSPLight(&klepto_seg5_lights_05004468.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004498, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  0, 11,  1, 0x0),
    gsSP1Triangle(11,  0,  2, 0x0),
    gsSPLight(&klepto_seg5_lights_05004480.l, 1),
    gsSPLight(&klepto_seg5_lights_05004480.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004558, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  6,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(12,  9,  8, 0x0, 12, 11,  9, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles( 1,  0, 13, 0x0, 13,  2, 14, 0x0),
    gsSP1Triangle(14,  2,  1, 0x0),
    gsSPVertex(klepto_seg5_vertex_05004648, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  4,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  3,  0,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x050047C8 - 0x050047F8
const Gfx klepto_seg5_dl_050047C8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(klepto_seg5_dl_05004698),
    gsSPEndDisplayList(),
};

// 0x050047F8
static const Lights1 klepto_seg5_lights_050047F8 = gdSPDefLights1(
    0x02, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05004810
static const Lights1 klepto_seg5_lights_05004810 = gdSPDefLights1(
    0x3f, 0x1d, 0x08,
    0xff, 0x75, 0x21, 0x28, 0x28, 0x28
);

// 0x05004828
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004828, 0x00145e90, 48337, 0x00004498, 192);

// 0x050048E8
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_050048E8, 0x00145e90, 48337, 0x00004558, 240);

// 0x050049D8
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_050049D8, 0x00145e90, 48337, 0x00004648, 80);

// 0x05004A28 - 0x05004B58
const Gfx klepto_seg5_dl_05004A28[] = {
    gsSPLight(&klepto_seg5_lights_050047F8.l, 1),
    gsSPLight(&klepto_seg5_lights_050047F8.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004828, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  0, 11,  1, 0x0),
    gsSP1Triangle(11,  0,  2, 0x0),
    gsSPLight(&klepto_seg5_lights_05004810.l, 1),
    gsSPLight(&klepto_seg5_lights_05004810.a, 2),
    gsSPVertex(klepto_seg5_vertex_050048E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  6,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(12,  9,  8, 0x0, 12, 11,  9, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles( 1,  0, 13, 0x0, 13,  2, 14, 0x0),
    gsSP1Triangle(14,  2,  1, 0x0),
    gsSPVertex(klepto_seg5_vertex_050049D8, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  4,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  3,  0,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004B58 - 0x05004B88
const Gfx klepto_seg5_dl_05004B58[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(klepto_seg5_dl_05004A28),
    gsSPEndDisplayList(),
};

// 0x05004B88
static const Lights1 klepto_seg5_lights_05004B88 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004BA0
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004BA0, 0x00145e90, 48337, 0x00004ba0, 64);

// 0x05004BE0 - 0x05004C28
const Gfx klepto_seg5_dl_05004BE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05002008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05004B88.l, 1),
    gsSPLight(&klepto_seg5_lights_05004B88.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004BA0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004C28 - 0x05004C98
const Gfx klepto_seg5_dl_05004C28[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05004BE0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05004C98
static const Lights1 klepto_seg5_lights_05004C98 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004CB0
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004CB0, 0x00145e90, 48337, 0x00004cb0, 64);

// 0x05004CF0 - 0x05004D38
const Gfx klepto_seg5_dl_05004CF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05002008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05004C98.l, 1),
    gsSPLight(&klepto_seg5_lights_05004C98.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004CB0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004D38 - 0x05004DA8
const Gfx klepto_seg5_dl_05004D38[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05004CF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05004DA8
static const Lights1 klepto_seg5_lights_05004DA8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004DC0
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004DC0, 0x00145e90, 48337, 0x00004dc0, 64);

// 0x05004E00 - 0x05004E48
const Gfx klepto_seg5_dl_05004E00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05002008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05004DA8.l, 1),
    gsSPLight(&klepto_seg5_lights_05004DA8.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004DC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004E48 - 0x05004EB8
const Gfx klepto_seg5_dl_05004E48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05004E00),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05004EB8
static const Lights1 klepto_seg5_lights_05004EB8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004ED0
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004ED0, 0x00145e90, 48337, 0x00004ed0, 64);

// 0x05004F10 - 0x05004F58
const Gfx klepto_seg5_dl_05004F10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05002008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05004EB8.l, 1),
    gsSPLight(&klepto_seg5_lights_05004EB8.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004ED0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004F58 - 0x05004FC8
const Gfx klepto_seg5_dl_05004F58[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05004F10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05004FC8
static const Lights1 klepto_seg5_lights_05004FC8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004FE0
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_05004FE0, 0x00145e90, 48337, 0x00004fe0, 64);

// 0x05005020 - 0x05005068
const Gfx klepto_seg5_dl_05005020[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05002008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_05004FC8.l, 1),
    gsSPLight(&klepto_seg5_lights_05004FC8.a, 2),
    gsSPVertex(klepto_seg5_vertex_05004FE0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005068 - 0x050050D8
const Gfx klepto_seg5_dl_05005068[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05005020),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x050050D8
static const Lights1 klepto_seg5_lights_050050D8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x050050F0
ROM_ASSET_LOAD_VTX(klepto_seg5_vertex_050050F0, 0x00145e90, 48337, 0x000050f0, 64);

// 0x05005130 - 0x05005178
const Gfx klepto_seg5_dl_05005130[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, klepto_seg5_texture_05002008),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&klepto_seg5_lights_050050D8.l, 1),
    gsSPLight(&klepto_seg5_lights_050050D8.a, 2),
    gsSPVertex(klepto_seg5_vertex_050050F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005178 - 0x050051E8
const Gfx klepto_seg5_dl_05005178[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(klepto_seg5_dl_05005130),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
