-- name: [CS] Extra Characters
-- description: [CS] Extra Characters\nBy Coop Deluxe Team\n\nThis Character Select pack adds other characters from the Mario series!

if not _G.charSelectExists then return end

--- @param m MarioState
local function mario_update(m)
    if active_player(m) == 0 then return end

    local voiceTable = _G.charSelect.character_get_voice(m)
    if voiceTable == VOICETABLE_TOADETTE or voiceTable == VOICETABLE_PEACH or voiceTable == VOICETABLE_DAISY or voiceTable == VOICETABLE_YOSHI then
        _G.charSelect.voice.snore(m)
    end

    if obj_has_model_extended(m.marioObj, E_MODEL_PEACH_PLAYER) ~= 0 then
        peach_update(m)
    elseif obj_has_model_extended(m.marioObj, E_MODEL_DAISY) ~= 0 then
        daisy_update(m)
    end
end

--- @param m MarioState
--- @param sound CharacterSound
local function character_sound(m, sound)
    local voiceTable = _G.charSelect.character_get_voice(m)
    if voiceTable == VOICETABLE_TOADETTE or voiceTable == VOICETABLE_PEACH or voiceTable == VOICETABLE_DAISY or voiceTable == VOICETABLE_YOSHI then
        return _G.charSelect.voice.sound(m, sound)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_CHARACTER_SOUND, character_sound)