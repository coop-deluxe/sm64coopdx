#include "pc/rom_assets.h"
// Test Platform (small tiny platform 1/4th the size of a box. Probably used in early modeling tests?)

// 0x08026008
static const Lights1 unknown_seg8_lights_08026008 = gdSPDefLights1(
    0x32, 0x32, 0x07,
    0xc8, 0xc8, 0x1e, 0x28, 0x28, 0x28
);

// 0x08026020
ROM_ASSET_LOAD_VTX(unknown_seg8_vertex_08026020, 0x001f2200, 59076, 0x00026020, 240);

// 0x08026110
ROM_ASSET_LOAD_VTX(unknown_seg8_vertex_08026110, 0x001f2200, 59076, 0x00026110, 240);

// 0x08026200
ROM_ASSET_LOAD_VTX(unknown_seg8_vertex_08026200, 0x001f2200, 59076, 0x00026200, 96);

// 0x08026260 - 0x080262F8
const Gfx unknown_seg8_dl_08026260[] = {
    gsSPSetLights1(unknown_seg8_lights_08026008),
    gsSPVertex(unknown_seg8_vertex_08026020, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(unknown_seg8_vertex_08026110, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(unknown_seg8_vertex_08026200, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};
