#include "pc/rom_assets.h"
// 0x07007C90 - 0x07007CA8
static const Lights1 thi_seg7_lights_07007C90 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07007CA8 - 0x07007CC0
static const Lights1 thi_seg7_lights_07007CA8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07007CC0 - 0x07007CD8
static const Lights1 thi_seg7_lights_07007CC0 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07007CD8 - 0x07007CF0
static const Lights1 thi_seg7_lights_07007CD8 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07007CF0 - 0x07007D08
static const Lights1 thi_seg7_lights_07007CF0 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xcc, 0xcc, 0xcc, 0x28, 0x28, 0x28
);

// 0x07007D08 - 0x07007D88
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07007D08, 0x004246d0, 32780, 0x00007d08, 128);

// 0x07007D88 - 0x07007DC8
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07007D88, 0x004246d0, 32780, 0x00007d88, 64);

// 0x07007DC8 - 0x07007E08
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07007DC8, 0x004246d0, 32780, 0x00007dc8, 64);

// 0x07007E08 - 0x07007EE8
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07007E08, 0x004246d0, 32780, 0x00007e08, 224);

// 0x07007EE8 - 0x07007FD8
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07007EE8, 0x004246d0, 32780, 0x00007ee8, 240);

// 0x07007FD8 - 0x070080D8
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07007FD8, 0x004246d0, 32780, 0x00007fd8, 256);

// 0x070080D8 - 0x070081C8
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070080D8, 0x004246d0, 32780, 0x000080d8, 240);

// 0x070081C8 - 0x070082A8
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070081C8, 0x004246d0, 32780, 0x000081c8, 224);

// 0x070082A8 - 0x07008388
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_070082A8, 0x004246d0, 32780, 0x000082a8, 224);

// 0x07008388 - 0x07008478
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008388, 0x004246d0, 32780, 0x00008388, 240);

// 0x07008478 - 0x07008568
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008478, 0x004246d0, 32780, 0x00008478, 240);

// 0x07008568 - 0x07008658
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008568, 0x004246d0, 32780, 0x00008568, 240);

// 0x07008658 - 0x07008748
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008658, 0x004246d0, 32780, 0x00008658, 240);

// 0x07008748 - 0x07008838
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008748, 0x004246d0, 32780, 0x00008748, 240);

// 0x07008838 - 0x07008928
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008838, 0x004246d0, 32780, 0x00008838, 240);

// 0x07008928 - 0x07008A28
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008928, 0x004246d0, 32780, 0x00008928, 256);

// 0x07008A28 - 0x07008B18
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008A28, 0x004246d0, 32780, 0x00008a28, 240);

// 0x07008B18 - 0x07008B78
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008B18, 0x004246d0, 32780, 0x00008b18, 96);

// 0x07008B78 - 0x07008C58
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008B78, 0x004246d0, 32780, 0x00008b78, 224);

// 0x07008C58 - 0x07008D38
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008C58, 0x004246d0, 32780, 0x00008c58, 224);

// 0x07008D38 - 0x07008D78
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008D38, 0x004246d0, 32780, 0x00008d38, 64);

// 0x07008D78 - 0x07008E38
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008D78, 0x004246d0, 32780, 0x00008d78, 192);

// 0x07008E38 - 0x07008F18
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008E38, 0x004246d0, 32780, 0x00008e38, 224);

// 0x07008F18 - 0x07008F98
ROM_ASSET_LOAD_VTX(thi_seg7_vertex_07008F18, 0x004246d0, 32780, 0x00008f18, 128);

// 0x07008F98 - 0x07009010
static const Gfx thi_seg7_dl_07008F98[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_0900B800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07007C90.l, 1),
    gsSPLight(&thi_seg7_lights_07007C90.a, 2),
    gsSPVertex(thi_seg7_vertex_07007D08, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  6,  5,  2, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009010 - 0x07009080
static const Gfx thi_seg7_dl_07009010[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07007CA8.l, 1),
    gsSPLight(&thi_seg7_lights_07007CA8.a, 2),
    gsSPVertex(thi_seg7_vertex_07007D88, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&thi_seg7_lights_07007CC0.l, 1),
    gsSPLight(&thi_seg7_lights_07007CC0.a, 2),
    gsSPVertex(thi_seg7_vertex_07007DC8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009080 - 0x07009530
static const Gfx thi_seg7_dl_07009080[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07007CA8.l, 1),
    gsSPLight(&thi_seg7_lights_07007CA8.a, 2),
    gsSPVertex(thi_seg7_vertex_07007E08, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  6,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 11, 12, 13, 0x0),
    gsSPLight(&thi_seg7_lights_07007CD8.l, 1),
    gsSPLight(&thi_seg7_lights_07007CD8.a, 2),
    gsSPVertex(thi_seg7_vertex_07007EE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07007FD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  7, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  8, 10,  6, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_070080D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_070081C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_070082A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  0, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 13, 11, 0x0),
    gsSPVertex(thi_seg7_vertex_07008388, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07008478, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(thi_seg7_vertex_07008568, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(thi_seg7_vertex_07008658, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(thi_seg7_vertex_07008748, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07008838, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07008928, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  1,  0, 0x0, 10, 11,  1, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(thi_seg7_vertex_07008A28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(thi_seg7_vertex_07008B18, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&thi_seg7_lights_07007CF0.l, 1),
    gsSPLight(&thi_seg7_lights_07007CF0.a, 2),
    gsSPVertex(thi_seg7_vertex_07008B78, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07008C58, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(thi_seg7_vertex_07008D38, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009530 - 0x070095A8
static const Gfx thi_seg7_dl_07009530[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thi_seg7_lights_07007CC0.l, 1),
    gsSPLight(&thi_seg7_lights_07007CC0.a, 2),
    gsSPVertex(thi_seg7_vertex_07008D78, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8,  7, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x070095A8 - 0x07009610
static const Gfx thi_seg7_dl_070095A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thi_seg7_vertex_07008E38, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  0,  8,  9, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0,  0, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009610 - 0x07009670
static const Gfx thi_seg7_dl_07009610[] = {
    gsSPLight(&thi_seg7_lights_07007C90.l, 1),
    gsSPLight(&thi_seg7_lights_07007C90.a, 2),
    gsSPVertex(thi_seg7_vertex_07008F18, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  0,  3,  5, 0x0),
    gsSP2Triangles( 6,  5,  3, 0x0,  6,  3,  7, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009670 - 0x07009740
const Gfx thi_seg7_dl_07009670[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07008F98),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07009010),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_07009080),
    gsSPDisplayList(thi_seg7_dl_07009530),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thi_seg7_dl_070095A8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(thi_seg7_dl_07009610),
    gsSPEndDisplayList(),
};
