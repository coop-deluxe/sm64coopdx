#include "pc/rom_assets.h"
// 0x07005568 - 0x07005658
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_07005568, 0x00496090, 31162, 0x00005568, 240);

// 0x07005658 - 0x07005690
static const Gfx wf_seg7_dl_07005658[] = {
    gsSPVertex(wf_seg7_vertex_07005568, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005690 - 0x070056C0
const Gfx wf_seg7_dl_07005690[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPDisplayList(wf_seg7_dl_07005658),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
