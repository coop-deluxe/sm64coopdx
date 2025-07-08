local strange_reflections = false
local inside_mirror_room = false
local mirror_room_rotation = false

local CHARACTERS = {
    [CT_MARIO] = {
        modelId = E_MODEL_MARIO,
        palette = {
            [PANTS] = { r = 0, g = 0, b = 255 },
            [SHIRT] = { r = 255, g = 0, b = 0 },
            [GLOVES] = { r = 255, g = 255, b = 255 },
            [SHOES] = { r = 114, g = 28, b = 14 },
            [HAIR] = { r = 115, g = 6, b = 0 },
            [SKIN] = { r = 254, g = 193, b = 121 },
            [CAP] = { r = 255, g = 0, b = 0 },
            [EMBLEM] = { r = 255, g = 0, b = 0 },
        },
    },
    [CT_LUIGI] = {
        modelId = E_MODEL_LUIGI,
        palette = {
            [PANTS] = { r = 0, g = 0, b = 255 },
            [SHIRT] = { r = 0, g = 255, b = 0 },
            [GLOVES] = { r = 255, g = 255, b = 255 },
            [SHOES] = { r = 114, g = 28, b = 14 },
            [HAIR] = { r = 115, g = 6, b = 0 },
            [SKIN] = { r = 254, g = 193, b = 121 },
            [CAP] = { r = 0, g = 255, b = 0 },
            [EMBLEM] = { r = 0, g = 255, b = 0 },
        },
    },
    [CT_WARIO] = {
        modelId = E_MODEL_WARIO,
        palette = {
            [PANTS] = { r = 127, g = 32, b = 122 },
            [SHIRT] = { r = 255, g = 189, b = 0 },
            [GLOVES] = { r = 255, g = 255, b = 255 },
            [SHOES] = { r = 14, g = 114, b = 28 },
            [HAIR] = { r = 115, g = 83, b = 0 },
            [SKIN] = { r = 254, g = 193, b = 121 },
            [CAP] = { r = 255, g = 189, b = 0 },
            [EMBLEM] = { r = 0, g = 0, b = 255 },
        },
    },
    [CT_WALUIGI] = {
        modelId = E_MODEL_WALUIGI,
        palette = {
            [PANTS] = { r = 22, g = 22, b = 39 },
            [SHIRT] = { r = 97, g = 38, b = 176 },
            [GLOVES] = { r = 255, g = 255, b = 255 },
            [SHOES] = { r = 254, g = 118, b = 0 },
            [HAIR] = { r = 115, g = 83, b = 0 },
            [SKIN] = { r = 254, g = 193, b = 121 },
            [CAP] = { r = 97, g = 38, b = 176 },
            [EMBLEM] = { r = 255, g = 222, b = 0 },
        },
    },
    [CT_TOAD] = {
        modelId = E_MODEL_TOAD_PLAYER,
        palette = {
            [PANTS] = { r = 255, g = 255, b = 255 },
            [SHIRT] = { r = 76, g = 44, b = 211 },
            [GLOVES] = { r = 255, g = 255, b = 255 },
            [SHOES] = { r = 104, g = 64, b = 27 },
            [HAIR] = { r = 115, g = 6, b = 0 },
            [SKIN] = { r = 254, g = 213, b = 161 },
            [CAP] = { r = 255, g = 0, b = 0 },
            [EMBLEM] = { r = 255, g = 0, b = 0 },
        },
    },
    [CT_MAX] = {
        modelId = E_MODEL_TOAD_PLAYER,
        palette = {
            [PANTS] = { r = 255, g = 128, b = 208 },
            [SHIRT] = { r = 255, g = 32, b = 64 },
            [GLOVES] = { r = 255, g = 128, b = 208 },
            [SHOES] = { r = 104, g = 64, b = 27 },
            [HAIR] = { r = 255, g = 128, b = 208 },
            [SKIN] = { r = 254, g = 213, b = 161 },
            [CAP] = { r = 255, g = 255, b = 255 },
            [EMBLEM] = { r = 255, g = 255, b = 255 }
        },
    },
}

local CHARACTER_PAIRS = {
    [CT_MARIO] = CT_LUIGI,
    [CT_LUIGI] = CT_MARIO,
    [CT_WARIO] = CT_WALUIGI,
    [CT_WALUIGI] = CT_WARIO,
    [CT_TOAD] = CT_MAX,
    [CT_MAX] = CT_TOAD,
}

hook_event(HOOK_MARIO_UPDATE, function (m)
    local np = gNetworkPlayers[m.playerIndex]
    network_player_reset_override_palette(np)
    m.marioObj.hookRender = 1

    if m.playerIndex ~= 0 then return end

    inside_mirror_room = (
        np.currLevelNum == LEVEL_CASTLE and
        np.currAreaIndex == 2 and
        m.pos.x >= 1730
    )

    local mirror = obj_get_first_with_behavior_id(id_bhvMirror)
    if mirror then
        if inside_mirror_room and mirror_room_rotation then
            mirror.oFaceAngleYaw = mirror.oFaceAngleYaw + 0x80
        else
            mirror.oFaceAngleYaw = 0xC000
        end
    end

    local bigBoo = obj_get_first_with_behavior_id(id_bhvBalconyBigBoo)
    if inside_mirror_room and strange_reflections then
        if not bigBoo then
            bigBoo = spawn_non_sync_object(id_bhvBalconyBigBoo, E_MODEL_BOO, 3500, 1408, 1825, nil)
        end
        obj_set_pos(bigBoo, 3500, 1408, 1825)
        bigBoo.header.gfx.node.flags = bigBoo.header.gfx.node.flags | GRAPH_RENDER_INVISIBLE
        bigBoo.hookRender = 1
    else
        obj_mark_for_deletion(bigBoo)
    end
end)

local function before_geo_process(node, matStackIndex)
    if inside_mirror_room and strange_reflections then

        -- Set the character palette
        local m = geo_get_mario_state()
        local np = gNetworkPlayers[m.playerIndex]
        local palette = CHARACTERS[m.character.type].palette
        network_player_set_override_palette_color(np, PANTS, palette[PANTS])
        network_player_set_override_palette_color(np, SHIRT, palette[SHIRT])
        network_player_set_override_palette_color(np, GLOVES, palette[GLOVES])
        network_player_set_override_palette_color(np, SHOES, palette[SHOES])
        network_player_set_override_palette_color(np, HAIR, palette[HAIR])
        network_player_set_override_palette_color(np, SKIN, palette[SKIN])
        network_player_set_override_palette_color(np, CAP, palette[CAP])
        network_player_set_override_palette_color(np, EMBLEM, palette[EMBLEM])
    end
end

local function on_mirror_object_render(mirrorObj)
    if inside_mirror_room and strange_reflections then
        local realObj = mirrorObj.oMirrorObjRealObj

        if obj_has_behavior_id(realObj, id_bhvBalconyBigBoo) == 1 then
            mirrorObj.header.gfx.node.flags = mirrorObj.header.gfx.node.flags & ~GRAPH_RENDER_INVISIBLE
        end

        if obj_has_behavior_id(realObj, id_bhvMario) == 1 then
            local m = geo_get_mario_state()
            local realCharacter = CHARACTERS[m.character.type]
            local mirrorCharacter = CHARACTERS[CHARACTER_PAIRS[m.character.type]]

            -- Set the models
            obj_set_model_extended(realObj, realCharacter.modelId)
            obj_set_model_extended(mirrorObj, mirrorCharacter.modelId)

            -- Mirror objects are rendered before the real object, so set the other palette now
            local np = gNetworkPlayers[m.playerIndex]
            local palette = mirrorCharacter.palette
            network_player_set_override_palette_color(np, PANTS, palette[PANTS])
            network_player_set_override_palette_color(np, SHIRT, palette[SHIRT])
            network_player_set_override_palette_color(np, GLOVES, palette[GLOVES])
            network_player_set_override_palette_color(np, SHOES, palette[SHOES])
            network_player_set_override_palette_color(np, HAIR, palette[HAIR])
            network_player_set_override_palette_color(np, SKIN, palette[SKIN])
            network_player_set_override_palette_color(np, CAP, palette[CAP])
            network_player_set_override_palette_color(np, EMBLEM, palette[EMBLEM])

            -- Hook the character's graph node to change the palette before rendering their model
            realObj.header.gfx.sharedChild.hookProcess = 1
        end
    end
end

hook_event(HOOK_BEFORE_GEO_PROCESS, before_geo_process)
hook_event(HOOK_ON_MIRROR_OBJECT_RENDER, on_mirror_object_render)

hook_mod_menu_checkbox("Mirror room rotation", false, function (index, value)
    mirror_room_rotation = value
end)

hook_mod_menu_checkbox("Strange reflections", false, function (index, value)
    strange_reflections = value
end)
