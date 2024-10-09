#include "pc/rom_assets.h"
// 0x07002800 - 0x07002818
static const Lights1 bob_seg7_lights_07002800 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07002818 - 0x07002908
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002818, 0x003fc2b0, 38830, 0x00002818, 240);

// 0x07002908 - 0x070029F8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002908, 0x003fc2b0, 38830, 0x00002908, 240);

// 0x070029F8 - 0x07002AD8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_070029F8, 0x003fc2b0, 38830, 0x000029f8, 224);

// 0x07002AD8 - 0x07002BD8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002AD8, 0x003fc2b0, 38830, 0x00002ad8, 256);

// 0x07002BD8 - 0x07002CC8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002BD8, 0x003fc2b0, 38830, 0x00002bd8, 240);

// 0x07002CC8 - 0x07002DC8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002CC8, 0x003fc2b0, 38830, 0x00002cc8, 256);

// 0x07002DC8 - 0x07002EB8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002DC8, 0x003fc2b0, 38830, 0x00002dc8, 240);

// 0x07002EB8 - 0x07002FB8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002EB8, 0x003fc2b0, 38830, 0x00002eb8, 256);

// 0x07002FB8 - 0x070030B8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07002FB8, 0x003fc2b0, 38830, 0x00002fb8, 256);

// 0x070030B8 - 0x070031B8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_070030B8, 0x003fc2b0, 38830, 0x000030b8, 256);

// 0x070031B8 - 0x07003298
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_070031B8, 0x003fc2b0, 38830, 0x000031b8, 224);

// 0x07003298 - 0x07003398
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003298, 0x003fc2b0, 38830, 0x00003298, 256);

// 0x07003398 - 0x07003498
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003398, 0x003fc2b0, 38830, 0x00003398, 256);

// 0x07003498 - 0x07003598
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003498, 0x003fc2b0, 38830, 0x00003498, 256);

// 0x07003598 - 0x07003678
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003598, 0x003fc2b0, 38830, 0x00003598, 224);

// 0x07003678 - 0x07003758
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003678, 0x003fc2b0, 38830, 0x00003678, 224);

// 0x07003758 - 0x070037E8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003758, 0x003fc2b0, 38830, 0x00003758, 144);

// 0x070037E8 - 0x070038E8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_070037E8, 0x003fc2b0, 38830, 0x000037e8, 256);

// 0x070038E8 - 0x070039E8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_070038E8, 0x003fc2b0, 38830, 0x000038e8, 256);

// 0x070039E8 - 0x07003A68
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_070039E8, 0x003fc2b0, 38830, 0x000039e8, 128);

// 0x07003A68 - 0x07003B58
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003A68, 0x003fc2b0, 38830, 0x00003a68, 240);

// 0x07003B58 - 0x07003C48
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003B58, 0x003fc2b0, 38830, 0x00003b58, 240);

// 0x07003C48 - 0x07003CA8
ROM_ASSET_LOAD_VTX(bob_seg7_vertex_07003C48, 0x003fc2b0, 38830, 0x00003c48, 96);

// 0x07003CA8 - 0x070041E0
static const Gfx bob_seg7_dl_07003CA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09005800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bob_seg7_lights_07002800.l, 1),
    gsSPLight(&bob_seg7_lights_07002800.a, 2),
    gsSPVertex(bob_seg7_vertex_07002818, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 1,  7,  8, 0x0,  6,  7,  1, 0x0),
    gsSP2Triangles( 1,  9, 10, 0x0,  4,  1, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  3,  4, 14, 0x0),
    gsSPVertex(bob_seg7_vertex_07002908, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 7, 12,  8, 0x0, 13, 14,  8, 0x0),
    gsSP1Triangle(12, 13,  8, 0x0),
    gsSPVertex(bob_seg7_vertex_070029F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  5,  8,  7, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0,  7, 11, 12, 0x0),
    gsSP2Triangles( 7, 12, 13, 0x0, 10,  7, 13, 0x0),
    gsSPVertex(bob_seg7_vertex_07002AD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  1,  6,  7, 0x0),
    gsSP2Triangles( 7,  2,  1, 0x0,  3,  2,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  3,  8,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(bob_seg7_vertex_07002BD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles(12,  2,  1, 0x0, 13,  0, 14, 0x0),
    gsSPVertex(bob_seg7_vertex_07002CC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(12, 11,  0, 0x0,  5, 13, 14, 0x0),
    gsSP1Triangle(15, 13,  5, 0x0),
    gsSPVertex(bob_seg7_vertex_07002DC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13, 12, 10, 0x0),
    gsSPVertex(bob_seg7_vertex_07002EB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  4, 0x0, 11, 12,  5, 0x0),
    gsSP2Triangles(13, 14,  4, 0x0, 15, 13,  4, 0x0),
    gsSP1Triangle( 4, 14,  9, 0x0),
    gsSPVertex(bob_seg7_vertex_07002FB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 11, 14, 15, 0x0),
    gsSP1Triangle(11, 15, 13, 0x0),
    gsSPVertex(bob_seg7_vertex_070030B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15,  6,  8, 0x0),
    gsSPVertex(bob_seg7_vertex_070031B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 13, 11, 0x0),
    gsSPVertex(bob_seg7_vertex_07003298, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  7, 0x0,  0,  8,  7, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0,  9,  8,  0, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 13, 12, 0x0),
    gsSP1Triangle(13, 15, 11, 0x0),
    gsSPVertex(bob_seg7_vertex_07003398, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bob_seg7_vertex_07003498, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 11, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(bob_seg7_vertex_07003598, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(bob_seg7_vertex_07003678, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  7, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12,  3,  5, 0x0,  3, 13,  4, 0x0),
    gsSPVertex(bob_seg7_vertex_07003758, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  6,  5,  2, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  7,  8,  1, 0x0),
    gsSP1Triangle( 0,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070041E0 - 0x070042B8
static const Gfx bob_seg7_dl_070041E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09009800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bob_seg7_vertex_070037E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(bob_seg7_vertex_070038E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(bob_seg7_vertex_070039E8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070042B8 - 0x07004390
static const Gfx bob_seg7_dl_070042B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09006000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bob_seg7_vertex_07003A68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 2,  1,  7, 0x0,  2,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bob_seg7_vertex_07003B58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bob_seg7_vertex_07003C48, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004390 - 0x07004478
const Gfx bob_seg7_dl_07004390[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(160, 160, 160, 255),
    gsSPFogPosition(980, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bob_seg7_dl_07003CA8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bob_seg7_dl_070041E0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bob_seg7_dl_070042B8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
