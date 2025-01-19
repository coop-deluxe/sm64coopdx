if not _G.charSelectExists then return end

local princessFloatActs = {
    [ACT_JUMP] = true,
    [ACT_DOUBLE_JUMP] = true,
    [ACT_TRIPLE_JUMP] = true,
    [ACT_LONG_JUMP] = true,
    [ACT_BACKFLIP] = true,
    [ACT_SIDE_FLIP] = true,
    [ACT_WALL_KICK_AIR] = true,
}

-----------------
-- Peach Float --
-----------------

ACT_PEACH_FLOAT = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_MOVING)

--- @param m MarioState
local function act_peach_float(m)
    -- apply movement when using action
    common_air_action_step(m, ACT_JUMP_LAND, CHAR_ANIM_BEND_KNESS_RIDING_SHELL, AIR_STEP_NONE)

    -- setup when action starts (horizontal speed and voiceline)
    if m.actionTimer == 0 then
        play_character_sound(m, CHAR_SOUND_HELLO)
    end

    
    if m.forwardVel > 20 then
        m.forwardVel = m.forwardVel - 0.5
    end

    -- Slowly decend
    m.vel.y = -1
    set_mario_particle_flags(m, PARTICLE_SPARKLES, 0)

    -- avoid issue with flying and then make the hover end after 2 secs or when stopping holding the button
    if m.prevAction ~= ACT_TRIPLE_JUMP and (m.flags & MARIO_WING_CAP) ~= 0 then
        if m.actionTimer >= 50 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    else
        if m.actionTimer >= 50 or (m.controller.buttonDown & A_BUTTON) == 0 then
            set_mario_action(m, ACT_FREEFALL, 0)
        end
    end

    -- increment the action timer to make the hover stop
    m.actionTimer = m.actionTimer + 1
end

--- @param m MarioState
function peach_update(m)
    if (m.input & INPUT_A_DOWN) ~= 0 and m.vel.y < -10 and m.prevAction ~= ACT_PEACH_FLOAT and princessFloatActs[m.action] then
        set_mario_action(m, ACT_PEACH_FLOAT, 0)
    end
end

hook_mario_action(ACT_PEACH_FLOAT, act_peach_float)

-----------------------
-- Daisy Double Jump --
-----------------------

ACT_DAISY_JUMP = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_MOVING)

--- @param m MarioState
local function act_daisy_jump(m)
    -- apply movement when using action
    common_air_action_step(m, ACT_JUMP_LAND, CHAR_ANIM_BEND_KNESS_RIDING_SHELL, AIR_STEP_NONE)

    -- setup when action starts (vertical speed and voiceline)
    if m.actionTimer == 0 then
        m.vel.y = m.forwardVel*0.3 + 40
        m.forwardVel = m.forwardVel*0.7
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
    if (m.input & INPUT_A_PRESSED) ~= 0 and m.vel.y < 10 and m.prevAction ~= ACT_DAISY_JUMP and princessFloatActs[m.action] then
        set_mario_action(m, ACT_DAISY_JUMP, 0)
    end
end

hook_mario_action(ACT_DAISY_JUMP, act_daisy_jump)

local function on_character_select_load()
    local CT_PEACH = extraCharacters[2].tablePos
    local CT_DAISY = extraCharacters[3].tablePos
    
    -- Peach
    _G.charSelect.character_hook_moveset(CT_PEACH, HOOK_MARIO_UPDATE, peach_update)
    -- Daisy
    _G.charSelect.character_hook_moveset(CT_DAISY, HOOK_MARIO_UPDATE, daisy_update)
end

hook_event(HOOK_ON_MODS_LOADED, on_character_select_load)