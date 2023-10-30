-- name: Personal Star Counter
-- description: See how many stars you've collected!\n\nCredits:\n\\#097419\\Mr.Needlemouse\\#FFFFFF\\ - Concept\nSunk\\#dcdcdc\\ - Creator\n\\#269A91\\Demnyx\\#dcdcdc\\ - Assistance\n\\#f296af\\PeachyPeach\\#dcdcdc\\ - Global functions
-- incompatible: gamemode arena

------------------------------
----- Localize functions -----
------------------------------
-- This looks strange but it makes the mod more performant
local tonumber, mod_storage_load, mod_storage_save, tostring, djui_hud_is_pause_menu_created, djui_hud_set_color, hud_get_value, djui_hud_print_text, djui_hud_render_texture, obj_get_first_with_behavior_id, djui_hud_set_resolution, djui_hud_set_font, djui_hud_get_screen_height, djui_hud_get_screen_width, djui_hud_set_render_behind_hud, hud_set_value, network_player_set_description, djui_popup_create = 
    tonumber, mod_storage_load, mod_storage_save, tostring, djui_hud_is_pause_menu_created, djui_hud_set_color, hud_get_value, djui_hud_print_text, djui_hud_render_texture, obj_get_first_with_behavior_id, djui_hud_set_resolution, djui_hud_set_font, djui_hud_get_screen_height, djui_hud_get_screen_width, djui_hud_set_render_behind_hud, hud_set_value, network_player_set_description, djui_popup_create
------------------------------

-- Initialize a value for the psc for everyone
for i = 0, MAX_PLAYERS - 1 do
	gPlayerSyncTable[i].psc = 0
end

local psc_toggle = true
local has_cheats_enabled = gServerSettings.enableCheats ~= 0

-- If there is no value in storage, default to 0
local TotalStarCounter = tonumber(mod_storage_load("StarCounter")) or 0
local ThisGameStarCounter = 0
local prevNumStars = 0

local introTimer = 0

-- When in these cutscenes, do special things like hiding or moving the star counters
local is_in_cutscenes = {
	[ACT_END_PEACH_CUTSCENE] = true,
	[ACT_CREDITS_CUTSCENE] = true,
	[ACT_END_WAVING_CUTSCENE] = true,
}

--- Whenever a star is collected, increment the other star counters
---@param m MarioState The Mario that does the interaction
---@param obj Object The object the Mario interacted with (Unused here)
---@param intType integer The interaction type
---@param interacted boolean If the interaction was successful (Unused here)
---@return nil
local function star_counter_on_interact(m, obj, intType, interacted)
    if not psc_toggle then return end

	if m.playerIndex == 0 and intType == INTERACT_STAR_OR_KEY then
        -- Interactions happen before hud rendering, which is why this check can work
        -- despite prevNumStars being updated every frame
        if m.numStars ~= prevNumStars then
            ThisGameStarCounter = ThisGameStarCounter + 1 -- Red star counter
            -- Disable total star counter if cheats are enabled
            if not has_cheats_enabled then
                TotalStarCounter = TotalStarCounter + 1 -- Green star counter
                mod_storage_save("StarCounter", tostring(TotalStarCounter)) -- Save to mod storage
            end
        end
	end
end

--- Hud alpha stuff from Agent X
--- Causes the hud to darken when the game is paused
---@param r number Red
---@param g number Green
---@param b number Blue
---@param a number Alpha (Transparency)
---@return nil
local function djui_hud_set_adjusted_color(r, g, b, a)
	local multiplier = 1
	if djui_hud_is_pause_menu_created() then multiplier = 0.57 end -- Star Display compatibility
	djui_hud_set_color(r * multiplier, g * multiplier, b * multiplier, a)
end

--- Sets the star counters onto the hud
---@param m MarioState Mario
---@param height number Screen height (Unused)
---@param width number Screen width
---@return nil
local function set_hud_star_positions(m, height, width)
    if introTimer >= 1195 or m.action ~= ACT_INTRO_CUTSCENE then
        local star_texture = gTextures.star
        -- Check if the timer is currently active
        local timer_current_value = hud_get_value(HUD_DISPLAY_TIMER)

        -- Offset based on if the timer is active
        local timer_offset_X = 0
        local timer_offset_Y = 0

        -- Offset based on if each counter has less than 100 stars
        local low_stars_offset_X = 0
        local low_stars_offset_Y = 0

        -- Based off of star texture pos
        local star_counter_offset_X = 0

        -- Y position, based off of the top of the screen
        local top_screen_offset_Y = 0

        -------------------------------
        ----- Yellow star counter -----
        -------------------------------

        -- Don't display while in a cutscene
        if not is_in_cutscenes[m.action] then
            star_counter_offset_X = 76
            top_screen_offset_Y = 15

            low_stars_offset_X = 14

            offsetX = 14
            if m.numStars < 100 then
                djui_hud_set_adjusted_color(246, 246, 246, 255)
                djui_hud_print_text("@", width - (star_counter_offset_X - 16), top_screen_offset_Y, 1)
                offsetX = 0
            end
            djui_hud_set_adjusted_color(255, 255, 255, 255)
            djui_hud_print_text(tostring(m.numStars), width - (star_counter_offset_X - 30) - offsetX, top_screen_offset_Y, 1)
            djui_hud_render_texture(star_texture, width - star_counter_offset_X, top_screen_offset_Y, 1, 1)
        end

        ----------------------------
        ----- Red star counter -----
        ----------------------------

        -- Move HUD graphics away from the TIMER HUD
        if timer_current_value ~= 0 then
            timer_offset_X = 60
            timer_offset_Y = 17
        end

        star_counter_offset_X = is_in_cutscenes[m.action] and 22 or 76
        top_screen_offset_Y = is_in_cutscenes[m.action] and 15 or 15 + 17

        low_stars_offset_X = 14

        local left_align = is_in_cutscenes[m.action]
        -- Render X if this counter has less than 100 stars
        if ThisGameStarCounter < 100 then
            djui_hud_set_adjusted_color(246, 246, 246, 255)
            djui_hud_print_text(
                "@", -- Text
                (left_align and (star_counter_offset_X + 16) or -- X pos in cutscenes
                    (width - (star_counter_offset_X - 16) - timer_offset_X)), -- X pos outside cutscenes
                top_screen_offset_Y + timer_offset_Y, -- Y pos
                1) -- Scale
            low_stars_offset_X = 0
        end
        -- Render counter
        djui_hud_set_adjusted_color(255, 255, 255, 255)
        djui_hud_print_text(
            tostring(ThisGameStarCounter), -- Text
            (left_align and (star_counter_offset_X + 30 - low_stars_offset_X) or -- X pos in cutscenes
                (width - (star_counter_offset_X - 30) - timer_offset_X - low_stars_offset_X)), -- X pos outside cutscenes
            top_screen_offset_Y + timer_offset_Y, -- Y pos
            1) -- Scale
        djui_hud_set_adjusted_color(232, 17, 35, 255)
        djui_hud_render_texture(
            star_texture, -- Texture
            (left_align and star_counter_offset_X or -- X pos in cutscenes
                (width - star_counter_offset_X - timer_offset_X)), -- X pos outside cutscenes
            top_screen_offset_Y + timer_offset_Y, -- Y pos
            1, 1) -- Scale

        ------------------------------
        ----- Green star counter -----
        ------------------------------

        -- Increment a seperate counter if the total star count is over 10000
        local perceived_total_counter = TotalStarCounter
        local milestone_counter = 0
        while perceived_total_counter >= 10000 do
            perceived_total_counter = perceived_total_counter - 10000
            milestone_counter = milestone_counter + 1
        end

        -- Move HUD graphics away from the TIMER HUD
        if timer_current_value ~= 0 then
            timer_offset_X = 0
            timer_offset_Y = -10
        end

        star_counter_offset_X = 76
        top_screen_offset_Y = is_in_cutscenes[m.action] and 15 or 15 + 17 * 2

        low_stars_offset_X = 14
        -- Render X if this counter has less than 100 stars
        if perceived_total_counter < 100 then
            djui_hud_set_adjusted_color(246, 246, 246, 255)
            djui_hud_print_text(
                "@", -- Text
                width - (star_counter_offset_X - 16) - timer_offset_X, -- X pos
                top_screen_offset_Y + timer_offset_Y, -- Y pos
                1) -- Scale
            low_stars_offset_X = 0
        end
        -- Render counter
        djui_hud_set_adjusted_color(255, 255, 255, 255)
        djui_hud_print_text(
            tostring(perceived_total_counter), -- Text
            width - (star_counter_offset_X - 30) - timer_offset_X - low_stars_offset_X, -- X pos
            top_screen_offset_Y + timer_offset_Y, -- Y pos
            1) -- Scale
        djui_hud_set_adjusted_color(50, 176, 40, 255)
        djui_hud_render_texture(
            star_texture, -- Texture
            width - star_counter_offset_X - timer_offset_X, -- X pos
            top_screen_offset_Y + timer_offset_Y, -- Y pos
            1, 1) -- Scale
        if milestone_counter ~= 0 then
            djui_hud_set_adjusted_color(255, 255, 255, 255)
            djui_hud_print_text(
                "@" .. milestone_counter, -- Text
                width - star_counter_offset_X - timer_offset_X, -- X pos
                (top_screen_offset_Y + 16) + timer_offset_Y, -- Y pos
                0.5) -- Scale
        end
    end
end

--- Renders star counters onto the screen
---@return nil
local function hud_render_psc()
	if not psc_toggle then return end
    -- If the act selector is active
	if obj_get_first_with_behavior_id(id_bhvActSelector) then return end

    -- HOOK_ON_HUD_RENDER doesn't supply a MarioState, so one has to be gotten from this
    ---@type MarioState
    local m = gMarioStates[0]

    -- Make HUD appear when the real one does during the intro
    if m.action == ACT_INTRO_CUTSCENE then
        if introTimer < 1195 then
            introTimer = introTimer + 1
        end
    end

    djui_hud_set_resolution(RESOLUTION_N64)
	djui_hud_set_font(FONT_HUD)

    local screen_height = djui_hud_get_screen_height()
	local screen_width = djui_hud_get_screen_width()

    -- Set prevNumStars
    prevNumStars = m.numStars
    -- Draw over credits fades
    djui_hud_set_render_behind_hud(not is_in_cutscenes[m.action])

    -- Force the normal star counter to be hidden
    hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_STAR_COUNT)

    set_hud_star_positions(m, screen_height, screen_width)
end

--- Display each person's star counter in the player menu
---@return nil
local function psc_update()
    gPlayerSyncTable[0].psc = ThisGameStarCounter
	for i = 0, MAX_PLAYERS - 1 do
		network_player_set_description(gNetworkPlayers[i], "\\#FF0000\\Stars: " .. tostring(gPlayerSyncTable[i].psc), 255, 255, 255, 255)
	end
end

local timer = 0
--- Inform the player that they have joined a game with cheats enabled
--- and won't be able to get any green stars
---@param m MarioState
---@return nil
local function psc_mario_update_inform_cheats(m)
    if m.playerIndex ~= 0 then return end
    if has_cheats_enabled then
        timer = timer + 1
        if timer == 30 then
            djui_popup_create("This game has cheats enabled. You cannot gain any \\#00FF00\\green stars\\#DCDCDC\\ from this game.", 3)
        end
    end
end

--- Toggle whether or not to display the star counter on the hud
---@param msg string
---@return boolean
local function toggle_psc(msg)
	if msg:lower() == "on" then
		psc_toggle = true
	elseif msg:lower() == "off" then
		psc_toggle = false
        hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) | HUD_DISPLAY_FLAG_STAR_COUNT)
	end
    return true
end

-----------------
----- Hooks -----
-----------------

hook_event(HOOK_ON_INTERACT, star_counter_on_interact)
hook_event(HOOK_ON_HUD_RENDER, hud_render_psc)
hook_event(HOOK_UPDATE, psc_update)
hook_event(HOOK_MARIO_UPDATE, psc_mario_update_inform_cheats)
hook_chat_command('psc', "On|Off - Displays stars you've collected. Default is On.", toggle_psc)

-- Globalize functions for other mods to use
-- Created by PeachyPeach
_G.PersonalStarCounter = {
    --- Get the amount of red stars collected
    ---@return integer
	get_star_counter = function ()
		return ThisGameStarCounter
	end,

    --- Get the amount of green stars collected
    ---@return integer
	get_total_star_counter = function ()
		return TotalStarCounter
	end,

    --- Force show or hide the star counters
    ---@param hide boolean
	hide_star_counters = function (hide)
		psc_toggle = hide
	end,

    --- Modify the value of the star counters
    ---@param red_change number How much to change the red (single game) star counter by
    ---@param green_change number How much to change the green (total) star counter by
    ---@param override_set boolean If true, force set the value of the star counters instead of change
    ---@param save boolean If true, save the green star counter to mod storage
    ---@return nil
    change_star_counter_value = function (red_change, green_change, override_set, save)
        ThisGameStarCounter = ThisGameStarCounter + red_change
        if override_set then
            ThisGameStarCounter = red_change
        end
        TotalStarCounter = TotalStarCounter + green_change
        if override_set then
            TotalStarCounter = green_change
        end
        if save then
            mod_storage_save("StarCounter", tostring(TotalStarCounter))
        end
    end
}