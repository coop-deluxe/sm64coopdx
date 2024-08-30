#include "pc/rom_assets.h"
// Haunted Cage

// 0x0500C258
static const Lights1 haunted_cage_seg5_lights_0500C258 = gdSPDefLights1(
    0x39, 0x0c, 0x0e,
    0x90, 0x1e, 0x25, 0x28, 0x28, 0x28
);

// 0x0500C270
static const Lights1 haunted_cage_seg5_lights_0500C270 = gdSPDefLights1(
    0x47, 0x47, 0x47,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x0500C288
ROM_ASSET_LOAD_TEXTURE(haunted_cage_seg5_texture_0500C288, "actors/haunted_cage/bbh_cage_floor.rgba16.inc.c", 0x00166c60, 26968, 0x0000c288, 2048);

// 0x0500CA88
ROM_ASSET_LOAD_TEXTURE(haunted_cage_seg5_texture_0500CA88, "actors/haunted_cage/bbh_cage_double_ornament.rgba16.inc.c", 0x00166c60, 26968, 0x0000ca88, 2048);

// 0x0500D288
ROM_ASSET_LOAD_TEXTURE(haunted_cage_seg5_texture_0500D288, "actors/haunted_cage/bbh_cage_ornament.rgba16.inc.c", 0x00166c60, 26968, 0x0000d288, 1024);

// 0x0500D688
ROM_ASSET_LOAD_TEXTURE(haunted_cage_seg5_texture_0500D688, "actors/haunted_cage/bbh_cage_wooden_base.rgba16.inc.c", 0x00166c60, 26968, 0x0000d688, 1024);

// 0x0500DA88
ROM_ASSET_LOAD_TEXTURE(haunted_cage_seg5_texture_0500DA88, "actors/haunted_cage/bbh_cage_bars.rgba16.inc.c", 0x00166c60, 26968, 0x0000da88, 2048);

// possibly garbage. does not at all appear to be a texture and is unreferenced
// also could be some sort of shader mask from much earlier in development, considering
// Big Boo's Haunt was a very very early level.
// 0x0500E288
ROM_ASSET_LOAD_TEXTURE(haunted_cage_seg5_texture_0500E288, "actors/haunted_cage/bbh_cage_garbage.rgba16.inc.c", 0x00166c60, 26968, 0x0000e288, 2048);

// 0x0500EA88
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500EA88, 0x00166c60, 26968, 0x0000ea88, 240);

// 0x0500EB78
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500EB78, 0x00166c60, 26968, 0x0000eb78, 240);

// 0x0500EC68
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500EC68, 0x00166c60, 26968, 0x0000ec68, 96);

// 0x0500ECC8
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500ECC8, 0x00166c60, 26968, 0x0000ecc8, 240);

// 0x0500EDB8
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500EDB8, 0x00166c60, 26968, 0x0000edb8, 224);

// 0x0500EE98
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500EE98, 0x00166c60, 26968, 0x0000ee98, 240);

// 0x0500EF88
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500EF88, 0x00166c60, 26968, 0x0000ef88, 128);

// 0x0500F008
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500F008, 0x00166c60, 26968, 0x0000f008, 256);

// 0x0500F108
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500F108, 0x00166c60, 26968, 0x0000f108, 256);

// 0x0500F208
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500F208, 0x00166c60, 26968, 0x0000f208, 256);

// 0x0500F308
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500F308, 0x00166c60, 26968, 0x0000f308, 256);

// 0x0500F408
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500F408, 0x00166c60, 26968, 0x0000f408, 192);

// 0x0500F4C8 - 0x0500F660
const Gfx haunted_cage_seg5_dl_0500F4C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_0500D288),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&haunted_cage_seg5_lights_0500C258.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500C258.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500EA88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EB78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EC68, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&haunted_cage_seg5_lights_0500C270.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500C270.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500ECC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EDB8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EE98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EF88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500F660 - 0x0500F760
const Gfx haunted_cage_seg5_dl_0500F660[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_0500CA88),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(haunted_cage_seg5_vertex_0500F008, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F108, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F208, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  6, 15,  7, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F308, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500F760 - 0x0500F7D8
const Gfx haunted_cage_seg5_dl_0500F760[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_0500C288),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(haunted_cage_seg5_vertex_0500F408, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  8,  6, 0x0),
    gsSP2Triangles( 0,  7,  9, 0x0,  0, 10,  8, 0x0),
    gsSP2Triangles( 0, 11, 10, 0x0,  0,  2, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500F7D8 - 0x0500F888
const Gfx haunted_cage_seg5_dl_0500F7D8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_0500F4C8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_0500F660),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_0500F760),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500F888
static const Lights1 haunted_cage_seg5_lights_0500F888 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500F8A0
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500F8A0, 0x00166c60, 26968, 0x0000f8a0, 240);

// 0x0500F990
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500F990, 0x00166c60, 26968, 0x0000f990, 240);

// 0x0500FA80
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500FA80, 0x00166c60, 26968, 0x0000fa80, 192);

// 0x0500FB40 - 0x0500FC28
const Gfx haunted_cage_seg5_dl_0500FB40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_0500D688),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&haunted_cage_seg5_lights_0500F888.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500F888.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500F8A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F990, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FA80, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500FC28 - 0x0500FC98
const Gfx haunted_cage_seg5_dl_0500FC28[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_0500FB40),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500FC98
static const Lights1 haunted_cage_seg5_lights_0500FC98 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x0500FCB0
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500FCB0, 0x00166c60, 26968, 0x0000fcb0, 240);

// 0x0500FDA0
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500FDA0, 0x00166c60, 26968, 0x0000fda0, 224);

// 0x0500FE80
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500FE80, 0x00166c60, 26968, 0x0000fe80, 256);

// 0x0500FF80
ROM_ASSET_LOAD_VTX(haunted_cage_seg5_vertex_0500FF80, 0x00166c60, 26968, 0x0000ff80, 112);

// 0x0500FFF0 - 0x05010100
const Gfx haunted_cage_seg5_dl_0500FFF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_0500DA88),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&haunted_cage_seg5_lights_0500FC98.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500FC98.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500FCB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FDA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FE80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FF80, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05010100 - 0x05010170
const Gfx haunted_cage_seg5_dl_05010100[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_0500FFF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
