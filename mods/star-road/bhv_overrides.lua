--- @param o Object
local function bhv_custom_koopa_the_quick_loop(o)
    if o.oKoopaMovementType >= KOOPA_BP_KOOPA_THE_QUICK_BASE then
        if gNetworkPlayers[0].currLevelNum == LEVEL_PSS then
            o.oKoopaTheQuickRaceIndex = 1
        else
            o.oKoopaTheQuickRaceIndex = 0
        end
    end
end

id_bhvKoopa = hook_behavior(id_bhvKoopa, OBJ_LIST_PUSHABLE, false, nil, bhv_custom_koopa_the_quick_loop, "bhvKoopa")

---------------------------------------------------

--- @param o Object
local function bhv_custom_castle_cannon_grate_init(o)
    o.oFlags = (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    o.collisionData = smlua_collision_util_get("castle_grounds_seg7_collision_cannon_grill")
    o.oCollisionDistance = 4000
    load_object_collision_model()

    if get_star_count() >= 65 then -- 65 star check
        o.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end
end

local function bhv_custom_castle_cannon_grate_loop()
    load_object_collision_model()
end

id_bhvSMSRHiddenAt120Stars = hook_behavior(id_bhvHiddenAt120Stars, OBJ_LIST_SURFACE, true, bhv_custom_castle_cannon_grate_init, bhv_custom_castle_cannon_grate_loop, "bhvSMSRHiddenAt120Stars")

---------------------------------------------------

local function bully_custom_act_level_death(o)
    if obj_lava_death() == 1 then
        spawn_mist_particles()
        local m = get_mario_from_global_index(o.oBullyLastNetworkPlayerIndex)
        spawn_non_sync_object(
            id_bhvBowserKey,
            E_MODEL_BOWSER_KEY,
            m.pos.x, m.pos.y, m.pos.z,
            nil
        )
    end
end

local function bhv_custom_big_bully_init(o)
    o.oFlags = (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)
    o.oAnimations = gObjectAnimations.bully_seg5_anims_0500470C
    object_drop_to_floor(o)
    cur_obj_set_home_once()
    o.oIntangibleTimer = 0

    cur_obj_init_animation(0)
    bhv_big_bully_init()
end

local function bhv_custom_big_bully_loop(o)
    if o.oAction == BULLY_ACT_LAVA_DEATH then
        o.oBullyPrevX = o.oPosX
        o.oBullyPrevY = o.oPosY
        o.oBullyPrevZ = o.oPosZ

        bully_custom_act_level_death(o)

        set_object_visibility(o, 3000)
    else
        bhv_bully_loop()
    end
end

id_bhvBigBully = hook_behavior(id_bhvBigBully, OBJ_LIST_GENACTOR, true, bhv_custom_big_bully_init, bhv_custom_big_bully_loop, "bhvBigBullyBoss")

---------------------------------------------------

--- @param o Object
local function bhv_custom_bowser_loop(o)
    local np = gNetworkPlayers[0]
    if np.currAreaSyncValid and np.currLevelSyncValid and np.currLevelNum ~= LEVEL_BOWSER_3 then
        -- force bowser into do nothing action when not displaying cutscene
        -- magic number hell
        if o.oAction ~= 5 and o.oAction ~= 6 and o.oAction ~= 20 then
            o.oAction = 4
            o.oSubAction = 11
        end
    end
end

id_bhvBowser = hook_behavior(id_bhvBowser, OBJ_LIST_GENACTOR, false, nil, bhv_custom_bowser_loop, "bhvBowser")

---------------------------------------------------

--- @param o Object
local function bhv_custom_grand_star_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oInteractType = INTERACT_WARP
    o.oIntangibleTimer = 0
    cur_obj_set_home_once()
end

local function bhv_custom_grand_star_loop()
    bhv_warp_loop()
    bhv_grand_star_loop()
end

id_bhvGrandStar = hook_behavior(id_bhvGrandStar, OBJ_LIST_LEVEL, true, bhv_custom_grand_star_init, bhv_custom_grand_star_loop, "bhvGrandStar")

---------------------------------------------------

--- @param o Object
local function bhv_custom_racing_penguin_update(o)
    if o.oRacingPenguinReachedBottom == 1 then
        o.oRacingPenguinWeightedNewTargetSpeed = 10
    end
end

id_bhvRacingPenguin = hook_behavior(id_bhvRacingPenguin, OBJ_LIST_GENACTOR, false, nil, bhv_custom_racing_penguin_update, "bhvRacingPenguin")
