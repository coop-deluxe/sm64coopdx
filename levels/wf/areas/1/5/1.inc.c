#include "pc/rom_assets.h"
// 0x070056C0 - 0x070056D8
static const Lights1 wf_seg7_lights_070056C0 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070056D8 - 0x070057C8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_070056D8, 0x00496090, 31162, 0x000056d8, 240);

// 0x070057C8 - 0x070058B8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_070057C8, 0x00496090, 31162, 0x000057c8, 240);

// 0x070058B8 - 0x070059A8
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_070058B8, 0x00496090, 31162, 0x000058b8, 240);

// 0x070059A8 - 0x07005A98
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_070059A8, 0x00496090, 31162, 0x000059a8, 240);

// 0x07005A98 - 0x07005B88
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_07005A98, 0x00496090, 31162, 0x00005a98, 240);

// 0x07005B88 - 0x07005C38
ROM_ASSET_LOAD_VTX(wf_seg7_vertex_07005B88, 0x00496090, 31162, 0x00005b88, 176);

// 0x07005C38 - 0x07005DD8
static const Gfx wf_seg7_dl_07005C38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_070056C0.l, 1),
    gsSPLight(&wf_seg7_lights_070056C0.a, 2),
    gsSPVertex(wf_seg7_vertex_070056D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 12, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_070057C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP1Triangle(14,  1,  0, 0x0),
    gsSPVertex(wf_seg7_vertex_070058B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 12, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_070059A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP1Triangle(14,  1,  0, 0x0),
    gsSPVertex(wf_seg7_vertex_07005A98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 13, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_07005B88, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP1Triangle(10,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005DD8 - 0x07005E48
const Gfx wf_seg7_dl_07005DD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_dl_07005C38),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
