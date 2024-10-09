#include "pc/rom_assets.h"
// 0x0700F830 - 0x0700F848
static const Lights1 ttc_seg7_lights_0700F830 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700F848 - 0x0700F860
static const Lights1 ttc_seg7_lights_0700F848 = gdSPDefLights1(
    0x46, 0x46, 0x46,
    0x8c, 0x8c, 0x8c, 0x28, 0x28, 0x28
);

// 0x0700F860 - 0x0700F8E0
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F860, 0x0042cf20, 42199, 0x0000f860, 128);

// 0x0700F8E0 - 0x0700F9C0
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F8E0, 0x0042cf20, 42199, 0x0000f8e0, 224);

// 0x0700F9C0 - 0x0700FA60
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F9C0, 0x0042cf20, 42199, 0x0000f9c0, 160);

// 0x0700FA60 - 0x0700FAA0
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700FA60, 0x0042cf20, 42199, 0x0000fa60, 64);

// 0x0700FAA0 - 0x0700FAF8
static const Gfx ttc_seg7_dl_0700FAA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_0700F830.l, 1),
    gsSPLight(&ttc_seg7_lights_0700F830.a, 2),
    gsSPVertex(ttc_seg7_vertex_0700F860, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FAF8 - 0x0700FB88
static const Gfx ttc_seg7_dl_0700FAF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_0700F8E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 7,  3,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_0700F9C0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  6,  0,  8, 0x0),
    gsSP1Triangle( 0,  2,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FB88 - 0x0700FBB8
static const Gfx ttc_seg7_dl_0700FB88[] = {
    gsSPLight(&ttc_seg7_lights_0700F848.l, 1),
    gsSPLight(&ttc_seg7_lights_0700F848.a, 2),
    gsSPVertex(ttc_seg7_vertex_0700FA60, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FBB8 - 0x0700FC80
const Gfx ttc_seg7_dl_0700FBB8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_0700FAA0),
    gsSPDisplayList(ttc_seg7_dl_0700FAF8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(ttc_seg7_dl_0700FB88),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
