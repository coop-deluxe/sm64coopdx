#include "pc/rom_assets.h"
// Koopa (Small Koopa, Big Koopa [Koopa the Quick])


// Unreferenced light group
UNUSED static const Lights1 koopa_lights_unused1 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060025A0
static const Lights1 koopa_seg6_lights_060025A0 = gdSPDefLights1(
    0x00, 0x59, 0x00,
    0x00, 0xb2, 0x00, 0x28, 0x28, 0x28
);

// 0x060025B8
static const Lights1 koopa_seg6_lights_060025B8 = gdSPDefLights1(
    0x70, 0x57, 0x00,
    0xe0, 0xae, 0x00, 0x28, 0x28, 0x28
);

// 0x060025D0
static const Lights1 koopa_seg6_lights_060025D0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 koopa_lights_unused2 = gdSPDefLights1(
    0x59, 0x59, 0x59,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x06002600
static const Lights1 koopa_seg6_lights_06002600 = gdSPDefLights1(
    0x00, 0x54, 0x00,
    0x00, 0xa9, 0x00, 0x28, 0x28, 0x28
);

// 0x06002618
static const Lights1 koopa_seg6_lights_06002618 = gdSPDefLights1(
    0x59, 0x59, 0x59,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x06002630
static const Lights1 koopa_seg6_lights_06002630 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// //! There is a malformed light entry here pointing to this texture + 0x18.
//     It results in the koopa actor 'wearing' what appears to be pink shorts
//     beneath its shell, despite the fact it was intended to be white like
//     the rest of its body. This is evident because once the mistake is corrected
//     it turns back to being white like the other polygons.
//     Due to debate in the PR surrounding the fix to this, said fix is on
//     a compile-time variable. Use TEXTURE_FIX=1 at compile time to fix this.
// 0x06002648
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06002648, "actors/koopa/koopa_shell_front.rgba16.inc.c", 0x001c4230, 80474, 0x00002648, 2048);

// 0x06002E48
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06002E48, "actors/koopa/koopa_shell_back.rgba16.inc.c", 0x001c4230, 80474, 0x00002e48, 2048);

// 0x06003648
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06003648, "actors/koopa/koopa_shoe.rgba16.inc.c", 0x001c4230, 80474, 0x00003648, 2048);

// 0x06003E48
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06003E48, "actors/koopa/koopa_shell_front_top.rgba16.inc.c", 0x001c4230, 80474, 0x00003e48, 2048);

// 0x06004648
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06004648, "actors/koopa/koopa_eyes_open.rgba16.inc.c", 0x001c4230, 80474, 0x00004648, 2048);

// 0x06004E48
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06004E48, "actors/koopa/koopa_eyes_closed.rgba16.inc.c", 0x001c4230, 80474, 0x00004e48, 2048);

// 0x06005648
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06005648, "actors/koopa/koopa_eye_border.rgba16.inc.c", 0x001c4230, 80474, 0x00005648, 2048);

// 0x06005E48
ROM_ASSET_LOAD_TEXTURE(koopa_seg6_texture_06005E48, "actors/koopa/koopa_nostrils.rgba16.inc.c", 0x001c4230, 80474, 0x00005e48, 4096);

// 0x06006E48
static const Lights1 koopa_seg6_lights_06006E48 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06006E60
static const Lights1 koopa_seg6_lights_06006E60 = gdSPDefLights1(
    0x67, 0x0b, 0x1a,
    0xce, 0x16, 0x35, 0x28, 0x28, 0x28
);

// 0x06006E78
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06006E78, 0x001c4230, 80474, 0x00006e78, 144);

// 0x06006F08
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06006F08, 0x001c4230, 80474, 0x00006f08, 240);

// 0x06006FF8
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06006FF8, 0x001c4230, 80474, 0x00006ff8, 256);

// 0x060070F8
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060070F8, 0x001c4230, 80474, 0x000070f8, 240);

// 0x060071E8
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060071E8, 0x001c4230, 80474, 0x000071e8, 128);

// 0x06007268
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007268, 0x001c4230, 80474, 0x00007268, 240);

// 0x06007358
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007358, 0x001c4230, 80474, 0x00007358, 256);

// 0x06007458
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007458, 0x001c4230, 80474, 0x00007458, 48);

// 0x06007488
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007488, 0x001c4230, 80474, 0x00007488, 48);

// 0x060074B8
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060074B8, 0x001c4230, 80474, 0x000074b8, 256);

// 0x060075B8
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060075B8, 0x001c4230, 80474, 0x000075b8, 160);

// 0x06007658 - 0x060076B0
const Gfx koopa_seg6_dl_06007658[] = {
    gsSPLight(&koopa_seg6_lights_06006E48.l, 1),
    gsSPLight(&koopa_seg6_lights_06006E48.a, 2),
    gsSPVertex(koopa_seg6_vertex_06006E78, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 7,  5,  0, 0x0,  8,  1,  0, 0x0),
    gsSP1Triangle( 0,  6,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x060076B0 - 0x06007850
const Gfx koopa_seg6_dl_060076B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06005648),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(koopa_seg6_vertex_06006F08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  5,  6,  8, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 9,  6, 10, 0x0,  7, 10,  6, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0,  8, 11,  3, 0x0),
    gsSP2Triangles(11,  8,  9, 0x0,  3, 11, 12, 0x0),
    gsSP2Triangles( 2,  3, 12, 0x0,  3, 13,  4, 0x0),
    gsSP2Triangles(13,  3,  2, 0x0,  2,  1, 13, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(koopa_seg6_vertex_06006FF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  4,  5,  8, 0x0),
    gsSP2Triangles( 6,  5,  3, 0x0,  0,  4,  1, 0x0),
    gsSP2Triangles( 8,  1,  4, 0x0,  2,  9,  0, 0x0),
    gsSP2Triangles( 2, 10,  9, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_060070F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  0, 11,  1, 0x0),
    gsSP1Triangle(14,  8, 10, 0x0),
    gsSPVertex(koopa_seg6_vertex_060071E8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  5,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x06007850 - 0x06007970
const Gfx koopa_seg6_dl_06007850[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06005E48),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(koopa_seg6_vertex_06007268, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  0,  6, 0x0),
    gsSP2Triangles( 6,  4,  1, 0x0,  5,  3,  1, 0x0),
    gsSP2Triangles( 7,  4,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles( 9,  5,  8, 0x0,  7,  6, 10, 0x0),
    gsSP2Triangles(11,  7, 10, 0x0,  8,  7, 11, 0x0),
    gsSP2Triangles(12,  9,  8, 0x0,  8, 11, 12, 0x0),
    gsSP1Triangle(13,  2, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_06007358, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 9,  1,  3, 0x0,  9,  3,  8, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0,  4, 12,  5, 0x0),
    gsSP2Triangles(13, 14, 12, 0x0, 14, 15, 12, 0x0),
    gsSP1Triangle(12, 11, 13, 0x0),
    gsSPVertex(koopa_seg6_vertex_06007458, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06007970 - 0x06007A60
const Gfx koopa_seg6_dl_06007970[] = {
    gsSPLight(&koopa_seg6_lights_06006E60.l, 1),
    gsSPLight(&koopa_seg6_lights_06006E60.a, 2),
    gsSPVertex(koopa_seg6_vertex_06007488, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&koopa_seg6_lights_06006E48.l, 1),
    gsSPLight(&koopa_seg6_lights_06006E48.a, 2),
    gsSPVertex(koopa_seg6_vertex_060074B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 6,  8,  5, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 5, 10,  3, 0x0,  8, 10,  5, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0, 12,  2,  1, 0x0),
    gsSP2Triangles( 1,  7, 11, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(12, 15,  2, 0x0, 12, 14, 15, 0x0),
    gsSP1Triangle( 0,  2, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_060075B8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  9,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06007A60 - 0x06007AA0
const Gfx koopa_seg6_dl_06007A60[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x06007AA0 - 0x06007AF8
const Gfx koopa_seg6_dl_06007AA0[] = {
    gsSPDisplayList(koopa_seg6_dl_06007658),
    gsSPDisplayList(koopa_seg6_dl_060076B0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(koopa_seg6_dl_06007850),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(koopa_seg6_dl_06007970),
    gsSPEndDisplayList(),
};

// 0x06007AF8 - 0x06007B20
const Gfx koopa_seg6_dl_06007AF8[] = {
    gsSPDisplayList(koopa_seg6_dl_06007A60),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06004648),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(koopa_seg6_dl_06007AA0),
};

// 0x06007B20 - 0x06007B48
const Gfx koopa_seg6_dl_06007B20[] = {
    gsSPDisplayList(koopa_seg6_dl_06007A60),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06004E48),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(koopa_seg6_dl_06007AA0),
};

// 0x06007B48
static const Lights1 koopa_seg6_lights_06007B48 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06007B60
static const Lights1 koopa_seg6_lights_06007B60 = gdSPDefLights1(
    0x70, 0x57, 0x00,
    0xe0, 0xae, 0x00, 0x28, 0x28, 0x28
);

// 0x06007B78
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007B78, 0x001c4230, 80474, 0x00007b78, 160);

// 0x06007C18
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007C18, 0x001c4230, 80474, 0x00007c18, 224);

// 0x06007CF8
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007CF8, 0x001c4230, 80474, 0x00007cf8, 80);

// 0x06007D48
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007D48, 0x001c4230, 80474, 0x00007d48, 240);

// 0x06007E38
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007E38, 0x001c4230, 80474, 0x00007e38, 240);

// 0x06007F28
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06007F28, 0x001c4230, 80474, 0x00007f28, 144);

// 0x06007FB8 - 0x06008050
const Gfx koopa_seg6_dl_06007FB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06002E48),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&koopa_seg6_lights_06007B48.l, 1),
    gsSPLight(&koopa_seg6_lights_06007B48.a, 2),
    gsSPVertex(koopa_seg6_vertex_06007B78, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 0,  3,  5, 0x0,  1,  4,  6, 0x0),
    gsSP2Triangles( 6,  4,  5, 0x0,  3,  2,  7, 0x0),
    gsSP2Triangles( 3,  8,  5, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 9,  5,  8, 0x0,  9,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008050 - 0x060080F8
const Gfx koopa_seg6_dl_06008050[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06002648),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(koopa_seg6_vertex_06007C18, 14, 0),
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

// 0x060080F8 - 0x06008250
const Gfx koopa_seg6_dl_060080F8[] = {
    gsSPLight(&koopa_seg6_lights_06007B60.l, 1),
    gsSPLight(&koopa_seg6_lights_06007B60.a, 2),
    gsSPVertex(koopa_seg6_vertex_06007CF8, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 2,  4,  3, 0x0),
    gsSPLight(&koopa_seg6_lights_06007B48.l, 1),
    gsSPLight(&koopa_seg6_lights_06007B48.a, 2),
    gsSPVertex(koopa_seg6_vertex_06007D48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  4,  3,  6, 0x0),
    gsSP2Triangles( 7,  4,  6, 0x0,  2,  5,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 12,  9, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 11, 10, 14, 0x0),
    gsSP2Triangles( 9,  2, 10, 0x0,  2,  9,  0, 0x0),
    gsSPVertex(koopa_seg6_vertex_06007E38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2, 12,  0, 0x0, 13, 14, 11, 0x0),
    gsSP1Triangle(11, 14,  9, 0x0),
    gsSPVertex(koopa_seg6_vertex_06007F28, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  6,  3,  2, 0x0),
    gsSP2Triangles( 7,  2,  5, 0x0,  6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008250 - 0x060082C0
const Gfx koopa_seg6_dl_06008250[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(koopa_seg6_dl_06007FB8),
    gsSPDisplayList(koopa_seg6_dl_06008050),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(koopa_seg6_dl_060080F8),
    gsSPEndDisplayList(),
};

// 0x060082C0
static const Lights1 koopa_seg6_lights_060082C0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060082D8
static const Lights1 koopa_seg6_lights_060082D8 = gdSPDefLights1(
    0x00, 0x64, 0x00,
    0x00, 0xc8, 0x00, 0x28, 0x28, 0x28
);

// 0x060082F0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060082F0, 0x001c4230, 80474, 0x000082f0, 256);

// 0x060083F0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060083F0, 0x001c4230, 80474, 0x000083f0, 128);

// 0x06008470
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008470, 0x001c4230, 80474, 0x00008470, 192);

// 0x06008530 - 0x060085E8
const Gfx koopa_seg6_dl_06008530[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06003648),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&koopa_seg6_lights_060082C0.l, 1),
    gsSPLight(&koopa_seg6_lights_060082C0.a, 2),
    gsSPVertex(koopa_seg6_vertex_060082F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 10, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 12, 15, 14, 0x0),
    gsSP2Triangles( 6, 14, 15, 0x0,  6, 15,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x060085E8 - 0x06008640
const Gfx koopa_seg6_dl_060085E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06003E48),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(koopa_seg6_vertex_060083F0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 5,  6,  1, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008640 - 0x060086D0
const Gfx koopa_seg6_dl_06008640[] = {
    gsSPLight(&koopa_seg6_lights_060082D8.l, 1),
    gsSPLight(&koopa_seg6_lights_060082D8.a, 2),
    gsSPVertex(koopa_seg6_vertex_06008470, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 3,  2,  6, 0x0,  7,  6,  2, 0x0),
    gsSP2Triangles( 7,  2,  5, 0x0,  3,  6,  8, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0,  7, 10,  6, 0x0),
    gsSP2Triangles( 6, 11,  8, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x060086D0 - 0x06008740
const Gfx koopa_seg6_dl_060086D0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(koopa_seg6_dl_06008530),
    gsSPDisplayList(koopa_seg6_dl_060085E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(koopa_seg6_dl_06008640),
    gsSPEndDisplayList(),
};

// 0x06008740
static const Lights1 koopa_seg6_lights_06008740 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06008758
static const Lights1 koopa_seg6_lights_06008758 = gdSPDefLights1(
    0x00, 0x64, 0x00,
    0x00, 0xc8, 0x00, 0x28, 0x28, 0x28
);

// 0x06008770
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008770, 0x001c4230, 80474, 0x00008770, 256);

// 0x06008870
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008870, 0x001c4230, 80474, 0x00008870, 128);

// 0x060088F0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060088F0, 0x001c4230, 80474, 0x000088f0, 192);

// 0x060089B0 - 0x06008A68
const Gfx koopa_seg6_dl_060089B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06003648),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&koopa_seg6_lights_06008740.l, 1),
    gsSPLight(&koopa_seg6_lights_06008740.a, 2),
    gsSPVertex(koopa_seg6_vertex_06008770, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  5,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 10, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 12, 15, 14, 0x0),
    gsSP2Triangles( 6, 14, 15, 0x0,  6, 15,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008A68 - 0x06008AC0
const Gfx koopa_seg6_dl_06008A68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, koopa_seg6_texture_06003E48),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(koopa_seg6_vertex_06008870, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 5,  6,  1, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008AC0 - 0x06008B50
const Gfx koopa_seg6_dl_06008AC0[] = {
    gsSPLight(&koopa_seg6_lights_06008758.l, 1),
    gsSPLight(&koopa_seg6_lights_06008758.a, 2),
    gsSPVertex(koopa_seg6_vertex_060088F0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  3,  8,  1, 0x0),
    gsSP2Triangles( 7,  1,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 3, 10, 11, 0x0,  3, 11,  8, 0x0),
    gsSP2Triangles( 5, 10,  3, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x06008B50 - 0x06008BC0
const Gfx koopa_seg6_dl_06008B50[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(koopa_seg6_dl_060089B0),
    gsSPDisplayList(koopa_seg6_dl_06008A68),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(koopa_seg6_dl_06008AC0),
    gsSPEndDisplayList(),
};

// 0x06008BC0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008BC0, 0x001c4230, 80474, 0x00008bc0, 256);

// 0x06008CC0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008CC0, 0x001c4230, 80474, 0x00008cc0, 224);

// 0x06008DA0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008DA0, 0x001c4230, 80474, 0x00008da0, 224);

// 0x06008E80
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008E80, 0x001c4230, 80474, 0x00008e80, 224);

// 0x06008F60
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06008F60, 0x001c4230, 80474, 0x00008f60, 224);

// 0x06009040
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009040, 0x001c4230, 80474, 0x00009040, 256);

// 0x06009140
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009140, 0x001c4230, 80474, 0x00009140, 256);

// 0x06009240
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009240, 0x001c4230, 80474, 0x00009240, 256);

// 0x06009340
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009340, 0x001c4230, 80474, 0x00009340, 208);

// 0x06009410
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009410, 0x001c4230, 80474, 0x00009410, 224);

// 0x060094F0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060094F0, 0x001c4230, 80474, 0x000094f0, 224);

// 0x060095D0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060095D0, 0x001c4230, 80474, 0x000095d0, 240);

// 0x060096C0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060096C0, 0x001c4230, 80474, 0x000096c0, 240);

// 0x060097B0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060097B0, 0x001c4230, 80474, 0x000097b0, 240);

// 0x060098A0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060098A0, 0x001c4230, 80474, 0x000098a0, 256);

// 0x060099A0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_060099A0, 0x001c4230, 80474, 0x000099a0, 144);

// 0x06009A30
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009A30, 0x001c4230, 80474, 0x00009a30, 160);

// 0x06009AD0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009AD0, 0x001c4230, 80474, 0x00009ad0, 224);

// 0x06009BB0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009BB0, 0x001c4230, 80474, 0x00009bb0, 240);

// 0x06009CA0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009CA0, 0x001c4230, 80474, 0x00009ca0, 240);

// 0x06009D90
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009D90, 0x001c4230, 80474, 0x00009d90, 240);

// 0x06009E80
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009E80, 0x001c4230, 80474, 0x00009e80, 256);

// 0x06009F80
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_06009F80, 0x001c4230, 80474, 0x00009f80, 144);

// 0x0600A010
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A010, 0x001c4230, 80474, 0x0000a010, 160);

// 0x0600A0B0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A0B0, 0x001c4230, 80474, 0x0000a0b0, 240);

// 0x0600A1A0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A1A0, 0x001c4230, 80474, 0x0000a1a0, 256);

// 0x0600A2A0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A2A0, 0x001c4230, 80474, 0x0000a2a0, 256);

// 0x0600A3A0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A3A0, 0x001c4230, 80474, 0x0000a3a0, 256);

// 0x0600A4A0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A4A0, 0x001c4230, 80474, 0x0000a4a0, 256);

// 0x0600A5A0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A5A0, 0x001c4230, 80474, 0x0000a5a0, 240);

// 0x0600A690
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A690, 0x001c4230, 80474, 0x0000a690, 256);

// 0x0600A790
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A790, 0x001c4230, 80474, 0x0000a790, 256);

// 0x0600A890
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A890, 0x001c4230, 80474, 0x0000a890, 256);

// 0x0600A990
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A990, 0x001c4230, 80474, 0x0000a990, 48);

// 0x0600A9C0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600A9C0, 0x001c4230, 80474, 0x0000a9c0, 256);

// 0x0600AAC0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600AAC0, 0x001c4230, 80474, 0x0000aac0, 240);

// 0x0600ABB0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600ABB0, 0x001c4230, 80474, 0x0000abb0, 224);

// 0x0600AC90
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600AC90, 0x001c4230, 80474, 0x0000ac90, 256);

// 0x0600AD90
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600AD90, 0x001c4230, 80474, 0x0000ad90, 256);

// 0x0600AE90
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600AE90, 0x001c4230, 80474, 0x0000ae90, 208);

// 0x0600AF60
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600AF60, 0x001c4230, 80474, 0x0000af60, 160);

// 0x0600B000
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B000, 0x001c4230, 80474, 0x0000b000, 224);

// 0x0600B0E0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B0E0, 0x001c4230, 80474, 0x0000b0e0, 176);

// 0x0600B190
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B190, 0x001c4230, 80474, 0x0000b190, 224);

// 0x0600B270
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B270, 0x001c4230, 80474, 0x0000b270, 256);

// 0x0600B370
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B370, 0x001c4230, 80474, 0x0000b370, 256);

// 0x0600B470
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B470, 0x001c4230, 80474, 0x0000b470, 240);

// 0x0600B560
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B560, 0x001c4230, 80474, 0x0000b560, 144);

// 0x0600B5F0
ROM_ASSET_LOAD_VTX(koopa_seg6_vertex_0600B5F0, 0x001c4230, 80474, 0x0000b5f0, 240);

// 0x0600B6E0 - 0x0600B838
const Gfx koopa_seg6_dl_0600B6E0[] = {
    gsSPLight(&koopa_seg6_lights_060025A0.l, 1),
    gsSPLight(&koopa_seg6_lights_060025A0.a, 2),
    gsSPVertex(koopa_seg6_vertex_06008BC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_06008CC0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  2,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  4, 0x0,  9,  4,  6, 0x0),
    gsSP2Triangles( 2,  8, 11, 0x0,  2, 11,  3, 0x0),
    gsSP2Triangles( 3, 12, 13, 0x0,  3, 13,  0, 0x0),
    gsSPVertex(koopa_seg6_vertex_06008DA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  8,  5, 10, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 11,  9, 13, 0x0),
    gsSPVertex(koopa_seg6_vertex_06008E80, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6,  7,  9, 0x0,  6,  9,  4, 0x0),
    gsSP2Triangles(10,  0,  3, 0x0, 10,  3, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600B838 - 0x0600B8B8
const Gfx koopa_seg6_dl_0600B838[] = {
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_06008F60, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles(12,  4,  6, 0x0, 12,  6, 13, 0x0),
    gsSP2Triangles( 5,  0,  3, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600B8B8 - 0x0600BA10
const Gfx koopa_seg6_dl_0600B8B8[] = {
    gsSPLight(&koopa_seg6_lights_060025A0.l, 1),
    gsSPLight(&koopa_seg6_lights_060025A0.a, 2),
    gsSPVertex(koopa_seg6_vertex_06009040, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009140, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  1, 0x0),
    gsSP2Triangles( 4,  6,  9, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 0, 11,  7, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 3, 12, 13, 0x0,  3, 13,  0, 0x0),
    gsSP1Triangle(10, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009240, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009340, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  5,  6,  8, 0x0),
    gsSP2Triangles( 5,  8,  3, 0x0,  9,  0,  2, 0x0),
    gsSP2Triangles( 9,  2, 10, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 12,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600BA10 - 0x0600BA90
const Gfx koopa_seg6_dl_0600BA10[] = {
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_06009410, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles(12,  4,  6, 0x0, 12,  6, 13, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0,  1, 13,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600BA90 - 0x0600BC18
const Gfx koopa_seg6_dl_0600BA90[] = {
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_060094F0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(koopa_seg6_vertex_060095D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9, 10, 0x0),
    gsSP2Triangles(10,  9,  0, 0x0, 11,  1, 12, 0x0),
    gsSP1Triangle( 1, 13, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_060096C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 2, 10, 11, 0x0, 12,  3,  5, 0x0),
    gsSP2Triangles(12,  8, 13, 0x0, 14,  0, 11, 0x0),
    gsSPVertex(koopa_seg6_vertex_060097B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10,  4, 12, 0x0, 12, 13, 10, 0x0),
    gsSP1Triangle( 8, 14,  7, 0x0),
    gsSPVertex(koopa_seg6_vertex_060098A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  0, 0x0),
    gsSP2Triangles(11, 12,  7, 0x0, 11,  7, 13, 0x0),
    gsSP1Triangle(14, 15,  6, 0x0),
    gsSPVertex(koopa_seg6_vertex_060099A0, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600BC18 - 0x0600BC88
const Gfx koopa_seg6_dl_0600BC18[] = {
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_06009A30, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600BC88 - 0x0600BE10
const Gfx koopa_seg6_dl_0600BC88[] = {
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_06009AD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009BB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 2, 10,  9, 0x0, 11,  1, 12, 0x0),
    gsSP1Triangle(13, 14,  1, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009CA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11,  0, 0x0,  3,  5, 12, 0x0),
    gsSP2Triangles(13,  6, 12, 0x0, 10,  2, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009D90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  9,  7, 11, 0x0),
    gsSP2Triangles(12,  5, 10, 0x0, 10, 13, 12, 0x0),
    gsSP1Triangle( 8, 14,  7, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009E80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  2,  9, 10, 0x0),
    gsSP2Triangles(11,  7, 12, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 8, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_06009F80, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600BE10 - 0x0600BE80
const Gfx koopa_seg6_dl_0600BE10[] = {
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_0600A010, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8,  0,  3, 0x0,  8,  3,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600BE80 - 0x0600C240
const Gfx koopa_seg6_dl_0600BE80[] = {
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_0600A0B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 5,  9,  2, 0x0,  3,  2,  9, 0x0),
    gsSP2Triangles(10,  6,  8, 0x0, 11,  5,  4, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A1A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  2, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A2A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A3A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9, 11,  6, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(14, 13,  9, 0x0,  7, 11, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A4A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(15,  7, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A5A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A690, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  6,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP2Triangles(13, 14,  2, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A790, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0, 11,  7,  6, 0x0),
    gsSP2Triangles(11,  9,  7, 0x0, 10,  9, 12, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0,  2, 10, 12, 0x0),
    gsSP2Triangles( 2,  1, 10, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle(15, 12, 13, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A890, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 10, 12, 11, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600A990, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&koopa_seg6_lights_060025D0.l, 1),
    gsSPLight(&koopa_seg6_lights_060025D0.a, 2),
    gsSPVertex(koopa_seg6_vertex_0600A9C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  2,  9, 10, 0x0),
    gsSP2Triangles( 4,  0, 11, 0x0, 12, 13,  5, 0x0),
    gsSP2Triangles( 6,  8, 12, 0x0, 11,  0, 14, 0x0),
    gsSP2Triangles( 6, 15,  7, 0x0, 10, 14,  2, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600AAC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(12,  8, 10, 0x0,  3, 13, 14, 0x0),
    gsSP2Triangles(10,  2, 12, 0x0,  7,  3,  5, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600ABB0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  3, 11, 0x0,  0, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600C240 - 0x0600C498
const Gfx koopa_seg6_dl_0600C240[] = {
    gsSPLight(&koopa_seg6_lights_06002618.l, 1),
    gsSPLight(&koopa_seg6_lights_06002618.a, 2),
    gsSPVertex(koopa_seg6_vertex_0600AC90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  9, 13, 12, 0x0),
    gsSP2Triangles( 5,  9, 14, 0x0,  6,  5, 14, 0x0),
    gsSP2Triangles(14, 15,  6, 0x0, 12, 14,  9, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0,  7,  9,  5, 0x0),
    gsSP1Triangle( 3,  2,  9, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600AD90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  0, 14,  1, 0x0),
    gsSP1Triangle( 9, 15,  1, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600AE90, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 3,  4,  9, 0x0,  0,  3, 10, 0x0),
    gsSP1Triangle(11, 12,  7, 0x0),
    gsSPLight(&koopa_seg6_lights_06002600.l, 1),
    gsSPLight(&koopa_seg6_lights_06002600.a, 2),
    gsSPVertex(koopa_seg6_vertex_0600AF60, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  6,  5,  1, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  4,  3,  9, 0x0),
    gsSP2Triangles( 7,  2,  5, 0x0,  6,  0,  8, 0x0),
    gsSP2Triangles( 8,  3,  6, 0x0,  6,  1,  0, 0x0),
    gsSPLight(&koopa_seg6_lights_060025B8.l, 1),
    gsSPLight(&koopa_seg6_lights_060025B8.a, 2),
    gsSPVertex(koopa_seg6_vertex_0600B000, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 1, 10,  2, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 6,  7,  9, 0x0,  0, 12,  1, 0x0),
    gsSP2Triangles( 2,  5,  4, 0x0,  9,  4,  6, 0x0),
    gsSP2Triangles( 5,  2, 10, 0x0,  9,  0,  2, 0x0),
    gsSP1Triangle( 8, 13, 11, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600B0E0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 2,  3,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  9, 10,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600C498 - 0x0600C6A0
const Gfx koopa_seg6_dl_0600C498[] = {
    gsSPLight(&koopa_seg6_lights_06002630.l, 1),
    gsSPLight(&koopa_seg6_lights_06002630.a, 2),
    gsSPVertex(koopa_seg6_vertex_0600B190, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600B270, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 2,  1,  9, 0x0,  2,  9, 12, 0x0),
    gsSP2Triangles( 7, 13,  8, 0x0, 14, 15, 12, 0x0),
    gsSP2Triangles(14, 12,  8, 0x0,  3,  2, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600B370, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0, 12,  1, 13, 0x0),
    gsSP2Triangles(14,  9, 11, 0x0, 14, 11, 15, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600B470, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  1, 0x0),
    gsSP2Triangles( 7,  1,  0, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(koopa_seg6_vertex_0600B560, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
#ifdef TEXTURE_FIX
    gsSPLight(&koopa_seg6_lights_06002630.l, 1),
    gsSPLight(&koopa_seg6_lights_06002630.a, 2),
#else
    gsSPLight((u8*)koopa_seg6_texture_06002648 + 0x20, 1), //! this malformed light results in a
    gsSPLight((u8*)koopa_seg6_texture_06002648 + 0x18, 2), //! koopa appearing to wear pink shorts.
#endif
    gsSPVertex(koopa_seg6_vertex_0600B5F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  3,  5,  8, 0x0),
    gsSP2Triangles( 6,  0,  4, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 6,  3, 11, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles( 9,  4,  0, 0x0, 12, 13,  7, 0x0),
    gsSP2Triangles(12,  7,  6, 0x0,  1,  7, 13, 0x0),
    gsSP2Triangles(10,  9,  2, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles( 0,  7,  1, 0x0,  6, 14, 12, 0x0),
    gsSPEndDisplayList(),
};
