#ifndef SMLUA_OBJ_UTILS_H
#define SMLUA_OBJ_UTILS_H

#include "behavior_table.h"
#include "smlua_model_utils.h"
#include "game/object_list_processor.h"

/* |description|
Spawns a synchronized object in at `x`, `y`, and `z` as a child object of the local Mario with his rotation.
You can change the fields of the object in `objSetupFunction`
|descriptionEnd| */
struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);
/* |description|
Spawns a synchronized object in at `x`, `y`, and `z` as a child object of the local Mario with his rotation.
You can change the fields of the object in `objSetupFunction`
|descriptionEnd| */
struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction);

/* |description|Checks if an object has `behaviorId`|descriptionEnd| */
s32 obj_has_behavior_id(struct Object *o, enum BehaviorId behaviorId);
/* |description|Checks if an object's model is equal to `modelId`|descriptionEnd| */
s32 obj_has_model_extended(struct Object *o, enum ModelExtendedId modelId);
/* |description|Returns an object's extended model id|descriptionEnd| */
enum ModelExtendedId obj_get_model_id_extended(struct Object *o);
/* |description|Sets an object's model to `modelId`|descriptionEnd| */
void obj_set_model_extended(struct Object *o, enum ModelExtendedId modelId);

/* |description|Gets a trajectory by `name`|descriptionEnd| */
Trajectory* get_trajectory(const char* name);

//
// Expose various object pointers
//

/* |description|When used in a geo function, retrieve the current processed object|descriptionEnd| */
struct Object *geo_get_current_object(void);
/* |description|Gets the object currently being processed|descriptionEnd| */
struct Object *get_current_object(void);
/* |description|Gets the NPC object Mario is talking to|descriptionEnd| */
struct Object *get_dialog_object(void);
/* |description|Gets the cutscene focus object|descriptionEnd| */
struct Object *get_cutscene_focus(void);
/* |description|Gets the secondary camera focus object|descriptionEnd| */
struct Object *get_secondary_camera_focus(void);
/* |description|Sets the cutscene focus object|descriptionEnd| */
void *set_cutscene_focus(struct Object *o);
/* |description|Sets the secondary camera focus object|descriptionEnd| */
void *set_secondary_camera_focus(struct Object *o);

//
// Helpers to iterate through the object table
//

/* |description|Gets the first object in an object list|descriptionEnd| */
struct Object *obj_get_first(enum ObjectList objList);
/* |description|Gets the first object loaded with `behaviorId`|descriptionEnd| */
struct Object *obj_get_first_with_behavior_id(enum BehaviorId behaviorId);
/* |description|
Gets the first object loaded with `behaviorId` and object signed 32-bit integer field
(look in `object_fields.h` to get the index of a field)
|descriptionEnd| */
struct Object *obj_get_first_with_behavior_id_and_field_s32(enum BehaviorId behaviorId, s32 fieldIndex, s32 value);
/* |description|
Gets the first object loaded with `behaviorId` and object float field
(look in `object_fields.h` to get the index of a field)
|descriptionEnd| */
struct Object *obj_get_first_with_behavior_id_and_field_f32(enum BehaviorId behaviorId, s32 fieldIndex, f32 value);

/* |description|Gets the next object in an object list|descriptionEnd| */
struct Object *obj_get_next(struct Object *o);
/* |description|Gets the next object loaded with the same behavior ID|descriptionEnd| */
struct Object *obj_get_next_with_same_behavior_id(struct Object *o);
/* |description|
Gets the next object loaded with the same behavior ID and object signed 32-bit integer field
(look in `object_fields.h` to get the index of a field)
|descriptionEnd| */
struct Object *obj_get_next_with_same_behavior_id_and_field_s32(struct Object *o, s32 fieldIndex, s32 value);
/* |description|
Gets the next object loaded with the same behavior ID and object float field
(look in `object_fields.h` to get the index of a field)
|descriptionEnd| */
struct Object *obj_get_next_with_same_behavior_id_and_field_f32(struct Object *o, s32 fieldIndex, f32 value);

/* |description|Gets the nearest object with `behaviorId` to `o`|descriptionEnd| */
struct Object *obj_get_nearest_object_with_behavior_id(struct Object *o, enum BehaviorId behaviorId);

/* |description|Counts every object with `behaviorId`|descriptionEnd| */
s32 obj_count_objects_with_behavior_id(enum BehaviorId behaviorId);

/* |description|Gets the corresponding collided object to an index from `o`|descriptionEnd| */
struct Object *obj_get_collided_object(struct Object *o, s16 index);

//
// Object fields
//

/* |description|Gets the unsigned 32-bit integer value from the field corresponding to `fieldIndex`|descriptionEnd| */
u32 obj_get_field_u32(struct Object *o, s32 fieldIndex);
/* |description|Gets the signed 32-bit integer value from the field corresponding to `fieldIndex`|descriptionEnd| */
s32 obj_get_field_s32(struct Object *o, s32 fieldIndex);
/* |description|Sets the float value from the field corresponding to `fieldIndex`|descriptionEnd| */
f32 obj_get_field_f32(struct Object *o, s32 fieldIndex);
/* |description|Gets the signed 32-bit integer value from the sub field corresponding to `fieldSubIndex` from the field corresponding to `fieldIndex`|descriptionEnd| */
s16 obj_get_field_s16(struct Object *o, s32 fieldIndex, s32 fieldSubIndex);

/* |description|Sets the unsigned 32-bit integer value from the field corresponding to `fieldIndex`|descriptionEnd| */
void obj_set_field_u32(struct Object *o, s32 fieldIndex, u32 value);
/* |description|Sets the signed 32-bit integer value from the field corresponding to `fieldIndex`|descriptionEnd| */
void obj_set_field_s32(struct Object *o, s32 fieldIndex, s32 value);
/* |description|Sets the float value from the field corresponding to `fieldIndex`|descriptionEnd| */
void obj_set_field_f32(struct Object *o, s32 fieldIndex, f32 value);
/* |description|Sets the signed 32-bit integer value from the sub field corresponding to `fieldSubIndex` from the field corresponding to `fieldIndex`|descriptionEnd| */
void obj_set_field_s16(struct Object *o, s32 fieldIndex, s32 fieldSubIndex, s16 value);

//
// Misc object helpers
//

/* |description|Returns a temporary particle spawn info pointer with its model loaded in from `modelId`|descriptionEnd| */
struct SpawnParticlesInfo* obj_get_temp_spawn_particles_info(enum ModelExtendedId modelId);
/* |description|Returns a temporary object hitbox pointer|descriptionEnd| */
struct ObjectHitbox* get_temp_object_hitbox(void);

/* |description|Checks if `o` is attackable|descriptionEnd| */
bool obj_is_attackable(struct Object *o);
/* |description|Checks if `o` is breakable|descriptionEnd| */
bool obj_is_breakable_object(struct Object *o);
/* |description|Checks if `o` is a Bully|descriptionEnd| */
bool obj_is_bully(struct Object *o);
/* |description|Checks if `o` is a coin|descriptionEnd| */
bool obj_is_coin(struct Object *o);
/* |description|Checks if `o` is an exclamation box|descriptionEnd| */
bool obj_is_exclamation_box(struct Object *o);
/* |description|Checks if `o` is grabbable|descriptionEnd| */
bool obj_is_grabbable(struct Object *o);
/* |description|Checks if `o` is a 1-Up Mushroom|descriptionEnd| */
bool obj_is_mushroom_1up(struct Object *o);
/* |description|Checks if `o` is a secret|descriptionEnd| */
bool obj_is_secret(struct Object *o);
/* |description|Checks if `o` is activated, tangible, and interactible|descriptionEnd| */
bool obj_is_valid_for_interaction(struct Object *o);

/* |description|Checks if `o1`'s hitbox is colliding with `o2`'s hitbox|descriptionEnd| */
bool obj_check_hitbox_overlap(struct Object *o1, struct Object *o2);
/* |description|Checks if `o`'s hitbox is colliding with the parameters of a hitbox|descriptionEnd| */
bool obj_check_overlap_with_hitbox_params(struct Object *o, f32 x, f32 y, f32 z, f32 h, f32 r, f32 d);

/* |description|Sets an object's velocity to `vx`, `vy`, and `vz`|descriptionEnd| */
void obj_set_vel(struct Object *o, f32 vx, f32 vy, f32 vz);
/* |description|Moves the object in the direction of `dx`, `dy`, and `dz`|descriptionEnd| */
void obj_move_xyz(struct Object *o, f32 dx, f32 dy, f32 dz);

/* |description|Sets the parameters of one of the two whirlpools (0-indexed) in an area|descriptionEnd| */
void set_whirlpools(f32 x, f32 y, f32 z, s16 strength, s16 area, s32 index);

#endif
