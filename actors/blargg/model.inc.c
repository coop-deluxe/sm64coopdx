#include "pc/rom_assets.h"
// Blargg (Unused)

// Unreferenced light group
UNUSED static const Lights1 blargg_lights_unused = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05004740
static const Lights1 blargg_seg5_lights_05004740 = gdSPDefLights1(
    0x3f, 0x0d, 0x05,
    0xff, 0x36, 0x16, 0x28, 0x28, 0x28
);

// 0x05004758
static const Lights1 blargg_seg5_lights_05004758 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x05004770
static const Lights1 blargg_seg5_lights_05004770 = gdSPDefLights1(
    0x3f, 0x0a, 0x06,
    0xff, 0x2a, 0x1a, 0x28, 0x28, 0x28
);

// 0x05004788
static const Lights1 blargg_seg5_lights_05004788 = gdSPDefLights1(
    0x3f, 0x0b, 0x07,
    0xff, 0x2e, 0x1f, 0x28, 0x28, 0x28
);

// 0x050047A0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050047A0, 0x00132c60, 7692, 0x000047a0, 256);

// 0x050048A0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050048A0, 0x00132c60, 7692, 0x000048a0, 256);

// 0x050049A0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050049A0, 0x00132c60, 7692, 0x000049a0, 128);

// 0x05004A20
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05004A20, 0x00132c60, 7692, 0x00004a20, 256);

// 0x05004B20
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05004B20, 0x00132c60, 7692, 0x00004b20, 192);

// 0x05004BE0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05004BE0, 0x00132c60, 7692, 0x00004be0, 256);

// 0x05004CE0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05004CE0, 0x00132c60, 7692, 0x00004ce0, 256);

// 0x05004DE0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05004DE0, 0x00132c60, 7692, 0x00004de0, 128);

// 0x05004E60
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05004E60, 0x00132c60, 7692, 0x00004e60, 256);

// 0x05004F60
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05004F60, 0x00132c60, 7692, 0x00004f60, 240);

// 0x05005050
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05005050, 0x00132c60, 7692, 0x00005050, 256);

// 0x05005150
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05005150, 0x00132c60, 7692, 0x00005150, 256);

// 0x05005250
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05005250, 0x00132c60, 7692, 0x00005250, 240);

// 0x05005340
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_05005340, 0x00132c60, 7692, 0x00005340, 160);

// 0x050053E0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050053E0, 0x00132c60, 7692, 0x000053e0, 256);

// 0x050054E0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050054E0, 0x00132c60, 7692, 0x000054e0, 256);

// 0x050055E0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050055E0, 0x00132c60, 7692, 0x000055e0, 256);

// 0x050056E0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050056E0, 0x00132c60, 7692, 0x000056e0, 256);

// 0x050057E0
ROM_ASSET_LOAD_VTX(blargg_seg5_vertex_050057E0, 0x00132c60, 7692, 0x000057e0, 240);

// 0x050058D0 - 0x05005A60
const Gfx blargg_seg5_dl_050058D0[] = {
    gsSPLight(&blargg_seg5_lights_05004758.l, 1),
    gsSPLight(&blargg_seg5_lights_05004758.a, 2),
    gsSPVertex(blargg_seg5_vertex_050047A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_050048A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_050049A0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&blargg_seg5_lights_05004740.l, 1),
    gsSPLight(&blargg_seg5_lights_05004740.a, 2),
    gsSPVertex(blargg_seg5_vertex_05004A20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8, 12, 13, 0x0),
    gsSP2Triangles( 5,  4, 14, 0x0,  5, 14, 15, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(blargg_seg5_vertex_05004B20, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 1,  8,  2, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 4, 10,  1, 0x0,  4,  7, 11, 0x0),
    gsSP1Triangle( 1, 10,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005A60 - 0x05005D00
const Gfx blargg_seg5_dl_05005A60[] = {
    gsSPLight(&blargg_seg5_lights_05004758.l, 1),
    gsSPLight(&blargg_seg5_lights_05004758.a, 2),
    gsSPVertex(blargg_seg5_vertex_05004BE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_05004CE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_05004DE0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&blargg_seg5_lights_05004770.l, 1),
    gsSPLight(&blargg_seg5_lights_05004770.a, 2),
    gsSPVertex(blargg_seg5_vertex_05004E60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  2,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0,  9, 13, 14, 0x0),
    gsSP1Triangle( 9, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_05004F60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  2,  9,  0, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(blargg_seg5_vertex_05005050, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 15, 13, 0x0, 14, 13, 12, 0x0),
    gsSPVertex(blargg_seg5_vertex_05005150, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11,  3,  9, 0x0,  1,  8,  2, 0x0),
    gsSP2Triangles(12,  0,  2, 0x0, 13, 14, 11, 0x0),
    gsSP2Triangles( 5,  7, 15, 0x0,  5,  8,  7, 0x0),
    gsSPVertex(blargg_seg5_vertex_05005250, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  3, 11, 10, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles(11,  8,  9, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(blargg_seg5_vertex_05005340, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  9,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005D00 - 0x05005EB8
const Gfx blargg_seg5_dl_05005D00[] = {
    gsSPLight(&blargg_seg5_lights_05004788.l, 1),
    gsSPLight(&blargg_seg5_lights_05004788.a, 2),
    gsSPVertex(blargg_seg5_vertex_050053E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_050054E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_050055E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(blargg_seg5_vertex_050056E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12,  4,  7, 0x0, 12,  7, 13, 0x0),
    gsSP2Triangles( 0,  6, 14, 0x0,  0, 14,  1, 0x0),
    gsSP2Triangles( 3, 15, 13, 0x0, 10, 15,  2, 0x0),
    gsSPVertex(blargg_seg5_vertex_050057E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  1,  0, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  5, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  8, 10,  6, 0x0),
    gsSP2Triangles( 8,  6, 11, 0x0, 14,  4,  7, 0x0),
    gsSP1Triangle(14,  7,  0, 0x0),
    gsSPEndDisplayList(),
};
