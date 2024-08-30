#include "pc/rom_assets.h"
// 0x0701FD60 - 0x0701FD78
static const Lights1 ssl_seg7_lights_0701FD60 = gdSPDefLights1(
    0x46, 0x46, 0x46,
    0x8c, 0x8c, 0x8c, 0x28, 0x28, 0x28
);

// 0x0701FD78 - 0x0701FD90
static const Lights1 ssl_seg7_lights_0701FD78 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701FD90 - 0x0701FE50
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701FD90, 0x003e76b0, 82641, 0x0001fd90, 192);

// 0x0701FE50 - 0x0701FF40
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701FE50, 0x003e76b0, 82641, 0x0001fe50, 240);

// 0x0701FF40 - 0x07020030
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701FF40, 0x003e76b0, 82641, 0x0001ff40, 240);

// 0x07020030 - 0x07020120
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020030, 0x003e76b0, 82641, 0x00020030, 240);

// 0x07020120 - 0x07020210
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020120, 0x003e76b0, 82641, 0x00020120, 240);

// 0x07020210 - 0x07020300
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020210, 0x003e76b0, 82641, 0x00020210, 240);

// 0x07020300 - 0x070203F0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020300, 0x003e76b0, 82641, 0x00020300, 240);

// 0x070203F0 - 0x070204E0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070203F0, 0x003e76b0, 82641, 0x000203f0, 240);

// 0x070204E0 - 0x07020550
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070204E0, 0x003e76b0, 82641, 0x000204e0, 112);

// 0x07020550 - 0x070205D0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020550, 0x003e76b0, 82641, 0x00020550, 128);

// 0x070205D0 - 0x070206C0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070205D0, 0x003e76b0, 82641, 0x000205d0, 240);

// 0x070206C0 - 0x070207B0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070206C0, 0x003e76b0, 82641, 0x000206c0, 240);

// 0x070207B0 - 0x07020870
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070207B0, 0x003e76b0, 82641, 0x000207b0, 192);

// 0x07020870 - 0x07020950
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020870, 0x003e76b0, 82641, 0x00020870, 224);

// 0x07020950 - 0x07020A20
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020950, 0x003e76b0, 82641, 0x00020950, 208);

// 0x07020A20 - 0x07020B20
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020A20, 0x003e76b0, 82641, 0x00020a20, 256);

// 0x07020B20 - 0x07020C20
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020B20, 0x003e76b0, 82641, 0x00020b20, 256);

// 0x07020C20 - 0x07020D10
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020C20, 0x003e76b0, 82641, 0x00020c20, 240);

// 0x07020D10 - 0x07020E00
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020D10, 0x003e76b0, 82641, 0x00020d10, 240);

// 0x07020E00 - 0x07020EB0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020E00, 0x003e76b0, 82641, 0x00020e00, 176);

// 0x07020EB0 - 0x07020FB0
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020EB0, 0x003e76b0, 82641, 0x00020eb0, 256);

// 0x07020FB0 - 0x07021090
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07020FB0, 0x003e76b0, 82641, 0x00020fb0, 224);

// 0x07021090 - 0x07021150
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07021090, 0x003e76b0, 82641, 0x00021090, 192);

// 0x07021150 - 0x07021250
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07021150, 0x003e76b0, 82641, 0x00021150, 256);

// 0x07021250 - 0x07021290
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07021250, 0x003e76b0, 82641, 0x00021250, 64);

// 0x07021290 - 0x070214E8
static const Gfx ssl_seg7_dl_07021290[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_0701FD60.l, 1),
    gsSPLight(&ssl_seg7_lights_0701FD60.a, 2),
    gsSPVertex(ssl_seg7_vertex_0701FD90, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPLight(&ssl_seg7_lights_0701FD78.l, 1),
    gsSPLight(&ssl_seg7_lights_0701FD78.a, 2),
    gsSPVertex(ssl_seg7_vertex_0701FE50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701FF40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020030, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020120, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020210, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020300, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070203F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_070204E0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x070214E8 - 0x07021638
static const Gfx ssl_seg7_dl_070214E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_0701FD60.l, 1),
    gsSPLight(&ssl_seg7_lights_0701FD60.a, 2),
    gsSPVertex(ssl_seg7_vertex_07020550, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 1,  6,  5, 0x0,  3,  4,  7, 0x0),
    gsSP2Triangles( 5,  7,  4, 0x0,  5,  6,  7, 0x0),
    gsSPLight(&ssl_seg7_lights_0701FD78.l, 1),
    gsSPLight(&ssl_seg7_lights_0701FD78.a, 2),
    gsSPVertex(ssl_seg7_vertex_070205D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070206C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070207B0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  4,  6,  9, 0x0),
    gsSP2Triangles(10,  4,  9, 0x0, 10,  9, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07021638 - 0x07021870
static const Gfx ssl_seg7_dl_07021638[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_0701FD60.l, 1),
    gsSPLight(&ssl_seg7_lights_0701FD60.a, 2),
    gsSPVertex(ssl_seg7_vertex_07020870, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles( 7,  9, 12, 0x0, 13,  7, 12, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020950, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle( 0,  2, 12, 0x0),
    gsSPLight(&ssl_seg7_lights_0701FD78.l, 1),
    gsSPLight(&ssl_seg7_lights_0701FD78.a, 2),
    gsSPVertex(ssl_seg7_vertex_07020A20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13,  2, 0x0, 14, 15,  0, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020B20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020C20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020D10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020E00, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  4, 0x0,  9, 10,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07021870 - 0x07021910
static const Gfx ssl_seg7_dl_07021870[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07020EB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  0,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07020FB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  7, 13,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07021910 - 0x07021968
static const Gfx ssl_seg7_dl_07021910[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_seg7_texture_07001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07021090, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07021968 - 0x070219D0
static const Gfx ssl_seg7_dl_07021968[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07021150, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070219D0 - 0x07021A08
static const Gfx ssl_seg7_dl_070219D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07021250, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07021A08 - 0x07021AC8
const Gfx ssl_seg7_dl_07021A08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_07021290),
    gsSPDisplayList(ssl_seg7_dl_070214E8),
    gsSPDisplayList(ssl_seg7_dl_07021638),
    gsSPDisplayList(ssl_seg7_dl_07021870),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_07021910),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_07021968),
    gsSPDisplayList(ssl_seg7_dl_070219D0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
