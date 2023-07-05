-- name: Personal Star Counter EX+
-- description: See how many stars you've collected!\n\nCredits:\n\\#097419\\Mr.Needlemouse\\#FFFFFF\\ - Concept\nSunk\\#dcdcdc\\ - Creator\n\\#269A91\\Demnyx\\#dcdcdc\\ - Assistance\n\\#f296af\\PeachyPeach\\#dcdcdc\\ - Global functions
-- incompatible: gamemode arena

for i = 0, (MAX_PLAYERS - 1) do
	gPlayerSyncTable[i].psc = 0
end

if mod_storage_load("StarCounter") == nil then
	mod_storage_save("StarCounter", "0")
end

local starCheater = false
local TotalStarCounter = tonumber(mod_storage_load("StarCounter"))
local StarCounter = 0
local prevNumStars = 0
local screenHeight = 0
local screenWidth = 0
local pscToggle = 1
local introTimer = 0

-- junk --
cutscenes = {
	[ACT_END_PEACH_CUTSCENE] = true,
	[ACT_CREDITS_CUTSCENE] = true,
	[ACT_END_WAVING_CUTSCENE] = true,
}

---@param m MarioState
--Increments an independent counter if a star is collected.
function localStarCounter(m, o, type)
	if (m.playerIndex == 0) and (type == INTERACT_STAR_OR_KEY) then
		--This ensures that it increments ONLY if a star is collected.
		if get_id_from_behavior(o.behavior) ~= id_bhvBowserKey then
			--The hook happens after the star count increments, so this allows the independent counter to increment ONLY when YELLOW star is collected.
			if m.numStars ~= prevNumStars then
				StarCounter = StarCounter + 1
				gPlayerSyncTable[0].psc = StarCounter
				if starCheater == false then --Only if not cheating
					TotalStarCounter = TotalStarCounter + 1
					mod_storage_save("StarCounter", tostring(TotalStarCounter))
				end
			end
		end
	end
end

-- Hud alpha stuff from Agent X
function djui_hud_set_adjusted_color(r, g, b, a)
	local multiplier = 1
	if djui_hud_is_pause_menu_created() then multiplier = 0.57 end --Star Display compatibility
	djui_hud_set_color(r * multiplier, g * multiplier, b * multiplier, a)
end

local function displayStarCounter()
	local m = gMarioStates[0]
	if pscToggle == 0 then return end
	if obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then
        return
	end

    --Make HUD appear when the real one does during the intro
    if m.action == ACT_INTRO_CUTSCENE then
        if introTimer ~= 1195 then
            introTimer = introTimer + 1
        end
    end

	djui_hud_set_resolution(RESOLUTION_N64)
	djui_hud_set_font(FONT_HUD)
    --Draw over credits fades
    if cutscenes[m.action] ~= true then
        djui_hud_set_render_behind_hud(true)
    else
        djui_hud_set_render_behind_hud(false)
    end

	--I don't want to put this in a seperate function, there's not enough code for it to be worth it.
	if m.playerIndex == 0 then
		prevNumStars = m.numStars
	else
		return
	end

	screenHeight = djui_hud_get_screen_height()
	screenWidth = djui_hud_get_screen_width()

	if a == nil then a = 255 end

	local timerValFrames = hud_get_value(HUD_DISPLAY_TIMER)
	local timerX = 0
	local timerY = 0

	-- Move HUD graphics away from the TIMER HUD
	if timerValFrames ~= 0 then
		timerX = 60
		timerY = 17
	end

	--Normal vanilla star counter (The fake real one)
	--Yes Im hiding the hardcoded one because alignment is a pain lmao
	if cutscenes[m.action] ~= true then
        if introTimer >= 1195
        or m.action ~= ACT_INTRO_CUTSCENE then
            if m.numStars >= 100 then
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(tostring(m.numStars), screenWidth - 60, screenHeight - 225, 1)
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_render_texture(gTextures.star, screenWidth - 76, screenHeight - 225, 1, 1.)
            else
                djui_hud_set_adjusted_color(246, 246, 246, a)
                djui_hud_print_text("X", screenWidth - 60, screenHeight - 225, 1)
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(tostring(m.numStars), screenWidth - 46, screenHeight - 225, 1)
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_render_texture(gTextures.star, screenWidth - 76, screenHeight - 225, 1, 1)
            end
        end
    end

	--Normal personal star counter (The red one)
    if cutscenes[m.action] == true then
        if StarCounter >= 100 then
            djui_hud_set_adjusted_color(255, 255, 255, a)
            djui_hud_print_text(tostring(StarCounter), screenWidth%2 + 38, screenHeight - 235, 1)
            djui_hud_set_adjusted_color(232, 17, 35, a)
            djui_hud_render_texture(gTextures.star, screenWidth%2 + 22, screenHeight - 235, 1, 1)
        else
            djui_hud_set_adjusted_color(246, 246, 246, a)
            djui_hud_print_text(tostring("X"), screenWidth%2 + 38, screenHeight - 235, 1)
            djui_hud_set_adjusted_color(255, 255, 255, a)
            djui_hud_print_text(tostring(StarCounter), screenWidth%2 + 54, screenHeight - 235, 1)
            djui_hud_set_adjusted_color(232, 17, 35, a)
            djui_hud_render_texture(gTextures.star, screenWidth%2 + 22, screenHeight - 235, 1, 1)
        end
    else
        if introTimer >= 1195
        or m.action ~= ACT_INTRO_CUTSCENE then
            if StarCounter >= 100 then
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(tostring(StarCounter), screenWidth - 60 - timerX, screenHeight - 208 - timerY, 1)
                djui_hud_set_adjusted_color(232, 17, 35, a)
                djui_hud_render_texture(gTextures.star, screenWidth - 76 - timerX, screenHeight - 208 - timerY, 1, 1)
            else
                djui_hud_set_adjusted_color(246, 246, 246, a)
                djui_hud_print_text(tostring("X"), screenWidth - 60 - timerX, screenHeight - 208 - timerY, 1)
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(tostring(StarCounter), screenWidth - 46 - timerX, screenHeight - 208 - timerY, 1)
                djui_hud_set_adjusted_color(232, 17, 35, a)
                djui_hud_render_texture(gTextures.star, screenWidth - 76 - timerX, screenHeight - 208 - timerY, 1, 1)
            end
        end
    end
	--Total star counter (The green one)
	if timerValFrames ~= 0 then
		timerX = 0
		timerY = -10
	end

	local perceived_total_counter = TotalStarCounter
	local milestone_counter = 0
	while perceived_total_counter >= 10000 do
		perceived_total_counter = perceived_total_counter - 10000
		milestone_counter = milestone_counter + 1
	end

    if cutscenes[m.action] == true then
        if perceived_total_counter >= 100 then
            djui_hud_set_adjusted_color(255, 255, 255, a)
            djui_hud_print_text(tostring(perceived_total_counter), screenWidth - 60, screenHeight - 235, 1)
            djui_hud_set_adjusted_color(50, 176, 40, a)
            djui_hud_render_texture(gTextures.star, screenWidth - 76, screenHeight - 235, 1, 1)
            if milestone_counter ~= 0 then
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(string.format("x%d", milestone_counter), screenWidth - 76, screenHeight - 235, 0.5)
            end
        else
            djui_hud_set_adjusted_color(246, 246, 246, a)
            djui_hud_print_text(tostring("X"), screenWidth - 60, screenHeight - 235, 1)
            djui_hud_set_adjusted_color(255, 255, 255, a)
            djui_hud_print_text(tostring(perceived_total_counter), screenWidth - 46, screenHeight - 235, 1)
            djui_hud_set_adjusted_color(50, 176, 40, a)
            djui_hud_render_texture(gTextures.star, screenWidth - 76, screenHeight - 235, 1, 1)
            if milestone_counter ~= 0 then
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(string.format("x%d", milestone_counter), screenWidth - 76, screenHeight - 235, 0.5)
            end
        end
    else
        if introTimer >= 1195
        or m.action ~= ACT_INTRO_CUTSCENE then
            if perceived_total_counter >= 100 then
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(tostring(perceived_total_counter), screenWidth - 60 - timerX, screenHeight - 190 - timerY, 1)
                djui_hud_set_adjusted_color(50, 176, 40, a)
                djui_hud_render_texture(gTextures.star, screenWidth - 76 - timerX, screenHeight - 190 - timerY, 1, 1)
                if milestone_counter ~= 0 then
                    djui_hud_set_adjusted_color(255, 255, 255, a)
                    djui_hud_print_text(string.format("x%d", milestone_counter), screenWidth - 76 - timerX, screenHeight - 174 - timerY, 0.5)
                end
            else
                djui_hud_set_adjusted_color(246, 246, 246, a)
                djui_hud_print_text(tostring("X"), screenWidth - 60 - timerX, screenHeight - 190 - timerY, 1)
                djui_hud_set_adjusted_color(255, 255, 255, a)
                djui_hud_print_text(tostring(perceived_total_counter), screenWidth - 46 - timerX, screenHeight - 190 - timerY, 1)
                djui_hud_set_adjusted_color(50, 176, 40, a)
                djui_hud_render_texture(gTextures.star, screenWidth - 76 - timerX, screenHeight - 190 - timerY, 1, 1)
                if milestone_counter ~= 0 then
                    djui_hud_set_adjusted_color(255, 255, 255, a)
                    djui_hud_print_text(string.format("x%d", milestone_counter), screenWidth - 76 - timerX, screenHeight - 174 - timerY, 0.5)
                end
            end
        end
    end
end

--Turn server cheats off, silly!
--Will be updated immediately when individual cheats get flags.
function cheaterStar()
	if starCheater == true then return end
	if gServerSettings.enableCheats ~= 0 then
		djui_popup_create("This server has cheats enabled.\n\\#31AF28\\Total Star Count\\#FFFFFF\\ will not change.", 2)
		play_sound_button_change_blocked()
		starCheater = true
	else
		starCheater = false
	end
end

--See how many stars everyone gets!
function updatePSC(m)
	gPlayerSyncTable[0].psc = StarCounter
end

--No star text icon yet, also the text gets removed after the second color change?
function update()
	for i = 0, (MAX_PLAYERS - 1) do
		gPlayerSyncTable[i].psc = gPlayerSyncTable[i].psc
		network_player_set_description(gNetworkPlayers[i], "\\#FF0000\\".."Stars"..--[[ "\\#FFFFFF\\".. ]]": " ..tostring(gPlayerSyncTable[i].psc), 255, 255, 255, 255)
	end
end

function pscToggle(msg)
	if msg == string.lower("On") or msg == "1" then
		pscToggle = 1
        hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_STAR_COUNT)
		return true
	elseif msg == string.lower("Off") or msg == "0" then
		pscToggle = 0
        hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) | HUD_DISPLAY_FLAG_STAR_COUNT)
		return true
	end
end

---------
--Hooks--
---------
hook_event(HOOK_ON_INTERACT, localStarCounter)
hook_event(HOOK_ON_HUD_RENDER, displayStarCounter)
hook_event(HOOK_ON_LEVEL_INIT, cheaterStar)
hook_event(HOOK_UPDATE, update)
hook_event(HOOK_UPDATE, updatePSC)
hook_chat_command('psc', "On|Off - Displays stars you've collected. Default is On.", pscToggle)

--Global functions for everyone to use!
--Thank you, PeachyPeach!
_G.PersonalStarCounter = {
	get_star_counter = function ()
		return StarCounter
	end,

	get_total_star_counter = function ()
		return TotalStarCounter
	end,

	hide_star_counters = function (hide)
		if hide then pscToggle = 0 else pscToggle = 1 end
	end,
}