#include "pc/rom_assets.h"
// 0x070021D8 - 0x070022C8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070021D8, 0x00437870, 75979, 0x000021d8, 240);

// 0x070022C8 - 0x070023B8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070022C8, 0x00437870, 75979, 0x000022c8, 240);

// 0x070023B8 - 0x070024B8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070023B8, 0x00437870, 75979, 0x000023b8, 256);

// 0x070024B8 - 0x07002598
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070024B8, 0x00437870, 75979, 0x000024b8, 224);

// 0x07002598 - 0x07002688
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07002598, 0x00437870, 75979, 0x00002598, 240);

// 0x07002688 - 0x070026F8
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_07002688, 0x00437870, 75979, 0x00002688, 112);

// 0x070026F8 - 0x070027F8
#ifdef VERSION_JP
static const Vtx rr_seg7_vertex_070026F8[] = {
    {{{  1636,    512,   -792}, 0, {  2694,   3714}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   817,    717,   -792}, 0, {   650,    308}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   817,    512,   -792}, 0, {     0,    990}, {0x96, 0x96, 0x96, 0xff}}},
    {{{ -1595,    512,   1072}, 0, {  3290,  -8974}, {0x96, 0x96, 0x96, 0xff}}},
    {{{ -1595,    717,   1072}, 0, {  3800,  -9486}, {0x96, 0x96, 0x96, 0xff}}},
    {{{  -980,    717,   1072}, 0, {  5334,  -7952}, {0x96, 0x96, 0x96, 0xff}}},
    {{{  -980,    512,   1072}, 0, {  4822,  -7442}, {0x96, 0x96, 0x96, 0xff}}},
    {{{  -980,    717,   2301}, 0, {  5334,  -7952}, {0x96, 0x96, 0x96, 0xff}}},
    {{{ -1595,    512,   2301}, 0, {  3290,  -8974}, {0x96, 0x96, 0x96, 0xff}}},
    {{{  -980,    512,   2301}, 0, {  4822,  -7442}, {0x96, 0x96, 0x96, 0xff}}},
    {{{ -1595,    717,   2301}, 0, {  3800,  -9486}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   817,    512,  -1406}, 0, {     0,    990}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   817,    717,  -1406}, 0, {   650,    308}, {0x96, 0x96, 0x96, 0xff}}},
    {{{  1636,    717,  -1406}, 0, {  3374,   3032}, {0x96, 0x96, 0x96, 0xff}}},
    {{{  1636,    512,  -1406}, 0, {  2694,   3714}, {0x96, 0x96, 0x96, 0xff}}},
    {{{  1636,    717,   -792}, 0, {  3374,   3032}, {0x96, 0x96, 0x96, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070026F8, 0x00437870, 75979, 0x000026f8, 256);
#endif

// 0x070027F8 - 0x070028E8
#ifdef VERSION_JP
static const Vtx rr_seg7_vertex_070027F8[] = {
    {{{ -1595,    717,   2301}, 0, {     0,    990}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{  -980,    717,   1072}, 0, {  4566,   2522}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{ -1595,    717,   1072}, 0, {  3034,   4054}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{  -980,    717,   2301}, 0, {  1502,   -542}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{  1636,    717,  -1406}, 0, {  4702,    344}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{   817,    717,   -792}, 0, {   -64,   1022}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{  1636,    717,   -792}, 0, {  2658,  -1700}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{   817,    717,  -1406}, 0, {  1978,   3066}, {0xc8, 0xc8, 0xc8, 0xff}}},
    {{{  1636,    512,  -1406}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  1636,    717,   -792}, 0, {  2694,   -372}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  1636,    512,   -792}, 0, {  2012,  -1054}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -980,    512,   1072}, 0, {  -540,    478}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -980,    717,   2301}, 0, {  3034,  -2076}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -980,    512,   2301}, 0, {  2524,  -2588}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -980,    717,   1072}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070027F8, 0x00437870, 75979, 0x000027f8, 240);
#endif

// 0x070028E8 - 0x070029D8
#ifdef VERSION_JP
static const Vtx rr_seg7_vertex_070028E8[] = {
    {{{ -1595,    512,   2301}, 0, {  2524,  -2588}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{ -1595,    717,   2301}, 0, {  3034,  -2076}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{ -1595,    717,   1072}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{ -1595,    512,   1072}, 0, {  -540,    478}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   817,    512,   -792}, 0, {  2012,  -1054}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   817,    717,   -792}, 0, {  2694,   -372}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   817,    717,  -1406}, 0, {   650,   1670}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   817,    512,  -1406}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  1636,    512,  -1406}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  1636,    717,  -1406}, 0, {   650,   1670}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  1636,    717,   -792}, 0, {  2694,   -372}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   817,    512,  -1406}, 0, {  1978,   3066}, {0x55, 0x55, 0x55, 0xff}}},
    {{{  1636,    512,   -792}, 0, {  2658,  -1700}, {0x55, 0x55, 0x55, 0xff}}},
    {{{   817,    512,   -792}, 0, {   -64,   1022}, {0x55, 0x55, 0x55, 0xff}}},
    {{{  1636,    512,  -1406}, 0, {  4702,    344}, {0x55, 0x55, 0x55, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070028E8, 0x00437870, 75979, 0x000028e8, 240);
#endif

// 0x070029D8 - 0x07002A18
#ifdef VERSION_JP
static const Vtx rr_seg7_vertex_070029D8[] = {
    {{{ -1595,    512,   1072}, 0, {  3034,   4054}, {0x55, 0x55, 0x55, 0xff}}},
    {{{  -980,    512,   1072}, 0, {  4566,   2522}, {0x55, 0x55, 0x55, 0xff}}},
    {{{  -980,    512,   2301}, 0, {  1502,   -542}, {0x55, 0x55, 0x55, 0xff}}},
    {{{ -1595,    512,   2301}, 0, {     0,    990}, {0x55, 0x55, 0x55, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(rr_seg7_vertex_070029D8, 0x00437870, 75979, 0x000029d8, 64);
#endif

// 0x07002A18 - 0x07002BC8
static const Gfx rr_seg7_dl_07002A18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_070021D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_070022C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_070023B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(rr_seg7_vertex_070024B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  7, 0x0,  0,  5,  7, 0x0),
    gsSP2Triangles( 8,  2,  9, 0x0,  2,  1,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(rr_seg7_vertex_07002598, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(rr_seg7_vertex_07002688, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002BC8 - 0x07002CC8
static const Gfx rr_seg7_dl_07002BC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(rr_seg7_vertex_070026F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(rr_seg7_vertex_070027F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_070028E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(rr_seg7_vertex_070029D8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07002CC8 - 0x07002D40
const Gfx rr_seg7_dl_07002CC8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(rr_seg7_dl_07002A18),
    gsSPDisplayList(rr_seg7_dl_07002BC8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
