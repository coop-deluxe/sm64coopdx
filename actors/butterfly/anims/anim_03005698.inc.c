#include "pc/rom_assets.h"
// 0x030055C8
ROM_ASSET_LOAD_ANIM(butterfly_seg3_animvalue_030055C8, 0x00201410, 96653, 0x000055c8, 124);

// 0x03005644
ROM_ASSET_LOAD_ANIM(butterfly_seg3_animindex_03005644, 0x00201410, 96653, 0x00005644, 84);

// 0x03005698
static const struct Animation butterfly_seg3_anim_03005698 = {
    0,
    0,
    7,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(butterfly_seg3_animindex_03005644),
    butterfly_seg3_animvalue_030055C8,
    butterfly_seg3_animindex_03005644,
    0,
    ANIM_FIELD_LENGTH(butterfly_seg3_animvalue_030055C8),
    ANIM_FIELD_LENGTH(butterfly_seg3_animindex_03005644),
};
