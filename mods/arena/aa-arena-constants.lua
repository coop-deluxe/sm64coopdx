if SM64COOPDX_VERSION == nil then
    local first = false
    hook_event(HOOK_ON_LEVEL_INIT, function()
        if not first then
            first = true
            play_sound(SOUND_MENU_CAMERA_BUZZ, gMarioStates[0].marioObj.header.gfx.cameraToObject)
            djui_chat_message_create("\\#ff7f7f\\This version of Arena is not supported with sm64ex-coop\nas it uses sm64coopdx exclusive Lua functionality.\n\\#dcdcdc\\To play this mod, try out sm64coopdx at\n\\#7f7fff\\https://sm64coopdx.com")
        end
    end)
    return
end

ITEM_NONE        = 0
ITEM_METAL_CAP   = 1
ITEM_HAMMER      = 2
ITEM_FIRE_FLOWER = 3
ITEM_CANNON_BOX  = 4
ITEM_BOBOMB      = 5
ITEM_COIN        = 6
ITEM_MAX         = 7

E_MODEL_HAMMER        = smlua_model_util_get_id("hammer_geo")
E_MODEL_FIRE_FLOWER   = smlua_model_util_get_id("fire_flower")
E_MODEL_CANNON_BOX    = smlua_model_util_get_id("cannon_box_geo")
E_MODEL_CANNON_BALL   = smlua_model_util_get_id("arena_ball_geo")
E_MODEL_FLAG_RED      = smlua_model_util_get_id("arena_flag_red_geo")
E_MODEL_FLAG_BLUE     = smlua_model_util_get_id("arena_flag_blue_geo")
E_MODEL_FLAG_WHITE    = smlua_model_util_get_id("arena_flag_white_geo")
E_MODEL_KOTH          = smlua_model_util_get_id("koth_geo")
E_MODEL_KOTH_ACTIVE   = smlua_model_util_get_id("koth_active_geo")
E_MODEL_SPRING_TOP    = smlua_model_util_get_id("spring_top_geo")
E_MODEL_SPRING_BOTTOM = smlua_model_util_get_id("spring_bottom_geo")

TEX_FLAG = get_texture_info('arena-flag')
TEX_KOTH = get_texture_info('arena-koth')
