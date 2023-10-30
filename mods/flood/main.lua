-- name: Flood
-- incompatible: gamemode
-- description: Flood v2.4.2\nBy \\#ec7731\\Agent X\\#dcdcdc\\\n\nThis mod adds a flood escape gamemode\nto sm64ex-coop, you must escape the flood and reach the top of the level before everything is flooded.

if unsupported then return end

local ROUND_STATE_INACTIVE = 0
ROUND_STATE_ACTIVE         = 1
local ROUND_COOLDOWN       = 600

local SPEEDRUN_MODE_OFF = 0
local SPEEDRUN_MODE_PROGRESS = 1
local SPEEDRUN_MODE_RESTART = 2

local TEX_FLOOD_FLAG = get_texture_info("flood_flag")

gGlobalSyncTable.roundState = ROUND_STATE_INACTIVE
gGlobalSyncTable.timer = ROUND_COOLDOWN
gGlobalSyncTable.level = LEVEL_BOB
gGlobalSyncTable.waterLevel = -20000
gGlobalSyncTable.speedMultiplier = 1

local sFlagIconPrevPos = { x = 0, y = 0 }

local globalTimer = 0
local listedSurvivors = false
local speedrunner = 0

-- localize functions to improve performance
local network_player_connected_count,init_single_mario,warp_to_level,play_sound,network_is_server,network_get_player_text_color_string,djui_chat_message_create,disable_time_stop,network_player_set_description,set_mario_action,obj_get_first_with_behavior_id,obj_check_hitbox_overlap,spawn_mist_particles,vec3f_dist,play_race_fanfare,play_music,djui_hud_set_resolution,djui_hud_get_screen_height,djui_hud_get_screen_width,djui_hud_render_rect,djui_hud_set_font,djui_hud_world_pos_to_screen_pos,clampf,math_floor,djui_hud_measure_text,djui_hud_print_text,hud_render_power_meter,hud_get_value,save_file_erase_current_backup_save,save_file_set_flags,save_file_set_using_backup_slot,find_floor_height,spawn_non_sync_object,set_environment_region,vec3f_set,vec3f_copy,math_random,set_ttc_speed_setting,get_level_name,hud_hide,smlua_text_utils_secret_star_replace,smlua_audio_utils_replace_sequence = network_player_connected_count,init_single_mario,warp_to_level,play_sound,network_is_server,network_get_player_text_color_string,djui_chat_message_create,disable_time_stop,network_player_set_description,set_mario_action,obj_get_first_with_behavior_id,obj_check_hitbox_overlap,spawn_mist_particles,vec3f_dist,play_race_fanfare,play_music,djui_hud_set_resolution,djui_hud_get_screen_height,djui_hud_get_screen_width,djui_hud_render_rect,djui_hud_set_font,djui_hud_world_pos_to_screen_pos,clampf,math.floor,djui_hud_measure_text,djui_hud_print_text,hud_render_power_meter,hud_get_value,save_file_erase_current_backup_save,save_file_set_flags,save_file_set_using_backup_slot,find_floor_height,spawn_non_sync_object,set_environment_region,vec3f_set,vec3f_copy,math.random,set_ttc_speed_setting,get_level_name,hud_hide,smlua_text_utils_secret_star_replace,smlua_audio_utils_replace_sequence

function speedrun_mode(mode)
    if mode == nil then
        return speedrunner > 0 and network_player_connected_count() == 1
    else
        return speedrunner == mode and network_player_connected_count() == 1
    end
end

-- runs serverside
local function round_start()
    gGlobalSyncTable.roundState = ROUND_STATE_ACTIVE
    gGlobalSyncTable.timer = if_then_else(gGlobalSyncTable.level == LEVEL_CTT or (gGlobalSyncTable.level == LEVEL_RR and game == GAME_STAR_ROAD), 730, 100)
end

-- runs serverside
local function round_end()
    gGlobalSyncTable.roundState = ROUND_STATE_INACTIVE
    gGlobalSyncTable.timer = ROUND_COOLDOWN
    gGlobalSyncTable.waterLevel = -20000
end

local function get_dest_act()
    if game ~= GAME_STAR_ROAD then
        return if_then_else(gNetworkPlayers[0].currLevelNum == LEVEL_CASTLE_GROUNDS, 99, 6)
    else
        if gNetworkPlayers[0].currLevelNum == LEVEL_CASTLE_GROUNDS then
            return 99
        end
        return if_then_else(gNetworkPlayers[0].currLevelNum == LEVEL_BBH, 1, 6)
    end
end

local function get_modifiers_string()
    if not cheats and not moveset then return "" end

    local modifiers = " ("
    if moveset then
        modifiers = modifiers .. "Moveset"
    else
        modifiers = modifiers .. "No moveset"
    end
    if cheats then
        modifiers = modifiers .. ", cheats"
    end
    modifiers = modifiers .. ")"
    return modifiers
end

function level_restart()
    round_start()
    init_single_mario(gMarioStates[0])
    mario_set_full_health(gMarioStates[0])
    gLevels[gGlobalSyncTable.level].time = 0
    warp_to_level(gGlobalSyncTable.level, gLevels[gGlobalSyncTable.level].area, get_dest_act())
end

local function server_update()
    if gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        if gNetworkPlayers[0].currLevelNum == gGlobalSyncTable.level then
            gGlobalSyncTable.waterLevel = gGlobalSyncTable.waterLevel + gLevels[gGlobalSyncTable.level].speed * gGlobalSyncTable.speedMultiplier

            local active = 0
            for i = 0, (MAX_PLAYERS - 1) do
                local m = gMarioStates[i]
                if active_player(m) ~= 0 and m.health > 0xff and not gPlayerSyncTable[i].finished then
                    active = active + 1
                end
            end

            if active == 0 then
                local dead = 0
                for i = 0, (MAX_PLAYERS) - 1 do
                    if active_player(gMarioStates[i]) ~= 0 and gMarioStates[i].health <= 0xff then
                        dead = dead + 1
                    end
                end
                if dead == network_player_connected_count() or (speedrun_mode() and gNetworkPlayers[0].currLevelNum ~= LEVEL_CTT) then
                    gGlobalSyncTable.timer = 0
                end

                if gGlobalSyncTable.timer > 0 then
                    gGlobalSyncTable.timer = gGlobalSyncTable.timer - 1
                else
                    round_end()

                    if not speedrun_mode() or speedrun_mode(SPEEDRUN_MODE_PROGRESS) then
                        -- move to the next level
                        local finished = 0
                        for i = 0, (MAX_PLAYERS - 1) do
                            if active_player(gMarioStates[i]) ~= 0 and gPlayerSyncTable[i].finished then
                                finished = finished + 1
                            end
                        end

                        if finished ~= 0 then
                            -- calculate position
                            local position = 1
                            for k, v in pairs(gMapRotation) do
                                if gGlobalSyncTable.level == v then
                                    position = k
                                end
                            end

                            position = position + 1
                            if position > FLOOD_LEVEL_COUNT - FLOOD_BONUS_LEVELS then
                                position = 1
                            end

                            gGlobalSyncTable.level = gMapRotation[position]
                        end
                    end
                end
            end
        end
    else
        if network_player_connected_count() > 1 then
            if gGlobalSyncTable.timer > 0 then
                gGlobalSyncTable.timer = gGlobalSyncTable.timer - 1

                if gGlobalSyncTable.timer == 30 or gGlobalSyncTable.timer == 60 or gGlobalSyncTable.timer == 90 then
                    play_sound(SOUND_MENU_CHANGE_SELECT, gMarioStates[0].marioObj.header.gfx.cameraToObject)
                elseif gGlobalSyncTable.timer == 11 then
                    play_sound(SOUND_GENERAL_RACE_GUN_SHOT, gMarioStates[0].marioObj.header.gfx.cameraToObject)
                end
            else
                round_start()
            end
        end
    end
end

local function update()
    if network_is_server() then server_update() end

    gServerSettings.playerInteractions = PLAYER_INTERACTIONS_NONE

    if gGlobalSyncTable.roundState == ROUND_STATE_INACTIVE then
        if gNetworkPlayers[0].currLevelNum ~= LEVEL_LOBBY or gNetworkPlayers[0].currActNum ~= 0 then
            if speedrun_mode() then
                level_restart()
            end

            warp_to_level(LEVEL_LOBBY, 1, 0)

            if not listedSurvivors and globalTimer > 5 then
                listedSurvivors = true
                local finished = 0
                local string = "Survivors:"
                for i = 0, (MAX_PLAYERS - 1) do
                    if gNetworkPlayers[i].connected and gPlayerSyncTable[i].finished then
                        string = string .. "\n" .. network_get_player_text_color_string(i) .. gNetworkPlayers[i].name
                        finished = finished + 1
                    end
                end
                if finished == 0 then
                    string = string .. "\n\\#ff0000\\None"
                end
                djui_chat_message_create(string)
            end
        end
    elseif gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        local act = get_dest_act()
        if gNetworkPlayers[0].currLevelNum ~= gGlobalSyncTable.level or gNetworkPlayers[0].currActNum ~= act then
            listedSurvivors = false
            mario_set_full_health(gMarioStates[0])
            gLevels[gGlobalSyncTable.level].time = 0
            gPlayerSyncTable[0].finished = false
            warp_to_level(gGlobalSyncTable.level, gLevels[gGlobalSyncTable.level].area, act)
        end
    end

    -- stops the star spawn cutscenes from happening
    local m = gMarioStates[0]
    if m.area ~= nil and m.area.camera ~= nil and (m.area.camera.cutscene == CUTSCENE_STAR_SPAWN or m.area.camera.cutscene == CUTSCENE_RED_COIN_STAR_SPAWN) then
        m.area.camera.cutscene = 0
        m.freeze = 0
        disable_time_stop()
    end

    globalTimer = globalTimer + 1
end

--- @param m MarioState
local function mario_update(m)
    if not gNetworkPlayers[m.playerIndex].connected then return end

    if m.health > 0xff then
        network_player_set_description(gNetworkPlayers[m.playerIndex], "Alive", 75, 255, 75, 255)
    else
        network_player_set_description(gNetworkPlayers[m.playerIndex], "Dead", 255, 75, 75, 255)
    end

    if m.playerIndex ~= 0 then return end

    -- action specific modifications
    if m.action == ACT_STEEP_JUMP then
        m.action = ACT_JUMP
    elseif m.action == ACT_JUMBO_STAR_CUTSCENE then
        m.flags = m.flags | MARIO_WING_CAP
    end

    -- disable instant warps
    if m.floor ~= nil and (m.floor.type == SURFACE_WARP or (m.floor.type >= SURFACE_PAINTING_WARP_D3 and m.floor.type <= SURFACE_PAINTING_WARP_FC) or (m.floor.type >= SURFACE_INSTANT_WARP_1B and m.floor.type <= SURFACE_INSTANT_WARP_1E)) then
        m.floor.type = SURFACE_DEFAULT
    end

    -- disable insta kills
    if m.floor ~= nil and (m.floor.type == SURFACE_INSTANT_QUICKSAND or m.floor.type == SURFACE_INSTANT_MOVING_QUICKSAND) then
        m.floor.type = SURFACE_BURNING
    end

    -- disable damage in lobby
    if gGlobalSyncTable.roundState == ROUND_STATE_INACTIVE then
        mario_set_full_health(m)
        m.peakHeight = m.pos.y
        return
    end

    -- dialog boxes
    if (m.action == ACT_SPAWN_NO_SPIN_AIRBORNE or m.action == ACT_SPAWN_NO_SPIN_LANDING or m.action == ACT_SPAWN_SPIN_AIRBORNE or m.action == ACT_SPAWN_SPIN_LANDING) and m.pos.y < m.floorHeight + 10 then
        set_mario_action(m, ACT_FREEFALL, 0)
    end

    -- manage CTT
    if gNetworkPlayers[0].currLevelNum == LEVEL_CTT then
        m.peakHeight = m.pos.y

        local star = obj_get_first_with_behavior_id(id_bhvFinalStar)
        if star ~= nil and obj_check_hitbox_overlap(m.marioObj, star) and m.action ~= ACT_JUMBO_STAR_CUTSCENE then
            spawn_mist_particles()
            set_mario_action(m, ACT_JUMBO_STAR_CUTSCENE, 0)
        end

        if m.action == ACT_JUMBO_STAR_CUTSCENE and m.actionTimer >= 499 then
            set_mario_spectator(m)
        end
    end

    -- check if the player has reached the end of the level 
    if gNetworkPlayers[0].currLevelNum == gGlobalSyncTable.level and not gPlayerSyncTable[0].finished and ((gNetworkPlayers[0].currLevelNum ~= LEVEL_CTT and m.pos.y == m.floorHeight)
    or (gNetworkPlayers[0].currLevelNum == LEVEL_CTT and m.action == ACT_JUMBO_STAR_CUTSCENE) or (m.action & ACT_FLAG_ON_POLE) ~= 0)
    and vec3f_dist(m.pos, gLevels[gGlobalSyncTable.level].goalPos) < 600 then
        gPlayerSyncTable[0].finished = true

        local string = ""
        if gNetworkPlayers[0].currLevelNum ~= LEVEL_CTT and not (game == GAME_STAR_ROAD and gNetworkPlayers[0].currLevelNum == LEVEL_RR) then
            string = string .. "\\#00ff00\\You escaped the flood!\n"
            play_race_fanfare()
        else
            string = string .. "\\#00ff00\\You escaped the \\#ffff00\\final\\#00ff00\\ flood! Congratulations!\n"
            play_music(0, SEQUENCE_ARGS(8, SEQ_EVENT_CUTSCENE_VICTORY), 0)
        end
        string = string .. "\\#ffffff\\Time: " .. string.format("%.3f", gLevels[gGlobalSyncTable.level].time / 30) .. get_modifiers_string()

        djui_chat_message_create(string)
    end

    -- update spectator if finished, manage other things if not
    if gPlayerSyncTable[0].finished then
        mario_set_full_health(m)
        if network_player_connected_count() > 1 and m.action ~= ACT_JUMBO_STAR_CUTSCENE then
            set_mario_spectator(m)
        end
    else
        if m.pos.y + 40 < gGlobalSyncTable.waterLevel then
            m.health = m.health - 30
        end

        if m.action == ACT_QUICKSAND_DEATH then
            m.health = 0xff
        end

        if m.health <= 0xff then
            if network_player_connected_count() > 1 then
                m.area.camera.cutscene = 0
                set_mario_spectator(m)
            end
        else
            gLevels[gGlobalSyncTable.level].time = gLevels[gGlobalSyncTable.level].time + 1
        end
    end
end

local function on_hud_render()
    local water = obj_get_first_with_behavior_id(id_bhvWater)
    if gNetworkPlayers[0].currLevelNum == gGlobalSyncTable.level and water ~= nil then
        djui_hud_set_resolution(RESOLUTION_DJUI)

        if gLakituState.pos.y < gGlobalSyncTable.waterLevel - 10 then
            switch(water.oAnimState, {
                [FLOOD_WATER] = function()
                    djui_hud_set_adjusted_color(0, 20, 200, 120)
                end,
                [FLOOD_LAVA] = function()
                    djui_hud_set_adjusted_color(200, 0, 0, 220)
                end,
                [FLOOD_SAND] = function()
                    djui_hud_set_adjusted_color(254, 193, 121, 220)
                end,
                [FLOOD_MUD] = function()
                    djui_hud_set_adjusted_color(74, 123, 0, 220)
                end
            })
            djui_hud_render_rect(0, 0, djui_hud_get_screen_width(), djui_hud_get_screen_height())
        end
    end

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_TINY)

    local level = gLevels[gNetworkPlayers[0].currLevelNum]
    if level ~= nil and level.name ~= "ctt" then
        local out = { x = 0, y = 0, z = 0 }
        djui_hud_world_pos_to_screen_pos(level.goalPos, out)
        local dX = clampf(out.x - 5, 0, djui_hud_get_screen_width() - 19.2)
        local dY = clampf(out.y - 20, 0, djui_hud_get_screen_height() - 19.2)

        djui_hud_set_adjusted_color(255, 255, 255, 200)
        djui_hud_render_texture_interpolated(TEX_FLOOD_FLAG, sFlagIconPrevPos.x, sFlagIconPrevPos.y, 0.15, 0.15, dX, dY, 0.15, 0.15)

        sFlagIconPrevPos.x = dX
        sFlagIconPrevPos.y = dY
    end

    local text = if_then_else(gGlobalSyncTable.roundState == ROUND_STATE_INACTIVE, "Type '/flood start' to start a round", "0.000 seconds" .. get_modifiers_string())
    if gNetworkPlayers[0].currAreaSyncValid then
        if gGlobalSyncTable.roundState == ROUND_STATE_INACTIVE then
            text = if_then_else(network_player_connected_count() > 1, "Round starts in " .. tostring(math_floor(gGlobalSyncTable.timer / 30)), "Type '/flood start' to start a round")
        elseif gNetworkPlayers[0].currLevelNum == gGlobalSyncTable.level then
            text = tostring(string.format("%.3f", gLevels[gGlobalSyncTable.level].time / 30)) .. " seconds" .. get_modifiers_string()
        end
    end

    local scale = 1
    local width = djui_hud_measure_text(text) * scale
    local x = (djui_hud_get_screen_width() - width) * 0.5

    djui_hud_set_adjusted_color(0, 0, 0, 128)
    djui_hud_render_rect(x - 6, 0, width + 12, 16)
    djui_hud_set_adjusted_color(255, 255, 255, 255)
    djui_hud_print_text(text, x, 0, scale)

    hud_render_power_meter(gMarioStates[0].health, djui_hud_get_screen_width() - 64, 0, 64, 64)

    djui_hud_set_font(FONT_HUD)

    djui_hud_render_texture(gTextures.coin, 5, 5, 1, 1)
    djui_hud_print_text("x", 21, 5, 1)
    djui_hud_print_text(tostring(hud_get_value(HUD_DISPLAY_COINS)), 37, 5, 1)

    if gGlobalSyncTable.speedMultiplier ~= 1 then
        djui_hud_print_text(string.format("%.2fx", gGlobalSyncTable.speedMultiplier), 5, 24, 1)
    end
end

local function on_level_init()
    -- reset save
    save_file_erase_current_backup_save()
    if gNetworkPlayers[0].currLevelNum ~= LEVEL_CASTLE_GROUNDS then
        save_file_set_flags(SAVE_FLAG_HAVE_VANISH_CAP)
        save_file_set_flags(SAVE_FLAG_HAVE_WING_CAP)
    end
    save_file_set_using_backup_slot(true)

    if gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        if network_is_server() then
            local start = gLevels[gGlobalSyncTable.level].customStartPos
            if start ~= nil then
                gGlobalSyncTable.waterLevel = find_floor_height(start.x, start.y, start.z) - 1200
            else
                -- only sub areas have a weird issue where this function appears to always return the floor lower limit on level init
                gGlobalSyncTable.waterLevel = if_then_else(gLevels[gGlobalSyncTable.level].area == 1, find_floor_height(gMarioStates[0].pos.x, gMarioStates[0].pos.y, gMarioStates[0].pos.z), gMarioStates[0].pos.y) - 1200
            end
        end

        if game == GAME_VANILLA then
            if gNetworkPlayers[0].currLevelNum == LEVEL_BITS then
                spawn_non_sync_object(
                    id_bhvCustomStaticObject,
                    E_MODEL_CTT,
                    10000, -2000, -40000,
                    function(o) obj_scale(o, 0.5) end
                )
            elseif gNetworkPlayers[0].currLevelNum == LEVEL_WDW then
                set_environment_region(1, -20000)
            end
        end

        spawn_non_sync_object(
            id_bhvWater,
            E_MODEL_FLOOD,
            0, gGlobalSyncTable.waterLevel, 0,
            nil
        )
    end

    local pos = gLevels[gNetworkPlayers[0].currLevelNum].goalPos
    if pos == nil then return end

    if gNetworkPlayers[0].currLevelNum == LEVEL_CTT then
        spawn_non_sync_object(
            id_bhvFinalStar,
            E_MODEL_STAR,
            pos.x, pos.y, pos.z,
            nil
        )
    else
        spawn_non_sync_object(
            id_bhvFloodFlag,
            E_MODEL_KOOPA_FLAG,
            pos.x, pos.y, pos.z,
            --- @param o Object
            function(o)
                o.oFaceAnglePitch = 0
                o.oFaceAngleYaw = pos.a
                o.oFaceAngleRoll = 0
            end
        )
    end
end

-- dynos warps mario back to castle grounds facing the wrong way, likely something from the title screen
local function on_warp()
    --- @type MarioState
    local m = gMarioStates[0]
    if gNetworkPlayers[0].currLevelNum == LEVEL_CASTLE_GROUNDS then
        if game == GAME_VANILLA then
            m.faceAngle.y = m.faceAngle.y + 0x8000
        elseif game == GAME_STAR_ROAD then
            if gGlobalSyncTable.roundState == ROUND_STATE_INACTIVE then
                vec3f_set(m.pos, -6797, 1830, 2710)
                m.faceAngle.y = 0x6000
            else
                vec3f_set(m.pos, -1644, -614, -1524)
                m.faceAngle.y = -0x4000
            end
        end

        if gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
            play_music(0, SEQUENCE_ARGS(4, SEQ_LEVEL_BOSS_KOOPA_FINAL), 0)
        end
    elseif gLevels[gGlobalSyncTable.level].customStartPos ~= nil then
        local start = gLevels[gGlobalSyncTable.level].customStartPos
        vec3f_copy(m.pos, start)
        set_mario_action(m, ACT_SPAWN_SPIN_AIRBORNE, 0)
        m.faceAngle.y = start.a
    end
end

local function on_player_connected()
    if network_is_server() and gGlobalSyncTable.roundState == ROUND_STATE_INACTIVE then gGlobalSyncTable.timer = ROUND_COOLDOWN end
end

local function on_start_command(msg)
    if msg == "?" then
        djui_chat_message_create("/flood \\#00ffff\\start\\#ffff00\\ [random|1-" .. FLOOD_LEVEL_COUNT .. "]\\#ffffff\\\nSets the level to a random one or a specific one, you can also leave it empty for normal progression.")
        return true
    end

    if msg == "random" then
        gGlobalSyncTable.level = gLevels[math_random(1, FLOOD_LEVEL_COUNT)]
    else
        local override = tonumber(msg)
        if override ~= nil then
            override = clamp(math_floor(override), 1, FLOOD_LEVEL_COUNT)
            gGlobalSyncTable.level = gMapRotation[override]
        else
            for k, v in pairs(gLevels) do
                if msg ~= nil and msg:lower() == v.name then
                    gGlobalSyncTable.level = k
                end
            end
        end
    end
    if gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        network_send(true, { restart = true })
        level_restart()
    else
        round_start()
    end
    return true
end

local function on_speed_command(msg)
    local speed = tonumber(msg)
    if speed ~= nil then
        speed = clampf(speed, 0, 10)
        djui_chat_message_create("Water speed set to " .. speed)
        gGlobalSyncTable.speedMultiplier = speed
        return true
    end

    djui_chat_message_create("/flood \\#00ffff\\speed\\#ffff00\\ [number]\\#ffffff\\\nSets the speed multiplier of the flood")
    return true
end

local function on_ttc_speed_command(msg)
    if gGlobalSyncTable.roundState ~= ROUND_STATE_INACTIVE then
        djui_chat_message_create("\\#ff0000\\You can only change the TTC speed before the round starts!")
        return true
    end

    msg = msg:lower()
    if msg == "fast" then
        set_ttc_speed_setting(TTC_SPEED_FAST)
        djui_chat_message_create("TTC speed set to fast")
        return true
    elseif msg == "slow" then
        set_ttc_speed_setting(TTC_SPEED_SLOW)
        djui_chat_message_create("TTC speed set to slow")
        return true
    elseif msg == "random" then
        set_ttc_speed_setting(TTC_SPEED_RANDOM)
        djui_chat_message_create("TTC speed set to random")
        return true
    elseif msg == "stopped" then
        set_ttc_speed_setting(TTC_SPEED_STOPPED)
        djui_chat_message_create("TTC speed stopped")
        return true
    end

    djui_chat_message_create("/flood \\#00ffff\\ttc-speed\\#ffff00\\ [fast|slow|random|stopped]\\#ffffff\\\nChanges the speed of TTC")
    return true
end

local function on_speedrun_command(msg)
    msg = msg:lower()
    if msg == "off" then
        djui_chat_message_create("Speedrun mode status: \\#ff0000\\OFF")
        speedrunner = SPEEDRUN_MODE_OFF
        return true
    elseif msg == "progress" then
        djui_chat_message_create("Speedrun mode status: \\#00ff00\\Progress Level")
        speedrunner = SPEEDRUN_MODE_PROGRESS
        return true
    elseif msg == "restart" then
        djui_chat_message_create("Speedrun mode status: \\#00ff00\\Restart Level")
        speedrunner = SPEEDRUN_MODE_RESTART
        return true
    end

    djui_chat_message_create("/flood \\#00ffff\\speedrun\\#ffff00\\ [off|progress|restart]\\#ffffff\\\nTo make adjustments to singleplayer Flood helpful for speedrunners")
    return true
end

local function on_scoreboard_command()
    djui_chat_message_create("Times:")
    local modifiers = get_modifiers_string()
    local total = 0
    for i = 1, FLOOD_LEVEL_COUNT do
        local level = gMapRotation[i]
        djui_chat_message_create(get_level_name(level_to_course(level), level, 1) .. " - " .. timestamp(gLevels[level].time) .. modifiers)
        total = total + gLevels[level].time
    end

    djui_chat_message_create("Total Time: " .. timestamp(total))
    return true
end

local function on_flood_command(msg)
    local args = split(msg)
    if args[1] == "start" then
        return on_start_command(args[2])
    elseif args[1] == "speed" then
        return on_speed_command(args[2])
    elseif args[1] == "ttc-speed" then
        return on_ttc_speed_command(args[2])
    elseif args[1] == "speedrun" then
        return on_speedrun_command(args[2])
    elseif args[1] == "scoreboard" then
        return on_scoreboard_command()
    end

    djui_chat_message_create("/flood \\#00ffff\\[start|speed|ttc-speed|speedrun|scoreboard]")
    return true
end

gServerSettings.skipIntro = 1
gServerSettings.stayInLevelAfterStar = 2

gLevelValues.entryLevel = LEVEL_LOBBY
gLevelValues.floorLowerLimit = -20000
gLevelValues.floorLowerLimitMisc = -20000 + 1000
gLevelValues.floorLowerLimitShadow = -20000 + 1000.0
gLevelValues.fixCollisionBugs = 1
gLevelValues.fixCollisionBugsRoundedCorners = 0

hud_hide()

if game == GAME_VANILLA then
    set_ttc_speed_setting(TTC_SPEED_SLOW)

    smlua_text_utils_secret_star_replace(COURSE_SA, "   Climb The Tower Flood")

    smlua_audio_utils_replace_sequence(SEQ_LEVEL_BOSS_KOOPA_FINAL, 37, 60, "00_pinball_custom")
end

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_ON_WARP, on_warp)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)

if network_is_server() then
    hook_chat_command("flood", "\\#00ffff\\[start|speed|ttc-speed|speedrun|scoreboard]", on_flood_command)
end

for i = 0, (MAX_PLAYERS - 1) do
    gPlayerSyncTable[i].finished = false
end