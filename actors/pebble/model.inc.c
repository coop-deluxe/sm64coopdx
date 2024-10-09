#include "pc/rom_assets.h"
// Pebble

// 0x0301C2C0
ROM_ASSET_LOAD_VTX(pebble_seg3_vertex_0301C2C0, 0x00201410, 96653, 0x0001c2c0, 64);

// 0x0301C300
ROM_ASSET_LOAD_TEXTURE(pebble_seg3_texture_0301C300, "actors/pebble/pebble.rgba16.inc.c", 0x00201410, 96653, 0x0001c300, 2048);

// 0x0301CB00 - 0x0301CB98
const Gfx pebble_seg3_dl_0301CB00[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPLoadTextureBlock(pebble_seg3_texture_0301C300, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(pebble_seg3_vertex_0301C2C0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
