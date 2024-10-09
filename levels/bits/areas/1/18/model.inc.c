#include "pc/rom_assets.h"
// 0x0700DD98 - 0x0700DE98
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700DD98, 0x0046c3a0, 47442, 0x0000dd98, 256);

// 0x0700DE98 - 0x0700DF98
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700DE98, 0x0046c3a0, 47442, 0x0000de98, 256);

// 0x0700DF98 - 0x0700E078
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700DF98, 0x0046c3a0, 47442, 0x0000df98, 224);

// 0x0700E078 - 0x0700E178
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E078, 0x0046c3a0, 47442, 0x0000e078, 256);

// 0x0700E178 - 0x0700E268
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E178, 0x0046c3a0, 47442, 0x0000e178, 240);

// 0x0700E268 - 0x0700E358
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E268, 0x0046c3a0, 47442, 0x0000e268, 240);

// 0x0700E358 - 0x0700E458
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E358, 0x0046c3a0, 47442, 0x0000e358, 256);

// 0x0700E458 - 0x0700E548
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E458, 0x0046c3a0, 47442, 0x0000e458, 240);

// 0x0700E548 - 0x0700E628
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E548, 0x0046c3a0, 47442, 0x0000e548, 224);

// 0x0700E628 - 0x0700E718
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E628, 0x0046c3a0, 47442, 0x0000e628, 240);

// 0x0700E718 - 0x0700E808
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E718, 0x0046c3a0, 47442, 0x0000e718, 240);

// 0x0700E808 - 0x0700E908
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E808, 0x0046c3a0, 47442, 0x0000e808, 256);

// 0x0700E908 - 0x0700EA08
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700E908, 0x0046c3a0, 47442, 0x0000e908, 256);

// 0x0700EA08 - 0x0700EB08
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700EA08, 0x0046c3a0, 47442, 0x0000ea08, 256);

// 0x0700EB08 - 0x0700EBF8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700EB08, 0x0046c3a0, 47442, 0x0000eb08, 240);

// 0x0700EBF8 - 0x0700ECD8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700EBF8, 0x0046c3a0, 47442, 0x0000ebf8, 224);

// 0x0700ECD8 - 0x0700EDC8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700ECD8, 0x0046c3a0, 47442, 0x0000ecd8, 240);

// 0x0700EDC8 - 0x0700EEC8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700EDC8, 0x0046c3a0, 47442, 0x0000edc8, 256);

// 0x0700EEC8 - 0x0700EFC8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700EEC8, 0x0046c3a0, 47442, 0x0000eec8, 256);

// 0x0700EFC8 - 0x0700F0B8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700EFC8, 0x0046c3a0, 47442, 0x0000efc8, 240);

// 0x0700F0B8 - 0x0700F198
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700F0B8, 0x0046c3a0, 47442, 0x0000f0b8, 224);

// 0x0700F198 - 0x0700F298
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700F198, 0x0046c3a0, 47442, 0x0000f198, 256);

// 0x0700F298 - 0x0700F398
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700F298, 0x0046c3a0, 47442, 0x0000f298, 256);

// 0x0700F398 - 0x0700F478
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700F398, 0x0046c3a0, 47442, 0x0000f398, 224);

// 0x0700F478 - 0x0700F568
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700F478, 0x0046c3a0, 47442, 0x0000f478, 240);

// 0x0700F568 - 0x0700F790
static const Gfx bits_seg7_dl_0700F568[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700DD98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 10,  7, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700DE98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  5, 10,  6, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700DF98, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  9,  8, 12, 0x0),
    gsSP1Triangle( 9, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E078, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(14, 13, 10, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E178, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E268, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E358, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F790 - 0x0700FC70
static const Gfx bits_seg7_dl_0700F790[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700E458, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E548, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E628, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E718, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E808, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15,  9, 11, 0x0),
    gsSPVertex(bits_seg7_vertex_0700E908, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 14, 10, 0x0, 13, 10, 15, 0x0),
    gsSP1Triangle(15, 10, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_0700EA08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11,  7, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11, 12,  7, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700EB08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700EBF8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700ECD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700EDC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11,  0, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700EEC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700EFC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700F0B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700F198, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 12, 11, 0x0),
    gsSPVertex(bits_seg7_vertex_0700F298, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_0700F398, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0,  7, 13,  8, 0x0),
    gsSPVertex(bits_seg7_vertex_0700F478, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FC70 - 0x0700FCE8
const Gfx bits_seg7_dl_0700FC70[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_0700F568),
    gsSPDisplayList(bits_seg7_dl_0700F790),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
