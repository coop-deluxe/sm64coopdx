#include "pc/rom_assets.h"
// 0x07012F18 - 0x07012F30
static const Lights1 wdw_seg7_lights_07012F18 = gdSPDefLights1(
    0x99, 0x99, 0x00,
    0xff, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x07012F30 - 0x07012F48
static const Lights1 wdw_seg7_lights_07012F30 = gdSPDefLights1(
    0x00, 0x00, 0x99,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// 0x07012F48 - 0x07012F60
static const Lights1 wdw_seg7_lights_07012F48 = gdSPDefLights1(
    0x00, 0x99, 0x00,
    0x00, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x07012F60 - 0x07012F78
static const Lights1 wdw_seg7_lights_07012F60 = gdSPDefLights1(
    0x99, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07012F78 - 0x07012FD8
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07012F78, 0x0040ed70, 45590, 0x00012f78, 96);

// 0x07012FD8 - 0x07013038
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07012FD8, 0x0040ed70, 45590, 0x00012fd8, 96);

// 0x07013038 - 0x07013098
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07013038, 0x0040ed70, 45590, 0x00013038, 96);

// 0x07013098 - 0x070130F8
ROM_ASSET_LOAD_VTX(wdw_seg7_vertex_07013098, 0x0040ed70, 45590, 0x00013098, 96);

// 0x070130F8 - 0x070131B8
static const Gfx wdw_seg7_dl_070130F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wdw_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wdw_seg7_lights_07012F18.l, 1),
    gsSPLight(&wdw_seg7_lights_07012F18.a, 2),
    gsSPVertex(wdw_seg7_vertex_07012F78, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&wdw_seg7_lights_07012F30.l, 1),
    gsSPLight(&wdw_seg7_lights_07012F30.a, 2),
    gsSPVertex(wdw_seg7_vertex_07012FD8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&wdw_seg7_lights_07012F48.l, 1),
    gsSPLight(&wdw_seg7_lights_07012F48.a, 2),
    gsSPVertex(wdw_seg7_vertex_07013038, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&wdw_seg7_lights_07012F60.l, 1),
    gsSPLight(&wdw_seg7_lights_07012F60.a, 2),
    gsSPVertex(wdw_seg7_vertex_07013098, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070131B8 - 0x07013238
const Gfx wdw_seg7_dl_070131B8[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 200),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wdw_seg7_dl_070130F8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
