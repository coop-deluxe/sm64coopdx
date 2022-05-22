gItemHeld = {}

-- setup held items
for i = 0, (MAX_PLAYERS - 1) do
    gItemHeld[i] = nil
end

ATTACH_NONE = 0
ATTACH_HAND = 1
ATTACH_HEAD = 2

------------


------------

define_custom_obj_fields({
    oArenaItemHeldType = 'u32',
    oArenaItemHeldOwner = 'u32',
})

function bhv_arena_item_held_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 255
    obj.oArenaItemHeldType = ITEM_FIRE_FLOWER
    obj.hookRender = 1
    obj_scale(obj, 1)
    cur_obj_hide()
end

function bhv_arena_item_held_loop(obj)
    local m = gMarioStates[obj.oArenaItemHeldOwner]
    local s = gPlayerSyncTable[obj.oArenaItemHeldOwner]
    local data = gItemHeldData[s.item]

    -- check if this should be inactive
    if s.item == ITEM_NONE or data == nil or not active_player(m) then
        cur_obj_hide()
        return
    end

    -- if the player is off screen, hide the obj
    if m.marioBodyState.updateTorsoTime ~= gMarioStates[0].marioBodyState.updateTorsoTime then
        cur_obj_hide()
        return
    end

    -- update pallet
    local np = gNetworkPlayers[obj.oArenaItemHeldOwner]
    if np ~= nil then
        obj.globalPlayerIndex = np.globalIndex
    end

    -- check if this should be activated
    if obj_is_hidden(obj) ~= 0 or obj.oArenaItemHeldType ~= s.item then
        cur_obj_unhide()
        obj_set_model_extended(obj, data.heldModel)
        obj_scale(obj, data.scale)
        obj.oAnimState = 0
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
    end

    -- update things
    obj.oArenaItemHeldType = s.item
    if data.updateAnimState then
        obj.oAnimState = obj.oAnimState + 1
    end
end

id_bhvArenaItemHeld = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_arena_item_held_init, bhv_arena_item_held_loop)

------------

function on_level_init()
    -- initialize all held items
    for i = 0, (MAX_PLAYERS - 1) do
        gItemHeld[i] = spawn_non_sync_object(id_bhvArenaItemHeld, E_MODEL_NONE, 0, 0, 0,
            function(obj)
                obj.oArenaItemHeldType = ITEM_NONE
                obj.oArenaItemHeldOwner = i
            end)
    end
end

function dot_along_angle(obj, m, angle)
    local v1 = {
        x = obj.oPosX - m.pos.x,
        y = obj.oPosY - m.pos.y,
        z = obj.oPosZ - m.pos.z,
    }
    vec3f_normalize(v1)
    local v2 = {
        x = sins(m.faceAngle.y + angle),
        y = 0,
        z = coss(m.faceAngle.y + angle),
    }
    return vec3f_dot(v1, v2)
end

function bhv_arena_item_held_hammer_render(obj)
    local m = gMarioStates[obj.oArenaItemHeldOwner]
    local e = gMarioStateExtras[obj.oArenaItemHeldOwner]
    local animFrame = m.marioObj.header.gfx.animInfo.animFrame

    if m.action == ACT_DIVE then
        obj.oFaceAnglePitch = e.rotAngle
        obj.oFaceAngleRoll = 0
    elseif m.action == ACT_DIVE_SLIDE then
        obj.oFaceAnglePitch = 0x4000
        obj.oFaceAngleRoll = 0
    elseif m.action == ACT_STOMACH_SLIDE_STOP then
        local loopEnd = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
        local scalar = 1
        if loopEnd == 38 then
            scalar = (1 - (animFrame / loopEnd) ^ 2)
        end
        obj.oFaceAnglePitch = 0x4000 * scalar
        obj.oFaceAngleRoll = 0
    elseif m.action == ACT_PUNCHING or m.action == ACT_MOVE_PUNCHING then
        local scalar = dot_along_angle(obj, m, 0) * 1.5
        if scalar > 0.723 then scalar = 0.723 end
        obj.oFaceAnglePitch = 0x5000 * scalar + 0x500
        obj.oFaceAngleRoll = 0x1000 * dot_along_angle(obj, m, -0x4000)
    elseif m.action == ACT_GROUND_POUND then
        local loopEnd = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
        if m.actionState == 0 then
            obj.oFaceAnglePitch = 0x16000 * animFrame / loopEnd
        else
            obj.oFaceAnglePitch = 0x4000
        end
        obj.oFaceAngleRoll = 0
    elseif m.action == ACT_GROUND_POUND_LAND then
        local loopEnd = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
        local scalar = 1
        if loopEnd == 6 then
            scalar = (1 - (animFrame / loopEnd) ^ 2)
        end
        obj.oFaceAnglePitch = 0x4000 * scalar
        obj.oFaceAngleRoll = 0
    elseif m.action == ACT_JUMP_KICK then
        local loopEnd = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
        local scalar = (animFrame / loopEnd) * 9
        if scalar > 4 then scalar = 4 end
        obj.oFaceAnglePitch = -0x8000 * scalar
        obj.oFaceAngleRoll = 0
    elseif m.action == ACT_BACKFLIP then
        local loopEnd = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
        local scalar = (animFrame / loopEnd) * 4
        if scalar > 4 then scalar = 4 end
        obj.oFaceAnglePitch = -0x8000 * scalar
        obj.oFaceAngleRoll = 0x1000 * dot_along_angle(obj, m, -0x4000)
    elseif m.action == ACT_TRIPLE_JUMP then
        local loopEnd = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
        local scalar = (animFrame / loopEnd) * 4
        if scalar > 4 then scalar = 4 end
        obj.oFaceAnglePitch = 0x8000 * scalar
        obj.oFaceAngleRoll = 0x1000 * dot_along_angle(obj, m, -0x4000)
    elseif m.action == ACT_SIDE_FLIP then
        local loopEnd = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
        local scalar = (animFrame / loopEnd) * 2
        if scalar > 4 then scalar = 4 end
        obj.oFaceAnglePitch = 0x8000 * scalar
        obj.oFaceAngleRoll = 0x1000 * dot_along_angle(obj, m, -0x4000)
    else
        obj.oFaceAnglePitch = 0x2500 * dot_along_angle(obj, m, 0) + 0x500
        obj.oFaceAngleRoll = 0x1000 * dot_along_angle(obj, m, -0x4000)
    end
end

function on_object_render(obj)
    if get_id_from_behavior(obj.behavior) ~= id_bhvArenaItemHeld then
        return
    end

    local m = gMarioStates[obj.oArenaItemHeldOwner]
    local data = gItemHeldData[obj.oArenaItemHeldType]

    if data == nil or not active_player(m) then
        return
    end

    obj.oFaceAngleYaw = m.faceAngle.y + data.yawOffset
    obj.oFaceAnglePitch = data.pitchOffset
    obj.oFaceAngleRoll = 0

    if data.attachment == ATTACH_HAND then
        obj.oPosX = get_hand_foot_pos_x(m, 0)
        obj.oPosY = get_hand_foot_pos_y(m, 0) + data.yOffset
        obj.oPosZ = get_hand_foot_pos_z(m, 0)
    elseif data.attachment == ATTACH_HEAD then
        obj.oPosX = m.marioBodyState.headPos.x
        obj.oPosY = m.marioBodyState.headPos.y + data.yOffset
        obj.oPosZ = m.marioBodyState.headPos.z
    end

    if data.renderAdjust ~= nil then
        data.renderAdjust(obj)
    end

    -- if the player is off screen, move the obj to the player origin
    if m.marioBodyState.updateTorsoTime ~= gMarioStates[0].marioBodyState.updateTorsoTime then
        obj.oPosX = m.pos.x
        obj.oPosY = m.pos.y
        obj.oPosZ = m.pos.z
    end

    if data.forwardOffset > 0 then
        obj.oPosX = obj.oPosX + sins(m.faceAngle.y) * data.forwardOffset
        obj.oPosZ = obj.oPosZ + coss(m.faceAngle.y) * data.forwardOffset
    end

    obj.header.gfx.pos.x = obj.oPosX
    obj.header.gfx.pos.y = obj.oPosY
    obj.header.gfx.pos.z = obj.oPosZ
end

hook_event(HOOK_ON_OBJECT_RENDER, on_object_render)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)

----

gItemHeldData = {
    [ITEM_NONE] = {
        heldModel = E_MODEL_NONE,
        updateAnimState = false,
        billboard = false,
        scale = 1,
        attachment = ATTACH_NONE,
        yawOffset = 0,
        pitchOffset = 0,
        yOffset = 0,
        forwardOffset = 0,
        renderAdjust = nil,
    },
    [ITEM_METAL_CAP] = {
        heldModel = E_MODEL_NONE,
        updateAnimState = false,
        billboard = false,
        scale = 1,
        attachment = ATTACH_NONE,
        yawOffset = 0,
        pitchOffset = 0,
        yOffset = 0,
        forwardOffset = 0,
        renderAdjust = nil,
    },
    [ITEM_HAMMER] = {
        heldModel = E_MODEL_HAMMER,
        updateAnimState = false,
        billboard = false,
        scale = 1,
        attachment = ATTACH_HAND,
        yawOffset = 0,
        pitchOffset = 0x1000,
        yOffset = 0,
        forwardOffset = 10,
        renderAdjust = bhv_arena_item_held_hammer_render,
    },
    [ITEM_FIRE_FLOWER] = {
        heldModel = E_MODEL_RED_FLAME,
        updateAnimState = true,
        billboard = true,
        scale = 2,
        attachment = ATTACH_HAND,
        yawOffset = 0,
        pitchOffset = 0,
        forwardOffset = 25,
        yOffset = 10,
        renderAdjust = nil,
    },
    [ITEM_CANNON_BOX] = {
        heldModel = E_MODEL_CANNON_BOX,
        updateAnimState = false,
        billboard = false,
        scale = 0.65,
        attachment = ATTACH_HEAD,
        yawOffset = -0x4000,
        pitchOffset = 0,
        yOffset = 50,
        forwardOffset = 0,
        renderAdjust = nil,
    },
    [ITEM_BOBOMB] = {
        heldModel = E_MODEL_BLACK_BOBOMB,
        updateAnimState = false,
        billboard = false,
        scale = 0.5,
        attachment = ATTACH_HAND,
        yawOffset = 0,
        pitchOffset = 0,
        yOffset = -25,
        forwardOffset = 25,
        animations = gObjectAnimations.bobomb_seg8_anims_0802396C,
        animationIndex = 1,
        renderAdjust = nil,
    },
    [ITEM_COIN] = {
        heldModel = E_MODEL_NONE,
        updateAnimState = false,
        billboard = false,
        scale = 1,
        attachment = ATTACH_NONE,
        yawOffset = 0,
        pitchOffset = 0,
        yOffset = 0,
        forwardOffset = 0,
        renderAdjust = nil,
    },
}