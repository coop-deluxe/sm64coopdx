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

burnActions = {
    [ACT_BURNING_FALL] = true,
    [ACT_BURNING_GROUND] = true, --Accounting for when you are on fire since that type of damage is handled differently.
    [ACT_BURNING_JUMP] = true
}
seenPopup = false
local frameCounter = 10
local function mario_update(m)
    if m.playerIndex ~= 0 then return end
    if network_is_server() and frameCounter > 0 then
        if m.controller.buttonDown & L_TRIG ~= 0 then
            gGlobalSyncTable.hardMode = true -- Starts up "Hard Mode." Hold the L button within 10 frames of loading Star Road to activate it.
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






hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_MARIO_UPDATE, mario_update)
