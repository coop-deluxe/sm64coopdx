-- name: Hide and Seek
-- incompatible: gamemode
-- description: A simple hide-and-seek gamemode for\nCo-op.\n\nThe game is split into two teams:\n\nHiders and Seekers. The goal is for all\n\Hiders to be converted into a Seeker within a certain timeframe.\n\nAll Seekers appear as a metal character.\n\nEnjoy! :D\n\nConcept by: Super Keeberghrh
-- pausable: false

-- constants
local ROUND_STATE_WAIT        = 0
local ROUND_STATE_ACTIVE      = 1
local ROUND_STATE_SEEKERS_WIN = 2
local ROUND_STATE_HIDERS_WIN  = 3
local ROUND_STATE_UNKNOWN_END = 4

-- globals
gGlobalSyncTable.roundState   = ROUND_STATE_WAIT -- current round state
gGlobalSyncTable.touchTag = false
gGlobalSyncTable.hiderCaps = false
gGlobalSyncTable.seekerCaps = false
gGlobalSyncTable.banKoopaShell = true
gGlobalSyncTable.disableBLJ = true
gGlobalSyncTable.displayTimer = 0 -- the displayed timer

-- variables
local sRoundTimer        = 0            -- the server's round timer
local sRoundStartTimeout = 15 * 30      -- fifteen seconds
local sRoundEndTimeout   = 3 * 60 * 30  -- three minutes
local pauseExitTimer = 0
local canLeave = false
local sFlashingIndex = 0
local np = gNetworkPlayers[0]
local cannonTimer = 0

-- server settings
gServerSettings.bubbleDeath = 0
gServerSettings.nametags = false

--localize functions to improve performance
local
hook_chat_command, network_player_set_description, hook_on_sync_table_change, network_is_server,
hook_event, djui_popup_create, network_get_player_text_color_string, play_sound,
play_character_sound, djui_chat_message_create, djui_hud_set_resolution, djui_hud_set_font,
djui_hud_set_color, djui_hud_render_rect, djui_hud_print_text, djui_hud_get_screen_width, djui_hud_get_screen_height,
djui_hud_measure_text, tostring, warp_to_level, warp_to_start_level, stop_cap_music, dist_between_objects,
math_floor, math_ceil, table_insert, set_camera_mode
=
hook_chat_command, network_player_set_description, hook_on_sync_table_change, network_is_server,
hook_event, djui_popup_create, network_get_player_text_color_string, play_sound,
play_character_sound, djui_chat_message_create, djui_hud_set_resolution, djui_hud_set_font,
djui_hud_set_color, djui_hud_render_rect, djui_hud_print_text, djui_hud_get_screen_width, djui_hud_get_screen_height,
djui_hud_measure_text, tostring, warp_to_level, warp_to_start_level, stop_cap_music, dist_between_objects,
math.floor, math.ceil, table.insert, set_camera_mode

local function on_or_off(value)
    if value then return "enabled" end
    return "disabled"
end

local function server_update()
    -- increment timer
    sRoundTimer = sRoundTimer + 1
    gGlobalSyncTable.displayTimer = math_floor(sRoundTimer / 30)

    -- figure out state of the game
    local hasSeeker = false
    local hasHider = false
    local activePlayers = {}
    local connectedCount = 0
    for i = 0, (MAX_PLAYERS-1) do
        if gNetworkPlayers[i].connected then
            connectedCount = connectedCount + 1
            table_insert(activePlayers, gPlayerSyncTable[i])
            if gPlayerSyncTable[i].seeking then
                hasSeeker = true
            else
                hasHider = true
            end
        end
    end

    -- only change state if there are 2+ players
    if connectedCount < 2 then
        gGlobalSyncTable.roundState = ROUND_STATE_WAIT
        return
    elseif gGlobalSyncTable.roundState == ROUND_STATE_WAIT then
        gGlobalSyncTable.roundState = ROUND_STATE_UNKNOWN_END
        sRoundTimer = 0
        gGlobalSyncTable.displayTimer = 0
    end

    -- check to see if the round should end
    if gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        if not hasHider or not hasSeeker or sRoundTimer > sRoundEndTimeout then
            if not hasHider then
                gGlobalSyncTable.roundState = ROUND_STATE_SEEKERS_WIN
            elseif sRoundTimer > sRoundEndTimeout then
                gGlobalSyncTable.roundState = ROUND_STATE_HIDERS_WIN
            else
                gGlobalSyncTable.roundState = ROUND_STATE_UNKNOWN_END
            end
            sRoundTimer = 0
            gGlobalSyncTable.displayTimer = 0
        else
            return
        end
    end

    -- start round
    if sRoundTimer >= sRoundStartTimeout then
        -- reset seekers
        for i=0,(MAX_PLAYERS-1) do
            gPlayerSyncTable[i].seeking = false
        end
        hasSeeker = false

        -- pick random seeker
        if not hasSeeker then
            local randNum = math.random(#activePlayers)
            local s = activePlayers[randNum]
            s.seeking = true
        end

        -- set round state
        gGlobalSyncTable.roundState = ROUND_STATE_ACTIVE
        sRoundTimer = 0
        gGlobalSyncTable.displayTimer = 0

    end
end

local function update()
    pauseExitTimer = pauseExitTimer + 1

    if pauseExitTimer >= 900 and not canLeave then
        canLeave = true
    end
    -- only allow the server to figure out the seeker
    if network_is_server() then
        server_update()
    end

    -- Force several camera configs
    camera_config_enable_camera_collisions(true)
    rom_hack_cam_set_collisions(1)
    camera_romhack_set_zoomed_in_dist(900)
    camera_romhack_set_zoomed_out_dist(1400)
    camera_romhack_set_zoomed_in_height(300)
    camera_romhack_set_zoomed_out_height(450)
end

local function screen_transition(trans)
    -- if the local player died next to a seeker, make them a seeker
    local s = gPlayerSyncTable[0]
    if not s.seeking then
        for i=1,(MAX_PLAYERS-1) do
            if gNetworkPlayers[i].connected and gNetworkPlayers[i].currLevelNum == np.currLevelNum and
                gNetworkPlayers[i].currActNum == np.currActNum and gNetworkPlayers[i].currAreaIndex == np.currAreaIndex
                and gPlayerSyncTable[i].seeking then

                local m = gMarioStates[0]
                local a = gMarioStates[i]

                if trans == WARP_TRANSITION_FADE_INTO_BOWSER or (m.floor.type == SURFACE_DEATH_PLANE and m.pos.y <= m.floorHeight + 2048) then
                    if dist_between_objects(m.marioObj, a.marioObj) <= 4000 and m.playerIndex == 0 then
                        s.seeking = true
                    end
                end
            end
        end
    end
end

--- @param m MarioState
local function mario_update(m)
    if (m.flags & MARIO_VANISH_CAP) ~= 0 then
        m.flags = m.flags & ~MARIO_VANISH_CAP --Always Remove Vanish Cap
        stop_cap_music()
    end

    if gGlobalSyncTable.disableBLJ and m.forwardVel <= -55 then
        m.forwardVel = -55
    end

    -- this code runs for all players
    local s = gPlayerSyncTable[m.playerIndex]

    if m.playerIndex == 0 and m.action == ACT_IN_CANNON and m.actionState == 2 then
        cannonTimer = cannonTimer + 1
        if cannonTimer >= 150 then -- 150 is 5 seconds
            m.forwardVel = 100 * coss(m.faceAngle.x)

            m.vel.y = 100 * sins(m.faceAngle.x)

            m.pos.x = m.pos.x + 120 * coss(m.faceAngle.x) * sins(m.faceAngle.y)
            m.pos.y = m.pos.y + 120 * sins(m.faceAngle.x)
            m.pos.z = m.pos.z + 120 * coss(m.faceAngle.x) * coss(m.faceAngle.y)

            play_sound(SOUND_ACTION_FLYING_FAST, m.marioObj.header.gfx.cameraToObject)
            play_sound(SOUND_OBJ_POUNDING_CANNON, m.marioObj.header.gfx.cameraToObject)

            m.marioObj.header.gfx.node.flags = m.marioObj.header.gfx.node.flags | GRAPH_RENDER_ACTIVE
            set_camera_mode(m.area.camera, m.area.camera.defMode, 1)

            set_mario_action(m, ACT_SHOT_FROM_CANNON, 0)
            queue_rumble_data_mario(m, 60, 70)
            m.usedObj.oAction = 2
            cannonTimer = 0
        end
    end

    -- remove caps
    if m.playerIndex == 0 or gGlobalSyncTable.roundState ~= ROUND_STATE_ACTIVE then
        if gGlobalSyncTable.seekerCaps and gPlayerSyncTable[m.playerIndex].seeking then
            m.flags = m.flags & ~MARIO_WING_CAP -- remove wing cap if seeking
            m.flags = m.flags & ~MARIO_METAL_CAP -- remove metal cap if seeking
            stop_cap_music()
            m.capTimer = 0
        elseif gGlobalSyncTable.hiderCaps and not gPlayerSyncTable[m.playerIndex].seeking then
            m.flags = m.flags & ~MARIO_WING_CAP -- remove wing cap if hiding
            m.flags = m.flags & ~MARIO_METAL_CAP -- remove metal cap if hiding
            stop_cap_music()
            m.capTimer = 0
        end
    end

    -- warp to the beninging
    if m.playerIndex == 0 then
        if gPlayerSyncTable[m.playerIndex].seeking and gGlobalSyncTable.displayTimer == 0 and gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
            warp_to_start_level()
        end
    end

    -- display all seekers as metal
    if s.seeking then
        m.marioBodyState.modelState = m.marioBodyState.modelState | MODEL_STATE_METAL
    end

    -- pu prevention
    if m.playerIndex == 0 and (m.pos.x > 0x7FFF or m.pos.x < -0x8000 or m.pos.z > 0x7FFF or m.pos.z < -0x8000) then
        s.seeking = true
        warp_restart_level()
    end
end

---@param m MarioState
---@param action integer
local function before_set_mario_action(m, action)
    if m.playerIndex == 0 then
        if action == ACT_WAITING_FOR_DIALOG or action == ACT_READING_SIGN or action == ACT_READING_NPC_DIALOG or action == ACT_JUMBO_STAR_CUTSCENE then
            return 1
        elseif action == ACT_READING_AUTOMATIC_DIALOG and get_id_from_behavior(m.interactObj.behavior) ~= id_bhvDoor and get_id_from_behavior(m.interactObj.behavior) ~= id_bhvStarDoor then
            return 1
        elseif action == ACT_EXIT_LAND_SAVE_DIALOG then
            set_camera_mode(m.area.camera, m.area.camera.defMode, 1)
            return ACT_IDLE
        end
    end
end

--- @param m MarioState
local function before_phys_step(m)
    -- prevent physics from being altered when bubbled
    local s = gPlayerSyncTable[m.playerIndex]

    if m.action == ACT_BUBBLED or s.seeking then return end

    -- only make seekers faster

    local hScale = 1.0
    local vScale = 1.0

    -- make swimming seekers 5% faster
    if (m.action & ACT_FLAG_SWIMMING) ~= 0 then
        hScale = hScale * 1.05
        if m.action ~= ACT_WATER_PLUNGE then
            vScale = vScale * 1.05
        end
    end
end

local function on_pvp_attack(attacker, victim)
    -- this code runs when a player attacks another player
    local sAttacker = gPlayerSyncTable[attacker.playerIndex]
    local sVictim = gPlayerSyncTable[victim.playerIndex]

    -- only consider local player
    if victim.playerIndex ~= 0 then
        return
    end

    -- make victim a seeker
    if sAttacker.seeking and not sVictim.seeking then
        sVictim.seeking = true
    end
end

--- @param m MarioState
local function on_player_connected(m)
    -- start out as a seeker
    local s = gPlayerSyncTable[m.playerIndex]
    s.seeking = true
    network_player_set_description(gNetworkPlayers[m.playerIndex], "seeker", 255, 64, 64, 255)
end

local function hud_top_render()
    local seconds = 0
    local text = ""

    if gGlobalSyncTable.roundState == ROUND_STATE_WAIT then
        seconds = 60
        text = "waiting for players"
    elseif gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        seconds = math_floor(sRoundEndTimeout / 30 - gGlobalSyncTable.displayTimer)
        if seconds < 0 then seconds = 0 end
        text = "seekers have " .. seconds .. " seconds"
    else
        seconds = math_floor(sRoundStartTimeout / 30 - gGlobalSyncTable.displayTimer)
        if seconds < 0 then seconds = 0 end
        text = "next round in " .. seconds .. " seconds"
    end

    local scale = 0.5

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()
    local width = djui_hud_measure_text(text) * scale

    local x = (screenWidth - width) * 0.5
    local y = 0

    local background = 0.0
    if seconds < 60 and gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        background = (math.sin(sFlashingIndex * 0.1) * 0.5 + 0.5) * 1
        background = background * background
        background = background * background
    end

    -- render top
    djui_hud_set_color(255 * background, 0, 0, 128)
    djui_hud_render_rect(x - 6, y, width + 12, 16)

    djui_hud_set_color(255, 255, 255, 255)
    djui_hud_print_text(text, x, y, scale)
end

local function hud_center_render()
    if gGlobalSyncTable.displayTimer > 3 then return end

    -- set text
    local text = ""
    if gGlobalSyncTable.roundState == ROUND_STATE_SEEKERS_WIN then
        text = "Seekers Win!"
    elseif gGlobalSyncTable.roundState == ROUND_STATE_HIDERS_WIN then
        text = "Hiders Win!"
    elseif gGlobalSyncTable.roundState == ROUND_STATE_ACTIVE then
        text = "Go!"
    else
        return
    end

    -- set scale
    local scale = 1

    -- get width of screen and text
    local screenWidth = djui_hud_get_screen_width()
    local screenHeight = djui_hud_get_screen_height()
    local width = djui_hud_measure_text(text) * scale
    local height = 32 * scale

    local x = (screenWidth - width) * 0.5
    local y = (screenHeight - height) * 0.5

    -- render
    djui_hud_set_color(0, 0, 0, 128)
    djui_hud_render_rect(x - 6 * scale, y, width + 12 * scale, height)

    djui_hud_set_color(255, 255, 255, 255)
    djui_hud_print_text(text, x, y, scale)
end

local function on_hud_render()
    -- render to N64 screen space, with the HUD font
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_NORMAL)

    hud_top_render()
    hud_center_render()

    sFlashingIndex = sFlashingIndex + 1
end

local function on_touch_tag_command()
    gGlobalSyncTable.touchTag = not gGlobalSyncTable.touchTag
    djui_chat_message_create("Touch tag: " .. on_or_off(gGlobalSyncTable.touchTag))
    return true
end

local function on_hider_cap_command()
    gGlobalSyncTable.hiderCaps = not gGlobalSyncTable.hiderCaps
    djui_chat_message_create("Hider Caps: " .. on_or_off(gGlobalSyncTable.hiderCaps))
    return true
end

local function on_seeker_cap_command()
    gGlobalSyncTable.seekerCaps = not gGlobalSyncTable.seekerCaps
    djui_chat_message_create("Seeker Caps: " .. on_or_off(gGlobalSyncTable.seekerCaps))
    return true
end

local function on_koopa_shell_command()
    gGlobalSyncTable.banKoopaShell = not gGlobalSyncTable.banKoopaShell
    djui_chat_message_create("Koopa Shells: " .. on_or_off(not gGlobalSyncTable.banKoopaShell))
    return true
end

local function on_blj_command()
    gGlobalSyncTable.disableBLJ = not gGlobalSyncTable.disableBLJ
    djui_chat_message_create("BLJS: " .. on_or_off(not gGlobalSyncTable.disableBLJ))
    return true
end


local function level_init()
    local s = gPlayerSyncTable[0]

    pauseExitTimer = 0
    canLeave = false

    if s.seeking then canLeave = true end
end

local function on_pause_exit()
    local s = gPlayerSyncTable[0]

    if not canLeave and not s.seeking then
        djui_popup_create(tostring(math_floor(30 - pauseExitTimer / 30)).." Seconds until you can leave!", 2)
        return false
    end
end

-----------------------
-- network callbacks --
-----------------------

local function on_round_state_changed()
    local rs = gGlobalSyncTable.roundState

    if rs == ROUND_STATE_ACTIVE then
        play_character_sound(gMarioStates[0], CHAR_SOUND_HERE_WE_GO)
    elseif rs == ROUND_STATE_SEEKERS_WIN then
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gMarioStates[0].marioObj.header.gfx.cameraToObject)
    elseif rs == ROUND_STATE_HIDERS_WIN then
        play_sound(SOUND_MENU_CLICK_CHANGE_VIEW, gMarioStates[0].marioObj.header.gfx.cameraToObject)
    end
end

local function on_seeking_changed(tag, oldVal, newVal)
    local m = gMarioStates[tag]
    local npT = gNetworkPlayers[tag]

    -- play sound and create popup if became a seeker
    if newVal and not oldVal then
        play_sound(SOUND_OBJ_BOWSER_LAUGH, m.marioObj.header.gfx.cameraToObject)
        playerColor = network_get_player_text_color_string(m.playerIndex)
        djui_popup_create(playerColor .. npT.name .. "\\#ffa0a0\\ is now a seeker", 2)
        sRoundTimer = 32
    end

    if newVal then
        network_player_set_description(npT, "seeker", 255, 64, 64, 255)
    else
        network_player_set_description(npT, "hider", 128, 128, 128, 255)
    end
end

local function check_touch_tag_allowed(i)
    if gMarioStates[i].action ~= ACT_TELEPORT_FADE_IN and gMarioStates[i].action ~= ACT_TELEPORT_FADE_OUT and gMarioStates[i].action ~= ACT_PULLING_DOOR and gMarioStates[i].action ~= ACT_PUSHING_DOOR and gMarioStates[i].action ~= ACT_WARP_DOOR_SPAWN and gMarioStates[i].action ~= ACT_ENTERING_STAR_DOOR and gMarioStates[i].action ~= ACT_STAR_DANCE_EXIT and gMarioStates[i].action ~= ACT_STAR_DANCE_NO_EXIT and gMarioStates[i].action ~= ACT_STAR_DANCE_WATER and gMarioStates[i].action ~= ACT_PANTING and gMarioStates[i].action ~= ACT_UNINITIALIZED and gMarioStates[i].action ~= ACT_WARP_DOOR_SPAWN then
        return true
    end

    return false
end

local function on_interact(m, obj, intee)
    if intee == INTERACT_PLAYER then

        if not gGlobalSyncTable.touchTag then
            return
        end

        if m ~= gMarioStates[0] then
            for i=0,(MAX_PLAYERS-1) do
                if gNetworkPlayers[i].connected and gNetworkPlayers[i].currAreaSyncValid then
                    if gPlayerSyncTable[m.playerIndex].seeking and not gPlayerSyncTable[i].seeking and obj == gMarioStates[i].marioObj and check_touch_tag_allowed(i)  then
                        gPlayerSyncTable[i].seeking = true

                        network_player_set_description(gNetworkPlayers[i], "seeker", 255, 64, 64, 255)
                    end
                end
            end
        end
    end
end

local function allow_interact(_, _, intee)
    if intee == INTERACT_KOOPA_SHELL and gGlobalSyncTable.banKoopaShell then
        return false
    end
end

function allow_pvp_attack(m1, m2)
    local s1 = gPlayerSyncTable[m1.playerIndex]
    local s2 = gPlayerSyncTable[m2.playerIndex]
    if s1.seeking == s2.seeking then
        return false
    end
    return true
end

gLevelValues.disableActs = true
gLevelValues.zoomOutCameraOnPause = false

-----------
-- hooks --
-----------

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_ON_SCREEN_TRANSITION, screen_transition)
hook_event(HOOK_BEFORE_SET_MARIO_ACTION, before_set_mario_action)
hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_BEFORE_PHYS_STEP, before_phys_step)
hook_event(HOOK_ALLOW_PVP_ATTACK, allow_pvp_attack)
hook_event(HOOK_ON_PVP_ATTACK, on_pvp_attack)
hook_event(HOOK_ON_PLAYER_CONNECTED, on_player_connected)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)
hook_event(HOOK_ON_LEVEL_INIT, level_init)
hook_event(HOOK_ON_PAUSE_EXIT, on_pause_exit) -- timer
hook_event(HOOK_ON_INTERACT, on_interact)
hook_event(HOOK_ALLOW_INTERACT, allow_interact)
hook_event(HOOK_USE_ACT_SELECT, function () return false end)

if network_is_server() then
   hook_chat_command("touch-to-tag", "Turn touch tag on or off", on_touch_tag_command)
   hook_chat_command("hiders-caps", "Turn caps for hiders on or off", on_hider_cap_command)
   hook_chat_command("seekers-caps", "Turn caps for seekers on or off", on_seeker_cap_command)
   hook_chat_command("koopa-shell", "Turn the koopa shell on or off", on_koopa_shell_command)
   hook_chat_command("bljs", "Turn bljs on or off", on_blj_command)
end

-- call functions when certain sync table values change
hook_on_sync_table_change(gGlobalSyncTable, "roundState", 0, on_round_state_changed)

for i = 0, (MAX_PLAYERS - 1) do
    gPlayerSyncTable[i].seeking = true
    hook_on_sync_table_change(gPlayerSyncTable[i], "seeking", i, on_seeking_changed)
    network_player_set_description(gNetworkPlayers[i], "seeker", 255, 64, 64, 255)
end

_G.HideAndSeek = {
    is_player_seeker = function (playerIndex)
        return gPlayerSyncTable[playerIndex].seeking
    end,

    set_player_seeker = function (playerIndex, seeking)
        gPlayerSyncTable[playerIndex].seeking = seeking
    end,
}
