#include "pc/rom_assets.h"
// Water Ring

// 0x06012368
static const Lights1 water_ring_seg6_lights_06012368 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06012380
ROM_ASSET_LOAD_TEXTURE(water_ring_seg6_texture_06012380, "actors/water_ring/water_ring.rgba16.inc.c", 0x001b9cc0, 41188, 0x00012380, 4096);

// 0x06013380
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013380, 0x001b9cc0, 41188, 0x00013380, 256);

// 0x06013480
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013480, 0x001b9cc0, 41188, 0x00013480, 256);

// 0x06013580
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013580, 0x001b9cc0, 41188, 0x00013580, 256);

// 0x06013680
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013680, 0x001b9cc0, 41188, 0x00013680, 256);

// 0x06013780
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013780, 0x001b9cc0, 41188, 0x00013780, 256);

// 0x06013880
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013880, 0x001b9cc0, 41188, 0x00013880, 256);

// 0x06013980
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013980, 0x001b9cc0, 41188, 0x00013980, 256);

// 0x06013A80
ROM_ASSET_LOAD_VTX(water_ring_seg6_vertex_06013A80, 0x001b9cc0, 41188, 0x00013a80, 64);

// 0x06013AC0 - 0x06013DD8
const Gfx water_ring_seg6_dl_06013AC0[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_DECALFADE, G_CC_DECALFADE),
    gsDPLoadTextureBlock(water_ring_seg6_texture_06012380, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTexture(0x1800, 0x07C0, 0, G_TX_RENDERTILE, G_ON),
    gsSPLight(&water_ring_seg6_lights_06012368.l, 1),
    gsSPLight(&water_ring_seg6_lights_06012368.a, 2),
    gsSPVertex(water_ring_seg6_vertex_06013380, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 15, 0x0,  5, 15,  6, 0x0),
    gsSPVertex(water_ring_seg6_vertex_06013480, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 15, 0x0,  5, 15,  6, 0x0),
    gsSPVertex(water_ring_seg6_vertex_06013580, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 15, 0x0,  5, 15,  6, 0x0),
    gsSPVertex(water_ring_seg6_vertex_06013680, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 15, 0x0,  5, 15,  6, 0x0),
    gsSPVertex(water_ring_seg6_vertex_06013780, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 15, 0x0,  5, 15,  6, 0x0),
    gsSPVertex(water_ring_seg6_vertex_06013880, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 15, 0x0,  5, 15,  6, 0x0),
    gsSPVertex(water_ring_seg6_vertex_06013980, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 15, 0x0,  5, 15,  6, 0x0),
    gsSPVertex(water_ring_seg6_vertex_06013A80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0F80, 0x07C0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};
