#include "pc/rom_assets.h"
// 0x07005FC8 - 0x07005FE0
static const Lights1 ddd_seg7_lights_07005FC8 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07005FE0 - 0x07005FF8
static const Lights1 ddd_seg7_lights_07005FE0 = gdSPDefLights1(
    0x1b, 0x1b, 0x1b,
    0x44, 0x44, 0x44, 0x28, 0x28, 0x28
);

// 0x07005FF8 - 0x07006010
static const Lights1 ddd_seg7_lights_07005FF8 = gdSPDefLights1(
    0x2f, 0x2f, 0x2f,
    0x77, 0x77, 0x77, 0x28, 0x28, 0x28
);

// 0x07006010 - 0x07006028
static const Lights1 ddd_seg7_lights_07006010 = gdSPDefLights1(
    0x44, 0x44, 0x44,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x07006028 - 0x07006040
static const Lights1 ddd_seg7_lights_07006028 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07006040 - 0x07006080
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006040, 0x0048d930, 33063, 0x00006040, 64);

// 0x07006080 - 0x070060C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006080, 0x0048d930, 33063, 0x00006080, 64);

// 0x070060C0 - 0x07006100
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070060C0, 0x0048d930, 33063, 0x000060c0, 64);

// 0x07006100 - 0x07006140
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006100, 0x0048d930, 33063, 0x00006100, 64);

// 0x07006140 - 0x070061C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006140, 0x0048d930, 33063, 0x00006140, 128);

// 0x070061C0 - 0x07006240
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070061C0, 0x0048d930, 33063, 0x000061c0, 128);

// 0x07006240 - 0x070062C0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006240, 0x0048d930, 33063, 0x00006240, 128);

// 0x070062C0 - 0x070063B0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070062C0, 0x0048d930, 33063, 0x000062c0, 240);

// 0x070063B0 - 0x070064A0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070063B0, 0x0048d930, 33063, 0x000063b0, 240);

// 0x070064A0 - 0x07006520
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070064A0, 0x0048d930, 33063, 0x000064a0, 128);

// 0x07006520 - 0x07006560
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006520, 0x0048d930, 33063, 0x00006520, 64);

// 0x07006560 - 0x070065A0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006560, 0x0048d930, 33063, 0x00006560, 64);

// 0x070065A0 - 0x070065E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070065A0, 0x0048d930, 33063, 0x000065a0, 64);

// 0x070065E0 - 0x070066E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070065E0, 0x0048d930, 33063, 0x000065e0, 256);

// 0x070066E0 - 0x070067E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070066E0, 0x0048d930, 33063, 0x000066e0, 256);

// 0x070067E0 - 0x070068E0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070067E0, 0x0048d930, 33063, 0x000067e0, 256);

// 0x070068E0 - 0x070069B0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070068E0, 0x0048d930, 33063, 0x000068e0, 208);

// 0x070069B0 - 0x07006AA0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_070069B0, 0x0048d930, 33063, 0x000069b0, 240);

// 0x07006AA0 - 0x07006BA0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006AA0, 0x0048d930, 33063, 0x00006aa0, 256);

// 0x07006BA0 - 0x07006C80
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006BA0, 0x0048d930, 33063, 0x00006ba0, 224);

// 0x07006C80 - 0x07006D70
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006C80, 0x0048d930, 33063, 0x00006c80, 240);

// 0x07006D70 - 0x07006E20
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07006D70, 0x0048d930, 33063, 0x00006d70, 176);

// 0x07006E20 - 0x07006EE0
static const Gfx ddd_seg7_dl_07006E20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_07005FC8.l, 1),
    gsSPLight(&ddd_seg7_lights_07005FC8.a, 2),
    gsSPVertex(ddd_seg7_vertex_07006040, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ddd_seg7_lights_07005FE0.l, 1),
    gsSPLight(&ddd_seg7_lights_07005FE0.a, 2),
    gsSPVertex(ddd_seg7_vertex_07006080, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ddd_seg7_lights_07005FF8.l, 1),
    gsSPLight(&ddd_seg7_lights_07005FF8.a, 2),
    gsSPVertex(ddd_seg7_vertex_070060C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ddd_seg7_lights_07006010.l, 1),
    gsSPLight(&ddd_seg7_lights_07006010.a, 2),
    gsSPVertex(ddd_seg7_vertex_07006100, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006EE0 - 0x07007080
static const Gfx ddd_seg7_dl_07006EE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_07005FE0.l, 1),
    gsSPLight(&ddd_seg7_lights_07005FE0.a, 2),
    gsSPVertex(ddd_seg7_vertex_07006140, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ddd_seg7_lights_07005FF8.l, 1),
    gsSPLight(&ddd_seg7_lights_07005FF8.a, 2),
    gsSPVertex(ddd_seg7_vertex_070061C0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ddd_seg7_lights_07006010.l, 1),
    gsSPLight(&ddd_seg7_lights_07006010.a, 2),
    gsSPVertex(ddd_seg7_vertex_07006240, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ddd_seg7_lights_07006028.l, 1),
    gsSPLight(&ddd_seg7_lights_07006028.a, 2),
    gsSPVertex(ddd_seg7_vertex_070062C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  4, 0x0,  9,  8,  6, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_070063B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ddd_seg7_vertex_070064A0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007080 - 0x07007298
static const Gfx ddd_seg7_dl_07007080[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_07005FE0.l, 1),
    gsSPLight(&ddd_seg7_lights_07005FE0.a, 2),
    gsSPVertex(ddd_seg7_vertex_07006520, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ddd_seg7_lights_07005FF8.l, 1),
    gsSPLight(&ddd_seg7_lights_07005FF8.a, 2),
    gsSPVertex(ddd_seg7_vertex_07006560, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ddd_seg7_lights_07006010.l, 1),
    gsSPLight(&ddd_seg7_lights_07006010.a, 2),
    gsSPVertex(ddd_seg7_vertex_070065A0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ddd_seg7_lights_07006028.l, 1),
    gsSPLight(&ddd_seg7_lights_07006028.a, 2),
    gsSPVertex(ddd_seg7_vertex_070065E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 6,  9,  8, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(11,  3, 10, 0x0,  2,  1, 11, 0x0),
    gsSP2Triangles( 2, 11, 12, 0x0, 13, 10, 14, 0x0),
    gsSP1Triangle( 0, 15,  1, 0x0),
    gsSPVertex(ddd_seg7_vertex_070066E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14,  2,  6, 0x0),
    gsSP2Triangles( 2,  7,  6, 0x0, 15,  2, 14, 0x0),
    gsSP1Triangle(15,  3,  2, 0x0),
    gsSPVertex(ddd_seg7_vertex_070067E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  0,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles(10,  9, 13, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_070068E0, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007298 - 0x07007408
static const Gfx ddd_seg7_dl_07007298[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ddd_seg7_vertex_070069B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_07006AA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ddd_seg7_vertex_07006BA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ddd_seg7_vertex_07006C80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_07006D70, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007408 - 0x070074C8
const Gfx ddd_seg7_dl_07007408[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_07006E20),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_07006EE0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_07007080),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_07007298),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
