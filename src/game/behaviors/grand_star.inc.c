// grand_star.c.inc

s32 arc_to_goal_pos(Vec3f goal, Vec3f pos, f32 yVel, f32 gravity) {
    if (!o) { return 0; }
    f32 dx = goal[0] - pos[0];
    f32 dz = goal[2] - pos[2];
    f32 planarDist = sqrtf(dx * dx + dz * dz);
    o->oMoveAngleYaw = atan2s(dz, dx);
    o->oVelY = yVel;
    o->oGravity = gravity;
    s32 time = -2.0f / o->oGravity * yVel - 1.0f;
    o->oForwardVel = planarDist / time;
    return time;
}

void grand_star_zero_velocity(void) {
    if (!o) { return; }
    o->oGravity = 0.0f;
    o->oVelY = 0.0f;
    o->oForwardVel = 0.0f;
}

void bhv_grand_star_init(void) {
    struct Object *other = cur_obj_nearest_object_with_behavior(bhvGrandStar);
    if (other == NULL) {
        if (!sync_object_is_initialized(o->oSyncID)) {
            struct SyncObject *so = sync_object_init(o, 4000.0f);
            if (so) {
                sync_object_init_field(o, &o->header.gfx.scale[0]);
                sync_object_init_field(o, &o->header.gfx.scale[1]);
                sync_object_init_field(o, &o->header.gfx.scale[2]);
                sync_object_init_field(o, &o->oPrevAction);
                sync_object_init_field(o, &o->oAction);
                sync_object_init_field(o, &o->oSubAction);
                sync_object_init_field(o, &o->oInteractStatus);
                sync_object_init_field(o, &o->oTimer);
                sync_object_init_field(o, &o->oHomeX);
                sync_object_init_field(o, &o->oHomeY);
                sync_object_init_field(o, &o->oHomeZ);
                sync_object_init_field(o, &o->oPosX);
                sync_object_init_field(o, &o->oPosY);
                sync_object_init_field(o, &o->oPosZ);
                sync_object_init_field(o, &o->oGravity);
                sync_object_init_field(o, &o->oVelY);
                sync_object_init_field(o, &o->oForwardVel);
                sync_object_init_field(o, &o->oAngleVelYaw);
                sync_object_init_field(o, &o->oMoveAngleYaw);
                sync_object_init_field(o, &o->oFaceAngleYaw);
                sync_object_init_field(o, &o->oGraphYOffset);
            }
        }
        return; 
    }
    
    obj_mark_for_deletion(o);
    if (gSecondCameraFocus == o) { gSecondCameraFocus = other; }
}

void bhv_grand_star_loop(void) {
    if (o->activeFlags == ACTIVE_FLAG_DEACTIVATED) { return; }
    
    if (o->oAction == 0) {
        if (o->oTimer == 0) {
            obj_set_angle(o, 0, 0, 0);
            o->oAngleVelYaw = 0x400;
            cur_obj_play_sound_2(SOUND_GENERAL2_STAR_APPEARS);
        }
        if (o->oTimer > 70) {
            o->oAction++;
        }
        spawn_sparkle_particles(3, 200, 80, -60);
    } else if (o->oAction == 1) {
        if (o->oTimer == 0) {
            Vec3f empty;
            empty[0] = empty[1] = empty[2] = 0.0f;
            
            cur_obj_play_sound_2(SOUND_GENERAL_GRAND_STAR);
            cutscene_object(CUTSCENE_STAR_SPAWN, o);
            o->oGrandStarUnk108 = arc_to_goal_pos(empty, &o->oPosX, 80.0f, -2.0f);
        }
        cur_obj_move_using_fvel_and_gravity();
        if (o->oSubAction == 0) {
            if (o->oPosY < o->oHomeY) {
                o->oPosY = o->oHomeY;
                o->oVelY = 60.0f;
                o->oForwardVel = 0.0f;
                o->oSubAction++;
                cur_obj_play_sound_2(SOUND_GENERAL_GRAND_STAR_JUMP);
            }
        } else if (o->oVelY < 0.0f && o->oPosY < o->oHomeY + 200.0f) {
            o->oPosY = o->oHomeY + 200.0f;
            grand_star_zero_velocity();
            gObjCutsceneDone = 1;
            set_mario_npc_dialog(&gMarioStates[0], 0, NULL);
            o->oAction++;
            o->oInteractStatus = 0;
            cur_obj_play_sound_2(SOUND_GENERAL_GRAND_STAR_JUMP);
        }
        spawn_sparkle_particles(3, 200, 80, -60);
    } else if (o->oAction == 2) {
        // Make our object tangible.
        cur_obj_become_tangible();
        // Check for if the jumbo star has been collected.
        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            // Make sure we're in the jumbo star cutscene.
            if (gMarioStates[0].action != ACT_JUMBO_STAR_CUTSCENE) {
                set_mario_action(&gMarioStates[0], ACT_JUMBO_STAR_CUTSCENE, 0);
            }
            // Increment our action, The star despawns next action.
            o->oAction++;
        }
    } else {
        // The star cutscene has started, Make sure the star is deleted
        // if it isn't already deactivated.
        if (o->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            // Mark our object for deletion.
            obj_mark_for_deletion(o);
            // Reset our interactive status.
            o->oInteractStatus = 0;
        }
    }
    if (o->oAngleVelYaw > 0x400) {
        o->oAngleVelYaw -= 0x100;
    }
    o->oFaceAngleYaw += o->oAngleVelYaw;
    cur_obj_scale(2.0f);
    o->oGraphYOffset = 110.0f;
}