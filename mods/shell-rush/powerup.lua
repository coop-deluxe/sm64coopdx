
POWERUP_NONE = 0
POWERUP_MUSHROOM = 1
POWERUP_GREEN_SHELL = 2
POWERUP_RED_SHELL = 3
POWERUP_BANANA = 4
POWERUP_MAX = 5

define_custom_obj_fields({
    oPowerupType = 'u32',
    oPowerupIndex = 'u32',
})

function bhv_powerup_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 255

    local m = gMarioStates[obj.heldByPlayerIndex]
    local mTheta = m.faceAngle.y
    local mMag = 0
    if obj.oPowerupType == POWERUP_BANANA then
        mMag = 100 * (obj.oPowerupIndex + 1)
    end
    obj.oPosX = m.pos.x - sins(mTheta) * mMag
    obj.oPosY = m.pos.y
    obj.oPosZ = m.pos.z - coss(mTheta) * mMag

end

function bhv_powerup_stale(obj)
    if obj.oPowerupType == POWERUP_MUSHROOM then
        obj.oAction = 1
        obj.oTimer = 0
    else
        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end
end

function bhv_powerup_spin(obj)
    local m = gMarioStates[obj.heldByPlayerIndex]
    local theta = get_network_area_timer() / 8.0
    theta = theta + (math.pi * 2) * obj.oPowerupIndex / 3.0
    local mag = 120
    if obj.oAction == 1 then
        local scalar = (1 - (obj.oTimer / 5))
        scalar = scalar * scalar
        mag = mag * scalar
    end

    local vec = {
        x = m.pos.x + math.sin(theta) * mag,
        y = m.pos.y + mag,
        z = m.pos.z + math.cos(theta) * mag
    }

    vec.y = find_floor_height(vec.x, vec.y, vec.z) + 50
    if vec.y < m.pos.y + 50 then vec.y = m.pos.y + 50 end

    return vec
end

function bhv_powerup_trail(obj)
    local prevObj = gMarioStates[obj.heldByPlayerIndex].marioObj
    local s = gPlayerSyncTable[obj.heldByPlayerIndex]

    for i = 0, 2 do
        if i >= obj.oPowerupIndex then
            break
        end
        if s.powerup[i] == POWERUP_BANANA then
            prevObj = gPowerups[obj.heldByPlayerIndex][i]
        end
    end

    local theta = math.atan2(prevObj.oPosX - obj.oPosX, prevObj.oPosZ - obj.oPosZ)
    if theta ~= theta then theta = 0 end
    local mag = 150

    local newPos = {
        x = prevObj.oPosX - math.sin(theta) * mag,
        y = prevObj.oPosY,
        z = prevObj.oPosZ - math.cos(theta) * mag
    }

    local vec = {
        x = (newPos.x + obj.oPosX) / 2,
        y = (newPos.y + obj.oPosY * 7) / 8,
        z = (newPos.z + obj.oPosZ) / 2
    }

    local floor = find_floor_height(vec.x, vec.y, vec.z) + 25
    if vec.y < floor then vec.y = floor end

    return vec
end

function bhv_powerup_loop(obj)
    local m = gMarioStates[obj.heldByPlayerIndex]
    local s = gPlayerSyncTable[obj.heldByPlayerIndex]
    local p = gPowerups[obj.heldByPlayerIndex][obj.oPowerupIndex]
    if obj.oAction == 0 then
        if s.powerup[obj.oPowerupIndex] ~= obj.oPowerupType or p ~= obj then
            bhv_powerup_stale(obj)
        end
    end

    local vec = nil
    if obj.oPowerupType == POWERUP_BANANA then
        vec = bhv_powerup_trail(obj)
    else
        vec = bhv_powerup_spin(obj)
    end


    local theta = get_network_area_timer() / 8.0
    theta = theta + (math.pi * 2) * obj.oPowerupIndex / 3.0

    obj_set_vec3f(obj, vec)
    obj.oFaceAngleYaw = theta * 0x6000
    obj.oFaceAngleRoll = 0
    obj.oFaceAnglePitch = 0

    if obj.oAction == 1 and obj.oTimer > 5 then
        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    end

end

id_bhvPowerup = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_powerup_init, bhv_powerup_loop)

-----------------

function use_powerup(m, powerup)
    local s = gPlayerSyncTable[m.playerIndex]
    local theta = m.faceAngle.y
    if powerup == POWERUP_BANANA then
        theta = theta + 0x8000
    end
    local spawnPosition = {
        x = m.pos.x + sins(theta) * 120,
        y = m.pos.y,
        z = m.pos.z + coss(theta) * 120,
    }

    if powerup == POWERUP_MUSHROOM then
        m.forwardVel = 300
        play_character_sound(m, CHAR_SOUND_YAHOO)
    elseif powerup == POWERUP_GREEN_SHELL then
        spawn_sync_object(
            id_bhvWeaponShell,
            E_MODEL_KOOPA_SHELL,
            spawnPosition.x, spawnPosition.y, spawnPosition.z,
            function (obj)
                if UNST22 then
                    obj.oFlyGuyIdleTimer = 0
                    obj.oFlyGuyOscTimer = gNetworkPlayers[0].globalIndex
                    obj.oFlyGuyUnusedJitter = 0
                else
                    obj.oWeaponShellType = 0
                    obj.oWeaponShellGlobalOwner = gNetworkPlayers[0].globalIndex
                    obj.oWeaponShellDeactivate = 0
                end
                obj.oMoveAngleYaw = m.faceAngle.y
                obj.oForwardVel = 85
                obj.oInteractStatus = 0
            end
        )
    elseif powerup == POWERUP_RED_SHELL then
        spawn_sync_object(
            id_bhvWeaponShell,
            E_MODEL_RED_SHELL,
            spawnPosition.x, spawnPosition.y, spawnPosition.z,
            function (obj)
                if UNST22 then
                    obj.oFlyGuyIdleTimer = 1
                    obj.oFlyGuyOscTimer = gNetworkPlayers[0].globalIndex
                    obj.oFlyGuyUnusedJitter = 0
                else
                    obj.oWeaponShellType = 1
                    obj.oWeaponShellGlobalOwner = gNetworkPlayers[0].globalIndex
                    obj.oWeaponShellDeactivate = 0
                end
                obj.oMoveAngleYaw = m.faceAngle.y
                obj.oForwardVel = 85
                obj.oInteractStatus = 0
            end
        )
    elseif powerup == POWERUP_BANANA then
        spawn_sync_object(
            id_bhvWeaponBanana,
            E_MODEL_BANANA,
            spawnPosition.x, spawnPosition.y, spawnPosition.z,
            function (obj)
                obj.oMoveAngleYaw = m.faceAngle.y
                obj.oWeaponBananaGlobalOwner = gNetworkPlayers[0].globalIndex
            end
        )
    end
end

function spawn_powerup(m, powerup, index)
    if not is_in_local_area(m) then
        return nil
    end

    if powerup == POWERUP_MUSHROOM then
        return spawn_non_sync_object(
            id_bhvPowerup,
            E_MODEL_1UP,
            0, 0, 0,
            function(obj)
                obj.heldByPlayerIndex = m.playerIndex
                obj.oPowerupType = powerup
                obj.oPowerupIndex = index
                obj_set_billboard(obj)
                obj_scale(obj, 1)
            end
        )
    elseif powerup == POWERUP_GREEN_SHELL then
        return spawn_non_sync_object(
            id_bhvPowerup,
            E_MODEL_KOOPA_SHELL,
            0, 0, 0,
            function(obj)
                obj.heldByPlayerIndex = m.playerIndex
                obj.oPowerupType = powerup
                obj.oPowerupIndex = index
                obj_scale(obj, 0.75)
            end
        )
    elseif powerup == POWERUP_RED_SHELL then
        return spawn_non_sync_object(
            id_bhvPowerup,
            E_MODEL_RED_SHELL,
            0, 0, 0,
            function(obj)
                obj.heldByPlayerIndex = m.playerIndex
                obj.oPowerupType = powerup
                obj.oPowerupIndex = index
                obj_scale(obj, 0.75)
            end
        )
    elseif powerup == POWERUP_BANANA then
        return spawn_non_sync_object(
            id_bhvPowerup,
            E_MODEL_BANANA,
            0, 0, 0,
            function(obj)
                obj.heldByPlayerIndex = m.playerIndex
                obj.oPowerupType = powerup
                obj.oPowerupIndex = index
                obj_scale(obj, 0.75)
            end
        )
    end
    return nil
end

function select_powerup()
    local m = gMarioStates[0]
    local s = gPlayerSyncTable[0]
    local pick = math.random(1, POWERUP_MAX-1)
    local luck = math.random() < 0.33

    -- don't give mushrooms when first place
    local rank = 0
    for i in pairs(gRankings) do
        if gRankings[i].playerIndex == 0 then
            rank = i
        end
    end
    if rank <= 1 then
        if pick == POWERUP_MUSHROOM then
            pick = POWERUP_GREEN_SHELL
        end
    end

    if luck then
        s.powerup[0] = pick
        s.powerup[1] = pick
        s.powerup[2] = pick
    else
        s.powerup[0] = pick
        s.powerup[1] = POWERUP_NONE
        s.powerup[2] = POWERUP_NONE
    end
end