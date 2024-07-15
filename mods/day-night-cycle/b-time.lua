local sNightSequences = {}

-- localize functions to improve performance
local mod_storage_remove,mod_storage_load_bool,math_floor,mod_storage_save_number,mod_storage_load_number,type,error,network_is_moderator,network_is_server,string_format,djui_hud_is_pause_menu_created,smlua_audio_utils_replace_sequence,fade_volume_scale,set_background_music,obj_mark_for_deletion = mod_storage_remove,mod_storage_load_bool,math.floor,mod_storage_save_number,mod_storage_load_number,type,error,network_is_moderator,network_is_server,string.format,djui_hud_is_pause_menu_created,smlua_audio_utils_replace_sequence,fade_volume_scale,set_background_music,obj_mark_for_deletion

-- purge legacy fields
mod_storage_remove("ampm")
mod_storage_remove("night-music")

use24h = mod_storage_load_bool("24h")

local savedInMenu = false
local autoSaveTimer = 0
--- @type boolean
playNightMusic = if_then_else(mod_storage_load("night_music") == nil, true, mod_storage_load_bool("night_music"))
playingNightMusic = false

--- Returns the amount of days that have passed
function get_day_count()
    return math_floor(gGlobalSyncTable.time / (MINUTE * 24))
end

function save_time()
    if gNetworkPlayers[0].currActNum == 99 then return end
    mod_storage_save_number("time", gGlobalSyncTable.time)
    print("Saving time to 'day-night-cycle.sav'")
end

function load_time()
    local time = mod_storage_load_number("time")
    if time == nil then
        time = MINUTE * 4 -- starts at the beginning of sunrise
        mod_storage_save_number("time", time)
    end
    return time
end

--- Returns the time in frames
function get_raw_time()
    return gGlobalSyncTable.time
end

--- @param time integer
--- Sets the time in frames
function set_raw_time(time)
    if type(time) ~= "number" then
        error("set_raw_time: Parameter 'time' must be a number")
        return
    end
    if not network_is_server() and not network_is_moderator() then return end

    gGlobalSyncTable.time = time
end

--- Returns the amount of time that has passed in the day in minutes
function get_time_minutes()
    return (gGlobalSyncTable.time / MINUTE) % 24
end

--- Returns the time scale
function get_time_scale()
    return gGlobalSyncTable.timeScale
end

--- @param scale number
--- Sets the time scale
function set_time_scale(scale)
    if type(scale) ~= "number" then
        error("set_time_scale: Parameter 'scale' must be a number")
        return
    end
    if not network_is_server() and not network_is_moderator() then return end

    gGlobalSyncTable.timeScale = scale
end

--- @param time number
--- Returns the properly formatted time string
function get_time_string(time)
    if type(time) ~= "number" then
        error("get_time_string: Parameter 'time' must be a number")
        if use24h then
            return "12:00 AM"
        else
            return "0:00"
        end
    end

    local minutes = (time / MINUTE) % 24
    local formattedMinutes = math_floor(minutes)
    local seconds = math_floor(time / SECOND) % 60

    if not use24h then
        if formattedMinutes == 0 then
            formattedMinutes = 12
        elseif formattedMinutes > 12 then
            formattedMinutes = formattedMinutes - 12
        end
    end

    return string_format("%d:%02d%s", formattedMinutes, seconds, if_then_else(not use24h, if_then_else(minutes < 12, " AM", " PM"), ""))
end

function time_tick()
    gGlobalSyncTable.time = gGlobalSyncTable.time + gGlobalSyncTable.timeScale

    -- auto save every 30s
    autoSaveTimer = (autoSaveTimer + 1) % (SECOND * 30)
    if autoSaveTimer == 0 then
        save_time()
    end

    -- save when paused
    if djui_hud_is_pause_menu_created() then
        if not savedInMenu then
            save_time()
            savedInMenu = true
        end
    else
        savedInMenu = false
    end
end

--- @param sequenceId SeqId
--- @param m64Name string
--- Registers a custom sequence as night music
function night_music_register(sequenceId, m64Name)
    if type(sequenceId) ~= "number" or math_floor(sequenceId) ~= sequenceId or sequenceId < 0 or sequenceId >= SEQ_COUNT then
        error("night_music_register: Parameter 'sequenceId' must be a SeqId")
        return
    end
    if type(m64Name) ~= "string" then
        error("night_music_register: Parameter 'm64Name' must be a string")
        return
    end

    local id = SEQ_COUNT + sequenceId
    smlua_audio_utils_replace_sequence(id, 42, 80, m64Name)
    sNightSequences[sequenceId] = id
end

--- Returns whether or not night music should be played
function should_play_night_music()
    return is_dnc_enabled() and show_day_night_cycle() and playNightMusic and dayNightCycleApi.playNightMusic
end

function update_night_music()
    if gNetworkPlayers[0].currActNum == 99 or gMarioStates[0].area == nil then return end
    local musicParam = gMarioStates[0].area.musicParam2

    if not should_play_night_music() then
        if playingNightMusic then
            playingNightMusic = false
            fade_volume_scale(SEQ_PLAYER_LEVEL, 127, 1)
            set_background_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, musicParam), 0)
        end
        return
    end

    local seq = sNightSequences[musicParam]
    if seq == nil then return end

    fade_volume_scale(0, 127, 1)

    local minutes = get_time_minutes()

    if minutes >= HOUR_SUNSET_END + 0.75 and minutes < HOUR_NIGHT_START then
        local threshold = 1 - (minutes - (HOUR_SUNSET_END + 0.75)) * 4  -- multiply by 4 because four quarters make a whole
        fade_volume_scale(SEQ_PLAYER_LEVEL, threshold * 127, 1)
    elseif minutes >= HOUR_SUNRISE_START + 0.75 and minutes <= HOUR_SUNRISE_END then
        local threshold = 1 - (minutes - (HOUR_SUNRISE_START + 0.75)) * 4
        fade_volume_scale(SEQ_PLAYER_LEVEL, threshold * 127, 1)
    end

    if (minutes >= HOUR_NIGHT_START or minutes < HOUR_SUNRISE_END) and not playingNightMusic then
        playingNightMusic = true
        fade_volume_scale(SEQ_PLAYER_LEVEL, 127, 1)
        set_background_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, seq), 450)
    elseif minutes >= HOUR_SUNRISE_END and minutes < HOUR_NIGHT_START and playingNightMusic then
        playingNightMusic = false
        fade_volume_scale(SEQ_PLAYER_LEVEL, 127, 1)
        set_background_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, musicParam), 0)
    end
end

--- @param obj Object
--- Function to delete an object if it's dark out, meant to be used in behaviors
function delete_at_dark(obj)
    if obj == nil then
        error("delete_at_dark: Parameter 'obj' must be an Object")
        return
    end
    local minutes = gGlobalSyncTable.time / MINUTE % 24

    local delete = minutes < HOUR_SUNRISE_START or minutes > HOUR_SUNSET_END
    overrideDelete = dnc_call_hook(DNC_HOOK_DELETE_AT_DARK, obj, delete)
    if overrideDelete ~= nil and type(overrideDelete) == "boolean" then delete = overrideDelete end

    if delete then obj_mark_for_deletion(obj) end
end