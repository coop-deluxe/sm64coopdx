-- name: Day Night Cycle DX
-- incompatible: light day-night-cycle
-- description: Day Night Cycle DX v2.4\nBy \\#ec7731\\Agent X\n\n\\#dcdcdc\\This mod adds a fully featured day & night cycle system with night, sunrise, day and sunset to sm64coopdx. It includes an API and hook system for interfacing with several components of the mod externally. This mod was originally made for sm64ex-coop but has been practically rewritten for sm64coopdx.\n\nDays last 24 minutes and with the /time command, you can get/set the time or change your settings.\n\nThere is also now a new menu in the pause menu for Day Night Cycle DX!\n\nSpecial thanks to \\#e06de4\\MaiskX3\\#dcdcdc\\ for the night time music.\nSpecial thanks to \\#00ffff\\AngelicMiracles\\#dcdcdc\\ for the sunset, sunrise and night time skyboxes.\nSpecial thanks to \\#344ee1\\eros71\\#dcdcdc\\ for salvaging\nthe mod files.

--- @class Vec2f
--- @field public x number
--- @field public y number

gGlobalSyncTable.dncEnabled = true
gGlobalSyncTable.time = if_then_else(network_is_server(), load_time(), HOUR_DAY_START)
gGlobalSyncTable.timeScale = tonumber(mod_storage_load("scale")) or 1.0
gGlobalSyncTable.sunrise = HOUR_SUNRISE_START
gGlobalSyncTable.sunset = HOUR_SUNSET_START

local init = false
local timeModifier = 0
local displayTime = mod_storage_load_bool_2("display_time")

-- localize functions to improve performance
local math_floor,table_insert,get_skybox,set_lighting_dir,set_lighting_color,set_vertex_color,set_fog_color,set_fog_intensity,network_check_singleplayer_pause,network_player_connected_count,obj_get_first_with_behavior_id,network_is_server,spawn_non_sync_object,obj_scale,clampf,set_lighting_color_ambient,djui_hud_set_resolution,djui_hud_set_font,hud_get_value,hud_is_hidden,djui_hud_get_screen_width,djui_hud_measure_text,djui_hud_get_screen_height,djui_hud_set_color,play_sound,djui_chat_message_create,string_format,mod_storage_save_number,mod_storage_save_bool,get_date_and_time = math.floor,table.insert,get_skybox,set_lighting_dir,set_lighting_color,set_vertex_color,set_fog_color,set_fog_intensity,network_check_singleplayer_pause,network_player_connected_count,obj_get_first_with_behavior_id,network_is_server,spawn_non_sync_object,obj_scale,clampf,set_lighting_color_ambient,djui_hud_set_resolution,djui_hud_set_font,hud_get_value,hud_is_hidden,djui_hud_get_screen_width,djui_hud_measure_text,djui_hud_get_screen_height,djui_hud_set_color,play_sound,djui_chat_message_create,string.format,mod_storage_save_number,mod_storage_save_bool,get_date_and_time

local sDncHooks = {
    [DNC_HOOK_SET_LIGHTING_COLOR] = {},
    [DNC_HOOK_SET_AMBIENT_LIGHTING_COLOR] = {},
    [DNC_HOOK_SET_LIGHTING_DIR] = {},
    [DNC_HOOK_SET_FOG_COLOR] = {},
    [DNC_HOOK_SET_FOG_INTENSITY] = {},
    [DNC_HOOK_SET_DISPLAY_TIME_COLOR] = {},
    [DNC_HOOK_SET_DISPLAY_TIME_POS] = {},
    [DNC_HOOK_DELETE_AT_DARK] = {},
    [DNC_HOOK_SET_TIME] = {},
    [DNC_HOOK_SET_SKYBOX_MODEL] = {},
    [DNC_HOOK_SUN_TIMES_CHANGED] = {}
}

--- @param hookEventType integer
--- @param func function
--- Hooks a function to the Day Night Cycle hook system
local function dnc_hook_event(hookEventType, func)
    if type(hookEventType) ~= "number" or math_floor(hookEventType) ~= hookEventType then
        error("dnc_hook_event: Parameter 'hookEventType' must be an integer")
        return
    end
    if type(func) ~= "function" then
        error("dnc_hook_event: Parameter 'func' must be a function")
        return
    end

    if sDncHooks[hookEventType] == nil then return end
    table_insert(sDncHooks[hookEventType], func)
end

--- @param hookEventType integer
function dnc_call_hook(hookEventType, ...)
    if sDncHooks[hookEventType] == nil then return end
    local ret = nil
    for hook in ipairs(sDncHooks[hookEventType]) do
        ret = sDncHooks[hookEventType][hook](...)
    end
    return ret
end

--- Returns whether or not Day Night Cycle is globally enabled
function is_dnc_enabled()
    return gGlobalSyncTable.dncEnabled and dayNightCycleApi.enabled
end

--- @param skybox integer
--- Checks if a skybox is always static while still running lighting code
function is_static_skybox(skybox)
    return skybox == BACKGROUND_HAUNTED or skybox == BACKGROUND_PURPLE_SKY
end

--- Returns whether or not the game should visually show the day night cycle
function show_day_night_cycle()
    local skybox = get_skybox()
    return (skybox ~= -1 and
        skybox ~= BACKGROUND_CUSTOM and
        skybox ~= BACKGROUND_FLAMING_SKY and
        skybox ~= BACKGROUND_GREEN_SKY)
        or in_vanilla_level(LEVEL_DDD) or in_vanilla_level(LEVEL_THI) or (in_vanilla_level(LEVEL_CASTLE) and gNetworkPlayers[0].currAreaIndex ~= 3) or in_vanilla_level(LEVEL_WDW)
end

local function reset_lighting()
    set_lighting_dir(1, 0)
    set_lighting_dir(2, 0)
    set_lighting_color(0, 255)
    set_lighting_color(1, 255)
    set_lighting_color(2, 255)
    set_vertex_color(0, 255)
    set_vertex_color(1, 255)
    set_vertex_color(2, 255)
    set_fog_color(0, 255)
    set_fog_color(1, 255)
    set_fog_color(2, 255)
    set_fog_intensity(1)
end

local function update()
    if not is_dnc_enabled() then
        reset_lighting()
        return
    end

    if network_check_singleplayer_pause() then return end
    if network_player_connected_count() == 1 and obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then return end

    if network_is_server() then time_tick() end
    if init then update_night_music() end

    -- spawn skyboxes
    local skybox = get_skybox()
    if skybox >= BACKGROUND_CUSTOM then skybox = BACKGROUND_OCEAN_SKY end
    if not _G.dayNightCycleApi.dddCeiling and in_vanilla_level(LEVEL_DDD) then skybox = BACKGROUND_OCEAN_SKY end
    if obj_get_first_with_behavior_id(bhvDNCSkybox) == nil and skybox ~= -1 and obj_get_first_with_behavior_id(bhvDNCNoSkybox) == nil then
        if show_day_night_cycle() and not is_static_skybox(skybox) then
            -- spawn day, sunset and night skyboxes
            for i = SKYBOX_DAY, SKYBOX_NIGHT do
                local thisSkybox = skybox
                if i == SKYBOX_SUNSET then
                    thisSkybox = if_then_else(skybox == BACKGROUND_BELOW_CLOUDS, BACKGROUND_BELOW_CLOUDS_SUNSET, BACKGROUND_SUNSET)
                elseif i == SKYBOX_NIGHT then
                    thisSkybox = if_then_else(skybox == BACKGROUND_BELOW_CLOUDS, BACKGROUND_BELOW_CLOUDS_NIGHT, BACKGROUND_NIGHT)
                end

                local model = E_MODEL_DNC_SKYBOX
                local overrideModel = dnc_call_hook(DNC_HOOK_SET_SKYBOX_MODEL, i, thisSkybox)
                if overrideModel ~= nil and type(overrideModel) == "number" then model = overrideModel end

                spawn_non_sync_object(
                    bhvDNCSkybox,
                    model,
                    0, 0, 0,
                    --- @param o Object
                    function(o)
                        o.oBehParams2ndByte = i
                        o.oAnimState = thisSkybox
                        obj_scale(o, SKYBOX_SCALE - 10 * i)
                    end
                )
            end
        else
            -- spawn static skybox
            spawn_non_sync_object(
                bhvDNCSkybox,
                E_MODEL_DNC_SKYBOX,
                0, 0, 0,
                --- @param o Object
                function(o)
                    o.oBehParams2ndByte = 0
                    o.oAnimState = skybox
                    obj_scale(o, SKYBOX_SCALE)
                end
            )
        end
    end

    local minutes = if_then_else(is_static_skybox(skybox), 12, get_time_minutes())

    local actSelector = obj_get_first_with_behavior_id(id_bhvActSelector)
    if actSelector == nil and show_day_night_cycle() then
        -- calculate lighting color
        local color = COLOR_DAY
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            color = color_lerp(COLOR_NIGHT, COLOR_SUNRISE, (minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION)
        elseif minutes >= HOUR_SUNRISE_END and minutes <= HOUR_DAY_START then
            color = color_lerp(COLOR_SUNRISE, COLOR_DAY, (minutes - HOUR_SUNRISE_END) / HOUR_SUNRISE_DURATION)
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_SUNSET_END then
            color = color_lerp(COLOR_DAY, COLOR_SUNSET, (minutes - HOUR_SUNSET_START) / HOUR_SUNSET_DURATION)
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            color = color_lerp(COLOR_SUNSET, COLOR_NIGHT, (minutes - HOUR_SUNSET_END) / HOUR_SUNSET_DURATION)
        elseif minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_START then
            color = COLOR_NIGHT
        elseif minutes > HOUR_DAY_START and minutes < HOUR_SUNSET_START then
            color = COLOR_DAY
        end
        local overrideColor = dnc_call_hook(DNC_HOOK_SET_LIGHTING_COLOR, table_clone(color))
        if overrideColor ~= nil and type(overrideColor) == "table" then color = overrideColor end

        -- calculate ambient lighting color
        local ambientColor = COLOR_AMBIENT_DAY
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            ambientColor = color_lerp(COLOR_AMBIENT_NIGHT, COLOR_AMBIENT_SUNRISE, (minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION)
        elseif minutes >= HOUR_SUNRISE_END and minutes <= HOUR_DAY_START then
            ambientColor = color_lerp(COLOR_AMBIENT_SUNRISE, COLOR_AMBIENT_DAY, (minutes - HOUR_SUNRISE_END) / HOUR_SUNRISE_DURATION)
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_SUNSET_END then
            ambientColor = color_lerp(COLOR_AMBIENT_DAY, COLOR_AMBIENT_SUNSET, (minutes - HOUR_SUNSET_START) / HOUR_SUNSET_DURATION)
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            ambientColor = color_lerp(COLOR_AMBIENT_SUNSET, COLOR_AMBIENT_NIGHT, (minutes - HOUR_SUNSET_END) / HOUR_SUNSET_DURATION)
        elseif minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_START then
            ambientColor = COLOR_AMBIENT_NIGHT
        elseif minutes > HOUR_DAY_START and minutes < HOUR_SUNSET_START then
            ambientColor = COLOR_AMBIENT_DAY
        end
        local overrideAmbientColor = dnc_call_hook(DNC_HOOK_SET_AMBIENT_LIGHTING_COLOR, table_clone(ambientColor))
        if overrideAmbientColor ~= nil and type(overrideColor) == "table" then ambientColor = overrideAmbientColor end

        -- calculate fog color
        local fogColor = COLOR_DAY
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            fogColor = color_lerp(FOG_COLOR_NIGHT, COLOR_SUNRISE, (minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION)
        elseif minutes >= HOUR_SUNRISE_END and minutes <= HOUR_DAY_START then
            fogColor = color_lerp(COLOR_SUNRISE, COLOR_DAY, (minutes - HOUR_SUNRISE_END) / HOUR_SUNRISE_DURATION)
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_SUNSET_END then
            fogColor = color_lerp(COLOR_DAY, COLOR_SUNSET, (minutes - HOUR_SUNSET_START) / HOUR_SUNSET_DURATION)
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            fogColor = color_lerp(COLOR_SUNSET, FOG_COLOR_NIGHT, (minutes - HOUR_SUNSET_END) / HOUR_SUNSET_DURATION)
        elseif minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_START then
            fogColor = FOG_COLOR_NIGHT
        elseif minutes > HOUR_DAY_START and minutes < HOUR_SUNSET_START then
            fogColor = COLOR_DAY
        end
        fogColor = color_lerp(fogColor, ambientColor, 0.5)
        local overrideFogColor = dnc_call_hook(DNC_HOOK_SET_FOG_COLOR, table_clone(fogColor))
        if overrideFogColor ~= nil and type(overrideFogColor) == "table" then fogColor = overrideFogColor end

        -- calculate lighting direction
        local dir = DIR_BRIGHT
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            dir = lerp(DIR_DARK, DIR_BRIGHT, clampf((minutes - HOUR_SUNRISE_START) / (HOUR_SUNRISE_DURATION), 0, 1))
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_NIGHT_START then
            dir = lerp(DIR_BRIGHT, DIR_DARK, clampf((minutes - HOUR_SUNSET_START) / (HOUR_NIGHT_START - HOUR_SUNSET_START), 0, 1))
        elseif minutes < HOUR_SUNRISE_START or minutes > HOUR_NIGHT_START then
            dir = DIR_DARK
        elseif minutes > HOUR_SUNRISE_END and minutes < HOUR_SUNSET_START then
            dir = DIR_BRIGHT
        end
        local overrideDir = dnc_call_hook(DNC_HOOK_SET_LIGHTING_DIR, dir)
        if overrideDir ~= nil and type(overrideDir) == "number" then dir = overrideDir end

        -- calculate fog intensity
        local intensity = FOG_INTENSITY_NORMAL
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            intensity = lerp(FOG_INTENSITY_DENSE, FOG_INTENSITY_NORMAL, clampf((minutes - HOUR_SUNRISE_START) / (HOUR_SUNRISE_DURATION), 0, 1))
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_NIGHT_START then
            intensity = lerp(FOG_INTENSITY_NORMAL, FOG_INTENSITY_DENSE, clampf((minutes - HOUR_SUNSET_START) / (HOUR_NIGHT_START - HOUR_SUNSET_START), 0, 1))
        elseif minutes < HOUR_SUNRISE_START or minutes > HOUR_NIGHT_START then
            intensity = FOG_INTENSITY_DENSE
        elseif minutes > HOUR_SUNRISE_END and minutes < HOUR_SUNSET_START then
            intensity = FOG_INTENSITY_NORMAL
        end
        local overrideIntensity = dnc_call_hook(DNC_HOOK_SET_FOG_INTENSITY, intensity)
        if overrideIntensity ~= nil and type(overrideIntensity) == "number" then intensity = overrideIntensity end

        set_lighting_dir(1, -(1 - dir))
        set_lighting_dir(2, -(1 - dir))
        -- make the castle still 25% ambient lit
        if in_vanilla_level(LEVEL_CASTLE) then
            color = color_lerp(COLOR_DAY, color, 0.75)
        end
        set_lighting_color(0, color.r)
        set_lighting_color(1, color.g)
        set_lighting_color(2, color.b)
        set_lighting_color_ambient(0, ambientColor.r)
        set_lighting_color_ambient(1, ambientColor.g)
        set_lighting_color_ambient(2, ambientColor.b)
        local mix = color_lerp(color, ambientColor, 0.5)
        set_vertex_color(0, mix.r)
        set_vertex_color(1, mix.g)
        set_vertex_color(2, mix.b)
        set_fog_color(0, fogColor.r)
        set_fog_color(1, fogColor.g)
        set_fog_color(2, fogColor.b)
        set_fog_intensity(intensity)

        -- lighting engine compatibility
        if obj_get_first_with_behavior_id(id_bhvAmbientLight) ~= nil then
            mix = color_lerp(color, COLOR_WHITE, 0.5) -- make the color less intense
            le_set_ambient_color(mix.r, mix.g, mix.b)
        end
    else
        reset_lighting()
    end

    init = true
end

local function on_hud_render_behind()
    if not is_dnc_enabled() then return end -- option check
    if not dayNightCycleApi.displayTime or not displayTime then return end -- API checks
    if check_common_hud_render_cancels() then return end -- game checks

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)

    local scale = 0.5
    local text = get_time_string(gGlobalSyncTable.time)

    local hidden = hud_is_hidden() or (hud_get_value(HUD_DISPLAY_FLAGS) & HUD_DISPLAY_FLAG_LIVES) == 0
    local x = if_then_else(hidden, (djui_hud_get_screen_width() * 0.5) - (djui_hud_measure_text(text) * (0.5 * scale)), 24)
    local y = if_then_else(hidden, (djui_hud_get_screen_height() - 20), 32)
    local overridePos = dnc_call_hook(DNC_HOOK_SET_DISPLAY_TIME_POS, { x = x, y = y })
    if overridePos ~= nil and type(overridePos) == "table" then
        x = overridePos.x
        y = overridePos.y
    end

    local color = COLOR_DISPLAY_DARK
    if not is_static_skybox(get_skybox()) then
        local minutes = get_time_minutes()
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            color = color_lerp(COLOR_DISPLAY_DARK, COLOR_DISPLAY_BRIGHT, (minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION)
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            color = color_lerp(COLOR_DISPLAY_BRIGHT, COLOR_DISPLAY_DARK, (minutes - HOUR_SUNSET_END) / HOUR_SUNSET_DURATION)
        elseif minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_START then
            color = COLOR_DISPLAY_DARK
        elseif minutes > HOUR_SUNRISE_END and minutes < HOUR_SUNSET_END then
            color = COLOR_DISPLAY_BRIGHT
        end
    end
    local overrideColor = dnc_call_hook(DNC_HOOK_SET_DISPLAY_TIME_COLOR, table_clone(color))
    if overrideColor ~= nil and type(overrideColor) == "table" then color = overrideColor end
    djui_hud_set_color(color.r, color.g, color.b, 255)

    djui_hud_print_outlined_text(text, x, y, scale, 0.0)
end

local function on_level_init()
    if not is_dnc_enabled() then return end

    playingNightMusic = false

    if gNetworkPlayers[0].currActNum ~= 99 then
        if network_is_server() then
            save_time()
        end
        return
    end

    --- @type NetworkPlayer
    local np = gNetworkPlayers[0]
    if np.currLevelNum == LEVEL_CASTLE_GROUNDS and gMarioStates[0].action ~= ACT_END_WAVING_CUTSCENE then
        set_time_minutes(HOUR_SUNSET_START - 0.7)
        gGlobalSyncTable.timeScale = 1.0
    elseif np.currLevelNum == LEVEL_THI and np.currAreaIndex == 1 then
        set_time_minutes(24 + HOUR_SUNRISE_START)
    end
end

local function on_warp()
    if not is_dnc_enabled() then return end
    if network_is_server() then save_time() end
    playingNightMusic = false
end

local function on_exit()
    if network_is_server() then save_time() end
end


--- @param msg string
local function on_set_command(msg)
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    if msg == "" then
        djui_chat_message_create("/time \\#00ffff\\set\\#ffff00\\ [TIME]\\#dcdcdc\\ to set the time")
        return
    end

    local oldTime = gGlobalSyncTable.time
    if msg == "morning" then
        set_time_minutes(HOUR_DAY_START)
    elseif msg == "day" or msg == "noon" then
        set_time_minutes(12)
    elseif msg == "night" then
        set_time_minutes(HOUR_NIGHT_START)
    elseif msg == "midnight" then
        set_time_minutes(0)
    elseif msg == "sunrise" then
        set_time_minutes(HOUR_SUNRISE_END)
    elseif msg == "sunset" then
        set_time_minutes(HOUR_SUNSET_END)
    else
        local amount = tonumber(msg)
        if amount ~= nil then
            gGlobalSyncTable.time = amount * SECOND
            djui_chat_message_create("[Day Night Cycle] Time set to " .. math_floor(gGlobalSyncTable.time / SECOND))
        else
            djui_chat_message_create(string.format("\\#ffa0a0\\[Day Night Cycle] Could not set time to '%s'", msg))
        end
    end

    dnc_call_hook(DNC_HOOK_SET_TIME, oldTime, gGlobalSyncTable.time)
    save_time()
end

--- @param msg string
local function on_add_command(msg)
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    local amount = tonumber(msg)
    if amount == nil then
        djui_chat_message_create("/time \\#00ffff\\add\\#ffff00\\ [AMOUNT]\\#dcdcdc\\ to add to the time")
        return
    end
    local oldTime = gGlobalSyncTable.time
    gGlobalSyncTable.time = gGlobalSyncTable.time + (amount * SECOND)
    dnc_call_hook(DNC_HOOK_SET_TIME, oldTime, gGlobalSyncTable.time)

    update_mod_menu_element_inputbox(modMenuTimeModifier, msg)

    djui_chat_message_create("[Day Night Cycle] Time set to " .. math_floor(gGlobalSyncTable.time / SECOND))

    save_time()
end

--- @param msg string
local function on_scale_command(msg)
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    local scale = tonumber(msg)
    if scale == nil then
        djui_chat_message_create("/time \\#00ffff\\scale\\#ffff00\\ [SCALE]\\#dcdcdc\\ to scale the rate at which time passes")
        return
    end
    gGlobalSyncTable.timeScale = scale
    mod_storage_save_number("scale", scale)

    update_mod_menu_element_slider(modMenuTimeScale, scale) -- I wonder

    djui_chat_message_create("[Day Night Cycle] Time scale set to " .. scale)

    save_time()
end

local function on_query_command()
    djui_chat_message_create(string.format("[Day Night Cycle] Time is %d (%s), day %d", math_floor(gGlobalSyncTable.time / SECOND), get_time_string(gGlobalSyncTable.time), get_day_count()))
end

local function on_24h_command()
    use24h = not use24h
    mod_storage_save_bool("24h", use24h)

    update_mod_menu_element_checkbox(modMenu24h, use24h)
end

local function on_sync_command()
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    djui_chat_message_create("[Day Night Cycle] Attempting to sync in-game time with real life time...")

    local dateTime = get_date_and_time()
    gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * dateTime.hour) + (SECOND * dateTime.minute)
    gGlobalSyncTable.timeScale = REAL_MINUTE

   save_time()
end

local function on_sync_sun_command()
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    if _G.dayNightCycleApi.lockSunHours then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] Changing sun hours has been locked by another mod.")
        return
    end

    syncSun = not syncSun
    mod_storage_save_bool("sync_sun", syncSun)
    if syncSun then
        djui_chat_message_create("[Day Night Cycle] Syncing sunrise and sunset times to real life...")

        local month = get_date_and_time().month + 1
        set_sun_hours(gSunriseTimes[month], gSunsetTimes[month])
    else
        djui_chat_message_create("[Day Night Cycle] Resetting sunrise and sunset times...")

        set_sun_hours(HOUR_SUNRISE_START_BASE, HOUR_SUNSET_START_BASE)
    end

    update_mod_menu_element_checkbox(modMenuSyncSun, syncSun)
end

local function on_music_command()
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    playNightMusic = not playNightMusic
    mod_storage_save_bool("night_music", playNightMusic)
    djui_chat_message_create("[Day Night Cycle] Night music status: " .. on_or_off(playNightMusic))

    update_mod_menu_element_checkbox(modMenuMusic, playNightMusic)
end

local function on_display_time_command()
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    displayTime = not displayTime
    mod_storage_save_bool("display_time", displayTime)
    djui_chat_message_create("[Day Night Cycle] Display time status: " .. on_or_off(displayTime))

    update_mod_menu_element_checkbox(modMenuDisplayTime, displayTime)
end

--- @param msg string
local function on_time_command(msg)
    local args = split(msg)

    if args[1] == "set" then
        if not network_is_server() then
            djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] You do not have permission to run /time set")
        else
            on_set_command(args[2] or "")
        end
    elseif args[1] == "add" then
        if not network_is_server() then
            djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] You do not have permission to run /time add")
        else
            on_add_command(args[2] or "")
        end
    elseif args[1] == "scale" then
        if not network_is_server() then
            djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] You do not have permission to run /time scale")
        else
            on_scale_command(args[2] or "")
        end
    elseif args[1] == "query" then
        on_query_command()
    elseif args[1] == "24h" then
        on_24h_command()
    elseif args[1] == "sync" then
        if not network_is_server() then
            djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] You do not have permission to run /time sync")
        else
            on_sync_command()
        end
    elseif args[1] == "sync-sun" then
        on_sync_sun_command()
    elseif args[1] == "music" then
        on_music_command()
    elseif args[1] == "display-time" then
        on_display_time_command()
    elseif args[1] ~= "" then
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] Unrecognized command '" .. args[1] .. "'")
    else
        if not network_is_server() then
            djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] You do not have permission to enable or disable Day Night Cycle")
        else
            gGlobalSyncTable.dncEnabled = not gGlobalSyncTable.dncEnabled
            djui_chat_message_create("[Day Night Cycle] Status: " .. on_or_off(gGlobalSyncTable.dncEnabled))
        end
    end

    return true
end


local function on_sunrise_changed(_, _, newVal)
    -- setting constants (variables in all caps) after declaring them goes against my morals but I will make an exception for this
    HOUR_SUNRISE_START = newVal
    HOUR_SUNRISE_END = HOUR_SUNRISE_START + HOUR_SUNRISE_DURATION

    HOUR_DAY_START = HOUR_SUNRISE_END + HOUR_SUNRISE_DURATION

    _G.dayNightCycleApi.constants.HOUR_SUNRISE_START = HOUR_SUNRISE_START
    _G.dayNightCycleApi.constants.HOUR_SUNRISE_END = HOUR_SUNRISE_END
    _G.dayNightCycleApi.constants.HOUR_DAY_START = HOUR_NIGHT_START

    dnc_call_hook(DNC_HOOK_SUN_TIMES_CHANGED)
end

local function on_sunset_changed(_, _, newVal)
    -- setting constants (variables in all caps) after declaring them goes against my morals but I will make an exception for this
    HOUR_SUNSET_START = newVal
    HOUR_SUNSET_END = HOUR_SUNSET_START + HOUR_SUNSET_DURATION

    HOUR_NIGHT_START = HOUR_SUNSET_END + HOUR_SUNSET_DURATION

    _G.dayNightCycleApi.constants.HOUR_SUNSET_START = HOUR_SUNSET_START
    _G.dayNightCycleApi.constants.HOUR_SUNSET_END = HOUR_SUNSET_END
    _G.dayNightCycleApi.constants.HOUR_NIGHT_START = HOUR_NIGHT_START

    dnc_call_hook(DNC_HOOK_SUN_TIMES_CHANGED)
end


--- @param value boolean
local function on_set_dnc_enabled(_, value)
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    gGlobalSyncTable.dncEnabled = value
end

--- @param value integer
local function on_set_time_scale(index, value)
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    gGlobalSyncTable.timeScale = value
    mod_storage_save_number("scale", value)
    update_mod_menu_element_name(index, "Time Scale: " .. value)
end

--- @param value string
local function on_set_time_modifier(_, value)
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    local number = tonumber(value)
    timeModifier = number or 0
end

local function on_add_hour()
    if _G.dayNightCycleApi.lockTime then
        play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
        djui_chat_message_create("\\#ffa0a0\\[Day Night Cycle] The Day Night Cycle settings have been locked by another mod.")
        return
    end

    local oldTime = gGlobalSyncTable.time
    gGlobalSyncTable.time = gGlobalSyncTable.time + timeModifier * SECOND
    dnc_call_hook(DNC_HOOK_SET_TIME, oldTime, gGlobalSyncTable.time)

    save_time()
end

local sReadonlyMetatable = {
    __index = function(table, key)
        return rawget(table, key)
    end,

    __newindex = function()
        error("Attempt to update a read-only table", 2)
    end
}

_G.dayNightCycleApi = {
    version = DNC_VERSION, -- The version of the mod
    enabled = true, -- Whether or not the day night cycle is enabled
    lockTime = false, -- Whether or not the player should be prevented from changing the time
    lockSunHours = false, -- Whether or not the player should be prevented from changing the sun hours
    displayTime = true, -- Whether or not to display the time on the HUD
    playNightMusic = true, -- Whether or not to play the night time music
    dddCeiling = true, -- Whether or not to show the sky in vanilla Dire, Dire Docks area 2
    is_dnc_enabled = is_dnc_enabled,
    get_day_count = get_day_count,
    get_raw_time = get_raw_time,
    set_raw_time = set_raw_time,
    get_time_minutes = get_time_minutes,
    set_time_minutes = set_time_minutes,
    get_time_scale = get_time_scale,
    set_time_scale = set_time_scale,
    get_time_string = get_time_string,
    set_sun_hours = set_sun_hours,
    delete_at_dark = delete_at_dark,
    is_static_skybox = is_static_skybox,
    show_day_night_cycle = show_day_night_cycle,
    should_play_night_music = should_play_night_music,
    night_music_register = night_music_register,
    dnc_hook_event = dnc_hook_event,
    constants = {
        DNC_VERSION_MAJOR = DNC_VERSION_MAJOR,
        DNC_VERSION_MINOR = DNC_VERSION_MINOR,
        DNC_VERSION_PATCH = DNC_VERSION_PATCH,
        DNC_VERSION = DNC_VERSION,

        SECOND = SECOND,
        MINUTE = MINUTE,

        HOUR_SUNRISE_START = HOUR_SUNRISE_START,
        HOUR_SUNRISE_END = HOUR_SUNRISE_END,
        HOUR_SUNRISE_DURATION = HOUR_SUNRISE_DURATION,

        HOUR_SUNSET_START = HOUR_SUNSET_START,
        HOUR_SUNSET_END = HOUR_SUNSET_END,
        HOUR_SUNSET_DURATION = HOUR_SUNSET_DURATION,

        HOUR_DAY_START = HOUR_DAY_START,
        HOUR_NIGHT_START = HOUR_NIGHT_START,

        DIR_DARK = DIR_DARK,
        DIR_BRIGHT = DIR_BRIGHT,

        FOG_INTENSITY_NORMAL = FOG_INTENSITY_NORMAL,
        FOG_INTENSITY_DENSE = FOG_INTENSITY_DENSE,

        COLOR_NIGHT = COLOR_NIGHT,
        COLOR_AMBIENT_NIGHT = COLOR_AMBIENT_NIGHT,
        COLOR_SUNRISE = COLOR_SUNRISE,
        COLOR_AMBIENT_SUNRISE = COLOR_AMBIENT_SUNRISE,
        COLOR_DAY = COLOR_DAY,
        COLOR_AMBIENT_DAY = COLOR_AMBIENT_DAY,
        COLOR_SUNSET = COLOR_SUNSET,
        COLOR_AMBIENT_SUNSET = COLOR_AMBIENT_SUNSET,

        FOG_COLOR_NIGHT = FOG_COLOR_NIGHT,

        COLOR_DISPLAY_DARK = COLOR_DISPLAY_DARK,
        COLOR_DISPLAY_BRIGHT = COLOR_DISPLAY_BRIGHT,

        SKYBOX_SCALE = SKYBOX_SCALE,
        SKYBOX_DAY = SKYBOX_DAY,
        SKYBOX_SUNSET = SKYBOX_SUNSET,
        SKYBOX_NIGHT = SKYBOX_NIGHT,

        -- * Called whenever the lighting color is calculated
        -- * Parameters: `Color` color
        -- * Return: `Color`
        DNC_HOOK_SET_LIGHTING_COLOR = DNC_HOOK_SET_LIGHTING_COLOR,
        -- * Called whenever the ambient lighting color is calculated
        -- * Parameters: `Color` ambientColor
        -- * Return: `Color`
        DNC_HOOK_SET_AMBIENT_LIGHTING_COLOR = DNC_HOOK_SET_AMBIENT_LIGHTING_COLOR,
        -- * Called whenever the lighting direction is calculated
        -- * Parameters: `number` dir
        -- * Return: `number`
        DNC_HOOK_SET_LIGHTING_DIR = DNC_HOOK_SET_LIGHTING_DIR,
        -- * Called whenever the fog color is calculated
        -- * Parameters: `Color` color
        -- * Return: `Color`
        DNC_HOOK_SET_FOG_COLOR = DNC_HOOK_SET_FOG_COLOR,
        -- * Called whenever the fog intensity is calculated
        -- * Parameters: `number` intensity
        -- * Return: `number`
        DNC_HOOK_SET_FOG_INTENSITY = DNC_HOOK_SET_FOG_INTENSITY,
        -- * Called whenever the HUD display time color is calculated
        -- * Parameters: `Color` color
        -- * Return: `Color`
        DNC_HOOK_SET_DISPLAY_TIME_COLOR = DNC_HOOK_SET_DISPLAY_TIME_COLOR,
        -- * Called whenever the HUD display time position is calculated
        -- * Parameters: `Vec2f` pos
        -- * Return: `Vec2f`
        DNC_HOOK_SET_DISPLAY_TIME_POS = DNC_HOOK_SET_DISPLAY_TIME_POS,
        -- * Called whenever `delete_at_dark` is run
        -- * Parameters: `Object` obj, `boolean` shouldDelete
        -- * Return: `boolean`
        DNC_HOOK_DELETE_AT_DARK = DNC_HOOK_DELETE_AT_DARK,
        -- * Called whenever `/time set` or `/time add` is ran
        -- * Parameters: `number` oldTime, `number` newTime
        DNC_HOOK_SET_TIME = DNC_HOOK_SET_TIME,
        -- * Called when the skyboxes are spawned in. Index 0 is day, index 1 is sunset, and index 2 is night.
        -- * Parameters: `integer` index, `integer` skybox
        -- * Return: `ModelExtendedId`
        DNC_HOOK_SET_SKYBOX_MODEL = DNC_HOOK_SET_SKYBOX_MODEL,
        -- * Called when sunrise and sunset times are changed
        DNC_HOOK_SUN_TIMES_CHANGED = DNC_HOOK_SUN_TIMES_CHANGED
    }
}
setmetatable(_G.dayNightCycleApi, sReadonlyMetatable)
setmetatable(_G.dayNightCycleApi.constants, sReadonlyMetatable)

night_music_register(SEQ_LEVEL_GRASS, "night_level_grass")
night_music_register(SEQ_LEVEL_INSIDE_CASTLE, "night_level_inside_castle")
night_music_register(SEQ_LEVEL_WATER, "night_level_water")
night_music_register(SEQ_LEVEL_HOT, "night_level_hot")
night_music_register(SEQ_LEVEL_SNOW, "night_level_snow")
night_music_register(SEQ_LEVEL_SLIDE, "night_level_slide")
night_music_register(SEQ_LEVEL_UNDERGROUND, "night_level_underground")

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_ON_WARP, on_warp)
hook_event(HOOK_ON_EXIT, on_exit)
hook_event(HOOK_ON_HUD_RENDER_BEHIND, on_hud_render_behind)

hook_chat_command("time", "\\#00ffff\\[set|add|scale|query|24h|sync|sync-sun|music|display-time]\\#dcdcdc\\ - The command handle for Day Night Cycle DX \\#7f7f7f\\(leave blank to toggle Day Night Cycle on or off)", on_time_command)

hook_on_sync_table_change(gGlobalSyncTable, "sunrise", 0, on_sunrise_changed)
hook_on_sync_table_change(gGlobalSyncTable, "sunset", 0, on_sunset_changed)

hook_mod_menu_text(string.format("Version %d.%d.%d", DNC_VERSION_MAJOR, DNC_VERSION_MINOR, DNC_VERSION_PATCH))

if network_is_server() then hook_mod_menu_checkbox("Enable Day Night Cycle", gGlobalSyncTable.dncEnabled, on_set_dnc_enabled) end

modMenuDisplayTime = hook_mod_menu_checkbox("Display Time On HUD", displayTime, on_display_time_command)
modMenu24h = hook_mod_menu_checkbox("24 Hour Time", use24h, on_24h_command)
modMenuMusic = hook_mod_menu_checkbox("Night Time Music", playNightMusic, on_music_command)

if network_is_server() then
    modMenuSyncSun = hook_mod_menu_checkbox("Use Real Life Sunrise/Sunset Times", syncSun, on_sync_sun_command)

    modMenuTimeScale = hook_mod_menu_slider("Time Scale: " .. gGlobalSyncTable.timeScale, gGlobalSyncTable.timeScale, 0, 20, on_set_time_scale)
    modMenuTimeModifier = hook_mod_menu_inputbox("Time Modifier", "0", 8, on_set_time_modifier)
    hook_mod_menu_button("Add To Time", on_add_hour)
    hook_mod_menu_button("Sync To Real Life Time", on_sync_command)
end

hook_mod_menu_button("Query Time", on_query_command)