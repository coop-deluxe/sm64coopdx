#include "pc/rom_assets.h"
// 0x07005CB0 - 0x07005D90
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07005CB0, 0x0048d930, 33063, 0x00005cb0, 224);

// 0x07005D90 - 0x07005E70
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07005D90, 0x0048d930, 33063, 0x00005d90, 224);

// 0x07005E70 - 0x07005EE0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07005E70, 0x0048d930, 33063, 0x00005e70, 112);

// 0x07005EE0 - 0x07005F78
static const Gfx ddd_seg7_dl_07005EE0[] = {
    gsSPVertex(ddd_seg7_vertex_07005CB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ddd_seg7_vertex_07005D90, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ddd_seg7_vertex_07005E70, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005F78 - 0x07005FC8
const Gfx ddd_seg7_dl_07005F78[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 98),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(ddd_seg7_dl_07005EE0),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
