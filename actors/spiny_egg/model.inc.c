#include "pc/rom_assets.h"
// Spiny Egg

// 0x050144F8
static const Lights1 spiny_egg_seg5_lights_050144F8 = gdSPDefLights1(
    0x3f, 0x3f, 0x00,
    0xff, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x05014510
static const Lights1 spiny_egg_seg5_lights_05014510 = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05014528
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014528, 0x00180bb0, 29674, 0x00014528, 144);

// 0x050145B8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_050145B8, 0x00180bb0, 29674, 0x000145b8, 144);

// 0x05014648
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014648, 0x00180bb0, 29674, 0x00014648, 144);

// 0x050146D8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_050146D8, 0x00180bb0, 29674, 0x000146d8, 144);

// 0x05014768
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014768, 0x00180bb0, 29674, 0x00014768, 144);

// 0x050147F8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_050147F8, 0x00180bb0, 29674, 0x000147f8, 144);

// 0x05014888
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014888, 0x00180bb0, 29674, 0x00014888, 144);

// 0x05014918
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014918, 0x00180bb0, 29674, 0x00014918, 144);

// 0x050149A8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_050149A8, 0x00180bb0, 29674, 0x000149a8, 256);

// 0x05014AA8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014AA8, 0x00180bb0, 29674, 0x00014aa8, 256);

// 0x05014BA8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014BA8, 0x00180bb0, 29674, 0x00014ba8, 256);

// 0x05014CA8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014CA8, 0x00180bb0, 29674, 0x00014ca8, 256);

// 0x05014DA8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014DA8, 0x00180bb0, 29674, 0x00014da8, 256);

// 0x05014EA8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014EA8, 0x00180bb0, 29674, 0x00014ea8, 256);

// 0x05014FA8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_05014FA8, 0x00180bb0, 29674, 0x00014fa8, 256);

// 0x050150A8
ROM_ASSET_LOAD_VTX(spiny_egg_seg5_vertex_050150A8, 0x00180bb0, 29674, 0x000150a8, 256);

// 0x050151A8 - 0x050151E0
const Gfx spiny_egg_seg5_dl_050151A8[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_05014528, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x050151E0 - 0x05015218
const Gfx spiny_egg_seg5_dl_050151E0[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_050145B8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05015218 - 0x05015250
const Gfx spiny_egg_seg5_dl_05015218[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_05014648, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05015250 - 0x05015288
const Gfx spiny_egg_seg5_dl_05015250[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_050146D8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05015288 - 0x050152C0
const Gfx spiny_egg_seg5_dl_05015288[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_05014768, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x050152C0 - 0x050152F8
const Gfx spiny_egg_seg5_dl_050152C0[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_050147F8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x050152F8 - 0x05015330
const Gfx spiny_egg_seg5_dl_050152F8[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_05014888, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05015330 - 0x05015368
const Gfx spiny_egg_seg5_dl_05015330[] = {
    gsSPLight(&spiny_egg_seg5_lights_050144F8.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_050144F8.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_05014918, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05015368 - 0x05015740
const Gfx spiny_egg_seg5_dl_05015368[] = {
    gsSPLight(&spiny_egg_seg5_lights_05014510.l, 1),
    gsSPLight(&spiny_egg_seg5_lights_05014510.a, 2),
    gsSPVertex(spiny_egg_seg5_vertex_050149A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(spiny_egg_seg5_vertex_05014AA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(spiny_egg_seg5_vertex_05014BA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(spiny_egg_seg5_vertex_05014CA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(spiny_egg_seg5_vertex_05014DA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(spiny_egg_seg5_vertex_05014EA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(spiny_egg_seg5_vertex_05014FA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(spiny_egg_seg5_vertex_050150A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x05015740 - 0x05015750
const Gfx spiny_egg_seg5_dl_05015740[] = {
    gsSPNumLights(NUMLIGHTS_1),
    gsSPEndDisplayList(),
};
