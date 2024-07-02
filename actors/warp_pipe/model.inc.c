#include "pc/rom_assets.h"
// Warp Pipe

// 0x030079E8
static const Lights1 warp_pipe_seg3_lights_030079E8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x03007A00
ROM_ASSET_LOAD_VTX(warp_pipe_seg3_vertex_03007A00, 0x00201410, 96653, 0x00007a00, 240);

// 0x03007AF0
ROM_ASSET_LOAD_VTX(warp_pipe_seg3_vertex_03007AF0, 0x00201410, 96653, 0x00007af0, 240);

// 0x03007BE0
ROM_ASSET_LOAD_VTX(warp_pipe_seg3_vertex_03007BE0, 0x00201410, 96653, 0x00007be0, 240);

// 0x03007CD0
ROM_ASSET_LOAD_VTX(warp_pipe_seg3_vertex_03007CD0, 0x00201410, 96653, 0x00007cd0, 240);

// 0x03007DC0
ROM_ASSET_LOAD_VTX(warp_pipe_seg3_vertex_03007DC0, 0x00201410, 96653, 0x00007dc0, 128);

// 0x03007E40
ROM_ASSET_LOAD_TEXTURE(warp_pipe_seg3_texture_03007E40, "actors/warp_pipe/warp_pipe_side.rgba16.inc.c", 0x00201410, 96653, 0x00007e40, 4096);

// 0x03008E40 - 0x03008F98
const Gfx warp_pipe_seg3_dl_03008E40[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, warp_pipe_seg3_texture_03007E40),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&warp_pipe_seg3_lights_030079E8.l, 1),
    gsSPLight(&warp_pipe_seg3_lights_030079E8.a, 2),
    gsSPVertex(warp_pipe_seg3_vertex_03007A00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(warp_pipe_seg3_vertex_03007AF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(warp_pipe_seg3_vertex_03007BE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(warp_pipe_seg3_vertex_03007CD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(warp_pipe_seg3_vertex_03007DC0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x03008F98 - 0x03008FF8
const Gfx warp_pipe_seg3_dl_03008F98[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(warp_pipe_seg3_dl_03008E40),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x03008FF8
static const Lights1 warp_pipe_seg3_lights_03008FF8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x03009010
static const Lights1 warp_pipe_seg3_lights_03009010 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x03009028
ROM_ASSET_LOAD_VTX(warp_pipe_seg3_vertex_03009028, 0x00201410, 96653, 0x00009028, 256);

// 0x03009128
ROM_ASSET_LOAD_VTX(warp_pipe_seg3_vertex_03009128, 0x00201410, 96653, 0x00009128, 64);

// 0x03009168
ROM_ASSET_LOAD_TEXTURE(warp_pipe_seg3_texture_03009168, "actors/warp_pipe/warp_pipe_top.rgba16.inc.c", 0x00201410, 96653, 0x00009168, 2048);

// 0x03009968 - 0x03009A20
const Gfx warp_pipe_seg3_dl_03009968[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, warp_pipe_seg3_texture_03009168),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&warp_pipe_seg3_lights_03008FF8.l, 1),
    gsSPLight(&warp_pipe_seg3_lights_03008FF8.a, 2),
    gsSPVertex(warp_pipe_seg3_vertex_03009028, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  8,  9,  4, 0x0),
    gsSP2Triangles( 7,  5, 10, 0x0, 11,  7, 10, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14,  9, 0x0),
    gsSP2Triangles( 0,  2, 15, 0x0, 13,  0, 15, 0x0),
    gsSP2Triangles(13, 15, 14, 0x0, 13,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x03009A20 - 0x03009A50
const Gfx warp_pipe_seg3_dl_03009A20[] = {
    gsSPLight(&warp_pipe_seg3_lights_03009010.l, 1),
    gsSPLight(&warp_pipe_seg3_lights_03009010.a, 2),
    gsSPVertex(warp_pipe_seg3_vertex_03009128, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x03009A50 - 0x03009AC8
const Gfx warp_pipe_seg3_dl_03009A50[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(warp_pipe_seg3_dl_03009968),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(warp_pipe_seg3_dl_03009A20),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
