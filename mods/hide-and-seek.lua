-- name: Hide and Seek
-- incompatible: gamemode
-- description: A simple manhunt gamemode for Co-op.\n\nThe game is split into two teams:\n\nHiders and Seekers. The goal is for all\n\Hiders to be converted into a Seeker within a certain timeframe.\n\nAll Seekers appear as a metal character, and are given boosted speed\n\and jump height.\n\nHiders are given no enhancements, and\n\become a Seeker upon dying.\n\nEnjoy! :D\n\nConcept by: Super Keeberghrh

-- globally sync enabled state
gGlobalSyncTable.hideAndSeek = true

-- keep track of round info for popup
gGlobalSyncTable.roundNumber = 0
gGlobalSyncTable.roundEnded = true
sRoundEndedTimer = 0
sRoundIntermissionTime = 5 * 30 -- five seconds

-- server keeps track of last player turned seeker
sLastSeekerIndex = 0

-- keep track of distance moved recently (camping detection)
sLastPos = {}
sLastPos.x = 0
sLastPos.y = 0
sLastPos.z = 0
sDistanceMoved = 0
sDistanceTimer = 0

function server_update(m)
    -- figure out state of the game
    local hasSeeker = false
    local hasHider = false
    local activePlayers = {}
    local connectedCount = 0
    for i=0,(MAX_PLAYERS-1) do
        if gNetworkPlayers[i].connected then
            connectedCount = connectedCount + 1
            table.insert(activePlayers, gPlayerSyncTable[i])
            if gPlayerSyncTable[i].seeking then
                hasSeeker = true
            else
                hasHider = true
            end
        end
    end

    -- only change state if there are 2+ players
    if connectedCount < 2 then
        sRoundEndedTimer = 0
        return
    end

    -- check to see if the round should end
    if not gGlobalSyncTable.roundEnded then
        if not hasHider or not hasSeeker then
            gGlobalSyncTable.roundEnded = true
            sRoundEndedTimer = 0
        else
            return
        end
    end

    -- if round was over for 5 seconds
    sRoundEndedTimer = sRoundEndedTimer + 1
    if sRoundEndedTimer >= sRoundIntermissionTime then
        -- reset seekers
        if not hasHider then
            for i=0,(MAX_PLAYERS-1) do
                gPlayerSyncTable[i].seeking = false
            end
            hasSeeker = false
        end

        -- set seeker to last one turned into seeker
        local np = gNetworkPlayers[sLastSeekerIndex]
        if np.connected then
            local s = gPlayerSyncTable[sLastSeekerIndex]
            s.seeking = true
            hasSeeker = true
        end

        -- pick random seeker if last turned to seeker is invalid
        if not hasSeeker then
            local s = activePlayers[math.random(#activePlayers)]
            s.seeking = true
        end

        -- increment round number
        gGlobalSyncTable.roundNumber = gGlobalSyncTable.roundNumber + 1
        gGlobalSyncTable.roundEnded = false
    end
end

function camping_detection(m)
    -- this code only runs for the local player
    local s = gPlayerSyncTable[m.playerIndex]

    -- track how far the local player has moved recently
    sDistanceMoved = sDistanceMoved - 0.25 + vec3f_dist(sLastPos, m.pos) * 0.02
    vec3f_copy(sLastPos, m.pos)

    -- clamp between 0 to 100
    if sDistanceMoved < 0   then sDistanceMoved = 0   end
    if sDistanceMoved > 100 then sDistanceMoved = 100 end

    -- if player hasn't moved enough, start a timer
    if sDistanceMoved < 10 and not s.seeking then
        sDistanceTimer = sDistanceTimer + 1
    end

    -- if the player has moved enough, reset the timer
    if sDistanceMoved > 20 then
        sDistanceTimer = 0
    end

    -- inform the player that they need to move, or make them a seeker
    if sDistanceTimer == 30 * 1 then
        djui_popup_create('\\#ff4040\\Keep moving!', 3)
    elseif sDistanceTimer > 30 * 6 then
        s.seeking = true
    end
end

function update()
    -- check gamemode enabled state
    if not gGlobalSyncTable.hideAndSeek then
        return
    end

    -- only allow the server to figure out the seeker
    if network_is_server() then
        server_update(gMarioStates[0])
    end

    -- check if local player is camping
    camping_detection(gMarioStates[0])
end

function mario_update(m)
    -- check gamemode enabled state
    if not gGlobalSyncTable.hideAndSeek then
        return
    end

    -- this code runs for all players
    local s = gPlayerSyncTable[m.playerIndex]

    -- if the local player died, make them a seeker
    if m.playerIndex == 0 and m.health <= 0x110 then
        s.seeking = true
    end

    -- display all seekers as metal
    if s.seeking then
        m.marioBodyState.modelState = MODEL_STATE_METAL
        m.health = 0x880
    end
end

function mario_before_phys_step(m)
    -- check gamemode enabled state
    if not gGlobalSyncTable.hideAndSeek then
        return
    end

    local s = gPlayerSyncTable[m.playerIndex]

    -- only make seekers faster
    if not s.seeking then
        return
    end

    local hScale = 1.0
    local vScale = 1.0

    -- make swimming seekers 5% faster
    if (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        hScale = hScale * 1.05
        if m.action ~= ACT_WATER_PLUNGE then
            vScale = vScale * 1.05
        end
    end

    -- faster ground movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 then
        hScale = hScale * 1.19
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

function on_pvp_attack(attacker, victim)
    -- check gamemode enabled state
    if not gGlobalSyncTable.hideAndSeek then
        return
    end

    -- this code runs when a player attacks another player
    local sAttacker = gPlayerSyncTable[attacker.playerIndex]
    local sVictim = gPlayerSyncTable[victim.playerIndex]

    -- only consider local player
    if victim.playerIndex ~= 0 then
        return
    end

    -- make victim a seeker
    if sAttacker.seeking and not sVictim.seeking then
        sVictim.seeking = true
    end
end

function on_player_connected(m)
    -- start out as a non-seeker
    local s = gPlayerSyncTable[m.playerIndex]
    s.seeking = false
end

function on_hide_and_seek_command(msg)
    if not network_is_server() then
        djui_chat_message_create('Only the server can change this setting!')
        return true
    end
    if msg == 'on' then
        djui_chat_message_create('Hide-and-seek mod: enabled')
        gGlobalSyncTable.hideAndSeek = true
        return true
    elseif msg == 'off' then
        djui_chat_message_create('Hide-and-seek mod: disabled')
        gGlobalSyncTable.hideAndSeek = false
        return true
    end
    return false
end

-----------------------
-- network callbacks --
-----------------------

function on_round_number_changed(tag, oldVal, newVal)
    -- inform players when a new round has begun
    if oldVal < newVal then
        djui_popup_create('\\#a0ffa0\\a new round has begun', 2)
        sDistanceMoved = 100
        sDistanceTimer = 0
        play_character_sound(gMarioStates[0], CHAR_SOUND_HERE_WE_GO)
    end
end

function on_round_ended_changed(tag, oldVal, newVal)
    -- inform players when a round has ended
    if newVal and not oldVal then
        djui_popup_create('\\#a0a0ff\\the round has ended', 2)
    end
end

function on_seeking_changed(tag, oldVal, newVal)
    local m = gMarioStates[tag]
    local np = gNetworkPlayers[tag]

    -- play sound and create popup if became a seeker
    if newVal and not oldVal then
        play_sound(SOUND_OBJ_BOWSER_LAUGH, m.marioObj.header.gfx.cameraToObject)
        playerColor = network_get_player_text_color_string(m.playerIndex)
        djui_popup_create(playerColor .. np.name .. '\\#ffa0a0\\ is now a seeker', 2)
        sLastSeekerIndex = m.playerIndex
    end
end

-----------
-- hooks --
-----------

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_BEFORE_PHYS_STEP, mario_before_phys_step)
hook_event(HOOK_ON_PVP_ATTACK, on_pvp_attack)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)

hook_chat_command('hide-and-seek', "[on|off] turn hide-and-seek on or off", on_hide_and_seek_command)

-- call functions when certain sync table values change
hook_on_sync_table_change(gGlobalSyncTable, 'roundNumber', 0, on_round_number_changed)
hook_on_sync_table_change(gGlobalSyncTable, 'roundEnded', 0, on_round_ended_changed)
for i=0,(MAX_PLAYERS-1) do
    hook_on_sync_table_change(gPlayerSyncTable[i], 'seeking', i, on_seeking_changed)
end
