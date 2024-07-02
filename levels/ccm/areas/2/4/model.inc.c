#include "pc/rom_assets.h"
// 0x0701E720 - 0x0701E738
static const Lights1 ccm_seg7_lights_0701E720 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701E738 - 0x0701E828
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701E738, 0x00383950, 74560, 0x0001e738, 240);

// 0x0701E828 - 0x0701E918
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701E828, 0x00383950, 74560, 0x0001e828, 240);

// 0x0701E918 - 0x0701EA08
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701E918, 0x00383950, 74560, 0x0001e918, 240);

// 0x0701EA08 - 0x0701EAF8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701EA08, 0x00383950, 74560, 0x0001ea08, 240);

// 0x0701EAF8 - 0x0701EBE8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701EAF8, 0x00383950, 74560, 0x0001eaf8, 240);

// 0x0701EBE8 - 0x0701ECC8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701EBE8, 0x00383950, 74560, 0x0001ebe8, 224);

// 0x0701ECC8 - 0x0701EDB8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701ECC8, 0x00383950, 74560, 0x0001ecc8, 240);

// 0x0701EDB8 - 0x0701EEA8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701EDB8, 0x00383950, 74560, 0x0001edb8, 240);

// 0x0701EEA8 - 0x0701EF88
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701EEA8, 0x00383950, 74560, 0x0001eea8, 224);

// 0x0701EF88 - 0x0701F068
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701EF88, 0x00383950, 74560, 0x0001ef88, 224);

// 0x0701F068 - 0x0701F158
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F068, 0x00383950, 74560, 0x0001f068, 240);

// 0x0701F158 - 0x0701F238
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F158, 0x00383950, 74560, 0x0001f158, 224);

// 0x0701F238 - 0x0701F318
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F238, 0x00383950, 74560, 0x0001f238, 224);

// 0x0701F318 - 0x0701F3F8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F318, 0x00383950, 74560, 0x0001f318, 224);

// 0x0701F3F8 - 0x0701F4E8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F3F8, 0x00383950, 74560, 0x0001f3f8, 240);

// 0x0701F4E8 - 0x0701F5C8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F4E8, 0x00383950, 74560, 0x0001f4e8, 224);

// 0x0701F5C8 - 0x0701F6C8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F5C8, 0x00383950, 74560, 0x0001f5c8, 256);

// 0x0701F6C8 - 0x0701F7C8
ROM_ASSET_LOAD_VTX(ccm_seg7_vertex_0701F6C8, 0x00383950, 74560, 0x0001f6c8, 256);

// 0x0701F7C8 - 0x0701FC78
static const Gfx ccm_seg7_dl_0701F7C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0701E720.l, 1),
    gsSPLight(&ccm_seg7_lights_0701E720.a, 2),
    gsSPVertex(ccm_seg7_vertex_0701E738, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 12,  8, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle(11, 14, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701E828, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701E918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701EA08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701EAF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(10, 14,  8, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701EBE8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701ECC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 10,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701EDB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 10,  9, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701EEA8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701EF88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  4,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(11, 13, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F068, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F158, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F238, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F318, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F3F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F4E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F5C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 13, 12, 0x0, 15,  2,  1, 0x0),
    gsSPVertex(ccm_seg7_vertex_0701F6C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 9, 14, 10, 0x0, 15, 11, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701FC78 - 0x0701FCD8
const Gfx ccm_seg7_dl_0701FC78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_0701F7C8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
