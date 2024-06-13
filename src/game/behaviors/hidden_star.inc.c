// hidden_star.c.inc

void bhv_hidden_star_init(void) {
    s16 count = count_objects_with_behavior(bhvHiddenStarTrigger);
    if (count == 0) {
        struct Object *obj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
        if (obj != NULL) { obj->oBehParams = o->oBehParams; }
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }

    if (gCurrentArea) {
        o->oHiddenStarTriggerCounter = gCurrentArea->numSecrets - count;
    }
    
    // We haven't interacted with a player yet.
    // We also don't sync this as not only is it not required
    // but it also is only set for an interaction.
    // Therefore this object must already be loaded for it to be set
    // and if it wasn't. You couldn't of possibly been the one
    // who last interacted to begin with.
    o->oHiddenStarLastInteractedObject = NULL;
    
    if (!sync_object_is_initialized(o->oSyncID)) {
        struct SyncObject *so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            sync_object_init_field(o, &o->oAction);
            sync_object_init_field(o, &o->oHiddenStarTriggerCounter);
            sync_object_init_field(o, &o->oPosX);
            sync_object_init_field(o, &o->oPosY);
            sync_object_init_field(o, &o->oPosZ);
            sync_object_init_field(o, &o->oTimer);
        }
    }
}

void bhv_hidden_star_loop(void) {
    switch (o->oAction) {
        case 0:
            if (gCurrentArea && o->oHiddenStarTriggerCounter >= gCurrentArea->numSecrets) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                struct Object *obj = spawn_red_coin_cutscene_star(o->oPosX, o->oPosY, o->oPosZ);
                if (obj != NULL) {
                    if (o->oHiddenStarLastInteractedObject == &gMarioStates[0]) {
                        obj->oStarSpawnExtCutsceneFlags = 1;
                    } else {
                        obj->oStarSpawnExtCutsceneFlags = 0;
                    }
                    spawn_mist_particles();
                }
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}

void bhv_hidden_star_trigger_loop(void) {
    if ((o->oInteractStatus & INT_STATUS_INTERACTED) || (gMarioStates[0].visibleToEnemies && obj_check_if_collided_with_object(o, gMarioObjects[0]) == 1)) {
        struct Object *hiddenStar = cur_obj_nearest_object_with_behavior(bhvHiddenStar);
        if (hiddenStar != NULL) {

            s16 count = (count_objects_with_behavior(bhvHiddenStarTrigger) - 1);
            if (gCurrentArea) {
                hiddenStar->oHiddenStarTriggerCounter = gCurrentArea->numSecrets - count;
            }
            spawn_orange_number(hiddenStar->oHiddenStarTriggerCounter, 0, 0, 0);
            
            // Set the last person who interacted with a secret to the 
            // parent so only they get the star cutscene.
            struct MarioState *player = nearest_mario_state_to_object(o);
            if (player) {
                hiddenStar->oHiddenStarLastInteractedObject = player;
            }

#ifdef VERSION_JP
            play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
#else
            if (count < 5) {
                play_sound(SOUND_MENU_COLLECT_SECRET + ((4 - count) << 16), gGlobalSoundSource);
            } else {
                play_sound(SOUND_MENU_COLLECT_SECRET, gGlobalSoundSource);
            }
#endif
        }

        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        if (!(o->oInteractStatus & INT_STATUS_INTERACTED)) {
            network_send_collect_item(o);
        }
    }
    if (gLevelValues.visibleSecrets) {
        obj_set_model(o, MODEL_PURPLE_MARBLE);
        obj_set_billboard(o);
    }
}

void bhv_bowser_course_red_coin_star_loop(void) {
    switch (o->oAction) {
        case 0:
            if (gCurrentArea && o->oHiddenStarTriggerCounter >= gCurrentArea->numRedCoins) {
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTimer > 2) {
                struct Object *obj = spawn_no_exit_star(o->oPosX, o->oPosY, o->oPosZ);
                if (obj != NULL) {
                    if (o->oHiddenStarLastInteractedObject == &gMarioStates[0]) {
                        obj->oStarSpawnExtCutsceneFlags = 1;
                    } else {
                        obj->oStarSpawnExtCutsceneFlags = 0;
                    }
                    spawn_mist_particles();
                }
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}
