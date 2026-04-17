// sl_snowman_wind.c.inc

u8 bhv_sl_snowman_wind_loop_continue_dialog(void) { return o->oSubAction == SL_SNOWMAN_WIND_ACT_TALKING; }

void bhv_sl_snowman_wind_loop(void) {
    // uses event based sync system. Sync when the wind starts blowing
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, o->oAction);
            sync_object_init_field(o, o->oPrevAction);
            sync_object_init_field(o, o->oTimer);
            sync_object_init_field(o, o->oSubAction);
            sync_object_init_field(o, o->globalPlayerIndex);
        }
    }

    struct Object *player = nearest_player_to_object(o);
    s32 distanceToPlayer = player ? dist_between_objects(o, player) : 10000;
    s32 angleToPlayer = player ? obj_angle_to_object(o, player) : 0;

    s16 marioAngleFromWindSource;
    Vec3f tempPos;

    if (o->oTimer == 0) {
        o->oSLSnowmanWindOriginalYaw = o->oMoveAngleYaw;
    }

    // Waiting for Mario to approach.
    if (o->oSubAction == SL_SNOWMAN_WIND_ACT_IDLE) {
        o->oDistanceToMario = 0;

        // Check if Mario is within 1000 units of the center of the bridge, and ready to speak.
        vec3f_copy(tempPos, &o->oPosX);
        obj_set_pos(o, 1100, 3328, 1164); // Position is in the middle of the ice bridge
        if (cur_obj_can_mario_activate_textbox(&gMarioStates[0], 1000.0f, 30.0f, 0x7FFF)) {
            o->oSubAction++;
            o->globalPlayerIndex = network_global_index_from_local(0);
            network_send_object(o);
        }
        vec3f_copy(&o->oPosX, tempPos);

    // Mario has come close, begin dialog.
    } else if (o->oSubAction == SL_SNOWMAN_WIND_ACT_TALKING) {
        if (o->globalPlayerIndex >= MAX_PLAYERS) o->globalPlayerIndex = 0;
        struct MarioState *marioState = &gMarioStates[network_local_index_from_global(o->globalPlayerIndex)];
        if (is_player_active(marioState) && marioState->visibleToEnemies && cur_obj_update_dialog(marioState, 2, 2, gBehaviorValues.dialogs.SnowmanWindDialog, 0, bhv_sl_snowman_wind_loop_continue_dialog)) {
            o->oSubAction++;
            network_send_object(o);
        }

    // Blowing, spawn wind particles (SL_SNOWMAN_WIND_ACT_BLOWING)
    } else if (distanceToPlayer < 1500.0f && player && absf(player->oPosY - o->oHomeY) < 500.0f) {
        // Point towards Mario, but only within 0x1500 angle units of the original angle.
        if ((marioAngleFromWindSource = angleToPlayer - o->oSLSnowmanWindOriginalYaw) > 0) {
            if (marioAngleFromWindSource < 0x1500) {
                o->oMoveAngleYaw = angleToPlayer;
            } else {
                o->oMoveAngleYaw = o->oSLSnowmanWindOriginalYaw + 0x1500;
            }
        } else {
            if (marioAngleFromWindSource > -0x1500) {
                o->oMoveAngleYaw = angleToPlayer;
            } else {
                o->oMoveAngleYaw = o->oSLSnowmanWindOriginalYaw - 0x1500;
            }
        }
        // Spawn wind and play wind sound
        cur_obj_spawn_strong_wind_particles(12, 3.0f, 0, 0, 0);
        cur_obj_play_sound_1(SOUND_AIR_BLOW_WIND);
    }
}
