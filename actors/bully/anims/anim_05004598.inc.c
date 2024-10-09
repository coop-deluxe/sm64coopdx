#include "pc/rom_assets.h"
// 0x050043F0
ROM_ASSET_LOAD_ANIM(bully_seg5_animvalue_050043F0, 0x00132c60, 7692, 0x000043f0, 256);


// 0x050044F0
ROM_ASSET_LOAD_ANIM(bully_seg5_animindex_050044F0, 0x00132c60, 7692, 0x000044f0, 168);

// 0x05004598
static const struct Animation bully_seg5_anim_05004598 = {
    0,
    0,
    0,
    0,
    0x18,
    ANIMINDEX_NUMPARTS(bully_seg5_animindex_050044F0),
    bully_seg5_animvalue_050043F0,
    bully_seg5_animindex_050044F0,
    0,
    ANIM_FIELD_LENGTH(bully_seg5_animvalue_050043F0),
    ANIM_FIELD_LENGTH(bully_seg5_animindex_050044F0),
};
