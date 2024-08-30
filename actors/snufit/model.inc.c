#include "pc/rom_assets.h"
// Snufit

// 0x060070E0
ROM_ASSET_LOAD_TEXTURE(snufit_seg6_texture_060070E0, "actors/snufit/snufit_body.rgba16.inc.c", 0x001e7ee0, 40011, 0x000070e0, 2048);

// 0x060078E0
ROM_ASSET_LOAD_TEXTURE(snufit_seg6_texture_060078E0, "actors/snufit/snufit_eye.rgba16.inc.c", 0x001e7ee0, 40011, 0x000078e0, 2048);

// 0x060080E0
ROM_ASSET_LOAD_TEXTURE(snufit_seg6_texture_060080E0, "actors/snufit/snufit_mask_strap.rgba16.inc.c", 0x001e7ee0, 40011, 0x000080e0, 1024);

// 0x060084E0
ROM_ASSET_LOAD_TEXTURE(snufit_seg6_texture_060084E0, "actors/snufit/snufit_mouth.rgba16.inc.c", 0x001e7ee0, 40011, 0x000084e0, 2048);

// 0x06008CE0
static const Lights1 snufit_seg6_lights_06008CE0 = gdSPDefLights1(
    0x47, 0x47, 0x47,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x06008CF8
static const Lights1 snufit_seg6_lights_06008CF8 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06008D10
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06008D10, 0x001e7ee0, 40011, 0x00008d10, 224);

// 0x06008DF0
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06008DF0, 0x001e7ee0, 40011, 0x00008df0, 192);

// 0x06008EB0
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06008EB0, 0x001e7ee0, 40011, 0x00008eb0, 224);

// 0x06008F90
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06008F90, 0x001e7ee0, 40011, 0x00008f90, 224);

// 0x06009070
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06009070, 0x001e7ee0, 40011, 0x00009070, 256);

// 0x06009170
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06009170, 0x001e7ee0, 40011, 0x00009170, 112);

// 0x060091E0 - 0x06009278
const Gfx snufit_seg6_dl_060091E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snufit_seg6_texture_060080E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&snufit_seg6_lights_06008CE0.l, 1),
    gsSPLight(&snufit_seg6_lights_06008CE0.a, 2),
    gsSPVertex(snufit_seg6_vertex_06008D10, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 4,  2,  6, 0x0,  3,  7,  5, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles(10,  8,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 10, 11, 0x0, 12, 11, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x06009278 - 0x060092F0
const Gfx snufit_seg6_dl_06009278[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snufit_seg6_texture_060078E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&snufit_seg6_lights_06008CF8.l, 1),
    gsSPLight(&snufit_seg6_lights_06008CF8.a, 2),
    gsSPVertex(snufit_seg6_vertex_06008DF0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x060092F0 - 0x06009498
const Gfx snufit_seg6_dl_060092F0[] = {
    gsSPVertex(snufit_seg6_vertex_06008EB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  2, 0x0,  8,  3,  2, 0x0),
    gsSP2Triangles( 6,  5,  9, 0x0,  5, 10,  9, 0x0),
    gsSP2Triangles( 5,  4, 10, 0x0,  6,  9, 11, 0x0),
    gsSP2Triangles(11,  9, 12, 0x0,  9, 10, 13, 0x0),
    gsSPVertex(snufit_seg6_vertex_06008F90, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  6,  0,  8, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 8,  2, 10, 0x0,  8,  0,  2, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(10,  2, 12, 0x0,  2,  1, 12, 0x0),
    gsSP1Triangle( 1, 13, 12, 0x0),
    gsSPVertex(snufit_seg6_vertex_06009070, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  4, 13,  6, 0x0),
    gsSP2Triangles( 4,  2, 13, 0x0,  6, 14,  8, 0x0),
    gsSP2Triangles( 6, 13, 14, 0x0,  8, 14, 15, 0x0),
    gsSPVertex(snufit_seg6_vertex_06009170, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  3,  5, 0x0),
    gsSP1Triangle( 2,  1,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06009498 - 0x06009530
const Gfx snufit_seg6_dl_06009498[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBA, G_CC_BLENDRGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snufit_seg6_dl_060091E0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snufit_seg6_dl_06009278),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(snufit_seg6_dl_060092F0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x06009530
static const Lights1 snufit_seg6_lights_06009530 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06009548
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06009548, 0x001e7ee0, 40011, 0x00009548, 192);

// 0x06009608
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06009608, 0x001e7ee0, 40011, 0x00009608, 96);

// 0x06009668 - 0x06009700
const Gfx snufit_seg6_dl_06009668[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snufit_seg6_texture_060080E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&snufit_seg6_lights_06009530.l, 1),
    gsSPLight(&snufit_seg6_lights_06009530.a, 2),
    gsSPVertex(snufit_seg6_vertex_06009548, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  1,  7,  5, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles(10,  8,  9, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0,  7, 11,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06009700 - 0x06009748
const Gfx snufit_seg6_dl_06009700[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snufit_seg6_texture_060084E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snufit_seg6_vertex_06009608, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06009748 - 0x060097C8
const Gfx snufit_seg6_dl_06009748[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snufit_seg6_dl_06009668),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snufit_seg6_dl_06009700),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x060097C8
static const Lights1 snufit_seg6_lights_060097C8 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060097E0
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_060097E0, 0x001e7ee0, 40011, 0x000097e0, 192);

// 0x060098A0 - 0x06009938
const Gfx snufit_seg6_dl_060098A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snufit_seg6_texture_060080E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&snufit_seg6_lights_060097C8.l, 1),
    gsSPLight(&snufit_seg6_lights_060097C8.a, 2),
    gsSPVertex(snufit_seg6_vertex_060097E0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 10,  0,  7, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0,  5,  9,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06009938 - 0x06009998
const Gfx snufit_seg6_dl_06009938[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snufit_seg6_dl_060098A0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06009998
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06009998, 0x001e7ee0, 40011, 0x00009998, 64);

// 0x060099D8 - 0x06009A10
const Gfx snufit_seg6_dl_060099D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snufit_seg6_texture_060070E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snufit_seg6_vertex_06009998, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06009A10 - 0x06009A80
const Gfx snufit_seg6_dl_06009A10[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snufit_seg6_dl_060099D8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06009A80
static const Lights1 snufit_seg6_lights_06009A80 = gdSPDefLights1(
    0x65, 0x08, 0x08,
    0xfe, 0x14, 0x14, 0x28, 0x28, 0x28
);

// 0x06009A98
ROM_ASSET_LOAD_VTX(snufit_seg6_vertex_06009A98, 0x001e7ee0, 40011, 0x00009a98, 128);

// 0x06009B18 - 0x06009B68
const Gfx snufit_seg6_dl_06009B18[] = {
    gsSPLight(&snufit_seg6_lights_06009A80.l, 1),
    gsSPLight(&snufit_seg6_lights_06009A80.a, 2),
    gsSPVertex(snufit_seg6_vertex_06009A98, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  6,  7,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x06009B68 - 0x06009B98
const Gfx snufit_seg6_dl_06009B68[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(snufit_seg6_dl_06009B18),
    gsSPEndDisplayList(),
};
