#ifndef SMLUA_ANIM_UTILS_H
#define SMLUA_ANIM_UTILS_H

#include "types.h"
#include "pc/lua/smlua.h"

typedef struct AnimationTable ObjectAnimPointer;

struct GlobalObjectAnimations {
    ObjectAnimPointer* amp_seg8_anims_08004034;
    ObjectAnimPointer* birds_seg5_anims_050009E8;
    ObjectAnimPointer* blargg_seg5_anims_0500616C;
    ObjectAnimPointer* blue_fish_seg3_anims_0301C2B0;
    ObjectAnimPointer* bobomb_seg8_anims_0802396C;
    ObjectAnimPointer* bookend_seg5_anims_05002540;
    ObjectAnimPointer* bowser_key_seg3_anims_list;
    ObjectAnimPointer* bowser_seg6_anims_06057690;
    ObjectAnimPointer* bub_seg6_anims_06012354;
    ObjectAnimPointer* bully_seg5_anims_0500470C;
    ObjectAnimPointer* butterfly_seg3_anims_030056B0;
    ObjectAnimPointer* castle_grounds_seg7_anims_flags;
    ObjectAnimPointer* chain_chomp_seg6_anims_06025178;
    ObjectAnimPointer* chair_seg5_anims_05005784;
    ObjectAnimPointer* chilly_chief_seg6_anims_06003994;
    ObjectAnimPointer* chuckya_seg8_anims_0800C070;
    ObjectAnimPointer* clam_shell_seg5_anims_05001744;
    ObjectAnimPointer* cyan_fish_seg6_anims_0600E264;
    ObjectAnimPointer* door_seg3_anims_030156C0;
    ObjectAnimPointer* dorrie_seg6_anims_0600F638;
    ObjectAnimPointer* eyerok_seg5_anims_050116E4;
    ObjectAnimPointer* flyguy_seg8_anims_08011A64;
    ObjectAnimPointer* goomba_seg8_anims_0801DA4C;
    ObjectAnimPointer* heave_ho_seg5_anims_0501534C;
    ObjectAnimPointer* hoot_seg5_anims_05005768;
    ObjectAnimPointer* king_bobomb_seg5_anims_0500FE30;
    ObjectAnimPointer* klepto_seg5_anims_05008CFC;
    ObjectAnimPointer* koopa_flag_seg6_anims_06001028;
    ObjectAnimPointer* koopa_seg6_anims_06011364;
    ObjectAnimPointer* lakitu_enemy_seg5_anims_050144D4;
    ObjectAnimPointer* lakitu_seg6_anims_060058F8;
    ObjectAnimPointer* mad_piano_seg5_anims_05009B14;
    ObjectAnimPointer* manta_seg5_anims_05008EB4;
    ObjectAnimPointer* mips_seg6_anims_06015634;
    ObjectAnimPointer* moneybag_seg6_anims_06005E5C;
    ObjectAnimPointer* monty_mole_seg5_anims_05007248;
    ObjectAnimPointer* peach_seg5_anims_0501C41C;
    ObjectAnimPointer* penguin_seg5_anims_05008B74;
    ObjectAnimPointer* piranha_plant_seg6_anims_0601C31C;
    ObjectAnimPointer* scuttlebug_seg6_anims_06015064;
    ObjectAnimPointer* seaweed_seg6_anims_0600A4D4;
    ObjectAnimPointer* skeeter_seg6_anims_06007DE0;
    ObjectAnimPointer* snowman_seg5_anims_0500D118;
    ObjectAnimPointer* spindrift_seg5_anims_05002D68;
    ObjectAnimPointer* spiny_seg5_anims_05016EAC;
    ObjectAnimPointer* spiny_egg_seg5_anims_050157E4;
    ObjectAnimPointer* sushi_seg5_anims_0500AE54;
    ObjectAnimPointer* swoop_seg6_anims_060070D0;
    ObjectAnimPointer* toad_seg6_anims_0600FB58;
    ObjectAnimPointer* ukiki_seg5_anims_05015784;
    ObjectAnimPointer* unagi_seg5_anims_05012824;
    ObjectAnimPointer* water_ring_seg6_anims_06013F7C;
    ObjectAnimPointer* whomp_seg6_anims_06020A04;
    ObjectAnimPointer* wiggler_seg5_anims_0500C874;
    ObjectAnimPointer* wiggler_seg5_anims_0500EC8C;
    ObjectAnimPointer* yoshi_seg5_anims_05024100;
};

extern struct GlobalObjectAnimations gGlobalObjectAnimations;

struct AnimationInfo {
    const char *name;
    s32 index;
    struct Animation *anim;
};

/* |description|Gets a vanilla mario Animation with `index`|descriptionEnd| */
struct Animation *get_mario_vanilla_animation(u16 index);

void smlua_anim_util_reset();

/* |description|Gets the animation with `name` and returns an `Animation`|descriptionEnd| */
struct Animation *smlua_anim_util_get_animation(const char *name);
/* |description|Gets the animation table with `name` and returns an `AnimationTable`|descriptionEnd| */
struct AnimationTable *smlua_anim_util_get_table(const char *name);
/* |description|Registers an animation with `name` and returns the index, returns -1 on failure|descriptionEnd| */
OVERLOAD(smlua_anim_util_register_animation) s32 smlua_anim_util_register_animation_with_name(const char *name, s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, LuaTable values, LuaTable index);
/* |description|Registers an animation and returns the index, returns -1 on failure|descriptionEnd| */
OVERLOAD(smlua_anim_util_register_animation) s32 smlua_anim_util_register_animation(s16 flags, s16 animYTransDivisor, s16 startFrame, s16 loopStart, s16 loopEnd, LuaTable values, LuaTable index);
/* |description|Sets the animation of `obj` to the animation with `name` |descriptionEnd| */
OVERLOAD(smlua_anim_util_set_animation) void smlua_anim_util_set_animation_with_name(struct Object *obj, const char *name);
/* |description|Sets the animation of `obj` to the animation with `index` |descriptionEnd| */
OVERLOAD(smlua_anim_util_set_animation) void smlua_anim_util_set_animation_with_index(struct Object *obj, s32 index);
/* |description|Sets the animation of `obj` to `anim` |descriptionEnd| */
OVERLOAD(smlua_anim_util_set_animation) void smlua_anim_util_set_animation(struct Object *obj, struct Animation *anim);
/* |description|Sets the animation table of `obj` to `animTable` |descriptionEnd| */
void smlua_anim_util_set_table(struct Object *obj, struct AnimationTable *animTable);
/* |description|Gets the name of the current animation of `obj`, returns `nil` if there's no name|descriptionEnd| */
const char *smlua_anim_util_get_current_animation_name(struct Object *obj);
/* |description|Gets the index of the current animation of `obj`, returns -1 if there's no index|descriptionEnd| */
s32 smlua_anim_util_get_current_animation_index(struct Object *obj);
/* |description|Gets the info of the current animation of `obj`, returns `nil` if there's no info|descriptionEnd| */
struct AnimationInfo *smlua_anim_util_get_current_info(struct Object *obj);

#endif
