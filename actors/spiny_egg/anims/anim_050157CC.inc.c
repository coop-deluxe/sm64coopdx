#include "pc/rom_assets.h"
// 0x05015750
ROM_ASSET_LOAD_ANIM(spiny_egg_seg5_animvalue_05015750, 0x00108a40, 48390, 0x00000000, 4);

// 0x05015754
ROM_ASSET_LOAD_ANIM(spiny_egg_seg5_animindex_05015754, 0x00180bb0, 29674, 0x00015754, 120);

// 0x050157CC
static const struct Animation spiny_egg_seg5_anim_050157CC = {
    0,
    0,
    0,
    0,
    0x64,
    ANIMINDEX_NUMPARTS(spiny_egg_seg5_animindex_05015754),
    spiny_egg_seg5_animvalue_05015750,
    spiny_egg_seg5_animindex_05015754,
    0,
    ANIM_FIELD_LENGTH(spiny_egg_seg5_animvalue_05015750),
    ANIM_FIELD_LENGTH(spiny_egg_seg5_animindex_05015754),
};
