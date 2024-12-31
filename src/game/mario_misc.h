#ifndef MARIO_MISC_H
#define MARIO_MISC_H

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"

extern struct GraphNodeObject gMirrorMario[MAX_PLAYERS];
extern struct MarioBodyState gBodyStates[MAX_PLAYERS];

Gfx *geo_draw_mario_head_goddard(s32 callContext, struct GraphNode *node, Mat4 *c);
/* |description|Behavior init function for NPC Toad|descriptionEnd| */
void bhv_toad_message_init(void);
/* |description|Behavior loop function for NPC Toad|descriptionEnd| */
void bhv_toad_message_loop(void);
/* |description|Behavior init function for Star Door unlock object|descriptionEnd| */
void bhv_unlock_door_star_init(void);
/* |description|Behavior loop function for Star Door unlock object|descriptionEnd| */
void bhv_unlock_door_star_loop(void);
/* |description|When used in a geo function, retrieve the MarioState associated to the current processed object|descriptionEnd| */
struct MarioState *geo_get_mario_state(void);
/* |description|When used in a geo function, retrieve the MarioBodyState associated to the current processed object|descriptionEnd| */
struct MarioBodyState *geo_get_body_state(void);
Gfx *geo_mirror_mario_set_alpha(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_switch_mario_stand_run(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx);
Gfx *geo_switch_mario_eyes(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_mario_tilt_torso(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_mario_head_rotation(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_switch_mario_hand(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_mario_hand_foot_scaler(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_switch_mario_cap_effect(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_switch_mario_cap_on_off(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_mario_rotate_wing_cap_wings(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_switch_mario_hand_grab_pos(s32 callContext, struct GraphNode *b, Mat4 *mtx);
Gfx *geo_render_mirror_mario(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx *geo_mirror_mario_backface_culling(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);
Gfx* geo_mario_set_player_colors(s32 callContext, struct GraphNode* node, UNUSED Mat4* c);
Gfx* geo_mario_cap_display_list(s32 callContext, struct GraphNode* node, UNUSED Mat4* c);
Gfx *geo_process_lua_function(s32 callContext, struct GraphNode *node, UNUSED Mat4 *c);

#endif // MARIO_MISC_H
