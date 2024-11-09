#include "pc/rom_assets.h"
// Sushi (Shark)

// Could be a duplicate binid of the previous actor, but i'm putting it here for
// macro reasons so I don't have to clutter the macros.inc with a new macro for this
// case.
UNUSED static const u64 sushi_unused_1 = 1;

// 0x05008ED0
ROM_ASSET_LOAD_TEXTURE(sushi_seg5_texture_05008ED0, "actors/sushi/sushi_snout.rgba16.inc.c", 0x0013b910, 41727, 0x00008ed0, 2048);

// 0x050096D0
ROM_ASSET_LOAD_TEXTURE(sushi_seg5_texture_050096D0, "actors/sushi/sushi_eye.rgba16.inc.c", 0x0013b910, 41727, 0x000096d0, 1024);

// 0x05009AD0
ROM_ASSET_LOAD_TEXTURE(sushi_seg5_texture_05009AD0, "actors/sushi/sushi_tooth.rgba16.inc.c", 0x0013b910, 41727, 0x00009ad0, 128);

// 0x05009B50
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_05009B50, 0x0013b910, 41727, 0x00009b50, 240);

// 0x05009C40
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_05009C40, 0x0013b910, 41727, 0x00009c40, 128);

// 0x05009CC0 - 0x05009DD0
const Gfx sushi_seg5_dl_05009CC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sushi_seg5_texture_05008ED0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sushi_seg5_vertex_05009B50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  1,  0, 0x0),
    gsSP2Triangles( 1,  5,  3, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 5,  0,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 6,  8,  3, 0x0,  3,  8,  7, 0x0),
    gsSP2Triangles( 9,  2, 10, 0x0,  2,  4, 10, 0x0),
    gsSP2Triangles( 2,  9,  0, 0x0, 10,  4,  7, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles(12, 13,  7, 0x0,  7, 13, 14, 0x0),
    gsSP2Triangles( 7, 14, 11, 0x0,  8, 12,  7, 0x0),
    gsSP2Triangles(11, 14,  9, 0x0,  6, 12,  8, 0x0),
    gsSPVertex(sushi_seg5_vertex_05009C40, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 5,  2,  6, 0x0,  7,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05009DD0 - 0x05009E40
const Gfx sushi_seg5_dl_05009DD0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sushi_seg5_dl_05009CC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05009E40
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_05009E40, 0x0013b910, 41727, 0x00009e40, 240);

// 0x05009F30 - 0x0500A008
const Gfx sushi_seg5_dl_05009F30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sushi_seg5_texture_05008ED0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sushi_seg5_vertex_05009E40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  5,  7,  0, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  5,  0, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8,  0,  9, 0x0),
    gsSP2Triangles( 3,  8, 10, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles( 9,  2, 11, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles( 3, 10, 12, 0x0, 11, 12, 10, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0, 13,  4,  3, 0x0),
    gsSP2Triangles(11, 13, 12, 0x0,  1, 14, 11, 0x0),
    gsSP2Triangles(11, 14, 13, 0x0, 12, 13,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A008 - 0x0500A078
const Gfx sushi_seg5_dl_0500A008[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sushi_seg5_dl_05009F30),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A078
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A078, 0x0013b910, 41727, 0x0000a078, 112);

// 0x0500A0E8 - 0x0500A160
const Gfx sushi_seg5_dl_0500A0E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sushi_seg5_texture_05008ED0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sushi_seg5_vertex_0500A078, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles( 6,  3,  0, 0x0,  6,  4,  3, 0x0),
    gsSP2Triangles( 5,  4,  2, 0x0,  4,  6,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A160 - 0x0500A1D0
const Gfx sushi_seg5_dl_0500A160[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sushi_seg5_dl_0500A0E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A1D0
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A1D0, 0x0013b910, 41727, 0x0000a1d0, 240);

// 0x0500A2C0
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A2C0, 0x0013b910, 41727, 0x0000a2c0, 256);

// 0x0500A3C0
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A3C0, 0x0013b910, 41727, 0x0000a3c0, 224);

// 0x0500A4A0
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A4A0, 0x0013b910, 41727, 0x0000a4a0, 160);

// 0x0500A540
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A540, 0x0013b910, 41727, 0x0000a540, 64);

// 0x0500A580 - 0x0500A748
const Gfx sushi_seg5_dl_0500A580[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sushi_seg5_texture_05008ED0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sushi_seg5_vertex_0500A1D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0,  8,  2,  9, 0x0),
    gsSP2Triangles( 2,  8, 10, 0x0,  1,  9,  2, 0x0),
    gsSP2Triangles( 1,  0,  9, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 11,  9,  0, 0x0),
    gsSP1Triangle(13, 14,  9, 0x0),
    gsSPVertex(sushi_seg5_vertex_0500A2C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  5,  6,  1, 0x0),
    gsSP2Triangles( 7,  4,  3, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles( 9, 14,  8, 0x0,  8, 14,  6, 0x0),
    gsSP2Triangles( 6, 14,  2, 0x0, 15, 14,  9, 0x0),
    gsSPVertex(sushi_seg5_vertex_0500A3C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 6,  5,  1, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 5,  6,  8, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0,  9,  6,  1, 0x0),
    gsSP2Triangles( 1,  4,  9, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSPVertex(sushi_seg5_vertex_0500A4A0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A748 - 0x0500A768
const Gfx sushi_seg5_dl_0500A748[] = {
    gsSPVertex(sushi_seg5_vertex_0500A540, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A768 - 0x0500A7E0
const Gfx sushi_seg5_dl_0500A768[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sushi_seg5_dl_0500A580),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(sushi_seg5_dl_0500A748),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A7E0
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A7E0, 0x0013b910, 41727, 0x0000a7e0, 128);

// 0x0500A860 - 0x0500A8A8
const Gfx sushi_seg5_dl_0500A860[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sushi_seg5_texture_050096D0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sushi_seg5_vertex_0500A7E0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A8A8 - 0x0500A918
const Gfx sushi_seg5_dl_0500A8A8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sushi_seg5_dl_0500A860),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500A918
ROM_ASSET_LOAD_VTX(sushi_seg5_vertex_0500A918, 0x0013b910, 41727, 0x0000a918, 64);

// 0x0500A958 - 0x0500A990
const Gfx sushi_seg5_dl_0500A958[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sushi_seg5_texture_05009AD0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(sushi_seg5_vertex_0500A918, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500A990 - 0x0500AA00
const Gfx sushi_seg5_dl_0500A990[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(sushi_seg5_dl_0500A958),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
