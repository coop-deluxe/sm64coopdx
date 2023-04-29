#include "types.h"

#include "pc/lua/smlua.h"
#include "smlua_anim_utils.h"
#include "pc/debuglog.h"

// models
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/custom0.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "actors/zcustom0.h"
#include "levels/castle_grounds/header.h"

struct GlobalObjectAnimations gGlobalObjectAnimations = {
    .amp_seg8_anims_08004034          = (struct Animation**) amp_seg8_anims_08004034,
    .birds_seg5_anims_050009E8        = (struct Animation**) birds_seg5_anims_050009E8,
    .blargg_seg5_anims_0500616C       = (struct Animation**) blargg_seg5_anims_0500616C,
    .blue_fish_seg3_anims_0301C2B0    = (struct Animation**) blue_fish_seg3_anims_0301C2B0,
    .bobomb_seg8_anims_0802396C       = (struct Animation**) bobomb_seg8_anims_0802396C,
    .bookend_seg5_anims_05002540      = (struct Animation**) bookend_seg5_anims_05002540,
    .bowser_key_seg3_anims_list       = (struct Animation**) bowser_key_seg3_anims_list,
    .bowser_seg6_anims_06057690       = (struct Animation**) bowser_seg6_anims_06057690,
    .bub_seg6_anims_06012354          = (struct Animation**) bub_seg6_anims_06012354,
    .bully_seg5_anims_0500470C        = (struct Animation**) bully_seg5_anims_0500470C,
    .butterfly_seg3_anims_030056B0    = (struct Animation**) butterfly_seg3_anims_030056B0,
    .castle_grounds_seg7_anims_flags  = (struct Animation**) castle_grounds_seg7_anims_flags,
    .chain_chomp_seg6_anims_06025178  = (struct Animation**) chain_chomp_seg6_anims_06025178,
    .chair_seg5_anims_05005784        = (struct Animation**) chair_seg5_anims_05005784,
    .chilly_chief_seg6_anims_06003994 = (struct Animation**) chilly_chief_seg6_anims_06003994,
    .chuckya_seg8_anims_0800C070      = (struct Animation**) chuckya_seg8_anims_0800C070,
    .clam_shell_seg5_anims_05001744   = (struct Animation**) clam_shell_seg5_anims_05001744,
    .cyan_fish_seg6_anims_0600E264    = (struct Animation**) cyan_fish_seg6_anims_0600E264,
    .door_seg3_anims_030156C0         = (struct Animation**) door_seg3_anims_030156C0,
    .dorrie_seg6_anims_0600F638       = (struct Animation**) dorrie_seg6_anims_0600F638,
    .eyerok_seg5_anims_050116E4       = (struct Animation**) eyerok_seg5_anims_050116E4,
    .flyguy_seg8_anims_08011A64       = (struct Animation**) flyguy_seg8_anims_08011A64,
    .goomba_seg8_anims_0801DA4C       = (struct Animation**) goomba_seg8_anims_0801DA4C,
    .heave_ho_seg5_anims_0501534C     = (struct Animation**) heave_ho_seg5_anims_0501534C,
    .hoot_seg5_anims_05005768         = (struct Animation**) hoot_seg5_anims_05005768,
    .king_bobomb_seg5_anims_0500FE30  = (struct Animation**) king_bobomb_seg5_anims_0500FE30,
    .klepto_seg5_anims_05008CFC       = (struct Animation**) klepto_seg5_anims_05008CFC,
    .koopa_flag_seg6_anims_06001028   = (struct Animation**) koopa_flag_seg6_anims_06001028,
    .koopa_seg6_anims_06011364        = (struct Animation**) koopa_seg6_anims_06011364,
    .lakitu_enemy_seg5_anims_050144D4 = (struct Animation**) lakitu_enemy_seg5_anims_050144D4,
    .lakitu_seg6_anims_060058F8       = (struct Animation**) lakitu_seg6_anims_060058F8,
    .mad_piano_seg5_anims_05009B14    = (struct Animation**) mad_piano_seg5_anims_05009B14,
    .manta_seg5_anims_05008EB4        = (struct Animation**) manta_seg5_anims_05008EB4,
    .mips_seg6_anims_06015634         = (struct Animation**) mips_seg6_anims_06015634,
    .moneybag_seg6_anims_06005E5C     = (struct Animation**) moneybag_seg6_anims_06005E5C,
    .monty_mole_seg5_anims_05007248   = (struct Animation**) monty_mole_seg5_anims_05007248,
    .peach_seg5_anims_0501C41C        = (struct Animation**) peach_seg5_anims_0501C41C,
    .penguin_seg5_anims_05008B74      = (struct Animation**) penguin_seg5_anims_05008B74,
    .piranha_plant_seg6_anims_0601C31C= (struct Animation**) piranha_plant_seg6_anims_0601C31C,
    .scuttlebug_seg6_anims_06015064   = (struct Animation**) scuttlebug_seg6_anims_06015064,
    .seaweed_seg6_anims_0600A4D4      = (struct Animation**) seaweed_seg6_anims_0600A4D4,
    .skeeter_seg6_anims_06007DE0      = (struct Animation**) skeeter_seg6_anims_06007DE0,
    .snowman_seg5_anims_0500D118      = (struct Animation**) snowman_seg5_anims_0500D118,
    .spindrift_seg5_anims_05002D68    = (struct Animation**) spindrift_seg5_anims_05002D68,
    .spiny_seg5_anims_05016EAC        = (struct Animation**) spiny_seg5_anims_05016EAC,
    .spiny_egg_seg5_anims_050157E4    = (struct Animation**) spiny_egg_seg5_anims_050157E4,
    .sushi_seg5_anims_0500AE54        = (struct Animation**) sushi_seg5_anims_0500AE54,
    .swoop_seg6_anims_060070D0        = (struct Animation**) swoop_seg6_anims_060070D0,
    .toad_seg6_anims_0600FB58         = (struct Animation**) toad_seg6_anims_0600FB58,
    .ukiki_seg5_anims_05015784        = (struct Animation**) ukiki_seg5_anims_05015784,
    .unagi_seg5_anims_05012824        = (struct Animation**) unagi_seg5_anims_05012824,
    .water_ring_seg6_anims_06013F7C   = (struct Animation**) water_ring_seg6_anims_06013F7C,
    .whomp_seg6_anims_06020A04        = (struct Animation**) whomp_seg6_anims_06020A04,
    .wiggler_seg5_anims_0500C874      = (struct Animation**) wiggler_seg5_anims_0500C874,
    .wiggler_seg5_anims_0500EC8C      = (struct Animation**) wiggler_seg5_anims_0500EC8C,
    .yoshi_seg5_anims_05024100        = (struct Animation**) yoshi_seg5_anims_05024100,
};

  ///////////////////////
 // custom animations //
///////////////////////

struct CustomAnimation {
    const char *name;
    struct Animation *anim;
    struct CustomAnimation *next;
};

struct CustomAnimation* sCustomAnimationHead = NULL;

static struct CustomAnimation *get_custom_animation_node(const char *name) {
    for (struct CustomAnimation *node = sCustomAnimationHead; node; node = node->next) {
        if (node->name && strcmp(node->name, name) == 0) {
            return node;
        }
    }
    return NULL;
}

void smlua_anim_util_reset() {
    for (struct CustomAnimation *node = sCustomAnimationHead; node;) {
        struct CustomAnimation *next = node->next;
        if (node->name) {
            free((void *) node->name);
        }
        if (node->anim) {
            if (node->anim->index) {
                free((void *) node->anim->index);
            }
            if (node->anim->values) {
                free((void *) node->anim->values);
            }
        }
        free(node);
        node = next;
    }
    sCustomAnimationHead = NULL;
}

void smlua_anim_util_register_animation(const char *name, s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, const s16 *values, const u16 *index) {

    // NULL-checks
    if (!name) {
        LOG_LUA_LINE("smlua_anim_util_register_animation: Parameter 'name' is NULL");
        return;
    }

    // Check if the name is not already taken
    if (get_custom_animation_node(name)) {
        LOG_LUA_LINE("smlua_anim_util_register_animation: An animation named '%s' already exists", name);
        return;
    }

    // Create a new node
    struct CustomAnimation *node = calloc(1, sizeof(struct CustomAnimation));
    node->name = strdup(name);
    node->anim = calloc(1, sizeof(struct Animation));
    node->anim->flags = flags;
    node->anim->animYTransDivisor = animYTransDivisor;
    node->anim->startFrame = startFrame;
    node->anim->loopStart = loopStart;
    node->anim->loopEnd = loopEnd;
    node->anim->unusedBoneCount = 0;
    node->anim->values = values;
    node->anim->index = index;
    node->anim->length = 0;
    node->next = sCustomAnimationHead;
    sCustomAnimationHead = node;
    LOG_INFO("Registered custom animation: %s", name);
}

void smlua_anim_util_set_animation(struct Object *obj, const char *name) {

    // NULL-checks
    if (!obj) {
        LOG_LUA_LINE("smlua_anim_util_set_animation: Parameter 'obj' is NULL");
        return;
    }
    if (!name) {
        LOG_LUA_LINE("smlua_anim_util_set_animation: Parameter 'name' is NULL");
        return;
    }

    // Check if the animation exists
    struct CustomAnimation *node = get_custom_animation_node(name);
    if (!node) {
        LOG_LUA_LINE("smlua_anim_util_set_animation: Animation '%s' doesn't exist", name);
        return;
    }

    // Set animation
    obj->header.gfx.animInfo.curAnim = node->anim;
}

const char *smlua_anim_util_get_current_animation_name(struct Object *obj) {

    // NULL-checks
    if (!obj) {
        LOG_LUA_LINE("smlua_anim_util_set_animation: Parameter 'obj' is NULL");
        return NULL;
    }

    // Check the animations
    for (struct CustomAnimation *node = sCustomAnimationHead; node; node = node->next) {
        if (node->anim == obj->header.gfx.animInfo.curAnim) {
            return node->name;
        }
    }
    return NULL;
}
