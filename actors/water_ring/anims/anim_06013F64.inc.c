#include "pc/rom_assets.h"
// 0x06013DD8
ROM_ASSET_LOAD_ANIM(water_ring_seg6_animvalue_06013DD8, 0x001b9cc0, 41188, 0x00013dd8, 360);

// 0x06013F40
ROM_ASSET_LOAD_ANIM(water_ring_seg6_animindex_06013F40, 0x001b9cc0, 41188, 0x00013f40, 36);

// 0x06013F64
static const struct Animation water_ring_seg6_anim_06013F64 = {
    0,
    0,
    0,
    0,
    0x3B,
    ANIMINDEX_NUMPARTS(water_ring_seg6_animindex_06013F40),
    water_ring_seg6_animvalue_06013DD8,
    water_ring_seg6_animindex_06013F40,
    0,
    ANIM_FIELD_LENGTH(water_ring_seg6_animvalue_06013DD8),
    ANIM_FIELD_LENGTH(water_ring_seg6_animindex_06013F40),
};
