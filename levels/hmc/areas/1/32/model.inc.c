#include "pc/rom_assets.h"
// 0x07021C10 - 0x07021D10
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07021C10, 0x003d0dc0, 89137, 0x00021c10, 256);

// 0x07021D10 - 0x07021E10
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07021D10, 0x003d0dc0, 89137, 0x00021d10, 256);

// 0x07021E10 - 0x07021F10
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07021E10, 0x003d0dc0, 89137, 0x00021e10, 256);

// 0x07021F10 - 0x07022000
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07021F10, 0x003d0dc0, 89137, 0x00021f10, 240);

// 0x07022000 - 0x07022100
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07022000, 0x003d0dc0, 89137, 0x00022000, 256);

// 0x07022100 - 0x07022200
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07022100, 0x003d0dc0, 89137, 0x00022100, 256);

// 0x07022200 - 0x070222F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_07022200, 0x003d0dc0, 89137, 0x00022200, 240);

// 0x070222F0 - 0x070223F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070222F0, 0x003d0dc0, 89137, 0x000222f0, 256);

// 0x070223F0 - 0x070224F0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070223F0, 0x003d0dc0, 89137, 0x000223f0, 256);

// 0x070224F0 - 0x070225B0
ROM_ASSET_LOAD_VTX(hmc_seg7_vertex_070224F0, 0x003d0dc0, 89137, 0x000224f0, 192);

// 0x070225B0 - 0x070228A0
static const Gfx hmc_seg7_dl_070225B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_0900A000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_07021C10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11,  7, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 0, 15,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_07021D10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  6,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0, 13, 15,  0, 0x0),
    gsSPVertex(hmc_seg7_vertex_07021E10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  5, 11, 12, 0x0),
    gsSP2Triangles( 2, 13, 14, 0x0,  2, 15, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07021F10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 10,  4,  6, 0x0),
    gsSP2Triangles(12, 13,  0, 0x0, 12, 14, 13, 0x0),
    gsSPVertex(hmc_seg7_vertex_07022000, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 10, 12, 11, 0x0),
    gsSP2Triangles( 3, 13,  1, 0x0,  3, 14, 13, 0x0),
    gsSP1Triangle( 4,  6, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_07022100, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  2, 13, 14, 0x0),
    gsSP1Triangle( 0, 15,  1, 0x0),
    gsSPVertex(hmc_seg7_vertex_07022200, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(hmc_seg7_vertex_070222F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070223F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(hmc_seg7_vertex_070224F0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  1,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  1,  8,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070228A0 - 0x07022910
const Gfx hmc_seg7_dl_070228A0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_dl_070225B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
