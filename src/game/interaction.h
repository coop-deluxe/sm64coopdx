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

#define PVP_ATTACK_KNOCKBACK_TIMER_DEFAULT          10
#define PVP_ATTACK_KNOCKBACK_TIMER_OVERRIDE         -5
#define PVP_ATTACK_OVERRIDE_VANILLA_INVINCIBILITY   0x0000FFFF

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

/* |description|
Handles Mario's interaction with coins. Collecting a coin increases Mario's coin count and heals him slightly.
Useful for score, and coin management
|descriptionEnd| */
u32 interact_coin(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interactions with water rings that heal Mario. Passing through water rings increases his health counter.
Useful for underwater stages
|descriptionEnd| */
u32 interact_water_ring(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with Stars or Keys. If Mario collects a star or key, it triggers a specific star grab cutscene and progression is updated. Also handles no-exit variants (like the wing cap stage star).
Useful for the main progression system of collecting Stars and unlocking new areas
|descriptionEnd| */
u32 interact_star_or_key(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles Mario's interaction with the Boo's Big Haunt (BBH) entrance object. When Mario tries to enter the BBH area, this function determines the resulting action (e.g., a jump or spin entrance)
|descriptionEnd| */
u32 interact_bbh_entrance(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with warps, including warp pipes and hole warps. If Mario steps onto a warp, he either transitions into another area or level.
Useful for connecting different parts of the game world and controlling transitions between levels as well as custom warp areas
|descriptionEnd| */
u32 interact_warp(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with warp doors that lead to other areas or require keys. If Mario can open the door (has enough stars or a key), he proceeds. Otherwise, it may show a dialog.
Useful for restricting access to certain areas based on progression
|descriptionEnd| */
u32 interact_warp_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction when Mario touches a door. If Mario meets the star requirement or has the key, he can unlock/open the door. Otherwise, it may display dialog indicating the requirement.
Useful for controlling access to locked areas and providing progression gating in the game
|descriptionEnd| */
u32 interact_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction when Mario touches a cannon base. If the cannon is ready, Mario enters the cannon, triggering a special action and camera behavior.
Useful for transitioning to cannon-aiming mode and enabling cannon travel within levels
|descriptionEnd| */
u32 interact_cannon_base(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with another player (in multiplayer scenarios). 
Checks if Mario and another player collide and resolves any special behavior like bouncing on top.
Useful for multiplayer interactions, such as PvP or cooperative gameplay mechanics
|descriptionEnd| */
u32 interact_player(struct MarioState* m, UNUSED u32 interactType, struct Object* o);

/* |description|
Handles interaction with the igloo barrier found in Snowman's Land. If Mario runs into the barrier, this function pushes him away and prevents passage without the vanish cap.
Useful for enforcing require-caps to access certain areas
|descriptionEnd| */
u32 interact_igloo_barrier(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with tornados. If Mario touches a tornado, he enters a spinning twirl action, losing control temporarily.
Useful for desert levels or areas where environmental hazards lift Mario into the air
|descriptionEnd| */
u32 interact_tornado(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with whirlpools. If Mario gets caught in a whirlpool, he's pulled toward it, resulting in a unique "caught" action.
Useful for hazards that trap Mario like whirlpools
|descriptionEnd| */
u32 interact_whirlpool(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with strong wind gusts. These gusts push Mario back, often knocking him off platforms or sending him flying backwards.
Useful for environmental wind hazards
|descriptionEnd| */
u32 interact_strong_wind(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with flame objects. If Mario touches a flame and is not invulnerable or protected by certain caps, he takes damage and may be set on fire, causing a burning jump.
Useful for simulating fire damage and hazards in levels
|descriptionEnd| */
u32 interact_flame(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with Snufit bullets (projectiles fired by certain enemies). If Mario is not protected, he takes damage. Otherwise, the bullet can be destroyed
|descriptionEnd| */
u32 interact_snufit_bullet(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interactions with objects like Clams or Bubbas, which can damage Mario or, in Bubba's case, eat Mario.
If Bubba eats Mario, it triggers a unique "caught" action. Otherwise, it deals damage and knockback if hit by a Clam
|descriptionEnd| */
u32 interact_clam_or_bubba(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with Bully enemies. Determines if Mario attacks the Bully or gets knocked back. Updates Mario's velocity and state accordingly, and can defeat the Bully if attacked successfully.
Useful for enemy encounters that involve pushing and shoving mechanics rather than just stomping like the bullies
|descriptionEnd| */
u32 interact_bully(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with shocking objects. If Mario touches an electrified enemy or hazard, he takes damage and may be stunned or shocked.
Useful for electric-themed enemies and obstacles
|descriptionEnd| */
u32 interact_shock(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with Mr. Blizzard (the snowman enemy) or similar objects. 
If Mario is attacked or collides with Mr. Blizzard, it applies damage and knockback if not protected or attacking
|descriptionEnd| */
u32 interact_mr_blizzard(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interactions where Mario hits an object from below (e.g., hitting a block from underneath). Determines if Mario damages/destroys the object, or if it damages Mario.
Useful for handling upward attacks, hitting coin blocks, or interacting with certain NPCs from below
|descriptionEnd| */
u32 interact_hit_from_below(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interactions where Mario bounces off the top of an object (e.g., Goombas, Koopas). 
Checks if Mario attacks the object from above and applies the appropriate knockback, sound effects, and object state changes.
Useful for enemy defeat mechanics and platform bouncing
|descriptionEnd| */
u32 interact_bounce_top(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with Spiny-walking enemies. If Mario attacks it (e.g., by punching), the enemy is hurt. If he fails to attack properly (say bouncing on top), Mario takes damage and knockback.
Useful for enemies that cannot be stomped from above and require direct attacks
|descriptionEnd| */
u32 interact_spiny_walking(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles damaging interactions from various objects (e.g., enemies, hazards). If Mario takes damage, it applies knockback and reduces health.
Useful for enemy attacks, environmental hazards, and managing damage related behaviors
|descriptionEnd| */
u32 interact_damage(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interactions with breakable objects (e.g., breakable boxes or bob-ombs). If Mario hits the object with a valid attack (like a punch or kick), the object is destroyed or changes state.
Useful for managing collectible items hidden in breakable objects and level progression through destructible blocks or walls
|descriptionEnd| */
u32 interact_breakable(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction when Mario touches a Koopa Shell. If conditions are met, Mario can hop onto the shell and start riding it, changing his movement mechanics.
Useful for implementing Koopa Shell behavior
|descriptionEnd| */
u32 interact_koopa_shell(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with poles (e.g., climbing poles). If Mario runs into a vertical pole, he can grab it and start climbing.
Useful for platforming mechanics
|descriptionEnd| */
u32 interact_pole(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with Hoot, the owl. If Mario can grab onto Hoot, this sets Mario onto a riding action, allowing him to fly around the level.
Useful for special traversal mechanics and shortcuts within a course
|descriptionEnd| */
u32 interact_hoot(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction when Mario picks up a cap object. This includes normal caps, wing caps, vanish caps, and metal caps.
Updates Mario's state (e.g., cap timers, sound effects) and may initiate putting on the cap animation.
Useful for managing cap statuses
|descriptionEnd| */
u32 interact_cap(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Handles interaction with grabbable objects (e.g., crates, small enemies, or Bowser). Checks if Mario can pick up the object and initiates the grab action if possible.
Useful for course mechanics, throwing items, and Bowser
|descriptionEnd| */
u32 interact_grabbable(struct MarioState *m, u32 interactType, struct Object *o);

/* |description|
Handles interaction with signs, NPCs, and other text-bearing objects. If Mario presses the interact button facing them, he enters a dialog reading state.
Useful for managing hints, story elements, or gameplay instructions through in-game dialogue
|descriptionEnd| */
u32 interact_text(struct MarioState *m, UNUSED u32 interactType, struct Object *o);

/* |description|
Calculates the angle between Mario and a specified object. Used for determining Mario's orientation relative to the object.
Useful for deciding directions between Mario and NPCs
|descriptionEnd| */
s16 mario_obj_angle_to_object(struct MarioState *m, struct Object *o);

/* |description|
Stops Mario from riding any currently ridden object (e.g., a Koopa shell or Hoot), updating the object's interaction status and Mario's state.
Useful for cleanly dismounting ridden objects
|descriptionEnd| */
void mario_stop_riding_object(struct MarioState *m);

/* |description|
Grabs the object currently referenced by Mario's `usedObj` if it's not already being held. 
Changes the object's state to indicate it is now held by Mario.
Useful for handling the moment Mario successfully picks up an object
|descriptionEnd| */
void mario_grab_used_object(struct MarioState *m);

/* |description|
Causes Mario to drop the object he is currently holding. Sets the held object's state accordingly and places it in front of Mario.
Useful for releasing carried objects, such as throwing Bob-ombs or setting down crates
|descriptionEnd| */
void mario_drop_held_object(struct MarioState *m);

/* |description|
Throws the object Mario is currently holding. The object is placed in front of Mario and given a forward velocity. 
Useful for attacking enemies with thrown objects, solving puzzles by throwing crates, or interacting with environment items
|descriptionEnd| */
void mario_throw_held_object(struct MarioState *m);

/* |description|
Causes Mario to stop riding any object (like a shell or Hoot) and also drop any held object. 
Resets related states to ensure Mario is no longer attached to or holding anything.
Useful when changing Mario's state after certain actions, transitions, or to prevent exploits
|descriptionEnd| */
void mario_stop_riding_and_holding(struct MarioState *m);

/* |description|
Checks if Mario is currently wearing his normal cap on his head. 
Returns true if Mario's flag state matches that of having the normal cap equipped on his head, otherwise false.
Useful for determining Mario's cap status
|descriptionEnd| */
u32 does_mario_have_normal_cap_on_head(struct MarioState *m);

/* |description|
Makes Mario blow off his normal cap at a given speed. 
Removes the normal cap from Mario's head and spawns it as a collectible object in the game world.
Useful for simulating events where Mario loses his cap due to enemy attacks or environmental forces
|descriptionEnd| */
void mario_blow_off_cap(struct MarioState *m, f32 capSpeed);

/* |description|
Makes Mario lose his normal cap to an enemy, such as Klepto or Ukiki. Updates flags so that the cap is no longer on Mario's head.
Returns true if Mario was wearing his normal cap, otherwise false.
Useful for scenarios where enemies steal Mario's cap
|descriptionEnd| */
u32 mario_lose_cap_to_enemy(struct MarioState* m, u32 arg);

/* |description|
Retrieves Mario's normal cap if it was previously lost. 
Removes the cap from Mario's hand state and places it on his head.
Useful when Mario recovers his normal cap from enemies, finds it in a level, or if it were to disappear
|descriptionEnd| */
void mario_retrieve_cap(struct MarioState* m);

/* |description|
Returns a collided object that matches a given interaction type from Mario's current collision data.
Useful for determining which object Mario has come into contact with
|descriptionEnd| */
struct Object *mario_get_collided_object(struct MarioState *m, u32 interactType);

/* |description|
Checks if Mario can grab the currently encountered object (usually triggered when Mario punches or dives). If conditions are met, initiates the grabbing process.
Useful for picking up objects, throwing enemies, or grabbing special items
|descriptionEnd| */
u32 mario_check_object_grab(struct MarioState *m);

/* |description|
Retrieves the save file flag associated with a door, based on the number of stars required to open it.
Used to check if the player has unlocked certain star doors or progressed far enough to access new areas
|descriptionEnd| */
u32 get_door_save_file_flag(struct Object *door);

void mario_process_interactions(struct MarioState *m);
void mario_handle_special_floors(struct MarioState *m);

/* |description|
Checks if the necessary conditions are met for one player to successfully attack another player in a PvP scenario.
Considers factors like invincibility, action states, and whether the attack is valid.
Useful for multiplayer where players can harm each other
|descriptionEnd| */
u8 passes_pvp_interaction_checks(struct MarioState* attacker, struct MarioState* victim);

/* |description|
Determines whether Mario should push or pull a door when he interacts with it, based on his orientation and position.
Useful for animating door interactions realistically, depending on which side Mario approaches from
|descriptionEnd| */
u32 should_push_or_pull_door(struct MarioState *m, struct Object *o);

/* |description|
Handles the logic of Mario taking damage and being knocked back by a damaging object. 
Decreases Mario's health, sets his knockback state, and triggers appropriate sound and camera effects.
Useful for implementing enemy attacks, hazards, and ensuring Mario receives proper feedback upon taking damage
|descriptionEnd| */
u32 take_damage_and_knock_back(struct MarioState *m, struct Object *o);

/* |description|
Determines the type of cap an object represents. Depending on the object's behavior, it returns a cap type (normal, metal, wing, vanish).
Useful for handling the logic of picking up, wearing, or losing different kinds of caps
|descriptionEnd| */
u32 get_mario_cap_flag(struct Object *capObject);

/* |description|
Determines how Mario interacts with a given object based on his current action, position, and other state variables. 
Calculates the appropriate interaction type (e.g., punch, kick, ground pound) that should result from Mario's contact with the specified object (`o`).
Useful for handling different types of player-object collisions, attacks, and object behaviors
|descriptionEnd| */
u32 determine_interaction(struct MarioState *m, struct Object *o);

u32 process_interaction(struct MarioState *m, u32 interactType, struct Object *o, u32 (*interact_function)(struct MarioState *, u32 interactType, struct Object *));

#endif // INTERACTION_H
