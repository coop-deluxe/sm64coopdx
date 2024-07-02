#include "pc/rom_assets.h"
// Bowser Key

// 0x030156E0, ambient color brown - light color orange
static const Lights1 bowser_key_lights = gdSPDefLights1(
    0x3f, 0x2c, 0x00,
    0xff, 0xb2, 0x00, 0x28, 0x28, 0x28
);

ALIGNED8 const Texture bowser_key_left_texture[] = {
#include "actors/bowser_key/bowser_key_left.rgba16.inc.c"
};

ALIGNED8 const Texture bowser_key_right_texture[] = {
#include "actors/bowser_key/bowser_key_right.rgba16.inc.c"
};

// 0x030156F8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group1, 0x00201410, 96653, 0x000156f8, 256);

// 0x030157F8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group2, 0x00201410, 96653, 0x000157f8, 256);

// 0x030158F8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group3, 0x00201410, 96653, 0x000158f8, 256);

// 0x030159F8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group4, 0x00201410, 96653, 0x000159f8, 256);

// 0x03015AF8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group5, 0x00201410, 96653, 0x00015af8, 256);

// 0x03015BF8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group6, 0x00201410, 96653, 0x00015bf8, 256);

// 0x03015CF8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group7, 0x00201410, 96653, 0x00015cf8, 224);

// 0x03015DD8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group8, 0x00201410, 96653, 0x00015dd8, 256);

// 0x03015ED8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group9, 0x00201410, 96653, 0x00015ed8, 256);

// 0x03015FD8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group10, 0x00201410, 96653, 0x00015fd8, 224);

// 0x030160B8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group11, 0x00201410, 96653, 0x000160b8, 256);

// 0x030161B8
ROM_ASSET_LOAD_VTX(bowser_key_dl_vertex_group12, 0x00201410, 96653, 0x000161b8, 64);

// 0x030161F8 - 0x03016530
const Gfx bowser_key_dl[] = {
    gsSPLight(&bowser_key_lights.l, 1),
    gsSPLight(&bowser_key_lights.a, 2),
    gsSPVertex(bowser_key_dl_vertex_group1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group4, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group5, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 13, 15, 10, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group6, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group7, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group9, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group10, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group11, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bowser_key_dl_vertex_group12, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};
