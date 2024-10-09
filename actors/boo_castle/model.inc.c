#include "pc/rom_assets.h"
// Boo (Castle)

// 0x06015658
static const Lights1 boo_castle_seg6_lights_06015658 = gdSPDefLights1(
    0x97, 0x9a, 0xff,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06015670
ROM_ASSET_LOAD_TEXTURE(boo_castle_seg6_texture_06015670, "actors/boo_castle/bbh_boo_eyes.rgba16.inc.c", 0x00166c60, 26968, 0x00009b40, 4096);

// 0x06016670
ROM_ASSET_LOAD_TEXTURE(boo_castle_seg6_texture_06016670, "actors/boo_castle/bbh_boo_mouth.rgba16.inc.c", 0x00166c60, 26968, 0x0000ab40, 2048);

// 0x06016E70
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06016E70, 0x00166c60, 26968, 0x0000b340, 192);

// 0x06016F30
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06016F30, 0x00166c60, 26968, 0x0000b400, 192);

// 0x06016FF0
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06016FF0, 0x00166c60, 26968, 0x0000b4c0, 240);

// 0x060170E0
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_060170E0, 0x00166c60, 26968, 0x0000b5b0, 240);

// 0x060171D0
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_060171D0, 0x00166c60, 26968, 0x0000b6a0, 240);

// 0x060172C0
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_060172C0, 0x00166c60, 26968, 0x0000b790, 240);

// 0x060173B0
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_060173B0, 0x00166c60, 26968, 0x0000b880, 240);

// 0x060174A0
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_060174A0, 0x00166c60, 26968, 0x0000b970, 240);

// 0x06017590
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06017590, 0x00166c60, 26968, 0x0000ba60, 240);

// 0x06017680
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06017680, 0x00166c60, 26968, 0x0000bb50, 240);

// 0x06017770
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06017770, 0x00166c60, 26968, 0x0000bc40, 240);

// 0x06017860
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06017860, 0x00166c60, 26968, 0x0000bd30, 240);

// 0x06017950
ROM_ASSET_LOAD_VTX(boo_castle_seg6_vertex_06017950, 0x00166c60, 26968, 0x0000be20, 192);

// 0x06017A10 - 0x06017A78
const Gfx boo_castle_seg6_dl_06017A10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, boo_castle_seg6_texture_06016670),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&boo_castle_seg6_lights_06015658.l, 1),
    gsSPLight(&boo_castle_seg6_lights_06015658.a, 2),
    gsSPVertex(boo_castle_seg6_vertex_06016E70, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06017A78 - 0x06017AD0
const Gfx boo_castle_seg6_dl_06017A78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, boo_castle_seg6_texture_06015670),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(boo_castle_seg6_vertex_06016F30, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06017AD0 - 0x06017CE0
const Gfx boo_castle_seg6_dl_06017AD0[] = {
    gsSPVertex(boo_castle_seg6_vertex_06016FF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_060170E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_060171D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_060172C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_060173B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_060174A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_06017590, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_06017680, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_06017770, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_06017860, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_castle_seg6_vertex_06017950, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06017CE0 - 0x06017D80
const Gfx boo_castle_seg6_dl_06017CE0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsSPNumLights(NUMLIGHTS_1),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(boo_castle_seg6_dl_06017A10),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(boo_castle_seg6_dl_06017A78),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(boo_castle_seg6_dl_06017AD0),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
