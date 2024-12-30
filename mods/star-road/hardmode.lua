local sBurnActions = { --Accounting for when you are on fire since that type of damage is handled differently.
    [ACT_BURNING_FALL] = true,
    [ACT_BURNING_GROUND] = true,
    [ACT_BURNING_JUMP] = true
}

local frameCounter = 10
local seenPopup = false

--- @param m MarioState
function mario_update_hardmode(m)
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

    if m.hurtCounter > 0 or sBurnActions[m.action] then
        m.health = 0
        m.healCounter = 0 -- prevents you from healing from a coin or any health regen object via landing on one while dying
    end
end

---@param m MarioState
function before_mario_update_hardmode(m)
    if not gGlobalSyncTable.hardMode then return end

    if m.action & ACT_GROUP_MASK == ACT_GROUP_SUBMERGED and m.area.terrainType ~= TERRAIN_SNOW then
        change = (m.pos.y < m.waterLevel - 140 and 1 or -0x1A)
        m.health = m.health + change
    end
end

function on_level_init_hardmode()
    if gGlobalSyncTable.hardMode then
        gMarioStates[0].numStars = save_file_get_total_star_count(get_current_save_file_num() - 1, COURSE_MIN - 1,
            COURSE_MAX - 1)
        gLevelValues.exitCastleArea = gNetworkPlayers[0].currAreaIndex
    end
end

function on_hud_render_hardmode()
    if not is_game_paused() or not gGlobalSyncTable.hardMode then return end

    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_HUD)

    djui_hud_set_color(255, 255, 255, 255)
    local height = djui_hud_get_screen_height()
    djui_hud_print_text("HARD MODE", 10, height - 30, 1)
end

function on_dialog_hardmode(dialogID)
    if dialogID == DIALOG_169 and gGlobalSyncTable.hardMode then -- red dialog box (Thank you again Emmi)
        set_dialog_override_color(255, 100, 100, 180, 255, 255, 255, 255)
    else
        reset_dialog_override_color()
    end
end


function hard_mode_menu(_, value)
    gGlobalSyncTable.hardMode = value
    save_file_set_using_backup_slot(gGlobalSyncTable.hardMode)
    save_file_reload(1)
    djui_popup_create(value and "\\#ff0000\\HARD MODE\\#dcdcdc\\ enabled." or "\\#ff0000\\HARD MODE\\#dcdcdc\\ disabled.", 1)
    play_sound(SOUND_MENU_MARIO_CASTLE_WARP, { x = 0, y = 0, z = 0 })
    warp_to_start_level()
end