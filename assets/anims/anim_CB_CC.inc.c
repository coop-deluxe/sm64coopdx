#include "pc/rom_assets.h"
static const struct Animation anim_CB[] = {
    1,
    189,
    0,
    0,
    0x11,
    ANIMINDEX_NUMPARTS(anim_CB_CC_indices),
    anim_CB_CC_values,
    anim_CB_CC_indices,
    0,
    ANIM_FIELD_LENGTH(anim_CB_CC_values),
    ANIM_FIELD_LENGTH(anim_CB_CC_indices),
};

static const struct Animation anim_CC[] = {
    1,
    189,
    0,
    0,
    0x01,
    ANIMINDEX_NUMPARTS(anim_CB_CC_indices),
    anim_CB_CC_values,
    anim_CB_CC_indices,
    0,
    ANIM_FIELD_LENGTH(anim_CB_CC_values),
    ANIM_FIELD_LENGTH(anim_CB_CC_indices),
};


ROM_ASSET_LOAD_ANIM(anim_CB_CC_indices, 0x00576a00, 252, 0x00000000, 252);

ROM_ASSET_LOAD_ANIM(anim_CB_CC_values, 0x00576afc, 1382, 0x00000000, 1382);

