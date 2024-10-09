#include "pc/rom_assets.h"
// Flyguy

// ???
UNUSED static const u64 flyguy_unused_1 = 0;

// 0x0800E088
ROM_ASSET_LOAD_TEXTURE(flyguy_seg8_texture_0800E088, "actors/flyguy/flyguy_cloth_wrinkle.rgba16.inc.c", 0x001f2200, 59076, 0x0000e088, 4096);

// 0x0800F088
ROM_ASSET_LOAD_TEXTURE(flyguy_seg8_texture_0800F088, "actors/flyguy/flyguy_face.rgba16.inc.c", 0x001f2200, 59076, 0x0000f088, 2048);

// 0x0800F888
ROM_ASSET_LOAD_TEXTURE(flyguy_seg8_texture_0800F888, "actors/flyguy/flyguy_propeller.ia16.inc.c", 0x001f2200, 59076, 0x0000f888, 2048);

// Unreferenced light group
UNUSED static const Lights1 flyguy_lights_unused1 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x080100A0
static const Lights1 flyguy_seg8_lights_080100A0 = gdSPDefLights1(
    0x00, 0x1f, 0x33,
    0x02, 0x7f, 0xcc, 0x28, 0x28, 0x28
);

// 0x080100B8
static const Lights1 flyguy_seg8_lights_080100B8 = gdSPDefLights1(
    0x3f, 0x32, 0x08,
    0xff, 0xc8, 0x23, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 flyguy_lights_unused2 = gdSPDefLights1(
    0x3a, 0x2f, 0x04,
    0xe8, 0xbd, 0x13, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 flyguy_lights_unused3 = gdSPDefLights1(
    0x2c, 0x00, 0x00,
    0xb2, 0x00, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 flyguy_lights_unused4 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 flyguy_lights_unused5 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x08010130
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010130, 0x001f2200, 59076, 0x00010130, 256);

// 0x08010230
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010230, 0x001f2200, 59076, 0x00010230, 256);

// 0x08010330
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010330, 0x001f2200, 59076, 0x00010330, 256);

// 0x08010430
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010430, 0x001f2200, 59076, 0x00010430, 48);

// 0x08010460
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010460, 0x001f2200, 59076, 0x00010460, 256);

// 0x08010560
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010560, 0x001f2200, 59076, 0x00010560, 224);

// 0x08010640
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010640, 0x001f2200, 59076, 0x00010640, 256);

// 0x08010740
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010740, 0x001f2200, 59076, 0x00010740, 48);

// 0x08010770
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010770, 0x001f2200, 59076, 0x00010770, 208);

// 0x08010840 - 0x08010968
const Gfx flyguy_seg8_dl_08010840[] = {
    gsSPLight(&flyguy_seg8_lights_080100A0.l, 1),
    gsSPLight(&flyguy_seg8_lights_080100A0.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08010130, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 15,  1, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010230, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 7,  5,  9, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010330, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  3,  8,  4, 0x0),
    gsSP2Triangles( 1,  9,  5, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles( 0,  7, 10, 0x0,  0, 10, 11, 0x0),
    gsSP2Triangles( 3,  5, 12, 0x0,  3, 12, 13, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0, 14, 12,  5, 0x0),
    gsSP2Triangles(14,  5,  9, 0x0,  6,  8, 15, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010430, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x08010968 - 0x08010A90
const Gfx flyguy_seg8_dl_08010968[] = {
    gsSPLight(&flyguy_seg8_lights_080100A0.l, 1),
    gsSPLight(&flyguy_seg8_lights_080100A0.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08010460, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  6,  5, 0x0),
    gsSP2Triangles(11,  5, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010560, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 1,  9, 10, 0x0,  5,  6,  8, 0x0),
    gsSP2Triangles(10,  3,  2, 0x0,  2,  4, 11, 0x0),
    gsSP2Triangles( 2, 11,  0, 0x0,  8,  7, 12, 0x0),
    gsSP2Triangles(10,  9,  7, 0x0, 10,  7,  6, 0x0),
    gsSP1Triangle(13,  9,  1, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010640, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  3, 10, 12, 0x0),
    gsSP2Triangles( 3, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010740, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x08010A90 - 0x08010AE0
const Gfx flyguy_seg8_dl_08010A90[] = {
    gsSPLight(&flyguy_seg8_lights_080100B8.l, 1),
    gsSPLight(&flyguy_seg8_lights_080100B8.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08010770, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0, 10, 11, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x08010AE0
static const Lights1 flyguy_seg8_lights_08010AE0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08010AF8
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010AF8, 0x001f2200, 59076, 0x00010af8, 64);

// 0x08010B38 - 0x08010B80
const Gfx flyguy_seg8_dl_08010B38[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flyguy_seg8_texture_0800F888),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&flyguy_seg8_lights_08010AE0.l, 1),
    gsSPLight(&flyguy_seg8_lights_08010AE0.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08010AF8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08010B80 - 0x08010BF0
const Gfx flyguy_seg8_dl_08010B80[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(flyguy_seg8_dl_08010B38),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x08010BF0
static const Lights1 flyguy_seg8_lights_08010BF0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08010C08
static const Lights1 flyguy_seg8_lights_08010C08 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x08010C20
static const Lights1 flyguy_seg8_lights_08010C20 = gdSPDefLights1(
    0x62, 0x00, 0x13,
    0xc4, 0x00, 0x26, 0x28, 0x28, 0x28
);

// 0x08010C38
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010C38, 0x001f2200, 59076, 0x00010c38, 144);

// 0x08010CC8
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010CC8, 0x001f2200, 59076, 0x00010cc8, 96);

// 0x08010D28
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010D28, 0x001f2200, 59076, 0x00010d28, 224);

// 0x08010E08
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010E08, 0x001f2200, 59076, 0x00010e08, 256);

// 0x08010F08
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08010F08, 0x001f2200, 59076, 0x00010f08, 256);

// 0x08011008
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08011008, 0x001f2200, 59076, 0x00011008, 240);

// 0x080110F8
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_080110F8, 0x001f2200, 59076, 0x000110f8, 256);

// 0x080111F8
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_080111F8, 0x001f2200, 59076, 0x000111f8, 224);

// 0x080112D8
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_080112D8, 0x001f2200, 59076, 0x000112d8, 112);

// 0x08011348
ROM_ASSET_LOAD_VTX(flyguy_seg8_vertex_08011348, 0x001f2200, 59076, 0x00011348, 96);

// 0x080113A8 - 0x08011420
const Gfx flyguy_seg8_dl_080113A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, flyguy_seg8_texture_0800F088),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&flyguy_seg8_lights_08010BF0.l, 1),
    gsSPLight(&flyguy_seg8_lights_08010BF0.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08010C38, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 0,  6,  4, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  0,  5,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x08011420 - 0x080116D0
const Gfx flyguy_seg8_dl_08011420[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, flyguy_seg8_texture_0800E088),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&flyguy_seg8_lights_08010C08.l, 1),
    gsSPLight(&flyguy_seg8_lights_08010C08.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08010CC8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&flyguy_seg8_lights_08010C20.l, 1),
    gsSPLight(&flyguy_seg8_lights_08010C20.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08010D28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  5,  3, 0x0,  1,  4,  2, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 2,  4,  7, 0x0,  2,  8,  9, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10,  3,  5, 0x0),
    gsSP2Triangles(10, 12,  3, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010E08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  8,  9,  5, 0x0),
    gsSP2Triangles( 1, 10, 11, 0x0, 11,  2,  1, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13,  1, 14, 0x0),
    gsSP1Triangle( 1,  0, 15, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08010F08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10,  7,  6, 0x0),
    gsSP2Triangles(11,  6, 12, 0x0, 13, 12,  6, 0x0),
    gsSP2Triangles( 6, 11, 10, 0x0, 14,  9,  1, 0x0),
    gsSP1Triangle(10, 11, 15, 0x0),
    gsSPVertex(flyguy_seg8_vertex_08011008, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  0, 0x0,  0,  7,  3, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0,  5, 10,  8, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSPVertex(flyguy_seg8_vertex_080110F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 11, 14, 0x0, 15, 12, 14, 0x0),
    gsSPVertex(flyguy_seg8_vertex_080111F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  7,  3,  2, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 5,  9,  6, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(11, 13, 12, 0x0),
    gsSPVertex(flyguy_seg8_vertex_080112D8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 4,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x080116D0 - 0x08011710
const Gfx flyguy_seg8_dl_080116D0[] = {
    gsSPLight(&flyguy_seg8_lights_08010C08.l, 1),
    gsSPLight(&flyguy_seg8_lights_08010C08.a, 2),
    gsSPVertex(flyguy_seg8_vertex_08011348, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x08011710 - 0x08011798
const Gfx flyguy_seg8_dl_08011710[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(flyguy_seg8_dl_080113A8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(flyguy_seg8_dl_08011420),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(flyguy_seg8_dl_080116D0),
    gsSPEndDisplayList(),
};
