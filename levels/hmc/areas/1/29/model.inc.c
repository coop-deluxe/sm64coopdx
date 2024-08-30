#include "pc/rom_assets.h"
// 0x070200B0 - 0x070200C8
static const Lights1 hmc_seg7_lights_070200B0 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070200C8 - 0x070201C8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070200C8, 0x003d0dc0, 89137, 0x000200c8, 256);

// 0x070201C8 - 0x07020248
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070201C8, 0x003d0dc0, 89137, 0x000201c8, 128);

// 0x07020248 - 0x07020308
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07020248, 0x003d0dc0, 89137, 0x00020248, 192);

// 0x07020308 - 0x070203E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07020308, 0x003d0dc0, 89137, 0x00020308, 224);

// 0x070203E8 - 0x070204E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070203E8, 0x003d0dc0, 89137, 0x000203e8, 256);

// 0x070204E8 - 0x070205E8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070204E8, 0x003d0dc0, 89137, 0x000204e8, 256);

// 0x070205E8 - 0x070206D8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070205E8, 0x003d0dc0, 89137, 0x000205e8, 240);

// 0x070206D8 - 0x070207C8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070206D8, 0x003d0dc0, 89137, 0x000206d8, 240);

// 0x070207C8 - 0x070208B8
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070207C8, 0x003d0dc0, 89137, 0x000207c8, 240);

// 0x070208B8 - 0x07020998
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070208B8, 0x003d0dc0, 89137, 0x000208b8, 224);

// 0x07020998 - 0x07020A98
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07020998, 0x003d0dc0, 89137, 0x00020998, 256);

// 0x07020A98 - 0x07020B18
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07020A98, 0x003d0dc0, 89137, 0x00020a98, 128);

// 0x07020B18 - 0x07020BD8
static const Gfx hmc_seg7_dl_07020B18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_070200B0.l, 1),
    gsSPLight(&hmc_seg7_lights_070200B0.a, 2),
    gsSPVertex(hmc_seg7_vertex_070200C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9,  7,  8, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 10,  8,  4, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles(11, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070201C8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07020BD8 - 0x07020C60
static const Gfx hmc_seg7_dl_07020BD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07020248, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0, 11,  2,  9, 0x0),
    gsSP2Triangles(11, 10,  2, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07020C60 - 0x07020D50
static const Gfx hmc_seg7_dl_07020C60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07020308, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 9,  8,  4, 0x0,  8,  5,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_070203E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11,  1, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles( 0,  2, 13, 0x0, 13,  2, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07020D50 - 0x07020EA0
static const Gfx hmc_seg7_dl_07020D50[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070204E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070205E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_070206D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_070207C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07020EA0 - 0x07020F90
static const Gfx hmc_seg7_dl_07020EA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_070208B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0,  6, 11,  7, 0x0),
    gsSP2Triangles( 5, 12, 13, 0x0,  5,  4, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_07020998, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 0,  7, 10, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles( 7,  9, 11, 0x0,  0, 10,  1, 0x0),
    gsSP2Triangles(12,  0, 13, 0x0, 12,  8,  7, 0x0),
    gsSP2Triangles( 0,  2, 13, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles( 8, 15,  9, 0x0, 12,  7,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07020F90 - 0x07020FD0
static const Gfx hmc_seg7_dl_07020F90[] = {
    gsSPVertex(hmc_seg7_vertex_07020A98, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  6,  4, 0x0),
    gsSP2Triangles( 0,  7,  3, 0x0,  0,  5,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07020FD0 - 0x070210E0
const Gfx hmc_seg7_dl_07020FD0[] = {
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
    gsSPDisplayList(hmc_seg7_dl_07020B18),
    gsSPDisplayList(hmc_seg7_dl_07020BD8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07020C60),
    gsSPDisplayList(hmc_seg7_dl_07020D50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07020EA0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(hmc_seg7_dl_07020F90),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
