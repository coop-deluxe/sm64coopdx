#include "pc/rom_assets.h"
// 0x05005404
ROM_ASSET_LOAD_ANIM(hoot_seg5_animvalue_05005404, 0x0012a7e0, 32879, 0x00005404, 508);

// 0x05005600
ROM_ASSET_LOAD_ANIM(hoot_seg5_animindex_05005600, 0x0012a7e0, 32879, 0x00005600, 336);

// 0x05005750
static const struct Animation hoot_seg5_anim_05005750 = {
    0,
    0,
    0,
    0,
    0x0A,
    ANIMINDEX_NUMPARTS(hoot_seg5_animindex_05005600),
    hoot_seg5_animvalue_05005404,
    hoot_seg5_animindex_05005600,
    0,
    ANIM_FIELD_LENGTH(hoot_seg5_animvalue_05005404),
    ANIM_FIELD_LENGTH(hoot_seg5_animindex_05005600),
};
