#include "pc/rom_assets.h"
// 0x05015130
ROM_ASSET_LOAD_ANIM(heave_ho_seg5_animvalue_05015130, 0x0012a7e0, 32879, 0x00015130, 312);

// 0x05015268
ROM_ASSET_LOAD_ANIM(heave_ho_seg5_animindex_05015268, 0x0012a7e0, 32879, 0x00015268, 204);

// 0x05015334
static const struct Animation heave_ho_seg5_anim_05015334 = {
    0,
    0,
    0,
    0,
    0x17,
    ANIMINDEX_NUMPARTS(heave_ho_seg5_animindex_05015268),
    heave_ho_seg5_animvalue_05015130,
    heave_ho_seg5_animindex_05015268,
    0,
    ANIM_FIELD_LENGTH(heave_ho_seg5_animvalue_05015130),
    ANIM_FIELD_LENGTH(heave_ho_seg5_animindex_05015268),
};
