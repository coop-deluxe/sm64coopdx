#include "pc/rom_assets.h"
// 0x07005990 - 0x070059A8
static const Lights1 jrb_seg7_lights_07005990 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070059A8 - 0x070059C0
static const Lights1 jrb_seg7_lights_070059A8 = gdSPDefLights1(
    0x26, 0x26, 0x26,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x070059C0 - 0x070059D8
static const Lights1 jrb_seg7_lights_070059C0 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x070059D8 - 0x07005AC8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070059D8, 0x0041a760, 37817, 0x000059d8, 240);

// 0x07005AC8 - 0x07005B78
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07005AC8, 0x0041a760, 37817, 0x00005ac8, 176);

// 0x07005B78 - 0x07005BF8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07005B78, 0x0041a760, 37817, 0x00005b78, 128);

// 0x07005BF8 - 0x07005CE8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07005BF8, 0x0041a760, 37817, 0x00005bf8, 240);

// 0x07005CE8 - 0x07005DD8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07005CE8, 0x0041a760, 37817, 0x00005ce8, 240);

// 0x07005DD8 - 0x07005EC8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07005DD8, 0x0041a760, 37817, 0x00005dd8, 240);

// 0x07005EC8 - 0x07005FB8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07005EC8, 0x0041a760, 37817, 0x00005ec8, 240);

// 0x07005FB8 - 0x070060B8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07005FB8, 0x0041a760, 37817, 0x00005fb8, 256);

// 0x070060B8 - 0x07006138
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070060B8, 0x0041a760, 37817, 0x000060b8, 128);

// 0x07006138 - 0x07006238
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006138, 0x0041a760, 37817, 0x00006138, 256);

// 0x07006238 - 0x07006318
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006238, 0x0041a760, 37817, 0x00006238, 224);

// 0x07006318 - 0x07006418
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006318, 0x0041a760, 37817, 0x00006318, 256);

// 0x07006418 - 0x070064C8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006418, 0x0041a760, 37817, 0x00006418, 176);

// 0x070064C8 - 0x07006508
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070064C8, 0x0041a760, 37817, 0x000064c8, 64);

// 0x07006508 - 0x070065A8
static const Gfx jrb_seg7_dl_07006508[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_07005990.l, 1),
    gsSPLight(&jrb_seg7_lights_07005990.a, 2),
    gsSPVertex(jrb_seg7_vertex_070059D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(jrb_seg7_vertex_07005AC8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070065A8 - 0x070067F0
static const Gfx jrb_seg7_dl_070065A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070059A8.l, 1),
    gsSPLight(&jrb_seg7_lights_070059A8.a, 2),
    gsSPVertex(jrb_seg7_vertex_07005B78, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  7,  5,  0, 0x0),
    gsSPLight(&jrb_seg7_lights_07005990.l, 1),
    gsSPLight(&jrb_seg7_lights_07005990.a, 2),
    gsSPVertex(jrb_seg7_vertex_07005BF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(jrb_seg7_vertex_07005CE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  6, 0x0, 10, 11,  7, 0x0),
    gsSP2Triangles( 9,  8, 12, 0x0,  9, 12, 13, 0x0),
    gsSP2Triangles(13, 11, 10, 0x0, 13, 12, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07005DD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0,  0, 13, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07005EC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 12,  2, 13, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07005FB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(13, 10, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_070060B8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070067F0 - 0x07006980
static const Gfx jrb_seg7_dl_070067F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_07006138, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  9,  7,  8, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 12, 15, 0x0),
    gsSP2Triangles(15, 12, 11, 0x0, 12, 14, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006238, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 6,  5,  9, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006318, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  7,  2,  1, 0x0),
    gsSP2Triangles( 3,  2,  8, 0x0,  2,  9,  8, 0x0),
    gsSP2Triangles( 3, 10, 11, 0x0, 12,  6,  5, 0x0),
    gsSP2Triangles(12, 13,  6, 0x0, 14, 13, 12, 0x0),
    gsSP1Triangle(15, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006418, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 9, 10,  4, 0x0, 10,  2,  4, 0x0),
    gsSP1Triangle( 2,  1,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006980 - 0x070069B0
static const Gfx jrb_seg7_dl_07006980[] = {
    gsSPLight(&jrb_seg7_lights_070059C0.l, 1),
    gsSPLight(&jrb_seg7_lights_070059C0.a, 2),
    gsSPVertex(jrb_seg7_vertex_070064C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070069B0 - 0x07006A98
const Gfx jrb_seg7_dl_070069B0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(15, 65, 100, 255),
    gsSPFogFactor(0x0724, 0xF9DC), // This isn't gsSPFogPosition since there is no valid min/max pair that corresponds to 0x0724F9DC
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07006508),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070065A8),
    gsSPDisplayList(jrb_seg7_dl_070067F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(jrb_seg7_dl_07006980),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
