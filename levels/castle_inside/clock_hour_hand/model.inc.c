#include "pc/rom_assets.h"
// 0x070589C0 - 0x070589D8
static const Lights1 inside_castle_seg7_lights_070589C0 = gdSPDefLights1(
    0x3f, 0x33, 0x19,
    0xff, 0xcc, 0x65, 0x28, 0x28, 0x28
);

// 0x070589D8 - 0x070589F0
static const Lights1 inside_castle_seg7_lights_070589D8 = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x070589F0 - 0x07058AF0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070589F0, 0x00396340, 232834, 0x000589f0, 256);

// 0x07058AF0 - 0x07058BD0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058AF0, 0x00396340, 232834, 0x00058af0, 224);

// 0x07058BD0 - 0x07058CD0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058BD0, 0x00396340, 232834, 0x00058bd0, 256);

// 0x07058CD0 - 0x07058DB0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058CD0, 0x00396340, 232834, 0x00058cd0, 224);

// 0x07058DB0 - 0x07058E50
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058DB0, 0x00396340, 232834, 0x00058db0, 160);

// 0x07058E50 - 0x07058F50
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058E50, 0x00396340, 232834, 0x00058e50, 256);

// 0x07058F50 - 0x07058FC0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07058F50, 0x00396340, 232834, 0x00058f50, 112);

// 0x07058FC0 - 0x07059190
static const Gfx inside_castle_seg7_dl_07058FC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_070589C0.l, 1),
    gsSPLight(&inside_castle_seg7_lights_070589C0.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070589F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 8, 10, 14, 0x0, 11, 15, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07058AF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07058BD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  5,  4, 13, 0x0),
    gsSP2Triangles(10, 12, 14, 0x0,  5, 13, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07058CD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4,  6, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07058DB0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSPLight(&inside_castle_seg7_lights_070589D8.l, 1),
    gsSPLight(&inside_castle_seg7_lights_070589D8.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07058E50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07058F50, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  6,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07059190 - 0x07059200
const Gfx inside_castle_seg7_dl_07059190[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07058FC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
