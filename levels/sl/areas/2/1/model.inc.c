#include "pc/rom_assets.h"
// 0x0700A9B0 - 0x0700A9C8
static const Lights1 sl_seg7_lights_0700A9B0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700A9C8 - 0x0700A9E0
static const Lights1 sl_seg7_lights_0700A9C8 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0700A9E0 - 0x0700AAE0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700A9E0, 0x00405fb0, 34952, 0x0000a9e0, 256);

// 0x0700AAE0 - 0x0700ABE0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700AAE0, 0x00405fb0, 34952, 0x0000aae0, 256);

// 0x0700ABE0 - 0x0700ACC0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700ABE0, 0x00405fb0, 34952, 0x0000abe0, 224);

// 0x0700ACC0 - 0x0700ADB0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700ACC0, 0x00405fb0, 34952, 0x0000acc0, 240);

// 0x0700ADB0 - 0x0700AEA0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700ADB0, 0x00405fb0, 34952, 0x0000adb0, 240);

// 0x0700AEA0 - 0x0700AFA0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700AEA0, 0x00405fb0, 34952, 0x0000aea0, 256);

// 0x0700AFA0 - 0x0700B080
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700AFA0, 0x00405fb0, 34952, 0x0000afa0, 224);

// 0x0700B080 - 0x0700B170
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B080, 0x00405fb0, 34952, 0x0000b080, 240);

// 0x0700B170 - 0x0700B250
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B170, 0x00405fb0, 34952, 0x0000b170, 224);

// 0x0700B250 - 0x0700B330
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B250, 0x00405fb0, 34952, 0x0000b250, 224);

// 0x0700B330 - 0x0700B420
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B330, 0x00405fb0, 34952, 0x0000b330, 240);

// 0x0700B420 - 0x0700B510
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B420, 0x00405fb0, 34952, 0x0000b420, 240);

// 0x0700B510 - 0x0700B5D0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B510, 0x00405fb0, 34952, 0x0000b510, 192);

// 0x0700B5D0 - 0x0700B620
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B5D0, 0x00405fb0, 34952, 0x0000b5d0, 80);

// 0x0700B620 - 0x0700B6C0
ROM_ASSET_LOAD_VTX(sl_seg7_vertex_0700B620, 0x00405fb0, 34952, 0x0000b620, 160);

// 0x0700B6C0 - 0x0700BA70
static const Gfx sl_seg7_dl_0700B6C0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sl_seg7_lights_0700A9B0.l, 1),
    gsSPLight(&sl_seg7_lights_0700A9B0.a, 2),
    gsSPVertex(sl_seg7_vertex_0700A9E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(sl_seg7_vertex_0700AAE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_0700ABE0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_0700ACC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(sl_seg7_vertex_0700ADB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_0700AEA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  6,  3, 0x0),
    gsSP2Triangles(11, 12,  6, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(sl_seg7_vertex_0700AFA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_0700B080, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(sl_seg7_vertex_0700B170, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(sl_seg7_vertex_0700B250, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(sl_seg7_vertex_0700B330, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(sl_seg7_vertex_0700B420, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(sl_seg7_vertex_0700B510, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  0, 11,  9, 0x0),
    gsSP1Triangle( 0,  2, 11, 0x0),
    gsSPLight(&sl_seg7_lights_0700A9C8.l, 1),
    gsSPLight(&sl_seg7_lights_0700A9C8.a, 2),
    gsSPVertex(sl_seg7_vertex_0700B5D0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP1Triangle( 0,  4,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BA70 - 0x0700BAE8
static const Gfx sl_seg7_dl_0700BA70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&sl_seg7_lights_0700A9B0.l, 1),
    gsSPLight(&sl_seg7_lights_0700A9B0.a, 2),
    gsSPVertex(sl_seg7_vertex_0700B620, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 8,  3,  0, 0x0,  8,  7,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BAE8 - 0x0700BB68
const Gfx sl_seg7_dl_0700BAE8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_0700B6C0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sl_seg7_dl_0700BA70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
