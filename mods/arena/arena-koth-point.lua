sArenaKothPoints = {}

function bhv_arena_koth_init(obj)
    table.insert(sArenaKothPoints, {
        pos = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ },
    })
    obj_mark_for_deletion(obj)
end

id_bhvArenaKoth = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_arena_koth_init, nil)

-------------

function find_koth_point()
    if #sArenaKothPoints == 0 then
        return -1
    end
    return math.random(#sArenaKothPoints)
end

-------------

gArenaKothActiveObj = nil
sArenaKothActiveLastRewardM = nil

function bhv_arena_koth_active_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    cur_obj_hide()
end

function bhv_arena_koth_active_loop(obj)
    -- sanity check like crazy
    if gGlobalSyncTable.gameMode ~= GAME_MODE_KOTH and gGlobalSyncTable.gameMode ~= GAME_MODE_TKOTH then
        cur_obj_hide()
        return
    end
    if gGlobalSyncTable.kothPoint < 1 or gGlobalSyncTable.kothPoint >= #sArenaKothPoints then
        if network_is_server() then
            gGlobalSyncTable.kothPoint = find_koth_point()
        end
        cur_obj_hide()
        return
    end
    local point = sArenaKothPoints[gGlobalSyncTable.kothPoint]
    if point == nil then
        if network_is_server() then
            gGlobalSyncTable.kothPoint = find_koth_point()
        end
        cur_obj_hide()
        return
    end

    -- unhide and rotate
    cur_obj_unhide()
    obj.oPosX = point.pos.x
    obj.oPosY = point.pos.y
    obj.oPosZ = point.pos.z
    obj.oFaceAngleYaw = obj.oFaceAngleYaw - 0x100

    -- figure out who is inside
    if (obj.oTimer % 10) == 0 and gGlobalSyncTable.gameState == GAME_STATE_ACTIVE then
        local containsM = nil
        local countM = 0
        local containsTeam = nil
        local teamMatch = true
        for i = 0, MAX_PLAYERS - 1 do
            local m = gMarioStates[i]
            local s = gPlayerSyncTable[i]
            local dX = obj.oPosX - m.pos.x
            local dY = obj.oPosY - m.pos.y
            local dZ = obj.oPosZ - m.pos.z
            local xzDist = math.sqrt(dX * dX + dZ * dZ)
            if active_player(m) and mario_health_float(m) > 0 and xzDist <= 440 and dY <= 10 and dY >= -1000 then
                if containsM == nil or m == sArenaKothActiveLastRewardM then
                    containsM = m
                end
                countM = countM + 1
                if containsTeam == nil then
                    containsTeam = s.team
                elseif containsTeam ~= s.team then
                    teamMatch = false
                end
            end
        end

        local rewardM = nil
        if gGlobalSyncTable.gameMode == GAME_MODE_KOTH and countM == 1 then
            rewardM = containsM
        elseif gGlobalSyncTable.gameMode == GAME_MODE_TKOTH and teamMatch == true then
            rewardM = containsM
        end

        if rewardM ~= nil then
            local s = gPlayerSyncTable[rewardM.playerIndex]
            local np = gNetworkPlayers[rewardM.playerIndex]
            if np ~= nil and s ~= nil then
                if network_is_server() and (obj.oTimer % 30) == 0 then
                    s.score = s.score + 1
                    if gGlobalSyncTable.gameMode == GAME_MODE_KOTH and s.score >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
                        round_end()
                    elseif gGlobalSyncTable.gameMode == GAME_MODE_TKOTH and calculate_team_score(s.team) >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
                        round_end()
                    end
                end
                obj_set_model_extended(obj, E_MODEL_KOTH_ACTIVE)
                obj.globalPlayerIndex = np.globalIndex
            else
                obj_set_model_extended(obj, E_MODEL_KOTH)
            end
        else
            obj_set_model_extended(obj, E_MODEL_KOTH)
        end
        sArenaKothActiveLastRewardM = rewardM

    end
end

id_bhvArenaKothActive = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_arena_koth_active_init, bhv_arena_koth_active_loop)

-------------

function on_level_init()
    sArenaKothPoints = {}
    gArenaKothActiveObj = spawn_non_sync_object(id_bhvArenaKothActive, E_MODEL_KOTH, 0, 0, 0, nil)
end

hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
