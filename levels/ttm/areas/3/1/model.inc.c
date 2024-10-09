#include "pc/rom_assets.h"
// 0x0701DC60 - 0x0701DC78
static const Lights1 ttm_seg7_lights_0701DC60 = gdSPDefLights1(
    0x08, 0x08, 0x08,
    0x22, 0x22, 0x22, 0x28, 0x28, 0x28
);

// 0x0701DC78 - 0x0701DC90
static const Lights1 ttm_seg7_lights_0701DC78 = gdSPDefLights1(
    0x0c, 0x0c, 0x0c,
    0x33, 0x33, 0x33, 0x28, 0x28, 0x28
);

// 0x0701DC90 - 0x0701DCA8
static const Lights1 ttm_seg7_lights_0701DC90 = gdSPDefLights1(
    0x11, 0x11, 0x11,
    0x44, 0x44, 0x44, 0x28, 0x28, 0x28
);

// 0x0701DCA8 - 0x0701DCC0
static const Lights1 ttm_seg7_lights_0701DCA8 = gdSPDefLights1(
    0x15, 0x15, 0x15,
    0x55, 0x55, 0x55, 0x28, 0x28, 0x28
);

// 0x0701DCC0 - 0x0701DCD8
static const Lights1 ttm_seg7_lights_0701DCC0 = gdSPDefLights1(
    0x19, 0x19, 0x19,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x0701DCD8 - 0x0701DCF0
static const Lights1 ttm_seg7_lights_0701DCD8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701DCF0 - 0x0701DD08
static const Lights1 ttm_seg7_lights_0701DCF0 = gdSPDefLights1(
    0x1d, 0x1d, 0x1d,
    0x77, 0x77, 0x77, 0x28, 0x28, 0x28
);

// 0x0701DD08 - 0x0701DD20
static const Lights1 ttm_seg7_lights_0701DD08 = gdSPDefLights1(
    0x22, 0x22, 0x22,
    0x88, 0x88, 0x88, 0x28, 0x28, 0x28
);

// 0x0701DD20 - 0x0701DD38
static const Lights1 ttm_seg7_lights_0701DD20 = gdSPDefLights1(
    0x26, 0x26, 0x26,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0701DD38 - 0x0701DD50
static const Lights1 ttm_seg7_lights_0701DD38 = gdSPDefLights1(
    0x2a, 0x2a, 0x2a,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x0701DD50 - 0x0701DD68
static const Lights1 ttm_seg7_lights_0701DD50 = gdSPDefLights1(
    0x2e, 0x2e, 0x2e,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0701DD68 - 0x0701DD80
static const Lights1 ttm_seg7_lights_0701DD68 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0xcc, 0xcc, 0xcc, 0x28, 0x28, 0x28
);

// 0x0701DD80 - 0x0701DD98
static const Lights1 ttm_seg7_lights_0701DD80 = gdSPDefLights1(
    0x37, 0x37, 0x37,
    0xdd, 0xdd, 0xdd, 0x28, 0x28, 0x28
);

// 0x0701DD98 - 0x0701DDB0
static const Lights1 ttm_seg7_lights_0701DD98 = gdSPDefLights1(
    0x3b, 0x3b, 0x3b,
    0xee, 0xee, 0xee, 0x28, 0x28, 0x28
);

// 0x0701DDB0 - 0x0701DDC8
static const Lights1 ttm_seg7_lights_0701DDB0 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0701DDC8 - 0x0701DE08
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701DDC8, 0x004d1910, 104662, 0x0001ddc8, 64);

// 0x0701DE08 - 0x0701DE88
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701DE08, 0x004d1910, 104662, 0x0001de08, 128);

// 0x0701DE88 - 0x0701DF08
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701DE88, 0x004d1910, 104662, 0x0001de88, 128);

// 0x0701DF08 - 0x0701DF88
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701DF08, 0x004d1910, 104662, 0x0001df08, 128);

// 0x0701DF88 - 0x0701E008
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701DF88, 0x004d1910, 104662, 0x0001df88, 128);

// 0x0701E008 - 0x0701E0F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E008, 0x004d1910, 104662, 0x0001e008, 240);

// 0x0701E0F8 - 0x0701E1E8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E0F8, 0x004d1910, 104662, 0x0001e0f8, 240);

// 0x0701E1E8 - 0x0701E2E8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E1E8, 0x004d1910, 104662, 0x0001e1e8, 256);

// 0x0701E2E8 - 0x0701E3E8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E2E8, 0x004d1910, 104662, 0x0001e2e8, 256);

// 0x0701E3E8 - 0x0701E4E8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E3E8, 0x004d1910, 104662, 0x0001e3e8, 256);

// 0x0701E4E8 - 0x0701E5E8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E4E8, 0x004d1910, 104662, 0x0001e4e8, 256);

// 0x0701E5E8 - 0x0701E668
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E5E8, 0x004d1910, 104662, 0x0001e5e8, 128);

// 0x0701E668 - 0x0701E728
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E668, 0x004d1910, 104662, 0x0001e668, 192);

// 0x0701E728 - 0x0701E828
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E728, 0x004d1910, 104662, 0x0001e728, 256);

// 0x0701E828 - 0x0701E918
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E828, 0x004d1910, 104662, 0x0001e828, 240);

// 0x0701E918 - 0x0701EA08
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701E918, 0x004d1910, 104662, 0x0001e918, 240);

// 0x0701EA08 - 0x0701EA48
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EA08, 0x004d1910, 104662, 0x0001ea08, 64);

// 0x0701EA48 - 0x0701EB28
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EA48, 0x004d1910, 104662, 0x0001ea48, 224);

// 0x0701EB28 - 0x0701EB98
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EB28, 0x004d1910, 104662, 0x0001eb28, 112);

// 0x0701EB98 - 0x0701EC38
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EB98, 0x004d1910, 104662, 0x0001eb98, 160);

// 0x0701EC38 - 0x0701ED28
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EC38, 0x004d1910, 104662, 0x0001ec38, 240);

// 0x0701ED28 - 0x0701EE18
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701ED28, 0x004d1910, 104662, 0x0001ed28, 240);

// 0x0701EE18 - 0x0701EE98
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EE18, 0x004d1910, 104662, 0x0001ee18, 128);

// 0x0701EE98 - 0x0701EF88
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EE98, 0x004d1910, 104662, 0x0001ee98, 240);

// 0x0701EF88 - 0x0701F088
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701EF88, 0x004d1910, 104662, 0x0001ef88, 256);

// 0x0701F088 - 0x0701F0F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F088, 0x004d1910, 104662, 0x0001f088, 112);

// 0x0701F0F8 - 0x0701F1E8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F0F8, 0x004d1910, 104662, 0x0001f0f8, 240);

// 0x0701F1E8 - 0x0701F2D8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F1E8, 0x004d1910, 104662, 0x0001f1e8, 240);

// 0x0701F2D8 - 0x0701F3C8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F2D8, 0x004d1910, 104662, 0x0001f2d8, 240);

// 0x0701F3C8 - 0x0701F4B8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F3C8, 0x004d1910, 104662, 0x0001f3c8, 240);

// 0x0701F4B8 - 0x0701F5A8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F4B8, 0x004d1910, 104662, 0x0001f4b8, 240);

// 0x0701F5A8 - 0x0701F6A8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F5A8, 0x004d1910, 104662, 0x0001f5a8, 256);

// 0x0701F6A8 - 0x0701F798
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F6A8, 0x004d1910, 104662, 0x0001f6a8, 240);

// 0x0701F798 - 0x0701F898
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F798, 0x004d1910, 104662, 0x0001f798, 256);

// 0x0701F898 - 0x0701F978
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F898, 0x004d1910, 104662, 0x0001f898, 224);

// 0x0701F978 - 0x0701FA58
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701F978, 0x004d1910, 104662, 0x0001f978, 224);

// 0x0701FA58 - 0x0701FB48
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701FA58, 0x004d1910, 104662, 0x0001fa58, 240);

// 0x0701FB48 - 0x0701FC38
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701FB48, 0x004d1910, 104662, 0x0001fb48, 240);

// 0x0701FC38 - 0x0701FCE8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701FC38, 0x004d1910, 104662, 0x0001fc38, 176);

// 0x0701FCE8 - 0x0701FDD8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701FCE8, 0x004d1910, 104662, 0x0001fce8, 240);

// 0x0701FDD8 - 0x0701FED8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701FDD8, 0x004d1910, 104662, 0x0001fdd8, 256);

// 0x0701FED8 - 0x0701FFC8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701FED8, 0x004d1910, 104662, 0x0001fed8, 240);

// 0x0701FFC8 - 0x070200C8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701FFC8, 0x004d1910, 104662, 0x0001ffc8, 256);

// 0x070200C8 - 0x070201A8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070200C8, 0x004d1910, 104662, 0x000200c8, 224);

// 0x070201A8 - 0x07020298
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070201A8, 0x004d1910, 104662, 0x000201a8, 240);

// 0x07020298 - 0x07020388
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020298, 0x004d1910, 104662, 0x00020298, 240);

// 0x07020388 - 0x07020478
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020388, 0x004d1910, 104662, 0x00020388, 240);

// 0x07020478 - 0x07020568
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020478, 0x004d1910, 104662, 0x00020478, 240);

// 0x07020568 - 0x07020648
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020568, 0x004d1910, 104662, 0x00020568, 224);

// 0x07020648 - 0x07020738
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020648, 0x004d1910, 104662, 0x00020648, 240);

// 0x07020738 - 0x07020828
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020738, 0x004d1910, 104662, 0x00020738, 240);

// 0x07020828 - 0x07020908
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020828, 0x004d1910, 104662, 0x00020828, 224);

// 0x07020908 - 0x07020A08
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020908, 0x004d1910, 104662, 0x00020908, 256);

// 0x07020A08 - 0x07020AF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020A08, 0x004d1910, 104662, 0x00020a08, 240);

// 0x07020AF8 - 0x07020BF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020AF8, 0x004d1910, 104662, 0x00020af8, 256);

// 0x07020BF8 - 0x07020CD8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020BF8, 0x004d1910, 104662, 0x00020bf8, 224);

// 0x07020CD8 - 0x07020DC8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020CD8, 0x004d1910, 104662, 0x00020cd8, 240);

// 0x07020DC8 - 0x07020EB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020DC8, 0x004d1910, 104662, 0x00020dc8, 240);

// 0x07020EB8 - 0x07020FA8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020EB8, 0x004d1910, 104662, 0x00020eb8, 240);

// 0x07020FA8 - 0x07021088
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07020FA8, 0x004d1910, 104662, 0x00020fa8, 224);

// 0x07021088 - 0x07021178
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021088, 0x004d1910, 104662, 0x00021088, 240);

// 0x07021178 - 0x07021268
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021178, 0x004d1910, 104662, 0x00021178, 240);

// 0x07021268 - 0x07021358
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021268, 0x004d1910, 104662, 0x00021268, 240);

// 0x07021358 - 0x07021448
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021358, 0x004d1910, 104662, 0x00021358, 240);

// 0x07021448 - 0x07021528
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021448, 0x004d1910, 104662, 0x00021448, 224);

// 0x07021528 - 0x07021618
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021528, 0x004d1910, 104662, 0x00021528, 240);

// 0x07021618 - 0x070216F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021618, 0x004d1910, 104662, 0x00021618, 224);

// 0x070216F8 - 0x070217F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070216F8, 0x004d1910, 104662, 0x000216f8, 256);

// 0x070217F8 - 0x07021898
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070217F8, 0x004d1910, 104662, 0x000217f8, 160);

// 0x07021898 - 0x07021988
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021898, 0x004d1910, 104662, 0x00021898, 240);

// 0x07021988 - 0x070219C8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021988, 0x004d1910, 104662, 0x00021988, 64);

// 0x070219C8 - 0x07021AB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070219C8, 0x004d1910, 104662, 0x000219c8, 240);

// 0x07021AB8 - 0x07021B78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021AB8, 0x004d1910, 104662, 0x00021ab8, 192);

// 0x07021B78 - 0x07021BF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021B78, 0x004d1910, 104662, 0x00021b78, 128);

// 0x07021BF8 - 0x07021C78
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021BF8, 0x004d1910, 104662, 0x00021bf8, 128);

// 0x07021C78 - 0x07021CF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021C78, 0x004d1910, 104662, 0x00021c78, 128);

// 0x07021CF8 - 0x07021DF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021CF8, 0x004d1910, 104662, 0x00021cf8, 256);

// 0x07021DF8 - 0x07021ED8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021DF8, 0x004d1910, 104662, 0x00021df8, 224);

// 0x07021ED8 - 0x07021FC8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021ED8, 0x004d1910, 104662, 0x00021ed8, 240);

// 0x07021FC8 - 0x07022098
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07021FC8, 0x004d1910, 104662, 0x00021fc8, 208);

// 0x07022098 - 0x07022198
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022098, 0x004d1910, 104662, 0x00022098, 256);

// 0x07022198 - 0x07022298
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022198, 0x004d1910, 104662, 0x00022198, 256);

// 0x07022298 - 0x07022398
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022298, 0x004d1910, 104662, 0x00022298, 256);

// 0x07022398 - 0x07022488
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022398, 0x004d1910, 104662, 0x00022398, 240);

// 0x07022488 - 0x07022578
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022488, 0x004d1910, 104662, 0x00022488, 240);

// 0x07022578 - 0x07022678
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022578, 0x004d1910, 104662, 0x00022578, 256);

// 0x07022678 - 0x070226F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022678, 0x004d1910, 104662, 0x00022678, 128);

// 0x070226F8 - 0x070227F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070226F8, 0x004d1910, 104662, 0x000226f8, 256);

// 0x070227F8 - 0x070228F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070227F8, 0x004d1910, 104662, 0x000227f8, 256);

// 0x070228F8 - 0x070229F8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070228F8, 0x004d1910, 104662, 0x000228f8, 256);

// 0x070229F8 - 0x07022AF8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070229F8, 0x004d1910, 104662, 0x000229f8, 256);

// 0x07022AF8 - 0x07022BD8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022AF8, 0x004d1910, 104662, 0x00022af8, 224);

// 0x07022BD8 - 0x07022CB8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022BD8, 0x004d1910, 104662, 0x00022bd8, 224);

// 0x07022CB8 - 0x07022DA8
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022CB8, 0x004d1910, 104662, 0x00022cb8, 240);

// 0x07022DA8 - 0x07022E98
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022DA8, 0x004d1910, 104662, 0x00022da8, 240);

// 0x07022E98 - 0x07022F08
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07022E98, 0x004d1910, 104662, 0x00022e98, 112);

// 0x07022F08 - 0x07023108
static const Gfx ttm_seg7_dl_07022F08[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0701DC60.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DC60.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701DDC8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DC78.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DC78.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701DE08, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DC90.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DC90.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701DE88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCA8.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCA8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701DF08, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCC0.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCC0.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701DF88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCD8.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCD8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701E008, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701E0F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701E1E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07023108 - 0x070240F0
static const Gfx ttm_seg7_dl_07023108[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_0900B800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0701DCA8.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCA8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701E2E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0,  2,  1, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701E3E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701E4E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701E5E8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  7,  3,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCC0.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCC0.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701E668, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCF0.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCF0.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701E728, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701E828, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701E918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701EA08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD08.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD08.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701EA48, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701EB28, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 1,  6,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD20.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD20.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701EB98, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD38.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD38.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701EC38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(10, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701ED28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0,  1, 13,  2, 0x0),
    gsSP1Triangle(13, 14,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701EE18, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD50.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD50.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701EE98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 10, 13, 14, 0x0),
    gsSP1Triangle(10, 14, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701EF88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13,  0, 14, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F088, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 5,  4,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD68.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD68.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701F0F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 13, 0x0,  9, 11, 13, 0x0),
    gsSP1Triangle(10, 14, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F1E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 12, 13,  9, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F2D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  1, 13,  2, 0x0),
    gsSP1Triangle( 1, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F3C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles( 6,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F4B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F5A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F6A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F798, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F898, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8, 13,  9, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701F978, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701FA58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701FB48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701FC38, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle(10,  4,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD80.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD80.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701FCE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(10, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701FDD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701FED8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701FFC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_070200C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070201A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 2,  1, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020298, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020388, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020478, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020568, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020648, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020738, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020828, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCD8.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCD8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07020908, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 10, 13, 14, 0x0),
    gsSP2Triangles(10, 14, 11, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 10,  8,  7, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020AF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  6,  8,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10,  7, 0x0),
    gsSP2Triangles( 1, 11,  2, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(15, 12, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020BF8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12,  5, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020CD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  5,  3,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020DC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020EB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07020FA8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10,  1, 11, 0x0),
    gsSP1Triangle( 0,  2, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021088, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021178, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021268, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021358, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021448, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  1,  0, 11, 0x0),
    gsSP2Triangles( 1, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021528, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(10,  9, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021618, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070216F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12,  8, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_070217F8, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  7,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x070240F0 - 0x07024178
static const Gfx ttm_seg7_dl_070240F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_07021898, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  4,  0, 0x0,  4,  5,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021988, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07024178 - 0x07024708
static const Gfx ttm_seg7_dl_07024178[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_0701DC90.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DC90.a, 2),
    gsSPVertex(ttm_seg7_vertex_070219C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021AB8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  8,  3,  5, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 10,  0,  2, 0x0),
    gsSP1Triangle(10,  2, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCA8.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCA8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07021B78, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCC0.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCC0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07021BF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCF0.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCF0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07021C78, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD08.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD08.a, 2),
    gsSPVertex(ttm_seg7_vertex_07021CF8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 15,  1,  0, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021DF8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021ED8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  7,  9,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07021FC8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10,  0,  2, 0x0, 10,  2, 11, 0x0),
    gsSP1Triangle(12, 10, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD20.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD20.a, 2),
    gsSPVertex(ttm_seg7_vertex_07022098, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  1, 15,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD38.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD38.a, 2),
    gsSPVertex(ttm_seg7_vertex_07022198, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  1, 15,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD50.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD50.a, 2),
    gsSPVertex(ttm_seg7_vertex_07022298, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD68.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD68.a, 2),
    gsSPVertex(ttm_seg7_vertex_07022398, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07022488, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07022578, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 1,  9, 11, 0x0,  9, 12, 10, 0x0),
    gsSP2Triangles( 1, 11,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07022678, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD80.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD80.a, 2),
    gsSPVertex(ttm_seg7_vertex_070226F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DD98.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DD98.a, 2),
    gsSPVertex(ttm_seg7_vertex_070227F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPLight(&ttm_seg7_lights_0701DCD8.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DCD8.a, 2),
    gsSPVertex(ttm_seg7_vertex_070228F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07024708 - 0x070247F0
static const Gfx ttm_seg7_dl_07024708[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_070229F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 5,  8,  3, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  3,  8, 0x0,  1,  7,  3, 0x0),
    gsSP2Triangles( 9,  4,  0, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles( 0,  4,  6, 0x0,  5, 10,  8, 0x0),
    gsSP2Triangles(11, 12,  5, 0x0, 11,  5,  9, 0x0),
    gsSP2Triangles( 5, 12, 10, 0x0,  0, 13,  1, 0x0),
    gsSP2Triangles( 0,  6, 13, 0x0,  2,  8, 14, 0x0),
    gsSP2Triangles(14,  8, 10, 0x0, 14, 10, 15, 0x0),
    gsSP2Triangles(14,  9,  0, 0x0, 14, 15,  9, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0, 15, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x070247F0 - 0x070249A0
static const Gfx ttm_seg7_dl_070247F0[] = {
    gsSPLight(&ttm_seg7_lights_0701DDB0.l, 1),
    gsSPLight(&ttm_seg7_lights_0701DDB0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07022AF8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  2,  7,  0, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles( 4, 10,  8, 0x0,  4, 11, 12, 0x0),
    gsSP2Triangles( 4, 12, 13, 0x0,  4, 13, 10, 0x0),
    gsSPVertex(ttm_seg7_vertex_07022BD8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  6,  3,  7, 0x0),
    gsSP2Triangles( 3,  5,  8, 0x0,  3,  8,  7, 0x0),
    gsSP2Triangles( 9,  4,  0, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 9,  0, 10, 0x0, 10, 12, 11, 0x0),
    gsSP2Triangles(13, 12, 10, 0x0, 13, 10,  6, 0x0),
    gsSP1Triangle( 7, 13,  6, 0x0),
    gsSPVertex(ttm_seg7_vertex_07022CB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_07022DA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(10,  9, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle(14, 13, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07022E98, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  0,  6, 0x0,  3,  5,  0, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x070249A0 - 0x07024AB0
const Gfx ttm_seg7_dl_070249A0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(980, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07022F08),
    gsSPDisplayList(ttm_seg7_dl_07023108),
    gsSPDisplayList(ttm_seg7_dl_070240F0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07024178),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_07024708),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(ttm_seg7_dl_070247F0),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
