#include "pc/rom_assets.h"
// 0x07064DC8 - 0x07064DE0
static const Lights1 inside_castle_seg7_lights_07064DC8 = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07064DE0 - 0x07064EE0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07064DE0, 0x00396340, 232834, 0x00064de0, 256);

// 0x07064EE0 - 0x07064FD0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07064EE0, 0x00396340, 232834, 0x00064ee0, 240);

// 0x07064FD0 - 0x070650D0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07064FD0, 0x00396340, 232834, 0x00064fd0, 256);

// 0x070650D0 - 0x070651C0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070650D0, 0x00396340, 232834, 0x000650d0, 240);

// 0x070651C0 - 0x070652B0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070651C0, 0x00396340, 232834, 0x000651c0, 240);

// 0x070652B0 - 0x070653A0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070652B0, 0x00396340, 232834, 0x000652b0, 240);

// 0x070653A0 - 0x07065460
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070653A0, 0x00396340, 232834, 0x000653a0, 192);

// 0x07065460 - 0x07065560
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065460, 0x00396340, 232834, 0x00065460, 256);

// 0x07065560 - 0x07065620
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065560, 0x00396340, 232834, 0x00065560, 192);

// 0x07065620 - 0x07065710
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065620, 0x00396340, 232834, 0x00065620, 240);

// 0x07065710 - 0x07065810
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065710, 0x00396340, 232834, 0x00065710, 256);

// 0x07065810 - 0x070658C0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065810, 0x00396340, 232834, 0x00065810, 176);

// 0x070658C0 - 0x070659C0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070658C0, 0x00396340, 232834, 0x000658c0, 256);

// 0x070659C0 - 0x07065AB0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070659C0, 0x00396340, 232834, 0x000659c0, 240);

// 0x07065AB0 - 0x07065BB0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065AB0, 0x00396340, 232834, 0x00065ab0, 256);

// 0x07065BB0 - 0x07065C90
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065BB0, 0x00396340, 232834, 0x00065bb0, 224);

// 0x07065C90 - 0x07065D80
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065C90, 0x00396340, 232834, 0x00065c90, 240);

// 0x07065D80 - 0x07065E70
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065D80, 0x00396340, 232834, 0x00065d80, 240);

// 0x07065E70 - 0x07065F50
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065E70, 0x00396340, 232834, 0x00065e70, 224);

// 0x07065F50 - 0x07066030
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07065F50, 0x00396340, 232834, 0x00065f50, 224);

// 0x07066030 - 0x07066110
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07066030, 0x00396340, 232834, 0x00066030, 224);

// 0x07066110 - 0x070661F0
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07066110, 0x00396340, 232834, 0x00066110, 224);

// 0x070661F0 - 0x07066260
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070661F0, 0x00396340, 232834, 0x000661f0, 112);

// 0x07066260 - 0x07066360
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07066260, 0x00396340, 232834, 0x00066260, 256);

// 0x07066360 - 0x07066460
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07066360, 0x00396340, 232834, 0x00066360, 256);

// 0x07066460 - 0x07066560
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07066460, 0x00396340, 232834, 0x00066460, 256);

// 0x07066560 - 0x07066768
static const Gfx inside_castle_seg7_dl_07066560[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_0900B000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07064DC8.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07064DC8.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07064DE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07064EE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07064FD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  5, 15,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070650D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070651C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070652B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 13, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070653A0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07066768 - 0x07066838
static const Gfx inside_castle_seg7_dl_07066768[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07065460, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065560, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 5,  6,  1, 0x0,  6,  7,  1, 0x0),
    gsSP2Triangles( 8,  4,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  4, 0x0,  6, 11,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07066838 - 0x07066910
static const Gfx inside_castle_seg7_dl_07066838[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07065620, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065710, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065810, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07066910 - 0x07066BE8
static const Gfx inside_castle_seg7_dl_07066910[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070658C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  9, 13, 12, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  0, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070659C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065AB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15,  9, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065BB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  6,  0,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065C90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065D80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065E70, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07065F50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07066030, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07066110, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  0,  5, 0x0,  6,  7,  0, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070661F0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07066BE8 - 0x07066CE0
static const Gfx inside_castle_seg7_dl_07066BE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_07066260, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07066360, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  8, 15,  9, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07066460, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  4, 11,  5, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07066CE0 - 0x07066D88
const Gfx inside_castle_seg7_dl_07066CE0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07066560),
    gsSPDisplayList(inside_castle_seg7_dl_07066768),
    gsSPDisplayList(inside_castle_seg7_dl_07066838),
    gsSPDisplayList(inside_castle_seg7_dl_07066910),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07066BE8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
