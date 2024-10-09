#include "pc/rom_assets.h"
// Chain Chomp

// 0x06021388
UNUSED static const Lights1 chain_chomp_lights_unused1 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060213A0
UNUSED static const Lights1 chain_chomp_lights_unused2 = gdSPDefLights1(
    0x03, 0x03, 0x05,
    0x0d, 0x0f, 0x16, 0x28, 0x28, 0x28
);

// 0x060213B8
UNUSED static const Lights1 chain_chomp_lights_unused3 = gdSPDefLights1(
    0x25, 0x00, 0x00,
    0x96, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x060213D0
ROM_ASSET_LOAD_TEXTURE(chain_chomp_seg6_texture_060213D0, "actors/chain_chomp/chain_chomp_bright_shine.rgba16.inc.c", 0x001c4230, 80474, 0x000213d0, 2048);

// 0x06021BD0
ROM_ASSET_LOAD_TEXTURE(chain_chomp_seg6_texture_06021BD0, "actors/chain_chomp/chain_chomp_dull_shine.rgba16.inc.c", 0x001c4230, 80474, 0x00021bd0, 2048);

// 0x060223D0
ROM_ASSET_LOAD_TEXTURE(chain_chomp_seg6_texture_060223D0, "actors/chain_chomp/chain_chomp_tongue.rgba16.inc.c", 0x001c4230, 80474, 0x000223d0, 2048);

// 0x06022BD0
ROM_ASSET_LOAD_TEXTURE(chain_chomp_seg6_texture_06022BD0, "actors/chain_chomp/chain_chomp_tooth.rgba16.inc.c", 0x00166c60, 26968, 0x00006af0, 2048);

// 0x060233D0
ROM_ASSET_LOAD_TEXTURE(chain_chomp_seg6_texture_060233D0, "actors/chain_chomp/chain_chomp_eye.rgba16.inc.c", 0x001c4230, 80474, 0x000233d0, 2048);

// 0x06023BD0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06023BD0, 0x001c4230, 80474, 0x00023bd0, 80);

// 0x06023C20
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06023C20, 0x001c4230, 80474, 0x00023c20, 256);

// 0x06023D20
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06023D20, 0x001c4230, 80474, 0x00023d20, 240);

// 0x06023E10
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06023E10, 0x001c4230, 80474, 0x00023e10, 240);

// 0x06023F00
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06023F00, 0x001c4230, 80474, 0x00023f00, 256);

// 0x06024000 - 0x06024040
const Gfx chain_chomp_seg6_dl_06024000[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, chain_chomp_seg6_texture_060223D0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(chain_chomp_seg6_vertex_06023BD0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 0,  4,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06024040 - 0x06024240
const Gfx chain_chomp_seg6_dl_06024040[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, chain_chomp_seg6_texture_060213D0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(chain_chomp_seg6_vertex_06023C20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  8,  6, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  0,  7,  3, 0x0),
    gsSP2Triangles( 9,  6,  8, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles(10,  7,  6, 0x0, 10, 11,  7, 0x0),
    gsSP2Triangles(11,  3,  7, 0x0, 12, 10,  9, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 13, 11, 10, 0x0),
    gsSP2Triangles(14, 12,  9, 0x0, 13, 15, 11, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_06023D20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  3,  5, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 3,  9,  1, 0x0,  8,  9,  3, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11,  4,  6, 0x0),
    gsSP2Triangles(11,  6, 12, 0x0, 10, 13, 14, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_06023E10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9,  8,  5, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0,  9, 11,  8, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_06023F00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 11,  8, 0x0, 11,  5,  7, 0x0),
    gsSP2Triangles(13,  5, 11, 0x0, 12, 13, 11, 0x0),
    gsSP2Triangles(14, 13, 12, 0x0, 14, 15, 13, 0x0),
    gsSP2Triangles(15,  0,  3, 0x0, 13,  3,  5, 0x0),
    gsSP1Triangle(15,  3, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x06024240 - 0x060242D0
const Gfx chain_chomp_seg6_dl_06024240[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(chain_chomp_seg6_dl_06024000),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(chain_chomp_seg6_dl_06024040),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x060242D0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_060242D0, 0x001c4230, 80474, 0x000242d0, 224);

// 0x060243B0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_060243B0, 0x001c4230, 80474, 0x000243b0, 256);

// 0x060244B0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_060244B0, 0x001c4230, 80474, 0x000244b0, 256);

// 0x060245B0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_060245B0, 0x001c4230, 80474, 0x000245b0, 256);

// 0x060246B0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_060246B0, 0x001c4230, 80474, 0x000246b0, 80);

// 0x06024700 - 0x06024900
const Gfx chain_chomp_seg6_dl_06024700[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, chain_chomp_seg6_texture_06021BD0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(chain_chomp_seg6_vertex_060242D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 0,  5,  4, 0x0,  6,  1,  7, 0x0),
    gsSP2Triangles( 1,  3,  7, 0x0,  1,  6,  2, 0x0),
    gsSP2Triangles( 6,  8,  2, 0x0,  9,  5,  2, 0x0),
    gsSP2Triangles( 8, 10,  2, 0x0, 10, 11,  2, 0x0),
    gsSP2Triangles(11,  9,  2, 0x0,  7,  3, 12, 0x0),
    gsSP2Triangles( 3, 13, 12, 0x0,  3,  4, 13, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_060243B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  6,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  7, 0x0,  5,  8,  7, 0x0),
    gsSP2Triangles( 5,  9,  8, 0x0,  2,  4, 10, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  4,  7, 10, 0x0),
    gsSP2Triangles( 2, 10, 11, 0x0, 12,  2, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_060244B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(15,  0,  2, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_060245B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  6,  3,  0, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9,  0,  2, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 11,  2,  5, 0x0),
    gsSP2Triangles( 9,  2, 11, 0x0, 11,  5, 13, 0x0),
    gsSP2Triangles(15,  0,  9, 0x0, 15,  6,  0, 0x0),
    gsSP1Triangle( 8, 15,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x06024900 - 0x06024940
const Gfx chain_chomp_seg6_dl_06024900[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, chain_chomp_seg6_texture_060223D0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(chain_chomp_seg6_vertex_060246B0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 0,  4,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06024940 - 0x060249D0
const Gfx chain_chomp_seg6_dl_06024940[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(chain_chomp_seg6_dl_06024700),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(chain_chomp_seg6_dl_06024900),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x060249D0
static const Lights1 chain_chomp_seg6_lights_060249D0 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x060249E8
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_060249E8, 0x001c4230, 80474, 0x000249e8, 192);

// 0x06024AA8 - 0x06024B00
const Gfx chain_chomp_seg6_dl_06024AA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, chain_chomp_seg6_texture_060233D0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&chain_chomp_seg6_lights_060249D0.l, 1),
    gsSPLight(&chain_chomp_seg6_lights_060249D0.a, 2),
    gsSPVertex(chain_chomp_seg6_vertex_060249E8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x06024B00 - 0x06024B70
const Gfx chain_chomp_seg6_dl_06024B00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(chain_chomp_seg6_dl_06024AA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06024B70
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06024B70, 0x001c4230, 80474, 0x00024b70, 240);

// 0x06024C60
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06024C60, 0x001c4230, 80474, 0x00024c60, 144);

// 0x06024CF0 - 0x06024D60
const Gfx chain_chomp_seg6_dl_06024CF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, chain_chomp_seg6_texture_06022BD0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(chain_chomp_seg6_vertex_06024B70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_06024C60, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x06024D60 - 0x06024DD0
const Gfx chain_chomp_seg6_dl_06024D60[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(chain_chomp_seg6_dl_06024CF0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x06024DD0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06024DD0, 0x001c4230, 80474, 0x00024dd0, 240);

// 0x06024EC0
ROM_ASSET_LOAD_VTX(chain_chomp_seg6_vertex_06024EC0, 0x001c4230, 80474, 0x00024ec0, 144);

// 0x06024F50 - 0x06024FC0
const Gfx chain_chomp_seg6_dl_06024F50[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, chain_chomp_seg6_texture_06022BD0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(chain_chomp_seg6_vertex_06024DD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(chain_chomp_seg6_vertex_06024EC0, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x06024FC0 - 0x06025030
const Gfx chain_chomp_seg6_dl_06024FC0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(chain_chomp_seg6_dl_06024F50),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
