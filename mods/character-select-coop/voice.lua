if incompatibleClient then return 0 end

local TYPE_TABLE = "table"
local TYPE_USERDATA = "userdata"
local TYPE_STRING = "string"

local SLEEP_TALK_SNORES = 8
local STARTING_SNORE = 46
local SLEEP_TALK_START = STARTING_SNORE + 49
local SLEEP_TALK_END = SLEEP_TALK_START + SLEEP_TALK_SNORES
local stallTimer = 0
local stallSayLine = 5

characterVoices = {
    [E_MODEL_WALUIGI] = {
        [CHAR_SOUND_OKEY_DOKEY] =        audio_sample_load('0B_waluigi_okey_dokey.aiff'),
        [CHAR_SOUND_LETS_A_GO] =         audio_sample_load('1A_waluigi_lets_a_go.aiff'), 
        [CHAR_SOUND_GAME_OVER] =         audio_sample_load('11_waluigi_game_over.aiff'), 
        [CHAR_SOUND_PUNCH_YAH] =         audio_sample_load('08_waluigi_punch_yah.aiff'), 
        [CHAR_SOUND_PUNCH_WAH] =         audio_sample_load('01_waluigi_jump_wah.aiff'),
        [CHAR_SOUND_PUNCH_HOO] =         audio_sample_load('09_waluigi_punch_hoo.aiff'), 
        [CHAR_SOUND_YAH_WAH_HOO] =       {audio_sample_load('00_waluigi_jump_hoo.aiff'), audio_sample_load('01_waluigi_jump_wah.aiff'), audio_sample_load('02_waluigi_yah.aiff')},
        [CHAR_SOUND_HOOHOO] =            audio_sample_load('01_waluigi_hoohoo.aiff'),
        [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = {audio_sample_load('04_waluigi_yahoo.aiff'), audio_sample_load('18_waluigi_waha.aiff'), audio_sample_load('19_waluigi_yippee.aiff')},
        [CHAR_SOUND_UH] =                audio_sample_load('05_waluigi_uh.aiff'),
        [CHAR_SOUND_UH2] =               audio_sample_load('05_waluigi_uh2.aiff'),
        [CHAR_SOUND_UH2_2] =             audio_sample_load('05_waluigi_uh2.aiff'),
        [CHAR_SOUND_DOH] =               audio_sample_load('10_waluigi_doh.aiff'),
        [CHAR_SOUND_OOOF] =              audio_sample_load('0B_waluigi_ooof.aiff'),
        [CHAR_SOUND_OOOF2] =             audio_sample_load('0B_waluigi_ooof.aiff'),
        [CHAR_SOUND_HAHA] =              audio_sample_load('03_waluigi_haha.aiff'),
        [CHAR_SOUND_HAHA_2] =            audio_sample_load('03_waluigi_haha.aiff'),
        [CHAR_SOUND_YAHOO] =             audio_sample_load('04_waluigi_yahoo.aiff'),
        [CHAR_SOUND_DOH] =               audio_sample_load('10_waluigi_doh.aiff'),
        [CHAR_SOUND_WHOA] =              audio_sample_load('08_waluigi_whoa.aiff'),
        [CHAR_SOUND_EEUH] =              audio_sample_load('09_waluigi_eeuh.aiff'),
        [CHAR_SOUND_WAAAOOOW] =          audio_sample_load('00_waluigi_waaaooow.aiff'),
        [CHAR_SOUND_TWIRL_BOUNCE] =      audio_sample_load('14_waluigi_twirl_bounce.aiff'),
        [CHAR_SOUND_GROUND_POUND_WAH] =  audio_sample_load('01_waluigi_jump_wah.aiff'),
        [CHAR_SOUND_WAH2] =              audio_sample_load('07_waluigi_wah2.aiff'),
        [CHAR_SOUND_HRMM] =              audio_sample_load('06_waluigi_hrmm.aiff'),
        [CHAR_SOUND_HERE_WE_GO] =        audio_sample_load('0C_waluigi_here_we_go.aiff'),
        [CHAR_SOUND_SO_LONGA_BOWSER] =   audio_sample_load('16_waluigi_so_longa_bowser.aiff'),
        -- DAMAGE
        [CHAR_SOUND_ATTACKED] =          audio_sample_load('0A_waluigi_attacked.aiff'),
        [CHAR_SOUND_PANTING] =           audio_sample_load('02_waluigi_panting.aiff'),
        [CHAR_SOUND_PANTING_COLD] =      audio_sample_load('02_waluigi_panting.aiff'),
        [CHAR_SOUND_ON_FIRE] =           audio_sample_load('04_waluigi_on_fire.aiff'),
        -- SLEEP SOUNDS
        [CHAR_SOUND_IMA_TIRED] =         audio_sample_load('17_waluigi_tired.aiff'),
        [CHAR_SOUND_YAWNING] =           audio_sample_load('0D_waluigi_yawning.aiff'),
        [CHAR_SOUND_SNORING1] =          audio_sample_load('0E_waluigi_snoring1.aiff'),
        [CHAR_SOUND_SNORING2] =          audio_sample_load('0F_waluigi_snoring2.aiff'),
        [CHAR_SOUND_SNORING3] =          audio_sample_load('15_waluigi_snoring3.aiff'),
        -- COUGHING
        [CHAR_SOUND_COUGHING1] =         audio_sample_load('06_waluigi_coughing.aiff'),
        [CHAR_SOUND_COUGHING2] =         audio_sample_load('06_waluigi_coughing.aiff'),
        [CHAR_SOUND_COUGHING3] =         audio_sample_load('06_waluigi_coughing.aiff'),
        -- DEATH
        [CHAR_SOUND_DYING] =             audio_sample_load('03_waluigi_dying.aiff'),
        [CHAR_SOUND_DROWNING] =          audio_sample_load('0C_waluigi_drowning.aiff'),
        [CHAR_SOUND_MAMA_MIA] =          audio_sample_load('0A_waluigi_mama_mia.aiff')
    }
}

local levelReverbs = {
    [LEVEL_NONE]              = { 0x00, 0x00, 0x00 },
    [LEVEL_UNKNOWN_1]         = { 0x00, 0x00, 0x00 },
    [LEVEL_UNKNOWN_2]         = { 0x00, 0x00, 0x00 },
    [LEVEL_UNKNOWN_3]         = { 0x00, 0x00, 0x00 },
    [LEVEL_BBH]               = { 0x28, 0x28, 0x28 },
    [LEVEL_CCM]               = { 0x10, 0x38, 0x38 },
    [LEVEL_CASTLE]            = { 0x20, 0x20, 0x30 },
    [LEVEL_HMC]               = { 0x28, 0x28, 0x28 },
    [LEVEL_SSL]               = { 0x08, 0x30, 0x30 },
    [LEVEL_BOB]               = { 0x08, 0x08, 0x08 },
    [LEVEL_SL]                = { 0x10, 0x28, 0x28 },
    [LEVEL_WDW]               = { 0x10, 0x18, 0x18 },
    [LEVEL_JRB]               = { 0x10, 0x18, 0x18 },
    [LEVEL_THI]               = { 0x0c, 0x0c, 0x20 },
    [LEVEL_TTC]               = { 0x18, 0x18, 0x18 },
    [LEVEL_RR]                = { 0x20, 0x20, 0x20 },
    [LEVEL_CASTLE_GROUNDS]    = { 0x08, 0x08, 0x08 },
    [LEVEL_BITDW]             = { 0x28, 0x28, 0x28 },
    [LEVEL_VCUTM]             = { 0x28, 0x28, 0x28 },
    [LEVEL_BITFS]             = { 0x28, 0x28, 0x28 },
    [LEVEL_SA]                = { 0x10, 0x10, 0x10 },
    [LEVEL_BITS]              = { 0x28, 0x28, 0x28 },
    [LEVEL_LLL]               = { 0x08, 0x30, 0x30 },
    [LEVEL_DDD]               = { 0x10, 0x20, 0x20 },
    [LEVEL_WF]                = { 0x08, 0x08, 0x08 },
    [LEVEL_ENDING]            = { 0x00, 0x00, 0x00 },
    [LEVEL_CASTLE_COURTYARD]  = { 0x08, 0x08, 0x08 },
    [LEVEL_PSS]               = { 0x28, 0x28, 0x28 },
    [LEVEL_COTMC]             = { 0x28, 0x28, 0x28 },
    [LEVEL_TOTWC]             = { 0x20, 0x20, 0x20 },
    [LEVEL_BOWSER_1]          = { 0x40, 0x40, 0x40 },
    [LEVEL_WMOTR]             = { 0x28, 0x28, 0x28 },
    [LEVEL_UNKNOWN_32]        = { 0x70, 0x00, 0x00 },
    [LEVEL_BOWSER_2]          = { 0x40, 0x40, 0x40 },
    [LEVEL_BOWSER_3]          = { 0x40, 0x40, 0x40 },
    [LEVEL_UNKNOWN_35]        = { 0x00, 0x00, 0x00 },
    [LEVEL_TTM]               = { 0x08, 0x08, 0x08 },
    [LEVEL_UNKNOWN_37]        = { 0x00, 0x00, 0x00 },
    [LEVEL_UNKNOWN_38]        = { 0x00, 0x00, 0x00 },
}

local stalledAudio = {}

---@param sample ModAudio
---@param pos Vec3f
---@param baseVolume number
---@param reverbAmount number (0 to 1, where 1 = full echo effect)
local function play_sound_with_reverb(sample, pos, baseVolume, reverbAmount)
    if is_game_paused() or optionTable[optionTableRef.localVoices].toggle == 0 then return end
    -- Play the original sample
    audio_sample_play(sample, pos, baseVolume)

    -- Define simple fake reverb delays and volume reductions
    local echoDelays = { 0.1, 0.2, 0.35, 0.5 }
    local echoVolumes = {
        baseVolume * reverbAmount * 0.6,
        baseVolume * reverbAmount * 0.4,
        baseVolume * reverbAmount * 0.25,
        baseVolume * reverbAmount * 0.15,
    }

    for i = 1, #echoDelays do
        table.insert(stalledAudio, {
            path = sample.filepath,
            frame = (get_global_timer() + math.floor(echoDelays[i]*30)),
            sample = sample, 
            pos = pos,
            volume = echoVolumes[i]
        })
    end
end


---@param sample ModAudio
local function stop_sound_with_reverb(sample)
    audio_sample_stop(sample)
    if #stalledAudio > 0 then
        for i = #stalledAudio, 1, -1 do
            if stalledAudio[i] ~= nil and stalledAudio[i].path == sample.filepath then
                audio_sample_stop(stalledAudio[i].sample)
                table.remove(stalledAudio, i)
            end
        end
    end
end

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
                            stop_sound_with_reverb(voiceTable[sound][voice])
                        end
                    else
                        stop_sound_with_reverb(voiceTable[sound])
                    end
                end
            end
        end
    end
end

local playerSample = {}
for i = 0, MAX_PLAYERS - 1 do
    playerSample[i] = nil
end

local characterAddonSounds = {
    [CHAR_SOUND_PUNCH_YAH] = {sound = SOUND_ACTION_THROW, pitch = 1.1},
    [CHAR_SOUND_PUNCH_WAH] = {sound = SOUND_ACTION_THROW, pitch = 1.0},
    [CHAR_SOUND_PUNCH_HOO] = {sound = SOUND_ACTION_THROW, pitch = 0.9},
}

---@param m MarioState
---@param sound CharacterSound
---@param pos Vec3f?
function custom_character_sound(m, sound, pos)
    local np = gNetworkPlayers[m.playerIndex]
    local voiceTable = character_get_voice(m)
    local voiceToggle = optionTable[optionTableRef.localVoices].toggle
    local voiceOff = (voiceToggle == 0 or (voiceToggle == 2 and m.playerIndex ~= 0))
    if m.playerIndex == 0 then
        if not startup_init_stall() then
            return NO_SOUND
        end
    end
    local index = m.playerIndex
    if playerSample[index] ~= nil and type(playerSample[index]) ~= TYPE_STRING then
        stop_sound_with_reverb(playerSample[index])
    end

    -- Add punch "woosh" since NO_SOUND removes it
    if characterAddonSounds[sound] and (voiceTable ~= nil or voiceOff) then
        local soundInfo = characterAddonSounds[sound]
        play_sound_with_freq_scale(soundInfo.sound, m.marioObj.header.gfx.cameraToObject, soundInfo.pitch);
    end

    -- Voice Toggle
    if voiceOff then return NO_SOUND end

    -- Vanilla Voicelines
    if voiceTable == nil then return end

    -- Load the appropriate sample
    local voice = character_get_voice(m)[sound]
    if voice == nil then return NO_SOUND end
    if type(voice) == TYPE_TABLE then
        if #voice > 0 then
            playerSample[index] = voice[math.random(1, #voice)]
        else
            return NO_SOUND
        end
    else
        playerSample[index] = voice
    end

    -- Play the sample
    -- Volume based on sound type
    local baseVolume = 1.0
    if sound == CHAR_SOUND_SNORING1 or sound == CHAR_SOUND_SNORING2 or sound == CHAR_SOUND_SNORING3 then
        baseVolume = 0.5
    end

    local position = pos or m.pos
    local reverbAmount = 0x08
    if levelReverbs[np.currLevelNum] ~= nil and levelReverbs[np.currLevelNum][np.currAreaIndex] ~= nil then
        reverbAmount = levelReverbs[np.currLevelNum][np.currAreaIndex]/127
    elseif smlua_level_util_get_info(np.currLevelNum) ~= nil then
        local levelInfo = smlua_level_util_get_info(np.currLevelNum)
        levelReverbs[np.currLevelNum] = {}
        levelReverbs[np.currLevelNum][1] = levelInfo.echoLevel1 or reverbAmount
        levelReverbs[np.currLevelNum][2] = levelInfo.echoLevel2 or reverbAmount
        levelReverbs[np.currLevelNum][3] = levelInfo.echoLevel3 or reverbAmount
        reverbAmount = levelReverbs[np.currLevelNum][np.currAreaIndex]/127
    else
        reverbAmount = levelReverbs[np.currLevelNum][1]/127
    end
    
    play_sound_with_reverb(playerSample[index], position, baseVolume, reverbAmount)

    return NO_SOUND
end

---@param m MarioState
function custom_character_snore(m)
    if is_game_paused() or optionTable[optionTableRef.localVoices].toggle == 0 or (optionTable[optionTableRef.localVoices].toggle == 2 and m.playerIndex ~= 0) then
        -- Remove echo lines that should have played while paused
        if #stalledAudio > 0 then
            for i = 1, #stalledAudio do
                if stalledAudio[i] ~= nil and stalledAudio[i].frame <= get_global_timer() then
                    table.remove(stalledAudio, i)
                end
            end
        end
        return
    end

    -- Putting echo stuffs in snore since it's on update
    if #stalledAudio > 0 then
        for i = 1, #stalledAudio do
            if stalledAudio[i] ~= nil and stalledAudio[i].frame <= get_global_timer() then
                local voice = stalledAudio[i]
                audio_sample_play(voice.sample, voice.pos, voice.volume)
                table.remove(stalledAudio, i)
            end
        end
    end

    if m.action ~= ACT_SLEEPING then
        return
    elseif m.actionState ~= 2 or (m.flags & MARIO_MARIO_SOUND_PLAYED) == 0 then
        return
    end

    -- get the voice table
    local voiceTable = character_get_voice(m)
    -- Check nil table for vanilla voices
    if voiceTable == nil then return end
    -- Check empty table for no sound
    if voiceTable == nil then return NO_SOUND end
    
    local snoreTable = voiceTable[CHAR_SOUND_SNORING3]
    if snoreTable == nil or snoreTable._pointer ~= nil then
        snoreTable = {}
        for i = CHAR_SOUND_SNORING1, CHAR_SOUND_SNORING3 do
            if voiceTable[i] ~= nil then
                table.insert(snoreTable, voiceTable[i])
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

function config_character_sounds()
    log_to_console_once("'config_character_sounds' is deprecated, and functionality is now baked into `character_add_voice`", CONSOLE_MESSAGE_WARNING)
end

-- Join sound
introLine = false
local function mario_update(m)
    if m.playerIndex ~= 0 then return end
    if startup_init_stall() and not introLine then
        if m.action ~= ACT_INTRO_CUTSCENE then
            play_character_sound(m, CHAR_SOUND_OKEY_DOKEY)
        end
        introLine = true
    end

    custom_character_snore(m)
end

hook_event(HOOK_CHARACTER_SOUND, custom_character_sound)
cs_hook_mario_update(mario_update)

-- Peach Line Replacements
---@param soundbits integer
---@param pos Vec3f 
local function on_play_sound(soundbits,pos)
    local endpeachsoundtable = {[SOUND_PEACH_MARIO] = true,[SOUND_PEACH_POWER_OF_THE_STARS] = true,[SOUND_PEACH_THANKS_TO_YOU] = true, [SOUND_PEACH_THANK_YOU_MARIO] = true,[SOUND_PEACH_SOMETHING_SPECIAL] = true,[SOUND_PEACH_BAKE_A_CAKE] = true,[SOUND_PEACH_FOR_MARIO] = true,[SOUND_PEACH_MARIO2] = true}
    local m = gMarioStates[0]
    if endpeachsoundtable[soundbits] and (character_get_voice(m) ~= nil) and (character_get_voice(m)[soundbits] ~= nil) then --ending peach cutscene sounds
        custom_character_sound(m,soundbits,pos)
        return NO_SOUND
    elseif (soundbits == SOUND_PEACH_DEAR_MARIO) and (character_get_voice(m) ~= nil) and (character_get_voice(m)[soundbits] ~= nil)  then --introduction peach sounds
        custom_character_sound(m,soundbits,pos)
        return NO_SOUND
    elseif (soundbits == SOUND_MENU_THANK_YOU_PLAYING_MY_GAME) and (character_get_voice(m) ~= nil) and (character_get_voice(m)[soundbits] ~= nil)  then --cake screen thank you for playing my game voice
        custom_character_sound(m,soundbits,pos)
        return NO_SOUND
    end
end

hook_event(HOOK_ON_PLAY_SOUND, on_play_sound)
