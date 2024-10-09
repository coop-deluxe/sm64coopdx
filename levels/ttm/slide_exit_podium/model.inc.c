#include "pc/rom_assets.h"
// 0x0702ACE8 - 0x0702AD00
static const Lights1 ttm_seg7_lights_0702ACE8 = gdSPDefLights1(
    0x0c, 0x0c, 0x0c,
    0x33, 0x33, 0x33, 0x28, 0x28, 0x28
);

// 0x0702AD00 - 0x0702AD18
static const Lights1 ttm_seg7_lights_0702AD00 = gdSPDefLights1(
    0x1d, 0x1d, 0x1d,
    0x77, 0x77, 0x77, 0x28, 0x28, 0x28
);

// 0x0702AD18 - 0x0702AD30
static const Lights1 ttm_seg7_lights_0702AD18 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0702AD30 - 0x0702B530
ROM_ASSET_LOAD_TEXTURE(ttm_seg7_texture_0702AD30, "levels/ttm/8.rgba16.inc.c", 0x00351960, 23013, 0x0000a800, 2048);

// 0x0702B530 - 0x0702B570
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0702B530, 0x004d1910, 104662, 0x0002b530, 64);

// 0x0702B570 - 0x0702B670
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0702B570, 0x004d1910, 104662, 0x0002b570, 256);

// 0x0702B670 - 0x0702B770
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0702B670, 0x004d1910, 104662, 0x0002b670, 256);

// 0x0702B770 - 0x0702B870
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0702B770, 0x004d1910, 104662, 0x0002b770, 256);

// 0x0702B870 - 0x0702B970
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0702B870, 0x004d1910, 104662, 0x0002b870, 256);

// 0x0702B970 - 0x0702B9D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0702B970, 0x004d1910, 104662, 0x0002b970, 96);

// 0x0702B9D0 - 0x0702BB60
static const Gfx ttm_seg7_dl_0702B9D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttm_seg7_texture_0702AD30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0702ACE8.l, 1),
    gsSPLight(&ttm_seg7_lights_0702ACE8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0702B530, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_0702AD00.l, 1),
    gsSPLight(&ttm_seg7_lights_0702AD00.a, 2),
    gsSPVertex(ttm_seg7_vertex_0702B570, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPLight(&ttm_seg7_lights_0702AD18.l, 1),
    gsSPLight(&ttm_seg7_lights_0702AD18.a, 2),
    gsSPVertex(ttm_seg7_vertex_0702B670, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0702B770, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0702B870, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_0702B970, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0702BB60 - 0x0702BBD0
const Gfx ttm_seg7_dl_0702BB60[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0702B9D0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
