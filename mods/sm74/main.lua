-- name: Super Mario 74 (+EE)
-- incompatible: romhack
-- description: This is two romhacks in one.\n\nSuper Mario 74 and Super Mario 74 Extreme Edition.\n\nThere are 60 custom levels, with a total of 308 stars.\n\nUse the chat command '/swap' to swap between EE and normal.\n\nCreated by Lugmillord\n\nPorted to PC by PeachyPeach and jesusyoshi54\n\nPorted to coop by djoslin0

local function on_level_init()
    local np = gNetworkPlayers[0]

    save_file_set_using_backup_slot(np.currAreaIndex ~= 1)
    gMarioStates[0].numStars = save_file_get_total_star_count(get_current_save_file_num()-1,COURSE_MIN-1,COURSE_MAX-1)
    gLevelValues.exitCastleArea = gNetworkPlayers[0].currAreaIndex

    star_areas_replace()
    course_names_swap()
    dialog_swap()

end

local function get_star_collection_dialog()
    return 0
end


local function on_swap_command()
    local np = gNetworkPlayers[0]
    if np.currAreaIndex == 1 then
        djui_chat_message_create("Swapping to Extreme Edition")
    else
        djui_chat_message_create("Swapping to normal edition")
    end
    warp_to_level(np.currLevelNum, np.currAreaIndex ~ 3, np.currActNum)
    return true
end


gLevelValues.entryLevel = LEVEL_CASTLE_COURTYARD
gLevelValues.exitCastleLevel = LEVEL_CASTLE_COURTYARD
gLevelValues.exitCastleWarpNode = 0x40
gLevelValues.skipCreditsAt = LEVEL_BOB

gBehaviorValues.KoopaBobAgility = 6.0
gBehaviorValues.KoopaThiAgility = 6.0
gBehaviorValues.trajectories.KoopaBobTrajectory = get_trajectory('KoopaTHI_path')
gBehaviorValues.trajectories.KoopaThiTrajectory = get_trajectory('KoopaTHI_path_EE')

gBehaviorValues.dialogs.KoopaQuickBobStartDialog = DIALOG_009
gBehaviorValues.dialogs.KoopaQuickThiStartDialog = DIALOG_009
gBehaviorValues.dialogs.KoopaQuickBobWinDialog = DIALOG_031
gBehaviorValues.dialogs.KoopaQuickThiWinDialog = DIALOG_031

gLevelValues.fixCollisionBugs = 1

movtexqc_register('bbh_2_Movtex_0',               0 + 4, 2, 0)
movtexqc_register('ccm_1_Movtex_0',               1 + 4, 1, 0)
movtexqc_register('hmc_1_Movtex_0',               3 + 4, 1, 0)
movtexqc_register('ssl_1_Movtex_0',               4 + 4, 1, 0)
movtexqc_register('ssl_2_Movtex_0',               4 + 4, 2, 0)
movtexqc_register('bob_1_Movtex_0',               5 + 4, 1, 0)
movtexqc_register('sl_1_Movtex_0',                6 + 4, 1, 0)
movtexqc_register('sl_2_Movtex_0',                6 + 4, 2, 0)
movtexqc_register('wdw_1_Movtex_0',               7 + 4, 1, 0)
movtexqc_register('jrb_1_Movtex_0',               8 + 4, 1, 0)
movtexqc_register('bitfs_1_Movtex_0',            15 + 4, 1, 0)
movtexqc_register('ddd_1_Movtex_0',              19 + 4, 1, 0)
movtexqc_register('castle_courtyard_1_Movtex_0', 22 + 4, 1, 0)
movtexqc_register('cotmc_1_Movtex_0',            24 + 4, 1, 0)
movtexqc_register('wmotr_2_Movtex_0',            27 + 4, 2, 0)

smlua_audio_utils_replace_sequence(0x02, 0x11, 80, "02_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x03, 0x1E, 75, "03_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x04, 0x25, 70, "04_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x05, 0x13, 75, "05_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x06, 0x0F, 75, "06_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x08, 0x0B, 70, "08_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x09, 0x0D, 65, "09_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x0B, 0x25, 65, "0B_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x0C, 0x15, 85, "0C_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x11, 0x19, 70, "11_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x13, 0x25, 65, "13_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x18, 0x1C, 75, "18_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x1E, 0x11, 75, "1E_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x21, 0x25, 75, "21_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x22, 0x25, 80, "22_Seq_sm74_custom")
smlua_audio_utils_replace_sequence(0x23, 0x25, 80, "23_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x24, 0x24, 70, "24_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x25, 0x25, 85, "25_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x26, 0x13, 75, "26_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x27, 0x11, 75, "27_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x28, 0x25, 85, "28_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x29, 0x23, 70, "29_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x2A, 0x21, 80, "2A_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x2B, 0x25, 80, "2B_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x2C, 0x25, 70, "2C_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x2D, 0x0E, 75, "2D_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x2E, 0x18, 80, "2E_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x2F, 0x1D, 70, "2F_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x30, 0x23, 65, "30_Seq_sm74EE_custom")
smlua_audio_utils_replace_sequence(0x31, 0x11, 80, "31_Seq_sm74EE_custom")

camera_set_romhack_override(RCO_ALL_EXCEPT_BOWSER)
camera_set_use_course_specific_settings(false)

hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_GET_STAR_COLLECTION_DIALOG, get_star_collection_dialog)
hook_chat_command('swap', "swap between Extreme Edition and normal", on_swap_command)
