#include <PR/ultratypes.h>
#include <string.h>

#include "area.h"
#include "actors/common1.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "interaction.h"
#include "level_update.h"
#include "mario.h"
#include "mario_step.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "save_file.h"
#include "seq_ids.h"
#include "sm64.h"
#include "sound_init.h"
#include "rumble_init.h"
#include "object_collision.h"
#include "hardcoded.h"

#include "pc/configfile.h"
#include "pc/network/network.h"
#include "pc/network/lag_compensation.h"
#include "pc/lua/smlua_hooks.h"

u8 sDelayInvincTimer;
s16 gInteractionInvulnerable;

struct InteractionHandler {
    u32 interactType;
    u32 (*handler)(struct MarioState *, u32, struct Object *);
};

static struct InteractionHandler sInteractionHandlers[] = {
    { INTERACT_COIN,           interact_coin },
    { INTERACT_WATER_RING,     interact_water_ring },
    { INTERACT_STAR_OR_KEY,    interact_star_or_key },
    { INTERACT_BBH_ENTRANCE,   interact_bbh_entrance },
    { INTERACT_WARP,           interact_warp },
    { INTERACT_WARP_DOOR,      interact_warp_door },
    { INTERACT_DOOR,           interact_door },
    { INTERACT_CANNON_BASE,    interact_cannon_base },
    { INTERACT_IGLOO_BARRIER,  interact_igloo_barrier },
    { INTERACT_TORNADO,        interact_tornado },
    { INTERACT_WHIRLPOOL,      interact_whirlpool },
    { INTERACT_STRONG_WIND,    interact_strong_wind },
    { INTERACT_FLAME,          interact_flame },
    { INTERACT_SNUFIT_BULLET,  interact_snufit_bullet },
    { INTERACT_CLAM_OR_BUBBA,  interact_clam_or_bubba },
    { INTERACT_BULLY,          interact_bully },
    { INTERACT_SHOCK,          interact_shock },
    { INTERACT_BOUNCE_TOP2,    interact_bounce_top },
    { INTERACT_MR_BLIZZARD,    interact_mr_blizzard },
    { INTERACT_HIT_FROM_BELOW, interact_hit_from_below },
    { INTERACT_BOUNCE_TOP,     interact_bounce_top },
    { INTERACT_DAMAGE,         interact_damage },
    { INTERACT_POLE,           interact_pole },
    { INTERACT_HOOT,           interact_hoot },
    { INTERACT_BREAKABLE,      interact_breakable },
    { INTERACT_KOOPA,          interact_bounce_top },
    { INTERACT_KOOPA_SHELL,    interact_koopa_shell },
    { INTERACT_SPINY_WALKING,  interact_spiny_walking },
    { INTERACT_CAP,            interact_cap },
    { INTERACT_GRABBABLE,      interact_grabbable },
    { INTERACT_TEXT,           interact_text },
    { INTERACT_PLAYER,         interact_player },
};

static u32 sForwardKnockbackActions[][3] = {
    { ACT_SOFT_FORWARD_GROUND_KB, ACT_FORWARD_GROUND_KB, ACT_HARD_FORWARD_GROUND_KB },
    { ACT_FORWARD_AIR_KB,         ACT_FORWARD_AIR_KB,    ACT_HARD_FORWARD_AIR_KB },
    { ACT_FORWARD_WATER_KB,       ACT_FORWARD_WATER_KB,  ACT_FORWARD_WATER_KB },
};

static u32 sBackwardKnockbackActions[][3] = {
    { ACT_SOFT_BACKWARD_GROUND_KB, ACT_BACKWARD_GROUND_KB, ACT_HARD_BACKWARD_GROUND_KB },
    { ACT_BACKWARD_AIR_KB,         ACT_BACKWARD_AIR_KB,    ACT_HARD_BACKWARD_AIR_KB },
    { ACT_BACKWARD_WATER_KB,       ACT_BACKWARD_WATER_KB,  ACT_BACKWARD_WATER_KB },
};

static u8 sDisplayingDoorText = FALSE;
static u8 sJustTeleported = FALSE;
u8 gPssSlideStarted = FALSE;
extern u8 gLastCollectedStarOrKey;

/**
 * Returns the type of cap Mario is wearing.
 */
u32 get_mario_cap_flag(struct Object *capObject) {
    if (!capObject) { return 0; }
    const BehaviorScript *script = virtual_to_segmented(0x13, capObject->behavior);

    if (script == smlua_override_behavior(bhvNormalCap)) {
        return MARIO_NORMAL_CAP;
    } else if (script == smlua_override_behavior(bhvMetalCap)) {
        return MARIO_METAL_CAP;
    } else if (script == smlua_override_behavior(bhvWingCap)) {
        return MARIO_WING_CAP;
    } else if (script == smlua_override_behavior(bhvVanishCap)) {
        return MARIO_VANISH_CAP;
    }

    return 0;
}

/**
 * Returns true if the passed in object has a moving angle yaw
 * in the angular range given towards Mario.
 */
u32 object_facing_mario(struct MarioState *m, struct Object *o, s16 angleRange) {
    if (!m || !o) { return FALSE; }
    f32 dx = m->pos[0] - o->oPosX;
    f32 dz = m->pos[2] - o->oPosZ;

    s16 angleToMario = atan2s(dz, dx);
    s16 dAngle = angleToMario - o->oMoveAngleYaw;

    if (-angleRange <= dAngle && dAngle <= angleRange) {
        return TRUE;
    }

    return FALSE;
}

s16 mario_obj_angle_to_object(struct MarioState *m, struct Object *o) {
    if (!m || !o) { return 0; }
    f32 dx = o->oPosX - m->pos[0];
    f32 dz = o->oPosZ - m->pos[2];

    return atan2s(dz, dx);
}

/**
 * Determines Mario's interaction with a given object depending on their proximity,
 * action, speed, and position.
 */
u32 determine_interaction(struct MarioState *m, struct Object *o) {
    if (!m || !o) { return 0; }

    u32 interaction = 0;
    u32 action = m->action;

    interaction = smlua_get_action_interaction_type(m);

    // hack: make water punch actually do something
    if (interaction == 0 && m->action == ACT_WATER_PUNCH && o->oInteractType & INTERACT_PLAYER) {
        f32 cossFaceAngle0 = coss(m->faceAngle[0]);
        Vec3f facing = { coss(m->faceAngle[1])*cossFaceAngle0, sins(m->faceAngle[0]), sins(m->faceAngle[1])*cossFaceAngle0 };
        Vec3f dif = { o->oPosX - m->pos[0], (o->oPosY + o->hitboxHeight * 0.5) - m->pos[1], o->oPosZ - m->pos[2] };
        vec3f_normalize(dif);
        f32 angle = vec3f_dot(facing, dif);
        // Unknown angle (60 degrees in each direction?)
        if (angle >= 0.5f) {
            interaction = INT_PUNCH;
        }
    }

    if ((interaction == 0 || interaction & INT_LUA) && action & ACT_FLAG_ATTACKING) {
        u32 flags = (MARIO_PUNCHING | MARIO_KICKING | MARIO_TRIPPING);
        if ((action == ACT_PUNCHING || action == ACT_MOVE_PUNCHING || action == ACT_JUMP_KICK) ||
            ((m->flags & flags) && (interaction & INT_LUA))) {
            s16 dYawToObject = mario_obj_angle_to_object(m, o) - m->faceAngle[1];

            if (m->flags & MARIO_PUNCHING) {
                // 120 degrees total, or 60 each way
                if (-0x2AAA <= dYawToObject && dYawToObject <= 0x2AAA) {
                    interaction = INT_PUNCH;
                }
            }
            if (m->flags & MARIO_KICKING) {
                // 120 degrees total, or 60 each way
                if (-0x2AAA <= dYawToObject && dYawToObject <= 0x2AAA) {
                    interaction = INT_KICK;
                }
            }
            if (m->flags & MARIO_TRIPPING) {
                // 180 degrees total, or 90 each way
                if (-0x4000 <= dYawToObject && dYawToObject <= 0x4000) {
                    interaction = INT_TRIP;
                }
            }
        } else if (action == ACT_GROUND_POUND) {
            if (m->vel[1] < 0.0f) {
                interaction = INT_GROUND_POUND;
            }
        } else if (action == ACT_TWIRLING) {
            if (m->vel[1] < 0.0f) {
                interaction = INT_TWIRL;
            }
        } else if (action == ACT_GROUND_POUND_LAND) {
            // Neither ground pounding nor twirling change Mario's vertical speed on landing.,
            // so the speed check is nearly always true (perhaps not if you land while going upwards?)
            // Additionally, actionState it set on each first thing in their action, so this is
            // only true prior to the very first frame (i.e. active 1 frame prior to it run).
            if (m->vel[1] < 0.0f && m->actionState == 0) {
                interaction = INT_GROUND_POUND;
            }
        } else if (action == ACT_TWIRL_LAND) {
            // Neither ground pounding nor twirling change Mario's vertical speed on landing.,
            // so the speed check is nearly always true (perhaps not if you land while going upwards?)
            // Additionally, actionState it set on each first thing in their action, so this is
            // only true prior to the very first frame (i.e. active 1 frame prior to it run).
            if (m->vel[1] < 0.0f && m->actionState == 0) {
                interaction = INT_TWIRL;
            }
        } else if (action == ACT_SLIDE_KICK || action == ACT_SLIDE_KICK_SLIDE) {
            interaction = INT_SLIDE_KICK;
        } else if (action & ACT_FLAG_RIDING_SHELL) {
            interaction = INT_FAST_ATTACK_OR_SHELL;
        } else if (m->forwardVel <= -26.0f || 26.0f <= m->forwardVel) {
            interaction = INT_FAST_ATTACK_OR_SHELL;
        }
    }

    // Prior to this, the interaction type could be overwritten. This requires, however,
    // that the interaction not be set prior. This specifically overrides turning a ground
    // pound into just a bounce.
    if (interaction == 0 && (action & ACT_FLAG_AIR)) {
        if (m->vel[1] < 0.0f) {
            if (m->pos[1] > o->oPosY) {
                interaction = INT_HIT_FROM_ABOVE;
            }
        } else {
            if (m->pos[1] < o->oPosY) {
                interaction = INT_HIT_FROM_BELOW;
            }
        }
    }

    return interaction;
}

/**
 * Sets the interaction types for INT_STATUS_INTERACTED, INT_STATUS_WAS_ATTACKED
 */
u32 attack_object(struct MarioState* m, struct Object *o, s32 interaction) {
    if (!o) { return 0; }
    u32 attackType = 0;
    interaction &= ~INT_LUA;

    switch (interaction) {
        case INT_GROUND_POUND:
        case INT_TWIRL:
        case INT_GROUND_POUND_OR_TWIRL:
            attackType = ATTACK_GROUND_POUND_OR_TWIRL;
            break;
        case INT_PUNCH:
            attackType = ATTACK_PUNCH;
            break;
        case INT_KICK:
        case INT_TRIP:
            attackType = ATTACK_KICK_OR_TRIP;
            break;
        case INT_SLIDE_KICK:
        case INT_FAST_ATTACK_OR_SHELL:
            attackType = ATTACK_FAST_ATTACK;
            break;
        case INT_HIT_FROM_ABOVE:
            attackType = ATTACK_FROM_ABOVE;
            break;
        case INT_HIT_FROM_BELOW:
            attackType = ATTACK_FROM_BELOW;
            break;
    }

    o->oInteractStatus = attackType + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED);

    smlua_call_event_hooks_interact_params_no_ret(HOOK_ON_ATTACK_OBJECT, m, o, interaction);
    return attackType;
}

void mario_stop_riding_object(struct MarioState *m) {
    if (!m) { return; }
    if (m->riddenObj != NULL && m->playerIndex == 0) {
        m->riddenObj->oInteractStatus = INT_STATUS_STOP_RIDING;
        if (m->riddenObj->oSyncID != 0) {
            network_send_object_reliability(m->riddenObj, TRUE);
        }
        stop_shell_music();
        m->riddenObj = NULL;
    }
}

void mario_grab_used_object(struct MarioState *m) {
    if (!m) { return; }
    if (m->usedObj == NULL || m->usedObj->oHeldState == HELD_HELD) { return; }
    if (m->heldObj == NULL && m->usedObj != NULL) {
        // prevent grabbing a non-grabbable object
        if (!(m->usedObj->oInteractType & INTERACT_GRABBABLE)) { return; }
        m->heldObj = m->usedObj;
        m->heldObj->heldByPlayerIndex = m->playerIndex;
        obj_set_held_state(m->heldObj, bhvCarrySomething3);
    }
}

void mario_drop_held_object(struct MarioState *m) {
    if (!m) { return; }
    if (m->playerIndex != 0) { return; }

    if (m->heldObj != NULL) {
        if (m->heldObj->behavior == segmented_to_virtual(smlua_override_behavior(bhvKoopaShellUnderwater))) {
            stop_shell_music();
        }

        obj_set_held_state(m->heldObj, bhvCarrySomething4);

        // ! When dropping an object instead of throwing it, it will be put at Mario's
        // y-positon instead of the HOLP's y-position. This fact is often exploited when
        // cloning objects.
        if (m->marioBodyState) {
            m->heldObj->oPosX = m->marioBodyState->heldObjLastPosition[0];
            m->heldObj->oPosY = m->pos[1];
            m->heldObj->oPosZ = m->marioBodyState->heldObjLastPosition[2];
        }

        m->heldObj->oMoveAngleYaw = m->faceAngle[1];

        if (m->heldObj->oSyncID != 0) {
            network_send_object(m->heldObj);
        }

        m->heldObj = NULL;
    }
}

void mario_throw_held_object(struct MarioState *m) {
    if (!m) { return; }
    if (m->playerIndex != 0) { return; }

    if (m->heldObj != NULL) {
        if (m->heldObj->behavior == segmented_to_virtual(smlua_override_behavior(bhvKoopaShellUnderwater))) {
            if (m->playerIndex == 0) { stop_shell_music(); }
        }

        obj_set_held_state(m->heldObj, bhvCarrySomething5);

        if (m->marioBodyState) {
            m->heldObj->oPosX = m->marioBodyState->heldObjLastPosition[0] + 32.0f * sins(m->faceAngle[1]);
            m->heldObj->oPosY = m->marioBodyState->heldObjLastPosition[1];
            m->heldObj->oPosZ = m->marioBodyState->heldObjLastPosition[2] + 32.0f * coss(m->faceAngle[1]);
        }

        m->heldObj->oMoveAngleYaw = m->faceAngle[1];

        if (m->heldObj->oSyncID != 0) {
            network_send_object(m->heldObj);
        }

        m->heldObj = NULL;
    }
}

void mario_stop_riding_and_holding(struct MarioState *m) {
    if (!m) { return; }
    mario_drop_held_object(m);
    mario_stop_riding_object(m);

    if (m->action == ACT_RIDING_HOOT && m->usedObj != NULL) {
        m->usedObj->oInteractStatus = 0;
        m->usedObj->oHootMarioReleaseTime = gGlobalTimer;
    }
}

u32 does_mario_have_normal_cap_on_head(struct MarioState *m) {
    if (!m) { return FALSE; }
    return (m->flags & (MARIO_CAPS | MARIO_CAP_ON_HEAD)) == (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);
}

void mario_blow_off_cap(struct MarioState *m, f32 capSpeed) {
    if (!m) { return; }
    if (m->playerIndex != 0) { return; }
    struct Object *capObject;

    if (does_mario_have_normal_cap_on_head(m)) {
        m->cap = SAVE_FLAG_CAP_ON_MR_BLIZZARD;

        m->flags &= ~(MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);

        u8 capModel = m->character->capModelId;
        capObject = spawn_object(m->marioObj, capModel, bhvNormalCap);
        if (capObject == NULL) { return; }
        capObject->globalPlayerIndex = gNetworkPlayers[m->playerIndex].globalIndex;
        capObject->oBehParams = m->playerIndex + 1;

        capObject->oPosY += (m->action & ACT_FLAG_SHORT_HITBOX) ? 120.0f : 180.0f;
        capObject->oForwardVel = capSpeed;
        capObject->oMoveAngleYaw = (s16)(m->faceAngle[1] + 0x400);

        if (m->forwardVel < 0.0f) {
            capObject->oMoveAngleYaw = (s16)(capObject->oMoveAngleYaw + 0x8000);
        }

        // set as it's own parent so we can spawn it over the network
        capObject->parentObj = capObject;

        struct Object* spawn_objects[] = { capObject };
        u32 models[] = { capModel };
        network_send_spawn_objects(spawn_objects, models, 1);
    }
}

u32 mario_lose_cap_to_enemy(struct MarioState* m, u32 arg) {
    if (!m) { return FALSE; }
    if (m->playerIndex != 0) { return FALSE; }
    u32 wasWearingCap = FALSE;

    if (does_mario_have_normal_cap_on_head(m)) {
        gMarioStates[0].cap = (arg == 1 ? SAVE_FLAG_CAP_ON_KLEPTO : SAVE_FLAG_CAP_ON_UKIKI);
        m->flags &= ~(MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);
        wasWearingCap = TRUE;
    }

    return wasWearingCap;
}

void mario_retrieve_cap(struct MarioState* m) {
    if (!m) { return; }
    mario_drop_held_object(m);
    save_file_clear_flags(SAVE_FLAG_CAP_ON_KLEPTO | SAVE_FLAG_CAP_ON_UKIKI);
    m->flags &= ~MARIO_CAP_ON_HEAD;
    m->flags |= MARIO_NORMAL_CAP | MARIO_CAP_IN_HAND;
}

u32 able_to_grab_object(struct MarioState *m, UNUSED struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 action = m->action;

    if (action == ACT_DIVE_SLIDE || action == ACT_DIVE) {
        if (!(o->oInteractionSubtype & INT_SUBTYPE_GRABS_MARIO)) {
            return TRUE;
        }
    } else if (action == ACT_PUNCHING || action == ACT_MOVE_PUNCHING) {
        if (m->actionArg < 2) {
            return TRUE;
        }
    }

    return FALSE;
}

struct Object *mario_get_collided_object(struct MarioState *m, u32 interactType) {
    if (!m) { return NULL; }
    s32 i;
    struct Object *object;

    for (i = 0; i < m->marioObj->numCollidedObjs; i++) {
        object = m->marioObj->collidedObjs[i];

        if (object != NULL && object->oInteractType == interactType) {
            return object;
        }
    }

    return NULL;
}

u32 mario_check_object_grab(struct MarioState *m) {
    if (!m) { return 0; }
    u32 result = FALSE;
    const BehaviorScript *script;

    if (m->playerIndex != 0) { return FALSE; }
    if (m->interactObj == NULL || m->interactObj->oHeldState == HELD_HELD) { return FALSE; }

    if (m->input & INPUT_INTERACT_OBJ_GRABBABLE) {
        script = virtual_to_segmented(0x13, m->interactObj->behavior);

        if (script == smlua_override_behavior(bhvBowser)) {
            s16 facingDYaw = m->faceAngle[1] - m->interactObj->oMoveAngleYaw;
            if (facingDYaw >= -0x5555 && facingDYaw <= 0x5555) {
                m->faceAngle[1] = m->interactObj->oMoveAngleYaw;
                m->usedObj = m->interactObj;
                result = set_mario_action(m, ACT_PICKING_UP_BOWSER, 0);
            }
        } else {
            s16 facingDYaw = mario_obj_angle_to_object(m, m->interactObj) - m->faceAngle[1];
            if (facingDYaw >= -0x2AAA && facingDYaw <= 0x2AAA) {
                m->usedObj = m->interactObj;

                if (!(m->action & ACT_FLAG_AIR)) {
                    set_mario_action(
                        m, (m->action & ACT_FLAG_DIVING) ? ACT_DIVE_PICKING_UP : ACT_PICKING_UP, 0);
                }

                result = TRUE;
            }
        }
    }

    return result;
}

u32 bully_knock_back_mario(struct MarioState *mario) {
    if (!mario) { return 0; }
    struct BullyCollisionData marioData;
    struct BullyCollisionData bullyData;
    s16 newMarioYaw;
    s16 newBullyYaw;
    s16 marioDYaw;
    UNUSED s16 bullyDYaw;

    u32 bonkAction = 0;

    struct Object *bully = mario->interactObj;

    //! Conversion ratios multiply to more than 1 (could allow unbounded speed
    // with bonk cancel - but this isn't important for regular bully battery)
    f32 bullyToMarioRatio = bully->hitboxRadius * 3 / 53;
    f32 marioToBullyRatio = 53.0f / bully->hitboxRadius;

    init_bully_collision_data(&marioData, mario->pos[0], mario->pos[2], mario->forwardVel,
                              mario->faceAngle[1], bullyToMarioRatio, 52.0f);

    init_bully_collision_data(&bullyData, bully->oPosX, bully->oPosZ, bully->oForwardVel,
                              bully->oMoveAngleYaw, marioToBullyRatio, bully->hitboxRadius + 2.0f);

    if (mario->forwardVel != 0.0f) {
        transfer_bully_speed(&marioData, &bullyData);
    } else {
        transfer_bully_speed(&bullyData, &marioData);
    }

    newMarioYaw = atan2s(marioData.velZ, marioData.velX);
    newBullyYaw = atan2s(bullyData.velZ, bullyData.velX);

    marioDYaw = newMarioYaw - mario->faceAngle[1];
    bullyDYaw = newBullyYaw - bully->oMoveAngleYaw;

    mario->faceAngle[1] = newMarioYaw;
    mario->forwardVel = sqrtf(marioData.velX * marioData.velX + marioData.velZ * marioData.velZ);
    mario->pos[0] = marioData.posX;
    mario->pos[2] = marioData.posZ;

    bully->oMoveAngleYaw = newBullyYaw;
    bully->oForwardVel = sqrtf(bullyData.velX * bullyData.velX + bullyData.velZ * bullyData.velZ);
    bully->oPosX = bullyData.posX;
    bully->oPosZ = bullyData.posZ;

    if (marioDYaw < -0x4000 || marioDYaw > 0x4000) {
        mario->faceAngle[1] += 0x8000;
        mario->forwardVel *= -1.0f;

        if (mario->action & ACT_FLAG_AIR) {
            bonkAction = ACT_BACKWARD_AIR_KB;
        } else {
            bonkAction = ACT_SOFT_BACKWARD_GROUND_KB;
        }
    } else {
        if (mario->action & ACT_FLAG_AIR) {
            bonkAction = ACT_FORWARD_AIR_KB;
        } else {
            bonkAction = ACT_SOFT_FORWARD_GROUND_KB;
        }
    }

    return bonkAction;
}

void bounce_off_object(struct MarioState *m, struct Object *o, f32 velY) {
    if (!m || !o) { return; }
    m->pos[1] = o->oPosY + o->hitboxHeight;
    m->vel[1] = velY;

    m->flags &= ~MARIO_UNKNOWN_08;

    play_sound(SOUND_ACTION_BOUNCE_OFF_OBJECT, m->marioObj->header.gfx.cameraToObject);
}

void hit_object_from_below(struct MarioState *m, UNUSED struct Object *o) {
    if (!m) { return; }
    m->vel[1] = 0.0f;
    if (m->playerIndex == 0) { set_camera_shake_from_hit(SHAKE_HIT_FROM_BELOW); }
}

static u32 unused_determine_knockback_action(struct MarioState *m) {
    if (!m) { return 0; }
    u32 bonkAction;
    s16 angleToObject = mario_obj_angle_to_object(m, m->interactObj);
    s16 facingDYaw = angleToObject - m->faceAngle[1];

    if (m->forwardVel < 16.0f) {
        m->forwardVel = 16.0f;
    }

    m->faceAngle[1] = angleToObject;

    if (facingDYaw >= -0x4000 && facingDYaw <= 0x4000) {
        m->forwardVel *= -1.0f;
        if (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) {
            bonkAction = ACT_BACKWARD_AIR_KB;
        } else {
            bonkAction = ACT_SOFT_BACKWARD_GROUND_KB;
        }
    } else {
        m->faceAngle[1] += 0x8000;
        if (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) {
            bonkAction = ACT_FORWARD_AIR_KB;
        } else {
            bonkAction = ACT_SOFT_FORWARD_GROUND_KB;
        }
    }

    return bonkAction;
}

u32 determine_knockback_action(struct MarioState *m, UNUSED s32 arg) {
    if (!m) { return 0; }
    if (m->interactObj == NULL) {
        return sForwardKnockbackActions[0][0];
    }

    u32 bonkAction;

    s16 terrainIndex = 0; // 1 = air, 2 = water, 0 = default
    s16 strengthIndex = 0;

    s16 angleToObject = mario_obj_angle_to_object(m, m->interactObj);
    s16 facingDYaw = angleToObject - m->faceAngle[1];
    s16 remainingHealth = m->health - 0x40 * m->hurtCounter;

    if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
        terrainIndex = 2;
    } else if (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) {
        terrainIndex = 1;
    }

    if (remainingHealth < 0x100) {
        strengthIndex = 2;
    } else if (m->interactObj->oDamageOrCoinValue >= 4) {
        strengthIndex = 2;
    } else if (m->interactObj->oDamageOrCoinValue >= 2) {
        strengthIndex = 1;
    }

    m->faceAngle[1] = angleToObject;

    if (terrainIndex == 2) {
        if (m->forwardVel < 28.0f) {
            mario_set_forward_vel(m, 28.0f);
        }

        if (m->pos[1] >= m->interactObj->oPosY) {
            if (m->vel[1] < 20.0f) {
                m->vel[1] = 20.0f;
            }
        } else {
            if (m->vel[1] > 0.0f) {
                m->vel[1] = 0.0f;
            }
        }
    } else {
        if (m->forwardVel < 16.0f) {
            mario_set_forward_vel(m, 16.0f);
        }
    }

    f32 sign = 1.0f;
    if (-0x4000 <= facingDYaw && facingDYaw <= 0x4000) {
        sign = -1.0f;
        m->forwardVel *= -1.0f;
        bonkAction = sBackwardKnockbackActions[terrainIndex][strengthIndex];
    } else {
        m->faceAngle[1] += 0x8000;
        bonkAction = sForwardKnockbackActions[terrainIndex][strengthIndex];
    }

    // set knockback very high when dealing with player attacks
    if (m->interactObj != NULL && (m->interactObj->oInteractType & INTERACT_PLAYER) && terrainIndex != 2) {
        f32 scaler = 1.0f;
        s8 hasBeenPunched = FALSE;
#define IF_REVAMPED_PVP(is, isNot) (gServerSettings.pvpType == PLAYER_PVP_REVAMPED ? (is) : (isNot));
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            struct MarioState* m2 = &gMarioStates[i];
            if (!is_player_active(m2)) { continue; }
            if (m2->marioObj == NULL) { continue; }
            if (m2->marioObj != m->interactObj) { continue; }
            // Redundent check in case the kicking flag somehow gets missed
            if (m2->action == ACT_JUMP_KICK || m2->flags & MARIO_KICKING) { scaler = IF_REVAMPED_PVP(1.9f, 2.0f); }
            else if (m2->action == ACT_DIVE) { scaler = 1.0f + IF_REVAMPED_PVP(m2->forwardVel * 0.005f, 0.0f); }
            else if ((m2->flags & MARIO_PUNCHING)) { scaler = IF_REVAMPED_PVP(-0.1f, 1.0f); hasBeenPunched = gServerSettings.pvpType == PLAYER_PVP_REVAMPED; }
            if (m2->flags & MARIO_METAL_CAP) { scaler *= 1.25f; }
            break;
        }

        if (m->flags & MARIO_METAL_CAP) {
            scaler *= 0.5f;
            if (scaler < 1) { scaler = 1; }
        }

        f32 mag = scaler * (f32)gServerSettings.playerKnockbackStrength * sign;
        m->forwardVel = mag;
        if (sign > 0 && terrainIndex == 1) { mag *= -1.0f; }

        m->vel[0] = (-mag * sins(m->interactObj->oFaceAngleYaw)) * IF_REVAMPED_PVP(1.1f, 1.0f);
        m->vel[1] = ((mag < 0) ? -mag : mag) * IF_REVAMPED_PVP(0.9f, 1.0f);
        m->vel[2] = (-mag * coss(m->interactObj->oFaceAngleYaw)) * IF_REVAMPED_PVP(1.1f, 1.0f);
        m->slideVelX = m->vel[0];
        m->slideVelZ = m->vel[2];
        m->knockbackTimer = hasBeenPunched ? PVP_ATTACK_KNOCKBACK_TIMER_OVERRIDE : PVP_ATTACK_KNOCKBACK_TIMER_DEFAULT;
#undef IF_REVAMPED_PVP
        m->faceAngle[1] = m->interactObj->oFaceAngleYaw + (sign == 1.0f ? 0 : 0x8000);
    }

    return bonkAction;
}

void push_mario_out_of_object(struct MarioState *m, struct Object *o, f32 padding) {
    if (!m || !o) { return; }
    f32 minDistance = o->hitboxRadius + m->marioObj->hitboxRadius + padding;

    f32 offsetX = m->pos[0] - o->oPosX;
    f32 offsetZ = m->pos[2] - o->oPosZ;
    f32 distance = sqrtf(offsetX * offsetX + offsetZ * offsetZ);

    if (distance < minDistance) {
        struct Surface *floor;
        s16 pushAngle;
        f32 newMarioX;
        f32 newMarioZ;

        if (distance == 0.0f) {
            pushAngle = m->faceAngle[1];
        } else {
            pushAngle = atan2s(offsetZ, offsetX);
        }

        newMarioX = o->oPosX + minDistance * sins(pushAngle);
        newMarioZ = o->oPosZ + minDistance * coss(pushAngle);

        f32_find_wall_collision(&newMarioX, &m->pos[1], &newMarioZ, 60.0f, 50.0f);

        find_floor(newMarioX, m->pos[1], newMarioZ, &floor);
        if (floor != NULL) {
            //! Doesn't update Mario's referenced floor (allows oob death when
            // an object pushes you into a steep slope while in a ground action)
            //  <Fixed when gLevelValues.fixCollisionBugs != 0>
            m->pos[0] = newMarioX;
            m->pos[2] = newMarioZ;
            if (gLevelValues.fixCollisionBugs) {
                m->floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &m->floor);
            }
        }
    }
}

void bounce_back_from_attack(struct MarioState *m, u32 interaction) {
    if (!m) { return; }
    if (interaction & (INT_PUNCH | INT_KICK | INT_TRIP)) {
        if (m->action == ACT_PUNCHING) {
            m->action = ACT_MOVE_PUNCHING;
        }

        if (m->action & ACT_FLAG_AIR) {
            mario_set_forward_vel(m, -16.0f);
        } else {
            mario_set_forward_vel(m, -48.0f);
        }

        if (m->playerIndex == 0) { set_camera_shake_from_hit(SHAKE_ATTACK); }
        set_mario_particle_flags(m, PARTICLE_TRIANGLE, FALSE);
    }

    if (interaction & (INT_PUNCH | INT_KICK | INT_TRIP | INT_FAST_ATTACK_OR_SHELL)) {
        play_sound(SOUND_ACTION_HIT_2, m->marioObj->header.gfx.cameraToObject);
    }
}

u32 should_push_or_pull_door(struct MarioState *m, struct Object *o) {
    if (!m || !o) { return 0; }
    f32 dx = o->oPosX - m->pos[0];
    f32 dz = o->oPosZ - m->pos[2];

    s16 dYaw = o->oMoveAngleYaw - atan2s(dz, dx);

    return (dYaw >= -0x4000 && dYaw <= 0x4000) ? 0x00000001 : 0x00000002;
}

u32 take_damage_from_interact_object(struct MarioState *m) {
    if (!m || m->interactObj == NULL) { return 0; }
    s32 shake;
    s32 damage = m->interactObj->oDamageOrCoinValue;

    if (damage >= 4) {
        shake = SHAKE_LARGE_DAMAGE;
    } else if (damage >= 2) {
        shake = SHAKE_MED_DAMAGE;
    } else {
        shake = SHAKE_SMALL_DAMAGE;
    }

    if (!(m->flags & MARIO_CAP_ON_HEAD)) {
        damage += (damage + 1) / 2;
    }

    if (m->flags & MARIO_METAL_CAP) {
        damage = 0;
    }

    // disable player-to-player damage if the server says so
    if (m->interactObj != NULL && m->interactObj->oInteractType & INTERACT_PLAYER) {
        if (gServerSettings.playerInteractions != PLAYER_INTERACTIONS_PVP) {
            damage = 0;
        }
    }

    m->hurtCounter += 4 * damage;

    queue_rumble_data_mario(m, 5, 80);
    if (m->playerIndex == 0) { set_camera_shake_from_hit(shake); }
    return damage;
}

u32 take_damage_and_knock_back(struct MarioState *m, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 damage;

    if (!gInteractionInvulnerable && !(m->flags & MARIO_VANISH_CAP)
        && !(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        o->oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_ATTACKED_MARIO;
        m->interactObj = o;

        damage = take_damage_from_interact_object(m);

        if (o->oInteractionSubtype & INT_SUBTYPE_BIG_KNOCKBACK) {
            m->forwardVel = 40.0f;
        }

        if (o->oDamageOrCoinValue > 0) {
            play_character_sound(m, CHAR_SOUND_ATTACKED);
        }

        update_mario_sound_and_camera(m);
        return drop_and_set_mario_action(m, determine_knockback_action(m, o->oDamageOrCoinValue), damage);
    }

    return FALSE;
}

void reset_mario_pitch(struct MarioState *m) {
    if (!m) { return; }
    if (m->action == ACT_WATER_JUMP || m->action == ACT_SHOT_FROM_CANNON || m->action == ACT_FLYING) {
        if (m->playerIndex == 0) {
            set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
        }
        m->faceAngle[0] = 0;
    }
}

u32 interact_coin(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (m != &gMarioStates[0] || (gDjuiInMainMenu && gCurrLevelNum == LEVEL_TTM)) {
        // only collect locally
        return FALSE;
    }

    m->numCoins += o->oDamageOrCoinValue;
    m->healCounter += 4 * o->oDamageOrCoinValue;

    o->oInteractStatus = INT_STATUS_INTERACTED;

    if (COURSE_IS_MAIN_COURSE(gCurrCourseNum) && m->numCoins - o->oDamageOrCoinValue < gLevelValues.coinsRequiredForCoinStar
        && m->numCoins >= gLevelValues.coinsRequiredForCoinStar) {
        bhv_spawn_star_no_level_exit(m->marioObj, 6, FALSE);
    }

    if (o->oDamageOrCoinValue >= 2) {
        queue_rumble_data_mario(m, 5, 80);
    }

    network_send_collect_coin(o);

    return FALSE;
}

u32 interact_water_ring(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    m->healCounter += 4 * o->oDamageOrCoinValue;
    o->oInteractStatus = INT_STATUS_INTERACTED;
    return FALSE;
}

u32 interact_star_or_key(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    // only allow for local player
    if (m != &gMarioStates[0]) { return FALSE; }

    u32 starIndex;
    u32 starGrabAction = ACT_STAR_DANCE_EXIT;
    u32 noExit = (o->oInteractionSubtype & INT_SUBTYPE_NO_EXIT) != 0;
    u32 grandStar = (o->oInteractionSubtype & INT_SUBTYPE_GRAND_STAR) != 0;

    u8 stayInLevelCommon = !(gCurrLevelNum == LEVEL_BOWSER_1 || gCurrLevelNum == LEVEL_BOWSER_2 || gCurrLevelNum == LEVEL_BOWSER_3);
    if (stayInLevelCommon && gServerSettings.stayInLevelAfterStar) { noExit = TRUE; }
    gLastCollectedStarOrKey = o->behavior == smlua_override_behavior(bhvBowserKey);

    if (m->health >= 0x100) {

        if (gServerSettings.stayInLevelAfterStar != 2) {
            mario_stop_riding_and_holding(m);
        }

        queue_rumble_data_mario(m, 5, 80);

        if (!noExit) {
            m->hurtCounter = 0;
            m->healCounter = 0;
            if (m->capTimer > 1) {
                m->capTimer = 1;
            }
        }

        if (gLevelValues.starHeal) {
            m->healCounter = 31;
            m->hurtCounter = 0;
        }

        if (noExit) {
            starGrabAction = ACT_STAR_DANCE_NO_EXIT;
        }

        if (m->action & ACT_FLAG_SWIMMING) {
            starGrabAction = ACT_STAR_DANCE_WATER;
        }

        if (m->action & ACT_FLAG_METAL_WATER) {
            starGrabAction = ACT_STAR_DANCE_WATER;
        }

        if (m->action & ACT_FLAG_AIR) {
            starGrabAction = ACT_FALL_AFTER_STAR_GRAB;
            if (gLevelValues.floatingStarDance && m->pos[1] - m->floorHeight > 1000) {
                starGrabAction = ACT_STAR_DANCE_WATER;
            }
        }

        if (m->marioObj != NULL) {
            spawn_object(m->marioObj, MODEL_NONE, bhvStarKeyCollectionPuffSpawner);
        }

        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->interactObj = o;
        m->usedObj = o;

        starIndex = (o->oBehParams >> 24) & (gLevelValues.useGlobalStarIds ? 0xFF : 0x1F);

        if (m == &gMarioStates[0]) {
            // sync the star collection
            network_send_collect_star(o, m->numCoins, starIndex);
        }
        save_file_collect_star_or_key(m->numCoins, starIndex, 0);

        s32 numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            gMarioStates[i].numStars = numStars;
        }

        if (!noExit) {
            drop_queued_background_music();
            fadeout_level_music(126);
        }

        play_sound(SOUND_MENU_STAR_SOUND, m->marioObj->header.gfx.cameraToObject);
#ifndef VERSION_JP
        update_mario_sound_and_camera(m);
#endif

        if (grandStar) {
            return set_mario_action(m, ACT_JUMBO_STAR_CUTSCENE, 0);
        }
        save_file_do_save(gCurrSaveFileNum - 1, TRUE);

        if (noExit && gServerSettings.stayInLevelAfterStar == 2) {
            return TRUE;
        }

        return set_mario_action(m, starGrabAction, noExit + 2 * grandStar);
    }

    return FALSE;
}

u32 interact_bbh_entrance(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (m->playerIndex != 0) { return FALSE; }
    if (m->action != ACT_BBH_ENTER_SPIN && m->action != ACT_BBH_ENTER_JUMP) {
        mario_stop_riding_and_holding(m);

        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->interactObj = o;
        m->usedObj = o;

        if (m->action & ACT_FLAG_AIR) {
            return set_mario_action(m, ACT_BBH_ENTER_SPIN, 0);
        }

        return set_mario_action(m, ACT_BBH_ENTER_JUMP, 0);
    }

    return FALSE;
}

u32 interact_warp(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 action;

    if (m->skipWarpInteractionsTimer > 0) {
        return FALSE;
    }

    if (m != &gMarioStates[0]) {
        // don't do for remote players
        return FALSE;
    }

    if (o->oInteractionSubtype & INT_SUBTYPE_FADING_WARP) {
        action = m->action;

        if (action == ACT_TELEPORT_FADE_IN) {
            sJustTeleported = TRUE;

        } else if (!sJustTeleported) {
            if (action == ACT_IDLE || action == ACT_PANTING || action == ACT_STANDING_AGAINST_WALL
                || action == ACT_CROUCHING) {
                m->interactObj = o;
                m->usedObj = o;

                sJustTeleported = TRUE;
                return set_mario_action(m, ACT_TELEPORT_FADE_OUT, 0);
            }
        }
    } else {
        if (m->action != ACT_EMERGE_FROM_PIPE) {
            o->oInteractStatus = INT_STATUS_INTERACTED;
            m->interactObj = o;
            m->usedObj = o;

            if (o->collisionData == segmented_to_virtual(warp_pipe_seg3_collision_03009AC8)) {
                play_sound(SOUND_MENU_ENTER_PIPE, m->marioObj->header.gfx.cameraToObject);
                queue_rumble_data_mario(m, 15, 80);
            } else {
                play_sound(SOUND_MENU_ENTER_HOLE, m->marioObj->header.gfx.cameraToObject);
                queue_rumble_data_mario(m, 12, 80);
            }

            mario_stop_riding_object(m);
            return set_mario_action(m, ACT_DISAPPEARED, (WARP_OP_WARP_OBJECT << 16) + 2);
        }
    }

    return FALSE;
}

u32 display_door_dialog(struct MarioState *m, u32 actionArg) {
    if (!m) { return FALSE; }
    if (m != &gMarioStates[0]) { return FALSE; }
    return (!sDisplayingDoorText) ? set_mario_action(m, ACT_READING_AUTOMATIC_DIALOG, actionArg) : FALSE;
}

u8 prevent_interact_door(struct MarioState* m, struct Object* o) {
    if (!m) { return FALSE; }
    // prevent multiple star/key unlocks on the same door
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct MarioState* m2 = &gMarioStates[i];
        if (m2 == m) { continue; }
        if (!is_player_active(m2)) { continue; }
        Vec3f diff = { 0 };
        vec3f_dif(diff, m->pos, m2->pos);
        if (vec3f_length(diff) > 200 && m2->usedObj != o) { continue; }
        if (m2->action == ACT_UNLOCKING_STAR_DOOR || m2->action == ACT_UNLOCKING_KEY_DOOR) {
            return TRUE;
        }
    }
    return FALSE;
}

u32 interact_warp_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 doorAction = 0;
    u32 saveFlags = save_file_get_flags();
    s16 warpDoorId = o->oBehParams >> 24;
    u32 actionArg;

    if (prevent_interact_door(m, o)) { return FALSE; }

    if (m->action == ACT_WALKING || m->action == ACT_DECELERATING) {
        if (warpDoorId == 1 && !(saveFlags & SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR)) {
            if (!(saveFlags & SAVE_FLAG_HAVE_KEY_2)) {
                if (display_door_dialog(m, (saveFlags & SAVE_FLAG_HAVE_KEY_1) ? gBehaviorValues.dialogs.KeyDoor1HaveDialog : gBehaviorValues.dialogs.KeyDoor1DontHaveDialog)) {
                    sDisplayingDoorText = TRUE;
                }
                return FALSE;
            }

            doorAction = ACT_UNLOCKING_KEY_DOOR;
        }

        if (warpDoorId == 2 && !(saveFlags & SAVE_FLAG_UNLOCKED_BASEMENT_DOOR)) {
            if (!(saveFlags & SAVE_FLAG_HAVE_KEY_1)) {
                if (display_door_dialog(m, (saveFlags & SAVE_FLAG_HAVE_KEY_2) ? gBehaviorValues.dialogs.KeyDoor2HaveDialog : gBehaviorValues.dialogs.KeyDoor2DontHaveDialog)) {
                    sDisplayingDoorText = TRUE;
                }
                return FALSE;
            }

            doorAction = ACT_UNLOCKING_KEY_DOOR;
        }

        if (m->action == ACT_WALKING || m->action == ACT_DECELERATING) {
            actionArg = should_push_or_pull_door(m, o) + 0x00000004;

            if (doorAction == 0) {
                if (actionArg & 0x00000001) {
                    doorAction = ACT_PULLING_DOOR;
                } else {
                    doorAction = ACT_PUSHING_DOOR;
                }
            }

            m->interactObj = o;
            m->usedObj = o;
            return set_mario_action(m, doorAction, actionArg);
        }
    }

    return FALSE;
}

u32 get_door_save_file_flag(struct Object *door) {
    if (door == NULL) { return 0; }
    u32 saveFileFlag = 0;
    s16 requiredNumStars = door->oBehParams >> 24;

    s16 isCcmDoor = door->oPosX < 0.0f;
    s16 isPssDoor = door->oPosY > 500.0f;

    switch (requiredNumStars) {
        case 1:
            if (isPssDoor) {
                saveFileFlag = SAVE_FLAG_UNLOCKED_PSS_DOOR;
            } else {
                saveFileFlag = SAVE_FLAG_UNLOCKED_WF_DOOR;
            }
            break;

        case 3:
            if (isCcmDoor) {
                saveFileFlag = SAVE_FLAG_UNLOCKED_CCM_DOOR;
            } else {
                saveFileFlag = SAVE_FLAG_UNLOCKED_JRB_DOOR;
            }
            break;

        case 8:
            saveFileFlag = SAVE_FLAG_UNLOCKED_BITDW_DOOR;
            break;

        case 30:
            saveFileFlag = SAVE_FLAG_UNLOCKED_BITFS_DOOR;
            break;

        case 50:
            saveFileFlag = SAVE_FLAG_UNLOCKED_50_STAR_DOOR;
            break;
    }

    return saveFileFlag;
}

u32 interact_door(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (m->playerIndex != 0 && o == NULL) { return FALSE; }
    s16 requiredNumStars = o->oBehParams >> 24;
    s16 numStars = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);

    if (o->oAction != 0) { return FALSE; }

    // prevent interacting with the same door as someone unlocking it
    if (prevent_interact_door(m, o)) { return FALSE; }

    if (m->action == ACT_WALKING || m->action == ACT_DECELERATING) {
        if (numStars >= requiredNumStars) {
            u32 actionArg = should_push_or_pull_door(m, o);
            u32 enterDoorAction;
            u32 doorSaveFileFlag;

            if (actionArg & 0x00000001) {
                enterDoorAction = ACT_PULLING_DOOR;
            } else {
                enterDoorAction = ACT_PUSHING_DOOR;
            }

            doorSaveFileFlag = get_door_save_file_flag(o);
            m->interactObj = o;
            m->usedObj = o;

            if (o->oInteractionSubtype & INT_SUBTYPE_STAR_DOOR) {
                enterDoorAction = ACT_ENTERING_STAR_DOOR;
            }

            if (doorSaveFileFlag != 0 && !(save_file_get_flags() & doorSaveFileFlag)) {
                enterDoorAction = ACT_UNLOCKING_STAR_DOOR;
            }

            return set_mario_action(m, enterDoorAction, actionArg);
        } else if (!sDisplayingDoorText) {
            u32 text = gBehaviorValues.dialogs.DoorNeedKeyDialog << 16;

            switch (requiredNumStars) {
                case 1:
                    text = gBehaviorValues.dialogs.DoorNeed1StarDialog << 16;
                    break;
                case 3:
                    text = gBehaviorValues.dialogs.DoorNeed3StarsDialog << 16;
                    break;
                case 8:
                    text = gBehaviorValues.dialogs.DoorNeed8StarsDialog << 16;
                    break;
                case 30:
                    text = gBehaviorValues.dialogs.DoorNeed30StarsDialog << 16;
                    break;
                case 50:
                    text = gBehaviorValues.dialogs.DoorNeed50StarsDialog << 16;
                    break;
                case 70:
                    text = gBehaviorValues.dialogs.DoorNeed70StarsDialog << 16;
                    break;
            }

            text += requiredNumStars - numStars;

            sDisplayingDoorText = TRUE;
            return set_mario_action(m, ACT_READING_AUTOMATIC_DIALOG, text);
        }
    } else if (m->action == ACT_IDLE && sDisplayingDoorText == TRUE && requiredNumStars == 70) {
        m->interactObj = o;
        m->usedObj = o;
        return set_mario_action(m, ACT_ENTERING_STAR_DOOR, should_push_or_pull_door(m, o));
    }

    return FALSE;
}

u32 interact_cannon_base(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (o->oAction != 0) { return FALSE; }
    if (m->playerIndex != 0) { return FALSE; }

    if (m->action != ACT_IN_CANNON) {
        mario_stop_riding_and_holding(m);
        o->oInteractStatus = INT_STATUS_INTERACTED;
        o->oCannonPlayerIndex = 0;
        m->interactObj = o;
        m->usedObj = o;
        return set_mario_action(m, ACT_IN_CANNON, 0);
    }

    return FALSE;
}

static u8 resolve_player_collision(struct MarioState* m, struct MarioState* m2) {
    if (!m || !m2) { return FALSE; }
    if (!m->marioObj || !m2->marioObj) { return FALSE; }
    if (m->invincTimer > 0 || m2->invincTimer > 0) { return FALSE; }
    if (m->action == ACT_DEATH_EXIT_LAND || m2->action == ACT_DEATH_EXIT_LAND) { return FALSE; }

    // move player outside of other player
    f32 extentY = m->marioObj->hitboxHeight;
    f32 radius = m->marioObj->hitboxRadius * 2.0f;

    if (!m->marioBodyState || !m2->marioBodyState) { return FALSE; }
    if (m->marioBodyState->mirrorMario || m2->marioBodyState->mirrorMario) { return FALSE; }

    f32* localTorso = m->marioBodyState->torsoPos;
    f32* remoteTorso = m2->marioBodyState->torsoPos;

    f32 marioRelY = localTorso[1] - remoteTorso[1];
    if (marioRelY < 0) { marioRelY = -marioRelY; }
    if (marioRelY >= extentY) { return FALSE; }


    f32 marioRelX = localTorso[0] - remoteTorso[0];
    f32 marioRelZ = localTorso[2] - remoteTorso[2];
    f32 marioDist = sqrtf(sqr(marioRelX) + sqr(marioRelZ));

    if (marioDist >= radius) { return FALSE; }

    // bounce
    u32 interaction = determine_interaction(m, m2->marioObj);
    if (interaction & INT_HIT_FROM_ABOVE) {
        m2->bounceSquishTimer = max(m2->bounceSquishTimer, 4);

        f32 velY;
        if (m2->action == ACT_CROUCHING) {
            mario_stop_riding_and_holding(m);
            set_mario_action(m, ACT_TWIRLING, 0);
            velY = fmax(fmin(100.0f, 30.0f + fabs(m->vel[1])), 80.0f);
        } else if (m->action == ACT_JUMP) {
            mario_stop_riding_and_holding(m);
            set_mario_action(m, ACT_DOUBLE_JUMP, 0);
            velY = fmax(fmin(55.0f, 15.0f + fabs(m->vel[1])), 35.0f);
        } else if (m->action == ACT_DOUBLE_JUMP) {
            mario_stop_riding_and_holding(m);
            set_mario_action(m, (m->specialTripleJump && m->playerIndex == 0) ? ACT_SPECIAL_TRIPLE_JUMP : m->flags & MARIO_WING_CAP ? ACT_FLYING_TRIPLE_JUMP : ACT_TRIPLE_JUMP, 0);
            velY = fmax(fmin(60.0f, 20.0f + fabs(m->vel[1])), 40.0f);
        } else if (m->action == ACT_LONG_JUMP) {
            velY = fmax(fmin(40.0f, 5.0f + fabs(m->vel[1])), 30.0f);
        } else if (m->action == ACT_HOLD_JUMP || m->action == ACT_HOLD_FREEFALL) {
            set_mario_action(m, ACT_HOLD_JUMP, 0);
            velY = fmax(fmin(40.0f, 15.0f + fabs(m->vel[1])), 25.0f);
        } else {
            mario_stop_riding_and_holding(m);
            set_mario_action(m, ACT_JUMP, 0);
            velY = fmax(fmin(50.0f, 15.0f + fabs(m->vel[1])), 30.0f);
        }
        bounce_off_object(m, m2->marioObj, velY);
        queue_rumble_data_mario(m, 5, 80);
        // don't do further interactions if we've hopped on top
        return TRUE;
    }

    f32 posX = m->pos[0] + (radius - marioDist) / radius * marioRelX;
    f32 posZ = m->pos[2] + (radius - marioDist) / radius * marioRelZ;
    // Prevent a push into out of bounds
    if (find_floor_height(posX, m->pos[1], posZ) == gLevelValues.floorLowerLimit) { return FALSE; }
    m->pos[0] = posX;
    m->pos[2] = posZ;
    m->marioBodyState->torsoPos[0] += (radius - marioDist) / radius * marioRelX;
    m->marioBodyState->torsoPos[2] += (radius - marioDist) / radius * marioRelZ;
    return FALSE;
}

u8 determine_player_damage_value(struct MarioState* attacker, u32 interaction) {
    if (gServerSettings.pvpType == PLAYER_PVP_REVAMPED) {
        if (attacker->action == ACT_GROUND_POUND_LAND) { return 2; }
        else if (interaction & INT_GROUND_POUND) { return 3; }
        else if (interaction & (INT_KICK | INT_SLIDE_KICK | INT_TRIP | INT_TWIRL)) { return 2; }
        else if (interaction & INT_PUNCH && attacker->actionArg < 3) { return 2; }
        else if (attacker->action == ACT_FLYING) { return (u8)(MAX((attacker->forwardVel - 40.0f) / 20.0f, 0)) + 1; }
        return 1;
    } else {
        if (interaction & INT_GROUND_POUND_OR_TWIRL) { return 3; }
        else if (interaction & INT_KICK) { return 2; }
        else if (interaction & INT_ATTACK_SLIDE) { return 1; }
        return 2;
    }
}

u8 player_is_sliding(struct MarioState* m) {
    if (!m) { return FALSE; }
    if (m->action & (ACT_FLAG_BUTT_OR_STOMACH_SLIDE | ACT_FLAG_DIVING)) {
        return TRUE;
    }

    switch (m->action) {
        case ACT_CROUCH_SLIDE:
        case ACT_SLIDE_KICK_SLIDE:
        case ACT_BUTT_SLIDE_AIR:
        case ACT_HOLD_BUTT_SLIDE_AIR:
            return TRUE;
    }
    return FALSE;
}

u8 passes_pvp_interaction_checks(struct MarioState* attacker, struct MarioState* victim) {
    if (!attacker || !victim) { return false; }

    // attacked
    u8 isInCutscene = ((attacker->action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE) || ((victim->action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE);
    isInCutscene = isInCutscene || (attacker->action == ACT_IN_CANNON) || (victim->action == ACT_IN_CANNON);
    u8 isAttackerInvulnerable = (attacker->action & ACT_FLAG_INVULNERABLE) || attacker->invincTimer != 0 || attacker->hurtCounter != 0;
    u8 isInvulnerable = (victim->action & ACT_FLAG_INVULNERABLE) || victim->invincTimer != 0 || victim->hurtCounter != 0 || isInCutscene;
    u8 isIgnoredAttack = (attacker->action == ACT_JUMP || attacker->action == ACT_DOUBLE_JUMP
                          || attacker->action == ACT_LONG_JUMP || attacker->action == ACT_SIDE_FLIP
                          || attacker->action == ACT_BACKFLIP || attacker->action == ACT_TRIPLE_JUMP
                          || attacker->action == ACT_WALL_KICK_AIR || attacker->action == ACT_WATER_JUMP
                          || attacker->action == ACT_STEEP_JUMP || attacker->action == ACT_HOLD_JUMP
                          || attacker->action == ACT_FREEFALL || attacker->action == ACT_LEDGE_GRAB);
    u8 isVictimIntangible = (victim->action & ACT_FLAG_INTANGIBLE);
    u8 isVictimGroundPounding = (victim->action == ACT_GROUND_POUND) && (victim->actionState != 0);
    if (victim->knockbackTimer != 0) {
        return false;
    }

    if (gServerSettings.pvpType == PLAYER_PVP_REVAMPED &&
        (attacker->action == ACT_PUNCHING || attacker->action == ACT_MOVE_PUNCHING) &&
        (victim->action == ACT_BACKWARD_GROUND_KB || victim->action == ACT_FORWARD_GROUND_KB ||
        victim->action == ACT_SOFT_BACKWARD_GROUND_KB || victim->action == ACT_SOFT_FORWARD_GROUND_KB)) {
        return true;
    }

    return (!isInvulnerable && !isIgnoredAttack && !isAttackerInvulnerable && !isVictimIntangible && !isVictimGroundPounding);
}

u32 interact_player(struct MarioState* m, UNUSED u32 interactType, struct Object* o) {
    // don't touch each other on level load
    if (gCurrentArea == NULL || gCurrentArea->localAreaTimer < 60) {
        return FALSE;
    }

    if (!m || !o) { return FALSE; }
    if (!is_player_active(m)) { return FALSE; }
    if (gServerSettings.playerInteractions == PLAYER_INTERACTIONS_NONE) { return FALSE; }
    if (m->action & ACT_FLAG_INTANGIBLE) { return FALSE; }

    struct MarioState* m2 = NULL;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (o == gMarioStates[i].marioObj) {
            if (!is_player_active(&gMarioStates[i])) { return FALSE; }
            m2 = &gMarioStates[i];
            break;
        }
    }
    if (m2 == NULL) { return FALSE; }
    if (m2->action & ACT_FLAG_INTANGIBLE) { return FALSE; }

    // vanish cap players can't interact
    u32 vanishFlags = (MARIO_VANISH_CAP | MARIO_CAP_ON_HEAD);
    if ((m->flags & vanishFlags) == vanishFlags) {
        return FALSE;
    }
    if ((m2->flags & vanishFlags) == vanishFlags) {
        return FALSE;
    }

    // don't do further interactions if we've hopped on top
    if (resolve_player_collision(m, m2)) {
        return FALSE;
    }

    return FALSE;
}

u32 interact_player_pvp(struct MarioState* attacker, struct MarioState* victim) {
    if (!attacker || !victim) { return false; }
    if (!is_player_active(attacker)) { return FALSE; }
    if (!is_player_active(victim)) { return FALSE; }
    if (gServerSettings.playerInteractions == PLAYER_INTERACTIONS_NONE) { return FALSE; }
    if (attacker->action == ACT_JUMBO_STAR_CUTSCENE) { return FALSE; }
    if (victim->action   == ACT_JUMBO_STAR_CUTSCENE) { return FALSE; }

    // vanish cap players can't interact
    u32 vanishFlags = (MARIO_VANISH_CAP | MARIO_CAP_ON_HEAD);
    if ((attacker->flags & vanishFlags) == vanishFlags) { return FALSE; }
    if ((victim->flags   & vanishFlags) == vanishFlags) { return FALSE; }

    // don't attack each other on level load
    if (gCurrentArea == NULL || gCurrentArea->localAreaTimer < 60) { return FALSE; }

    // make sure it passes pvp checks before rollback
    if (!passes_pvp_interaction_checks(attacker, victim)) { return FALSE; }

    // grab the lag compensation version of the victim
    struct MarioState* cVictim = NULL;
    if (victim->playerIndex == 0) {
        cVictim = lag_compensation_get_local_state(&gNetworkPlayers[attacker->playerIndex]);
    }
    if (cVictim == NULL) { cVictim = victim; }

    // make sure we overlap
    f32 overlapScale = (attacker->playerIndex == 0) ? 0.6f : 1.0f;
    if (gServerSettings.pvpType == PLAYER_PVP_REVAMPED && attacker->action == ACT_GROUND_POUND_LAND) {
        overlapScale += 0.3f;
    }
    if (!detect_player_hitbox_overlap(attacker, cVictim, overlapScale)) {
        return FALSE;
    }

#define PLAYER_IN_ROLLOUT_FLIP(m) ((m->action == ACT_FORWARD_ROLLOUT || m->action == ACT_BACKWARD_ROLLOUT) && m->actionState == 1)

    // see if it was an attack
    u32 interaction = determine_interaction(attacker, cVictim->marioObj);
    // Specfically override jump kicks to prevent low damage and low knockback kicks
    if (interaction & INT_HIT_FROM_BELOW && attacker->action == ACT_JUMP_KICK) { interaction = INT_KICK; }
    // Allow rollouts to attack
    else if (PLAYER_IN_ROLLOUT_FLIP(attacker)) { interaction = INT_HIT_FROM_BELOW; }
    if (!(interaction & INT_ANY_ATTACK) || (interaction & INT_HIT_FROM_ABOVE) || !passes_pvp_interaction_checks(attacker, cVictim)) {
        return FALSE;
    }

    // call the Lua hook
    bool allow = true;
    smlua_call_event_hooks_mario_params_ret_bool(HOOK_ALLOW_PVP_ATTACK, attacker, cVictim, interaction, &allow);
    if (!allow) {
        // Lua blocked the interaction
        return FALSE;
    }

    // determine if slide attack should be ignored
    if ((interaction & INT_ATTACK_SLIDE) || player_is_sliding(cVictim)) {
        // determine the difference in velocities
        //Vec3f velDiff;
        //vec3f_dif(velDiff, attacker->vel, cVictim->vel);
        // Allow groundpounds to always hit sliding/fast attacks
        if (gServerSettings.pvpType == PLAYER_PVP_REVAMPED && attacker->action == ACT_GROUND_POUND) {
            // do nothing
        } else {
            if (attacker->action == ACT_SLIDE_KICK_SLIDE || attacker->action == ACT_SLIDE_KICK) {
                // if the difference vectors are not different enough, do not attack
                if (vec3f_length(attacker->vel) < 15) { return FALSE; }
            } else {
                // if the difference vectors are not different enough, do not attack
                if (vec3f_length(attacker->vel) < 40) { return FALSE; }
            }

            u8 forceAllowAttack = FALSE;
            if (gServerSettings.pvpType == PLAYER_PVP_REVAMPED) {
                // Give slidekicks trade immunity by making them (almost) invincible
                // Also give rollout flips immunity to dives
                if ((cVictim->action == ACT_SLIDE_KICK && attacker->action != ACT_SLIDE_KICK) ||
                    (PLAYER_IN_ROLLOUT_FLIP(cVictim) && attacker->action == ACT_DIVE)) {
                    return FALSE;
                } else if ((attacker->action == ACT_SLIDE_KICK) ||
                           (PLAYER_IN_ROLLOUT_FLIP(cVictim) && cVictim->action == ACT_DIVE)) {
                    forceAllowAttack = TRUE;
                }
            }
            // if the victim is going faster, do not attack
            if (vec3f_length(cVictim->vel) > vec3f_length(attacker->vel) && !forceAllowAttack) {
                return FALSE;
            }
        }
    }

#undef PLAYER_IN_ROLLOUT_FLIP

    // determine if ground pound should be ignored
    if (attacker->action == ACT_GROUND_POUND) {
        // not moving down yet?
        if (attacker->actionState == 0) { return FALSE; }
        victim->bounceSquishTimer = max(victim->bounceSquishTimer, 20);
    }

    if (victim->playerIndex == 0) {
        victim->interactObj = attacker->marioObj;
        if (interaction & INT_KICK) {
            if (victim->action == ACT_FIRST_PERSON) {
                // without this branch, the player will be stuck in first person
                raise_background_noise(2);
                set_camera_mode(victim->area->camera, -1, 1);
                victim->input &= ~INPUT_FIRST_PERSON;
            }
            set_mario_action(victim, ACT_FREEFALL, 0);
        }
        if (!(victim->flags & MARIO_METAL_CAP)) {
            attacker->marioObj->oDamageOrCoinValue = determine_player_damage_value(attacker, interaction);
            if (attacker->flags & MARIO_METAL_CAP) { attacker->marioObj->oDamageOrCoinValue *= 2; }
        }
    }

    victim->invincTimer = max(victim->invincTimer, 3);
    take_damage_and_knock_back(victim, attacker->marioObj);
    if (gServerSettings.pvpType != PLAYER_PVP_REVAMPED || !(attacker->flags & MARIO_PUNCHING)) {
        bounce_back_from_attack(attacker, interaction);
    }
    victim->interactObj = NULL;

    smlua_call_event_hooks_mario_params(HOOK_ON_PVP_ATTACK, attacker, victim, interaction);
    return FALSE;
}

u32 interact_igloo_barrier(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    //! Sets used object without changing action (LOTS of interesting glitches,
    // but unfortunately the igloo barrier is the only object with this interaction
    // type)
    m->interactObj = o;
    m->usedObj = o;
    push_mario_out_of_object(m, o, 5.0f);
    return FALSE;
}

u32 interact_tornado(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    struct Object *marioObj = m->marioObj;

    if (m->action != ACT_TORNADO_TWIRLING && m->action != ACT_SQUISHED) {
        mario_stop_riding_and_holding(m);
        mario_set_forward_vel(m, 0.0f);
        update_mario_sound_and_camera(m);

        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->interactObj = o;
        m->usedObj = o;

        marioObj->oMarioTornadoYawVel = 0x400;
        marioObj->oMarioTornadoPosY = m->pos[1] - o->oPosY;

        play_character_sound(m, CHAR_SOUND_WAAAOOOW);
        queue_rumble_data_mario(m, 30, 60);

        return set_mario_action(m, ACT_TORNADO_TWIRLING, m->action == ACT_TWIRLING);
    }

    return FALSE;
}

u32 interact_whirlpool(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    struct Object *marioObj = m->marioObj;

    if (m->action != ACT_CAUGHT_IN_WHIRLPOOL) {
        mario_stop_riding_and_holding(m);
        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->interactObj = o;
        m->usedObj = o;

        m->forwardVel = 0.0f;

        marioObj->oMarioWhirlpoolPosY = m->pos[1] - o->oPosY;

        play_character_sound(m, CHAR_SOUND_WAAAOOOW);
        queue_rumble_data_mario(m, 30, 60);

        return set_mario_action(m, ACT_CAUGHT_IN_WHIRLPOOL, 0);
    }

    return FALSE;
}

u32 interact_strong_wind(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    UNUSED struct Object *marioObj = m->marioObj;

    if (m->action != ACT_GETTING_BLOWN) {
        mario_stop_riding_and_holding(m);
        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->interactObj = o;
        m->usedObj = o;

        m->faceAngle[1] = o->oMoveAngleYaw + 0x8000;
        m->unkC4 = 0.4f;
        m->forwardVel = -24.0f;
        m->vel[1] = 12.0f;

        play_character_sound(m, CHAR_SOUND_WAAAOOOW);
        update_mario_sound_and_camera(m);
        return set_mario_action(m, ACT_GETTING_BLOWN, 0);
    }

    return FALSE;
}

u32 interact_flame(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 burningAction = ACT_BURNING_JUMP;

    if (!gInteractionInvulnerable && !(m->flags & MARIO_METAL_CAP) && !(m->flags & MARIO_VANISH_CAP)
        && !(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        queue_rumble_data_mario(m, 5, 80);

        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->interactObj = o;

        if ((m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER))
            || m->waterLevel - m->pos[1] > 50.0f) {
            play_sound(SOUND_GENERAL_FLAME_OUT, m->marioObj->header.gfx.cameraToObject);
        } else {
            m->marioObj->oMarioBurnTimer = 0;
            update_mario_sound_and_camera(m);
            play_character_sound(m, CHAR_SOUND_ON_FIRE);

            if ((m->action & ACT_FLAG_AIR) && m->vel[1] <= 0.0f) {
                burningAction = ACT_BURNING_FALL;
            }

            return drop_and_set_mario_action(m, burningAction, 1);
        }
    }

    return FALSE;
}

u32 interact_snufit_bullet(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (!gInteractionInvulnerable && !(m->flags & MARIO_VANISH_CAP)) {
        if (m->flags & MARIO_METAL_CAP) {
            o->oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED;
            play_sound(SOUND_ACTION_UNKNOWN458, m->marioObj->header.gfx.cameraToObject);
        } else {
            o->oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_ATTACKED_MARIO;
            m->interactObj = o;
            take_damage_from_interact_object(m);

            play_character_sound(m, CHAR_SOUND_ATTACKED);
            update_mario_sound_and_camera(m);

            return drop_and_set_mario_action(m, determine_knockback_action(m, o->oDamageOrCoinValue),
                                             o->oDamageOrCoinValue);
        }
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return FALSE;
}

u32 interact_clam_or_bubba(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (o->oInteractionSubtype & INT_SUBTYPE_EATS_MARIO) {
        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->interactObj = o;
        return set_mario_action(m, ACT_EATEN_BY_BUBBA, 0);
    } else if (take_damage_and_knock_back(m, o)) {
        return TRUE;
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return TRUE;
}

u32 interact_bully(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    UNUSED u32 unused;

    u32 interaction;
    if (m->flags & MARIO_METAL_CAP) {
        interaction = INT_FAST_ATTACK_OR_SHELL;
    } else {
        interaction = determine_interaction(m, o);
    }

    m->interactObj = o;

    if (interaction & INT_ATTACK_NOT_FROM_BELOW) {
        queue_rumble_data_mario(m, 5, 80);
        push_mario_out_of_object(m, o, 5.0f);

        m->forwardVel = -16.0f;
        o->oMoveAngleYaw = m->faceAngle[1];
        o->oForwardVel = 3392.0f / o->hitboxRadius;

        attack_object(m, o, interaction);
        bounce_back_from_attack(m, interaction);
        return TRUE;
    }

    else if (!gInteractionInvulnerable && !(m->flags & MARIO_VANISH_CAP)
             && !(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        o->oInteractStatus = INT_STATUS_INTERACTED;
        m->invincTimer = 2;

        update_mario_sound_and_camera(m);
        play_character_sound(m, CHAR_SOUND_EEUH);
        play_sound(SOUND_OBJ_BULLY_METAL, m->marioObj->header.gfx.cameraToObject);

        push_mario_out_of_object(m, o, 5.0f);
        drop_and_set_mario_action(m, bully_knock_back_mario(m), 0);
        queue_rumble_data_mario(m, 5, 80);

        return TRUE;
    }

    return FALSE;
}

u32 interact_shock(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (!gInteractionInvulnerable && !(m->flags & MARIO_VANISH_CAP)
        && !(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        u32 actionArg = (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) == 0;

        o->oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_ATTACKED_MARIO;
        m->interactObj = o;

        take_damage_from_interact_object(m);
        play_character_sound(m, CHAR_SOUND_ATTACKED);
        queue_rumble_data_mario(m, 70, 60);

        if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
            return drop_and_set_mario_action(m, ACT_WATER_SHOCKED, 0);
        } else {
            update_mario_sound_and_camera(m);
            return drop_and_set_mario_action(m, ACT_SHOCKED, actionArg);
        }
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return FALSE;
}

static u32 interact_stub(UNUSED struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }
    return FALSE;
}

u32 interact_mr_blizzard(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (take_damage_and_knock_back(m, o)) {
        return TRUE;
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return FALSE;
}

u32 interact_hit_from_below(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    UNUSED u32 unused;

    u32 interaction;
    if (m->flags & MARIO_METAL_CAP) {
        interaction = INT_FAST_ATTACK_OR_SHELL;
    } else {
        interaction = determine_interaction(m, o);
    }

    if (interaction & INT_ANY_ATTACK) {
        queue_rumble_data_mario(m, 5, 80);
        attack_object(m, o, interaction);
        bounce_back_from_attack(m, interaction);

        if (interaction & INT_HIT_FROM_BELOW) {
            hit_object_from_below(m, o);
        }

        if (interaction & INT_HIT_FROM_ABOVE) {
            if (o->oInteractionSubtype & INT_SUBTYPE_TWIRL_BOUNCE) {
                bounce_off_object(m, o, 80.0f);
                reset_mario_pitch(m);
#ifndef VERSION_JP
                play_character_sound(m, CHAR_SOUND_TWIRL_BOUNCE);
#endif
                return drop_and_set_mario_action(m, ACT_TWIRLING, 0);
            } else {
                bounce_off_object(m, o, 30.0f);
            }
        }
    } else if (take_damage_and_knock_back(m, o)) {
        return TRUE;
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return FALSE;
}

u32 interact_bounce_top(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 interaction;
    if (m->flags & MARIO_METAL_CAP) {
        interaction = INT_FAST_ATTACK_OR_SHELL;
    } else {
        interaction = determine_interaction(m, o);
    }

    if (interaction & INT_ATTACK_NOT_FROM_BELOW) {
        queue_rumble_data_mario(m, 5, 80);
        attack_object(m, o, interaction);
        bounce_back_from_attack(m, interaction);

        if (interaction & INT_HIT_FROM_ABOVE) {
            if (o->oInteractionSubtype & INT_SUBTYPE_TWIRL_BOUNCE) {
                bounce_off_object(m, o, 80.0f);
                reset_mario_pitch(m);
#ifndef VERSION_JP
                play_character_sound(m, CHAR_SOUND_TWIRL_BOUNCE);
#endif
                return drop_and_set_mario_action(m, ACT_TWIRLING, 0);
            } else {
                bounce_off_object(m, o, 30.0f);
            }
        }
    } else if (take_damage_and_knock_back(m, o)) {
        return TRUE;
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return FALSE;
}

u32 interact_spiny_walking(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 interaction = determine_interaction(m, o);

    if (interaction & INT_PUNCH) {
        o->oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED | ATTACK_PUNCH;
        bounce_back_from_attack(m, interaction);
    } else if (take_damage_and_knock_back(m, o)) {
        return TRUE;
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return FALSE;
}

u32 interact_damage(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (take_damage_and_knock_back(m, o)) {
        return TRUE;
    }

    if (!(o->oInteractionSubtype & INT_SUBTYPE_DELAY_INVINCIBILITY)) {
        sDelayInvincTimer = TRUE;
    }

    return FALSE;
}

u32 interact_breakable(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 interaction = determine_interaction(m, o);

    if (interaction & INT_ATTACK_NOT_WEAK_FROM_ABOVE) {
        attack_object(m, o, interaction);
        bounce_back_from_attack(m, interaction);

        m->interactObj = o;

        switch (interaction & ~INT_LUA) {
            case INT_HIT_FROM_ABOVE:
                bounce_off_object(m, o, 30.0f); //! Not in the 0x8F mask
                break;

            case INT_HIT_FROM_BELOW:
                hit_object_from_below(m, o);
                break;
        }

        return TRUE;
    }

    return FALSE;
}

u32 interact_koopa_shell(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (m->playerIndex != 0) { return FALSE; }

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        return FALSE;
    }

    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (gMarioStates[i].riddenObj == o) { return FALSE; }
    }

    if (!(m->action & ACT_FLAG_RIDING_SHELL)) {
        u32 interaction = determine_interaction(m, o);

        if (interaction & INT_HIT_FROM_ABOVE || m->action == ACT_WALKING
            || m->action == ACT_HOLD_WALKING) {
            m->interactObj = o;
            m->usedObj = o;
            m->riddenObj = o;

            attack_object(m, o, interaction);
            update_mario_sound_and_camera(m);
            if (m->playerIndex == 0) { play_shell_music(); }
            mario_drop_held_object(m);

            //! Puts Mario in ground action even when in air, making it easy to
            // escape air actions into crouch slide (shell cancel)
            return set_mario_action(m, ACT_RIDING_SHELL_GROUND, 0);
        }

        push_mario_out_of_object(m, o, 2.0f);
    }

    return FALSE;
}

u32 check_object_grab_mario(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if (m != &gMarioStates[0]) { return false; }

    if ((!(m->action & (ACT_FLAG_AIR | ACT_FLAG_INVULNERABLE | ACT_FLAG_ATTACKING)) || !gInteractionInvulnerable)
        && (o->oInteractionSubtype & INT_SUBTYPE_GRABS_MARIO)) {
        if (object_facing_mario(m, o, 0x2AAA)) {
            mario_stop_riding_and_holding(m);
            o->oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_GRABBED_MARIO;

            m->faceAngle[1] = o->oMoveAngleYaw;
            m->interactObj = o;
            m->usedObj = o;

            update_mario_sound_and_camera(m);
            play_character_sound(m, CHAR_SOUND_OOOF);
            queue_rumble_data_mario(m, 5, 80);
            o->usingObj = m->marioObj;
            return set_mario_action(m, ACT_GRABBED, 0);
        }
    }

    push_mario_out_of_object(m, o, -5.0f);
    return FALSE;
}

u32 interact_pole(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    s32 actionId = m->action & ACT_ID_MASK;
    if (actionId >= 0x080 && actionId < 0x0A0) {
        if (!(m->prevAction & ACT_FLAG_ON_POLE) || m->usedObj != o) {
#ifdef VERSION_SH
            f32 velConv = m->forwardVel; // conserve the velocity.
            struct Object *marioObj = m->marioObj;
            u32 lowSpeed;
#else
            u32 lowSpeed = (m->forwardVel <= 10.0f);
            struct Object *marioObj = m->marioObj;
#endif

            mario_stop_riding_and_holding(m);

#ifdef VERSION_SH
            lowSpeed = (velConv <= 10.0f);
#endif

            m->interactObj = o;
            m->usedObj = o;
            m->vel[1] = 0.0f;
            m->forwardVel = 0.0f;

            marioObj->oMarioPoleUnk108 = 0;
            marioObj->oMarioPoleYawVel = 0;
            marioObj->oMarioPolePos = m->pos[1] - o->oPosY;

            if (lowSpeed) {
                return set_mario_action(m, ACT_GRAB_POLE_SLOW, 0);
            }

            //! @bug Using m->forwardVel here is assumed to be 0.0f due to the set from earlier.
            //       This is fixed in the Shindou version.
#ifdef VERSION_SH
            marioObj->oMarioPoleYawVel = (s32)(velConv * 0x100 + 0x1000);
#else
            marioObj->oMarioPoleYawVel = (s32)(m->forwardVel * 0x100 + 0x1000);
#endif
            reset_mario_pitch(m);
            queue_rumble_data_mario(m, 5, 80);
            return set_mario_action(m, ACT_GRAB_POLE_FAST, 0);
        }
    }

    return FALSE;
}

u32 interact_hoot(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    s32 actionId = m->action & ACT_ID_MASK;

    if (m != &gMarioStates[0]) { return FALSE; }

    //! Can pause to advance the global timer without falling too far, allowing
    // you to regrab after letting go.
    if (m->usedObj != NULL && actionId >= 0x080 && actionId < 0x098
        && (gGlobalTimer - m->usedObj->oHootMarioReleaseTime > 30)) {
        mario_stop_riding_and_holding(m);
        o->oInteractStatus = INT_STATUS_HOOT_GRABBED_BY_MARIO;
        m->interactObj = o;
        m->usedObj = o;
        o->heldByPlayerIndex = 0;

        queue_rumble_data_mario(m, 5, 80);
        update_mario_sound_and_camera(m);
        return set_mario_action(m, ACT_RIDING_HOOT, 0);
    }

    return FALSE;
}

u32 interact_cap(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    // only allow for local
    if (m != &gMarioStates[0]) { return FALSE; }

    u32 capFlag = get_mario_cap_flag(o);
    u16 capMusic = 0;
    u16 capTime = 0;

    if ((capFlag == MARIO_NORMAL_CAP) && (!(gBehaviorValues.MultipleCapCollection)) ) {
        // refuse normal cap when already on head
        if (m->flags & (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD)) { return FALSE; }
    }

    if (m->action != ACT_GETTING_BLOWN && capFlag != 0) {
        m->interactObj = o;
        o->oInteractStatus = INT_STATUS_INTERACTED;

        m->flags &= ~MARIO_CAP_ON_HEAD & ~MARIO_CAP_IN_HAND;
        m->flags |= capFlag;

        switch (capFlag) {
            case MARIO_VANISH_CAP:
                capTime = gLevelValues.vanishCapDuration;
                capMusic = SEQUENCE_ARGS(4, gLevelValues.vanishCapSequence);
                break;

            case MARIO_METAL_CAP:
                capTime = gLevelValues.metalCapDuration;
                capMusic = SEQUENCE_ARGS(4, gLevelValues.metalCapSequence);
                break;

            case MARIO_WING_CAP:
                capTime = gLevelValues.wingCapDuration;
                capMusic = SEQUENCE_ARGS(4, gLevelValues.wingCapSequence);
                break;
        }

        if (capTime > m->capTimer) {
            m->capTimer = capTime;
        }

        if ((m->action & ACT_FLAG_IDLE) || m->action == ACT_WALKING) {
            m->flags |= MARIO_CAP_IN_HAND;
            set_mario_action(m, ACT_PUTTING_ON_CAP, 0);
        } else {
            m->flags |= MARIO_CAP_ON_HEAD;
        }

        play_sound(SOUND_MENU_STAR_SOUND, m->marioObj->header.gfx.cameraToObject);
        play_character_sound(m, CHAR_SOUND_HERE_WE_GO);

        if (capMusic != 0) {
            play_cap_music(capMusic);
        }
        network_send_collect_item(o);
        return TRUE;
    }

    return FALSE;
}

u32 interact_grabbable(struct MarioState *m, u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    const BehaviorScript *script = virtual_to_segmented(0x13, o->behavior);

    if (m->playerIndex != 0) { return FALSE; }

    if (o->oInteractionSubtype & INT_SUBTYPE_KICKABLE) {
        u32 interaction = determine_interaction(m, o);
        if (interaction & (INT_KICK | INT_TRIP)) {
            attack_object(m, o, interaction);
            bounce_back_from_attack(m, interaction);
            return FALSE;
        }
    }

    if ((o->oInteractionSubtype & INT_SUBTYPE_GRABS_MARIO)) {
        if (check_object_grab_mario(m, interactType, o)) {
            if (o->oSyncID != 0) { network_send_object(o); }
            return TRUE;
        }
    }

    if (able_to_grab_object(m, o)) {
        if (!(o->oInteractionSubtype & INT_SUBTYPE_NOT_GRABBABLE)) {
            m->interactObj = o;
            m->input |= INPUT_INTERACT_OBJ_GRABBABLE;
            if (o->oSyncID != 0) { network_send_object(o); }
            return TRUE;
        }
    }

    if (script != smlua_override_behavior(bhvBowser)) {
        push_mario_out_of_object(m, o, -5.0f);
    }

    return FALSE;
}

u32 mario_can_talk(struct MarioState *m, u32 arg) {
    if (!m) { return FALSE; }
    s16 val6;

    if ((m->action & ACT_FLAG_IDLE) != 0x00000000) {
        return TRUE;
    }

    if (m->action == ACT_WALKING) {
        if (arg) {
            return TRUE;
        }

        val6 = m->marioObj->header.gfx.animInfo.animID;

        if (val6 == 0x0080 || val6 == 0x007F || val6 == 0x006C) {
            return TRUE;
        }
    }

    return FALSE;
}

#ifdef VERSION_JP
#define READ_MASK (INPUT_B_PRESSED)
#else
#define READ_MASK (INPUT_B_PRESSED | INPUT_A_PRESSED)
#endif

#ifdef VERSION_JP
#define SIGN_RANGE 0x38E3
#else
#define SIGN_RANGE 0x4000
#endif

u32 check_read_sign(struct MarioState *m, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if ((m->input & READ_MASK) && mario_can_talk(m, 0) && object_facing_mario(m, o, SIGN_RANGE)) {
        s16 facingDYaw = (s16)(o->oMoveAngleYaw + 0x8000) - m->faceAngle[1];
        if (facingDYaw >= -SIGN_RANGE && facingDYaw <= SIGN_RANGE) {
            f32 targetX = o->oPosX + 105.0f * sins(o->oMoveAngleYaw);
            f32 targetZ = o->oPosZ + 105.0f * coss(o->oMoveAngleYaw);

            m->marioObj->oMarioReadingSignDYaw = facingDYaw;
            m->marioObj->oMarioReadingSignDPosX = targetX - m->pos[0];
            m->marioObj->oMarioReadingSignDPosZ = targetZ - m->pos[2];

            m->interactObj = o;
            m->usedObj = o;
            return set_mario_action(m, ACT_READING_SIGN, 0);
        }
    }

    return FALSE;
}

u32 check_npc_talk(struct MarioState *m, struct Object *o) {
    if (!m || !o) { return FALSE; }
    if ((m->input & READ_MASK) && mario_can_talk(m, 1)) {
        s16 facingDYaw = mario_obj_angle_to_object(m, o) - m->faceAngle[1];
        if (facingDYaw >= -0x4000 && facingDYaw <= 0x4000) {
            o->oInteractStatus = INT_STATUS_INTERACTED;

            m->interactObj = o;
            m->usedObj = o;

            push_mario_out_of_object(m, o, -10.0f);
            return set_mario_action(m, ACT_WAITING_FOR_DIALOG, 0);
        }
    }

    push_mario_out_of_object(m, o, -10.0f);
    return FALSE;
}

u32 interact_text(struct MarioState *m, UNUSED u32 interactType, struct Object *o) {
    if (!m || !o) { return FALSE; }
    u32 interact = FALSE;

    if (o->oInteractionSubtype & INT_SUBTYPE_SIGN) {
        interact = check_read_sign(m, o);
    } else if (o->oInteractionSubtype & INT_SUBTYPE_NPC) {
        interact = check_npc_talk(m, o);
    } else {
        push_mario_out_of_object(m, o, 2.0f);
    }

    return interact;
}

void check_kick_or_punch_wall(struct MarioState *m) {
    if (!m) { return; }
    if (m->flags & (MARIO_PUNCHING | MARIO_KICKING | MARIO_TRIPPING)) {
        Vec3f detector;
        detector[0] = m->pos[0] + 50.0f * sins(m->faceAngle[1]);
        detector[2] = m->pos[2] + 50.0f * coss(m->faceAngle[1]);
        detector[1] = m->pos[1];

        struct WallCollisionData wcd = { 0 };
        resolve_and_return_wall_collisions_data(detector, 80.0f, 5.0f, &wcd);
        if (wcd.numWalls > 0) {
            if (m->action != ACT_MOVE_PUNCHING || m->forwardVel >= 0.0f) {
                if (m->action == ACT_PUNCHING) {
                    m->action = ACT_MOVE_PUNCHING;
                }

                mario_set_forward_vel(m, -48.0f);
                play_sound(SOUND_ACTION_HIT_2, m->marioObj->header.gfx.cameraToObject);
                set_mario_particle_flags(m, PARTICLE_TRIANGLE, FALSE);
            } else if (m->action & ACT_FLAG_AIR) {
                mario_set_forward_vel(m, -16.0f);
                play_sound(SOUND_ACTION_HIT_2, m->marioObj->header.gfx.cameraToObject);
                set_mario_particle_flags(m, PARTICLE_TRIANGLE, FALSE);
            }
        }
    }
}

// Intended for interactions triggered by mods
u32 process_interaction(struct MarioState *m, u32 interactType, struct Object *o, u32 (*interact_function)(struct MarioState *, u32 interactType, struct Object *)) {
    if (!m || !o) { return FALSE; }
    bool allow = true;
    smlua_call_event_hooks_interact_params_ret_bool(HOOK_ALLOW_INTERACT, m, o, interactType, &allow);
    if (allow) {
        if (interact_function(m, interactType, o)) {
            smlua_call_event_hooks_interact_params(HOOK_ON_INTERACT, m, o, interactType, true);
            return TRUE;
        } else {
            smlua_call_event_hooks_interact_params(HOOK_ON_INTERACT, m, o, interactType, false);
        }
    }
    return FALSE;
}

void mario_process_interactions(struct MarioState *m) {
    if (!m) { return; }
    sDelayInvincTimer = FALSE;
    gInteractionInvulnerable = (m->action & ACT_FLAG_INVULNERABLE) || m->invincTimer != 0;

    if (m->skipWarpInteractionsTimer) {
        m->skipWarpInteractionsTimer--;
    }

    if (!(m->action & ACT_FLAG_INTANGIBLE) && m->collidedObjInteractTypes != 0 && is_player_active(m)) {
        s32 i;
        for (i = 0; i < 32; i++) {
            u32 interactType = sInteractionHandlers[i].interactType;
            if (m->collidedObjInteractTypes & interactType) {
                struct Object *object = mario_get_collided_object(m, interactType);
                bool allowRemoteInteractions = object && object->allowRemoteInteractions;

                if (m->playerIndex != 0 && interactType != (u32)INTERACT_PLAYER && interactType != (u32)INTERACT_POLE && !allowRemoteInteractions) {
                    // skip interactions for remote
                    continue;
                }

                m->collidedObjInteractTypes &= ~interactType;

                if (object && !(object->oInteractStatus & INT_STATUS_INTERACTED)) {
                    bool allow = true;
                    smlua_call_event_hooks_interact_params_ret_bool(HOOK_ALLOW_INTERACT, m, object, interactType, &allow);
                    if (allow) {
                        if (sInteractionHandlers[i].handler(m, interactType, object)) {
                            smlua_call_event_hooks_interact_params(HOOK_ON_INTERACT, m, object, interactType, true);
                            break;
                        } else {
                            smlua_call_event_hooks_interact_params(HOOK_ON_INTERACT, m, object, interactType, false);
                        }
                    }
                }
            }
        }
    }

    if (!(m->action & ACT_FLAG_INTANGIBLE) && is_player_active(m)) {
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np2 = &gNetworkPlayers[i];
            if (!np2->connected) { continue; }
            if (&gMarioStates[i] == m) { continue; }
            interact_player_pvp(m, &gMarioStates[i]);
        }
    }

    if (m->invincTimer > 0 && !sDelayInvincTimer) {
        m->invincTimer -= 1;
    }

    smlua_call_event_hooks_mario_param(HOOK_ON_INTERACTIONS, m);

    //! If the kick/punch flags are set and an object collision changes Mario's
    // action, he will get the kick/punch wall speed anyway.
    check_kick_or_punch_wall(m);
    m->flags &= ~MARIO_PUNCHING & ~MARIO_KICKING & ~MARIO_TRIPPING;

    // limit to only local mario
    if (m == &gMarioStates[0]) {
        if (!(m->marioObj->collidedObjInteractTypes & (INTERACT_WARP_DOOR | INTERACT_DOOR))) {
            sDisplayingDoorText = FALSE;
        }
        if (!(m->marioObj->collidedObjInteractTypes & INTERACT_WARP)) {
            sJustTeleported = FALSE;
        }
    }
}

void check_death_barrier(struct MarioState *m) {
    if (!m || m->playerIndex != 0) { return; }

    if (m->pos[1] < m->floorHeight + 2048.0f) {
        bool allowDeath = true;
        smlua_call_event_hooks_mario_param_ret_bool(HOOK_ON_DEATH, m, &allowDeath);
        if (!allowDeath) { return; }

        if (mario_can_bubble(m)) {
            switch (gCurrCourseNum) {
                case COURSE_COTMC:    // (20) Cavern of the Metal Cap
                case COURSE_TOTWC:    // (21) Tower of the Wing Cap
                case COURSE_VCUTM:    // (22) Vanish Cap Under the Moat
                case COURSE_WMOTR:    // (23) Winged Mario over the Rainbow
                    if (!gLevelValues.bubbleOnDeathBarrierInCapStages){
                        break;
                    }
                default:
                    mario_set_bubbled(m);
                    return;
            }
        }

        if (m->action == ACT_BUBBLED) {
            m->pos[1] = m->floorHeight + 2048.0f;
            if (m->vel[1] < 0) { m->vel[1] = 0; }
            return;
        }

        if (level_trigger_warp(m, WARP_OP_WARP_FLOOR) == 20 && !(m->flags & MARIO_UNKNOWN_18)) {
            play_character_sound(m, CHAR_SOUND_WAAAOOOW);
        }
    }
}

void check_lava_boost(struct MarioState *m) {
    if (!m) { return; }
    bool allow = true;
    smlua_call_event_hooks_mario_param_and_int_ret_bool(HOOK_ALLOW_HAZARD_SURFACE, m, HAZARD_TYPE_LAVA_FLOOR, &allow);
    if (m->action == ACT_BUBBLED || (!allow)) { return; }
    if (!(m->action & ACT_FLAG_RIDING_SHELL) && m->pos[1] < m->floorHeight + 10.0f) {
        if (!(m->flags & MARIO_METAL_CAP)) {
            m->hurtCounter += (m->flags & MARIO_CAP_ON_HEAD) ? 12 : 18;
        }

        update_mario_sound_and_camera(m);
        drop_and_set_mario_action(m, ACT_LAVA_BOOST, 0);
    }
}

void pss_begin_slide(UNUSED struct MarioState *m) {
    if (!m) { return; }
    if (!m->visibleToEnemies) { return; }
    if (!(gHudDisplay.flags & HUD_DISPLAY_FLAG_TIMER)) {
        level_control_timer(TIMER_CONTROL_SHOW);
        level_control_timer(TIMER_CONTROL_START);
        gPssSlideStarted = TRUE;
    }
}

void pss_end_slide(struct MarioState *m) {
    if (!m) { return; }
    //! This flag isn't set on death or level entry, allowing double star spawn
    if (gPssSlideStarted) {
        u16 slideTime = level_control_timer(TIMER_CONTROL_STOP);
        if (slideTime < gLevelValues.pssSlideStarTime) {
            // PSS secret star uses oBehParams to spawn
            s32 tmp = m->marioObj->oBehParams;
            m->marioObj->oBehParams = (gLevelValues.pssSlideStarIndex << 24);
            f32* starPos = gLevelValues.starPositions.PssSlideStarPos;
            spawn_default_star(starPos[0], starPos[1], starPos[2]);
            m->marioObj->oBehParams = tmp;
        }
        gPssSlideStarted = FALSE;
    }
}

void mario_handle_special_floors(struct MarioState *m) {
    if (!m) { return; }
    if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE || gDjuiInMainMenu) {
        return;
    }

    if (m->floor != NULL) {
        s32 floorType = m->floor->type;

        switch (floorType) {
            case SURFACE_DEATH_PLANE:
            case SURFACE_VERTICAL_WIND:
                check_death_barrier(m);
                break;

            case SURFACE_WARP:
                level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                break;

            case SURFACE_TIMER_START:
                pss_begin_slide(m);
                break;

            case SURFACE_TIMER_END:
                pss_end_slide(m);
                break;
        }

        if (!(m->action & ACT_FLAG_AIR) && !(m->action & ACT_FLAG_SWIMMING)) {
            switch (floorType) {
                case SURFACE_BURNING:
                    check_lava_boost(m);
                    break;
            }
        }
    }
}
