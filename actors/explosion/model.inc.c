#include "pc/rom_assets.h"
// Explosion

// 0x030009C8
ROM_ASSET_LOAD_VTX(explosion_seg3_vertex_030009C8, 0x00201410, 96653, 0x000009c8, 64);

// 0x03000A08
ROM_ASSET_LOAD_TEXTURE(explosion_seg3_texture_03000A08, "actors/explosion/explosion_0.rgba16.inc.c", 0x00201410, 96653, 0x00000a08, 2048);

// 0x03001208
ROM_ASSET_LOAD_TEXTURE(explosion_seg3_texture_03001208, "actors/explosion/explosion_1.rgba16.inc.c", 0x00201410, 96653, 0x00001208, 2048);

// 0x03001A08
ROM_ASSET_LOAD_TEXTURE(explosion_seg3_texture_03001A08, "actors/explosion/explosion_2.rgba16.inc.c", 0x00201410, 96653, 0x00001a08, 2048);

// 0x03002208
ROM_ASSET_LOAD_TEXTURE(explosion_seg3_texture_03002208, "actors/explosion/explosion_3.rgba16.inc.c", 0x00201410, 96653, 0x00002208, 2048);

// 0x03002A08
ROM_ASSET_LOAD_TEXTURE(explosion_seg3_texture_03002A08, "actors/explosion/explosion_4.rgba16.inc.c", 0x00201410, 96653, 0x00002a08, 2048);

// 0x03003208
ROM_ASSET_LOAD_TEXTURE(explosion_seg3_texture_03003208, "actors/explosion/explosion_5.rgba16.inc.c", 0x00201410, 96653, 0x00003208, 2048);

// 0x03003A08
ROM_ASSET_LOAD_TEXTURE(explosion_seg3_texture_03003A08, "actors/explosion/explosion_6.rgba16.inc.c", 0x00201410, 96653, 0x00003a08, 2048);

// 0x03004208 - 0x03004298
const Gfx explosion_seg3_dl_03004208[] = {
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsDPSetEnvColor(255, 255, 255, 150),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(explosion_seg3_vertex_030009C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x03004298 - 0x030042B0
const Gfx explosion_seg3_dl_03004298[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_03000A08),
    gsSPBranchList(explosion_seg3_dl_03004208),
};

// 0x030042B0 - 0x030042C8
const Gfx explosion_seg3_dl_030042B0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_03001208),
    gsSPBranchList(explosion_seg3_dl_03004208),
};

// 0x030042C8 - 0x030042E0
const Gfx explosion_seg3_dl_030042C8[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_03001A08),
    gsSPBranchList(explosion_seg3_dl_03004208),
};

// 0x030042E0 - 0x030042F8
const Gfx explosion_seg3_dl_030042E0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_03002208),
    gsSPBranchList(explosion_seg3_dl_03004208),
};

// 0x030042F8 - 0x03004310
const Gfx explosion_seg3_dl_030042F8[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_03002A08),
    gsSPBranchList(explosion_seg3_dl_03004208),
};

// 0x03004310 - 0x03004328
const Gfx explosion_seg3_dl_03004310[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_03003208),
    gsSPBranchList(explosion_seg3_dl_03004208),
};

// 0x03004328 - 0x03004340
const Gfx explosion_seg3_dl_03004328[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_03003A08),
    gsSPBranchList(explosion_seg3_dl_03004208),
};
