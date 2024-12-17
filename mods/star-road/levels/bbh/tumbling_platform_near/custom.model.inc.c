#include "custom.model.inc.h"

ALIGNED8 const Texture spooky_09004000[] = {
#include "../../textures/spooky/bbh_textures.04000.rgba16.inc.c"
};

Vtx VB_geo_bbh_0005F8_0x701f870[] = {
{{{ 0, 233, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255}}},
{{{ 0, -6, 0 }, 0, { -3681, 0 }, { 0, 0, 0, 255}}},
{{{ -282, 292, 282 }, 0, { -3681, 957 }, { 0, 0, 0, 255}}},
{{{ 282, 292, 282 }, 0, { -2401, 957 }, { 0, 0, 0, 255}}},
{{{ -282, 292, -282 }, 0, { -4961, 957 }, { 0, 0, 0, 255}}},
{{{ 282, 292, -282 }, 0, { -3681, 957 }, { 0, 0, 0, 255}}},
};

Vtx VB_geo_bbh_0005F8_0x701f8d0[] = {
{{{ -282, 292, -282 }, 0, { -6780, -1167 }, { 0, 0, 0, 255}}},
{{{ 282, 292, 282 }, 0, { -5332, -2615 }, { 0, 0, 0, 255}}},
{{{ 282, 292, -282 }, 0, { -5332, -1167 }, { 0, 0, 0, 255}}},
{{{ -282, 292, 282 }, 0, { -6780, -2615 }, { 0, 0, 0, 255}}},
};

Light_t Light_geo_bbh_0005F8_0x701fb98 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 255, 255, 255}, 0
};

Gfx DL_geo_bbh_0005F8_0x701fa50[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsSPLight(&Light_geo_bbh_0005F8_0x701fb98.col, 1),
gsSPLight(&Light_geo_bbh_0005F8_0x701fb98.col, 2),
gsDPSetTextureImage(0, 2, 1, spooky_09004000),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_geo_bbh_0005F8_0x701f870, 6, 0),
gsSP2Triangles(0, 0, 0, 0,2, 1, 3, 0),
gsSP2Triangles(4, 1, 2, 0,5, 1, 4, 0),
gsSP1Triangle(5, 3, 1, 0),
gsDPSetTextureImage(0, 2, 1, spooky_09004800),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_geo_bbh_0005F8_0x701f8d0, 4, 0),
gsSP2Triangles(0, 1, 2, 0,1, 0, 3, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

