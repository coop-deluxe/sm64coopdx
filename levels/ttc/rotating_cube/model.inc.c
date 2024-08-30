#include "pc/rom_assets.h"
// 0x0700E950 - 0x0700E968
static const Lights1 ttc_seg7_lights_0700E950 = gdSPDefLights1(
    0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x0700E968 - 0x0700E980
static const Lights1 ttc_seg7_lights_0700E968 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700E980 - 0x0700EA20
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700E980, 0x0042cf20, 42199, 0x0000e980, 160);

// 0x0700EA20 - 0x0700EAC0
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700EA20, 0x0042cf20, 42199, 0x0000ea20, 160);

// 0x0700EAC0 - 0x0700EBC0
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700EAC0, 0x0042cf20, 42199, 0x0000eac0, 256);

// 0x0700EBC0 - 0x0700EC50
static const Gfx ttc_seg7_dl_0700EBC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_0700E950.l, 1),
    gsSPLight(&ttc_seg7_lights_0700E950.a, 2),
    gsSPVertex(ttc_seg7_vertex_0700E980, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  6,  9, 0x0),
    gsSPLight(&ttc_seg7_lights_0700E968.l, 1),
    gsSPLight(&ttc_seg7_lights_0700E968.a, 2),
    gsSPVertex(ttc_seg7_vertex_0700EA20, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  6,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EC50 - 0x0700ECB8
static const Gfx ttc_seg7_dl_0700EC50[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_0700EAC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700ECB8 - 0x0700ED68
const Gfx ttc_seg7_dl_0700ECB8[] = {
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
    gsSPDisplayList(ttc_seg7_dl_0700EBC0),
    gsSPDisplayList(ttc_seg7_dl_0700EC50),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
