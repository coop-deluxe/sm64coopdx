#include "pc/rom_assets.h"
// Tree

// 0x0302DE10

// 0x0302DE28
ROM_ASSET_LOAD_TEXTURE(tree_seg3_texture_0302DE28, "actors/tree/tree_left_side.rgba16.inc.c", 0x00201410, 96653, 0x0002de28, 4096);

// 0x0302EE28
ROM_ASSET_LOAD_TEXTURE(tree_seg3_texture_0302EE28, "actors/tree/tree_right_side.rgba16.inc.c", 0x00201410, 96653, 0x0002ee28, 4096);

// 0x0302FE28
ROM_ASSET_LOAD_VTX(tree_seg3_vertex_0302FE28, 0x00201410, 96653, 0x0002fe28, 48);

// 0x0302FE58
ROM_ASSET_LOAD_VTX(tree_seg3_vertex_0302FE58, 0x00201410, 96653, 0x0002fe58, 48);

// 0x0302FE88 - 0x0302FEB8
const Gfx tree_seg3_dl_0302FE88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_0302DE28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(tree_seg3_vertex_0302FE28, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0302FEB8 - 0x0302FEE8
const Gfx tree_seg3_dl_0302FEB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_0302EE28),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(tree_seg3_vertex_0302FE58, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0302FEE8 - 0x0302FF60
const Gfx tree_seg3_dl_0302FEE8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(tree_seg3_dl_0302FE88),
    gsSPDisplayList(tree_seg3_dl_0302FEB8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0302FF60
ROM_ASSET_LOAD_TEXTURE(tree_seg3_texture_0302FF60, "actors/tree/pine_tree.rgba16.inc.c", 0x00201410, 96653, 0x0002ff60, 4096);

// 0x03030F60
ROM_ASSET_LOAD_VTX(tree_seg3_vertex_03030F60, 0x00201410, 96653, 0x00030f60, 64);

// 0x03030FA0 - 0x03031048
const Gfx tree_seg3_dl_03030FA0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_0302FF60),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tree_seg3_lights_0302DE10.l, 1),
    gsSPLight(&tree_seg3_lights_0302DE10.a, 2),
    gsSPVertex(tree_seg3_vertex_03030F60, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03031048
ROM_ASSET_LOAD_TEXTURE(tree_seg3_texture_03031048, "actors/tree/snowy_pine_tree.rgba16.inc.c", 0x00201410, 96653, 0x00031048, 4096);

// 0x03032048
ROM_ASSET_LOAD_VTX(tree_seg3_vertex_03032048, 0x00201410, 96653, 0x00030f60, 64);

// 0x03032088 - 0x03032130
const Gfx tree_seg3_dl_03032088[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_03031048),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tree_seg3_lights_0302DE10.l, 1),
    gsSPLight(&tree_seg3_lights_0302DE10.a, 2),
    gsSPVertex(tree_seg3_vertex_03032048, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03032130
ROM_ASSET_LOAD_VTX(tree_seg3_vertex_03032130, 0x00201410, 96653, 0x00030f60, 64);

// 0x03032170 - 0x03032218
const Gfx tree_seg3_dl_03032170[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_0302FF60),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tree_seg3_lights_0302DE10.l, 1),
    gsSPLight(&tree_seg3_lights_0302DE10.a, 2),
    gsSPVertex(tree_seg3_vertex_03032130, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03032218
ROM_ASSET_LOAD_TEXTURE(tree_seg3_texture_03032218, "actors/tree/palm_tree.rgba16.inc.c", 0x00201410, 96653, 0x00032218, 4096);

// 0x03033218
ROM_ASSET_LOAD_VTX(tree_seg3_vertex_03033218, 0x00201410, 96653, 0x00033218, 64);

// 0x03033258 - 0x03033300
const Gfx tree_seg3_dl_03033258[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tree_seg3_texture_03032218),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&tree_seg3_lights_0302DE10.l, 1),
    gsSPLight(&tree_seg3_lights_0302DE10.a, 2),
    gsSPVertex(tree_seg3_vertex_03033218, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
