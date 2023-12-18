function delete_at_dark() end
if SM64COOPDX_VERSION == nil then return end

gGlobalSyncTable.time = 0
gGlobalSyncTable.timeScale = 1

local sNightSequences = {}

-- localize functions to improve performance
local math_floor,network_is_server,djui_hud_is_pause_menu_created,smlua_audio_utils_replace_sequence,fade_volume_scale,set_background_music,obj_mark_for_deletion = math.floor,network_is_server,djui_hud_is_pause_menu_created,smlua_audio_utils_replace_sequence,fade_volume_scale,set_background_music,obj_mark_for_deletion

mod_storage_remove("ampm")
use24h = mod_storage_load_bool("24h") or false

local savedInMenu = false
local autoSaveTimer = 0
playingNightMusic = false

--- Returns the amount of days that have passed
function get_day_count()
    return math_floor(gGlobalSyncTable.time / (MINUTE * 24))
end

function save_time()
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
gGlobalSyncTable.time = load_time()

--- @return string
--- Returns the properly formatted time string
function get_time_string()
    local minutes = (gGlobalSyncTable.time / MINUTE) % 24
    local formattedMinutes = math_floor(minutes)
    local seconds = math_floor(gGlobalSyncTable.time / SECOND) % 60

    if not use24h then
        if formattedMinutes == 0 then
            formattedMinutes = 12
        elseif formattedMinutes > 12 then
            formattedMinutes = formattedMinutes - 12
        end
    end

    return math_floor(formattedMinutes) .. ":" .. string.format("%02d", seconds) .. if_then_else(not use24h, if_then_else(minutes < 12, " AM", " PM"), "")
end

function time_tick()
    if not network_is_server() then return end

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

function night_music_register(sequenceId, m64Name)
    local id = SEQ_COUNT + sequenceId
    smlua_audio_utils_replace_sequence(id, 20, 127, m64Name)
    sNightSequences[sequenceId] = id
end

function handle_night_music()
    if not show_day_night_cycle() or gNetworkPlayers[0].currActNum == 99 or gMarioStates[0].area == nil then return end
    local seq = sNightSequences[gMarioStates[0].area.musicParam2]
    if seq == nil then return end

    fade_volume_scale(0, 127, 1)

    local minutes = (gGlobalSyncTable.time / MINUTE) % 24

    if minutes >= HOUR_SUNSET_END + 0.75 and minutes <= HOUR_NIGHT_START then
        local threshold = 1 - (minutes - (HOUR_SUNSET_END + 0.75)) * 4  -- multiply by 4 because four quarters make a whole
        fade_volume_scale(SEQ_PLAYER_LEVEL, threshold * 127, 1)
    elseif minutes >= HOUR_SUNRISE_START + 0.75 and minutes <= HOUR_SUNRISE_END then
        local threshold = 1 - (minutes - (HOUR_SUNRISE_START + 0.75)) * 4
        fade_volume_scale(SEQ_PLAYER_LEVEL, threshold * 127, 1)
    end

    if (minutes >= HOUR_NIGHT_START or minutes < HOUR_SUNRISE_END) and not playingNightMusic then
        playingNightMusic = true
        fade_volume_scale(SEQ_PLAYER_LEVEL, 127, 1)
        set_background_music(0, SEQUENCE_ARGS(4, seq), 450)
    elseif minutes >= HOUR_SUNRISE_END and minutes < HOUR_NIGHT_START and playingNightMusic then
        playingNightMusic = false
        fade_volume_scale(0, 127, 1)
        set_background_music(0, SEQUENCE_ARGS(4, gMarioStates[0].area.musicParam2), 0)
    end
end

--- @return number
--- Returns the time in frames
function get_raw_time()
    return gGlobalSyncTable.time
end

--- @param time number
--- @return nil
--- Sets the time in frames
function set_raw_time(time)
    if type(time) ~= "number" then return end
    gGlobalSyncTable.time = time
end

--- @param o Object
function delete_at_dark(o)
    local minutes = gGlobalSyncTable.time / MINUTE % 24

    if minutes < HOUR_SUNRISE_START or minutes > HOUR_SUNSET_END then
       obj_mark_for_deletion(o)
    end
end