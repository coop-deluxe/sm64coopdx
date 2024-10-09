#include "pc/rom_assets.h"
// Goomba

// Unreferenced light group
UNUSED static const Lights1 goomba_lights_unused1 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 goomba_lights_unused2 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x080194D0
static const Lights1 goomba_seg8_lights_080194D0 = gdSPDefLights1(
    0x15, 0x0b, 0x04,
    0x54, 0x2e, 0x10, 0x28, 0x28, 0x28
);

// 0x080194E8
static const Lights1 goomba_seg8_lights_080194E8 = gdSPDefLights1(
    0x18, 0x0d, 0x04,
    0x61, 0x34, 0x13, 0x28, 0x28, 0x28
);

// 0x08019500
static const Lights1 goomba_seg8_lights_08019500 = gdSPDefLights1(
    0x1d, 0x10, 0x08,
    0x77, 0x42, 0x20, 0x28, 0x28, 0x28
);

// 0x08019518
static const Lights1 goomba_seg8_lights_08019518 = gdSPDefLights1(
    0x37, 0x2d, 0x13,
    0xde, 0xb4, 0x4e, 0x28, 0x28, 0x28
);

// 0x08019530
ROM_ASSET_LOAD_TEXTURE(goomba_seg8_texture_08019530, "actors/goomba/goomba_body.rgba16.inc.c", 0x001f2200, 59076, 0x00019530, 2048);

// 0x08019D30
ROM_ASSET_LOAD_TEXTURE(goomba_seg8_texture_08019D30, "actors/goomba/goomba_face.rgba16.inc.c", 0x001f2200, 59076, 0x00019d30, 2048);

// 0x0801A530
ROM_ASSET_LOAD_TEXTURE(goomba_seg8_texture_0801A530, "actors/goomba/goomba_face_blink.rgba16.inc.c", 0x001f2200, 59076, 0x0001a530, 2048);

// 0x0801AD30
static const Lights1 goomba_seg8_lights_0801AD30 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0801AD48
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801AD48, 0x001f2200, 59076, 0x0001ad48, 240);

// 0x0801AE38
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801AE38, 0x001f2200, 59076, 0x0001ae38, 256);

// 0x0801AF38
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801AF38, 0x001f2200, 59076, 0x0001af38, 256);

// 0x0801B038
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B038, 0x001f2200, 59076, 0x0001b038, 256);

// 0x0801B138
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B138, 0x001f2200, 59076, 0x0001b138, 256);

// 0x0801B238
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B238, 0x001f2200, 59076, 0x0001b238, 176);

// 0x0801B2E8 - 0x0801B560
const Gfx goomba_seg8_dl_0801B2E8[] = {
    gsSPLight(&goomba_seg8_lights_0801AD30.l, 1),
    gsSPLight(&goomba_seg8_lights_0801AD30.a, 2),
    gsSPVertex(goomba_seg8_vertex_0801AD48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 5,  6,  8, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles( 7,  5,  9, 0x0,  3,  7, 10, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  3, 11,  4, 0x0),
    gsSP2Triangles( 3, 10, 12, 0x0,  3, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801AE38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  1,  4,  2, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  6,  0,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 9, 11,  7, 0x0, 12,  9, 13, 0x0),
    gsSP2Triangles(12, 11,  9, 0x0,  7, 11, 12, 0x0),
    gsSP1Triangle(14,  2, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801AF38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  5,  3,  0, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  1,  3,  7, 0x0),
    gsSP2Triangles( 5,  8,  3, 0x0,  6,  3,  8, 0x0),
    gsSP2Triangles( 7,  6,  9, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  1,  7, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801B038, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9,  3,  7, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0,  7,  8, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  3, 14,  4, 0x0),
    gsSP1Triangle( 9, 15,  3, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801B138, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  1,  4,  8, 0x0),
    gsSP2Triangles( 4,  9,  5, 0x0,  4, 10,  9, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3, 10, 0x0),
    gsSP2Triangles(11,  9, 10, 0x0, 11, 12,  9, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801B238, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  1,  8, 0x0),
    gsSP2Triangles( 8,  1,  0, 0x0,  3,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0801B560 - 0x0801B5A0
const Gfx goomba_seg8_dl_0801B560[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0801B5A0 - 0x0801B5C8
const Gfx goomba_seg8_dl_0801B5A0[] = {
    gsSPDisplayList(goomba_seg8_dl_0801B2E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0801B5C8 - 0x0801B5F0
const Gfx goomba_seg8_dl_0801B5C8[] = {
    gsSPDisplayList(goomba_seg8_dl_0801B560),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, goomba_seg8_texture_08019D30),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(goomba_seg8_dl_0801B5A0),
};

// 0x0801B5F0 - 0x0801B618
const Gfx goomba_seg8_dl_0801B5F0[] = {
    gsSPDisplayList(goomba_seg8_dl_0801B560),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, goomba_seg8_texture_0801A530),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(goomba_seg8_dl_0801B5A0),
};

// 0x0801B618
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B618, 0x001f2200, 59076, 0x0001b618, 64);

// 0x0801B658 - 0x0801B690
const Gfx goomba_seg8_dl_0801B658[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, goomba_seg8_texture_08019530),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(goomba_seg8_vertex_0801B618, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0801B690 - 0x0801B700
const Gfx goomba_seg8_dl_0801B690[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(goomba_seg8_dl_0801B658),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0801B700
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B700, 0x001f2200, 59076, 0x0001b700, 256);

// 0x0801B800
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B800, 0x001f2200, 59076, 0x0001b800, 240);

// 0x0801B8F0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B8F0, 0x001f2200, 59076, 0x0001b8f0, 224);

// 0x0801B9D0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801B9D0, 0x001f2200, 59076, 0x0001b9d0, 128);

// 0x0801BA50
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801BA50, 0x001f2200, 59076, 0x0001ba50, 240);

// 0x0801BB40
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801BB40, 0x001f2200, 59076, 0x0001bb40, 256);

// 0x0801BC40
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801BC40, 0x001f2200, 59076, 0x0001bc40, 256);

// 0x0801BD40
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801BD40, 0x001f2200, 59076, 0x0001bd40, 128);

// 0x0801BDC0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801BDC0, 0x001f2200, 59076, 0x0001bdc0, 256);

// 0x0801BEC0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801BEC0, 0x001f2200, 59076, 0x0001bec0, 240);

// 0x0801BFB0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801BFB0, 0x001f2200, 59076, 0x0001bfb0, 240);

// 0x0801C0A0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C0A0, 0x001f2200, 59076, 0x0001c0a0, 256);

// 0x0801C1A0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C1A0, 0x001f2200, 59076, 0x0001c1a0, 224);

// 0x0801C280
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C280, 0x001f2200, 59076, 0x0001c280, 224);

// 0x0801C360
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C360, 0x001f2200, 59076, 0x0001c360, 256);

// 0x0801C460
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C460, 0x001f2200, 59076, 0x0001c460, 256);

// 0x0801C560
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C560, 0x001f2200, 59076, 0x0001c560, 192);

// 0x0801C620
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C620, 0x001f2200, 59076, 0x0001c620, 256);

// 0x0801C720
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C720, 0x001f2200, 59076, 0x0001c720, 240);

// 0x0801C810
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C810, 0x001f2200, 59076, 0x0001c810, 256);

// 0x0801C910
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801C910, 0x001f2200, 59076, 0x0001c910, 240);

// 0x0801CA00
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801CA00, 0x001f2200, 59076, 0x0001ca00, 256);

// 0x0801CB00
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801CB00, 0x001f2200, 59076, 0x0001cb00, 240);

// 0x0801CBF0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801CBF0, 0x001f2200, 59076, 0x0001cbf0, 256);

// 0x0801CCF0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801CCF0, 0x001f2200, 59076, 0x0001ccf0, 256);

// 0x0801CDF0
ROM_ASSET_LOAD_VTX(goomba_seg8_vertex_0801CDF0, 0x001f2200, 59076, 0x0001cdf0, 48);

// 0x0801CE20 - 0x0801CF78
const Gfx goomba_seg8_dl_0801CE20[] = {
    gsSPLight(&goomba_seg8_lights_080194D0.l, 1),
    gsSPLight(&goomba_seg8_lights_080194D0.a, 2),
    gsSPVertex(goomba_seg8_vertex_0801B700, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801B800, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  2, 12, 13, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  9, 11, 0x0),
    gsSP2Triangles( 2, 13,  4, 0x0,  2,  4,  3, 0x0),
    gsSP2Triangles( 3,  5, 14, 0x0,  3, 14,  0, 0x0),
    gsSP2Triangles( 8,  7,  5, 0x0,  8,  5,  4, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801B8F0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  8,  5, 10, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 11,  9, 13, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801B9D0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 2,  4,  7, 0x0,  2,  7,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0801CF78 - 0x0801D0D0
const Gfx goomba_seg8_dl_0801CF78[] = {
    gsSPLight(&goomba_seg8_lights_080194E8.l, 1),
    gsSPLight(&goomba_seg8_lights_080194E8.a, 2),
    gsSPVertex(goomba_seg8_vertex_0801BA50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 0,  3,  6, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 12,  9, 14, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801BB40, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  8,  5, 10, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 11,  9, 13, 0x0),
    gsSP2Triangles(13,  8, 14, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801BC40, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 2,  8,  3, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9,  6, 12, 0x0,  9, 12, 13, 0x0),
    gsSP2Triangles( 0,  3, 14, 0x0,  0, 14, 15, 0x0),
    gsSP2Triangles(11,  2,  1, 0x0, 11,  1,  4, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801BD40, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0801D0D0 - 0x0801D360
const Gfx goomba_seg8_dl_0801D0D0[] = {
    gsSPLight(&goomba_seg8_lights_08019500.l, 1),
    gsSPLight(&goomba_seg8_lights_08019500.a, 2),
    gsSPVertex(goomba_seg8_vertex_0801BDC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801BEC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0, 10, 11,  7, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801BFB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  3,  5,  2, 0x0),
    gsSP1Triangle( 3,  2,  1, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C0A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13, 14, 0x0),
    gsSP2Triangles(10, 15, 12, 0x0, 10, 12,  0, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C1A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 11,  8, 13, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C280, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13,  2, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C360, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(10,  9, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(12,  9, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C460, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C560, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0801D360 - 0x0801D760
const Gfx goomba_seg8_dl_0801D360[] = {
    gsSPLight(&goomba_seg8_lights_08019518.l, 1),
    gsSPLight(&goomba_seg8_lights_08019518.a, 2),
    gsSPVertex(goomba_seg8_vertex_0801C620, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 12, 0x0,  5, 12,  1, 0x0),
    gsSP2Triangles( 7, 15, 14, 0x0,  7, 14,  5, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C720, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0, 10,  7,  6, 0x0),
    gsSP2Triangles( 2, 12, 11, 0x0,  2, 11, 10, 0x0),
    gsSP2Triangles( 1, 13, 12, 0x0,  1, 12,  2, 0x0),
    gsSP2Triangles( 5, 14, 13, 0x0,  5, 13,  1, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C810, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 12, 0x0,  5, 12,  1, 0x0),
    gsSP2Triangles( 7, 15, 14, 0x0,  7, 14,  5, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801C910, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0, 10,  7,  6, 0x0),
    gsSP2Triangles( 2, 12, 11, 0x0,  2, 11, 10, 0x0),
    gsSP2Triangles( 1, 13, 12, 0x0,  1, 12,  2, 0x0),
    gsSP2Triangles( 5, 14, 13, 0x0,  5, 13,  1, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801CA00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 5, 14, 12, 0x0,  5, 12,  1, 0x0),
    gsSP2Triangles( 7, 15, 14, 0x0,  7, 14,  5, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801CB00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0, 10,  7,  6, 0x0),
    gsSP2Triangles( 2, 12, 11, 0x0,  2, 11, 10, 0x0),
    gsSP2Triangles( 1, 13, 12, 0x0,  1, 12,  2, 0x0),
    gsSP2Triangles( 5, 14, 13, 0x0,  5, 13,  1, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801CBF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles( 2, 12, 13, 0x0,  2, 13, 14, 0x0),
    gsSP1Triangle( 2, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801CCF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles( 7, 11, 12, 0x0,  7, 12, 13, 0x0),
    gsSP2Triangles( 7, 13, 14, 0x0,  7, 14, 15, 0x0),
    gsSPVertex(goomba_seg8_vertex_0801CDF0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0801D760 - 0x0801D770
const Gfx goomba_seg8_dl_0801D760[] = {
    gsSPNumLights(NUMLIGHTS_1),
    gsSPEndDisplayList(),
};
