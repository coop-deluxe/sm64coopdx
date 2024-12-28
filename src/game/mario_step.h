#ifndef MARIO_STEP_H
#define MARIO_STEP_H

#include <PR/ultratypes.h>

#include "types.h"

struct BullyCollisionData {
  /*0x00*/ f32 conversionRatio;
  /*0x04*/ f32 radius;
  /*0x08*/ f32 posX;
  /*0x0C*/ f32 posZ;
  /*0x10*/ f32 velX;
  /*0x14*/ f32 velZ;
};

extern struct Surface gWaterSurfacePseudoFloor;

/* |description|Always returns zero. May have been originally used for beta trampolines|descriptionEnd| */
f32 get_additive_y_vel_for_jumps(void);
void stub_mario_step_1(struct MarioState *);
void stub_mario_step_2(void);

/* |description|Reflects Mario off a wall if he is colliding with one and flips forward velocity if `negateSpeed` is TRUE |descriptionEnd| */
void mario_bonk_reflection(struct MarioState *m, u8 negateSpeed);
void transfer_bully_speed(struct BullyCollisionData *obj1, struct BullyCollisionData *obj2);
BAD_RETURN(s32) init_bully_collision_data(struct BullyCollisionData *data, f32 posX, f32 posZ,
                                          f32 forwardVel, s16 yaw, f32 conversionRatio, f32 radius);
/* |description|Updates Mario's state in quicksand, sinks him at `sinkingSpeed` if he's in non instant quicksand|descriptionEnd| */
u32 mario_update_quicksand(struct MarioState *m, f32 sinkingSpeed);
/* |description|Pushes Mario off a steep floor and sets his action to `action` with `actionArg`|descriptionEnd| */
u32 mario_push_off_steep_floor(struct MarioState *m, u32 action, u32 actionArg);
/* |description|Pushes Mario in the direction of the quicksand based on the floor surface|descriptionEnd| */
u32 mario_update_moving_sand(struct MarioState *m);
/* |description|Pushes Mario in the direction of the wind based on the floor surface|descriptionEnd| */
u32 mario_update_windy_ground(struct MarioState *m);
/* |description|Sets all of Mario's velocity variables to 0 and sets his Y position to the floor height|descriptionEnd| */
void stop_and_set_height_to_floor(struct MarioState *m);
/* |description|Performs a full Mario stationary physics step (4 substeps) and returns an `GROUND_STEP_*` result|descriptionEnd| */
s32 stationary_ground_step(struct MarioState *m);
/* |description|Performs a full Mario ground physics step (4 substeps) and returns an `GROUND_STEP_*` result|descriptionEnd| */
s32 perform_ground_step(struct MarioState *m);
/* |description|Performs a full Mario air physics step (4 substeps) and returns an `AIR_STEP_*` result|descriptionEnd| */
s32 perform_air_step(struct MarioState *m, u32 stepArg);

/* |description|Sets Mario's velocity to his forward velocity multiplied by the cosine and sine of his pitch and yaw|descriptionEnd| */
void set_vel_from_pitch_and_yaw(struct MarioState* m);

#endif // MARIO_STEP_H
