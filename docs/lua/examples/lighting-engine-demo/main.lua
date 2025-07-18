-- name: Lighting Engine Demo
-- description: Lighting Engine Demo\nBy \\#ec7731\\Agent X\n\n\\#dcdcdc\\Open the mod menu in the pause menu to see what you can do.

flashlightColor = { 255, 255, 200 }

--- @param cmd Gfx
--- @param op integer
local function parse_dl(cmd, op)
    if op == G_SETENVCOLOR then
        gfx_set_command(cmd, "gsDPSetEnvColor(255, 255, 255, %i)", if_then_else(_G.dayNightCycleApi ~= nil and _G.dayNightCycleApi.is_dnc_enabled(), 0, 255))
    end
end

--- @param node GraphNode
function geo_hide_if_dnc(node)
    local dl = cast_graph_node(node.next)
    gfx_parse(dl.displayList, parse_dl)
end

local function update()
    shading_update()

    --- @type MarioState
    local m = gMarioStates[0]

    if (m.controller.buttonPressed & L_JPAD) ~= 0 then
        audio_sample_play(SOUND_CUSTOM_FLASHLIGHT, m.pos, 1.0)
        local flashlight = obj_get_first_with_behavior_id(bhvFlashlight)
        if flashlight ~= nil then
            delete_flashlight(flashlight)
        else
            spawn_flashlight()
        end
    end
end

local function on_level_init()
    local levelNum = gNetworkPlayers[0].currLevelNum
    if levelNum == LEVEL_HL or levelNum == LEVEL_CANALS then return end

    le_set_ambient_color(30, 30, 75)
end


local function on_set_flashlight_color(index, value)
    flashlightColor[index + 1] = value
end

set_override_skybox(BACKGROUND_HAUNTED)
set_fog_color(0, 30)
set_fog_color(1, 30)
set_fog_color(2, 75)

djui_popup_create("Use Left D-Pad to turn on the flashlight.", 2)

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)

hook_mod_menu_slider("Flashlight Red", flashlightColor[1], 0, 255, on_set_flashlight_color)
hook_mod_menu_slider("Flashlight Green", flashlightColor[2], 0, 255, on_set_flashlight_color)
hook_mod_menu_slider("Flashlight Blue", flashlightColor[3], 0, 255, on_set_flashlight_color)
hook_mod_menu_button("Warp to Black Mesa", function() warp_to_level(LEVEL_HL, 1, 0) end)
hook_mod_menu_button("Warp to Sunset Canals", function() warp_to_level(LEVEL_CANALS, 1, 0) end)