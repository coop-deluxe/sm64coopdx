-- name: Arena
-- description: An arena-shooter inspired game mode with custom weapons and levels.\nSeven gamemodes in one, three custom stages, and five weapons.
-- incompatible: gamemode arena
-- pausable: false

GAME_STATE_ACTIVE   = 1
GAME_STATE_INACTIVE = 2

GAME_MODE_DM    = 1
GAME_MODE_TDM   = 2
GAME_MODE_CTF   = 3
GAME_MODE_FT    = 4
GAME_MODE_TFT   = 5
GAME_MODE_KOTH  = 6
GAME_MODE_TKOTH = 7

gGameModes = {
    [GAME_MODE_DM]    = { shortName = 'DM',    name = 'Deathmatch',            teams = false, teamSpawns = false, useScore = false, scoreCap = 10,  minPlayers = 0, maxPlayers = 99 },
    [GAME_MODE_TDM]   = { shortName = 'TDM',   name = 'Team Deathmatch',       teams = true,  teamSpawns = false, useScore = false, scoreCap = 20,  minPlayers = 4, maxPlayers = 99 },
    [GAME_MODE_CTF]   = { shortName = 'CTF',   name = 'Capture the Flag',      teams = true,  teamSpawns = true,  useScore = false, scoreCap =  3,  minPlayers = 4, maxPlayers = 99 },
    [GAME_MODE_FT]    = { shortName = 'FT',    name = 'Flag Tag',              teams = false, teamSpawns = false, useScore = true,  scoreCap = 60,  minPlayers = 0, maxPlayers = 99 },
    [GAME_MODE_TFT]   = { shortName = 'TFT',   name = 'Team Flag Tag',         teams = true,  teamSpawns = false, useScore = true,  scoreCap = 120, minPlayers = 4, maxPlayers = 99 },
    [GAME_MODE_KOTH]  = { shortName = 'KOTH',  name = 'King of the Hill',      teams = false, teamSpawns = false, useScore = true,  scoreCap = 45,  minPlayers = 0, maxPlayers = 6  },
    [GAME_MODE_TKOTH] = { shortName = 'TKOTH', name = 'Team King of the Hill', teams = true,  teamSpawns = false, useScore = true,  scoreCap = 90,  minPlayers = 4, maxPlayers = 99 }
}

LEVEL_ARENA_ORIGIN    = level_register('level_arena_origin_entry',    COURSE_NONE, 'Origin',    'origin',    28000, 0x08, 0x08, 0x08)
LEVEL_ARENA_SKY_BEACH = level_register('level_arena_sky_beach_entry', COURSE_NONE, 'Sky Beach', 'beach',     28000, 0x08, 0x08, 0x08)
LEVEL_ARENA_PILLARS   = level_register('level_arena_pillars_entry',   COURSE_NONE, 'Pillars',   'pillars',   28000, 0x08, 0x08, 0x08)
LEVEL_ARENA_FORTS     = level_register('level_arena_forts_entry',     COURSE_NONE, 'Forts',     'forts',     28000, 0x08, 0x08, 0x08)
LEVEL_ARENA_CITADEL   = level_register('level_arena_citadel_entry',   COURSE_NONE, 'Citadel',   'citadel',   28000, 0x08, 0x08, 0x08)
LEVEL_ARENA_SPIRE     = level_register('level_arena_spire_entry',     COURSE_NONE, 'Spire',     'spire',     28000, 0x08, 0x08, 0x08)
LEVEL_ARENA_RAINBOW   = level_register('level_arena_rainbow_entry',   COURSE_NONE, 'Rainbow',   'rainbow',   28000, 0x28, 0x28, 0x28)
LEVEL_ARENA_CITY      = level_register('level_arena_city_entry',      COURSE_NONE, 'City',      'city',      28000, 0x28, 0x28, 0x28)

local gGameLevels = {
    { level = LEVEL_ARENA_ORIGIN,    name = 'Origin'    },
    { level = LEVEL_ARENA_SKY_BEACH, name = 'Sky Beach' },
    { level = LEVEL_ARENA_PILLARS,   name = 'Pillars'   },
    { level = LEVEL_ARENA_FORTS,     name = 'Forts'     },
    { level = LEVEL_ARENA_CITADEL,   name = 'Citadel'   },
    { level = LEVEL_ARENA_SPIRE,     name = 'Spire'     },
    { level = LEVEL_ARENA_RAINBOW,   name = 'Rainbow'   },
    { level = LEVEL_ARENA_CITY,      name = 'City'      }
}

-- expose certain functions to other mods
_G.Arena = {
    add_level = function (levelNum, levelName)
        table.insert(gGameLevels, { level = levelNum, name = levelName })
    end,
    get_player_team = function (localIndex)
        return gPlayerSyncTable[localIndex].team
    end
}

-- setup global sync table
gGlobalSyncTable.gameState = GAME_STATE_ACTIVE
gGlobalSyncTable.gameMode  = GAME_MODE_DM
gGlobalSyncTable.currentLevel = gGameLevels[math.random(#gGameLevels)].level
gGlobalSyncTable.roundsPerShuffle = 3
gGlobalSyncTable.capTeam1 = 0
gGlobalSyncTable.capTeam2 = 0
gGlobalSyncTable.kothPoint = -1
gGlobalSyncTable.message = ' '
sWaitTimerMax = 15 * 30 -- 15 seconds
sWaitTimer = 0
sRoundCount = 0

sRandomizeMode = true

-- force pvp and knockback
gServerSettings.playerInteractions = PLAYER_INTERACTIONS_PVP
gServerSettings.playerKnockbackStrength = 20

-- use fixed collisions
gLevelValues.fixCollisionBugs = 1

function calculate_rankings()
    local rankings = {}
    for i = 0, (MAX_PLAYERS - 1) do
        local s  = gPlayerSyncTable[i]
        local np = gNetworkPlayers[i]
        local m  = gMarioStates[i]
        if active_player(m) then
            local score = 0
            if gGameModes[gGlobalSyncTable.gameMode].useScore then
                score = s.score * 1000 + (1 - (np.globalIndex / MAX_PLAYERS))
            else
                score = s.kills * 1000 - s.deaths + (1 - (np.globalIndex / MAX_PLAYERS))
            end
            table.insert(rankings, { score = score, m = m })
        end
    end

    table.sort(rankings, function (v1, v2) return v1.score > v2.score end)

    for i in pairs(rankings) do
        local m = rankings[i].m
        local s = gPlayerSyncTable[m.playerIndex]
        s.rank = i
    end
end

function calculate_team_rank(teamNum)
    if teamNum < 1 or teamNum > 2 then
        return 0
    end
    local red = calculate_team_score(1)
    local blue = calculate_team_score(2)
    if teamNum == 1 then
        if red >= blue then
            return 1
        else
            return 2
        end
    else
        if blue >= red then
            return 1
        else
            return 2
        end
    end
end

function calculate_team_score(teamNum)
    if gGlobalSyncTable.gameMode == GAME_MODE_CTF then
        if teamNum == 1 then
            return gGlobalSyncTable.capTeam1
        elseif teamNum == 2 then
            return gGlobalSyncTable.capTeam2
        else
            return 0
        end
    end

    local score = 0
    for i = 0, (MAX_PLAYERS - 1) do
        local s  = gPlayerSyncTable[i]
        local np = gNetworkPlayers[i]
        if np.connected and s.team == teamNum then
            if gGameModes[gGlobalSyncTable.gameMode].useScore then
                score = score + s.score
            else
                score = score + s.kills
            end
        end
    end
    return score
end

function pick_team_on_join(m)
    -- no teams
    if not gGameModes[gGlobalSyncTable.gameMode].teams then
        return 0
    end

    -- count teams
    local teamCount = {}
    for i = 0, (MAX_PLAYERS - 1) do
        local inp = gNetworkPlayers[i]
        local is = gPlayerSyncTable[i]
        if inp.connected and i ~= m.playerIndex then
            if teamCount[is.team] == nil then
                teamCount[is.team] = 0
            end
            teamCount[is.team] = teamCount[is.team] + 1
        end
    end

    -- sanitize counts
    local redCount = teamCount[1]
    if redCount == nil then redCount = 0 end
    local blueCount = teamCount[2]
    if blueCount == nil then blueCount = 0 end

    -- pick team
    if redCount == blueCount then
        return math.random(1,2)
    elseif redCount < blueCount then
        return 1
    else
        return 2
    end
end

function shuffle_teams()
    local t = {}
    local count = 0
    -- create table of players
    for i = 0, (MAX_PLAYERS-1) do
        local m = gMarioStates[i]
        local s = gPlayerSyncTable[i]
        if active_player(m) then
            table.insert(t, s)
            count = count + 1
        end
    end

    -- shuffle
    for i = #t, 2, -1 do
        local j = math.random(i)
        t[i], t[j] = t[j], t[i]
    end

    -- assign teams
    local team1Count = 0
    local team2Count = 0
    local oddS = nil
    for i, s in ipairs(t) do
        if (i - 1) < count / 2 then
            s.team = 1
            team1Count = team1Count + 1
            oddS = s
        else
            s.team = 2
            team2Count = team2Count + 1
        end
    end

    -- shuffle odd player
    if team1Count > team2Count then
        oddS.team = math.random(1, 2)
    end
end

function round_begin()
    gGlobalSyncTable.message = ' '
    gGlobalSyncTable.gameState = GAME_STATE_ACTIVE
    gGlobalSyncTable.capTeam1 = 0
    gGlobalSyncTable.capTeam2 = 0
    gGlobalSyncTable.kothPoint = -1
    bhv_arena_flag_reset()

    local roundShuffle = false
    sRoundCount = sRoundCount + 1
    if sRoundCount >= gGlobalSyncTable.roundsPerShuffle then
        sRoundCount = 0
        roundShuffle = true
    end

    local playerCount = network_player_connected_count()

    if roundShuffle and sRandomizeMode then
        local gamemodes = {}
        for i, gm in ipairs(gGameModes) do
            if playerCount >= gm.minPlayers and playerCount <= gm.maxPlayers then
                table.insert(gamemodes, i)
            end
        end
        gGlobalSyncTable.gameMode = gamemodes[math.random(#gamemodes)]
    end

    if roundShuffle then

        local curLevel = nil

        for i, gl in ipairs(gGameLevels) do
            if gGlobalSyncTable.currentLevel == gl.level then
                curLevel = i
            end
        end

        if curLevel ~= nil then
            if curLevel >= #gGameLevels then
                curLevel = 1
            else
                curLevel = curLevel + 1
            end
            gGlobalSyncTable.currentLevel = gGameLevels[curLevel].level
        else
            gGlobalSyncTable.currentLevel = gGameLevels[math.random(#gGameLevels)].level
        end
    end

    for i = 0, (MAX_PLAYERS - 1) do
        player_reset_sync_table(gMarioStates[i])
        if not gGameModes[gGlobalSyncTable.gameMode].teams then
            local s = gPlayerSyncTable[i]
            s.team = 0
        end
    end

    if gGameModes[gGlobalSyncTable.gameMode].teams then
        shuffle_teams()
    end

    send_arena_respawn()
end

function round_end()
    calculate_rankings()

    gGlobalSyncTable.gameState = GAME_STATE_INACTIVE
    sWaitTimer = sWaitTimerMax

    if gGlobalSyncTable.gameMode == GAME_MODE_DM or gGlobalSyncTable.gameMode == GAME_MODE_FT or gGlobalSyncTable.gameMode == GAME_MODE_KOTH then
        lowestRank = 999
        winner = nil
        for i = 0, (MAX_PLAYERS - 1) do
            local m  = gMarioStates[i]
            local s  = gPlayerSyncTable[i]
            local np = gNetworkPlayers[i]
            if np.connected and s.rank > 0 and s.rank < lowestRank then
                lowestRank = s.rank
                winner = m
            end
        end

        if winner ~= nil then
            local winnerNp = gNetworkPlayers[winner.playerIndex]
            gGlobalSyncTable.message = strip_colors(winnerNp.name) .. ' Wins!'
        else
            gGlobalSyncTable.message = 'Round Ended'
        end
    elseif gGlobalSyncTable.gameMode == GAME_MODE_TDM or gGlobalSyncTable.gameMode == GAME_MODE_CTF or gGlobalSyncTable.gameMode == GAME_MODE_TFT or gGlobalSyncTable.gameMode == GAME_MODE_TKOTH then
        local redScore  = calculate_team_score(1)
        local blueScore = calculate_team_score(2)
        if redScore > blueScore then
            gGlobalSyncTable.message = 'Red Team Wins!'
        elseif blueScore > redScore then
            gGlobalSyncTable.message = 'Blue Team Wins!'
        else
            gGlobalSyncTable.message = 'Round Ended'
        end
    else
        gGlobalSyncTable.message = 'Round Ended'
    end
end

function on_arena_player_death(victimGlobalId, attackerGlobalId)
    local npVictim   = network_player_from_global_index(victimGlobalId)
    local npAttacker = network_player_from_global_index(attackerGlobalId)
    if npVictim == nil then
        return
    end

    if network_is_server() then
        bhv_arena_flag_check_death(npVictim)
    end

    local sVictim = gPlayerSyncTable[npVictim.localIndex]
    local sAttacker = nil
    if npAttacker ~= nil then sAttacker = gPlayerSyncTable[npAttacker.localIndex] end
    local normalColor = '\\#dcdcdc\\'

    if npAttacker == nil or npVictim == npAttacker then
        -- create popup
        local victimColor = network_get_player_text_color_string(npVictim.localIndex)
        djui_popup_create(victimColor .. npVictim.name .. normalColor .. " died!", 2)

        -- adjust deaths/kills
        if network_is_server() and gGlobalSyncTable.gameState == GAME_STATE_ACTIVE then
            sVictim.deaths = sVictim.deaths + 1
            if sVictim.kills > 0 then
                sVictim.kills = sVictim.kills - 1
            end
        end
    else
        -- create popup
        local victimColor = network_get_player_text_color_string(npVictim.localIndex)
        local attackerColor = network_get_player_text_color_string(npAttacker.localIndex)
        djui_popup_create(attackerColor .. npAttacker.name .. normalColor .. " killed " .. victimColor .. npVictim.name .. normalColor .. "!", 2)

        -- adjust deaths/kills
        if network_is_server() and gGlobalSyncTable.gameState == GAME_STATE_ACTIVE then
            sVictim.deaths = sVictim.deaths + 1
            sAttacker.kills = sAttacker.kills + 1
        end
    end

    if network_is_server() and gGlobalSyncTable.gameState == GAME_STATE_ACTIVE then
        if gGlobalSyncTable.gameMode == GAME_MODE_DM then
            if sAttacker ~= nil and sAttacker.kills >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
                round_end()
            end
        elseif gGlobalSyncTable.gameMode == GAME_MODE_TDM then
            if sAttacker.team ~= 0 then
                local teamScore = calculate_team_score(sAttacker.team)
                if teamScore >= gGameModes[gGlobalSyncTable.gameMode].scoreCap then
                    round_end()                    
                end
            end
        end
    end
end

function end_round_if_team_empty()
    if not sRandomizeMode then
        return
    end
    local redCount = 0
    local blueCount = 0
    for i = 0, (MAX_PLAYERS - 1) do
        local s  = gPlayerSyncTable[i]
        local np = gNetworkPlayers[i]
        if np.connected then
            if s.team == 1 then
                redCount = redCount + 1
            elseif s.team == 2 then
                blueCount = blueCount + 1
            end
        end
    end
    if redCount == 0 or blueCount == 0 then
        round_end()
    end
end

---

local function split(s)
    local result = {}
    for match in (s):gmatch(string.format("[^%s]+", " ")) do
        table.insert(result, match)
    end
    return result
end

function level_check()
    local np = gNetworkPlayers[0]
    if np.currLevelNum ~= gGlobalSyncTable.currentLevel or np.currActNum ~= 1 or np.currAreaIndex ~= 1 then
        warp_to_level(gGlobalSyncTable.currentLevel, 1, 1)
        return false
    end
    return true
end

function on_sync_valid()
    if level_check() then
        player_respawn(gMarioStates[0])
    end
end

function on_pause_exit(exitToCastle)
    return false
end

function on_server_update()
    if gGlobalSyncTable.gameState == GAME_STATE_ACTIVE then
        calculate_rankings()
        if gGameModes[gGlobalSyncTable.gameMode].teams then
            end_round_if_team_empty()
        end
    elseif gGlobalSyncTable.gameState == GAME_STATE_INACTIVE then
        sWaitTimer = sWaitTimer - 1
        if sWaitTimer <= 0 then
            sWaitTimer = 0
            round_begin()
        end
    end
end

function on_update()
    if network_is_server() then
        on_server_update()
    end
    local np = gNetworkPlayers[0]
    if np.currAreaSyncValid then
        level_check()
    end
end

function on_gamemode_command(msg)
    msg = msg:lower()
    local setMode = nil

    for i, gm in ipairs(gGameModes) do
        if msg == gm.shortName:lower() then
            setMode = i
        end
    end

    if msg == 'random' then
        djui_chat_message_create("[Arena] Setting to random gamemode.")
        sRandomizeMode = true
        round_end()
        sWaitTimer = 1
        sRoundCount = 0
        return true
    end

    if setMode ~= nil then
        djui_chat_message_create("[Arena] Setting game mode.")
        gGlobalSyncTable.gameMode = setMode
        sRandomizeMode = false
        round_end()
        sWaitTimer = 1
        sRoundCount = 0
        return true
    end

    djui_chat_message_create("/arena \\#00ffff\\gamemode\\#ffff00\\ " .. string.format("[%s|random]\\#dcdcdc\\ sets gamemode", sGameModeShortTimes))
    return true
end

function on_level_command(msg)
    msg = msg:lower()
    local setLevel = nil

    for i, gl in ipairs(gGameLevels) do
        if msg == gl.name:lower() then
            setLevel = i
        end
    end

    if setLevel ~= nil then
        gGlobalSyncTable.currentLevel = gGameLevels[setLevel].level
        round_end()
        sWaitTimer = 1
        sRoundCount = 0
        return true
    end

    djui_chat_message_create("/arena \\#00ffff\\level\\#ffff00\\ " .. string.format("[%s]\\#dcdcdc\\ sets level", get_level_choices()))
    return true
end

function on_jump_leniency_command(msg)
    local num = tonumber(msg)
    if not network_is_server and not network_is_moderator() then
        djui_chat_message_create("\\#ffa0a0\\[Arena] You need to be a moderator to use this command.")
        return true
    elseif num == nil then
        djui_chat_message_create("\\#ffa0a0\\[Arena] Invalid number!")
        return true
    else
        gGlobalSyncTable.jumpLeniency = num
        djui_chat_message_create("[Arena] The number of jump leniency frames has been set to " .. num)
        return true
    end
end

local function on_arena_command(msg)
    local args = split(msg)
    if args[1] == "gamemode" then
        return on_gamemode_command(args[2] or "")
    elseif args[1] == "level" then
        local name = args[2] or ""
        if args[3] ~= nil then
            name = name .. " " .. args[3]
        end
        return on_level_command(name or "")
    elseif args[1] == "jump-leniency" then
        return on_jump_leniency_command(args[2] or "")
    end

    djui_chat_message_create("/arena \\#00ffff\\[gamemode|level|jump-leniency]")
    return true
end

hook_event(HOOK_ON_SYNC_VALID, on_sync_valid)
hook_event(HOOK_ON_PAUSE_EXIT, on_pause_exit)
hook_event(HOOK_UPDATE, on_update)

sGameModeShortTimes = ''
for i, gm in ipairs(gGameModes) do
    if string.len(sGameModeShortTimes) > 0 then
        sGameModeShortTimes = sGameModeShortTimes .. '|'
    end
    sGameModeShortTimes = sGameModeShortTimes .. gm.shortName
end

function get_level_choices()
    local levelChoices = ''
    for i, gl in ipairs(gGameLevels) do
        if string.len(levelChoices) > 0 then
            levelChoices = levelChoices .. '|'
        end
        levelChoices = levelChoices .. gl.name
    end
    return levelChoices
end

if network_is_server() then
    hook_chat_command("arena", "\\#00ffff\\[gamemode|level|jump-leniency]", on_arena_command)
end

if _G.dayNightCycleApi ~= nil then
    _G.dayNightCycleApi.enable_day_night_cycle(false)
end
