#include "pc/rom_assets.h"
// Cannon Barrel

// 0x08005878
static const Lights1 cannon_barrel_seg8_lights_08005878 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08005890
static const Lights1 cannon_barrel_seg8_lights_08005890 = gdSPDefLights1(
    0x00, 0x00, 0x0f,
    0x00, 0x00, 0x32, 0x28, 0x28, 0x28
);

// 0x080058A8
ROM_ASSET_LOAD_TEXTURE(cannon_barrel_seg8_texture_080058A8, "actors/cannon_barrel/cannon_barrel.rgba16.inc.c", 0x001f2200, 59076, 0x000058a8, 2048);

// 0x080060A8
ROM_ASSET_LOAD_VTX(cannon_barrel_seg8_vertex_080060A8, 0x001f2200, 59076, 0x000060a8, 256);

// 0x080061A8
ROM_ASSET_LOAD_VTX(cannon_barrel_seg8_vertex_080061A8, 0x001f2200, 59076, 0x000061a8, 256);

// 0x080062A8
ROM_ASSET_LOAD_VTX(cannon_barrel_seg8_vertex_080062A8, 0x001f2200, 59076, 0x000062a8, 256);

// 0x080063A8
ROM_ASSET_LOAD_VTX(cannon_barrel_seg8_vertex_080063A8, 0x001f2200, 59076, 0x000063a8, 96);

// 0x08006408 - 0x080064C0
const Gfx cannon_barrel_seg8_dl_08006408[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cannon_barrel_seg8_texture_080058A8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cannon_barrel_seg8_lights_08005878.l, 1),
    gsSPLight(&cannon_barrel_seg8_lights_08005878.a, 2),
    gsSPVertex(cannon_barrel_seg8_vertex_080060A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9,  6, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 10, 13, 12, 0x0),
    gsSP2Triangles(14, 15, 12, 0x0, 14,  3, 15, 0x0),
    gsSP2Triangles(14,  0,  3, 0x0, 14, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x080064C0 - 0x08006660
const Gfx cannon_barrel_seg8_dl_080064C0[] = {
    gsSPLight(&cannon_barrel_seg8_lights_08005890.l, 1),
    gsSPLight(&cannon_barrel_seg8_lights_08005890.a, 2),
    gsSPVertex(cannon_barrel_seg8_vertex_080061A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  4,  7,  9, 0x0),
    gsSP2Triangles( 4,  9,  2, 0x0,  4,  2,  1, 0x0),
    gsSP2Triangles( 4,  1, 10, 0x0,  4, 10,  8, 0x0),
    gsSP2Triangles(11,  9,  7, 0x0, 11,  7,  6, 0x0),
    gsSP2Triangles(12,  2,  9, 0x0, 12,  9, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 10,  1, 0x0),
    gsSP2Triangles(13,  1,  0, 0x0, 14,  8, 10, 0x0),
    gsSP2Triangles(14, 10, 13, 0x0, 15,  8, 14, 0x0),
    gsSP2Triangles(15,  5,  8, 0x0,  3,  5, 15, 0x0),
    gsSPVertex(cannon_barrel_seg8_vertex_080062A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  0,  6,  4, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  3,  8,  2, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  9,  0,  2, 0x0),
    gsSP2Triangles( 9,  6,  0, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles(11,  9,  2, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 13, 11,  2, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0,  8,  7, 14, 0x0),
    gsSP1Triangle(13, 15, 12, 0x0),
    gsSPVertex(cannon_barrel_seg8_vertex_080063A8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  0,  2, 0x0),
    gsSP1Triangle( 5,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x08006660 - 0x080066C8
const Gfx cannon_barrel_seg8_dl_08006660[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cannon_barrel_seg8_dl_08006408),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(cannon_barrel_seg8_dl_080064C0),
    gsSPEndDisplayList(),
};
