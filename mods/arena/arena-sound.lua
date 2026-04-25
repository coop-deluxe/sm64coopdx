local m = gMarioStates[0]
local np = gNetworkPlayers[0]

local pauseMenuShouldShowMusic = true
local pauseMenuShowLevelID = true

local curMap = -1
local audioMainPaused = false
local audioMain --Used for the main audio
local audioSpecial --Used for things like cap music
local audioCurSeq

local bgms = {
    [55] = {audio='snow.ogg',    loopEnd = 500,     loopStart = 0,      volume = 1, name="Frosty Citadel - Sonic Gaiden"  },
    [56] = {audio='rainbow.ogg', loopEnd = 148.657, loopStart = 12.406, volume = 1, name="Rainbow Road - Coop Deluxe"     },
    [57] = {audio='city.ogg',    loopEnd = 500,     loopStart = 06.975, volume = 1, name="City Outskirts - Sonic Megamix" }
}

-- disable cap music
function music()
    if bgms[np.currLevelNum] then
        stop_cap_music()
    end
end
hook_event(HOOK_UPDATE, music)

function handleMusic()
    ------------------------------------------------------
    --          Handle stopping/starting of music       --
    ------------------------------------------------------
    --Handle main course music
    if curMap ~= np.currLevelNum and m.area.macroObjects then
        curMap = np.currLevelNum
        audioCurSeq = get_current_background_music()
        if audioMain then
            audio_stream_stop(audioMain)
            audioMain = nil
        end
        if bgms[curMap] and bgms[curMap].audio then
            set_background_music(0,0,0)
            audioMain = audio_stream_load(bgms[curMap].audio)
            if audioMain then
                audio_stream_set_looping(audioMain, true)
                audio_stream_play(audioMain, true, bgms[curMap].volume)
                print("Playing new audio " .. bgms[curMap].name)
            else
                djui_popup_create('Missing audio!: ' .. bgms[curMap].audio, 10)
                print("Attempted to load filed audio file, but couldn't find it on the system: " .. bgms[curMap].audio)
            end
        else
            print("No audio for this map, so not stopping default: " .. curMap)
        end
    end
    --Handle cap music
    if m.capTimer > 0 and bgms[-2] then
        --Handle pausing main streamed music, if applicable.
        if audioMain and not audioMainPaused then
            audioMainPaused = true
            audio_stream_pause(audioMain)
        end
        --Start up cap music if it's defined.
        if not audioSpecial then
            set_background_music(0,0,0)
            stop_cap_music()
            audioSpecial = audio_stream_load(bgms[-2].audio)
            if audioSpecial then
                audio_stream_set_looping(audioSpecial, true)
                audio_stream_play(audioSpecial, true, bgms[-2].volume)
                print("Playing cap audio " .. bgms[-2].name)
            else
                djui_popup_create('Missing audio!: ' .. bgms[-2].audio, 3)
                print("Attempted to load filed audio file, but couldn't find it on the system: " .. bgms[-2].audio)
            end
        end
    else
        if audioSpecial then
            audio_stream_stop(audioSpecial)
            audioSpecial = nil
            if audioMain and audioMainPaused then
                audioMainPaused = false
                audio_stream_play(audioMain, false, bgms[curMap].volume)
            else
                set_background_music(0, audioCurSeq, 10)
            end
        end
    end

    if audioMain then
        audio_stream_set_volume(audioMain, is_game_paused() and bgms[curMap].volume/3.5 or bgms[curMap].volume)

        local curPosition = audio_stream_get_position(audioMain)
        if curPosition >= bgms[curMap].loopEnd then
            local minus = bgms[curMap].loopStart - bgms[curMap].loopEnd
            audio_stream_set_position(audioMain, curPosition - math.abs(minus))
        end
    end
    if audioSpecial then
        local curPosition = audio_stream_get_position(audioSpecial)
        if curPosition >= bgms[-2].loopEnd then
            local minus = bgms[-2].loopStart - bgms[-2].loopEnd
            audio_stream_set_position(audioSpecial, curPosition - math.abs(minus))
        end
    end
end

function hud_render()
    if pauseMenuShouldShowMusic and is_game_paused() then
        djui_hud_set_resolution(RESOLUTION_DJUI)
        djui_hud_set_font(FONT_NORMAL)
        local screenWidth = djui_hud_get_screen_width()
        local screenHeight = djui_hud_get_screen_height()
        local height = 64
        local y = screenHeight - height
        djui_hud_set_color(200,200,200,255)
        local text
        if pauseMenuShowLevelID then
            text = "Level ID: " .. np.currLevelNum
        elseif audioSpecial then
            text = "Music: " .. bgms[-2].name
        elseif audioMain then
            text = "Music: " .. bgms[curMap].name
        end
        djui_hud_print_text(text, 5, y, 1)
    end
end
hook_event(HOOK_ON_HUD_RENDER, hud_render)
hook_event(HOOK_UPDATE, handleMusic)
