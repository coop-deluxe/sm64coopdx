#include "pc/rom_assets.h"
// 0x07006A98 - 0x07006AB0
static const Lights1 jrb_seg7_lights_07006A98 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07006AB0 - 0x07006BA0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006AB0, 0x0041a760, 37817, 0x00006ab0, 240);

// 0x07006BA0 - 0x07006CA0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006BA0, 0x0041a760, 37817, 0x00006ba0, 256);

// 0x07006CA0 - 0x07006D90
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006CA0, 0x0041a760, 37817, 0x00006ca0, 240);

// 0x07006D90 - 0x07006E70
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006D90, 0x0041a760, 37817, 0x00006d90, 224);

// 0x07006E70 - 0x07006F60
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006E70, 0x0041a760, 37817, 0x00006e70, 240);

// 0x07006F60 - 0x07007050
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07006F60, 0x0041a760, 37817, 0x00006f60, 240);

// 0x07007050 - 0x07007110
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07007050, 0x0041a760, 37817, 0x00007050, 192);

// 0x07007110 - 0x070071D0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07007110, 0x0041a760, 37817, 0x00007110, 192);

// 0x070071D0 - 0x070072A0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070071D0, 0x0041a760, 37817, 0x000071d0, 208);

// 0x070072A0 - 0x070074A8
static const Gfx jrb_seg7_dl_070072A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_07006A98.l, 1),
    gsSPLight(&jrb_seg7_lights_07006A98.a, 2),
    gsSPVertex(jrb_seg7_vertex_07006AB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006BA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0,  6, 11,  7, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006CA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006D90, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006E70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(jrb_seg7_vertex_07006F60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(jrb_seg7_vertex_07007050, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  3,  4, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 8,  6,  7, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0,  9, 11, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x070074A8 - 0x07007500
static const Gfx jrb_seg7_dl_070074A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_07007110, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007500 - 0x07007570
static const Gfx jrb_seg7_dl_07007500[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_070071D0, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  0, 11, 12, 0x0),
    gsSP1Triangle( 0, 12,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007570 - 0x07007628
const Gfx jrb_seg7_dl_07007570[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070072A0),
    gsSPDisplayList(jrb_seg7_dl_070074A8),
    gsSPDisplayList(jrb_seg7_dl_07007500),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
