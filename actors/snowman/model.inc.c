#include "pc/rom_assets.h"
// Snowman

// ???
UNUSED static const u64 snowman_unused_1 = 1;

// Unreferenced light group
UNUSED static const Lights1 snowman_lights_unused1 = gdSPDefLights1(
    0x0d, 0x0c, 0x28,
    0x35, 0x32, 0xa2, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 snowman_lights_unused2 = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 snowman_lights_unused3 = gdSPDefLights1(
    0x08, 0x07, 0x04,
    0x23, 0x1c, 0x12, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 snowman_lights_unused4 = gdSPDefLights1(
    0x03, 0x03, 0x02,
    0x0e, 0x0d, 0x0b, 0x28, 0x28, 0x28
);

// 0x05008C70
ROM_ASSET_LOAD_TEXTURE(snowman_seg5_texture_05008C70, "actors/snowman/mr_blizzard_mitten.rgba16.inc.c", 0x00160670, 20585, 0x00008c70, 2048);

// 0x05009470
ROM_ASSET_LOAD_TEXTURE(snowman_seg5_texture_05009470, "actors/snowman/mr_blizzard_left_side.rgba16.inc.c", 0x00160670, 20585, 0x00009470, 4096);

// 0x0500A470
ROM_ASSET_LOAD_TEXTURE(snowman_seg5_texture_0500A470, "actors/snowman/mr_blizzard_right_side.rgba16.inc.c", 0x00160670, 20585, 0x0000a470, 4096);

// 0x0500B470
ROM_ASSET_LOAD_TEXTURE(snowman_seg5_texture_0500B470, "actors/snowman/mr_blizzard_eye.rgba16.inc.c", 0x00160670, 20585, 0x0000b470, 2048);

// 0x0500BC70
ROM_ASSET_LOAD_TEXTURE(snowman_seg5_texture_0500BC70, "actors/snowman/mr_blizzard_mouth.rgba16.inc.c", 0x00160670, 20585, 0x0000bc70, 2048);

// 0x0500C470
static const Lights1 snowman_seg5_lights_0500C470 = gdSPDefLights1(
    0x1c, 0x0f, 0x07,
    0x38, 0x1e, 0x0e, 0x28, 0x28, 0x28
);

// 0x0500C488
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500C488, 0x00160670, 20585, 0x0000c488, 64);

// 0x0500C4C8 - 0x0500C500
const Gfx snowman_seg5_dl_0500C4C8[] = {
    gsSPLight(&snowman_seg5_lights_0500C470.l, 1),
    gsSPLight(&snowman_seg5_lights_0500C470.a, 2),
    gsSPVertex(snowman_seg5_vertex_0500C488, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C500 - 0x0500C530
const Gfx snowman_seg5_dl_0500C500[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(snowman_seg5_dl_0500C4C8),
    gsSPEndDisplayList(),
};

// 0x0500C530
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500C530, 0x00160670, 20585, 0x0000c530, 64);

// 0x0500C570
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500C570, 0x00160670, 20585, 0x0000c570, 64);

// 0x0500C5B0 - 0x0500C5E8
const Gfx snowman_seg5_dl_0500C5B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_05009470),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500C530, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C5E8 - 0x0500C620
const Gfx snowman_seg5_dl_0500C5E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_0500A470),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500C570, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C620 - 0x0500C698
const Gfx snowman_seg5_dl_0500C620[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500C5B0),
    gsSPDisplayList(snowman_seg5_dl_0500C5E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500C698
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500C698, 0x00160670, 20585, 0x0000c698, 128);

// 0x0500C718 - 0x0500C760
const Gfx snowman_seg5_dl_0500C718[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_0500B470),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500C698, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C760 - 0x0500C7D0
const Gfx snowman_seg5_dl_0500C760[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500C718),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500C7D0
static const Lights1 snowman_seg5_lights_0500C7D0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C7E8
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500C7E8, 0x00160670, 20585, 0x0000c7e8, 256);

// 0x0500C8E8
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500C8E8, 0x00160670, 20585, 0x0000c8e8, 144);

// 0x0500C978 - 0x0500CAA8
const Gfx snowman_seg5_dl_0500C978[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_05008C70),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&snowman_seg5_lights_0500C7D0.l, 1),
    gsSPLight(&snowman_seg5_lights_0500C7D0.a, 2),
    gsSPVertex(snowman_seg5_vertex_0500C7E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  1,  4, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0,  7,  2,  1, 0x0),
    gsSP2Triangles( 8, 11,  7, 0x0, 11,  2,  7, 0x0),
    gsSP2Triangles( 5, 12, 13, 0x0, 13, 14,  5, 0x0),
    gsSP2Triangles( 5,  3, 12, 0x0,  5, 14, 10, 0x0),
    gsSP2Triangles(10, 14,  9, 0x0, 13,  9, 14, 0x0),
    gsSP2Triangles( 8,  9, 13, 0x0,  2, 15,  0, 0x0),
    gsSPVertex(snowman_seg5_vertex_0500C8E8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  2,  6,  4, 0x0),
    gsSP2Triangles( 2,  5,  7, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 3,  6,  2, 0x0,  7,  8,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CAA8 - 0x0500CB08
const Gfx snowman_seg5_dl_0500CAA8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500C978),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500CB08
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500CB08, 0x00160670, 20585, 0x0000cb08, 64);

// 0x0500CB48
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500CB48, 0x00160670, 20585, 0x0000cb48, 64);

// 0x0500CB88 - 0x0500CBC0
const Gfx snowman_seg5_dl_0500CB88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_05009470),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500CB08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CBC0 - 0x0500CBF8
const Gfx snowman_seg5_dl_0500CBC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_0500A470),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500CB48, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CBF8 - 0x0500CC70
const Gfx snowman_seg5_dl_0500CBF8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500CB88),
    gsSPDisplayList(snowman_seg5_dl_0500CBC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500CC70
ROM_ASSET_LOAD_VTX(snowman_seg5_vertex_0500CC70, 0x00160670, 20585, 0x0000cc70, 64);

// 0x0500CCB0 - 0x0500CCE8
const Gfx snowman_seg5_dl_0500CCB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_0500BC70),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500CC70, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CCE8 - 0x0500CD58
const Gfx snowman_seg5_dl_0500CCE8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500CCB0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
