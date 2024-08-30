#include "pc/rom_assets.h"
// 0x0700B248 - 0x0700B260
static const Lights1 ccm_seg7_lights_0700B248 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700B260 - 0x0700B278
static const Lights1 ccm_seg7_lights_0700B260 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700B278 - 0x0700B290
static const Lights1 ccm_seg7_lights_0700B278 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700B290 - 0x0700B2A8
static const Lights1 ccm_seg7_lights_0700B290 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0700B2A8 - 0x0700B3A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B2A8, 0x00383950, 74560, 0x0000b2a8, 256);

// 0x0700B3A8 - 0x0700B4A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B3A8, 0x00383950, 74560, 0x0000b3a8, 256);

// 0x0700B4A8 - 0x0700B5A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B4A8, 0x00383950, 74560, 0x0000b4a8, 256);

// 0x0700B5A8 - 0x0700B6A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B5A8, 0x00383950, 74560, 0x0000b5a8, 256);

// 0x0700B6A8 - 0x0700B7A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B6A8, 0x00383950, 74560, 0x0000b6a8, 256);

// 0x0700B7A8 - 0x0700B8A8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B7A8, 0x00383950, 74560, 0x0000b7a8, 256);

// 0x0700B8A8 - 0x0700B988
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B8A8, 0x00383950, 74560, 0x0000b8a8, 224);

// 0x0700B988 - 0x0700BA08
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700B988, 0x00383950, 74560, 0x0000b988, 128);

// 0x0700BA08 - 0x0700BB08
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BA08, 0x00383950, 74560, 0x0000ba08, 256);

// 0x0700BB08 - 0x0700BB38
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BB08, 0x00383950, 74560, 0x0000bb08, 48);

// 0x0700BB38 - 0x0700BB88
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BB38, 0x00383950, 74560, 0x0000bb38, 80);

// 0x0700BB88 - 0x0700BC78
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BB88, 0x00383950, 74560, 0x0000bb88, 240);

// 0x0700BC78 - 0x0700BD68
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BC78, 0x00383950, 74560, 0x0000bc78, 240);

// 0x0700BD68 - 0x0700BE58
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BD68, 0x00383950, 74560, 0x0000bd68, 240);

// 0x0700BE58 - 0x0700BEC8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BE58, 0x00383950, 74560, 0x0000be58, 112);

// 0x0700BEC8 - 0x0700BF88
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0700BEC8, 0x00383950, 74560, 0x0000bec8, 192);

// 0x0700BF88 - 0x0700C000
static const Gfx ccm_seg7_dl_0700BF88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ccm_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 4 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0700B248.l, 1),
    gsSPLight(&ccm_seg7_lights_0700B248.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700B2A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C000 - 0x0700C220
static const Gfx ccm_seg7_dl_0700C000[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_0700B3A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700B4A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700B5A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700B6A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700B7A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700B8A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700B988, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ccm_seg7_lights_0700B260.l, 1),
    gsSPLight(&ccm_seg7_lights_0700B260.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700BA08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700BB08, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&ccm_seg7_lights_0700B278.l, 1),
    gsSPLight(&ccm_seg7_lights_0700B278.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700BB38, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 0,  4,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C220 - 0x0700C330
static const Gfx ccm_seg7_dl_0700C220[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0700B248.l, 1),
    gsSPLight(&ccm_seg7_lights_0700B248.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700BB88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700BC78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700BD68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700BE58, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C330 - 0x0700C380
static const Gfx ccm_seg7_dl_0700C330[] = {
    gsSPLight(&ccm_seg7_lights_0700B290.l, 1),
    gsSPLight(&ccm_seg7_lights_0700B290.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700BEC8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C380 - 0x0700C438
const Gfx ccm_seg7_dl_0700C380[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 2, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (4 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0700BF88),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0700C000),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0700C220),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(ccm_seg7_dl_0700C330),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
