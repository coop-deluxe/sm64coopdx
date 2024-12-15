#include "custom.model.inc.h"
Vtx VB_ddd_geo_000478_0x7000000[] = {
{{{ 0, -579, 37 }, 0, { -2584, 3 }, { 0, 0, 0, 255}}},
{{{ 32, -579, -18 }, 0, { -2872, 4 }, { 0, 0, 0, 255}}},
{{{ 32, -579, 18 }, 0, { -2680, 4 }, { 0, 0, 0, 255}}},
{{{ 25, 580, 15 }, 0, { -2699, 5943 }, { 0, 0, 0, 255}}},
{{{ 0, 580, 30 }, 0, { -2622, 5942 }, { 0, 0, 0, 255}}},
{{{ -32, -579, 18 }, 0, { -2680, 2 }, { 0, 0, 0, 255}}},
{{{ -25, 580, 15 }, 0, { -2699, 5941 }, { 0, 0, 0, 255}}},
{{{ -32, -579, -18 }, 0, { -2872, 2 }, { 0, 0, 0, 255}}},
{{{ 0, -579, -37 }, 0, { -2968, 3 }, { 0, 0, 0, 255}}},
{{{ -25, 580, -14 }, 0, { -2852, 5941 }, { 0, 0, 0, 255}}},
{{{ 25, 580, -14 }, 0, { -2852, 5943 }, { 0, 0, 0, 255}}},
{{{ 0, 580, -29 }, 0, { -2929, 5942 }, { 0, 0, 0, 255}}},
};

Light_t Light_ddd_geo_000478_0x7000530 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 255, 255, 255}, 0
};

Gfx DL_ddd_geo_000478_0x70003c0[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsSPLight(&Light_ddd_geo_000478_0x7000530.col, 1),
gsSPLight(&Light_ddd_geo_000478_0x7000530.col, 2),
gsDPSetTextureImage(0, 2, 1, ddd_custom_texture_07000624),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_ddd_geo_000478_0x7000000, 12, 0),
gsSP2Triangles(0, 1, 2, 0,0, 3, 4, 0),
gsSP2Triangles(0, 7, 8, 0,0, 8, 1, 0),
gsSP2Triangles(1, 3, 2, 0,1, 11, 10, 0),
gsSP2Triangles(3, 0, 2, 0,3, 1, 10, 0),
gsSP2Triangles(4, 5, 0, 0,4, 9, 6, 0),
gsSP2Triangles(5, 4, 6, 0,6, 7, 5, 0),
gsSP2Triangles(7, 0, 5, 0,7, 6, 9, 0),
gsSP2Triangles(8, 9, 11, 0,9, 4, 11, 0),
gsSP2Triangles(9, 8, 7, 0,11, 1, 8, 0),
gsSP2Triangles(11, 3, 10, 0,11, 4, 3, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

