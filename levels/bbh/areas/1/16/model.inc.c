#include "pc/rom_assets.h"
// 0x0700D850 - 0x0700D868
static const Lights1 bbh_seg7_lights_0700D850 = gdSPDefLights1(
    0x20, 0x20, 0x20,
    0x50, 0x50, 0x50, 0x28, 0x28, 0x28
);

// 0x0700D868 - 0x0700D880
static const Lights1 bbh_seg7_lights_0700D868 = gdSPDefLights1(
    0x3c, 0x3c, 0x3c,
    0x96, 0x96, 0x96, 0x28, 0x28, 0x28
);

// 0x0700D880 - 0x0700D898
static const Lights1 bbh_seg7_lights_0700D880 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700D898 - 0x0700D918
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700D898, 0x00371c40, 68724, 0x0000d898, 128);

// 0x0700D918 - 0x0700D9B8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700D918, 0x00371c40, 68724, 0x0000d918, 160);

// 0x0700D9B8 - 0x0700DA98
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700D9B8, 0x00371c40, 68724, 0x0000d9b8, 224);

// 0x0700DA98 - 0x0700DB98
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700DA98, 0x00371c40, 68724, 0x0000da98, 256);

// 0x0700DB98 - 0x0700DC88
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700DB98, 0x00371c40, 68724, 0x0000db98, 240);

// 0x0700DC88 - 0x0700DD78
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700DC88, 0x00371c40, 68724, 0x0000dc88, 240);

// 0x0700DD78 - 0x0700DE68
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700DD78, 0x00371c40, 68724, 0x0000dd78, 240);

// 0x0700DE68 - 0x0700DF58
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700DE68, 0x00371c40, 68724, 0x0000de68, 240);

// 0x0700DF58 - 0x0700E058
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700DF58, 0x00371c40, 68724, 0x0000df58, 256);

// 0x0700E058 - 0x0700E158
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E058, 0x00371c40, 68724, 0x0000e058, 256);

// 0x0700E158 - 0x0700E258
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E158, 0x00371c40, 68724, 0x0000e158, 256);

// 0x0700E258 - 0x0700E338
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E258, 0x00371c40, 68724, 0x0000e258, 224);

// 0x0700E338 - 0x0700E418
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E338, 0x00371c40, 68724, 0x0000e338, 224);

// 0x0700E418 - 0x0700E508
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E418, 0x00371c40, 68724, 0x0000e418, 240);

// 0x0700E508 - 0x0700E5F8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E508, 0x00371c40, 68724, 0x0000e508, 240);

// 0x0700E5F8 - 0x0700E6B8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E5F8, 0x00371c40, 68724, 0x0000e5f8, 192);

// 0x0700E6B8 - 0x0700E7A8
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E6B8, 0x00371c40, 68724, 0x0000e6b8, 240);

// 0x0700E7A8 - 0x0700E898
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E7A8, 0x00371c40, 68724, 0x0000e7a8, 240);

// 0x0700E898 - 0x0700E988
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E898, 0x00371c40, 68724, 0x0000e898, 240);

// 0x0700E988 - 0x0700EA78
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700E988, 0x00371c40, 68724, 0x0000e988, 240);

// 0x0700EA78 - 0x0700EB68
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700EA78, 0x00371c40, 68724, 0x0000ea78, 240);

// 0x0700EB68 - 0x0700EC48
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700EB68, 0x00371c40, 68724, 0x0000eb68, 224);

// 0x0700EC48 - 0x0700ED28
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700EC48, 0x00371c40, 68724, 0x0000ec48, 224);

// 0x0700ED28 - 0x0700EE28
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700ED28, 0x00371c40, 68724, 0x0000ed28, 256);

// 0x0700EE28 - 0x0700EE98
ROM_ASSET_LOAD_VTX(bbh_seg7_vertex_0700EE28, 0x00371c40, 68724, 0x0000ee28, 112);

// 0x0700EE98 - 0x0700EFD8
static const Gfx bbh_seg7_dl_0700EE98[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_0700D850.l, 1),
    gsSPLight(&bbh_seg7_lights_0700D850.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700D898, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&bbh_seg7_lights_0700D868.l, 1),
    gsSPLight(&bbh_seg7_lights_0700D868.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700D918, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPLight(&bbh_seg7_lights_0700D880.l, 1),
    gsSPLight(&bbh_seg7_lights_0700D880.a, 2),
    gsSPVertex(bbh_seg7_vertex_0700D9B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700DA98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EFD8 - 0x0700F2B8
static const Gfx bbh_seg7_dl_0700EFD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700DB98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700DC88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700DD78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700DE68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700DF58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 12,  9, 11, 0x0),
    gsSP2Triangles( 9, 14, 10, 0x0, 15, 10, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E058, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E158, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13,  9, 12, 0x0),
    gsSP2Triangles(14, 11, 10, 0x0, 14, 15, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E258, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E338, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E418, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  6,  8, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E508, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E5F8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F2B8 - 0x0700F3D8
static const Gfx bbh_seg7_dl_0700F2B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700E6B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E7A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E898, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 7, 14,  8, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700E988, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 4,  6, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F3D8 - 0x0700F510
static const Gfx bbh_seg7_dl_0700F3D8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700EA78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 3, 14,  4, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700EB68, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700EC48, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700ED28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700EE28, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F510 - 0x0700F5C8
const Gfx bbh_seg7_dl_0700F510[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700EE98),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700EFD8),
    gsSPDisplayList(bbh_seg7_dl_0700F2B8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700F3D8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
