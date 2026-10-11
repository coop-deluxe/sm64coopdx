#include "types.h"

#include "pc/lua/smlua.h"
#include "smlua_anim_utils.h"
#include "object_fields.h"
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
    .amp_seg8_anims_08004034          = (struct AnimationTable*) &amp_seg8_anims_08004034,
    .birds_seg5_anims_050009E8        = (struct AnimationTable*) &birds_seg5_anims_050009E8,
    .blargg_seg5_anims_0500616C       = (struct AnimationTable*) &blargg_seg5_anims_0500616C,
    .blue_fish_seg3_anims_0301C2B0    = (struct AnimationTable*) &blue_fish_seg3_anims_0301C2B0,
    .bobomb_seg8_anims_0802396C       = (struct AnimationTable*) &bobomb_seg8_anims_0802396C,
    .bookend_seg5_anims_05002540      = (struct AnimationTable*) &bookend_seg5_anims_05002540,
    .bowser_key_seg3_anims_list       = (struct AnimationTable*) &bowser_key_seg3_anims_list,
    .bowser_seg6_anims_06057690       = (struct AnimationTable*) &bowser_seg6_anims_06057690,
    .bub_seg6_anims_06012354          = (struct AnimationTable*) &bub_seg6_anims_06012354,
    .bully_seg5_anims_0500470C        = (struct AnimationTable*) &bully_seg5_anims_0500470C,
    .butterfly_seg3_anims_030056B0    = (struct AnimationTable*) &butterfly_seg3_anims_030056B0,
    .castle_grounds_seg7_anims_flags  = (struct AnimationTable*) &castle_grounds_seg7_anims_flags,
    .chain_chomp_seg6_anims_06025178  = (struct AnimationTable*) &chain_chomp_seg6_anims_06025178,
    .chair_seg5_anims_05005784        = (struct AnimationTable*) &chair_seg5_anims_05005784,
    .chilly_chief_seg6_anims_06003994 = (struct AnimationTable*) &chilly_chief_seg6_anims_06003994,
    .chuckya_seg8_anims_0800C070      = (struct AnimationTable*) &chuckya_seg8_anims_0800C070,
    .clam_shell_seg5_anims_05001744   = (struct AnimationTable*) &clam_shell_seg5_anims_05001744,
    .cyan_fish_seg6_anims_0600E264    = (struct AnimationTable*) &cyan_fish_seg6_anims_0600E264,
    .door_seg3_anims_030156C0         = (struct AnimationTable*) &door_seg3_anims_030156C0,
    .dorrie_seg6_anims_0600F638       = (struct AnimationTable*) &dorrie_seg6_anims_0600F638,
    .eyerok_seg5_anims_050116E4       = (struct AnimationTable*) &eyerok_seg5_anims_050116E4,
    .flyguy_seg8_anims_08011A64       = (struct AnimationTable*) &flyguy_seg8_anims_08011A64,
    .goomba_seg8_anims_0801DA4C       = (struct AnimationTable*) &goomba_seg8_anims_0801DA4C,
    .heave_ho_seg5_anims_0501534C     = (struct AnimationTable*) &heave_ho_seg5_anims_0501534C,
    .hoot_seg5_anims_05005768         = (struct AnimationTable*) &hoot_seg5_anims_05005768,
    .king_bobomb_seg5_anims_0500FE30  = (struct AnimationTable*) &king_bobomb_seg5_anims_0500FE30,
    .klepto_seg5_anims_05008CFC       = (struct AnimationTable*) &klepto_seg5_anims_05008CFC,
    .koopa_flag_seg6_anims_06001028   = (struct AnimationTable*) &koopa_flag_seg6_anims_06001028,
    .koopa_seg6_anims_06011364        = (struct AnimationTable*) &koopa_seg6_anims_06011364,
    .lakitu_enemy_seg5_anims_050144D4 = (struct AnimationTable*) &lakitu_enemy_seg5_anims_050144D4,
    .lakitu_seg6_anims_060058F8       = (struct AnimationTable*) &lakitu_seg6_anims_060058F8,
    .mad_piano_seg5_anims_05009B14    = (struct AnimationTable*) &mad_piano_seg5_anims_05009B14,
    .manta_seg5_anims_05008EB4        = (struct AnimationTable*) &manta_seg5_anims_05008EB4,
    .mips_seg6_anims_06015634         = (struct AnimationTable*) &mips_seg6_anims_06015634,
    .moneybag_seg6_anims_06005E5C     = (struct AnimationTable*) &moneybag_seg6_anims_06005E5C,
    .monty_mole_seg5_anims_05007248   = (struct AnimationTable*) &monty_mole_seg5_anims_05007248,
    .peach_seg5_anims_0501C41C        = (struct AnimationTable*) &peach_seg5_anims_0501C41C,
    .penguin_seg5_anims_05008B74      = (struct AnimationTable*) &penguin_seg5_anims_05008B74,
    .piranha_plant_seg6_anims_0601C31C= (struct AnimationTable*) &piranha_plant_seg6_anims_0601C31C,
    .scuttlebug_seg6_anims_06015064   = (struct AnimationTable*) &scuttlebug_seg6_anims_06015064,
    .seaweed_seg6_anims_0600A4D4      = (struct AnimationTable*) &seaweed_seg6_anims_0600A4D4,
    .skeeter_seg6_anims_06007DE0      = (struct AnimationTable*) &skeeter_seg6_anims_06007DE0,
    .snowman_seg5_anims_0500D118      = (struct AnimationTable*) &snowman_seg5_anims_0500D118,
    .spindrift_seg5_anims_05002D68    = (struct AnimationTable*) &spindrift_seg5_anims_05002D68,
    .spiny_seg5_anims_05016EAC        = (struct AnimationTable*) &spiny_seg5_anims_05016EAC,
    .spiny_egg_seg5_anims_050157E4    = (struct AnimationTable*) &spiny_egg_seg5_anims_050157E4,
    .sushi_seg5_anims_0500AE54        = (struct AnimationTable*) &sushi_seg5_anims_0500AE54,
    .swoop_seg6_anims_060070D0        = (struct AnimationTable*) &swoop_seg6_anims_060070D0,
    .toad_seg6_anims_0600FB58         = (struct AnimationTable*) &toad_seg6_anims_0600FB58,
    .ukiki_seg5_anims_05015784        = (struct AnimationTable*) &ukiki_seg5_anims_05015784,
    .unagi_seg5_anims_05012824        = (struct AnimationTable*) &unagi_seg5_anims_05012824,
    .water_ring_seg6_anims_06013F7C   = (struct AnimationTable*) &water_ring_seg6_anims_06013F7C,
    .whomp_seg6_anims_06020A04        = (struct AnimationTable*) &whomp_seg6_anims_06020A04,
    .wiggler_seg5_anims_0500C874      = (struct AnimationTable*) &wiggler_seg5_anims_0500C874,
    .wiggler_seg5_anims_0500EC8C      = (struct AnimationTable*) &wiggler_seg5_anims_0500EC8C,
    .yoshi_seg5_anims_05024100        = (struct AnimationTable*) &yoshi_seg5_anims_05024100,
};

struct Animation *get_mario_vanilla_animation(u16 index) {
    static struct MarioAnimDmaRelatedThing *marioAnims = (struct MarioAnimDmaRelatedThing *) gMarioAnims;

    if (index < marioAnims->count) {
        struct Animation* anim = (struct Animation*) (gMarioAnims + marioAnims->anim[index].offset);
        if ((uintptr_t) anim->values < (uintptr_t) anim) {
            anim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) anim + (uintptr_t) anim->values);
        }
        if ((uintptr_t) anim->index < (uintptr_t) anim) {
            anim->index = (void *) VIRTUAL_TO_PHYSICAL((u8 *) anim + (uintptr_t) anim->index);
        }
        return anim;
    }
    return NULL;
}

  ///////////////////////
 // custom animations //
///////////////////////

static struct DynamicPool *sAnimationPool = NULL;
static s32 sAnimationIndex = 0;

static struct AnimationInfo *find_animation_info_from_name(const char *name) {
    if (!sAnimationPool) { return NULL; }
    struct DynamicPoolNode *node = sAnimationPool->tail;
    while (node) {
        struct DynamicPoolNode *prev = node->prev;
        struct AnimationInfo *animInfo = (struct AnimationInfo *)node->ptr;
        if (animInfo->name && !strcmp(name, animInfo->name)) { return animInfo; }
        node = prev;
    }
    return NULL;
}

static struct AnimationInfo *find_animation_info(s32 index) {
    if (!sAnimationPool) { return NULL; }
    struct DynamicPoolNode *node = sAnimationPool->tail;
    while (node) {
        struct DynamicPoolNode *prev = node->prev;
        struct AnimationInfo *animInfo = (struct AnimationInfo *)node->ptr;
        if (index == animInfo->index) { return animInfo; }
        node = prev;
    }
    return NULL;
}

static void smlua_anim_util_free_info(struct AnimationInfo *animInfo) {
    if (animInfo->name) {
        free((void *)animInfo->name);
    }
    if (animInfo->anim) {
        if (animInfo->anim->index) {
            free((void *)animInfo->anim->index);
        }
        if (animInfo->anim->values) {
            free((void *)animInfo->anim->values);
        }
        free(animInfo->anim);
    }
}

void smlua_anim_util_reset(void) {
    if (!sAnimationPool) { return; }
    struct DynamicPoolNode *node = sAnimationPool->tail;
    while (node) {
        struct DynamicPoolNode *prev = node->prev;
        struct AnimationInfo *animInfo = (struct AnimationInfo *)node->ptr;
        smlua_anim_util_free_info(animInfo);
        node = prev;
    }
    dynamic_pool_free_pool(sAnimationPool);
    sAnimationIndex = 0;
    sAnimationPool = NULL;
}

struct Animation *smlua_anim_util_get_animation(const char *name) {
    struct Animation *anim = dynos_animation_get(name);
    if (anim) {
        return anim;
    }

    struct AnimationInfo *animInfo = find_animation_info_from_name(name);
    if (animInfo) {
        return animInfo->anim;
    }

    LOG_LUA_LINE("smlua_anim_util_get: Failed to find animation with name '%s'", name);
    return NULL;
}

struct AnimationTable *smlua_anim_util_get_table(const char *name) {
    struct AnimationTable *animTable = dynos_animation_table_get(name);
    if (!animTable) {
        LOG_LUA_LINE("smlua_anim_util_get_table: Failed to find animation table with name '%s'", name);
    }
    return animTable;
}

static u16 *smlua_anim_util_to_u16_list(lua_State* L, int index, u32* length) {

    // Get number of values
    *length = lua_rawlen(L, index);
    if (!*length) { LOG_LUA("smlua_to_u16_list: Table must not be empty"); return NULL; }
    u16 *values = calloc(*length, sizeof(u16));

    // Retrieve values
    lua_pushnil(L);
    s32 top = lua_gettop(L);
    while (lua_next(L, index) != 0) {
        int indexKey = lua_gettop(L) - 1;
        int indexValue = lua_gettop(L) - 0;

        lua_Integer key = smlua_to_integer(L, indexKey);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("smlua_to_u16_list: Failed to convert table key");
            free(values);
            return 0;
        }

        if (key < 1 || key > *length) {
            LOG_LUA("smlua_to_u16_list: Table key out of bounds: " LUA_INTEGER_FMT, key);
            free(values);
            return 0;
        }

        u16 value = smlua_to_integer(L, indexValue);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("smlua_to_u16_list: Failed to convert table value");
            free(values);
            return 0;
        }

        values[key - 1] = value;
        lua_settop(L, top);
    }
    lua_settop(L, top);
    return values;
}

static s32 smlua_anim_util_register_animation_internal(const char *name, s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, LuaTable values, LuaTable index) {
    // Initialize animation pool
    if (!sAnimationPool) {
        sAnimationPool = dynamic_pool_init();
    }
    
    lua_State *L = gLuaState;
    
    lua_rawgeti(L, LUA_REGISTRYINDEX, values);
    s32 valuesIdx = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, index);
    s32 indexIdx = lua_gettop(L);

    u32 valuesLength;
    u16 *valuesList = smlua_anim_util_to_u16_list(L, valuesIdx, &valuesLength);
    if (!valuesList) {
        LOG_LUA_LINE("smlua_anim_util_register_animation: Failed to allocate values buffer");
        lua_pop(L, 2);
        luaL_unref(L, LUA_REGISTRYINDEX, values);
        luaL_unref(L, LUA_REGISTRYINDEX, index);
        return -1;
    }
    u32 indexLength;
    u16 *indexList = smlua_anim_util_to_u16_list(L, indexIdx, &indexLength);
    if (!indexList) {
        LOG_LUA_LINE("smlua_anim_util_register_animation: Failed to allocate index buffer");
        free(valuesList);
        lua_pop(L, 2);
        luaL_unref(L, LUA_REGISTRYINDEX, values);
        luaL_unref(L, LUA_REGISTRYINDEX, index);
        return -1;
    }

    lua_pop(L, 2);
    luaL_unref(L, LUA_REGISTRYINDEX, values);
    luaL_unref(L, LUA_REGISTRYINDEX, index);

    // Allocate an animation in the pool
    struct AnimationInfo *animInfo = dynamic_pool_alloc(sAnimationPool, sizeof(struct AnimationInfo));
    if (!animInfo) {
        LOG_LUA_LINE("smlua_anim_util_register_animation: Failed to allocate an animation in the animation pool");
        free(valuesList);
        free(indexList);
        return -1;
    }

    if (name) {
        animInfo->name = strdup(name);
    }

    animInfo->index                   = sAnimationIndex++;
    animInfo->anim                    = calloc(1, sizeof(struct Animation));
    animInfo->anim->flags             = flags;
    animInfo->anim->animYTransDivisor = animYTransDivisor;
    animInfo->anim->startFrame        = startFrame;
    animInfo->anim->loopStart         = loopStart;
    animInfo->anim->loopEnd           = loopEnd;
    animInfo->anim->unusedBoneCount   = 0; //ANIMINDEX_NUMPARTS(indexList);
    animInfo->anim->values            = valuesList;
    animInfo->anim->index             = indexList;
    animInfo->anim->valuesLength      = valuesLength;
    animInfo->anim->indexLength       = indexLength;
    animInfo->anim->length            = 0;

    return animInfo->index;
}

s32 smlua_anim_util_register_animation_with_name(const char *name, s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, LuaTable values, LuaTable index) {
    // Ensure name is not empty
    if (!name) {
        LOG_LUA_LINE("smlua_anim_util_register_animation: Parameter 'name' is invalid");
        luaL_unref(gLuaState, LUA_REGISTRYINDEX, values);
        luaL_unref(gLuaState, LUA_REGISTRYINDEX, index);
        return -1;
    }

    // Check if the name is not already taken
    if (find_animation_info_from_name(name)) {
        LOG_LUA_LINE("smlua_anim_util_register_animation: An animation named '%s' already exists", name);
        luaL_unref(gLuaState, LUA_REGISTRYINDEX, values);
        luaL_unref(gLuaState, LUA_REGISTRYINDEX, index);
        return -1;
    }

    s32 animIndex = smlua_anim_util_register_animation_internal(name, flags, animYTransDivisor, startFrame, loopStart, loopEnd, values, index);

    if (animIndex != -1) {
        LOG_INFO("smlua_anim_util_register_animation: Registered custom animation with name '%s', index %d", name, animIndex);
    }
    return animIndex;
}

s32 smlua_anim_util_register_animation(s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, LuaTable values, LuaTable index) {
    s32 animIndex = smlua_anim_util_register_animation_internal(NULL, flags, animYTransDivisor, startFrame, loopStart, loopEnd, values, index);

    if (animIndex != -1) {
        LOG_INFO("smlua_anim_util_register_animation: Registered custom animation with index %d", animIndex);
    }
    return animIndex;
}

void smlua_anim_util_set_animation_with_name(struct Object *obj, const char *name) {
    if (!name) {
        LOG_LUA_LINE("smlua_anim_util_set_animation: Parameter 'name' is invalid");
        return;
    }

    // Check if the animation exists
    struct AnimationInfo *animInfo = find_animation_info_from_name(name);
    if (!animInfo) {
        LOG_LUA_LINE("smlua_anim_util_set_animation: Animation '%s' doesn't exist", name);
        return;
    }

    // Set animation
    obj->header.gfx.animInfo.curAnim = animInfo->anim;
}

void smlua_anim_util_set_animation_with_index(struct Object *obj, s32 index) {
    // Check if the animation exists
    struct AnimationInfo *animInfo = find_animation_info(index);
    if (!animInfo) {
        LOG_LUA_LINE("smlua_anim_util_set_animation: Animation with index %d doesn't exist", index);
        return;
    }

    // Set animation
    obj->header.gfx.animInfo.curAnim = animInfo->anim;
}

void smlua_anim_util_set_animation(struct Object *obj, struct Animation *anim) {
    // Set animation
    obj->header.gfx.animInfo.curAnim = anim;
}

void smlua_anim_util_set_table(struct Object *obj, struct AnimationTable *animTable) {
    // Set animation
    obj->oAnimations = animTable;
}

const char *smlua_anim_util_get_current_animation_name(struct Object *obj) {
    if (!sAnimationPool) { return NULL; }

    // Check the animations
    struct DynamicPoolNode *node = sAnimationPool->tail;
    while (node) {
        struct DynamicPoolNode *prev = node->prev;
        struct AnimationInfo *animInfo = (struct AnimationInfo *)node->ptr;
        if (animInfo->anim == obj->header.gfx.animInfo.curAnim) { return animInfo->name; }
        node = prev;
    }

    return NULL;
}

s32 smlua_anim_util_get_current_animation_index(struct Object *obj) {
    // Check the animations
    if (!sAnimationPool) { return -1; }

    // Check the animations
    struct DynamicPoolNode *node = sAnimationPool->tail;
    while (node) {
        struct DynamicPoolNode *prev = node->prev;
        struct AnimationInfo *animInfo = (struct AnimationInfo *)node->ptr;
        if (animInfo->anim == obj->header.gfx.animInfo.curAnim) { return animInfo->index; }
        node = prev;
    }

    return -1;
}

struct AnimationInfo *smlua_anim_util_get_current_info(struct Object *obj) {
    // Check the animations
    if (!sAnimationPool) { return NULL; }

    // Check the animations
    struct DynamicPoolNode *node = sAnimationPool->tail;
    while (node) {
        struct DynamicPoolNode *prev = node->prev;
        struct AnimationInfo *animInfo = (struct AnimationInfo *)node->ptr;
        if (animInfo->anim == obj->header.gfx.animInfo.curAnim) { return animInfo; }
        node = prev;
    }

    return NULL;
}
