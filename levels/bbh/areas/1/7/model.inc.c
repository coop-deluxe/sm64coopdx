#include "pc/rom_assets.h"
// 0x07008F18 - 0x07008F30
static const Lights1 bbh_seg7_lights_07008F18 = gdSPDefLights1(
    0x20, 0x20, 0x20,
    0x50, 0x50, 0x50, 0x28, 0x28, 0x28
);

// 0x07008F30 - 0x07008F48
static const Lights1 bbh_seg7_lights_07008F30 = gdSPDefLights1(
    0x3c, 0x3c, 0x3c,
    0x96, 0x96, 0x96, 0x28, 0x28, 0x28
);

// 0x07008F48 - 0x07008F60
static const Lights1 bbh_seg7_lights_07008F48 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07008F60 - 0x07008FE0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07008F60, 0x00371c40, 68724, 0x00008f60, 128);

// 0x07008FE0 - 0x070090E0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07008FE0, 0x00371c40, 68724, 0x00008fe0, 256);

// 0x070090E0 - 0x070091E0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070090E0, 0x00371c40, 68724, 0x000090e0, 256);

// 0x070091E0 - 0x070092D0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070091E0, 0x00371c40, 68724, 0x000091e0, 240);

// 0x070092D0 - 0x070093B0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070092D0, 0x00371c40, 68724, 0x000092d0, 224);

// 0x070093B0 - 0x070094A0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070093B0, 0x00371c40, 68724, 0x000093b0, 240);

// 0x070094A0 - 0x07009540
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070094A0, 0x00371c40, 68724, 0x000094a0, 160);

// 0x07009540 - 0x07009640
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009540, 0x00371c40, 68724, 0x00009540, 256);

// 0x07009640 - 0x07009720
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009640, 0x00371c40, 68724, 0x00009640, 224);

// 0x07009720 - 0x07009810
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009720, 0x00371c40, 68724, 0x00009720, 240);

// 0x07009810 - 0x070098F0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009810, 0x00371c40, 68724, 0x00009810, 224);

// 0x070098F0 - 0x070099F0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070098F0, 0x00371c40, 68724, 0x000098f0, 256);

// 0x070099F0 - 0x07009AE0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_070099F0, 0x00371c40, 68724, 0x000099f0, 240);

// 0x07009AE0 - 0x07009BD0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009AE0, 0x00371c40, 68724, 0x00009ae0, 240);

// 0x07009BD0 - 0x07009CB0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009BD0, 0x00371c40, 68724, 0x00009bd0, 224);

// 0x07009CB0 - 0x07009D90
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009CB0, 0x00371c40, 68724, 0x00009cb0, 224);

// 0x07009D90 - 0x07009E80
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009D90, 0x00371c40, 68724, 0x00009d90, 240);

// 0x07009E80 - 0x07009F70
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009E80, 0x00371c40, 68724, 0x00009e80, 240);

// 0x07009F70 - 0x0700A050
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_07009F70, 0x00371c40, 68724, 0x00009f70, 224);

// 0x0700A050 - 0x0700A130
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A050, 0x00371c40, 68724, 0x0000a050, 224);

// 0x0700A130 - 0x0700A220
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A130, 0x00371c40, 68724, 0x0000a130, 240);

// 0x0700A220 - 0x0700A300
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A220, 0x00371c40, 68724, 0x0000a220, 224);

// 0x0700A300 - 0x0700A380
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A300, 0x00371c40, 68724, 0x0000a300, 128);

// 0x0700A380 - 0x0700A3E0
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A380, 0x00371c40, 68724, 0x0000a380, 96);

// 0x0700A3E0 - 0x0700A460
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A3E0, 0x00371c40, 68724, 0x0000a3e0, 128);

// 0x0700A460 - 0x0700A550
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A460, 0x00371c40, 68724, 0x0000a460, 240);

// 0x0700A550 - 0x0700A600
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A550, 0x00371c40, 68724, 0x0000a550, 176);

// 0x0700A600 - 0x0700A700
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A600, 0x00371c40, 68724, 0x0000a600, 256);

// 0x0700A700 - 0x0700A800
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700A700, 0x00371c40, 68724, 0x0000a700, 256);

// 0x0700A800 - 0x0700AA08
static const Gfx bbh_seg7_dl_0700A800[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07008F18.l, 1),
    gsSPLight(&bbh_seg7_lights_07008F18.a, 2),
    gsSPVertex(bbh_seg7_vertex_07008F60, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&bbh_seg7_lights_07008F30.l, 1),
    gsSPLight(&bbh_seg7_lights_07008F30.a, 2),
    gsSPVertex(bbh_seg7_vertex_07008FE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0, 10,  0,  8, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 12,  5, 13, 0x0),
    gsSP2Triangles( 7, 14,  8, 0x0, 12, 13, 15, 0x0),
    gsSPLight(&bbh_seg7_lights_07008F48.l, 1),
    gsSPLight(&bbh_seg7_lights_07008F48.a, 2),
    gsSPVertex(bbh_seg7_vertex_070090E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_070091E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9,  5, 10, 0x0),
    gsSP2Triangles( 5,  4, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 7,  8, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_070092D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070093B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_070094A0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AA08 - 0x0700ACB0
static const Gfx bbh_seg7_dl_0700AA08[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07009540, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009640, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009720, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 9, 13, 14, 0x0,  9,  8, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009810, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 3,  4,  6, 0x0,  5,  1,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070098F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070099F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12, 10,  8, 0x0, 13, 11, 14, 0x0),
    gsSP1Triangle(14, 11,  7, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009AE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009BD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009CB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009D90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700ACB0 - 0x0700AE20
static const Gfx bbh_seg7_dl_0700ACB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07009E80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07009F70, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700A050, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700A130, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700A220, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700A300, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AE20 - 0x0700AE68
static const Gfx bbh_seg7_dl_0700AE20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700A380, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  1,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AE68 - 0x0700AEB0
static const Gfx bbh_seg7_dl_0700AE68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700A3E0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AEB0 - 0x0700AF40
static const Gfx bbh_seg7_dl_0700AEB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700A460, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700A550, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP1Triangle( 6,  8, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AF40 - 0x0700AFF0
static const Gfx bbh_seg7_dl_0700AF40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700A600, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  2, 11,  0, 0x0),
    gsSP2Triangles( 1,  0, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700A700, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  0, 0x0),
    gsSP2Triangles( 7,  0,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AFF0 - 0x0700B0D8
const Gfx bbh_seg7_dl_0700AFF0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700A800),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700AA08),
    gsSPDisplayList(bbh_seg7_dl_0700ACB0),
    gsSPDisplayList(bbh_seg7_dl_0700AE20),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700AE68),
    gsSPDisplayList(bbh_seg7_dl_0700AEB0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700AF40),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
