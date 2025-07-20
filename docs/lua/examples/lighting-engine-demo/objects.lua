--- @param o Object
local function bhv_spawn_point_light(o)
    local light = spawn_non_sync_object(
        id_bhvPointLight,
        E_MODEL_NONE,
        o.oPosX, o.oPosY, o.oPosZ,
        nil
    )
    if get_id_from_behavior(o.behavior) == id_bhvKoopaShell then
        light.oBehParams = 0x00FF0064
    else
        light.oBehParams = 0xFFFFFF32
    end
    light.parentObj = o
end

--- @param o Object
function bhv_flashlight_loop(o)
    local fp = get_first_person_enabled()
    local pos = gMarioStates[0].pos
    local yaw = if_then_else(fp, gFirstPersonCamera.yaw + 0x8000, gMarioStates[0].faceAngle.y)

    local dirX = sins(yaw) * 300
    local dirY = if_then_else(fp, -gFirstPersonCamera.pitch * 0.06, 120)
    local dirZ = coss(yaw) * 300

    local raycast = collision_find_surface_on_ray(pos.x, pos.y, pos.z, dirX, dirY, dirZ)
    if raycast.surface == nil then
        o.oPosX = pos.x + dirX
        o.oPosY = pos.y + dirY
        o.oPosZ = pos.z + dirZ
    else
        vec3f_to_object_pos(o, raycast.hitPos)
    end

    le_set_light_pos(o.oLightID, o.oPosX, o.oPosY, o.oPosZ)
    le_set_light_color(o.oLightID, flashlightColor[1], flashlightColor[2], flashlightColor[3])
end

function spawn_flashlight()
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
function delete_flashlight(flashlight)
    le_remove_light(flashlight.oLightID)
    obj_mark_for_deletion(flashlight)
    return nil
end

id_bhvKoopaShell = hook_behavior(id_bhvKoopaShell, OBJ_LIST_LEVEL, false, bhv_spawn_point_light, nil, "bhvKoopaShell")