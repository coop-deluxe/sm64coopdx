#include "pc/rom_assets.h"
// Bullet Bill

// 0x0500BA90
static const Lights1 bullet_bill_seg5_lights_0500BA90 = gdSPDefLights1(
    0x06, 0x07, 0x14,
    0x19, 0x1c, 0x52, 0x28, 0x28, 0x28
);

// 0x0500BAA8
ROM_ASSET_LOAD_TEXTURE(bullet_bill_seg5_texture_0500BAA8, "actors/bullet_bill/bullet_bill_eye.rgba16.inc.c", 0x0012a7e0, 32879, 0x0000baa8, 4096);

// 0x0500CAA8
ROM_ASSET_LOAD_TEXTURE(bullet_bill_seg5_texture_0500CAA8, "actors/bullet_bill/bullet_bill_mouth.rgba16.inc.c", 0x0012a7e0, 32879, 0x0000caa8, 4096);

// 0x0500DAA8
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500DAA8, 0x0012a7e0, 32879, 0x0000daa8, 240);

// 0x0500DB98
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500DB98, 0x0012a7e0, 32879, 0x0000db98, 144);

// 0x0500DC28
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500DC28, 0x0012a7e0, 32879, 0x0000dc28, 240);

// 0x0500DD18
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500DD18, 0x0012a7e0, 32879, 0x0000dd18, 240);

// 0x0500DE08
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500DE08, 0x0012a7e0, 32879, 0x0000de08, 192);

// 0x0500DEC8
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500DEC8, 0x0012a7e0, 32879, 0x0000dec8, 240);

// 0x0500DFB8
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500DFB8, 0x0012a7e0, 32879, 0x0000dfb8, 240);

// 0x0500E0A8
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500E0A8, 0x0012a7e0, 32879, 0x0000e0a8, 240);

// 0x0500E198
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500E198, 0x0012a7e0, 32879, 0x0000e198, 240);

// 0x0500E288
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500E288, 0x0012a7e0, 32879, 0x0000e288, 240);

// 0x0500E378
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500E378, 0x0012a7e0, 32879, 0x0000e378, 240);

// 0x0500E468
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500E468, 0x0012a7e0, 32879, 0x0000e468, 240);

// 0x0500E558
ROM_ASSET_LOAD_VTX(bullet_bill_seg5_vertex_0500E558, 0x0012a7e0, 32879, 0x0000e558, 144);

// 0x0500E5E8 - 0x0500E678
const Gfx bullet_bill_seg5_dl_0500E5E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bullet_bill_seg5_texture_0500BAA8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bullet_bill_seg5_lights_0500BA90.l, 1),
    gsSPLight(&bullet_bill_seg5_lights_0500BA90.a, 2),
    gsSPVertex(bullet_bill_seg5_vertex_0500DAA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500DB98, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E678 - 0x0500E730
const Gfx bullet_bill_seg5_dl_0500E678[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bullet_bill_seg5_texture_0500CAA8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bullet_bill_seg5_vertex_0500DC28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500DD18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500DE08, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E730 - 0x0500E8A8
const Gfx bullet_bill_seg5_dl_0500E730[] = {
    gsSPVertex(bullet_bill_seg5_vertex_0500DEC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500DFB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500E0A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500E198, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500E288, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500E378, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500E468, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bullet_bill_seg5_vertex_0500E558, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500E8A8 - 0x0500E918
const Gfx bullet_bill_seg5_dl_0500E8A8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_BLENDRGBA, G_CC_BLENDRGBA),
    gsSPNumLights(NUMLIGHTS_1),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bullet_bill_seg5_dl_0500E5E8),
    gsSPDisplayList(bullet_bill_seg5_dl_0500E678),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(bullet_bill_seg5_dl_0500E730),
    gsSPEndDisplayList(),
};
