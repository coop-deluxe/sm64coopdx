-------------------
-- Yoshi Moveset --
-------------------

if not charSelect then return end

-- Flutterable actions, these don't match the DS flutterable actions
local flutterActs = {
    [ACT_JUMP]        = true,
    [ACT_DOUBLE_JUMP] = true,
    [ACT_TRIPLE_JUMP] = true,
    [ACT_LONG_JUMP]   = true,
    [ACT_FREEFALL]    = true
}

_G.ACT_FLUTTER = allocate_mario_action(ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_GROUP_AIRBORNE)
YOSHI_ANIM_FLUTTER = 'yoshi_flutter_jump'

---@param m MarioState
function act_flutter(m)
    -- End flutter after 1 second
    if m.actionTimer >= 30 or (m.input & INPUT_A_DOWN) == 0 then
        if m.actionTimer < 30 then
            play_character_sound(m, CHAR_SOUND_MAX) -- Stop sample after letting go of A
        end
        return set_mario_action(m, ACT_FREEFALL, 0)
    end

    local ended = common_air_action_step(m, ACT_JUMP_LAND, CHAR_ANIM_RUNNING_UNUSED, 0) ~= 0 -- Checks if the action ended earlier due to forced actions like bonking or landing

    if ended then
        play_character_sound(m, CHAR_SOUND_MAX) -- Stop sample after landing
    elseif m.actionTimer == 0 then
        play_character_sound(m, YOSHI_SOUND_FLUTTER) -- Play audio sample
    end

    smlua_anim_util_set_animation(m.marioObj, YOSHI_ANIM_FLUTTER) -- Sets the animation

    m.marioBodyState.eyeState = MARIO_EYES_CLOSED                 -- Eye State
    m.vel.y = approach_f32(m.vel.y, m.actionTimer / 1.25, 8, 8)   -- Height increases faster as the 1 second passes
    m.marioObj.header.gfx.animInfo.animAccel = 0x10000 * 2        -- Anim Speed

    m.actionTimer = m.actionTimer + 1
    return false
end

---@param m MarioState
function yoshi_update(m)
    if m.prevAction & ACT_FLAG_AIR == 0 and m.action & ACT_FLAG_AIR ~= 0 and flutterActs[m.action] and m.controller.buttonDown & A_BUTTON ~= 0 and m.vel.y < 0 then
        set_mario_action(m, ACT_FLUTTER, 0)
    end
end

hook_mario_action(ACT_FLUTTER, act_flutter)
