-- name: Hide and Seek
-- incompatible: gamemode
-- description: A simple hide-and-seek gamemode for\nCo-op.\n\nThe game is split into two teams:\n\nHiders and Seekers. The goal is for all\n\Hiders to be converted into a Seeker within a certain timeframe.\n\nAll Seekers appear as a metal character, and are given boosted speed\n\and jump height.\n\nHiders are given no enhancements, and\n\become a Seeker upon dying.\n\nEnjoy! :D\n\nConcept by: Super Keeberghrh

-- globally sync enabled state
gGlobalSyncTable.hideAndSeek = true

-- keep track of round info for popup
ROUND_END_UNKNOWN = 1
ROUND_END_SEEKER_WIN = 2
ROUND_END_HIDER_WIN = 3
gGlobalSyncTable.roundNumber = 0
gGlobalSyncTable.roundEnded = ROUND_END_UNKNOWN

sRoundEndedTimer = 0
sRoundEndedTimeout = 15 * 30 -- fifteen seconds
sFlashingIndex = 0
sDisplayCenterTimer = 0

-- server keeps track of last player turned seeker
sLastSeekerIndex = 0

-- keep track of the amount of time since someone was turned into seeker
sLastSeekerTimer = 0
sLastSeekerTimeout = 3 * 60 * 30 -- three minutes

-- keep track of distance moved recently (camping detection)
sLastPos = {}
sLastPos.x = 0
sLastPos.y = 0
sLastPos.z = 0
sDistanceMoved = 0
sDistanceTimer = 0
sDistanceTimeout = 10 * 30

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
        sLastSeekerTimer = 0
        return
    end

    -- check to see if the round should end
    if gGlobalSyncTable.roundEnded == 0 then
        if not hasHider or not hasSeeker or sLastSeekerTimer > sLastSeekerTimeout then
            if not hasHider then
                gGlobalSyncTable.roundEnded = ROUND_END_SEEKER_WIN
            elseif sLastSeekerTimer > sLastSeekerTimeout then
                gGlobalSyncTable.roundEnded = ROUND_END_HIDER_WIN
            else
                gGlobalSyncTable.roundEnded = ROUND_END_UNKNOWN
            end
            sRoundEndedTimer = 0
        else
            return
        end
    end

    -- if round was over for 5 seconds
    if sRoundEndedTimer >= sRoundEndedTimeout then
        -- reset seekers
        for i=0,(MAX_PLAYERS-1) do
            gPlayerSyncTable[i].seeking = false
        end
        hasSeeker = false

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
        gGlobalSyncTable.roundEnded = 0
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
    if sDistanceMoved > 25 then
        sDistanceTimer = 0
    end

    -- inform the player that they need to move, or make them a seeker
    if sDistanceTimer > sDistanceTimeout then
        s.seeking = true
    end

    -- make sound
    if sDistanceTimer > 0 and sDistanceTimer % 30 == 1 then
        play_sound(SOUND_MENU_CAMERA_BUZZ, m.marioObj.header.gfx.cameraToObject)
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
    if gGlobalSyncTable.roundEnded == 0 then
        camping_detection(gMarioStates[0])
    else
        sDistanceTimer = 0
    end

    -- update sLastSeekerTimer and sRoundEndedTimer
    if gGlobalSyncTable.roundEnded == 0 then
        sLastSeekerTimer = sLastSeekerTimer + 1
    else
        sRoundEndedTimer = sRoundEndedTimer + 1
    end
    sDisplayCenterTimer = sDisplayCenterTimer + 1
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
    -- prevent physics from being altered when bubbled
    if m.action == ACT_BUBBLED then
        return
    end

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

function hud_top_render()
    -- check gamemode enabled state
    if not gGlobalSyncTable.hideAndSeek then
        return
    end

    local seconds = 0
    local text = ''

    if network_player_connected_count() < 2 then
        seconds = 60
        text = 'waiting for players'
    elseif gGlobalSyncTable.roundEnded == 0 then
        seconds = math.floor((sLastSeekerTimeout - sLastSeekerTimer) / 30)
        text = 'seekers have ' .. seconds .. ' seconds'
    else
        seconds = math.floor((sRoundEndedTimeout - sRoundEndedTimer) / 30)
        text = 'next round in ' .. seconds .. ' seconds'
    end

    if seconds < 0 then seconds = 0 end
    local scale = 0.50

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()
    local width = djui_hud_measure_text(text) * scale

    local x = (screenWidth - width) / 2.0
    local y = 0

    local background = 0.0
    if seconds < 60 and gGlobalSyncTable.roundEnded == 0 then
        background = (math.sin(sFlashingIndex / 10.0) * 0.5 + 0.5) * 1.0
        background = background * background
        background = background * background
    end

    -- render top
    djui_hud_set_color(255 * background, 0, 0, 128);
    djui_hud_render_rect(x - 6, y, width + 12, 16);

    djui_hud_set_color(255, 255, 255, 255);
    djui_hud_print_text(text, x, y, scale);
end

function hud_bottom_render()
    local seconds = math.floor((sDistanceTimeout - sDistanceTimer) / 30)
    if seconds < 0 then seconds = 0 end
    if sDistanceTimer < 1 then return end

    local text = 'Keep moving! (' .. seconds .. ')'
    local scale = 0.50

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()
    local screenHeight = djui_hud_get_screen_height()
    local width = djui_hud_measure_text(text) * scale

    local x = (screenWidth - width) / 2.0
    local y = screenHeight - 16

    local background = (math.sin(sFlashingIndex / 10.0) * 0.5 + 0.5) * 1.0
    background = background * background
    background = background * background

    -- render top
    djui_hud_set_color(255 * background, 0, 0, 128);
    djui_hud_render_rect(x - 6, y, width + 12, 16);

    djui_hud_set_color(255, 255, 255, 255);
    djui_hud_print_text(text, x, y, scale);
end

function hud_center_render()
    if sDisplayCenterTimer > 30 * 5 then return end

    -- set text
    local text = ''
    if gGlobalSyncTable.roundEnded == ROUND_END_SEEKER_WIN then
        text = 'Seekers Win!'
    elseif gGlobalSyncTable.roundEnded == ROUND_END_HIDER_WIN then
        text = 'Hiders Win!'
    elseif gGlobalSyncTable.roundEnded == 0 then
        text = 'Go!'
    else
        return
    end

    -- set scale
    local scale = 1 - (sRoundEndedTimer / 30) + 4
    if scale < 0 then scale = 0 end
    if scale > 1 then scale = 1 end
    scale = scale * scale
    scale = scale * scale
    scale = scale * scale

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()
    local screenHeight = djui_hud_get_screen_height()
    local width = djui_hud_measure_text(text) * scale
    local height = 32 * scale

    local x = (screenWidth - width) / 2.0
    local y = (screenHeight - height) / 2.0

    -- render
    djui_hud_set_color(0, 0, 0, 128);
    djui_hud_render_rect(x - 6 * scale, y, width + 12 * scale, height);

    djui_hud_set_color(255, 255, 255, 255);
    djui_hud_print_text(text, x, y, scale);
end

function on_hud_render()
    -- render to N64 screen space, with the HUD font
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)

    hud_top_render()
    hud_bottom_render()
    hud_center_render()

    sFlashingIndex = sFlashingIndex + 1
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
    play_character_sound(gMarioStates[0], CHAR_SOUND_HERE_WE_GO)
    sDisplayCenterTimer = 0
end

function on_round_ended_changed(tag, oldVal, newVal)
    if oldVal == 0 and newVal ~= 0 then
        sLastSeekerTimer = 0
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gMarioStates[0].marioObj.header.gfx.cameraToObject)
        sDisplayCenterTimer = 0
    elseif newVal == 0 and oldVal ~= 0 then
        sLastSeekerTimer = 0
    end

    sRoundEndedTimer = 0
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
        sLastSeekerTimer = 0
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
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)

hook_chat_command('hide-and-seek', "[on|off] turn hide-and-seek on or off", on_hide_and_seek_command)

-- call functions when certain sync table values change
hook_on_sync_table_change(gGlobalSyncTable, 'roundNumber', 0, on_round_number_changed)
hook_on_sync_table_change(gGlobalSyncTable, 'roundEnded', 0, on_round_ended_changed)
for i=0,(MAX_PLAYERS-1) do
    gPlayerSyncTable[i].seeking = true
    hook_on_sync_table_change(gPlayerSyncTable[i], 'seeking', i, on_seeking_changed)
end
