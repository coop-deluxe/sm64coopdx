gGlobalSyncTable.hardMode = false

function on_level_init()
    local m = gMarioStates[0]
    local np = gNetworkPlayers[0]
    if gGlobalSyncTable.hardMode then
        gMarioStates[0].numStars = save_file_get_total_star_count(get_current_save_file_num() - 1, COURSE_MIN - 1,
            COURSE_MAX - 1)
        gLevelValues.exitCastleArea = gNetworkPlayers[0].currAreaIndex
    end
end

burnActions = { --Accounting for when you are on fire since that type of damage is handled differently.
    [ACT_BURNING_FALL] = true,
    [ACT_BURNING_GROUND] = true,
    [ACT_BURNING_JUMP] = true
}
seenPopup = false
local frameCounter = 10
local function mario_update(m)
    if m.playerIndex ~= 0 then return end
    if network_is_server() and frameCounter > 0 then
        if m.controller.buttonDown & L_TRIG ~= 0 then
            gGlobalSyncTable.hardMode = true -- Starts up "Hard Mode" on Hack Boot. Hold the L button within 10 frames of loading Star Road to activate it.
            frameCounter = 0
            save_file_set_using_backup_slot(gGlobalSyncTable.hardMode)
            save_file_reload(1)
            djui_popup_create("\\#ff0000\\HARD MODE\\#dcdcdc\\ Activated", 1)
            play_sound(SOUND_MENU_MARIO_CASTLE_WARP + 1 << 0, { x = 0, y = 0, z = 0 })
        end
        frameCounter = frameCounter - 1
    end
    if not gGlobalSyncTable.hardMode then return end
    if not seenPopup and not network_is_server() then
        save_file_set_using_backup_slot(gGlobalSyncTable.hardMode)
        save_file_reload(1)
        djui_popup_create("You have joined a \\#ff0000\\HARD MODE\\#dcdcdc\\ lobby.", 3)
        play_sound(SOUND_MENU_MARIO_CASTLE_WARP + 1 << 0, { x = 0, y = 0, z = 0 })
        seenPopup = true
    end
    if m.hurtCounter > 0 or burnActions[m.action] then
        m.hurtCounter = 64 -- Damage Check. Hard Mode is a OHKO mode.
        m.healCounter = 0  -- Prevents you from healing from a coin or any health regen object via landing on one while dying.
    end
    if not gGlobalSyncTable.hardMode then return false end
end

function hard_mode_menu(_, value)
    gGlobalSyncTable.hardMode = value
    save_file_set_using_backup_slot(gGlobalSyncTable.hardMode)
    save_file_reload(1)
    djui_popup_create(value and "\\#ff0000\\HARD MODE\\#dcdcdc\\ Activated" or "You are currently in NORMAL MODE.", 1)
    play_sound(SOUND_MENU_MARIO_CASTLE_WARP + 1 << 0, { x = 0, y = 0, z = 0 })
    warp_to_warpnode(16, 1, 0, 128)
end

function dialog_box_colors(id)
    if changed_dialogs[id] and gGlobalSyncTable.hardMode then -- red dialog box (Thank you  again Emmi)
        set_dialog_override_color(255, 100, 100, 180, 255, 255, 255, 255)
    else
        reset_dialog_override_color()
    end
end

if network_is_server() then
    hook_mod_menu_checkbox("Hard Mode", gGlobalSyncTable.hardMode, hard_mode_menu)
end

local function menu_hud_render()
    if is_game_paused() and gGlobalSyncTable.hardMode then
        djui_hud_set_font(FONT_CUSTOM_HUD)
        djui_hud_set_color(0xdc, 0xdc, 0xdc, 255)
        local height = djui_hud_get_screen_height()
        djui_hud_print_text("Hard Mode", 40, height - 130, 4)
    end
end
-- Main loop
local function hud_render()
    djui_hud_set_resolution(RESOLUTION_DJUI)
    menu_hud_render()
end


hook_event(HOOK_ON_HUD_RENDER, hud_render)
hook_event(HOOK_ON_DIALOG, dialog_box_colors)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_MARIO_UPDATE, mario_update)
