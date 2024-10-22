if not _G.charSelectExists then
    local first = false
    hook_event(HOOK_ON_LEVEL_INIT, function()
        if not first then
            first = true
            play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource)
            djui_chat_message_create("\\#ffffa0\\[CS] VL-Tone & Cjes Luigi requires Character Select to be enabled.\nPlease rehost with it enabled.")
        end
    end)
    return
end

MOD_VERSION = "v4.1"

E_MODEL_VL = smlua_model_util_get_id("vl_geo")
E_MODEL_CJES = smlua_model_util_get_id("cjes_geo")
