#include "pc/rom_assets.h"
// Skeeter

// Unreferenced light group
UNUSED static const Lights1 skeeter_lights_unused1 = gdSPDefLights1(
    0x3f, 0x20, 0x02,
    0xfc, 0x80, 0x08, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 skeeter_lights_unused2 = gdSPDefLights1(
    0x05, 0x05, 0x02,
    0x15, 0x15, 0x08, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 skeeter_lights_unused3 = gdSPDefLights1(
    0x03, 0x10, 0x29,
    0x0e, 0x40, 0xa4, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 skeeter_lights_unused4 = gdSPDefLights1(
    0x3b, 0x3a, 0x36,
    0xef, 0xea, 0xd9, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 skeeter_lights_unused5 = gdSPDefLights1(
    0x33, 0x0c, 0x00,
    0xcf, 0x32, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 skeeter_lights_unused6 = gdSPDefLights1(
    0x10, 0x29, 0x20,
    0x42, 0xa5, 0x81, 0x28, 0x28, 0x28
);

// 0x06000090
ROM_ASSET_LOAD_TEXTURE(skeeter_seg6_texture_06000090, "actors/skeeter/skeeter_eye.rgba16.inc.c", 0x001b9cc0, 41188, 0x00000090, 2048);

// 0x06000890
ROM_ASSET_LOAD_TEXTURE(skeeter_seg6_texture_06000890, "actors/skeeter/skeeter_iris.rgba16.inc.c", 0x001b9cc0, 41188, 0x00000890, 256);

// 0x06000990
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000990, 0x001b9cc0, 41188, 0x00000990, 64);

// 0x060009D0 - 0x06000A08
const Gfx skeeter_seg6_dl_060009D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, skeeter_seg6_texture_06000090),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(skeeter_seg6_vertex_06000990, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06000A08 - 0x06000A78
const Gfx skeeter_seg6_dl_06000A08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(skeeter_seg6_dl_060009D0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06000A78
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000A78, 0x001b9cc0, 41188, 0x00000a78, 64);

// 0x06000AB8 - 0x06000AF0
const Gfx skeeter_seg6_dl_06000AB8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, skeeter_seg6_texture_06000090),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(skeeter_seg6_vertex_06000A78, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06000AF0 - 0x06000B60
const Gfx skeeter_seg6_dl_06000AF0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(skeeter_seg6_dl_06000AB8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06000B60
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000B60, 0x001b9cc0, 41188, 0x00000b60, 64);

// 0x06000BA0 - 0x06000BD8
const Gfx skeeter_seg6_dl_06000BA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, skeeter_seg6_texture_06000090),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(skeeter_seg6_vertex_06000B60, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06000BD8 - 0x06000C48
const Gfx skeeter_seg6_dl_06000BD8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(skeeter_seg6_dl_06000BA0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06000C48
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000C48, 0x001b9cc0, 41188, 0x00000c48, 48);

// 0x06000C78 - 0x06000CA8
const Gfx skeeter_seg6_dl_06000C78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, skeeter_seg6_texture_06000890),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 8 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(skeeter_seg6_vertex_06000C48, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06000CA8 - 0x06000D18
const Gfx skeeter_seg6_dl_06000CA8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(skeeter_seg6_dl_06000C78),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06000D18
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000D18, 0x001b9cc0, 41188, 0x00000d18, 48);

// 0x06000D48 - 0x06000D78
const Gfx skeeter_seg6_dl_06000D48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, skeeter_seg6_texture_06000890),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 8 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(skeeter_seg6_vertex_06000D18, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06000D78 - 0x06000DE8
const Gfx skeeter_seg6_dl_06000D78[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(skeeter_seg6_dl_06000D48),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06000DE8
static const Lights1 skeeter_seg6_lights_06000DE8 = gdSPDefLights1(
    0x7f, 0x55, 0x00,
    0xff, 0xaa, 0x00, 0x28, 0x28, 0x28
);

// 0x06000E00
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000E00, 0x001b9cc0, 41188, 0x00000e00, 96);

// 0x06000E60 - 0x06000EC0
const Gfx skeeter_seg6_dl_06000E60[] = {
    gsSPLight(&skeeter_seg6_lights_06000DE8.l, 1),
    gsSPLight(&skeeter_seg6_lights_06000DE8.a, 2),
    gsSPVertex(skeeter_seg6_vertex_06000E00, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 0,  5,  4, 0x0,  5,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06000EC0 - 0x06000EF0
const Gfx skeeter_seg6_dl_06000EC0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(skeeter_seg6_dl_06000E60),
    gsSPEndDisplayList(),
};

// 0x06000EF0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000EF0, 0x001b9cc0, 41188, 0x00000ef0, 176);

// 0x06000FA0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000FA0, 0x001b9cc0, 41188, 0x00000fa0, 64);

// 0x06000FE0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06000FE0, 0x001b9cc0, 41188, 0x00000fe0, 64);

// 0x06001020
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001020, 0x001b9cc0, 41188, 0x00000ef0, 176);

// 0x060010D0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060010D0, 0x001b9cc0, 41188, 0x00000fa0, 64);

// 0x06001110
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001110, 0x001b9cc0, 41188, 0x00000fe0, 64);

// 0x06001150
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001150, 0x001b9cc0, 41188, 0x00001150, 176);

// 0x06001200
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001200, 0x001b9cc0, 41188, 0x00001200, 64);

// 0x06001240
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001240, 0x001b9cc0, 41188, 0x00001240, 64);

// 0x06001280
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001280, 0x001b9cc0, 41188, 0x00001280, 256);

// 0x06001380
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001380, 0x001b9cc0, 41188, 0x00001380, 256);

// 0x06001480
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001480, 0x001b9cc0, 41188, 0x00001480, 256);

// 0x06001580
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001580, 0x001b9cc0, 41188, 0x00001580, 256);

// 0x06001680
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001680, 0x001b9cc0, 41188, 0x00001680, 256);

// 0x06001780
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001780, 0x001b9cc0, 41188, 0x00001780, 256);

// 0x06001880
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001880, 0x001b9cc0, 41188, 0x00001880, 256);

// 0x06001980
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001980, 0x001b9cc0, 41188, 0x00001980, 256);

// 0x06001A80
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001A80, 0x001b9cc0, 41188, 0x00001150, 176);

// 0x06001B30
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001B30, 0x001b9cc0, 41188, 0x00001200, 64);

// 0x06001B70
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001B70, 0x001b9cc0, 41188, 0x00001240, 64);

// 0x06001BB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001BB0, 0x001b9cc0, 41188, 0x00001bb0, 256);

// 0x06001CB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001CB0, 0x001b9cc0, 41188, 0x00001cb0, 256);

// 0x06001DB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001DB0, 0x001b9cc0, 41188, 0x00001db0, 256);

// 0x06001EB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001EB0, 0x001b9cc0, 41188, 0x00001eb0, 256);

// 0x06001FB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06001FB0, 0x001b9cc0, 41188, 0x00001fb0, 256);

// 0x060020B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060020B0, 0x001b9cc0, 41188, 0x000020b0, 256);

// 0x060021B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060021B0, 0x001b9cc0, 41188, 0x000021b0, 256);

// 0x060022B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060022B0, 0x001b9cc0, 41188, 0x000022b0, 256);

// 0x060023B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060023B0, 0x001b9cc0, 41188, 0x000023b0, 256);

// 0x060024B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060024B0, 0x001b9cc0, 41188, 0x000024b0, 256);

// 0x060025B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060025B0, 0x001b9cc0, 41188, 0x000025b0, 256);

// 0x060026B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060026B0, 0x001b9cc0, 41188, 0x000026b0, 256);

// 0x060027B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060027B0, 0x001b9cc0, 41188, 0x000027b0, 256);

// 0x060028B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060028B0, 0x001b9cc0, 41188, 0x000028b0, 256);

// 0x060029B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060029B0, 0x001b9cc0, 41188, 0x000029b0, 256);

// 0x06002AB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06002AB0, 0x001b9cc0, 41188, 0x00002ab0, 256);

// 0x06002BB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06002BB0, 0x001b9cc0, 41188, 0x00002bb0, 256);

// 0x06002CB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06002CB0, 0x001b9cc0, 41188, 0x00002cb0, 256);

// 0x06002DB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06002DB0, 0x001b9cc0, 41188, 0x00002db0, 256);

// 0x06002EB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06002EB0, 0x001b9cc0, 41188, 0x00002eb0, 256);

// 0x06002FB0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06002FB0, 0x001b9cc0, 41188, 0x00002fb0, 256);

// 0x060030B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060030B0, 0x001b9cc0, 41188, 0x000030b0, 256);

// 0x060031B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060031B0, 0x001b9cc0, 41188, 0x000031b0, 256);

// 0x060032B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060032B0, 0x001b9cc0, 41188, 0x000032b0, 256);

// 0x060033B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060033B0, 0x001b9cc0, 41188, 0x000033b0, 256);

// 0x060034B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060034B0, 0x001b9cc0, 41188, 0x000034b0, 256);

// 0x060035B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060035B0, 0x001b9cc0, 41188, 0x000035b0, 256);

// 0x060036B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060036B0, 0x001b9cc0, 41188, 0x000036b0, 256);

// 0x060037B0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060037B0, 0x001b9cc0, 41188, 0x000037b0, 64);

// 0x060037F0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060037F0, 0x001b9cc0, 41188, 0x000037f0, 256);

// 0x060038F0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060038F0, 0x001b9cc0, 41188, 0x000038f0, 256);

// 0x060039F0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_060039F0, 0x001b9cc0, 41188, 0x000039f0, 256);

// 0x06003AF0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06003AF0, 0x001b9cc0, 41188, 0x00003af0, 256);

// 0x06003BF0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06003BF0, 0x001b9cc0, 41188, 0x00003bf0, 256);

// 0x06003CF0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06003CF0, 0x001b9cc0, 41188, 0x00003cf0, 256);

// 0x06003DF0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06003DF0, 0x001b9cc0, 41188, 0x00003df0, 256);

// 0x06003EF0
ROM_ASSET_LOAD_VTX(skeeter_seg6_vertex_06003EF0, 0x001b9cc0, 41188, 0x00003ef0, 256);

// 0x06003FF0 - 0x06004040
const Gfx skeeter_seg6_dl_06003FF0[] = {
    gsSPVertex(skeeter_seg6_vertex_06000EF0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x06004040 - 0x06004070
const Gfx skeeter_seg6_dl_06004040[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_06000FA0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06004070 - 0x060040A0
const Gfx skeeter_seg6_dl_06004070[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_06000FE0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x060040A0 - 0x060040F0
const Gfx skeeter_seg6_dl_060040A0[] = {
    gsSPVertex(skeeter_seg6_vertex_06001020, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x060040F0 - 0x06004120
const Gfx skeeter_seg6_dl_060040F0[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_060010D0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06004120 - 0x06004150
const Gfx skeeter_seg6_dl_06004120[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_06001110, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06004150 - 0x060041A0
const Gfx skeeter_seg6_dl_06004150[] = {
    gsSPVertex(skeeter_seg6_vertex_06001150, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  3,  2, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x060041A0 - 0x060041D0
const Gfx skeeter_seg6_dl_060041A0[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_06001200, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x060041D0 - 0x06004200
const Gfx skeeter_seg6_dl_060041D0[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_06001240, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06004200 - 0x060045C8
const Gfx skeeter_seg6_dl_06004200[] = {
    gsSPVertex(skeeter_seg6_vertex_06001280, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001380, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001480, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001580, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001680, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001780, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001880, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001980, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x060045C8 - 0x06004618
const Gfx skeeter_seg6_dl_060045C8[] = {
    gsSPVertex(skeeter_seg6_vertex_06001A80, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  3,  2, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x06004618 - 0x06004648
const Gfx skeeter_seg6_dl_06004618[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_06001B30, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06004648 - 0x06004678
const Gfx skeeter_seg6_dl_06004648[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_06001B70, 4, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSP1Triangle( 0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06004678 - 0x06004A40
const Gfx skeeter_seg6_dl_06004678[] = {
    gsSPVertex(skeeter_seg6_vertex_06001BB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001CB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001DB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001EB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06001FB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060020B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060021B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060022B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 5,  4,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 13, 14, 12, 0x0),
    gsSP2Triangles(13, 12, 11, 0x0, 15, 14, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x06004A40 - 0x06005328
const Gfx skeeter_seg6_dl_06004A40[] = {
    gsSPVertex(skeeter_seg6_vertex_060023B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060024B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060025B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060026B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060027B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060028B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060029B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06002AB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06002BB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06002CB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06002DB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06002EB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06002FB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060030B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060031B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060032B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060033B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060034B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060035B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  6,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060036B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x06005328 - 0x06005358
const Gfx skeeter_seg6_dl_06005328[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(skeeter_seg6_vertex_060037B0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06005358 - 0x06005720
const Gfx skeeter_seg6_dl_06005358[] = {
    gsSPVertex(skeeter_seg6_vertex_060037F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060038F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_060039F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06003AF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06003BF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06003CF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06003DF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(skeeter_seg6_vertex_06003EF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPEndDisplayList(),
};
