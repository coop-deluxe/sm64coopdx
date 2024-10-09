#include "pc/rom_assets.h"
// 0x070127C8 - 0x070128A8
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070127C8, 0x0040ed70, 45590, 0x000127c8, 224);

// 0x070128A8 - 0x07012908
static const Gfx wdw_seg7_dl_070128A8[] = {
    gsSPVertex(wdw_seg7_vertex_070127C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 6,  8,  5, 0x0,  7,  9,  6, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0, 10, 11,  0, 0x0),
    gsSP2Triangles(10,  2, 12, 0x0, 11, 13,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012908 - 0x07012938
const Gfx wdw_seg7_dl_07012908[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPDisplayList(wdw_seg7_dl_070128A8),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
