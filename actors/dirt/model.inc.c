#include "pc/rom_assets.h"
// Dirt

// 0x0302BD68
static const Lights1 dirt_seg3_lights_0302BD68 = gdSPDefLights1(
    0x3f, 0x19, 0x19,
    0xff, 0x64, 0x64, 0x28, 0x28, 0x28
);

// 0x0302BD80
static const Lights1 dirt_seg3_lights_0302BD80 = gdSPDefLights1(
    0x19, 0x3f, 0x19,
    0x64, 0xff, 0x64, 0x28, 0x28, 0x28
);

// 0x0302BD98
static const Lights1 dirt_seg3_lights_0302BD98 = gdSPDefLights1(
    0x19, 0x19, 0x3f,
    0x64, 0x64, 0xff, 0x28, 0x28, 0x28
);

// 0x0302BDB0
static const Lights1 dirt_seg3_lights_0302BDB0 = gdSPDefLights1(
    0x3f, 0x3f, 0x19,
    0xff, 0xff, 0x64, 0x28, 0x28, 0x28
);

// 0x0302BDC8
ROM_ASSET_LOAD_VTX(dirt_seg3_vertex_0302BDC8, 0x00201410, 96653, 0x0002bdc8, 48);

// 0x0302BDF8
ROM_ASSET_LOAD_TEXTURE(dirt_seg3_texture_0302BDF8, "actors/dirt/dirt_particle.rgba16.inc.c", 0x00201410, 96653, 0x0002bdf8, 512);

// 0x0302BFF8 - 0x0302C028
const Gfx dirt_seg3_dl_0302BFF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dirt_seg3_texture_0302BDF8),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dirt_seg3_vertex_0302BDC8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0302C028 - 0x0302C098
const Gfx dirt_seg3_dl_0302C028[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(dirt_seg3_dl_0302BFF8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0302C098
ROM_ASSET_LOAD_VTX(dirt_seg3_vertex_0302C098, 0x00201410, 96653, 0x0002c098, 48);

// 0x0302C0C8
ROM_ASSET_LOAD_VTX(dirt_seg3_vertex_0302C0C8, 0x00201410, 96653, 0x0002c0c8, 48);

// 0x0302C0F8
ROM_ASSET_LOAD_VTX(dirt_seg3_vertex_0302C0F8, 0x00201410, 96653, 0x0002c0f8, 160);

// 0x0302C198
ROM_ASSET_LOAD_VTX(dirt_seg3_vertex_0302C198, 0x00201410, 96653, 0x0002c198, 160);

// 0x0302C238 - 0x0302C298
const Gfx dirt_seg3_dl_0302C238[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(dirt_seg3_vertex_0302C0F8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  6,  7,  0, 0x0),
    gsSP2Triangles( 2,  8,  6, 0x0,  1,  9,  2, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  2,  6,  0, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0302C298 - 0x0302C2B8
const Gfx dirt_seg3_dl_0302C298[] = {
    gsSPLight(&dirt_seg3_lights_0302BD68.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BD68.a, 2),
    gsSPDisplayList(dirt_seg3_dl_0302C238),
    gsSPEndDisplayList(),
};

// 0x0302C2B8 - 0x0302C2D8
const Gfx dirt_seg3_dl_0302C2B8[] = {
    gsSPLight(&dirt_seg3_lights_0302BD80.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BD80.a, 2),
    gsSPDisplayList(dirt_seg3_dl_0302C238),
    gsSPEndDisplayList(),
};

// 0x0302C2D8 - 0x0302C2F8
const Gfx dirt_seg3_dl_0302C2D8[] = {
    gsSPLight(&dirt_seg3_lights_0302BD98.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BD98.a, 2),
    gsSPDisplayList(dirt_seg3_dl_0302C238),
    gsSPEndDisplayList(),
};

// 0x0302C2F8 - 0x0302C318
const Gfx dirt_seg3_dl_0302C2F8[] = {
    gsSPLight(&dirt_seg3_lights_0302BDB0.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BDB0.a, 2),
    gsSPDisplayList(dirt_seg3_dl_0302C238),
    gsSPEndDisplayList(),
};

// 0x0302C318 - 0x0302C378
const Gfx dirt_seg3_dl_0302C318[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPVertex(dirt_seg3_vertex_0302C198, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 0,  5,  3, 0x0,  6,  7,  0, 0x0),
    gsSP2Triangles( 2,  8,  6, 0x0,  1,  9,  2, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  2,  6,  0, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0302C378 - 0x0302C3B0
const Gfx dirt_seg3_dl_0302C378[] = {
    gsSPLight(&dirt_seg3_lights_0302BD68.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BD68.a, 2),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(dirt_seg3_vertex_0302C098, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0302C3B0 - 0x0302C3E8
const Gfx dirt_seg3_dl_0302C3B0[] = {
    gsSPLight(&dirt_seg3_lights_0302BD80.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BD80.a, 2),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(dirt_seg3_vertex_0302C098, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0302C3E8 - 0x0302C420
const Gfx dirt_seg3_dl_0302C3E8[] = {
    gsSPLight(&dirt_seg3_lights_0302BD98.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BD98.a, 2),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(dirt_seg3_vertex_0302C098, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0302C420 - 0x0302C458
const Gfx dirt_seg3_dl_0302C420[] = {
    gsSPLight(&dirt_seg3_lights_0302BDB0.l, 1),
    gsSPLight(&dirt_seg3_lights_0302BDB0.a, 2),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPVertex(dirt_seg3_vertex_0302C098, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0302C458 - 0x0302C480
const Gfx dirt_seg3_dl_0302C458[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPVertex(dirt_seg3_vertex_0302C0C8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
