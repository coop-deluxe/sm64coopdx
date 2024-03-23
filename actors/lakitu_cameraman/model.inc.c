#include "pc/rom_assets.h"
// Lakitu (Cameraman)

// 0x06000000
ROM_ASSET_LOAD_TEXTURE(lakitu_seg6_texture_06000000, "actors/lakitu_cameraman/lakitu_cameraman_cloud_face_unused.rgba16.inc.c", 0x00180bb0, 29674, 0x0000ece0, 2048);

// 0x06000800
ROM_ASSET_LOAD_TEXTURE(lakitu_seg6_texture_06000800, "actors/lakitu_cameraman/lakitu_cameraman_eyes_open.rgba16.inc.c", 0x00180bb0, 29674, 0x0000f4e0, 4096);

// 0x06001800
ROM_ASSET_LOAD_TEXTURE(lakitu_seg6_texture_06001800, "actors/lakitu_cameraman/lakitu_cameraman_eyes_closed.rgba16.inc.c", 0x00180bb0, 29674, 0x000104e0, 4096);

// 0x06002800
ROM_ASSET_LOAD_TEXTURE(lakitu_seg6_texture_06002800, "actors/lakitu_cameraman/lakitu_cameraman_shell.rgba16.inc.c", 0x00180bb0, 29674, 0x000114e0, 2048);

// 0x06003000
ROM_ASSET_LOAD_TEXTURE(lakitu_seg6_texture_06003000, "actors/lakitu_cameraman/lakitu_cameraman_frown.rgba16.inc.c", 0x00180bb0, 29674, 0x00011ce0, 2048);

// 0x06003800
ROM_ASSET_LOAD_TEXTURE(lakitu_seg6_texture_06003800, "actors/lakitu_cameraman/lakitu_camera_lens.rgba16.inc.c", 0x001d8310, 51422, 0x00003800, 512);

// 0x06003A00
static const Lights1 lakitu_seg6_lights_06003A00 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06003A18
static const Lights1 lakitu_seg6_lights_06003A18 = gdSPDefLights1(
    0x79, 0x55, 0x00,
    0xf2, 0xab, 0x00, 0x28, 0x28, 0x28
);

// 0x06003A30
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06003A30, 0x00180bb0, 29674, 0x00012510, 256);

// 0x06003B30
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06003B30, 0x00180bb0, 29674, 0x00012610, 160);

// 0x06003BD0
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06003BD0, 0x00180bb0, 29674, 0x000126b0, 176);

// 0x06003C80 - 0x06003DB0
const Gfx lakitu_seg6_dl_06003C80[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_seg6_texture_06002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lakitu_seg6_lights_06003A00.l, 1),
    gsSPLight(&lakitu_seg6_lights_06003A00.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06003A30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  8,  7,  1, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0,  3,  5, 10, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0,  8,  1, 12, 0x0),
    gsSP2Triangles(12,  1,  0, 0x0, 13, 11, 12, 0x0),
    gsSP2Triangles(13, 12,  0, 0x0, 14, 13,  0, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(lakitu_seg6_vertex_06003B30, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 4,  5,  7, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 8,  5,  6, 0x0,  8,  6,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x06003DB0 - 0x06003E30
const Gfx lakitu_seg6_dl_06003DB0[] = {
    gsSPLight(&lakitu_seg6_lights_06003A18.l, 1),
    gsSPLight(&lakitu_seg6_lights_06003A18.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06003BD0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 5,  3,  2, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 7,  8,  1, 0x0,  9,  7,  0, 0x0),
    gsSP2Triangles( 1,  0,  7, 0x0,  8, 10,  1, 0x0),
    gsSP2Triangles( 1, 10,  5, 0x0,  0,  6,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x06003E30 - 0x06003E98
const Gfx lakitu_seg6_dl_06003E30[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lakitu_seg6_dl_06003C80),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(lakitu_seg6_dl_06003DB0),
    gsSPEndDisplayList(),
};

// 0x06003E98
static const Lights1 lakitu_seg6_lights_06003E98 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06003EB0
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06003EB0, 0x00180bb0, 29674, 0x00012990, 256);

// 0x06003FB0
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06003FB0, 0x00180bb0, 29674, 0x00012a90, 240);

// 0x060040A0
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_060040A0, 0x00180bb0, 29674, 0x00012b80, 256);

// 0x060041A0
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_060041A0, 0x00180bb0, 29674, 0x00012c80, 240);

// 0x06004290
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004290, 0x00180bb0, 29674, 0x00012d70, 256);

// 0x06004390
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004390, 0x00180bb0, 29674, 0x00012e70, 128);

// 0x06004410 - 0x06004680
const Gfx lakitu_seg6_dl_06004410[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_seg6_texture_06003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lakitu_seg6_lights_06003E98.l, 1),
    gsSPLight(&lakitu_seg6_lights_06003E98.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06003EB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 3,  5,  1, 0x0,  1,  6,  7, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  1,  0,  4, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 9,  7,  8, 0x0,  2,  7,  9, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0,  2, 11, 10, 0x0),
    gsSP2Triangles( 2, 12, 11, 0x0,  2,  9, 12, 0x0),
    gsSP2Triangles( 9, 13, 12, 0x0,  9,  8, 13, 0x0),
    gsSP2Triangles(14,  5,  3, 0x0,  5, 15,  6, 0x0),
    gsSP1Triangle( 5, 14, 15, 0x0),
    gsSPVertex(lakitu_seg6_vertex_06003FB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  6,  0,  3, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 11,  6,  3, 0x0),
    gsSP2Triangles( 2, 11,  3, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(lakitu_seg6_vertex_060040A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  4,  6,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  7, 12,  8, 0x0),
    gsSP2Triangles(13,  8, 12, 0x0,  9,  8, 14, 0x0),
    gsSP1Triangle(15,  8, 13, 0x0),
    gsSPVertex(lakitu_seg6_vertex_060041A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  6,  4, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(14, 10, 13, 0x0),
    gsSPVertex(lakitu_seg6_vertex_06004290, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 3,  7, 10, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles( 3, 10, 12, 0x0,  1, 14,  2, 0x0),
    gsSP1Triangle(13,  9, 15, 0x0),
    gsSPVertex(lakitu_seg6_vertex_06004390, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06004680 - 0x060046E0
const Gfx lakitu_seg6_dl_06004680[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lakitu_seg6_dl_06004410),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x060046E0
static const Lights1 lakitu_seg6_lights_060046E0 = gdSPDefLights1(
    0x79, 0x55, 0x00,
    0xf2, 0xab, 0x00, 0x28, 0x28, 0x28
);

// 0x060046F8
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_060046F8, 0x00180bb0, 29674, 0x000135b0, 240);

// 0x060047E8 - 0x060048D8
const Gfx lakitu_seg6_dl_060047E8[] = {
    gsSPLight(&lakitu_seg6_lights_060046E0.l, 1),
    gsSPLight(&lakitu_seg6_lights_060046E0.a, 2),
    gsSPVertex(lakitu_seg6_vertex_060046F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  4,  8, 0x0,  3,  8,  4, 0x0),
    gsSP2Triangles( 9,  7,  6, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles( 5,  7, 10, 0x0,  3,  5, 11, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  1,  6,  2, 0x0),
    gsSP2Triangles( 2,  6,  8, 0x0,  9,  6,  1, 0x0),
    gsSP2Triangles( 1, 12,  9, 0x0, 12, 10,  9, 0x0),
    gsSP2Triangles( 1,  0, 12, 0x0, 11, 13,  3, 0x0),
    gsSP2Triangles(14,  0,  2, 0x0, 14,  2,  8, 0x0),
    gsSP2Triangles( 3, 14,  8, 0x0, 13,  0,  3, 0x0),
    gsSP2Triangles( 3,  0, 14, 0x0,  0, 13, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 12, 13, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x060048D8
static const Lights1 lakitu_seg6_lights_060048D8 = gdSPDefLights1(
    0x79, 0x55, 0x00,
    0xf2, 0xab, 0x00, 0x28, 0x28, 0x28
);

// 0x060048F0
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_060048F0, 0x00180bb0, 29674, 0x000133b8, 240);

// 0x060049E0 - 0x06004AD0
const Gfx lakitu_seg6_dl_060049E0[] = {
    gsSPLight(&lakitu_seg6_lights_060048D8.l, 1),
    gsSPLight(&lakitu_seg6_lights_060048D8.a, 2),
    gsSPVertex(lakitu_seg6_vertex_060048F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 6,  1,  3, 0x0,  1,  7,  3, 0x0),
    gsSP2Triangles( 8,  7,  0, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 0,  7,  1, 0x0,  9,  4,  8, 0x0),
    gsSP2Triangles( 4,  9,  5, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11,  8,  0, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0,  2, 12, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 12,  5, 0x0),
    gsSP2Triangles( 9, 10, 13, 0x0,  9, 13,  5, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0,  1, 14,  2, 0x0),
    gsSP2Triangles( 2, 14, 12, 0x0,  6, 14,  1, 0x0),
    gsSP2Triangles( 5, 14,  6, 0x0,  5, 12, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x06004AD0
static const Lights1 lakitu_seg6_lights_06004AD0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06004AE8
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004AE8, 0x00180bb0, 29674, 0x000131d8, 192);

// 0x06004BA8 - 0x06004BE8
const Gfx lakitu_seg6_dl_06004BA8[] = {
    gsSPLight(&lakitu_seg6_lights_06004AD0.l, 1),
    gsSPLight(&lakitu_seg6_lights_06004AD0.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06004AE8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06004BE8 - 0x06004C30
const Gfx lakitu_seg6_dl_06004BE8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x06004C30 - 0x06004C60
const Gfx lakitu_seg6_dl_06004C30[] = {
    gsSPDisplayList(lakitu_seg6_dl_06004BA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06004C60 - 0x06004C88
const Gfx lakitu_seg6_dl_06004C60[] = {
    gsSPDisplayList(lakitu_seg6_dl_06004BE8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_seg6_texture_06000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(lakitu_seg6_dl_06004C30),
};

// 0x06004C88 - 0x06004CB0
const Gfx lakitu_seg6_dl_06004C88[] = {
    gsSPDisplayList(lakitu_seg6_dl_06004BE8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_seg6_texture_06001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(lakitu_seg6_dl_06004C30),
};

// 0x06004CB0
static const Lights1 lakitu_seg6_lights_06004CB0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06004CC8
static const Lights1 lakitu_seg6_lights_06004CC8 = gdSPDefLights1(
    0x0c, 0x0c, 0x0c,
    0x19, 0x19, 0x19, 0x28, 0x28, 0x28
);

// 0x06004CE0
static const Lights1 lakitu_seg6_lights_06004CE0 = gdSPDefLights1(
    0x19, 0x22, 0x20,
    0x32, 0x44, 0x40, 0x28, 0x28, 0x28
);

// 0x06004CF8
static const Lights1 lakitu_seg6_lights_06004CF8 = gdSPDefLights1(
    0x18, 0x18, 0x18,
    0x30, 0x30, 0x30, 0x28, 0x28, 0x28
);

// 0x06004D10
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004D10, 0x001d8310, 51422, 0x00004d10, 64);

// 0x06004D50
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004D50, 0x001d8310, 51422, 0x00004d50, 240);

// 0x06004E40
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004E40, 0x001d8310, 51422, 0x00004e40, 240);

// 0x06004F30
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004F30, 0x001d8310, 51422, 0x00004f30, 96);

// 0x06004F90
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06004F90, 0x001d8310, 51422, 0x00004f90, 224);

// 0x06005070
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06005070, 0x001d8310, 51422, 0x00005070, 224);

// 0x06005150
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06005150, 0x001d8310, 51422, 0x00005150, 128);

// 0x060051D0 - 0x06005218
const Gfx lakitu_seg6_dl_060051D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lakitu_seg6_texture_06003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lakitu_seg6_lights_06004CB0.l, 1),
    gsSPLight(&lakitu_seg6_lights_06004CB0.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06004D10, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06005218 - 0x06005360
const Gfx lakitu_seg6_dl_06005218[] = {
    gsSPLight(&lakitu_seg6_lights_06004CC8.l, 1),
    gsSPLight(&lakitu_seg6_lights_06004CC8.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06004D50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(lakitu_seg6_vertex_06004E40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(lakitu_seg6_vertex_06004F30, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&lakitu_seg6_lights_06004CE0.l, 1),
    gsSPLight(&lakitu_seg6_lights_06004CE0.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06004F90, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(lakitu_seg6_vertex_06005070, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPLight(&lakitu_seg6_lights_06004CF8.l, 1),
    gsSPLight(&lakitu_seg6_lights_06004CF8.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06005150, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  1,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06005360 - 0x060053D8
const Gfx lakitu_seg6_dl_06005360[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lakitu_seg6_dl_060051D0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(lakitu_seg6_dl_06005218),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// Unreferenced light group
UNUSED static const Lights1 lakitu_cameraman_lights_unused1 = gdSPDefLights1(
    0x33, 0x1f, 0x0c,
    0xcc, 0x7f, 0x33, 0x28, 0x28, 0x28
);

// 0x060053F0
static const Lights1 lakitu_seg6_lights_060053F0 = gdSPDefLights1(
    0x29, 0x13, 0x06,
    0xa5, 0x4f, 0x1b, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 lakitu_cameraman_lights_unused2 = gdSPDefLights1(
    0x06, 0x06, 0x06,
    0x19, 0x19, 0x19, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 lakitu_cameraman_lights_unused3 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x06005438
static const Lights1 lakitu_seg6_lights_06005438 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 lakitu_cameraman_lights_unused4 = gdSPDefLights1(
    0x0d, 0x2c, 0x0b,
    0x34, 0xb2, 0x2c, 0x28, 0x28, 0x28
);

// 0x06005468
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06005468, 0x00180bb0, 29674, 0x00013790, 208);

// 0x06005538
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06005538, 0x001d8310, 51422, 0x00005538, 48);

// 0x06005568
ROM_ASSET_LOAD_VTX(lakitu_seg6_vertex_06005568, 0x001d8310, 51422, 0x00005568, 48);

// 0x06005598 - 0x060055E8
const Gfx lakitu_seg6_dl_06005598[] = {
    gsSPLight(&lakitu_seg6_lights_060053F0.l, 1),
    gsSPLight(&lakitu_seg6_lights_060053F0.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06005468, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0, 10, 11, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x060055E8 - 0x06005610
const Gfx lakitu_seg6_dl_060055E8[] = {
    gsSPLight(&lakitu_seg6_lights_06005438.l, 1),
    gsSPLight(&lakitu_seg6_lights_06005438.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06005538, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06005610 - 0x06005638
const Gfx lakitu_seg6_dl_06005610[] = {
    gsSPLight(&lakitu_seg6_lights_06005438.l, 1),
    gsSPLight(&lakitu_seg6_lights_06005438.a, 2),
    gsSPVertex(lakitu_seg6_vertex_06005568, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};
