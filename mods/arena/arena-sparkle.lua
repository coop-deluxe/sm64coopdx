define_custom_obj_fields({
    oArenaSparkleOwner = 'u32',
    oArenaSparkleOffsetX = 'f32',
    oArenaSparkleOffsetY = 'f32',
    oArenaSparkleOffsetZ = 'f32',
})

function bhv_arena_sparkle_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oAnimState = -1
    obj_set_billboard(obj)
    obj.oArenaSparkleOffsetX = math.random() * 0x4000 - 0x2000
    obj.oArenaSparkleOffsetY = math.random() * 0x4000 - 0x2000
    obj.oArenaSparkleOffsetZ = math.random() * 200
    obj_scale_random(obj, 1, 0)
end

function bhv_arena_sparkle_loop(obj) 
    obj.oAnimState = obj.oAnimState + 1
    if obj.oTimer > 9 then
        obj.activeFlags = ACTIVE_FLAG_DEACTIVATED;
    end

    local m = gMarioStates[obj.oArenaSparkleOwner]
    local held = gItemHeld[obj.oArenaSparkleOwner]
    if held ~= nil then
        local offset = {
            x = held.oPosX + sins(m.faceAngle.y) * 70,
            y = held.oPosY - 25,
            z = held.oPosZ + coss(m.faceAngle.y) * 70,
        }
        local scalar = (obj.oArenaSparkleOffsetZ * (1 - (obj.oTimer / 10) ^ 3))
        local offset2 = {
            x = offset.x + sins(m.faceAngle.y + obj.oArenaSparkleOffsetX) * scalar,
            y = offset.y + sins(obj.oArenaSparkleOffsetY) * scalar,
            z = offset.z + coss(m.faceAngle.y + obj.oArenaSparkleOffsetX) * scalar,
        }
        --obj.oPosX = offset.x + obj.oArenaSparkleOffsetX * (1 - (obj.oTimer / 10))
        --obj.oPosY = offset.y + obj.oArenaSparkleOffsetY * (1 - (obj.oTimer / 10))
        --obj.oPosZ = offset.z + obj.oArenaSparkleOffsetZ * (1 - (obj.oTimer / 10))
        obj.oPosX = offset2.x
        obj.oPosY = offset2.y
        obj.oPosZ = offset2.z
    end
    obj_scale(obj, (obj.oTimer / 10) * 1)
end

id_bhvArenaSparkle = hook_behavior(nil, OBJ_LIST_UNIMPORTANT, true, bhv_arena_sparkle_init, bhv_arena_sparkle_loop)
