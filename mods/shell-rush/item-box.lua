local itemBoxTimeout = 30 * 4 -- 4 seocnds

define_custom_obj_fields({
    oItemBoxTouched = 'u32',
})

function bhv_item_box_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 100
    obj_scale(obj, 1.0)

    obj.oPosY = obj.oPosY + 100
    local floor = cur_obj_update_floor_height_and_get_floor()
    if floor ~= nil then
        obj.oPosY = obj.oFloorHeight + 130
    end

    network_init_object(obj, false, {
        'oItemBoxTouched',
        'oTimer'
    })
end

function bhv_item_box_collect(obj)
    spawn_sparkles(obj)
    spawn_mist(obj)
    obj.oItemBoxTouched = 1
    obj.oTimer = 0
    network_send_object(obj, true)
    select_powerup()
    cur_obj_play_sound_2(SOUND_GENERAL_COLLECT_1UP)
end

function bhv_item_box_loop(obj)
    if obj.oItemBoxTouched == 1 then
        if obj.oTimer >= itemBoxTimeout then
            obj.oItemBoxTouched = 0
            if network_is_server() then
                network_send_object(obj, true)
            end
        elseif obj.oTimer < 5 then
            obj_scale(obj, 1 - (obj.oTimer / 5))
        elseif obj.oTimer >= itemBoxTimeout - 10 then
            obj_scale(obj, (obj.oTimer - (itemBoxTimeout - 10)) / 10)
            cur_obj_unhide()
        else
            cur_obj_hide()
        end
        return
    else
        obj_scale(obj, 1.0)
        cur_obj_unhide()
    end

    obj.oFaceAngleYaw = obj.oFaceAngleYaw + 0x250
    obj.oFaceAngleRoll = 0
    obj.oFaceAnglePitch = 0

    local m = nearest_mario_state_to_object(obj)
    if m == gMarioStates[0] then
        local s = gPlayerSyncTable[0]
        if s.powerup[0] == POWERUP_NONE and s.powerup[1] == POWERUP_NONE and s.powerup[2] == POWERUP_NONE then
            local player = m.marioObj
            local yDist = math.abs(obj.oPosY - player.oPosY)
            local xzDist = math.sqrt(math.pow(obj.oPosX - player.oPosX, 2) + math.pow(obj.oPosZ - player.oPosZ, 2))
            if xzDist < 120 and yDist < 200 then
                bhv_item_box_collect(obj)
            end
        end
    end
end

id_bhvItemBox = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_item_box_init, bhv_item_box_loop)
E_MODEL_ITEM_BOX = smlua_model_util_get_id("item_box_geo")
