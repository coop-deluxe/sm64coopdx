#include "pc/rom_assets.h"
// 0x070081A8 - 0x070081C0
static const Lights1 jrb_seg7_lights_070081A8 = gdSPDefLights1(
    0x1e, 0x2c, 0x3a,
    0x79, 0xb2, 0xeb, 0x28, 0x28, 0x28
);

// 0x070081C0 - 0x070081D8
static const Lights1 jrb_seg7_lights_070081C0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070081D8 - 0x070082C8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070081D8, 0x0041a760, 37817, 0x000081d8, 240);

// 0x070082C8 - 0x070083B8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070082C8, 0x0041a760, 37817, 0x000082c8, 240);

// 0x070083B8 - 0x07008478
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070083B8, 0x0041a760, 37817, 0x000083b8, 192);

// 0x07008478 - 0x07008578
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07008478, 0x0041a760, 37817, 0x00008478, 256);

// 0x07008578 - 0x07008668
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07008578, 0x0041a760, 37817, 0x00008578, 240);

// 0x07008668 - 0x070086C8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07008668, 0x0041a760, 37817, 0x00008668, 96);

// 0x070086C8 - 0x070087B8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070086C8, 0x0041a760, 37817, 0x000086c8, 240);

// 0x070087B8 - 0x070088A8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070087B8, 0x0041a760, 37817, 0x000087b8, 240);

// 0x070088A8 - 0x070089A8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070088A8, 0x0041a760, 37817, 0x000088a8, 256);

// 0x070089A8 - 0x07008A98
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070089A8, 0x0041a760, 37817, 0x000089a8, 240);

// 0x07008A98 - 0x07008AC8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07008A98, 0x0041a760, 37817, 0x00008a98, 48);

// 0x07008AC8 - 0x07008B88
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07008AC8, 0x0041a760, 37817, 0x00008ac8, 192);

// 0x07008B88 - 0x07008C90
static const Gfx jrb_seg7_dl_07008B88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070081A8.l, 1),
    gsSPLight(&jrb_seg7_lights_070081A8.a, 2),
    gsSPVertex(jrb_seg7_vertex_070081D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(jrb_seg7_vertex_070082C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(jrb_seg7_vertex_070083B8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 4, 11, 10, 0x0,  4, 10,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008C90 - 0x07008DD0
static const Gfx jrb_seg7_dl_07008C90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070081C0.l, 1),
    gsSPLight(&jrb_seg7_lights_070081C0.a, 2),
    gsSPVertex(jrb_seg7_vertex_07008478, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles( 5,  7,  1, 0x0,  6, 10, 11, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0,  6, 11,  7, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0,  7, 11, 12, 0x0),
    gsSP2Triangles( 7,  2,  1, 0x0,  7, 13,  2, 0x0),
    gsSP2Triangles(13,  4,  2, 0x0, 13, 12,  4, 0x0),
    gsSP2Triangles( 9, 14,  8, 0x0,  9, 15, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07008578, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  1,  3,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12,  4, 13, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 4,  6, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07008668, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008DD0 - 0x07008F70
static const Gfx jrb_seg7_dl_07008DD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_070086C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  6,  3,  9, 0x0),
    gsSP2Triangles( 6,  9,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 3, 10,  9, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070087B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(jrb_seg7_vertex_070088A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  3,  6, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles(10,  1,  0, 0x0, 10, 11,  1, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_070089A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 6,  3,  0, 0x0,  3,  8,  4, 0x0),
    gsSP2Triangles( 9,  3,  6, 0x0,  9, 10,  3, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07008A98, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008F70 - 0x07008FD8
static const Gfx jrb_seg7_dl_07008F70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_07008AC8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles( 9, 11,  6, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008FD8 - 0x070090B0
const Gfx jrb_seg7_dl_07008FD8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07008B88),
    gsSPDisplayList(jrb_seg7_dl_07008C90),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07008DD0),
    gsSPDisplayList(jrb_seg7_dl_07008F70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x070090B0 - 0x07009190
const Gfx jrb_seg7_dl_070090B0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07008B88),
    gsSPDisplayList(jrb_seg7_dl_07008C90),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07008DD0),
    gsSPDisplayList(jrb_seg7_dl_07008F70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x07009190 - 0x070091A8
static const Lights1 jrb_seg7_lights_07009190 = gdSPDefLights1(
    0x1e, 0x2c, 0x3a,
    0x79, 0xb2, 0xeb, 0x28, 0x28, 0x28
);

// 0x070091A8 - 0x070091C0
static const Lights1 jrb_seg7_lights_070091A8 = gdSPDefLights1(
    0x19, 0x2c, 0x3f,
    0x65, 0xb2, 0xff, 0x28, 0x28, 0x28
);

// 0x070091C0 - 0x070091D8
static const Lights1 jrb_seg7_lights_070091C0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070091D8 - 0x07009218
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070091D8, 0x0041a760, 37817, 0x000091d8, 64);

// 0x07009218 - 0x07009258
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009218, 0x0041a760, 37817, 0x00009218, 64);

// 0x07009258 - 0x07009358
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009258, 0x0041a760, 37817, 0x00009258, 256);

// 0x07009358 - 0x070093A8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009358, 0x0041a760, 37817, 0x00009358, 80);

// 0x070093A8 - 0x07009488
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070093A8, 0x0041a760, 37817, 0x000093a8, 224);

// 0x07009488 - 0x07009588
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009488, 0x0041a760, 37817, 0x00009488, 256);

// 0x07009588 - 0x07009688
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009588, 0x0041a760, 37817, 0x00009588, 256);

// 0x07009688 - 0x07009738
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009688, 0x0041a760, 37817, 0x00009688, 176);

// 0x07009738 - 0x07009798
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009738, 0x0041a760, 37817, 0x00009738, 96);

// 0x07009798 - 0x07009808
static const Gfx jrb_seg7_dl_07009798[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_07009190.l, 1),
    gsSPLight(&jrb_seg7_lights_07009190.a, 2),
    gsSPVertex(jrb_seg7_vertex_070091D8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&jrb_seg7_lights_070091A8.l, 1),
    gsSPLight(&jrb_seg7_lights_070091A8.a, 2),
    gsSPVertex(jrb_seg7_vertex_07009218, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009808 - 0x070098C0
static const Gfx jrb_seg7_dl_07009808[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070091C0.l, 1),
    gsSPLight(&jrb_seg7_lights_070091C0.a, 2),
    gsSPVertex(jrb_seg7_vertex_07009258, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11,  1, 12, 0x0),
    gsSP2Triangles(11, 13,  1, 0x0, 14,  1,  0, 0x0),
    gsSP2Triangles(14, 12,  1, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07009358, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 2,  4,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070098C0 - 0x07009A10
static const Gfx jrb_seg7_dl_070098C0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_070093A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07009488, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  7,  4, 0x0,  9,  4,  3, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0, 10,  5,  6, 0x0),
    gsSP2Triangles(11,  0,  2, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13,  2, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07009588, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  3,  1, 0x0,  5,  3,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  6, 13, 0x0, 14, 15,  2, 0x0),
    gsSPVertex(jrb_seg7_vertex_07009688, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 3,  0,  5, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 5,  2,  6, 0x0,  5,  6,  7, 0x0),
    gsSP1Triangle( 8,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009A10 - 0x07009A58
static const Gfx jrb_seg7_dl_07009A10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_07009738, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009A58 - 0x07009B30
const Gfx jrb_seg7_dl_07009A58[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07009798),
    gsSPDisplayList(jrb_seg7_dl_07009808),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070098C0),
    gsSPDisplayList(jrb_seg7_dl_07009A10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x07009B30 - 0x07009C10
const Gfx jrb_seg7_dl_07009B30[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_07009798),
    gsSPDisplayList(jrb_seg7_dl_07009808),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070098C0),
    gsSPDisplayList(jrb_seg7_dl_07009A10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x07009C10 - 0x07009C28
static const Lights1 jrb_seg7_lights_07009C10 = gdSPDefLights1(
    0x1e, 0x2c, 0x3a,
    0x79, 0xb2, 0xeb, 0x28, 0x28, 0x28
);

// 0x07009C28 - 0x07009C40
static const Lights1 jrb_seg7_lights_07009C28 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07009C40 - 0x07009C58
static const Lights1 jrb_seg7_lights_07009C40 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07009C58 - 0x07009D48
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009C58, 0x0041a760, 37817, 0x00009c58, 240);

// 0x07009D48 - 0x07009E38
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009D48, 0x0041a760, 37817, 0x00009d48, 240);

// 0x07009E38 - 0x07009F38
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009E38, 0x0041a760, 37817, 0x00009e38, 256);

// 0x07009F38 - 0x07009FC8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009F38, 0x0041a760, 37817, 0x00009f38, 144);

// 0x07009FC8 - 0x0700A048
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07009FC8, 0x0041a760, 37817, 0x00009fc8, 128);

// 0x0700A048 - 0x0700A128
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700A048, 0x0041a760, 37817, 0x0000a048, 224);

// 0x0700A128 - 0x0700A228
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700A128, 0x0041a760, 37817, 0x0000a128, 256);

// 0x0700A228 - 0x0700A2F8
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700A228, 0x0041a760, 37817, 0x0000a228, 208);

// 0x0700A2F8 - 0x0700A3A8
static const Gfx jrb_seg7_dl_0700A2F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_07009C10.l, 1),
    gsSPLight(&jrb_seg7_lights_07009C10.a, 2),
    gsSPVertex(jrb_seg7_vertex_07009C58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(jrb_seg7_vertex_07009D48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A3A8 - 0x0700A470
static const Gfx jrb_seg7_dl_0700A3A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_07009C28.l, 1),
    gsSPLight(&jrb_seg7_lights_07009C28.a, 2),
    gsSPVertex(jrb_seg7_vertex_07009E38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  8,  3, 0x0,  6,  7,  9, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0,  0, 12, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 1, 14, 13, 0x0,  7, 15,  9, 0x0),
    gsSPVertex(jrb_seg7_vertex_07009F38, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP1Triangle( 5,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A470 - 0x0700A608
static const Gfx jrb_seg7_dl_0700A470[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_07009C40.l, 1),
    gsSPLight(&jrb_seg7_lights_07009C40.a, 2),
    gsSPVertex(jrb_seg7_vertex_07009FC8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  7,  1,  3, 0x0),
    gsSP2Triangles( 7,  2,  1, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  6,  3,  4, 0x0),
    gsSPLight(&jrb_seg7_lights_07009C28.l, 1),
    gsSPLight(&jrb_seg7_lights_07009C28.a, 2),
    gsSPVertex(jrb_seg7_vertex_0700A048, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  5,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700A128, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700A228, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 5,  0,  3, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 7,  5,  9, 0x0,  8,  6,  5, 0x0),
    gsSP2Triangles( 9,  5,  3, 0x0,  9,  3, 10, 0x0),
    gsSP2Triangles( 8, 11,  6, 0x0, 10,  3, 12, 0x0),
    gsSP1Triangle( 3,  4, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A608 - 0x0700A6D8
const Gfx jrb_seg7_dl_0700A608[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_0700A2F8),
    gsSPDisplayList(jrb_seg7_dl_0700A3A8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_0700A470),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0700A6D8 - 0x0700A6F0
static const Lights1 jrb_seg7_lights_0700A6D8 = gdSPDefLights1(
    0x1e, 0x2c, 0x3a,
    0x79, 0xb2, 0xeb, 0x28, 0x28, 0x28
);

// 0x0700A6F0 - 0x0700A708
static const Lights1 jrb_seg7_lights_0700A6F0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700A708 - 0x0700A748
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700A708, 0x0041a760, 37817, 0x0000a708, 64);

// 0x0700A748 - 0x0700A838
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700A748, 0x0041a760, 37817, 0x0000a748, 240);

// 0x0700A838 - 0x0700A938
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700A838, 0x0041a760, 37817, 0x0000a838, 256);

// 0x0700A938 - 0x0700AA18
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700A938, 0x0041a760, 37817, 0x0000a938, 224);

// 0x0700AA18 - 0x0700AA98
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_0700AA18, 0x0041a760, 37817, 0x0000aa18, 128);

// 0x0700AA98 - 0x0700AAE0
static const Gfx jrb_seg7_dl_0700AA98[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_0700A6D8.l, 1),
    gsSPLight(&jrb_seg7_lights_0700A6D8.a, 2),
    gsSPVertex(jrb_seg7_vertex_0700A708, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AAE0 - 0x0700AB60
static const Gfx jrb_seg7_dl_0700AAE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_0700A6F0.l, 1),
    gsSPLight(&jrb_seg7_lights_0700A6F0.a, 2),
    gsSPVertex(jrb_seg7_vertex_0700A748, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 10, 13, 12, 0x0),
    gsSP1Triangle( 9, 11, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AB60 - 0x0700AC68
static const Gfx jrb_seg7_dl_0700AB60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_0700A838, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  3,  7,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  3,  1,  8, 0x0),
    gsSP2Triangles( 6,  3,  8, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 7,  5,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 14,  8,  1, 0x0),
    gsSP2Triangles(15, 14,  0, 0x0,  0, 14,  1, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700A938, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles(12, 10,  7, 0x0,  7, 10,  8, 0x0),
    gsSPVertex(jrb_seg7_vertex_0700AA18, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AC68 - 0x0700AD38
const Gfx jrb_seg7_dl_0700AC68[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_0700AA98),
    gsSPDisplayList(jrb_seg7_dl_0700AAE0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_0700AB60),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
