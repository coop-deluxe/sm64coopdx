#include "pc/rom_assets.h"
// Hoot

// 0x05000900
static const Lights1 hoot_seg5_lights_05000900 = gdSPDefLights1(
    0x30, 0x1b, 0x0f,
    0xc0, 0x6e, 0x3d, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 hoot_lights_unused1 = gdSPDefLights1(
    0x37, 0x27, 0x0b,
    0xdd, 0x9d, 0x2d, 0x28, 0x28, 0x28
);

// 0x05000930
static const Lights1 hoot_seg5_lights_05000930 = gdSPDefLights1(
    0x36, 0x26, 0x11,
    0xdb, 0x99, 0x46, 0x28, 0x28, 0x28
);

// 0x05000948
static const Lights1 hoot_seg5_lights_05000948 = gdSPDefLights1(
    0x06, 0x06, 0x06,
    0x19, 0x19, 0x19, 0x28, 0x28, 0x28
);

// 0x05000960
static const Lights1 hoot_seg5_lights_05000960 = gdSPDefLights1(
    0x1d, 0x0a, 0x05,
    0x77, 0x2a, 0x16, 0x28, 0x28, 0x28
);

// 0x05000978
static const Lights1 hoot_seg5_lights_05000978 = gdSPDefLights1(
    0x06, 0x06, 0x06,
    0x19, 0x19, 0x19, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 hoot_lights_unused2 = gdSPDefLights1(
    0x39, 0x27, 0x0a,
    0xe6, 0x9d, 0x29, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 hoot_lights_unused3 = gdSPDefLights1(
    0x1d, 0x06, 0x3b,
    0x75, 0x18, 0xef, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 hoot_lights_unused4 = gdSPDefLights1(
    0x3a, 0x29, 0x09,
    0xeb, 0xa6, 0x27, 0x28, 0x28, 0x28
);

// 0x050009D8
static const Lights1 hoot_seg5_lights_050009D8 = gdSPDefLights1(
    0x18, 0x07, 0x03,
    0x63, 0x1e, 0x0f, 0x28, 0x28, 0x28
);

// 0x050009F0
static const Lights1 hoot_seg5_lights_050009F0 = gdSPDefLights1(
    0x3f, 0x3a, 0x09,
    0xfe, 0xea, 0x26, 0x28, 0x28, 0x28
);

// 0x05000A08
static const Lights1 hoot_seg5_lights_05000A08 = gdSPDefLights1(
    0x13, 0x0d, 0x0b,
    0x4d, 0x35, 0x2e, 0x28, 0x28, 0x28
);

// 0x05000A20
ROM_ASSET_LOAD_TEXTURE(hoot_seg5_texture_05000A20, "actors/hoot/hoot_eyes.rgba16.inc.c", 0x0012a7e0, 32879, 0x00000a20, 2048);

// 0x05001220
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05001220, 0x0012a7e0, 32879, 0x00001220, 240);

// 0x05001310
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05001310, 0x0012a7e0, 32879, 0x00001310, 192);

// 0x050013D0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050013D0, 0x0012a7e0, 32879, 0x000013d0, 48);

// 0x05001400
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05001400, 0x0012a7e0, 32879, 0x00001400, 240);

// 0x050014F0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050014F0, 0x0012a7e0, 32879, 0x000014f0, 240);

// 0x050015E0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050015E0, 0x0012a7e0, 32879, 0x000015e0, 240);

// 0x050016D0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050016D0, 0x0012a7e0, 32879, 0x000016d0, 240);

// 0x050017C0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050017C0, 0x0012a7e0, 32879, 0x000017c0, 240);

// 0x050018B0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050018B0, 0x0012a7e0, 32879, 0x000018b0, 240);

// 0x050019A0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050019A0, 0x0012a7e0, 32879, 0x000019a0, 240);

// 0x05001A90
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05001A90, 0x0012a7e0, 32879, 0x00001a90, 240);

// 0x05001B80 - 0x05001C00
const Gfx hoot_seg5_dl_05001B80[] = {
    gsDPLoadTextureBlock(hoot_seg5_texture_05000A20, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLight(&hoot_seg5_lights_050009D8.l, 1),
    gsSPLight(&hoot_seg5_lights_050009D8.a, 2),
    gsSPVertex(hoot_seg5_vertex_05001220, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05001C00 - 0x05001DF0
const Gfx hoot_seg5_dl_05001C00[] = {
    gsSPLight(&hoot_seg5_lights_050009F0.l, 1),
    gsSPLight(&hoot_seg5_lights_050009F0.a, 2),
    gsSPVertex(hoot_seg5_vertex_05001310, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPLight(&hoot_seg5_lights_05000A08.l, 1),
    gsSPLight(&hoot_seg5_lights_05000A08.a, 2),
    gsSPVertex(hoot_seg5_vertex_050013D0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&hoot_seg5_lights_050009D8.l, 1),
    gsSPLight(&hoot_seg5_lights_050009D8.a, 2),
    gsSPVertex(hoot_seg5_vertex_05001400, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050014F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050015E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050016D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050017C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050018B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050019A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_05001A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05001DF0 - 0x05001E38
const Gfx hoot_seg5_dl_05001DF0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBA, G_CC_BLENDRGBA),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPDisplayList(hoot_seg5_dl_05001B80),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(hoot_seg5_dl_05001C00),
    gsSPEndDisplayList(),
};

// 0x05001E38
static const Lights1 hoot_seg5_lights_05001E38 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05001E50
ROM_ASSET_LOAD_TEXTURE(hoot_seg5_texture_05001E50, "actors/hoot/hoot_wing.rgba16.inc.c", 0x0012a7e0, 32879, 0x00001e50, 2048);

// 0x05002650
ROM_ASSET_LOAD_TEXTURE(hoot_seg5_texture_05002650, "actors/hoot/hoot_wing_tip.rgba16.inc.c", 0x0012a7e0, 32879, 0x00002650, 2048);

// //! The vertex macro which calls this has too large of a size.
// 0x05002E50
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05002E50, 0x0012a7e0, 32879, 0x00002e50, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x1E, 0x38
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x05002EB0 - 0x05002F10
const Gfx hoot_seg5_dl_05002EB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05002650),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_05001E38.l, 1),
    gsSPLight(&hoot_seg5_lights_05001E38.a, 2),
    gsSPVertex(hoot_seg5_vertex_05002E50, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05002F10 - 0x05002F60
const Gfx hoot_seg5_dl_05002F10[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_05002EB0),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05002F60
static const Lights1 hoot_seg5_lights_05002F60 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! The vertex macro which calls this has too large of a size.
// 0x05002F78
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05002F78, 0x0012a7e0, 32879, 0x00002f78, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x2F, 0x60
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x05002FD8 - 0x05003038
const Gfx hoot_seg5_dl_05002FD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05001E50),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_05002F60.l, 1),
    gsSPLight(&hoot_seg5_lights_05002F60.a, 2),
    gsSPVertex(hoot_seg5_vertex_05002F78, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003038 - 0x05003088
const Gfx hoot_seg5_dl_05003038[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_05002FD8),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003088
static const Lights1 hoot_seg5_lights_05003088 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! The vertex macro which calls this has too large of a size.
// 0x050030A0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050030A0, 0x0012a7e0, 32879, 0x000030a0, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x30, 0x88
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x05003100 - 0x05003160
const Gfx hoot_seg5_dl_05003100[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05001E50),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_05003088.l, 1),
    gsSPLight(&hoot_seg5_lights_05003088.a, 2),
    gsSPVertex(hoot_seg5_vertex_050030A0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003160 - 0x050031B0
const Gfx hoot_seg5_dl_05003160[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_05003100),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x050031B0
static const Lights1 hoot_seg5_lights_050031B0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! The vertex macro which calls this has too large of a size.
// 0x050031C8
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050031C8, 0x0012a7e0, 32879, 0x000031c8, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x31, 0xB0
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x05003228 - 0x05003288
const Gfx hoot_seg5_dl_05003228[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05001E50),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_050031B0.l, 1),
    gsSPLight(&hoot_seg5_lights_050031B0.a, 2),
    gsSPVertex(hoot_seg5_vertex_050031C8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003288 - 0x050032D8
const Gfx hoot_seg5_dl_05003288[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_05003228),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x050032D8
static const Lights1 hoot_seg5_lights_050032D8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! The vertex macro which calls this has too large of a size.
// 0x050032F0
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050032F0, 0x0012a7e0, 32879, 0x000032f0, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x32, 0xD8
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x05003350 - 0x050033B0
const Gfx hoot_seg5_dl_05003350[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05002650),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_050032D8.l, 1),
    gsSPLight(&hoot_seg5_lights_050032D8.a, 2),
    gsSPVertex(hoot_seg5_vertex_050032F0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x050033B0 - 0x05003400
const Gfx hoot_seg5_dl_050033B0[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_05003350),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003400
static const Lights1 hoot_seg5_lights_05003400 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! The vertex macro which calls this has too large of a size.
// 0x05003418
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003418, 0x0012a7e0, 32879, 0x00003418, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x34, 0x00
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x05003478 - 0x050034D8
const Gfx hoot_seg5_dl_05003478[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05001E50),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_05003400.l, 1),
    gsSPLight(&hoot_seg5_lights_05003400.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003418, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x050034D8 - 0x05003528
const Gfx hoot_seg5_dl_050034D8[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_05003478),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003528
static const Lights1 hoot_seg5_lights_05003528 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! The vertex macro which calls this has too large of a size.
// 0x05003540
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003540, 0x0012a7e0, 32879, 0x00003540, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x35, 0x28
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x050035A0 - 0x05003600
const Gfx hoot_seg5_dl_050035A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05001E50),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_05003528.l, 1),
    gsSPLight(&hoot_seg5_lights_05003528.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003540, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003600 - 0x05003650
const Gfx hoot_seg5_dl_05003600[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_050035A0),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003650
static const Lights1 hoot_seg5_lights_05003650 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! The vertex macro which calls this has too large of a size.
// 0x05003668
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003668, 0x0012a7e0, 32879, 0x00003668, 96);

// vertex   -752,      0,   1280,  -2800,      0,  0x07, 0x00, 0x00, 0x00
// vertex  -6656,      0,      0,  -3328,      0,  0x07, 0x3F, 0xF1, 0x00
// vertex  -2800,   4096,      0,  -3584,      0,  0x00, 0x07, 0xC0, 0x7C
// vertex    902,     16,   1280,    904,     16,  0x05, 0x00, 0x36, 0x50
// vertex   1200,    192,   1280, -16640,      0,  0x00, 0x00, 0x0A, 0x14
// vertex -16640,      0,     30, -18432,      0,  0x00, 0x00, 0x00, 0x00

// 0x050036C8 - 0x05003728
const Gfx hoot_seg5_dl_050036C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hoot_seg5_texture_05001E50),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&hoot_seg5_lights_05003650.l, 1),
    gsSPLight(&hoot_seg5_lights_05003650.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003668, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003728 - 0x05003778
const Gfx hoot_seg5_dl_05003728[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPDisplayList(hoot_seg5_dl_050036C8),
    gsSPTexture(0x8000, 0x8000, 1, G_TX_RENDERTILE + 1, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003778
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003778, 0x0012a7e0, 32879, 0x00003778, 240);

// 0x05003868
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003868, 0x0012a7e0, 32879, 0x00003868, 240);

// 0x05003958
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003958, 0x0012a7e0, 32879, 0x00003958, 256);

// 0x05003A58
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003A58, 0x0012a7e0, 32879, 0x00003a58, 240);

// 0x05003B48
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003B48, 0x0012a7e0, 32879, 0x00003b48, 96);

// 0x05003BA8
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003BA8, 0x0012a7e0, 32879, 0x00003ba8, 240);

// 0x05003C98
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003C98, 0x0012a7e0, 32879, 0x00003c98, 192);

// 0x05003D58
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003D58, 0x0012a7e0, 32879, 0x00003d58, 256);

// 0x05003E58
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003E58, 0x0012a7e0, 32879, 0x00003e58, 192);

// 0x05003F18
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003F18, 0x0012a7e0, 32879, 0x00003f18, 64);

// 0x05003F58
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05003F58, 0x0012a7e0, 32879, 0x00003f58, 240);

// 0x05004048
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05004048, 0x0012a7e0, 32879, 0x00004048, 192);

// 0x05004108
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05004108, 0x0012a7e0, 32879, 0x00004108, 240);

// 0x050041F8
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050041F8, 0x0012a7e0, 32879, 0x000041f8, 224);

// 0x050042D8
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050042D8, 0x0012a7e0, 32879, 0x000042d8, 224);

// 0x050043B8
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050043B8, 0x0012a7e0, 32879, 0x000043b8, 240);

// 0x050044A8
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_050044A8, 0x0012a7e0, 32879, 0x000044a8, 160);

// 0x05004548
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05004548, 0x0012a7e0, 32879, 0x00004548, 256);

// 0x05004648
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05004648, 0x0012a7e0, 32879, 0x00004648, 192);

// 0x05004708
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05004708, 0x0012a7e0, 32879, 0x00004708, 64);

// 0x05004748
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05004748, 0x0012a7e0, 32879, 0x00004748, 224);

// 0x05004828
ROM_ASSET_LOAD_VTX(hoot_seg5_vertex_05004828, 0x0012a7e0, 32879, 0x00004828, 256);

// 0x05004928 - 0x05004A98
const Gfx hoot_seg5_dl_05004928[] = {
    gsSPLight(&hoot_seg5_lights_05000930.l, 1),
    gsSPLight(&hoot_seg5_lights_05000930.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003778, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_05003868, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_05003958, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 4, 10,  5, 0x0,  2, 11,  0, 0x0),
    gsSP2Triangles(12, 11,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(hoot_seg5_vertex_05003A58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_05003B48, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&hoot_seg5_lights_05000948.l, 1),
    gsSPLight(&hoot_seg5_lights_05000948.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003BA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_05003C98, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004A98 - 0x05004B38
const Gfx hoot_seg5_dl_05004A98[] = {
    gsSPLight(&hoot_seg5_lights_05000960.l, 1),
    gsSPLight(&hoot_seg5_lights_05000960.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003D58, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(hoot_seg5_vertex_05003E58, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPLight(&hoot_seg5_lights_05000978.l, 1),
    gsSPLight(&hoot_seg5_lights_05000978.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003F18, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004B38 - 0x05004CA8
const Gfx hoot_seg5_dl_05004B38[] = {
    gsSPLight(&hoot_seg5_lights_05000948.l, 1),
    gsSPLight(&hoot_seg5_lights_05000948.a, 2),
    gsSPVertex(hoot_seg5_vertex_05003F58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_05004048, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPLight(&hoot_seg5_lights_05000930.l, 1),
    gsSPLight(&hoot_seg5_lights_05000930.a, 2),
    gsSPVertex(hoot_seg5_vertex_05004108, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050041F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(hoot_seg5_vertex_050042D8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(hoot_seg5_vertex_050043B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(hoot_seg5_vertex_050044A8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004CA8 - 0x05004D48
const Gfx hoot_seg5_dl_05004CA8[] = {
    gsSPLight(&hoot_seg5_lights_05000960.l, 1),
    gsSPLight(&hoot_seg5_lights_05000960.a, 2),
    gsSPVertex(hoot_seg5_vertex_05004548, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(hoot_seg5_vertex_05004648, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPLight(&hoot_seg5_lights_05000978.l, 1),
    gsSPLight(&hoot_seg5_lights_05000978.a, 2),
    gsSPVertex(hoot_seg5_vertex_05004708, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004D48 - 0x05004EC0
const Gfx hoot_seg5_dl_05004D48[] = {
    gsSPLight(&hoot_seg5_lights_05000900.l, 1),
    gsSPLight(&hoot_seg5_lights_05000900.a, 2),
    gsSPVertex(hoot_seg5_vertex_05004748, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  1,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  2, 11, 0x0,  0, 12,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0, 12,  3,  5, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  8,  1,  6, 0x0),
    gsSP2Triangles(11,  2, 13, 0x0, 12,  0,  2, 0x0),
    gsSP2Triangles( 8,  7, 13, 0x0,  2,  8, 13, 0x0),
    gsSP2Triangles( 2, 10, 12, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles(11, 13,  7, 0x0,  5,  4,  1, 0x0),
    gsSP1Triangle( 1,  8,  2, 0x0),
    gsSPLight(&hoot_seg5_lights_05000960.l, 1),
    gsSPLight(&hoot_seg5_lights_05000960.a, 2),
    gsSPVertex(hoot_seg5_vertex_05004828, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  4,  3, 0x0),
    gsSP2Triangles( 7,  6,  9, 0x0, 10, 11,  5, 0x0),
    gsSP2Triangles( 7,  1,  4, 0x0,  6,  8, 12, 0x0),
    gsSP2Triangles(13, 14,  0, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles( 2, 13,  0, 0x0, 13,  2,  9, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  3, 11, 12, 0x0),
    gsSP2Triangles(14, 10,  5, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 5,  0, 14, 0x0, 12,  8,  3, 0x0),
    gsSP2Triangles(11,  3,  5, 0x0,  7,  2,  1, 0x0),
    gsSP1Triangle(15,  2,  7, 0x0),
    gsSPEndDisplayList(),
};
