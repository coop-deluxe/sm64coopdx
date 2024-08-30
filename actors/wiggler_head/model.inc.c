#include "pc/rom_assets.h"
// Wiggler Head

// 0x0500C878
static const Lights1 wiggler_seg5_lights_0500C878 = gdSPDefLights1(
    0x37, 0x00, 0x00,
    0xdf, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0500C890
static const Lights1 wiggler_seg5_lights_0500C890 = gdSPDefLights1(
    0x39, 0x11, 0x00,
    0xe7, 0x47, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 wiggler_head_lights_unused1 = gdSPDefLights1(
    0x1b, 0x06, 0x00,
    0x6d, 0x1a, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 wiggler_head_lights_unused2 = gdSPDefLights1(
    0x3a, 0x22, 0x05,
    0xea, 0x8b, 0x16, 0x28, 0x28, 0x28
);

// 0x0500C8D8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500C8D8, 0x00180bb0, 29674, 0x0000b278, 256);

// 0x0500C9D8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500C9D8, 0x00180bb0, 29674, 0x0000b378, 256);

// 0x0500CAD8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500CAD8, 0x00180bb0, 29674, 0x0000b478, 256);

// 0x0500CBD8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500CBD8, 0x00180bb0, 29674, 0x0000b578, 64);

// 0x0500CC18
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500CC18, 0x00180bb0, 29674, 0x0000cc18, 240);

// 0x0500CD08
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500CD08, 0x00180bb0, 29674, 0x0000cd08, 240);

// 0x0500CDF8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500CDF8, 0x00180bb0, 29674, 0x0000b798, 256);

// 0x0500CEF8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500CEF8, 0x00180bb0, 29674, 0x0000b898, 256);

// 0x0500CFF8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500CFF8, 0x00180bb0, 29674, 0x0000cff8, 256);

// 0x0500D0F8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500D0F8, 0x00180bb0, 29674, 0x0000d0f8, 64);

// 0x0500D138
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500D138, 0x00180bb0, 29674, 0x0000d138, 240);

// 0x0500D228
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500D228, 0x00180bb0, 29674, 0x0000d228, 240);

// Unused vertices? what are these? [D318]
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500D318, 0x00180bb0, 29674, 0x0000d318, 2304);

// 0x0500DC18 - 0x0500DD70
const Gfx wiggler_seg5_dl_0500DC18[] = {
    gsSPLight(&wiggler_seg5_lights_0500C878.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500C878.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500C8D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500C9D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  6,  2,  5, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12,  8, 0x0),
    gsSP2Triangles( 9, 13,  7, 0x0, 10,  8,  6, 0x0),
    gsSP2Triangles(14, 13,  9, 0x0, 14,  9, 15, 0x0),
    gsSP2Triangles( 2,  7, 13, 0x0,  2, 13,  0, 0x0),
    gsSP2Triangles( 6,  4, 10, 0x0,  6,  5,  4, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500CAD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500CBD8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500DD70 - 0x0500DDF8
const Gfx wiggler_seg5_dl_0500DD70[] = {
    gsSPLight(&wiggler_seg5_lights_0500C890.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500C890.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500CC18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500DDF8 - 0x0500DE80
const Gfx wiggler_seg5_dl_0500DDF8[] = {
    gsSPLight(&wiggler_seg5_lights_0500C890.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500C890.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500CD08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500DE80 - 0x0500DFD8
const Gfx wiggler_seg5_dl_0500DE80[] = {
    gsSPLight(&wiggler_seg5_lights_0500C878.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500C878.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500CDF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500CEF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  0,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 6, 13,  8, 0x0,  7,  9, 12, 0x0),
    gsSP2Triangles(14,  8, 13, 0x0, 14, 13, 15, 0x0),
    gsSP2Triangles( 2, 13,  6, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles(12,  3,  7, 0x0, 12,  4,  3, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500CFF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 15, 0x0),
    gsSPVertex(wiggler_seg5_vertex_0500D0F8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500DFD8 - 0x0500E060
const Gfx wiggler_seg5_dl_0500DFD8[] = {
    gsSPLight(&wiggler_seg5_lights_0500C890.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500C890.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500D138, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E060 - 0x0500E0E8
const Gfx wiggler_seg5_dl_0500E060[] = {
    gsSPLight(&wiggler_seg5_lights_0500C890.l, 1),
    gsSPLight(&wiggler_seg5_lights_0500C890.a, 2),
    gsSPVertex(wiggler_seg5_vertex_0500D228, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles( 1,  4,  7, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(10, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E0E8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500E0E8, 0x00180bb0, 29674, 0x0000e0e8, 64);

// 0x0500E128
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500E128, 0x00180bb0, 29674, 0x0000e128, 64);

// 0x0500E168 - 0x0500E1A0
const Gfx wiggler_seg5_dl_0500E168[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05009230),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500E0E8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E1A0 - 0x0500E1D8
const Gfx wiggler_seg5_dl_0500E1A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_0500A230),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500E128, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E1D8 - 0x0500E250
const Gfx wiggler_seg5_dl_0500E1D8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wiggler_seg5_dl_0500E168),
    gsSPDisplayList(wiggler_seg5_dl_0500E1A0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500E250
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500E250, 0x00180bb0, 29674, 0x0000e250, 96);

// 0x0500E2B0 - 0x0500E2F8
const Gfx wiggler_seg5_dl_0500E2B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05008A30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500E250, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  0,  5,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E2F8 - 0x0500E368
const Gfx wiggler_seg5_dl_0500E2F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wiggler_seg5_dl_0500E2B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500E368
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500E368, 0x00180bb0, 29674, 0x0000e368, 128);

// 0x0500E3E8 - 0x0500E430
const Gfx wiggler_seg5_dl_0500E3E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05007A30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500E368, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E430 - 0x0500E4A0
const Gfx wiggler_seg5_dl_0500E430[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wiggler_seg5_dl_0500E3E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500E4A0
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500E4A0, 0x00180bb0, 29674, 0x0000e4a0, 64);

// 0x0500E4E0 - 0x0500E518
const Gfx wiggler_seg5_dl_0500E4E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05008230),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500E4A0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E518 - 0x0500E588
const Gfx wiggler_seg5_dl_0500E518[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wiggler_seg5_dl_0500E4E0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0500E588
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500E588, 0x00180bb0, 29674, 0x0000e588, 64);

// 0x0500E5C8
ROM_ASSET_LOAD_VTX(wiggler_seg5_vertex_0500E5C8, 0x00180bb0, 29674, 0x0000e5c8, 64);

// 0x0500E608 - 0x0500E640
const Gfx wiggler_seg5_dl_0500E608[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05005A30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500E588, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E640 - 0x0500E678
const Gfx wiggler_seg5_dl_0500E640[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wiggler_seg5_texture_05006A30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wiggler_seg5_vertex_0500E5C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E678 - 0x0500E6F0
const Gfx wiggler_seg5_dl_0500E678[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wiggler_seg5_dl_0500E608),
    gsSPDisplayList(wiggler_seg5_dl_0500E640),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
