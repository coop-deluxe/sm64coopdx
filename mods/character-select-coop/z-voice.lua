
if incompatibleClient then return 0 end

local voiceTimeout = false

local SLEEP_TALK_SNORES = 8

gCustomVoiceSamples = {}
gCustomVoiceStream = nil

-- localize functions to improve performance
local audio_sample_stop,audio_sample_destroy,type,math_random,audio_stream_stop,audio_stream_destroy,audio_stream_load,audio_stream_play,audio_sample_load,audio_sample_play,is_game_paused,play_character_sound = audio_sample_stop,audio_sample_destroy,type,math.random,audio_stream_stop,audio_stream_destroy,audio_stream_load,audio_stream_play,audio_sample_load,audio_sample_play,is_game_paused,play_character_sound

--- @param m MarioState
function stop_custom_character_sound(m, sound)
    local voice_sample = gCustomVoiceSamples[m.playerIndex]
    if voice_sample == nil or not voice_sample.loaded or voice_sample.isStream then
        return nil
    end

    audio_sample_stop(voice_sample)
    if voice_sample.file.relativePath:match('^.+/(.+)$') == sound then
        return voice_sample
    end
    audio_sample_destroy(voice_sample)
    gCustomVoiceSamples[m.playerIndex] = nil -- prevent this from pointing to another sample or possibly garbage data

    return nil
end

--- @param m MarioState
function play_custom_character_sound(m, voice)
    if voiceTimeout then return 0 end
    local sound
    if type(voice) == "table" then
        sound = voice[math_random(#voice)]
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
            local lagTimer = 0
            repeat
                lagTimer = lagTimer + 1
                if lagTimer > 500 then
                    voiceTimeout = true
                    if optionTable[optionTableRef.notification].toggle == 1 then
                        djui_chat_message_create("\\#FFAAAA\\Note: Custom Character Voices are unavalible due to\ninability to load audio, This is most likely because\nyour client does not support custom audio functionality.")
                    elseif optionTable[optionTableRef.notification].toggle == 2 then
                        djui_popup_create('Character Select:\nCustom Character Voices\nare unavalible due to\ninability to load audio!', 4)
                    end
                    break
                end
            until voice_sample.loaded
        end
        audio_sample_play(voice_sample, m.pos, 1)
        gCustomVoiceSamples[m.playerIndex] = voice_sample
    end
    return 0
end

--- @param m MarioState
local function custom_character_sound(m, characterSound)
    if is_game_paused() or voiceTimeout or optionTable[optionTableRef.localVoices].toggle == 0 then return 0 end
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
    if is_game_paused() or voiceTimeout or optionTable[optionTableRef.localVoices].toggle == 0 then return end

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

function stop_all_character_sounds()
    if gCustomVoiceStream then
        audio_stream_stop(gCustomVoiceStream)
        audio_stream_destroy(gCustomVoiceStream)
        gCustomVoiceStream = nil
    end
    for i = 0, MAX_PLAYERS-1 do
        stop_custom_character_sound(gMarioStates[i])
    end
end
hook_event(HOOK_ON_WARP, stop_all_character_sounds)
hook_event(HOOK_UPDATE, function ()
    if is_game_paused() then
        stop_all_character_sounds()
    end
end)

_G.charSelect.voice = {
    sound = custom_character_sound,
    snore = custom_character_snore,
}
