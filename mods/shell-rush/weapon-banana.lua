local bananaTimeout = 30 * 60 * 1 --- one minute

define_custom_obj_fields({
    oWeaponBananaGlobalOwner = 'u32',
})

function bhv_weapon_banana_init(obj)
    obj.oGraphYOffset = 0
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 255
    obj.oVelY = 0
    obj_scale(obj, 0.9)

    obj.oPosY = obj.oPosY + 50

    local hitbox = get_temp_object_hitbox()
    hitbox.interactType      = INTERACT_DAMAGE
    hitbox.downOffset        = 0
    hitbox.damageOrCoinValue = 4
    hitbox.health            = 1
    hitbox.numLootCoins      = 1
    hitbox.radius            = 100
    hitbox.height            = 70
    hitbox.hurtboxRadius     = 100
    hitbox.hurtboxHeight     = 70
    obj_set_hitbox(obj, hitbox)

    cur_obj_play_sound_2(SOUND_GENERAL_BOING1)

    network_init_object(obj, true, {
        'oWeaponBananaGlobalOwner'
    })
end

function bhv_weapon_banana_destroy(obj)
    obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
    spawn_triangles(obj)
    cur_obj_play_sound_2(SOUND_GENERAL_FLAME_OUT)
end

function bhv_weapon_banana_loop(obj)
    local floor = cur_obj_update_floor_height_and_get_floor()
    if floor ~= nil then
        if obj.oPosY < obj.oFloorHeight + 10 then
            obj.oVelY = 0
            obj.oPosY = obj.oFloorHeight + 5
            obj_orient_graph(obj, floor.normal.x, floor.normal.y, floor.normal.z)
        else
            obj.oVelY = obj.oVelY - 3
            obj.oPosY = obj.oPosY + obj.oVelY
            if obj.oPosY < obj.oFloorHeight + 10 then
                spawn_mist(obj)
            end
        end
    end

    -- prevent interactions for the first 5 frames
    if obj.oTimer < 5 then
        obj.oInteractStatus = 0
    end

    if cur_obj_check_interacted() ~= 0 or obj.oTimer > bananaTimeout then
        bhv_weapon_banana_destroy(obj)
    end
end

id_bhvWeaponBanana = hook_behavior(nil, OBJ_LIST_PUSHABLE, true, bhv_weapon_banana_init, bhv_weapon_banana_loop)
E_MODEL_BANANA = smlua_model_util_get_id("banana_geo")
