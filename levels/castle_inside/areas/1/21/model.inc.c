#include "pc/rom_assets.h"
// 0x07037C58 - 0x07037C70
static const Lights1 inside_castle_seg7_lights_07037C58 = gdSPDefLights1(
    0x37, 0x37, 0x37,
    0xdd, 0xdd, 0xdd, 0x28, 0x28, 0x28
);

// 0x07037C70 - 0x07037D70
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07037C70, 0x00396340, 232834, 0x00037c70, 256);

// 0x07037D70 - 0x07037DE8
static const Gfx inside_castle_seg7_dl_07037D70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07037C58.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07037C58.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07037C70, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07037DE8 - 0x07037E38
const Gfx inside_castle_seg7_dl_07037DE8[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetEnvColor(255, 255, 255, 100),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(inside_castle_seg7_dl_07037D70),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
