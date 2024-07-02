#include "pc/rom_assets.h"
// 0x0700EF98 - 0x0700EFB0
static const Lights1 jrb_seg7_lights_0700EF98 = gdSPDefLights1(
    0x3c, 0x66, 0x66,
    0x96, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700EFB0 - 0x0700F0B0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700EFB0, 0x0041a760, 37817, 0x0000efb0, 256);

// 0x0700F0B0 - 0x0700F190
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F0B0, 0x0041a760, 37817, 0x0000f0b0, 224);

// 0x0700F190 - 0x0700F270
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F190, 0x0041a760, 37817, 0x0000f190, 224);

// 0x0700F270 - 0x0700F350
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F270, 0x0041a760, 37817, 0x0000f270, 224);

// 0x0700F350 - 0x0700F440
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F350, 0x0041a760, 37817, 0x0000f350, 240);

// 0x0700F440 - 0x0700F520
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F440, 0x0041a760, 37817, 0x0000f440, 224);

// 0x0700F520 - 0x0700F600
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F520, 0x0041a760, 37817, 0x0000f520, 224);

// 0x0700F600 - 0x0700F6E0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F600, 0x0041a760, 37817, 0x0000f600, 224);

// 0x0700F6E0 - 0x0700F7C0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F6E0, 0x0041a760, 37817, 0x0000f6e0, 224);

// 0x0700F7C0 - 0x0700F8A0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F7C0, 0x0041a760, 37817, 0x0000f7c0, 224);

// 0x0700F8A0 - 0x0700F9A0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F8A0, 0x0041a760, 37817, 0x0000f8a0, 256);

// 0x0700F9A0 - 0x0700FA90
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700F9A0, 0x0041a760, 37817, 0x0000f9a0, 240);

// 0x0700FA90 - 0x0700FB30
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700FA90, 0x0041a760, 37817, 0x0000fa90, 160);

// 0x0700FB30 - 0x0700FE48
static const Gfx jrb_seg7_dl_0700FB30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_0700EF98.l, 1),
    gsSPLight(&jrb_seg7_lights_0700EF98.a, 2),
    gsSPVertex(jrb_seg7_vertex_0700EFB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 0, 14,  1, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F0B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F190, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F270, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F350, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F440, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F520, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F600, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F6E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F7C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F8A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700F9A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700FA90, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FE48 - 0x0700FEB8
const Gfx jrb_seg7_dl_0700FE48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_0700FB30),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
