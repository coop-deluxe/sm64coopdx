-- name: Nametags
-- incompatible: nametags
-- description: Nametags\nBy \\#ec7731\\Agent X\\#ffffff\\\n\nThis mod adds nametags to sm64ex-coop, this helps to easily identify other players without the player list, nametags can toggled with \\#ffff00\\/nametags [on|off]\\#ffffff\\

MAX_SCALE = 0.32

gGlobalSyncTable.nametags = true
gGlobalSyncTable.dist = 7000

for k, v in pairs(gActiveMods) do
    local name = v.name:lower()
    if v.enabled and (name:find("hide") or name:find("hns") or name:find("hunt")) then
        gGlobalSyncTable.nametags = false
    end
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

function djui_hud_print_outlined_text(text, x, y, scale, r, g, b, outlineDarkness)
    -- render outline
    djui_hud_set_adjusted_color(r * outlineDarkness, g * outlineDarkness, b * outlineDarkness, 255)
    djui_hud_print_text(text, x - (1*(scale*2)), y, scale)
    djui_hud_print_text(text, x + (1*(scale*2)), y, scale)
    djui_hud_print_text(text, x, y - (1*(scale*2)), scale)
    djui_hud_print_text(text, x, y + (1*(scale*2)), scale)
    -- render text
    djui_hud_set_adjusted_color(r, g, b, 255)
    djui_hud_print_text(text, x, y, scale)
    djui_hud_set_color(255, 255, 255, 255)
end

function name_and_hex(name)
    local nameTable = {}
    name:gsub(".", function(c) table.insert(nameTable, c) end)

    local removed = false
    local color = "000000"
    for k, v in pairs(nameTable) do
        if v == "\\" and not removed then
            removed = true
            nameTable[k] = ""     -- \
            nameTable[k + 1] = "" -- #
            if nameTable[k + 2] ~= nil and nameTable[k + 3] ~= nil and nameTable[k + 4] ~= nil and nameTable[k + 5] ~= nil and nameTable[k + 6] ~= nil and nameTable[k + 7] ~= nil then
                color = nameTable[k + 2] .. nameTable[k + 3] .. nameTable[k + 4] .. nameTable[k + 5] .. nameTable[k + 6] .. nameTable[k + 7]
            end
            nameTable[k + 2] = "" -- f
            nameTable[k + 3] = "" -- f
            nameTable[k + 4] = "" -- f
            nameTable[k + 5] = "" -- f
            nameTable[k + 6] = "" -- f
            nameTable[k + 7] = "" -- f
            nameTable[k + 8] = "" -- \
        end
    end
    return { name = table.concat(nameTable, ""), color = color }
end

function hex_to_rgb(hex)
    local hexTable = {}
    hex:gsub("..", function(c) table.insert(hexTable, c) end)
    return { r = tonumber(hexTable[1], 16), g = tonumber(hexTable[2], 16), b = tonumber(hexTable[3], 16) }
end

showSelfTag = false
function on_hud_render()
    if not gGlobalSyncTable.nametags or not gNetworkPlayers[0].currAreaSyncValid or obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then return end

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)

    for i = if_then_else(showSelfTag, 0, 1), network_player_connected_count() - 1 do
        local m = gMarioStates[i]
        if active_player(m) ~= 0 then
            if m.playerIndex == 0 and (m.input & INPUT_FIRST_PERSON) ~= 0 then return end
            local out = { x = 0, y = 0, z = 0 }
            local pos = { x = m.marioObj.header.gfx.pos.x, y = m.marioBodyState.headPos.y + 120, z = m.marioObj.header.gfx.pos.z }
            djui_hud_world_pos_to_screen_pos(pos, out)

            local scale = MAX_SCALE
            if m.playerIndex ~= 0 and vec3f_dist(gMarioStates[0].pos, m.pos) > 1000 then
                scale = 0.5
                scale = scale + vec3f_dist(gMarioStates[0].pos, m.pos) / gGlobalSyncTable.dist
                scale = clamp(1 - scale, 0, MAX_SCALE)
            end
            local info = name_and_hex(gNetworkPlayers[i].name)
            local color = { r = 162, g = 202, b = 234 }
            network_player_palette_to_color(gNetworkPlayers[i], SHIRT, color)
            local measure = djui_hud_measure_text(info.name) * scale * 0.5
            djui_hud_print_outlined_text(info.name, out.x - measure, out.y, scale, color.r, color.g, color.b, 0.25)
        end
    end
end

function on_nametags_command(msg)
    if msg == "on" then
        gGlobalSyncTable.nametags = true
        djui_chat_message_create("Nametag status: \\#00ff00\\ON")
    else
        gGlobalSyncTable.nametags = false
        djui_chat_message_create("Nametag status: \\#ff0000\\OFF")
    end
    return true
end

function on_nametag_distance_command(msg)
    if tonumber(msg) ~= nil then
        djui_chat_message_create("Set distance to " .. msg)
        gGlobalSyncTable.dist = tonumber(msg)
    else
        djui_chat_message_create("\\#ff0000\\Failed to set distance to " .. msg)
    end
    return true
end

function on_show_my_tag_command(msg)
    if msg == "on" then
        showSelfTag = true
        djui_chat_message_create("Show my tag status: \\#00ff00\\ON")
    else
        showSelfTag = false
        djui_chat_message_create("Show my tag status: \\#ff0000\\OFF")
    end
    return true
end

hook_event(HOOK_ON_HUD_RENDER, on_hud_render)

if network_is_server() then
    hook_chat_command("nametags", "[on|off] to turn nametags on or off, default is \\#00ff00\\ON", on_nametags_command)
    hook_chat_command("nametag-distance", "[number] set the distance at which nametags disappear, default is 7000", on_nametag_distance_command)
end

hook_chat_command("show-my-tag", "[on|off] to turn your own nametag on or off, default is \\#ff0000\\OFF", on_show_my_tag_command)
