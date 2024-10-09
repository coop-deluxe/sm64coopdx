#include "pc/rom_assets.h"
// 0x070010B0 - 0x070011B0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_070010B0, 0x004cdbd0, 3611, 0x000010b0, 256);

// 0x070011B0 - 0x070012B0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_070011B0, 0x004cdbd0, 3611, 0x000011b0, 256);

// 0x070012B0 - 0x070012E0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_070012B0, 0x004cdbd0, 3611, 0x000012b0, 48);

// 0x070012E0 - 0x070013E0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_070012E0, 0x004cdbd0, 3611, 0x000012e0, 256);

// 0x070013E0 - 0x070014E0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_070013E0, 0x004cdbd0, 3611, 0x000013e0, 256);

// 0x070014E0 - 0x070015E0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_070014E0, 0x004cdbd0, 3611, 0x000014e0, 256);

// 0x070015E0 - 0x070016A0
ROM_ASSET_LOAD_VTX(bowser_2_seg7_vertex_070015E0, 0x004cdbd0, 3611, 0x000015e0, 192);

// 0x070016A0 - 0x07001788
static const Gfx bowser_2_seg7_dl_070016A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bowser_2_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_2_seg7_vertex_070010B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  4, 0x0, 11, 10,  7, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0,  2, 12, 11, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bowser_2_seg7_vertex_070011B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  9, 12, 13, 0x0),
    gsSP1Triangle( 9, 14, 15, 0x0),
    gsSPVertex(bowser_2_seg7_vertex_070012B0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07001788 - 0x07001930
static const Gfx bowser_2_seg7_dl_07001788[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bowser_2_seg7_vertex_070012E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  8,  6,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 10, 12, 11, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 14,  9, 11, 0x0),
    gsSP2Triangles(13, 14, 11, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(bowser_2_seg7_vertex_070013E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 12, 14, 13, 0x0),
    gsSP1Triangle(14, 15, 13, 0x0),
    gsSPVertex(bowser_2_seg7_vertex_070014E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 9,  4,  6, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(11, 13, 12, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(15, 10, 12, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(bowser_2_seg7_vertex_070015E0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0, 10,  6,  8, 0x0),
    gsSP2Triangles(11, 10,  8, 0x0,  9, 11,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07001930 - 0x070019F0
const Gfx bowser_2_seg7_dl_07001930[] = {
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
    gsSPDisplayList(bowser_2_seg7_dl_070016A0),
    gsSPDisplayList(bowser_2_seg7_dl_07001788),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
