#include "pc/rom_assets.h"
// 0x0604F048
ROM_ASSET_LOAD_ANIM(bowser_seg6_animvalue_0604F048, 0x00188440, 199722, 0x0004f198, 3304);

// 0x0604FD30
ROM_ASSET_LOAD_ANIM(bowser_seg6_animindex_0604FD30, 0x00188440, 199722, 0x0004fe80, 540);

// 0x0604FF4C
static const struct Animation bowser_seg6_anim_0604FF4C = {
    0,
    0,
    0,
    0,
    0x2A,
    ANIMINDEX_NUMPARTS(bowser_seg6_animindex_0604FD30),
    bowser_seg6_animvalue_0604F048,
    bowser_seg6_animindex_0604FD30,
    0,
    ANIM_FIELD_LENGTH(bowser_seg6_animvalue_0604F048),
    ANIM_FIELD_LENGTH(bowser_seg6_animindex_0604FD30),
};
