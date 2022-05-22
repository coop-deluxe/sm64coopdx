define_custom_obj_fields({
    oArenaFlameGlobalOwner = 'u32',
})

local sArenaChildFlameLife = 30 * 1.5

function bhv_arena_child_flame_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    if global_index_hurts_mario_state(obj.oArenaFlameGlobalOwner, gMarioStates[0]) then
        obj.oInteractType = INTERACT_FLAME
    else
        obj.oInteractType = 0
    end
    obj.oGraphYOffset = 30

    obj.hitboxRadius = 25
    obj.hitboxHeight = 10
    obj.hitboxDownOffset = 0

    obj.hurtboxRadius = 25
    obj.hurtboxHeight = 10

    obj.oWallHitboxRadius = 50
    obj.oGravity = -400 / 100
    obj.oBounciness = -80 / 100
    obj.oDragStrength = 300 / 100
    obj.oFriction = 300 / 100
    obj.oBuoyancy = 200 / 100

    obj_scale(obj, 3)

    obj_set_billboard(obj)

    -- override blue flame
    local np = network_player_from_global_index(obj.oArenaFlameGlobalOwner)
    if np ~= nil then
        local s = gPlayerSyncTable[np.localIndex]
        if s.team == 2 then
            obj_set_model_extended(obj, E_MODEL_BLUE_FLAME)
        end
    end

end

function bhv_arena_child_flame_loop(obj)
    obj.activeFlags = obj.activeFlags | ACTIVE_FLAG_UNK10

    local lifeRemain = (sArenaChildFlameLife - obj.oTimer) / sArenaChildFlameLife
    local size = 3 * (1 - (1 - lifeRemain) ^ 3)
    obj_scale(obj, size)
    if size < 1.5 then
        obj.oInteractType = 0
    end

    if lifeRemain <= 0 then
        obj_mark_for_deletion(obj)
    end

    obj.oInteractStatus = 0
    obj.oIntangibleTimer = 0

    obj.oAnimState = obj.oAnimState + 1
end

id_bhvArenaChildFlame = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_arena_child_flame_init, bhv_arena_child_flame_loop)

----------------------

local sArenaFlameLife = 30 * 5

function bhv_arena_flame_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    if global_index_hurts_mario_state(obj.oArenaFlameGlobalOwner, gMarioStates[0]) then
        obj.oInteractType = INTERACT_FLAME
    else
        obj.oInteractType = 0
    end
    obj.oGraphYOffset = 30

    obj.hitboxRadius = 50
    obj.hitboxHeight = 25
    obj.hitboxDownOffset = 25

    obj.hurtboxRadius = 50
    obj.hurtboxHeight = 25

    obj.oWallHitboxRadius = 100
    obj.oGravity = -400 / 100
    obj.oBounciness = -80 / 100
    obj.oDragStrength = 120 / 100
    obj.oFriction = 120 / 100
    obj.oBuoyancy = 200 / 100

    obj_scale(obj, 3)

    obj_set_billboard(obj)
    cur_obj_play_sound_2(SOUND_OBJ_FLAME_BLOWN)

    -- override blue flame
    local np = network_player_from_global_index(obj.oArenaFlameGlobalOwner)
    if np ~= nil then
        local s = gPlayerSyncTable[np.localIndex]
        if s.team == 2 then
            obj_set_model_extended(obj, E_MODEL_BLUE_FLAME)
        end
    end

    network_init_object(obj, false, nil)
end

function bhv_arena_flame_loop(obj)
    obj.activeFlags = obj.activeFlags | ACTIVE_FLAG_UNK10
    cur_obj_update_floor_and_walls();

    local lifeRemain = (sArenaFlameLife - obj.oTimer) / sArenaFlameLife
    local size = 5 * (1 - (1 - lifeRemain) ^ 3)
    obj_scale(obj, size)
    if size < 1.5 then
        obj.oInteractType = 0
    end

    if lifeRemain <= 0 then
        obj_mark_for_deletion(obj)
    end

    -- spawn child flame
    if (obj.oTimer % 2) == 0 then
        spawn_non_sync_object(id_bhvArenaChildFlame, E_MODEL_RED_FLAME, obj.oPosX, obj.oPosY, obj.oPosZ,
            function(obj2)
                obj2.oArenaFlameGlobalOwner = obj.oArenaFlameGlobalOwner
            end)
    end

    -- find nearest target
    local pos = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }
    local target = nil
    local targetDist = 2000
    for i = 0, (MAX_PLAYERS - 1) do
        local m = gMarioStates[i]
        if global_index_hurts_mario_state(obj.oArenaFlameGlobalOwner, m) and active_player(m) then
            local dist = vec3f_dist(pos, m.pos)
            if dist < targetDist then
                target = m
                targetDist = dist
            end
        end
    end

    if target ~= nil then
        -- aim toward target
        local targetYaw = atan2s(target.pos.z - pos.z, target.pos.x - pos.x)
        obj.oMoveAngleYaw = approach_s16_symmetric(obj.oMoveAngleYaw, targetYaw, 0x350)

        -- jump
        local floorDiff = obj.oFloorHeight - obj.oPosY
        if math.abs(floorDiff) < 5 and math.abs(obj.oVelY) < 5 and obj.oPosY < target.pos.y then
            obj.oVelY = 50
        end
    end

    cur_obj_move_standard(78)
    obj.oInteractStatus = 0
    obj.oIntangibleTimer = 0

    obj.oAnimState = obj.oAnimState + 1
end

id_bhvArenaFlame = hook_behavior(nil, OBJ_LIST_GENACTOR, true, bhv_arena_flame_init, bhv_arena_flame_loop)

------------------
