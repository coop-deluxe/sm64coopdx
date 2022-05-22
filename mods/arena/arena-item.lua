local arenaItemTimeout = 30 * 15 -- 15 seconds

-----------------

define_custom_obj_fields({
    oArenaItemType = 'u32',
    oArenaItemTouched = 'u32',
})

function bhv_arena_item_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 255
    obj.oArenaItemType = (obj.oBehParams >> 24) % ITEM_MAX

    -- update pallet
    obj.globalPlayerIndex = gNetworkPlayers[0].globalIndex

    local data = gItemData[obj.oArenaItemType]
    obj_scale(obj, data.scale)

    network_init_object(obj, false, {
        'oArenaItemType',
        'oArenaItemTouched',
        'oTimer'
    })
end

function bhv_arena_item_collect(obj)
    spawn_sparkles(obj.oPosX, obj.oPosY, obj.oPosZ)
    spawn_mist(obj, 2)
    obj.oArenaItemTouched = 1
    obj.oTimer = 0
    network_send_object(obj, true)
    cur_obj_play_sound_2(SOUND_GENERAL_COLLECT_1UP)

    local s = gPlayerSyncTable[0]
    s.charging = 0
    s.ammo = 5
    s.item = obj.oArenaItemType
end

function bhv_arena_item_collect_metal_cap(obj)
    spawn_sparkles(obj.oPosX, obj.oPosY, obj.oPosZ)
    spawn_mist(obj, 2)
    obj.oArenaItemTouched = 1
    obj.oTimer = 0
    network_send_object(obj, true)

    local m = gMarioStates[0]
    m.flags = m.flags & (~MARIO_CAP_ON_HEAD & ~MARIO_CAP_IN_HAND)

    local capTime = 600 * 2.5
    local capMusic = SEQUENCE_ARGS(4, SEQ_EVENT_METAL_CAP)

    if capTime > m.capTimer then
        m.capTimer = capTime
    end

    m.flags = m.flags | MARIO_CAP_ON_HEAD

    play_sound(SOUND_MENU_STAR_SOUND, m.marioObj.header.gfx.cameraToObject)
    play_character_sound(m, CHAR_SOUND_HERE_WE_GO)

    play_cap_music(capMusic)
end

function bhv_arena_item_collect_coin(obj)
    spawn_sparkles(obj.oPosX, obj.oPosY, obj.oPosZ)
    spawn_mist(obj, 2)
    obj.oArenaItemTouched = 1
    obj.oTimer = 0
    network_send_object(obj, true)

    cur_obj_play_sound_2(SOUND_GENERAL_COIN)

    local m = gMarioStates[0]
    m.numCoins = m.numCoins + 1
    m.healCounter = m.healCounter + 8
end

function bhv_arena_item_update_touch(obj)
    local data = gItemData[obj.oArenaItemType]
    if obj.oArenaItemTouched == 1 then
        if obj.oTimer >= data.timeout then
            obj.oArenaItemTouched = 0
            if network_is_server() then
                network_send_object(obj, true)
            end
        elseif obj.oTimer < 5 then
            obj_scale(obj, data.scale - (obj.oTimer / 5))
        elseif obj.oTimer >= data.timeout - 10 then
            obj_scale(obj, (obj.oTimer - (data.timeout - 10)) / 10)
            cur_obj_unhide()
        else
            cur_obj_hide()
        end
        return true
    else
        obj_scale(obj, data.scale)
        cur_obj_unhide()
        return false
    end
end

function bhv_arena_item_update_model(obj)
    local data = gItemData[obj.oArenaItemType]
    if data == nil then return end

    obj_set_model_extended(obj, data.model)
    obj.oFaceAnglePitch = data.pitchOffset

    if data.billboard then
        obj.header.gfx.node.flags = obj.header.gfx.node.flags | GRAPH_RENDER_BILLBOARD
    else
        obj.header.gfx.node.flags = obj.header.gfx.node.flags & ~GRAPH_RENDER_BILLBOARD
    end

    if data.animations ~= nil then
        obj.oAnimations = data.animations
        cur_obj_init_animation(data.animationIndex)
    else
        obj.oAnimations = nil
    end

    if data.updateAnimState then
        obj.oAnimState = obj.oAnimState + 1
    end
end

function bhv_arena_item_update_rotation(obj)
    obj.oFaceAngleYaw   = obj.oFaceAngleYaw + 600
    obj.oFaceAngleRoll  = 0
    obj.oFaceAnglePitch = 0
end

function bhv_arena_item_check_collect(obj)
    local data = gItemData[obj.oArenaItemType]
    local m = nearest_mario_state_to_object(obj)
    if m == gMarioStates[0] then
        local s = gPlayerSyncTable[0]
        local player = m.marioObj
        local yDist = math.abs(obj.oPosY - player.oPosY)
        local xzDist = math.sqrt((obj.oPosX - player.oPosX) ^ 2 + (obj.oPosZ - player.oPosZ) ^ 2)
        if xzDist < 160 and yDist < 250 then
            if data ~= nil and data.customCollectionFunc ~= nil then
                data.customCollectionFunc(obj)
            elseif s.item == ITEM_NONE and s.item == ITEM_NONE and s.item == ITEM_NONE then
                bhv_arena_item_collect(obj)
            end
        end
    end
end

function bhv_arena_item_loop(obj)
    -- update touch
    if bhv_arena_item_update_touch(obj) then
        return
    end

    -- update model
    bhv_arena_item_update_model(obj)

    -- update rotation
    bhv_arena_item_update_rotation(obj)

    -- see if player touched
    bhv_arena_item_check_collect(obj)

end

id_bhvArenaItem = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_arena_item_init, bhv_arena_item_loop)

-----------------

gItemData = {
    [ITEM_NONE] = {
        model = E_MODEL_NONE,
        pitchOffset = 0,
        scale = 1,
        billboard = false,
        updateAnimState = false,
        timeout = arenaItemTimeout,
        customCollectionFunc = nil,
    },
    [ITEM_METAL_CAP] = {
        model = E_MODEL_MARIOS_METAL_CAP,
        pitchOffset = 0,
        scale = 2,
        billboard = false,
        updateAnimState = false,
        timeout = arenaItemTimeout * 5,
        customCollectionFunc = bhv_arena_item_collect_metal_cap,
    },
    [ITEM_HAMMER] = {
        model = E_MODEL_HAMMER,
        pitchOffset = 0x2000,
        scale = 1,
        billboard = false,
        updateAnimState = false,
        timeout = arenaItemTimeout,
        customCollectionFunc = nil,
    },
    [ITEM_FIRE_FLOWER] = {
        model = E_MODEL_FIRE_FLOWER,
        pitchOffset = 0,
        scale = 1,
        billboard = false,
        updateAnimState = false,
        timeout = arenaItemTimeout,
        customCollectionFunc = nil,
    },
    [ITEM_CANNON_BOX] = {
        model = E_MODEL_CANNON_BOX,
        pitchOffset = 0,
        scale = 1,
        billboard = false,
        updateAnimState = false,
        timeout = arenaItemTimeout,
        customCollectionFunc = nil,
    },
    [ITEM_BOBOMB] = {
        model = E_MODEL_BLACK_BOBOMB,
        pitchOffset = 0,
        animations = gObjectAnimations.bobomb_seg8_anims_0802396C,
        animationIndex = 0,
        scale = 1,
        billboard = false,
        updateAnimState = false,
        timeout = arenaItemTimeout,
        customCollectionFunc = nil,
    },
    [ITEM_COIN] = {
        model = E_MODEL_YELLOW_COIN,
        pitchOffset = 0,
        scale = 1,
        billboard = true,
        updateAnimState = true,
        timeout = arenaItemTimeout,
        customCollectionFunc = bhv_arena_item_collect_coin,
    },
}
