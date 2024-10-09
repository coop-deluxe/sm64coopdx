#include "pc/rom_assets.h"
// 0x070030A8 - 0x070030C0
static const Lights1 jrb_seg7_lights_070030A8 = gdSPDefLights1(
    0x10, 0x25, 0x1e,
    0x41, 0x96, 0x78, 0x28, 0x28, 0x28
);

// 0x070030C0 - 0x070030D8
static const Lights1 jrb_seg7_lights_070030C0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070030D8 - 0x070030F0
static const Lights1 jrb_seg7_lights_070030D8 = gdSPDefLights1(
    0x1e, 0x27, 0x3a,
    0x79, 0x9f, 0xeb, 0x28, 0x28, 0x28
);

// 0x070030F0 - 0x070031F0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070030F0, 0x0041a760, 37817, 0x000030f0, 256);

// 0x070031F0 - 0x07003250
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070031F0, 0x0041a760, 37817, 0x000031f0, 96);

// 0x07003250 - 0x07003350
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003250, 0x0041a760, 37817, 0x00003250, 256);

// 0x07003350 - 0x07003450
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003350, 0x0041a760, 37817, 0x00003350, 256);

// 0x07003450 - 0x07003540
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003450, 0x0041a760, 37817, 0x00003450, 240);

// 0x07003540 - 0x07003640
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003540, 0x0041a760, 37817, 0x00003540, 256);

// 0x07003640 - 0x07003700
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003640, 0x0041a760, 37817, 0x00003640, 192);

// 0x07003700 - 0x07003800
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003700, 0x0041a760, 37817, 0x00003700, 256);

// 0x07003800 - 0x070038F0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003800, 0x0041a760, 37817, 0x00003800, 240);

// 0x070038F0 - 0x070039E0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070038F0, 0x0041a760, 37817, 0x000038f0, 240);

// 0x070039E0 - 0x07003A90
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070039E0, 0x0041a760, 37817, 0x000039e0, 176);

// 0x07003A90 - 0x07003B10
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003A90, 0x0041a760, 37817, 0x00003a90, 128);

// 0x07003B10 - 0x07003C10
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003B10, 0x0041a760, 37817, 0x00003b10, 256);

// 0x07003C10 - 0x07003D10
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003C10, 0x0041a760, 37817, 0x00003c10, 256);

// 0x07003D10 - 0x07003E00
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003D10, 0x0041a760, 37817, 0x00003d10, 240);

// 0x07003E00 - 0x07003EF0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003E00, 0x0041a760, 37817, 0x00003e00, 240);

// 0x07003EF0 - 0x07003FD0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003EF0, 0x0041a760, 37817, 0x00003ef0, 224);

// 0x07003FD0 - 0x070040C0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_07003FD0, 0x0041a760, 37817, 0x00003fd0, 240);

// 0x070040C0 - 0x070041C0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070040C0, 0x0041a760, 37817, 0x000040c0, 256);

// 0x070041C0 - 0x070041F0
ROM_ASSET_LOAD_VTX(jrb_seg7_vertex_070041C0, 0x0041a760, 37817, 0x000041c0, 48);

// 0x070041F0 - 0x070044C8
static const Gfx jrb_seg7_dl_070041F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070030A8.l, 1),
    gsSPLight(&jrb_seg7_lights_070030A8.a, 2),
    gsSPVertex(jrb_seg7_vertex_070030F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  2, 0x0,  4,  3,  6, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  6,  3,  9, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  9,  3, 10, 0x0),
    gsSP2Triangles( 3,  7, 10, 0x0, 11,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0, 12, 10,  7, 0x0),
    gsSP2Triangles(13,  5,  1, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles(11,  4,  6, 0x0, 14, 11,  6, 0x0),
    gsSP2Triangles(14,  6,  9, 0x0, 15, 14,  9, 0x0),
    gsSP2Triangles(15,  9, 10, 0x0, 12, 15, 10, 0x0),
    gsSPVertex(jrb_seg7_vertex_070031F0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSPLight(&jrb_seg7_lights_070030C0.l, 1),
    gsSPLight(&jrb_seg7_lights_070030C0.a, 2),
    gsSPVertex(jrb_seg7_vertex_07003250, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles( 6,  8, 11, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles( 6, 12, 13, 0x0,  6, 10,  7, 0x0),
    gsSP1Triangle( 8, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003350, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  7,  3,  2, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 9,  6, 10, 0x0,  9,  5,  6, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(14, 12, 15, 0x0, 12, 13, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003450, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles(10, 11,  0, 0x0, 12,  0, 11, 0x0),
    gsSP2Triangles(13,  1,  0, 0x0, 14, 13,  0, 0x0),
    gsSP1Triangle(12, 14,  0, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003540, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13,  0, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003640, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  5,  3, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 0,  7,  8, 0x0,  0,  6,  7, 0x0),
    gsSP1Triangle( 9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x070044C8 - 0x07004658
static const Gfx jrb_seg7_dl_070044C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070030D8.l, 1),
    gsSPLight(&jrb_seg7_lights_070030D8.a, 2),
    gsSPVertex(jrb_seg7_vertex_07003700, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  2,  5, 0x0,  6,  3,  0, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(12, 15,  8, 0x0, 10, 14, 13, 0x0),
    gsSP2Triangles(10,  9, 14, 0x0,  8, 15,  9, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003800, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  8,  9,  7, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0, 10,  5,  8, 0x0),
    gsSP2Triangles( 5,  9,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070038F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(13,  4,  6, 0x0, 13,  6, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070039E0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP1Triangle( 8,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004658 - 0x070046C0
static const Gfx jrb_seg7_dl_07004658[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_07003A90, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  0,  2,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070046C0 - 0x07004940
static const Gfx jrb_seg7_dl_070046C0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09004800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070030C0.l, 1),
    gsSPLight(&jrb_seg7_lights_070030C0.a, 2),
    gsSPVertex(jrb_seg7_vertex_07003B10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  7,  3, 0x0),
    gsSP2Triangles( 2,  8,  9, 0x0,  2,  9,  7, 0x0),
    gsSP2Triangles(10,  8,  2, 0x0, 10,  2, 11, 0x0),
    gsSP2Triangles(11,  2,  6, 0x0, 12,  4,  3, 0x0),
    gsSP2Triangles(12,  3, 13, 0x0,  3,  7, 14, 0x0),
    gsSP1Triangle(15, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003C10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 9, 11, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003D10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle(10, 14, 11, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003E00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003EF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 6, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003FD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 3,  8,  0, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070040C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_070041C0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004940 - 0x07004A18
const Gfx jrb_seg7_dl_07004940[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070041F0),
    gsSPDisplayList(jrb_seg7_dl_070044C8),
    gsSPDisplayList(jrb_seg7_dl_07004658),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070046C0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
