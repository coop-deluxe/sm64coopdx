if SM64COOPDX_VERSION == nil then return end

local pauseMenuShouldShowMusic = true
local pauseMenuMusicRGBA = {200,200,200,255}
local pauseMenuShowLevelID = false
local curMap = -1
local audioMainPaused = false
local audioMain = nil --Used for the main audio
local audioSpecial = nil --Used for things like cap music
local audioCurSeq = nil
local bgms = {
	[56] =         {audio='rainbow.ogg', loopEnd = 218.781, loopStart = 06.975, volume = -5, name="Ric Fellini - All my Loving"}, --B1
	-- [57] =         {audio='space.ogg', loopEnd = 300, loopStart = 06.975, volume = -5, name="Echo the Dolphin - Title Screen"}, --B1
}

-- disable cap music
function music()
    local np = gNetworkPlayers[0]
    if np.currLevelNum == LEVEL_ARENA_RAINBOW or LEVEL_ARENA_SPACE then
        stop_cap_music()
    end
end

hook_event(HOOK_UPDATE, music)

function handleMusic()
	------------------------------------------------------
    --          Handle stopping/starting of music       --
	------------------------------------------------------
	--Handle main course music
    if (curMap ~= gNetworkPlayers[0].currLevelNum and gMarioStates[0].area.macroObjects ~= nil) then
        curMap = gNetworkPlayers[0].currLevelNum
		audioCurSeq = get_current_background_music()
        if (audioMain ~= nil) then
            audio_stream_stop(audioMain)
            audio_stream_destroy(audioMain)
            audioMain = nil
        end
        if (bgms[curMap] ~= nil and bgms[curMap].audio ~= nil) then 
            set_background_music(0,0,0)
            audioMain = audio_stream_load(bgms[curMap].audio)
            if (audioMain ~= nil) then
                audio_stream_set_looping(audioMain, true)
                audio_stream_play(audioMain, true, bgms[curMap].volume);
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
	if (gMarioStates[0].capTimer > 0 and bgms[-2] ~= nil) then
		--Handle pausing main streamed music, if applicable.
		if (audioMain ~= nil and audioMainPaused == false) then
			audioMainPaused = true
			audio_stream_pause(audioMain)
		end
		--Start up cap music if it's defined.
		if (audioSpecial == nil) then
            set_background_music(0,0,0)
			stop_cap_music()
			audioSpecial = audio_stream_load(bgms[-2].audio)
			if (audioSpecial ~= nil) then
				audio_stream_set_looping(audioSpecial, true)
				audio_stream_play(audioSpecial, true, bgms[-2].volume)
				print("Playing cap audio " .. bgms[-2].name)
			else
				djui_popup_create('Missing audio!: ' .. bgms[-2].audio, 3)
                print("Attempted to load filed audio file, but couldn't find it on the system: " .. bgms[-2].audio)
			end
		end	
	else
		if (audioSpecial ~= nil) then
			audio_stream_stop(audioSpecial)
			audio_stream_destroy(audioSpecial)
			audioSpecial = nil
			if (audioMain ~= nil and audioMainPaused == true) then
				audioMainPaused = false
				audio_stream_play(audioMain, false, bgms[curMap].volume)
			else
				set_background_music(0, audioCurSeq, 10) 
			
			end
		end
	end
	
    if (audioMain ~= nil) then 
		local curPosition = audio_stream_get_position(audioMain)
		if (curPosition >= bgms[curMap].loopEnd ) then
			local minus = bgms[curMap].loopStart - bgms[curMap].loopEnd
			audio_stream_set_position(audioMain, curPosition - math.abs(minus))
		end
    end
	if (audioSpecial ~= nil) then
		local curPosition = audio_stream_get_position(audioSpecial)
		if (curPosition >= bgms[-2].loopEnd) then
			local minus = bgms[-2].loopStart - bgms[-2].loopEnd
			audio_stream_set_position(audioSpecial, curPosition - math.abs(minus))
		end
	end
end

function hud_render()
    if (pauseMenuShouldShowMusic == true and is_game_paused()) then
        djui_hud_set_resolution(RESOLUTION_DJUI);
        djui_hud_set_font(FONT_NORMAL);
        local screenWidth = djui_hud_get_screen_width()
		local screenHeight = djui_hud_get_screen_height()
        local height = 64
        local y = screenHeight - height
        djui_hud_set_color(pauseMenuMusicRGBA[1], pauseMenuMusicRGBA[2], pauseMenuMusicRGBA[3], pauseMenuMusicRGBA[4]);		
		local text = "";
		if (pauseMenuShowLevelID == true) then
			text = "Level ID: " .. gNetworkPlayers[0].currLevelNum
		elseif (audioSpecial ~= nil) then
			text = "Music: " .. bgms[-2].name
		elseif (audioMain ~= nil) then
			text = "Music: " .. bgms[curMap].name
		end
		djui_hud_print_text(text, 5, y, 1);
    end
end
hook_event(HOOK_ON_HUD_RENDER, hud_render)
hook_event(HOOK_UPDATE, handleMusic)