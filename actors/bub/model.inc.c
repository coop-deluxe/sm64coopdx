#include "pc/rom_assets.h"
// Bub

// 0x0600E278
static const Lights1 bub_seg6_lights_0600E280 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0600E290
static const Lights1 bub_seg6_lights_0600E290 = gdSPDefLights1(
    0x3f, 0x1d, 0x25,
    0xff, 0x75, 0x94, 0x28, 0x28, 0x28
);

// 0x0600E2A8
ROM_ASSET_LOAD_TEXTURE(bub_seg6_texture_0600E2A8, "actors/bub/bub_eye_border.rgba16.inc.c", 0x00180bb0, 29674, 0x00001408, 2048);

// 0x0600EAA8
ROM_ASSET_LOAD_TEXTURE(bub_seg6_texture_0600EAA8, "actors/bub/bub_fins.rgba16.inc.c", 0x00180bb0, 29674, 0x00001c08, 2048);

// 0x0600F2A8
ROM_ASSET_LOAD_TEXTURE(bub_seg6_texture_0600F2A8, "actors/bub/bub_eyes.rgba16.inc.c", 0x00180bb0, 29674, 0x00000408, 4096);

// 0x060102A8
ROM_ASSET_LOAD_TEXTURE(bub_seg6_texture_060102A8, "actors/bub/bub_scales.rgba16.inc.c", 0x00180bb0, 29674, 0x00002408, 4096);

// 0x060112A8
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_060112A8, 0x001b9cc0, 41188, 0x000112a8, 224);

// 0x06011388
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011388, 0x001b9cc0, 41188, 0x00011388, 48);

// 0x060113B8
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_060113B8, 0x001b9cc0, 41188, 0x000113b8, 96);

// 0x06011418
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011418, 0x001b9cc0, 41188, 0x00011418, 112);

// 0x06011488
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011488, 0x001b9cc0, 41188, 0x00011488, 240);

// 0x06011578
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011578, 0x001b9cc0, 41188, 0x00011578, 224);

// 0x06011658
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011658, 0x001b9cc0, 41188, 0x00011658, 192);

// 0x06011718
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011718, 0x001b9cc0, 41188, 0x00011718, 192);

// 0x060117D8
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_060117D8, 0x001b9cc0, 41188, 0x000117d8, 112);

// 0x06011848 - 0x060118C0
const Gfx bub_seg6_dl_06011848[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bub_seg6_texture_0600E2A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bub_seg6_lights_0600E280.l, 1),
    gsSPLight(&bub_seg6_lights_0600E280.a, 2),
    gsSPVertex(bub_seg6_vertex_060112A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bub_seg6_vertex_06011388, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x060118C0 - 0x06011918
const Gfx bub_seg6_dl_060118C0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bub_seg6_texture_0600EAA8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bub_seg6_vertex_060113B8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 5,  3,  2, 0x0,  4,  3,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011918 - 0x06011968
const Gfx bub_seg6_dl_06011918[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bub_seg6_texture_0600F2A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bub_seg6_vertex_06011418, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  6,  2,  4, 0x0),
    gsSP1Triangle( 6,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011968 - 0x06011A50
const Gfx bub_seg6_dl_06011968[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bub_seg6_texture_060102A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bub_seg6_vertex_06011488, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9, 10,  0, 0x0),
    gsSP2Triangles( 9,  0, 11, 0x0, 11, 12,  9, 0x0),
    gsSP2Triangles(10, 13,  0, 0x0, 13,  1,  0, 0x0),
    gsSP2Triangles( 2, 11,  0, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(bub_seg6_vertex_06011578, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bub_seg6_vertex_06011658, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011A50 - 0x06011B28
const Gfx bub_seg6_dl_06011A50[] = {
    gsSPLight(&bub_seg6_lights_0600E290.l, 1),
    gsSPLight(&bub_seg6_lights_0600E290.a, 2),
    gsSPVertex(bub_seg6_vertex_06011718, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8,  5,  0, 0x0),
    gsSP2Triangles( 0, 11,  8, 0x0,  8, 10,  5, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0, 10,  9,  6, 0x0),
    gsSPLight(&bub_seg6_lights_0600E280.l, 1),
    gsSPLight(&bub_seg6_lights_0600E280.a, 2),
    gsSPVertex(bub_seg6_vertex_060117D8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  0,  2,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011B28 - 0x06011BD8
const Gfx bub_seg6_dl_06011B28[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bub_seg6_dl_06011848),
    gsSPDisplayList(bub_seg6_dl_060118C0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bub_seg6_dl_06011918),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bub_seg6_dl_06011968),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bub_seg6_dl_06011A50),
    gsSPEndDisplayList(),
};

// 0x06011BD8
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011BD8, 0x001b9cc0, 41188, 0x00011bd8, 128);

// 0x06011C58 - 0x06011CF0
const Gfx bub_seg6_dl_06011C58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bub_seg6_texture_0600EAA8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bub_seg6_lights_0600E280.l, 1),
    gsSPLight(&bub_seg6_lights_0600E280.a, 2),
    gsSPVertex(bub_seg6_vertex_06011BD8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 6,  1,  0, 0x0,  4,  0,  3, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 7,  1,  6, 0x0,  2,  7,  3, 0x0),
    gsSP2Triangles( 3,  7,  4, 0x0,  1,  7,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011CF0 - 0x06011D50
const Gfx bub_seg6_dl_06011CF0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bub_seg6_dl_06011C58),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06011D50
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011D50, 0x001b9cc0, 41188, 0x00011d50, 112);

// 0x06011DC0 - 0x06011E48
const Gfx bub_seg6_dl_06011DC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bub_seg6_texture_0600EAA8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bub_seg6_lights_0600E280.l, 1),
    gsSPLight(&bub_seg6_lights_0600E280.a, 2),
    gsSPVertex(bub_seg6_vertex_06011D50, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  5,  0, 0x0,  3,  6,  0, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  6,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011E48 - 0x06011EA8
const Gfx bub_seg6_dl_06011E48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bub_seg6_dl_06011DC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06011EA8
ROM_ASSET_LOAD_VTX(bub_seg6_vertex_06011EA8, 0x001b9cc0, 41188, 0x00011ea8, 112);

// 0x06011F18 - 0x06011FA0
const Gfx bub_seg6_dl_06011F18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bub_seg6_texture_0600EAA8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bub_seg6_lights_0600E280.l, 1),
    gsSPLight(&bub_seg6_lights_0600E280.a, 2),
    gsSPVertex(bub_seg6_vertex_06011EA8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  6,  4,  0, 0x0),
    gsSP2Triangles( 6,  5,  2, 0x0,  4,  6,  2, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  1,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x06011FA0 - 0x06012000
const Gfx bub_seg6_dl_06011FA0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bub_seg6_dl_06011F18),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
