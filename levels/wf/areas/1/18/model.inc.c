#include "pc/rom_assets.h"
// 0x0700BFE0 - 0x0700BFF8
static const Lights1 wf_seg7_lights_0700BFE0 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700BFF8 - 0x0700C0E8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700BFF8, 0x00496090, 31162, 0x0000bff8, 240);

// 0x0700C0E8 - 0x0700C1E8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C0E8, 0x00496090, 31162, 0x0000c0e8, 256);

// 0x0700C1E8 - 0x0700C218
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C1E8, 0x00496090, 31162, 0x0000c1e8, 48);

// 0x0700C218 - 0x0700C318
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C218, 0x00496090, 31162, 0x0000c218, 256);

// 0x0700C318 - 0x0700C3F8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C318, 0x00496090, 31162, 0x0000c318, 224);

// 0x0700C3F8 - 0x0700C4E8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C3F8, 0x00496090, 31162, 0x0000c3f8, 240);

// 0x0700C4E8 - 0x0700C5D8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C4E8, 0x00496090, 31162, 0x0000c4e8, 240);

// 0x0700C5D8 - 0x0700C6C8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C5D8, 0x00496090, 31162, 0x0000c5d8, 240);

// 0x0700C6C8 - 0x0700C7B8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C6C8, 0x00496090, 31162, 0x0000c6c8, 240);

// 0x0700C7B8 - 0x0700C8A8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C7B8, 0x00496090, 31162, 0x0000c7b8, 240);

// 0x0700C8A8 - 0x0700C998
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C8A8, 0x00496090, 31162, 0x0000c8a8, 240);

// 0x0700C998 - 0x0700CA88
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700C998, 0x00496090, 31162, 0x0000c998, 240);

// 0x0700CA88 - 0x0700CB78
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700CA88, 0x00496090, 31162, 0x0000ca88, 240);

// 0x0700CB78 - 0x0700CC38
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_0700CB78, 0x00496090, 31162, 0x0000cb78, 192);

// 0x0700CC38 - 0x0700CD00
static const Gfx wf_seg7_dl_0700CC38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_0700BFE0.l, 1),
    gsSPLight(&wf_seg7_lights_0700BFE0.a, 2),
    gsSPVertex(wf_seg7_vertex_0700BFF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C0E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 15, 0x0, 11, 15, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C1E8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CD00 - 0x0700CDB0
static const Gfx wf_seg7_dl_0700CD00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_0700C218, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C318, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  1,  4,  6, 0x0),
    gsSP2Triangles( 1,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CDB0 - 0x0700D028
static const Gfx wf_seg7_dl_0700CDB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_0700C3F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C4E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C5D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 10,  7, 0x0,  9,  3,  5, 0x0),
    gsSP2Triangles( 9,  5, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C6C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C7B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C8A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_0700C998, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_0700CA88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(wf_seg7_vertex_0700CB78, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D028 - 0x0700D0A8
const Gfx wf_seg7_dl_0700D028[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_dl_0700CC38),
    gsSPDisplayList(wf_seg7_dl_0700CD00),
    gsSPDisplayList(wf_seg7_dl_0700CDB0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
