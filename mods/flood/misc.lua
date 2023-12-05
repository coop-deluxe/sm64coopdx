if unsupported then return end

E_MODEL_FLOOD = smlua_model_util_get_id("flood_geo")
E_MODEL_CTT = smlua_model_util_get_id("ctt_geo") -- easter egg in the distance
E_MODEL_LAUNCHPAD = smlua_model_util_get_id("launchpad_geo")

local COL_LAUNCHPAD = smlua_collision_util_get("launchpad_collision")

-- localize functions to improve performance
local get_environment_region,set_environment_region,set_override_far,cur_obj_scale,cur_obj_init_animation,bhv_pole_base_loop,nearest_mario_state_to_object,play_mario_jump_sound,set_mario_action,spawn_non_sync_object,mario_set_forward_vel,vec3f_set,load_object_collision_model,obj_mark_for_deletion,network_is_server,obj_check_hitbox_overlap,obj_has_behavior_id = get_environment_region,set_environment_region,set_override_far,cur_obj_scale,cur_obj_init_animation,bhv_pole_base_loop,nearest_mario_state_to_object,play_mario_jump_sound,set_mario_action,spawn_non_sync_object,mario_set_forward_vel,vec3f_set,load_object_collision_model,obj_mark_for_deletion,network_is_server,obj_check_hitbox_overlap,obj_has_behavior_id

--- @param o Object
local function bhv_water_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oAnimState = gLevels[gGlobalSyncTable.level].type

    o.header.gfx.skipInViewCheck = true

    o.oFaceAnglePitch = 0
    o.oFaceAngleRoll = 0
end

--- @param o Object
local function bhv_water_loop(o)
    o.oPosY = gGlobalSyncTable.waterLevel

    if game == GAME_VANILLA and gGlobalSyncTable.level ~= LEVEL_SSL then
        o.oFaceAngleYaw = o.oTimer * 5 * (gLevels[gNetworkPlayers[0].currLevelNum].speed or 1)
    end

    if game == GAME_VANILLA and gNetworkPlayers[0].currLevelNum ~= LEVEL_WDW and gNetworkPlayers[0].currLevelNum ~= LEVEL_HMC then
        for i = 1, 3 do
            if get_environment_region(i) < gGlobalSyncTable.waterLevel then
                set_environment_region(i, -20000)
            end
        end
    else
        set_environment_region(1, -20000)
    end
end

id_bhvWater = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_water_init, bhv_water_loop)


--- @param o Object
local function bhv_custom_static_object_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.header.gfx.skipInViewCheck = true
    set_override_far(50000)
end

id_bhvCustomStaticObject = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_custom_static_object_init, nil)


--- @param o Object
local function bhv_final_star_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.hitboxRadius = 160
    o.hitboxHeight = 100

    cur_obj_scale(2)
end

--- @param o Object
local function bhv_final_star_loop(o)
    o.oFaceAngleYaw = o.oFaceAngleYaw + 0x800
end

id_bhvFinalStar = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_final_star_init, bhv_final_star_loop)


--- @param o Object
local function bhv_flood_flag_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oInteractType = INTERACT_POLE
    o.hitboxRadius = 80
    o.hitboxHeight = 700
    o.oIntangibleTimer = 0
    o.oAnimations = gObjectAnimations.koopa_flag_seg6_anims_06001028

    cur_obj_init_animation(0)
end

--- @param o Object
local function bhv_flood_flag_loop(o)
    bhv_pole_base_loop()
end

id_bhvFloodFlag = hook_behavior(nil, OBJ_LIST_POLELIKE, true, bhv_flood_flag_init, bhv_flood_flag_loop)


local function bhv_launchpad_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oCollisionDistance = 500
    o.collisionData = COL_LAUNCHPAD
    obj_scale(o, 0.85)
end

local function bhv_launchpad_loop(o)
    local m = nearest_mario_state_to_object(o)
    if m.marioObj.platform == o then
        play_mario_jump_sound(m)
        if o.oBehParams2ndByte ~= 255 then
            set_mario_action(m, ACT_TWIRLING, 0)
            m.vel.y = o.oBehParams2ndByte
        else
            spawn_non_sync_object(
                id_bhvWingCap,
                E_MODEL_NONE,
                m.pos.x + m.vel.x, m.pos.y + m.vel.y, m.pos.z + m.vel.z,
                nil
            )
            set_mario_action(m, ACT_FLYING_TRIPLE_JUMP, 0)
            mario_set_forward_vel(m, 100)
            vec3f_set(m.angleVel, 0, 0, 0)
            vec3f_set(m.faceAngle, 0, 0x4500, 0)
            m.vel.y = 55
        end
    end
    load_object_collision_model()
end

id_bhvLaunchpad = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_launchpad_init, bhv_launchpad_loop)


--- @param o Object
local function obj_hide(o)
    o.header.gfx.node.flags = o.header.gfx.node.flags | GRAPH_RENDER_INVISIBLE
end

--- @param o Object
local function obj_mark_for_deletion_on_sync(o)
    if gNetworkPlayers[0].currAreaSyncValid then obj_mark_for_deletion(o) end
end

hook_behavior(id_bhvStar, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)
hook_behavior(id_bhvHoot, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)
hook_behavior(id_bhvWarpPipe, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)
hook_behavior(id_bhvFadingWarp, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)
hook_behavior(id_bhvBalconyBigBoo, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)
hook_behavior(id_bhvExclamationBox, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)
hook_behavior(id_bhvWaterLevelDiamond, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)
hook_behavior(id_bhvKoopaRaceEndpoint, OBJ_LIST_UNIMPORTANT, true, obj_hide, obj_mark_for_deletion_on_sync)

--- @param m MarioState
local function before_phys_step(m)
    if m.playerIndex ~= 0 then return end

    if m.pos.y + 40 < gGlobalSyncTable.waterLevel and gNetworkPlayers[m.playerIndex].currLevelNum == gGlobalSyncTable.level then
        m.vel.y = m.vel.y + 2
        m.peakHeight = m.pos.y
    end
end

--- @param m MarioState
--- @param o Object
local function allow_interact(m, o)
    if m.action == ACT_SPECTATOR or
    (o.header.gfx.node.flags & GRAPH_RENDER_ACTIVE) == 0 or
    o.oInteractType == INTERACT_WARP_DOOR or
    o.oInteractType == INTERACT_WARP then
        return false
    end

    return true
end

local function on_death()
    local m = gMarioStates[0]
    if m.floor.type == SURFACE_DEATH_PLANE or m.floor.type == SURFACE_VERTICAL_WIND then
        m.health = 0xFF
    end
    return false
end

local function on_pause_exit()
    if network_is_server() then
        network_send(true, { restart = true })
        level_restart()
    end
    return false
end

--- @param m MarioState
local function allow_hazard_surface(m)
    if m.health <= 0xFF then return false end
    return true
end

-- thanks Peachy
--- @param o Object
local function on_object_unload(o)
    local m = gMarioStates[0]
    if (o.header.gfx.node.flags & GRAPH_RENDER_INVISIBLE) == 0 and obj_has_behavior_id(o, id_bhv1Up) == 1 and obj_check_hitbox_overlap(o, m.marioObj) then
        m.healCounter = 31
        m.hurtCounter = 0
    end
end

local function on_packet_receive(dataTable)
    if dataTable.restart then level_restart() end
end

hook_event(HOOK_BEFORE_PHYS_STEP, before_phys_step)
hook_event(HOOK_ALLOW_INTERACT, allow_interact)
hook_event(HOOK_ON_DEATH, on_death)
hook_event(HOOK_ON_PAUSE_EXIT, on_pause_exit)
hook_event(HOOK_ALLOW_HAZARD_SURFACE, allow_hazard_surface)
hook_event(HOOK_ON_OBJECT_UNLOAD, on_object_unload)
hook_event(HOOK_ON_PACKET_RECEIVE, on_packet_receive)