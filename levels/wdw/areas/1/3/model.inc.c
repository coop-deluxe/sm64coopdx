#include "pc/rom_assets.h"
// 0x070122C8 - 0x070123A8
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070122C8, 0x0040ed70, 45590, 0x000122c8, 224);

// 0x070123A8 - 0x070124A8
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070123A8, 0x0040ed70, 45590, 0x000123a8, 256);

// 0x070124A8 - 0x07012598
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_070124A8, 0x0040ed70, 45590, 0x000124a8, 240);

// 0x07012598 - 0x07012658
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07012598, 0x0040ed70, 45590, 0x00012598, 192);

// 0x07012658 - 0x07012798
static const Gfx wdw_seg7_dl_07012658[] = {
    gsSPVertex(wdw_seg7_vertex_070122C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles( 7,  9, 12, 0x0,  7, 12, 13, 0x0),
    gsSPVertex(wdw_seg7_vertex_070123A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  9,  6, 0x0),
    gsSP2Triangles( 2, 10, 11, 0x0,  2, 11,  0, 0x0),
    gsSP2Triangles(11, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wdw_seg7_vertex_070124A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  3, 0x0,  3,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 10, 0x0),
    gsSPVertex(wdw_seg7_vertex_07012598, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  0,  8,  9, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  8, 10,  9, 0x0),
    gsSP1Triangle( 9, 11,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012798 - 0x070127C8
const Gfx wdw_seg7_dl_07012798[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPDisplayList(wdw_seg7_dl_07012658),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
