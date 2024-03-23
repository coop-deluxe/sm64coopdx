#include "pc/rom_assets.h"
// 0x0700B4A8 - 0x0700B598
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700B4A8, 0x004af930, 34262, 0x0000b4a8, 240);

// 0x0700B598 - 0x0700B688
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700B598, 0x004af930, 34262, 0x0000b598, 240);

// 0x0700B688 - 0x0700B778
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700B688, 0x004af930, 34262, 0x0000b688, 240);

// 0x0700B778 - 0x0700B868
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700B778, 0x004af930, 34262, 0x0000b778, 240);

// 0x0700B868 - 0x0700B958
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700B868, 0x004af930, 34262, 0x0000b868, 240);

// 0x0700B958 - 0x0700BA48
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700B958, 0x004af930, 34262, 0x0000b958, 240);

// 0x0700BA48 - 0x0700BB38
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700BA48, 0x004af930, 34262, 0x0000ba48, 240);

// 0x0700BB38 - 0x0700BC28
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700BB38, 0x004af930, 34262, 0x0000bb38, 240);

// 0x0700BC28 - 0x0700BD18
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700BC28, 0x004af930, 34262, 0x0000bc28, 240);

// 0x0700BD18 - 0x0700BDF8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700BD18, 0x004af930, 34262, 0x0000bd18, 224);

// 0x0700BDF8 - 0x0700BEE8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700BDF8, 0x004af930, 34262, 0x0000bdf8, 240);

// 0x0700BEE8 - 0x0700BFD8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700BEE8, 0x004af930, 34262, 0x0000bee8, 240);

// 0x0700BFD8 - 0x0700C0C8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700BFD8, 0x004af930, 34262, 0x0000bfd8, 240);

// 0x0700C0C8 - 0x0700C1B8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C0C8, 0x004af930, 34262, 0x0000c0c8, 240);

// 0x0700C1B8 - 0x0700C2A8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C1B8, 0x004af930, 34262, 0x0000c1b8, 240);

// 0x0700C2A8 - 0x0700C398
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C2A8, 0x004af930, 34262, 0x0000c2a8, 240);

// 0x0700C398 - 0x0700C488
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C398, 0x004af930, 34262, 0x0000c398, 240);

// 0x0700C488 - 0x0700C578
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C488, 0x004af930, 34262, 0x0000c488, 240);

// 0x0700C578 - 0x0700C668
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C578, 0x004af930, 34262, 0x0000c578, 240);

// 0x0700C668 - 0x0700C758
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C668, 0x004af930, 34262, 0x0000c668, 240);

// 0x0700C758 - 0x0700C848
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C758, 0x004af930, 34262, 0x0000c758, 240);

// 0x0700C848 - 0x0700C928
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C848, 0x004af930, 34262, 0x0000c848, 224);

// 0x0700C928 - 0x0700CA18
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700C928, 0x004af930, 34262, 0x0000c928, 240);

// 0x0700CA18 - 0x0700CB08
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700CA18, 0x004af930, 34262, 0x0000ca18, 240);

// 0x0700CB08 - 0x0700CBF8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700CB08, 0x004af930, 34262, 0x0000cb08, 240);

// 0x0700CBF8 - 0x0700CCA8
ROM_ASSET_LOAD_VTX(pss_seg7_vertex_0700CBF8, 0x004af930, 34262, 0x0000cbf8, 176);

// 0x0700CCA8 - 0x0700D338
static const Gfx pss_seg7_dl_0700CCA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(pss_seg7_vertex_0700B4A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700B598, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700B688, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700B778, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700B868, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700B958, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700BA48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700BB38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700BC28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700BD18, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle( 0,  2, 13, 0x0),
    gsSPVertex(pss_seg7_vertex_0700BDF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700BEE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700BFD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C0C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C1B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C2A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C398, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C488, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C578, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C668, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C758, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C848, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  3,  1, 0x0),
    gsSPVertex(pss_seg7_vertex_0700C928, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700CA18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(pss_seg7_vertex_0700CB08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(pss_seg7_vertex_0700CBF8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D338 - 0x0700D3A8
const Gfx pss_seg7_dl_0700D338[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(pss_seg7_dl_0700CCA8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
