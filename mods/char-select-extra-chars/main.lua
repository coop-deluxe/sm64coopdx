-- name: [CS] Extra Characters
-- description: [CS] Extra Characters\nBy Coop Deluxe Team\n\nThis Character Select pack adds other characters from the Mario series! Currently, The only character that has been added is \\#ff46a1\\Toadette\\#dcdcdc\\.
-- deluxe: true

if SM64COOPDX_VERSION == nil then
    local first = false
    hook_event(HOOK_ON_LEVEL_INIT, function()
        if not first then
            first = true
            play_sound(SOUND_MENU_CAMERA_BUZZ, gMarioStates[0].marioObj.header.gfx.cameraToObject)
            djui_chat_message_create("\\#ffa0a0\\Extra Characters is not supported with sm64ex-coop\nas it uses sm64coopdx exclusive Lua functionality.\n\\#dcdcdc\\To play this mod, try out sm64coopdx at\n\\#7f7fff\\https://sm64coopdx.com")
        end
    end)
    return
end
if not _G.charSelectExists then
    local first = false
    hook_event(HOOK_ON_LEVEL_INIT, function()
        if not first then
            first = true
            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
            djui_chat_message_create("\\#ffffa0\\Extra Characters requires Character Select to be enabled.\nPlease rehost with it enabled.")
        end
    end)
    return
end

local E_MODEL_TOADETTE = smlua_model_util_get_id("toadette_geo")

local TEX_TOADETTE = get_texture_info("toadette_icon")

local VOICETABLE_TOADETTE = {
    [CHAR_SOUND_ATTACKED] = "toadette_hurt_hard.ogg",
    [CHAR_SOUND_GROUND_POUND_WAH] = "toadette_wah.ogg",
    [CHAR_SOUND_HAHA] = "toadette_haahaa.ogg",
    [CHAR_SOUND_HAHA_2] = "toadette_haahaa.ogg",
    [CHAR_SOUND_HERE_WE_GO] = "toadette_here_we_go.ogg",
    [CHAR_SOUND_HOOHOO] = "toadette_jump.ogg",
    [CHAR_SOUND_ON_FIRE] = "toadette_burning.ogg",
    [CHAR_SOUND_OOOF] = "toadette_oof.ogg",
    [CHAR_SOUND_OOOF2] = "toadette_oof_2.ogg",
    [CHAR_SOUND_PUNCH_HOO] = "toadette_hoo.ogg",
    [CHAR_SOUND_PUNCH_WAH] = "toadette_wah.ogg",
    [CHAR_SOUND_PUNCH_YAH] = "toadette_yah.ogg",
    [CHAR_SOUND_SO_LONGA_BOWSER] = "toadette_bowser.ogg",
    [CHAR_SOUND_TWIRL_BOUNCE] = "toadette_boing.ogg",
    [CHAR_SOUND_WAAAOOOW] = "toadette_fall.ogg",
    [CHAR_SOUND_WAH2] = "toadette_jump.ogg",
    [CHAR_SOUND_WHOA] = "toadette_woah.ogg",
    [CHAR_SOUND_YAHOO] = "toadette_yahoo.ogg",
    [CHAR_SOUND_YAHOO_WAHA_YIPPEE] = {"toadette_yahoo.ogg", "toadette_yippee.ogg"},
    [CHAR_SOUND_YAH_WAH_HOO] = {"toadette_yah.ogg", "toadette_wah.ogg", "toadette_hoo.ogg"},
    [CHAR_SOUND_OKEY_DOKEY] = "toadette_okay.ogg",
    [CHAR_SOUND_LETS_A_GO] = "toadette_lets_a_go.ogg",
    [CHAR_SOUND_DYING] = "toadette_dead.ogg",
    [CHAR_SOUND_DROWNING] = "toadette_drowning.ogg",
    [CHAR_SOUND_EEUH] = "toadette_eugh.ogg",
    [CHAR_SOUND_MAMA_MIA] = "toadette_ooh.ogg",
    [CHAR_SOUND_DOH] = "toadette_oof.ogg",
    [CHAR_SOUND_HRMM] = "toadette_pickup.ogg",
    [CHAR_SOUND_PANTING] = "toadette_pant.ogg",
    [CHAR_SOUND_UH] = "toadette_oof.ogg"
}

_G.charSelect.character_add("Toadette", {"A female toad who debutted in", "2003 as a partner for Toad in", "Mario Kart: Double Dash!"}, "Toadette", { r = 255, g = 70, b = 161 }, E_MODEL_TOADETTE, CT_TOAD, TEX_TOADETTE)
_G.charSelect.character_add_voice(E_MODEL_TOADETTE, VOICETABLE_TOADETTE)

hook_event(HOOK_MARIO_UPDATE, function (m)
    if _G.charSelect.character_get_voice(m) == VOICETABLE_TOADETTE then _G.charSelect.voice.snore(m) end
end)
hook_event(HOOK_CHARACTER_SOUND, function (m, sound)
    if _G.charSelect.character_get_voice(m) == VOICETABLE_TOADETTE then return _G.charSelect.voice.sound(m, sound) end
end)