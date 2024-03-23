#include "pc/rom_assets.h"
// 0x08003E30
ROM_ASSET_LOAD_ANIM(amp_seg8_animvalue_08003E30, 0x001f2200, 59076, 0x00003e30, 324);

// 0x08003F74
ROM_ASSET_LOAD_ANIM(amp_seg8_animindex_08003F74, 0x001f2200, 59076, 0x00003f74, 168);

// 0x0800401C
static const struct Animation amp_seg8_anim_0800401C = {
    0,
    0,
    0,
    0,
    0x13,
    ANIMINDEX_NUMPARTS(amp_seg8_animindex_08003F74),
    amp_seg8_animvalue_08003E30,
    amp_seg8_animindex_08003F74,
    0,
    ANIM_FIELD_LENGTH(amp_seg8_animvalue_08003E30),
    ANIM_FIELD_LENGTH(amp_seg8_animindex_08003F74),
};
