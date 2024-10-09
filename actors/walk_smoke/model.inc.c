#include "pc/rom_assets.h"
// Walk Smoke

// 0x0401DE60
ROM_ASSET_LOAD_VTX(smoke_seg4_vertex_0401DE60, 0x00114750, 78432, 0x0001de60, 64);

// 0x0401DEA0
ROM_ASSET_LOAD_TEXTURE(smoke_seg4_texture_0401DEA0, "actors/walk_smoke/walk_smoke_0.ia16.inc.c", 0x00114750, 78432, 0x0001dea0, 2048);

// 0x0401E6A0
ROM_ASSET_LOAD_TEXTURE(smoke_seg4_texture_0401E6A0, "actors/walk_smoke/walk_smoke_1.ia16.inc.c", 0x00114750, 78432, 0x0001e6a0, 2048);

// 0x0401EEA0
ROM_ASSET_LOAD_TEXTURE(smoke_seg4_texture_0401EEA0, "actors/walk_smoke/walk_smoke_2.ia16.inc.c", 0x00114750, 78432, 0x0001eea0, 2048);

// 0x0401F6A0
ROM_ASSET_LOAD_TEXTURE(smoke_seg4_texture_0401F6A0, "actors/walk_smoke/walk_smoke_3.ia16.inc.c", 0x00114750, 78432, 0x0001f6a0, 2048);

// 0x0401FEA0
ROM_ASSET_LOAD_TEXTURE(smoke_seg4_texture_0401FEA0, "actors/walk_smoke/walk_smoke_4.ia16.inc.c", 0x00114750, 78432, 0x0001fea0, 2048);

// 0x040206A0
ROM_ASSET_LOAD_TEXTURE(smoke_seg4_texture_040206A0, "actors/walk_smoke/walk_smoke_5.ia16.inc.c", 0x00114750, 78432, 0x000206a0, 2048);

// 0x04020EA0
ROM_ASSET_LOAD_TEXTURE(smoke_seg4_texture_04020EA0, "actors/walk_smoke/walk_smoke_6.ia16.inc.c", 0x00114750, 78432, 0x00020ea0, 2048);

// 0x040216A0 - 0x04021718
const Gfx smoke_seg4_dl_040216A0[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(smoke_seg4_vertex_0401DE60, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x04021718 - 0x04021730
const Gfx smoke_seg4_dl_04021718[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_0401DEA0),
    gsSPBranchList(smoke_seg4_dl_040216A0),
};

// 0x04021730 - 0x04021748
const Gfx smoke_seg4_dl_04021730[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_0401E6A0),
    gsSPBranchList(smoke_seg4_dl_040216A0),
};

// 0x04021748 - 0x04021760
const Gfx smoke_seg4_dl_04021748[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_0401EEA0),
    gsSPBranchList(smoke_seg4_dl_040216A0),
};

// 0x04021760 - 0x04021778
const Gfx smoke_seg4_dl_04021760[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_0401F6A0),
    gsSPBranchList(smoke_seg4_dl_040216A0),
};

// 0x04021778 - 0x04021790
const Gfx smoke_seg4_dl_04021778[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_0401FEA0),
    gsSPBranchList(smoke_seg4_dl_040216A0),
};

// 0x04021790 - 0x040217A8
const Gfx smoke_seg4_dl_04021790[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_040206A0),
    gsSPBranchList(smoke_seg4_dl_040216A0),
};

// 0x040217A8 - 0x040217C0
const Gfx smoke_seg4_dl_040217A8[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_04020EA0),
    gsSPBranchList(smoke_seg4_dl_040216A0),
};
