-------------------
-- Moveset Hooks --
-------------------

if not charSelect then return end

------------------------------
-- Character Data Resetting --
------------------------------

local charResetActions

--- Resets the character action
--- @param m MarioState
function character_actions_reset(m)
    if m.playerIndex ~= 0 then return end
    local CT_CHAR = character_get_current_number()

    -- Insert your actions to force reset when you aren't that character
    charResetActions = charResetActions or {
        [ACT_BIRDO_HOLD_WALKING]  = CT_BIRDO,
        [ACT_SPIT_EGG]            = CT_BIRDO,
        [ACT_SPIT_EGG_AIR]        = CT_BIRDO,
        [ACT_SPIT_EGG_WALK]       = CT_BIRDO,
    }

    if charResetActions[m.action] and charResetActions[m.action] ~= CT_CHAR then
        force_idle_state(m)
    end
end

local PITCH_AND_HITBOX_RESET_ACTIONS
--- @param m MarioState
function reset_from_action(m)
    if m.marioBodyState.allowPartRotation == 1 then
        vec3s_copy(m.marioBodyState.torsoAngle, gVec3sZero())
        vec3s_copy(m.marioBodyState.headAngle, gVec3sZero())
        m.marioBodyState.allowPartRotation = false
    end

    --- Resets the body rotations, pitch, and hitbox size on new actions
    PITCH_AND_HITBOX_RESET_ACTIONS = PITCH_AND_HITBOX_RESET_ACTIONS or {
        [ACT_DONKEY_KONG_ROLL] = 1,
        [ACT_DONKEY_KONG_ROLL_AIR] = 1,
        [ACT_DONKEY_KONG_POUND] = 1,
        [ACT_DONKEY_KONG_POUND_HIT] = 1,
        [ACT_SONIC_SPIN_JUMP] = 1,
        [ACT_SONIC_AIR_SPIN] = 1,
        [ACT_SONIC_HOMING_ATTACK] = 1,
        [ACT_SONIC_SPIN_DASH] = 1,
    }

    if PITCH_AND_HITBOX_RESET_ACTIONS[m.prevAction] then
        m.faceAngle.x = 0
        m.marioObj.hitboxRadius = 37
    end
end

hook_event(HOOK_MARIO_UPDATE, character_actions_reset)
hook_event(HOOK_ON_SET_MARIO_ACTION, reset_from_action)

------------
--  Main  --
------------

local chars = { "Mario", "Luigi", "Toad", "Waluigi", "Wario" }

-- inject extra characters
for _, char in ipairs(extraCharacters) do
    table.insert(chars, char.name)
end

local movesetHooks = {}
for _, name in ipairs(chars) do
    movesetHooks[name] = require ("movesets/" .. name)
end

local function on_character_select_load()
    -- inject vanilla characters
    for i = 1, CT_MAX do
        table.insert(extraCharacters, { name = chars[i], tablePos = i - 1 })
    end

    for _, char in ipairs(extraCharacters) do
        for _, hook in ipairs(movesetHooks[char.name]) do
            if hook.global then
                hook_event(hook[1], hook[2])
            else
                character_hook_moveset(char.tablePos, hook[1], hook[2])
            end
        end
    end
end

hook_event(HOOK_ON_MODS_LOADED, on_character_select_load)
