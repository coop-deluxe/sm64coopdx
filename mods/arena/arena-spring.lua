define_custom_obj_fields({
    oArenaSpringSprung = 'u32',
})

function bhv_arena_spring_child_init(obj)
    obj.oHomeX = obj.oPosX
    obj.oHomeY = obj.oPosY
    obj.oHomeZ = obj.oPosZ
end

function bhv_arena_spring_child_loop(obj)
    local p = obj.parentObj
    if p == nil then
        return
    end

    local pitch = obj.oFaceAnglePitch + 16384
    local yaw = obj.oFaceAngleYaw + 32768

    local vel = {
        x = coss(pitch) * sins(yaw),
        y = sins(pitch),
        z = coss(pitch) * coss(yaw),
    }

    vec3f_normalize(vel)
    vec3f_mul(vel, 110 * p.header.gfx.scale.y)

    obj.oPosX = obj.oHomeX + vel.x
    obj.oPosY = obj.oHomeY + vel.y
    obj.oPosZ = obj.oHomeZ + vel.z
end

id_bhvArenaSpringChild = hook_behavior(nil, OBJ_LIST_DEFAULT, true, nil, bhv_arena_spring_child_loop, 'id_bhvArenaSpringChild')

------------------------------------

function bhv_arena_spring_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oOpacity = 255
    obj_set_model_extended(obj, E_MODEL_SPRING_BOTTOM)
    spawn_non_sync_object(id_bhvArenaSpringChild, E_MODEL_SPRING_TOP, obj.oPosX, obj.oPosY, obj.oPosZ,  function(c)
        c.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
        c.parentObj = obj
        c.oOpacity = 255
        c.oFaceAnglePitch = obj.oFaceAnglePitch
        c.oFaceAngleYaw = obj.oFaceAngleYaw
        c.oFaceAngleRoll = obj.oFaceAngleRoll
    end)
    network_init_object(obj, false, {
        'oArenaSpringSprung'
    })
end

function bhv_arena_spring_launch(obj)
    local m = gMarioStates[0]
    local behParams = obj.oBehParams
    local strength = behParams & 0xFF
    local pitchAdjust = ((behParams >> 8) & 0xFF) * 0.01
    if pitchAdjust == 0 then pitchAdjust = 1 end

    local opitch = obj.oFaceAnglePitch
    local pitch = opitch * pitchAdjust + 16384
    local yaw = obj.oFaceAngleYaw + 32768

    local vel = {
        x = coss(pitch) * sins(yaw),
        y = sins(pitch),
        z = coss(pitch) * coss(yaw),
    }

    vec3f_normalize(vel)
    vec3f_mul(vel, 300)

    spawn_non_sync_object(id_bhvTriangleParticleSpawner, E_MODEL_NONE,
        obj.oPosX + vel.x,
        obj.oPosY + vel.y,
        obj.oPosZ + vel.z,
        nil)

    vec3f_normalize(vel)
    vec3f_mul(vel, strength)

    if math.abs(opitch) >= 2500 then
        set_mario_action(m, ACT_SHOT_FROM_CANNON, 0)
        m.vel.y = vel.y
        m.faceAngle.y = yaw
        m.forwardVel = math.sqrt((vel.x * vel.x) + vel.z * vel.z)
    else
        set_mario_action(m, ACT_TRIPLE_JUMP, 0)
        m.vel.y = vel.y
        m.forwardVel = 0
        local e = gMarioStateExtras[0]
        e.springing = 1
    end
    obj.oArenaSpringSprung = 15

    network_send_object(obj, false)
end

function bhv_arena_spring_loop(obj)
    local player = gMarioStates[0].marioObj
    local dist = math.sqrt((obj.oPosX - player.oPosX) ^ 2 + (obj.oPosY - player.oPosY) ^ 2 + (obj.oPosZ - player.oPosZ) ^ 2)
    if dist < 160 and mario_health_float(gMarioStates[0]) > 0 then
        bhv_arena_spring_launch(obj)
    end
    if obj.oArenaSpringSprung > 0 then
        obj.oArenaSpringSprung = obj.oArenaSpringSprung - 1
    end
    local sprung = obj.oArenaSpringSprung
    local sx = 15 - sprung
    scale = 0

    if sx == 1 then
        cur_obj_play_sound_2(SOUND_GENERAL_POUND_ROCK)
    end

    if sx < 3 then
        scale = (sx/5) + 2/5
    else
        scale = 1 - ((sx - 3) / 12)
        scale = scale * scale
    end
    obj.header.gfx.scale.y = scale * scale + 0.1
end

id_bhvArenaSpring = hook_behavior(nil, OBJ_LIST_DEFAULT, true, bhv_arena_spring_init, bhv_arena_spring_loop, 'id_bhvArenaSpring')
