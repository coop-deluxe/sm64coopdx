#include "pc/rom_assets.h"
// 0x07009DF0 - 0x07009EB0
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07009DF0, 0x004246d0, 32780, 0x00009df0, 192);

// 0x07009EB0 - 0x07009F58
static const Gfx thi_seg7_dl_07009EB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_07009DF0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 4,  6,  1, 0x0,  6,  7,  1, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  8,  2,  9, 0x0),
    gsSP2Triangles( 7,  9,  2, 0x0, 10,  3,  2, 0x0),
    gsSP2Triangles(10,  2,  8, 0x0, 10,  4,  5, 0x0),
    gsSP2Triangles(10,  8,  4, 0x0,  4,  8, 11, 0x0),
    gsSP2Triangles( 8,  9, 11, 0x0,  4, 11,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009F58 - 0x07009FC8
const Gfx thi_seg7_dl_07009F58[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07009EB0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
