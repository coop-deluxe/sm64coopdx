#include "pc/rom_assets.h"
// Door

// 0x03009CE0
static const Lights1 door_seg3_lights_03009CE0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x03009CF8
static const Lights1 door_seg3_lights_03009CF8 = gdSPDefLights1(
    0x3f, 0x3f, 0x00,
    0xff, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x03009D10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_03009D10, "actors/door/polished_wooden_door.rgba16.inc.c", 0x00201410, 96653, 0x00009d10, 4096);

// 0x0300AD10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_0300AD10, "actors/door/polished_wooden_door_overlay.rgba16.inc.c", 0x00201410, 96653, 0x0000ad10, 4096);

// 0x0300BD10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_0300BD10, "actors/door/rough_wooden_door.rgba16.inc.c", 0x00201410, 96653, 0x0000bd10, 4096);

// 0x0300CD10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_0300CD10, "actors/door/rough_wooden_door_overlay.rgba16.inc.c", 0x00201410, 96653, 0x0000cd10, 2048);

// 0x0300D510
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_0300D510, "actors/door/metal_door.rgba16.inc.c", 0x00201410, 96653, 0x0000d510, 4096);

// 0x0300E510
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_0300E510, "actors/door/metal_door_overlay.rgba16.inc.c", 0x00201410, 96653, 0x0000e510, 2048);

// 0x0300ED10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_0300ED10, "actors/door/hmc_mural_door.rgba16.inc.c", 0x00201410, 96653, 0x0000ed10, 4096);

// 0x0300FD10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_0300FD10, "actors/door/hmc_mural_door_overlay.rgba16.inc.c", 0x00201410, 96653, 0x0000fd10, 2048);

// 0x03010510
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_03010510, "actors/door/bbh_door.rgba16.inc.c", 0x00201410, 96653, 0x00010510, 4096);

// 0x03011510
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_03011510, "actors/door/bbh_door_overlay.rgba16.inc.c", 0x00201410, 96653, 0x00011510, 2048);

// 0x03011D10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_03011D10, "actors/door/zero_star_door_sign.rgba16.inc.c", 0x00201410, 96653, 0x00011d10, 2048);

// 0x03012510
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_03012510, "actors/door/one_star_door_sign.rgba16.inc.c", 0x00201410, 96653, 0x00012510, 2048);

// 0x03012D10
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_03012D10, "actors/door/three_star_door_sign.rgba16.inc.c", 0x00201410, 96653, 0x00012d10, 2048);

// 0x03013510
ROM_ASSET_LOAD_TEXTURE(door_seg3_texture_03013510, "actors/door/door_lock.rgba16.inc.c", 0x00201410, 96653, 0x00013510, 1024);

// 0x03013910
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03013910, 0x00201410, 96653, 0x00013910, 256);

// 0x03013A10
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03013A10, 0x00201410, 96653, 0x00013a10, 128);

// 0x03013A90
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03013A90, 0x00201410, 96653, 0x00013a90, 192);

// 0x03013B50
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03013B50, 0x00201410, 96653, 0x00013b50, 192);

// 0x03013C10 - 0x03013CC8
const Gfx door_seg3_dl_03013C10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300AD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&door_seg3_lights_03009CE0.l, 1),
    gsSPLight(&door_seg3_lights_03009CE0.a, 2),
    gsSPVertex(door_seg3_vertex_03013910, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03009D10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(door_seg3_vertex_03013A10, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x03013CC8 - 0x03013D78
const Gfx door_seg3_dl_03013CC8[] = {
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPVertex(door_seg3_vertex_03013A90, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  3, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 7,  6,  3, 0x0,  7,  3,  1, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  9,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  0, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles(10,  5,  6, 0x0, 10, 11,  5, 0x0),
    gsSP2Triangles(11,  0,  5, 0x0, 11,  8,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x03013D78 - 0x03013E28
const Gfx door_seg3_dl_03013D78[] = {
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPVertex(door_seg3_vertex_03013B50, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 5,  0,  4, 0x0,  2,  1,  6, 0x0),
    gsSP2Triangles( 1,  7,  6, 0x0,  1,  5,  7, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  3,  6,  9, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  4,  3, 10, 0x0),
    gsSP2Triangles( 3,  9, 10, 0x0,  7,  4, 11, 0x0),
    gsSP2Triangles( 7, 11,  8, 0x0,  4, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x03013E28 - 0x03013EA8
const Gfx door_seg3_dl_03013E28[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(door_seg3_dl_03013C10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPDisplayList(door_seg3_dl_03013CC8),
    gsSPDisplayList(door_seg3_dl_03013D78),
    gsSPEndDisplayList(),
};

// 0x03013EA8 - 0x03013F20
const Gfx door_seg3_dl_03013EA8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(door_seg3_dl_03013C10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPDisplayList(door_seg3_dl_03013CC8),
    gsSPEndDisplayList(),
};

// 0x03013F20
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03013F20, 0x00201410, 96653, 0x00013f20, 128);

// 0x03013FA0
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03013FA0, 0x00201410, 96653, 0x00013fa0, 128);

// 0x03014020 - 0x03014100
const Gfx door_seg3_dl_03014020[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03009D10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&door_seg3_lights_03009CE0.l, 1),
    gsSPLight(&door_seg3_lights_03009CE0.a, 2),
    gsSPVertex(door_seg3_vertex_03013F20, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPVertex(door_seg3_vertex_03013FA0, 8, 0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03014100 - 0x03014128
const Gfx door_seg3_dl_03014100[] = {
    gsSPDisplayList(door_seg3_dl_03014020),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03014128 - 0x03014140
const Gfx door_seg3_dl_03014128[] = {
    gsSPDisplayList(door_seg3_dl_03014020),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03014140
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03014140, 0x00201410, 96653, 0x00014140, 64);

// 0x03014180
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03014180, 0x00201410, 96653, 0x00014180, 64);

// 0x030141C0 - 0x03014218
const Gfx door_seg3_dl_030141C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPLight(&door_seg3_lights_03009CE0.l, 1),
    gsSPLight(&door_seg3_lights_03009CE0.a, 2),
    gsSPEndDisplayList(),
};

// 0x03014218 - 0x03014250
const Gfx door_seg3_dl_03014218[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03014250 - 0x03014280
const Gfx door_seg3_dl_03014250[] = {
    gsSPDisplayList(door_seg3_dl_030141C0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03011D10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(door_seg3_vertex_03014140, 4, 0),
    gsSPBranchList(door_seg3_dl_03014218),
};

// 0x03014280 - 0x030142B0
const Gfx door_seg3_dl_03014280[] = {
    gsSPDisplayList(door_seg3_dl_030141C0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03011D10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(door_seg3_vertex_03014180, 4, 0),
    gsSPBranchList(door_seg3_dl_03014218),
};

// 0x030142B0 - 0x030142E0
const Gfx door_seg3_dl_030142B0[] = {
    gsSPDisplayList(door_seg3_dl_030141C0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03012510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(door_seg3_vertex_03014140, 4, 0),
    gsSPBranchList(door_seg3_dl_03014218),
};

// 0x030142E0 - 0x03014310
const Gfx door_seg3_dl_030142E0[] = {
    gsSPDisplayList(door_seg3_dl_030141C0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03012510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(door_seg3_vertex_03014180, 4, 0),
    gsSPBranchList(door_seg3_dl_03014218),
};

// 0x03014310 - 0x03014340
const Gfx door_seg3_dl_03014310[] = {
    gsSPDisplayList(door_seg3_dl_030141C0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03012D10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(door_seg3_vertex_03014140, 4, 0),
    gsSPBranchList(door_seg3_dl_03014218),
};

// 0x03014340 - 0x03014370
const Gfx door_seg3_dl_03014340[] = {
    gsSPDisplayList(door_seg3_dl_030141C0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03012D10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(door_seg3_vertex_03014180, 4, 0),
    gsSPBranchList(door_seg3_dl_03014218),
};

// 0x03014370
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03014370, 0x00201410, 96653, 0x00014370, 128);

// 0x030143F0
ROM_ASSET_LOAD_VTX(door_seg3_vertex_030143F0, 0x00201410, 96653, 0x000143f0, 128);

// 0x03014470 - 0x030144E0
const Gfx door_seg3_dl_03014470[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03013510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&door_seg3_lights_03009CE0.l, 1),
    gsSPLight(&door_seg3_lights_03009CE0.a, 2),
    gsSPEndDisplayList(),
};

// 0x030144E0 - 0x03014528
const Gfx door_seg3_dl_030144E0[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03014528 - 0x03014540
const Gfx door_seg3_dl_03014528[] = {
    gsSPDisplayList(door_seg3_dl_03014470),
    gsSPVertex(door_seg3_vertex_03014370, 8, 0),
    gsSPBranchList(door_seg3_dl_030144E0),
};

// 0x03014540 - 0x03014558
const Gfx door_seg3_dl_03014540[] = {
    gsSPDisplayList(door_seg3_dl_03014470),
    gsSPVertex(door_seg3_vertex_030143F0, 8, 0),
    gsSPBranchList(door_seg3_dl_030144E0),
};

// 0x03014558
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03014558, 0x00201410, 96653, 0x00014558, 256);

// 0x03014658
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03014658, 0x00201410, 96653, 0x00014658, 128);

// 0x030146D8
ROM_ASSET_LOAD_VTX(door_seg3_vertex_030146D8, 0x00201410, 96653, 0x000146d8, 240);

// 0x030147C8
ROM_ASSET_LOAD_VTX(door_seg3_vertex_030147C8, 0x00201410, 96653, 0x000147c8, 192);

// 0x03014888 - 0x030149C0
const Gfx door_seg3_dl_03014888[] = {
    gsSPVertex(door_seg3_vertex_030146D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  8,  7,  3, 0x0),
    gsSP2Triangles( 9,  5,  4, 0x0, 10,  9,  4, 0x0),
    gsSP2Triangles(10,  4,  6, 0x0,  9,  8,  5, 0x0),
    gsSP2Triangles( 7, 10,  6, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles(11, 10,  7, 0x0, 12,  9, 10, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 13,  8,  9, 0x0),
    gsSP2Triangles(14,  7,  8, 0x0, 13, 14,  8, 0x0),
    gsSP1Triangle(14, 11,  7, 0x0),
    gsSPVertex(door_seg3_vertex_030147C8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  4,  3,  0, 0x0),
    gsSP2Triangles( 5,  4,  8, 0x0,  6,  5,  9, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0,  4,  0,  8, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 7, 10,  1, 0x0,  8,  0,  2, 0x0),
    gsSP1Triangle( 8,  2, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x030149C0 - 0x03014A20
const Gfx door_seg3_dl_030149C0[] = {
    gsSPLight(&door_seg3_lights_03009CE0.l, 1),
    gsSPLight(&door_seg3_lights_03009CE0.a, 2),
    gsSPVertex(door_seg3_vertex_03014558, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x03014A20 - 0x03014A50
const Gfx door_seg3_dl_03014A20[] = {
    gsSPVertex(door_seg3_vertex_03014658, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x03014A50 - 0x03014A80
const Gfx door_seg3_dl_03014A50[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x03014A80 - 0x03014B30
const Gfx door_seg3_dl_03014A80[] = {
    gsSPDisplayList(door_seg3_dl_03014A50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300CD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_030149C0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300BD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014A20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014888),
};

// 0x03014B30 - 0x03014BE0
const Gfx door_seg3_dl_03014B30[] = {
    gsSPDisplayList(door_seg3_dl_03014A50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300CD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_030149C0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300BD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014A20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014888),
};

// 0x03014BE0 - 0x03014C90
const Gfx door_seg3_dl_03014BE0[] = {
    gsSPDisplayList(door_seg3_dl_03014A50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300E510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_030149C0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300D510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014A20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014888),
};

// 0x03014C90 - 0x03014D40
const Gfx door_seg3_dl_03014C90[] = {
    gsSPDisplayList(door_seg3_dl_03014A50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300FD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_030149C0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300ED10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014A20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014888),
};

// 0x03014D40 - 0x03014DF0
const Gfx door_seg3_dl_03014D40[] = {
    gsSPDisplayList(door_seg3_dl_03014A50),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03011510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_030149C0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03010510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014A20),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014888),
};

// 0x03014DF0
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03014DF0, 0x00201410, 96653, 0x00014df0, 128);

// 0x03014E70
ROM_ASSET_LOAD_VTX(door_seg3_vertex_03014E70, 0x00201410, 96653, 0x00014e70, 128);

// 0x03014EF0 - 0x03014F30
const Gfx door_seg3_dl_03014EF0[] = {
    gsSPLight(&door_seg3_lights_03009CE0.l, 1),
    gsSPLight(&door_seg3_lights_03009CE0.a, 2),
    gsSPVertex(door_seg3_vertex_03014DF0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x03014F30 - 0x03014F68
const Gfx door_seg3_dl_03014F30[] = {
    gsSPVertex(door_seg3_vertex_03014E70, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x03014F68 - 0x03014F98
const Gfx door_seg3_dl_03014F68[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x03014F98 - 0x03015008
const Gfx door_seg3_dl_03014F98[] = {
    gsSPDisplayList(door_seg3_dl_03014F68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300BD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014EF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014F30),
};

// 0x03015008 - 0x03015078
const Gfx door_seg3_dl_03015008[] = {
    gsSPDisplayList(door_seg3_dl_03014F68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300BD10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014EF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014F30),
};

// 0x03015078 - 0x030150E8
const Gfx door_seg3_dl_03015078[] = {
    gsSPDisplayList(door_seg3_dl_03014F68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300D510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014EF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014F30),
};

// 0x030150E8 - 0x03015158
const Gfx door_seg3_dl_030150E8[] = {
    gsSPDisplayList(door_seg3_dl_03014F68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_0300ED10),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014EF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014F30),
};

// 0x03015158 - 0x030151C8
const Gfx door_seg3_dl_03015158[] = {
    gsSPDisplayList(door_seg3_dl_03014F68),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, door_seg3_texture_03010510),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(door_seg3_dl_03014EF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPLight(&door_seg3_lights_03009CF8.l, 1),
    gsSPLight(&door_seg3_lights_03009CF8.a, 2),
    gsSPBranchList(door_seg3_dl_03014F30),
};
