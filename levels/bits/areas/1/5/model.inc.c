#include "pc/rom_assets.h"
// 0x07005E58 - 0x07005F58
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07005E58, 0x0046c3a0, 47442, 0x00005e58, 256);

// 0x07005F58 - 0x07006058
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07005F58, 0x0046c3a0, 47442, 0x00005f58, 256);

// 0x07006058 - 0x07006158
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006058, 0x0046c3a0, 47442, 0x00006058, 256);

// 0x07006158 - 0x07006248
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006158, 0x0046c3a0, 47442, 0x00006158, 240);

// 0x07006248 - 0x07006328
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006248, 0x0046c3a0, 47442, 0x00006248, 224);

// 0x07006328 - 0x07006418
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006328, 0x0046c3a0, 47442, 0x00006328, 240);

// 0x07006418 - 0x070064F8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006418, 0x0046c3a0, 47442, 0x00006418, 224);

// 0x070064F8 - 0x070065D8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070064F8, 0x0046c3a0, 47442, 0x000064f8, 224);

// 0x070065D8 - 0x070066D8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070065D8, 0x0046c3a0, 47442, 0x000065d8, 256);

// 0x070066D8 - 0x070067C8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070066D8, 0x0046c3a0, 47442, 0x000066d8, 240);

// 0x070067C8 - 0x070068B8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070067C8, 0x0046c3a0, 47442, 0x000067c8, 240);

// 0x070068B8 - 0x070069A8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070068B8, 0x0046c3a0, 47442, 0x000068b8, 240);

// 0x070069A8 - 0x07006A98
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070069A8, 0x0046c3a0, 47442, 0x000069a8, 240);

// 0x07006A98 - 0x07006B78
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006A98, 0x0046c3a0, 47442, 0x00006a98, 224);

// 0x07006B78 - 0x07006C68
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006B78, 0x0046c3a0, 47442, 0x00006b78, 240);

// 0x07006C68 - 0x07006D68
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006C68, 0x0046c3a0, 47442, 0x00006c68, 256);

// 0x07006D68 - 0x07006E58
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006D68, 0x0046c3a0, 47442, 0x00006d68, 240);

// 0x07006E58 - 0x07006F58
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006E58, 0x0046c3a0, 47442, 0x00006e58, 256);

// 0x07006F58 - 0x07007058
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07006F58, 0x0046c3a0, 47442, 0x00006f58, 256);

// 0x07007058 - 0x07007138
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07007058, 0x0046c3a0, 47442, 0x00007058, 224);

// 0x07007138 - 0x07007218
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07007138, 0x0046c3a0, 47442, 0x00007138, 224);

// 0x07007218 - 0x07007308
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07007218, 0x0046c3a0, 47442, 0x00007218, 240);

// 0x07007308 - 0x070073F8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07007308, 0x0046c3a0, 47442, 0x00007308, 240);

// 0x070073F8 - 0x07007448
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070073F8, 0x0046c3a0, 47442, 0x000073f8, 80);

// 0x07007448 - 0x07007AF0
static const Gfx bits_seg7_dl_07007448[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07005E58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 6,  8,  3, 0x0,  7,  9,  6, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07005F58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12,  7, 0x0),
    gsSP2Triangles(11,  7,  9, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07006058, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4,  9,  2, 0x0),
    gsSP2Triangles(10, 11,  5, 0x0,  5,  7, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07006158, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 10, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07006248, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  8,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bits_seg7_vertex_07006328, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07006418, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070064F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  4,  2,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070065D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 11, 15, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070066D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070067C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  9, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070068B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13,  9, 11, 0x0),
    gsSP1Triangle(13, 11, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070069A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0, 10,  9, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07006A98, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(bits_seg7_vertex_07006B78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_07006C68, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles( 7,  9, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07006D68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_07006E58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 7,  9, 12, 0x0,  4, 13, 14, 0x0),
    gsSP1Triangle( 4, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07006F58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11,  5, 14, 0x0, 11, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07007058, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07007138, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07007218, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 14, 11, 0x0),
    gsSPVertex(bits_seg7_vertex_07007308, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070073F8, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 3,  0,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007AF0 - 0x07007B60
const Gfx bits_seg7_dl_07007AF0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_07007448),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
