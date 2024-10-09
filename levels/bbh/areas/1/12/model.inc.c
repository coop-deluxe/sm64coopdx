#include "pc/rom_assets.h"
// 0x0700BC68 - 0x0700BC80
static const Lights1 bbh_seg7_lights_0700BC68 = gdSPDefLights1(
    0x20, 0x20, 0x20,
    0x50, 0x50, 0x50, 0x28, 0x28, 0x28
);

// 0x0700BC80 - 0x0700BC98
static const Lights1 bbh_seg7_lights_0700BC80 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700BC98 - 0x0700BD18
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700BC98, 0x00371c40, 68724, 0x0000bc98, 128);

// 0x0700BD18 - 0x0700BE18
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700BD18, 0x00371c40, 68724, 0x0000bd18, 256);

// 0x0700BE18 - 0x0700BEF8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700BE18, 0x00371c40, 68724, 0x0000be18, 224);

// 0x0700BEF8 - 0x0700BFD8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700BEF8, 0x00371c40, 68724, 0x0000bef8, 224);

// 0x0700BFD8 - 0x0700C088
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700BFD8, 0x00371c40, 68724, 0x0000bfd8, 176);

// 0x0700C088 - 0x0700C188
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C088, 0x00371c40, 68724, 0x0000c088, 256);

// 0x0700C188 - 0x0700C268
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C188, 0x00371c40, 68724, 0x0000c188, 224);

// 0x0700C268 - 0x0700C358
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C268, 0x00371c40, 68724, 0x0000c268, 240);

// 0x0700C358 - 0x0700C458
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C358, 0x00371c40, 68724, 0x0000c358, 256);

// 0x0700C458 - 0x0700C548
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C458, 0x00371c40, 68724, 0x0000c458, 240);

// 0x0700C548 - 0x0700C648
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C548, 0x00371c40, 68724, 0x0000c548, 256);

// 0x0700C648 - 0x0700C748
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C648, 0x00371c40, 68724, 0x0000c648, 256);

// 0x0700C748 - 0x0700C838
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C748, 0x00371c40, 68724, 0x0000c748, 240);

// 0x0700C838 - 0x0700C878
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C838, 0x00371c40, 68724, 0x0000c838, 64);

// 0x0700C878 - 0x0700C978
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C878, 0x00371c40, 68724, 0x0000c878, 256);

// 0x0700C978 - 0x0700C9B8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C978, 0x00371c40, 68724, 0x0000c978, 64);

// 0x0700C9B8 - 0x0700CAA8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700C9B8, 0x00371c40, 68724, 0x0000c9b8, 240);

// 0x0700CAA8 - 0x0700CB58
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700CAA8, 0x00371c40, 68724, 0x0000caa8, 176);

// 0x0700CB58 - 0x0700CCB0
static const Gfx bbh_seg7_dl_0700CB58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0700BC68.l, 1),
    gsSPLight(&bbh_seg7_lights_0700BC68.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700BC98, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&bbh_seg7_lights_0700BC80.l, 1),
    gsSPLight(&bbh_seg7_lights_0700BC80.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700BD18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  6, 10,  7, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(11, 13, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700BE18, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700BEF8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700BFD8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CCB0 - 0x0700CD18
static const Gfx bbh_seg7_dl_0700CCB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700C088, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CD18 - 0x0700CF40
static const Gfx bbh_seg7_dl_0700CD18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700C188, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700C268, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700C358, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700C458, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 12,  8, 10, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700C548, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0,  6,  8, 14, 0x0),
    gsSP1Triangle(15,  6, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700C648, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(15, 11, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700C748, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700C838, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CF40 - 0x0700CFA8
static const Gfx bbh_seg7_dl_0700CF40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700C878, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CFA8 - 0x0700CFE0
static const Gfx bbh_seg7_dl_0700CFA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700C978, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700CFE0 - 0x0700D080
static const Gfx bbh_seg7_dl_0700CFE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09009000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700C9B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 14, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700CAA8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7, 10,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D080 - 0x0700D178
const Gfx bbh_seg7_dl_0700D080[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700CB58),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700CCB0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700CD18),
    gsSPDisplayList(bbh_seg7_dl_0700CF40),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700CFA8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700CFE0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
