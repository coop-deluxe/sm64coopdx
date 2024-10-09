// wdw_water_level.c.inc
static u32 sWaterDiamondPicked = 0;

static void bhv_init_changing_water_level_on_received_post(UNUSED u8 fromLocalIndex) {
    struct SyncObject* diamondSo = sync_object_get(sWaterDiamondPicked);
    if (diamondSo == NULL || diamondSo->behavior != smlua_override_behavior(bhvWaterLevelDiamond)) { return; }
    struct Object* diamond = sync_object_get_object(sWaterDiamondPicked);
    if (diamond == NULL || diamond->behavior != smlua_override_behavior(bhvWaterLevelDiamond)) { return; }

    diamond->oAction = WATER_LEVEL_DIAMOND_ACT_CHANGE_WATER_LEVEL;
    gWDWWaterLevelChanging = 1;
}

// called when WDW is loaded.
void bhv_init_changing_water_level_loop(void) {
    if (!sync_object_is_initialized(o->oSyncID)) {
        sWaterDiamondPicked = 0;
        struct SyncObject* so = sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so != NULL) {
            so->on_received_post = bhv_init_changing_water_level_on_received_post;
            sync_object_init_field(o, &sWaterDiamondPicked);
        }
    }

    if (!gEnvironmentRegions) { return; }

    if (gCurrentObject->oAction == 0) {
        gCurrentObject->oAction++;
    } else if (gCurrentObject->oTimer < 10) {
        if (gEnvironmentRegions && gEnvironmentRegionsLength > 6) {
            *gEnvironmentLevels = gEnvironmentRegions[6];
        }
    } else {
        if (gEnvironmentRegions && gEnvironmentRegionsLength > 6) {
            gEnvironmentRegions[6] = *gEnvironmentLevels + sins(o->oWaterLevelTriggerUnkF4) * 20.0f;
        }
        gCurrentObject->oWaterLevelTriggerUnkF4 += 0x200;
    }
}

void bhv_water_level_diamond_loop(void) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    struct Object* player = marioState ? marioState->marioObj : NULL;

    struct Object* manager = cur_obj_nearest_object_with_behavior(bhvInitializeChangingWaterLevel);

    if (!sync_object_is_initialized(o->oSyncID)) {
        sync_object_init(o, SYNC_DISTANCE_ONLY_EVENTS);
    }

    if (gEnvironmentRegions != NULL) {
        switch (o->oAction) {
            case WATER_LEVEL_DIAMOND_ACT_INIT:
                o->oFaceAngleYaw = 0;
                o->oWaterLevelTriggerTargetWaterLevel = (s32) o->oPosY;
                if (o->oTimer > 10)
                    o->oAction++; // Sets to WATER_LEVEL_DIAMOND_ACT_IDLE
                break;
            case WATER_LEVEL_DIAMOND_ACT_IDLE:
                if (marioState == &gMarioStates[0] && player && obj_check_if_collided_with_object(o, player)) {
                    if (gWDWWaterLevelChanging == 0) {
                        o->oAction++; // Sets to WATER_LEVEL_DIAMOND_ACT_CHANGE_WATER_LEVEL
                        gWDWWaterLevelChanging = 1;

                        if (manager != NULL && o->oSyncID != 0) {
                            sWaterDiamondPicked = o->oSyncID;
                            network_send_object(manager);
                        }
                    }
                }
                break;
            case WATER_LEVEL_DIAMOND_ACT_CHANGE_WATER_LEVEL:
                o->oAngleVelYaw = 0;
                *gEnvironmentLevels = (s32) approach_f32_symmetric(
                    (f32) *gEnvironmentLevels, (f32) o->oWaterLevelTriggerTargetWaterLevel, gLevelValues.wdwWaterLevelSpeed);
                if (*gEnvironmentLevels == o->oWaterLevelTriggerTargetWaterLevel) {
                    if ((s16) o->oFaceAngleYaw == 0)
                        o->oAction++; // Sets to WATER_LEVEL_DIAMOND_ACT_IDLE_SPINNING
                    else
                        o->oAngleVelYaw = 0x800;
                } else {
                    if (o->oTimer == 0)
                        cur_obj_play_sound_2(SOUND_GENERAL_WATER_LEVEL_TRIG);
                    else {
                        if (*gEnvironmentLevels > o->oWaterLevelTriggerTargetWaterLevel)
                            cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
                        else
                            cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN); // same as above
                    }
                    o->oAngleVelYaw = 0x800;
                    reset_rumble_timers_2(&gMarioStates[0], 2);
                }
                break;
            case WATER_LEVEL_DIAMOND_ACT_IDLE_SPINNING:
                if (!obj_check_if_collided_with_object(o, player)) {
                    gWDWWaterLevelChanging = 0;
                    o->oAction = WATER_LEVEL_DIAMOND_ACT_IDLE;
                    o->oAngleVelYaw = 0;
                    struct SyncObject* so = sync_object_get(o->oSyncID);
                    if (so && so->behavior == o->behavior) {
                        so->lastReliablePacketIsStale = true;
                    }

                }
                break;
        }
        o->oFaceAngleYaw += o->oAngleVelYaw;
    }
}
