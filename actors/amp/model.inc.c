#include "pc/rom_assets.h"
// Amp

// 0x08000F18
ROM_ASSET_LOAD_TEXTURE(amp_seg8_texture_08000F18, "actors/amp/amp_electricity.rgba16.inc.c", 0x001f2200, 59076, 0x00000f18, 1024);

// 0x08001318
ROM_ASSET_LOAD_TEXTURE(amp_seg8_texture_08001318, "actors/amp/amp_eyes.rgba16.inc.c", 0x001f2200, 59076, 0x00001318, 2048);

// 0x08001B18
ROM_ASSET_LOAD_TEXTURE(amp_seg8_texture_08001B18, "actors/amp/amp_body.rgba16.inc.c", 0x001f2200, 59076, 0x00001b18, 2048);

// 0x08002318
ROM_ASSET_LOAD_TEXTURE(amp_seg8_texture_08002318, "actors/amp/amp_mouth.rgba16.inc.c", 0x001f2200, 59076, 0x00002318, 2048);

// 0x08002B18
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08002B18, 0x001f2200, 59076, 0x00002b18, 80);

// 0x08002B68 - 0x08002BA0
const Gfx amp_seg8_dl_08002B68[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, amp_seg8_texture_08000F18),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(amp_seg8_vertex_08002B18, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x08002BA0 - 0x08002C10
const Gfx amp_seg8_dl_08002BA0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(amp_seg8_dl_08002B68),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x08002C10
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08002C10, 0x001f2200, 59076, 0x00002c10, 64);

// 0x08002C50 - 0x08002C88
const Gfx amp_seg8_dl_08002C50[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, amp_seg8_texture_08001318),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(amp_seg8_vertex_08002C10, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08002C88 - 0x08002CF8
const Gfx amp_seg8_dl_08002C88[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(amp_seg8_dl_08002C50),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08002CF8
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08002CF8, 0x001f2200, 59076, 0x00002cf8, 64);

// 0x08002D38 - 0x08002D70
const Gfx amp_seg8_dl_08002D38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, amp_seg8_texture_08002318),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(amp_seg8_vertex_08002CF8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08002D70 - 0x08002DE0
const Gfx amp_seg8_dl_08002D70[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(amp_seg8_dl_08002D38),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08002DE0
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08002DE0, 0x001f2200, 59076, 0x00002de0, 64);

// 0x08002E20 - 0x08002E58
const Gfx amp_seg8_dl_08002E20[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, amp_seg8_texture_08001B18),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(amp_seg8_vertex_08002DE0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08002E58 - 0x08002EC8
const Gfx amp_seg8_dl_08002E58[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(amp_seg8_dl_08002E20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08002EC8
static const Lights1 amp_seg8_lights_08002EC8 = gdSPDefLights1(
    0x33, 0x3f, 0x00,
    0xcf, 0xff, 0x00, 0x28, 0x28, 0x28
);

// //! Another malformed entry: Vertex interpreted as light
// 0x08002EE0
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08002EE0, 0x001f2200, 59076, 0x00002ee0, 96);

// 0x08002F40
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08002F40, 0x001f2200, 59076, 0x00002ee0, 96);

// 0x08002FA0
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08002FA0, 0x001f2200, 59076, 0x00002ee0, 96);

// 0x08003000
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003000, 0x001f2200, 59076, 0x00003000, 96);

// 0x08003060
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003060, 0x001f2200, 59076, 0x00003060, 256);

// 0x08003160
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003160, 0x001f2200, 59076, 0x00003160, 256);

// 0x08003260
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003260, 0x001f2200, 59076, 0x00003260, 256);

// 0x08003360
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003360, 0x001f2200, 59076, 0x00003360, 256);

// 0x08003460
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003460, 0x001f2200, 59076, 0x00003460, 256);

// 0x08003560
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003560, 0x001f2200, 59076, 0x00003560, 256);

// 0x08003660
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003660, 0x001f2200, 59076, 0x00003660, 256);

// 0x08003760
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003760, 0x001f2200, 59076, 0x00003760, 256);

// 0x08003860
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_08003860, 0x001f2200, 59076, 0x00003860, 64);

// 0x080038A0
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_080038A0, 0x001f2200, 59076, 0x000038a0, 48);

// 0x080038D0
ROM_ASSET_LOAD_VTX(amp_seg8_vertex_080038D0, 0x001f2200, 59076, 0x000038d0, 64);

// 0x08003910 - 0x08003940
const Gfx amp_seg8_dl_08003910[] = {
    gsSPLight(&amp_seg8_lights_08002EC8.l, 1),
    gsSPLight(&amp_seg8_lights_08002EC8.a, 2),
    gsSPVertex(amp_seg8_vertex_08002EE0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x08003940 - 0x08003970
const Gfx amp_seg8_dl_08003940[] = {
    gsSPLight(&amp_seg8_lights_08002EC8.l, 1),
    gsSPLight(&amp_seg8_lights_08002EC8.a, 2),
    gsSPVertex(amp_seg8_vertex_08002F40, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x08003970 - 0x080039A0
const Gfx amp_seg8_dl_08003970[] = {
    gsSPLight(&amp_seg8_lights_08002EC8.l, 1),
    gsSPLight(&amp_seg8_lights_08002EC8.a, 2),
    gsSPVertex(amp_seg8_vertex_08002FA0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x080039A0 - 0x080039D0
const Gfx amp_seg8_dl_080039A0[] = {
    gsSPLight(&amp_seg8_lights_08002EC8.l, 1),
    gsSPLight(&amp_seg8_lights_08002EC8.a, 2),
    gsSPVertex(amp_seg8_vertex_08003000, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x080039D0 - 0x08003DA8
const Gfx amp_seg8_dl_080039D0[] = {
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0 + 0x8, 1),
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0, 2),
    gsSPVertex(amp_seg8_vertex_08003060, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(amp_seg8_vertex_08003160, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(amp_seg8_vertex_08003260, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(amp_seg8_vertex_08003360, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(amp_seg8_vertex_08003460, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(amp_seg8_vertex_08003560, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(amp_seg8_vertex_08003660, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(amp_seg8_vertex_08003760, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x08003DA8 - 0x08003DD8
const Gfx amp_seg8_dl_08003DA8[] = {
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0 + 0x8, 1),
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0, 2),
    gsSPVertex(amp_seg8_vertex_08003860, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x08003DD8 - 0x08003E00
const Gfx amp_seg8_dl_08003DD8[] = {
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0 + 0x8, 1),
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0, 2),
    gsSPVertex(amp_seg8_vertex_080038A0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x08003E00 - 0x08003E30
const Gfx amp_seg8_dl_08003E00[] = {
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0 + 0x8, 1),
    gsSPLight((const u8*)amp_seg8_vertex_08002EE0, 2),
    gsSPVertex(amp_seg8_vertex_080038D0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};
