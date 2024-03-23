#include "pc/rom_assets.h"
// Koopa Shell

// 0x08026388
static const Lights1 koopa_shell_seg8_lights_08026388 = gdSPDefLights1(
    0x11, 0x33, 0x06,
    0x45, 0xcd, 0x1a, 0x28, 0x28, 0x28
);

// 0x080263A0
static const Lights1 koopa_shell_seg8_lights_080263A0 = gdSPDefLights1(
    0x39, 0x0a, 0x07,
    0xe4, 0x29, 0x1d, 0x28, 0x28, 0x28
);

// 0x080263B8
static const Lights1 koopa_shell_seg8_lights_080263B8 = gdSPDefLights1(
    0x21, 0x30, 0x39,
    0x84, 0xc3, 0xe5, 0x28, 0x28, 0x28
);

// 0x080263D0
static const Lights1 koopa_shell_seg8_lights_080263D0 = gdSPDefLights1(
    0x3e, 0x3f, 0x3e,
    0xfa, 0xff, 0xf8, 0x28, 0x28, 0x28
);

// 0x080263E8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_080263E8, 0x001f2200, 59076, 0x000263e8, 240);

// 0x080264D8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_080264D8, 0x001f2200, 59076, 0x000264d8, 240);

// 0x080265C8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_080265C8, 0x001f2200, 59076, 0x000265c8, 240);

// 0x080266B8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_080266B8, 0x001f2200, 59076, 0x000266b8, 240);

// 0x080267A8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_080267A8, 0x001f2200, 59076, 0x000267a8, 240);

// 0x08026898
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026898, 0x001f2200, 59076, 0x00026898, 240);

// 0x08026988
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026988, 0x001f2200, 59076, 0x00026988, 144);

// 0x08026A18
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026A18, 0x001f2200, 59076, 0x00026a18, 240);

// 0x08026B08
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026B08, 0x001f2200, 59076, 0x00026b08, 240);

// 0x08026BF8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026BF8, 0x001f2200, 59076, 0x00026bf8, 240);

// 0x08026CE8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026CE8, 0x001f2200, 59076, 0x00026ce8, 240);

// 0x08026DD8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026DD8, 0x001f2200, 59076, 0x00026dd8, 240);

// 0x08026EC8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026EC8, 0x001f2200, 59076, 0x00026ec8, 240);

// 0x08026FB8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08026FB8, 0x001f2200, 59076, 0x00026fb8, 240);

// 0x080270A8
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_080270A8, 0x001f2200, 59076, 0x000270a8, 96);

// 0x08027108 - 0x08027170
const Gfx koopa_shell_seg8_dl_08027108[] = {
    gsSPVertex(koopa_shell_seg8_vertex_080263E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_080264D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x08027170 - 0x08027258
const Gfx koopa_shell_seg8_dl_08027170[] = {
    gsSPVertex(koopa_shell_seg8_vertex_080265C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_080266B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_080267A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026898, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026988, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x08027258 - 0x080273C8
const Gfx koopa_shell_seg8_dl_08027258[] = {
    gsSPVertex(koopa_shell_seg8_vertex_08026A18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026B08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026BF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026CE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026DD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026EC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08026FB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_080270A8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x080273C8 - 0x08027420
const Gfx koopa_shell_seg8_dl_080273C8[] = {
    gsDPPipeSync(),
    gsSPNumLights(NUMLIGHTS_1),
    gsSPLight(&koopa_shell_seg8_lights_08026388.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_08026388.a, 2),
    gsSPDisplayList(koopa_shell_seg8_dl_08027108),
    gsSPLight(&koopa_shell_seg8_lights_080263B8.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_080263B8.a, 2),
    gsSPDisplayList(koopa_shell_seg8_dl_08027170),
    gsSPLight(&koopa_shell_seg8_lights_080263D0.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_080263D0.a, 2),
    gsSPBranchList(koopa_shell_seg8_dl_08027258),
};

// 0x08027420 - 0x08027470
const Gfx koopa_shell_seg8_dl_08027420[] = {
    gsDPPipeSync(),
    gsSPLight(&koopa_shell_seg8_lights_080263A0.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_080263A0.a, 2),
    gsSPDisplayList(koopa_shell_seg8_dl_08027108),
    gsSPLight(&koopa_shell_seg8_lights_080263B8.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_080263B8.a, 2),
    gsSPDisplayList(koopa_shell_seg8_dl_08027170),
    gsSPLight(&koopa_shell_seg8_lights_080263D0.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_080263D0.a, 2),
    gsSPBranchList(koopa_shell_seg8_dl_08027258),
};

// 0x08027470
static const Lights1 koopa_shell_seg8_lights_08027470 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08027488
static const Lights1 koopa_shell_seg8_lights_08027488 = gdSPDefLights1(
    0x38, 0x2b, 0x00,
    0xe0, 0xae, 0x00, 0x28, 0x28, 0x28
);

// 0x080274A0
ROM_ASSET_LOAD_TEXTURE(koopa_shell_seg8_texture_080274A0, "actors/koopa_shell/koopa_shell_front.rgba16.inc.c", 0x001c4230, 80474, 0x00002648, 2048);

// 0x08027CA0
ROM_ASSET_LOAD_TEXTURE(koopa_shell_seg8_texture_08027CA0, "actors/koopa_shell/koopa_shell_back.rgba16.inc.c", 0x001c4230, 80474, 0x00002e48, 2048);

// 0x080284A0
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_080284A0, 0x001f2200, 59076, 0x000284a0, 160);

// 0x08028540
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08028540, 0x001f2200, 59076, 0x00028540, 224);

// 0x08028620
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08028620, 0x001f2200, 59076, 0x00028620, 80);

// 0x08028670
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08028670, 0x001f2200, 59076, 0x00028670, 240);

// 0x08028760
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08028760, 0x001f2200, 59076, 0x00028760, 240);

// 0x08028850
ROM_ASSET_LOAD_VTX(koopa_shell_seg8_vertex_08028850, 0x001f2200, 59076, 0x00028850, 144);

// 0x080288E0 - 0x08028978
const Gfx koopa_shell_seg8_dl_080288E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_shell_seg8_texture_08027CA0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&koopa_shell_seg8_lights_08027470.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_08027470.a, 2),
    gsSPVertex(koopa_shell_seg8_vertex_080284A0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 0,  3,  5, 0x0,  1,  4,  6, 0x0),
    gsSP2Triangles( 6,  4,  5, 0x0,  3,  2,  7, 0x0),
    gsSP2Triangles( 3,  8,  5, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 9,  5,  8, 0x0,  9,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x08028978 - 0x08028A20
const Gfx koopa_shell_seg8_dl_08028978[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_shell_seg8_texture_080274A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(koopa_shell_seg8_vertex_08028540, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  1,  0,  5, 0x0),
    gsSP2Triangles( 4,  6,  0, 0x0,  6,  5,  0, 0x0),
    gsSP2Triangles( 3,  2,  7, 0x0,  8,  2,  1, 0x0),
    gsSP2Triangles( 2,  8,  7, 0x0,  9,  4,  3, 0x0),
    gsSP2Triangles( 3, 10,  9, 0x0,  7, 11,  3, 0x0),
    gsSP2Triangles(11, 10,  3, 0x0, 10, 12,  9, 0x0),
    gsSP2Triangles( 4,  9, 13, 0x0,  4, 13,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x08028A20 - 0x08028B78
const Gfx koopa_shell_seg8_dl_08028A20[] = {
    gsSPLight(&koopa_shell_seg8_lights_08027488.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_08027488.a, 2),
    gsSPVertex(koopa_shell_seg8_vertex_08028620, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 2,  4,  3, 0x0),
    gsSPLight(&koopa_shell_seg8_lights_08027470.l, 1),
    gsSPLight(&koopa_shell_seg8_lights_08027470.a, 2),
    gsSPVertex(koopa_shell_seg8_vertex_08028670, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  4,  3,  6, 0x0),
    gsSP2Triangles( 7,  4,  6, 0x0,  2,  5,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 12,  9, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 11, 10, 14, 0x0),
    gsSP2Triangles( 9,  2, 10, 0x0,  2,  9,  0, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08028760, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2, 12,  0, 0x0, 13, 14, 11, 0x0),
    gsSP1Triangle(11, 14,  9, 0x0),
    gsSPVertex(koopa_shell_seg8_vertex_08028850, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  6,  3,  2, 0x0),
    gsSP2Triangles( 7,  2,  5, 0x0,  6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x08028B78 - 0x08028BE8
const Gfx koopa_shell_seg8_dl_08028B78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(koopa_shell_seg8_dl_080288E0),
    gsSPDisplayList(koopa_shell_seg8_dl_08028978),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(koopa_shell_seg8_dl_08028A20),
    gsSPEndDisplayList(),
};
