-- name: Star Road
-- description: Star Road is a romhack created by SKELUX\n\nwww.youtube.com/c/Skelux\n\nThere are 23 custom levels, with a total of 130 stars.\n\nPorted to PC by AloXado320, PeachyPeach, and PrinceFrizzy\n\nPorted to coop by djoslin0, PrinceFrizzy, and Isaac.
-- incompatible: romhack

--------------
-- movtexs --
--------------

movtexqc_register('bbh_1_Movtex_0',              LEVEL_BBH,              1, 0)
movtexqc_register('ccm_1_Movtex_0',              LEVEL_CCM,              1, 0)
movtexqc_register('hmc_1_Movtex_0',              LEVEL_HMC,              1, 0)
movtexqc_register('ssl_1_Movtex_0',              LEVEL_SSL,              1, 0)
movtexqc_register('bob_1_Movtex_0',              LEVEL_BOB,              1, 0)
movtexqc_register('sl_1_Movtex_0',               LEVEL_SL,               1, 0)
movtexqc_register('jrb_1_Movtex_0',              LEVEL_JRB,              1, 0)
movtexqc_register('castle_grounds_1_Movtex_0',   LEVEL_CASTLE_GROUNDS,   1, 0)
movtexqc_register('lll_1_Movtex_0',              LEVEL_LLL,              1, 0)
movtexqc_register('wf_1_Movtex_0',               LEVEL_WF,               1, 0)
movtexqc_register('ending_1_Movtex_0',           LEVEL_ENDING,           1, 0)
movtexqc_register('castle_courtyard_1_Movtex_0', LEVEL_CASTLE_COURTYARD, 1, 0)
movtexqc_register('pss_1_Movtex_0',              LEVEL_PSS,              1, 0)
movtexqc_register('cotmc_1_Movtex_0',            LEVEL_COTMC,            1, 0)
movtexqc_register('totwc_1_Movtex_0',            LEVEL_TOTWC,            1, 0)
movtexqc_register('wmotr_1_Movtex_0',            LEVEL_WMOTR,            1, 0)

------------------
-- extra levels --
------------------

LEVEL_ZERO_LIFE = level_register('level_zerolife_entry', COURSE_NONE, 'ZERO LIFE', 'zl', 28000, 0x28, 0x28, 0x28)

---------------------------
-- force server settings --
---------------------------

gLevelValues.fixCollisionBugs = true
gLevelValues.vanishCapSequence = 0x32

gServerSettings.skipIntro = 1

-----------
-- music --
-----------

-- These have a custom entry in the Star road sequences.json patch. But aren't actually ripped.
--smlua_audio_utils_replace_sequence(0x01, 0x22, 80, "01_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_COLLECT_STAR

smlua_audio_utils_replace_sequence(0x02, 0x25, 80, "02_Seq_smsrdeluxe_custom") -- SEQ_MENU_TITLE_SCREEN
smlua_audio_utils_replace_sequence(0x03, 0x25, 75, "03_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_GRASS
smlua_audio_utils_replace_sequence(0x04, 0x25, 70, "04_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_INSIDE_CASTLE
smlua_audio_utils_replace_sequence(0x05, 0x25, 75, "05_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_WATER
smlua_audio_utils_replace_sequence(0x06, 0x25, 75, "06_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_HOT
smlua_audio_utils_replace_sequence(0x07, 0x19, 75, "07_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_BOSS_KOOPA
smlua_audio_utils_replace_sequence(0x08, 0x25, 70, "08_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_SNOW
smlua_audio_utils_replace_sequence(0x09, 0x0D, 65, "09_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_SLIDE, Is this possibly just normal slide? TODO: Verify this later on.
smlua_audio_utils_replace_sequence(0x0B, 0x14, 65, "0B_Seq_smsrdeluxe_custom") -- SEQ_EVENT_PIRANHA_PLANT
smlua_audio_utils_replace_sequence(0x0C, 0x17, 85, "0C_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_UNDERGROUND
smlua_audio_utils_replace_sequence(0x0D, 0x25, 75, "0D_Seq_smsrdeluxe_custom") -- SEQ_MENU_STAR_SELECT, Star Road has music here instead of the original intro effect.
smlua_audio_utils_replace_sequence(0x0E, 0x25, 65, "0E_Seq_smsrdeluxe_custom") -- SEQ_EVENT_POWERUP
smlua_audio_utils_replace_sequence(0x0F, 0x25, 70, "0F_Seq_smsrdeluxe_custom") -- SEQ_EVENT_METAL_CAP
smlua_audio_utils_replace_sequence(0x10, 0x25, 65, "10_Seq_smsrdeluxe_custom") -- SEQ_EVENT_KOOPA_MESSAGE
smlua_audio_utils_replace_sequence(0x11, 0x25, 70, "11_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_KOOPA_ROAD
smlua_audio_utils_replace_sequence(0x12, 0x25, 70, "12_Seq_smsrdeluxe_custom") -- SEQ_EVENT_HIGH_SCORE
smlua_audio_utils_replace_sequence(0x13, 0x1E, 65, "13_Seq_smsrdeluxe_custom") -- SEQ_EVENT_MERRY_GO_ROUND
smlua_audio_utils_replace_sequence(0x14, 0x1A, 80, "14_Seq_smsrdeluxe_custom") -- SEQ_EVENT_RACE
smlua_audio_utils_replace_sequence(0x15, 0x0E, 70, "15_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_STAR_SPAWN
smlua_audio_utils_replace_sequence(0x16, 0x25, 85, "16_Seq_smsrdeluxe_custom") -- SEQ_EVENT_BOSS
smlua_audio_utils_replace_sequence(0x17, 0x1A, 75, "17_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_COLLECT_KEY
smlua_audio_utils_replace_sequence(0x18, 0x25, 75, "18_Seq_smsrdeluxe_custom") -- SEQ_EVENT_ENDLESS_STAIRS
smlua_audio_utils_replace_sequence(0x19, 0x11, 85, "19_Seq_smsrdeluxe_custom") -- SEQ_LEVEL_BOSS_KOOPA_FINAL
smlua_audio_utils_replace_sequence(0x1A, 0x25, 70, "1A_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_CREDITS
smlua_audio_utils_replace_sequence(0x1B, 0x14, 80, "1B_Seq_smsrdeluxe_custom") -- SEQ_EVENT_SOLVE_PUZZLE
smlua_audio_utils_replace_sequence(0x1C, 0x20, 80, "1C_Seq_smsrdeluxe_custom") -- SEQ_EVENT_TOAD_MESSAGE
smlua_audio_utils_replace_sequence(0x1D, 0x11, 70, "1D_Seq_smsrdeluxe_custom") -- SEQ_EVENT_PEACH_MESSAGE
smlua_audio_utils_replace_sequence(0x1E, 0x25, 75, "1E_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_INTRO
smlua_audio_utils_replace_sequence(0x1F, 0x25, 80, "1F_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_VICTORY
smlua_audio_utils_replace_sequence(0x20, 0x25, 70, "20_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_ENDING
smlua_audio_utils_replace_sequence(0x21, 0x25, 65, "21_Seq_smsrdeluxe_custom") -- SEQ_MENU_FILE_SELECT
smlua_audio_utils_replace_sequence(0x22, 0x11, 80, "22_Seq_smsrdeluxe_custom") -- SEQ_EVENT_CUTSCENE_LAKITU

-- TODO: See if we can figure out the original volumes for the things below this point.
smlua_audio_utils_replace_sequence(0x23, 0x25, 80, "23_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x24, 0x11, 70, "24_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x25, 0x25, 85, "25_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x26, 0x25, 75, "26_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x27, 0x25, 75, "27_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x28, 0x25, 85, "28_Seq_smsrdeluxe_custom") -- One of Simpleflips outros. (Don't know the actual song name.)
smlua_audio_utils_replace_sequence(0x29, 0x25, 70, "29_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x2A, 0x11, 80, "2A_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x2B, 0x1B, 80, "2B_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x2C, 0x25, 70, "2C_Seq_smsrdeluxe_custom")

-- We don't know the correct instruments for these.
smlua_audio_utils_replace_sequence(0x2D, 0x25, 75, "2D_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x2E, 0x12, 80, "2E_Seq_smsrdeluxe_custom") -- Final Boss Music
smlua_audio_utils_replace_sequence(0x2F, 0x25, 70, "2F_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x30, 0x25, 65, "30_Seq_smsrdeluxe_custom") -- Game Over Area
smlua_audio_utils_replace_sequence(0x31, 0x25, 80, "31_Seq_smsrdeluxe_custom")
smlua_audio_utils_replace_sequence(0x32, 0x25, 80, "32_Seq_smsrdeluxe_custom")

------------
-- camera --
------------
camera_set_use_course_specific_settings(false)

----------------------------------

function mario_update_local(m)
    override_camera()
end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end
end

function on_death()
    local m = gMarioStates[0]
    if m.numLives <= 0 then
        warp_to_level(LEVEL_ZERO_LIFE, 1, 0)
        m.numLives = 4
    end
end

function on_warp_and_init() -- 130 stars castle grounds music
    local m = gMarioStates[0]
    if m.numStars >= 130 and gNetworkPlayers[0].currLevelNum == LEVEL_CASTLE_GROUNDS then
        play_music(0, 0x2F, 1)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_DEATH, on_death)
hook_event(HOOK_ON_LEVEL_INIT, on_warp_and_init)
hook_event(HOOK_ON_WARP, on_warp_and_init)