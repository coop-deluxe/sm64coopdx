#include "pc/rom_assets.h"
// 0x07011BE0 - 0x07011BF8
static const Lights1 ttc_seg7_lights_07011BE0 = gdSPDefLights1(
    0x46, 0x46, 0x46,
    0x8c, 0x8c, 0x8c, 0x28, 0x28, 0x28
);

// 0x07011BF8 - 0x07011C10
static const Lights1 ttc_seg7_lights_07011BF8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07011C10 - 0x07011D10
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07011C10, 0x0042cf20, 42199, 0x00011c10, 256);

// 0x07011D10 - 0x07011DC0
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07011D10, 0x0042cf20, 42199, 0x00011d10, 176);

// 0x07011DC0 - 0x07011EC0
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07011DC0, 0x0042cf20, 42199, 0x00011dc0, 256);

// 0x07011EC0 - 0x07012028
static const Gfx ttc_seg7_dl_07011EC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_07011BE0.l, 1),
    gsSPLight(&ttc_seg7_lights_07011BE0.a, 2),
    gsSPVertex(ttc_seg7_vertex_07011C10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  2,  6,  3, 0x0),
    gsSP2Triangles( 2,  7,  6, 0x0,  6,  8,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles( 9,  4,  8, 0x0,  2, 10, 11, 0x0),
    gsSP2Triangles( 9, 12,  0, 0x0, 13,  1, 12, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 12,  9, 0x0),
    gsSP2Triangles( 2,  1, 13, 0x0,  2, 14, 15, 0x0),
    gsSP2Triangles( 2,  3, 14, 0x0,  2, 11,  7, 0x0),
    gsSPVertex(ttc_seg7_vertex_07011D10, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  7,  4, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles( 8, 10,  3, 0x0,  8,  3,  2, 0x0),
    gsSPLight(&ttc_seg7_lights_07011BF8.l, 1),
    gsSPLight(&ttc_seg7_lights_07011BF8.a, 2),
    gsSPVertex(ttc_seg7_vertex_07011DC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012028 - 0x070120D0
const Gfx ttc_seg7_dl_07012028[] = {
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
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_07011EC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
