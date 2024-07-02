#include "pc/rom_assets.h"
// 0x0700C488 - 0x0700C4A0
static const Lights1 ttm_seg7_lights_0700C488 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700C4A0 - 0x0700C4B8
static const Lights1 ttm_seg7_lights_0700C4A0 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700C4B8 - 0x0700C4D0
static const Lights1 ttm_seg7_lights_0700C4B8 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700C4D0 - 0x0700C5D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C4D0, 0x004d1910, 104662, 0x0000c4d0, 256);

// 0x0700C5D0 - 0x0700C600
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C5D0, 0x004d1910, 104662, 0x0000c5d0, 48);

// 0x0700C600 - 0x0700C690
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C600, 0x004d1910, 104662, 0x0000c600, 144);

// 0x0700C690 - 0x0700C780
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C690, 0x004d1910, 104662, 0x0000c690, 240);

// 0x0700C780 - 0x0700C7B0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C780, 0x004d1910, 104662, 0x0000c780, 48);

// 0x0700C7B0 - 0x0700C810
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C7B0, 0x004d1910, 104662, 0x0000c7b0, 96);

// 0x0700C810 - 0x0700C850
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C810, 0x004d1910, 104662, 0x0000c810, 64);

// 0x0700C850 - 0x0700C8C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C850, 0x004d1910, 104662, 0x0000c850, 112);

// 0x0700C8C0 - 0x0700C900
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0700C8C0, 0x004d1910, 104662, 0x0000c8c0, 64);

// 0x0700C900 - 0x0700C9F8
static const Gfx ttm_seg7_dl_0700C900[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700C488.l, 1),
    gsSPLight(&ttm_seg7_lights_0700C488.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700C4D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700C5D0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_0700C4A0.l, 1),
    gsSPLight(&ttm_seg7_lights_0700C4A0.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700C600, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPLight(&ttm_seg7_lights_0700C4B8.l, 1),
    gsSPLight(&ttm_seg7_lights_0700C4B8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700C690, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0700C780, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C9F8 - 0x0700CA78
static const Gfx ttm_seg7_dl_0700C9F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0700C488.l, 1),
    gsSPLight(&ttm_seg7_lights_0700C488.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700C7B0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  2,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0700C4B8.l, 1),
    gsSPLight(&ttm_seg7_lights_0700C4B8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700C810, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CA78 - 0x0700CAE0
static const Gfx ttm_seg7_dl_0700CA78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttm_seg7_texture_07001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_0700C850, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  6,  4, 0x0),
    gsSPLight(&ttm_seg7_lights_0700C488.l, 1),
    gsSPLight(&ttm_seg7_lights_0700C488.a, 2),
    gsSPVertex(ttm_seg7_vertex_0700C8C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CAE0 - 0x0700CB60
const Gfx ttm_seg7_dl_0700CAE0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0700C900),
    gsSPDisplayList(ttm_seg7_dl_0700C9F8),
    gsSPDisplayList(ttm_seg7_dl_0700CA78),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
