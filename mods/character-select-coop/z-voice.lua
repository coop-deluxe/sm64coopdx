if incompatibleClient then return end

-- rewritten custom voice system for Character Select
-- by Agent X

-- will need some revising in the future, but this will do for now.

local SLEEP_TALK_SNORES = 8
local STARTING_SNORE = 46
local SLEEP_TALK_START = STARTING_SNORE + 49
local SLEEP_TALK_END = SLEEP_TALK_START + SLEEP_TALK_SNORES

local function stop_all_custom_character_sounds()
    -- run through each player
    for i = 0, MAX_PLAYERS - 1 do
        local m = gMarioStates[i]
        -- get the voice table, if there is one
        local voiceTable = character_get_voice(m)
        if voiceTable ~= nil then
            -- run through each sample
            for sound in pairs(voiceTable) do
                -- if the sample is found, try to stop it
                if voiceTable[sound] ~= nil and type(voiceTable[sound]) ~= "string" then
                    -- if there's no pointer then it must be a sound clip table
                    if voiceTable[sound]._pointer == nil then
                        for voice in pairs(voiceTable[sound]) do
                            if type(voiceTable[sound][voice]) == "string" then
                                break
                            end
                            audio_sample_stop(voiceTable[sound][voice])
                        end
                    else
                        audio_sample_stop(voiceTable[sound])
                    end
                end
            end
        end
    end
end

--[[local function stop_custom_character_sound(m, sound)
    local voiceTable = character_get_voice(m)
    -- if there's no pointer then it must be a sound clip table
    if type(voiceTable[sound]) == "string" then return end
    if voiceTable[sound]._pointer == nil then
        for voice in pairs(voiceTable[sound]) do
            if type(voiceTable[voice]) == "string" then
                break
            end
            audio_sample_stop(voiceTable[sound][voice])
        end
    else
        audio_sample_stop(voiceTable[sound])
    end
end]]

--- @param m MarioState
--- @param sound CharacterSound
local function custom_character_sound(m, sound)
    if optionTable[optionTableRef.localVoices].toggle == 0 then return NO_SOUND end

    -- get the voice table
    local voiceTable = character_get_voice(m)
    -- load samples that haven't been loaded
    for voice, name in pairs(voiceTable) do
        if type(voiceTable[voice]) == "string" then
            voiceTable[voice] = audio_sample_load(name)
        end
    end

    -- get the sample to play
    local voice = voiceTable[sound]
    if voice == nil then return NO_SOUND end
    local sample = voice
    -- if there's no pointer then it must be a sound clip table
    if voice._pointer == nil then
        -- run through each sample and load in any samples that haven't been loaded
        for i, name in pairs(voice) do
            if type(voice[i]) == "string" then
                voice[i] = audio_sample_load(name)
            end
        end
        -- choose a random sample
        sample = voice[math.random(#voice)]
    end

    -- play the sample
    audio_sample_stop(sample)
    if sound == CHAR_SOUND_SNORING1 or sound == CHAR_SOUND_SNORING2 or sound == CHAR_SOUND_SNORING3 then
        audio_sample_play(sample, m.pos, 0.5)
    else
        audio_sample_play(sample, m.pos, 1.0)
    end
    return NO_SOUND
end

--- @param m MarioState
local function custom_character_snore(m)
    if is_game_paused() or optionTable[optionTableRef.localVoices].toggle == 0 then return end

    if m.action ~= ACT_SLEEPING then
        -- if m.isSnoring ~= 0 then
        --     stop_custom_character_sound(m, CHAR_SOUND_SNORING1)
        --     stop_custom_character_sound(m, CHAR_SOUND_SNORING2)
        --     stop_custom_character_sound(m, CHAR_SOUND_SNORING3)
        -- end
        return
    elseif m.actionState ~= 2 or (m.flags & MARIO_MARIO_SOUND_PLAYED) == 0 then
        return
    end

    local voice = character_get_voice(m)
    local snoreTable = voice[CHAR_SOUND_SNORING3]
    -- for some reason CS seemed to originally expect snoring to all be under SNORING3 for some reason???
    -- if there's a pointer then it can't be a sound clip table
    if snoreTable == nil or snoreTable._pointer ~= nil then
        snoreTable = {}
        for i = CHAR_SOUND_SNORING1, CHAR_SOUND_SNORING3 do
            if voice[i] ~= nil then
                table.insert(snoreTable, voice[i])
            end
        end
    end

    local animFrame = m.marioObj.header.gfx.animInfo.animFrame
    if snoreTable ~= nil and #snoreTable >= 2 then
        if animFrame == 2 and m.actionTimer < SLEEP_TALK_START then
            custom_character_sound(m, snoreTable[2])
        elseif animFrame == 25 then
            if #snoreTable >= 3 then
                m.actionTimer = m.actionTimer + 1
                if m.actionTimer >= SLEEP_TALK_END then
                    m.actionTimer = STARTING_SNORE
                end
                if m.actionTimer == SLEEP_TALK_START then
                    play_character_sound(m, CHAR_SOUND_SNORING3)
                elseif m.actionTimer < SLEEP_TALK_START then
                    play_character_sound(m, CHAR_SOUND_SNORING1)
                end
            else
                play_character_sound(m, CHAR_SOUND_SNORING1)
            end
        end
    elseif animFrame == 2 then
        play_character_sound(m, CHAR_SOUND_SNORING2)

    elseif animFrame == 25 then
        play_character_sound(m, CHAR_SOUND_SNORING1)
    end
end

local function update()
    if is_game_paused() then
        stop_all_custom_character_sounds()
    end
end

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_ON_LEVEL_INIT, stop_all_custom_character_sounds)

_G.charSelect.voice = {
    sound = custom_character_sound,
    snore = custom_character_snore,
}