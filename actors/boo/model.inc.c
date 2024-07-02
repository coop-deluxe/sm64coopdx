#include "pc/rom_assets.h"
// Boo

// 0x05009B28
static const Lights1 boo_seg5_lights_05009B28 = gdSPDefLights1(
    0x97, 0x9a, 0xff,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05009B40
ROM_ASSET_LOAD_TEXTURE(boo_seg5_texture_05009B40, "actors/boo/boo_eyes.rgba16.inc.c", 0x00166c60, 26968, 0x00009b40, 4096);

// 0x0500AB40
ROM_ASSET_LOAD_TEXTURE(boo_seg5_texture_0500AB40, "actors/boo/boo_mouth.rgba16.inc.c", 0x00166c60, 26968, 0x0000ab40, 2048);

// 0x0500B340
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B340, 0x00166c60, 26968, 0x0000b340, 192);

// 0x0500B400
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B400, 0x00166c60, 26968, 0x0000b400, 192);

// 0x0500B4C0
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B4C0, 0x00166c60, 26968, 0x0000b4c0, 240);

// 0x0500B5B0
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B5B0, 0x00166c60, 26968, 0x0000b5b0, 240);

// 0x0500B6A0
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B6A0, 0x00166c60, 26968, 0x0000b6a0, 240);

// 0x0500B790
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B790, 0x00166c60, 26968, 0x0000b790, 240);

// 0x0500B880
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B880, 0x00166c60, 26968, 0x0000b880, 240);

// 0x0500B970
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500B970, 0x00166c60, 26968, 0x0000b970, 240);

// 0x0500BA60
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500BA60, 0x00166c60, 26968, 0x0000ba60, 240);

// 0x0500BB50
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500BB50, 0x00166c60, 26968, 0x0000bb50, 240);

// 0x0500BC40
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500BC40, 0x00166c60, 26968, 0x0000bc40, 240);

// 0x0500BD30
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500BD30, 0x00166c60, 26968, 0x0000bd30, 240);

// 0x0500BE20
ROM_ASSET_LOAD_VTX(boo_seg5_vertex_0500BE20, 0x00166c60, 26968, 0x0000be20, 192);

// 0x0500BEE0 - 0x0500BF48
const Gfx boo_seg5_dl_0500BEE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, boo_seg5_texture_0500AB40),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&boo_seg5_lights_05009B28.l, 1),
    gsSPLight(&boo_seg5_lights_05009B28.a, 2),
    gsSPVertex(boo_seg5_vertex_0500B340, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BF48 - 0x0500BFA0
const Gfx boo_seg5_dl_0500BF48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, boo_seg5_texture_05009B40),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(boo_seg5_vertex_0500B400, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BFA0 - 0x0500C1B0
const Gfx boo_seg5_dl_0500BFA0[] = {
    gsSPVertex(boo_seg5_vertex_0500B4C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500B5B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500B6A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500B790, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500B880, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500B970, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500BA60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500BB50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500BC40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500BD30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(boo_seg5_vertex_0500BE20, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C1B0 - 0x0500C250
const Gfx boo_seg5_dl_0500C1B0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBFADEA, G_CC_BLENDRGBFADEA),
    gsSPNumLights(NUMLIGHTS_1),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(boo_seg5_dl_0500BEE0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(boo_seg5_dl_0500BF48),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(boo_seg5_dl_0500BFA0),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
