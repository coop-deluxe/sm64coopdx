#include "pc/rom_assets.h"
// 0x0700B0D8 - 0x0700B0F0
static const Lights1 ddd_seg7_lights_0700B0D8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x49, 0x49, 0x49
);

// 0x0700B0F0 - 0x0700B1D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B0F0, 0x0048d930, 33063, 0x0000b0f0, 224);

// 0x0700B1D0 - 0x0700B2D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B1D0, 0x0048d930, 33063, 0x0000b1d0, 256);

// 0x0700B2D0 - 0x0700B3D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B2D0, 0x0048d930, 33063, 0x0000b2d0, 256);

// 0x0700B3D0 - 0x0700B4D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B3D0, 0x0048d930, 33063, 0x0000b3d0, 256);

// 0x0700B4D0 - 0x0700B5D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B4D0, 0x0048d930, 33063, 0x0000b4d0, 256);

// 0x0700B5D0 - 0x0700B6D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B5D0, 0x0048d930, 33063, 0x0000b5d0, 256);

// 0x0700B6D0 - 0x0700B7D0
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B6D0, 0x0048d930, 33063, 0x0000b6d0, 256);

// 0x0700B7D0 - 0x0700B890
ROM_ASSET_LOAD_VTX(ddd_seg7_vertex_0700B7D0, 0x0048d930, 33063, 0x0000b7d0, 192);

// 0x0700B890 - 0x0700BAE0
static const Gfx ddd_seg7_dl_0700B890[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ddd_seg7_texture_07002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ddd_seg7_lights_0700B0D8.l, 1),
    gsSPLight(&ddd_seg7_lights_0700B0D8.a, 2),
    gsSPVertex(ddd_seg7_vertex_0700B0F0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(11, 13, 12, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700B1D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700B2D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700B3D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700B4D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(10, 15, 11, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700B5D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700B6D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ddd_seg7_vertex_0700B7D0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11,  3,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BAE0 - 0x0700BB50
const Gfx ddd_seg7_dl_0700BAE0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ddd_seg7_dl_0700B890),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
