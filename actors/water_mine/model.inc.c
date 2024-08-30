#include "pc/rom_assets.h"
// Water Mine (unused)

// 0x0600A4E0
static const Lights1 water_mine_seg6_lights_0600A4E0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0600A4F8
ROM_ASSET_LOAD_TEXTURE(water_mine_seg6_texture_0600A4F8, "actors/water_mine/water_mine_left_side_unused.rgba16.inc.c", 0x00188440, 199722, 0x00057c10, 4096);

// 0x0600B4F8
ROM_ASSET_LOAD_TEXTURE(water_mine_seg6_texture_0600B4F8, "actors/water_mine/water_mine_right_side_unused.rgba16.inc.c", 0x00188440, 199722, 0x00058c10, 4096);

// 0x0600C4F8
ROM_ASSET_LOAD_TEXTURE(water_mine_seg6_texture_0600C4F8, "actors/water_mine/water_mine_spike_unused.rgba16.inc.c", 0x00188440, 199722, 0x00059c10, 2048);

// 0x0600CCF8
ROM_ASSET_LOAD_VTX(water_mine_seg6_vertex_0600CCF8, 0x001b9cc0, 41188, 0x0000ccf8, 64);

// 0x0600CD38
ROM_ASSET_LOAD_VTX(water_mine_seg6_vertex_0600CD38, 0x001b9cc0, 41188, 0x0000cd38, 64);

// 0x0600CD78
ROM_ASSET_LOAD_VTX(water_mine_seg6_vertex_0600CD78, 0x00188440, 199722, 0x0005a490, 240);

// 0x0600CE68
ROM_ASSET_LOAD_VTX(water_mine_seg6_vertex_0600CE68, 0x00188440, 199722, 0x0005a580, 240);

// 0x0600CF58
ROM_ASSET_LOAD_VTX(water_mine_seg6_vertex_0600CF58, 0x00188440, 199722, 0x0005a670, 240);

// 0x0600D048
ROM_ASSET_LOAD_VTX(water_mine_seg6_vertex_0600D048, 0x00188440, 199722, 0x0005a760, 240);

// 0x0600D138
ROM_ASSET_LOAD_VTX(water_mine_seg6_vertex_0600D138, 0x00188440, 199722, 0x0005a850, 192);

// 0x0600D1F8 - 0x0600D230
const Gfx water_mine_seg6_dl_0600D1F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_mine_seg6_texture_0600A4F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(water_mine_seg6_vertex_0600CCF8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600D230 - 0x0600D268
const Gfx water_mine_seg6_dl_0600D230[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_mine_seg6_texture_0600B4F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(water_mine_seg6_vertex_0600CD38, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600D268 - 0x0600D2E0
const Gfx water_mine_seg6_dl_0600D268[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(water_mine_seg6_dl_0600D1F8),
    gsSPDisplayList(water_mine_seg6_dl_0600D230),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0600D2E0 - 0x0600D3F8
const Gfx water_mine_seg6_dl_0600D2E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_mine_seg6_texture_0600C4F8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&water_mine_seg6_lights_0600A4E0.l, 1),
    gsSPLight(&water_mine_seg6_lights_0600A4E0.a, 2),
    gsSPVertex(water_mine_seg6_vertex_0600CD78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(water_mine_seg6_vertex_0600CE68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(water_mine_seg6_vertex_0600CF58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(water_mine_seg6_vertex_0600D048, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(water_mine_seg6_vertex_0600D138, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0600D3F8 - 0x0600D458
const Gfx water_mine_seg6_dl_0600D3F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(water_mine_seg6_dl_0600D2E0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
