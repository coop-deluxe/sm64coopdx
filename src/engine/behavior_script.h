#ifndef BEHAVIOR_SCRIPT_H
#define BEHAVIOR_SCRIPT_H

#include <PR/ultratypes.h>

#define BHV_PROC_CONTINUE 0
#define BHV_PROC_BREAK    1

#define cur_obj_get_int(offset) gCurrentObject->OBJECT_FIELD_S32(offset)
#define cur_obj_get_float(offset) gCurrentObject->OBJECT_FIELD_F32(offset)

#define cur_obj_add_float(offset, value) gCurrentObject->OBJECT_FIELD_F32(offset) += (f32)(value)
#define cur_obj_set_float(offset, value) gCurrentObject->OBJECT_FIELD_F32(offset) = (f32)(value)
#define cur_obj_add_int(offset, value) gCurrentObject->OBJECT_FIELD_S32(offset) += (s32)(value)
#define cur_obj_set_int(offset, value) gCurrentObject->OBJECT_FIELD_S32(offset) = (s32)(value)
#define cur_obj_or_int(offset, value)  gCurrentObject->OBJECT_FIELD_S32(offset) |= (s32)(value)
#define cur_obj_and_int(offset, value) gCurrentObject->OBJECT_FIELD_S32(offset) &= (s32)(value)
#define cur_obj_set_vptr(offset, value) gCurrentObject->OBJECT_FIELD_VPTR(offset) = (void *)(value)

#define obj_and_int(object, offset, value) object->OBJECT_FIELD_S32(offset) &= (s32)(value)

/* |description|Generates a pseudo random integer between 0 and 65535|descriptionEnd| */
u16 random_u16(void);
/* |description|Generates a pseudo random float between 0.0 and 1.0|descriptionEnd| */
float random_float(void);
/* |description|Returns either 1 or -1 with a pseudo 50:50 chance|descriptionEnd| */
s32 random_sign(void);

void stub_behavior_script_2(void);

void cur_obj_update(void);

/* |description|Updates an object's graphical position and angle|descriptionEnd| */
void obj_update_gfx_pos_and_angle(struct Object *obj);

/* |description|Sets the current object's position to random integers between 0 and 65536|descriptionEnd| */
u16 position_based_random_u16(void);
/* |description|Sets the current object's position to random floats between 0.0 and 1.0|descriptionEnd| */
f32 position_based_random_float_position(void);
/* |description|Gets the draw distance scalar|descriptionEnd| */
f32 draw_distance_scalar(void);

#endif // BEHAVIOR_SCRIPT_H
