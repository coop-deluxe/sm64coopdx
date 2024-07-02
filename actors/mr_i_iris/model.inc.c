#include "pc/rom_assets.h"
// Mr I (Iris)

// 0x06002130
ROM_ASSET_LOAD_VTX(mr_i_iris_seg6_vertex_06002130, 0x001e7ee0, 40011, 0x00002130, 64);

// 0x06002170
ROM_ASSET_LOAD_TEXTURE(mr_i_iris_seg6_texture_06002170, "actors/mr_i_iris/mr_i_iris_open.rgba16.inc.c", 0x001e7ee0, 40011, 0x00002170, 2048);

// 0x06002970
ROM_ASSET_LOAD_TEXTURE(mr_i_iris_seg6_texture_06002970, "actors/mr_i_iris/mr_i_iris_mostly_open.rgba16.inc.c", 0x001e7ee0, 40011, 0x00002970, 2048);

// 0x06003170
ROM_ASSET_LOAD_TEXTURE(mr_i_iris_seg6_texture_06003170, "actors/mr_i_iris/mr_i_iris_mostly_closed.rgba16.inc.c", 0x001e7ee0, 40011, 0x00003170, 2048);

// 0x06003970
ROM_ASSET_LOAD_TEXTURE(mr_i_iris_seg6_texture_06003970, "actors/mr_i_iris/mr_i_iris_closed.rgba16.inc.c", 0x001e7ee0, 40011, 0x00003970, 2048);

// 0x06004170 - 0x060041D8
const Gfx mr_i_iris_seg6_dl_06004170[] = {
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(mr_i_iris_seg6_vertex_06002130, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x060041D8 - 0x060041F0
const Gfx mr_i_iris_seg6_dl_060041D8[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mr_i_iris_seg6_texture_06002170),
    gsSPBranchList(mr_i_iris_seg6_dl_06004170),
};

// 0x060041F0 - 0x06004208
const Gfx mr_i_iris_seg6_dl_060041F0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mr_i_iris_seg6_texture_06002970),
    gsSPBranchList(mr_i_iris_seg6_dl_06004170),
};

// 0x06004208 - 0x06004220
const Gfx mr_i_iris_seg6_dl_06004208[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mr_i_iris_seg6_texture_06003170),
    gsSPBranchList(mr_i_iris_seg6_dl_06004170),
};

// 0x06004220 - 0x06004238
const Gfx mr_i_iris_seg6_dl_06004220[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mr_i_iris_seg6_texture_06003970),
    gsSPBranchList(mr_i_iris_seg6_dl_06004170),
};
