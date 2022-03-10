#ifndef SMLUA_OBJ_UTILS_H
#define SMLUA_OBJ_UTILS_H

#include "behavior_table.h"
#include "smlua_model_utils.h"
#include "game/object_list_processor.h"

struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);
struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);

s32 obj_has_behavior_id(struct Object *o, enum BehaviorId behaviorId);
s32 obj_has_model_extended(struct Object *o, enum ModelExtendedId modelId);
void obj_set_model_extended(struct Object *o, enum ModelExtendedId modelId);

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

// misc obj helpers

struct SpawnParticlesInfo* obj_get_temp_spawn_particles_info(enum ModelExtendedId modelId);

#endif
