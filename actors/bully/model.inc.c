#include "pc/rom_assets.h"
// Bully

// 0x05000000
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05000000, 0x00132c60, 7692, 0x00000000, 224);

// 0x050000E0
ROM_ASSET_LOAD_TEXTURE(bully_seg5_texture_050000E0, "actors/bully/bully_horn.rgba16.inc.c", 0x00132c60, 7692, 0x000000e0, 512);

// 0x050002E0 - 0x05000398
const Gfx bully_seg5_dl_050002E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bully_seg5_texture_050000E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bully_seg5_vertex_05000000, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  5,  8,  3, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  9,  6, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11,  2, 0x0,  0, 12, 10, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0,  2,  1, 10, 0x0),
    gsSP2Triangles(10,  1,  0, 0x0,  2, 11, 13, 0x0),
    gsSP2Triangles( 0, 13, 12, 0x0,  2, 13,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05000398 - 0x05000408
const Gfx bully_seg5_dl_05000398[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bully_seg5_dl_050002E0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05000408
static const Lights1 bully_seg5_lights_05000408 = gdSPDefLights1(
    0x00, 0x38, 0x00,
    0x00, 0xe3, 0x00, 0x28, 0x28, 0x28
);

// 0x05000420
static const Lights1 bully_seg5_lights_05000420 = gdSPDefLights1(
    0x00, 0x3f, 0x00,
    0x00, 0xff, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 bully_lights_unused = gdSPDefLights1(
    0x3f, 0x29, 0x00,
    0xff, 0xa5, 0x00, 0x28, 0x28, 0x28
);

// 0x05000450
static const Lights1 bully_seg5_lights_05000450 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// //! There's another malformed light entry here.
// 0x05000468
ROM_ASSET_LOAD_TEXTURE(bully_seg5_texture_05000468, "actors/bully/bully_left_side.rgba16.inc.c", 0x00132c60, 7692, 0x00000468, 4096);

// 0x05001468
ROM_ASSET_LOAD_TEXTURE(bully_seg5_texture_05001468, "actors/bully/bully_right_side.rgba16.inc.c", 0x00132c60, 7692, 0x00001468, 4096);

// 0x05002468
ROM_ASSET_LOAD_TEXTURE(bully_seg5_texture_05002468, "actors/bully/bully_eye.rgba16.inc.c", 0x00132c60, 7692, 0x00002468, 2048);

// 0x05002C68
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05002C68, 0x00132c60, 7692, 0x00002c68, 224);

// 0x05002D48
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05002D48, 0x00132c60, 7692, 0x00002d48, 64);

// 0x05002D88
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05002D88, 0x00132c60, 7692, 0x00002d88, 224);

// 0x05002E68
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05002E68, 0x00132c60, 7692, 0x00002e68, 64);

// 0x05002EA8
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05002EA8, 0x00132c60, 7692, 0x00002ea8, 96);

// 0x05002F08
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05002F08, 0x00132c60, 7692, 0x00002f08, 256);

// 0x05003008
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003008, 0x00132c60, 7692, 0x00003008, 256);

// 0x05003108
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003108, 0x00132c60, 7692, 0x00003108, 256);

// 0x05003208
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003208, 0x00132c60, 7692, 0x00003208, 256);

// 0x05003308
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003308, 0x00132c60, 7692, 0x00003308, 256);

// 0x05003408
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003408, 0x00132c60, 7692, 0x00003408, 256);

// 0x05003508
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003508, 0x00132c60, 7692, 0x00003508, 256);

// 0x05003608
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003608, 0x00132c60, 7692, 0x00003608, 256);

// 0x05003708 - 0x050037A0
const Gfx bully_seg5_dl_05003708[] = {
    gsSPLight(&bully_seg5_lights_05000408.l, 1),
    gsSPLight(&bully_seg5_lights_05000408.a, 2),
    gsSPVertex(bully_seg5_vertex_05002C68, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 1,  6,  7, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  8,  2,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  0,  8, 11, 0x0),
    gsSPVertex(bully_seg5_vertex_05002D48, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x050037A0 - 0x05003838
const Gfx bully_seg5_dl_050037A0[] = {
    gsSPLight(&bully_seg5_lights_05000420.l, 1),
    gsSPLight(&bully_seg5_lights_05000420.a, 2),
    gsSPVertex(bully_seg5_vertex_05002D88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  1, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0,  9, 10,  0, 0x0),
    gsSP2Triangles( 9,  0,  8, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(11,  8, 13, 0x0, 13,  8,  2, 0x0),
    gsSPVertex(bully_seg5_vertex_05002E68, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003838 - 0x05003878
const Gfx bully_seg5_dl_05003838[] = {
    gsSPLight((u8*)bully_seg5_texture_05000468 + 0x8, 1), //! yet another malformed light...
    gsSPLight(bully_seg5_texture_05000468, 2),
    gsSPVertex(bully_seg5_vertex_05002EA8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003878 - 0x05003C50
const Gfx bully_seg5_dl_05003878[] = {
    gsSPLight(&bully_seg5_lights_05000450.l, 1),
    gsSPLight(&bully_seg5_lights_05000450.a, 2),
    gsSPVertex(bully_seg5_vertex_05002F08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(bully_seg5_vertex_05003008, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(bully_seg5_vertex_05003108, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(bully_seg5_vertex_05003208, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(bully_seg5_vertex_05003308, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(bully_seg5_vertex_05003408, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(bully_seg5_vertex_05003508, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(bully_seg5_vertex_05003608, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003C50
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003C50, 0x00132c60, 7692, 0x00003c50, 64);

// 0x05003C90
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003C90, 0x00132c60, 7692, 0x00003c90, 64);

// 0x05003CD0 - 0x05003D08
const Gfx bully_seg5_dl_05003CD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bully_seg5_texture_05000468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bully_seg5_vertex_05003C50, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003D08 - 0x05003D40
const Gfx bully_seg5_dl_05003D08[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bully_seg5_texture_05001468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bully_seg5_vertex_05003C90, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003D40 - 0x05003DB8
const Gfx bully_seg5_dl_05003D40[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bully_seg5_dl_05003CD0),
    gsSPDisplayList(bully_seg5_dl_05003D08),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05003DB8
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003DB8, 0x00132c60, 7692, 0x00003db8, 64);

// 0x05003DF8
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003DF8, 0x00132c60, 7692, 0x00003df8, 64);

// 0x05003E38 - 0x05003E70
const Gfx bully_seg5_dl_05003E38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bully_seg5_texture_05000468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bully_seg5_vertex_05003DB8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003E70 - 0x05003EA8
const Gfx bully_seg5_dl_05003E70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bully_seg5_texture_05001468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bully_seg5_vertex_05003DF8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003EA8 - 0x05003F20
const Gfx bully_seg5_dl_05003EA8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bully_seg5_dl_05003E38),
    gsSPDisplayList(bully_seg5_dl_05003E70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05003F20
ROM_ASSET_LOAD_VTX(bully_seg5_vertex_05003F20, 0x00132c60, 7692, 0x00003f20, 96);

// 0x05003F80 - 0x05003FC8
const Gfx bully_seg5_dl_05003F80[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bully_seg5_texture_05002468),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bully_seg5_vertex_05003F20, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003FC8 - 0x05004038
const Gfx bully_seg5_dl_05003FC8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bully_seg5_dl_05003F80),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
