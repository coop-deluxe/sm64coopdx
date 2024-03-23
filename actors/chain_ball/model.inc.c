#include "pc/rom_assets.h"
// Chain Ball


// 0x06020AA0
ROM_ASSET_LOAD_VTX(chain_ball_seg6_vertex_06020AA0, 0x001c4230, 80474, 0x00020aa0, 64);

// align? binid?
UNUSED static const u64 chain_ball_unused_1 = 0;

// 0x06020AE8
ROM_ASSET_LOAD_TEXTURE(chain_ball_seg6_texture_06020AE8, "actors/chain_ball/chain_ball.rgba16.inc.c", 0x001c4230, 80474, 0x00020ae8, 2048);

// 0x060212E8 - 0x06021380
const Gfx chain_ball_seg6_dl_060212E8[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPLoadTextureBlock(chain_ball_seg6_texture_06020AE8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(chain_ball_seg6_vertex_06020AA0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
