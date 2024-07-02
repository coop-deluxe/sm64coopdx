#include "pc/rom_assets.h"
// 0x07004030 - 0x07004048
static const Lights1 bowser_3_seg7_lights_07004030 = gdSPDefLights1(
    0x22, 0x22, 0x22,
    0x89, 0x89, 0x8a, 0x28, 0x28, 0x28
);

// 0x07004048 - 0x07004060
static const Lights1 bowser_3_seg7_lights_07004048 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07004060 - 0x07004160
ROM_ASSET_LOAD_VTX(bowser_3_seg7_vertex_07004060, 0x004cec00, 10476, 0x00004060, 256);

// 0x07004160 - 0x070041C0
ROM_ASSET_LOAD_VTX(bowser_3_seg7_vertex_07004160, 0x004cec00, 10476, 0x00004160, 96);

// 0x070041C0 - 0x07004260
ROM_ASSET_LOAD_VTX(bowser_3_seg7_vertex_070041C0, 0x004cec00, 10476, 0x000041c0, 160);

// 0x07004260 - 0x07004350
ROM_ASSET_LOAD_VTX(bowser_3_seg7_vertex_07004260, 0x004cec00, 10476, 0x00004260, 240);

// 0x07004350 - 0x07004440
ROM_ASSET_LOAD_VTX(bowser_3_seg7_vertex_07004350, 0x004cec00, 10476, 0x00004350, 240);

// 0x07004440 - 0x07004500
ROM_ASSET_LOAD_VTX(bowser_3_seg7_vertex_07004440, 0x004cec00, 10476, 0x00004440, 192);

// 0x07004500 - 0x070045D8
static const Gfx bowser_3_seg7_dl_07004500[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bowser_3_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bowser_3_seg7_lights_07004030.l, 1),
    gsSPLight(&bowser_3_seg7_lights_07004030.a, 2),
    gsSPVertex(bowser_3_seg7_vertex_07004060, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 6,  8, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bowser_3_seg7_vertex_07004160, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&bowser_3_seg7_lights_07004048.l, 1),
    gsSPLight(&bowser_3_seg7_lights_07004048.a, 2),
    gsSPVertex(bowser_3_seg7_vertex_070041C0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 3,  8,  5, 0x0,  5,  9,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x070045D8 - 0x070046B0
static const Gfx bowser_3_seg7_dl_070045D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bowser_3_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_3_seg7_vertex_07004260, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bowser_3_seg7_vertex_07004350, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bowser_3_seg7_vertex_07004440, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x070046B0 - 0x07004740
const Gfx bowser_3_seg7_dl_070046B0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bowser_3_seg7_dl_07004500),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bowser_3_seg7_dl_070045D8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
