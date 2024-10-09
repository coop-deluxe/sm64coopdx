#include "pc/rom_assets.h"
// Sparkles

// 0x04027450
ROM_ASSET_LOAD_VTX(sparkles_seg4_vertex_04027450, 0x00114750, 78432, 0x00027450, 64);

// 0x04027490
ROM_ASSET_LOAD_TEXTURE(sparkles_seg4_texture_04027490, "actors/sparkle/sparkle_0.rgba16.inc.c", 0x00114750, 78432, 0x00027490, 2048);

// 0x04027C90
ROM_ASSET_LOAD_TEXTURE(sparkles_seg4_texture_04027C90, "actors/sparkle/sparkle_1.rgba16.inc.c", 0x00114750, 78432, 0x00027c90, 2048);

// 0x04028490
ROM_ASSET_LOAD_TEXTURE(sparkles_seg4_texture_04028490, "actors/sparkle/sparkle_2.rgba16.inc.c", 0x00114750, 78432, 0x00028490, 2048);

// 0x04028C90
ROM_ASSET_LOAD_TEXTURE(sparkles_seg4_texture_04028C90, "actors/sparkle/sparkle_3.rgba16.inc.c", 0x00114750, 78432, 0x00028c90, 2048);

// 0x04029490
ROM_ASSET_LOAD_TEXTURE(sparkles_seg4_texture_04029490, "actors/sparkle/sparkle_4.rgba16.inc.c", 0x00114750, 78432, 0x00029490, 2048);

// 0x04029C90
ROM_ASSET_LOAD_TEXTURE(sparkles_seg4_texture_04029C90, "actors/sparkle/sparkle_5.rgba16.inc.c", 0x00114750, 78432, 0x00029c90, 2048);

// 0x0402A490 - 0x0402A4F8
const Gfx sparkles_seg4_dl_0402A490[] = {
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(sparkles_seg4_vertex_04027450, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0402A4F8 - 0x0402A510
const Gfx sparkles_seg4_dl_0402A4F8[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sparkles_seg4_texture_04027490),
    gsSPBranchList(sparkles_seg4_dl_0402A490),
};

// 0x0402A510 - 0x0402A528
const Gfx sparkles_seg4_dl_0402A510[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sparkles_seg4_texture_04027C90),
    gsSPBranchList(sparkles_seg4_dl_0402A490),
};

// 0x0402A528 - 0x0402A540
const Gfx sparkles_seg4_dl_0402A528[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sparkles_seg4_texture_04028490),
    gsSPBranchList(sparkles_seg4_dl_0402A490),
};

// 0x0402A540 - 0x0402A558
const Gfx sparkles_seg4_dl_0402A540[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sparkles_seg4_texture_04028C90),
    gsSPBranchList(sparkles_seg4_dl_0402A490),
};

// 0x0402A558 - 0x0402A570
const Gfx sparkles_seg4_dl_0402A558[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sparkles_seg4_texture_04029490),
    gsSPBranchList(sparkles_seg4_dl_0402A490),
};

// 0x0402A570 - 0x0402A588
const Gfx sparkles_seg4_dl_0402A570[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sparkles_seg4_texture_04029C90),
    gsSPBranchList(sparkles_seg4_dl_0402A490),
};
