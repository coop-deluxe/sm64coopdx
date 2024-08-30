#include "pc/rom_assets.h"
// King Bobomb

// Unreferenced light group
UNUSED static const Lights1 king_bobomb_lights_unused1 = gdSPDefLights1(
    0x36, 0x1e, 0x00,
    0xd9, 0x7a, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 king_bobomb_lights_unused2 = gdSPDefLights1(
    0x00, 0x00, 0x3f,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 king_bobomb_lights_unused3 = gdSPDefLights1(
    0x3c, 0x28, 0x00,
    0xf1, 0xa2, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 king_bobomb_lights_unused4 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 king_bobomb_lights_unused5 = gdSPDefLights1(
    0x06, 0x06, 0x06,
    0x19, 0x19, 0x19, 0x28, 0x28, 0x28
);

// 0x05000078
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05000078, "actors/king_bobomb/bob-omb_buddy_left_side_unused.rgba16.inc.c", 0x00134d20, 26785, 0x00000078, 4096);

// 0x05001078
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05001078, "actors/king_bobomb/bob-omb_buddy_right_side_unused.rgba16.inc.c", 0x00134d20, 26785, 0x00001078, 4096);

// 0x05002078
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05002078, "actors/king_bobomb/king_bob-omb_arm.rgba16.inc.c", 0x00134d20, 26785, 0x00002078, 2048);

// 0x05002878
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05002878, "actors/king_bobomb/king_bob-omb_body_unused.rgba16.inc.c", 0x00134d20, 26785, 0x00002878, 8192);

// 0x05004878
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05004878, "actors/king_bobomb/king_bob-omb_eyes.rgba16.inc.c", 0x00134d20, 26785, 0x00004878, 4096);

// 0x05005878
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05005878, "actors/king_bobomb/king_bob-omb_hand.rgba16.inc.c", 0x0012a7e0, 32879, 0x00000040, 2048);

// 0x05006078
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05006078, "actors/king_bobomb/king_bob-omb_crown_rim.rgba16.inc.c", 0x00134d20, 26785, 0x00006078, 1024);

// 0x05006478
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05006478, "actors/king_bobomb/bob-omb_buddy_body_unused.rgba16.inc.c", 0x00134d20, 26785, 0x00006478, 8192);

// 0x05008478
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05008478, "actors/king_bobomb/king_bob-omb_left_side.rgba16.inc.c", 0x00134d20, 26785, 0x00008478, 4096);

// 0x05009478
ROM_ASSET_LOAD_TEXTURE(king_bobomb_seg5_texture_05009478, "actors/king_bobomb/king_bob-omb_right_side.rgba16.inc.c", 0x00134d20, 26785, 0x00009478, 4096);

// 0x0500A478
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500A478, 0x00134d20, 26785, 0x0000a478, 64);

// 0x0500A4B8 - 0x0500A4F0
const Gfx king_bobomb_seg5_dl_0500A4B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05002078),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500A478, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A4F0 - 0x0500A560
const Gfx king_bobomb_seg5_dl_0500A4F0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500A4B8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A560
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500A560, 0x00134d20, 26785, 0x0000a560, 64);

// 0x0500A5A0 - 0x0500A5D8
const Gfx king_bobomb_seg5_dl_0500A5A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05002078),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500A560, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A5D8 - 0x0500A648
const Gfx king_bobomb_seg5_dl_0500A5D8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500A5A0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A648
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500A648, 0x00134d20, 26785, 0x0000a648, 64);

// 0x0500A688 - 0x0500A6C0
const Gfx king_bobomb_seg5_dl_0500A688[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05005878),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500A648, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A6C0 - 0x0500A730
const Gfx king_bobomb_seg5_dl_0500A6C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500A688),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A730
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500A730, 0x00134d20, 26785, 0x0000a478, 64);

// 0x0500A770 - 0x0500A7A8
const Gfx king_bobomb_seg5_dl_0500A770[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05002078),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500A730, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A7A8 - 0x0500A818
const Gfx king_bobomb_seg5_dl_0500A7A8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500A770),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A818
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500A818, 0x00134d20, 26785, 0x0000a560, 64);

// 0x0500A858 - 0x0500A890
const Gfx king_bobomb_seg5_dl_0500A858[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05002078),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500A818, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A890 - 0x0500A900
const Gfx king_bobomb_seg5_dl_0500A890[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500A858),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A900
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500A900, 0x00134d20, 26785, 0x0000a648, 64);

// 0x0500A940 - 0x0500A978
const Gfx king_bobomb_seg5_dl_0500A940[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05005878),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500A900, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A978 - 0x0500A9E8
const Gfx king_bobomb_seg5_dl_0500A978[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500A940),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A9E8
static const Lights1 king_bobomb_seg5_lights_0500A9E8 = gdSPDefLights1(
    0x6f, 0x56, 0x11,
    0xde, 0xad, 0x23, 0x28, 0x28, 0x28
);

// 0x0500AA00
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500AA00, 0x00134d20, 26785, 0x0000aa00, 256);

// 0x0500AB00
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500AB00, 0x00134d20, 26785, 0x0000ab00, 192);

// 0x0500ABC0 - 0x0500AD08
const Gfx king_bobomb_seg5_dl_0500ABC0[] = {
    gsSPLight(&king_bobomb_seg5_lights_0500A9E8.l, 1),
    gsSPLight(&king_bobomb_seg5_lights_0500A9E8.a, 2),
    gsSPVertex(king_bobomb_seg5_vertex_0500AA00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  1,  8,  7, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0,  1,  6,  9, 0x0),
    gsSP2Triangles( 1, 10,  4, 0x0,  1,  3, 10, 0x0),
    gsSP2Triangles(11, 12,  7, 0x0, 11,  7,  8, 0x0),
    gsSP2Triangles( 7, 12,  0, 0x0,  7,  0,  2, 0x0),
    gsSP2Triangles( 9, 11,  8, 0x0, 10,  5,  4, 0x0),
    gsSP2Triangles( 9, 13, 11, 0x0, 14, 13,  9, 0x0),
    gsSP2Triangles(14,  9,  6, 0x0, 14,  6,  5, 0x0),
    gsSP2Triangles(14,  5, 15, 0x0, 10, 15,  5, 0x0),
    gsSPVertex(king_bobomb_seg5_vertex_0500AB00, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 7,  5,  2, 0x0,  8,  4,  3, 0x0),
    gsSP2Triangles( 8,  3,  6, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 7, 10,  5, 0x0,  5, 10, 11, 0x0),
    gsSP2Triangles(11,  6,  5, 0x0, 11,  9,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500AD08 - 0x0500AD38
const Gfx king_bobomb_seg5_dl_0500AD08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(king_bobomb_seg5_dl_0500ABC0),
    gsSPEndDisplayList(),
};

// 0x0500AD38
static const Lights1 king_bobomb_seg5_lights_0500AD38 = gdSPDefLights1(
    0x6f, 0x4f, 0x10,
    0xde, 0x9e, 0x20, 0x28, 0x28, 0x28
);

// 0x0500AD50
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500AD50, 0x00134d20, 26785, 0x0000ad50, 256);

// 0x0500AE50
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500AE50, 0x00134d20, 26785, 0x0000ae50, 208);

// 0x0500AF20 - 0x0500B068
const Gfx king_bobomb_seg5_dl_0500AF20[] = {
    gsSPLight(&king_bobomb_seg5_lights_0500AD38.l, 1),
    gsSPLight(&king_bobomb_seg5_lights_0500AD38.a, 2),
    gsSPVertex(king_bobomb_seg5_vertex_0500AD50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 1,  3,  6, 0x0,  1,  6,  7, 0x0),
    gsSP2Triangles( 1,  8,  4, 0x0,  1,  9,  8, 0x0),
    gsSP2Triangles( 1, 10,  9, 0x0,  1,  7, 10, 0x0),
    gsSP2Triangles( 8, 11,  5, 0x0,  8,  9, 12, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0,  8,  5,  4, 0x0),
    gsSP2Triangles(10, 12,  9, 0x0,  6,  3,  0, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10,  7, 13, 0x0),
    gsSP2Triangles(10, 14, 12, 0x0,  6, 13,  7, 0x0),
    gsSP1Triangle( 6,  0, 15, 0x0),
    gsSPVertex(king_bobomb_seg5_vertex_0500AE50, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  0,  3,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  6,  4,  0, 0x0),
    gsSP2Triangles( 7,  5,  3, 0x0,  8,  5,  7, 0x0),
    gsSP2Triangles( 3,  9,  7, 0x0,  3,  2,  9, 0x0),
    gsSP2Triangles(10,  9,  2, 0x0,  1,  4, 11, 0x0),
    gsSP2Triangles( 2, 12, 10, 0x0,  2,  1, 12, 0x0),
    gsSP1Triangle(11, 12,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B068 - 0x0500B098
const Gfx king_bobomb_seg5_dl_0500B068[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(king_bobomb_seg5_dl_0500AF20),
    gsSPEndDisplayList(),
};

// 0x0500B098
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500B098, 0x00134d20, 26785, 0x0000b098, 64);

// 0x0500B0D8
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500B0D8, 0x00134d20, 26785, 0x0000b0d8, 64);

// 0x0500B118 - 0x0500B150
const Gfx king_bobomb_seg5_dl_0500B118[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05008478),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500B098, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B150 - 0x0500B188
const Gfx king_bobomb_seg5_dl_0500B150[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05009478),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(king_bobomb_seg5_vertex_0500B0D8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B188 - 0x0500B200
const Gfx king_bobomb_seg5_dl_0500B188[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500B118),
    gsSPDisplayList(king_bobomb_seg5_dl_0500B150),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500B200
static const Lights1 king_bobomb_seg5_lights_0500B200 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500B218
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500B218, 0x00134d20, 26785, 0x0000b218, 96);

// 0x0500B278 - 0x0500B2D0
const Gfx king_bobomb_seg5_dl_0500B278[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05004878),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&king_bobomb_seg5_lights_0500B200.l, 1),
    gsSPLight(&king_bobomb_seg5_lights_0500B200.a, 2),
    gsSPVertex(king_bobomb_seg5_vertex_0500B218, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 2,  3,  0, 0x0,  4,  5,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B2D0 - 0x0500B330
const Gfx king_bobomb_seg5_dl_0500B2D0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500B278),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500B330
static const Lights1 king_bobomb_seg5_lights_0500B330 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500B348
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500B348, 0x00134d20, 26785, 0x0000b348, 128);

// 0x0500B3C8 - 0x0500B418
const Gfx king_bobomb_seg5_dl_0500B3C8[] = {
    gsSPLight(&king_bobomb_seg5_lights_0500B330.l, 1),
    gsSPLight(&king_bobomb_seg5_lights_0500B330.a, 2),
    gsSPVertex(king_bobomb_seg5_vertex_0500B348, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B418 - 0x0500B458
const Gfx king_bobomb_seg5_dl_0500B418[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(king_bobomb_seg5_dl_0500B3C8),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0500B458
static const Lights1 king_bobomb_seg5_lights_0500B458 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500B470
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500B470, 0x00134d20, 26785, 0x0000b470, 256);

// 0x0500B570
ROM_ASSET_LOAD_VTX(king_bobomb_seg5_vertex_0500B570, 0x00134d20, 26785, 0x0000b570, 128);

// 0x0500B5F0 - 0x0500B6C0
const Gfx king_bobomb_seg5_dl_0500B5F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, king_bobomb_seg5_texture_05006078),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&king_bobomb_seg5_lights_0500B458.l, 1),
    gsSPLight(&king_bobomb_seg5_lights_0500B458.a, 2),
    gsSPVertex(king_bobomb_seg5_vertex_0500B470, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 5,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(king_bobomb_seg5_vertex_0500B570, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  5,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B6C0 - 0x0500B730
const Gfx king_bobomb_seg5_dl_0500B6C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(king_bobomb_seg5_dl_0500B5F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
