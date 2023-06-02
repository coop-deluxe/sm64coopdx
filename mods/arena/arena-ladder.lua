ACT_LADDER = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR)

-- behavior params:

-- ladder height
-- ex:  1388
-- object yaw = ladder yaw

local sLadderClimb = 0
local ladders = {}

---@param obj Object
function bhv_arena_ladder_init(obj)
    obj.hitboxRadius = 40
    obj.hitboxHeight = obj.oBehParams
    table.insert(ladders, obj)
end

id_bhvArenaLadder = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_arena_ladder_init, nil)

---@param m MarioState
function mario_check_for_ladder(m)
    if not (m.action & ACT_FLAG_ATTACKING ~= 0) or #ladders == 0 then return end
    for i, ladder in pairs(ladders) do
        if lateral_dist_between_objects(m.marioObj, ladder) < ladder.hitboxRadius + m.marioObj.hitboxRadius and m.pos.y < ladder.oPosY + ladder.hitboxHeight and m.pos.y + m.marioObj.hitboxHeight > ladder.oPosY then
            gMarioStateExtras[m.playerIndex].ladder = ladder
            set_mario_action(m, ACT_LADDER, 0)
        end
    end
end

---@param m MarioState
function act_ladder(m)
    if gMarioStateExtras[m.playerIndex].ladder == nil then
        for i, ladder in pairs(ladders) do
            if lateral_dist_between_objects(m.marioObj, ladder) < ladder.hitboxRadius + m.marioObj.hitboxRadius and m.pos.y < ladder.oPosY + ladder.hitboxHeight and m.pos.y + m.marioObj.hitboxHeight > ladder.oPosY then
                gMarioStateExtras[m.playerIndex].ladder = ladder
            end
        end
    end
    local ladder = gMarioStateExtras[m.playerIndex].ladder

    m.vel.x = 0
    m.vel.y = 0
    m.vel.z = 0
    m.forwardVel = 0

    perform_air_step(m, 0)

    m.pos.x = ladder.oPosX
    m.pos.z = ladder.oPosZ

    set_mario_animation(m, MARIO_ANIM_BEING_GRABBED)
    local loop = m.marioObj.header.gfx.animInfo.curAnim.loopEnd
    set_anim_to_frame(m, m.pos.y/10 - math.floor(m.pos.y / 10 / loop) * loop)

    m.marioObj.header.gfx.angle.x = 8192
    m.faceAngle.y = ladder.oFaceAngleYaw

    m.pos.y = m.pos.y + m.controller.rawStickY*.2
    if m.pos.y > ladder.oPosY + ladder.hitboxHeight then
        m.pos.y = ladder.oPosY + ladder.hitboxHeight
    end
    if m.pos.y < ladder.oPosY then
        m.pos.y = ladder.oPosY
    end
    if (m.input & (INPUT_A_PRESSED | INPUT_B_PRESSED)) ~= 0 then
        set_mario_action(m,ACT_FREEFALL,0)
        m.vel.y = m.controller.rawStickY * 0.2
        gMarioStateExtras[m.playerIndex].ladder = nil
    end
    if m.playerIndex ~= 0 then return end
    if ladder.oPosY < m.pos.y and m.pos.y < ladder.oPosY + ladder.hitboxHeight then
        sLadderClimb = sLadderClimb + math.abs(m.controller.rawStickY * 0.2)
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
