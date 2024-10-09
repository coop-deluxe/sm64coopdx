#include "pc/rom_assets.h"
// 0x07004D40 - 0x07004D58
static const Lights1 jrb_seg7_lights_07004D40 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07004D58 - 0x07004D70
static const Lights1 jrb_seg7_lights_07004D58 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07004D70 - 0x07004DF0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07004D70, 0x0041a760, 37817, 0x00004d70, 128);

// 0x07004DF0 - 0x07004EF0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07004DF0, 0x0041a760, 37817, 0x00004df0, 256);

// 0x07004EF0 - 0x07004FF0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07004EF0, 0x0041a760, 37817, 0x00004ef0, 256);

// 0x07004FF0 - 0x070050F0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07004FF0, 0x0041a760, 37817, 0x00004ff0, 256);

// 0x070050F0 - 0x070051F0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070050F0, 0x0041a760, 37817, 0x000050f0, 256);

// 0x070051F0 - 0x070052F0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070051F0, 0x0041a760, 37817, 0x000051f0, 256);

// 0x070052F0 - 0x070053F0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070052F0, 0x0041a760, 37817, 0x000052f0, 256);

// 0x070053F0 - 0x070054E0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070053F0, 0x0041a760, 37817, 0x000053f0, 240);

// 0x070054E0 - 0x07005560
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070054E0, 0x0041a760, 37817, 0x000054e0, 128);

// 0x07005560 - 0x07005660
static const Gfx jrb_seg7_dl_07005560[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_07004D40.l, 1),
    gsSPLight(&jrb_seg7_lights_07004D40.a, 2),
    gsSPVertex(jrb_seg7_vertex_07004D70, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  4,  5, 0x0),
    gsSPLight(&jrb_seg7_lights_07004D58.l, 1),
    gsSPLight(&jrb_seg7_lights_07004D58.a, 2),
    gsSPVertex(jrb_seg7_vertex_07004DF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  5,  0, 0x0,  8,  9,  5, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 13, 11, 0x0),
    gsSP2Triangles(14, 13, 12, 0x0, 14, 15, 13, 0x0),
    gsSP2Triangles( 6, 15, 14, 0x0,  6,  7, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005660 - 0x070058C8
static const Gfx jrb_seg7_dl_07005660[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_07004EF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  4,  3,  7, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07004FF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 15, 12, 0x0, 14, 12, 11, 0x0),
    gsSPVertex(jrb_seg7_vertex_070050F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 5, 12, 11, 0x0,  6,  5, 11, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_070051F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 10, 15, 11, 0x0),
    gsSPVertex(jrb_seg7_vertex_070052F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_070053F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  5,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles( 9, 10,  5, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 13, 12, 11, 0x0),
    gsSP1Triangle(13, 14, 12, 0x0),
    gsSPVertex(jrb_seg7_vertex_070054E0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP1Triangle( 6,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070058C8 - 0x07005990
const Gfx jrb_seg7_dl_070058C8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07005560),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07005660),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
