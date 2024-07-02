#include "pc/rom_assets.h"
// 0x0500240C
ROM_ASSET_LOAD_ANIM(bookend_seg5_animvalue_0500240C, 0x00166c60, 26968, 0x0000240c, 128);

// 0x0500248C
ROM_ASSET_LOAD_ANIM(bookend_seg5_animindex_0500248C, 0x00166c60, 26968, 0x0000248c, 132);

// 0x05002510
static const struct Animation bookend_seg5_anim_05002510 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(bookend_seg5_animindex_0500248C),
    bookend_seg5_animvalue_0500240C,
    bookend_seg5_animindex_0500248C,
    0,
    ANIM_FIELD_LENGTH(bookend_seg5_animvalue_0500240C),
    ANIM_FIELD_LENGTH(bookend_seg5_animindex_0500248C),
};

// what the hell? no values/indexes for the table?
