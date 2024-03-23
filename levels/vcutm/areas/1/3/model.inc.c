#include "pc/rom_assets.h"
// 0x07008140 - 0x07008220
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07008140, 0x0045c600, 19475, 0x00008140, 224);

// 0x07008220 - 0x07008300
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07008220, 0x0045c600, 19475, 0x00008220, 224);

// 0x07008300 - 0x070083F0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07008300, 0x0045c600, 19475, 0x00008300, 240);

// 0x070083F0 - 0x070084E0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070083F0, 0x0045c600, 19475, 0x000083f0, 240);

// 0x070084E0 - 0x070085D0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070084E0, 0x0045c600, 19475, 0x000084e0, 240);

// 0x070085D0 - 0x070086D0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070085D0, 0x0045c600, 19475, 0x000085d0, 256);

// 0x070086D0 - 0x070087D0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070086D0, 0x0045c600, 19475, 0x000086d0, 256);

// 0x070087D0 - 0x070088D0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070087D0, 0x0045c600, 19475, 0x000087d0, 256);

// 0x070088D0 - 0x070089D0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070088D0, 0x0045c600, 19475, 0x000088d0, 256);

// 0x070089D0 - 0x07008AC0
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_070089D0, 0x0045c600, 19475, 0x000089d0, 240);

// 0x07008AC0 - 0x07008B20
ROM_ASSET_LOAD_VTX(vcutm_seg7_vertex_07008AC0, 0x0045c600, 19475, 0x00008ac0, 96);

// 0x07008B20 - 0x07008E10
static const Gfx vcutm_seg7_dl_07008B20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, vcutm_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(vcutm_seg7_vertex_07008140, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07008220, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07008300, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070083F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 9,  8, 12, 0x0,  0, 13, 14, 0x0),
    gsSP1Triangle( 0,  2, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070084E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 7,  6,  3, 0x0,  9,  0, 10, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070085D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  2,  5, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle(13,  6, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070086D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070087D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  3, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070088D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(vcutm_seg7_vertex_070089D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_07008AC0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008E10 - 0x07008E80
const Gfx vcutm_seg7_dl_07008E10[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(vcutm_seg7_dl_07008B20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
