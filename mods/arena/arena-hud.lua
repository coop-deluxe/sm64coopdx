gHudIcons = {
    flags = {
        [0] = { tex = TEX_FLAG, prevX = 0, prevY = 0, r = 255, g = 255, b = 255 },
        [1] = { tex = TEX_FLAG, prevX = 0, prevY = 0, r = 255, g = 120, b = 120 },
        [2] = { tex = TEX_FLAG, prevX = 0, prevY = 0, r = 120, g = 120, b = 255 },
    },
    koth = { tex = TEX_KOTH, prevX = 0, prevY = 0, r = 255, g = 255, b = 255 },
}

function rank_str(rank)
    if rank == 1 then
        return '1st'
    elseif rank == 2 then
        return '2nd'
    elseif rank == 3 then
        return '3rd'
    else
        return tostring(rank) .. 'th'
    end
end

function rank_color_g(rank)
    return clamp(255 - 255 * (rank / 8), 0, 255)
end

function update_ranking_descriptions()
    for i = 0, (MAX_PLAYERS - 1) do
        local s  = gPlayerSyncTable[i]
        local np = gNetworkPlayers[i]
        local m  = gMarioStates[i]
        if active_player(m) then
            if s.rank > 0 then
                local score = s.kills
                if gGameModes[gGlobalSyncTable.gameMode].useScore then
                    score = s.score
                end
                local description = string.format('%s %d', rank_str(s.rank), score)
                local r = 255
                local g = rank_color_g(i)
                local b = 0
                network_player_set_description(np, description, r, g, b, 255)
            else
                network_player_set_description(np, ' ', 255, 255, 255, 255)
            end
        end
    end
end

function render_game_mode()
    local m  = gMarioStates[0]
    local np = gNetworkPlayers[0]
    local s  = gPlayerSyncTable[0]

    if s.rank <= 0 then
        return
    end

    local scoreCap = gGameModes[gGlobalSyncTable.gameMode].scoreCap

    local txt = string.format("%s", gGameModes[gGlobalSyncTable.gameMode].name)
    if gGlobalSyncTable.gameMode == GAME_MODE_DM then
        txt = string.format("%s | First to %d kills", gGameModes[gGlobalSyncTable.gameMode].name, scoreCap)
    elseif gGlobalSyncTable.gameMode == GAME_MODE_TDM then
        txt = string.format("%s | First team to %d kills", gGameModes[gGlobalSyncTable.gameMode].name, scoreCap)
    elseif gGlobalSyncTable.gameMode == GAME_MODE_CTF then
        txt = string.format("%s | First team to %d captures", gGameModes[gGlobalSyncTable.gameMode].name, scoreCap)
    elseif gGlobalSyncTable.gameMode == GAME_MODE_FT then
        txt = string.format("%s | First to %d points", gGameModes[gGlobalSyncTable.gameMode].name, scoreCap)
    elseif gGlobalSyncTable.gameMode == GAME_MODE_TFT then
        txt = string.format("%s | First team to %d points", gGameModes[gGlobalSyncTable.gameMode].name, scoreCap)
    elseif gGlobalSyncTable.gameMode == GAME_MODE_KOTH then
        txt = string.format("%s | First to %d points", gGameModes[gGlobalSyncTable.gameMode].name, scoreCap)
    elseif gGlobalSyncTable.gameMode == GAME_MODE_TKOTH then
        txt = string.format("%s | First team to %d points", gGameModes[gGlobalSyncTable.gameMode].name, scoreCap)
    end
    local scale = 0.25
    local width = (djui_hud_measure_text(txt) + 8) * scale
    local height = 4 * scale + 28 * scale
    local x = 4 * scale
    local y = 2 * scale
    djui_hud_set_color(0, 0, 0, 128)
    djui_hud_render_rect(x, y, width, height)

    x = x + 4 * scale
    djui_hud_set_color(0, 0, 0, 255)
    djui_hud_print_text(txt, x + 2 * scale, y + 2 * scale, scale)
    djui_hud_set_color(255, 255, 255, 255)
    djui_hud_print_text(txt, x + 0 * scale, y + 0 * scale, scale)
end

function render_single_team_score(team)
    local txt = string.format("%d", calculate_team_score(team))

    local scale = 0.25
    local width = 64 * scale
    local textWidth = djui_hud_measure_text(txt) * scale
    local height = 4 * scale + 28 * scale
    local x = 4 * scale
    local y = 72 * scale

    if team == 1 then
        djui_hud_set_color(128, 0, 0, 128)
    elseif team == 2 then
        x = x + 72 * scale
        djui_hud_set_color(0, 0, 128, 128)
    end
    djui_hud_render_rect(x, y, width, height)

    x = x + (width - textWidth) / 2
    djui_hud_set_color(0, 0, 0, 255)
    djui_hud_print_text(txt, x + 2 * scale, y + 2 * scale, scale)
    djui_hud_set_color(255, 255, 255, 255)
    djui_hud_print_text(txt, x + 0 * scale, y + 0 * scale, scale)
end

function render_team_score()
    if not gGameModes[gGlobalSyncTable.gameMode].teams then
        return
    end

    render_single_team_score(1)
    render_single_team_score(2)
end

function render_local_rank()
    local m  = gMarioStates[0]
    local np = gNetworkPlayers[0]
    local s  = gPlayerSyncTable[0]

    if s.rank <= 0 then
        return
    end

    local rankTxt = ""
    if gGameModes[gGlobalSyncTable.gameMode].useScore then
        rankTxt = string.format("%s | %d points | %d kills | %d deaths", rank_str(s.rank), s.score, s.kills, s.deaths)
    else
        rankTxt = string.format("%s | %d kills | %d deaths", rank_str(s.rank), s.kills, s.deaths)
    end
    local scale = 0.25
    local width = (djui_hud_measure_text(rankTxt) + 8) * scale
    local height = 4 * scale + 28 * scale

    local x = 4 * scale
    local y = 36 * scale
    djui_hud_set_color(0, 0, 0, 128)
    djui_hud_render_rect(x, y, width, height)

    x = x + 4 * scale
    djui_hud_set_color(0, 0, 0, 255)
    djui_hud_print_text(rankTxt, x + 2 * scale, y + 2 * scale, scale)
    djui_hud_set_color(255, rank_color_g(s.rank), 0, 255)
    djui_hud_print_text(rankTxt, x + 0 * scale, y + 0 * scale, scale)
end

function render_server_message()
    local txt = gGlobalSyncTable.message
    if txt == nil or string.len(txt) <= 1 then
        return
    end

    -- get screen dimensions
    local screenWidth  = djui_hud_get_screen_width()
    local screenHeight = djui_hud_get_screen_height()

    local scale = 1
    local width = (djui_hud_measure_text(txt) + 8) * scale
    local height = 4 * scale + 28 * scale
    local x = (screenWidth - width) / 2
    local y = (screenHeight / 4)

    djui_hud_set_color(0, 0, 0, 128)
    djui_hud_render_rect(x, y, width, height)

    x = x + 4 * scale
    djui_hud_set_color(0, 0, 0, 255)
    djui_hud_print_text(txt, x + 2 * scale, y + 2 * scale, scale)
    djui_hud_set_color(255, 255, 255, 255)
    djui_hud_print_text(txt, x + 0 * scale, y + 0 * scale, scale)
end

function render_health()
    -- get screen dimensions
    local screenWidth  = djui_hud_get_screen_width()
    local screenHeight = djui_hud_get_screen_height()

    local scale = 1
    local width = 128 * scale
    local height = 16 * scale
    local x = math.floor((screenWidth - width) / 2)
    local y = math.floor(screenHeight - height - 4 * scale)

    djui_hud_set_color(0, 0, 0, 128)
    djui_hud_render_rect(x, y, width, height)

    x = x + 2 * scale
    y = y + 2 * scale
    width = width - 4 * scale
    height = height - 4 * scale
    health = mario_health_float(gMarioStates[0])
    width = math.floor(width * health)
    rscale = clamp(((1 - health) ^ 2) * 3, 0, 1)
    gscale = clamp((health ^ 2) * 2, 0, 1)
    djui_hud_set_color(255 * rscale, 255 * gscale, 0, 128)
    djui_hud_render_rect(x, y, width, height)
end

function render_hud_icon(obj, hudIcon)
    local pos = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }
    local out = { x = 0, y = 0, z = 0 }
    djui_hud_world_pos_to_screen_pos(pos, out)

    if out.z > -260 then
        return
    end

    local alpha = clamp(vec3f_dist(pos, gMarioStates[0].pos) / 5000, 0, 1) - 0.2
    if alpha <= 0 then
        return
    end
    alpha = 1 - ((1 - alpha) ^ 3)

    local dX = out.x - 4
    local dY = out.y - 4

    djui_hud_set_color(hudIcon.r, hudIcon.g, hudIcon.b, alpha * 200)
    djui_hud_render_texture_interpolated(hudIcon.tex, hudIcon.prevX, hudIcon.prevY, 0.3, 0.3, dX, dY, 0.3, 0.3)

    hudIcon.prevX = dX
    hudIcon.prevY = dY
end

function on_hud_render()
    -- set resolution and font
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)

    -- do the things
    update_ranking_descriptions()
    render_game_mode()
    render_local_rank()
    render_team_score()
    render_server_message()
    render_health()

    -- render hud icons
    if gGlobalSyncTable.gameMode == GAME_MODE_FT or gGlobalSyncTable.gameMode == GAME_MODE_TFT then
        if gArenaFlagInfo[0] ~= nil and gArenaFlagInfo[0].obj ~= nil then
            render_hud_icon(gArenaFlagInfo[0].obj, gHudIcons.flags[0])
        end
    elseif gGlobalSyncTable.gameMode == GAME_MODE_CTF then
        if gArenaFlagInfo[1] ~= nil and gArenaFlagInfo[1].obj ~= nil then
            render_hud_icon(gArenaFlagInfo[1].obj, gHudIcons.flags[1])
        end
        if gArenaFlagInfo[2] ~= nil and gArenaFlagInfo[2].obj ~= nil then
            render_hud_icon(gArenaFlagInfo[2].obj, gHudIcons.flags[2])
        end
    elseif gGlobalSyncTable.gameMode == GAME_MODE_KOTH or gGlobalSyncTable.gameMode == GAME_MODE_TKOTH then
        if gArenaKothActiveObj ~= nil then
            render_hud_icon(gArenaKothActiveObj, gHudIcons.koth)
        end
    end
end

hud_hide()
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
