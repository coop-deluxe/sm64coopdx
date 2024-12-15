#include "custom.model.inc.h"
Vtx VB_geo_bbh_000640_0x600d578[] = {
{{{ 0, 80, 0 }, 0, { -16896, 5632 }, { 0, 0, 0, 255}}},
{{{ 299, -20, -300 }, 0, { -17408, 6144 }, { 0, 0, 0, 255}}},
{{{ 299, -20, 299 }, 0, { -17408, 5120 }, { 0, 0, 0, 255}}},
{{{ -300, -20, -300 }, 0, { -16384, 6144 }, { 0, 0, 0, 255}}},
{{{ -300, -20, 299 }, 0, { -16384, 5120 }, { 0, 0, 0, 255}}},
{{{ 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255}}},
};

Light_t Light_geo_bbh_000640_0x600d748 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 255, 255, 255}, 0
};

Gfx DL_geo_bbh_000640_0x600d668[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsSPLight(&Light_geo_bbh_000640_0x600d748.col, 1),
gsSPLight(&Light_geo_bbh_000640_0x600d748.col, 2),
gsDPSetTextureImage(0, 2, 1, spooky_09006800),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_geo_bbh_000640_0x600d578, 6, 0),
gsSP2Triangles(0, 3, 4, 0,1, 0, 2, 0),
gsSP2Triangles(1, 3, 0, 0,2, 0, 4, 0),
gsSP1Triangle(5, 5, 5, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

