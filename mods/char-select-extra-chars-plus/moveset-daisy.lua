-------------------
-- Daisy Moveset --
-------------------

if not charSelect then return end

local midairJumpActs = {
    [ACT_JUMP]          = true,
    [ACT_DOUBLE_JUMP]   = true,
    [ACT_TRIPLE_JUMP]   = true,
    [ACT_LONG_JUMP]     = true,
    [ACT_BACKFLIP]      = true,
    [ACT_SIDE_FLIP]     = true,
    [ACT_WALL_KICK_AIR] = true,
}

_G.ACT_MIDAIR_JUMP = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_MOVING)

--- @param m MarioState
local function act_midair_jump(m)
    -- apply movement when using action
    common_air_action_step(m, ACT_JUMP_LAND, CHAR_ANIM_BEND_KNESS_RIDING_SHELL, AIR_STEP_NONE)

    -- setup when action starts (vertical speed and voiceline)
    if m.actionTimer == 0 then
        m.vel.y = m.forwardVel * 0.3 + 40
        m.forwardVel = m.forwardVel * 0.7
        play_character_sound(m, CHAR_SOUND_HELLO)
    end

    set_mario_particle_flags(m, PARTICLE_LEAF, 0)

    -- avoid issue with flying and then make the hover end after 2 secs or when stopping holding the button
    if m.prevAction ~= ACT_TRIPLE_JUMP and (m.flags & MARIO_WING_CAP) ~= 0 then
        if m.actionTimer >= 10 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    else
        if m.actionTimer >= 10 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    end

    -- increment the action timer to make the hover stop
    m.actionTimer = m.actionTimer + 1
end

--- @param m MarioState
function daisy_update(m)
    if (m.input & INPUT_A_PRESSED) ~= 0 and m.vel.y < 10 and m.prevAction ~= ACT_MIDAIR_JUMP and midairJumpActs[m.action] then
        set_mario_action(m, ACT_MIDAIR_JUMP, 0)
    end
end

hook_mario_action(ACT_MIDAIR_JUMP, act_midair_jump)
