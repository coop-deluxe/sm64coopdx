#include "pc/rom_assets.h"
// 0x050056F0
ROM_ASSET_LOAD_ANIM(chair_seg5_animvalue_050056F0, 0x00166c60, 26968, 0x000056f0, 16);

// 0x05005700
ROM_ASSET_LOAD_ANIM(chair_seg5_animindex_05005700, 0x00166c60, 26968, 0x00005700, 108);

// 0x0500576C
static const struct Animation chair_seg5_anim_0500576C = {
    0,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(chair_seg5_animindex_05005700),
    chair_seg5_animvalue_050056F0,
    chair_seg5_animindex_05005700,
    0,
    ANIM_FIELD_LENGTH(chair_seg5_animvalue_050056F0),
    ANIM_FIELD_LENGTH(chair_seg5_animindex_05005700),
};
