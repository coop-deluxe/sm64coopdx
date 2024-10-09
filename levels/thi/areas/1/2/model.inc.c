#include "pc/rom_assets.h"
// 0x07005330 - 0x07005348
static const Lights1 thi_seg7_lights_07005330 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07005348 - 0x07005360
static const Lights1 thi_seg7_lights_07005348 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07005360 - 0x07005378
static const Lights1 thi_seg7_lights_07005360 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07005378 - 0x07005390
static const Lights1 thi_seg7_lights_07005378 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07005390 - 0x07005470
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005390, 0x004246d0, 32780, 0x00005390, 224);

// 0x07005470 - 0x07005550
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005470, 0x004246d0, 32780, 0x00005470, 224);

// 0x07005550 - 0x070055D0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005550, 0x004246d0, 32780, 0x00005550, 128);

// 0x070055D0 - 0x070056C0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070055D0, 0x004246d0, 32780, 0x000055d0, 240);

// 0x070056C0 - 0x070057B0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070056C0, 0x004246d0, 32780, 0x000056c0, 240);

// 0x070057B0 - 0x07005890
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070057B0, 0x004246d0, 32780, 0x000057b0, 224);

// 0x07005890 - 0x07005990
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005890, 0x004246d0, 32780, 0x00005890, 256);

// 0x07005990 - 0x07005A80
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005990, 0x004246d0, 32780, 0x00005990, 240);

// 0x07005A80 - 0x07005B70
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005A80, 0x004246d0, 32780, 0x00005a80, 240);

// 0x07005B70 - 0x07005C30
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005B70, 0x004246d0, 32780, 0x00005b70, 192);

// 0x07005C30 - 0x07005D30
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005C30, 0x004246d0, 32780, 0x00005c30, 256);

// 0x07005D30 - 0x07005DA0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005D30, 0x004246d0, 32780, 0x00005d30, 112);

// 0x07005DA0 - 0x07005EA0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005DA0, 0x004246d0, 32780, 0x00005da0, 256);

// 0x07005EA0 - 0x07005FA0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005EA0, 0x004246d0, 32780, 0x00005ea0, 256);

// 0x07005FA0 - 0x07005FE0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005FA0, 0x004246d0, 32780, 0x00005fa0, 64);

// 0x07005FE0 - 0x070060E0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07005FE0, 0x004246d0, 32780, 0x00005fe0, 256);

// 0x070060E0 - 0x070061D0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070060E0, 0x004246d0, 32780, 0x000060e0, 240);

// 0x070061D0 - 0x070062C0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070061D0, 0x004246d0, 32780, 0x000061d0, 240);

// 0x070062C0 - 0x070063C0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070062C0, 0x004246d0, 32780, 0x000062c0, 256);

// 0x070063C0 - 0x07006660
static const Gfx thi_seg7_dl_070063C0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07005330.l, 1),
    gsSPLight(&thi_seg7_lights_07005330.a, 2),
    gsSPVertex(thi_seg7_vertex_07005390, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07005470, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07005550, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&thi_seg7_lights_07005348.l, 1),
    gsSPLight(&thi_seg7_lights_07005348.a, 2),
    gsSPVertex(thi_seg7_vertex_070055D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_070056C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(thi_seg7_vertex_070057B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07005890, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07005990, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14,  0, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(thi_seg7_vertex_07005A80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(thi_seg7_vertex_07005B70, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  3, 11,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006660 - 0x07006770
static const Gfx thi_seg7_dl_07006660[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07005330.l, 1),
    gsSPLight(&thi_seg7_lights_07005330.a, 2),
    gsSPVertex(thi_seg7_vertex_07005C30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 7,  3,  6, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 5,  4, 10, 0x0, 11,  8,  7, 0x0),
    gsSP2Triangles(11,  9,  8, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07005D30, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  3,  5, 0x0),
    gsSPLight(&thi_seg7_lights_07005360.l, 1),
    gsSPLight(&thi_seg7_lights_07005360.a, 2),
    gsSPVertex(thi_seg7_vertex_07005DA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006770 - 0x07006800
static const Gfx thi_seg7_dl_07006770[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07005348.l, 1),
    gsSPLight(&thi_seg7_lights_07005348.a, 2),
    gsSPVertex(thi_seg7_vertex_07005EA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07005FA0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006800 - 0x07006868
static const Gfx thi_seg7_dl_07006800[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_07005FE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006868 - 0x07006908
static const Gfx thi_seg7_dl_07006868[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_070060E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_070061D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006908 - 0x07006968
static const Gfx thi_seg7_dl_07006908[] = {
    gsSPLight(&thi_seg7_lights_07005378.l, 1),
    gsSPLight(&thi_seg7_lights_07005378.a, 2),
    gsSPVertex(thi_seg7_vertex_070062C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006968 - 0x07006A30
const Gfx thi_seg7_dl_07006968[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_070063C0),
    gsSPDisplayList(thi_seg7_dl_07006660),
    gsSPDisplayList(thi_seg7_dl_07006770),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07006800),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07006868),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(thi_seg7_dl_07006908),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
