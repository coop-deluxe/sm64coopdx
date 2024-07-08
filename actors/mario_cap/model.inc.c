#include "pc/rom_assets.h"
// Mario Cap (Normal Cap, Metal, Winged, etc)

// 0x0301CF08
static const Lights1 mario_cap_seg3_lights_0301CF08 = gdSPDefLights1(
    0x39, 0x03, 0x00,
    0x73, 0x06, 0x00, 0x28, 0x28, 0x28
);

// 0x0301CF20
static const Lights1 mario_cap_seg3_lights_0301CF20 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0301CF38
static const Lights1 mario_cap_seg3_lights_0301CF38 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

static const Lights1 mario_cap_black_lights_group = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

#include "actors/mario/mario_externs.h"
#define mario_cap_texture_metal_shade              mario_texture_metal_shade
#define mario_cap_texture_metal_light              mario_texture_metal_light
#define mario_cap_texture_m_logo                   mario_texture_m_logo
#define mario_cap_texture_m_blend                  mario_texture_m_blend
#define mario_cap_texture_m_cap                    mario_texture_m_cap
#define mario_cap_texture_wings_half_1             mario_texture_wings_half_1
#define mario_cap_texture_wings_half_2             mario_texture_wings_half_2
#define mario_cap_texture_metal_wings_half_1_shade mario_texture_metal_wings_half_1_shade
#define mario_cap_texture_metal_wings_half_1_light mario_texture_metal_wings_half_1_light
#define mario_cap_texture_metal_wings_half_2_shade mario_texture_metal_wings_half_2_shade
#define mario_cap_texture_metal_wings_half_2_light mario_texture_metal_wings_half_2_light

// 0x0301CF50
ROM_ASSET_LOAD_TEXTURE(mario_cap_seg3_texture_0301CF50, "actors/mario_cap/mario_cap_metal.rgba16.inc.c", 0x00114750, 78432, 0x00000090, 4096);

// 0x0301DF50
ROM_ASSET_LOAD_TEXTURE(mario_cap_seg3_texture_0301DF50, "actors/mario_cap/mario_cap_logo.rgba16.inc.c", 0x00114750, 78432, 0x00001890, 2048);

// 0x0301E750
ROM_ASSET_LOAD_TEXTURE(mario_cap_seg3_texture_0301E750, "actors/mario_cap/mario_cap_wing.rgba16.inc.c", 0x00114750, 78432, 0x00008090, 4096);

// 0x0301F750
ROM_ASSET_LOAD_TEXTURE(mario_cap_seg3_texture_0301F750, "actors/mario_cap/mario_cap_wing_tip.rgba16.inc.c", 0x00114750, 78432, 0x00009090, 4096);

// 0x03020750
ROM_ASSET_LOAD_TEXTURE(mario_cap_seg3_texture_03020750, "actors/mario_cap/mario_cap_metal_wing_unused.rgba16.inc.c", 0x00114750, 78432, 0x0000a090, 4096);

// 0x03021750
ROM_ASSET_LOAD_TEXTURE(mario_cap_seg3_texture_03021750, "actors/mario_cap/mario_cap_metal_wing_tip_unused.rgba16.inc.c", 0x00114750, 78432, 0x0000b090, 4096);

// 0x03022750
ROM_ASSET_LOAD_VTX(mario_cap_seg3_vertex_03022750, 0x00114750, 78432, 0x0001bf50, 112);

// 0x030227C0
ROM_ASSET_LOAD_VTX(mario_cap_seg3_vertex_030227C0, 0x00114750, 78432, 0x0001bfc0, 256);

// 0x030228C0
ROM_ASSET_LOAD_VTX(mario_cap_seg3_vertex_030228C0, 0x00114750, 78432, 0x0001c0c0, 240);

// 0x030229B0
ROM_ASSET_LOAD_VTX(mario_cap_seg3_vertex_030229B0, 0x00114750, 78432, 0x0001c1b0, 240);

// 0x03022AA0
ROM_ASSET_LOAD_VTX(mario_cap_seg3_vertex_03022AA0, 0x00114750, 78432, 0x0001c2a0, 144);

// 0x03022B30 - 0x03022B68
const Gfx mario_cap_seg3_dl_03022B30[] = {
    gsSPVertex(mario_cap_seg3_vertex_03022750, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  2,  3,  0, 0x0),
    gsSP1Triangle( 5,  6,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x03022B68 - 0x03022CC8
const Gfx mario_cap_seg3_dl_03022B68[] = {
    gsSPVertex(mario_cap_seg3_vertex_030227C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 3,  0,  5, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles(11,  8,  7, 0x0,  8, 12,  9, 0x0),
    gsSP2Triangles(12,  8, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(mario_cap_seg3_vertex_030228C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  5,  1,  0, 0x0),
    gsSP2Triangles( 1,  6,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9,  7,  6, 0x0, 10,  4,  3, 0x0),
    gsSP2Triangles( 9, 11,  7, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12, 11,  9, 0x0, 13, 14,  4, 0x0),
    gsSPVertex(mario_cap_seg3_vertex_030229B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  1, 0x0,  1,  4,  2, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 8,  7,  2, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 10,  9, 0x0,  7, 10,  0, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0,  0, 10, 12, 0x0),
    gsSP2Triangles(11,  8, 13, 0x0, 14, 12,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x03022CC8 - 0x03022D10
const Gfx mario_cap_seg3_dl_03022CC8[] = {
    gsSPVertex(mario_cap_seg3_vertex_03022AA0, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  6,  5, 0x0),
    gsSP2Triangles( 0,  7,  5, 0x0,  0,  5,  1, 0x0),
    gsSP1Triangle( 2,  8,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x03022D10 - 0x03022D38
const Gfx mario_cap_seg3_dl_03022D10[] = {
    gsSPDisplayList(mario_cap_seg3_dl_03022B68),
    gsDPSetCombineLERP(SHADE, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, SHADE, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsDPSetPrimColor(0, 0, 115, 115, 115, 255),
    gsSPCopyLightsPlayerPart(CAP),
    gsSPDisplayList(mario_cap_seg3_dl_03022CC8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x03022D38
static const Vtx mario_cap_seg3_vertex_03022D38[] = {
    {{{   199,    247,    -55}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   131,    274,     20}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    69,     71,     38}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   199,    247,    -55}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    69,     71,     38}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   138,     44,    -37}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -137,     44,    -37}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -68,     71,     38}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -198,    247,    -55}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -68,     71,     38}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -130,    274,     20}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -198,    247,    -55}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x03022DF8
static const Vtx mario_cap_seg3_vertex_03022DF8[] = {
    {{{   268,    219,   -132}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   199,    247,    -55}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   138,     44,    -37}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   207,     16,   -114}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -206,     16,   -114}, 0, {   990,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -137,     44,    -37}, 0, {     0,   2012}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -267,    219,   -132}, 0, {   990,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -198,    247,    -55}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x03022E78 - 0x03022EA8
const Gfx mario_cap_seg3_dl_03022E78[] = {
    gsSPVertex(mario_cap_seg3_vertex_03022D38, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x03022EA8 - 0x03022ED8
const Gfx mario_cap_seg3_dl_03022EA8[] = {
    gsSPVertex(mario_cap_seg3_vertex_03022DF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x03022ED8 - 0x03022F20
const Gfx mario_cap_seg3_dl_03022ED8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

const Gfx mario_cap_seg3_dl_03022ED8_metal[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsSPEndDisplayList(),
};

// 0x03022F20 - 0x03022F48
const Gfx mario_cap_seg3_dl_03022F20[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

const Gfx mario_cap_m_logo_decal[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, SHADE, TEXEL1, SHADE, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, SHADE, TEXEL1, SHADE, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 17),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_m_logo),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_m_blend),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_cap_seg3_dl_03022B30),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, TEXEL1, 0, ENVIRONMENT, 0, TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, TEXEL1, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPCopyLightsPlayerPart(CAP),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_m_logo),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_m_cap),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),
    gsSPDisplayList(mario_cap_seg3_dl_03022B30),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x03022F48 - 0x03022FF8
const Gfx mario_cap_seg3_dl_03022F48[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(CAP),
    gsSPDisplayList(mario_cap_seg3_dl_03022D10),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x03022FF8 - 0x030230B0
const Gfx mario_cap_seg3_dl_03022FF8[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT),
    gsSPSetGeometryMode(G_TEXTURE_GEN),
    gsSPTexture(4032, 1984, 0, 0, 1),
    gsSPLight(&mario_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(1, 0, 0, 252, 124),
    gsSPDisplayList(mario_cap_seg3_dl_03022B30),
    gsSPDisplayList(mario_cap_seg3_dl_03022B68),
    gsSPDisplayList(mario_cap_seg3_dl_03022CC8),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0x0F80, 0x07C0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x030230B0 - 0x03023108
const Gfx mario_cap_seg3_dl_030230B0[] = {
    gsSPDisplayList(mario_cap_seg3_dl_03022ED8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_cap_texture_wings_half_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_cap_seg3_dl_03022E78),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_cap_texture_wings_half_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_cap_seg3_dl_03022EA8),
    gsSPDisplayList(mario_cap_seg3_dl_03022F20),
    gsSPEndDisplayList(),
};

// 0x03023108 - 0x03023160
const Gfx mario_cap_seg3_dl_03023108[] = {
    gsSPDisplayList(mario_cap_seg3_dl_03022ED8_metal),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_1_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_1_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_cap_seg3_dl_03022E78),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_2_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_2_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_cap_seg3_dl_03022EA8),
    gsSPDisplayList(mario_cap_seg3_dl_03022F20),
    gsSPEndDisplayList(),
};

// 0x03023160 - 0x03023298
const Gfx mario_cap_seg3_dl_03023160[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPCopyLightsPlayerPart(CAP), //gsSPLight(&mario_cap_seg3_lights_0301CF38.a, 2),
    gsSPDisplayList(mario_cap_seg3_dl_03022D10),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_cap_texture_wings_half_1),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_cap_seg3_dl_03022E78),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mario_cap_texture_wings_half_2),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(mario_cap_seg3_dl_03022EA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x03023298 - 0x030233D0
const Gfx mario_cap_seg3_dl_03023298[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, TEXEL1, 0, 0, 0, ENVIRONMENT),
    gsSPSetGeometryMode(G_TEXTURE_GEN),
    gsSPTexture(4032, 1984, 0, 0, 1),
    gsSPLight(&mario_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(0, 0, 0, 252, 124),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 128),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0),
    gsDPSetTileSize(1, 0, 0, 252, 124),
    gsSPDisplayList(mario_cap_seg3_dl_03022B30),
    gsSPDisplayList(mario_cap_seg3_dl_03022B68),
    gsSPDisplayList(mario_cap_seg3_dl_03022CC8),
    gsSPTexture(0x0F80, 0x07C0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, SHADE, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0),
    gsSPTexture(65535, 65535, 0, 0, 1),
    gsSPLight(&mario_cap_black_lights_group.l, 1),
    gsSPCopyLightEXT(2, 15),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_1_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_1_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_cap_seg3_dl_03022E78),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_2_shade),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 252),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, mario_cap_texture_metal_wings_half_2_light),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 512, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 2047, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 512, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 6, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 252),
    gsSPDisplayList(mario_cap_seg3_dl_03022EA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

const Gfx mario_cap_material_revert_render_settings[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
    gsSPTexture(65535, 65535, 0, 0, 0),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetAlphaCompare(G_AC_NONE),

    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(7, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),

    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
    gsDPLoadBlock(6, 0, 0, 1023, 256),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 5, 0),
    gsDPSetTileSize(1, 0, 0, 124, 124),

    gsSPEndDisplayList(),
};
