#ifndef INTERACTION_H
#define INTERACTION_H

#include <PR/ultratypes.h>

#include "types.h"

#define INTERACT_UNKNOWN_08 (1 <<  8)

enum InteractionType {
    INTERACT_HOOT           = /* 0x00000001 */ (1 <<  0),
    INTERACT_GRABBABLE      = /* 0x00000002 */ (1 <<  1),
    INTERACT_DOOR           = /* 0x00000004 */ (1 <<  2),
    INTERACT_DAMAGE         = /* 0x00000008 */ (1 <<  3),
    INTERACT_COIN           = /* 0x00000010 */ (1 <<  4),
    INTERACT_CAP            = /* 0x00000020 */ (1 <<  5),
    INTERACT_POLE           = /* 0x00000040 */ (1 <<  6),
    INTERACT_KOOPA          = /* 0x00000080 */ (1 <<  7),
    INTERACT_SPINY_WALKING  = /* 0x00000100 */ (1 <<  8),
    INTERACT_BREAKABLE      = /* 0x00000200 */ (1 <<  9),
    INTERACT_STRONG_WIND    = /* 0x00000400 */ (1 << 10),
    INTERACT_WARP_DOOR      = /* 0x00000800 */ (1 << 11),
    INTERACT_STAR_OR_KEY    = /* 0x00001000 */ (1 << 12),
    INTERACT_WARP           = /* 0x00002000 */ (1 << 13),
    INTERACT_CANNON_BASE    = /* 0x00004000 */ (1 << 14),
    INTERACT_BOUNCE_TOP     = /* 0x00008000 */ (1 << 15),
    INTERACT_WATER_RING     = /* 0x00010000 */ (1 << 16),
    INTERACT_BULLY          = /* 0x00020000 */ (1 << 17),
    INTERACT_FLAME          = /* 0x00040000 */ (1 << 18),
    INTERACT_KOOPA_SHELL    = /* 0x00080000 */ (1 << 19),
    INTERACT_BOUNCE_TOP2    = /* 0x00100000 */ (1 << 20),
    INTERACT_MR_BLIZZARD    = /* 0x00200000 */ (1 << 21),
    INTERACT_HIT_FROM_BELOW = /* 0x00400000 */ (1 << 22),
    INTERACT_TEXT           = /* 0x00800000 */ (1 << 23),
    INTERACT_TORNADO        = /* 0x01000000 */ (1 << 24),
    INTERACT_WHIRLPOOL      = /* 0x02000000 */ (1 << 25),
    INTERACT_CLAM_OR_BUBBA  = /* 0x04000000 */ (1 << 26),
    INTERACT_BBH_ENTRANCE   = /* 0x08000000 */ (1 << 27),
    INTERACT_SNUFIT_BULLET  = /* 0x10000000 */ (1 << 28),
    INTERACT_SHOCK          = /* 0x20000000 */ (1 << 29),
    INTERACT_IGLOO_BARRIER  = /* 0x40000000 */ (1 << 30),
    INTERACT_PLAYER         = /* 0x80000000 */ (1 << 31),
};

enum InteractionFlag {
    INT_GROUND_POUND          = /* 0x00000001 */ (1 << 0),
    INT_PUNCH                 = /* 0x00000002 */ (1 << 1),
    INT_KICK                  = /* 0x00000004 */ (1 << 2),
    INT_TRIP                  = /* 0x00000008 */ (1 << 3),
    INT_SLIDE_KICK            = /* 0x00000010 */ (1 << 4),
    INT_FAST_ATTACK_OR_SHELL  = /* 0x00000020 */ (1 << 5),
    INT_HIT_FROM_ABOVE        = /* 0x00000040 */ (1 << 6),
    INT_HIT_FROM_BELOW        = /* 0x00000080 */ (1 << 7),
    INT_TWIRL                 = /* 0x00000100 */ (1 << 8),
    INT_GROUND_POUND_OR_TWIRL = (INT_GROUND_POUND | INT_TWIRL),
    INT_LUA                   = /* 0x10000000 */ (1 << 31) ,
};

#define INT_ATTACK_NOT_FROM_BELOW       (INT_GROUND_POUND_OR_TWIRL | INT_PUNCH | INT_KICK | INT_TRIP | INT_SLIDE_KICK | INT_FAST_ATTACK_OR_SHELL | INT_HIT_FROM_ABOVE)
#define INT_ANY_ATTACK                  (INT_GROUND_POUND_OR_TWIRL | INT_PUNCH | INT_KICK | INT_TRIP | INT_SLIDE_KICK | INT_FAST_ATTACK_OR_SHELL | INT_HIT_FROM_ABOVE | INT_HIT_FROM_BELOW)
#define INT_ATTACK_NOT_WEAK_FROM_ABOVE  (INT_GROUND_POUND_OR_TWIRL | INT_PUNCH | INT_KICK | INT_TRIP | INT_HIT_FROM_BELOW)
#define INT_ATTACK_SLIDE                (INT_SLIDE_KICK | INT_FAST_ATTACK_OR_SHELL)

// INTERACT_WARP
#define INT_SUBTYPE_FADING_WARP 0x00000001

// Damaging interactions
#define INT_SUBTYPE_DELAY_INVINCIBILITY 0x00000002
#define INT_SUBTYPE_BIG_KNOCKBACK 0x00000008 /* Used by Bowser, sets Mario's forward velocity to 40 on hit */

// INTERACT_GRABBABLE
#define INT_SUBTYPE_GRABS_MARIO 0x00000004 /* Also makes the object heavy */
#define INT_SUBTYPE_HOLDABLE_NPC 0x00000010 /* Allows the object to be gently dropped, and sets vertical speed to 0 when dropped with no forwards velocity */
#define INT_SUBTYPE_DROP_IMMEDIATELY 0x00000040 /* This gets set by grabbable NPCs that talk to Mario to make him drop them after the dialog is finished */
#define INT_SUBTYPE_KICKABLE 0x00000100
#define INT_SUBTYPE_NOT_GRABBABLE 0x00000200 /* Used by Heavy-Ho to allow it to throw Mario, without Mario being able to pick it up */

// INTERACT_DOOR
#define INT_SUBTYPE_STAR_DOOR 0x00000020

//INTERACT_BOUNCE_TOP
#define INT_SUBTYPE_TWIRL_BOUNCE 0x00000080

// INTERACT_STAR_OR_KEY
#define INT_SUBTYPE_NO_EXIT 0x00000400
#define INT_SUBTYPE_GRAND_STAR 0x00000800

// INTERACT_TEXT
#define INT_SUBTYPE_SIGN 0x00001000
#define INT_SUBTYPE_NPC 0x00004000

// INTERACT_CLAM_OR_BUBBA
#define INT_SUBTYPE_EATS_MARIO 0x00002000


#define ATTACK_PUNCH                 1
#define ATTACK_KICK_OR_TRIP          2
#define ATTACK_FROM_ABOVE            3
#define ATTACK_GROUND_POUND_OR_TWIRL 4
#define ATTACK_FAST_ATTACK           5
#define ATTACK_FROM_BELOW            6

#define INT_STATUS_ATTACK_MASK 0x000000FF

#define INT_STATUS_HOOT_GRABBED_BY_MARIO (1 <<  0) /* 0x00000001 */
#define INT_STATUS_MARIO_UNK1            (1 <<  1) /* 0x00000002 */
#define INT_STATUS_MARIO_UNK2            (1 <<  2) /* 0x00000004 */
#define INT_STATUS_MARIO_DROP_OBJECT     (1 <<  3) /* 0x00000008 */
#define INT_STATUS_HIT_BY_SHOCKWAVE      (1 <<  4) /* 0x00000010 */
#define INT_STATUS_MARIO_UNK5            (1 <<  5) /* 0x00000020 */
#define INT_STATUS_MARIO_UNK6            (1 <<  6) /* 0x00000040 */
#define INT_STATUS_MARIO_UNK7            (1 <<  7) /* 0x00000080 */
#define INT_STATUS_GRABBED_MARIO         (1 << 11) /* 0x00000800 */
#define INT_STATUS_ATTACKED_MARIO        (1 << 13) /* 0x00002000 */
#define INT_STATUS_WAS_ATTACKED          (1 << 14) /* 0x00004000 */
#define INT_STATUS_INTERACTED            (1 << 15) /* 0x00008000 */
#define INT_STATUS_TRAP_TURN             (1 << 20) /* 0x00100000 */
#define INT_STATUS_HIT_MINE              (1 << 21) /* 0x00200000 */
#define INT_STATUS_STOP_RIDING           (1 << 22) /* 0x00400000 */
#define INT_STATUS_TOUCHED_BOB_OMB       (1 << 23) /* 0x00800000 */

extern s16 gInteractionInvulnerable;
extern u8 gPssSlideStarted;

u32 interact_coin(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_water_ring(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_star_or_key(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_bbh_entrance(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_warp(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_warp_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_cannon_base(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_player(struct MarioState* m, UNUSED u32 interactType, struct Object* o);
u32 interact_igloo_barrier(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_tornado(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_whirlpool(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_strong_wind(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_flame(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_snufit_bullet(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_clam_or_bubba(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_bully(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_shock(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_mr_blizzard(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_hit_from_below(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_bounce_top(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_spiny_walking(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_damage(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_breakable(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_koopa_shell(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_pole(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_hoot(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_cap(struct MarioState *m, UNUSED u32 interactType, struct Object *o);
u32 interact_grabbable(struct MarioState *m, u32 interactType, struct Object *o);
u32 interact_text(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

s16 mario_obj_angle_to_object(struct MarioState *m, struct Object *o);
void mario_stop_riding_object(struct MarioState *m);
void mario_grab_used_object(struct MarioState *m);
void mario_drop_held_object(struct MarioState *m);
void mario_throw_held_object(struct MarioState *m);
void mario_stop_riding_and_holding(struct MarioState *m);
u32 does_mario_have_normal_cap_on_head(struct MarioState *m);
void mario_blow_off_cap(struct MarioState *m, f32 capSpeed);
u32 mario_lose_cap_to_enemy(struct MarioState* m, u32 arg);
void mario_retrieve_cap(struct MarioState* m);
struct Object *mario_get_collided_object(struct MarioState *m, u32 interactType);
u32 mario_check_object_grab(struct MarioState *m);
u32 get_door_save_file_flag(struct Object *door);
void mario_process_interactions(struct MarioState *m);
void mario_handle_special_floors(struct MarioState *m);
u8 passes_pvp_interaction_checks(struct MarioState* attacker, struct MarioState* victim);
u32 should_push_or_pull_door(struct MarioState *m, struct Object *o);
u32 take_damage_and_knock_back(struct MarioState *m, struct Object *o);
u32 get_mario_cap_flag(struct Object *capObject);
u32 determine_interaction(struct MarioState *m, struct Object *o);
u32 process_interaction(struct MarioState *m, u32 interactType, struct Object *o, u32 (*interact_function)(struct MarioState *, u32 interactType, struct Object *));

#endif // INTERACTION_H
