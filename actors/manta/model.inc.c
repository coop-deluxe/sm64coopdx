#include "pc/rom_assets.h"
// Manta Ray

// 0x05001758
static const Lights1 manta_seg5_lights_05001758 = gdSPDefLights1(
    0x31, 0x3b, 0x3b,
    0xc6, 0xee, 0xed, 0x28, 0x28, 0x28
);

// 0x05001770
static const Lights1 manta_seg5_lights_05001770 = gdSPDefLights1(
    0x00, 0x16, 0x18,
    0x03, 0x5b, 0x63, 0x28, 0x28, 0x28
);

// Unreferenced light group
static const Lights1 manta_lights_unused = gdSPDefLights1(
    0x3f, 0x3f, 0x35,
    0xff, 0xff, 0xd7, 0x28, 0x28, 0x28
);

// 0x050017A0
ROM_ASSET_LOAD_TEXTURE(manta_seg5_texture_050017A0, "actors/manta/manta_fin_corner.rgba16.inc.c", 0x0013b910, 41727, 0x000017a0, 2048);

// 0x05001FA0
ROM_ASSET_LOAD_TEXTURE(manta_seg5_texture_05001FA0, "actors/manta/manta_gills.rgba16.inc.c", 0x0013b910, 41727, 0x00001fa0, 4096);

// 0x05002FA0
ROM_ASSET_LOAD_TEXTURE(manta_seg5_texture_05002FA0, "actors/manta/manta_eye.rgba16.inc.c", 0x0013b910, 41727, 0x00002fa0, 2048);

// 0x050037A0
ROM_ASSET_LOAD_TEXTURE(manta_seg5_texture_050037A0, "actors/manta/manta_fin_edge.rgba16.inc.c", 0x0013b910, 41727, 0x000037a0, 4096);

// 0x050047A0
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050047A0, 0x0013b910, 41727, 0x000047a0, 256);

// 0x050048A0
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050048A0, 0x0013b910, 41727, 0x000048a0, 192);

// 0x05004960 - 0x050049C8
const Gfx manta_seg5_dl_05004960[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_05002FA0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050047A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x050049C8 - 0x05004A70
const Gfx manta_seg5_dl_050049C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050017A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050048A0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 1,  0,  5, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  5,  4, 0x0,  3,  4,  6, 0x0),
    gsSP2Triangles( 7,  8,  2, 0x0,  8,  0,  2, 0x0),
    gsSP2Triangles( 6,  4,  9, 0x0,  4,  5,  9, 0x0),
    gsSP2Triangles( 5, 10,  9, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 0, 10,  5, 0x0,  0,  8, 10, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0,  8, 11, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004A70 - 0x05004AE8
const Gfx manta_seg5_dl_05004A70[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05004960),
    gsSPDisplayList(manta_seg5_dl_050049C8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05004AE8
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05004AE8, 0x0013b910, 41727, 0x00004ae8, 256);

// 0x05004BE8
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05004BE8, 0x0013b910, 41727, 0x00004be8, 192);

// 0x05004CA8 - 0x05004D10
const Gfx manta_seg5_dl_05004CA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_05002FA0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05004AE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  7,  6,  4, 0x0),
    gsSP2Triangles( 8,  6,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004D10 - 0x05004DB8
const Gfx manta_seg5_dl_05004D10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050017A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05004BE8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  7,  4,  5, 0x0),
    gsSP2Triangles( 8,  3,  4, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 9,  7,  6, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 8, 10,  3, 0x0, 10,  1,  3, 0x0),
    gsSP2Triangles(11,  2,  1, 0x0, 10, 11,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004DB8 - 0x05004E30
const Gfx manta_seg5_dl_05004DB8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05004CA8),
    gsSPDisplayList(manta_seg5_dl_05004D10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05004E30
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05004E30, 0x0013b910, 41727, 0x00004e30, 48);

// 0x05004E60 - 0x05004E90
const Gfx manta_seg5_dl_05004E60[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05004E30, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05004E90 - 0x05004F00
const Gfx manta_seg5_dl_05004E90[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05004E60),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05004F00
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05004F00, 0x0013b910, 41727, 0x00004f00, 160);

// 0x05004FA0 - 0x05005038
const Gfx manta_seg5_dl_05004FA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050017A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05004F00, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 3,  0,  5, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  5,  2, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9,  2,  4, 0x0),
    gsSP2Triangles( 4,  7,  9, 0x0,  2,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005038 - 0x050050A8
const Gfx manta_seg5_dl_05005038[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05004FA0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x050050A8
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050050A8, 0x0013b910, 41727, 0x000050a8, 112);

// 0x05005118
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005118, 0x0013b910, 41727, 0x00005118, 160);

// 0x050051B8
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050051B8, 0x0013b910, 41727, 0x000051b8, 144);

// 0x05005248 - 0x05005288
const Gfx manta_seg5_dl_05005248[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050017A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050050A8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  3,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005288 - 0x05005308
const Gfx manta_seg5_dl_05005288[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05005118, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 5,  3,  6, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 7,  3,  0, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0,  0,  9,  7, 0x0),
    gsSP1Triangle( 2,  9,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005308 - 0x05005358
const Gfx manta_seg5_dl_05005308[] = {
    gsSPVertex(manta_seg5_vertex_050051B8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 8,  4,  7, 0x0,  5,  4,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005358 - 0x050053F0
const Gfx manta_seg5_dl_05005358[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05005248),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05005288),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(manta_seg5_dl_05005308),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x050053F0
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050053F0, 0x0013b910, 41727, 0x000053f0, 128);

// 0x05005470
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005470, 0x0013b910, 41727, 0x00005470, 128);

// 0x050054F0 - 0x05005558
const Gfx manta_seg5_dl_050054F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050053F0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 0,  4,  6, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 4,  5,  7, 0x0,  4,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005558 - 0x050055A8
const Gfx manta_seg5_dl_05005558[] = {
    gsSPVertex(manta_seg5_vertex_05005470, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 5,  6,  0, 0x0,  6,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  3,  5, 0x0),
    gsSP2Triangles( 7,  2,  1, 0x0,  7,  4,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x050055A8 - 0x05005620
const Gfx manta_seg5_dl_050055A8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_050054F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(manta_seg5_dl_05005558),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05005620
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005620, 0x0013b910, 41727, 0x00005620, 96);

// 0x05005680
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005680, 0x0013b910, 41727, 0x00005680, 96);

// 0x050056E0 - 0x05005730
const Gfx manta_seg5_dl_050056E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05005620, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  1,  3,  5, 0x0),
    gsSP1Triangle( 5,  2,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005730 - 0x05005768
const Gfx manta_seg5_dl_05005730[] = {
    gsSPVertex(manta_seg5_vertex_05005680, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 3,  0,  2, 0x0,  4,  5,  0, 0x0),
    gsSP1Triangle( 5,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005768 - 0x050057E0
const Gfx manta_seg5_dl_05005768[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_050056E0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(manta_seg5_dl_05005730),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x050057E0
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050057E0, 0x0013b910, 41727, 0x000057e0, 160);

// 0x05005880 - 0x05005918
const Gfx manta_seg5_dl_05005880[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050017A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050057E0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  1, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  4,  2,  1, 0x0),
    gsSP2Triangles( 7,  5,  6, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 3,  5,  7, 0x0,  7,  0,  8, 0x0),
    gsSP2Triangles( 2,  8,  0, 0x0,  3,  7,  9, 0x0),
    gsSP2Triangles( 9,  4,  3, 0x0,  8,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005918 - 0x05005988
const Gfx manta_seg5_dl_05005918[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05005880),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05005988
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005988, 0x0013b910, 41727, 0x00005988, 112);

// 0x050059F8
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050059F8, 0x0013b910, 41727, 0x000059f8, 160);

// 0x05005A98
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005A98, 0x0013b910, 41727, 0x00005a98, 144);

// 0x05005B28 - 0x05005B68
const Gfx manta_seg5_dl_05005B28[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050017A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05005988, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005B68 - 0x05005BE8
const Gfx manta_seg5_dl_05005B68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050059F8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  6,  4,  2, 0x0),
    gsSP2Triangles( 3,  7,  4, 0x0,  2,  4,  7, 0x0),
    gsSP2Triangles( 6,  2,  1, 0x0,  8,  7,  3, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9,  2, 0x0),
    gsSP1Triangle( 2,  9,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005BE8 - 0x05005C38
const Gfx manta_seg5_dl_05005BE8[] = {
    gsSPVertex(manta_seg5_vertex_05005A98, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 7,  4,  3, 0x0,  1,  8,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005C38 - 0x05005CD0
const Gfx manta_seg5_dl_05005C38[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05005B28),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05005B68),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(manta_seg5_dl_05005BE8),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05005CD0
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005CD0, 0x0013b910, 41727, 0x00005cd0, 128);

// 0x05005D50
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005D50, 0x0013b910, 41727, 0x00005d50, 128);

// 0x05005DD0 - 0x05005E38
const Gfx manta_seg5_dl_05005DD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05005CD0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  1,  6, 0x0),
    gsSP2Triangles( 7,  6,  1, 0x0,  0,  7,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005E38 - 0x05005E88
const Gfx manta_seg5_dl_05005E38[] = {
    gsSPVertex(manta_seg5_vertex_05005D50, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  4,  0,  2, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  4,  2,  6, 0x0),
    gsSP2Triangles( 2,  5,  7, 0x0,  7,  6,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05005E88 - 0x05005F00
const Gfx manta_seg5_dl_05005E88[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05005DD0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(manta_seg5_dl_05005E38),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05005F00
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005F00, 0x0013b910, 41727, 0x00005f00, 96);

// 0x05005F60
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05005F60, 0x0013b910, 41727, 0x00005f60, 96);

// 0x05005FC0 - 0x05006010
const Gfx manta_seg5_dl_05005FC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05005F00, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  4,  0,  5, 0x0),
    gsSP1Triangle( 2,  5,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006010 - 0x05006048
const Gfx manta_seg5_dl_05006010[] = {
    gsSPVertex(manta_seg5_vertex_05005F60, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  0,  2,  5, 0x0),
    gsSP1Triangle( 5,  4,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006048 - 0x050060C0
const Gfx manta_seg5_dl_05006048[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05005FC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(manta_seg5_dl_05006010),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x050060C0
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050060C0, 0x0013b910, 41727, 0x000060c0, 224);

// 0x050061A0
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050061A0, 0x0013b910, 41727, 0x000061a0, 240);

// 0x05006290
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05006290, 0x0013b910, 41727, 0x00006290, 224);

// 0x05006370
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05006370, 0x0013b910, 41727, 0x00006370, 176);

// 0x05006420
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05006420, 0x0013b910, 41727, 0x00006420, 240);

// 0x05006510 - 0x05006588
const Gfx manta_seg5_dl_05006510[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050017A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050060C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles( 4,  6, 10, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0, 13, 12, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006588 - 0x050065F0
const Gfx manta_seg5_dl_05006588[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_05001FA0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_050061A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  7, 13, 0x0, 11, 10, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x050065F0 - 0x050066D0
const Gfx manta_seg5_dl_050065F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, manta_seg5_texture_050037A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(manta_seg5_vertex_05006290, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  2,  5,  8, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  6,  5,  2, 0x0),
    gsSP2Triangles( 5,  7,  3, 0x0,  6,  2,  9, 0x0),
    gsSP2Triangles(10,  6,  9, 0x0,  7,  6, 11, 0x0),
    gsSP2Triangles(10, 11,  6, 0x0,  8, 12,  0, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0, 13,  1,  0, 0x0),
    gsSP1Triangle( 2,  1,  9, 0x0),
    gsSPVertex(manta_seg5_vertex_05006370, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9,  0, 0x0),
    gsSP1Triangle( 2, 10,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x050066D0 - 0x05006750
const Gfx manta_seg5_dl_050066D0[] = {
    gsSPVertex(manta_seg5_vertex_05006420, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 3, 10,  6, 0x0, 11, 12,  1, 0x0),
    gsSP2Triangles(11,  1,  0, 0x0,  1, 10,  3, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  3, 13, 14, 0x0),
    gsSP2Triangles( 2,  3, 14, 0x0,  5, 13,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006750 - 0x05006808
const Gfx manta_seg5_dl_05006750[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05006510),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_05006588),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(manta_seg5_dl_050065F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(manta_seg5_dl_050066D0),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05006808
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05006808, 0x0013b910, 41727, 0x00006808, 96);

// 0x05006868
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05006868, 0x0013b910, 41727, 0x00006868, 96);

// 0x050068C8
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050068C8, 0x0013b910, 41727, 0x000068c8, 128);

// 0x05006948
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05006948, 0x0013b910, 41727, 0x00006948, 128);

// 0x050069C8
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_050069C8, 0x0013b910, 41727, 0x000069c8, 192);

// 0x05006A88
ROM_ASSET_LOAD_VTX(manta_seg5_vertex_05006A88, 0x0013b910, 41727, 0x00006a88, 128);

// 0x05006B08 - 0x05006B70
const Gfx manta_seg5_dl_05006B08[] = {
    gsSPLight(&manta_seg5_lights_05001770.l, 1),
    gsSPLight(&manta_seg5_lights_05001770.a, 2),
    gsSPVertex(manta_seg5_vertex_05006808, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  0,  5, 0x0),
    gsSPLight(&manta_seg5_lights_05001758.l, 1),
    gsSPLight(&manta_seg5_lights_05001758.a, 2),
    gsSPVertex(manta_seg5_vertex_05006868, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006B70 - 0x05006C08
const Gfx manta_seg5_dl_05006B70[] = {
    gsSPLight(&manta_seg5_lights_05001770.l, 1),
    gsSPLight(&manta_seg5_lights_05001770.a, 2),
    gsSPVertex(manta_seg5_vertex_050068C8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  5,  0,  3, 0x0),
    gsSP2Triangles( 6,  7,  1, 0x0,  6,  1,  5, 0x0),
    gsSPLight(&manta_seg5_lights_05001758.l, 1),
    gsSPLight(&manta_seg5_lights_05001758.a, 2),
    gsSPVertex(manta_seg5_vertex_05006948, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05006C08 - 0x05006CA0
const Gfx manta_seg5_dl_05006C08[] = {
    gsSPLight(&manta_seg5_lights_05001770.l, 1),
    gsSPLight(&manta_seg5_lights_05001770.a, 2),
    gsSPVertex(manta_seg5_vertex_050069C8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  3, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0,  6, 11,  5, 0x0),
    gsSPLight(&manta_seg5_lights_05001758.l, 1),
    gsSPLight(&manta_seg5_lights_05001758.a, 2),
    gsSPVertex(manta_seg5_vertex_05006A88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  3, 0x0),
    gsSPEndDisplayList(),
};
