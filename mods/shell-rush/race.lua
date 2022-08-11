gRankings = {}

GAME_STATE_INACTIVE = 0
GAME_STATE_RACE_COUNTDOWN = 1
GAME_STATE_RACE_ACTIVE = 2
GAME_STATE_RACE_FINISH = 3

gGlobalSyncTable.maxLaps = 5
gGlobalSyncTable.gameState = GAME_STATE_INACTIVE
gGlobalSyncTable.gotoLevel = -1
gGlobalSyncTable.raceStartTime = 0
gGlobalSyncTable.raceQuitTime = 0

function race_start(level)
    gGlobalSyncTable.gotoLevel = level
    gGlobalSyncTable.gameState = GAME_STATE_RACE_COUNTDOWN
    gGlobalSyncTable.raceStartTime = 0
    gGlobalSyncTable.raceQuitTime = 0

    for i = 0, (MAX_PLAYERS - 1) do
        local s = gPlayerSyncTable[i]
        s.random = math.random()
        s.finish = 0
    end
end

function race_clear_rankings()
    for k,v in pairs(gRankings) do gRankings[k]=nil end
end

function race_increment_lap()
    local s = gPlayerSyncTable[0]
    s.lap = s.lap + 1
    if s.lap > gGlobalSyncTable.maxLaps then
        s.lap = gGlobalSyncTable.maxLaps
        if s.finish == 0 then
            s.finish = get_network_area_timer()
            play_race_fanfare()
        end
    end
end

function race_update_rankings()
    -- order players by score
    ordered = {}
    for i = 0, (MAX_PLAYERS - 1) do
        local m = gMarioStates[i]
        local s = gPlayerSyncTable[i]
        if active_player(m) then
            local score = 0
            if s.finish > 0 then
                score = (gGlobalSyncTable.maxLaps + 2) * 10000 + (10000 / s.finish)
            else
                -- figure out distance score
                local maxDist = vec3f_dist(get_waypoint(s.waypoint - 1), get_waypoint(s.waypoint))
                if maxDist == 0 then maxDist = 1 end
                local dist = vec3f_dist(m.pos, get_waypoint(s.waypoint))
                local distScore = clamp(1 - (dist/maxDist), 0, 1)

                -- figure out entire score
                local lastWaypoint = get_waypoint_index(s.waypoint - 1)
                score = s.lap * 10000 + lastWaypoint * 100 + distScore
                if s.lap == 0 then score = 0 end
            end
            if score > 0 then
                table.insert(ordered, { score = score, m = m })
            end
        end
    end

    table.sort(ordered, function (v1, v2) return v1.score > v2.score end)

    -- clear rankings
    race_clear_rankings()

    -- set rankings
    for i,v in ipairs(ordered) do
        table.insert(gRankings, v.m)
    end
end

function race_start_line()
    local index = 0
    for i = 0, (MAX_PLAYERS - 1) do
        local s = gPlayerSyncTable[i]
        if network_is_server() then
            s.finish = 0
        end
        if active_player(gMarioStates[i]) and s.random < gPlayerSyncTable[0].random then
            index = index + 1
        end
    end

    local lineIndex = (index % 2) + 1
    local lineBackIndex = index - (index % 2)

    local m = gMarioStates[0]
    local spawnLine = gLevelData.spawn[lineIndex]
    local point = vec3f_tween(spawnLine.a, spawnLine.b, lineBackIndex / MAX_PLAYERS)
    local waypoint = get_waypoint(1)

    m.pos.x = point.x
    m.pos.y = point.y
    m.pos.z = point.z

    m.marioObj.oIntangibleTimer = 5
    set_mario_action(m, ACT_RIDING_SHELL_GROUND, 0)
    m.vel.x = 0
    m.vel.y = 0
    m.vel.z = 0
    m.slideVelX = 0
    m.slideVelZ = 0
    m.forwardVel = 0
    m.faceAngle.x = 0
    m.faceAngle.y = atan2s(waypoint.z - m.pos.z, waypoint.x - m.pos.x)
    m.faceAngle.z = 0
end

function race_update()
    -- automatically start race
    if gGlobalSyncTable.gameState == GAME_STATE_INACTIVE and network_player_connected_count() > 1 then
        race_start(LEVEL_SL)
    end

    local np = gNetworkPlayers[0]
    if gGlobalSyncTable.gotoLevel ~= -1 and np.currAreaSyncValid and np.currLevelSyncValid then
        if np.currLevelNum ~= gGlobalSyncTable.gotoLevel then
            if gGlobalSyncTable.gotoLevel == LEVEL_CASTLE_GROUNDS then
                warp_to_castle(LEVEL_VCUTM)
            else
                warp_to_level(gGlobalSyncTable.gotoLevel, 1, 16)
            end
        end
    end

    -- make sure this is a valid level
    if gLevelData == gLevelDataTable[-1] then
        return
    end

    if gGlobalSyncTable.gameState == GAME_STATE_RACE_COUNTDOWN then
        race_start_line()
        race_clear_rankings()
        if network_is_server() then
            if gGlobalSyncTable.raceStartTime == 0 then
                if np.currAreaSyncValid then
                    gGlobalSyncTable.raceStartTime = get_network_area_timer() + 30 * 5
                    gGlobalSyncTable.raceQuitTime = 0
                end
            elseif gGlobalSyncTable.raceStartTime > get_network_area_timer() + 30 * 5 then
                gGlobalSyncTable.raceStartTime = get_network_area_timer() + 30 * 5
                gGlobalSyncTable.raceQuitTime = 0
            elseif gGlobalSyncTable.raceStartTime > 0 and get_network_area_timer() >= gGlobalSyncTable.raceStartTime then
                gGlobalSyncTable.gameState = GAME_STATE_RACE_ACTIVE
            end
        end

    elseif gGlobalSyncTable.gameState == GAME_STATE_RACE_ACTIVE then
        race_update_rankings()
        if network_is_server() then
            if gGlobalSyncTable.raceQuitTime == 0 then
                -- check for race finish
                local foundFinisher = false
                for i = 0, (MAX_PLAYERS - 1) do
                    local m = gMarioStates[i]
                    local s = gPlayerSyncTable[i]
                    if active_player(m) and s.finish > 0 then
                        foundFinisher = true
                    end
                end
                if foundFinisher then
                    -- set a timer until the race is finished
                    gGlobalSyncTable.raceQuitTime = get_network_area_timer() + 30 * 20
                end
            elseif gGlobalSyncTable.raceQuitTime > 0 and get_network_area_timer() > gGlobalSyncTable.raceQuitTime then
                -- race is finished, start a new one
                if gLevelData == gLevelDataTable[LEVEL_CASTLE_GROUNDS] then
                    race_start(LEVEL_BOB)
                elseif gLevelData == gLevelDataTable[LEVEL_BOB] then
                    race_start(LEVEL_SL)
                elseif gLevelData == gLevelDataTable[LEVEL_SL] then
                    race_start(LEVEL_TTM)
                elseif gLevelData == gLevelDataTable[LEVEL_TTM] then
                    race_start(LEVEL_CCM)
                elseif gLevelData == gLevelDataTable[LEVEL_CCM] then
                    race_start(LEVEL_CASTLE_GROUNDS)
                end
            end
        end
    end
end

function on_race_command(msg)
    if not network_is_server() then
        djui_chat_message_create('Only the server can change this setting!')
        return true
    end
    if msg == 'CG' then
        race_start(LEVEL_CASTLE_GROUNDS)
        return true
    end
    if msg == 'BOB' then
        race_start(LEVEL_BOB)
        return true
    end
    if msg == 'SL' then
        race_start(LEVEL_SL)
        return true
    end
    if msg == 'TTM' then
        race_start(LEVEL_TTM)
        return true
    end
    if msg == 'CCM' then
        race_start(LEVEL_CCM)
    end
    return false
end

function on_laps_command(msg)
    if not network_is_server() then
        djui_chat_message_create('Only the server can change this setting!')
        return true
    end
    if tonumber(msg) > 0 then
        gGlobalSyncTable.maxLaps = math.floor(tonumber(msg))
        return true
    end
    return false
end

function on_game_state_changed(tag, oldVal, newVal)
    local m = gMarioStates[0]
    if oldVal ~= newVal then
        if newVal == GAME_STATE_RACE_ACTIVE then
            play_sound(SOUND_GENERAL_RACE_GUN_SHOT, m.marioObj.header.gfx.cameraToObject)
        end
    end
end

if network_is_server() then
    hook_chat_command('race', "[CG|BOB|SL|TTM|CCM]", on_race_command)
    hook_chat_command('laps', "[number]", on_laps_command)
end
hook_on_sync_table_change(gGlobalSyncTable, 'gameState', i, on_game_state_changed)
