-- name: Hide and Seek
-- incompatible: gamemode
-- description: A simple manhunt gamemode for Co-op.\n\nThe game is split into two teams:\n\nHiders and Seekers. The goal is for all\n\Hiders to be converted into a Seeker within a certain timeframe.\n\nAll Seekers appear as a metal character, and are given boosted speed\n\and jump height.\n\nHiders are given no enhancements, and\n\become a Seeker upon dying.\n\nEnjoy! :D\n\nConcept by: Super Keeberghrh

sStaleTimer = 0
sWasLocalSeeking = false

function update(m)
    -- only allow the server to figure out the seeker
    if not network_is_server() then
        return
    end

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

        -- pick random seeker
        if not hasSeeker then
            s = activePlayers[math.random(#activePlayers)]
            s.seeking = true
        end
    end
end

function mario_local_update(m)
    -- this code only runs for the local player
    local s = gPlayerSyncTable[m.playerIndex]

    -- disabled code that allows players to swap teams
    --if (m.controller.buttonPressed & D_JPAD) ~= 0 and m.action == ACT_CROUCHING then
    --    s.seeking = not s.seeking
    --end

    if m.health <= 0x110 then
        s.seeking = true
    end

    if s.seeking and not sWasLocalSeeking then
        play_sound(SOUND_OBJ_BOWSER_LAUGH, m.marioObj.header.gfx.cameraToObject)
    elseif not s.seeking and sWasLocalSeeking then
        play_character_sound(m, CHAR_SOUND_HERE_WE_GO)
    end

    sWasLocalSeeking = s.seeking

end

function mario_update(m)
    -- this code runs for all players
    local s = gPlayerSyncTable[m.playerIndex]

    -- display all seekers as metal
    if s.seeking then
        m.marioBodyState.modelState = MODEL_STATE_METAL
        m.health = 0x880
    end


    -- only run the following code for the local player
    if m.playerIndex == 0 then
        mario_local_update(m)
    end
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
