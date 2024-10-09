#include "pc/rom_assets.h"
// Cyan Fish

// ???
UNUSED static const u64 cyan_fish_unused_1 = 0;

// 0x0600D468
ROM_ASSET_LOAD_TEXTURE(cyan_fish_seg6_texture_0600D468, "actors/cyan_fish/cyan_fish.rgba16.inc.c", 0x001b9cc0, 41188, 0x0000d468, 2048);

static const Lights1 cyan_fish_seg6_lights_0600DC68 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0600DC80
ROM_ASSET_LOAD_VTX(cyan_fish_seg6_vertex_0600DC80, 0x001b9cc0, 41188, 0x0000dc80, 160);

// 0x0600DD20 - 0x0600DDD8
const Gfx cyan_fish_seg6_dl_0600DD20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cyan_fish_seg6_texture_0600D468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cyan_fish_seg6_lights_0600DC68.l, 1),
    gsSPLight(&cyan_fish_seg6_lights_0600DC68.a, 2),
    gsSPVertex(cyan_fish_seg6_vertex_0600DC80, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  4,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  1,  6,  2, 0x0),
    gsSP2Triangles( 1,  5,  7, 0x0,  1,  7,  6, 0x0),
    gsSP2Triangles( 6,  3,  2, 0x0,  4,  3,  8, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 5,  9,  7, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  5,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600DDD8 - 0x0600DE38
const Gfx cyan_fish_seg6_dl_0600DDD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cyan_fish_seg6_dl_0600DD20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0600DE38
static const Lights1 cyan_fish_seg6_lights_0600DE38 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0600DE50
ROM_ASSET_LOAD_VTX(cyan_fish_seg6_vertex_0600DE50, 0x001b9cc0, 41188, 0x0000de50, 64);

// 0x0600DE90 - 0x0600DED8
const Gfx cyan_fish_seg6_dl_0600DE90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cyan_fish_seg6_texture_0600D468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cyan_fish_seg6_lights_0600DE38.l, 1),
    gsSPLight(&cyan_fish_seg6_lights_0600DE38.a, 2),
    gsSPVertex(cyan_fish_seg6_vertex_0600DE50, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600DED8 - 0x0600DF48
const Gfx cyan_fish_seg6_dl_0600DED8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cyan_fish_seg6_dl_0600DE90),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0600DF48
static const Lights1 cyan_fish_seg6_lights_0600DF48 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0600DF60
ROM_ASSET_LOAD_VTX(cyan_fish_seg6_vertex_0600DF60, 0x001b9cc0, 41188, 0x0000df60, 96);

// 0x0600DFC0 - 0x0600E038
const Gfx cyan_fish_seg6_dl_0600DFC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cyan_fish_seg6_texture_0600D468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cyan_fish_seg6_lights_0600DF48.l, 1),
    gsSPLight(&cyan_fish_seg6_lights_0600DF48.a, 2),
    gsSPVertex(cyan_fish_seg6_vertex_0600DF60, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  3,  0,  5, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  0,  2,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600E038 - 0x0600E098
const Gfx cyan_fish_seg6_dl_0600E038[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cyan_fish_seg6_dl_0600DFC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
