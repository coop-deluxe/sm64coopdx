#include "pc/rom_assets.h"
// 0x070074C8 - 0x070074E0
static const Lights1 ddd_seg7_lights_070074C8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070074E0 - 0x070075E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070074E0, 0x0048d930, 33063, 0x000074e0, 256);

// 0x070075E0 - 0x070076C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070075E0, 0x0048d930, 33063, 0x000075e0, 224);

// 0x070076C0 - 0x070077B0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070076C0, 0x0048d930, 33063, 0x000076c0, 240);

// 0x070077B0 - 0x070078B0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070077B0, 0x0048d930, 33063, 0x000077b0, 256);

// 0x070078B0 - 0x070079A0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070078B0, 0x0048d930, 33063, 0x000078b0, 240);

// 0x070079A0 - 0x07007A80
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070079A0, 0x0048d930, 33063, 0x000079a0, 224);

// 0x07007A80 - 0x07007AF0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07007A80, 0x0048d930, 33063, 0x00007a80, 112);

// 0x07007AF0 - 0x07007CB8
static const Gfx ddd_seg7_dl_07007AF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_070074C8.l, 1),
    gsSPLight(&ddd_seg7_lights_070074C8.a, 2),
    gsSPVertex(ddd_seg7_vertex_070074E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12,  0, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_070075E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ddd_seg7_vertex_070076C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  0, 14,  1, 0x0),
    gsSPVertex(ddd_seg7_vertex_070077B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_070078B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_070079A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ddd_seg7_vertex_07007A80, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007CB8 - 0x07007D18
const Gfx ddd_seg7_dl_07007CB8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_07007AF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
