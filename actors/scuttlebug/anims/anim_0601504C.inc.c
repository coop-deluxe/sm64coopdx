#include "pc/rom_assets.h"
// 0x06014398
ROM_ASSET_LOAD_ANIM(scuttlebug_seg6_animvalue_06014398, 0x001e7ee0, 40011, 0x00014398, 2736);


// 0x06014E48
ROM_ASSET_LOAD_ANIM(scuttlebug_seg6_animindex_06014E48, 0x001e7ee0, 40011, 0x00014e48, 516);

// 0x0601504C
static const struct Animation scuttlebug_seg6_anim_0601504C = {
    0,
    0,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(scuttlebug_seg6_animindex_06014E48),
    scuttlebug_seg6_animvalue_06014398,
    scuttlebug_seg6_animindex_06014E48,
    0,
    ANIM_FIELD_LENGTH(scuttlebug_seg6_animvalue_06014398),
    ANIM_FIELD_LENGTH(scuttlebug_seg6_animindex_06014E48),
};
