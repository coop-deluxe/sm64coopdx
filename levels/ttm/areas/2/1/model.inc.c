#include "pc/rom_assets.h"
// 0x070172D8 - 0x070172F0
static const Lights1 ttm_seg7_lights_070172D8 = gdSPDefLights1(
    0x08, 0x08, 0x08,
    0x22, 0x22, 0x22, 0x28, 0x28, 0x28
);

// 0x070172F0 - 0x07017308
static const Lights1 ttm_seg7_lights_070172F0 = gdSPDefLights1(
    0x0c, 0x0c, 0x0c,
    0x33, 0x33, 0x33, 0x28, 0x28, 0x28
);

// 0x07017308 - 0x07017320
static const Lights1 ttm_seg7_lights_07017308 = gdSPDefLights1(
    0x11, 0x11, 0x11,
    0x44, 0x44, 0x44, 0x28, 0x28, 0x28
);

// 0x07017320 - 0x07017338
static const Lights1 ttm_seg7_lights_07017320 = gdSPDefLights1(
    0x15, 0x15, 0x15,
    0x55, 0x55, 0x55, 0x28, 0x28, 0x28
);

// 0x07017338 - 0x07017350
static const Lights1 ttm_seg7_lights_07017338 = gdSPDefLights1(
    0x19, 0x19, 0x19,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07017350 - 0x07017368
static const Lights1 ttm_seg7_lights_07017350 = gdSPDefLights1(
    0x1d, 0x1d, 0x1d,
    0x77, 0x77, 0x77, 0x28, 0x28, 0x28
);

// 0x07017368 - 0x07017380
static const Lights1 ttm_seg7_lights_07017368 = gdSPDefLights1(
    0x2a, 0x2a, 0x2a,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x07017380 - 0x07017398
static const Lights1 ttm_seg7_lights_07017380 = gdSPDefLights1(
    0x2e, 0x2e, 0x2e,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x07017398 - 0x070173B0
static const Lights1 ttm_seg7_lights_07017398 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0xcc, 0xcc, 0xcc, 0x28, 0x28, 0x28
);

// 0x070173B0 - 0x070173C8
static const Lights1 ttm_seg7_lights_070173B0 = gdSPDefLights1(
    0x37, 0x37, 0x37,
    0xdd, 0xdd, 0xdd, 0x28, 0x28, 0x28
);

// 0x070173C8 - 0x070173E0
static const Lights1 ttm_seg7_lights_070173C8 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070173E0 - 0x070173F8
static const Lights1 ttm_seg7_lights_070173E0 = gdSPDefLights1(
    0x22, 0x22, 0x22,
    0x88, 0x88, 0x88, 0x28, 0x28, 0x28
);

// 0x070173F8 - 0x07017410
static const Lights1 ttm_seg7_lights_070173F8 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07017410 - 0x07017450
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017410, 0x004d1910, 104662, 0x00017410, 64);

// 0x07017450 - 0x070174D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017450, 0x004d1910, 104662, 0x00017450, 128);

// 0x070174D0 - 0x07017550
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070174D0, 0x004d1910, 104662, 0x000174d0, 128);

// 0x07017550 - 0x070175D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017550, 0x004d1910, 104662, 0x00017550, 128);

// 0x070175D0 - 0x07017650
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070175D0, 0x004d1910, 104662, 0x000175d0, 128);

// 0x07017650 - 0x07017690
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017650, 0x004d1910, 104662, 0x00017650, 64);

// 0x07017690 - 0x07017780
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017690, 0x004d1910, 104662, 0x00017690, 240);

// 0x07017780 - 0x07017870
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017780, 0x004d1910, 104662, 0x00017780, 240);

// 0x07017870 - 0x07017960
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017870, 0x004d1910, 104662, 0x00017870, 240);

// 0x07017960 - 0x07017A60
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017960, 0x004d1910, 104662, 0x00017960, 256);

// 0x07017A60 - 0x07017AE0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017A60, 0x004d1910, 104662, 0x00017a60, 128);

// 0x07017AE0 - 0x07017BD0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017AE0, 0x004d1910, 104662, 0x00017ae0, 240);

// 0x07017BD0 - 0x07017CC0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017BD0, 0x004d1910, 104662, 0x00017bd0, 240);

// 0x07017CC0 - 0x07017D60
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017CC0, 0x004d1910, 104662, 0x00017cc0, 160);

// 0x07017D60 - 0x07017E50
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017D60, 0x004d1910, 104662, 0x00017d60, 240);

// 0x07017E50 - 0x07017F30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017E50, 0x004d1910, 104662, 0x00017e50, 224);

// 0x07017F30 - 0x07017FC0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017F30, 0x004d1910, 104662, 0x00017f30, 144);

// 0x07017FC0 - 0x070180C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07017FC0, 0x004d1910, 104662, 0x00017fc0, 256);

// 0x070180C0 - 0x070181C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070180C0, 0x004d1910, 104662, 0x000180c0, 256);

// 0x070181C0 - 0x070182C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070181C0, 0x004d1910, 104662, 0x000181c0, 256);

// 0x070182C0 - 0x070183C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070182C0, 0x004d1910, 104662, 0x000182c0, 256);

// 0x070183C0 - 0x070184C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070183C0, 0x004d1910, 104662, 0x000183c0, 256);

// 0x070184C0 - 0x070185C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070184C0, 0x004d1910, 104662, 0x000184c0, 256);

// 0x070185C0 - 0x070186C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070185C0, 0x004d1910, 104662, 0x000185c0, 256);

// 0x070186C0 - 0x070187C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070186C0, 0x004d1910, 104662, 0x000186c0, 256);

// 0x070187C0 - 0x070187F0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070187C0, 0x004d1910, 104662, 0x000187c0, 48);

// 0x070187F0 - 0x07018830
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070187F0, 0x004d1910, 104662, 0x000187f0, 64);

// 0x07018830 - 0x07018870
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018830, 0x004d1910, 104662, 0x00018830, 64);

// 0x07018870 - 0x07018970
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018870, 0x004d1910, 104662, 0x00018870, 256);

// 0x07018970 - 0x07018A60
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018970, 0x004d1910, 104662, 0x00018970, 240);

// 0x07018A60 - 0x07018B10
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018A60, 0x004d1910, 104662, 0x00018a60, 176);

// 0x07018B10 - 0x07018C00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018B10, 0x004d1910, 104662, 0x00018b10, 240);

// 0x07018C00 - 0x07018CF0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018C00, 0x004d1910, 104662, 0x00018c00, 240);

// 0x07018CF0 - 0x07018D30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018CF0, 0x004d1910, 104662, 0x00018cf0, 64);

// 0x07018D30 - 0x07018E20
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018D30, 0x004d1910, 104662, 0x00018d30, 240);

// 0x07018E20 - 0x07018ED0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018E20, 0x004d1910, 104662, 0x00018e20, 176);

// 0x07018ED0 - 0x07018FD0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018ED0, 0x004d1910, 104662, 0x00018ed0, 256);

// 0x07018FD0 - 0x070190B0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07018FD0, 0x004d1910, 104662, 0x00018fd0, 224);

// 0x070190B0 - 0x070191A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070190B0, 0x004d1910, 104662, 0x000190b0, 240);

// 0x070191A0 - 0x07019280
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070191A0, 0x004d1910, 104662, 0x000191a0, 224);

// 0x07019280 - 0x07019370
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019280, 0x004d1910, 104662, 0x00019280, 240);

// 0x07019370 - 0x07019460
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019370, 0x004d1910, 104662, 0x00019370, 240);

// 0x07019460 - 0x07019550
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019460, 0x004d1910, 104662, 0x00019460, 240);

// 0x07019550 - 0x07019640
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019550, 0x004d1910, 104662, 0x00019550, 240);

// 0x07019640 - 0x07019730
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019640, 0x004d1910, 104662, 0x00019640, 240);

// 0x07019730 - 0x07019820
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019730, 0x004d1910, 104662, 0x00019730, 240);

// 0x07019820 - 0x07019910
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019820, 0x004d1910, 104662, 0x00019820, 240);

// 0x07019910 - 0x07019A00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019910, 0x004d1910, 104662, 0x00019910, 240);

// 0x07019A00 - 0x07019B00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019A00, 0x004d1910, 104662, 0x00019a00, 256);

// 0x07019B00 - 0x07019BF0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019B00, 0x004d1910, 104662, 0x00019b00, 240);

// 0x07019BF0 - 0x07019CD0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019BF0, 0x004d1910, 104662, 0x00019bf0, 224);

// 0x07019CD0 - 0x07019DC0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019CD0, 0x004d1910, 104662, 0x00019cd0, 240);

// 0x07019DC0 - 0x07019EB0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019DC0, 0x004d1910, 104662, 0x00019dc0, 240);

// 0x07019EB0 - 0x07019FA0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019EB0, 0x004d1910, 104662, 0x00019eb0, 240);

// 0x07019FA0 - 0x0701A090
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07019FA0, 0x004d1910, 104662, 0x00019fa0, 240);

// 0x0701A090 - 0x0701A180
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A090, 0x004d1910, 104662, 0x0001a090, 240);

// 0x0701A180 - 0x0701A270
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A180, 0x004d1910, 104662, 0x0001a180, 240);

// 0x0701A270 - 0x0701A2F0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A270, 0x004d1910, 104662, 0x0001a270, 128);

// 0x0701A2F0 - 0x0701A330
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A2F0, 0x004d1910, 104662, 0x0001a2f0, 64);

// 0x0701A330 - 0x0701A410
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A330, 0x004d1910, 104662, 0x0001a330, 224);

// 0x0701A410 - 0x0701A500
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A410, 0x004d1910, 104662, 0x0001a410, 240);

// 0x0701A500 - 0x0701A5F0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A500, 0x004d1910, 104662, 0x0001a500, 240);

// 0x0701A5F0 - 0x0701A6E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A5F0, 0x004d1910, 104662, 0x0001a5f0, 240);

// 0x0701A6E0 - 0x0701A7D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A6E0, 0x004d1910, 104662, 0x0001a6e0, 240);

// 0x0701A7D0 - 0x0701A8C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A7D0, 0x004d1910, 104662, 0x0001a7d0, 240);

// 0x0701A8C0 - 0x0701A9B0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A8C0, 0x004d1910, 104662, 0x0001a8c0, 240);

// 0x0701A9B0 - 0x0701AA70
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701A9B0, 0x004d1910, 104662, 0x0001a9b0, 192);

// 0x0701AA70 - 0x0701AB50
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701AA70, 0x004d1910, 104662, 0x0001aa70, 224);

// 0x0701AB50 - 0x0701ABD0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701AB50, 0x004d1910, 104662, 0x0001ab50, 128);

// 0x0701ABD0 - 0x0701ACC0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701ABD0, 0x004d1910, 104662, 0x0001abd0, 240);

// 0x0701ACC0 - 0x0701ADB0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701ACC0, 0x004d1910, 104662, 0x0001acc0, 240);

// 0x0701ADB0 - 0x0701AEA0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701ADB0, 0x004d1910, 104662, 0x0001adb0, 240);

// 0x0701AEA0 - 0x0701AFA0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701AEA0, 0x004d1910, 104662, 0x0001aea0, 256);

// 0x0701AFA0 - 0x0701B0A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701AFA0, 0x004d1910, 104662, 0x0001afa0, 256);

// 0x0701B0A0 - 0x0701B1A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B0A0, 0x004d1910, 104662, 0x0001b0a0, 256);

// 0x0701B1A0 - 0x0701B2A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B1A0, 0x004d1910, 104662, 0x0001b1a0, 256);

// 0x0701B2A0 - 0x0701B3A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B2A0, 0x004d1910, 104662, 0x0001b2a0, 256);

// 0x0701B3A0 - 0x0701B4A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B3A0, 0x004d1910, 104662, 0x0001b3a0, 256);

// 0x0701B4A0 - 0x0701B5A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B4A0, 0x004d1910, 104662, 0x0001b4a0, 256);

// 0x0701B5A0 - 0x0701B6A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B5A0, 0x004d1910, 104662, 0x0001b5a0, 256);

// 0x0701B6A0 - 0x0701B7A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B6A0, 0x004d1910, 104662, 0x0001b6a0, 256);

// 0x0701B7A0 - 0x0701B8A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B7A0, 0x004d1910, 104662, 0x0001b7a0, 256);

// 0x0701B8A0 - 0x0701B990
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B8A0, 0x004d1910, 104662, 0x0001b8a0, 240);

// 0x0701B990 - 0x0701BA90
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701B990, 0x004d1910, 104662, 0x0001b990, 256);

// 0x0701BA90 - 0x0701BB90
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701BA90, 0x004d1910, 104662, 0x0001ba90, 256);

// 0x0701BB90 - 0x0701BC90
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701BB90, 0x004d1910, 104662, 0x0001bb90, 256);

// 0x0701BC90 - 0x0701BD90
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701BC90, 0x004d1910, 104662, 0x0001bc90, 256);

// 0x0701BD90 - 0x0701BE00
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701BD90, 0x004d1910, 104662, 0x0001bd90, 112);

// 0x0701BE00 - 0x0701BEE0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_0701BE00, 0x004d1910, 104662, 0x0001be00, 224);

// 0x0701BEE0 - 0x0701C008
static const Gfx ttm_seg7_dl_0701BEE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_070172D8.l, 1),
    gsSPLight(&ttm_seg7_lights_070172D8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017410, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ttm_seg7_lights_070172F0.l, 1),
    gsSPLight(&ttm_seg7_lights_070172F0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017450, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_07017308.l, 1),
    gsSPLight(&ttm_seg7_lights_07017308.a, 2),
    gsSPVertex(ttm_seg7_vertex_070174D0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_07017320.l, 1),
    gsSPLight(&ttm_seg7_lights_07017320.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017550, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_07017338.l, 1),
    gsSPLight(&ttm_seg7_lights_07017338.a, 2),
    gsSPVertex(ttm_seg7_vertex_070175D0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701C008 - 0x0701C688
static const Gfx ttm_seg7_dl_0701C008[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_0900B800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07017350.l, 1),
    gsSPLight(&ttm_seg7_lights_07017350.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017650, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ttm_seg7_lights_07017368.l, 1),
    gsSPLight(&ttm_seg7_lights_07017368.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017690, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(10, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07017780, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0,  1, 13,  2, 0x0),
    gsSP1Triangle(13, 14,  2, 0x0),
    gsSPLight(&ttm_seg7_lights_07017380.l, 1),
    gsSPLight(&ttm_seg7_lights_07017380.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017870, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 10, 0x0),
    gsSPVertex(ttm_seg7_vertex_07017960, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 14,  0, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07017A60, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP1Triangle( 5,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_07017398.l, 1),
    gsSPLight(&ttm_seg7_lights_07017398.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017AE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0,  9, 13, 10, 0x0),
    gsSP1Triangle(13, 14, 10, 0x0),
    gsSPVertex(ttm_seg7_vertex_07017BD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 12, 13, 10, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_07017CC0, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPLight(&ttm_seg7_lights_070173B0.l, 1),
    gsSPLight(&ttm_seg7_lights_070173B0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017D60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(10, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07017E50, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07017F30, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP1Triangle( 6,  8,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_070173C8.l, 1),
    gsSPLight(&ttm_seg7_lights_070173C8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07017FC0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9,  5, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(12, 14, 15, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070180C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 10, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 12, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070181C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  4, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11,  8, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 12, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070182C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles(11, 14, 13, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070183C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 6, 11,  7, 0x0,  6, 12, 11, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 12, 14, 13, 0x0),
    gsSP1Triangle(15, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070184C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  3,  2,  7, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 11, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070185C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  1, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070186C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12,  9, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_070187C0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701C688 - 0x0701C6F8
static const Gfx ttm_seg7_dl_0701C688[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07017398.l, 1),
    gsSPLight(&ttm_seg7_lights_07017398.a, 2),
    gsSPVertex(ttm_seg7_vertex_070187F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ttm_seg7_lights_070173C8.l, 1),
    gsSPLight(&ttm_seg7_lights_070173C8.a, 2),
    gsSPVertex(ttm_seg7_vertex_07018830, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701C6F8 - 0x0701D708
static const Gfx ttm_seg7_dl_0701C6F8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09008800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07017308.l, 1),
    gsSPLight(&ttm_seg7_lights_07017308.a, 2),
    gsSPVertex(ttm_seg7_vertex_07018870, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07017320.l, 1),
    gsSPLight(&ttm_seg7_lights_07017320.a, 2),
    gsSPVertex(ttm_seg7_vertex_07018970, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07018A60, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07017338.l, 1),
    gsSPLight(&ttm_seg7_lights_07017338.a, 2),
    gsSPVertex(ttm_seg7_vertex_07018B10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07018C00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07018CF0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07017350.l, 1),
    gsSPLight(&ttm_seg7_lights_07017350.a, 2),
    gsSPVertex(ttm_seg7_vertex_07018D30, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07018E20, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_070173E0.l, 1),
    gsSPLight(&ttm_seg7_lights_070173E0.a, 2),
    gsSPVertex(ttm_seg7_vertex_07018ED0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07018FD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070190B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070191A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019280, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019370, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019460, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019550, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019640, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019730, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019820, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019910, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019A00, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019B00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019BF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019CD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019DC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019EB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07019FA0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A090, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A180, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A270, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPLight(&ttm_seg7_lights_07017368.l, 1),
    gsSPLight(&ttm_seg7_lights_07017368.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701A2F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ttm_seg7_lights_07017380.l, 1),
    gsSPLight(&ttm_seg7_lights_07017380.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701A330, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A410, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A500, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A5F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A6E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A7D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A8C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701A9B0, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_07017398.l, 1),
    gsSPLight(&ttm_seg7_lights_07017398.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701AA70, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9,  0, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701AB50, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_070173C8.l, 1),
    gsSPLight(&ttm_seg7_lights_070173C8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701ABD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701ACC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701ADB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0,  9, 13, 10, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701AEA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(10, 14, 15, 0x0, 10, 15,  9, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701AFA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B0A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  1,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 13, 14, 12, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B1A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B2A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles(13, 14, 12, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B3A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 12, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B4A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(10, 11, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B5A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14,  6, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B6A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 7,  9, 14, 0x0, 15,  7, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B7A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13,  5, 14, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B8A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701B990, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  4, 11, 0x0,  4,  6, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701BA90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  4,  6, 0x0, 10,  6, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701BB90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(14, 15,  4, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701BC90, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  2,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  5, 10,  6, 0x0),
    gsSP2Triangles( 5, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_0701BD90, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701D708 - 0x0701D798
static const Gfx ttm_seg7_dl_0701D708[] = {
    gsSPLight(&ttm_seg7_lights_070173F8.l, 1),
    gsSPLight(&ttm_seg7_lights_070173F8.a, 2),
    gsSPVertex(ttm_seg7_vertex_0701BE00, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  4,  0,  5, 0x0),
    gsSP2Triangles( 2,  1,  6, 0x0,  5,  7,  2, 0x0),
    gsSP2Triangles( 5,  2,  8, 0x0,  5,  9, 10, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0,  5, 11, 12, 0x0),
    gsSP2Triangles( 5, 12,  4, 0x0,  5,  8,  9, 0x0),
    gsSP2Triangles( 2, 13,  8, 0x0,  2,  6, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701D798 - 0x0701D888
const Gfx ttm_seg7_dl_0701D798[] = {
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
    gsSPDisplayList(ttm_seg7_dl_0701BEE0),
    gsSPDisplayList(ttm_seg7_dl_0701C008),
    gsSPDisplayList(ttm_seg7_dl_0701C688),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_0701C6F8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(ttm_seg7_dl_0701D708),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
