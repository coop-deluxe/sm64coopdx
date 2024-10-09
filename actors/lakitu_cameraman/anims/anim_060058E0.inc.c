#include "pc/rom_assets.h"
// 0x06005638
ROM_ASSET_LOAD_ANIM(lakitu_seg6_animvalue_06005638, 0x001d8310, 51422, 0x00005638, 524);

// 0x06005844
ROM_ASSET_LOAD_ANIM(lakitu_seg6_animindex_06005844, 0x001d8310, 51422, 0x00005844, 156);

// 0x060058E0
static const struct Animation lakitu_seg6_anim_060058E0 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(lakitu_seg6_animindex_06005844),
    lakitu_seg6_animvalue_06005638,
    lakitu_seg6_animindex_06005844,
    0,
    ANIM_FIELD_LENGTH(lakitu_seg6_animvalue_06005638),
    ANIM_FIELD_LENGTH(lakitu_seg6_animindex_06005844),
};
