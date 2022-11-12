-- name: Counter-Op
-- description: All players except the host will try to kill the host

gServerSettings.playerInteractions = PLAYER_INTERACTIONS_PVP

function get_main_character()
    local np = network_player_from_global_index(0)
    if np == nil then
        np = gNetworkPlayers[0]
    end
    return gMarioStates[np.localIndex]
end

function is_main_character(m)
    local main = get_main_character()
    return m.playerIndex == main.playerIndex
end

function does_level_match(m1, m2)
    local np1 = gNetworkPlayers[m1.playerIndex]
    local np2 = gNetworkPlayers[m2.playerIndex]
    if np1.currActNum ~= np2.currActNum then
        return false
    end
    if np1.currAreaIndex ~= np2.currAreaIndex then
        return false
    end
    if np1.currCourseNum ~= np2.currCourseNum then
        return false
    end
    if np1.currLevelNum ~= np2.currLevelNum then
        return false
    end
    return true
end

function mario_update_local(m)
    if not is_main_character(m) then
        local main = get_main_character()
        local mainNp = gNetworkPlayers[main.playerIndex]
        --print('>>>', mainNp.globalIndex, mainNp.currAreaSyncValid, mainNp.currLevelSyncValid)
        --if mainNp.currAreaSyncValid and mainNp.currLevelSyncValid then
            if not does_level_match(m, main) then
                warp_to_level(mainNp.currLevelNum, mainNp.currAreaIndex, mainNp.currActNum)
            end
        --end
    end
end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end

    local np = gNetworkPlayers[m.playerIndex]
    if is_main_character(m) then
        m.visibleToEnemies = 1
        if np.modelIndex == CT_TOAD then
            np.overrideModelIndex = CT_MARIO
        end
    else
        m.visibleToEnemies = 0
        if np.modelIndex ~= CT_TOAD then
            np.overrideModelIndex = CT_TOAD
        end
    end
end

function allow_pvp_attack(m1, m2)
    return m1.visibleToEnemies ~= m2.visibleToEnemies
end

function allow_interact(m, obj, interactType)
    if not is_main_character(m) then
        if (interactType & INTERACT_WARP) ~= 0 then return true end
        if (interactType & INTERACT_WARP_DOOR) ~= 0 then return true end
        if (interactType & INTERACT_STRONG_WIND) ~= 0 then return true end
        if (interactType & INTERACT_BBH_ENTRANCE) ~= 0 then return true end
        if (interactType & INTERACT_PLAYER) ~= 0 then return true end
        return false
    end

    return true
end

hook_event(HOOK_ALLOW_INTERACT, allow_interact)
hook_event(HOOK_ALLOW_PVP_ATTACK, allow_pvp_attack)
hook_event(HOOK_MARIO_UPDATE, mario_update)