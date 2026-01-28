-------------------
-- Moveset Hooks --
-------------------

local OmmEnabled = OmmEnabled
if not charSelect then return end

------------------------------
-- Character Data Resetting --
------------------------------

-- Insert your actions to force reset when you aren't that character
local charResetActions = {
    [ACT_BIRDO_HOLD_WALKING]  = CT_BIRDO,
    [ACT_SPIT_EGG]            = CT_BIRDO,
    [ACT_SPIT_EGG_AIR]        = CT_BIRDO,
    [ACT_SPIT_EGG_WALK]       = CT_BIRDO,
}

--- Resets the character action
--- @param m MarioState
function character_actions_reset(m)
    if m.playerIndex ~= 0 then return end
    local CT_CHAR = character_get_current_number()
    if charResetActions[m.action] and charResetActions[m.action] ~= CT_CHAR then
        force_idle_state(m)
    end
end

--- Resets the body rotations, pitch, and hitbox size on new actions
local PITCH_AND_HITBOX_RESET_ACTIONS = {
    [ACT_DONKEY_KONG_ROLL] = 1,
    [ACT_DONKEY_KONG_ROLL_AIR] = 1,
    [ACT_DONKEY_KONG_POUND] = 1,
    [ACT_DONKEY_KONG_POUND_HIT] = 1,
    [ACT_SPIN_JUMP] = 1,
    [ACT_AIR_SPIN] = 1,
    [ACT_HOMING_ATTACK] = 1,
    [ACT_SPIN_DASH] = 1,
}
--- @param m MarioState
function reset_from_action(m)
    if m.marioBodyState.allowPartRotation == 1 then
        vec3s_copy(m.marioBodyState.torsoAngle, gVec3sZero())
        vec3s_copy(m.marioBodyState.headAngle, gVec3sZero())
        m.marioBodyState.allowPartRotation = false
    end

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

local function on_character_select_load()
    -- Character Types Enum --

    _G.CT_TOADETTE     = extraCharacters[ 1].tablePos       --- @type CharacterType
    _G.CT_PEACH        = extraCharacters[ 2].tablePos       --- @type CharacterType
    _G.CT_DAISY        = extraCharacters[ 3].tablePos       --- @type CharacterType
    _G.CT_YOSHI        = extraCharacters[ 4].tablePos       --- @type CharacterType
    _G.CT_BIRDO        = extraCharacters[ 5].tablePos       --- @type CharacterType
    _G.CT_FOREMANSPIKE = extraCharacters[ 6].tablePos       --- @type CharacterType
    _G.CT_PAULINE      = extraCharacters[ 7].tablePos       --- @type CharacterType
    _G.CT_ROSALINA     = extraCharacters[ 8].tablePos       --- @type CharacterType
    _G.CT_WAPEACH      = extraCharacters[ 9].tablePos       --- @type CharacterType
    _G.CT_DONKEY_KONG  = extraCharacters[10].tablePos       --- @type CharacterType
    _G.CT_SONIC        = extraCharacters[11].tablePos       --- @type CharacterType

    -- Toadette
    character_hook_moveset(CT_TOADETTE, HOOK_MARIO_UPDATE, toadette_update)
    character_hook_moveset(CT_TOADETTE, HOOK_ON_SET_MARIO_ACTION, toadette_on_set_action)
    character_hook_moveset(CT_TOADETTE, HOOK_BEFORE_PHYS_STEP, toadette_before_phys_step)
    -- Peach
    character_hook_moveset(CT_PEACH, HOOK_MARIO_UPDATE, peach_update)
    -- Daisy
    character_hook_moveset(CT_DAISY, HOOK_MARIO_UPDATE, daisy_update)
    -- Yoshi
    character_hook_moveset(CT_YOSHI, HOOK_MARIO_UPDATE, yoshi_update)
    -- Birdo
    character_hook_moveset(CT_BIRDO, HOOK_MARIO_UPDATE, birdo_update)
    character_hook_moveset(CT_BIRDO, HOOK_ON_SET_MARIO_ACTION, birdo_on_set_action)
    character_hook_moveset(CT_BIRDO, HOOK_BEFORE_SET_MARIO_ACTION, birdo_before_action)
    character_hook_moveset(CT_BIRDO, HOOK_ON_INTERACT, birdo_on_interact)
    character_hook_moveset(CT_BIRDO, HOOK_BEFORE_PHYS_STEP, birdo_before_phys_step)
    character_hook_moveset(CT_BIRDO, HOOK_BEFORE_MARIO_UPDATE, birdo_before_update)
    -- Spike
    character_hook_moveset(CT_FOREMANSPIKE, HOOK_MARIO_UPDATE, spike_update)
    character_hook_moveset(CT_FOREMANSPIKE, HOOK_BEFORE_SET_MARIO_ACTION, spike_before_action)
    -- Pauline
    if not OmmEnabled then
        hook_event(HOOK_ON_SET_MARIO_ACTION, pauline_init_action) -- Must run for every character
        character_hook_moveset(CT_PAULINE, HOOK_BEFORE_SET_MARIO_ACTION, pauline_before_action)
        character_hook_moveset(CT_PAULINE, HOOK_BEFORE_MARIO_UPDATE, pauline_cancel_action)
        hook_event(HOOK_MARIO_UPDATE, pauline_update) -- Must run for every character
    end
    -- Rosalina
    character_hook_moveset(CT_ROSALINA, HOOK_MARIO_UPDATE, rosalina_update)
    -- character_hook_moveset(CT_ROSALINA, HOOK_ON_PVP_ATTACK, rosalina_on_pvp_attack)
    character_hook_moveset(CT_ROSALINA, HOOK_ALLOW_INTERACT, rosalina_allow_interact)
    character_hook_moveset(CT_ROSALINA, HOOK_BEFORE_SET_MARIO_ACTION, rosalina_before_action)
    -- Wapeach
    character_hook_moveset(CT_WAPEACH, HOOK_BEFORE_SET_MARIO_ACTION, wapeach_before_action)
    -- Donkey Kong
    character_hook_moveset(CT_DONKEY_KONG, HOOK_BEFORE_PHYS_STEP, donkey_kong_before_phys_step)
    character_hook_moveset(CT_DONKEY_KONG, HOOK_BEFORE_SET_MARIO_ACTION, donkey_kong_before_action)
    character_hook_moveset(CT_DONKEY_KONG, HOOK_ON_INTERACT, donkey_kong_on_interact)
    -- Sonic
    character_hook_moveset(CT_SONIC, HOOK_BEFORE_SET_MARIO_ACTION, before_set_sonic_action)
    character_hook_moveset(CT_SONIC, HOOK_ON_SET_MARIO_ACTION, on_set_sonic_action)
    character_hook_moveset(CT_SONIC, HOOK_ALLOW_INTERACT, sonic_allow_interact)
    character_hook_moveset(CT_SONIC, HOOK_ON_INTERACT, sonic_on_interact)
    character_hook_moveset(CT_SONIC, HOOK_ALLOW_FORCE_WATER_ACTION, function () return false end)
    character_hook_moveset(CT_SONIC, HOOK_MARIO_UPDATE, sonic_update)
    character_hook_moveset(CT_SONIC, HOOK_BEFORE_PHYS_STEP, sonic_before_phys_step)
    character_hook_moveset(CT_SONIC, HOOK_ON_HUD_RENDER_BEHIND, sonic_hud_stuff)
end

hook_event(HOOK_ON_MODS_LOADED, on_character_select_load)
