-- name: .Day Night Cycle DX
-- incompatible: light
-- description: Day Night Cycle DX v2.0\nBy \\#ec7731\\Agent X\n\n\\#dcdcdc\\This mod adds a fully featured day night cycle system with night, sunrise, day and sunset to sm64coopdx. Days last 24 minutes and you can switch to and from 24 hour time with /time 24h\n\nSpecial thanks to \\#00ffff\\AngelicMiracles \\#dcdcdc\\for the sunset, sunrise and night time skyboxes
-- deluxe: true

--- @diagnostic disable: undefined-global

if SM64COOPDX_VERSION == nil then return end

SECOND = 30
MINUTE = SECOND * 60

HOUR_SUNRISE_START = 4
HOUR_SUNRISE_END = 5
HOUR_SUNRISE_DURATION = HOUR_SUNRISE_END - HOUR_SUNRISE_START

HOUR_SUNSET_START = 19
HOUR_SUNSET_END = 20
HOUR_SUNSET_DURATION = HOUR_SUNSET_END - HOUR_SUNSET_START

HOUR_DAY_START = 6
HOUR_NIGHT_START = 21

local DIR_DARK = 0.6
local DIR_BRIGHT = 1

local COLOR_NIGHT   = { r = 70,  g = 75,  b = 100 }
local COLOR_SUNRISE = { r = 255, g = 255, b = 200 }
local COLOR_DAY     = { r = 255, g = 255, b = 255 }
local COLOR_SUNSET  = { r = 255, g = 155, b = 100 }

local FOG_COLOR_NIGHT = { r = 30, g = 30, b = 50 }

local COLOR_DISPLAY_DARK   = { r = 48,  g = 90,  b = 200 }
local COLOR_DISPLAY_BRIGHT = { r = 255, g = 255, b = 80  }

local SKYBOX_SCALE = 200

local REAL_MINUTE = 1 / 60

gGlobalSyncTable.dncEnabled = true
local dncDisplayTime = true

-- localize functions to improve performance
local network_is_moderator,network_is_server,set_override_envfx,set_lighting_dir,set_lighting_color,get_skybox,obj_get_first_with_behavior_id,spawn_non_sync_object,obj_scale,clampf,djui_hud_set_resolution,djui_hud_set_font,hud_is_hidden,djui_hud_get_screen_width,djui_hud_measure_text,djui_hud_get_screen_height,djui_hud_set_color,djui_hud_print_text,djui_chat_message_create,math_floor = network_is_moderator,network_is_server,set_override_envfx,set_lighting_dir,set_lighting_color,get_skybox,obj_get_first_with_behavior_id,spawn_non_sync_object,obj_scale,clampf,djui_hud_set_resolution,djui_hud_set_font,hud_is_hidden,djui_hud_get_screen_width,djui_hud_measure_text,djui_hud_get_screen_height,djui_hud_set_color,djui_hud_print_text,djui_chat_message_create,math.floor

--- @param enable boolean
--- @return nil
--- Globally enables or disables Day Night Cycle
local function enable_day_night_cycle(enable)
    if not network_is_server() and not network_is_moderator() then return end
    if type(enable) ~= "boolean" then return end
    gGlobalSyncTable.dncEnabled = enable
    djui_popup_create("Day Night Cycle has been " .. if_then_else(gGlobalSyncTable.dncEnabled, "enabled.", "disabled."), 2)
end

--- Returns whether or not DNC will display the time on the HUD
local function get_display_time()
    return dncDisplayTime
end

--- @param enable boolean
--- @return nil
--- Sets whether or not DNC will display the time on the HUD
local function set_display_time(enable)
    if type(enable) ~= "boolean" then return end
    dncDisplayTime = enable
end

local function update()
    if not gGlobalSyncTable.dncEnabled then
        set_override_envfx(-1)

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

        return
    end

    time_tick()
    handle_night_music()

    -- spawn skyboxes
    local skybox = get_skybox()
    if obj_get_first_with_behavior_id(bhvSkybox) == nil and skybox ~= -1 then
        if show_day_night_cycle() then
            -- spawn day, sunset and night skyboxes
            for i = 0, 2 do
                local model = 0
                if i == 0 then
                    model = gVanillaSkyboxModels[skybox] or E_MODEL_SKYBOX_OCEAN_SKY
                else
                    model = if_then_else(i == 1, E_MODEL_SKYBOX_SUNSET, E_MODEL_SKYBOX_NIGHT)
                end

                spawn_non_sync_object(
                    bhvSkybox,
                    model,
                    0, 0, 0,
                    --- @param o Object
                    function(o)
                        o.oBehParams2ndByte = i
                        obj_scale(o, SKYBOX_SCALE + 1 * i)
                    end
                )
            end
        else
            -- spawn static skybox
            spawn_non_sync_object(
                bhvSkybox,
                gVanillaSkyboxModels[skybox] or E_MODEL_SKYBOX_OCEAN_SKY,
                0, 0, 0,
                --- @param o Object
                function(o)
                    o.oBehParams2ndByte = 0
                    obj_scale(o, SKYBOX_SCALE)
                end
            )
        end
    end

    local minutes = (gGlobalSyncTable.time / MINUTE) % 24

    local actSelector = obj_get_first_with_behavior_id(id_bhvActSelector)
    if actSelector == nil and (show_day_night_cycle() or in_vanilla_level(LEVEL_DDD) or in_vanilla_level(LEVEL_TTM)) then -- DDD has a subarea connected by instant warps and TTM has a subarea with sunlight coming through it
        -- blizzard effect at night in snow levels
        if (minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_END) and gMarioStates[0].area.terrainType == TERRAIN_SNOW then
            set_override_envfx(ENVFX_SNOW_BLIZZARD)
        else
            set_override_envfx(-1)
        end

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

        -- calculate fog intensity
        local intensity = 1
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            intensity = lerp(1.02, 1, clampf((minutes - HOUR_SUNRISE_START) / (HOUR_SUNRISE_DURATION), 0, 1))
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_NIGHT_START then
            intensity = lerp(1, 1.02, clampf((minutes - HOUR_SUNSET_START) / (HOUR_NIGHT_START - HOUR_SUNSET_START), 0, 1))
        elseif minutes < HOUR_SUNRISE_START or minutes > HOUR_NIGHT_START then
            intensity = 1.02
        elseif minutes > HOUR_SUNRISE_END and minutes < HOUR_SUNSET_START then
            intensity = 1
        end

        set_lighting_dir(1, -(1 - dir))
        set_lighting_dir(2, -(1 - dir))
        set_lighting_color(0, color.r)
        set_lighting_color(1, color.g)
        set_lighting_color(2, color.b)
        set_vertex_color(0, color.r)
        set_vertex_color(1, color.g)
        set_vertex_color(2, color.b)
        set_fog_color(0, fogColor.r)
        set_fog_color(1, fogColor.g)
        set_fog_color(2, fogColor.b)
        set_fog_intensity(intensity)
    else
        set_override_envfx(-1)

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
end

local function on_hud_render_behind()
    if not gGlobalSyncTable.dncEnabled or not dncDisplayTime then return end -- api checks
    if obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil or gNetworkPlayers[0].currActNum == 99 then return end -- game checks

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_TINY)

    local scale = 1
    local text = get_time_string()

    local hidden = hud_is_hidden()
    local x = if_then_else(hidden, (djui_hud_get_screen_width() * 0.5) - (djui_hud_measure_text(text) * (0.5 * scale)), 24)
    local y = if_then_else(hidden, (djui_hud_get_screen_height() - 20), 32)

    local minutes = (gGlobalSyncTable.time / MINUTE) % 24

    -- outlined text
    djui_hud_set_color(0, 0, 0, 255)
    djui_hud_print_text(text, x - 1, y, scale)
    djui_hud_print_text(text, x + 1, y, scale)
    djui_hud_print_text(text, x, y - 1, scale)
    djui_hud_print_text(text, x, y + 1, scale)
    if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
        local color = color_lerp(COLOR_DISPLAY_DARK, COLOR_DISPLAY_BRIGHT, (minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION)
        djui_hud_set_color(color.r, color.g, color.b, 255)
    elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
        local color = color_lerp(COLOR_DISPLAY_BRIGHT, COLOR_DISPLAY_DARK, (minutes - HOUR_SUNSET_END) / HOUR_SUNSET_DURATION)
        djui_hud_set_color(color.r, color.g, color.b, 255)
    elseif minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_START then
        djui_hud_set_color(COLOR_DISPLAY_DARK.r, COLOR_DISPLAY_DARK.g, COLOR_DISPLAY_DARK.b, 255)
    elseif minutes > HOUR_SUNRISE_END and minutes < HOUR_SUNSET_END then
        djui_hud_set_color(COLOR_DISPLAY_BRIGHT.r, COLOR_DISPLAY_BRIGHT.g, COLOR_DISPLAY_BRIGHT.b, 255)
    end
    djui_hud_print_text(text, x, y, scale)
end

local function on_level_init()
    if not gGlobalSyncTable.dncEnabled then return end

    playingNightMusic = false

    if gNetworkPlayers[0].currLevelNum == LEVEL_CASTLE_GROUNDS and gNetworkPlayers[0].currActNum == 99 then
        if gMarioStates[0].action ~= ACT_END_WAVING_CUTSCENE then
            gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * (HOUR_SUNSET_START - 0.75))
            gGlobalSyncTable.timeScale = 1
        else
            gGlobalSyncTable.time = (get_day_count() + 1) * (MINUTE * 24) + (MINUTE * HOUR_SUNRISE_END)
        end
    end
end

local function on_warp()
    if not gGlobalSyncTable.dncEnabled then return end
    if network_is_server() then save_time() end
end

local function on_exit()
    if network_is_server() then save_time() end
end

local function on_set_command(msg)
    if msg == "" then
        djui_chat_message_create("/time \\#00ffff\\set\\#ffff00\\ [TIME]\\#dcdcdc\\ to set the time")
        return true
    end
    if msg == "morning" then
        gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * 6)
    elseif msg == "day" or msg == "noon" then
        gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * 12)
    elseif msg == "night" then
        gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * 21)
    elseif msg == "midnight" then
        gGlobalSyncTable.time = get_day_count() * (MINUTE * 24)
    elseif msg == "sunrise" then
        gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * 5)
    elseif msg == "sunset" then
        gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * 20)
    else
        local amount = tonumber(msg)
        if amount ~= nil then
            gGlobalSyncTable.time = amount * SECOND
        end
    end

    djui_chat_message_create("Time set to " .. math_floor(gGlobalSyncTable.time / SECOND))

    if network_is_server() then save_time() end
end

local function on_add_command(msg)
    local amount = tonumber(msg)
    if amount == nil then
        djui_chat_message_create("/time \\#00ffff\\add\\#ffff00\\ [AMOUNT]\\#dcdcdc\\ to add to the time")
        return
    end
    gGlobalSyncTable.time = gGlobalSyncTable.time + (amount * SECOND)

    djui_chat_message_create("[Day Night Cycle] Time set to " .. math_floor(gGlobalSyncTable.time / SECOND))

    if network_is_server() then save_time() end
end

local function on_scale_command(msg)
    local scale = tonumber(msg)
    if scale == nil then
        djui_chat_message_create("/time \\#00ffff\\scale\\#ffff00\\ [SCALE]\\#dcdcdc\\ to scale the rate at which time passes")
        return
    end
    gGlobalSyncTable.timeScale = scale

    djui_chat_message_create("[Day Night Cycle] Time scale set to " .. scale)

    if network_is_server() then save_time() end
end

local function on_query_command()
    djui_chat_message_create(string.format("Time is %d (%s), day %d", math_floor(gGlobalSyncTable.time / SECOND), get_time_string(), get_day_count()))
end

local function on_24h_command()
    use24h = not use24h
    mod_storage_save_bool("24h", use24h)
end

local function on_sync_command()
    djui_chat_message_create("[Day Night Cycle] Attempting to sync in-game time with real world time...")

    local dateTime = get_date_and_time()
    gGlobalSyncTable.time = get_day_count() * (MINUTE * 24) + (MINUTE * dateTime.hour) + (SECOND * dateTime.minute)
    gGlobalSyncTable.timeScale = REAL_MINUTE

    if network_is_server() then save_time() end
end

local function on_time_command(msg)
    local args = split(msg)
    local perms = network_is_server() or network_is_moderator()
    if args[1] == "set" then
        if not perms then
            djui_chat_message_create("\\#d86464\\[Day Night Cycle] You do not have permission to run /time set")
        else
            on_set_command(args[2] or "")
        end
    elseif args[1] == "add" then
        if not perms then
            djui_chat_message_create("\\#d86464\\[Day Night Cycle] You do not have permission to run /time add")
        else
            on_add_command(args[2] or "")
        end
    elseif args[1] == "scale" then
        if not perms then
            djui_chat_message_create("\\#d86464\\[Day Night Cycle] You do not have permission to run /time scale")
        else
            on_scale_command(args[2] or "")
        end
    elseif args[1] == "query" then
        on_query_command()
    elseif args[1] == "24h" then
        on_24h_command()
    elseif args[1] == "sync" then
        if not perms then
            djui_chat_message_create("\\#d86464\\[Day Night Cycle] You do not have permission to run /time sync")
        else
            on_sync_command()
        end
    else
        if not perms then
            djui_chat_message_create("\\#d86464\\[Day Night Cycle] You do not have permission to enable or disable Day Night Cycle")
        else
            gGlobalSyncTable.dncEnabled = not gGlobalSyncTable.dncEnabled
            djui_chat_message_create("[Day Night Cycle] Status: " .. on_or_off(gGlobalSyncTable.dncEnabled))
        end
    end

    return true
end

_G.dayNightCycleApi = {
    enable_day_night_cycle = enable_day_night_cycle,
    get_display_time = get_display_time,
    set_display_time = set_display_time,
    get_day_count = get_day_count,
    get_time_string = get_time_string,
    get_raw_time = get_raw_time,
    set_raw_time = set_raw_time,
}

night_music_register(SEQ_LEVEL_GRASS, "03_level_grass")
night_music_register(SEQ_LEVEL_WATER, "05_level_water")
night_music_register(SEQ_LEVEL_HOT, "06_level_hot")
night_music_register(SEQ_LEVEL_SNOW, "08_level_snow")

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_ON_HUD_RENDER_BEHIND, on_hud_render_behind)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_ON_WARP, on_warp)
hook_event(HOOK_ON_EXIT, on_exit)

hook_chat_command("time", "\\#00ffff\\[set|add|scale|query|24h|sync]\\#7f7f7f\\ (leave blank to toggle Day Night Cycle on or off)", on_time_command)