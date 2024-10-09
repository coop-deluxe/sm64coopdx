#include "pc/rom_assets.h"
// TODO: what is this? 0700C4C0-0700C4C8 [8,8]
UNUSED static const u64 castle_grounds_unused_0 = 0;

// 0x0700C4C8 - 0x0700C4E0
static const Lights1 castle_grounds_seg7_lights_0700C4C8 = gdSPDefLights1(
    0x66, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0700C4E0 - 0x0700C4F8
static const Lights1 castle_grounds_seg7_lights_0700C4E0 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// TODO: what is this? 0700C4F8-0700C500 [8,8]
UNUSED static const u64 castle_grounds_unused_1 = 0;

// 0x0700C500 - 0x0700C530
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_0700C500, 0x0044abc0, 39442, 0x0000c500, 48);

// 0x0700C530 - 0x0700C570
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_0700C530, 0x0044abc0, 39442, 0x0000c530, 64);

// 0x0700C570 - 0x0700C5B0
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_0700C570, 0x0044abc0, 39442, 0x0000c570, 64);

// 0x0700C5B0 - 0x0700C5F0
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_0700C5B0, 0x0044abc0, 39442, 0x0000c5b0, 64);

// 0x0700C5F0 - 0x0700C640
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_0700C5F0, 0x0044abc0, 39442, 0x0000c5f0, 80);

// 0x0700C640 - 0x0700C670
ROM_ASSET_LOAD_VTX(castle_grounds_seg7_vertex_0700C640, 0x0044abc0, 39442, 0x0000c640, 48);

// 0x0700C670 - 0x0700C6A8
const Gfx castle_grounds_seg7_dl_0700C670[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_0700C500, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0700C6A8 - 0x0700C6E8
const Gfx castle_grounds_seg7_dl_0700C6A8[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_0700C530, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0700C6E8 - 0x0700C728
const Gfx castle_grounds_seg7_dl_0700C6E8[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_0700C570, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0700C728 - 0x0700C768
const Gfx castle_grounds_seg7_dl_0700C728[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_0700C5B0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0700C768 - 0x0700C7C8
const Gfx castle_grounds_seg7_dl_0700C768[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&castle_grounds_seg7_lights_0700C4E0.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_0700C4E0.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_0700C5F0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.l, 1),
    gsSPLight(&castle_grounds_seg7_lights_0700C4C8.a, 2),
    gsSPVertex(castle_grounds_seg7_vertex_0700C640, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
