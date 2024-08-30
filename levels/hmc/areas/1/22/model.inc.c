#include "pc/rom_assets.h"
// 0x07019430 - 0x07019448
static const Lights1 hmc_seg7_lights_07019430 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07019448 - 0x07019548
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019448, 0x003d0dc0, 89137, 0x00019448, 256);

// 0x07019548 - 0x07019588
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019548, 0x003d0dc0, 89137, 0x00019548, 64);

// 0x07019588 - 0x07019678
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019588, 0x003d0dc0, 89137, 0x00019588, 240);

// 0x07019678 - 0x07019758
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019678, 0x003d0dc0, 89137, 0x00019678, 224);

// 0x07019758 - 0x07019848
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019758, 0x003d0dc0, 89137, 0x00019758, 240);

// 0x07019848 - 0x07019938
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019848, 0x003d0dc0, 89137, 0x00019848, 240);

// 0x07019938 - 0x070199D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019938, 0x003d0dc0, 89137, 0x00019938, 160);

// 0x070199D8 - 0x07019AD8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070199D8, 0x003d0dc0, 89137, 0x000199d8, 256);

// 0x07019AD8 - 0x07019BC8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019AD8, 0x003d0dc0, 89137, 0x00019ad8, 240);

// 0x07019BC8 - 0x07019CB8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019BC8, 0x003d0dc0, 89137, 0x00019bc8, 240);

// 0x07019CB8 - 0x07019D18
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07019CB8, 0x003d0dc0, 89137, 0x00019cb8, 96);

// 0x07019D18 - 0x07019DC8
static const Gfx hmc_seg7_dl_07019D18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07019430.l, 1),
    gsSPLight(&hmc_seg7_lights_07019430.a, 2),
    gsSPVertex(hmc_seg7_vertex_07019448, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 6,  9,  8, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019548, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019DC8 - 0x07019F70
static const Gfx hmc_seg7_dl_07019DC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07019588, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  6,  8, 11, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0,  8,  2, 11, 0x0),
    gsSP2Triangles( 8,  3,  0, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 8, 10,  3, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019678, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019758, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019848, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 7,  3,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 10, 14, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019938, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  2,  1,  8, 0x0),
    gsSP2Triangles( 2,  7,  9, 0x0,  2,  9,  3, 0x0),
    gsSP2Triangles( 2,  8,  7, 0x0,  7,  8,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019F70 - 0x0701A080
static const Gfx hmc_seg7_dl_07019F70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070199D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 9,  2, 10, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019AD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019BC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 3,  2,  8, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  4, 0x0, 10, 11,  7, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_07019CB8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701A080 - 0x0701A150
const Gfx hmc_seg7_dl_0701A080[] = {
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
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07019D18),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07019DC8),
    gsSPDisplayList(hmc_seg7_dl_07019F70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
