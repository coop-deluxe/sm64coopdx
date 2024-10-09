#include "pc/rom_assets.h"
// 0x0700FCE8 - 0x0700FDE8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700FCE8, 0x0046c3a0, 47442, 0x0000fce8, 256);

// 0x0700FDE8 - 0x0700FED8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700FDE8, 0x0046c3a0, 47442, 0x0000fde8, 240);

// 0x0700FED8 - 0x0700FFC8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700FED8, 0x0046c3a0, 47442, 0x0000fed8, 240);

// 0x0700FFC8 - 0x070100C8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_0700FFC8, 0x0046c3a0, 47442, 0x0000ffc8, 256);

// 0x070100C8 - 0x070101C8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070100C8, 0x0046c3a0, 47442, 0x000100c8, 256);

// 0x070101C8 - 0x07010208
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070101C8, 0x0046c3a0, 47442, 0x000101c8, 64);

// 0x07010208 - 0x07010308
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010208, 0x0046c3a0, 47442, 0x00010208, 256);

// 0x07010308 - 0x070103F8
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_07010308[] = {
    {{{  -921,   -229,   -434}, 0, {   308,    650}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -306,   -383,   -434}, 0, {  1076,   1924}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -921,   -383,   -434}, 0, {    54,    904}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -306,   -229,   -434}, 0, {  1330,   1670}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   922,   -383,   -434}, 0, {  3120,   3968}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   307,   -383,   -434}, 0, {  2098,   2946}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   307,   -229,   -434}, 0, {  2352,   2692}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   922,   -229,   -434}, 0, {  3374,   3714}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   922,   -383,   -741}, 0, {  3546,  -1564}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   296,   -383,   -741}, 0, {  2504,   -524}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   296,   -383,   -434}, 0, {  1992,  -1034}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   205,    -25,   -434}, 0, { -1222,    478}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   205,   -229,   -434}, 0, {  -882,    138}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   205,   -229,   -332}, 0, {  -712,    308}, {0x96, 0x96, 0x96, 0xff}}},
    {{{   205,    -25,   -332}, 0, { -1052,    650}, {0x96, 0x96, 0x96, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010308, 0x0046c3a0, 47442, 0x00010308, 240);
#endif

// 0x070103F8 - 0x070104D8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070103F8, 0x0046c3a0, 47442, 0x000103f8, 224);

// 0x070104D8 - 0x070105C8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070104D8, 0x0046c3a0, 47442, 0x000104d8, 240);

// 0x070105C8 - 0x070106C8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070105C8, 0x0046c3a0, 47442, 0x000105c8, 256);

// 0x070106C8 - 0x070107A8
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_070106C8[] = {
    {{{   922,   -434,   -434}, 0, { -3096,  -2758}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   922,   -229,   -434}, 0, { -3436,  -2416}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   922,   -229,   1613}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -921,   -434,   1613}, 0, {   308,    650}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -921,   -229,   1613}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -921,   -229,   -434}, 0, { -3436,  -2416}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -921,   -434,   -434}, 0, { -3096,  -2758}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   307,   -229,   -434}, 0, {  -882,    138}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   307,    -25,  -1049}, 0, { -2244,   -544}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   307,    179,  -1049}, 0, { -2584,   -202}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   307,    -25,   -434}, 0, { -1222,    478}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -517,    179,  -1759}, 0, {  -252,   1788}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -517,    282,  -1759}, 0, {     0,   1532}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -517,    282,  -2190}, 0, {  1076,   2608}, {0x7d, 0x7d, 0x7d, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070106C8, 0x0046c3a0, 47442, 0x000106c8, 224);
#endif

// 0x070107A8 - 0x07010888
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_070107A8[] = {
    {{{  -204,   -229,   -434}, 0, {  3374,   4394}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -204,     77,  -1049}, 0, {  4908,   4906}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -204,    179,  -1049}, 0, {  5078,   4736}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -306,   -229,   -434}, 0, {  -882,    138}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -306,    -25,   -434}, 0, { -1222,    478}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -306,    -25,  -1049}, 0, { -2244,   -544}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -306,    179,  -1049}, 0, { -2584,   -202}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   205,   -229,   -434}, 0, {  -882,    138}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   205,    -25,   -434}, 0, { -1222,    478}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   205,     77,  -1049}, 0, { -2414,   -372}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   205,    179,  -1049}, 0, { -2584,   -202}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -517,    179,  -1759}, 0, {  -252,   1788}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -517,    282,  -2190}, 0, {  1076,   2608}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -517,    179,  -2190}, 0, {   820,   2862}, {0x7d, 0x7d, 0x7d, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070107A8, 0x0046c3a0, 47442, 0x000107a8, 224);
#endif

// 0x07010888 - 0x07010978
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_07010888[] = {
    {{{  -921,   -229,   -332}, 0, {  -712,    308}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -921,    -25,   -434}, 0, { -1222,    478}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -921,   -229,   -434}, 0, {  -882,    138}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   522,    179,  -2190}, 0, {   820,   2862}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   524,    282,  -1757}, 0, {    -4,   1528}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   524,    179,  -1757}, 0, {  -258,   1782}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   522,    282,  -2190}, 0, {  1076,   2608}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -328,    282,  -1837}, 0, {   196,   1728}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -328,    384,  -2112}, 0, {  1136,   2156}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -328,    282,  -2112}, 0, {   880,   2412}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{  -328,    384,  -1837}, 0, {   452,   1472}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   333,    282,  -2112}, 0, {   880,   2412}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   333,    384,  -2112}, 0, {  1136,   2156}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   333,    384,  -1837}, 0, {  1136,   2156}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   333,    282,  -1837}, 0, {   880,   2412}, {0x7d, 0x7d, 0x7d, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010888, 0x0046c3a0, 47442, 0x00010888, 240);
#endif

// 0x07010978 - 0x07010A68
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010978, 0x0046c3a0, 47442, 0x00010978, 240);

// 0x07010A68 - 0x07010B58
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010A68, 0x0046c3a0, 47442, 0x00010a68, 240);

// 0x07010B58 - 0x07010C48
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010B58, 0x0046c3a0, 47442, 0x00010b58, 240);

// 0x07010C48 - 0x07010D38
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_07010C48[] = {
    {{{   922,   -434,   -434}, 0, {  -116,   1074}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   922,   -383,   -741}, 0, {   480,   1500}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   922,   -383,   -434}, 0, {     0,    990}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   922,   -434,   -741}, 0, {   394,   1584}, {0x7d, 0x7d, 0x7d, 0xff}}},
    {{{   200,     77,   1096}, 0, {  -132,   2692}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   415,     77,   1311}, 0, {   752,   2692}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   200,     77,   1311}, 0, {   308,   2248}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   307,    -25,  -1049}, 0, {  2352,  -5482}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   307,   -229,   -434}, 0, {  1330,  -4460}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -306,   -229,   -434}, 0, {  2352,  -3438}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -306,    -25,  -1049}, 0, {  3374,  -4460}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -721,    179,    379}, 0, { -1836,   3372}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -506,    179,    594}, 0, {  -950,   3372}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -721,    179,    594}, 0, { -1392,   2930}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -506,    179,    379}, 0, { -1392,   3816}, {0x44, 0x44, 0x44, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010C48, 0x0046c3a0, 47442, 0x00010c48, 240);
#endif

// 0x07010D38 - 0x07010E18
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010D38, 0x0046c3a0, 47442, 0x00010d38, 224);

// 0x07010E18 - 0x07010EF8
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_07010E18[] = {
    {{{   307,   -383,   -434}, 0, {  2098,   2946}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -306,   -229,   -434}, 0, {  1330,   1670}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   307,   -229,   -434}, 0, {  2352,   2692}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -306,   -383,   -434}, 0, {  1076,   1924}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -511,   -434,   2022}, 0, { -7014,  -1224}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -921,   -434,   1613}, 0, { -7014,    138}, {0x44, 0x44, 0x44, 0xff}}},
    {{{  -921,   -434,   -741}, 0, { -3096,   4054}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   922,   -434,   -741}, 0, {     0,    990}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   922,   -434,   1613}, 0, { -3948,  -2928}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   512,   -434,   2022}, 0, { -5310,  -2928}, {0x44, 0x44, 0x44, 0xff}}},
    {{{   296,   -383,   -741}, 0, {  2504,   -524}, {0x50, 0x50, 0x50, 0xff}}},
    {{{  -313,   -383,   -741}, 0, {  1490,    490}, {0x50, 0x50, 0x50, 0xff}}},
    {{{  -313,   -383,   -434}, 0, {   978,    -20}, {0x50, 0x50, 0x50, 0xff}}},
    {{{   296,   -383,   -434}, 0, {  1992,  -1034}, {0x50, 0x50, 0x50, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010E18, 0x0046c3a0, 47442, 0x00010e18, 224);
#endif

// 0x07010EF8 - 0x07010FE8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010EF8, 0x0046c3a0, 47442, 0x00010ef8, 240);

// 0x07010FE8 - 0x070110C8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07010FE8, 0x0046c3a0, 47442, 0x00010fe8, 224);

// 0x070110C8 - 0x070111B8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070110C8, 0x0046c3a0, 47442, 0x000110c8, 240);

// 0x070111B8 - 0x07011298
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_070111B8, 0x0046c3a0, 47442, 0x000111b8, 224);

// 0x07011298 - 0x07011388
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011298, 0x0046c3a0, 47442, 0x00011298, 240);

// 0x07011388 - 0x07011478
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_07011388[] = {
    {{{   512,   -434,   2022}, 0, { -2756,   3032}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -511,   -229,   2022}, 0, {  -712,   1670}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -511,   -434,   2022}, 0, { -1052,   1328}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   512,   -229,   2022}, 0, { -2414,   3372}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -212,    179,  -2495}, 0, {  -736,   1304}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   218,    282,  -2495}, 0, {   592,   2124}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   218,    179,  -2495}, 0, {   336,   2378}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -212,    282,  -2495}, 0, {  -482,   1048}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   218,    179,  -1454}, 0, {   336,   2378}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -212,    282,  -1454}, 0, {  -482,   1048}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -212,    179,  -1454}, 0, {  -736,   1304}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   218,    282,  -1454}, 0, {   592,   2124}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -921,    -25,   -434}, 0, {   650,    308}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -306,   -229,   -434}, 0, {  1330,   1670}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -921,   -229,   -434}, 0, {   308,    650}, {0x64, 0x64, 0x64, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011388, 0x0046c3a0, 47442, 0x00011388, 240);
#endif

// 0x07011478 - 0x07011558
#ifdef VERSION_JP
static const Vtx bits_seg7_vertex_07011478[] = {
    {{{  -134,    282,  -2306}, 0, {  -286,   1244}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -134,    384,  -2306}, 0, {     0,    990}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   139,    384,  -2306}, 0, {   652,   1672}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   139,    282,  -1643}, 0, {   396,   1928}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   139,    384,  -1643}, 0, {   652,   1672}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -134,    384,  -1643}, 0, {     0,    990}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -134,    282,  -1643}, 0, {  -286,   1244}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   307,    -25,   -434}, 0, {  2694,   2350}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   922,    -25,   -434}, 0, {  3716,   3372}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   922,   -229,   -434}, 0, {  3374,   3714}, {0x64, 0x64, 0x64, 0xff}}},
    {{{   307,   -229,   -434}, 0, {  2352,   2692}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -921,    -25,   -434}, 0, {   650,    308}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -306,    -25,   -434}, 0, {  1672,   1328}, {0x64, 0x64, 0x64, 0xff}}},
    {{{  -306,   -229,   -434}, 0, {  1330,   1670}, {0x64, 0x64, 0x64, 0xff}}},
};
#else
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011478, 0x0046c3a0, 47442, 0x00011478, 224);
#endif

// 0x07011558 - 0x07011648
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011558, 0x0046c3a0, 47442, 0x00011558, 240);

// 0x07011648 - 0x07011738
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011648, 0x0046c3a0, 47442, 0x00011648, 240);

// 0x07011738 - 0x07011838
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011738, 0x0046c3a0, 47442, 0x00011738, 256);

// 0x07011838 - 0x07011938
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011838, 0x0046c3a0, 47442, 0x00011838, 256);

// 0x07011938 - 0x07011A38
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011938, 0x0046c3a0, 47442, 0x00011938, 256);

// 0x07011A38 - 0x07011B38
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011A38, 0x0046c3a0, 47442, 0x00011a38, 256);

// 0x07011B38 - 0x07011C38
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011B38, 0x0046c3a0, 47442, 0x00011b38, 256);

// 0x07011C38 - 0x07011D38
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011C38, 0x0046c3a0, 47442, 0x00011c38, 256);

// 0x07011D38 - 0x07011E38
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011D38, 0x0046c3a0, 47442, 0x00011d38, 256);

// 0x07011E38 - 0x07011EF8
ROM_ASSET_LOAD_VTX(bits_seg7_vertex_07011E38, 0x0046c3a0, 47442, 0x00011e38, 192);

// 0x07011EF8 - 0x07012098
static const Gfx bits_seg7_dl_07011EF8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_0700FCE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  6, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_0700FDE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700FED8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_0700FFC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070100C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_070101C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012098 - 0x07012758
static const Gfx bits_seg7_dl_07012098[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07010208, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_07010308, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070103F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070104D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070105C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  9,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_070106C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070107A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07010888, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07010978, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07010A68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07010B58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07010C48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_07010D38, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(bits_seg7_vertex_07010E18, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07010EF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  6, 10, 0x0),
    gsSP2Triangles( 3, 10,  8, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0,  0, 13, 14, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bits_seg7_vertex_07010FE8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_070110C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_070111B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07011298, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07011388, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07011478, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07011558, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07011648, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bits_seg7_vertex_07011738, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07011838, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07011938, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 11, 13, 0x0,  1, 15,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012758 - 0x07012898
static const Gfx bits_seg7_dl_07012758[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bits_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07011A38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(bits_seg7_vertex_07011B38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 9, 14, 10, 0x0, 15, 11, 13, 0x0),
    gsSPVertex(bits_seg7_vertex_07011C38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(bits_seg7_vertex_07011D38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 9, 14, 10, 0x0, 15, 11, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012898 - 0x070128F0
static const Gfx bits_seg7_dl_07012898[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bits_seg7_texture_07001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bits_seg7_vertex_07011E38, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x070128F0 - 0x070129A8
const Gfx bits_seg7_dl_070128F0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_07011EF8),
    gsSPDisplayList(bits_seg7_dl_07012098),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_07012758),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bits_seg7_dl_07012898),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
