#include "pc/rom_assets.h"
// Clam Shell

// Unreferenced light group
UNUSED static const Lights1 clam_shell_lights_unused1 = gdSPDefLights1(
    0x1b, 0x23, 0x30,
    0x6d, 0x8f, 0xc3, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 clam_shell_lights_unused2 = gdSPDefLights1(
    0x18, 0x28, 0x38,
    0x60, 0xa2, 0xe2, 0x28, 0x28, 0x28
);

// 0x05000030
ROM_ASSET_LOAD_TEXTURE(clam_shell_seg5_texture_05000030, "actors/clam_shell/clam_shell.rgba16.inc.c", 0x0013b910, 41727, 0x00000030, 2048);

// 0x05000830
ROM_ASSET_LOAD_TEXTURE(clam_shell_seg5_texture_05000830, "actors/clam_shell/clam_shell_mouth.rgba16.inc.c", 0x0013b910, 41727, 0x00000830, 2048);

// 0x05001030
static const Lights1 clam_shell_seg5_lights_05001030 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05001048
ROM_ASSET_LOAD_VTX(clam_shell_seg5_vertex_05001048, 0x0013b910, 41727, 0x00001048, 176);

// 0x050010F8
ROM_ASSET_LOAD_VTX(clam_shell_seg5_vertex_050010F8, 0x0013b910, 41727, 0x000010f8, 176);

// 0x050011A8 - 0x05001238
const Gfx clam_shell_seg5_dl_050011A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, clam_shell_seg5_texture_05000030),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&clam_shell_seg5_lights_05001030.l, 1),
    gsSPLight(&clam_shell_seg5_lights_05001030.a, 2),
    gsSPVertex(clam_shell_seg5_vertex_05001048, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  4,  0,  6, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  3,  8,  0, 0x0),
    gsSP2Triangles( 6,  0,  9, 0x0,  2, 10,  9, 0x0),
    gsSP2Triangles( 9,  7,  6, 0x0,  9,  0,  2, 0x0),
    gsSP1Triangle( 8,  1,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05001238 - 0x050012B8
const Gfx clam_shell_seg5_dl_05001238[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, clam_shell_seg5_texture_05000830),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(clam_shell_seg5_vertex_050010F8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 0,  3,  6, 0x0,  6,  1,  0, 0x0),
    gsSP2Triangles( 2,  8,  9, 0x0,  9, 10,  3, 0x0),
    gsSP2Triangles( 9,  3,  2, 0x0,  3, 10,  4, 0x0),
    gsSP1Triangle( 2,  3,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x050012B8 - 0x05001320
const Gfx clam_shell_seg5_dl_050012B8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(clam_shell_seg5_dl_050011A8),
    gsSPDisplayList(clam_shell_seg5_dl_05001238),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05001320
static const Lights1 clam_shell_seg5_lights_05001320 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05001338
ROM_ASSET_LOAD_VTX(clam_shell_seg5_vertex_05001338, 0x0013b910, 41727, 0x00001338, 160);

// 0x050013D8
ROM_ASSET_LOAD_VTX(clam_shell_seg5_vertex_050013D8, 0x0013b910, 41727, 0x000013d8, 160);

// 0x05001478 - 0x050014F8
const Gfx clam_shell_seg5_dl_05001478[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, clam_shell_seg5_texture_05000030),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&clam_shell_seg5_lights_05001320.l, 1),
    gsSPLight(&clam_shell_seg5_lights_05001320.a, 2),
    gsSPVertex(clam_shell_seg5_vertex_05001338, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 0,  7,  8, 0x0,  2,  7,  0, 0x0),
    gsSP2Triangles( 8,  3,  0, 0x0,  0,  9,  1, 0x0),
    gsSP1Triangle( 6,  9,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x050014F8 - 0x05001568
const Gfx clam_shell_seg5_dl_050014F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, clam_shell_seg5_texture_05000830),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(clam_shell_seg5_vertex_050013D8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  2,  7,  4, 0x0),
    gsSP2Triangles( 8,  9,  2, 0x0,  2,  9,  6, 0x0),
    gsSP1Triangle( 5,  8,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05001568 - 0x050015D0
const Gfx clam_shell_seg5_dl_05001568[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(clam_shell_seg5_dl_05001478),
    gsSPDisplayList(clam_shell_seg5_dl_050014F8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
