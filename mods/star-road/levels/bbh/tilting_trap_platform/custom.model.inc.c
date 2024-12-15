#include "custom.model.inc.h"

ALIGNED8 const Texture spooky_09002400[] = {
#include "../../textures/spooky/bbh_textures.02400.rgba16.inc.c"
};

Vtx VB_geo_bbh_0005C8_0x701f390[] = {
{{{ 400, 46, 199 }, 0, { 5889, -9215 }, { 0, 0, 0, 255}}},
{{{ -399, 56, -200 }, 0, { 3852, -13289 }, { 0, 0, 0, 255}}},
{{{ -399, 56, 199 }, 0, { 5889, -13289 }, { 0, 0, 0, 255}}},
{{{ 400, 46, -200 }, 0, { 3852, -9215 }, { 0, 0, 0, 255}}},
};

Vtx VB_geo_bbh_0005C8_0x701f3d0[] = {
{{{ 399, -58, -199 }, 0, { 967, 7175 }, { 0, 0, 0, 255}}},
{{{ 400, 46, 199 }, 0, { -89, 7439 }, { 0, 0, 0, 255}}},
{{{ 400, 46, -200 }, 0, { 967, 7453 }, { 0, 0, 0, 255}}},
{{{ 399, -53, 200 }, 0, { -89, 7175 }, { 0, 0, 0, 255}}},
{{{ -400, -43, 200 }, 0, { -89, 5062 }, { 0, 0, 0, 255}}},
{{{ -400, -43, 200 }, 0, { -2202, 7175 }, { 0, 0, 0, 255}}},
{{{ -400, -48, -199 }, 0, { 3080, 7175 }, { 0, 0, 0, 255}}},
{{{ -399, 56, 199 }, 0, { -2202, 7439 }, { 0, 0, 0, 255}}},
{{{ -400, -48, -199 }, 0, { 967, 5062 }, { 0, 0, 0, 255}}},
{{{ -399, 56, -200 }, 0, { 3080, 7453 }, { 0, 0, 0, 255}}},
};

Light_t Light_geo_bbh_0005C8_0x701f6f0 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 255, 255, 255}, 0
};

Gfx DL_geo_bbh_0005C8_0x701f570[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsSPLight(&Light_geo_bbh_0005C8_0x701f6f0.col, 1),
gsSPLight(&Light_geo_bbh_0005C8_0x701f6f0.col, 2),
gsDPSetTextureImage(0, 2, 1, spooky_09000800),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_geo_bbh_0005C8_0x701f390, 4, 0),
gsSP2Triangles(0, 1, 2, 0,1, 0, 3, 0),
gsDPSetTextureImage(0, 2, 1, spooky_09002400),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPPipeSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_geo_bbh_0005C8_0x701f3d0, 10, 0),
gsSP2Triangles(0, 1, 3, 0,0, 4, 8, 0),
gsSP2Triangles(1, 0, 2, 0,1, 5, 3, 0),
gsSP2Triangles(2, 6, 9, 0,4, 0, 3, 0),
gsSP2Triangles(5, 1, 7, 0,6, 2, 0, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

