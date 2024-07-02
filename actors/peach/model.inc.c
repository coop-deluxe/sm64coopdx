#include "pc/rom_assets.h"
// Peach

// 0x050009F8
static const Lights1 peach_seg5_lights_050009F8 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05000A10
static const Lights1 peach_seg5_lights_05000A10 = gdSPDefLights1(
    0x7f, 0x5f, 0x0c,
    0xff, 0xbf, 0x18, 0x28, 0x28, 0x28
);

// 0x05000A28
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05000A28, "actors/peach/peach_eye_open.rgba16.inc.c", 0x0016d870, 76997, 0x00000a28, 2048);

// 0x05001228
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05001228, "actors/peach/peach_eye_mostly_open.rgba16.inc.c", 0x0016d870, 76997, 0x00001228, 2048);

// 0x05001A28
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05001A28, "actors/peach/peach_eye_mostly_closed.rgba16.inc.c", 0x0016d870, 76997, 0x00001a28, 2048);

// 0x05002228
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05002228, "actors/peach/peach_eye_closed.rgba16.inc.c", 0x0016d870, 76997, 0x00002228, 2048);

// 0x05002A28
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05002A28, "actors/peach/peach_crown_jewel.rgba16.inc.c", 0x0016d870, 76997, 0x00002a28, 512);

// 0x05002C28
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05002C28, "actors/peach/peach_chest_jewel.rgba16.inc.c", 0x0016d870, 76997, 0x00002c28, 512);

// 0x05002E28
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05002E28, "actors/peach/peach_lips_scrunched.rgba16.inc.c", 0x0016d870, 76997, 0x00002e28, 2048);

// 0x05003628
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05003628, "actors/peach/peach_lips.rgba16.inc.c", 0x0016d870, 76997, 0x00003628, 2048);

// 0x05003E28
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05003E28, "actors/peach/peach_nostril.rgba16.inc.c", 0x0016d870, 76997, 0x00003e28, 512);

// 0x05004028
ROM_ASSET_LOAD_TEXTURE(peach_seg5_texture_05004028, "actors/peach/peach_dress.rgba16.inc.c", 0x0016d870, 76997, 0x00004028, 2048);

// 0x05004828
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004828, 0x0016d870, 76997, 0x00004828, 256);

// 0x05004928
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004928, 0x0016d870, 76997, 0x00004928, 240);

// 0x05004A18
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004A18, 0x0016d870, 76997, 0x00004a18, 144);

// 0x05004AA8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004AA8, 0x0016d870, 76997, 0x00004aa8, 48);

// 0x05004AD8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004AD8, 0x0016d870, 76997, 0x00004ad8, 256);

// 0x05004BD8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004BD8, 0x0016d870, 76997, 0x00004bd8, 240);

// 0x05004CC8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004CC8, 0x0016d870, 76997, 0x00004cc8, 240);

// 0x05004DB8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004DB8, 0x0016d870, 76997, 0x00004db8, 128);

// 0x05004E38
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004E38, 0x0016d870, 76997, 0x00004e38, 80);

// 0x05004E88
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004E88, 0x0016d870, 76997, 0x00004e88, 240);

// 0x05004F78
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05004F78, 0x0016d870, 76997, 0x00004f78, 256);

// 0x05005078
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05005078, 0x0016d870, 76997, 0x00005078, 240);

// 0x05005168
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05005168, 0x0016d870, 76997, 0x00005168, 256);

// 0x05005268
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05005268, 0x0016d870, 76997, 0x00005268, 256);

// 0x05005368
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05005368, 0x0016d870, 76997, 0x00005368, 256);

// 0x05005468
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05005468, 0x0016d870, 76997, 0x00005468, 256);

// 0x05005568
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05005568, 0x0016d870, 76997, 0x00005568, 224);

// 0x05005648 - 0x05005750
const Gfx peach_seg5_dl_05005648[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_050009F8.l, 1),
    gsSPLight(&peach_seg5_lights_050009F8.a, 2),
    gsSPVertex(peach_seg5_vertex_05004828, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  5,  1,  6, 0x0),
    gsSP2Triangles( 7,  1,  8, 0x0,  6,  1,  3, 0x0),
    gsSP2Triangles( 2,  1,  7, 0x0,  8,  1,  4, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 12,  9, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(peach_seg5_vertex_05004928, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  9,  4,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 10, 0x0),
    gsSPVertex(peach_seg5_vertex_05004A18, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  0,  7, 0x0,  7,  0,  8, 0x0),
    gsSP1Triangle( 2,  8,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005750 - 0x05005780
const Gfx peach_seg5_dl_05005750[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05003E28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(peach_seg5_vertex_05004AA8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005780 - 0x050058B8
const Gfx peach_seg5_dl_05005780[] = {
    gsSPVertex(peach_seg5_vertex_05004AD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  4,  1, 0x0),
    gsSP2Triangles( 6,  2,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 9,  6, 11, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(peach_seg5_vertex_05004BD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  2,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 14, 10,  9, 0x0),
    gsSPVertex(peach_seg5_vertex_05004CC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles( 3,  9,  4, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  0,  4, 13, 0x0),
    gsSP1Triangle(14,  0, 13, 0x0),
    gsSPVertex(peach_seg5_vertex_05004DB8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  5,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x050058B8 - 0x050058E0
const Gfx peach_seg5_dl_050058B8[] = {
    gsSPVertex(peach_seg5_vertex_05004E38, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP1Triangle( 0,  2,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x050058E0 - 0x05005C48
const Gfx peach_seg5_dl_050058E0[] = {
    gsSPLight(&peach_seg5_lights_05000A10.l, 1),
    gsSPLight(&peach_seg5_lights_05000A10.a, 2),
    gsSPVertex(peach_seg5_vertex_05004E88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  5,  0, 0x0,  6,  4,  0, 0x0),
    gsSP2Triangles( 7,  1,  0, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles( 7,  0,  8, 0x0,  8,  0,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  5, 10,  9, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13,  7,  9, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  9, 12, 14, 0x0),
    gsSP2Triangles( 5,  9,  8, 0x0, 14, 13,  9, 0x0),
    gsSPVertex(peach_seg5_vertex_05004F78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 2,  7,  0, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 12,  8, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles( 9, 13, 14, 0x0, 15, 13,  9, 0x0),
    gsSPVertex(peach_seg5_vertex_05005078, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles( 8, 11,  3, 0x0,  3, 11,  4, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(peach_seg5_vertex_05005168, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  2,  3, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  2,  5,  7, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  7,  9,  2, 0x0),
    gsSP2Triangles(10,  2,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(peach_seg5_vertex_05005268, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  6,  7, 0x0),
    gsSP2Triangles( 3,  1,  8, 0x0,  8,  1,  5, 0x0),
    gsSP2Triangles( 6,  1,  0, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12,  3, 0x0, 13, 10,  3, 0x0),
    gsSP1Triangle(14, 15, 13, 0x0),
    gsSPVertex(peach_seg5_vertex_05005368, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 7,  2,  3, 0x0,  5,  4,  8, 0x0),
    gsSP2Triangles( 9,  4,  0, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles(10, 11,  5, 0x0, 12, 13,  0, 0x0),
    gsSP2Triangles(14, 15, 11, 0x0, 14, 11, 10, 0x0),
    gsSPVertex(peach_seg5_vertex_05005468, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles(11,  9, 10, 0x0, 10, 12, 11, 0x0),
    gsSP2Triangles(13,  1,  0, 0x0, 14,  4,  3, 0x0),
    gsSP1Triangle( 3, 15, 14, 0x0),
    gsSPVertex(peach_seg5_vertex_05005568, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 5,  1,  6, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 1,  5,  3, 0x0,  2,  7,  0, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  5,  8,  3, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0,  3, 10,  4, 0x0),
    gsSP2Triangles(11,  4, 10, 0x0, 12,  0,  7, 0x0),
    gsSP1Triangle( 5, 13,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005C48 - 0x05005CB0
const Gfx peach_seg5_dl_05005C48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05005648),
    gsSPDisplayList(peach_seg5_dl_05005750),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x05005CB0 - 0x05005CE0
const Gfx peach_seg5_dl_05005CB0[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_050058E0),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05005CE0 - 0x05005D38
const Gfx peach_seg5_dl_05005CE0[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05000A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002E28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005D38 - 0x05005D90
const Gfx peach_seg5_dl_05005D38[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05001228),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002E28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005D90 - 0x05005DE8
const Gfx peach_seg5_dl_05005D90[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05001A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002E28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005DE8 - 0x05005E40
const Gfx peach_seg5_dl_05005DE8[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002228),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002E28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005E40 - 0x05005E98
const Gfx peach_seg5_dl_05005E40[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05000A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05003628),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005E98 - 0x05005EF0
const Gfx peach_seg5_dl_05005E98[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05001228),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05003628),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005EF0 - 0x05005F48
const Gfx peach_seg5_dl_05005EF0[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05001A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05003628),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005F48 - 0x05005FA0
const Gfx peach_seg5_dl_05005F48[] = {
    gsSPDisplayList(peach_seg5_dl_05005C48),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002228),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_05005780),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05003628),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(peach_seg5_dl_050058B8),
    gsSPDisplayList(peach_seg5_dl_05005CB0),
    gsSPEndDisplayList(),
};

// 0x05005FA0
static const Lights1 peach_seg5_lights_05005FA0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05005FB8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05005FB8, 0x0016d870, 76997, 0x00005fb8, 160);

// 0x05006058 - 0x050060E0
const Gfx peach_seg5_dl_05006058[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05000A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05005FA0.l, 1),
    gsSPLight(&peach_seg5_lights_05005FA0.a, 2),
    gsSPVertex(peach_seg5_vertex_05005FB8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 9,  0,  6, 0x0,  9,  6,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x050060E0 - 0x05006138
const Gfx peach_seg5_dl_050060E0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05006058),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05006138
static const Lights1 peach_seg5_lights_05006138 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05006150
static const Lights1 peach_seg5_lights_05006150 = gdSPDefLights1(
    0x6c, 0x54, 0x5f,
    0xd9, 0xa9, 0xbe, 0x28, 0x28, 0x28
);

// 0x05006168
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006168, 0x0016d870, 76997, 0x00006168, 128);

// 0x050061E8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050061E8, 0x0016d870, 76997, 0x000061e8, 80);

// 0x05006238
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006238, 0x0016d870, 76997, 0x00006238, 224);

// 0x05006318
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006318, 0x0016d870, 76997, 0x00006318, 240);

// 0x05006408
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006408, 0x0016d870, 76997, 0x00006408, 224);

// 0x050064E8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050064E8, 0x0016d870, 76997, 0x000064e8, 256);

// 0x050065E8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050065E8, 0x0016d870, 76997, 0x000065e8, 256);

// 0x050066E8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050066E8, 0x0016d870, 76997, 0x000066e8, 64);

// 0x05006728 - 0x05006798
const Gfx peach_seg5_dl_05006728[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05002C28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05006138.l, 1),
    gsSPLight(&peach_seg5_lights_05006138.a, 2),
    gsSPVertex(peach_seg5_vertex_05006168, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  6,  1,  3, 0x0),
    gsSP2Triangles( 7,  1,  6, 0x0,  2,  1,  7, 0x0),
    gsSP1Triangle( 5,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006798 - 0x05006A18
const Gfx peach_seg5_dl_05006798[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05004028),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05006150.l, 1),
    gsSPLight(&peach_seg5_lights_05006150.a, 2),
    gsSPVertex(peach_seg5_vertex_050061E8, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP1Triangle( 3,  0,  2, 0x0),
    gsSPLight(&peach_seg5_lights_05006138.l, 1),
    gsSPLight(&peach_seg5_lights_05006138.a, 2),
    gsSPVertex(peach_seg5_vertex_05006238, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 7,  3,  0, 0x0,  0,  8,  6, 0x0),
    gsSP2Triangles( 0,  5,  8, 0x0,  0,  9,  4, 0x0),
    gsSP2Triangles( 2,  9,  0, 0x0,  8, 10,  6, 0x0),
    gsSP2Triangles( 3,  7, 11, 0x0,  7, 12, 11, 0x0),
    gsSP1Triangle( 8,  5, 13, 0x0),
    gsSPVertex(peach_seg5_vertex_05006318, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  4,  9,  2, 0x0),
    gsSP2Triangles( 2,  9,  5, 0x0, 10, 11,  7, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0,  1, 12, 13, 0x0),
    gsSP1Triangle(12,  1, 14, 0x0),
    gsSPVertex(peach_seg5_vertex_05006408, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(peach_seg5_vertex_050064E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  1,  0, 0x0),
    gsSP2Triangles(10,  0, 11, 0x0, 12,  0, 10, 0x0),
    gsSP2Triangles(13,  0,  2, 0x0,  0, 12,  9, 0x0),
    gsSP2Triangles( 0, 13, 11, 0x0, 14,  1,  9, 0x0),
    gsSP2Triangles( 2,  1, 14, 0x0, 13,  2, 15, 0x0),
    gsSPVertex(peach_seg5_vertex_050065E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 5,  9,  6, 0x0,  9,  5,  8, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0,  6,  9, 11, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  4,  6, 12, 0x0),
    gsSP2Triangles(13,  4, 12, 0x0, 14, 15,  0, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(peach_seg5_vertex_050066E8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006A18 - 0x05006A90
const Gfx peach_seg5_dl_05006A18[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05006728),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05006798),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05006A90
static const Lights1 peach_seg5_lights_05006A90 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05006AA8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006AA8, 0x0016d870, 76997, 0x00006aa8, 256);

// 0x05006BA8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006BA8, 0x0016d870, 76997, 0x00006ba8, 256);

// 0x05006CA8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006CA8, 0x0016d870, 76997, 0x00006ca8, 256);

// 0x05006DA8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006DA8, 0x0016d870, 76997, 0x00006da8, 256);

// 0x05006EA8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05006EA8, 0x0016d870, 76997, 0x00006ea8, 256);

// 0x05006FA8 - 0x05007230
const Gfx peach_seg5_dl_05006FA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05004028),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05006A90.l, 1),
    gsSPLight(&peach_seg5_lights_05006A90.a, 2),
    gsSPVertex(peach_seg5_vertex_05006AA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles( 9,  4,  3, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  3,  6, 0x0,  4, 10,  5, 0x0),
    gsSP2Triangles( 6,  7, 11, 0x0,  4, 12, 13, 0x0),
    gsSP2Triangles(13, 10,  4, 0x0, 12,  4,  9, 0x0),
    gsSP2Triangles( 2,  1, 14, 0x0,  1,  0, 15, 0x0),
    gsSPVertex(peach_seg5_vertex_05006BA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  6,  2,  3, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  7,  2,  6, 0x0),
    gsSP2Triangles( 8,  0,  9, 0x0, 10,  0, 11, 0x0),
    gsSP2Triangles( 0,  7, 11, 0x0,  1,  0,  8, 0x0),
    gsSP2Triangles( 0, 10,  9, 0x0, 12,  7,  6, 0x0),
    gsSP2Triangles(11,  7, 12, 0x0, 13, 11, 12, 0x0),
    gsSP2Triangles(11, 14, 10, 0x0, 14, 11, 13, 0x0),
    gsSP2Triangles( 9, 10, 15, 0x0, 10, 14, 15, 0x0),
    gsSPVertex(peach_seg5_vertex_05006CA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  3,  5, 0x0,  3, 13,  1, 0x0),
    gsSP2Triangles(14, 13,  3, 0x0,  3, 12, 14, 0x0),
    gsSP1Triangle(15, 12,  5, 0x0),
    gsSPVertex(peach_seg5_vertex_05006DA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  5,  2,  3, 0x0),
    gsSP2Triangles( 8,  3,  4, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 3, 11,  5, 0x0, 12, 11,  3, 0x0),
    gsSP2Triangles( 3,  8, 12, 0x0, 13, 12,  8, 0x0),
    gsSP1Triangle(14, 15, 13, 0x0),
    gsSPVertex(peach_seg5_vertex_05006EA8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0,  9, 13, 11, 0x0),
    gsSP2Triangles( 8, 13,  9, 0x0, 14, 12, 15, 0x0),
    gsSP2Triangles(10, 12, 14, 0x0, 12,  3, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x05007230 - 0x05007288
const Gfx peach_seg5_dl_05007230[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05006FA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

#ifndef VERSION_JP
// 0x05007288 - 0x050072E8
const Gfx peach_seg5_us_dl_05007288[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetRenderMode(G_RM_CUSTOM_AA_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05006FA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};
#endif

// 0x05007288
static const Lights1 peach_seg5_lights_05007288 = gdSPDefLights1(
    0x7f, 0x5f, 0x0c,
    0xff, 0xbf, 0x18, 0x28, 0x28, 0x28
);

// 0x050072A0
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050072A0, 0x0016d870, 76997, 0x00007300, 224);

// 0x05007380
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007380, 0x0016d870, 76997, 0x000073e0, 256);

// 0x05007480
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007480, 0x0016d870, 76997, 0x000074e0, 256);

// 0x05007580
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007580, 0x0016d870, 76997, 0x000075e0, 256);

// 0x05007680
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007680, 0x0016d870, 76997, 0x000076e0, 256);

// 0x05007780
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007780, 0x0016d870, 76997, 0x000077e0, 144);

// 0x05007810 - 0x05007AB8
const Gfx peach_seg5_dl_05007810[] = {
    gsSPLight(&peach_seg5_lights_05007288.l, 1),
    gsSPLight(&peach_seg5_lights_05007288.a, 2),
    gsSPVertex(peach_seg5_vertex_050072A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  3,  4,  7, 0x0),
    gsSP2Triangles( 3,  6,  8, 0x0,  3,  8,  0, 0x0),
    gsSP2Triangles( 5,  3,  7, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles( 0,  7,  4, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 0, 10,  7, 0x0, 11,  9,  0, 0x0),
    gsSP2Triangles( 0,  8, 11, 0x0,  7, 12,  5, 0x0),
    gsSP2Triangles(13, 12,  7, 0x0, 10, 13,  7, 0x0),
    gsSPVertex(peach_seg5_vertex_05007380, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  3, 0x0),
    gsSP2Triangles( 7,  5,  3, 0x0,  8,  3,  6, 0x0),
    gsSP2Triangles( 3,  8,  0, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 0,  8,  4, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  4, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 11, 12,  4, 0x0),
    gsSP2Triangles( 4, 12, 13, 0x0, 13,  7,  4, 0x0),
    gsSP2Triangles( 9, 14, 15, 0x0, 15, 10,  9, 0x0),
    gsSPVertex(peach_seg5_vertex_05007480, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  7,  0,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12,  4, 11, 0x0,  9, 13, 14, 0x0),
    gsSP1Triangle( 9, 15, 13, 0x0),
    gsSPVertex(peach_seg5_vertex_05007580, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  1,  0, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles(10,  4,  6, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 9, 14, 10, 0x0, 15, 14,  9, 0x0),
    gsSPVertex(peach_seg5_vertex_05007680, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  6, 0x0,  9,  6, 11, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles( 5,  4, 12, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle( 9, 13, 10, 0x0),
    gsSPVertex(peach_seg5_vertex_05007780, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  5,  8,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05007AB8 - 0x05007AE0
const Gfx peach_seg5_dl_05007AB8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_05007810),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05007AE0
static const Lights1 peach_seg5_lights_05007AE0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05007AF8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007AF8, 0x0016d870, 76997, 0x00007b58, 240);

// 0x05007BE8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007BE8, 0x0016d870, 76997, 0x00007c48, 256);

// 0x05007CE8 - 0x05007E58
const Gfx peach_seg5_dl_05007CE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05004028),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05007AE0.l, 1),
    gsSPLight(&peach_seg5_lights_05007AE0.a, 2),
    gsSPVertex(peach_seg5_vertex_05007AF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  3,  0, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  2,  1,  9, 0x0),
    gsSP2Triangles( 2,  9,  7, 0x0,  5,  2,  8, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  8, 10,  3, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  3, 12, 0x0),
    gsSP2Triangles( 3, 11,  4, 0x0, 10, 12,  3, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0, 10, 14, 12, 0x0),
    gsSPVertex(peach_seg5_vertex_05007BE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  0, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  8,  0,  5, 0x0),
    gsSP2Triangles( 9,  0,  8, 0x0,  0, 10,  1, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  4, 11, 12, 0x0),
    gsSP2Triangles( 7,  4, 12, 0x0,  4,  3, 11, 0x0),
    gsSP2Triangles(13,  6,  1, 0x0, 13,  1, 14, 0x0),
    gsSP2Triangles( 1, 10, 14, 0x0, 10, 15, 14, 0x0),
    gsSP2Triangles(10,  9, 15, 0x0,  8, 15,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x05007E58 - 0x05007EB0
const Gfx peach_seg5_dl_05007E58[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05007CE8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05007EB0
static const Lights1 peach_seg5_lights_05007EB0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05007EC8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007EC8, 0x0016d870, 76997, 0x00007f28, 240);

// 0x05007FB8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05007FB8, 0x0016d870, 76997, 0x00008018, 256);

// 0x050080B8 - 0x05008228
const Gfx peach_seg5_dl_050080B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05004028),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05007EB0.l, 1),
    gsSPLight(&peach_seg5_lights_05007EB0.a, 2),
    gsSPVertex(peach_seg5_vertex_05007EC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  4,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  3,  6,  0, 0x0),
    gsSP2Triangles( 7,  6,  3, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  0,  9,  8, 0x0),
    gsSP2Triangles( 6,  9,  0, 0x0,  1, 10,  4, 0x0),
    gsSP2Triangles(11,  1, 12, 0x0,  8, 12,  1, 0x0),
    gsSP2Triangles( 1, 11, 10, 0x0,  4, 10,  5, 0x0),
    gsSP1Triangle( 6, 13, 14, 0x0),
    gsSPVertex(peach_seg5_vertex_05007FB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 5,  2,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  0, 0x0,  8,  5,  7, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0, 11,  0, 10, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  1,  0, 11, 0x0),
    gsSP2Triangles(12, 10,  8, 0x0, 12,  8,  7, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0,  1, 11, 13, 0x0),
    gsSP2Triangles(14,  1, 13, 0x0, 14,  3,  1, 0x0),
    gsSP2Triangles(14, 15,  3, 0x0, 15,  4,  3, 0x0),
    gsSP1Triangle( 4, 15,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008228 - 0x05008280
const Gfx peach_seg5_dl_05008228[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_050080B8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05008280
static const Lights1 peach_seg5_lights_05008280 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05008298
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05008298, 0x0016d870, 76997, 0x000082f8, 192);

// 0x05008358
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05008358, 0x0016d870, 76997, 0x000083b8, 208);

// 0x05008428 - 0x050084C0
const Gfx peach_seg5_dl_05008428[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05000A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05008280.l, 1),
    gsSPLight(&peach_seg5_lights_05008280.a, 2),
    gsSPVertex(peach_seg5_vertex_05008298, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  4,  7,  3, 0x0),
    gsSP2Triangles( 7,  4,  8, 0x0,  8,  9,  7, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(11,  9,  8, 0x0,  6,  5, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x050084C0 - 0x05008560
const Gfx peach_seg5_dl_050084C0[] = {
    gsSPVertex(peach_seg5_vertex_05008358, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  5,  2, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 7,  0,  5, 0x0,  3,  6,  5, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  1,  0,  9, 0x0),
    gsSP2Triangles( 0,  7,  8, 0x0,  4,  1, 10, 0x0),
    gsSP2Triangles( 1,  9, 11, 0x0, 11, 10,  1, 0x0),
    gsSP2Triangles(12,  8,  7, 0x0, 12,  7,  6, 0x0),
    gsSP2Triangles(11,  8, 12, 0x0, 11,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008560 - 0x050085D0
const Gfx peach_seg5_dl_05008560[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05008428),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_050084C0),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x050085D0
static const Lights1 peach_seg5_lights_050085D0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x050085E8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050085E8, 0x0016d870, 76997, 0x00008648, 224);

// 0x050086C8 - 0x050087A8
const Gfx peach_seg5_dl_050086C8[] = {
    gsSPLight(&peach_seg5_lights_050085D0.l, 1),
    gsSPLight(&peach_seg5_lights_050085D0.a, 2),
    gsSPVertex(peach_seg5_vertex_050085E8, 14, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  8,  0,  4, 0x0),
    gsSP2Triangles( 9, 10,  0, 0x0,  0,  8,  9, 0x0),
    gsSP2Triangles( 1,  0, 10, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0,  9,  7, 11, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 10, 12,  5, 0x0),
    gsSP2Triangles(10,  5,  1, 0x0,  6, 13,  7, 0x0),
    gsSP2Triangles( 7, 13, 11, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles(13,  3,  5, 0x0, 12, 13,  5, 0x0),
    gsSP1Triangle( 6,  3, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x050087A8 - 0x050087D0
const Gfx peach_seg5_dl_050087A8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_050086C8),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x050087D0
static const Lights1 peach_seg5_lights_050087D0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x050087E8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050087E8, 0x0016d870, 76997, 0x00008848, 192);

// 0x050088A8
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_050088A8, 0x0016d870, 76997, 0x00008908, 208);

// 0x05008978 - 0x05008A10
const Gfx peach_seg5_dl_05008978[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05000A28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_050087D0.l, 1),
    gsSPLight(&peach_seg5_lights_050087D0.a, 2),
    gsSPVertex(peach_seg5_vertex_050087E8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  6,  7, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(10, 11,  2, 0x0, 11,  4,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008A10 - 0x05008AB0
const Gfx peach_seg5_dl_05008A10[] = {
    gsSPVertex(peach_seg5_vertex_050088A8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 5,  2,  1, 0x0,  6,  4,  2, 0x0),
    gsSP2Triangles( 3,  4,  7, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 0,  3,  8, 0x0,  9,  0,  8, 0x0),
    gsSP2Triangles( 1,  0,  9, 0x0,  1, 10, 11, 0x0),
    gsSP2Triangles(10,  1,  9, 0x0, 11,  5,  1, 0x0),
    gsSP2Triangles( 7,  4, 12, 0x0,  4,  6, 12, 0x0),
    gsSP2Triangles(12,  6, 11, 0x0,  6,  5, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008AB0 - 0x05008B20
const Gfx peach_seg5_dl_05008AB0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05008978),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_05008A10),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05008B20
static const Lights1 peach_seg5_lights_05008B20 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05008B38
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05008B38, 0x0016d870, 76997, 0x00008b98, 224);

// 0x05008C18 - 0x05008CF8
const Gfx peach_seg5_dl_05008C18[] = {
    gsSPLight(&peach_seg5_lights_05008B20.l, 1),
    gsSPLight(&peach_seg5_lights_05008B20.a, 2),
    gsSPVertex(peach_seg5_vertex_05008B38, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  0, 0x0,  5,  2,  6, 0x0),
    gsSP2Triangles( 4,  6,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 0,  5,  7, 0x0,  5,  8,  7, 0x0),
    gsSP2Triangles( 9,  8,  5, 0x0,  6,  9,  5, 0x0),
    gsSP2Triangles( 7, 10,  0, 0x0, 10,  1,  0, 0x0),
    gsSP2Triangles( 3, 11, 12, 0x0,  4,  3, 12, 0x0),
    gsSP2Triangles(10, 11,  3, 0x0,  1, 10,  3, 0x0),
    gsSP2Triangles( 9,  6,  4, 0x0, 12,  9,  4, 0x0),
    gsSP2Triangles(13,  9, 12, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles( 9, 13,  8, 0x0, 10,  7, 13, 0x0),
    gsSP2Triangles( 7,  8, 13, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008CF8 - 0x05008D20
const Gfx peach_seg5_dl_05008CF8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_05008C18),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05008D20
static const Lights1 peach_seg5_lights_05008D20 = gdSPDefLights1(
    0x0b, 0x1a, 0x67,
    0x16, 0x35, 0xce, 0x28, 0x28, 0x28
);

// 0x05008D38
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05008D38, 0x0016d870, 76997, 0x00008d98, 256);

// 0x05008E38 - 0x05008F20
const Gfx peach_seg5_dl_05008E38[] = {
    gsSPLight(&peach_seg5_lights_05008D20.l, 1),
    gsSPLight(&peach_seg5_lights_05008D20.a, 2),
    gsSPVertex(peach_seg5_vertex_05008D38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  1, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  5,  4,  8, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  6,  7,  9, 0x0),
    gsSP2Triangles( 1,  6,  9, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 7, 11, 10, 0x0,  7,  8, 11, 0x0),
    gsSP2Triangles( 2,  9, 12, 0x0,  9, 10, 12, 0x0),
    gsSP2Triangles( 1,  9,  2, 0x0,  2, 12, 13, 0x0),
    gsSP2Triangles( 8, 14, 11, 0x0,  8, 15, 14, 0x0),
    gsSP2Triangles( 4, 15,  8, 0x0,  4,  0, 15, 0x0),
    gsSP2Triangles( 0,  2, 15, 0x0, 15,  2, 13, 0x0),
    gsSP1Triangle(15, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05008F20 - 0x05008F48
const Gfx peach_seg5_dl_05008F20[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_05008E38),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05008F48
static const Lights1 peach_seg5_lights_05008F48 = gdSPDefLights1(
    0x0b, 0x1a, 0x67,
    0x16, 0x35, 0xce, 0x28, 0x28, 0x28
);

// 0x05008F60
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05008F60, 0x0016d870, 76997, 0x00008fc0, 256);

// 0x05009060 - 0x05009148
const Gfx peach_seg5_dl_05009060[] = {
    gsSPLight(&peach_seg5_lights_05008F48.l, 1),
    gsSPLight(&peach_seg5_lights_05008F48.a, 2),
    gsSPVertex(peach_seg5_vertex_05008F60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  8,  5,  6, 0x0),
    gsSP2Triangles( 4,  2,  6, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 9,  2,  4, 0x0,  1,  8,  6, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0, 10, 11,  3, 0x0),
    gsSP2Triangles(10,  3,  7, 0x0, 11,  9,  3, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 12,  0,  9, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0, 12, 13,  0, 0x0),
    gsSP2Triangles(13, 14,  0, 0x0,  0, 14,  1, 0x0),
    gsSP2Triangles(13, 15, 14, 0x0, 14,  8,  1, 0x0),
    gsSP2Triangles(14,  7,  8, 0x0, 15, 10,  7, 0x0),
    gsSP1Triangle(15,  7, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05009148 - 0x05009170
const Gfx peach_seg5_dl_05009148[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_05009060),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05009170
static const Lights1 peach_seg5_lights_05009170 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05009188
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009188, 0x0016d870, 76997, 0x000091e8, 256);

// 0x05009288
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009288, 0x0016d870, 76997, 0x000092e8, 256);

// 0x05009388 - 0x05009500
const Gfx peach_seg5_dl_05009388[] = {
    gsSPLight(&peach_seg5_lights_05009170.l, 1),
    gsSPLight(&peach_seg5_lights_05009170.a, 2),
    gsSPVertex(peach_seg5_vertex_05009188, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  0, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 7,  0,  6, 0x0,  8,  1,  0, 0x0),
    gsSP2Triangles( 9,  3, 10, 0x0, 10,  3,  2, 0x0),
    gsSP2Triangles(11,  4,  3, 0x0,  9, 11,  3, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4, 12,  6, 0x0),
    gsSP2Triangles(11, 12,  4, 0x0,  6, 12, 11, 0x0),
    gsSP2Triangles(13,  8,  7, 0x0,  6, 14,  7, 0x0),
    gsSP2Triangles( 7, 14, 13, 0x0, 14,  6, 11, 0x0),
    gsSP1Triangle(15,  9, 10, 0x0),
    gsSPVertex(peach_seg5_vertex_05009288, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 5,  3,  1, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 0,  4,  8, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  9,  6, 0x0, 10,  9,  4, 0x0),
    gsSP2Triangles( 8,  1,  0, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles( 7, 13,  8, 0x0, 14,  8, 13, 0x0),
    gsSP2Triangles(14, 11,  8, 0x0,  8, 12,  1, 0x0),
    gsSP2Triangles( 5,  1, 12, 0x0, 11,  5, 12, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  7,  6, 15, 0x0),
    gsSP1Triangle( 6, 10, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x05009500 - 0x05009528
const Gfx peach_seg5_dl_05009500[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_05009388),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05009528
static const Lights1 peach_seg5_lights_05009528 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05009540
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009540, 0x0016d870, 76997, 0x000095a0, 256);

// 0x05009640
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009640, 0x0016d870, 76997, 0x000096a0, 256);

// 0x05009740
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009740, 0x0016d870, 76997, 0x000097a0, 128);

// 0x050097C0 - 0x05009940
const Gfx peach_seg5_dl_050097C0[] = {
    gsSPLight(&peach_seg5_lights_05009528.l, 1),
    gsSPLight(&peach_seg5_lights_05009528.a, 2),
    gsSPVertex(peach_seg5_vertex_05009540, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  2,  6,  4, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  9,  5,  3, 0x0),
    gsSP2Triangles( 9,  3,  7, 0x0,  3,  4,  8, 0x0),
    gsSP2Triangles( 9, 10,  5, 0x0,  1,  0,  5, 0x0),
    gsSP2Triangles( 5, 11, 12, 0x0,  1,  5, 12, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  4,  6,  1, 0x0),
    gsSP2Triangles(10, 13, 14, 0x0,  4,  1, 15, 0x0),
    gsSP1Triangle(12, 15,  1, 0x0),
    gsSPVertex(peach_seg5_vertex_05009640, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  6,  8,  4, 0x0),
    gsSP2Triangles( 2,  9,  5, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 9, 10,  5, 0x0,  5, 10, 11, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  3,  4, 12, 0x0),
    gsSP2Triangles( 1,  9,  2, 0x0,  1, 11,  9, 0x0),
    gsSP2Triangles(13, 14, 15, 0x0,  7, 15, 14, 0x0),
    gsSPVertex(peach_seg5_vertex_05009740, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  2,  3, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  5,  4,  6, 0x0),
    gsSP1Triangle( 5,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05009940 - 0x05009968
const Gfx peach_seg5_dl_05009940[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPDisplayList(peach_seg5_dl_050097C0),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

// 0x05009968
static const Lights1 peach_seg5_lights_05009968 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05009980
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009980, 0x0016d870, 76997, 0x000099e0, 240);

// 0x05009A70
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009A70, 0x0016d870, 76997, 0x00009ad0, 240);

// 0x05009B60
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009B60, 0x0016d870, 76997, 0x00009bc0, 256);

// 0x05009C60
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009C60, 0x0016d870, 76997, 0x00009cc0, 240);

// 0x05009D50
ROM_ASSET_LOAD_VTX(peach_seg5_vertex_05009D50, 0x0016d870, 76997, 0x00009db0, 208);

// 0x05009E20 - 0x0500A0A8
const Gfx peach_seg5_dl_05009E20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, peach_seg5_texture_05004028),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&peach_seg5_lights_05009968.l, 1),
    gsSPLight(&peach_seg5_lights_05009968.a, 2),
    gsSPVertex(peach_seg5_vertex_05009980, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 3,  2,  5, 0x0,  5,  6,  3, 0x0),
    gsSP2Triangles( 7,  0,  3, 0x0,  3,  8,  7, 0x0),
    gsSP2Triangles( 3,  6,  9, 0x0,  9,  8,  3, 0x0),
    gsSP2Triangles( 1, 10,  4, 0x0, 10, 11,  4, 0x0),
    gsSP2Triangles( 4, 12,  5, 0x0, 13, 12,  4, 0x0),
    gsSP2Triangles(11, 14,  4, 0x0,  4, 14, 13, 0x0),
    gsSPVertex(peach_seg5_vertex_05009A70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  5,  9,  7, 0x0),
    gsSP2Triangles(10,  9,  5, 0x0,  5, 11, 10, 0x0),
    gsSP2Triangles( 8, 11,  5, 0x0,  8, 12, 11, 0x0),
    gsSP2Triangles(10, 11, 13, 0x0, 12, 13, 11, 0x0),
    gsSP1Triangle(13, 14, 10, 0x0),
    gsSPVertex(peach_seg5_vertex_05009B60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  1,  9, 10, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0,  9,  1,  0, 0x0),
    gsSP2Triangles(11,  9,  8, 0x0, 12, 11,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  2,  1, 10, 0x0),
    gsSP2Triangles(13,  2, 10, 0x0,  0,  2, 14, 0x0),
    gsSP2Triangles(14,  2, 13, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(peach_seg5_vertex_05009C60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  5,  0,  4, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles(10,  5,  8, 0x0,  5,  6,  9, 0x0),
    gsSP2Triangles( 9,  6,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 12, 11, 0x0),
    gsSPVertex(peach_seg5_vertex_05009D50, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 4,  7,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 4,  9,  7, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11,  3, 0x0,  3, 11,  1, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0,  2, 12,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A0A8 - 0x0500A128
const Gfx peach_seg5_dl_0500A0A8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05009E20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

#ifndef VERSION_JP
// 0x0500A188 - 0x0500A210
const Gfx peach_seg5_us_dl_0500A188[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(peach_seg5_dl_05009E20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};
#endif
