_G.ACT_LADDER = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR)

-- behavior params:

-- ladder height
-- ex:  1388
-- object yaw = ladder yaw

function bhv_arena_ladder_init(o)
    o.hitboxRadius = 40
    o.hitboxHeight = o.oBehParams
end
id_bhvArenaLadder = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_arena_ladder_init, nil)

function mario_check_for_ladder(m)
    if m.action == ACT_FORWARD_ROLLOUT and m.prevAction == ACT_LADDER then
        m.forwardVel = 10
    end

    local ladder = obj_get_first_with_behavior_id(id_bhvArenaLadder)
    while ladder do
        if obj_check_hitbox_overlap(m.marioObj, ladder) ~= 0 then
            local dYawToObject = ladder.oFaceAngleYaw - m.faceAngle.y
            if ((m.action & ACT_FLAG_AIR ~= 0 and m.forwardVel > 20)
            or (m.action & ACT_FLAG_ATTACKING ~= 0 and (m.action ~= ACT_GROUND_POUND or m.action ~= ACT_GROUND_POUND_LAND))
            or (m.action & ACT_FLAG_AIR == 0 and m.input & INPUT_A_PRESSED ~= 0)
            ) and math.abs(dYawToObject) < 0x2000 and m.action ~= ACT_LADDER then
                m.usedObj = ladder
                m.input = m.input & ~INPUT_A_PRESSED
                return set_mario_action(m, ACT_LADDER, 0)
            end
        end
        ladder = obj_get_next_with_same_behavior_id(ladder)
    end
end
hook_event(HOOK_BEFORE_MARIO_UPDATE, mario_check_for_ladder)

function act_ladder(m)
    local ladder = m.usedObj
    if not ladder or obj_has_behavior_id(ladder, id_bhvArenaLadder) == 0 then return set_mario_action(m, ACT_FREEFALL, 0) end

    local stickX = m.controller.rawStickX
    local stickY = m.controller.rawStickY

    m.vel.x = ladder.oPosX
    m.vel.z = ladder.oPosZ
    m.vel.y = clampf(m.pos.y + stickY*.15, ladder.oPosY, ladder.oPosY + ladder.hitboxHeight)

    vec3f_copy(m.marioObj.header.gfx.pos, m.pos)

    set_character_animation(m, CHAR_ANIM_BEING_GRABBED)
    local loop = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
    set_anim_to_frame(m, (m.pos.y/10) % loop)

    m.faceAngle.x = 8192
    m.faceAngle.y = ladder.oFaceAngleYaw
    m.faceAngle.z = 0

    vec3s_copy(m.marioObj.header.gfx.angle, m.faceAngle)

    if m.input & INPUT_A_PRESSED ~= 0 then
        if math.abs(stickX) > 64 then
            m.faceAngle.y = m.faceAngle.y - 16384*signum_positive(stickX)
            m.forwardVel = 10
            m.vel.y = 10
            return set_mario_action(m, ACT_FORWARD_ROLLOUT, 0)
        end
        if stickY > 64 and m.pos.y == ladder.oPosY + ladder.hitboxHeight then
            m.forwardVel = 10
            m.vel.y = 10
            return set_mario_action(m, ACT_FORWARD_ROLLOUT, 0)
        end
        m.faceAngle.y = m.faceAngle.y + 32768
        m.forwardVel = 30
        m.vel.y = 50
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0)
    end
    if m.input & INPUT_Z_PRESSED ~= 0 then
        m.vel.y = stickY * 0.2
        m.forwardVel = 0
        m.input = m.input & ~INPUT_Z_PRESSED
        return set_mario_action(m, ACT_FREEFALL, 0)
    end
    if ladder.oPosY < m.pos.y and m.pos.y < ladder.oPosY + ladder.hitboxHeight then
        m.actionTimer = m.actionTimer + math.abs(stickY * 0.2)
    end
    if m.actionTimer > 128 then
        m.actionTimer = 0
        play_sound(SOUND_GENERAL_METAL_POUND, m.marioObj.header.gfx.cameraToObject)
    end
end
hook_mario_action(ACT_LADDER, act_ladder)
