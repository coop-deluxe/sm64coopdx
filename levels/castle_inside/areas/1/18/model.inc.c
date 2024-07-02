#include "pc/rom_assets.h"
// 0x070352F8 - 0x07035310
static const Lights1 inside_castle_seg7_lights_070352F8 = gdSPDefLights1(
    0x19, 0x19, 0x19,
    0x44, 0x44, 0x44, 0x28, 0x28, 0x28
);

// 0x07035310 - 0x07035328
static const Lights1 inside_castle_seg7_lights_07035310 = gdSPDefLights1(
    0x26, 0x26, 0x26,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07035328 - 0x07035340
static const Lights1 inside_castle_seg7_lights_07035328 = gdSPDefLights1(
    0x1f, 0x1f, 0x1f,
    0x55, 0x55, 0x55, 0x28, 0x28, 0x28
);

// 0x07035340 - 0x07035358
static const Lights1 inside_castle_seg7_lights_07035340 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07035358 - 0x07035458
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035358, 0x00396340, 232834, 0x00035358, 256);

// 0x07035458 - 0x07035548
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035458, 0x00396340, 232834, 0x00035458, 240);

// 0x07035548 - 0x070355B8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035548, 0x00396340, 232834, 0x00035548, 112);

// 0x070355B8 - 0x070355F8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070355B8, 0x00396340, 232834, 0x000355b8, 64);

// 0x070355F8 - 0x070356B8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070355F8, 0x00396340, 232834, 0x000355f8, 192);

// 0x070356B8 - 0x070357B8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070356B8, 0x00396340, 232834, 0x000356b8, 256);

// 0x070357B8 - 0x070358A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070357B8, 0x00396340, 232834, 0x000357b8, 240);

// 0x070358A8 - 0x07035998
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070358A8, 0x00396340, 232834, 0x000358a8, 240);

// 0x07035998 - 0x07035A98
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035998, 0x00396340, 232834, 0x00035998, 256);

// 0x07035A98 - 0x07035AF8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035A98, 0x00396340, 232834, 0x00035a98, 96);

// 0x07035AF8 - 0x07035B98
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035AF8, 0x00396340, 232834, 0x00035af8, 160);

// 0x07035B98 - 0x07035C98
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035B98, 0x00396340, 232834, 0x00035b98, 256);

// 0x07035C98 - 0x07035D98
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035C98, 0x00396340, 232834, 0x00035c98, 256);

// 0x07035D98 - 0x07035E88
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035D98, 0x00396340, 232834, 0x00035d98, 240);

// 0x07035E88 - 0x07035F78
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035E88, 0x00396340, 232834, 0x00035e88, 240);

// 0x07035F78 - 0x07036078
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07035F78, 0x00396340, 232834, 0x00035f78, 256);

// 0x07036078 - 0x07036168
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07036078, 0x00396340, 232834, 0x00036078, 240);

// 0x07036168 - 0x07036268
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07036168, 0x00396340, 232834, 0x00036168, 256);

// 0x07036268 - 0x07036368
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07036268, 0x00396340, 232834, 0x00036268, 256);

// 0x07036368 - 0x070363D8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_07036368, 0x00396340, 232834, 0x00036368, 112);

// 0x070363D8 - 0x070364B8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070363D8, 0x00396340, 232834, 0x000363d8, 224);

// 0x070364B8 - 0x070365A8
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070364B8, 0x00396340, 232834, 0x000364b8, 240);

// 0x070365A8 - 0x07036698
ROM_ASSET_LOAD_VTX(inside_castle_seg7_vertex_070365A8, 0x00396340, 232834, 0x000365a8, 240);

// 0x07036698 - 0x07036780
static const Gfx inside_castle_seg7_dl_07036698[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_070352F8.l, 1),
    gsSPLight(&inside_castle_seg7_lights_070352F8.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07035358, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPLight(&inside_castle_seg7_lights_07035310.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07035310.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07035458, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07035548, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07036780 - 0x070367C8
static const Gfx inside_castle_seg7_dl_07036780[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07035328.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07035328.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070355B8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070367C8 - 0x07036850
static const Gfx inside_castle_seg7_dl_070367C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07035310.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07035310.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070355F8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 5,  2,  6, 0x0,  4,  7,  3, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  8,  5,  6, 0x0),
    gsSP2Triangles(10,  8,  6, 0x0, 11, 10,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07036850 - 0x070369B8
static const Gfx inside_castle_seg7_dl_07036850[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_070356B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 3,  4,  6, 0x0,  7,  5,  3, 0x0),
    gsSP2Triangles( 7,  3,  6, 0x0,  2,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070357B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070358A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07035998, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07035A98, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070369B8 - 0x07036CB8
static const Gfx inside_castle_seg7_dl_070369B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_07035328.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07035328.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07035AF8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  7,  9, 0x0),
    gsSPLight(&inside_castle_seg7_lights_07035310.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07035310.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_07035B98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07035C98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles( 8, 10, 12, 0x0,  8, 13, 11, 0x0),
    gsSP2Triangles(13, 14, 11, 0x0, 14, 15, 11, 0x0),
    gsSP2Triangles(14, 12, 15, 0x0, 12, 10, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07035D98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 8,  7,  2, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07035E88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  1,  0,  7, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0,  8,  1,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles( 9,  3,  2, 0x0,  9, 14,  8, 0x0),
    gsSP1Triangle( 9,  2, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07035F78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(11, 14, 15, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07036078, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 13, 14, 11, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07036168, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  7,  9, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07036268, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_07036368, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07036CB8 - 0x07036D88
static const Gfx inside_castle_seg7_dl_07036CB8[] = {
    gsSPLight(&inside_castle_seg7_lights_07035340.l, 1),
    gsSPLight(&inside_castle_seg7_lights_07035340.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_070363D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070364B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(inside_castle_seg7_vertex_070365A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07036D88 - 0x07036E68
const Gfx inside_castle_seg7_dl_07036D88[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07036698),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_07036780),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_070367C8),
    gsSPDisplayList(inside_castle_seg7_dl_07036850),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_070369B8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(inside_castle_seg7_dl_07036CB8),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
