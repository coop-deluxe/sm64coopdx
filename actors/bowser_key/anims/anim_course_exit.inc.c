#include "pc/rom_assets.h"
// 0x03016530
ROM_ASSET_LOAD_ANIM(bowser_key_seg3_animvalue_course_exit, 0x00201410, 96653, 0x00016530, 1684);

// 0x03016BC4
ROM_ASSET_LOAD_ANIM(bowser_key_seg3_animindex_course_exit, 0x00201410, 96653, 0x00016bc4, 36);

// 0x03016BE8
static const struct Animation bowser_key_seg3_anim_course_exit = {
    1,
    0,
    0,
    0,
    0x8C,
    ANIMINDEX_NUMPARTS(bowser_key_seg3_animindex_course_exit),
    bowser_key_seg3_animvalue_course_exit,
    bowser_key_seg3_animindex_course_exit,
    0,
    ANIM_FIELD_LENGTH(bowser_key_seg3_animvalue_course_exit),
    ANIM_FIELD_LENGTH(bowser_key_seg3_animindex_course_exit),
};
