
function on_hud_render()
    local s = gPlayerSyncTable[0]
    hud_hide()

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)

    local scale = 0.25
    local width = 0
    local height = 4 * scale

    for i in pairs(gRankings) do
        local np = gNetworkPlayers[gRankings[i].playerIndex]
        local w = (djui_hud_measure_text(tostring(i) .. '. ' .. np.name) + 8) * scale
        if w > width then width = w end
        height = height + 28 * scale
    end

    djui_hud_set_color(0, 0, 0, 128)
    djui_hud_render_rect(0, 0, width, height)

    local x = 4 * scale
    local y = 0
    local rank = 0

    -- draw rankings
    for i in pairs(gRankings) do
        local np = gNetworkPlayers[gRankings[i].playerIndex]
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_print_text(tostring(i) .. '. ' .. np.name, x + 2 * scale, y + 2 * scale, scale)
        if gRankings[i].playerIndex == 0 then
            rank = i
            djui_hud_set_color(255, 240, 150, 255)
        else
            djui_hud_set_color(220, 220, 220, 255)
        end
        djui_hud_print_text(tostring(i) .. '. ' .. np.name, x + 0 * scale, y + 0 * scale, scale)
        y = y + 28 * scale
    end


    if gGlobalSyncTable.gameState == GAME_STATE_RACE_COUNTDOWN then
        -- draw countdown
        scale = 0.6
        djui_hud_set_font(FONT_MENU)
        djui_hud_set_color(64, 128, 255, 255)
        local countdown = math.floor((gGlobalSyncTable.raceStartTime - get_network_area_timer()) / 30)
        countdown = clamp(countdown + 1, 1, 5)

        local countdownText = tostring(countdown)
        x = (djui_hud_get_screen_width() - djui_hud_measure_text(countdownText) * scale) / 2
        djui_hud_print_text(countdownText, x, 2 * scale, scale)
    else
        -- draw lap counter
        scale = 0.3
        djui_hud_set_font(FONT_MENU)
        djui_hud_set_color(64, 128, 255, 255)
        local lapText = 'LAP ' .. tostring(s.lap) .. ' /' .. tostring(gGlobalSyncTable.maxLaps)
        if s.finish ~= nil and s.finish > 0 then lapText = 'FINISHED' end
        x = (djui_hud_get_screen_width() - djui_hud_measure_text(lapText) * scale) / 2
        djui_hud_print_text(lapText, x, 2 * scale, scale)

        -- draw player rank
        if rank > 0 then
            scale = 0.6
            djui_hud_set_color(255, clamp(255 - 255 * (rank / 8), 0, 255), 0, 255)

            local rankText = tostring(rank) .. 'th'
            if rank == 1 then rankText = '1st' end
            if rank == 2 then rankText = '2nd' end
            if rank == 3 then rankText = '3rd' end

            x = (djui_hud_get_screen_width() - djui_hud_measure_text(rankText) * scale) / 2
            y = (djui_hud_get_screen_height() - 80 * scale)
            djui_hud_print_text(rankText, x, y, scale)
        end
    end

    if gGlobalSyncTable.raceQuitTime > 0 then
        -- draw ending countdown
        scale = 0.6
        djui_hud_set_font(FONT_MENU)
        djui_hud_set_color(64, 128, 255, 255)
        local countdown = math.floor((gGlobalSyncTable.raceQuitTime - get_network_area_timer()) / 30)
        countdown = clamp(countdown + 1, 1, 20)

        local countdownText = tostring(countdown)
        x = (djui_hud_get_screen_width() - djui_hud_measure_text(countdownText) * scale) / 2
        y = 40 * scale
        djui_hud_print_text(countdownText, x, y, scale)
    end

end

hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
