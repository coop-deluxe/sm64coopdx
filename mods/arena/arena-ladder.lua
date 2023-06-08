ACT_LADDER = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR)

-- behavior params:

-- ladder height
-- ex:  1388
-- object yaw = ladder yaw

local sLadderClimb = 0
local ladders = {}

gPlayerSyncTable[0].ladder = {}
gPlayerSyncTable[0].ladder.x = nil
gPlayerSyncTable[0].ladder.y = nil
gPlayerSyncTable[0].ladder.z = nil
gPlayerSyncTable[0].ladder.height = nil
gPlayerSyncTable[0].ladder.angle = nil

---@param obj Object
function bhv_arena_ladder_init(obj)
    obj.hitboxRadius = 40
    obj.hitboxHeight = obj.oBehParams
    table.insert(ladders, obj)
end

id_bhvArenaLadder = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_arena_ladder_init, nil)

---@param m MarioState
function mario_check_for_ladder(m)
    if m.action == ACT_FORWARD_ROLLOUT and m.prevAction == ACT_LADDER then
        m.forwardVel = 10
    end
    if not (m.action & ACT_FLAG_ATTACKING ~= 0) or #ladders == 0 or m.action == ACT_LADDER then return end
    for i, ladder in pairs(ladders) do
        if lateral_dist_between_objects(m.marioObj, ladder) < ladder.hitboxRadius + m.marioObj.hitboxRadius and m.pos.y < ladder.oPosY + ladder.hitboxHeight and m.pos.y + m.marioObj.hitboxHeight > ladder.oPosY then
            gPlayerSyncTable[m.playerIndex].ladder.x = ladder.oPosX
            gPlayerSyncTable[m.playerIndex].ladder.y = ladder.oPosY
            gPlayerSyncTable[m.playerIndex].ladder.z = ladder.oPosZ
            gPlayerSyncTable[m.playerIndex].ladder.height = ladder.hitboxHeight
            gPlayerSyncTable[m.playerIndex].ladder.angle = ladder.oFaceAngleYaw
            set_mario_action(m, ACT_LADDER, 0)
        end
    end
end

---@param m MarioState
function act_ladder(m)
    local ladder = gPlayerSyncTable[m.playerIndex].ladder
    local x = m.controller.rawStickX
    local y = m.controller.rawStickY

    m.vel.x = 0
    m.vel.y = 0
    m.vel.z = 0
    m.forwardVel = 0

    perform_air_step(m, 0)

    m.pos.x = ladder.x
    m.pos.z = ladder.z

    set_mario_animation(m, MARIO_ANIM_BEING_GRABBED)
    local loop = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
    set_anim_to_frame(m, m.pos.y/10 - math.floor(m.pos.y / 10 / loop) * loop)

    m.marioObj.header.gfx.angle.x = 8192
    m.faceAngle.y = ladder.angle

    m.pos.y = m.pos.y + y*.2
    if m.pos.y > ladder.y + ladder.height then
        m.pos.y = ladder.y + ladder.height
    end
    if m.pos.y < ladder.y then
        m.pos.y = ladder.y
    end
    if m.input & INPUT_A_PRESSED ~= 0 then
        if math.abs(m.controller.rawStickX) > 64 then
            set_mario_action(m,ACT_FORWARD_ROLLOUT,0)
            m.faceAngle.y = m.faceAngle.y - 16384*math.abs(x)/x
            m.forwardVel = 10
            m.vel.y = 10
            return
        end
        if m.controller.rawStickY > 64 then
            set_mario_action(m,ACT_FORWARD_ROLLOUT,0)
            m.forwardVel = 10
            m.vel.y = 10
            return
        end
        set_mario_action(m,ACT_WALL_KICK_AIR,0)
        m.faceAngle.y = m.faceAngle.y + 32768
        m.forwardVel = 30
        m.vel.y = 50
        return
    end
    if m.input & INPUT_Z_PRESSED ~= 0 then
        set_mario_action(m,ACT_FREEFALL,0)
        m.vel.y = y * 0.2
        return
    end
    if m.playerIndex ~= 0 then return end
    if ladder.y < m.pos.y and m.pos.y < ladder.y + ladder.height then
        sLadderClimb = sLadderClimb + math.abs(y * 0.2)
    end
    if sLadderClimb > 128 and m.playerIndex == 0 then
        sLadderClimb = 0
        play_sound(SOUND_GENERAL_METAL_POUND, m.marioObj.header.gfx.cameraToObject)
    end
end
function clearladders()
    ladders = {}
end
hook_event(HOOK_ON_LEVEL_INIT,clearladders)
hook_mario_action(ACT_LADDER, { every_frame = act_ladder })
