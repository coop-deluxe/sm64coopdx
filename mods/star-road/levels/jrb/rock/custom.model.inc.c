#include "custom.model.inc.h"
Vtx VB_jrb_geo_000930_0x7007808[] = {
{{{ 0, 0, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255}}},
{{{ -300, 0, -300 }, 0, { -4125, -1024 }, { 0, 0, 0, 255}}},
{{{ 300, 0, 300 }, 0, { -3101, -2048 }, { 0, 0, 0, 255}}},
{{{ 300, 0, -300 }, 0, { -3101, -1024 }, { 0, 0, 0, 255}}},
{{{ -300, 0, 300 }, 0, { -4125, -2048 }, { 0, 0, 0, 255}}},
};

Light_t Light_jrb_geo_000930_0x70079d8 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 255, 255, 255}, 0
};

Gfx DL_jrb_geo_000930_0x70078f8[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsSPLight(&Light_jrb_geo_000930_0x70079d8.col, 1),
gsSPLight(&Light_jrb_geo_000930_0x70079d8.col, 2),
gsDPSetTextureImage(0, 2, 1, water_09000000),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_jrb_geo_000930_0x7007808, 5, 0),
gsSP2Triangles(0, 0, 0, 0,1, 2, 3, 0),
gsSP1Triangle(2, 1, 4, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

