#include "pc/rom_assets.h"
// Small Key (unused)

// ???
UNUSED static const u64 small_key_unused_1 = 0;

// 0x05005798
static const Lights1 small_key_seg5_lights_05005798 = gdSPDefLights1(
    0x3f, 0x19, 0x0c,
    0xff, 0x64, 0x32, 0x28, 0x28, 0x28
);

// 0x050057B0
static const Lights1 small_key_seg5_lights_050057B0 = gdSPDefLights1(
    0x0c, 0x3f, 0x19,
    0x32, 0xff, 0x64, 0x28, 0x28, 0x28
);

// 0x050057C8
static const Lights1 small_key_seg5_lights_050057C8 = gdSPDefLights1(
    0x0c, 0x19, 0x3f,
    0x32, 0x64, 0xff, 0x28, 0x28, 0x28
);

// 0x050057E0
static const Lights1 small_key_seg5_lights_050057E0 = gdSPDefLights1(
    0x33, 0x3f, 0x00,
    0xcc, 0xff, 0x00, 0x28, 0x28, 0x28
);

// align
UNUSED static const u64 small_key_unused_2 = 0;
// 0x05005800
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05005800, 0x00166c60, 26968, 0x00005800, 240);

// 0x050058F0
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_050058F0, 0x00166c60, 26968, 0x000058f0, 240);

// 0x050059E0
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_050059E0, 0x00166c60, 26968, 0x000059e0, 240);

// 0x05005AD0
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05005AD0, 0x00166c60, 26968, 0x00005ad0, 240);

// 0x05005BC0
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05005BC0, 0x00166c60, 26968, 0x00005bc0, 240);

// 0x05005CB0
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05005CB0, 0x00166c60, 26968, 0x00005cb0, 240);

// 0x05005DA0
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05005DA0, 0x00166c60, 26968, 0x00005da0, 240);

// 0x05005E90
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05005E90, 0x00166c60, 26968, 0x00005e90, 240);

// 0x05005F80
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05005F80, 0x00166c60, 26968, 0x00005f80, 240);

// 0x05006070
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05006070, 0x00166c60, 26968, 0x00006070, 240);

// 0x05006160
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05006160, 0x00166c60, 26968, 0x00006160, 240);

// 0x05006250
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05006250, 0x00166c60, 26968, 0x00006250, 240);

// 0x05006340
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05006340, 0x00166c60, 26968, 0x00006340, 240);

// 0x05006430
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05006430, 0x00166c60, 26968, 0x00006430, 240);

// 0x05006520
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05006520, 0x00166c60, 26968, 0x00006520, 240);

// 0x05006610
ROM_ASSET_LOAD_VTX(small_key_seg5_vertex_05006610, 0x00166c60, 26968, 0x00006610, 240);

// 0x05006700 - 0x05006A08
const Gfx small_key_seg5_dl_05006700[] = {
    gsSPVertex(small_key_seg5_vertex_05005800, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_050058F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_050059E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05005AD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05005BC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05005CB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05005DA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05005E90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05005F80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05006070, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05006160, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05006250, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05006340, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05006430, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05006520, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(small_key_seg5_vertex_05006610, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006A08 - 0x05006A28
const Gfx small_key_seg5_dl_05006A08[] = {
    gsSPSetLights1(small_key_seg5_lights_050057C8),
    gsSPBranchList(small_key_seg5_dl_05006700),
};

// 0x05006A28 - 0x05006A48
const Gfx small_key_seg5_dl_05006A28[] = {
    gsSPSetLights1(small_key_seg5_lights_050057B0),
    gsSPBranchList(small_key_seg5_dl_05006700),
};

// 0x05006A48 - 0x05006A68
const Gfx small_key_seg5_dl_05006A48[] = {
    gsSPSetLights1(small_key_seg5_lights_05005798),
    gsSPBranchList(small_key_seg5_dl_05006700),
};

// 0x05006A68 - 0x05006A88
const Gfx small_key_seg5_dl_05006A68[] = {
    gsSPSetLights1(small_key_seg5_lights_050057E0),
    gsSPBranchList(small_key_seg5_dl_05006700),
};
