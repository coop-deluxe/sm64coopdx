#include "pc/rom_assets.h"
// Mad Piano

// Unreferenced light group
UNUSED static const Lights1 mad_piano_lights_unused1 = gdSPDefLights1(
    0x05, 0x04, 0x08,
    0x14, 0x13, 0x20, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 mad_piano_lights_unused2 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 mad_piano_lights_unused3 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 mad_piano_lights_unused4 = gdSPDefLights1(
    0x30, 0x00, 0x00,
    0xc3, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05006AF0
ROM_ASSET_LOAD_TEXTURE(mad_piano_seg5_texture_05006AF0, "actors/mad_piano/mad_piano_tooth.rgba16.inc.c", 0x00166c60, 26968, 0x00006af0, 2048);

// 0x050072F0
ROM_ASSET_LOAD_TEXTURE(mad_piano_seg5_texture_050072F0, "actors/mad_piano/mad_piano_body.rgba16.inc.c", 0x00166c60, 26968, 0x000072f0, 1024);

// 0x050076F0
ROM_ASSET_LOAD_TEXTURE(mad_piano_seg5_texture_050076F0, "actors/mad_piano/mad_piano_keys_corner.rgba16.inc.c", 0x00166c60, 26968, 0x000076f0, 1024);

// 0x05007AF0
ROM_ASSET_LOAD_TEXTURE(mad_piano_seg5_texture_05007AF0, "actors/mad_piano/mad_piano_mouth.rgba16.inc.c", 0x00166c60, 26968, 0x00007af0, 1024);

// 0x05007EF0
ROM_ASSET_LOAD_TEXTURE(mad_piano_seg5_texture_05007EF0, "actors/mad_piano/mad_piano_keys.rgba16.inc.c", 0x00166c60, 26968, 0x00007ef0, 1024);

// 0x050082F0
ROM_ASSET_LOAD_TEXTURE(mad_piano_seg5_texture_050082F0, "actors/mad_piano/mad_piano_keys_edge.rgba16.inc.c", 0x00166c60, 26968, 0x000082f0, 1024);

// 0x050086F0
static const Lights1 mad_piano_seg5_lights_050086F0 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05008708
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05008708, 0x00166c60, 26968, 0x00008708, 160);

// 0x050087A8
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_050087A8, 0x00166c60, 26968, 0x000087a8, 240);

// 0x05008898
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05008898, 0x00166c60, 26968, 0x00008898, 240);

// 0x05008988
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05008988, 0x00166c60, 26968, 0x00008988, 240);

// 0x05008A78
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05008A78, 0x00166c60, 26968, 0x00008a78, 240);

// 0x05008B68 - 0x05008BD0
const Gfx mad_piano_seg5_dl_05008B68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mad_piano_seg5_texture_050072F0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mad_piano_seg5_lights_050086F0.l, 1),
    gsSPLight(&mad_piano_seg5_lights_050086F0.a, 2),
    gsSPVertex(mad_piano_seg5_vertex_05008708, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  0,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008BD0 - 0x05008CB0
const Gfx mad_piano_seg5_dl_05008BD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mad_piano_seg5_texture_05006AF0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(mad_piano_seg5_vertex_050087A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(mad_piano_seg5_vertex_05008898, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(mad_piano_seg5_vertex_05008988, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(mad_piano_seg5_vertex_05008A78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008CB0 - 0x05008D40
const Gfx mad_piano_seg5_dl_05008CB0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mad_piano_seg5_dl_05008B68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mad_piano_seg5_dl_05008BD0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x05008D40
static const Lights1 mad_piano_seg5_lights_05008D40 = gdSPDefLights1(
    0x3d, 0x3d, 0x3d,
    0xcc, 0xcc, 0xcc, 0x28, 0x28, 0x28
);

// 0x05008D58
static const Lights1 mad_piano_seg5_lights_05008D58 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05008D70
static const Lights1 mad_piano_seg5_lights_05008D70 = gdSPDefLights1(
    0x26, 0x26, 0x26,
    0x7f, 0x7f, 0x7f, 0x28, 0x28, 0x28
);

// 0x05008D88
static const Lights1 mad_piano_seg5_lights_05008D88 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05008DA0
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05008DA0, 0x00166c60, 26968, 0x00008da0, 208);

// 0x05008E70
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05008E70, 0x00166c60, 26968, 0x00008e70, 240);

// 0x05008F60
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05008F60, 0x00166c60, 26968, 0x00008f60, 240);

// 0x05009050
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05009050, 0x00166c60, 26968, 0x00009050, 256);

// 0x05009150
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05009150, 0x00166c60, 26968, 0x00009150, 240);

// 0x05009240
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05009240, 0x00166c60, 26968, 0x00009240, 240);

// 0x05009330
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05009330, 0x00166c60, 26968, 0x00009330, 192);

// 0x050093F0
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_050093F0, 0x00166c60, 26968, 0x000093f0, 64);

// 0x05009430
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05009430, 0x00166c60, 26968, 0x00009430, 64);

// 0x05009470
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_05009470, 0x00166c60, 26968, 0x00009470, 128);

// 0x050094F0
ROM_ASSET_LOAD_VTX(mad_piano_seg5_vertex_050094F0, 0x00166c60, 26968, 0x000094f0, 160);

// 0x05009590 - 0x050096C8
const Gfx mad_piano_seg5_dl_05009590[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mad_piano_seg5_texture_050072F0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mad_piano_seg5_lights_05008D40.l, 1),
    gsSPLight(&mad_piano_seg5_lights_05008D40.a, 2),
    gsSPVertex(mad_piano_seg5_vertex_05008DA0, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  7,  9, 0x0),
    gsSP2Triangles(11,  9,  1, 0x0,  0, 12, 11, 0x0),
    gsSP1Triangle( 0, 11,  1, 0x0),
    gsSPLight(&mad_piano_seg5_lights_05008D58.l, 1),
    gsSPLight(&mad_piano_seg5_lights_05008D58.a, 2),
    gsSPVertex(mad_piano_seg5_vertex_05008E70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(mad_piano_seg5_vertex_05008F60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(mad_piano_seg5_vertex_05009050, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(10, 14, 13, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x050096C8 - 0x050097B0
const Gfx mad_piano_seg5_dl_050096C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mad_piano_seg5_texture_05007AF0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(mad_piano_seg5_vertex_05009150, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(mad_piano_seg5_vertex_05009240, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(mad_piano_seg5_vertex_05009330, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0,  4, 11,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x050097B0 - 0x050097F8
const Gfx mad_piano_seg5_dl_050097B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mad_piano_seg5_texture_050082F0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mad_piano_seg5_lights_05008D70.l, 1),
    gsSPLight(&mad_piano_seg5_lights_05008D70.a, 2),
    gsSPVertex(mad_piano_seg5_vertex_050093F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x050097F8 - 0x05009840
const Gfx mad_piano_seg5_dl_050097F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mad_piano_seg5_texture_05007EF0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&mad_piano_seg5_lights_05008D40.l, 1),
    gsSPLight(&mad_piano_seg5_lights_05008D40.a, 2),
    gsSPVertex(mad_piano_seg5_vertex_05009430, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05009840 - 0x05009888
const Gfx mad_piano_seg5_dl_05009840[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mad_piano_seg5_texture_050076F0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(mad_piano_seg5_vertex_05009470, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05009888 - 0x050098E8
const Gfx mad_piano_seg5_dl_05009888[] = {
    gsSPLight(&mad_piano_seg5_lights_05008D88.l, 1),
    gsSPLight(&mad_piano_seg5_lights_05008D88.a, 2),
    gsSPVertex(mad_piano_seg5_vertex_050094F0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0,  7,  6, 0x0),
    gsSP2Triangles( 0,  8,  7, 0x0,  0,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x050098E8 - 0x050099B8
const Gfx mad_piano_seg5_dl_050098E8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mad_piano_seg5_dl_05009590),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mad_piano_seg5_dl_050096C8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mad_piano_seg5_dl_050097B0),
    gsSPDisplayList(mad_piano_seg5_dl_050097F8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(mad_piano_seg5_dl_05009840),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(mad_piano_seg5_dl_05009888),
    gsSPEndDisplayList(),
};
