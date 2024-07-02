#include "pc/rom_assets.h"
// 0x07004880 - 0x07004980
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004880, 0x0046c3a0, 47442, 0x00004880, 256);

// 0x07004980 - 0x07004A00
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004980, 0x0046c3a0, 47442, 0x00004980, 128);

// 0x07004A00 - 0x07004B00
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004A00, 0x0046c3a0, 47442, 0x00004a00, 256);

// 0x07004B00 - 0x07004C00
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004B00, 0x0046c3a0, 47442, 0x00004b00, 256);

// 0x07004C00 - 0x07004D00
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004C00, 0x0046c3a0, 47442, 0x00004c00, 256);

// 0x07004D00 - 0x07004DF0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004D00, 0x0046c3a0, 47442, 0x00004d00, 240);

// 0x07004DF0 - 0x07004EE0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004DF0, 0x0046c3a0, 47442, 0x00004df0, 240);

// 0x07004EE0 - 0x07004FD0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004EE0, 0x0046c3a0, 47442, 0x00004ee0, 240);

// 0x07004FD0 - 0x070050D0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07004FD0, 0x0046c3a0, 47442, 0x00004fd0, 256);

// 0x070050D0 - 0x070051D0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070050D0, 0x0046c3a0, 47442, 0x000050d0, 256);

// 0x070051D0 - 0x070052B0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070051D0, 0x0046c3a0, 47442, 0x000051d0, 224);

// 0x070052B0 - 0x070053B0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070052B0, 0x0046c3a0, 47442, 0x000052b0, 256);

// 0x070053B0 - 0x070054A0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070053B0, 0x0046c3a0, 47442, 0x000053b0, 240);

// 0x070054A0 - 0x070054F0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070054A0, 0x0046c3a0, 47442, 0x000054a0, 80);

// 0x070054F0 - 0x070055F0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070054F0, 0x0046c3a0, 47442, 0x000054f0, 256);

// 0x070055F0 - 0x070056E0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070055F0, 0x0046c3a0, 47442, 0x000055f0, 240);

// 0x070056E0 - 0x07005760
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070056E0, 0x0046c3a0, 47442, 0x000056e0, 128);

// 0x07005760 - 0x07005860
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07005760, 0x0046c3a0, 47442, 0x00005760, 256);

// 0x07005860 - 0x070058A0
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07005860, 0x0046c3a0, 47442, 0x00005860, 64);

// 0x070058A0 - 0x07005930
static const Gfx bits_seg7_dl_070058A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07004880, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07004980, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005930 - 0x07005C50
static const Gfx bits_seg7_dl_07005930[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07004A00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 15, 12, 11, 0x0),
    gsSPVertex(bits_seg7_vertex_07004B00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8, 11, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07004C00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07004D00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  4,  0,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07004DF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  0,  2, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07004EE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07004FD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(14, 15, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_070050D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_070051D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  9, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070052B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  6,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_070053B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070054A0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 0,  4,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005C50 - 0x07005D38
static const Gfx bits_seg7_dl_07005C50[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_070054F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles( 5, 12, 13, 0x0,  5, 13, 14, 0x0),
    gsSP2Triangles( 5, 14,  6, 0x0, 11,  8, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_070055F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 12, 14, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070056E0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005D38 - 0x07005DB8
static const Gfx bits_seg7_dl_07005D38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bits_seg7_texture_07002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07005760, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07005860, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005DB8 - 0x07005E58
const Gfx bits_seg7_dl_07005DB8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_070058A0),
    gsSPDisplayList(bits_seg7_dl_07005930),
    gsSPDisplayList(bits_seg7_dl_07005C50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_07005D38),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
