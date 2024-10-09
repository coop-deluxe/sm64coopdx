#include "pc/rom_assets.h"
// 0x07023C70 - 0x07023C88
static const Lights1 hmc_seg7_lights_07023C70 = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07023C88 - 0x07023D48
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07023C88, 0x003d0dc0, 89137, 0x00023c88, 192);

// 0x07023D48 - 0x07023E10
static const Gfx hmc_seg7_dl_07023D48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_07004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_07023C70.l, 1),
    gsSPLight(&hmc_seg7_lights_07023C70.a, 2),
    gsSPVertex(hmc_seg7_vertex_07023C88, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  3,  8,  0, 0x0),
    gsSP2Triangles( 8,  9,  1, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles( 1,  0,  8, 0x0,  3, 10,  8, 0x0),
    gsSP2Triangles( 3,  4, 10, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles(11,  9,  7, 0x0, 11,  7,  6, 0x0),
    gsSP2Triangles(11,  1,  9, 0x0, 11,  2,  1, 0x0),
    gsSP2Triangles(11,  6,  2, 0x0,  7, 10,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07023E10 - 0x07023EB8
const Gfx hmc_seg7_dl_07023E10[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(960, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_07023D48),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
