#include "pc/rom_assets.h"
// Treasure Chest

// 0x06013F90
static const Lights1 treasure_chest_seg6_lights_06013F90 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06013FA8
ROM_ASSET_LOAD_TEXTURE(treasure_chest_seg6_texture_06013FA8, "actors/treasure_chest/treasure_chest_lock.rgba16.inc.c", 0x001b9cc0, 41188, 0x00013fa8, 2048);

// 0x060147A8
ROM_ASSET_LOAD_TEXTURE(treasure_chest_seg6_texture_060147A8, "actors/treasure_chest/treasure_chest_side.rgba16.inc.c", 0x001b9cc0, 41188, 0x000147a8, 2048);

// 0x06014FA8
ROM_ASSET_LOAD_TEXTURE(treasure_chest_seg6_texture_06014FA8, "actors/treasure_chest/treasure_chest_lock_top.rgba16.inc.c", 0x001b9cc0, 41188, 0x00014fa8, 2048);

// 0x060157A8
ROM_ASSET_LOAD_TEXTURE(treasure_chest_seg6_texture_060157A8, "actors/treasure_chest/treasure_chest_front.rgba16.inc.c", 0x001b9cc0, 41188, 0x000157a8, 4096);

// 0x060167A8
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_060167A8, 0x001b9cc0, 41188, 0x000167a8, 64);

// 0x060167E8
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_060167E8, 0x001b9cc0, 41188, 0x000167e8, 256);

// 0x060168E8
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_060168E8, 0x001b9cc0, 41188, 0x000168e8, 48);

// 0x06016918
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06016918, 0x001b9cc0, 41188, 0x00016918, 240);

// 0x06016A08
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06016A08, 0x001b9cc0, 41188, 0x00016a08, 240);

// 0x06016AF8
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06016AF8, 0x001b9cc0, 41188, 0x00016af8, 128);

// 0x06016B78
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06016B78, 0x001b9cc0, 41188, 0x00016b78, 256);

// 0x06016C78
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06016C78, 0x001b9cc0, 41188, 0x00016c78, 224);

// 0x06016D58 - 0x06016DA0
const Gfx treasure_chest_seg6_dl_06016D58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_06013FA8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.l, 1),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.a, 2),
    gsSPVertex(treasure_chest_seg6_vertex_060167A8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016DA0 - 0x06016E18
const Gfx treasure_chest_seg6_dl_06016DA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_06014FA8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_060167E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_060168E8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016E18 - 0x06016EE0
const Gfx treasure_chest_seg6_dl_06016E18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_060147A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06016918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06016A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06016AF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016EE0 - 0x06016F90
const Gfx treasure_chest_seg6_dl_06016EE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_060157A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06016B78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06016C78, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  1, 11,  2, 0x0),
    gsSP2Triangles( 1, 12, 11, 0x0,  0, 13,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016F90 - 0x06017030
const Gfx treasure_chest_seg6_dl_06016F90[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06016D58),
    gsSPDisplayList(treasure_chest_seg6_dl_06016DA0),
    gsSPDisplayList(treasure_chest_seg6_dl_06016E18),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06016EE0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06017030
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06017030, 0x001b9cc0, 41188, 0x00017030, 224);

// 0x06017110
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06017110, 0x001b9cc0, 41188, 0x00017110, 240);

// 0x06017200
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06017200, 0x001b9cc0, 41188, 0x00017200, 240);

// 0x060172F0
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_060172F0, 0x001b9cc0, 41188, 0x000172f0, 64);

// 0x06017330
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06017330, 0x001b9cc0, 41188, 0x00017330, 240);

// 0x06017420
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06017420, 0x001b9cc0, 41188, 0x00017420, 112);

// 0x06017490
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06017490, 0x001b9cc0, 41188, 0x00017490, 256);

// 0x06017590
ROM_ASSET_LOAD_VTX(treasure_chest_seg6_vertex_06017590, 0x001b9cc0, 41188, 0x00017590, 240);

// 0x06017680 - 0x06017790
const Gfx treasure_chest_seg6_dl_06017680[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_060147A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.l, 1),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.a, 2),
    gsSPVertex(treasure_chest_seg6_vertex_06017030, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017110, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017200, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_060172F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06017790 - 0x06017810
const Gfx treasure_chest_seg6_dl_06017790[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_06014FA8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06017330, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017420, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06017810 - 0x060178C0
const Gfx treasure_chest_seg6_dl_06017810[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_060157A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06017490, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017590, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9,  5, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 10, 12, 0x0, 13, 14, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x060178C0 - 0x06017958
const Gfx treasure_chest_seg6_dl_060178C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06017680),
    gsSPDisplayList(treasure_chest_seg6_dl_06017790),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06017810),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
