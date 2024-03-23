#include "pc/rom_assets.h"
// 0x0700A1E0 - 0x0700A2E0
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_0700A1E0, 0x004b80d0, 26886, 0x0000a1e0, 256);

// 0x0700A2E0 - 0x0700A3D0
ROM_ASSET_LOAD_VTX(cotmc_seg7_vertex_0700A2E0, 0x004b80d0, 26886, 0x0000a2e0, 240);

// 0x0700A3D0 - 0x0700A4B8
static const Gfx cotmc_seg7_dl_0700A3D0[] = {
    gsSPVertex(cotmc_seg7_vertex_0700A1E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  7,  5,  2, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  9,  3,  5, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0, 10, 11,  4, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 10, 15, 11, 0x0),
    gsSPVertex(cotmc_seg7_vertex_0700A2E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  4,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles( 6, 11, 10, 0x0,  9, 10, 12, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A4B8 - 0x0700A508
const Gfx cotmc_seg7_dl_0700A4B8[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 180),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPDisplayList(cotmc_seg7_dl_0700A3D0),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
