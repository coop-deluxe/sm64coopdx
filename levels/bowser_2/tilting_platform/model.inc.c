#include "pc/rom_assets.h"
// 0x07000800 - 0x07000900
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_07000800, 0x004cdbd0, 3611, 0x00000800, 256);

// 0x07000900 - 0x07000A00
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_07000900, 0x004cdbd0, 3611, 0x00000900, 256);

// 0x07000A00 - 0x07000AA0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_07000A00, 0x004cdbd0, 3611, 0x00000a00, 160);

// 0x07000AA0 - 0x07000BA0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_07000AA0, 0x004cdbd0, 3611, 0x00000aa0, 256);

// 0x07000BA0 - 0x07000C30
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_07000BA0, 0x004cdbd0, 3611, 0x00000ba0, 144);

// 0x07000C30 - 0x07000D30
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_07000C30, 0x004cdbd0, 3611, 0x00000c30, 256);

// 0x07000D30 - 0x07000E28
const Gfx bowser_2_seg7_dl_07000D30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_2_seg7_vertex_07000800, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  7,  5,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bowser_2_seg7_vertex_07000900, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bowser_2_seg7_vertex_07000A00, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07000E28 - 0x07000ED0
static const Gfx bowser_2_seg7_dl_07000E28[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_2_seg7_vertex_07000AA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0, 11,  8,  6, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 11, 13, 14, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 10,  9, 15, 0x0),
    gsSP2Triangles( 2,  1, 14, 0x0,  0, 15,  1, 0x0),
    gsSP2Triangles( 2, 14, 13, 0x0, 10, 15,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x07000ED0 - 0x07000F38
static const Gfx bowser_2_seg7_dl_07000ED0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_2_seg7_vertex_07000BA0, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  4,  6,  2, 0x0),
    gsSP2Triangles( 8,  5,  2, 0x0,  7,  8,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07000F38 - 0x07000FE0
static const Gfx bowser_2_seg7_dl_07000F38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_2_seg7_vertex_07000C30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  0,  8,  3, 0x0),
    gsSP2Triangles( 0, 11,  8, 0x0, 12, 13,  2, 0x0),
    gsSP2Triangles(14, 13, 12, 0x0, 12,  2,  1, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 10,  9, 15, 0x0),
    gsSP2Triangles(14, 15, 13, 0x0, 10, 15, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07000FE0 - 0x070010B0
const Gfx bowser_2_seg7_dl_07000FE0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 50, 0, 255),
    gsSPFogPosition(960, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bowser_2_seg7_dl_07000D30),
    gsSPDisplayList(bowser_2_seg7_dl_07000E28),
    gsSPDisplayList(bowser_2_seg7_dl_07000ED0),
    gsSPDisplayList(bowser_2_seg7_dl_07000F38),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
