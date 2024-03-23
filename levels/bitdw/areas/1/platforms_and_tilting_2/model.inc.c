#include "pc/rom_assets.h"
// 0x07007B30 - 0x07007C30
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007B30, 0x00454e00, 29021, 0x00007b30, 256);

// 0x07007C30 - 0x07007D30
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007C30, 0x00454e00, 29021, 0x00007c30, 256);

// 0x07007D30 - 0x07007E30
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007D30, 0x00454e00, 29021, 0x00007d30, 256);

// 0x07007E30 - 0x07007F30
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007E30, 0x00454e00, 29021, 0x00007e30, 256);

// 0x07007F30 - 0x07008030
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07007F30, 0x00454e00, 29021, 0x00007f30, 256);

// 0x07008030 - 0x07008120
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008030, 0x00454e00, 29021, 0x00008030, 240);

// 0x07008120 - 0x07008210
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008120, 0x00454e00, 29021, 0x00008120, 240);

// 0x07008210 - 0x07008310
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008210, 0x00454e00, 29021, 0x00008210, 256);

// 0x07008310 - 0x07008380
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008310, 0x00454e00, 29021, 0x00008310, 112);

// 0x07008380 - 0x07008480
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008380, 0x00454e00, 29021, 0x00008380, 256);

// 0x07008480 - 0x07008580
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008480, 0x00454e00, 29021, 0x00008480, 256);

// 0x07008580 - 0x07008680
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008580, 0x00454e00, 29021, 0x00008580, 256);

// 0x07008680 - 0x07008740
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008680, 0x00454e00, 29021, 0x00008680, 192);

// 0x07008740 - 0x07008830
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008740, 0x00454e00, 29021, 0x00008740, 240);

// 0x07008830 - 0x07008930
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008830, 0x00454e00, 29021, 0x00008830, 256);

// 0x07008930 - 0x07008970
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008930, 0x00454e00, 29021, 0x00008930, 64);

// 0x07008970 - 0x07008A70
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008970, 0x00454e00, 29021, 0x00008970, 256);

// 0x07008A70 - 0x07008AF0
ROM_ASSET_LOAD_VTX(bitdw_seg7_vertex_07008A70, 0x00454e00, 29021, 0x00008a70, 128);

// 0x07008AF0 - 0x07008D58
static const Gfx bitdw_seg7_dl_07008AF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bitdw_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07007B30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007C30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007D30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007E30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07007F30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 11, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008030, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008120, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 10, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008210, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008310, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008D58 - 0x07008E88
static const Gfx bitdw_seg7_dl_07008D58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07008380, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008480, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008580, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008680, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008E88 - 0x07008F60
static const Gfx bitdw_seg7_dl_07008E88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07008740, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle(11, 14,  9, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008830, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  0, 11,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008930, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008F60 - 0x07008FF0
static const Gfx bitdw_seg7_dl_07008F60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07008970, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bitdw_seg7_vertex_07008A70, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008FF0 - 0x07009078
const Gfx bitdw_seg7_dl_07008FF0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitdw_seg7_dl_07008AF0),
    gsSPDisplayList(bitdw_seg7_dl_07008D58),
    gsSPDisplayList(bitdw_seg7_dl_07008E88),
    gsSPDisplayList(bitdw_seg7_dl_07008F60),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
