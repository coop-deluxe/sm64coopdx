--
-- Custom object and Mario update
-- Don't mind this file, it's not relevant to the purpose of this demo.
--

shape_toggle = false

local E_MODEL_SHAPE = smlua_model_util_get_id("shape_geo")

local function bhv_shape_init(o)
    o.oFlags = o.oFlags | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oAnimState = 0
end

local function bhv_shape_loop(o)
    local m = gMarioStates[0]
    o.oPosX = m.pos.x + 160 * sins(o.oMoveAngleYaw + o.oAction * 0x5555)
    o.oPosY = m.pos.y + 80
    o.oPosZ = m.pos.z + 160 * coss(o.oMoveAngleYaw + o.oAction * 0x5555)
    o.oFaceAngleYaw = o.oFaceAngleYaw - 0x100
    o.oMoveAngleYaw = o.oMoveAngleYaw + 0x100
    if o.oTimer % 2 == 0 then
        o.oAnimState = (o.oAnimState + 1) % 11
    end
end

local id_bhvShape = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_shape_init, bhv_shape_loop, "bhvShape")

local function mario_update(m)
    if m.playerIndex == 0 then
        if m.controller.buttonPressed & X_BUTTON ~= 0 then
            shape_toggle = not shape_toggle
            if shape_toggle then
                for i = 1, 3 do
                    local obj = spawn_non_sync_object(id_bhvShape, E_MODEL_SHAPE, 0, 0, 0, nil)
                    if obj then obj.oAction = i end
                end
            else
                local obj = obj_get_first_with_behavior_id(id_bhvShape)
                while obj ~= nil do
                    obj_mark_for_deletion(obj)
                    obj = obj_get_next_with_same_behavior_id(obj)
                end
            end
        end
    end
end

local function on_level_init()
    shape_toggle = false
    gfx_delete_all()
    vtx_delete_all()
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
