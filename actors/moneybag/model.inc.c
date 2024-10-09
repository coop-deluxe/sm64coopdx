#include "pc/rom_assets.h"
// Moneybag

// 0x060039B0
ROM_ASSET_LOAD_TEXTURE(moneybag_seg6_texture_060039B0, "actors/moneybag/moneybag_mouth.rgba16.inc.c", 0x001e51f0, 11160, 0x000039b0, 4096);

// 0x060049B0
ROM_ASSET_LOAD_TEXTURE(moneybag_seg6_texture_060049B0, "actors/moneybag/moneybag_eyes.rgba16.inc.c", 0x001e51f0, 11160, 0x000049b0, 2048);

// 0x060051B0
static const Lights1 moneybag_seg6_lights_060051B0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060051C8
static const Lights1 moneybag_seg6_lights_060051C8 = gdSPDefLights1(
    0x00, 0x3f, 0x23,
    0x00, 0x7f, 0x47, 0x28, 0x28, 0x28
);

// 0x060051E0
ROM_ASSET_LOAD_VTX(moneybag_seg6_vertex_060051E0, 0x001e51f0, 11160, 0x000051e0, 160);

// 0x06005280
ROM_ASSET_LOAD_VTX(moneybag_seg6_vertex_06005280, 0x001e51f0, 11160, 0x00005280, 128);

// 0x06005300 - 0x06005358
const Gfx moneybag_seg6_dl_06005300[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, moneybag_seg6_texture_060039B0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&moneybag_seg6_lights_060051B0.l, 1),
    gsSPLight(&moneybag_seg6_lights_060051B0.a, 2),
    gsSPVertex(moneybag_seg6_vertex_060051E0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  4,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x06005358 - 0x060053B8
const Gfx moneybag_seg6_dl_06005358[] = {
    gsSPLight(&moneybag_seg6_lights_060051C8.l, 1),
    gsSPLight(&moneybag_seg6_lights_060051C8.a, 2),
    gsSPVertex(moneybag_seg6_vertex_06005280, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 5,  3,  7, 0x0,  4,  7,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x060053B8 - 0x06005428
const Gfx moneybag_seg6_dl_060053B8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(moneybag_seg6_dl_06005300),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(moneybag_seg6_dl_06005358),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x06005428
static const Lights1 moneybag_seg6_lights_06005428 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06005440
ROM_ASSET_LOAD_VTX(moneybag_seg6_vertex_06005440, 0x001e51f0, 11160, 0x00005440, 224);

// 0x06005520
ROM_ASSET_LOAD_VTX(moneybag_seg6_vertex_06005520, 0x001e51f0, 11160, 0x00005520, 112);

// 0x06005590 - 0x06005618
const Gfx moneybag_seg6_dl_06005590[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, moneybag_seg6_texture_060039B0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&moneybag_seg6_lights_06005428.l, 1),
    gsSPLight(&moneybag_seg6_lights_06005428.a, 2),
    gsSPVertex(moneybag_seg6_vertex_06005440, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 5, 11, 12, 0x0,  0, 13,  1, 0x0),
    gsSPVertex(moneybag_seg6_vertex_06005520, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06005618 - 0x06005688
const Gfx moneybag_seg6_dl_06005618[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(moneybag_seg6_dl_06005590),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x06005688 - 0x060056A8
const Gfx moneybag_seg6_dl_06005688[] = {
    gsSPDisplayList(moneybag_seg6_dl_060053B8),
    gsSPDisplayList(moneybag_seg6_dl_06005618),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x060056A8
ROM_ASSET_LOAD_VTX(moneybag_seg6_vertex_060056A8, 0x001e51f0, 11160, 0x000056a8, 96);

// 0x06005708 - 0x06005750
const Gfx moneybag_seg6_dl_06005708[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, moneybag_seg6_texture_060049B0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(moneybag_seg6_vertex_060056A8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  5,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06005750 - 0x060057C0
const Gfx moneybag_seg6_dl_06005750[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADE, G_CC_DECALFADE),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(moneybag_seg6_dl_06005708),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// Unreferenced light group
UNUSED static const Lights1 moneybag_lights_unused1 = gdSPDefLights1(
    0x0c, 0x20, 0x06,
    0x30, 0x83, 0x1a, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 moneybag_lights_unused2 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x060057F0
static const Lights1 moneybag_seg6_lights_060057F0 = gdSPDefLights1(
    0x3f, 0x3f, 0x00,
    0xff, 0xff, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 moneybag_lights_unused3 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x06005820
ROM_ASSET_LOAD_VTX(moneybag_seg6_vertex_06005820, 0x001e51f0, 11160, 0x00005820, 176);

// 0x060058D0
ROM_ASSET_LOAD_VTX(moneybag_seg6_vertex_060058D0, 0x001e51f0, 11160, 0x000058d0, 176);

// 0x06005980 - 0x060059F0
const Gfx moneybag_seg6_dl_06005980[] = {
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPLight(&moneybag_seg6_lights_060057F0.l, 1),
    gsSPLight(&moneybag_seg6_lights_060057F0.a, 2),
    gsSPVertex(moneybag_seg6_vertex_06005820, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0, 10,  1,  0, 0x0),
    gsSP2Triangles( 0,  4, 10, 0x0,  2,  3,  0, 0x0),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x060059F0 - 0x06005A60
const Gfx moneybag_seg6_dl_060059F0[] = {
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPLight(&moneybag_seg6_lights_060057F0.l, 1),
    gsSPLight(&moneybag_seg6_lights_060057F0.a, 2),
    gsSPVertex(moneybag_seg6_vertex_060058D0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  5,  7, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0,  2,  1, 10, 0x0),
    gsSP2Triangles(10,  3,  2, 0x0,  2,  4,  0, 0x0),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
