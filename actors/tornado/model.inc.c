#include "pc/rom_assets.h"
// Tornado

// 0x05013128
ROM_ASSET_LOAD_TEXTURE(tornado_seg5_texture_05013128, "actors/tornado/tornado.ia16.inc.c", 0x0013b910, 41727, 0x00012848, 4096);

// 0x05014128
static const Lights1 tornado_seg5_lights_05014128 = gdSPDefLights1(
    0x3b, 0x34, 0x23,
    0xee, 0xd0, 0x8d, 0x28, 0x28, 0x28
);

// 0x05014140
ROM_ASSET_LOAD_VTX(tornado_seg5_vertex_05014140, 0x00145e90, 48337, 0x00014140, 224);

// 0x05014220
ROM_ASSET_LOAD_VTX(tornado_seg5_vertex_05014220, 0x00145e90, 48337, 0x00014220, 256);

// 0x05014320
ROM_ASSET_LOAD_VTX(tornado_seg5_vertex_05014320, 0x00145e90, 48337, 0x00014320, 224);

// 0x05014400
ROM_ASSET_LOAD_VTX(tornado_seg5_vertex_05014400, 0x00145e90, 48337, 0x00014400, 80);

// 0x05014450 - 0x050145C0
const Gfx tornado_seg5_dl_05014450[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, tornado_seg5_texture_05013128),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tornado_seg5_lights_05014128.l, 1),
    gsSPLight(&tornado_seg5_lights_05014128.a, 2),
    gsSPVertex(tornado_seg5_vertex_05014140, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  3,  7,  5, 0x0),
    gsSP2Triangles( 1,  6,  8, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 1,  8, 10, 0x0, 11,  3, 12, 0x0),
    gsSP2Triangles(11, 13,  3, 0x0, 13,  7,  3, 0x0),
    gsSPVertex(tornado_seg5_vertex_05014220, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  8,  6,  3, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles( 2, 10,  8, 0x0, 11,  2,  8, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(tornado_seg5_vertex_05014320, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  3,  6,  5, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  9,  6,  3, 0x0),
    gsSP2Triangles( 7,  9,  3, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 13, 11, 0x0),
    gsSPVertex(tornado_seg5_vertex_05014400, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 3,  2,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x050145C0 - 0x05014630
const Gfx tornado_seg5_dl_050145C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(tornado_seg5_dl_05014450),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
