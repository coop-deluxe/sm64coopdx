#include "pc/rom_assets.h"
// Spindrift

// Unreferenced light group

// Unreferenced light group

// 0x05000030

// 0x05000048

// Unreferenced light group

// 0x05000078

// 0x05000090

// Unreferenced light group

// 0x050000C0
ROM_ASSET_LOAD_VTX(spindrift_seg5_vertex_050000C0, 0x00160670, 20585, 0x000000c0, 96);

// 0x05000120
ROM_ASSET_LOAD_VTX(spindrift_seg5_vertex_05000120, 0x00160670, 20585, 0x00000120, 96);

// 0x05000180
ROM_ASSET_LOAD_VTX(spindrift_seg5_vertex_05000180, 0x00160670, 20585, 0x00000180, 144);

// 0x05000210
ROM_ASSET_LOAD_VTX(spindrift_seg5_vertex_05000210, 0x00160670, 20585, 0x00000210, 144);

// 0x050002A0 - 0x05000328
const Gfx spindrift_seg5_dl_050002A0[] = {
    gsSPLight(&spindrift_seg5_lights_05000048.l, 1),
    gsSPLight(&spindrift_seg5_lights_05000048.a, 2),
    gsSPVertex(spindrift_seg5_vertex_050000C0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 1,  3,  2, 0x0,  4,  5,  2, 0x0),
    gsSP1Triangle( 5,  0,  2, 0x0),
    gsSPLight(&spindrift_seg5_lights_05000030.l, 1),
    gsSPLight(&spindrift_seg5_lights_05000030.a, 2),
    gsSPVertex(spindrift_seg5_vertex_05000120, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  4,  0,  5, 0x0),
    gsSP1Triangle( 5,  0,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05000328 - 0x050003D8
const Gfx spindrift_seg5_dl_05000328[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&spindrift_seg5_lights_05000090.l, 1),
    gsSPLight(&spindrift_seg5_lights_05000090.a, 2),
    gsSPVertex(spindrift_seg5_vertex_05000180, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 7,  4,  0, 0x0,  5,  4,  8, 0x0),
    gsSP2Triangles( 5,  1,  3, 0x0,  4,  5,  3, 0x0),
    gsSPLight(&spindrift_seg5_lights_05000078.l, 1),
    gsSPLight(&spindrift_seg5_lights_05000078.a, 2),
    gsSPVertex(spindrift_seg5_vertex_05000210, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP1Triangle( 8,  7,  3, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
