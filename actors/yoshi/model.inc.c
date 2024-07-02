#include "pc/rom_assets.h"
// Yoshi

// 0x0501C458
static const Lights1 yoshi_seg5_lights_0501C458 = gdSPDefLights1(
    0x00, 0x7c, 0x00,
    0x00, 0xf9, 0x00, 0x28, 0x28, 0x28
);

// 0x0501C470
static const Lights1 yoshi_seg5_lights_0501C470 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0501C488
static const Lights1 yoshi_seg5_lights_0501C488 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0501C4A0
ROM_ASSET_LOAD_TEXTURE(yoshi_seg5_texture_0501C4A0, "actors/yoshi/yoshi_eye.rgba16.inc.c", 0x0016d870, 76997, 0x0001c588, 512);

// 0x0501C6A0
ROM_ASSET_LOAD_TEXTURE(yoshi_seg5_texture_0501C6A0, "actors/yoshi/yoshi_eye_blink.rgba16.inc.c", 0x0016d870, 76997, 0x0001c788, 512);

// 0x0501C8A0
ROM_ASSET_LOAD_TEXTURE(yoshi_seg5_texture_0501C8A0, "actors/yoshi/yoshi_nostril.rgba16.inc.c", 0x0016d870, 76997, 0x0001c988, 512);

// 0x0501CAA0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CAA0, 0x0016d870, 76997, 0x0001cb88, 96);

// 0x0501CB00
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CB00, 0x0016d870, 76997, 0x0001cbe8, 176);

// 0x0501CBB0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CBB0, 0x0016d870, 76997, 0x0001cc98, 80);

// 0x0501CC00
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CC00, 0x0016d870, 76997, 0x0001cce8, 240);

// 0x0501CCF0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CCF0, 0x0016d870, 76997, 0x0001cdd8, 240);

// 0x0501CDE0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CDE0, 0x0016d870, 76997, 0x0001cec8, 256);

// 0x0501CEE0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CEE0, 0x0016d870, 76997, 0x0001cfc8, 256);

// 0x0501CFE0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501CFE0, 0x0016d870, 76997, 0x0001d0c8, 256);

// 0x0501D0E0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501D0E0, 0x0016d870, 76997, 0x0001d1c8, 224);

// 0x0501D1C0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501D1C0, 0x0016d870, 76997, 0x0001d2a8, 256);

// 0x0501D2C0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501D2C0, 0x0016d870, 76997, 0x0001d3a8, 112);

// 0x0501D330
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501D330, 0x0016d870, 76997, 0x0001d418, 224);

// 0x0501D410
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501D410, 0x0016d870, 76997, 0x0001d4f8, 48);

// 0x0501D440 - 0x0501D488
const Gfx yoshi_seg5_dl_0501D440[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, yoshi_seg5_texture_0501C8A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&yoshi_seg5_lights_0501C458.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501C458.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501CAA0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0501D488 - 0x0501D4E0
const Gfx yoshi_seg5_dl_0501D488[] = {
    gsSPLight(&yoshi_seg5_lights_0501C470.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501C470.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501CB00, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  5,  0,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 7, 10,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0501D4E0 - 0x0501D8F8
const Gfx yoshi_seg5_dl_0501D4E0[] = {
    gsSPLight(&yoshi_seg5_lights_0501C488.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501C488.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501CBB0, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  1,  3, 0x0,  2,  1,  4, 0x0),
    gsSPLight(&yoshi_seg5_lights_0501C458.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501C458.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501CC00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 8,  4,  3, 0x0,  3,  7,  9, 0x0),
    gsSP2Triangles(10,  7,  6, 0x0,  7, 10, 11, 0x0),
    gsSP2Triangles( 9,  7, 11, 0x0, 12,  9, 11, 0x0),
    gsSP2Triangles( 4,  8,  0, 0x0,  0,  8, 12, 0x0),
    gsSP2Triangles(13,  4,  0, 0x0,  5,  4, 13, 0x0),
    gsSP2Triangles(12, 14,  0, 0x0,  1,  0, 14, 0x0),
    gsSP1Triangle( 2, 13,  0, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501CCF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 3,  1,  6, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 8,  3,  7, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 10, 11, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle(14, 13, 12, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501CDE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  2,  1,  7, 0x0),
    gsSP2Triangles( 3,  2,  7, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles( 8,  6,  9, 0x0, 10,  6,  8, 0x0),
    gsSP2Triangles(10,  0,  6, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles( 4,  3, 11, 0x0,  5, 12,  9, 0x0),
    gsSP2Triangles( 9, 13,  8, 0x0, 11, 14, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501CEE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 1,  7,  2, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 6,  5, 11, 0x0, 11,  5,  2, 0x0),
    gsSP2Triangles( 2, 12, 11, 0x0, 13, 11, 12, 0x0),
    gsSP1Triangle(14,  8, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501CFE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  1,  6, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 3,  7,  1, 0x0,  8,  9,  3, 0x0),
    gsSP2Triangles( 2,  7, 10, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles(10, 12,  2, 0x0, 13, 12, 14, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 12, 10, 14, 0x0),
    gsSP2Triangles(14, 10,  3, 0x0,  9, 15, 14, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501D0E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  8, 12,  5, 0x0),
    gsSP2Triangles(13,  8,  4, 0x0,  5, 12,  1, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501D1C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 4,  6,  0, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 4,  8,  6, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles(11,  1,  0, 0x0,  0,  6,  9, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0, 12,  7,  3, 0x0),
    gsSP2Triangles( 5,  1, 11, 0x0, 13, 11, 10, 0x0),
    gsSP2Triangles(10, 14, 15, 0x0, 15, 13, 10, 0x0),
    gsSP1Triangle(10,  9, 14, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501D2C0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  3,  5,  6, 0x0),
    gsSPLight(&yoshi_seg5_lights_0501C470.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501C470.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501D330, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles( 4,  7,  5, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 8,  9,  7, 0x0,  6,  5, 11, 0x0),
    gsSP2Triangles(12, 13,  5, 0x0,  5, 13, 11, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501D410, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0501D8F8 - 0x0501D940
const Gfx yoshi_seg5_dl_0501D8F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(yoshi_seg5_dl_0501D440),
    gsSPEndDisplayList(),
};

// 0x0501D940 - 0x0501D970
const Gfx yoshi_seg5_dl_0501D940[] = {
    gsSPDisplayList(yoshi_seg5_dl_0501D488),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(yoshi_seg5_dl_0501D4E0),
    gsSPEndDisplayList(),
};

// 0x0501D970 - 0x0501D998
const Gfx yoshi_seg5_dl_0501D970[] = {
    gsSPDisplayList(yoshi_seg5_dl_0501D8F8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, yoshi_seg5_texture_0501C4A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(yoshi_seg5_dl_0501D940),
};

// 0x0501D998 - 0x0501D9C0
const Gfx yoshi_seg5_dl_0501D998[] = {
    gsSPDisplayList(yoshi_seg5_dl_0501D8F8),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, yoshi_seg5_texture_0501C6A0),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 16 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPBranchList(yoshi_seg5_dl_0501D940),
};

// 0x0501D9C0
static const Lights1 yoshi_seg5_lights_0501D9C0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0501D9D8
static const Lights1 yoshi_seg5_lights_0501D9D8 = gdSPDefLights1(
    0x00, 0x7b, 0x00,
    0x00, 0xf7, 0x00, 0x28, 0x28, 0x28
);

// 0x0501D9F0
static const Lights1 yoshi_seg5_lights_0501D9F0 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 yoshi_lights_unused1 = gdSPDefLights1(
    0x59, 0x59, 0x59,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// Unreferenced light group
UNUSED static const Lights1 yoshi_lights_unused2 = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0501DA38
static const Lights1 yoshi_seg5_lights_0501DA38 = gdSPDefLights1(
    0x45, 0x00, 0x00,
    0x8b, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0501DA50
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501DA50, 0x0016d870, 76997, 0x0001db38, 240);

// 0x0501DB40
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501DB40, 0x0016d870, 76997, 0x0001dc28, 240);

// 0x0501DC30
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501DC30, 0x0016d870, 76997, 0x0001dd18, 224);

// 0x0501DD10
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501DD10, 0x0016d870, 76997, 0x0001ddf8, 256);

// 0x0501DE10
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501DE10, 0x0016d870, 76997, 0x0001def8, 240);

// 0x0501DF00
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501DF00, 0x0016d870, 76997, 0x0001dfe8, 240);

// 0x0501DFF0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501DFF0, 0x0016d870, 76997, 0x0001e0d8, 224);

// 0x0501E0D0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E0D0, 0x0016d870, 76997, 0x0001e1b8, 224);

// 0x0501E1B0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E1B0, 0x0016d870, 76997, 0x0001e298, 48);

// 0x0501E1E0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E1E0, 0x0016d870, 76997, 0x0001e2c8, 224);

// 0x0501E2C0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E2C0, 0x0016d870, 76997, 0x0001e3a8, 256);

// 0x0501E3C0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E3C0, 0x0016d870, 76997, 0x0001e4a8, 240);

// 0x0501E4B0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E4B0, 0x0016d870, 76997, 0x0001e598, 128);

// 0x0501E530
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E530, 0x0016d870, 76997, 0x0001e618, 160);

// 0x0501E5D0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E5D0, 0x0016d870, 76997, 0x0001e6b8, 176);

// 0x0501E680
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E680, 0x0016d870, 76997, 0x0001e768, 224);

// 0x0501E760
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E760, 0x0016d870, 76997, 0x0001e848, 256);

// 0x0501E860
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E860, 0x0016d870, 76997, 0x0001e948, 240);

// 0x0501E950
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E950, 0x0016d870, 76997, 0x0001ea38, 128);

// 0x0501E9D0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501E9D0, 0x0016d870, 76997, 0x0001eab8, 160);

// 0x0501EA70
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501EA70, 0x0016d870, 76997, 0x0001eb58, 176);

// 0x0501EB20
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501EB20, 0x0016d870, 76997, 0x0001ec08, 240);

// 0x0501EC10
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501EC10, 0x0016d870, 76997, 0x0001ecf8, 256);

// 0x0501ED10
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501ED10, 0x0016d870, 76997, 0x0001edf8, 256);

// 0x0501EE10
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501EE10, 0x0016d870, 76997, 0x0001eef8, 256);

// 0x0501EF10
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501EF10, 0x0016d870, 76997, 0x0001eff8, 240);

// 0x0501F000
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F000, 0x0016d870, 76997, 0x0001f0e8, 256);

// 0x0501F100
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F100, 0x0016d870, 76997, 0x0001f1e8, 128);

// 0x0501F180
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F180, 0x0016d870, 76997, 0x0001f268, 256);

// 0x0501F280
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F280, 0x0016d870, 76997, 0x0001f368, 256);

// 0x0501F380
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F380, 0x0016d870, 76997, 0x0001f468, 256);

// 0x0501F480
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F480, 0x0016d870, 76997, 0x0001f568, 192);

// 0x0501F540
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F540, 0x0016d870, 76997, 0x0001f628, 256);

// 0x0501F640
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F640, 0x0016d870, 76997, 0x0001f728, 240);

// 0x0501F730
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F730, 0x0016d870, 76997, 0x0001f818, 240);

// 0x0501F820
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F820, 0x0016d870, 76997, 0x0001f908, 240);

// 0x0501F910
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501F910, 0x0016d870, 76997, 0x0001f9f8, 240);

// 0x0501FA00
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501FA00, 0x0016d870, 76997, 0x0001fae8, 240);

// 0x0501FAF0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501FAF0, 0x0016d870, 76997, 0x0001fbd8, 176);

// 0x0501FBA0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501FBA0, 0x0016d870, 76997, 0x0001fc88, 240);

// 0x0501FC90
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501FC90, 0x0016d870, 76997, 0x0001fd78, 256);

// 0x0501FD90
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501FD90, 0x0016d870, 76997, 0x0001fe78, 256);

// 0x0501FE90
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501FE90, 0x0016d870, 76997, 0x0001ff78, 256);

// 0x0501FF90
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_0501FF90, 0x0016d870, 76997, 0x00020078, 240);

// 0x05020080
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020080, 0x0016d870, 76997, 0x00020168, 256);

// 0x05020180
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020180, 0x0016d870, 76997, 0x00020268, 128);

// 0x05020200
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020200, 0x0016d870, 76997, 0x000202e8, 256);

// 0x05020300
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020300, 0x0016d870, 76997, 0x000203e8, 256);

// 0x05020400
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020400, 0x0016d870, 76997, 0x000204e8, 256);

// 0x05020500
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020500, 0x0016d870, 76997, 0x000205e8, 192);

// 0x050205C0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_050205C0, 0x0016d870, 76997, 0x000206a8, 256);

// 0x050206C0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_050206C0, 0x0016d870, 76997, 0x000207a8, 240);

// 0x050207B0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_050207B0, 0x0016d870, 76997, 0x00020898, 240);

// 0x050208A0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_050208A0, 0x0016d870, 76997, 0x00020988, 240);

// 0x05020990
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020990, 0x0016d870, 76997, 0x00020a78, 240);

// 0x05020A80
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020A80, 0x0016d870, 76997, 0x00020b68, 256);

// 0x05020B80
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020B80, 0x0016d870, 76997, 0x00020c68, 256);

// 0x05020C80
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020C80, 0x0016d870, 76997, 0x00020d68, 224);

// 0x05020D60
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020D60, 0x0016d870, 76997, 0x00020e48, 256);

// 0x05020E60
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020E60, 0x0016d870, 76997, 0x00020f48, 48);

// 0x05020E90
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020E90, 0x0016d870, 76997, 0x00020f78, 256);

// 0x05020F90
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05020F90, 0x0016d870, 76997, 0x00021078, 128);

// 0x05021010
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05021010, 0x0016d870, 76997, 0x000210f8, 256);

// 0x05021110
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_05021110, 0x0016d870, 76997, 0x000211f8, 192);

// 0x050211D0
ROM_ASSET_LOAD_VTX(yoshi_seg5_vertex_050211D0, 0x0016d870, 76997, 0x000212b8, 224);

// 0x050212B0 - 0x05021490
const Gfx yoshi_seg5_dl_050212B0[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9C0.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9C0.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501DA50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501DB40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501DC30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 2, 12, 13, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501DD10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 8, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501DE10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 13,  0, 14, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501DF00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9,  5, 0x0),
    gsSP2Triangles(10,  3,  2, 0x0,  1, 11,  2, 0x0),
    gsSP2Triangles(12, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 9,  8, 13, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501DFF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 10, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E0D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E1B0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021490 - 0x050215D8
const Gfx yoshi_seg5_dl_05021490[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501E1E0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle( 6, 12, 13, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E2C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  3,  2, 11, 0x0),
    gsSP2Triangles( 3, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(12, 14, 11, 0x0,  2,  1, 15, 0x0),
    gsSP1Triangle( 2, 15, 12, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E3C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  0, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 5, 10,  7, 0x0, 11,  7, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  7,  6,  5, 0x0),
    gsSP1Triangle( 0,  3,  4, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E4B0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  5,  3,  0, 0x0),
    gsSP1Triangle( 7,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x050215D8 - 0x05021678
const Gfx yoshi_seg5_dl_050215D8[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501E530, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  2,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  2,  9,  0, 0x0),
    gsSP2Triangles( 9,  7,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  7,  8,  4, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 4,  3,  9, 0x0,  9,  3,  0, 0x0),
    gsSP2Triangles( 7,  9,  2, 0x0,  1,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021678 - 0x05021718
const Gfx yoshi_seg5_dl_05021678[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501E5D0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  4,  8,  1, 0x0),
    gsSP2Triangles( 2,  9, 10, 0x0,  4,  0,  7, 0x0),
    gsSP2Triangles( 1,  8,  2, 0x0,  2,  8,  3, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  5,  6,  9, 0x0),
    gsSP2Triangles( 9,  6, 10, 0x0, 10,  6,  0, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  2,  3,  9, 0x0),
    gsSP2Triangles( 5,  9,  3, 0x0,  2, 10,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021718 - 0x05021860
const Gfx yoshi_seg5_dl_05021718[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501E680, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13,  5, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E760, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11,  1, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 14, 15,  2, 0x0),
    gsSP1Triangle(14,  2,  1, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E860, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8, 10,  5, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  5,  4,  8, 0x0),
    gsSP1Triangle( 6,  0,  3, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501E950, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP1Triangle( 6,  5,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021860 - 0x05021900
const Gfx yoshi_seg5_dl_05021860[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501E9D0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  6,  7,  0, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  2,  9,  0, 0x0),
    gsSP2Triangles( 5,  6,  9, 0x0,  7,  4,  0, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 9,  3,  5, 0x0,  2,  3,  9, 0x0),
    gsSP2Triangles( 0,  9,  6, 0x0,  5,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021900 - 0x050219A0
const Gfx yoshi_seg5_dl_05021900[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501EA70, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  1,  8,  4, 0x0),
    gsSP2Triangles( 9, 10,  0, 0x0,  6,  2,  4, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0,  5,  8,  0, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0, 10,  7,  3, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0,  2,  7,  9, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0, 10,  5,  0, 0x0),
    gsSP2Triangles( 5, 10,  3, 0x0,  2,  9,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x050219A0 - 0x05021B90
const Gfx yoshi_seg5_dl_050219A0[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9F0.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9F0.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501EB20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(10, 14,  8, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501EC10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8, 13, 14, 0x0),
    gsSP1Triangle(15, 10, 12, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501ED10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0, 11, 10,  5, 0x0),
    gsSP2Triangles( 5, 12, 11, 0x0, 13, 14,  6, 0x0),
    gsSP1Triangle(14, 15,  6, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501EE10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  2,  8,  0, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  4,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501EF10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2,  7,  0, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(10,  3,  5, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F000, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  7, 13,  8, 0x0),
    gsSP2Triangles( 5, 14,  3, 0x0,  2, 15,  0, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F100, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021B90 - 0x05021CD8
const Gfx yoshi_seg5_dl_05021B90[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501F180, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  4, 0x0),
    gsSP2Triangles( 7,  3, 13, 0x0, 14,  5,  4, 0x0),
    gsSP2Triangles( 9,  5, 14, 0x0, 13,  3, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F280, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2, 12, 13, 0x0, 14, 12, 11, 0x0),
    gsSP1Triangle(15,  3,  5, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F380, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  7, 12,  0, 0x0),
    gsSP2Triangles( 0, 15,  7, 0x0, 14,  1, 12, 0x0),
    gsSP2Triangles( 9, 13, 10, 0x0,  6, 10,  7, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F480, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  4,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0, 10,  8,  7, 0x0),
    gsSP1Triangle( 1,  9, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021CD8 - 0x05021E38
const Gfx yoshi_seg5_dl_05021CD8[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501F540, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  3, 15,  4, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F640, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  2,  1,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F730, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles( 8, 14, 10, 0x0,  6,  3,  5, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F820, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  5, 0x0,  2, 11,  3, 0x0),
    gsSP2Triangles(12,  7, 13, 0x0,  8, 14,  6, 0x0),
    gsSP1Triangle(11,  1, 13, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501F910, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  4,  3,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  2, 0x0),
    gsSP1Triangle(13, 14,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021E38 - 0x05021F70
const Gfx yoshi_seg5_dl_05021E38[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501FA00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 2,  9,  3, 0x0,  8, 10,  2, 0x0),
    gsSP2Triangles( 8,  2, 11, 0x0,  3, 12,  4, 0x0),
    gsSP2Triangles( 2, 10,  9, 0x0,  7, 13, 10, 0x0),
    gsSP2Triangles( 5, 14,  0, 0x0,  0, 14,  1, 0x0),
    gsSP2Triangles( 1, 14, 11, 0x0, 11, 14,  6, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0,  3,  9, 12, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0,  8, 11,  6, 0x0),
    gsSP1Triangle( 5,  0,  3, 0x0),
    gsSPLight(&yoshi_seg5_lights_0501D9C0.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9C0.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501FAF0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 1,  9,  2, 0x0,  3,  4,  8, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  8,  6, 10, 0x0),
    gsSP2Triangles( 9,  5,  7, 0x0,  8, 10,  3, 0x0),
    gsSP2Triangles( 7,  2,  9, 0x0,  7,  4,  2, 0x0),
    gsSP1Triangle( 7,  8,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x05021F70 - 0x05022160
const Gfx yoshi_seg5_dl_05021F70[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9F0.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9F0.a, 2),
    gsSPVertex(yoshi_seg5_vertex_0501FBA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(10, 14,  8, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501FC90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14,  6, 0x0),
    gsSP1Triangle(10, 12, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501FD90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  0,  2, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0,  3, 10, 11, 0x0),
    gsSP2Triangles(11, 12,  3, 0x0,  8, 13, 14, 0x0),
    gsSP1Triangle( 8, 15, 13, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501FE90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  2,  8,  0, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  7,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_0501FF90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 2,  7,  0, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 3,  5, 10, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020080, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0,  6, 13,  7, 0x0),
    gsSP2Triangles( 5, 14,  3, 0x0,  2, 15,  0, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020180, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 6,  5,  2, 0x0,  7,  6,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05022160 - 0x050222A8
const Gfx yoshi_seg5_dl_05022160[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_05020200, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  4, 11, 12, 0x0),
    gsSP2Triangles(13,  5,  7, 0x0,  4,  3, 14, 0x0),
    gsSP2Triangles(14,  3,  9, 0x0, 15,  5, 13, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020300, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  0, 0x0,  9, 13, 14, 0x0),
    gsSP1Triangle( 3,  5, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020400, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  2, 14,  7, 0x0),
    gsSP2Triangles( 7, 15,  2, 0x0, 14,  1, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0,  7, 10,  8, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020500, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  2, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 2,  1,  9, 0x0,  8,  7, 10, 0x0),
    gsSP1Triangle(11,  9,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x050222A8 - 0x05022408
const Gfx yoshi_seg5_dl_050222A8[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_050205C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  4, 15,  5, 0x0),
    gsSPVertex(yoshi_seg5_vertex_050206C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  1,  0, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(yoshi_seg5_vertex_050207B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  7,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13,  0,  2, 0x0),
    gsSP2Triangles(12, 14,  6, 0x0,  3,  5,  8, 0x0),
    gsSPVertex(yoshi_seg5_vertex_050208A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  5, 0x0,  4, 11,  0, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0,  5, 14,  8, 0x0),
    gsSP1Triangle(12,  1, 11, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020990, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  1,  0, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  0, 11, 12, 0x0),
    gsSP1Triangle( 4, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x05022408 - 0x05022608
const Gfx yoshi_seg5_dl_05022408[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_05020A80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  4, 13, 0x0, 14,  5, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020B80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  7, 10,  8, 0x0),
    gsSP2Triangles(12, 13,  6, 0x0,  1, 14, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020C80, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0,  2, 13,  0, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020D60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  1, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0, 12, 13,  1, 0x0),
    gsSP1Triangle( 4, 14, 15, 0x0),
    gsSPVertex(yoshi_seg5_vertex_05020E60, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&yoshi_seg5_lights_0501D9C0.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9C0.a, 2),
    gsSPVertex(yoshi_seg5_vertex_05020E90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  5,  9,  3, 0x0),
    gsSP2Triangles( 7,  6,  4, 0x0,  1,  9,  2, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8,  1,  6, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles(12, 11, 14, 0x0, 13, 15, 14, 0x0),
    gsSP2Triangles(14, 15,  8, 0x0,  3, 10, 12, 0x0),
    gsSP2Triangles(12,  4,  3, 0x0, 12, 14,  7, 0x0),
    gsSP2Triangles( 8,  7, 14, 0x0,  7,  4, 12, 0x0),
    gsSPLight(&yoshi_seg5_lights_0501D9F0.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9F0.a, 2),
    gsSPVertex(yoshi_seg5_vertex_05020F90, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  6,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x05022608 - 0x050227D8
const Gfx yoshi_seg5_dl_05022608[] = {
    gsSPLight(&yoshi_seg5_lights_0501D9D8.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9D8.a, 2),
    gsSPVertex(yoshi_seg5_vertex_05021010, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  4, 13, 0x0,  3,  5, 14, 0x0),
    gsSP2Triangles( 8,  1,  6, 0x0, 10,  0, 11, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0,  8, 15,  1, 0x0),
    gsSP2Triangles(14,  7,  3, 0x0, 13,  9, 12, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0,  7, 14,  8, 0x0),
    gsSP2Triangles( 3, 13,  4, 0x0,  1, 15,  2, 0x0),
    gsSPLight(&yoshi_seg5_lights_0501DA38.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501DA38.a, 2),
    gsSPVertex(yoshi_seg5_vertex_05021110, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  9,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  6, 0x0,  2,  9, 10, 0x0),
    gsSP2Triangles( 5, 11,  3, 0x0,  2, 10,  0, 0x0),
    gsSP2Triangles(11,  8,  3, 0x0,  1,  4,  3, 0x0),
    gsSPLight(&yoshi_seg5_lights_0501D9C0.l, 1),
    gsSPLight(&yoshi_seg5_lights_0501D9C0.a, 2),
    gsSPVertex(yoshi_seg5_vertex_050211D0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  6, 0x0),
    gsSP2Triangles(10,  3,  5, 0x0,  5,  6, 11, 0x0),
    gsSP2Triangles( 5,  2, 12, 0x0,  2,  1, 12, 0x0),
    gsSP2Triangles( 2, 11, 13, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles(12, 10,  5, 0x0,  8, 13, 11, 0x0),
    gsSP2Triangles(11,  2,  5, 0x0,  6,  8, 11, 0x0),
    gsSP2Triangles( 9,  5,  4, 0x0,  3, 10,  1, 0x0),
    gsSP2Triangles(10, 12,  1, 0x0,  0,  2, 13, 0x0),
    gsSPEndDisplayList(),
};
