#ifndef SMLUA_OBJ_UTILS_H
#define SMLUA_OBJ_UTILS_H

#include "behavior_table.h"
#include "smlua_model_utils.h"
#include "game/object_list_processor.h"

struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);

// this is too dangerous for now
//struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z);

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

#endif
