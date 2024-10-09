#include "pc/rom_assets.h"
// 0x05007708
ROM_ASSET_LOAD_ANIM(penguin_seg5_animvalue_05007708, 0x00160670, 20585, 0x00007708, 588);

// 0x05007954
ROM_ASSET_LOAD_ANIM(penguin_seg5_animindex_05007954, 0x00160670, 20585, 0x00007954, 144);

// 0x050079E4
static const struct Animation penguin_seg5_anim_050079E4 = {
    1,
    0,
    0,
    0,
    0x19,
    ANIMINDEX_NUMPARTS(penguin_seg5_animindex_05007954),
    penguin_seg5_animvalue_05007708,
    penguin_seg5_animindex_05007954,
    0,
    ANIM_FIELD_LENGTH(penguin_seg5_animvalue_05007708),
    ANIM_FIELD_LENGTH(penguin_seg5_animindex_05007954),
};
