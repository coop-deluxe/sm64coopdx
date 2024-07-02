#include "pc/rom_assets.h"
// 0x07002E80 - 0x07002F80
ROM_ASSET_LOAD_VTX(sa_vertex_07002E80, 0x0046b090, 4364, 0x00002e80, 256);

// 0x07002F80 - 0x07002FD0
static const Gfx sa_dl_07002F80[] = {
    gsSPVertex(sa_vertex_07002E80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002FD0 - 0x07003000
const Gfx sa_seg7_dl_07002FD0[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPDisplayList(sa_dl_07002F80),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
