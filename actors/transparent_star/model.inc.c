#include "pc/rom_assets.h"
// Transparent Star

// 0x0302C488
static const Lights1 transparent_star_seg3_lights_0302C488 = gdSPDefLights1(
    0x03, 0x05, 0x17,
    0x1e, 0x32, 0xe6, 0x28, 0x28, 0x28
);

// 0x0302C4A0
ROM_ASSET_LOAD_VTX(transparent_star_seg3_vertex_0302C4A0, 0x00201410, 96653, 0x0002b6f0, 192);

// 0x0302C560 - 0x0302C620
const Gfx transparent_star_seg3_dl_0302C560[] = {
    gsSPLight(&transparent_star_seg3_lights_0302C488.l, 1),
    gsSPLight(&transparent_star_seg3_lights_0302C488.a, 2),
    gsSPVertex(transparent_star_seg3_vertex_0302C4A0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  7,  2,  4, 0x0),
    gsSP2Triangles( 8,  6,  4, 0x0,  9,  4, 10, 0x0),
    gsSP2Triangles( 9, 11,  4, 0x0,  4,  5, 10, 0x0),
    gsSP2Triangles(11,  8,  4, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 0,  7,  6, 0x0,  0,  6,  8, 0x0),
    gsSP2Triangles( 0,  8, 11, 0x0,  0, 11,  9, 0x0),
    gsSP2Triangles(10,  5,  0, 0x0, 10,  0,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0302C620 - 0x0302C658
const Gfx transparent_star_seg3_dl_0302C620[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsDPSetEnvColor(255, 255, 255, 120),
    gsSPDisplayList(transparent_star_seg3_dl_0302C560),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
