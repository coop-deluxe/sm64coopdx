#include "pc/rom_assets.h"
// 0x07008FD0 - 0x07009010
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_07008FD0, 0x0048d930, 33063, 0x00008fd0, 64);

// 0x07009010 - 0x07009030
static const Gfx ddd_seg7_dl_07009010[] = {
    gsSPVertex(ddd_seg7_vertex_07008FD0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009030 - 0x07009080
const Gfx ddd_seg7_dl_07009030[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 80),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPDisplayList(ddd_seg7_dl_07009010),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
