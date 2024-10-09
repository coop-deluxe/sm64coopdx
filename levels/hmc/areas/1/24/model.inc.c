#include "pc/rom_assets.h"
// 0x0701A4B8 - 0x0701A4D0
static const Lights1 hmc_seg7_lights_0701A4B8 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0701A4D0 - 0x0701A4E8
static const Lights1 hmc_seg7_lights_0701A4D0 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701A4E8 - 0x0701A500
static const Lights1 hmc_seg7_lights_0701A4E8 = gdSPDefLights1(
    0x79, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0701A500 - 0x0701A518
static const Lights1 hmc_seg7_lights_0701A500 = gdSPDefLights1(
    0x51, 0x43, 0x26,
    0xac, 0x8e, 0x52, 0x28, 0x28, 0x28
);

// 0x0701A518 - 0x0701A530
static const Lights1 hmc_seg7_lights_0701A518 = gdSPDefLights1(
    0x5a, 0x46, 0x1d,
    0xbf, 0x94, 0x3f, 0x28, 0x28, 0x28
);

// 0x0701A530 - 0x0701A610
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701A530, 0x003d0dc0, 89137, 0x0001a530, 224);

// 0x0701A610 - 0x0701A6F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701A610, 0x003d0dc0, 89137, 0x0001a610, 224);

// 0x0701A6F0 - 0x0701A7F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701A6F0, 0x003d0dc0, 89137, 0x0001a6f0, 256);

// 0x0701A7F0 - 0x0701A8F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701A7F0, 0x003d0dc0, 89137, 0x0001a7f0, 256);

// 0x0701A8F0 - 0x0701A9F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701A8F0, 0x003d0dc0, 89137, 0x0001a8f0, 256);

// 0x0701A9F0 - 0x0701AAE0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701A9F0, 0x003d0dc0, 89137, 0x0001a9f0, 240);

// 0x0701AAE0 - 0x0701AB50
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701AAE0, 0x003d0dc0, 89137, 0x0001aae0, 112);

// 0x0701AB50 - 0x0701AC30
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701AB50, 0x003d0dc0, 89137, 0x0001ab50, 224);

// 0x0701AC30 - 0x0701AD30
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701AC30, 0x003d0dc0, 89137, 0x0001ac30, 256);

// 0x0701AD30 - 0x0701AE10
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701AD30, 0x003d0dc0, 89137, 0x0001ad30, 224);

// 0x0701AE10 - 0x0701AE80
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701AE10, 0x003d0dc0, 89137, 0x0001ae10, 112);

// 0x0701AE80 - 0x0701AF40
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701AE80, 0x003d0dc0, 89137, 0x0001ae80, 192);

// 0x0701AF40 - 0x0701B040
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701AF40, 0x003d0dc0, 89137, 0x0001af40, 256);

// 0x0701B040 - 0x0701B120
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B040, 0x003d0dc0, 89137, 0x0001b040, 224);

// 0x0701B120 - 0x0701B220
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B120, 0x003d0dc0, 89137, 0x0001b120, 256);

// 0x0701B220 - 0x0701B320
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B220, 0x003d0dc0, 89137, 0x0001b220, 256);

// 0x0701B320 - 0x0701B400
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B320, 0x003d0dc0, 89137, 0x0001b320, 224);

// 0x0701B400 - 0x0701B500
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B400, 0x003d0dc0, 89137, 0x0001b400, 256);

// 0x0701B500 - 0x0701B5F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B500, 0x003d0dc0, 89137, 0x0001b500, 240);

// 0x0701B5F0 - 0x0701B6F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B5F0, 0x003d0dc0, 89137, 0x0001b5f0, 256);

// 0x0701B6F0 - 0x0701B7E0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B6F0, 0x003d0dc0, 89137, 0x0001b6f0, 240);

// 0x0701B7E0 - 0x0701B8D0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B7E0, 0x003d0dc0, 89137, 0x0001b7e0, 240);

// 0x0701B8D0 - 0x0701B9D0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B8D0, 0x003d0dc0, 89137, 0x0001b8d0, 256);

// 0x0701B9D0 - 0x0701BAC0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701B9D0, 0x003d0dc0, 89137, 0x0001b9d0, 240);

// 0x0701BAC0 - 0x0701BBC0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701BAC0, 0x003d0dc0, 89137, 0x0001bac0, 256);

// 0x0701BBC0 - 0x0701BCC0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701BBC0, 0x003d0dc0, 89137, 0x0001bbc0, 256);

// 0x0701BCC0 - 0x0701BDC0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701BCC0, 0x003d0dc0, 89137, 0x0001bcc0, 256);

// 0x0701BDC0 - 0x0701BEC0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701BDC0, 0x003d0dc0, 89137, 0x0001bdc0, 256);

// 0x0701BEC0 - 0x0701BFB0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701BEC0, 0x003d0dc0, 89137, 0x0001bec0, 240);

// 0x0701BFB0 - 0x0701C0B0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701BFB0, 0x003d0dc0, 89137, 0x0001bfb0, 256);

// 0x0701C0B0 - 0x0701C1B0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C0B0, 0x003d0dc0, 89137, 0x0001c0b0, 256);

// 0x0701C1B0 - 0x0701C290
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C1B0, 0x003d0dc0, 89137, 0x0001c1b0, 224);

// 0x0701C290 - 0x0701C390
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C290, 0x003d0dc0, 89137, 0x0001c290, 256);

// 0x0701C390 - 0x0701C480
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C390, 0x003d0dc0, 89137, 0x0001c390, 240);

// 0x0701C480 - 0x0701C560
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C480, 0x003d0dc0, 89137, 0x0001c480, 224);

// 0x0701C560 - 0x0701C5A0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C560, 0x003d0dc0, 89137, 0x0001c560, 64);

// 0x0701C5A0 - 0x0701C5E0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C5A0, 0x003d0dc0, 89137, 0x0001c5a0, 64);

// 0x0701C5E0 - 0x0701C6E0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C5E0, 0x003d0dc0, 89137, 0x0001c5e0, 256);

// 0x0701C6E0 - 0x0701C7E0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C6E0, 0x003d0dc0, 89137, 0x0001c6e0, 256);

// 0x0701C7E0 - 0x0701C8E0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C7E0, 0x003d0dc0, 89137, 0x0001c7e0, 256);

// 0x0701C8E0 - 0x0701C950
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C8E0, 0x003d0dc0, 89137, 0x0001c8e0, 112);

// 0x0701C950 - 0x0701CA30
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701C950, 0x003d0dc0, 89137, 0x0001c950, 224);

// 0x0701CA30 - 0x0701CB20
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701CA30, 0x003d0dc0, 89137, 0x0001ca30, 240);

// 0x0701CB20 - 0x0701CC10
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701CB20, 0x003d0dc0, 89137, 0x0001cb20, 240);

// 0x0701CC10 - 0x0701CD10
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701CC10, 0x003d0dc0, 89137, 0x0001cc10, 256);

// 0x0701CD10 - 0x0701CE10
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701CD10, 0x003d0dc0, 89137, 0x0001cd10, 256);

// 0x0701CE10 - 0x0701CF00
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701CE10, 0x003d0dc0, 89137, 0x0001ce10, 240);

// 0x0701CF00 - 0x0701D000
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701CF00, 0x003d0dc0, 89137, 0x0001cf00, 256);

// 0x0701D000 - 0x0701D0F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701D000, 0x003d0dc0, 89137, 0x0001d000, 240);

// 0x0701D0F0 - 0x0701D1B0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701D0F0, 0x003d0dc0, 89137, 0x0001d0f0, 192);

// 0x0701D1B0 - 0x0701D230
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701D1B0, 0x003d0dc0, 89137, 0x0001d1b0, 128);

// 0x0701D230 - 0x0701D2B0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701D230, 0x003d0dc0, 89137, 0x0001d230, 128);

// 0x0701D2B0 - 0x0701D3B0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701D2B0, 0x003d0dc0, 89137, 0x0001d2b0, 256);

// 0x0701D3B0 - 0x0701D4B0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701D3B0, 0x003d0dc0, 89137, 0x0001d3b0, 256);

// 0x0701D4B0 - 0x0701D5A0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_0701D4B0, 0x003d0dc0, 89137, 0x0001d4b0, 240);

// 0x0701D5A0 - 0x0701D708
static const Gfx hmc_seg7_dl_0701D5A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_0701A4B8.l, 1),
    gsSPLight(&hmc_seg7_lights_0701A4B8.a, 2),
    gsSPVertex(hmc_seg7_vertex_0701A530, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  6,  7, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0,  8,  3, 10, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0,  0,  2, 13, 0x0),
    gsSPLight(&hmc_seg7_lights_0701A4D0.l, 1),
    gsSPLight(&hmc_seg7_lights_0701A4D0.a, 2),
    gsSPVertex(hmc_seg7_vertex_0701A610, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 10, 13, 12, 0x0),
    gsSP2Triangles(13,  6,  8, 0x0, 13,  8, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701A6F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 3,  8,  6, 0x0,  3,  7,  9, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701D708 - 0x0701D8B0
static const Gfx hmc_seg7_dl_0701D708[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701A7F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles(12,  7, 11, 0x0, 13, 14, 11, 0x0),
    gsSP2Triangles(14, 12, 11, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701A8F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  6,  5,  1, 0x0),
    gsSP2Triangles( 1,  5,  9, 0x0,  1,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0,  8, 13,  5, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0, 14, 15, 11, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701A9F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 13, 11, 12, 0x0),
    gsSP1Triangle(13, 12, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701AAE0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSP1Triangle( 6,  4,  5, 0x0),
    gsSPLight(&hmc_seg7_lights_0701A4E8.l, 1),
    gsSPLight(&hmc_seg7_lights_0701A4E8.a, 2),
    gsSPVertex(hmc_seg7_vertex_0701AB50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701D8B0 - 0x0701E228
static const Gfx hmc_seg7_dl_0701D8B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_0701A500.l, 1),
    gsSPLight(&hmc_seg7_lights_0701A500.a, 2),
    gsSPVertex(hmc_seg7_vertex_0701AC30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 1,  6,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 8, 10, 13, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 6, 14, 15, 0x0,  6, 15,  7, 0x0),
    gsSP2Triangles(14, 13, 15, 0x0, 14,  8, 13, 0x0),
    gsSPLight(&hmc_seg7_lights_0701A518.l, 1),
    gsSPLight(&hmc_seg7_lights_0701A518.a, 2),
    gsSPVertex(hmc_seg7_vertex_0701AD30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  3,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701AE10, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPLight(&hmc_seg7_lights_0701A4B8.l, 1),
    gsSPLight(&hmc_seg7_lights_0701A4B8.a, 2),
    gsSPVertex(hmc_seg7_vertex_0701AE80, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  7, 0x0),
    gsSP2Triangles( 5, 10,  8, 0x0, 10, 11,  8, 0x0),
    gsSPLight(&hmc_seg7_lights_0701A4D0.l, 1),
    gsSPLight(&hmc_seg7_lights_0701A4D0.a, 2),
    gsSPVertex(hmc_seg7_vertex_0701AF40, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 1,  8,  9, 0x0,  1,  9,  2, 0x0),
    gsSP2Triangles(10,  2,  9, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(12,  0,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B040, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  5, 12, 0x0),
    gsSP2Triangles(13, 12,  5, 0x0,  7, 13,  5, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B120, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B220, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  3,  6, 0x0),
    gsSP2Triangles( 1,  6,  4, 0x0,  1,  5,  7, 0x0),
    gsSP2Triangles( 1,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  9, 13, 14, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B320, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B400, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  2,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 9,  7,  8, 0x0, 11,  3, 12, 0x0),
    gsSP2Triangles(13,  3,  5, 0x0, 12,  3, 13, 0x0),
    gsSP1Triangle( 8, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B500, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  1,  5,  3, 0x0),
    gsSP2Triangles( 1,  6,  5, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0,  0,  9,  6, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0,  5, 11, 10, 0x0),
    gsSP2Triangles( 5, 12, 11, 0x0,  5,  7, 12, 0x0),
    gsSP2Triangles(13,  0,  2, 0x0,  9, 14,  8, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B5F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  9,  6, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  4, 0x0, 11,  4, 12, 0x0),
    gsSP2Triangles(11, 10,  4, 0x0, 12,  4,  3, 0x0),
    gsSP2Triangles(10, 13,  7, 0x0,  7, 14,  8, 0x0),
    gsSP2Triangles(13, 14,  7, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B6F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B7E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 10, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B8D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 6,  5,  3, 0x0,  6,  3,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles( 8, 10, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701B9D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 0,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  6,  5, 0x0, 10, 11,  6, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 10, 13, 0x0),
    gsSP1Triangle(13, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701BAC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  8,  9,  5, 0x0),
    gsSP2Triangles(10,  2,  1, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 8, 14,  9, 0x0,  8, 13, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701BBC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  7, 0x0,  1,  7,  8, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles(11,  5,  4, 0x0, 12, 11,  4, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701BCC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701BDC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701BEC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  4,  0,  3, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  9,  8,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14,  8, 0x0),
    gsSP1Triangle(13,  8,  9, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701BFB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 15, 11, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C0B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  5,  0,  3, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 5,  3,  8, 0x0,  3,  2,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C1B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 12, 13,  8, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C290, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle( 8, 15, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C390, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C480, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C560, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E228 - 0x0701E260
static const Gfx hmc_seg7_dl_0701E228[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701C5A0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E260 - 0x0701E370
static const Gfx hmc_seg7_dl_0701E260[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701C5E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9,  3,  6, 0x0),
    gsSP2Triangles( 9,  6,  7, 0x0,  2,  1, 11, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C6E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C7E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701C8E0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  6,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E370 - 0x0701E528
static const Gfx hmc_seg7_dl_0701E370[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701C950, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701CA30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701CB20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 6,  2,  5, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 8,  2,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0, 10,  1,  0, 0x0),
    gsSP2Triangles(10, 11,  1, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701CC10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  2,  1,  6, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  8,  5,  4, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(11, 15, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701CD10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E528 - 0x0701E688
static const Gfx hmc_seg7_dl_0701E528[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701CE10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 5,  7,  0, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 0,  9,  1, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 5,  2, 13, 0x0, 14,  5, 13, 0x0),
    gsSP1Triangle(14,  3,  5, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701CF00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 11, 14, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701D000, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  9,  3,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701D0F0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E688 - 0x0701E6D0
static const Gfx hmc_seg7_dl_0701E688[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701D1B0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E6D0 - 0x0701E718
static const Gfx hmc_seg7_dl_0701E6D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701D230, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E718 - 0x0701E820
static const Gfx hmc_seg7_dl_0701E718[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_0701D2B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  9,  3,  8, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0, 11, 12,  1, 0x0),
    gsSP2Triangles( 0, 11,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701D3B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  3,  5,  0, 0x0),
    gsSP2Triangles( 3,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_0701D4B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701E820 - 0x0701E958
const Gfx hmc_seg7_dl_0701E820[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(960, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0701D5A0),
    gsSPDisplayList(hmc_seg7_dl_0701D708),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0701D8B0),
    gsSPDisplayList(hmc_seg7_dl_0701E228),
    gsSPDisplayList(hmc_seg7_dl_0701E260),
    gsSPDisplayList(hmc_seg7_dl_0701E370),
    gsSPDisplayList(hmc_seg7_dl_0701E528),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0701E688),
    gsSPDisplayList(hmc_seg7_dl_0701E6D0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_0701E718),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
