#include "pc/rom_assets.h"
// 0x07001800 - 0x07001818
static const Lights1 wmotr_seg7_lights_07001800 = gdSPDefLights1(
    0xbf, 0xbf, 0xbf,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07001818 - 0x07001830
static const Lights1 wmotr_seg7_lights_07001818 = gdSPDefLights1(
    0x72, 0x72, 0x72,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x07001830 - 0x07001920
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001830, 0x004c4320, 38405, 0x00001830, 240);

// 0x07001920 - 0x07001A10
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001920, 0x004c4320, 38405, 0x00001920, 240);

// 0x07001A10 - 0x07001B00
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001A10, 0x004c4320, 38405, 0x00001a10, 240);

// 0x07001B00 - 0x07001BF0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001B00, 0x004c4320, 38405, 0x00001b00, 240);

// 0x07001BF0 - 0x07001CE0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001BF0, 0x004c4320, 38405, 0x00001bf0, 240);

// 0x07001CE0 - 0x07001DD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001CE0, 0x004c4320, 38405, 0x00001ce0, 240);

// 0x07001DD0 - 0x07001EC0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001DD0, 0x004c4320, 38405, 0x00001dd0, 240);

// 0x07001EC0 - 0x07001FB0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001EC0, 0x004c4320, 38405, 0x00001ec0, 240);

// 0x07001FB0 - 0x07002010
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07001FB0, 0x004c4320, 38405, 0x00001fb0, 96);

// 0x07002010 - 0x07002100
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002010, 0x004c4320, 38405, 0x00002010, 240);

// 0x07002100 - 0x070021F0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002100, 0x004c4320, 38405, 0x00002100, 240);

// 0x070021F0 - 0x070022E0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070021F0, 0x004c4320, 38405, 0x000021f0, 240);

// 0x070022E0 - 0x070023D0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070022E0, 0x004c4320, 38405, 0x000022e0, 240);

// 0x070023D0 - 0x07002450
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070023D0, 0x004c4320, 38405, 0x000023d0, 128);

// 0x07002450 - 0x07002540
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002450, 0x004c4320, 38405, 0x00002450, 240);

// 0x07002540 - 0x07002630
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002540, 0x004c4320, 38405, 0x00002540, 240);

// 0x07002630 - 0x07002670
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002630, 0x004c4320, 38405, 0x00002630, 64);

// 0x07002670 - 0x07002770
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002670, 0x004c4320, 38405, 0x00002670, 256);

// 0x07002770 - 0x07002870
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002770, 0x004c4320, 38405, 0x00002770, 256);

// 0x07002870 - 0x07002970
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002870, 0x004c4320, 38405, 0x00002870, 256);

// 0x07002970 - 0x07002A50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002970, 0x004c4320, 38405, 0x00002970, 224);

// 0x07002A50 - 0x07002B50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002A50, 0x004c4320, 38405, 0x00002a50, 256);

// 0x07002B50 - 0x07002C50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002B50, 0x004c4320, 38405, 0x00002b50, 256);

// 0x07002C50 - 0x07002D50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002C50, 0x004c4320, 38405, 0x00002c50, 256);

// 0x07002D50 - 0x07002E50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002D50, 0x004c4320, 38405, 0x00002d50, 256);

// 0x07002E50 - 0x07002F50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002E50, 0x004c4320, 38405, 0x00002e50, 256);

// 0x07002F50 - 0x07003050
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07002F50, 0x004c4320, 38405, 0x00002f50, 256);

// 0x07003050 - 0x07003150
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003050, 0x004c4320, 38405, 0x00003050, 256);

// 0x07003150 - 0x07003240
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003150, 0x004c4320, 38405, 0x00003150, 240);

// 0x07003240 - 0x07003340
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003240, 0x004c4320, 38405, 0x00003240, 256);

// 0x07003340 - 0x07003440
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003340, 0x004c4320, 38405, 0x00003340, 256);

// 0x07003440 - 0x07003540
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003440, 0x004c4320, 38405, 0x00003440, 256);

// 0x07003540 - 0x07003620
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003540, 0x004c4320, 38405, 0x00003540, 224);

// 0x07003620 - 0x07003720
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003620, 0x004c4320, 38405, 0x00003620, 256);

// 0x07003720 - 0x07003820
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003720, 0x004c4320, 38405, 0x00003720, 256);

// 0x07003820 - 0x07003920
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003820, 0x004c4320, 38405, 0x00003820, 256);

// 0x07003920 - 0x07003A20
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003920, 0x004c4320, 38405, 0x00003920, 256);

// 0x07003A20 - 0x07003B20
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003A20, 0x004c4320, 38405, 0x00003a20, 256);

// 0x07003B20 - 0x07003C20
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003B20, 0x004c4320, 38405, 0x00003b20, 256);

// 0x07003C20 - 0x07003D10
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003C20, 0x004c4320, 38405, 0x00003c20, 240);

// 0x07003D10 - 0x07003E00
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003D10, 0x004c4320, 38405, 0x00003d10, 240);

// 0x07003E00 - 0x07003EF0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003E00, 0x004c4320, 38405, 0x00003e00, 240);

// 0x07003EF0 - 0x07003FD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003EF0, 0x004c4320, 38405, 0x00003ef0, 224);

// 0x07003FD0 - 0x070040C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07003FD0, 0x004c4320, 38405, 0x00003fd0, 240);

// 0x070040C0 - 0x070041C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070040C0, 0x004c4320, 38405, 0x000040c0, 256);

// 0x070041C0 - 0x070042C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070041C0, 0x004c4320, 38405, 0x000041c0, 256);

// 0x070042C0 - 0x070043C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070042C0, 0x004c4320, 38405, 0x000042c0, 256);

// 0x070043C0 - 0x070044C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070043C0, 0x004c4320, 38405, 0x000043c0, 256);

// 0x070044C0 - 0x070045C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070044C0, 0x004c4320, 38405, 0x000044c0, 256);

// 0x070045C0 - 0x070046C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070045C0, 0x004c4320, 38405, 0x000045c0, 256);

// 0x070046C0 - 0x070047C0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070046C0, 0x004c4320, 38405, 0x000046c0, 256);

// 0x070047C0 - 0x070048B0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070047C0, 0x004c4320, 38405, 0x000047c0, 240);

// 0x070048B0 - 0x070049B0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070048B0, 0x004c4320, 38405, 0x000048b0, 256);

// 0x070049B0 - 0x07004AB0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070049B0, 0x004c4320, 38405, 0x000049b0, 256);

// 0x07004AB0 - 0x07004BB0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07004AB0, 0x004c4320, 38405, 0x00004ab0, 256);

// 0x07004BB0 - 0x07004CA0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07004BB0, 0x004c4320, 38405, 0x00004bb0, 240);

// 0x07004CA0 - 0x07004DA0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07004CA0, 0x004c4320, 38405, 0x00004ca0, 256);

// 0x07004DA0 - 0x07004EA0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07004DA0, 0x004c4320, 38405, 0x00004da0, 256);

// 0x07004EA0 - 0x07004FA0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07004EA0, 0x004c4320, 38405, 0x00004ea0, 256);

// 0x07004FA0 - 0x070050A0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07004FA0, 0x004c4320, 38405, 0x00004fa0, 256);

// 0x070050A0 - 0x07005190
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070050A0, 0x004c4320, 38405, 0x000050a0, 240);

// 0x07005190 - 0x07005290
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005190, 0x004c4320, 38405, 0x00005190, 256);

// 0x07005290 - 0x07005390
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005290, 0x004c4320, 38405, 0x00005290, 256);

// 0x07005390 - 0x07005490
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005390, 0x004c4320, 38405, 0x00005390, 256);

// 0x07005490 - 0x07005590
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005490, 0x004c4320, 38405, 0x00005490, 256);

// 0x07005590 - 0x07005690
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005590, 0x004c4320, 38405, 0x00005590, 256);

// 0x07005690 - 0x07005790
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005690, 0x004c4320, 38405, 0x00005690, 256);

// 0x07005790 - 0x07005890
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005790, 0x004c4320, 38405, 0x00005790, 256);

// 0x07005890 - 0x07005990
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005890, 0x004c4320, 38405, 0x00005890, 256);

// 0x07005990 - 0x07005A90
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005990, 0x004c4320, 38405, 0x00005990, 256);

// 0x07005A90 - 0x07005B80
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005A90, 0x004c4320, 38405, 0x00005a90, 240);

// 0x07005B80 - 0x07005C70
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005B80, 0x004c4320, 38405, 0x00005b80, 240);

// 0x07005C70 - 0x07005D60
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005C70, 0x004c4320, 38405, 0x00005c70, 240);

// 0x07005D60 - 0x07005E50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005D60, 0x004c4320, 38405, 0x00005d60, 240);

// 0x07005E50 - 0x07005F50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005E50, 0x004c4320, 38405, 0x00005e50, 256);

// 0x07005F50 - 0x07006050
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07005F50, 0x004c4320, 38405, 0x00005f50, 256);

// 0x07006050 - 0x07006150
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006050, 0x004c4320, 38405, 0x00006050, 256);

// 0x07006150 - 0x07006240
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006150, 0x004c4320, 38405, 0x00006150, 240);

// 0x07006240 - 0x07006330
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006240, 0x004c4320, 38405, 0x00006240, 240);

// 0x07006330 - 0x07006420
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006330, 0x004c4320, 38405, 0x00006330, 240);

// 0x07006420 - 0x07006500
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006420, 0x004c4320, 38405, 0x00006420, 224);

// 0x07006500 - 0x07006600
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006500, 0x004c4320, 38405, 0x00006500, 256);

// 0x07006600 - 0x070066F0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006600, 0x004c4320, 38405, 0x00006600, 240);

// 0x070066F0 - 0x070067F0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070066F0, 0x004c4320, 38405, 0x000066f0, 256);

// 0x070067F0 - 0x070068E0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070067F0, 0x004c4320, 38405, 0x000067f0, 240);

// 0x070068E0 - 0x070069E0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070068E0, 0x004c4320, 38405, 0x000068e0, 256);

// 0x070069E0 - 0x07006AE0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070069E0, 0x004c4320, 38405, 0x000069e0, 256);

// 0x07006AE0 - 0x07006BE0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006AE0, 0x004c4320, 38405, 0x00006ae0, 256);

// 0x07006BE0 - 0x07006CD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006BE0, 0x004c4320, 38405, 0x00006be0, 240);

// 0x07006CD0 - 0x07006DD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006CD0, 0x004c4320, 38405, 0x00006cd0, 256);

// 0x07006DD0 - 0x07006EB0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006DD0, 0x004c4320, 38405, 0x00006dd0, 224);

// 0x07006EB0 - 0x07006FB0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006EB0, 0x004c4320, 38405, 0x00006eb0, 256);

// 0x07006FB0 - 0x070070A0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07006FB0, 0x004c4320, 38405, 0x00006fb0, 240);

// 0x070070A0 - 0x070071A0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070070A0, 0x004c4320, 38405, 0x000070a0, 256);

// 0x070071A0 - 0x070072A0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070071A0, 0x004c4320, 38405, 0x000071a0, 256);

// 0x070072A0 - 0x070073A0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070072A0, 0x004c4320, 38405, 0x000072a0, 256);

// 0x070073A0 - 0x070074A0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070073A0, 0x004c4320, 38405, 0x000073a0, 256);

// 0x070074A0 - 0x07007590
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070074A0, 0x004c4320, 38405, 0x000074a0, 240);

// 0x07007590 - 0x07007690
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007590, 0x004c4320, 38405, 0x00007590, 256);

// 0x07007690 - 0x07007790
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007690, 0x004c4320, 38405, 0x00007690, 256);

// 0x07007790 - 0x07007890
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007790, 0x004c4320, 38405, 0x00007790, 256);

// 0x07007890 - 0x07007980
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007890, 0x004c4320, 38405, 0x00007890, 240);

// 0x07007980 - 0x07007A60
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007980, 0x004c4320, 38405, 0x00007980, 224);

// 0x07007A60 - 0x07007B60
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007A60, 0x004c4320, 38405, 0x00007a60, 256);

// 0x07007B60 - 0x07007C60
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007B60, 0x004c4320, 38405, 0x00007b60, 256);

// 0x07007C60 - 0x07007D50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007C60, 0x004c4320, 38405, 0x00007c60, 240);

// 0x07007D50 - 0x07007E50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007D50, 0x004c4320, 38405, 0x00007d50, 256);

// 0x07007E50 - 0x07007F50
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007E50, 0x004c4320, 38405, 0x00007e50, 256);

// 0x07007F50 - 0x07008040
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07007F50, 0x004c4320, 38405, 0x00007f50, 240);

// 0x07008040 - 0x07008140
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008040, 0x004c4320, 38405, 0x00008040, 256);

// 0x07008140 - 0x07008220
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008140, 0x004c4320, 38405, 0x00008140, 224);

// 0x07008220 - 0x07008320
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008220, 0x004c4320, 38405, 0x00008220, 256);

// 0x07008320 - 0x07008420
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008320, 0x004c4320, 38405, 0x00008320, 256);

// 0x07008420 - 0x07008510
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008420, 0x004c4320, 38405, 0x00008420, 240);

// 0x07008510 - 0x07008610
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008510, 0x004c4320, 38405, 0x00008510, 256);

// 0x07008610 - 0x07008700
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008610, 0x004c4320, 38405, 0x00008610, 240);

// 0x07008700 - 0x07008800
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008700, 0x004c4320, 38405, 0x00008700, 256);

// 0x07008800 - 0x070088F0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008800, 0x004c4320, 38405, 0x00008800, 240);

// 0x070088F0 - 0x070089F0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070088F0, 0x004c4320, 38405, 0x000088f0, 256);

// 0x070089F0 - 0x07008AD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_070089F0, 0x004c4320, 38405, 0x000089f0, 224);

// 0x07008AD0 - 0x07008BD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008AD0, 0x004c4320, 38405, 0x00008ad0, 256);

// 0x07008BD0 - 0x07008CD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008BD0, 0x004c4320, 38405, 0x00008bd0, 256);

// 0x07008CD0 - 0x07008DD0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008CD0, 0x004c4320, 38405, 0x00008cd0, 256);

// 0x07008DD0 - 0x07008EB0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008DD0, 0x004c4320, 38405, 0x00008dd0, 224);

// 0x07008EB0 - 0x07008EF0
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07008EB0, 0x004c4320, 38405, 0x00008eb0, 64);

// 0x07008EF0 - 0x07009148
static const Gfx wmotr_seg7_dl_07008EF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wmotr_seg7_texture_07001600),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 8 * 32 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wmotr_seg7_lights_07001800.l, 1),
    gsSPLight(&wmotr_seg7_lights_07001800.a, 2),
    gsSPVertex(wmotr_seg7_vertex_07001830, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001920, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001A10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001B00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001BF0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001CE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001DD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001EC0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07001FB0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009148 - 0x070092A0
static const Gfx wmotr_seg7_dl_07009148[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wmotr_seg7_texture_07000800),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 16 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wmotr_seg7_lights_07001818.l, 1),
    gsSPLight(&wmotr_seg7_lights_07001818.a, 2),
    gsSPVertex(wmotr_seg7_vertex_07002010, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002100, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070021F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070022E0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070023D0, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070092A0 - 0x07009458
static const Gfx wmotr_seg7_dl_070092A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wmotr_seg7_texture_07000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wmotr_seg7_vertex_07002450, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002540, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002630, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPLight(&wmotr_seg7_lights_07001800.l, 1),
    gsSPLight(&wmotr_seg7_lights_07001800.a, 2),
    gsSPVertex(wmotr_seg7_vertex_07002670, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  7,  2,  8, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0, 13, 14,  0, 0x0),
    gsSP2Triangles(13,  0, 12, 0x0, 14,  1,  0, 0x0),
    gsSP2Triangles(15, 13, 12, 0x0, 11, 15, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002770, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 4, 10, 11, 0x0,  4, 11,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  7,  9,  6, 0x0),
    gsSP2Triangles(12, 10,  4, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles(14, 15, 12, 0x0, 15, 13, 12, 0x0),
    gsSP2Triangles(14, 12,  9, 0x0,  8, 14,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009458 - 0x0700C1F8
static const Gfx wmotr_seg7_dl_07009458[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wmotr_seg7_texture_07000C00),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wmotr_seg7_vertex_07002870, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  6,  7,  2, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  8,  3,  2, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 10, 12, 11, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 14, 15, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002970, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  6,  4,  0, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  7, 0x0, 11,  7, 13, 0x0),
    gsSP2Triangles(12,  8,  7, 0x0, 13,  7, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002A50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 3,  5,  1, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 8,  3,  0, 0x0,  9, 10,  7, 0x0),
    gsSP2Triangles( 6,  7, 10, 0x0,  1,  5, 11, 0x0),
    gsSP2Triangles( 6, 11,  5, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002B50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 6,  0,  4, 0x0,  4,  2,  7, 0x0),
    gsSP2Triangles( 3,  7,  2, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 6,  4,  9, 0x0,  9,  4,  8, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0,  8,  7, 11, 0x0),
    gsSP2Triangles( 3, 10,  7, 0x0, 12,  8, 11, 0x0),
    gsSP2Triangles(11, 10, 13, 0x0, 11, 13, 14, 0x0),
    gsSP2Triangles(15, 11, 14, 0x0, 12, 11, 15, 0x0),
    gsSP1Triangle( 3, 13, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002C50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  4, 0x0),
    gsSP2Triangles( 6,  0,  5, 0x0,  4,  2,  7, 0x0),
    gsSP2Triangles( 3,  7,  2, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 9,  4,  8, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles( 8,  7,  3, 0x0,  8,  3, 10, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0, 11,  8, 10, 0x0),
    gsSP2Triangles(10,  3, 12, 0x0, 13, 12,  3, 0x0),
    gsSP2Triangles( 3, 14, 13, 0x0, 10, 12, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002D50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 7,  6,  4, 0x0,  8,  2,  5, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 5, 11, 12, 0x0,  5,  6, 11, 0x0),
    gsSP2Triangles( 8,  5, 13, 0x0, 13,  5, 12, 0x0),
    gsSP2Triangles( 7, 11,  6, 0x0, 11, 14, 15, 0x0),
    gsSP2Triangles(12, 11, 15, 0x0,  7, 14, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002E50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 2,  3,  7, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles(13,  6, 12, 0x0,  7,  6, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0,  9, 15, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07002F50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  0,  6,  1, 0x0),
    gsSP2Triangles( 7,  6,  0, 0x0,  8,  9,  7, 0x0),
    gsSP2Triangles( 7,  9,  6, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles(11, 10,  8, 0x0, 12, 13, 11, 0x0),
    gsSP2Triangles(11, 13, 10, 0x0, 12, 14, 13, 0x0),
    gsSP1Triangle(15, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003050, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  3,  5,  0, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9,  8,  6, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0, 11, 10,  9, 0x0),
    gsSP2Triangles(12, 13, 11, 0x0, 11, 13, 10, 0x0),
    gsSP2Triangles(14, 15, 12, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003150, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  5,  3,  0, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  8,  9,  7, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0,  1, 13, 12, 0x0),
    gsSP2Triangles( 1,  3, 14, 0x0,  1, 14, 13, 0x0),
    gsSP2Triangles( 9, 11, 14, 0x0,  7,  9, 14, 0x0),
    gsSP2Triangles( 3,  5, 14, 0x0,  5,  7, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003240, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  1,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  1,  8,  9, 0x0),
    gsSP2Triangles( 9,  8,  5, 0x0,  3,  5,  8, 0x0),
    gsSP2Triangles( 9,  5, 10, 0x0,  5,  4, 11, 0x0),
    gsSP2Triangles(10,  5, 11, 0x0,  0,  2, 12, 0x0),
    gsSP2Triangles(13, 14,  2, 0x0, 13,  2, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003340, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  4,  2, 0x0,  2,  1,  6, 0x0),
    gsSP2Triangles( 2,  6,  7, 0x0,  8,  2,  3, 0x0),
    gsSP2Triangles( 5,  9,  4, 0x0,  9,  3,  4, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0, 10,  8,  3, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles( 9, 13, 10, 0x0,  9, 14, 13, 0x0),
    gsSP1Triangle(13, 15, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003440, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  7,  4,  0, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003540, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  4,  5,  2, 0x0),
    gsSP2Triangles( 3,  2,  5, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  8,  3,  6, 0x0),
    gsSP2Triangles( 7,  0,  3, 0x0,  4,  1,  9, 0x0),
    gsSP2Triangles(10,  9,  1, 0x0, 10,  1,  0, 0x0),
    gsSP2Triangles( 4, 11,  5, 0x0,  6,  5, 11, 0x0),
    gsSP2Triangles(12,  6, 13, 0x0,  6, 11, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003620, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 6,  4,  8, 0x0,  9,  6,  7, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0,  8,  4, 10, 0x0),
    gsSP2Triangles(11,  8,  1, 0x0,  7,  8, 11, 0x0),
    gsSP2Triangles( 8, 10,  1, 0x0, 10, 12,  2, 0x0),
    gsSP2Triangles( 1, 10,  2, 0x0,  3, 12, 10, 0x0),
    gsSP2Triangles(11,  1,  0, 0x0,  0,  2, 13, 0x0),
    gsSP2Triangles(13,  2, 14, 0x0,  2, 12, 15, 0x0),
    gsSP2Triangles( 2, 15, 14, 0x0,  3, 15, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003720, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  6,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  5,  2,  7, 0x0),
    gsSP2Triangles( 3,  7,  2, 0x0,  4,  5,  8, 0x0),
    gsSP2Triangles( 5,  7,  9, 0x0,  8,  5,  9, 0x0),
    gsSP2Triangles( 9,  7,  3, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0,  9,  3, 11, 0x0),
    gsSP2Triangles( 3, 12, 13, 0x0, 13, 14,  3, 0x0),
    gsSP2Triangles(11,  3, 14, 0x0, 10, 11, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003820, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 2,  3,  6, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 7,  2,  6, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0, 10,  6, 11, 0x0),
    gsSP2Triangles( 6, 12, 11, 0x0,  6,  5, 12, 0x0),
    gsSP2Triangles( 4, 12,  5, 0x0,  4, 13, 12, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 11, 12, 14, 0x0),
    gsSP2Triangles(10, 11, 15, 0x0, 15, 11, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003920, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles( 9,  2, 10, 0x0,  2, 11, 10, 0x0),
    gsSP2Triangles( 9, 10, 12, 0x0,  7, 13,  8, 0x0),
    gsSP2Triangles(14, 13,  7, 0x0,  7, 15, 12, 0x0),
    gsSP1Triangle( 7,  6, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003A20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  5,  7,  4, 0x0),
    gsSP2Triangles( 8,  9,  6, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0, 13, 10,  8, 0x0),
    gsSP2Triangles(13, 14, 10, 0x0, 15, 14, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003B20, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  5,  7,  4, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9,  8,  6, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0,  9, 11,  8, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 12, 14, 13, 0x0),
    gsSP1Triangle(15, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003C20, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  5,  7,  4, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  9, 11, 13, 0x0),
    gsSP2Triangles(14,  9, 13, 0x0,  7,  8, 10, 0x0),
    gsSP2Triangles( 4,  7, 10, 0x0,  1,  4, 10, 0x0),
    gsSP1Triangle(12,  1, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003D10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  4, 0x0,  1,  4,  6, 0x0),
    gsSP2Triangles( 3,  7,  4, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  6,  7,  9, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0,  7,  8, 10, 0x0),
    gsSP2Triangles( 3, 11,  8, 0x0,  0,  2, 12, 0x0),
    gsSP1Triangle(13, 14,  2, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003E00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 6,  3,  1, 0x0,  1,  7,  8, 0x0),
    gsSP2Triangles( 1,  8,  9, 0x0,  6, 10,  3, 0x0),
    gsSP2Triangles(10, 11,  2, 0x0, 10,  2,  3, 0x0),
    gsSP2Triangles(11,  0,  2, 0x0, 11, 12,  0, 0x0),
    gsSP2Triangles(12,  4,  0, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(10, 14, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003EF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  1,  4, 0x0),
    gsSP2Triangles( 6,  3,  2, 0x0,  7,  6,  2, 0x0),
    gsSP2Triangles( 8,  7,  2, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07003FD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 10,  8,  4, 0x0),
    gsSP2Triangles( 7,  9,  1, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  3, 11,  4, 0x0),
    gsSP2Triangles(10,  4, 11, 0x0,  1,  9, 12, 0x0),
    gsSP2Triangles(10, 12,  9, 0x0,  2,  1, 13, 0x0),
    gsSP2Triangles( 1, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSP1Triangle(10, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070040C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 6,  5,  3, 0x0,  7,  2,  8, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  2,  5,  8, 0x0),
    gsSP2Triangles( 8,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  8,  6, 10, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 12, 11,  6, 0x0),
    gsSP2Triangles(13, 10, 14, 0x0,  9, 10, 13, 0x0),
    gsSP2Triangles(10, 11, 14, 0x0, 14, 11, 15, 0x0),
    gsSP1Triangle(12, 15, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070041C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 2,  4,  6, 0x0,  4,  5,  7, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 8,  5,  9, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 8,  9, 11, 0x0,  7,  8, 12, 0x0),
    gsSP2Triangles(13,  7, 12, 0x0,  6,  7, 13, 0x0),
    gsSP2Triangles(12,  8, 14, 0x0, 11, 14,  8, 0x0),
    gsSP1Triangle(12, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070042C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 2,  3,  7, 0x0,  7,  3,  6, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 11, 10, 0x0, 12, 10, 13, 0x0),
    gsSP2Triangles( 6,  8, 14, 0x0, 15,  6, 14, 0x0),
    gsSP2Triangles( 7,  6, 15, 0x0, 14,  8, 13, 0x0),
    gsSP1Triangle(12, 13,  8, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070043C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  3,  2,  7, 0x0),
    gsSP2Triangles( 7,  2,  6, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 10,  9, 0x0, 11,  9, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  6, 13, 14, 0x0),
    gsSP2Triangles(15,  6, 14, 0x0,  7,  6, 15, 0x0),
    gsSP1Triangle(14, 13, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070044C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  4,  2,  7, 0x0),
    gsSP2Triangles( 7,  2,  6, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle( 6, 13, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070045C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0,  7,  2,  6, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0, 10,  6,  9, 0x0),
    gsSP2Triangles(11,  9, 12, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 15, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070046C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 8, 10,  6, 0x0, 11,  9,  6, 0x0),
    gsSP2Triangles(12, 11,  6, 0x0,  6, 10,  5, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070047C0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 6,  5,  3, 0x0,  7,  8,  6, 0x0),
    gsSP2Triangles( 6,  9,  5, 0x0,  8, 10,  6, 0x0),
    gsSP2Triangles( 6, 10,  9, 0x0,  7, 11,  8, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070048B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  1,  0, 0x0),
    gsSP2Triangles( 5,  6,  1, 0x0,  7,  8,  5, 0x0),
    gsSP2Triangles( 8,  9,  5, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles( 5, 10, 11, 0x0, 11,  6,  5, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0, 14, 13, 12, 0x0),
    gsSP1Triangle(14, 15, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070049B0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  3,  5,  4, 0x0),
    gsSP2Triangles( 3,  6,  5, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  7,  3, 0x0,  9, 10,  8, 0x0),
    gsSP2Triangles( 8, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(14, 15,  9, 0x0,  9, 15, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07004AB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 7,  6,  3, 0x0,  8,  7,  3, 0x0),
    gsSP2Triangles( 3,  5,  1, 0x0,  9,  7,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP2Triangles(14, 11, 10, 0x0, 14, 15, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07004BB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  1,  4,  3, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  8,  3,  6, 0x0),
    gsSP2Triangles( 7,  3,  5, 0x0,  9,  8,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 4, 14,  5, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07004CA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 8,  7, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0,  6,  9, 14, 0x0),
    gsSP2Triangles(15,  6, 14, 0x0, 15,  7,  6, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07004DA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  2,  3, 0x0,  5,  0,  6, 0x0),
    gsSP2Triangles( 0,  7,  6, 0x0,  7,  0,  8, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0, 11,  1, 12, 0x0),
    gsSP2Triangles( 1,  0, 12, 0x0, 13,  6,  7, 0x0),
    gsSP2Triangles(13,  5,  6, 0x0, 14, 13,  9, 0x0),
    gsSP2Triangles( 5, 13, 15, 0x0, 14, 15, 13, 0x0),
    gsSP2Triangles(15, 12,  5, 0x0,  0,  5, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07004EA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  3,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0, 10,  4,  8, 0x0),
    gsSP2Triangles(11,  7, 12, 0x0, 11,  8,  7, 0x0),
    gsSP2Triangles( 2,  5,  3, 0x0,  1,  5,  2, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07004FA0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 3,  2,  5, 0x0,  6,  0,  2, 0x0),
    gsSP2Triangles( 2,  7,  8, 0x0,  4,  9,  2, 0x0),
    gsSP2Triangles( 9,  6,  2, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070050A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  6,  4,  2, 0x0),
    gsSP2Triangles( 5,  4,  7, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9,  2, 0x0,  2, 10,  6, 0x0),
    gsSP2Triangles( 2,  9, 10, 0x0, 11,  5, 12, 0x0),
    gsSP2Triangles(12,  5, 13, 0x0, 13,  5,  7, 0x0),
    gsSP2Triangles( 6, 13,  7, 0x0, 14, 11, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005190, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  2, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11,  8, 10, 0x0, 12, 11, 10, 0x0),
    gsSP2Triangles( 1, 13,  2, 0x0, 14, 15,  5, 0x0),
    gsSP1Triangle(15,  3,  5, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005290, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 7, 14,  8, 0x0, 13, 12, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005390, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 12, 14, 15, 0x0),
    gsSP1Triangle(13, 12, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005490, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0,  9, 12, 11, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005590, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(11, 10, 13, 0x0, 13, 12, 14, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005690, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  4,  9, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(10,  9, 11, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(14, 13, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005790, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 12, 14, 15, 0x0),
    gsSP1Triangle(13, 12, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005890, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 8, 11, 10, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(11, 13, 12, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005990, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 6,  9, 10, 0x0,  6, 10, 11, 0x0),
    gsSP2Triangles( 6, 12,  7, 0x0, 13, 14,  6, 0x0),
    gsSP2Triangles( 6, 11, 15, 0x0,  6, 15, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  3,  8,  0, 0x0),
    gsSP2Triangles( 9, 10,  3, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles( 0, 11, 12, 0x0,  0, 12, 13, 0x0),
    gsSP1Triangle( 0, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005B80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles( 4,  9, 10, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2, 12, 13, 0x0,  2, 13, 14, 0x0),
    gsSP1Triangle( 2, 14,  3, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005C70, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  7,  8,  0, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  7, 10,  8, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005D60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  5,  4, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  3,  4,  7, 0x0),
    gsSP2Triangles( 9,  1,  3, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 10, 12, 0x0, 14, 11, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005E50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  3, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  1,  4, 0x0,  8,  4,  7, 0x0),
    gsSP2Triangles( 5,  4,  9, 0x0, 10,  4,  1, 0x0),
    gsSP2Triangles(11,  1, 12, 0x0, 11, 13,  1, 0x0),
    gsSP2Triangles(13,  2,  1, 0x0,  8, 12,  1, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 14, 15, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07005F50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  9, 12, 0x0),
    gsSP2Triangles( 9,  7, 12, 0x0, 10,  9, 11, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006050, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 2,  8,  7, 0x0,  8,  2,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9, 12, 10, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006150, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 7,  4,  0, 0x0,  4,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  5,  8,  3, 0x0),
    gsSP2Triangles( 9,  0, 10, 0x0,  0,  2, 10, 0x0),
    gsSP2Triangles(11,  0,  9, 0x0, 11,  7,  0, 0x0),
    gsSP2Triangles( 7, 12,  6, 0x0,  7, 13, 12, 0x0),
    gsSP2Triangles(14, 11,  9, 0x0, 13, 11, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006240, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  4,  0,  5, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  8,  5,  6, 0x0),
    gsSP2Triangles( 5,  8,  4, 0x0,  9, 10,  1, 0x0),
    gsSP2Triangles( 9,  1, 11, 0x0,  2,  1, 12, 0x0),
    gsSP2Triangles(12,  1, 10, 0x0, 11,  1,  4, 0x0),
    gsSP1Triangle( 7, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006330, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 1,  8,  3, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 13, 11, 10, 0x0),
    gsSP1Triangle(14,  4,  6, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006420, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  3,  5,  1, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 3,  6,  5, 0x0,  8,  3,  0, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006500, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  8,  2,  9, 0x0),
    gsSP2Triangles(10,  0,  8, 0x0,  9, 11,  8, 0x0),
    gsSP2Triangles(11, 10,  8, 0x0,  2, 12, 13, 0x0),
    gsSP2Triangles( 9,  2, 13, 0x0, 12,  2, 14, 0x0),
    gsSP2Triangles( 2,  1, 14, 0x0,  9, 13, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006600, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  8,  0,  9, 0x0),
    gsSP2Triangles(10,  6,  8, 0x0,  0, 11,  9, 0x0),
    gsSP2Triangles( 0,  2, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070066F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  5,  6,  0, 0x0),
    gsSP2Triangles( 0,  7,  3, 0x0,  0,  6,  7, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 7,  6,  9, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles(10,  3,  7, 0x0,  1,  3, 11, 0x0),
    gsSP2Triangles(11,  3, 10, 0x0,  8, 12,  9, 0x0),
    gsSP2Triangles( 9, 13, 10, 0x0,  9, 12, 14, 0x0),
    gsSP1Triangle(13, 15, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070067F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 7,  6,  3, 0x0,  1,  7,  3, 0x0),
    gsSP2Triangles( 1,  8,  9, 0x0,  7,  1,  9, 0x0),
    gsSP2Triangles( 0,  8,  1, 0x0, 10, 11,  7, 0x0),
    gsSP2Triangles(11,  6,  7, 0x0,  6, 11,  4, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070068E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  6,  9, 0x0, 10,  8,  9, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSP1Triangle(11, 15, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070069E0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  1,  4,  6, 0x0),
    gsSP2Triangles( 5,  1,  0, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0, 11,  7, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006AE0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  3,  1,  5, 0x0),
    gsSP2Triangles( 1,  6,  5, 0x0,  1,  4,  6, 0x0),
    gsSP2Triangles( 3,  7,  8, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 9,  4,  0, 0x0, 10,  4,  9, 0x0),
    gsSP2Triangles(10, 11,  4, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle(13, 15, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006BE0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  0,  6,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 0,  8,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle(13, 11, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006CD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 5,  1,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  5,  8,  7, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8,  4, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSP1Triangle(11, 13, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006DD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 5,  3,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  5,  8,  7, 0x0),
    gsSP2Triangles( 8,  5,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8,  4, 0x0,  7,  9, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006EB0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  7, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 3,  9,  8, 0x0,  9,  3,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9,  5, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 11, 10, 12, 0x0),
    gsSP2Triangles(10, 13, 12, 0x0, 13, 10,  5, 0x0),
    gsSP2Triangles(14, 13,  5, 0x0,  2,  1, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07006FB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  1,  4, 0x0,  2,  3,  5, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  5,  3,  7, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  8,  6,  4, 0x0),
    gsSP2Triangles( 7,  6,  9, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  8,  4, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070070A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0,  9,  8, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0,  7, 14,  8, 0x0),
    gsSP1Triangle(13, 12, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070071A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 5,  8,  7, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles( 9, 12, 11, 0x0, 11, 13, 14, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070072A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 3,  6,  5, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 14, 13, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070073A0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4,  3,  8, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles(15, 14,  6, 0x0, 15,  6,  5, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070074A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0, 11, 12,  0, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0,  1, 13, 14, 0x0),
    gsSP1Triangle( 2,  1, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007590, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  8, 11, 10, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 10, 11, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007690, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 11, 13, 14, 0x0),
    gsSP1Triangle(10, 15, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007790, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0,  8, 12, 11, 0x0),
    gsSP2Triangles( 8, 13, 12, 0x0, 14, 15,  6, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007890, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 3,  8,  7, 0x0,  2,  9,  3, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0,  2, 11, 12, 0x0),
    gsSP2Triangles( 2, 13, 11, 0x0,  2, 14, 13, 0x0),
    gsSP1Triangle( 2, 12,  9, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007980, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  7, 0x0,  3,  8,  6, 0x0),
    gsSP2Triangles( 3,  9,  8, 0x0,  2, 10,  3, 0x0),
    gsSP2Triangles( 3,  7, 11, 0x0,  3, 11,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  2, 12, 10, 0x0),
    gsSP1Triangle( 2, 13, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007A60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  1,  0, 0x0,  7,  6,  0, 0x0),
    gsSP2Triangles( 1,  6,  8, 0x0,  6,  9,  8, 0x0),
    gsSP2Triangles(10,  9,  6, 0x0, 10,  6,  7, 0x0),
    gsSP2Triangles( 1,  8, 11, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007B60, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSP2Triangles( 5,  4,  8, 0x0,  4,  9,  8, 0x0),
    gsSP2Triangles( 7,  9,  4, 0x0, 10,  5,  8, 0x0),
    gsSP2Triangles(11,  5, 10, 0x0, 12,  5, 11, 0x0),
    gsSP2Triangles( 5, 12, 13, 0x0, 14,  5, 13, 0x0),
    gsSP1Triangle( 7,  6, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007C60, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 5,  0,  2, 0x0,  5,  2,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  1,  7,  6, 0x0),
    gsSP2Triangles( 0,  9,  1, 0x0,  1,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(14, 13, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007D50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  7, 0x0,  5,  4,  7, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  9, 10,  6, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0,  5, 11, 12, 0x0),
    gsSP2Triangles( 8,  5, 12, 0x0, 11,  5,  7, 0x0),
    gsSP2Triangles( 1,  0, 13, 0x0, 14,  2, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007E50, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  0, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  6,  8, 0x0),
    gsSP2Triangles( 8,  9,  3, 0x0, 10,  0, 11, 0x0),
    gsSP2Triangles(10,  5,  0, 0x0,  0,  2, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07007F50, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 1,  3,  4, 0x0,  5,  2,  6, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  7,  0,  5, 0x0),
    gsSP2Triangles( 8,  0,  7, 0x0,  0,  9,  3, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0, 10,  5,  6, 0x0),
    gsSP2Triangles(11,  5, 10, 0x0,  5, 11,  7, 0x0),
    gsSP2Triangles(12, 13,  8, 0x0, 12,  8, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008040, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 6,  7,  3, 0x0,  4,  9, 10, 0x0),
    gsSP2Triangles( 5,  4, 10, 0x0,  7, 11,  8, 0x0),
    gsSP2Triangles(12,  1, 13, 0x0,  0, 14,  1, 0x0),
    gsSP2Triangles(14, 13,  1, 0x0, 15,  5, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008140, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  4,  2,  5, 0x0),
    gsSP2Triangles( 1,  5,  2, 0x0,  6,  7,  5, 0x0),
    gsSP2Triangles( 1,  6,  5, 0x0,  1,  8,  9, 0x0),
    gsSP2Triangles( 1,  9,  6, 0x0,  8,  1,  0, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008220, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  4,  3,  7, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  8, 10,  9, 0x0),
    gsSP2Triangles( 9,  1,  0, 0x0, 11,  1,  9, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 12,  1, 13, 0x0),
    gsSP2Triangles( 1, 14, 13, 0x0, 11, 14,  1, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0,  8,  0, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008320, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles( 8, 10, 11, 0x0, 10,  2, 12, 0x0),
    gsSP2Triangles(10, 12, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008420, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 2,  1,  7, 0x0,  2,  7,  4, 0x0),
    gsSP2Triangles( 1,  8,  9, 0x0,  1,  0,  8, 0x0),
    gsSP2Triangles( 7,  1,  9, 0x0, 10,  7,  9, 0x0),
    gsSP2Triangles(10,  4,  7, 0x0,  5,  4, 11, 0x0),
    gsSP2Triangles(11,  4, 10, 0x0,  8, 12,  9, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0,  9, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008510, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  0,  8, 0x0,  2,  8,  0, 0x0),
    gsSP2Triangles( 1, 10,  2, 0x0,  2, 10, 11, 0x0),
    gsSP2Triangles( 2, 11, 12, 0x0,  1,  0, 13, 0x0),
    gsSP2Triangles( 0, 14, 13, 0x0,  7, 14,  0, 0x0),
    gsSP1Triangle(15, 10,  1, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008610, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9,  5, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13,  6, 14, 0x0),
    gsSP1Triangle( 6, 13,  7, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008700, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  3,  4, 0x0,  6,  7,  8, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0,  6, 10, 11, 0x0),
    gsSP2Triangles(12,  6, 11, 0x0, 13,  6, 12, 0x0),
    gsSP2Triangles( 6, 14,  9, 0x0, 14,  6, 13, 0x0),
    gsSP1Triangle(14, 15,  9, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008800, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 0,  3,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 1,  3,  8, 0x0,  8,  3,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13,  9, 14, 0x0),
    gsSP2Triangles(13,  8,  9, 0x0,  5, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070088F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  5,  3,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  4,  0, 0x0),
    gsSP2Triangles(11,  4, 10, 0x0, 11, 12,  4, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_070089F0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  6,  7, 11, 0x0),
    gsSP2Triangles( 4, 12,  7, 0x0, 11,  7, 12, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008AD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  8,  6, 10, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles( 9, 12, 13, 0x0, 11,  9, 13, 0x0),
    gsSP2Triangles(12,  9, 10, 0x0, 13, 12, 14, 0x0),
    gsSP2Triangles(14, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008BD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 4,  2,  6, 0x0,  5,  2,  3, 0x0),
    gsSP2Triangles( 6,  5,  7, 0x0,  7,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  7,  3, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles(11,  9,  3, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008CD0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 5,  7,  9, 0x0,  6,  5,  9, 0x0),
    gsSP2Triangles(10,  7,  8, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 10,  8, 0x0),
    gsSP2Triangles(10, 12, 13, 0x0, 11, 10, 13, 0x0),
    gsSP2Triangles( 2,  1, 14, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008DD0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  0,  4, 0x0,  5,  0,  2, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  4,  0,  6, 0x0),
    gsSP2Triangles( 7,  5,  2, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  9,  7,  2, 0x0),
    gsSP2Triangles( 8,  7,  9, 0x0,  8,  9, 10, 0x0),
    gsSP1Triangle(11, 12, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07008EB0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C1F8 - 0x0700C2A0
const Gfx wmotr_seg7_dl_0700C1F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wmotr_seg7_dl_07008EF0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wmotr_seg7_dl_07009148),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wmotr_seg7_dl_070092A0),
    gsSPDisplayList(wmotr_seg7_dl_07009458),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0700C2A0 - 0x0700C2B8
static const Lights1 wmotr_seg7_lights_0700C2A0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700C2B8 - 0x0700C3B8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C2B8, 0x004c4320, 38405, 0x0000c2b8, 256);

// 0x0700C3B8 - 0x0700C4B8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C3B8, 0x004c4320, 38405, 0x0000c3b8, 256);

// 0x0700C4B8 - 0x0700C5A8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C4B8, 0x004c4320, 38405, 0x0000c4b8, 240);

// 0x0700C5A8 - 0x0700C6A8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C5A8, 0x004c4320, 38405, 0x0000c5a8, 256);

// 0x0700C6A8 - 0x0700C7A8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C6A8, 0x004c4320, 38405, 0x0000c6a8, 256);

// 0x0700C7A8 - 0x0700C8A8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C7A8, 0x004c4320, 38405, 0x0000c7a8, 256);

// 0x0700C8A8 - 0x0700C9A8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C8A8, 0x004c4320, 38405, 0x0000c8a8, 256);

// 0x0700C9A8 - 0x0700CA98
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700C9A8, 0x004c4320, 38405, 0x0000c9a8, 240);

// 0x0700CA98 - 0x0700CB98
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700CA98, 0x004c4320, 38405, 0x0000ca98, 256);

// 0x0700CB98 - 0x0700CC98
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700CB98, 0x004c4320, 38405, 0x0000cb98, 256);

// 0x0700CC98 - 0x0700CD98
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700CC98, 0x004c4320, 38405, 0x0000cc98, 256);

// 0x0700CD98 - 0x0700CE98
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700CD98, 0x004c4320, 38405, 0x0000cd98, 256);

// 0x0700CE98 - 0x0700CF88
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700CE98, 0x004c4320, 38405, 0x0000ce98, 240);

// 0x0700CF88 - 0x0700D088
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700CF88, 0x004c4320, 38405, 0x0000cf88, 256);

// 0x0700D088 - 0x0700D188
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D088, 0x004c4320, 38405, 0x0000d088, 256);

// 0x0700D188 - 0x0700D288
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D188, 0x004c4320, 38405, 0x0000d188, 256);

// 0x0700D288 - 0x0700D378
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D288, 0x004c4320, 38405, 0x0000d288, 240);

// 0x0700D378 - 0x0700D468
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D378, 0x004c4320, 38405, 0x0000d378, 240);

// 0x0700D468 - 0x0700D558
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D468, 0x004c4320, 38405, 0x0000d468, 240);

// 0x0700D558 - 0x0700D638
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D558, 0x004c4320, 38405, 0x0000d558, 224);

// 0x0700D638 - 0x0700D728
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D638, 0x004c4320, 38405, 0x0000d638, 240);

// 0x0700D728 - 0x0700D828
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D728, 0x004c4320, 38405, 0x0000d728, 256);

// 0x0700D828 - 0x0700D928
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D828, 0x004c4320, 38405, 0x0000d828, 256);

// 0x0700D928 - 0x0700DA28
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700D928, 0x004c4320, 38405, 0x0000d928, 256);

// 0x0700DA28 - 0x0700DB28
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700DA28, 0x004c4320, 38405, 0x0000da28, 256);

// 0x0700DB28 - 0x0700DC28
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700DB28, 0x004c4320, 38405, 0x0000db28, 256);

// 0x0700DC28 - 0x0700DD28
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700DC28, 0x004c4320, 38405, 0x0000dc28, 256);

// 0x0700DD28 - 0x0700DE18
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700DD28, 0x004c4320, 38405, 0x0000dd28, 240);

// 0x0700DE18 - 0x0700DF18
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700DE18, 0x004c4320, 38405, 0x0000de18, 256);

// 0x0700DF18 - 0x0700E018
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700DF18, 0x004c4320, 38405, 0x0000df18, 256);

// 0x0700E018 - 0x0700E118
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700E018, 0x004c4320, 38405, 0x0000e018, 256);

// 0x0700E118 - 0x0700E188
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700E118, 0x004c4320, 38405, 0x0000e118, 112);

// 0x0700E188 - 0x0700EFD8
static const Gfx wmotr_seg7_dl_0700E188[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wmotr_seg7_texture_07000C00),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wmotr_seg7_lights_0700C2A0.l, 1),
    gsSPLight(&wmotr_seg7_lights_0700C2A0.a, 2),
    gsSPVertex(wmotr_seg7_vertex_0700C2B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  2,  5,  6, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  3,  2,  6, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 6,  5,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 3,  6, 10, 0x0, 10,  6,  9, 0x0),
    gsSP2Triangles( 7,  4, 11, 0x0,  1, 11,  4, 0x0),
    gsSP2Triangles( 7, 12,  8, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles(13,  7, 14, 0x0,  9, 12, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700C3B8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 2,  4,  5, 0x0,  6,  5,  4, 0x0),
    gsSP2Triangles( 2,  5,  7, 0x0,  8,  2,  7, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0,  7,  5,  9, 0x0),
    gsSP2Triangles( 6,  9,  5, 0x0, 10,  7, 11, 0x0),
    gsSP2Triangles( 7,  9, 11, 0x0,  8,  7, 10, 0x0),
    gsSP2Triangles(11,  9,  6, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 14, 15,  6, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700C4B8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 0,  8,  9, 0x0,  0,  9,  7, 0x0),
    gsSP2Triangles( 0,  6, 10, 0x0, 11, 12,  0, 0x0),
    gsSP2Triangles(11,  0, 10, 0x0, 13,  0, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700C5A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 7,  2,  8, 0x0,  2,  5,  8, 0x0),
    gsSP2Triangles( 8,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 9,  8, 10, 0x0,  8,  6, 10, 0x0),
    gsSP2Triangles(10,  6, 11, 0x0, 12, 10, 13, 0x0),
    gsSP2Triangles( 9, 10, 12, 0x0, 10, 11, 13, 0x0),
    gsSP2Triangles(14, 15, 11, 0x0, 13, 11, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700C6A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 2,  5,  7, 0x0,  7,  5,  8, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0,  6,  7,  9, 0x0),
    gsSP2Triangles( 7,  8, 10, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  9, 10, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700C7A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 5,  2,  6, 0x0,  2,  4,  6, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  6,  9, 0x0),
    gsSP2Triangles( 5,  6,  8, 0x0,  6,  7,  9, 0x0),
    gsSP2Triangles( 9,  7, 10, 0x0, 11,  9, 12, 0x0),
    gsSP2Triangles( 8,  9, 11, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700C8A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 5,  2,  6, 0x0,  4,  5,  7, 0x0),
    gsSP2Triangles( 7,  5,  8, 0x0,  5,  6,  8, 0x0),
    gsSP2Triangles( 8,  6,  9, 0x0, 10,  8, 11, 0x0),
    gsSP2Triangles( 7,  8, 10, 0x0,  8,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 10, 11, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700C9A8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  4, 0x0),
    gsSP2Triangles( 7,  8,  5, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 7,  9,  8, 0x0, 10,  9,  7, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 12, 13, 10, 0x0),
    gsSP1Triangle(14, 13, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700CA98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  0, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  4, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  5, 0x0,  9,  6,  4, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0,  9, 11,  6, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 14, 12, 10, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 15, 12, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700CB98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  0,  3, 0x0),
    gsSP2Triangles(11, 12,  0, 0x0, 13, 12, 11, 0x0),
    gsSP2Triangles(13, 14, 12, 0x0, 15, 14, 13, 0x0),
    gsSP2Triangles(15, 10, 14, 0x0,  8, 10, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700CC98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 10,  8, 0x0),
    gsSP2Triangles(11, 12, 10, 0x0,  7, 12, 11, 0x0),
    gsSP2Triangles( 7,  6, 12, 0x0, 13, 14,  7, 0x0),
    gsSP2Triangles(15, 13,  7, 0x0,  7, 14,  5, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700CD98, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8,  2,  9, 0x0, 10,  8,  7, 0x0),
    gsSP2Triangles(10, 11,  8, 0x0, 11,  0,  8, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0, 12,  2, 13, 0x0),
    gsSP2Triangles( 9,  2, 12, 0x0,  1, 14,  2, 0x0),
    gsSP2Triangles(13,  2, 14, 0x0, 15,  9, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700CE98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  4,  5,  1, 0x0),
    gsSP2Triangles( 5,  6,  1, 0x0,  1,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0, 13, 12, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700CF88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  3,  1,  5, 0x0),
    gsSP2Triangles( 0,  6,  4, 0x0,  7,  4,  8, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  6,  0,  9, 0x0),
    gsSP2Triangles( 0, 10,  9, 0x0, 10,  0, 11, 0x0),
    gsSP2Triangles(12,  0,  2, 0x0,  0, 12, 11, 0x0),
    gsSP2Triangles(13,  6,  9, 0x0,  6, 13, 14, 0x0),
    gsSP2Triangles( 8,  6, 14, 0x0, 15, 11, 12, 0x0),
    gsSP1Triangle(15, 10, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D088, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  2,  9, 10, 0x0),
    gsSP2Triangles( 2,  1,  9, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles( 9, 12, 11, 0x0,  9, 13, 12, 0x0),
    gsSP2Triangles( 8,  7, 14, 0x0,  7, 10, 14, 0x0),
    gsSP2Triangles( 2, 10,  7, 0x0, 10, 11, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D188, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  5,  4,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 15, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D288, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11,  6, 0x0, 11, 12,  6, 0x0),
    gsSP1Triangle(13, 11, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D378, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  5,  4,  1, 0x0),
    gsSP2Triangles( 6,  2,  4, 0x0,  7,  3,  0, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0, 10,  8,  3, 0x0),
    gsSP2Triangles( 3,  9,  5, 0x0, 11,  2, 12, 0x0),
    gsSP2Triangles(12,  2,  6, 0x0, 13, 14, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D468, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D558, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  3,  2, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12,  9, 11, 0x0, 13, 12, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D638, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 2,  1,  5, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 6,  2,  3, 0x0,  6,  0,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  4,  5, 10, 0x0),
    gsSP2Triangles(11, 10,  5, 0x0, 11,  5,  1, 0x0),
    gsSP2Triangles( 3,  4, 12, 0x0, 12,  4,  7, 0x0),
    gsSP2Triangles( 4, 10,  7, 0x0,  0, 13,  1, 0x0),
    gsSP2Triangles(11,  1, 13, 0x0,  7, 10,  8, 0x0),
    gsSP2Triangles(11,  8, 10, 0x0, 14,  7,  9, 0x0),
    gsSP1Triangle(12,  7, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D728, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles( 9,  5, 10, 0x0,  6, 10,  5, 0x0),
    gsSP2Triangles( 8,  9,  0, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles( 9, 10,  1, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles( 1, 10, 12, 0x0,  6, 11, 10, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSP2Triangles( 2, 12, 15, 0x0,  6, 13, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D828, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  0,  4, 0x0),
    gsSP2Triangles( 6,  0,  5, 0x0,  4,  2,  7, 0x0),
    gsSP2Triangles( 3,  7,  2, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 9,  4,  8, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles( 8,  7,  3, 0x0,  8,  3, 10, 0x0),
    gsSP2Triangles(11,  8, 10, 0x0,  9,  8, 11, 0x0),
    gsSP2Triangles(10,  3, 12, 0x0,  3, 13, 14, 0x0),
    gsSP2Triangles(14, 12,  3, 0x0, 10, 12, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700D928, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  3,  4,  6, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  2,  3,  8, 0x0),
    gsSP2Triangles( 8,  3,  6, 0x0,  9,  7, 10, 0x0),
    gsSP2Triangles( 6,  5, 11, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles(13,  6, 12, 0x0,  8,  6, 13, 0x0),
    gsSP2Triangles( 7, 11,  5, 0x0, 11, 14, 15, 0x0),
    gsSP2Triangles(12, 11, 15, 0x0,  7, 14, 11, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700DA28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  6,  4, 0x0),
    gsSP2Triangles( 2,  3,  7, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  5, 11, 12, 0x0),
    gsSP2Triangles(13,  5, 12, 0x0,  7,  5, 13, 0x0),
    gsSP2Triangles(13, 12, 10, 0x0,  8, 14, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700DB28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 2,  3,  5, 0x0,  6,  7,  0, 0x0),
    gsSP2Triangles( 0,  7,  1, 0x0,  8,  9,  6, 0x0),
    gsSP2Triangles( 6,  9,  7, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles( 8, 11,  9, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 14, 15, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700DC28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  3, 0x0,  5,  8,  6, 0x0),
    gsSP2Triangles( 9,  8,  5, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 9, 11,  8, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 12, 14, 13, 0x0),
    gsSP1Triangle(15, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700DD28, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 7,  6,  4, 0x0,  8,  7,  4, 0x0),
    gsSP2Triangles( 9,  7,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles( 9, 11,  7, 0x0, 12, 13, 10, 0x0),
    gsSP2Triangles(10, 13, 11, 0x0, 12, 14, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700DE18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 6,  7,  1, 0x0,  8,  6,  1, 0x0),
    gsSP2Triangles( 9,  8,  1, 0x0,  5,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  1, 13, 14, 0x0),
    gsSP2Triangles( 1, 14, 15, 0x0,  1, 15,  2, 0x0),
    gsSP2Triangles( 1,  7, 13, 0x0,  3,  2, 15, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700DF18, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  6,  3,  5, 0x0),
    gsSP2Triangles( 2,  3,  6, 0x0,  7,  0,  8, 0x0),
    gsSP2Triangles( 9, 10,  8, 0x0, 11,  9,  8, 0x0),
    gsSP2Triangles( 0, 12,  8, 0x0,  8, 10, 13, 0x0),
    gsSP2Triangles( 8, 13, 14, 0x0, 15,  8, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700E018, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  3, 0x0),
    gsSP2Triangles( 5,  3,  6, 0x0,  7,  2,  3, 0x0),
    gsSP2Triangles( 7,  8,  2, 0x0,  8,  0,  2, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0,  5, 10,  7, 0x0),
    gsSP2Triangles( 9, 11, 10, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(10, 13,  7, 0x0, 11, 14, 10, 0x0),
    gsSP1Triangle(15, 12, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700E118, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EFD8 - 0x0700F048
const Gfx wmotr_seg7_dl_0700EFD8[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 180),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wmotr_seg7_dl_0700E188),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x0700F048 - 0x0700F138
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F048, 0x004c4320, 38405, 0x0000f048, 240);

// 0x0700F138 - 0x0700F228
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F138, 0x004c4320, 38405, 0x0000f138, 240);

// 0x0700F228 - 0x0700F318
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F228, 0x004c4320, 38405, 0x0000f228, 240);

// 0x0700F318 - 0x0700F408
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F318, 0x004c4320, 38405, 0x0000f318, 240);

// 0x0700F408 - 0x0700F508
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F408, 0x004c4320, 38405, 0x0000f408, 256);

// 0x0700F508 - 0x0700F5F8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F508, 0x004c4320, 38405, 0x0000f508, 240);

// 0x0700F5F8 - 0x0700F6D8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F5F8, 0x004c4320, 38405, 0x0000f5f8, 224);

// 0x0700F6D8 - 0x0700F7C8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F6D8, 0x004c4320, 38405, 0x0000f6d8, 240);

// 0x0700F7C8 - 0x0700F8B8
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F7C8, 0x004c4320, 38405, 0x0000f7c8, 240);

// 0x0700F8B8 - 0x0700F998
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F8B8, 0x004c4320, 38405, 0x0000f8b8, 224);

// 0x0700F998 - 0x0700FA88
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700F998, 0x004c4320, 38405, 0x0000f998, 240);

// 0x0700FA88 - 0x0700FB78
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700FA88, 0x004c4320, 38405, 0x0000fa88, 240);

// 0x0700FB78 - 0x0700FC68
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700FB78, 0x004c4320, 38405, 0x0000fb78, 240);

// 0x0700FC68 - 0x0700FD58
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700FC68, 0x004c4320, 38405, 0x0000fc68, 240);

// 0x0700FD58 - 0x0700FE48
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700FD58, 0x004c4320, 38405, 0x0000fd58, 240);

// 0x0700FE48 - 0x0700FF38
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700FE48, 0x004c4320, 38405, 0x0000fe48, 240);

// 0x0700FF38 - 0x07010028
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_0700FF38, 0x004c4320, 38405, 0x0000ff38, 240);

// 0x07010028 - 0x07010118
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07010028, 0x004c4320, 38405, 0x00010028, 240);

// 0x07010118 - 0x07010158
ROM_ASSET_LOAD_VTX(wmotr_seg7_vertex_07010118, 0x004c4320, 38405, 0x00010118, 64);

// 0x07010158 - 0x07010608
static const Gfx wmotr_seg7_dl_07010158[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wmotr_seg7_texture_07001400),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 8 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wmotr_seg7_vertex_0700F048, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F138, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F228, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F318, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F408, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F508, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 9, 14, 10, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F5F8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F6D8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F7C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F8B8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700F998, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700FA88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700FB78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700FC68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700FD58, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700FE48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wmotr_seg7_vertex_0700FF38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07010028, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(wmotr_seg7_vertex_07010118, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010608 - 0x07010688
const Gfx wmotr_seg7_dl_07010608[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 128),
    gsDPSetCombineMode(G_CC_MODULATERGBFADEA, G_CC_MODULATERGBFADEA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wmotr_seg7_dl_07010158),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
