#include "pc/rom_assets.h"
#include "include/types.h"
// 0x0700C7C8 - 0x0700C8F0
ROM_ASSET_LOAD_ANIM(castle_grounds_seg7_animvalue_flags, 0x0044abc0, 39442, 0x0000c7c8, 296);

// 0x0700C8F0 - 0x0700C944
ROM_ASSET_LOAD_ANIM(castle_grounds_seg7_animindex_flags, 0x0044abc0, 39442, 0x0000c8f0, 84);

// 0x0700C944 - 0x0700C95C
static const struct Animation castle_grounds_seg7_anim_flags = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(castle_grounds_seg7_animindex_flags),
    castle_grounds_seg7_animvalue_flags,
    castle_grounds_seg7_animindex_flags,
    0,
    ANIM_FIELD_LENGTH(castle_grounds_seg7_animvalue_flags),
    ANIM_FIELD_LENGTH(castle_grounds_seg7_animindex_flags),
};

// 0x0700C95C - 0x0700C960
const struct AnimationTable castle_grounds_seg7_anims_flags = {
    .anims = {
        &castle_grounds_seg7_anim_flags, // 0x0700C944
    },
    .count = 1
};
