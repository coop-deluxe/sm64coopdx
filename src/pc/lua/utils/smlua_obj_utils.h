#ifndef SMLUA_OBJ_UTILS_H
#define SMLUA_OBJ_UTILS_H

#include "behavior_table.h"
#include "smlua_model_utils.h"
#include "game/object_list_processor.h"

struct Struct802C0DF0 {
    u8 unk0; // Index
    u8 unk1; // Unused
    u8 unk2; // oBehParams1stByte
    u16 model;
    const BehaviorScript *behavior;
};

struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);
struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);

s32 obj_has_behavior_id(struct Object *o, enum BehaviorId behaviorId);
s32 obj_has_model_extended(struct Object *o, enum ModelExtendedId modelId);
void obj_set_model_extended(struct Object *o, enum ModelExtendedId modelId);

Trajectory* get_trajectory(const char* name);

//
// Helpers to iterate through the object table
//

struct Object *obj_get_first(enum ObjectList objList);
struct Object *obj_get_first_with_behavior_id(enum BehaviorId behaviorId);
struct Object *obj_get_first_with_behavior_id_and_field_s32(enum BehaviorId behaviorId, s32 fieldIndex, s32 value);
struct Object *obj_get_first_with_behavior_id_and_field_f32(enum BehaviorId behaviorId, s32 fieldIndex, f32 value);

struct Object *obj_get_next(struct Object *o);
struct Object *obj_get_next_with_same_behavior_id(struct Object *o);
struct Object *obj_get_next_with_same_behavior_id_and_field_s32(struct Object *o, s32 fieldIndex, s32 value);
struct Object *obj_get_next_with_same_behavior_id_and_field_f32(struct Object *o, s32 fieldIndex, f32 value);

struct Object *obj_get_nearest_object_with_behavior_id(struct Object *o, enum BehaviorId behaviorId);

s32 obj_count_objects_with_behavior_id(enum BehaviorId behaviorId);

struct Object *obj_get_collided_object(struct Object *o, s16 index);

// misc obj helpers

struct SpawnParticlesInfo* obj_get_temp_spawn_particles_info(enum ModelExtendedId modelId);
struct ObjectHitbox* get_temp_object_hitbox(void);

bool obj_is_attackable(struct Object *o);
bool obj_is_breakable_object(struct Object *o);
bool obj_is_bully(struct Object *o);
bool obj_is_coin(struct Object *o);
bool obj_is_exclamation_box(struct Object *o);
bool obj_is_grabbable(struct Object *o) ;
bool obj_is_mushroom_1up(struct Object *o);
bool obj_is_secret(struct Object *o);
bool obj_is_valid_for_interaction(struct Object *o);

bool obj_check_hitbox_overlap(struct Object *o1, struct Object *o2);
bool obj_check_overlap_with_hitbox_params(struct Object *o, f32 x, f32 y, f32 z, f32 h, f32 r, f32 d);

void obj_set_vel(struct Object *o, f32 vx, f32 vy, f32 vz);
void obj_move_xyz(struct Object *o, f32 dx, f32 dy, f32 dz);

void set_whirlpools(f32 x, f32 y, f32 z, s16 strength, s16 area, s32 index);

struct Struct802C0DF0* get_exclamation_box_new_contents_pointer(void);
u8 get_exclamation_box_new_contents_size(void);
void set_exclamation_box_new_contents(struct Struct802C0DF0 contents[], u8 size);
void restore_exclamation_box_original_contents(void);

#endif
