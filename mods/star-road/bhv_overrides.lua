function bhv_custom_koopa_the_quick_loop(obj)
    if obj.oKoopaMovementType >= KOOPA_BP_KOOPA_THE_QUICK_BASE then
        if gNetworkPlayers[0].currLevelNum == 27 then
            obj.oKoopaTheQuickRaceIndex = 1
        else
            obj.oKoopaTheQuickRaceIndex = 0
        end
    end
end

-- hook the behavior
bhvKoopa = hook_behavior(id_bhvKoopa, OBJ_LIST_PUSHABLE, false, nil, bhv_custom_koopa_the_quick_loop)

---------------------------------------------------

function bhv_custom_castle_cannon_grate_init(obj)
    obj.oFlags = (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.collisionData = smlua_collision_util_get("castle_grounds_seg7_collision_cannon_grill")
    obj.oCollisionDistance = 4000
    load_object_collision_model()

    if get_star_count() > 64 then -- 65 star check
        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end
end

function bhv_custom_castle_cannon_grate_loop(obj)
    load_object_collision_model()
end

-- hook the behavior
bhvSMSRHiddenAt120Stars = hook_behavior(id_bhvHiddenAt120Stars, OBJ_LIST_SURFACE, true, bhv_custom_castle_cannon_grate_init, bhv_custom_castle_cannon_grate_loop)

---------------------------------------------------

function bully_custom_act_level_death(obj)
    if obj_lava_death() == 1 then
        spawn_mist_particles()
        local m = get_mario_from_global_index(obj.oBullyLastNetworkPlayerIndex)
        spawn_non_sync_object(id_bhvBowserKey, E_MODEL_BOWSER_KEY, m.pos.x, m.pos.y, m.pos.z, nil)
    end
end

function bhv_custom_big_bully_init(obj)
    obj.oFlags = (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    obj.oAnimations = gObjectAnimations.bully_seg5_anims_0500470C
    object_drop_to_floor(obj)
    cur_obj_set_home_once()
    obj.oIntangibleTimer = 0

    cur_obj_init_animation(0)
    bhv_big_bully_init()
end

function bhv_custom_bully_loop(obj)
    if obj.oAction == BULLY_ACT_LAVA_DEATH then
        obj.oBullyPrevX = obj.oPosX
        obj.oBullyPrevY = obj.oPosY
        obj.oBullyPrevZ = obj.oPosZ

        bully_custom_act_level_death(obj)

        set_object_visibility(obj, 3000)
    else
        bhv_bully_loop()
    end
end

-- hook the behavior
bhvBigBullyBoss = hook_behavior(id_bhvBigBully, OBJ_LIST_GENACTOR, true, bhv_custom_big_bully_init, bhv_custom_bully_loop)

---------------------------------------------------

function bhv_custom_bowser_loop(obj)
    local np = gNetworkPlayers[0]
    if np.currAreaSyncValid and np.currLevelSyncValid and np.currLevelNum ~= LEVEL_BOWSER_3 then
        -- force bowser into do nothing action when not displaying cutscene
        if obj.oAction ~= 5 and obj.oAction ~= 6 and obj.oAction ~= 20 then
            obj.oAction = 4
            obj.oSubAction = 11
        end
    end
end

-- hook the behavior
id_bhvBowserCustom = hook_behavior(id_bhvBowser, OBJ_LIST_GENACTOR, false, nil, bhv_custom_bowser_loop)

---------------------------------------------------

function bhv_custom_grand_star_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oInteractType = INTERACT_WARP
    obj.oIntangibleTimer = 0
    cur_obj_set_home_once()
end

function bhv_custom_grand_star_loop(obj)
    bhv_warp_loop()
    bhv_grand_star_loop()
end

-- hook the behavior
id_bhvGrandStar = hook_behavior(id_bhvGrandStar, OBJ_LIST_LEVEL, true, bhv_custom_grand_star_init, bhv_custom_grand_star_loop)
