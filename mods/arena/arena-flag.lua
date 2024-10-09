ARENA_FLAG_INVALID_GLOBAL = 0xFF
---

gArenaFlagInfo = {}
sFlagScoreTimer = 0

define_custom_obj_fields({
    oArenaFlagTeam = 'u32',
    oArenaFlagHeldByGlobal = 'u32',
    oArenaFlagAtBase = 'u32',
})

function bhv_arena_flag_init(obj)
    local team = (obj.oBehParams >> 24) & 0xFF

    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 255
    obj.oArenaFlagTeam = team
    obj.oArenaFlagHeldByGlobal = ARENA_FLAG_INVALID_GLOBAL
    obj.oArenaFlagAtBase = 1

    gArenaFlagInfo[team] = {
        pos = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ },
        team = team,
        obj = obj,
    }

    if team == 0 then
        obj_set_model_extended(obj, E_MODEL_FLAG_WHITE)
    elseif team == 1 then
        obj_set_model_extended(obj, E_MODEL_FLAG_RED)
    elseif team == 2 then
        obj_set_model_extended(obj, E_MODEL_FLAG_BLUE)
    else
        obj_mark_for_deletion(obj)
    end

    network_init_object(obj, false, {
        'oArenaFlagHeldByGlobal',
        'oArenaFlagAtBase',
        'oPosX',
        'oPosY',
        'oPosZ',
    })
end

function bhv_arena_flag_update_pos_rot(obj)
    -- spin
    obj.oFaceAngleYaw   = obj.oFaceAngleYaw - 600
    obj.oFaceAngleRoll  = 0
    obj.oFaceAnglePitch = 0

    local data = gArenaFlagInfo[obj.oArenaFlagTeam]
    if obj.oArenaFlagAtBase == 1 then
        -- set at base
        obj.oPosX = data.pos.x
        obj.oPosY = data.pos.y
        obj.oPosZ = data.pos.z
        return
    end

    if obj.oArenaFlagHeldByGlobal == ARENA_FLAG_INVALID_GLOBAL then
        return
    end

    local np = network_player_from_global_index(obj.oArenaFlagHeldByGlobal)
    if np == nil then
        return
    end

    -- set at player
    local m = gMarioStates[np.localIndex]
    local awayMag = -50
    local yOffset = 50
    if np.localIndex ~= 0 then
        yOffset = 150
        awayMag = -30
    end
    obj.oPosX = m.pos.x + sins(m.faceAngle.y) * awayMag
    obj.oPosY = m.pos.y + yOffset
    obj.oPosZ = m.pos.z + coss(m.faceAngle.y) * awayMag
    obj.oFaceAngleYaw = m.faceAngle.y + 0x4000
    obj.oFaceAngleRoll = -0x400
end

function bhv_arena_flag_update_score(obj)
    if gGlobalSyncTable.gameMode ~= GAME_MODE_FT and gGlobalSyncTable.gameMode ~= GAME_MODE_TFT then
        return
    end

    if not network_is_server() then
        return
    end

    if obj.oArenaFlagTeam ~= 0 then
        return
    end

    if obj.oArenaFlagHeldByGlobal == ARENA_FLAG_INVALID_GLOBAL then
        return
    end

    if gGlobalSyncTable.gameState ~= GAME_STATE_ACTIVE then
        return
    end

    local np = network_player_from_global_index(obj.oArenaFlagHeldByGlobal)
    if np == nil then
        return
    end

    sFlagScoreTimer = sFlagScoreTimer + 1
    if (sFlagScoreTimer % 30) == 0 then
        local s = gPlayerSyncTable[np.localIndex]
        s.score = s.score + 1
        if gGlobalSyncTable.gameMode == GAME_MODE_TFT then
            local teamScore = calculate_team_score(s.team)
            if teamScore >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
                round_end()
            end
        elseif s.score >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
            round_end()
        end
    end
end

function bhv_arena_flag_update_rotation(obj)
    if obj.oArenaFlagHeldByGlobal ~= ARENA_FLAG_INVALID_GLOBAL then
        return
    end
end

function bhv_arena_flag_return(obj, showMessage)
    if obj.oArenaFlagAtBase == 1 then
        return
    end
    local otherTeam = get_other_team(obj.oArenaFlagTeam)
    local data = gArenaFlagInfo[obj.oArenaFlagTeam]

    obj.oArenaFlagHeldByGlobal = ARENA_FLAG_INVALID_GLOBAL
    obj.oArenaFlagAtBase = 1
    obj.oPosX = data.pos.x
    obj.oPosY = data.pos.y
    obj.oPosZ = data.pos.z
    network_send_object(obj, true)
    if showMessage then
        local msg = string.format('%sThe %s%s%s flag was returned!', team_color_str(otherTeam), team_color_str(obj.oArenaFlagTeam), team_name_str(obj.oArenaFlagTeam), team_color_str(otherTeam))
        send_arena_flag(obj.oArenaFlagTeam, ARENA_FLAG_INVALID_GLOBAL, msg)
    end
end

function bhv_arena_flag_collect(obj, m)
    local data = gArenaFlagInfo[obj.oArenaFlagTeam]
    local s  = gPlayerSyncTable[m.playerIndex]
    local np = gNetworkPlayers[m.playerIndex]
    local e  = gMarioStateExtras[m.playerIndex]
    if e.levelTimer < 30 then
        return false
    end

    if obj.oArenaFlagTeam > 0 and s.team == obj.oArenaFlagTeam then
        if obj.oArenaFlagAtBase == 1 then
            local otherTeam = get_other_team(obj.oArenaFlagTeam)
            local otherData = gArenaFlagInfo[otherTeam]
            local otherFlag = otherData.obj
            if otherFlag.oArenaFlagHeldByGlobal == np.globalIndex then
                -- capture flag
                otherFlag.oArenaFlagHeldByGlobal = ARENA_FLAG_INVALID_GLOBAL
                otherFlag.oArenaFlagAtBase = 1
                otherFlag.oPosX = otherData.pos.x
                otherFlag.oPosY = otherData.pos.y
                otherFlag.oPosZ = otherData.pos.z
                network_send_object(otherFlag, true)
                local msg = string.format('%s%s captured the %s%s%s flag!', team_color_str(s.team), strip_colors(np.name), team_color_str(otherTeam), team_name_str(otherTeam), team_color_str(s.team))
                send_arena_flag(otherFlag.oArenaFlagTeam, np.globalIndex, msg)
                if gGlobalSyncTable.gameState == GAME_STATE_ACTIVE then
                    if s.team == 1 then
                        gGlobalSyncTable.capTeam1 = gGlobalSyncTable.capTeam1 + 1
                        if gGlobalSyncTable.capTeam1 >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
                            round_end()
                        end
                    elseif s.team == 2 then
                        gGlobalSyncTable.capTeam2 = gGlobalSyncTable.capTeam2 + 1
                        if gGlobalSyncTable.capTeam2 >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
                            round_end()
                        end
                    end
                end
                return true
            end
            return false
        end

        -- return flag
        obj.oArenaFlagHeldByGlobal = ARENA_FLAG_INVALID_GLOBAL
        obj.oArenaFlagAtBase = 1
        obj.oPosX = data.pos.x
        obj.oPosY = data.pos.y
        obj.oPosZ = data.pos.z
        network_send_object(obj, true)
        local msg = string.format('%s%s returned the %s flag!', team_color_str(s.team), strip_colors(np.name), team_name_str(s.team))
        send_arena_flag(obj.oArenaFlagTeam, np.globalIndex, msg)
        return true
    end

    -- pick up flag
    obj.oArenaFlagHeldByGlobal = np.globalIndex
    obj.oArenaFlagAtBase = 0
    obj.oTimer = 0
    obj.oPosX = m.pos.x
    obj.oPosY = m.pos.y
    obj.oPosZ = m.pos.z
    network_send_object(obj, true)
    local msg = string.format('%s%s picked up the %s%s%s flag!', team_color_str(s.team), strip_colors(np.name), team_color_str(obj.oArenaFlagTeam), team_name_str(obj.oArenaFlagTeam), team_color_str(s.team))
    send_arena_flag(obj.oArenaFlagTeam, np.globalIndex, msg)
    return true
end

function bhv_arena_flag_check_collect(obj)
    if not network_is_server() then
        return
    end

    if obj.oArenaFlagHeldByGlobal ~= ARENA_FLAG_INVALID_GLOBAL then
        return
    end

    for i = 0, MAX_PLAYERS - 1 do
        local m  = gMarioStates[i]
        local player = m.marioObj
        local yDist = math.abs(obj.oPosY - player.oPosY)
        local xzDist = math.sqrt((obj.oPosX - player.oPosX) ^ 2 + (obj.oPosZ - player.oPosZ) ^ 2)
        if active_player(m) and mario_health_float(m) > 0 and xzDist < 160 and yDist < 250 then
            if bhv_arena_flag_collect(obj, m) then
                return
            end
        end
    end
end

function bhv_arena_update_scale(obj)
    local np = gNetworkPlayers[0]
    if obj.oArenaFlagHeldByGlobal == np.globalIndex then
        cur_obj_scale(0.4)
    else
        cur_obj_scale(1.0)
    end
end

function bhv_arena_flag_check_drop(obj)
    if not network_is_server() then
        return
    end

    if obj.oArenaFlagHeldByGlobal == ARENA_FLAG_INVALID_GLOBAL then
        return
    end

    local np = network_player_from_global_index(obj.oArenaFlagHeldByGlobal)
    if np == nil then
        bhv_arena_flag_return(obj, true)
        return
    end

    local m = gMarioStates[np.localIndex]
    local s = gPlayerSyncTable[np.localIndex]
    if not active_player(m) then
        bhv_arena_flag_return(obj, true)
        return
    end

    if mario_health_float(m) <= 0 then
        obj.oArenaFlagHeldByGlobal = ARENA_FLAG_INVALID_GLOBAL
        obj.oArenaFlagAtBase = 0
        obj.oTimer = 0
        network_send_object(obj, true)
        local msg = string.format('%s%s dropped the %s%s%s flag!', team_color_str(s.team), strip_colors(np.name), team_color_str(obj.oArenaFlagTeam), team_name_str(obj.oArenaFlagTeam), team_color_str(s.team))
        send_arena_flag(obj.oArenaFlagTeam, ARENA_FLAG_INVALID_GLOBAL, msg)
        return
    end
end

function bhv_arena_flag_check_death(npVictim)
    if not network_is_server() then
        return
    end
    if npVictim == nil then
        return
    end
    for teamNum = 0, 2 do
        local data = gArenaFlagInfo[teamNum]
        if data ~= nil and data.obj ~= nil and npVictim.globalIndex == data.obj.oArenaFlagHeldByGlobal then
            bhv_arena_flag_return(data.obj, true)
        end
    end
end

function bhv_arena_flag_check_return(obj)
    if not network_is_server() then
        return
    end
    if obj.oArenaFlagHeldByGlobal ~= ARENA_FLAG_INVALID_GLOBAL then
        return
    end
    if obj.oArenaFlagAtBase == 1 then
        return
    end
    if obj.oTimer > 30 * 30 then
        obj.oTimer = 0
        bhv_arena_flag_return(obj, true)
    end
end

function bhv_arena_flag_reset()
    for teamNum = 0, 2 do
        local data = gArenaFlagInfo[teamNum]
        if data ~= nil and data.obj ~= nil then
            bhv_arena_flag_return(data.obj, false)
        end
    end
end

function bhv_arena_flag_hide(obj)
    if gGlobalSyncTable.gameMode == GAME_MODE_CTF and (obj.oArenaFlagTeam == 1 or obj.oArenaFlagTeam == 2) then
        cur_obj_unhide()
        return false
    elseif (gGlobalSyncTable.gameMode == GAME_MODE_FT or gGlobalSyncTable.gameMode == GAME_MODE_TFT) and obj.oArenaFlagTeam == 0 then
        cur_obj_unhide()
        return false
    else
        cur_obj_hide()
        return true
    end
end

function is_holding_flag(m)
    local np = gNetworkPlayers[m.playerIndex]
    for teamNum = 0, 2 do
        local data = gArenaFlagInfo[teamNum]
        if data ~= nil and data.obj ~= nil and np.globalIndex == data.obj.oArenaFlagHeldByGlobal then
            return true
        end
    end
    return false
end

function bhv_arena_flag_loop(obj)
    if bhv_arena_flag_hide(obj) then
        return
    end
    bhv_arena_flag_update_pos_rot(obj)
    bhv_arena_flag_update_score(obj)
    bhv_arena_flag_check_collect(obj)
    bhv_arena_update_scale(obj)
    bhv_arena_flag_check_drop(obj)
    bhv_arena_flag_check_return(obj)
end

id_bhvArenaFlag = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_arena_flag_init, bhv_arena_flag_loop)
