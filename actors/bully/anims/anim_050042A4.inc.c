#include "pc/rom_assets.h"
// 0x05004038
ROM_ASSET_LOAD_ANIM(bully_seg5_animvalue_05004038, 0x00132c60, 7692, 0x00004038, 452);

// 0x050041FC
ROM_ASSET_LOAD_ANIM(bully_seg5_animindex_050041FC, 0x00132c60, 7692, 0x000041fc, 168);

// 0x050042A4
static const struct Animation bully_seg5_anim_050042A4 = {
    0,
    0,
    0,
    0,
    0x16,
    ANIMINDEX_NUMPARTS(bully_seg5_animindex_050041FC),
    bully_seg5_animvalue_05004038,
    bully_seg5_animindex_050041FC,
    0,
    ANIM_FIELD_LENGTH(bully_seg5_animvalue_05004038),
    ANIM_FIELD_LENGTH(bully_seg5_animindex_050041FC),
};
