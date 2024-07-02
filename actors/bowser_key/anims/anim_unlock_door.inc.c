#include "pc/rom_assets.h"
// 0x03016C00
ROM_ASSET_LOAD_ANIM(bowser_key_seg3_animvalue_unlock_door, 0x00201410, 96653, 0x00016c00, 1684);

// 0x03017294
ROM_ASSET_LOAD_ANIM(bowser_key_seg3_animindex_unlock_door, 0x00201410, 96653, 0x00016bc4, 36);

// 0x030172B8
static const struct Animation bowser_key_seg3_anim_unlock_door = {
    1,
    0,
    0,
    0,
    0x8C,
    ANIMINDEX_NUMPARTS(bowser_key_seg3_animindex_unlock_door),
    bowser_key_seg3_animvalue_unlock_door,
    bowser_key_seg3_animindex_unlock_door,
    0,
    ANIM_FIELD_LENGTH(bowser_key_seg3_animvalue_unlock_door),
    ANIM_FIELD_LENGTH(bowser_key_seg3_animindex_unlock_door),
};
