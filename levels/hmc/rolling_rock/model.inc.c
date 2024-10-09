#include "pc/rom_assets.h"
// 0x07023160 - 0x07023178
static const Lights1 hmc_seg7_lights_07023160 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07023178 - 0x07023278
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023178, 0x003d0dc0, 89137, 0x00023178, 256);

// 0x07023278 - 0x07023378
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023278, 0x003d0dc0, 89137, 0x00023278, 256);

// 0x07023378 - 0x07023478
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023378, 0x003d0dc0, 89137, 0x00023378, 256);

// 0x07023478 - 0x07023558
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023478, 0x003d0dc0, 89137, 0x00023478, 224);

// 0x07023558 - 0x07023638
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023558, 0x003d0dc0, 89137, 0x00023558, 224);

// 0x07023638 - 0x07023728
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023638, 0x003d0dc0, 89137, 0x00023638, 240);

// 0x07023728 - 0x07023828
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023728, 0x003d0dc0, 89137, 0x00023728, 256);

// 0x07023828 - 0x070238D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023828, 0x003d0dc0, 89137, 0x00023828, 176);

// 0x070238D8 - 0x07023BC8
static const Gfx hmc_seg7_dl_070238D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07023160.l, 1),
    gsSPLight(&hmc_seg7_lights_07023160.a, 2),
    gsSPVertex(hmc_seg7_vertex_07023178, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 1,  4,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0,  7, 10,  9, 0x0),
    gsSP2Triangles( 8,  9, 11, 0x0,  1, 12,  2, 0x0),
    gsSP2Triangles( 1,  6, 12, 0x0,  2, 12, 13, 0x0),
    gsSP1Triangle( 6, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07023278, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  6, 11,  7, 0x0),
    gsSP2Triangles( 7, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07023378, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0,  6, 10, 12, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07023478, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  9, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 10,  4, 12, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07023558, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  1,  7,  6, 0x0),
    gsSP2Triangles( 2,  6,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07023638, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 1,  5,  7, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  8, 11, 10, 0x0),
    gsSP2Triangles( 9, 10, 12, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 1,  7, 13, 0x0,  2, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07023728, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0, 12, 14, 13, 0x0),
    gsSP2Triangles(12,  5, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07023828, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  1,  7,  6, 0x0),
    gsSP2Triangles( 2,  6,  8, 0x0,  7,  9,  3, 0x0),
    gsSP2Triangles( 9,  4,  3, 0x0,  9, 10,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07023BC8 - 0x07023C70
const Gfx hmc_seg7_dl_07023BC8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(960, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_070238D8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
