#include "pc/rom_assets.h"
ROM_ASSET_LOAD_TEXTURE(texture_castle_light, "levels/castle_inside/castle_light.ia16.inc.c", 0x00347a50, 27905, 0x0000b800, 2048);

// 0x07000800 - 0x07001000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07000800, "levels/castle_inside/1.rgba16.inc.c", 0x00396340, 232834, 0x00000800, 2048);

// 0x07001000 - 0x07002000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07001000, "levels/castle_inside/2.ia16.inc.c", 0x00326e40, 25130, 0x0000b800, 4096);

// 0x07002000 - 0x07003000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07002000, "levels/castle_inside/3.rgba16.inc.c", 0x00396340, 232834, 0x00002000, 4096);

// 0x07003000 - 0x07003800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07003000, "levels/castle_inside/4.rgba16.inc.c", 0x00396340, 232834, 0x00003000, 2048);

// 0x07003800 - 0x07004800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07003800, "levels/castle_inside/5.rgba16.inc.c", 0x00396340, 232834, 0x00003800, 4096);

// 0x07004800 - 0x07005800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07004800, "levels/castle_inside/6.rgba16.inc.c", 0x00396340, 232834, 0x00004800, 4096);

// 0x07005800 - 0x07006000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07005800, "levels/castle_inside/7.rgba16.inc.c", 0x00396340, 232834, 0x00005800, 2048);

// 0x07006000 - 0x07006800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07006000, "levels/castle_inside/8.rgba16.inc.c", 0x00396340, 232834, 0x00006000, 2048);

// 0x07006800 - 0x07007000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07006800, "levels/castle_inside/9.rgba16.inc.c", 0x00396340, 232834, 0x00006800, 2048);

// 0x07007000 - 0x07007800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07007000, "levels/castle_inside/10.rgba16.inc.c", 0x00396340, 232834, 0x00007000, 2048);

// 0x07007800 - 0x07008000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07007800, "levels/castle_inside/11.rgba16.inc.c", 0x00396340, 232834, 0x00007800, 2048);

// 0x07008000 - 0x07008800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07008000, "levels/castle_inside/12.rgba16.inc.c", 0x00396340, 232834, 0x00008000, 2048);

// 0x07008800 - 0x07009000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07008800, "levels/castle_inside/13.rgba16.inc.c", 0x00396340, 232834, 0x00008800, 2048);

// 0x07009000 - 0x07009800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07009000, "levels/castle_inside/14.rgba16.inc.c", 0x00396340, 232834, 0x00009000, 2048);

// 0x07009800 - 0x0700A000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07009800, "levels/castle_inside/15.rgba16.inc.c", 0x00396340, 232834, 0x00009800, 2048);

// 0x0700A000 - 0x0700A800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0700A000, "levels/castle_inside/16.ia16.inc.c", 0x00396340, 232834, 0x0000a000, 2048);

// 0x0700A800 - 0x0700B800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0700A800, "levels/castle_inside/17.rgba16.inc.c", 0x00396340, 232834, 0x0000a800, 4096);

// 0x0700B800 - 0x0700C800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0700B800, "levels/castle_inside/18.rgba16.inc.c", 0x00396340, 232834, 0x0000b800, 4096);

// 0x0700C800 - 0x0700D800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0700C800, "levels/castle_inside/19.rgba16.inc.c", 0x00396340, 232834, 0x0000c800, 4096);

// 0x0700D800 - 0x0700E800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0700D800, "levels/castle_inside/20.rgba16.inc.c", 0x00396340, 232834, 0x0000d800, 4096);

// 0x0700E800 - 0x0700F800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0700E800, "levels/castle_inside/21.rgba16.inc.c", 0x00396340, 232834, 0x0000e800, 4096);

// 0x0700F800 - 0x07010800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0700F800, "levels/castle_inside/22.rgba16.inc.c", 0x00396340, 232834, 0x0000f800, 4096);

#ifdef VERSION_JP
// 0x07010800 - 0x07011800
ALIGNED8 const Texture inside_castle_seg7_texture_07010800[] = {
#include "levels/castle_inside/23.rgba16.inc.c"
};

// 0x07011800 - 0x0701200
ALIGNED8 const Texture inside_castle_seg7_texture_07011800[] = {
#include "levels/castle_inside/24.rgba16.inc.c"
};

#else
// 0x07010800 - 0x07011800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07010800, "levels/castle_inside/23_us.rgba16.inc.c", 0x00396340, 232834, 0x00010800, 4096);

// 0x07011800 - 0x0701200
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07011800, "levels/castle_inside/24_us.rgba16.inc.c", 0x00396340, 232834, 0x00011800, 4096);
#endif

// 0x07012800 - 0x07013800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07012800, "levels/castle_inside/25.rgba16.inc.c", 0x00396340, 232834, 0x00012800, 4096);

// 0x07013800 - 0x07014800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07013800, "levels/castle_inside/26.rgba16.inc.c", 0x00396340, 232834, 0x00013800, 4096);

// 0x07014800 - 0x07015800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07014800, "levels/castle_inside/27.rgba16.inc.c", 0x00396340, 232834, 0x00014800, 4096);

// 0x07015800 - 0x07016800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07015800, "levels/castle_inside/28.rgba16.inc.c", 0x00396340, 232834, 0x00015800, 4096);

// 0x07016800 - 0x07017000
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07016800, "levels/castle_inside/29.rgba16.inc.c", 0x00396340, 232834, 0x00016800, 2048);

// 0x07017000 - 0x07017800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07017000, "levels/castle_inside/30.rgba16.inc.c", 0x00396340, 232834, 0x00017000, 2048);

// 0x07017800 - 0x07018800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07017800, "levels/castle_inside/31.rgba16.inc.c", 0x00396340, 232834, 0x00017800, 4096);

// 0x07018800 - 0x07019800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07018800, "levels/castle_inside/32.rgba16.inc.c", 0x00396340, 232834, 0x00018800, 4096);

// 0x07019800 - 0x0701A800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07019800, "levels/castle_inside/33.rgba16.inc.c", 0x00396340, 232834, 0x00019800, 4096);

// 0x0701A800 - 0x0701B800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0701A800, "levels/castle_inside/34.rgba16.inc.c", 0x00396340, 232834, 0x0001a800, 4096);

// 0x0701B800 - 0x0701C800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0701B800, "levels/castle_inside/35.rgba16.inc.c", 0x00396340, 232834, 0x0001b800, 4096);

// 0x0701C800 - 0x0701D800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0701C800, "levels/castle_inside/36.rgba16.inc.c", 0x00396340, 232834, 0x0001c800, 4096);

// 0x0701D800 - 0x0701E800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0701D800, "levels/castle_inside/37.rgba16.inc.c", 0x00396340, 232834, 0x0001d800, 4096);

// 0x0701E800 - 0x0701F800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0701E800, "levels/castle_inside/38.rgba16.inc.c", 0x00396340, 232834, 0x0001e800, 4096);

// 0x0701F800 - 0x07020800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_0701F800, "levels/castle_inside/39.rgba16.inc.c", 0x00396340, 232834, 0x0001f800, 4096);

// 0x07020800 - 0x07021800
ROM_ASSET_LOAD_TEXTURE(inside_castle_seg7_texture_07020800, "levels/castle_inside/40.rgba16.inc.c", 0x00396340, 232834, 0x00020800, 4096);
