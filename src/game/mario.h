#ifndef MARIO_H
#define MARIO_H

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"

extern u16 gLocalBubbleCounter;
struct WallCollisionData;

/* |description|
Checks if Mario's current animation has reached its final frame (i.e., the last valid frame in the animation).
Useful for deciding when to transition out of an animation-driven action
|descriptionEnd| */
s32 is_anim_at_end(struct MarioState *m);

/* |description|
Checks if Mario's current animation has passed the second-to-last valid frame (i.e., effectively at or beyond its final frames).
Useful for advanced checks where slightly early transitions or timing are needed before the final frame
|descriptionEnd| */
s32 is_anim_past_end(struct MarioState *m);

/* |description|
Sets Mario's current animation to `targetAnimID` at a default acceleration (no speed change)
|descriptionEnd| */
s16 set_mario_animation(struct MarioState *m, s32 targetAnimID);

/* |description|
Sets Mario's current animation to `targetAnimID` with a custom `accel` value to speed up or slow down the animation.
Useful for controlling animation timing, e.g., slow-motion or fast-forward effects
|descriptionEnd| */
s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel);

/* |description|
Sets the character-specific animation at its default rate (no acceleration)
|descriptionEnd| */
s16 set_character_animation(struct MarioState *m, enum CharacterAnimID targetAnimID);

/* |description|
Sets a character-specific animation where the animation speed is adjusted by `accel`.
Useful for varying animation speeds based on context or dynamic conditions (e.g., slow-motion)
|descriptionEnd| */
s16 set_character_anim_with_accel(struct MarioState *m, enum CharacterAnimID targetAnimID, s32 accel);

/* |description|
Sets the current animation frame to a specific `animFrame`
|descriptionEnd| */
void set_anim_to_frame(struct MarioState *m, s16 animFrame);

/* |description|
Checks if Mario's current animation is past a specified `animFrame`.
Useful for conditional logic where an action can branch after reaching a specific point in the animation
|descriptionEnd| */
s32 is_anim_past_frame(struct MarioState *m, s16 animFrame);

/* |description|
Retrieves the current animation flags and calculates the translation for Mario's animation, rotating it into the global coordinate system based on `yaw`.
Useful for determining positional offsets from animations (e.g., stepping forward in a walk animation) and applying them to Mario's position
|descriptionEnd| */
s16 find_mario_anim_flags_and_translation(struct Object *o, s32 yaw, Vec3s translation);

/* |description|
Applies the translation from Mario's current animation to his world position. Considers animation flags (horizontal/vertical translation)
|descriptionEnd| */
void update_mario_pos_for_anim(struct MarioState *m);

/* |description|
Determines the vertical translation from Mario's animation (how much the animation moves Mario up or down). Returns the y-component of the animation's translation.
Useful for adjusting Mario's vertical position based on an ongoing animation (e.g., a bounce or jump)
|descriptionEnd| */
s16 return_mario_anim_y_translation(struct MarioState *m);

/* |description|
Plays a sound if Mario does not currently have a specific flag set. Once played, the flag is set to prevent immediate repeats
|descriptionEnd| */
void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags);

/* |description|
Plays Mario’s jump sound if it hasn't been played yet since the last action change. This helps avoid overlapping jump voice lines on repeated jumps
|descriptionEnd| */
void play_mario_jump_sound(struct MarioState *m);

/* |description|
Adjusts the pitch/volume of Mario's movement-based sounds according to his forward velocity (`m.forwardVel`).
Useful for adding dynamic audio feedback based on Mario's running or walking speed
|descriptionEnd| */
void adjust_sound_for_speed(struct MarioState *m);

/* |description|
Plays the specified sound effect and spawns surface-appropriate particles (e.g., water splash, snow, sand). Checks if Mario is metal to adjust audio accordingly
|descriptionEnd| */
void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType);

/* |description|
Plays an action sound once per action, optionally spawning wave or dust particles depending on the surface. This sets the `MARIO_ACTION_SOUND_PLAYED` flag to prevent repeats
|descriptionEnd| */
void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType);

/* |description|
Plays a normal landing sound (or metal landing sound if Mario is metal) and spawns appropriate particle effects (water splash, dust, etc.)
|descriptionEnd| */
void play_mario_landing_sound(struct MarioState *m, u32 soundBits);

/* |description|
A variant of `play_mario_landing_sound` that ensures the sound is only played once per action. Uses `play_mario_action_sound` internally
|descriptionEnd| */
void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits);

/* |description|
Plays a heavier, more forceful landing sound, possibly for ground pounds or large impacts. Takes into account whether Mario has a metal cap equipped.
Useful for making big impact landings stand out aurally
|descriptionEnd| */
void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits);

/* |description|
A variant of `play_mario_heavy_landing_sound` that ensures the sound is only played once per action (using `play_mario_action_sound` internally).
Useful for consistent heavy landing effects without repetition
|descriptionEnd| */
void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits);

/* |description|
Plays a given action sound (like a jump or landing) and also a Mario voice line if certain conditions are met. It manages flags to avoid repeated sounds
|descriptionEnd| */
void play_mario_sound(struct MarioState *m, s32 primarySoundBits, s32 scondarySoundBits);

/* |description|
Returns true if Mario is in any of the crouching or crawling states, checking his current action
|descriptionEnd| */
bool mario_is_crouching(struct MarioState *m);

/* |description|
Checks whether Mario can become bubbled under certain game conditions (multiplayer bubble mechanic). Returns false if already bubbled or if not allowed by settings
|descriptionEnd| */
bool mario_can_bubble(struct MarioState* m);

/* |description|
Transitions Mario into a bubbled state (if available in multiplayer), decrementing lives and preventing normal movement
|descriptionEnd| */
void mario_set_bubbled(struct MarioState* m);

/* |description|
Sets Mario's forward velocity (`m.forwardVel`) and updates `slideVelX/Z` and `m.vel` accordingly, based on `m.faceAngle.y`.
Useful for controlling Mario's speed and direction in various actions (jumping, walking, sliding, etc.)
|descriptionEnd| */
void mario_set_forward_vel(struct MarioState *m, f32 speed);

/* |description|
Retrieves the slipperiness class of Mario's current floor, ranging from not slippery to very slippery. Considers terrain types and special surfaces.
Useful for controlling friction, movement speed adjustments, and whether Mario slips or walks
|descriptionEnd| */
s32 mario_get_floor_class(struct MarioState *m);

/* |description|
Computes a value added to terrain sounds, depending on the floor’s type (sand, snow, water, etc.) and slipperiness. This returns a sound 'addend' used with sound effects.
Useful for playing context-specific footstep or movement sounds
|descriptionEnd| */
u32 mario_get_terrain_sound_addend(struct MarioState *m);

/* |description|
Checks for and resolves wall collisions at a given position `pos`, returning the last wall encountered. Primarily used to prevent Mario from going through walls.
Useful for collision detection when updating Mario’s movement or adjusting his position
|descriptionEnd| */
struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius);

/* |description|
Similar to `resolve_and_return_wall_collisions` but also returns detailed collision data (`WallCollisionData`). This can handle multiple walls and store them for further checks
|descriptionEnd| */
void resolve_and_return_wall_collisions_data(Vec3f pos, f32 offset, f32 radius, struct WallCollisionData* collisionData);

f32 vec3f_find_ceil(Vec3f pos, f32 height, struct Surface **ceil);
f32 vec3f_mario_ceil(Vec3f pos, f32 height, struct Surface **ceil);

/* |description|
Determines if Mario is facing downhill relative to his floor angle, optionally accounting for forward velocity direction. Returns true if he is oriented down the slope.
Useful for deciding if Mario will walk or slide on sloped floors
|descriptionEnd| */
s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw);

/* |description|
Checks whether Mario's current floor is slippery based on both the floor's surface class and Mario's environment (e.g., special slides).
Useful for deciding if Mario should transition to sliding or maintain normal traction
|descriptionEnd| */
u32 mario_floor_is_slippery(struct MarioState *m);

/* |description|
Checks whether Mario's floor is a slope, i.e., not flat but not necessarily steep. This depends on the floor's surface class and angle
|descriptionEnd| */
s32 mario_floor_is_slope(struct MarioState *m);

/* |description|
Checks whether Mario's floor is steep enough to cause special behavior, such as forcing slides or preventing certain actions. Returns true if the slope is too steep.
Useful for restricting normal movement on surfaces with extreme angles
|descriptionEnd| */
s32 mario_floor_is_steep(struct MarioState *m);

/* |description|
Finds the floor height relative to Mario's current position given a polar displacement (`angleFromMario`, `distFromMario`).
Useful for determining height differentials ahead or behind Mario, e.g. for slope checks or collision logic
|descriptionEnd| */
f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario);

/* |description|
Returns a slope angle based on comparing the floor heights slightly in front and behind Mario. It essentially calculates how steep the ground is in a specific yaw direction.
Useful for slope-based calculations such as setting walking or sliding behaviors
|descriptionEnd| */
s16 find_floor_slope(struct MarioState *m, s16 yawOffset);

/* |description|
Updates the background noise and camera modes based on Mario's action. Especially relevant for actions like first-person view or sleeping.
Useful for synchronizing camera behavior and ambient sounds with Mario's state changes
|descriptionEnd| */
void update_mario_sound_and_camera(struct MarioState *m);

/* |description|
Transitions Mario into ACT_STEEP_JUMP if the floor is too steep, adjusting his forward velocity and orientation accordingly.
Useful for forcing special jump states on surfaces exceeding normal slope limits
|descriptionEnd| */
void set_steep_jump_action(struct MarioState *m);

/* |description|
Adjusts Mario's vertical velocity (`m.vel.y`) based on his forward speed. This function also accounts for conditions like quicksand to halve velocity
|descriptionEnd| */
void set_mario_y_vel_based_on_fspeed(struct MarioState *m, f32 initialVelY, f32 multiplier);

/* |description|
Sets Mario's action to the specified `action` and `actionArg`, routing through group-specific transition functions (e.g., airborne actions). Resets sound flags and updates internal timers
|descriptionEnd| */
u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg);

/* |description|
When Mario lands on the ground, decides whether to jump again (single, double, triple) or enter a steep jump if the floor is very steep. Handles quicksand logic as well
|descriptionEnd| */
s32 set_jump_from_landing(struct MarioState *m);

/* |description|
Sets Mario to a jumping action (regular, double, triple, or steep jump) if conditions allow it. If the floor is too steep or if in quicksand, it changes the action accordingly
|descriptionEnd| */
s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg);

/* |description|
Drops any currently held object and sets Mario to a new action. This function is typically used when Mario transitions to states where he cannot hold objects
|descriptionEnd| */
s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg);

/* |description|
Increments Mario's `hurtCounter` and immediately sets a new action. Often used when Mario takes damage and transitions into a knockback or stunned action.
|descriptionEnd| */
s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter);

/* |description|
Checks for inputs that cause common action transitions (jump, freefall, walking, sliding).
Useful for quickly exiting certain stationary actions when Mario begins moving or leaves the floor
|descriptionEnd| */
s32 check_common_action_exits(struct MarioState *m);

/* |description|
Checks for inputs that cause common hold-action transitions (hold jump, hold freefall, hold walking, hold sliding)
|descriptionEnd| */
s32 check_common_hold_action_exits(struct MarioState *m);

/* |description|
Transitions Mario from being underwater to a walking state. Resets camera to the default mode and can handle object-holding states.
Useful for restoring standard ground movement when emerging from water
|descriptionEnd| */
s32 transition_submerged_to_walking(struct MarioState *m);

/* |description|
Transitions Mario into a "water plunge" action, used when he enters water from above. Adjusts position, velocity, and camera mode
|descriptionEnd| */
s32 set_water_plunge_action(struct MarioState *m);

/* |description|
Main driver for Mario's behavior. Executes the current action group (stationary, moving, airborne, etc.) in a loop until no further action changes are necessary
|descriptionEnd| */
s32 execute_mario_action(UNUSED struct Object *o);

/* |description|
Forces Mario into an idle state, either `ACT_IDLE` or `ACT_WATER_IDLE` depending on whether he is submerged.
Useful for quickly resetting Mario's state to an idle pose under special conditions (e.g., cutscene triggers)
|descriptionEnd| */
s32 force_idle_state(struct MarioState* m);

/* |description|
Initializes the fields of a single `MarioState` structure when the player spawns or respawns. Sets starting position, velocity, action, and various internal flags
|descriptionEnd| */
void init_single_mario(struct MarioState* m);

void init_mario(void);
void init_mario_single_from_save_file(struct MarioState* m, u16 index);
void init_mario_from_save_file(void);

/* |description|
Sets Mario's particle flags to spawn various visual effects (dust, water splashes, etc.), with an option to clear or set new flags
|descriptionEnd| */
void set_mario_particle_flags(struct MarioState* m, u32 flags, u8 clear);

/* |description|
Updates Mario's wall information based on wall collisions (`WallCollisionData`). Chooses the most relevant wall depending on the level’s collision fix settings
|descriptionEnd| */
void mario_update_wall(struct MarioState* m, struct WallCollisionData* wcd);

#endif // MARIO_H
