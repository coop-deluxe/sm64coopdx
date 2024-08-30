#include "pc/rom_assets.h"
// 0x0700FEB8 - 0x0700FED0
static const Lights1 jrb_seg7_lights_0700FEB8 = gdSPDefLights1(
    0x50, 0x66, 0x58,
    0xc8, 0xff, 0xdc, 0x28, 0x28, 0x28
);

// 0x0700FED0 - 0x0700FFC0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700FED0, 0x0041a760, 37817, 0x0000fed0, 240);

// 0x0700FFC0 - 0x070100C0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700FFC0, 0x0041a760, 37817, 0x0000ffc0, 256);

// 0x070100C0 - 0x070101B0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070100C0, 0x0041a760, 37817, 0x000100c0, 240);

// 0x070101B0 - 0x07010290
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070101B0, 0x0041a760, 37817, 0x000101b0, 224);

// 0x07010290 - 0x07010390
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07010290, 0x0041a760, 37817, 0x00010290, 256);

// 0x07010390 - 0x07010548
static const Gfx jrb_seg7_dl_07010390[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_0700FEB8.l, 1),
    gsSPLight(&jrb_seg7_lights_0700FEB8.a, 2),
    gsSPVertex(jrb_seg7_vertex_0700FED0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0,  8, 11, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700FFC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_070100C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0,  6,  9, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070101B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(jrb_seg7_vertex_07010290, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0,  6, 11, 10, 0x0),
    gsSP2Triangles( 0, 12, 13, 0x0,  0, 14, 12, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  0, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010548 - 0x070105B8
const Gfx jrb_seg7_dl_07010548[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07010390),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
