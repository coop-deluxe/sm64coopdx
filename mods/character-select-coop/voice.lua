for i = 0, MAX_PLAYERS -1, 1 do
    gPlayerSyncTable[i].customVoice = 0
end

local voicecount = 0

local SLEEP_TALK_SNORES = 8

gCustomVoiceSamples = {}
gCustomVoiceSamplesBackup = {}
gCustomVoiceStream = nil

--- @param m MarioState
function stop_custom_character_sound(m, sound)
    local voice_sample = gCustomVoiceSamples[m.playerIndex]
    if voice_sample == false and gCustomVoiceSamplesBackup[m.playerIndex].loaded then
        audio_sample_stop(gCustomVoiceSamplesBackup[m.playerIndex])
        audio_sample_destroy(gCustomVoiceSamplesBackup[m.playerIndex])
        voicecount = voicecount - 1
        gCustomVoiceSamplesBackup[m.playerIndex] = nil
        return
    end
    if voice_sample == nil or type(voice_sample) == "boolean" then
        return
    end
    if not voice_sample.loaded then
        gCustomVoiceSamplesBackup[m.playerIndex] = true
        return
    end

    audio_sample_stop(voice_sample)
    if voice_sample.file.relativePath:match('^.+/(.+)$') == sound then
        return voice_sample
    end
    audio_sample_destroy(voice_sample)
    voicecount = voicecount - 1
end

--- @param m MarioState
function play_custom_character_sound(m, voice)
    local sound
    if type(voice) == "table" then
        sound = voice[math.random(#voice)]
    else
        sound = voice
    end
    if sound == nil then return 0 end

    --Get current sample and stop it
    local voice_sample = stop_custom_character_sound(m, sound)

    if type(sound) ~= "string" then
        return sound
    end

    if (m.area == nil or m.area.camera == nil) and m.playerIndex == 0 then
        if gCustomVoiceStream ~= nil then
            audio_stream_stop(gCustomVoiceStream)
            audio_stream_destroy(gCustomVoiceStream)
        end
        gCustomVoiceStream = audio_stream_load(sound)
        audio_stream_play(gCustomVoiceStream, true, 1)
    else
        if voice_sample == nil then
            voice_sample = audio_sample_load(sound)
			while not voice_sample.loaded do end
            voicecount = voicecount + 1
        end
        audio_sample_play(voice_sample, m.pos, 1)

        if gCustomVoiceSamplesBackup[m.playerIndex] ~= nil and not(gCustomVoiceSamples[m.playerIndex] == false) then
            gCustomVoiceSamplesBackup[m.playerIndex] = voice_sample
        else
            gCustomVoiceSamples[m.playerIndex] = voice_sample
        end
    end
    return 0
end

--- @param m MarioState
local function custom_character_sound(m, characterSound)
    if is_game_paused() or optionTable[optionTableRef.localVoices].toggle == 0 then return end
    if characterSound == CHAR_SOUND_SNORING3 then return 0 end
    if characterSound == CHAR_SOUND_HAHA and m.hurtCounter > 0 then return 0 end

    local voice = _G.charSelect.character_get_voice(m)[characterSound]
    if voice ~= nil then
        return play_custom_character_sound(m, voice)
    end
    return 0
end

local STARTING_SNORE = 46
local SLEEP_TALK_START = STARTING_SNORE + 49
local SLEEP_TALK_END = SLEEP_TALK_START + SLEEP_TALK_SNORES

--- @param m MarioState
local function custom_character_snore(m)
    if is_game_paused() or optionTable[optionTableRef.localVoices].toggle == 0 then return end
    if gCustomVoiceSamplesBackup[m.playerIndex] ~= nil and not (gCustomVoiceSamples[m.playerIndex] == false) then
        if gCustomVoiceSamples[m.playerIndex].loaded then
            audio_sample_destroy(gCustomVoiceSamples[m.playerIndex])
            voicecount = voicecount - 1
            gCustomVoiceSamples[m.playerIndex] = false
        end
    end
    local SNORE3_TABLE = _G.charSelect.character_get_voice(m)[CHAR_SOUND_SNORING3]
    
    if m.action ~= ACT_SLEEPING then
        if m.isSnoring > 0 then
            stop_custom_character_sound(m)
        end
        return

    elseif not (m.actionState == 2 and (m.flags & MARIO_MARIO_SOUND_PLAYED) ~= 0) then
        return
    end

    local animFrame = m.marioObj.header.gfx.animInfo.animFrame

    if SNORE3_TABLE ~= nil and #SNORE3_TABLE >= 2 then
        if animFrame == 2 and m.actionTimer < SLEEP_TALK_START then
            play_custom_character_sound(m, SNORE3_TABLE[2])
        elseif animFrame == 25 then
            if #SNORE3_TABLE >= 3 then
                m.actionTimer = m.actionTimer + 1
                if m.actionTimer >= SLEEP_TALK_END then
                    m.actionTimer = STARTING_SNORE
                end
                if m.actionTimer == SLEEP_TALK_START then
                    play_custom_character_sound(m, SNORE3_TABLE[3])
                elseif m.actionTimer < SLEEP_TALK_START then
                    play_custom_character_sound(m, SNORE3_TABLE[1])
                end
            else
                play_custom_character_sound(m, SNORE3_TABLE[1])
            end
        end
    elseif animFrame == 2 then
        play_character_sound(m, CHAR_SOUND_SNORING2)

    elseif animFrame == 25 then
        play_character_sound(m, CHAR_SOUND_SNORING1)
    end
end

_G.charSelect.voice = {
    sound = custom_character_sound,
    snore = custom_character_snore,
}
gPlayerSyncTable[0].customVoice = true