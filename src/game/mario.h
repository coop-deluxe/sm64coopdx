#ifndef MARIO_H
#define MARIO_H

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"

extern u16 gLocalBubbleCounter;
struct WallCollisionData;

s32 is_anim_at_end(struct MarioState *m);
s32 is_anim_past_end(struct MarioState *m);
s16 set_mario_animation(struct MarioState *m, s32 targetAnimID);
s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel);

s16 set_character_animation(struct MarioState *m, s32 targetAnimID);
s16 set_character_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel);

void set_anim_to_frame(struct MarioState *m, s16 animFrame);
s32 is_anim_past_frame(struct MarioState *m, s16 animFrame);
s16 find_mario_anim_flags_and_translation(struct Object *o, s32 yaw, Vec3s translation);
void update_mario_pos_for_anim(struct MarioState *m);
s16 return_mario_anim_y_translation(struct MarioState *m);
void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags);
void play_mario_jump_sound(struct MarioState *m);
void adjust_sound_for_speed(struct MarioState *m);
void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType);
void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType);
void play_mario_landing_sound(struct MarioState *m, u32 soundBits);
void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits);
void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits);
void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits);
void play_mario_sound(struct MarioState *m, s32 primarySoundBits, s32 scondarySoundBits);
bool mario_is_crouching(struct MarioState *m);
bool mario_can_bubble(struct MarioState* m);
void mario_set_bubbled(struct MarioState* m);
void mario_set_forward_vel(struct MarioState *m, f32 speed);
s32 mario_get_floor_class(struct MarioState *m);
u32 mario_get_terrain_sound_addend(struct MarioState *m);
struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius);
void resolve_and_return_wall_collisions_data(Vec3f pos, f32 offset, f32 radius, struct WallCollisionData* collisionData);
f32 vec3f_find_ceil(Vec3f pos, f32 height, struct Surface **ceil);
f32 vec3f_mario_ceil(Vec3f pos, f32 height, struct Surface **ceil);
s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw);
u32 mario_floor_is_slippery(struct MarioState *m);
s32 mario_floor_is_slope(struct MarioState *m);
s32 mario_floor_is_steep(struct MarioState *m);
f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario);
s16 find_floor_slope(struct MarioState *m, s16 yawOffset);
void update_mario_sound_and_camera(struct MarioState *m);
void set_steep_jump_action(struct MarioState *m);
void set_mario_y_vel_based_on_fspeed(struct MarioState *m, f32 initialVelY, f32 multiplier);
u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg);
s32 set_jump_from_landing(struct MarioState *m);
s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg);
s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg);
s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter);
s32 check_common_action_exits(struct MarioState *m);
s32 check_common_hold_action_exits(struct MarioState *m);
s32 transition_submerged_to_walking(struct MarioState *m);
s32 set_water_plunge_action(struct MarioState *m);
s32 execute_mario_action(UNUSED struct Object *o);
s32 force_idle_state(struct MarioState* m);
void init_single_mario(struct MarioState* m);
void init_mario(void);
void init_mario_single_from_save_file(struct MarioState* m, u16 index);
void init_mario_from_save_file(void);
void set_mario_particle_flags(struct MarioState* m, u32 flags, u8 clear);
void mario_update_wall(struct MarioState* m, struct WallCollisionData* wcd);

#endif // MARIO_H
