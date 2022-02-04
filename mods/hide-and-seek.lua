-- name: Hide and Seek
-- incompatible: gamemode
-- description: A simple manhunt gamemode for Co-op.\n\nThe game is split into two teams:\n\nHiders and Seekers. The goal is for all\n\Hiders to be converted into a Seeker within a certain timeframe.\n\nAll Seekers appear as a metal character, and are given boosted speed\n\and jump height.\n\nHiders are given no enhancements, and\n\become a Seeker upon dying.\n\nEnjoy! :D\n\nConcept by: Super Keeberghrh

-- cache old seeking state for sounds and popups
sCachedState = {}
for i=0,(MAX_PLAYERS-1) do
    sCachedState[i] = {}
    sCachedState[i].seeking = false
end

-- keep track of round numbers for popup
sCachedRoundNumber = 0
gGlobalSyncTable.roundNumber = 0

-- timer for server to start a new round
sStaleTimer = 0

-- server keeps track of last player turned seeker
sLastSeekerIndex = 0

-- keep track of distance moved recently
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
    for i=0,(MAX_PLAYERS-1) do
        if gNetworkPlayers[i].connected then
            table.insert(activePlayers, gPlayerSyncTable[i])
            if gPlayerSyncTable[i].seeking then
                hasSeeker = true
            else
                hasHider = true
            end
        end
    end

    -- increment stale timer
    if not hasHider or not hasSeeker then
        sStaleTimer = sStaleTimer + 1
    else
        sStaleTimer = 0
    end

    -- if there have been no hiders, or no seekers, for 5 seconds
    if sStaleTimer >= 30 * 5 then
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
    end
end

function update()
    -- only allow the server to figure out the seeker
    if network_is_server() then
        server_update(gMarioStates[0])
    end

    -- inform players when a new round has begun
    if sCachedRoundNumber < gGlobalSyncTable.roundNumber then
        sCachedRoundNumber = gGlobalSyncTable.roundNumber
        djui_popup_create('\\#a0ffa0\\a new round has begun', 2)
        sDistanceMoved = 100
        sDistanceTimer = 0
        play_character_sound(gMarioStates[0], CHAR_SOUND_HERE_WE_GO)
    end

    camping_detection(gMarioStates[0])
end

function camping_detection(m)
    -- this code only runs for the local player
    local s = gPlayerSyncTable[m.playerIndex]

    -- become a seeker if you stop moving
    sDistanceMoved = sDistanceMoved - 0.25 + vec3f_dist(sLastPos, m.pos) * 0.02
    vec3f_copy(sLastPos, m.pos)
    if sDistanceMoved > 100 then
        sDistanceMoved = 100
    end
    if sDistanceMoved < 0 then
        sDistanceMoved = 0
    end
    if sDistanceMoved < 10 and not s.seeking then
        sDistanceTimer = sDistanceTimer + 1
        if sDistanceTimer == 30 * 1 then
            djui_popup_create('\\#ff4040\\Keep moving!', 3)
        elseif sDistanceTimer > 30 * 6 then
            s.seeking = true
        end
    end
    if sDistanceMoved > 20 then
        sDistanceTimer = 0
    end
end

function mario_local_update(m)
    -- this code only runs for the local player
    local s = gPlayerSyncTable[m.playerIndex]

    if m.health <= 0x110 then
        s.seeking = true
    end
end

function mario_update(m)
    -- this code runs for all players
    local s = gPlayerSyncTable[m.playerIndex]

    -- only run certain code for the local player
    if m.playerIndex == 0 then
        mario_local_update(m)
    end

    -- display all seekers as metal
    if s.seeking then
        m.marioBodyState.modelState = MODEL_STATE_METAL
        m.health = 0x880
    end

    -- play sound and create popup if seeker state changed
    local c = sCachedState[m.playerIndex]
    local np = gNetworkPlayers[m.playerIndex]

    if s.seeking and not c.seeking then
        play_sound(SOUND_OBJ_BOWSER_LAUGH, m.marioObj.header.gfx.cameraToObject)
        playerColor = network_get_player_text_color_string(m.playerIndex)
        djui_popup_create(playerColor .. np.name .. '\\#ffa0a0\\ is now a seeker', 2)
        sLastSeekerIndex = m.playerIndex
    end
    c.seeking = s.seeking
end

function mario_before_phys_step(m)
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

-----------
-- hooks --
-----------

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_BEFORE_PHYS_STEP, mario_before_phys_step)
hook_event(HOOK_ON_PVP_ATTACK, on_pvp_attack)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)
