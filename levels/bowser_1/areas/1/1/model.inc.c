#include "pc/rom_assets.h"
// 0x07002000 - 0x07002018
static const Lights1 bowser_1_seg7_lights_07002000 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07002018 - 0x07002108
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002018, 0x004c2920, 6292, 0x00002018, 240);

// 0x07002108 - 0x07002138
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002108, 0x004c2920, 6292, 0x00002108, 48);

// 0x07002138 - 0x07002228
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002138, 0x004c2920, 6292, 0x00002138, 240);

// 0x07002228 - 0x07002318
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002228, 0x004c2920, 6292, 0x00002228, 240);

// 0x07002318 - 0x07002358
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002318, 0x004c2920, 6292, 0x00002318, 64);

// 0x07002358 - 0x07002448
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002358, 0x004c2920, 6292, 0x00002358, 240);

// 0x07002448 - 0x07002538
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002448, 0x004c2920, 6292, 0x00002448, 240);

// 0x07002538 - 0x07002578
ROM_ASSET_LOAD_VTX(bowser_1_seg7_vertex_07002538, 0x004c2920, 6292, 0x00002538, 64);

// 0x07002578 - 0x070025F8
static const Gfx bowser_1_seg7_dl_07002578[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bowser_1_seg7_texture_07001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bowser_1_seg7_lights_07002000.l, 1),
    gsSPLight(&bowser_1_seg7_lights_07002000.a, 2),
    gsSPVertex(bowser_1_seg7_vertex_07002018, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  1,  6, 0x0,  7,  1,  8, 0x0),
    gsSP2Triangles( 1,  9, 10, 0x0, 11,  1, 12, 0x0),
    gsSP1Triangle(13,  1, 14, 0x0),
    gsSPVertex(bowser_1_seg7_vertex_07002108, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070025F8 - 0x070026B0
static const Gfx bowser_1_seg7_dl_070025F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bowser_1_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_1_seg7_vertex_07002138, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bowser_1_seg7_vertex_07002228, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bowser_1_seg7_vertex_07002318, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070026B0 - 0x07002768
static const Gfx bowser_1_seg7_dl_070026B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bowser_1_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_1_seg7_vertex_07002358, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bowser_1_seg7_vertex_07002448, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bowser_1_seg7_vertex_07002538, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002768 - 0x07002838
const Gfx bowser_1_seg7_dl_07002768[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(10, 30, 20, 255),
    gsSPFogFactor(0x10AA, 0xF056), // This isn't gsSPFogPosition since there is no valid min/max pair that corresponds to 0x10AAF056
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bowser_1_seg7_dl_07002578),
    gsSPDisplayList(bowser_1_seg7_dl_070025F8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bowser_1_seg7_dl_070026B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
