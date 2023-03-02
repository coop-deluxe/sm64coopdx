-- name: Nametags
-- incompatible: nametags
-- description: Nametags\nBy \\#ec7731\\Agent X\\#dcdcdc\\\n\nThis mod adds nametags to sm64ex-coop, this helps to easily identify other players without the player list, nametags can toggled on and off with \\#ffff00\\/nametag-distance 7000\\#dcdcdc\\ and \\#ffff00\\/nametag-distance 0\\#dcdcdc\\ respectively.

MAX_SCALE = 0.32

gGlobalSyncTable.dist = 7000
gGlobalSyncTable.health = true

showSelfTag = false

for k, v in pairs(gActiveMods) do
    local name = v.name:lower()
    if v.enabled and (name:find("hide") or name:find("hns") or name:find("hunt")) then
        gGlobalSyncTable.dist = 0
    end
end

function on_or_off(value)
    if value then return "\\#00ff00\\ON" end
    return "\\#ff0000\\OFF"
end

function clamp(x, a, b)
    if x < a then return a end
    if x > b then return b end
    return x
end

--- @param m MarioState
function active_player(m)
    local np = gNetworkPlayers[m.playerIndex]
    if m.playerIndex == 0 then
        return 1
    end
    if not np.connected then
        return 0
    end
    if np.currCourseNum ~= gNetworkPlayers[0].currCourseNum then
        return 0
    end
    if np.currActNum ~= gNetworkPlayers[0].currActNum then
        return 0
    end
    if np.currLevelNum ~= gNetworkPlayers[0].currLevelNum then
        return 0
    end
    if np.currAreaIndex ~= gNetworkPlayers[0].currAreaIndex then
        return 0
    end
    return is_player_active(m)
end

function if_then_else(cond, if_true, if_false)
    if cond then return if_true end
    return if_false
end

function djui_hud_set_adjusted_color(r, g, b, a)
    local multiplier = 1
    if is_game_paused() then multiplier = 0.5 end
    djui_hud_set_color(r * multiplier, g * multiplier, b * multiplier, a)
end

function djui_hud_print_outlined_text(text, x, y, scale, r, g, b, a, outlineDarkness)
    -- render outline
    djui_hud_set_adjusted_color(r * outlineDarkness, g * outlineDarkness, b * outlineDarkness, a)
    djui_hud_print_text(text, x - (1*(scale*2)), y, scale)
    djui_hud_print_text(text, x + (1*(scale*2)), y, scale)
    djui_hud_print_text(text, x, y - (1*(scale*2)), scale)
    djui_hud_print_text(text, x, y + (1*(scale*2)), scale)
    -- render text
    djui_hud_set_adjusted_color(r, g, b, 255)
    djui_hud_print_text(text, x, y, scale)
    djui_hud_set_color(255, 255, 255, 255)
end

function name_without_hex(name)
    local s = ''
    local inSlash = false
    for i = 1, #name do
        local c = name:sub(i,i)
        if c == '\\' then
            inSlash = not inSlash
        elseif not inSlash then
            s = s .. c
        end
    end
    return s
end

function on_hud_render()
    if gGlobalSyncTable.dist == 0 or not gNetworkPlayers[0].currAreaSyncValid or obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then return end

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)

    for i = if_then_else(showSelfTag, 0, 1), (MAX_PLAYERS - 1) do
        local m = gMarioStates[i]
        if active_player(m) ~= 0 and m.action ~= ACT_IN_CANNON and (m.playerIndex ~= 0 or (m.playerIndex == 0 and m.action ~= ACT_FIRST_PERSON)) then
            local out = { x = 0, y = 0, z = 0 }
            local pos = { x = m.marioObj.header.gfx.pos.x, y = m.pos.y + 210, z = m.marioObj.header.gfx.pos.z }
            djui_hud_world_pos_to_screen_pos(pos, out)

            local scale = MAX_SCALE
            if m.playerIndex ~= 0 and vec3f_dist(gMarioStates[0].pos, m.pos) > 1000 then
                scale = 0.5
                scale = scale + vec3f_dist(gMarioStates[0].pos, m.pos) / gGlobalSyncTable.dist
                scale = clamp(1 - scale, 0, MAX_SCALE)
            end
            local name = name_without_hex(gNetworkPlayers[i].name)
            local color = { r = 162, g = 202, b = 234 }
            network_player_palette_to_color(gNetworkPlayers[i], SHIRT, color)
            local measure = djui_hud_measure_text(name) * scale * 0.5
            local alpha = if_then_else(m.action ~= ACT_CROUCHING and m.action ~= ACT_START_CRAWLING and m.action ~= ACT_CRAWLING and m.action ~= ACT_STOP_CRAWLING, 255, 100)
            djui_hud_print_outlined_text(name, out.x - measure, out.y, scale, color.r, color.g, color.b, alpha, 0.25)

            if m.playerIndex ~= 0 and gGlobalSyncTable.health then
                djui_hud_set_adjusted_color(255, 255, 255, alpha)
                local healthScale = 75 * scale
                hud_render_power_meter(m.health, out.x - (healthScale * 0.5), out.y - healthScale, healthScale, healthScale)
            end
        end
    end
end

function on_nametag_distance_command(msg)
    local dist = tonumber(msg)
    if dist ~= nil then
        djui_chat_message_create("Set nametag distance to " .. msg)
        gGlobalSyncTable.dist = dist
        return true
    end
    return false
end

function on_show_health_command()
    gGlobalSyncTable.health = not gGlobalSyncTable.health
    djui_chat_message_create("Show health status: " .. on_or_off(gGlobalSyncTable.health))
    return true
end

function on_show_tag_command()
    showSelfTag = not showSelfTag
    djui_chat_message_create("Show my tag status: " .. on_or_off(showSelfTag))
    return true
end

hook_event(HOOK_ON_HUD_RENDER, on_hud_render)

if network_is_server() then
    hook_chat_command("nametag-distance", "[number] set the distance at which nametags disappear, default is 7000, 0 turns nametags off", on_nametag_distance_command)
    hook_chat_command("show-health", "to toggle showing health above the nametag, default is \\#00ff00\\ON", on_show_health_command)
end

hook_chat_command("show-tag", "to toggle your own nametag on or off, default is \\#ff0000\\OFF", on_show_tag_command)