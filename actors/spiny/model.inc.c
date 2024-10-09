#include "pc/rom_assets.h"
// Spiny

// 0x050157F8
static const Lights1 spiny_seg5_lights_050157F8 = gdSPDefLights1(
    0x32, 0x23, 0x0a,
    0xca, 0x8d, 0x29, 0x28, 0x28, 0x28
);

// 0x05015810
static const Lights1 spiny_seg5_lights_05015810 = gdSPDefLights1(
    0x3a, 0x2c, 0x1f,
    0xeb, 0xb0, 0x7f, 0x28, 0x28, 0x28
);

// 0x05015828
static const Lights1 spiny_seg5_lights_05015828 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x05015840
static const Lights1 spiny_seg5_lights_05015840 = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05015858
static const Lights1 spiny_seg5_lights_05015858 = gdSPDefLights1(
    0x3d, 0x25, 0x01,
    0xf4, 0x96, 0x07, 0x28, 0x28, 0x28
);

// 0x05015870
static const Lights1 spiny_seg5_lights_05015870 = gdSPDefLights1(
    0x3c, 0x2c, 0x09,
    0xf1, 0xb2, 0x25, 0x28, 0x28, 0x28
);

// 0x05015888
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015888, 0x00180bb0, 29674, 0x00015888, 208);

// 0x05015958
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015958, 0x00180bb0, 29674, 0x00015958, 96);

// 0x050159B8
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_050159B8, 0x00180bb0, 29674, 0x000159b8, 208);

// 0x05015A88
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015A88, 0x00180bb0, 29674, 0x00015a88, 96);

// 0x05015AE8
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015AE8, 0x00180bb0, 29674, 0x00015ae8, 208);

// 0x05015BB8
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015BB8, 0x00180bb0, 29674, 0x00015bb8, 96);

// 0x05015C18
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015C18, 0x00180bb0, 29674, 0x00015c18, 208);

// 0x05015CE8
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015CE8, 0x00180bb0, 29674, 0x00015ce8, 96);

// 0x05015D48
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015D48, 0x00180bb0, 29674, 0x00015d48, 256);

// 0x05015E48
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015E48, 0x00180bb0, 29674, 0x00015e48, 256);

// 0x05015F48
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015F48, 0x00180bb0, 29674, 0x00015f48, 96);

// 0x05015FA8
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05015FA8, 0x00180bb0, 29674, 0x00015fa8, 256);

// 0x050160A8
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_050160A8, 0x00180bb0, 29674, 0x000160a8, 160);

// 0x05016148
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05016148, 0x00180bb0, 29674, 0x00016148, 240);

// 0x05016238
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05016238, 0x00180bb0, 29674, 0x00016238, 240);

// 0x05016328
ROM_ASSET_LOAD_VTX(spiny_seg5_vertex_05016328, 0x00180bb0, 29674, 0x00016328, 240);

// 0x05016418 - 0x050164E0
const Gfx spiny_seg5_dl_05016418[] = {
    gsSPLight(&spiny_seg5_lights_050157F8.l, 1),
    gsSPLight(&spiny_seg5_lights_050157F8.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015888, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 5,  4,  0, 0x0,  0, 10, 11, 0x0),
    gsSP2Triangles(11,  6,  3, 0x0,  1, 12,  9, 0x0),
    gsSP2Triangles( 3,  5, 11, 0x0, 11,  5,  0, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  9, 12,  8, 0x0),
    gsSP2Triangles( 9,  2,  1, 0x0,  2, 10,  0, 0x0),
    gsSPLight(&spiny_seg5_lights_05015810.l, 1),
    gsSPLight(&spiny_seg5_lights_05015810.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015958, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  1,  5,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x050164E0 - 0x050165A8
const Gfx spiny_seg5_dl_050164E0[] = {
    gsSPLight(&spiny_seg5_lights_050157F8.l, 1),
    gsSPLight(&spiny_seg5_lights_050157F8.a, 2),
    gsSPVertex(spiny_seg5_vertex_050159B8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 5,  4,  0, 0x0,  0, 10, 11, 0x0),
    gsSP2Triangles(11,  6,  3, 0x0,  1, 12,  9, 0x0),
    gsSP2Triangles( 3,  5, 11, 0x0, 11,  5,  0, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  9, 12,  8, 0x0),
    gsSP2Triangles( 9,  2,  1, 0x0,  2, 10,  0, 0x0),
    gsSPLight(&spiny_seg5_lights_05015810.l, 1),
    gsSPLight(&spiny_seg5_lights_05015810.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015A88, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  1,  5,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x050165A8 - 0x05016670
const Gfx spiny_seg5_dl_050165A8[] = {
    gsSPLight(&spiny_seg5_lights_050157F8.l, 1),
    gsSPLight(&spiny_seg5_lights_050157F8.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015AE8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0, 10, 11,  2, 0x0),
    gsSP2Triangles( 5,  7, 10, 0x0,  8, 12,  1, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0,  2,  3, 10, 0x0),
    gsSP2Triangles( 5,  9,  6, 0x0,  9, 12,  8, 0x0),
    gsSP2Triangles( 1,  0,  8, 0x0,  2, 11,  0, 0x0),
    gsSPLight(&spiny_seg5_lights_05015810.l, 1),
    gsSPLight(&spiny_seg5_lights_05015810.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015BB8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  0,  5,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05016670 - 0x05016738
const Gfx spiny_seg5_dl_05016670[] = {
    gsSPLight(&spiny_seg5_lights_050157F8.l, 1),
    gsSPLight(&spiny_seg5_lights_050157F8.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015C18, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0, 10, 11,  2, 0x0),
    gsSP2Triangles( 5,  7, 10, 0x0,  8, 12,  1, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0,  2,  3, 10, 0x0),
    gsSP2Triangles( 5,  9,  6, 0x0,  9, 12,  8, 0x0),
    gsSP2Triangles( 1,  0,  8, 0x0,  2, 11,  0, 0x0),
    gsSPLight(&spiny_seg5_lights_05015810.l, 1),
    gsSPLight(&spiny_seg5_lights_05015810.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015CE8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  0,  5,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05016738 - 0x05016A48
const Gfx spiny_seg5_dl_05016738[] = {
    gsSPLight(&spiny_seg5_lights_05015828.l, 1),
    gsSPLight(&spiny_seg5_lights_05015828.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015D48, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  1,  0,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9,  6, 0x0, 10,  6,  4, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0,  1, 12,  3, 0x0),
    gsSP2Triangles(10, 12,  8, 0x0, 10,  3, 12, 0x0),
    gsSP2Triangles( 4,  3, 10, 0x0, 13, 11, 14, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 15, 14,  5, 0x0),
    gsSPVertex(spiny_seg5_vertex_05015E48, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10, 11,  6, 0x0),
    gsSP2Triangles( 6, 11, 12, 0x0, 10,  6,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSP2Triangles(14, 15,  7, 0x0, 12,  0, 13, 0x0),
    gsSP2Triangles( 7,  6, 14, 0x0, 14,  6, 12, 0x0),
    gsSPVertex(spiny_seg5_vertex_05015F48, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  2,  4, 0x0,  4,  2,  1, 0x0),
    gsSPLight(&spiny_seg5_lights_05015858.l, 1),
    gsSPLight(&spiny_seg5_lights_05015858.a, 2),
    gsSPVertex(spiny_seg5_vertex_05015FA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  6,  0,  4, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(11,  9, 12, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles(11, 13, 10, 0x0,  0,  5,  9, 0x0),
    gsSP2Triangles(14,  3, 15, 0x0, 14, 15, 13, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  0, 10,  1, 0x0),
    gsSP2Triangles( 6,  5,  0, 0x0, 15, 10, 13, 0x0),
    gsSP2Triangles( 3,  1, 15, 0x0, 10, 15,  1, 0x0),
    gsSPLight(&spiny_seg5_lights_05015840.l, 1),
    gsSPLight(&spiny_seg5_lights_05015840.a, 2),
    gsSPVertex(spiny_seg5_vertex_050160A8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  8,  1, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  3,  1,  7, 0x0),
    gsSP2Triangles( 3,  5,  9, 0x0,  1,  8,  7, 0x0),
    gsSP2Triangles( 3,  9,  2, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 4,  7,  6, 0x0,  4,  6,  5, 0x0),
    gsSPLight(&spiny_seg5_lights_05015870.l, 1),
    gsSPLight(&spiny_seg5_lights_05015870.a, 2),
    gsSPVertex(spiny_seg5_vertex_05016148, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(spiny_seg5_vertex_05016238, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(spiny_seg5_vertex_05016328, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05016A48 - 0x05016A58
const Gfx spiny_seg5_dl_05016A48[] = {
    gsSPNumLights(NUMLIGHTS_1),
    gsSPEndDisplayList(),
};
