-- Character Voices --
-- Don't edit this file, just use the `charSelect.character_add_voice(modelID, voiceTable)` function

if not _G.charSelectExists then return end

local voiceTables = {
    [VOICETABLE_TOADETTE] = true,
    [VOICETABLE_YOSHI]    = true,
    [VOICETABLE_PEACH]    = true,
    [VOICETABLE_DAISY]    = true,
    [VOICETABLE_BIRDO]    = true
}

--- @param m MarioState
local function mario_update(m)
    if is_player_active(m) == 0 then return end
    local voiceTable = charSelect.character_get_voice(m)
    if voiceTables[voiceTable] then
        return charSelect.voice.snore(m)
    end
end

--- @param m MarioState
--- @param sound CharacterSound
local function character_sound(m, sound)
    local voiceTable = charSelect.character_get_voice(m)
    if voiceTables[voiceTable] then
        return charSelect.voice.sound(m, sound)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_CHARACTER_SOUND, character_sound)