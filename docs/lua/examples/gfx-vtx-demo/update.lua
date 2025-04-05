--
-- Custom object and Mario update
-- Don't mind this file, it's not relevant to the purpose of this demo.
--

current_shape = 0

local E_MODEL_SHAPE = smlua_model_util_get_id("shape_geo")

local function bhv_shape_init(o)
    o.oFlags = o.oFlags | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oAnimState = 0
end

local function bhv_shape_loop(o)
    o.oFaceAngleYaw = o.oFaceAngleYaw - 0x100
    if o.oTimer % 2 == 0 then
        o.oAnimState = (o.oAnimState + 1) % 11
    end
end

local id_bhvShape = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_shape_init, bhv_shape_loop, "bhvShape")

local function mario_update(m)
    if m.playerIndex == 0 then
        if m.controller.buttonPressed & X_BUTTON ~= 0 then
            local obj = obj_get_first_with_behavior_id(id_bhvShape)
            if obj == nil then
                obj = spawn_non_sync_object(id_bhvShape, E_MODEL_SHAPE, 0, 0, 0, nil)
            end
            obj.oPosX = m.pos.x + 200 * sins(m.faceAngle.y)
            obj.oPosY = m.pos.y + 150
            obj.oPosZ = m.pos.z + 200 * coss(m.faceAngle.y)
        elseif m.controller.buttonPressed & Y_BUTTON ~= 0 then
            current_shape = (current_shape + 1) % #SHAPES
        end
    end
end

local function on_hud_render()
    djui_hud_set_resolution(RESOLUTION_DJUI)
    djui_hud_set_font(FONT_MENU)
    djui_hud_set_color(0xFF, 0xFF, 0x00, 0xFF)
    djui_hud_print_text(SHAPES[current_shape + 1].name, 8, djui_hud_get_screen_height() - 64, 1)
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
