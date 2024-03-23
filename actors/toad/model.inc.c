#include "pc/rom_assets.h"
// Toad

// 0x06005908
static const Lights1 toad_seg6_lights_06005908 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06005920
ROM_ASSET_LOAD_TEXTURE(toad_seg6_texture_06005920, "actors/toad/toad_face.rgba16.inc.c", 0x001d8310, 51422, 0x00005920, 2048);

// 0x06006120
ROM_ASSET_LOAD_TEXTURE(toad_seg6_texture_06006120, "actors/toad/toad_head.rgba16.inc.c", 0x001d8310, 51422, 0x00006120, 2048);

// 0x06006920
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006920, 0x001d8310, 51422, 0x00006920, 240);

// 0x06006A10
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006A10, 0x001d8310, 51422, 0x00006a10, 256);

// 0x06006B10
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006B10, 0x001d8310, 51422, 0x00006b10, 192);

// 0x06006BD0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006BD0, 0x001d8310, 51422, 0x00006bd0, 240);

// 0x06006CC0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006CC0, 0x001d8310, 51422, 0x00006cc0, 256);

// 0x06006DC0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006DC0, 0x001d8310, 51422, 0x00006dc0, 256);

// 0x06006EC0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006EC0, 0x001d8310, 51422, 0x00006ec0, 240);

// 0x06006FB0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06006FB0, 0x001d8310, 51422, 0x00006fb0, 256);

// 0x060070B0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_060070B0, 0x001d8310, 51422, 0x000070b0, 256);

// 0x060071B0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_060071B0, 0x001d8310, 51422, 0x000071b0, 80);

// 0x06007200
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06007200, 0x001d8310, 51422, 0x00007200, 256);

// 0x06007300 - 0x06007498
const Gfx toad_seg6_dl_06007300[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, toad_seg6_texture_06005920),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&toad_seg6_lights_06005908.l, 1),
    gsSPLight(&toad_seg6_lights_06005908.a, 2),
    gsSPVertex(toad_seg6_vertex_06006920, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  6,  1,  0, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  3,  7,  5, 0x0),
    gsSP2Triangles( 1,  6,  8, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 7,  9,  6, 0x0, 10,  9,  7, 0x0),
    gsSP2Triangles( 3, 11,  7, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles( 8, 12,  1, 0x0, 13, 14,  8, 0x0),
    gsSP2Triangles( 9, 13,  8, 0x0, 12,  8, 14, 0x0),
    gsSPVertex(toad_seg6_vertex_06006A10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles(13, 11,  1, 0x0,  1, 12,  2, 0x0),
    gsSP2Triangles(13,  1,  0, 0x0,  2, 12, 14, 0x0),
    gsSP1Triangle( 2, 14, 15, 0x0),
    gsSPVertex(toad_seg6_vertex_06006B10, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 2,  3,  7, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 5,  2,  8, 0x0,  8,  2,  7, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0,  6,  5,  8, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 10,  8,  9, 0x0),
    gsSP1Triangle(10,  9, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06007498 - 0x060076C0
const Gfx toad_seg6_dl_06007498[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, toad_seg6_texture_06006120),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(toad_seg6_vertex_06006BD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 3,  2,  6, 0x0,  6,  2,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles( 8, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(toad_seg6_vertex_06006CC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 10,  7, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 13, 12, 11, 0x0),
    gsSP2Triangles(14,  1,  0, 0x0, 15, 14,  0, 0x0),
    gsSPVertex(toad_seg6_vertex_06006DC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(12,  4,  3, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(toad_seg6_vertex_06006EC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  7,  8, 0x0, 11, 10, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(toad_seg6_vertex_06006FB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(toad_seg6_vertex_060070B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0,  9, 13, 10, 0x0),
    gsSP2Triangles(14, 13,  9, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(toad_seg6_vertex_060071B0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  3,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x060076C0 - 0x06007710
const Gfx toad_seg6_dl_060076C0[] = {
    gsSPVertex(toad_seg6_vertex_06007200, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06007710 - 0x06007788
const Gfx toad_seg6_dl_06007710[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(toad_seg6_dl_06007300),
    gsSPDisplayList(toad_seg6_dl_06007498),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_060076C0),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

#ifndef VERSION_JP
// 0x06007788 - 0x06007808
const Gfx toad_seg6_us_dl_06007788[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetRenderMode(G_RM_CUSTOM_AA_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(toad_seg6_dl_06007300),
    gsSPDisplayList(toad_seg6_dl_06007498),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_060076C0),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
#endif

// 0x06007788
static const Lights1 toad_seg6_lights_06007788 = gdSPDefLights1(
    0x21, 0x13, 0x5a,
    0x42, 0x27, 0xb5, 0x28, 0x28, 0x28
);

// 0x060077A0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_060077A0, 0x001d8310, 51422, 0x00007820, 256);

// 0x060078A0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_060078A0, 0x001d8310, 51422, 0x00007920, 192);

// 0x06007960 - 0x06007A48
const Gfx toad_seg6_dl_06007960[] = {
    gsSPLight(&toad_seg6_lights_06007788.l, 1),
    gsSPLight(&toad_seg6_lights_06007788.a, 2),
    gsSPVertex(toad_seg6_vertex_060077A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0, 12,  8, 11, 0x0),
    gsSP2Triangles(12,  5,  8, 0x0, 10,  9, 13, 0x0),
    gsSP2Triangles( 0, 14,  1, 0x0, 15,  0,  2, 0x0),
    gsSPVertex(toad_seg6_vertex_060078A0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 5,  9,  8, 0x0,  4,  2, 10, 0x0),
    gsSP2Triangles( 8,  1,  5, 0x0,  8,  7, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06007A48 - 0x06007A80
const Gfx toad_seg6_dl_06007A48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(toad_seg6_dl_06007960),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

#ifndef VERSION_JP
// 0x06007B00 - 0x06007B28
const Gfx toad_seg6_us_dl_06007B00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_06007960),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
#endif

// 0x06007A80
static const Lights1 toad_seg6_lights_06007A80 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06007A98
static const Lights1 toad_seg6_lights_06007A98 = gdSPDefLights1(
    0x7f, 0x6a, 0x50,
    0xfe, 0xd5, 0xa1, 0x28, 0x28, 0x28
);

// 0x06007AB0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06007AB0, 0x001d8310, 51422, 0x00007b58, 224);

// 0x06007B90
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06007B90, 0x001d8310, 51422, 0x00007c38, 192);

// 0x06007C50
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06007C50, 0x001d8310, 51422, 0x00007cf8, 192);

// 0x06007D10 - 0x06007EB0
const Gfx toad_seg6_dl_06007D10[] = {
    gsSPLight(&toad_seg6_lights_06007A80.l, 1),
    gsSPLight(&toad_seg6_lights_06007A80.a, 2),
    gsSPVertex(toad_seg6_vertex_06007AB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0, 10,  7,  6, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 11,  6,  5, 0x0),
    gsSP2Triangles( 7,  0,  8, 0x0,  0,  7, 10, 0x0),
    gsSP2Triangles( 2, 12, 13, 0x0,  2,  1, 12, 0x0),
    gsSP2Triangles( 2,  8,  0, 0x0,  2, 13,  9, 0x0),
    gsSP1Triangle( 2,  9,  8, 0x0),
    gsSPVertex(toad_seg6_vertex_06007B90, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  1, 0x0),
    gsSP2Triangles( 7,  1,  9, 0x0,  7, 10,  8, 0x0),
    gsSP2Triangles( 7,  9,  4, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles( 5,  9,  0, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(11,  6,  0, 0x0, 11,  0,  2, 0x0),
    gsSP1Triangle( 0,  6,  5, 0x0),
    gsSPLight(&toad_seg6_lights_06007A98.l, 1),
    gsSPLight(&toad_seg6_lights_06007A98.a, 2),
    gsSPVertex(toad_seg6_vertex_06007C50, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  6,  2,  4, 0x0),
    gsSP2Triangles( 2,  7,  3, 0x0,  5,  8,  4, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  4,  8, 0x0),
    gsSP2Triangles(10,  3,  7, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles( 7,  6, 11, 0x0,  9, 11,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06007EB0 - 0x06007ED8
const Gfx toad_seg6_dl_06007EB0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_06007D10),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x06007ED8
static const Lights1 toad_seg6_lights_06007ED8 = gdSPDefLights1(
    0x7f, 0x6a, 0x50,
    0xfe, 0xd5, 0xa1, 0x28, 0x28, 0x28
);

// 0x06007EF0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06007EF0, 0x001d8310, 51422, 0x00007f98, 256);

// 0x06007FF0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06007FF0, 0x001d8310, 51422, 0x00008098, 208);

// 0x060080C0 - 0x060081F8
const Gfx toad_seg6_dl_060080C0[] = {
    gsSPLight(&toad_seg6_lights_06007ED8.l, 1),
    gsSPLight(&toad_seg6_lights_06007ED8.a, 2),
    gsSPVertex(toad_seg6_vertex_06007EF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  4,  3,  0, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 4,  2,  7, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  4,  9,  3, 0x0),
    gsSP2Triangles( 4,  8, 10, 0x0, 11,  9,  4, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0,  1,  3, 12, 0x0),
    gsSP2Triangles(11,  3,  9, 0x0, 12,  3, 11, 0x0),
    gsSP2Triangles( 7, 13,  8, 0x0,  7,  6, 13, 0x0),
    gsSP2Triangles(10, 14, 15, 0x0, 10, 15, 11, 0x0),
    gsSPVertex(toad_seg6_vertex_06007FF0, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  2,  8,  4, 0x0),
    gsSP2Triangles( 2,  5,  8, 0x0,  5,  2,  9, 0x0),
    gsSP2Triangles( 5,  9,  6, 0x0,  9,  2,  1, 0x0),
    gsSP2Triangles(10,  9,  1, 0x0, 10,  1, 11, 0x0),
    gsSP2Triangles( 9, 12,  6, 0x0,  9, 10, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x060081F8 - 0x06008220
const Gfx toad_seg6_dl_060081F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_060080C0),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x06008220
static const Lights1 toad_seg6_lights_06008220 = gdSPDefLights1(
    0x7f, 0x6a, 0x50,
    0xfe, 0xd5, 0xa1, 0x28, 0x28, 0x28
);

// 0x06008238
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06008238, 0x001d8310, 51422, 0x000082e0, 256);

// 0x06008338
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06008338, 0x001d8310, 51422, 0x000083e0, 176);

// 0x060083E8 - 0x06008520
const Gfx toad_seg6_dl_060083E8[] = {
    gsSPLight(&toad_seg6_lights_06008220.l, 1),
    gsSPLight(&toad_seg6_lights_06008220.a, 2),
    gsSPVertex(toad_seg6_vertex_06008238, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  0,  4,  6, 0x0),
    gsSP2Triangles( 0,  7,  8, 0x0,  8,  3,  0, 0x0),
    gsSP2Triangles( 2,  7,  0, 0x0,  6,  5,  0, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles( 7,  2,  9, 0x0, 11,  7, 10, 0x0),
    gsSP2Triangles(12,  3,  8, 0x0, 12,  8, 11, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  6,  3, 12, 0x0),
    gsSP2Triangles( 1,  9,  2, 0x0, 12, 11, 10, 0x0),
    gsSP2Triangles( 6, 12, 13, 0x0,  6, 14, 15, 0x0),
    gsSP2Triangles( 6, 15,  5, 0x0, 13, 14,  6, 0x0),
    gsSPVertex(toad_seg6_vertex_06008338, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  0,  5, 0x0),
    gsSP2Triangles( 8,  7,  5, 0x0,  3,  1,  9, 0x0),
    gsSP2Triangles( 1,  0,  7, 0x0,  9,  1,  7, 0x0),
    gsSP2Triangles( 8, 10,  7, 0x0,  9,  7, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008520 - 0x06008560
const Gfx toad_seg6_dl_06008520[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_060083E8),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// US: 8608
#ifndef VERSION_JP
// 0x06008608 - 0x06008650
const Gfx toad_seg6_us_dl_06008608[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_060083E8),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPEndDisplayList(),
};
#endif

// 0x06008560
static const Lights1 toad_seg6_lights_06008560 = gdSPDefLights1(
    0x34, 0x20, 0x0d,
    0x68, 0x40, 0x1b, 0x28, 0x28, 0x28
);

// 0x06008578
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06008578, 0x001d8310, 51422, 0x00008668, 256);

// 0x06008678
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_06008678, 0x001d8310, 51422, 0x00008768, 208);

// 0x06008748 - 0x06008890
const Gfx toad_seg6_dl_06008748[] = {
    gsSPLight(&toad_seg6_lights_06008560.l, 1),
    gsSPLight(&toad_seg6_lights_06008560.a, 2),
    gsSPVertex(toad_seg6_vertex_06008578, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  7,  3, 0x0,  2,  8,  7, 0x0),
    gsSP2Triangles( 2,  9,  8, 0x0,  2,  6,  9, 0x0),
    gsSP2Triangles( 2,  1, 10, 0x0,  2, 10,  4, 0x0),
    gsSP2Triangles( 7, 11,  0, 0x0, 12, 11,  7, 0x0),
    gsSP2Triangles(12,  7,  8, 0x0,  7,  0,  3, 0x0),
    gsSP2Triangles(12,  8,  9, 0x0, 10,  5,  4, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0, 14,  9,  6, 0x0),
    gsSP2Triangles(14, 13,  9, 0x0,  5, 14,  6, 0x0),
    gsSP1Triangle(10, 15,  5, 0x0),
    gsSPVertex(toad_seg6_vertex_06008678, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 7,  5,  2, 0x0,  8,  4,  3, 0x0),
    gsSP2Triangles( 8,  3,  6, 0x0,  9,  7,  1, 0x0),
    gsSP2Triangles( 7, 10,  5, 0x0,  5, 10, 11, 0x0),
    gsSP2Triangles(11,  6,  5, 0x0, 11, 12,  6, 0x0),
    gsSP1Triangle( 6, 12,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008890 - 0x060088B8
const Gfx toad_seg6_dl_06008890[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_06008748),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x060088B8
static const Lights1 toad_seg6_lights_060088B8 = gdSPDefLights1(
    0x34, 0x20, 0x0d,
    0x68, 0x40, 0x1b, 0x28, 0x28, 0x28
);

// 0x060088D0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_060088D0, 0x001d8310, 51422, 0x000089c0, 256);

// 0x060089D0
ROM_ASSET_LOAD_VTX(toad_seg6_vertex_060089D0, 0x001d8310, 51422, 0x00008ac0, 192);

// 0x06008A90 - 0x06008BD8
const Gfx toad_seg6_dl_06008A90[] = {
    gsSPLight(&toad_seg6_lights_060088B8.l, 1),
    gsSPLight(&toad_seg6_lights_060088B8.a, 2),
    gsSPVertex(toad_seg6_vertex_060088D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 0,  8,  3, 0x0,  0,  9,  8, 0x0),
    gsSP2Triangles( 0, 10,  9, 0x0,  0,  7, 10, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8,  9, 11, 0x0),
    gsSP2Triangles( 8, 12,  4, 0x0,  8,  4,  3, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0,  6,  5,  2, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10,  7, 13, 0x0),
    gsSP2Triangles(10, 14, 11, 0x0, 13,  7,  6, 0x0),
    gsSP2Triangles(13,  6, 15, 0x0,  6,  2, 15, 0x0),
    gsSPVertex(toad_seg6_vertex_060089D0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  0,  3,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  6,  4,  0, 0x0),
    gsSP2Triangles( 7,  5,  3, 0x0,  3,  8,  7, 0x0),
    gsSP2Triangles( 3,  2,  8, 0x0,  1,  4,  9, 0x0),
    gsSP2Triangles(10,  8,  2, 0x0,  2, 11, 10, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0,  9, 11,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008BD8 - 0x06008C00
const Gfx toad_seg6_dl_06008BD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(toad_seg6_dl_06008A90),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
