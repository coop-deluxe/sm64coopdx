#include "custom.model.inc.h"
// 0x0701FDB8 - 0x0701FEA8
ALIGNED8 const Texture spooky_09005600[] = {
#include "../../textures/spooky/bbh_textures.05600.rgba16.inc.c"
};

Vtx VB_geo_bbh_000628_0x701fdb8[] = {
{{{ -300, 800, -299 }, 0, { 3748, 14623 }, { 0, 0, 0, 255}}},
{{{ 300, 800, 300 }, 0, { 5284, 13087 }, { 0, 0, 0, 255}}},
{{{ 300, 800, -299 }, 0, { 5284, 14623 }, { 0, 0, 0, 255}}},
{{{ -300, 800, 300 }, 0, { 3748, 13087 }, { 0, 0, 0, 255}}},
};

Vtx VB_geo_bbh_000628_0x701fdf8[] = {
{{{ -300, 800, -299 }, 0, { 17320, 8308 }, { 0, 0, 0, 255}}},
{{{ 300, -800, -299 }, 0, { 18769, 4212 }, { 0, 0, 0, 255}}},
{{{ -300, -800, -299 }, 0, { 17320, 4212 }, { 0, 0, 0, 255}}},
{{{ -300, -800, 300 }, 0, { 15872, 4212 }, { 0, 0, 0, 255}}},
{{{ -300, 800, 300 }, 0, { 15872, 8308 }, { 0, 0, 0, 255}}},
{{{ 300, 800, 300 }, 0, { 17320, 8308 }, { 0, 0, 0, 255}}},
{{{ 300, 800, -299 }, 0, { 18769, 8308 }, { 0, 0, 0, 255}}},
{{{ 300, -800, 300 }, 0, { 17320, 4212 }, { 0, 0, 0, 255}}},
};

Light_t Light_geo_bbh_000628_0x70200e0 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 255, 255, 255}, 0
};

Gfx DL_geo_bbh_000628_0x701ff98[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsSPLight(&Light_geo_bbh_000628_0x70200e0.col, 1),
gsSPLight(&Light_geo_bbh_000628_0x70200e0.col, 2),
gsDPSetTextureImage(0, 2, 1, spooky_09005600),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_geo_bbh_000628_0x701fdb8, 4, 0),
gsSP2Triangles(0, 1, 2, 0,1, 0, 3, 0),
gsDPSetTextureImage(0, 2, 1, spooky_09006000),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_geo_bbh_000628_0x701fdf8, 8, 0),
gsSP2Triangles(0, 1, 2, 0,0, 3, 4, 0),
gsSP2Triangles(1, 0, 6, 0,1, 5, 7, 0),
gsSP2Triangles(3, 0, 2, 0,3, 5, 4, 0),
gsSP2Triangles(5, 1, 6, 0,5, 3, 7, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

