#include "pc/rom_assets.h"
// 0x07001000 - 0x07001018
static const Lights1 ttc_seg7_lights_07001000 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07001018 - 0x07001030
static const Lights1 ttc_seg7_lights_07001018 = gdSPDefLights1(
    0x19, 0x19, 0x19,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x07001030 - 0x07001048
static const Lights1 ttc_seg7_lights_07001030 = gdSPDefLights1(
    0x26, 0x26, 0x26,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07001048 - 0x07001060
static const Lights1 ttc_seg7_lights_07001048 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07001060 - 0x07001078
static const Lights1 ttc_seg7_lights_07001060 = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07001078 - 0x07001168
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001078, 0x0042cf20, 42199, 0x00001078, 240);

// 0x07001168 - 0x07001258
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001168, 0x0042cf20, 42199, 0x00001168, 240);

// 0x07001258 - 0x07001348
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001258, 0x0042cf20, 42199, 0x00001258, 240);

// 0x07001348 - 0x07001438
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001348, 0x0042cf20, 42199, 0x00001348, 240);

// 0x07001438 - 0x07001528
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001438, 0x0042cf20, 42199, 0x00001438, 240);

// 0x07001528 - 0x07001618
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001528, 0x0042cf20, 42199, 0x00001528, 240);

// 0x07001618 - 0x07001708
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001618, 0x0042cf20, 42199, 0x00001618, 240);

// 0x07001708 - 0x070017F8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001708, 0x0042cf20, 42199, 0x00001708, 240);

// 0x070017F8 - 0x070018E8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070017F8, 0x0042cf20, 42199, 0x000017f8, 240);

// 0x070018E8 - 0x070019D8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070018E8, 0x0042cf20, 42199, 0x000018e8, 240);

// 0x070019D8 - 0x07001AC8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070019D8, 0x0042cf20, 42199, 0x000019d8, 240);

// 0x07001AC8 - 0x07001BB8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001AC8, 0x0042cf20, 42199, 0x00001ac8, 240);

// 0x07001BB8 - 0x07001CB8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001BB8, 0x0042cf20, 42199, 0x00001bb8, 256);

// 0x07001CB8 - 0x07001DA8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001CB8, 0x0042cf20, 42199, 0x00001cb8, 240);

// 0x07001DA8 - 0x07001E38
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001DA8, 0x0042cf20, 42199, 0x00001da8, 144);

// 0x07001E38 - 0x07001E78
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001E38, 0x0042cf20, 42199, 0x00001e38, 64);

// 0x07001E78 - 0x07001F78
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001E78, 0x0042cf20, 42199, 0x00001e78, 256);

// 0x07001F78 - 0x07002058
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07001F78, 0x0042cf20, 42199, 0x00001f78, 224);

// 0x07002058 - 0x07002158
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002058, 0x0042cf20, 42199, 0x00002058, 256);

// 0x07002158 - 0x07002248
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002158, 0x0042cf20, 42199, 0x00002158, 240);

// 0x07002248 - 0x07002348
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002248, 0x0042cf20, 42199, 0x00002248, 256);

// 0x07002348 - 0x07002428
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002348, 0x0042cf20, 42199, 0x00002348, 224);

// 0x07002428 - 0x07002528
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002428, 0x0042cf20, 42199, 0x00002428, 256);

// 0x07002528 - 0x07002628
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002528, 0x0042cf20, 42199, 0x00002528, 256);

// 0x07002628 - 0x07002728
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002628, 0x0042cf20, 42199, 0x00002628, 256);

// 0x07002728 - 0x07002828
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002728, 0x0042cf20, 42199, 0x00002728, 256);

// 0x07002828 - 0x07002928
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002828, 0x0042cf20, 42199, 0x00002828, 256);

// 0x07002928 - 0x07002A28
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002928, 0x0042cf20, 42199, 0x00002928, 256);

// 0x07002A28 - 0x07002B28
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002A28, 0x0042cf20, 42199, 0x00002a28, 256);

// 0x07002B28 - 0x07002C28
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002B28, 0x0042cf20, 42199, 0x00002b28, 256);

// 0x07002C28 - 0x07002D08
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002C28, 0x0042cf20, 42199, 0x00002c28, 224);

// 0x07002D08 - 0x07002D88
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002D08, 0x0042cf20, 42199, 0x00002d08, 128);

// 0x07002D88 - 0x07002E88
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002D88, 0x0042cf20, 42199, 0x00002d88, 256);

// 0x07002E88 - 0x07002F68
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002E88, 0x0042cf20, 42199, 0x00002e88, 224);

// 0x07002F68 - 0x07003068
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07002F68, 0x0042cf20, 42199, 0x00002f68, 256);

// 0x07003068 - 0x07003158
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003068, 0x0042cf20, 42199, 0x00003068, 240);

// 0x07003158 - 0x07003258
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003158, 0x0042cf20, 42199, 0x00003158, 256);

// 0x07003258 - 0x07003288
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003258, 0x0042cf20, 42199, 0x00003258, 48);

// 0x07003288 - 0x07003378
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003288, 0x0042cf20, 42199, 0x00003288, 240);

// 0x07003378 - 0x07003468
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003378, 0x0042cf20, 42199, 0x00003378, 240);

// 0x07003468 - 0x07003558
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003468, 0x0042cf20, 42199, 0x00003468, 240);

// 0x07003558 - 0x07003648
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003558, 0x0042cf20, 42199, 0x00003558, 240);

// 0x07003648 - 0x07003738
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003648, 0x0042cf20, 42199, 0x00003648, 240);

// 0x07003738 - 0x07003838
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003738, 0x0042cf20, 42199, 0x00003738, 256);

// 0x07003838 - 0x07003928
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003838, 0x0042cf20, 42199, 0x00003838, 240);

// 0x07003928 - 0x07003A08
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003928, 0x0042cf20, 42199, 0x00003928, 224);

// 0x07003A08 - 0x07003AF8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003A08, 0x0042cf20, 42199, 0x00003a08, 240);

// 0x07003AF8 - 0x07003BE8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003AF8, 0x0042cf20, 42199, 0x00003af8, 240);

// 0x07003BE8 - 0x07003CD8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003BE8, 0x0042cf20, 42199, 0x00003be8, 240);

// 0x07003CD8 - 0x07003DC8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003CD8, 0x0042cf20, 42199, 0x00003cd8, 240);

// 0x07003DC8 - 0x07003EB8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003DC8, 0x0042cf20, 42199, 0x00003dc8, 240);

// 0x07003EB8 - 0x07003FA8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003EB8, 0x0042cf20, 42199, 0x00003eb8, 240);

// 0x07003FA8 - 0x07004098
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07003FA8, 0x0042cf20, 42199, 0x00003fa8, 240);

// 0x07004098 - 0x07004188
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004098, 0x0042cf20, 42199, 0x00004098, 240);

// 0x07004188 - 0x07004278
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004188, 0x0042cf20, 42199, 0x00004188, 240);

// 0x07004278 - 0x07004378
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004278, 0x0042cf20, 42199, 0x00004278, 256);

// 0x07004378 - 0x07004478
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004378, 0x0042cf20, 42199, 0x00004378, 256);

// 0x07004478 - 0x07004578
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004478, 0x0042cf20, 42199, 0x00004478, 256);

// 0x07004578 - 0x07004658
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004578, 0x0042cf20, 42199, 0x00004578, 224);

// 0x07004658 - 0x07004738
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004658, 0x0042cf20, 42199, 0x00004658, 224);

// 0x07004738 - 0x07004838
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004738, 0x0042cf20, 42199, 0x00004738, 256);

// 0x07004838 - 0x07004918
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004838, 0x0042cf20, 42199, 0x00004838, 224);

// 0x07004918 - 0x07004A08
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004918, 0x0042cf20, 42199, 0x00004918, 240);

// 0x07004A08 - 0x07004B08
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004A08, 0x0042cf20, 42199, 0x00004a08, 256);

// 0x07004B08 - 0x07004C08
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004B08, 0x0042cf20, 42199, 0x00004b08, 256);

// 0x07004C08 - 0x07004CB8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004C08, 0x0042cf20, 42199, 0x00004c08, 176);

// 0x07004CB8 - 0x07004DA8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004CB8, 0x0042cf20, 42199, 0x00004cb8, 240);

// 0x07004DA8 - 0x07004E98
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004DA8, 0x0042cf20, 42199, 0x00004da8, 240);

// 0x07004E98 - 0x07004F88
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004E98, 0x0042cf20, 42199, 0x00004e98, 240);

// 0x07004F88 - 0x07005078
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07004F88, 0x0042cf20, 42199, 0x00004f88, 240);

// 0x07005078 - 0x07005168
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005078, 0x0042cf20, 42199, 0x00005078, 240);

// 0x07005168 - 0x07005258
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005168, 0x0042cf20, 42199, 0x00005168, 240);

// 0x07005258 - 0x07005348
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005258, 0x0042cf20, 42199, 0x00005258, 240);

// 0x07005348 - 0x07005438
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005348, 0x0042cf20, 42199, 0x00005348, 240);

// 0x07005438 - 0x07005528
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005438, 0x0042cf20, 42199, 0x00005438, 240);

// 0x07005528 - 0x07005618
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005528, 0x0042cf20, 42199, 0x00005528, 240);

// 0x07005618 - 0x07005708
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005618, 0x0042cf20, 42199, 0x00005618, 240);

// 0x07005708 - 0x070057B8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005708, 0x0042cf20, 42199, 0x00005708, 176);

// 0x070057B8 - 0x070058B8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070057B8, 0x0042cf20, 42199, 0x000057b8, 256);

// 0x070058B8 - 0x070059A8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070058B8, 0x0042cf20, 42199, 0x000058b8, 240);

// 0x070059A8 - 0x07005A88
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070059A8, 0x0042cf20, 42199, 0x000059a8, 224);

// 0x07005A88 - 0x07005B88
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005A88, 0x0042cf20, 42199, 0x00005a88, 256);

// 0x07005B88 - 0x07005C78
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005B88, 0x0042cf20, 42199, 0x00005b88, 240);

// 0x07005C78 - 0x07005D58
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005C78, 0x0042cf20, 42199, 0x00005c78, 224);

// 0x07005D58 - 0x07005E48
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005D58, 0x0042cf20, 42199, 0x00005d58, 240);

// 0x07005E48 - 0x07005F28
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005E48, 0x0042cf20, 42199, 0x00005e48, 224);

// 0x07005F28 - 0x07006018
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07005F28, 0x0042cf20, 42199, 0x00005f28, 240);

// 0x07006018 - 0x07006118
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006018, 0x0042cf20, 42199, 0x00006018, 256);

// 0x07006118 - 0x07006208
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006118, 0x0042cf20, 42199, 0x00006118, 240);

// 0x07006208 - 0x070062F8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006208, 0x0042cf20, 42199, 0x00006208, 240);

// 0x070062F8 - 0x07006378
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070062F8, 0x0042cf20, 42199, 0x000062f8, 128);

// 0x07006378 - 0x07006468
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006378, 0x0042cf20, 42199, 0x00006378, 240);

// 0x07006468 - 0x07006558
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006468, 0x0042cf20, 42199, 0x00006468, 240);

// 0x07006558 - 0x07006648
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006558, 0x0042cf20, 42199, 0x00006558, 240);

// 0x07006648 - 0x07006738
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006648, 0x0042cf20, 42199, 0x00006648, 240);

// 0x07006738 - 0x07006838
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006738, 0x0042cf20, 42199, 0x00006738, 256);

// 0x07006838 - 0x07006918
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006838, 0x0042cf20, 42199, 0x00006838, 224);

// 0x07006918 - 0x07006A08
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006918, 0x0042cf20, 42199, 0x00006918, 240);

// 0x07006A08 - 0x07006AF8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006A08, 0x0042cf20, 42199, 0x00006a08, 240);

// 0x07006AF8 - 0x07006BE8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006AF8, 0x0042cf20, 42199, 0x00006af8, 240);

// 0x07006BE8 - 0x07006CD8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006BE8, 0x0042cf20, 42199, 0x00006be8, 240);

// 0x07006CD8 - 0x07006DC8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006CD8, 0x0042cf20, 42199, 0x00006cd8, 240);

// 0x07006DC8 - 0x07006EB8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006DC8, 0x0042cf20, 42199, 0x00006dc8, 240);

// 0x07006EB8 - 0x07006EF8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006EB8, 0x0042cf20, 42199, 0x00006eb8, 64);

// 0x07006EF8 - 0x07006FE8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006EF8, 0x0042cf20, 42199, 0x00006ef8, 240);

// 0x07006FE8 - 0x070070D8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07006FE8, 0x0042cf20, 42199, 0x00006fe8, 240);

// 0x070070D8 - 0x070071D8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070070D8, 0x0042cf20, 42199, 0x000070d8, 256);

// 0x070071D8 - 0x07007218
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070071D8, 0x0042cf20, 42199, 0x000071d8, 64);

// 0x07007218 - 0x07007318
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007218, 0x0042cf20, 42199, 0x00007218, 256);

// 0x07007318 - 0x070073F8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007318, 0x0042cf20, 42199, 0x00007318, 224);

// 0x070073F8 - 0x070074E8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070073F8, 0x0042cf20, 42199, 0x000073f8, 240);

// 0x070074E8 - 0x070075E8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070074E8, 0x0042cf20, 42199, 0x000074e8, 256);

// 0x070075E8 - 0x070076C8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070075E8, 0x0042cf20, 42199, 0x000075e8, 224);

// 0x070076C8 - 0x070077C8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070076C8, 0x0042cf20, 42199, 0x000076c8, 256);

// 0x070077C8 - 0x070078C8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070077C8, 0x0042cf20, 42199, 0x000077c8, 256);

// 0x070078C8 - 0x070079C8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070078C8, 0x0042cf20, 42199, 0x000078c8, 256);

// 0x070079C8 - 0x07007AC8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070079C8, 0x0042cf20, 42199, 0x000079c8, 256);

// 0x07007AC8 - 0x07007BA8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007AC8, 0x0042cf20, 42199, 0x00007ac8, 224);

// 0x07007BA8 - 0x07007C88
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007BA8, 0x0042cf20, 42199, 0x00007ba8, 224);

// 0x07007C88 - 0x07007D78
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007C88, 0x0042cf20, 42199, 0x00007c88, 240);

// 0x07007D78 - 0x07007E68
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007D78, 0x0042cf20, 42199, 0x00007d78, 240);

// 0x07007E68 - 0x07007F48
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007E68, 0x0042cf20, 42199, 0x00007e68, 224);

// 0x07007F48 - 0x07008038
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07007F48, 0x0042cf20, 42199, 0x00007f48, 240);

// 0x07008038 - 0x07008128
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008038, 0x0042cf20, 42199, 0x00008038, 240);

// 0x07008128 - 0x07008208
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008128, 0x0042cf20, 42199, 0x00008128, 224);

// 0x07008208 - 0x070082F8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008208, 0x0042cf20, 42199, 0x00008208, 240);

// 0x070082F8 - 0x07008368
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070082F8, 0x0042cf20, 42199, 0x000082f8, 112);

// 0x07008368 - 0x07008458
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008368, 0x0042cf20, 42199, 0x00008368, 240);

// 0x07008458 - 0x07008558
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008458, 0x0042cf20, 42199, 0x00008458, 256);

// 0x07008558 - 0x07008658
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008558, 0x0042cf20, 42199, 0x00008558, 256);

// 0x07008658 - 0x07008748
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008658, 0x0042cf20, 42199, 0x00008658, 240);

// 0x07008748 - 0x07008848
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008748, 0x0042cf20, 42199, 0x00008748, 256);

// 0x07008848 - 0x070088A8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_07008848, 0x0042cf20, 42199, 0x00008848, 96);

// 0x070088A8 - 0x070089A8
ROM_ASSET_LOAD_VTX(ttc_seg7_vertex_070088A8, 0x0042cf20, 42199, 0x000088a8, 256);

// 0x070089A8 - 0x07008CD8
static const Gfx ttc_seg7_dl_070089A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttc_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 64 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_07001000.l, 1),
    gsSPLight(&ttc_seg7_lights_07001000.a, 2),
    gsSPVertex(ttc_seg7_vertex_07001078, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001168, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001258, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001348, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001438, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001528, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001618, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001708, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_070017F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_070018E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_070019D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001AC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008CD8 - 0x07008DD0
static const Gfx ttc_seg7_dl_07008CD8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09007800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 64 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_07001BB8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 11, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001CB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 3,  4,  0, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14,  7, 0x0),
    gsSP1Triangle(13,  7,  6, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001DA8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008DD0 - 0x07009278
static const Gfx ttc_seg7_dl_07008DD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09007000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_07001018.l, 1),
    gsSPLight(&ttc_seg7_lights_07001018.a, 2),
    gsSPVertex(ttc_seg7_vertex_07001E38, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&ttc_seg7_lights_07001000.l, 1),
    gsSPLight(&ttc_seg7_lights_07001000.a, 2),
    gsSPVertex(ttc_seg7_vertex_07001E78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  8,  2,  9, 0x0),
    gsSP2Triangles( 8,  0,  2, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07001F78, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 6,  1,  7, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8, 13,  9, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002058, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(12, 14, 15, 0x0, 12, 15, 10, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002158, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002248, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9,  5, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002348, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  1,  9, 0x0,  8, 10,  1, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002428, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002528, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0, 14, 15, 11, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002628, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14,  5,  1, 0x0, 14, 15,  5, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002728, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 6,  4,  5, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles( 8, 13, 14, 0x0,  8, 14, 15, 0x0),
    gsSP1Triangle( 8, 15, 11, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002828, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0,  4,  6, 10, 0x0),
    gsSP2Triangles(10,  6,  8, 0x0,  6, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14,  8, 12, 0x0),
    gsSP2Triangles(14, 10,  8, 0x0,  8, 15, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002928, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 3,  5,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002A28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002B28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10,  7, 0x0,  7, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002C28, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  9, 12, 0x0),
    gsSP1Triangle( 9, 13, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009278 - 0x07009480
static const Gfx ttc_seg7_dl_07009278[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09008400),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_07001030.l, 1),
    gsSPLight(&ttc_seg7_lights_07001030.a, 2),
    gsSPVertex(ttc_seg7_vertex_07002D08, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttc_seg7_lights_07001000.l, 1),
    gsSPLight(&ttc_seg7_lights_07001000.a, 2),
    gsSPVertex(ttc_seg7_vertex_07002D88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11,  0, 12, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002E88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 3,  7,  4, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 1,  7,  6, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  8, 13, 11, 0x0),
    gsSP1Triangle( 8, 10, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07002F68, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  8,  4, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003068, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003158, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 8,  4,  7, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 4,  9,  5, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003258, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009480 - 0x07009A88
static const Gfx ttc_seg7_dl_07009480[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09003800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_07003288, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003378, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003468, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003558, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003648, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003738, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003838, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003928, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003AF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003BE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003CD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003DC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003EB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07003FA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004098, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004188, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004278, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  6,  7,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004378, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004478, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8, 13,  9, 0x0),
    gsSP2Triangles( 7, 14,  8, 0x0, 14, 15,  8, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004578, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004658, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004738, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  0,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009A88 - 0x07009BF0
static const Gfx ttc_seg7_dl_07009A88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09006800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_07004838, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 4,  8,  7, 0x0,  4,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004A08, 16, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 3,  7,  6, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0,  0,  2, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004B08, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004C08, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009BF0 - 0x07009F00
static const Gfx ttc_seg7_dl_07009BF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09002800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_07004CB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004DA8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004E98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07004F88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005078, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005168, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005258, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005348, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005438, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005528, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005618, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005708, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009F00 - 0x0700A2C8
static const Gfx ttc_seg7_dl_07009F00[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09001000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_070057B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  0,  3, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles(10,  8, 11, 0x0,  7, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0, 12, 15, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_070058B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  6,  4, 0x0),
    gsSP2Triangles( 1,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  0,  2,  8, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 10, 14, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_070059A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13,  2,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005A88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  5,  9,  8, 0x0),
    gsSP2Triangles( 5, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 9, 14, 15, 0x0,  9, 15,  8, 0x0),
    gsSP1Triangle(11, 15, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005B88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005C78, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  1,  6,  5, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10, 11,  0, 0x0),
    gsSP1Triangle(10, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005D58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  1,  9, 0x0,  8,  5,  1, 0x0),
    gsSP2Triangles( 8, 10,  5, 0x0,  8, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005E48, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07005F28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9,  6,  8, 0x0, 10,  1, 11, 0x0),
    gsSP2Triangles(10,  2,  1, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006018, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  4,  7,  3, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  0,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 15,  9, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006118, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006208, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_070062F8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A2C8 - 0x0700A600
static const Gfx ttc_seg7_dl_0700A2C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09003000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_07006378, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006468, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006558, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006648, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006738, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(11, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006838, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006AF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006BE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006CD8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006DC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006EB8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A600 - 0x0700A700
static const Gfx ttc_seg7_dl_0700A600[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09002000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_07006EF8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07006FE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_070070D8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_070071D8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A700 - 0x0700ACD8
static const Gfx ttc_seg7_dl_0700A700[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09008000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 8 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_07007218, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07007318, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_070073F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14,  0, 0x0),
    gsSPVertex(ttc_seg7_vertex_070074E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_070075E8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  8, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_070076C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(12, 15, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_070077C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 15, 11, 0x0),
    gsSPVertex(ttc_seg7_vertex_070078C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSP1Triangle(13, 15, 10, 0x0),
    gsSPVertex(ttc_seg7_vertex_070079C8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  3, 12,  4, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07007AC8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  7, 13,  8, 0x0),
    gsSPVertex(ttc_seg7_vertex_07007BA8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  6,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_07007C88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle( 4, 14,  5, 0x0),
    gsSPVertex(ttc_seg7_vertex_07007D78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 1, 14,  2, 0x0),
    gsSPVertex(ttc_seg7_vertex_07007E68, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07007F48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008038, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 3,  5,  2, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008128, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008208, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_070082F8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPLight(&ttc_seg7_lights_07001048.l, 1),
    gsSPLight(&ttc_seg7_lights_07001048.a, 2),
    gsSPVertex(ttc_seg7_vertex_07008368, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14,  0,  2, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008458, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008558, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008658, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  5,  4, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008748, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15,  0,  2, 0x0),
    gsSPVertex(ttc_seg7_vertex_07008848, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700ACD8 - 0x0700AD38
static const Gfx ttc_seg7_dl_0700ACD8[] = {
    gsSPLight(&ttc_seg7_lights_07001060.l, 1),
    gsSPLight(&ttc_seg7_lights_07001060.a, 2),
    gsSPVertex(ttc_seg7_vertex_070088A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AD38 - 0x0700AED8
const Gfx ttc_seg7_dl_0700AD38[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_070089A8),
    gsSPDisplayList(ttc_seg7_dl_07008CD8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_07008DD0),
    gsSPDisplayList(ttc_seg7_dl_07009278),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_07009480),
    gsSPDisplayList(ttc_seg7_dl_07009A88),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_07009BF0),
    gsSPDisplayList(ttc_seg7_dl_07009F00),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_0700A2C8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_0700A600),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_dl_0700A700),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(ttc_seg7_dl_0700ACD8),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
