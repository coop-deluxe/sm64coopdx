#include "pc/rom_assets.h"
// 0x0700F090 - 0x0700F0A8
static const Lights1 ttc_seg7_lights_0700F090 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700F0A8 - 0x0700F188
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F0A8, 0x0042cf20, 42199, 0x0000f0a8, 224);

// 0x0700F188 - 0x0700F278
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F188, 0x0042cf20, 42199, 0x0000f188, 240);

// 0x0700F278 - 0x0700F338
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F278, 0x0042cf20, 42199, 0x0000f278, 192);

// 0x0700F338 - 0x0700F438
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F338, 0x0042cf20, 42199, 0x0000f338, 256);

// 0x0700F438 - 0x0700F528
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_0700F438, 0x0042cf20, 42199, 0x0000f438, 240);

// 0x0700F528 - 0x0700F5A0
static const Gfx ttc_seg7_dl_0700F528[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttc_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 64 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_0700F090.l, 1),
    gsSPLight(&ttc_seg7_lights_0700F090.a, 2),
    gsSPVertex(ttc_seg7_vertex_0700F0A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  0, 13,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F5A0 - 0x0700F670
static const Gfx ttc_seg7_dl_0700F5A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_0700F188, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  6,  9, 0x0,  3, 10, 11, 0x0),
    gsSP2Triangles( 3, 11, 12, 0x0,  3,  8, 10, 0x0),
    gsSP2Triangles( 3,  9, 13, 0x0,  3, 13, 14, 0x0),
    gsSP1Triangle( 3, 14,  7, 0x0),
    gsSPVertex(ttc_seg7_vertex_0700F278, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 0,  8,  7, 0x0,  0,  6,  8, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  0, 10, 11, 0x0),
    gsSP1Triangle( 0, 11,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F670 - 0x0700F760
static const Gfx ttc_seg7_dl_0700F670[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_0700F338, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles( 9, 10,  6, 0x0,  8,  7, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  1, 12, 11, 0x0),
    gsSP2Triangles( 1,  0, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_0700F438, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F760 - 0x0700F830
const Gfx ttc_seg7_dl_0700F760[] = {
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
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_0700F528),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_0700F5A0),
    gsSPDisplayList(ttc_seg7_dl_0700F670),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
