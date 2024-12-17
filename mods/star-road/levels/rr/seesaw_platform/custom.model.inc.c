#include "custom.model.inc.h"
Vtx VB_rr_geo_000908_0x3032048[] = {
{{{ 128, 512, 0 }, 0, { 990, 0 }, { 0, 0, 127, 255}}},
{{{ -127, 512, 0 }, 0, { 0, 0 }, { 0, 0, 127, 255}}},
{{{ -127, 0, 0 }, 0, { 0, 2012 }, { 0, 0, 127, 255}}},
{{{ 128, 0, 0 }, 0, { 990, 2012 }, { 0, 0, 127, 255}}},
};

Light_t Light_rr_geo_000908_0x302de18 = {
{ 255, 255, 255}, 0, { 255, 255, 255}, 0, { 40, 40, 40}, 0
};

Ambient_t Light_rr_geo_000908_0x302de10 = {
{63, 63, 63}, 0, {63, 63, 63}, 0
};

Gfx DL_rr_geo_000908_0x701b0c8[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0),
gsSPGeometryMode(G_SHADING_SMOOTH, 0),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsSPTexture(65535, 65535, 0, 0, 1),
gsDPTileSync(),
gsDPSetTile(0, 2, 8, 0, 0, 0, 2, 6, 0, 2, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 252),
gsDPSetTextureImage(0, 2, 1, rr_custom_texture_0300BD10),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 2047, 256),
gsSPLight(&Light_rr_geo_000908_0x302de18.col, 1),
gsSPLight(&Light_rr_geo_000908_0x302de10.col, 2),
gsSPVertex(VB_rr_geo_000908_0x3032048, 4, 0),
gsSP2Triangles(0, 1, 2, 0,0, 2, 3, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsDPPipeSync(),
gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
gsSPGeometryMode(0, G_SHADING_SMOOTH),
gsSPEndDisplayList(),
};

