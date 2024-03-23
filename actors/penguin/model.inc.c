#include "pc/rom_assets.h"
// Penguin

// 0x05002D80
static const Lights1 penguin_seg5_lights_05002D80 = gdSPDefLights1(
    0x06, 0x06, 0x39,
    0x0f, 0x0f, 0x90, 0x28, 0x28, 0x28
);

// 0x05002D98
static const Lights1 penguin_seg5_lights_05002D98 = gdSPDefLights1(
    0x52, 0x34, 0x0a,
    0xce, 0x84, 0x1a, 0x28, 0x28, 0x28
);

// 0x05002DB0
static const Lights1 penguin_seg5_lights_05002DB0 = gdSPDefLights1(
    0x59, 0x42, 0x14,
    0xdf, 0xa7, 0x34, 0x28, 0x28, 0x28
);

// 0x05002DC8
static const Lights1 penguin_seg5_lights_05002DC8 = gdSPDefLights1(
    0x66, 0x66, 0x65,
    0xff, 0xff, 0xfd, 0x28, 0x28, 0x28
);

// 0x05002DE0
ROM_ASSET_LOAD_TEXTURE(penguin_seg5_texture_05002DE0, "actors/penguin/penguin_eye_open.rgba16.inc.c", 0x00160670, 20585, 0x00002de0, 2048);

// 0x050035E0
ROM_ASSET_LOAD_TEXTURE(penguin_seg5_texture_050035E0, "actors/penguin/penguin_eye_half_closed.rgba16.inc.c", 0x00160670, 20585, 0x000035e0, 2048);

// 0x05003DE0
ROM_ASSET_LOAD_TEXTURE(penguin_seg5_texture_05003DE0, "actors/penguin/penguin_eye_closed.rgba16.inc.c", 0x00160670, 20585, 0x00003de0, 2048);

// 0x050045E0
ROM_ASSET_LOAD_TEXTURE(penguin_seg5_texture_050045E0, "actors/penguin/penguin_eye_angry.rgba16.inc.c", 0x00160670, 20585, 0x000045e0, 2048);

// 0x05004DE0
ROM_ASSET_LOAD_TEXTURE(penguin_seg5_texture_05004DE0, "actors/penguin/penguin_eye_angry_unused.rgba16.inc.c", 0x00160670, 20585, 0x00004de0, 2048);

// 0x050055E0
ROM_ASSET_LOAD_TEXTURE(penguin_seg5_texture_050055E0, "actors/penguin/penguin_beak.rgba16.inc.c", 0x00160670, 20585, 0x000055e0, 2048);

// 0x05005DE0
static const Lights1 penguin_seg5_lights_05005DE0 = gdSPDefLights1(
    0x04, 0x0f, 0x41,
    0x0b, 0x26, 0xa4, 0x28, 0x28, 0x28
);

// 0x05005DF8
static const Lights1 penguin_seg5_lights_05005DF8 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05005E10
static const Lights1 penguin_seg5_lights_05005E10 = gdSPDefLights1(
    0x60, 0x55, 0x0b,
    0xf2, 0xd5, 0x1c, 0x28, 0x28, 0x28
);

// 0x05005E28
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05005E28, 0x00160670, 20585, 0x00005e28, 128);

// 0x05005EA8
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05005EA8, 0x00160670, 20585, 0x00005ea8, 64);

// 0x05005EE8
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05005EE8, 0x00160670, 20585, 0x00005ee8, 256);

// 0x05005FE8
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05005FE8, 0x00160670, 20585, 0x00005fe8, 256);

// 0x050060E8
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_050060E8, 0x00160670, 20585, 0x000060e8, 112);

// 0x05006158
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006158, 0x00160670, 20585, 0x00006158, 48);

// 0x05006188 - 0x050061C8
const Gfx penguin_seg5_dl_05006188[] = {
    gsSPLight(&penguin_seg5_lights_05005DE0.l, 1),
    gsSPLight(&penguin_seg5_lights_05005DE0.a, 2),
    gsSPVertex(penguin_seg5_vertex_05005E28, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x050061C8 - 0x050061F8
const Gfx penguin_seg5_dl_050061C8[] = {
    gsSPLight(&penguin_seg5_lights_05005DF8.l, 1),
    gsSPLight(&penguin_seg5_lights_05005DF8.a, 2),
    gsSPVertex(penguin_seg5_vertex_05005EA8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x050061F8 - 0x05006380
const Gfx penguin_seg5_dl_050061F8[] = {
    gsSPLight(&penguin_seg5_lights_05005DE0.l, 1),
    gsSPLight(&penguin_seg5_lights_05005DE0.a, 2),
    gsSPVertex(penguin_seg5_vertex_05005EE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  1,  4,  6, 0x0),
    gsSP2Triangles( 6,  3,  1, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  4,  5,  9, 0x0),
    gsSP2Triangles( 4,  8,  6, 0x0,  9,  7,  4, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0, 10,  3,  6, 0x0),
    gsSP2Triangles(11,  8,  7, 0x0, 12,  2,  3, 0x0),
    gsSP2Triangles(13, 11,  7, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(penguin_seg5_vertex_05005FE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  6,  2, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9,  3, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  0,  3,  9, 0x0),
    gsSP2Triangles( 5,  4, 10, 0x0, 11,  0,  9, 0x0),
    gsSP2Triangles(11,  1,  0, 0x0, 12,  1, 11, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(15, 12, 14, 0x0),
    gsSPVertex(penguin_seg5_vertex_050060E8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  2,  3, 0x0),
    gsSP2Triangles( 2,  5,  4, 0x0,  4,  5,  6, 0x0),
    gsSPLight(&penguin_seg5_lights_05005E10.l, 1),
    gsSPLight(&penguin_seg5_lights_05005E10.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006158, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006380 - 0x050063C8
const Gfx penguin_seg5_dl_05006380[] = {
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBA, G_CC_BLENDRGBA),
    gsSPEndDisplayList(),
};

// 0x050063C8 - 0x05006428
const Gfx penguin_seg5_dl_050063C8[] = {
    gsSPDisplayList(penguin_seg5_dl_05006188),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, penguin_seg5_texture_050055E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(penguin_seg5_dl_050061C8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(penguin_seg5_dl_050061F8),
    gsSPEndDisplayList(),
};

// 0x05006428 - 0x05006458
const Gfx penguin_seg5_dl_05006428[] = {
    gsSPDisplayList(penguin_seg5_dl_05006380),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, penguin_seg5_texture_05002DE0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(penguin_seg5_dl_050063C8),
    gsSPEndDisplayList(),
};

// 0x05006458 - 0x05006488
const Gfx penguin_seg5_dl_05006458[] = {
    gsSPDisplayList(penguin_seg5_dl_05006380),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, penguin_seg5_texture_050035E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(penguin_seg5_dl_050063C8),
    gsSPEndDisplayList(),
};

// 0x05006488 - 0x050064B8
const Gfx penguin_seg5_dl_05006488[] = {
    gsSPDisplayList(penguin_seg5_dl_05006380),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, penguin_seg5_texture_05003DE0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(penguin_seg5_dl_050063C8),
    gsSPEndDisplayList(),
};

// 0x050064B8 - 0x050064E8
const Gfx penguin_seg5_dl_050064B8[] = {
    gsSPDisplayList(penguin_seg5_dl_05006380),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, penguin_seg5_texture_050045E0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(penguin_seg5_dl_050063C8),
    gsSPEndDisplayList(),
};

// 0x050064E8 - 0x05006518
const Gfx penguin_seg5_dl_050064E8[] = {
    gsSPDisplayList(penguin_seg5_dl_05006380),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, penguin_seg5_texture_05004DE0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(penguin_seg5_dl_050063C8),
    gsSPEndDisplayList(),
};

// 0x05006518
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006518, 0x00160670, 20585, 0x00006518, 160);

// 0x050065B8
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_050065B8, 0x00160670, 20585, 0x000065b8, 160);

// 0x05006658
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006658, 0x00160670, 20585, 0x00006658, 240);

// 0x05006748
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006748, 0x00160670, 20585, 0x00006748, 240);

// 0x05006838
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006838, 0x00160670, 20585, 0x00006838, 80);

// 0x05006888
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006888, 0x00160670, 20585, 0x00006888, 256);

// 0x05006988
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006988, 0x00160670, 20585, 0x00006988, 240);

// 0x05006A78
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006A78, 0x00160670, 20585, 0x00006a78, 240);

// 0x05006B68
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006B68, 0x00160670, 20585, 0x00006b68, 256);

// 0x05006C68
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006C68, 0x00160670, 20585, 0x00006c68, 256);

// 0x05006D68
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006D68, 0x00160670, 20585, 0x00006d68, 128);

// 0x05006DE8
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006DE8, 0x00160670, 20585, 0x00006de8, 64);

// 0x05006E28
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006E28, 0x00160670, 20585, 0x00006e28, 240);

// 0x05006F18
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05006F18, 0x00160670, 20585, 0x00006f18, 256);

// 0x05007018
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_05007018, 0x00160670, 20585, 0x00007018, 144);

// 0x050070A8
ROM_ASSET_LOAD_VTX(penguin_seg5_vertex_050070A8, 0x00160670, 20585, 0x000070a8, 240);

// 0x05007198 - 0x050071E8
const Gfx penguin_seg5_dl_05007198[] = {
    gsSPLight(&penguin_seg5_lights_05002D80.l, 1),
    gsSPLight(&penguin_seg5_lights_05002D80.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006518, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0,  0,  9,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x050071E8 - 0x05007238
const Gfx penguin_seg5_dl_050071E8[] = {
    gsSPLight(&penguin_seg5_lights_05002D80.l, 1),
    gsSPLight(&penguin_seg5_lights_05002D80.a, 2),
    gsSPVertex(penguin_seg5_vertex_050065B8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05007238 - 0x050072C8
const Gfx penguin_seg5_dl_05007238[] = {
    gsSPLight(&penguin_seg5_lights_05002D98.l, 1),
    gsSPLight(&penguin_seg5_lights_05002D98.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006658, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 1,  4,  6, 0x0,  1,  6,  2, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  1,  0,  4, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  2, 12,  0, 0x0),
    gsSP2Triangles( 0, 12,  3, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0,  9, 14, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x050072C8 - 0x05007358
const Gfx penguin_seg5_dl_050072C8[] = {
    gsSPLight(&penguin_seg5_lights_05002D98.l, 1),
    gsSPLight(&penguin_seg5_lights_05002D98.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006748, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  5, 11, 0x0,  8, 12,  9, 0x0),
    gsSP2Triangles( 6,  2, 11, 0x0,  2, 10, 11, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  2,  1, 10, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0,  6, 11,  5, 0x0),
    gsSP2Triangles( 8, 13, 12, 0x0,  7, 14,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05007358 - 0x05007540
const Gfx penguin_seg5_dl_05007358[] = {
    gsSPLight(&penguin_seg5_lights_05002DB0.l, 1),
    gsSPLight(&penguin_seg5_lights_05002DB0.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006838, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 1,  4,  3, 0x0),
    gsSPLight(&penguin_seg5_lights_05002D80.l, 1),
    gsSPLight(&penguin_seg5_lights_05002D80.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006888, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  0, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles( 9,  4,  1, 0x0,  3, 14, 15, 0x0),
    gsSPVertex(penguin_seg5_vertex_05006988, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  7, 0x0, 14,  0,  2, 0x0),
    gsSPVertex(penguin_seg5_vertex_05006A78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 14, 0x0),
    gsSPVertex(penguin_seg5_vertex_05006B68, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11,  1,  6, 0x0, 12,  2, 13, 0x0),
    gsSP2Triangles( 3,  7,  4, 0x0, 14, 15,  1, 0x0),
    gsSPVertex(penguin_seg5_vertex_05006C68, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  2, 10, 0x0),
    gsSP2Triangles( 4,  7, 11, 0x0,  8,  4,  3, 0x0),
    gsSP2Triangles( 0,  9,  6, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(15, 12,  1, 0x0),
    gsSPVertex(penguin_seg5_vertex_05006D68, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSPLight(&penguin_seg5_lights_05002D80.l, 1),
    gsSPLight(&penguin_seg5_lights_05002D80.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006DE8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05007540 - 0x05007708
const Gfx penguin_seg5_dl_05007540[] = {
    gsSPLight(&penguin_seg5_lights_05002D80.l, 1),
    gsSPLight(&penguin_seg5_lights_05002D80.a, 2),
    gsSPVertex(penguin_seg5_vertex_05006E28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  2,  9,  6, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  4, 10,  5, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0,  5, 11,  1, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0, 10,  9,  2, 0x0),
    gsSP1Triangle( 3, 14,  4, 0x0),
    gsSPVertex(penguin_seg5_vertex_05006F18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  1, 0x0),
    gsSP2Triangles(11,  8, 12, 0x0, 13,  5,  4, 0x0),
    gsSP2Triangles( 0, 14, 15, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 6, 11,  2, 0x0,  1,  0,  5, 0x0),
    gsSP2Triangles( 1, 10,  6, 0x0,  6,  2,  1, 0x0),
    gsSP2Triangles( 5, 13,  1, 0x0,  2, 12, 14, 0x0),
    gsSPVertex(penguin_seg5_vertex_05007018, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  2,  8, 0x0),
    gsSPLight(&penguin_seg5_lights_05002DC8.l, 1),
    gsSPLight(&penguin_seg5_lights_05002DC8.a, 2),
    gsSPVertex(penguin_seg5_vertex_050070A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  2,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  9,  2,  7, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0, 13,  9, 10, 0x0),
    gsSP2Triangles( 2,  1,  7, 0x0, 13, 10, 14, 0x0),
    gsSP2Triangles(14, 10,  8, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles(13,  6,  2, 0x0,  3,  7,  1, 0x0),
    gsSP2Triangles(11,  8,  3, 0x0, 12, 14,  8, 0x0),
    gsSP1Triangle( 2,  9, 13, 0x0),
    gsSPEndDisplayList(),
};
