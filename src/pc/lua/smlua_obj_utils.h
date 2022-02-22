#ifndef SMLUA_OBJ_UTILS_H
#define SMLUA_OBJ_UTILS_H

#include "behavior_table.h"
#include "smlua_model_utils.h"

struct Object* spawn_object_sync(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z);

#endif
