#include "pc/rom_assets.h"
// 0x07012BD0 - 0x07012BE8
static const Lights1 ssl_seg7_lights_07012BD0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07012BE8 - 0x07012C00
static const Lights1 ssl_seg7_lights_07012BE8 = gdSPDefLights1(
    0x46, 0x46, 0x46,
    0x8c, 0x8c, 0x8c, 0x28, 0x28, 0x28
);

// 0x07012C00 - 0x07012C18
static const Lights1 ssl_seg7_lights_07012C00 = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07012C18 - 0x07012C30
static const Lights1 ssl_seg7_lights_07012C18 = gdSPDefLights1(
    0x4b, 0x4b, 0x4b,
    0x96, 0x96, 0x96, 0x28, 0x28, 0x28
);

// 0x07012C30 - 0x07012C48
static const Lights1 ssl_seg7_lights_07012C30 = gdSPDefLights1(
    0x64, 0x64, 0x64,
    0xc8, 0xc8, 0xc8, 0x28, 0x28, 0x28
);

// 0x07012C48 - 0x07012CC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07012C48, 0x003e76b0, 82641, 0x00012c48, 128);

// 0x07012CC8 - 0x07012D48
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07012CC8, 0x003e76b0, 82641, 0x00012cc8, 128);

// 0x07012D48 - 0x07012E48
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07012D48, 0x003e76b0, 82641, 0x00012d48, 256);

// 0x07012E48 - 0x07012E78
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07012E48, 0x003e76b0, 82641, 0x00012e48, 48);

// 0x07012E78 - 0x07012F68
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07012E78, 0x003e76b0, 82641, 0x00012e78, 240);

// 0x07012F68 - 0x07013068
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07012F68, 0x003e76b0, 82641, 0x00012f68, 256);

// 0x07013068 - 0x07013158
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013068, 0x003e76b0, 82641, 0x00013068, 240);

// 0x07013158 - 0x07013248
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013158, 0x003e76b0, 82641, 0x00013158, 240);

// 0x07013248 - 0x07013338
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013248, 0x003e76b0, 82641, 0x00013248, 240);

// 0x07013338 - 0x07013428
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013338, 0x003e76b0, 82641, 0x00013338, 240);

// 0x07013428 - 0x07013528
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013428, 0x003e76b0, 82641, 0x00013428, 256);

// 0x07013528 - 0x07013628
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013528, 0x003e76b0, 82641, 0x00013528, 256);

// 0x07013628 - 0x07013728
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013628, 0x003e76b0, 82641, 0x00013628, 256);

// 0x07013728 - 0x07013818
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013728, 0x003e76b0, 82641, 0x00013728, 240);

// 0x07013818 - 0x07013918
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013818, 0x003e76b0, 82641, 0x00013818, 256);

// 0x07013918 - 0x070139F8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013918, 0x003e76b0, 82641, 0x00013918, 224);

// 0x070139F8 - 0x07013AD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070139F8, 0x003e76b0, 82641, 0x000139f8, 224);

// 0x07013AD8 - 0x07013BD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013AD8, 0x003e76b0, 82641, 0x00013ad8, 256);

// 0x07013BD8 - 0x07013CC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013BD8, 0x003e76b0, 82641, 0x00013bd8, 240);

// 0x07013CC8 - 0x07013DC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013CC8, 0x003e76b0, 82641, 0x00013cc8, 256);

// 0x07013DC8 - 0x07013EC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013DC8, 0x003e76b0, 82641, 0x00013dc8, 256);

// 0x07013EC8 - 0x07013FC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013EC8, 0x003e76b0, 82641, 0x00013ec8, 256);

// 0x07013FC8 - 0x07014098
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07013FC8, 0x003e76b0, 82641, 0x00013fc8, 208);

// 0x07014098 - 0x07014188
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014098, 0x003e76b0, 82641, 0x00014098, 240);

// 0x07014188 - 0x07014278
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014188, 0x003e76b0, 82641, 0x00014188, 240);

// 0x07014278 - 0x07014368
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014278, 0x003e76b0, 82641, 0x00014278, 240);

// 0x07014368 - 0x07014448
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014368, 0x003e76b0, 82641, 0x00014368, 224);

// 0x07014448 - 0x07014548
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014448, 0x003e76b0, 82641, 0x00014448, 256);

// 0x07014548 - 0x07014628
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014548, 0x003e76b0, 82641, 0x00014548, 224);

// 0x07014628 - 0x07014728
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014628, 0x003e76b0, 82641, 0x00014628, 256);

// 0x07014728 - 0x07014818
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014728, 0x003e76b0, 82641, 0x00014728, 240);

// 0x07014818 - 0x070148F8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014818, 0x003e76b0, 82641, 0x00014818, 224);

// 0x070148F8 - 0x070149E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070148F8, 0x003e76b0, 82641, 0x000148f8, 240);

// 0x070149E8 - 0x07014AC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070149E8, 0x003e76b0, 82641, 0x000149e8, 224);

// 0x07014AC8 - 0x07014BB8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014AC8, 0x003e76b0, 82641, 0x00014ac8, 240);

// 0x07014BB8 - 0x07014CA8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014BB8, 0x003e76b0, 82641, 0x00014bb8, 240);

// 0x07014CA8 - 0x07014D98
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014CA8, 0x003e76b0, 82641, 0x00014ca8, 240);

// 0x07014D98 - 0x07014E88
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014D98, 0x003e76b0, 82641, 0x00014d98, 240);

// 0x07014E88 - 0x07014F78
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014E88, 0x003e76b0, 82641, 0x00014e88, 240);

// 0x07014F78 - 0x07015078
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07014F78, 0x003e76b0, 82641, 0x00014f78, 256);

// 0x07015078 - 0x07015168
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015078, 0x003e76b0, 82641, 0x00015078, 240);

// 0x07015168 - 0x07015248
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015168, 0x003e76b0, 82641, 0x00015168, 224);

// 0x07015248 - 0x07015348
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015248, 0x003e76b0, 82641, 0x00015248, 256);

// 0x07015348 - 0x07015428
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015348, 0x003e76b0, 82641, 0x00015348, 224);

// 0x07015428 - 0x07015528
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015428, 0x003e76b0, 82641, 0x00015428, 256);

// 0x07015528 - 0x07015628
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015528, 0x003e76b0, 82641, 0x00015528, 256);

// 0x07015628 - 0x07015728
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015628, 0x003e76b0, 82641, 0x00015628, 256);

// 0x07015728 - 0x07015818
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015728, 0x003e76b0, 82641, 0x00015728, 240);

// 0x07015818 - 0x07015908
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015818, 0x003e76b0, 82641, 0x00015818, 240);

// 0x07015908 - 0x07015A08
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015908, 0x003e76b0, 82641, 0x00015908, 256);

// 0x07015A08 - 0x07015AE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015A08, 0x003e76b0, 82641, 0x00015a08, 224);

// 0x07015AE8 - 0x07015B48
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015AE8, 0x003e76b0, 82641, 0x00015ae8, 96);

// 0x07015B48 - 0x07015BE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015B48, 0x003e76b0, 82641, 0x00015b48, 160);

// 0x07015BE8 - 0x07015CE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015BE8, 0x003e76b0, 82641, 0x00015be8, 256);

// 0x07015CE8 - 0x07015DD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015CE8, 0x003e76b0, 82641, 0x00015ce8, 240);

// 0x07015DD8 - 0x07015EC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015DD8, 0x003e76b0, 82641, 0x00015dd8, 240);

// 0x07015EC8 - 0x07015FB8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015EC8, 0x003e76b0, 82641, 0x00015ec8, 240);

// 0x07015FB8 - 0x070160A8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07015FB8, 0x003e76b0, 82641, 0x00015fb8, 240);

// 0x070160A8 - 0x07016198
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070160A8, 0x003e76b0, 82641, 0x000160a8, 240);

// 0x07016198 - 0x07016288
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016198, 0x003e76b0, 82641, 0x00016198, 240);

// 0x07016288 - 0x07016378
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016288, 0x003e76b0, 82641, 0x00016288, 240);

// 0x07016378 - 0x07016478
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016378, 0x003e76b0, 82641, 0x00016378, 256);

// 0x07016478 - 0x07016578
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016478, 0x003e76b0, 82641, 0x00016478, 256);

// 0x07016578 - 0x07016678
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016578, 0x003e76b0, 82641, 0x00016578, 256);

// 0x07016678 - 0x07016758
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016678, 0x003e76b0, 82641, 0x00016678, 224);

// 0x07016758 - 0x07016848
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016758, 0x003e76b0, 82641, 0x00016758, 240);

// 0x07016848 - 0x07016938
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016848, 0x003e76b0, 82641, 0x00016848, 240);

// 0x07016938 - 0x07016A18
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016938, 0x003e76b0, 82641, 0x00016938, 224);

// 0x07016A18 - 0x07016B08
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016A18, 0x003e76b0, 82641, 0x00016a18, 240);

// 0x07016B08 - 0x07016BF8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016B08, 0x003e76b0, 82641, 0x00016b08, 240);

// 0x07016BF8 - 0x07016CE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016BF8, 0x003e76b0, 82641, 0x00016bf8, 240);

// 0x07016CE8 - 0x07016DD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016CE8, 0x003e76b0, 82641, 0x00016ce8, 240);

// 0x07016DD8 - 0x07016EC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016DD8, 0x003e76b0, 82641, 0x00016dd8, 240);

// 0x07016EC8 - 0x07016FB8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016EC8, 0x003e76b0, 82641, 0x00016ec8, 240);

// 0x07016FB8 - 0x07016FF8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016FB8, 0x003e76b0, 82641, 0x00016fb8, 64);

// 0x07016FF8 - 0x070170E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07016FF8, 0x003e76b0, 82641, 0x00016ff8, 240);

// 0x070170E8 - 0x070171D8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070170E8, 0x003e76b0, 82641, 0x000170e8, 240);

// 0x070171D8 - 0x070172C8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070171D8, 0x003e76b0, 82641, 0x000171d8, 240);

// 0x070172C8 - 0x070173B8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070172C8, 0x003e76b0, 82641, 0x000172c8, 240);

// 0x070173B8 - 0x070174A8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070173B8, 0x003e76b0, 82641, 0x000173b8, 240);

// 0x070174A8 - 0x070175A8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070174A8, 0x003e76b0, 82641, 0x000174a8, 256);

// 0x070175A8 - 0x07017698
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070175A8, 0x003e76b0, 82641, 0x000175a8, 240);

// 0x07017698 - 0x07017778
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017698, 0x003e76b0, 82641, 0x00017698, 224);

// 0x07017778 - 0x07017858
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017778, 0x003e76b0, 82641, 0x00017778, 224);

// 0x07017858 - 0x07017938
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017858, 0x003e76b0, 82641, 0x00017858, 224);

// 0x07017938 - 0x07017A28
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017938, 0x003e76b0, 82641, 0x00017938, 240);

// 0x07017A28 - 0x07017B18
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017A28, 0x003e76b0, 82641, 0x00017a28, 240);

// 0x07017B18 - 0x07017C08
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017B18, 0x003e76b0, 82641, 0x00017b18, 240);

// 0x07017C08 - 0x07017CF8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017C08, 0x003e76b0, 82641, 0x00017c08, 240);

// 0x07017CF8 - 0x07017DE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017CF8, 0x003e76b0, 82641, 0x00017cf8, 240);

// 0x07017DE8 - 0x07017ED8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017DE8, 0x003e76b0, 82641, 0x00017de8, 240);

// 0x07017ED8 - 0x07017FC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017ED8, 0x003e76b0, 82641, 0x00017ed8, 240);

// 0x07017FC8 - 0x070180B8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07017FC8, 0x003e76b0, 82641, 0x00017fc8, 240);

// 0x070180B8 - 0x070181A8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070180B8, 0x003e76b0, 82641, 0x000180b8, 240);

// 0x070181A8 - 0x07018298
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070181A8, 0x003e76b0, 82641, 0x000181a8, 240);

// 0x07018298 - 0x07018388
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018298, 0x003e76b0, 82641, 0x00018298, 240);

// 0x07018388 - 0x07018478
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018388, 0x003e76b0, 82641, 0x00018388, 240);

// 0x07018478 - 0x07018568
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018478, 0x003e76b0, 82641, 0x00018478, 240);

// 0x07018568 - 0x07018658
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018568, 0x003e76b0, 82641, 0x00018568, 240);

// 0x07018658 - 0x07018748
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018658, 0x003e76b0, 82641, 0x00018658, 240);

// 0x07018748 - 0x07018838
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018748, 0x003e76b0, 82641, 0x00018748, 240);

// 0x07018838 - 0x07018928
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018838, 0x003e76b0, 82641, 0x00018838, 240);

// 0x07018928 - 0x07018A18
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018928, 0x003e76b0, 82641, 0x00018928, 240);

// 0x07018A18 - 0x07018B08
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018A18, 0x003e76b0, 82641, 0x00018a18, 240);

// 0x07018B08 - 0x07018BF8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018B08, 0x003e76b0, 82641, 0x00018b08, 240);

// 0x07018BF8 - 0x07018CE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018BF8, 0x003e76b0, 82641, 0x00018bf8, 240);

// 0x07018CE8 - 0x07018DD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018CE8, 0x003e76b0, 82641, 0x00018ce8, 240);

// 0x07018DD8 - 0x07018EC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018DD8, 0x003e76b0, 82641, 0x00018dd8, 240);

// 0x07018EC8 - 0x07018FB8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018EC8, 0x003e76b0, 82641, 0x00018ec8, 240);

// 0x07018FB8 - 0x070190A8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07018FB8, 0x003e76b0, 82641, 0x00018fb8, 240);

// 0x070190A8 - 0x07019198
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_070190A8, 0x003e76b0, 82641, 0x000190a8, 240);

// 0x07019198 - 0x07019278
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019198, 0x003e76b0, 82641, 0x00019198, 224);

// 0x07019278 - 0x07019378
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019278, 0x003e76b0, 82641, 0x00019278, 256);

// 0x07019378 - 0x07019458
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019378, 0x003e76b0, 82641, 0x00019378, 224);

// 0x07019458 - 0x07019548
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019458, 0x003e76b0, 82641, 0x00019458, 240);

// 0x07019548 - 0x07019648
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019548, 0x003e76b0, 82641, 0x00019548, 256);

// 0x07019648 - 0x07019748
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019648, 0x003e76b0, 82641, 0x00019648, 256);

// 0x07019748 - 0x07019848
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019748, 0x003e76b0, 82641, 0x00019748, 256);

// 0x07019848 - 0x07019928
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019848, 0x003e76b0, 82641, 0x00019848, 224);

// 0x07019928 - 0x07019A18
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019928, 0x003e76b0, 82641, 0x00019928, 240);

// 0x07019A18 - 0x07019AF8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019A18, 0x003e76b0, 82641, 0x00019a18, 224);

// 0x07019AF8 - 0x07019BE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019AF8, 0x003e76b0, 82641, 0x00019af8, 240);

// 0x07019BE8 - 0x07019CD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019BE8, 0x003e76b0, 82641, 0x00019be8, 240);

// 0x07019CD8 - 0x07019DD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019CD8, 0x003e76b0, 82641, 0x00019cd8, 256);

// 0x07019DD8 - 0x07019EB8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019DD8, 0x003e76b0, 82641, 0x00019dd8, 224);

// 0x07019EB8 - 0x07019F98
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019EB8, 0x003e76b0, 82641, 0x00019eb8, 224);

// 0x07019F98 - 0x0701A098
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_07019F98, 0x003e76b0, 82641, 0x00019f98, 256);

// 0x0701A098 - 0x0701A198
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A098, 0x003e76b0, 82641, 0x0001a098, 256);

// 0x0701A198 - 0x0701A298
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A198, 0x003e76b0, 82641, 0x0001a198, 256);

// 0x0701A298 - 0x0701A398
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A298, 0x003e76b0, 82641, 0x0001a298, 256);

// 0x0701A398 - 0x0701A498
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A398, 0x003e76b0, 82641, 0x0001a398, 256);

// 0x0701A498 - 0x0701A588
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A498, 0x003e76b0, 82641, 0x0001a498, 240);

// 0x0701A588 - 0x0701A688
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A588, 0x003e76b0, 82641, 0x0001a588, 256);

// 0x0701A688 - 0x0701A778
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A688, 0x003e76b0, 82641, 0x0001a688, 240);

// 0x0701A778 - 0x0701A858
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A778, 0x003e76b0, 82641, 0x0001a778, 224);

// 0x0701A858 - 0x0701A938
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A858, 0x003e76b0, 82641, 0x0001a858, 224);

// 0x0701A938 - 0x0701AA28
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701A938, 0x003e76b0, 82641, 0x0001a938, 240);

// 0x0701AA28 - 0x0701AB08
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701AA28, 0x003e76b0, 82641, 0x0001aa28, 224);

// 0x0701AB08 - 0x0701ABF8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701AB08, 0x003e76b0, 82641, 0x0001ab08, 240);

// 0x0701ABF8 - 0x0701ACE8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701ABF8, 0x003e76b0, 82641, 0x0001abf8, 240);

// 0x0701ACE8 - 0x0701ADD8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701ACE8, 0x003e76b0, 82641, 0x0001ace8, 240);

// 0x0701ADD8 - 0x0701AEC8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701ADD8, 0x003e76b0, 82641, 0x0001add8, 240);

// 0x0701AEC8 - 0x0701AFB8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701AEC8, 0x003e76b0, 82641, 0x0001aec8, 240);

// 0x0701AFB8 - 0x0701B0A8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701AFB8, 0x003e76b0, 82641, 0x0001afb8, 240);

// 0x0701B0A8 - 0x0701B188
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B0A8, 0x003e76b0, 82641, 0x0001b0a8, 224);

// 0x0701B188 - 0x0701B288
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B188, 0x003e76b0, 82641, 0x0001b188, 256);

// 0x0701B288 - 0x0701B328
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B288, 0x003e76b0, 82641, 0x0001b288, 160);

// 0x0701B328 - 0x0701B418
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B328, 0x003e76b0, 82641, 0x0001b328, 240);

// 0x0701B418 - 0x0701B508
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B418, 0x003e76b0, 82641, 0x0001b418, 240);

// 0x0701B508 - 0x0701B5F8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B508, 0x003e76b0, 82641, 0x0001b508, 240);

// 0x0701B5F8 - 0x0701B6E8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B5F8, 0x003e76b0, 82641, 0x0001b5f8, 240);

// 0x0701B6E8 - 0x0701B7A8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B6E8, 0x003e76b0, 82641, 0x0001b6e8, 192);

// 0x0701B7A8 - 0x0701B888
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B7A8, 0x003e76b0, 82641, 0x0001b7a8, 224);

// 0x0701B888 - 0x0701B988
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B888, 0x003e76b0, 82641, 0x0001b888, 256);

// 0x0701B988 - 0x0701BA88
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701B988, 0x003e76b0, 82641, 0x0001b988, 256);

// 0x0701BA88 - 0x0701BB88
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701BA88, 0x003e76b0, 82641, 0x0001ba88, 256);

// 0x0701BB88 - 0x0701BC48
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701BB88, 0x003e76b0, 82641, 0x0001bb88, 192);

// 0x0701BC48 - 0x0701BD28
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701BC48, 0x003e76b0, 82641, 0x0001bc48, 224);

// 0x0701BD28 - 0x0701BE08
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701BD28, 0x003e76b0, 82641, 0x0001bd28, 224);

// 0x0701BE08 - 0x0701BF08
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701BE08, 0x003e76b0, 82641, 0x0001be08, 256);

// 0x0701BF08 - 0x0701BFF8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701BF08, 0x003e76b0, 82641, 0x0001bf08, 240);

// 0x0701BFF8 - 0x0701C0D8
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701BFF8, 0x003e76b0, 82641, 0x0001bff8, 224);

// 0x0701C0D8 - 0x0701C198
ROM_ASSET_LOAD_VTX(ssl_seg7_vertex_0701C0D8, 0x003e76b0, 82641, 0x0001c0d8, 192);

// 0x0701C198 - 0x0701CFA8
static const Gfx ssl_seg7_dl_0701C198[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_0900A800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_07012BD0.l, 1),
    gsSPLight(&ssl_seg7_lights_07012BD0.a, 2),
    gsSPVertex(ssl_seg7_vertex_07012C48, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&ssl_seg7_lights_07012BE8.l, 1),
    gsSPLight(&ssl_seg7_lights_07012BE8.a, 2),
    gsSPVertex(ssl_seg7_vertex_07012CC8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 1,  6,  5, 0x0,  3,  4,  7, 0x0),
    gsSP2Triangles( 5,  7,  4, 0x0,  5,  6,  7, 0x0),
    gsSPLight(&ssl_seg7_lights_07012BD0.l, 1),
    gsSPLight(&ssl_seg7_lights_07012BD0.a, 2),
    gsSPVertex(ssl_seg7_vertex_07012D48, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 3,  6,  5, 0x0,  5,  7,  4, 0x0),
    gsSP2Triangles( 8,  6,  3, 0x0,  9,  8,  3, 0x0),
    gsSP2Triangles( 0, 10, 11, 0x0,  0,  4, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07012E48, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPLight(&ssl_seg7_lights_07012C00.l, 1),
    gsSPLight(&ssl_seg7_lights_07012C00.a, 2),
    gsSPVertex(ssl_seg7_vertex_07012E78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07012F68, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  4, 11,  5, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 11,  4, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles(12,  2, 14, 0x0, 13, 12, 14, 0x0),
    gsSPLight(&ssl_seg7_lights_07012C18.l, 1),
    gsSPLight(&ssl_seg7_lights_07012C18.a, 2),
    gsSPVertex(ssl_seg7_vertex_07013068, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  1, 13, 14, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013158, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013248, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013338, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013428, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0,  3,  9,  8, 0x0),
    gsSP2Triangles( 3,  8, 10, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2,  1, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013528, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  2,  4,  3, 0x0),
    gsSP2Triangles( 2,  5,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013628, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 0,  7,  6, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  8,  5,  7, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(15,  8,  9, 0x0, 15,  9, 11, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013728, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013818, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013918, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_070139F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  0,  8, 11, 0x0),
    gsSP2Triangles( 8,  7, 11, 0x0,  0,  2, 12, 0x0),
    gsSP1Triangle(11, 13,  0, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013AD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013BD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 7, 10, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013CC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(10,  9, 12, 0x0,  9, 11, 13, 0x0),
    gsSP2Triangles(14, 13, 11, 0x0, 14, 11, 15, 0x0),
    gsSP2Triangles( 7, 12, 14, 0x0,  7, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013DC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013EC8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  6,  5, 0x0),
    gsSP2Triangles(11, 12,  6, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07013FC8, 13, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  0, 0x0,  6,  1,  4, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12, 11,  8, 0x0),
    gsSPLight(&ssl_seg7_lights_07012BD0.l, 1),
    gsSPLight(&ssl_seg7_lights_07012BD0.a, 2),
    gsSPVertex(ssl_seg7_vertex_07014098, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014188, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014278, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014368, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle( 0, 13,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014448, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014548, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014628, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014728, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014818, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_070148F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070149E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014AC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014BB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014CA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014D98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014E88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07014F78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015078, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015168, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015248, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015348, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  4,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  1, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  7, 12,  8, 0x0),
    gsSP2Triangles( 7,  6,  4, 0x0,  7, 13,  6, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015428, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  4,  6, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(11, 15,  9, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015528, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015628, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015728, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015818, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  6, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701CFA8 - 0x0701D060
static const Gfx ssl_seg7_dl_0701CFA8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_07015908, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  4,  6,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015A08, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015AE8, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// CLEAR #

// 0x0701D060 - 0x0701E980
static const Gfx ssl_seg7_dl_0701D060[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_07012C00.l, 1),
    gsSPLight(&ssl_seg7_lights_07012C00.a, 2),
    gsSPVertex(ssl_seg7_vertex_07015B48, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPLight(&ssl_seg7_lights_07012C30.l, 1),
    gsSPLight(&ssl_seg7_lights_07012C30.a, 2),
    gsSPVertex(ssl_seg7_vertex_07015BE8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  1, 15,  2, 0x0),
    gsSPLight(&ssl_seg7_lights_07012C18.l, 1),
    gsSPLight(&ssl_seg7_lights_07012C18.a, 2),
    gsSPVertex(ssl_seg7_vertex_07015CE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015DD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015EC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07015FB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 1,  0, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070160A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016198, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016288, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016378, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016478, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(14, 15, 13, 0x0, 14, 13, 11, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016578, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016678, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016758, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016848, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016938, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016A18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016B08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016BF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016CE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016DD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016EC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07016FB8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ssl_seg7_lights_07012BD0.l, 1),
    gsSPLight(&ssl_seg7_lights_07012BD0.a, 2),
    gsSPVertex(ssl_seg7_vertex_07016FF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070170E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070171D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070172C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070173B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070174A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 10,  7, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_070175A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017698, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017778, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  1,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017858, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017938, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017A28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017B18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017C08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017CF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017DE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017ED8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07017FC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_070180B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070181A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018298, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018388, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018478, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018568, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018658, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018748, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018838, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018928, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018A18, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018B08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018BF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018CE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018DD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018EC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07018FB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_070190A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019198, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019278, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0,  2,  9,  8, 0x0),
    gsSP2Triangles( 2, 10,  9, 0x0, 11,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  9, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019378, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019458, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019548, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles( 7, 10,  9, 0x0,  7, 11, 10, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019648, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12,  3, 0x0),
    gsSP2Triangles( 3, 12,  4, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019748, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  6,  5, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019848, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  5,  8, 0x0),
    gsSP2Triangles( 4,  8,  6, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 4, 10,  5, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 5, 10,  2, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019928, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019A18, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019AF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019BE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019CD8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12,  0, 0x0),
    gsSP2Triangles(11,  0,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019DD8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019EB8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  9, 13, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_07019F98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  7, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  0, 13, 14, 0x0),
    gsSP2Triangles( 0, 14,  1, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A098, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  4,  2,  6, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A198, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A298, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(10,  9, 14, 0x0, 10, 15,  8, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A398, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A498, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A588, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 8,  6,  9, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(11, 15, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A688, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A778, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A858, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701A938, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701AA28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701AB08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701ABF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701ACE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701ADD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701AEC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  4,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7, 10,  8, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701AFB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 10,  6,  8, 0x0),
    gsSP2Triangles(10, 11,  6, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B0A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  3,  5,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle( 0,  2, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B188, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 7,  3, 10, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 9,  8,  7, 0x0,  9, 11,  8, 0x0),
    gsSP2Triangles( 9, 10, 12, 0x0,  1,  9,  2, 0x0),
    gsSP2Triangles( 1, 11,  9, 0x0,  0,  9, 12, 0x0),
    gsSP2Triangles( 0,  2,  9, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B288, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// CLEAR #

// 0x0701E980 - 0x0701EAD8
static const Gfx ssl_seg7_dl_0701E980[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_seg7_texture_07001800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_0701B328, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B418, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B508, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B5F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B6E8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701EAD8 - 0x0701ECB0
static const Gfx ssl_seg7_dl_0701EAD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_pyramid_sand),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_0701B7A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  1,  0,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B888, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 2,  6,  3, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  3,  8,  9, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0, 11,  8,  7, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0,  4, 10,  5, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701B988, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 7,  6,  5, 0x0,  5,  8,  7, 0x0),
    gsSP2Triangles( 7,  9,  6, 0x0, 10,  9,  7, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 12,  3, 10, 0x0),
    gsSP2Triangles( 3, 12,  4, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701BA88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701BB88, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  4,  2, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  5,  2,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701ECB0 - 0x0701EE80
static const Gfx ssl_seg7_dl_0701ECB0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, generic_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_0701BC48, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  4,  7, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0, 11, 12,  2, 0x0),
    gsSP1Triangle(11, 13, 12, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701BD28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0,  9, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701BE08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701BF08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701BFF8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0,  9, 10,  3, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ssl_seg7_vertex_0701C0D8, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701EE80 - 0x0701EF80
const Gfx ssl_seg7_dl_0701EE80[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogFactor(0x0E49, 0xF2B7), // This isn't gsSPFogPosition since there is no valid min/max pair that corresponds to 0x0E49F2B7
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_0701C198),
    gsSPDisplayList(ssl_seg7_dl_0701CFA8),
    gsSPDisplayList(ssl_seg7_dl_0701D060),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_0701E980),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_dl_0701EAD8),
    gsSPDisplayList(ssl_seg7_dl_0701ECB0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
