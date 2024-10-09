#include "pc/rom_assets.h"
// Piranha Plant

// 0x060113B0
static const Lights1 piranha_plant_seg6_lights_060113B0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060113C8
static const Lights1 piranha_plant_seg6_lights_060113C8 = gdSPDefLights1(
    0x0a, 0x2b, 0x02,
    0x2b, 0xae, 0x0a, 0x28, 0x28, 0x28
);

// 0x060113E0
static const Lights1 piranha_plant_seg6_lights_060113E0 = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x060113F8
ROM_ASSET_LOAD_TEXTURE(piranha_plant_seg6_texture_060113F8, "actors/piranha_plant/piranha_plant_tongue.rgba16.inc.c", 0x00188440, 199722, 0x00024438, 4096);

// 0x060123F8
ROM_ASSET_LOAD_TEXTURE(piranha_plant_seg6_texture_060123F8, "actors/piranha_plant/piranha_plant_skin.rgba16.inc.c", 0x001c4230, 80474, 0x000123f8, 2048);

// 0x06012BF8
ROM_ASSET_LOAD_TEXTURE(piranha_plant_seg6_texture_06012BF8, "actors/piranha_plant/piranha_plant_stem.rgba16.inc.c", 0x001c4230, 80474, 0x00012bf8, 2048);

// 0x060133F8
ROM_ASSET_LOAD_TEXTURE(piranha_plant_seg6_texture_060133F8, "actors/piranha_plant/piranha_plant_bottom_lip.rgba16.inc.c", 0x001c4230, 80474, 0x000133f8, 2048);

// 0x06013BF8
ROM_ASSET_LOAD_TEXTURE(piranha_plant_seg6_texture_06013BF8, "actors/piranha_plant/piranha_plant_tooth.rgba16.inc.c", 0x001c4230, 80474, 0x00013bf8, 2048);

// 0x060143F8
ROM_ASSET_LOAD_TEXTURE(piranha_plant_seg6_texture_060143F8, "actors/piranha_plant/piranha_plant_leaf.rgba16.inc.c", 0x001c4230, 80474, 0x000143f8, 4096);

// 0x060153F8
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_060153F8, 0x001c4230, 80474, 0x000153f8, 64);

// 0x06015438 - 0x06015480
const Gfx piranha_plant_seg6_dl_06015438[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_060143F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_060153F8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06015480 - 0x060154F0
const Gfx piranha_plant_seg6_dl_06015480[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06015438),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x060154F0
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_060154F0, 0x001c4230, 80474, 0x000154f0, 64);

// 0x06015530 - 0x06015578
const Gfx piranha_plant_seg6_dl_06015530[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_060143F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_060154F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06015578 - 0x060155E8
const Gfx piranha_plant_seg6_dl_06015578[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06015530),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x060155E8
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_060155E8, 0x001c4230, 80474, 0x000155e8, 224);

// 0x060156C8
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_060156C8, 0x001c4230, 80474, 0x000156c8, 208);

// 0x06015798 - 0x06015850
const Gfx piranha_plant_seg6_dl_06015798[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_06012BF8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_060155E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(piranha_plant_seg6_vertex_060156C8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11,  1,  0, 0x0),
    gsSP1Triangle(11, 12,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06015850 - 0x060158B0
const Gfx piranha_plant_seg6_dl_06015850[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06015798),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x060158B0
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_060158B0, 0x001c4230, 80474, 0x000158b0, 224);

// 0x06015990
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06015990, 0x001c4230, 80474, 0x00015990, 240);

// 0x06015A80
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06015A80, 0x001c4230, 80474, 0x00015a80, 192);

// 0x06015B40
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06015B40, 0x001c4230, 80474, 0x00015b40, 256);

// 0x06015C40
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06015C40, 0x001c4230, 80474, 0x00015c40, 256);

// 0x06015D40
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06015D40, 0x001c4230, 80474, 0x00015d40, 128);

// 0x06015DC0
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06015DC0, 0x001c4230, 80474, 0x00015dc0, 128);

// 0x06015E40 - 0x06015EA8
const Gfx piranha_plant_seg6_dl_06015E40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_06013BF8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_060158B0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x06015EA8 - 0x06015F68
const Gfx piranha_plant_seg6_dl_06015EA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_060133F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113C8.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113C8.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06015990, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  3,  5,  8, 0x0),
    gsSP2Triangles( 3,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14,  9, 0x0),
    gsSP1Triangle( 9, 12, 13, 0x0),
    gsSPVertex(piranha_plant_seg6_vertex_06015A80, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 0,  2,  9, 0x0,  9, 10,  0, 0x0),
    gsSP1Triangle( 9, 11, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x06015F68 - 0x06016060
const Gfx piranha_plant_seg6_dl_06015F68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_060123F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06015B40, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0, 12, 13, 15, 0x0),
    gsSPVertex(piranha_plant_seg6_vertex_06015C40, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles(14, 15, 12, 0x0, 13, 14, 12, 0x0),
    gsSPVertex(piranha_plant_seg6_vertex_06015D40, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016060 - 0x060160B0
const Gfx piranha_plant_seg6_dl_06016060[] = {
    gsSPLight(&piranha_plant_seg6_lights_060113E0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113E0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06015DC0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  2,  1,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x060160B0 - 0x06016120
const Gfx piranha_plant_seg6_dl_060160B0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06015EA8),
    gsSPDisplayList(piranha_plant_seg6_dl_06015F68),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(piranha_plant_seg6_dl_06016060),
    gsSPEndDisplayList(),
};

// 0x06016120 - 0x06016190
const Gfx piranha_plant_seg6_dl_06016120[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06015E40),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x06016190
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016190, 0x001c4230, 80474, 0x00016190, 224);

// 0x06016270
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016270, 0x001c4230, 80474, 0x00016270, 240);

// 0x06016360
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016360, 0x001c4230, 80474, 0x00016360, 256);

// 0x06016460
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016460, 0x001c4230, 80474, 0x00016460, 48);

// 0x06016490
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016490, 0x001c4230, 80474, 0x00016490, 240);

// 0x06016580
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016580, 0x001c4230, 80474, 0x00016580, 256);

// 0x06016680
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016680, 0x001c4230, 80474, 0x00016680, 96);

// 0x060166E0
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_060166E0, 0x001c4230, 80474, 0x000166e0, 112);

// 0x06016750 - 0x060167B8
const Gfx piranha_plant_seg6_dl_06016750[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_06013BF8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06016190, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x060167B8 - 0x06016890
const Gfx piranha_plant_seg6_dl_060167B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_060133F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113C8.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113C8.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06016270, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 10,  9, 0x0,  9, 13, 12, 0x0),
    gsSP1Triangle(11, 14,  9, 0x0),
    gsSPVertex(piranha_plant_seg6_vertex_06016360, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles( 2, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(piranha_plant_seg6_vertex_06016460, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016890 - 0x06016960
const Gfx piranha_plant_seg6_dl_06016890[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_060123F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06016490, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(piranha_plant_seg6_vertex_06016580, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016960 - 0x060169A8
const Gfx piranha_plant_seg6_dl_06016960[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_060113F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(piranha_plant_seg6_vertex_06016680, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x060169A8 - 0x060169E8
const Gfx piranha_plant_seg6_dl_060169A8[] = {
    gsSPLight(&piranha_plant_seg6_lights_060113C8.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113C8.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_060166E0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  5,  4,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x060169E8 - 0x06016A78
const Gfx piranha_plant_seg6_dl_060169E8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_060167B8),
    gsSPDisplayList(piranha_plant_seg6_dl_06016890),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06016960),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(piranha_plant_seg6_dl_060169A8),
    gsSPEndDisplayList(),
};

// 0x06016A78 - 0x06016AE8
const Gfx piranha_plant_seg6_dl_06016A78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06016750),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x06016AE8
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016AE8, 0x001c4230, 80474, 0x00016ae8, 192);

// 0x06016BA8 - 0x06016C10
const Gfx piranha_plant_seg6_dl_06016BA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_06012BF8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06016AE8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016C10 - 0x06016C70
const Gfx piranha_plant_seg6_dl_06016C10[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06016BA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06016C70
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016C70, 0x001c4230, 80474, 0x00016c70, 192);

// 0x06016D30 - 0x06016D98
const Gfx piranha_plant_seg6_dl_06016D30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_06012BF8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06016C70, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016D98 - 0x06016DF8
const Gfx piranha_plant_seg6_dl_06016D98[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06016D30),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06016DF8
ROM_ASSET_LOAD_VTX(piranha_plant_seg6_vertex_06016DF8, 0x001c4230, 80474, 0x00016df8, 192);

// 0x06016EB8 - 0x06016F20
const Gfx piranha_plant_seg6_dl_06016EB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, piranha_plant_seg6_texture_06012BF8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.l, 1),
    gsSPLight(&piranha_plant_seg6_lights_060113B0.a, 2),
    gsSPVertex(piranha_plant_seg6_vertex_06016DF8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016F20 - 0x06016F80
const Gfx piranha_plant_seg6_dl_06016F20[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(piranha_plant_seg6_dl_06016EB8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
