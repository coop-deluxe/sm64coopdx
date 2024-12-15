#include "custom.model.inc.h"
Vtx VB_bowser_3_geo_0002A8_0x7003748[] = {
{{{ 0, 127, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255}}},
{{{ -188, 127, -581 }, 0, { -1146, 5041 }, { 0, 0, 0, 255}}},
{{{ -188, 127, 581 }, 0, { -1146, -4478 }, { 0, 0, 0, 255}}},
{{{ 283, 127, 871 }, 0, { 2075, -6858 }, { 0, 0, 0, 255}}},
{{{ -610, 127, 0 }, 0, { -4028, 281 }, { 0, 0, 0, 255}}},
{{{ -741, 127, -538 }, 0, { -4918, 4694 }, { 0, 0, 0, 255}}},
{{{ 283, 127, -871 }, 0, { 2075, 7421 }, { 0, 0, 0, 255}}},
{{{ -741, 127, 538 }, 0, { -4918, -4131 }, { 0, 0, 0, 255}}},
{{{ 494, 127, 359 }, 0, { 3516, -2660 }, { 0, 0, 0, 255}}},
{{{ 494, 127, -359 }, 0, { 3516, 3223 }, { 0, 0, 0, 255}}},
{{{ 916, 127, 0 }, 0, { 6398, 281 }, { 0, 0, 0, 255}}},
};

Light_t Light_bowser_3_geo_0002A8_0x7002008 = {
{ 102, 102, 102}, 0, { 102, 102, 102}, 0, { 40, 40, 40}, 0
};

Ambient_t Light_bowser_3_geo_0002A8_0x7002000 = {
{102, 102, 102}, 0, {102, 102, 102}, 0
};

Gfx DL_bowser_3_geo_0002A8_0x7003928[] = {
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 1),
gsSPLight(&Light_bowser_3_geo_0002A8_0x7002008.col, 1),
gsSPLight(&Light_bowser_3_geo_0002A8_0x7002000.col, 2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0),
gsSPTexture(65535, 65535, 0, 0, 1),
gsDPTileSync(),
gsDPSetTextureImage(0, 2, 1, bowser_3_custom_texture_0401D560),
gsDPSetTile(0, 2, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0),
gsDPLoadSync(),
gsDPLoadBlock(7, 0, 0, 1023, 256),
gsDPSetTile(0, 2, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0),
gsDPSetTileSize(0, 0, 0, 124, 124),
gsSPVertex(VB_bowser_3_geo_0002A8_0x7003748, 11, 0),
gsSP2Triangles(0, 0, 0, 0,1, 2, 3, 0),
gsSP2Triangles(1, 3, 6, 0,1, 4, 2, 0),
gsSP2Triangles(2, 4, 7, 0,4, 1, 5, 0),
gsSP2Triangles(6, 3, 8, 0,6, 8, 9, 0),
gsSP1Triangle(9, 8, 10, 0),
gsSPTexture(65535, 65535, 0, 0, 0),
gsDPPipeSync(),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE, TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE),
gsSPTexture(65535, 65535, 0, 0, 0),
gsSPEndDisplayList(),
};

