#include "pc/rom_assets.h"
// Birds

// 0x05000000
static const Lights1 birds_seg5_lights_05000000 = gdSPDefLights1(
    0x07, 0x24, 0x2c,
    0x1d, 0x91, 0xb0, 0x28, 0x28, 0x28
);

// 0x05000018
static const Lights1 birds_seg5_lights_05000018 = gdSPDefLights1(
    0x33, 0x27, 0x0d,
    0xce, 0x9d, 0x34, 0x28, 0x28, 0x28
);

// 0x05000030
static const Lights1 birds_seg5_lights_05000030 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05000048
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_05000048, 0x0016d870, 76997, 0x00000048, 144);

// 0x050000D8
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_050000D8, 0x0016d870, 76997, 0x000000d8, 48);

// 0x05000108
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_05000108, 0x0016d870, 76997, 0x00000108, 48);

// 0x05000138
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_05000138, 0x0016d870, 76997, 0x00000138, 48);

// 0x05000168
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_05000168, 0x0016d870, 76997, 0x00000168, 144);

// 0x050001F8
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_050001F8, 0x0016d870, 76997, 0x000001f8, 256);

// 0x050002F8
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_050002F8, 0x0016d870, 76997, 0x000002f8, 256);

// 0x050003F8
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_050003F8, 0x0016d870, 76997, 0x000003f8, 48);

// 0x05000428
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_05000428, 0x0016d870, 76997, 0x00000428, 160);

// 0x050004C8
ROM_ASSET_LOAD_VTX(birds_seg5_vertex_050004C8, 0x0016d870, 76997, 0x000004c8, 96);

// 0x05000528 - 0x05000598
const Gfx birds_seg5_dl_05000528[] = {
    gsSPLight(&birds_seg5_lights_05000000.l, 1),
    gsSPLight(&birds_seg5_lights_05000000.a, 2),
    gsSPVertex(birds_seg5_vertex_05000048, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  6, 0x0),
    gsSP2Triangles( 6,  8,  5, 0x0,  6,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  7, 0x0,  2,  7,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05000598 - 0x05000600
const Gfx birds_seg5_dl_05000598[] = {
    gsSPLight(&birds_seg5_lights_05000000.l, 1),
    gsSPLight(&birds_seg5_lights_05000000.a, 2),
    gsSPVertex(birds_seg5_vertex_050000D8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&birds_seg5_lights_05000000.l, 1),
    gsSPLight(&birds_seg5_lights_05000000.a, 2),
    gsSPVertex(birds_seg5_vertex_05000108, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&birds_seg5_lights_05000000.l, 1),
    gsSPLight(&birds_seg5_lights_05000000.a, 2),
    gsSPVertex(birds_seg5_vertex_05000138, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05000600 - 0x05000670
const Gfx birds_seg5_dl_05000600[] = {
    gsSPLight(&birds_seg5_lights_05000000.l, 1),
    gsSPLight(&birds_seg5_lights_05000000.a, 2),
    gsSPVertex(birds_seg5_vertex_05000168, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  5,  8,  4, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  8,  1, 0x0,  4,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05000670 - 0x050007E0
const Gfx birds_seg5_dl_05000670[] = {
    gsSPLight(&birds_seg5_lights_05000000.l, 1),
    gsSPLight(&birds_seg5_lights_05000000.a, 2),
    gsSPVertex(birds_seg5_vertex_050001F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  1,  9, 10, 0x0),
    gsSP2Triangles( 1,  0, 11, 0x0, 12,  3, 13, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  5, 14, 10, 0x0),
    gsSP2Triangles(13, 15, 12, 0x0, 11, 15,  1, 0x0),
    gsSPVertex(birds_seg5_vertex_050002F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  5,  9, 0x0, 10,  7, 11, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 11, 13,  2, 0x0),
    gsSP2Triangles( 2, 14, 11, 0x0, 11,  7,  3, 0x0),
    gsSP1Triangle( 7,  6, 15, 0x0),
    gsSPVertex(birds_seg5_vertex_050003F8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&birds_seg5_lights_05000030.l, 1),
    gsSPLight(&birds_seg5_lights_05000030.a, 2),
    gsSPVertex(birds_seg5_vertex_05000428, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  7, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 9,  7,  2, 0x0,  2,  7,  0, 0x0),
    gsSP2Triangles( 2,  3,  9, 0x0,  7,  9,  8, 0x0),
    gsSP1Triangle( 5,  4,  1, 0x0),
    gsSPLight(&birds_seg5_lights_05000018.l, 1),
    gsSPLight(&birds_seg5_lights_05000018.a, 2),
    gsSPVertex(birds_seg5_vertex_050004C8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP1Triangle( 1,  3,  5, 0x0),
    gsSPEndDisplayList(),
};
