
/**
 * Behavior for bhvWigglerHead and bhvWigglerBody.
 * The bhvWigglerHead object controls the wiggler's behavior, and physically manifests
 * as the wiggler's head. The bhvWigglerBody objects represent the 3 tail body
 * parts, numbered 1 closest to the head, and 3 at the end of the tail.
 * Processing order is bhvWigglerHead, then bhvWigglerBody 1, 2, then 3.
 */

/**
 * Hitbox for wiggler's non-head body parts.
 */
static struct ObjectHitbox sWigglerBodyPartHitbox = {
    .interactType = INTERACT_BOUNCE_TOP,
    .downOffset = 0,
    .damageOrCoinValue = 3,
    .health = 99, // never decreases
    .numLootCoins = 0,
    .radius = 20,
    .height = 20,
    .hurtboxRadius = 20,
    .hurtboxHeight = 10,
};

/**
 * Hitbox for wiggler's head.
 */
static struct ObjectHitbox sWigglerHitbox = {
    .interactType = INTERACT_BOUNCE_TOP,
    .downOffset = 0,
    .damageOrCoinValue = 3,
    .health = 4,
    .numLootCoins = 0,
    .radius = 60,
    .height = 50,
    .hurtboxRadius = 30,
    .hurtboxHeight = 40,
};

/**
 * Attack handler for wiggler while in the walking action.
 */
static u8 sWigglerAttackHandlers[] = {
    /* ATTACK_PUNCH:                 */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_KICK_OR_TRIP:          */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_ABOVE:            */ ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON,
    /* ATTACK_GROUND_POUND_OR_TWIRL: */ ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON,
    /* ATTACK_FAST_ATTACK:           */ ATTACK_HANDLER_KNOCKBACK,
    /* ATTACK_FROM_BELOW:            */ ATTACK_HANDLER_KNOCKBACK,
};

/**
 * Target speed while walking when wiggler has health 1, 2, 3, and 4.
 */
static f32 sWigglerSpeeds[] = { 2.0f, 40.0f, 30.0f, 16.0f };

/**
 * Update function for bhvWigglerBody.
 * Set object position and angle based on wiggler segment data and avoid falling
 * through the floor.
 * Tangible if the wiggler is not in the shrinking action, but does nothing on
 * attack.
 */
void bhv_wiggler_body_part_update(void) {
    if (o == NULL) { return; }
    
    struct Object *parent = o->parentObj;
    
    if (parent == NULL) { return; }
    
    // Sanity check the array size of our segments,
    // This should never be higher then 3
    // in normal circumstances.
    if (o->oBehParams2ndByte > 3 || o->oBehParams2ndByte < 0) { return; }
    if (!parent->oWigglerSegments) { return; }
    
    struct ChainSegment *segment = &parent->oWigglerSegments[o->oBehParams2ndByte];
    
    if (segment == NULL) { return; }

    cur_obj_scale(parent->header.gfx.scale[0]);

    o->oFaceAnglePitch = segment->pitch;
    o->oFaceAngleYaw = segment->yaw;

    // TODO: What is this for?
    f32 posOffset = -37.5f * o->header.gfx.scale[0];
    f32 dy = posOffset * coss(o->oFaceAnglePitch) - posOffset;
    f32 dxz = posOffset * sins(o->oFaceAnglePitch);
    f32 dx = dxz * sins(o->oFaceAngleYaw);
    f32 dz = dxz * coss(o->oFaceAngleYaw);

    o->oPosX = segment->posX + dx;
    o->oPosY = segment->posY + dy;
    o->oPosZ = segment->posZ + dz;

    if (o->oPosY < parent->oWigglerFallThroughFloorsHeight) {
        //! Since position is recomputed each frame, tilting the wiggler up
        //  while on the ground could cause the tail segments to clip through
        //  the floor
        o->oPosY += -30.0f;
        cur_obj_update_floor_height();
        if (o->oFloorHeight > o->oPosY) // TODO: Check ineq swap
        {
            o->oPosY = o->oFloorHeight;
        }
    }

    segment->posY = o->oPosY;

    // Inherit walking animation speed from wiggler
    cur_obj_init_animation_with_accel_and_sound(0, parent->oWigglerWalkAnimSpeed);
    if (parent->oWigglerWalkAnimSpeed == 0.0f) {
        cur_obj_reverse_animation();
    }

    if (parent->oAction == WIGGLER_ACT_SHRINK) {
        cur_obj_become_intangible();
    } else {
        cur_obj_become_tangible();
        obj_check_attacks(&sWigglerBodyPartHitbox, o->oAction);
    }
}

/**
 * Initialize the segment data and spawn the body part objects.
 */
void wiggler_init_segments(void) {
    struct ChainSegment *segments = dynamic_pool_alloc(gLevelPool, 4 * sizeof(struct ChainSegment));

    // Each segment represents the global position and orientation of each
    // object. Segment 0 represents the wiggler's head, and segment i>0
    // represents body part i.
    o->oWigglerSegments = segments;

    if (segments != NULL) {
        for (s32 i = 0; i <= 3; i++) {
            chain_segment_init(segments + i);

            (segments + i)->posX = o->oPosX;
            (segments + i)->posY = o->oPosY;
            (segments + i)->posZ = o->oPosZ;

            (segments + i)->pitch = o->oFaceAnglePitch;
            (segments + i)->yaw = o->oFaceAngleYaw;
        }

        o->header.gfx.animInfo.animFrame = -1;

        // Spawn each body part
        for (s32 i = 1; i <= 3; i++) {
            struct Object *bodyPart = spawn_object_relative(i, 0, 0, 0, o, MODEL_WIGGLER_BODY, bhvWigglerBody);
            if (bodyPart != NULL) {
                obj_init_animation_with_sound(bodyPart, (struct AnimationTable*)&wiggler_seg5_anims_0500C874, 0);
                bodyPart->header.gfx.animInfo.animFrame = (23 * i) % 26 - 1;
            }
        }

        o->oAction = WIGGLER_ACT_WALK;
        cur_obj_unhide();
    }

#if defined(VERSION_EU) || defined(AVOID_UB)
    o->oHealth = 4; // This fixes Wiggler reading UB on his first frame of his acceleration, as his health is not set.
#endif
}

/**
 * Update the tail to reflect changes in the head's yaw and pitch, and ensure
 * that the distance between parts is exactly the intended distance.
 * Since these positions are completely recomputed each frame, it is not possible
 * for a body part to get stuck on geometry and separate from the rest of the
 * body.
 */
void wiggler_update_segments(void) {
    f32 segmentLength = 35.0f * o->header.gfx.scale[0];
    if (!o->oWigglerSegments) { return; }

    for (s32 i = 1; i <= 3; i++) {
        struct ChainSegment *prevBodyPart = &o->oWigglerSegments[i - 1];
        struct ChainSegment *bodyPart = &o->oWigglerSegments[i];
        if (!prevBodyPart || !bodyPart) { continue; }
        f32 dx = bodyPart->posX - prevBodyPart->posX;
        f32 dy = bodyPart->posY - prevBodyPart->posY;
        f32 dz = bodyPart->posZ - prevBodyPart->posZ;

        // As the head turns, propagate this rotation backward if the difference
        // is more than 45 degrees
        s16 dyaw = atan2s(-dz, -dx) - prevBodyPart->yaw;
        clamp_s16(&dyaw, -0x2000, 0x2000);
        bodyPart->yaw = prevBodyPart->yaw + dyaw;

        // As the head tilts, propagate the tilt backward
        f32 dxz = sqrtf(dx * dx + dz * dz);
        s16 dpitch = atan2s(dxz, dy) - prevBodyPart->pitch;
        clamp_s16(&dpitch, -0x2000, 0x2000);
        bodyPart->pitch = prevBodyPart->pitch + dpitch;

        // Set the body part's position relative to the previous body part's
        // position, using the current body part's angles. This means that the
        // head can rotate up to 45 degrees without the body moving
        bodyPart->posY = segmentLength * sins(bodyPart->pitch) + prevBodyPart->posY;
        dxz = segmentLength * coss(bodyPart->pitch);
        bodyPart->posX = prevBodyPart->posX - dxz * sins(bodyPart->yaw);
        bodyPart->posZ = prevBodyPart->posZ - dxz * coss(bodyPart->yaw);
    }
}

 u8 wiggler_act_walk_continue_dialog(void) { return o->oAction == WIGGLER_ACT_WALK && o->oWigglerTextStatus < WIGGLER_TEXT_STATUS_COMPLETED_DIALOG; }

/**
 * Show text if necessary. Then walk toward mario if not at full health, and
 * otherwise wander in random directions.
 * If attacked by mario, enter either the jumped on or knockback action.
 */
static void wiggler_act_walk(void) {
    struct MarioState *marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 25000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;
    treat_far_home_as_mario(1200.0f, &distanceToPlayer, &angleToPlayer);

    o->oWigglerWalkAnimSpeed = 0.06f * o->oForwardVel;

    // Update text if necessary
    if (o->oWigglerTextStatus < WIGGLER_TEXT_STATUS_COMPLETED_DIALOG) {
        if (o->oWigglerTextStatus == WIGGLER_TEXT_STATUS_AWAIT_DIALOG && !gDjuiInMainMenu) {
            seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            o->oWigglerTextStatus = WIGGLER_TEXT_STATUS_SHOWING_DIALOG;
        }

        // If Mario is positioned below the wiggler, assume he entered through the
        // lower cave entrance, so don't display text.
        if ((player && player->oPosY < o->oPosY) || (cur_obj_update_dialog_with_cutscene(&gMarioStates[0], 2, 0, CUTSCENE_DIALOG, gBehaviorValues.dialogs.WigglerDialog, wiggler_act_walk_continue_dialog) != 0)) {
            o->oWigglerTextStatus = WIGGLER_TEXT_STATUS_COMPLETED_DIALOG;
            network_send_object_reliability(o, TRUE);
        }
    } else {
        //! Every object's health is initially 2048, and wiggler's doesn't change
        //  to 4 until after this runs the first time. It indexes out of bounds
        //  and uses the value 113762.3 for one frame on US. This is fixed up
        //  in wiggler_init_segments if AVOID_UB is defined.
        obj_forward_vel_approach(BHV_ARR(sWigglerSpeeds, o->oHealth - 1, f32), 1.0f);

        if (o->oWigglerWalkAwayFromWallTimer != 0) {
            o->oWigglerWalkAwayFromWallTimer -= 1;
        } else {
            if (distanceToPlayer >= 25000.0f) {
                // If >1200 away from home, turn to home
                o->oWigglerTargetYaw = angleToPlayer;
            }

            if (obj_bounce_off_walls_edges_objects(&o->oWigglerTargetYaw)) {
                //! If the wiggler could self-intersect, or intersect a different
                //  non-mario object, this could potentially be used to force
                //  the wiggler to walk straight - past his usual radius
                o->oWigglerWalkAwayFromWallTimer = random_linear_offset(30, 30);
            } else {
                if (o->oHealth < 4) {
                    o->oWigglerTargetYaw = angleToPlayer;
                } else if (o->oWigglerTimeUntilRandomTurn != 0) {
                    o->oWigglerTimeUntilRandomTurn -= 1;
                } else {
                    o->oWigglerTargetYaw = o->oMoveAngleYaw + 0x4000 * (s16) random_sign();
                    o->oWigglerTimeUntilRandomTurn = random_linear_offset(30, 50);
                }
            }
        }

        // If moving at high speeds, could overflow. But can't reach such speeds
        // in practice
        s16 yawTurnSpeed = (s16)(30.0f * o->oForwardVel);
        cur_obj_rotate_yaw_toward(o->oWigglerTargetYaw, yawTurnSpeed);
        obj_face_yaw_approach(o->oMoveAngleYaw, 2 * yawTurnSpeed);

        obj_face_pitch_approach(0, 0x320);

        // For the first two seconds of walking, stay invulnerable
        cur_obj_become_tangible();
        if (o->oTimer < 60) {
            obj_check_attacks(&sWigglerHitbox, o->oAction);
        } else if (obj_handle_attacks(&sWigglerHitbox, o->oAction, sWigglerAttackHandlers)) {
            if (o->oAction != WIGGLER_ACT_JUMPED_ON) {
                o->oAction = WIGGLER_ACT_KNOCKBACK;
            }

            o->oWigglerWalkAwayFromWallTimer = 0;
            o->oWigglerWalkAnimSpeed = 0.0f;
        }
    }
}

u8 wiggler_act_jumped_on_continue_dialog(void) { return o->oAction == WIGGLER_ACT_JUMPED_ON && o->header.gfx.scale[1] >= 4.0f && o->oTimer > 30; }

/**
 * Squish and unsquish, then show text and enter either the walking or shrinking
 * action.
 */
static void wiggler_act_jumped_on(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);

    // Text to show on first, second, and third attack.
    s32* attackText[3] = {
        (s32*) &gBehaviorValues.dialogs.WigglerAttack1Dialog,
        (s32*) &gBehaviorValues.dialogs.WigglerAttack2Dialog,
        (s32*) &gBehaviorValues.dialogs.WigglerAttack3Dialog
    };

    // Shrink until the squish speed becomes 0, then unisquish
    if (approach_f32_ptr(&o->oWigglerSquishSpeed, 0.0f, 0.05f)) {
        // Note that 4 is the default scale
        approach_f32_ptr(&o->header.gfx.scale[1], 4.0f, 0.2f);
    } else {
        o->header.gfx.scale[1] -= o->oWigglerSquishSpeed;
    }

    // Wait for a second after unsquishing, then show text and either shrink (if
    // defeated) or go back to walking
    s16 dialogIndex = (o->oHealth - 2);
    if (o->header.gfx.scale[1] >= 4.0f) {
        if (o->oTimer > 30) {
            if ((dialogIndex >= 0 && dialogIndex <= 2) && marioState && should_start_or_continue_dialog(marioState, o) && cur_obj_update_dialog_with_cutscene(marioState, 2, 0, CUTSCENE_DIALOG, *attackText[dialogIndex], wiggler_act_jumped_on_continue_dialog) != 0) {
                // Because we don't want the wiggler to disappear after being
                // defeated, we leave its health at 1
                if (--o->oHealth <= 1) {
                    o->oHealth = 1;
                    o->oAction = WIGGLER_ACT_SHRINK;
                    cur_obj_become_intangible();
                } else {
                    o->oAction = WIGGLER_ACT_WALK;
                    o->oMoveAngleYaw = o->oFaceAngleYaw;

                    if (o->oHealth == 2) {
                        cur_obj_play_sound_2(SOUND_OBJ_WIGGLER_JUMP);
                        o->oForwardVel = 10.0f;
                        o->oVelY = 70.0f;
                    }
                }
                network_send_object_reliability(o, TRUE);
            }
        }
    } else {
        o->oTimer = 0;
    }

    obj_check_attacks(&sWigglerHitbox, o->oAction);
}

/**
 * Decelerate to a stop and then enter the walk action.
 */
static void wiggler_act_knockback(void) {
    if (o->oVelY > 0.0f) {
        o->oFaceAnglePitch -= o->oVelY * 30.0f;
    } else {
        obj_face_pitch_approach(0, 0x190);
    }

    if (obj_forward_vel_approach(0.0f, 1.0f) && o->oFaceAnglePitch == 0) {
        o->oAction = WIGGLER_ACT_WALK;
        o->oMoveAngleYaw = o->oFaceAngleYaw;
    }

    obj_check_attacks(&sWigglerHitbox, o->oAction);
}

/**
 * Shrink, then spawn the star and enter the fall through floor action.
 */
static void wiggler_act_shrink(void) {
    if (o->oTimer >= 20) {
        if (o->oTimer == 20) {
            cur_obj_play_sound_2(SOUND_OBJ_ENEMY_DEFEAT_SHRINK);
        }

        // 4 is the default scale, so shrink to 1/4 of regular size
        if (approach_f32_ptr(&o->header.gfx.scale[0], 1.0f, 0.1f)) {

            f32* starPos = gLevelValues.starPositions.WigglerStarPos;
            struct Object *star = spawn_default_star(starPos[0], starPos[1], starPos[2]);
            
            // If we're not the closet to Wiggler,
            // Don't play this cutscene!
            if (star != NULL && nearest_mario_state_to_object(o) != &gMarioStates[0]) {
                star->oStarSpawnExtCutsceneFlags = 0;
            }
            
            o->oAction = WIGGLER_ACT_FALL_THROUGH_FLOOR;
        }

        cur_obj_scale(o->header.gfx.scale[0]);
    }
}

/**
 * Fall through floors until y < 1700, then enter the walking action.
 */
static void wiggler_act_fall_through_floor(void) {
    if (o->oTimer == 60) {
        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
        o->oWigglerFallThroughFloorsHeight = 1700.0f;
    } else if (o->oTimer > 60) {
        if (o->oPosY < o->oWigglerFallThroughFloorsHeight) {
            o->oAction = WIGGLER_ACT_WALK;
        } else {
            o->oFaceAnglePitch = obj_get_pitch_from_vel();
        }

        cur_obj_move_using_fvel_and_gravity();
    }
}

/**
 * Attack handler for when wiggler is jumped or ground pounded on.
 * Stop and enter the jumped on action.
 */
void wiggler_jumped_on_attack_handler(void) {
    cur_obj_play_sound_2(SOUND_OBJ_WIGGLER_ATTACKED);
    // Check for if we've already defeated the Wiggler.
    if (o->header.gfx.scale[0] == 1.0f) {
        o->oAction = WIGGLER_ACT_KNOCKBACK;
        return;
    }
    o->oAction = WIGGLER_ACT_JUMPED_ON;
    o->oForwardVel = o->oVelY = 0.0f;
    o->oWigglerSquishSpeed = 0.4f;
}

u8 bhv_wiggler_ignore_if_true(void) {
    return o->oAction == WIGGLER_ACT_UNINITIALIZED;
}

static Vec3f wigglerPrePos = { 0 };
static u8 wigglerCompletedDialog = FALSE;

void bhv_wiggler_on_received_pre(UNUSED u8 localIndex) {
    wigglerPrePos[0] = o->oPosX;
    wigglerPrePos[1] = o->oPosY;
    wigglerPrePos[2] = o->oPosZ;
    wigglerCompletedDialog = (o->oWigglerTextStatus == WIGGLER_TEXT_STATUS_COMPLETED_DIALOG);
}

void bhv_wiggler_on_received_post(UNUSED u8 localIndex) {
    if (o == NULL) { return; }

    Vec3f posDiff = { 0 };
    posDiff[0] = o->oPosX - wigglerPrePos[0];
    posDiff[1] = o->oPosY - wigglerPrePos[1];
    posDiff[2] = o->oPosZ - wigglerPrePos[2];
    for (s32 i = 0; i < 3; i++) {
        o->oWigglerSegments[i].posX += posDiff[0];
        o->oWigglerSegments[i].posY += posDiff[1];
        o->oWigglerSegments[i].posZ += posDiff[2];
    }
    if (wigglerCompletedDialog) {
        o->oWigglerTextStatus = WIGGLER_TEXT_STATUS_COMPLETED_DIALOG;
    }
}

/**
 * Update function for bhvWigglerHead.
 */
void bhv_wiggler_update(void) {
    // PARTIAL_UPDATE
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject* so = sync_object_init(o, 4000.0f);
        if (so) {
            so->ignore_if_true = bhv_wiggler_ignore_if_true;
            so->on_received_pre = bhv_wiggler_on_received_pre;
            so->on_received_post = bhv_wiggler_on_received_post;
            sync_object_init_field(o, &o->oFaceAnglePitch);
            sync_object_init_field(o, &o->oWigglerFallThroughFloorsHeight);
            sync_object_init_field(o, &o->oWigglerWalkAnimSpeed);
            sync_object_init_field(o, &o->oWigglerSquishSpeed);
            sync_object_init_field(o, &o->oWigglerTimeUntilRandomTurn);
            sync_object_init_field(o, &o->oWigglerTargetYaw);
            sync_object_init_field(o, &o->oWigglerWalkAwayFromWallTimer);
            sync_object_init_field(o, &o->oHealth);
            sync_object_init_field(o, &o->header.gfx.scale[0]);
            sync_object_init_field(o, &o->header.gfx.scale[1]);
            sync_object_init_field(o, &o->header.gfx.scale[2]);
            sync_object_init_field(o, &o->oFaceAngleYaw);
        }
    }

    struct Object* player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 25000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;
    o->oDistanceToMario = distanceToPlayer;
    o->oAngleToMario = angleToPlayer;

    if (o->oAction == WIGGLER_ACT_UNINITIALIZED) {
        wiggler_init_segments();
    } else {
        if (o->oAction == WIGGLER_ACT_FALL_THROUGH_FLOOR) {
            wiggler_act_fall_through_floor();
        } else {
            treat_far_home_as_mario(1200.0f, &distanceToPlayer, &angleToPlayer);

            // Walking animation and sound
            cur_obj_init_animation_with_accel_and_sound(0, o->oWigglerWalkAnimSpeed);
            if (o->oWigglerWalkAnimSpeed != 0.0f) {
                cur_obj_play_sound_at_anim_range(0, 13,
                              o->oHealth >= 4 ? SOUND_OBJ_WIGGLER_LOW_PITCH : SOUND_OBJ_WIGGLER_HIGH_PITCH);
            } else {
                cur_obj_reverse_animation();
            }

            cur_obj_update_floor_and_walls();
            switch (o->oAction) {
                case WIGGLER_ACT_WALK:
                    wiggler_act_walk();
                    break;
                case WIGGLER_ACT_KNOCKBACK:
                    wiggler_act_knockback();
                    break;
                case WIGGLER_ACT_JUMPED_ON:
                    wiggler_act_jumped_on();
                    break;
                case WIGGLER_ACT_SHRINK:
                    wiggler_act_shrink();
                    break;
                case WIGGLER_ACT_FALL_THROUGH_FLOOR:
                    wiggler_act_fall_through_floor();
                    break;
            }

            cur_obj_move_standard(-78);
        }

        // Update segment 0 with data from the wiggler object
        if (o->oWigglerSegments) {
            o->oWigglerSegments[0].posX = o->oPosX;
            o->oWigglerSegments[0].posY = o->oPosY;
            o->oWigglerSegments[0].posZ = o->oPosZ;
            o->oWigglerSegments[0].pitch = o->oFaceAnglePitch;
            o->oWigglerSegments[0].yaw = o->oFaceAngleYaw;
        }

        // Update the rest of the segments to follow segment 0
        wiggler_update_segments();
    }
}
