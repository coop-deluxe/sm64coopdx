-- name: Lighting Engine Demo
-- description: Lighting Engine Demo\nBy \\#ec7731\\Agent X\n\n\\#dcdcdc\\Open the panel in the pause menu to see what you can do.

local flashlightColor = { 255, 255, 200 }

--- @param node GraphNode
function geo_hide_if_dnc(node)
    local dl = cast_graph_node(node.next)
    gfx_parse(dl.displayList, function(cmd, op)
        if op == G_SETENVCOLOR then
            gfx_set_command(cmd, "gsDPSetEnvColor", 255, 255, 255, if_then_else(_G.dayNightCycleApi ~= nil and _G.dayNightCycleApi.is_dnc_enabled(), 0, 255))
        end
    end)
end

--- @param o Object
local function bhv_spawn_point_light(o)
    local light = spawn_non_sync_object(
        id_bhvPointLight,
        E_MODEL_NONE,
        o.oPosX, o.oPosY, o.oPosZ,
        nil
    )
    if get_id_from_behavior(o.behavior) == id_bhvKoopaShell then
        light.oBehParams = 0x00FF0032
    else
        light.oBehParams = 0xFFFFFF32
    end
    light.parentObj = o
end

--- @param o Object
function bhv_flashlight_loop(o)
    local pos = gMarioStates[0].pos
    local yaw = gFirstPersonCamera.yaw + 0x8000
    o.oPosX = pos.x + sins(yaw) * 300
    o.oPosY = pos.y + -gFirstPersonCamera.pitch * 0.06
    o.oPosZ = pos.z + coss(yaw) * 300
    le_set_light_pos(o.oLightID, o.oPosX, o.oPosY, o.oPosZ)
    le_set_light_color(o.oLightID, flashlightColor[1], flashlightColor[2], flashlightColor[3])
end

local function spawn_flashlight()
    local flashlight = spawn_non_sync_object(
        bhvFlashlight,
        E_MODEL_NONE,
        0, 0, 0,
        nil
    )
    flashlight.oBehParams = (flashlightColor[1] << 24) | (flashlightColor[2] << 16) | (flashlightColor[3] << 8) | (90)
    return flashlight
end

--- @param flashlight Object
local function delete_flashlight(flashlight)
    le_remove_light(flashlight.oLightID)
    obj_mark_for_deletion(flashlight)
    return nil
end

--- @param m MarioState
local function calculate_mario_lighting(m)
    local color = { r = 0, g = 0, b = 0 }
    local dir = { x = 0, y = 0, z = 0 }

    le_calculate_lighting_color(m.pos, color, 0.25)
    le_calculate_lighting_dir(m.pos, dir)

    m.marioBodyState.lightR = color.r
    m.marioBodyState.lightG = color.g
    m.marioBodyState.lightB = color.b
    m.marioBodyState.shadeR = m.marioBodyState.lightR * 0.5
    m.marioBodyState.shadeG = m.marioBodyState.lightG * 0.5
    m.marioBodyState.shadeB = m.marioBodyState.lightB * 0.5

    m.marioBodyState.lightingDirX = -DEFAULT_LIGHTING_DIR + dir.x
    m.marioBodyState.lightingDirY = -DEFAULT_LIGHTING_DIR + dir.y
    m.marioBodyState.lightingDirZ = -DEFAULT_LIGHTING_DIR + dir.z
end

--- @param m MarioState
local function mario_update(m)
    if m.playerIndex ~= 0 then return end

    calculate_mario_lighting(m)

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


local function on_set_flashlight_color(index, value)
    flashlightColor[index + 1] = value
end

id_bhvKoopaShell = hook_behavior(id_bhvKoopaShell, OBJ_LIST_LEVEL, false, bhv_spawn_point_light, nil, "bhvKoopaShell")

hook_event(HOOK_MARIO_UPDATE, mario_update)

hook_mod_menu_slider("Flashlight Red", flashlightColor[1], 0, 255, on_set_flashlight_color)
hook_mod_menu_slider("Flashlight Green", flashlightColor[2], 0, 255, on_set_flashlight_color)
hook_mod_menu_slider("Flashlight Blue", flashlightColor[3], 0, 255, on_set_flashlight_color)
hook_mod_menu_button("Warp to Black Mesa", function() warp_to_level(LEVEL_HL, 1, 0) end)
hook_mod_menu_button("Warp to Sunset Canals", function() warp_to_level(LEVEL_CANALS, 1, 0) end)