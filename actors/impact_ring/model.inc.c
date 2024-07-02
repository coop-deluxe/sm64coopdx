#include "pc/rom_assets.h"
// Impact Ring

// 0x0601C9D0
ROM_ASSET_LOAD_VTX(impact_ring_seg6_vertex_0601C9D0, 0x00188440, 199722, 0x0001c9d0, 64);

// 0x0601CA10
ROM_ASSET_LOAD_VTX(impact_ring_seg6_vertex_0601CA10, 0x00188440, 199722, 0x0001ca10, 64);

// 0x0601CA50
ROM_ASSET_LOAD_TEXTURE(impact_ring_seg6_texture_0601CA50, "actors/impact_ring/impact_ring_left_side.ia16.inc.c", 0x00188440, 199722, 0x0001ca50, 4096);

// 0x0601DA50
ROM_ASSET_LOAD_TEXTURE(impact_ring_seg6_texture_0601DA50, "actors/impact_ring/impact_ring_right_side.ia16.inc.c", 0x00188440, 199722, 0x0001da50, 4096);

// 0x0601EA50 - 0x0601EA88
const Gfx impact_ring_seg6_dl_0601EA50[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, impact_ring_seg6_texture_0601CA50),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(impact_ring_seg6_vertex_0601C9D0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601EA88 - 0x0601EAC0
const Gfx impact_ring_seg6_dl_0601EA88[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, impact_ring_seg6_texture_0601DA50),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(impact_ring_seg6_vertex_0601CA10, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601EAC0 - 0x0601EB40
const Gfx impact_ring_seg6_dl_0601EAC0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIFADEA, G_CC_MODULATEIFADEA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(impact_ring_seg6_dl_0601EA50),
    gsSPDisplayList(impact_ring_seg6_dl_0601EA88),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
