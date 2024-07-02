#include "pc/rom_assets.h"
// Ukiki

// Unreferenced light group
UNUSED static const Lights1 ukiki_lights_unused1 = gdSPDefLights1(
    0x1d, 0x12, 0x07,
    0x77, 0x48, 0x1f, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 ukiki_lights_unused2 = gdSPDefLights1(
    0x39, 0x24, 0x18,
    0xe7, 0x93, 0x61, 0x28, 0x28, 0x28
);

// 0x05007BA0
static const Lights1 ukiki_seg5_lights_05007BA0 = gdSPDefLights1(
    0x39, 0x24, 0x18,
    0xe7, 0x93, 0x61, 0x28, 0x28, 0x28
);

// The hell?
UNUSED static const u64 ukiki_unused_1 = 1;

// 0x05007BC0
ROM_ASSET_LOAD_TEXTURE(ukiki_seg5_texture_05007BC0, "actors/ukiki/ukiki_face.rgba16.inc.c", 0x001521d0, 57608, 0x00007bc0, 4096);

// 0x05008BC0
ROM_ASSET_LOAD_TEXTURE(ukiki_seg5_texture_05008BC0, "actors/ukiki/ukiki_face_blink.rgba16.inc.c", 0x001521d0, 57608, 0x00008bc0, 4096);

// 0x05009BC0
ROM_ASSET_LOAD_TEXTURE(ukiki_seg5_texture_05009BC0, "actors/ukiki/ukiki_butt.rgba16.inc.c", 0x001521d0, 57608, 0x00009bc0, 2048);

// 0x0500A3C0
ROM_ASSET_LOAD_TEXTURE(ukiki_seg5_texture_0500A3C0, "actors/ukiki/ukiki_fur.rgba16.inc.c", 0x001521d0, 57608, 0x0000a3c0, 2048);

// 0x0500ABC0
static const Lights1 ukiki_seg5_lights_0500ABC0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500ABD8
static const Lights1 ukiki_seg5_lights_0500ABD8 = gdSPDefLights1(
    0x77, 0x66, 0x45,
    0xee, 0xcd, 0x8a, 0x28, 0x28, 0x28
);

// 0x0500ABF0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500ABF0, 0x001521d0, 57608, 0x0000abf0, 256);

// 0x0500ACF0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500ACF0, 0x001521d0, 57608, 0x0000acf0, 256);

// 0x0500ADF0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500ADF0, 0x001521d0, 57608, 0x0000adf0, 256);

// 0x0500AEF0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500AEF0, 0x001521d0, 57608, 0x0000aef0, 112);

// 0x0500AF60
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500AF60, 0x001521d0, 57608, 0x0000af60, 224);

// 0x0500B040 - 0x0500B1D8
const Gfx ukiki_seg5_dl_0500B040[] = {
    gsSPLight(&ukiki_seg5_lights_0500ABC0.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500ABC0.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500ABF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 2,  6,  0, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 3,  0,  9, 0x0,  3,  9,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11,  8, 0x0),
    gsSP2Triangles( 0, 10,  9, 0x0, 12,  7,  8, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ukiki_seg5_vertex_0500ACF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 2,  7,  0, 0x0,  0,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  8, 0x0,  0,  7, 10, 0x0),
    gsSP2Triangles( 7,  2,  4, 0x0, 11, 12,  6, 0x0),
    gsSP2Triangles( 7,  6, 12, 0x0,  6,  7,  4, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ukiki_seg5_vertex_0500ADF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 11, 13, 0x0),
    gsSP2Triangles(15, 12, 11, 0x0, 13, 12,  3, 0x0),
    gsSP2Triangles( 5,  3, 12, 0x0, 12, 15,  5, 0x0),
    gsSPVertex(ukiki_seg5_vertex_0500AEF0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 5,  0,  6, 0x0,  0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B1D8 - 0x0500B278
const Gfx ukiki_seg5_dl_0500B1D8[] = {
    gsSPLight(&ukiki_seg5_lights_0500ABD8.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500ABD8.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500AF60, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 0,  4,  6, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  0,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 11, 13, 10, 0x0),
    gsSP2Triangles(10, 12,  9, 0x0, 10, 13, 12, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0,  3,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B278 - 0x0500B2B8
const Gfx ukiki_seg5_dl_0500B278[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x0500B2B8 - 0x0500B2E8
const Gfx ukiki_seg5_dl_0500B2B8[] = {
    gsSPDisplayList(ukiki_seg5_dl_0500B040),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(ukiki_seg5_dl_0500B1D8),
    gsSPEndDisplayList(),
};

// 0x0500B2E8 - 0x0500B310
const Gfx ukiki_seg5_dl_0500B2E8[] = {
    gsSPDisplayList(ukiki_seg5_dl_0500B278),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_05007BC0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(ukiki_seg5_dl_0500B2B8),
};

// 0x0500B310 - 0x0500B338
const Gfx ukiki_seg5_dl_0500B310[] = {
    gsSPDisplayList(ukiki_seg5_dl_0500B278),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_05008BC0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(ukiki_seg5_dl_0500B2B8),
};

// 0x0500B338
static const Lights1 ukiki_seg5_lights_0500B338 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500B350
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500B350, 0x001521d0, 57608, 0x0000b350, 240);

// 0x0500B440
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500B440, 0x001521d0, 57608, 0x0000b440, 256);

// 0x0500B540
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500B540, 0x001521d0, 57608, 0x0000b540, 224);

// 0x0500B620
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500B620, 0x001521d0, 57608, 0x0000b620, 64);

// 0x0500B660 - 0x0500B7E8
const Gfx ukiki_seg5_dl_0500B660[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500B338.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500B338.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500B350, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 3,  7,  5, 0x0,  3,  4,  7, 0x0),
    gsSP2Triangles( 8,  1,  3, 0x0,  3,  6,  8, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles( 2,  8, 10, 0x0,  2,  1,  8, 0x0),
    gsSP2Triangles(11, 10,  8, 0x0, 11,  8,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 11, 12, 14, 0x0),
    gsSP1Triangle(11,  9, 12, 0x0),
    gsSPVertex(ukiki_seg5_vertex_0500B440, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  3,  6,  5, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  2,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11,  8,  7, 0x0, 12,  2,  1, 0x0),
    gsSP2Triangles( 2, 12,  6, 0x0, 13, 12,  1, 0x0),
    gsSP2Triangles(14, 15,  1, 0x0,  0, 14,  1, 0x0),
    gsSPVertex(ukiki_seg5_vertex_0500B540, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10,  8, 11, 0x0,  9,  8, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B7E8 - 0x0500B820
const Gfx ukiki_seg5_dl_0500B7E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_05009BC0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ukiki_seg5_vertex_0500B620, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B820 - 0x0500B888
const Gfx ukiki_seg5_dl_0500B820[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500B660),
    gsSPDisplayList(ukiki_seg5_dl_0500B7E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500B888
static const Lights1 ukiki_seg5_lights_0500B888 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500B8A0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500B8A0, 0x001521d0, 57608, 0x0000b8a0, 128);

// 0x0500B920 - 0x0500B988
const Gfx ukiki_seg5_dl_0500B920[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500B888.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500B888.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500B8A0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 0,  7,  3, 0x0,  7,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B988 - 0x0500B9E8
const Gfx ukiki_seg5_dl_0500B988[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500B920),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500B9E8
static const Lights1 ukiki_seg5_lights_0500B9E8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500BA00
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500BA00, 0x001521d0, 57608, 0x0000ba00, 144);

// 0x0500BA90 - 0x0500BB28
const Gfx ukiki_seg5_dl_0500BA90[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500B9E8.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500B9E8.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500BA00, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  1,  6,  2, 0x0),
    gsSP2Triangles( 3,  5,  1, 0x0,  4,  2,  7, 0x0),
    gsSP2Triangles( 7,  2,  6, 0x0,  3,  4,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 5,  3,  8, 0x0,  5,  8,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BB28 - 0x0500BB88
const Gfx ukiki_seg5_dl_0500BB28[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500BA90),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500BB88
static const Lights1 ukiki_seg5_lights_0500BB88 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500BBA0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500BBA0, 0x001521d0, 57608, 0x0000bba0, 112);

// 0x0500BC10 - 0x0500BC78
const Gfx ukiki_seg5_dl_0500BC10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500BB88.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500BB88.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500BBA0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  6,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BC78 - 0x0500BCD8
const Gfx ukiki_seg5_dl_0500BC78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500BC10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500BCD8
static const Lights1 ukiki_seg5_lights_0500BCD8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500BCF0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500BCF0, 0x001521d0, 57608, 0x0000bcf0, 176);

// 0x0500BDA0 - 0x0500BE38
const Gfx ukiki_seg5_dl_0500BDA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500BCD8.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500BCD8.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500BCF0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  3,  5, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 0,  6,  4, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 2,  7,  6, 0x0,  3,  4,  8, 0x0),
    gsSP2Triangles( 9,  8,  4, 0x0,  5,  3,  8, 0x0),
    gsSP2Triangles( 5,  8, 10, 0x0,  9, 10,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BE38 - 0x0500BE98
const Gfx ukiki_seg5_dl_0500BE38[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500BDA0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500BE98
static const Lights1 ukiki_seg5_lights_0500BE98 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500BEB0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500BEB0, 0x001521d0, 57608, 0x0000beb0, 176);

// 0x0500BF60 - 0x0500BFF8
const Gfx ukiki_seg5_dl_0500BF60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500BE98.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500BE98.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500BEB0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  0,  3,  8, 0x0),
    gsSP2Triangles( 3,  9,  8, 0x0,  0, 10,  1, 0x0),
    gsSP2Triangles(10,  0,  8, 0x0, 10,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BFF8 - 0x0500C058
const Gfx ukiki_seg5_dl_0500BFF8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500BF60),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500C058
static const Lights1 ukiki_seg5_lights_0500C058 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C070
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500C070, 0x001521d0, 57608, 0x0000c070, 176);

// 0x0500C120 - 0x0500C1B8
const Gfx ukiki_seg5_dl_0500C120[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500C058.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500C058.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500C070, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 1,  6,  7, 0x0,  1,  7,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  4,  5,  7, 0x0),
    gsSP2Triangles( 3,  4,  8, 0x0,  4,  9,  8, 0x0),
    gsSP2Triangles(10,  3,  8, 0x0, 10,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C1B8 - 0x0500C218
const Gfx ukiki_seg5_dl_0500C1B8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500C120),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500C218
static const Lights1 ukiki_seg5_lights_0500C218 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C230
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500C230, 0x001521d0, 57608, 0x0000c230, 160);

// 0x0500C2D0 - 0x0500C368
const Gfx ukiki_seg5_dl_0500C2D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500C218.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500C218.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500C230, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 0,  5,  4, 0x0,  2,  6,  7, 0x0),
    gsSP2Triangles( 2,  7,  5, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  9,  4, 0x0,  3,  4,  9, 0x0),
    gsSP2Triangles( 1,  3,  9, 0x0,  6,  8,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C368 - 0x0500C3C8
const Gfx ukiki_seg5_dl_0500C368[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500C2D0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500C3C8
static const Lights1 ukiki_seg5_lights_0500C3C8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C3E0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500C3E0, 0x001521d0, 57608, 0x0000c3e0, 176);

// 0x0500C490 - 0x0500C528
const Gfx ukiki_seg5_dl_0500C490[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500C3C8.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500C3C8.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500C3E0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  1, 0x0),
    gsSP2Triangles( 1,  8,  9, 0x0,  1,  9,  5, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0,  8, 10,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C528 - 0x0500C588
const Gfx ukiki_seg5_dl_0500C528[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500C490),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500C588
static const Lights1 ukiki_seg5_lights_0500C588 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C5A0
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500C5A0, 0x001521d0, 57608, 0x0000c5a0, 176);

// 0x0500C650 - 0x0500C6E8
const Gfx ukiki_seg5_dl_0500C650[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500C588.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500C588.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500C5A0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  1,  6,  3, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0,  7, 10,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C6E8 - 0x0500C748
const Gfx ukiki_seg5_dl_0500C6E8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500C650),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500C748
static const Lights1 ukiki_seg5_lights_0500C748 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C760
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500C760, 0x001521d0, 57608, 0x0000c760, 160);

// 0x0500C800 - 0x0500C898
const Gfx ukiki_seg5_dl_0500C800[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500C748.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500C748.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500C760, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  3, 0x0),
    gsSP2Triangles( 5,  6,  1, 0x0,  1,  6,  7, 0x0),
    gsSP2Triangles( 1,  7,  4, 0x0,  3,  4,  7, 0x0),
    gsSP2Triangles( 0,  3,  8, 0x0,  3,  7,  9, 0x0),
    gsSP2Triangles( 6,  5,  9, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C898 - 0x0500C8F8
const Gfx ukiki_seg5_dl_0500C898[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500C800),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500C8F8
static const Lights1 ukiki_seg5_lights_0500C8F8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C910
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500C910, 0x001521d0, 57608, 0x0000c910, 160);

// 0x0500C9B0 - 0x0500CA48
const Gfx ukiki_seg5_dl_0500C9B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ukiki_seg5_texture_0500A3C0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ukiki_seg5_lights_0500C8F8.l, 1),
    gsSPLight(&ukiki_seg5_lights_0500C8F8.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500C910, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 0,  3,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  6, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0,  1,  8,  7, 0x0),
    gsSP2Triangles( 9,  0,  6, 0x0,  9,  6,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CA48 - 0x0500CAA8
const Gfx ukiki_seg5_dl_0500CA48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ukiki_seg5_dl_0500C9B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500CAA8
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500CAA8, 0x001521d0, 57608, 0x0000caa8, 256);

// 0x0500CBA8
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500CBA8, 0x001521d0, 57608, 0x0000cba8, 128);

// 0x0500CC28
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500CC28, 0x001521d0, 57608, 0x0000cc28, 256);

// 0x0500CD28
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500CD28, 0x001521d0, 57608, 0x0000cd28, 128);

// 0x0500CDA8
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500CDA8, 0x001521d0, 57608, 0x0000cda8, 240);

// 0x0500CE98
ROM_ASSET_LOAD_VTX(ukiki_seg5_vertex_0500CE98, 0x001521d0, 57608, 0x0000ce98, 208);

// 0x0500CF68 - 0x0500CFF0
const Gfx ukiki_seg5_dl_0500CF68[] = {
    gsSPLight(&ukiki_seg5_lights_05007BA0.l, 1),
    gsSPLight(&ukiki_seg5_lights_05007BA0.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500CAA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ukiki_seg5_vertex_0500CBA8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CFF0 - 0x0500D078
const Gfx ukiki_seg5_dl_0500CFF0[] = {
    gsSPLight(&ukiki_seg5_lights_05007BA0.l, 1),
    gsSPLight(&ukiki_seg5_lights_05007BA0.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500CC28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ukiki_seg5_vertex_0500CD28, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500D078 - 0x0500D108
const Gfx ukiki_seg5_dl_0500D078[] = {
    gsSPLight(&ukiki_seg5_lights_05007BA0.l, 1),
    gsSPLight(&ukiki_seg5_lights_05007BA0.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500CDA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  2,  7,  6, 0x0),
    gsSP2Triangles( 2,  6,  5, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles(13,  3,  6, 0x0, 13,  6,  7, 0x0),
    gsSP2Triangles( 4, 14,  2, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 1, 13,  7, 0x0,  1,  7,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500D108 - 0x0500D198
const Gfx ukiki_seg5_dl_0500D108[] = {
    gsSPLight(&ukiki_seg5_lights_05007BA0.l, 1),
    gsSPLight(&ukiki_seg5_lights_05007BA0.a, 2),
    gsSPVertex(ukiki_seg5_vertex_0500CE98, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 1,  7,  8, 0x0,  1,  8,  2, 0x0),
    gsSP2Triangles( 9, 10,  2, 0x0,  9,  2,  8, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  4,  7,  1, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  0,  3, 12, 0x0),
    gsSPEndDisplayList(),
};
