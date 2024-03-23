#include "pc/rom_assets.h"
// 0x07005000 - 0x07005018
static const Lights1 ttm_seg7_lights_07005000 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07005018 - 0x07005030
static const Lights1 ttm_seg7_lights_07005018 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07005030 - 0x07005048
static const Lights1 ttm_seg7_lights_07005030 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x07005048 - 0x07005060
static const Lights1 ttm_seg7_lights_07005048 = gdSPDefLights1(
    0x37, 0x29, 0x22,
    0x6e, 0x52, 0x44, 0x28, 0x28, 0x28
);

// 0x07005060 - 0x07005160
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005060, 0x004d1910, 104662, 0x00005060, 256);

// 0x07005160 - 0x07005250
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005160, 0x004d1910, 104662, 0x00005160, 240);

// 0x07005250 - 0x07005330
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005250, 0x004d1910, 104662, 0x00005250, 224);

// 0x07005330 - 0x07005420
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005330, 0x004d1910, 104662, 0x00005330, 240);

// 0x07005420 - 0x07005520
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005420, 0x004d1910, 104662, 0x00005420, 256);

// 0x07005520 - 0x07005620
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005520, 0x004d1910, 104662, 0x00005520, 256);

// 0x07005620 - 0x07005700
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005620, 0x004d1910, 104662, 0x00005620, 224);

// 0x07005700 - 0x070057E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005700, 0x004d1910, 104662, 0x00005700, 224);

// 0x070057E0 - 0x070058E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070057E0, 0x004d1910, 104662, 0x000057e0, 256);

// 0x070058E0 - 0x070059E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070058E0, 0x004d1910, 104662, 0x000058e0, 256);

// 0x070059E0 - 0x07005AE0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070059E0, 0x004d1910, 104662, 0x000059e0, 256);

// 0x07005AE0 - 0x07005BD0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005AE0, 0x004d1910, 104662, 0x00005ae0, 240);

// 0x07005BD0 - 0x07005CD0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005BD0, 0x004d1910, 104662, 0x00005bd0, 256);

// 0x07005CD0 - 0x07005DD0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005CD0, 0x004d1910, 104662, 0x00005cd0, 256);

// 0x07005DD0 - 0x07005EB0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005DD0, 0x004d1910, 104662, 0x00005dd0, 224);

// 0x07005EB0 - 0x07005FA0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005EB0, 0x004d1910, 104662, 0x00005eb0, 240);

// 0x07005FA0 - 0x07006080
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07005FA0, 0x004d1910, 104662, 0x00005fa0, 224);

// 0x07006080 - 0x07006170
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006080, 0x004d1910, 104662, 0x00006080, 240);

// 0x07006170 - 0x07006250
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006170, 0x004d1910, 104662, 0x00006170, 224);

// 0x07006250 - 0x07006340
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006250, 0x004d1910, 104662, 0x00006250, 240);

// 0x07006340 - 0x07006430
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006340, 0x004d1910, 104662, 0x00006340, 240);

// 0x07006430 - 0x070064C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006430, 0x004d1910, 104662, 0x00006430, 144);

// 0x070064C0 - 0x070065C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070064C0, 0x004d1910, 104662, 0x000064c0, 256);

// 0x070065C0 - 0x070066C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070065C0, 0x004d1910, 104662, 0x000065c0, 256);

// 0x070066C0 - 0x070067A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070066C0, 0x004d1910, 104662, 0x000066c0, 224);

// 0x070067A0 - 0x07006880
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070067A0, 0x004d1910, 104662, 0x000067a0, 224);

// 0x07006880 - 0x07006970
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006880, 0x004d1910, 104662, 0x00006880, 240);

// 0x07006970 - 0x07006A50
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006970, 0x004d1910, 104662, 0x00006970, 224);

// 0x07006A50 - 0x07006B40
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006A50, 0x004d1910, 104662, 0x00006a50, 240);

// 0x07006B40 - 0x07006C30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006B40, 0x004d1910, 104662, 0x00006b40, 240);

// 0x07006C30 - 0x07006D30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006C30, 0x004d1910, 104662, 0x00006c30, 256);

// 0x07006D30 - 0x07006E30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006D30, 0x004d1910, 104662, 0x00006d30, 256);

// 0x07006E30 - 0x07006F30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006E30, 0x004d1910, 104662, 0x00006e30, 256);

// 0x07006F30 - 0x07007030
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07006F30, 0x004d1910, 104662, 0x00006f30, 256);

// 0x07007030 - 0x07007120
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007030, 0x004d1910, 104662, 0x00007030, 240);

// 0x07007120 - 0x07007200
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007120, 0x004d1910, 104662, 0x00007120, 224);

// 0x07007200 - 0x07007300
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007200, 0x004d1910, 104662, 0x00007200, 256);

// 0x07007300 - 0x07007400
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007300, 0x004d1910, 104662, 0x00007300, 256);

// 0x07007400 - 0x070074F0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007400, 0x004d1910, 104662, 0x00007400, 240);

// 0x070074F0 - 0x070075F0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070074F0, 0x004d1910, 104662, 0x000074f0, 256);

// 0x070075F0 - 0x070076E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070075F0, 0x004d1910, 104662, 0x000075f0, 240);

// 0x070076E0 - 0x070077D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070076E0, 0x004d1910, 104662, 0x000076e0, 240);

// 0x070077D0 - 0x070078C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070077D0, 0x004d1910, 104662, 0x000077d0, 240);

// 0x070078C0 - 0x070079A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070078C0, 0x004d1910, 104662, 0x000078c0, 224);

// 0x070079A0 - 0x07007A90
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070079A0, 0x004d1910, 104662, 0x000079a0, 240);

// 0x07007A90 - 0x07007B80
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007A90, 0x004d1910, 104662, 0x00007a90, 240);

// 0x07007B80 - 0x07007C70
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007B80, 0x004d1910, 104662, 0x00007b80, 240);

// 0x07007C70 - 0x07007D60
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007C70, 0x004d1910, 104662, 0x00007c70, 240);

// 0x07007D60 - 0x07007E40
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007D60, 0x004d1910, 104662, 0x00007d60, 224);

// 0x07007E40 - 0x07007F20
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007E40, 0x004d1910, 104662, 0x00007e40, 224);

// 0x07007F20 - 0x07007FC0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007F20, 0x004d1910, 104662, 0x00007f20, 160);

// 0x07007FC0 - 0x07008000
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07007FC0, 0x004d1910, 104662, 0x00007fc0, 64);

// 0x07008000 - 0x070080F0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008000, 0x004d1910, 104662, 0x00008000, 240);

// 0x070080F0 - 0x070081F0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070080F0, 0x004d1910, 104662, 0x000080f0, 256);

// 0x070081F0 - 0x070082E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070081F0, 0x004d1910, 104662, 0x000081f0, 240);

// 0x070082E0 - 0x070083D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070082E0, 0x004d1910, 104662, 0x000082e0, 240);

// 0x070083D0 - 0x070084C0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070083D0, 0x004d1910, 104662, 0x000083d0, 240);

// 0x070084C0 - 0x070085B0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070084C0, 0x004d1910, 104662, 0x000084c0, 240);

// 0x070085B0 - 0x070086A0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070085B0, 0x004d1910, 104662, 0x000085b0, 240);

// 0x070086A0 - 0x07008790
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070086A0, 0x004d1910, 104662, 0x000086a0, 240);

// 0x07008790 - 0x07008880
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008790, 0x004d1910, 104662, 0x00008790, 240);

// 0x07008880 - 0x070088E0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008880, 0x004d1910, 104662, 0x00008880, 96);

// 0x070088E0 - 0x070089D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070088E0, 0x004d1910, 104662, 0x000088e0, 240);

// 0x070089D0 - 0x07008A80
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_070089D0, 0x004d1910, 104662, 0x000089d0, 176);

// 0x07008A80 - 0x07008B70
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008A80, 0x004d1910, 104662, 0x00008a80, 240);

// 0x07008B70 - 0x07008C50
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008B70, 0x004d1910, 104662, 0x00008b70, 224);

// 0x07008C50 - 0x07008D40
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008C50, 0x004d1910, 104662, 0x00008c50, 240);

// 0x07008D40 - 0x07008E30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008D40, 0x004d1910, 104662, 0x00008d40, 240);

// 0x07008E30 - 0x07008E60
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008E30, 0x004d1910, 104662, 0x00008e30, 48);

// 0x07008E60 - 0x07008F30
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008E60, 0x004d1910, 104662, 0x00008e60, 208);

// 0x07008F30 - 0x07009010
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07008F30, 0x004d1910, 104662, 0x00008f30, 224);

// 0x07009010 - 0x070090D0
ROM_ASSET_LOAD_VTX(ttm_seg7_vertex_07009010, 0x004d1910, 104662, 0x00009010, 192);

// 0x070090D0 - 0x07009C98
static const Gfx ttm_seg7_dl_070090D0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09004000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07005000.l, 1),
    gsSPLight(&ttm_seg7_lights_07005000.a, 2),
    gsSPVertex(ttm_seg7_vertex_07005060, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005160, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005250, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005330, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005420, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005520, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005620, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005700, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_070057E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_070058E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  1,  3,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070059E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005AE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005BD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005CD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005DD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005EB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07005FA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 10, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006080, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006170, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006250, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006340, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006430, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPLight(&ttm_seg7_lights_07005018.l, 1),
    gsSPLight(&ttm_seg7_lights_07005018.a, 2),
    gsSPVertex(ttm_seg7_vertex_070064C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  0,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_070065C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_070066C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070067A0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11,  2,  1, 0x0, 11,  1, 12, 0x0),
    gsSP1Triangle( 2, 13,  0, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006880, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006970, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006A50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006B40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006C30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006D30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006E30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07006F30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007030, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007120, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPLight(&ttm_seg7_lights_07005030.l, 1),
    gsSPLight(&ttm_seg7_lights_07005030.a, 2),
    gsSPVertex(ttm_seg7_vertex_07007200, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007300, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0, 13, 14,  1, 0x0),
    gsSP2Triangles( 0, 13,  1, 0x0, 15, 12, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007400, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070074F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  4, 11,  5, 0x0),
    gsSP2Triangles(12,  4,  7, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttm_seg7_vertex_070075F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070076E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0, 10,  7,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070077D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070078C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_070079A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007B80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007C70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007D60, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007E40, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_07007F20, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009C98 - 0x07009CE0
static const Gfx ttm_seg7_dl_07009C98[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09005000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07005000.l, 1),
    gsSPLight(&ttm_seg7_lights_07005000.a, 2),
    gsSPVertex(ttm_seg7_vertex_07007FC0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009CE0 - 0x0700A038
static const Gfx ttm_seg7_dl_07009CE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_07008000, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070080F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070081F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070082E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070083D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070084C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070085B0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070086A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07008790, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07008880, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ttm_seg7_lights_07005018.l, 1),
    gsSPLight(&ttm_seg7_lights_07005018.a, 2),
    gsSPVertex(ttm_seg7_vertex_070088E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0, 11,  7,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_070089D0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 0, 10,  1, 0x0),
    gsSPLight(&ttm_seg7_lights_07005030.l, 1),
    gsSPLight(&ttm_seg7_lights_07005030.a, 2),
    gsSPVertex(ttm_seg7_vertex_07008A80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07008B70, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07008C50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07008D40, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttm_seg7_vertex_07008E30, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A038 - 0x0700A098
static const Gfx ttm_seg7_dl_0700A038[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttm_seg7_texture_07002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_07005000.l, 1),
    gsSPLight(&ttm_seg7_lights_07005000.a, 2),
    gsSPVertex(ttm_seg7_vertex_07008E60, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle(10, 11, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A098 - 0x0700A120
static const Gfx ttm_seg7_dl_0700A098[] = {
    gsSPLight(&ttm_seg7_lights_07005048.l, 1),
    gsSPLight(&ttm_seg7_lights_07005048.a, 2),
    gsSPVertex(ttm_seg7_vertex_07008F30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_07009010, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A120 - 0x0700A1B0
const Gfx ttm_seg7_dl_0700A120[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_dl_070090D0),
    gsSPDisplayList(ttm_seg7_dl_07009C98),
    gsSPDisplayList(ttm_seg7_dl_07009CE0),
    gsSPDisplayList(ttm_seg7_dl_0700A038),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(ttm_seg7_dl_0700A098),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
