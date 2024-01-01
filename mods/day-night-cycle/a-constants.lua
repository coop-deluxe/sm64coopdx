if SM64COOPDX_VERSION == nil then
    local first = false
    hook_event(HOOK_ON_LEVEL_INIT, function()
        if not first then
            first = true
            play_sound(SOUND_MENU_CAMERA_BUZZ, gMarioStates[0].marioObj.header.gfx.cameraToObject)
            djui_chat_message_create("\\#ff7f7f\\Day Night Cycle is no longer supported with sm64ex-coop\nas it uses sm64coopdx exclusive Lua functionality.\n\\#dcdcdc\\To play this mod, try out sm64coopdx at\n\\#7f7fff\\https://sm64coopdx.com")
        end
    end)
    return
end

-- time constants
SECOND = 30
MINUTE = SECOND * 60

HOUR_SUNRISE_START = 4
HOUR_SUNRISE_END = 5
HOUR_SUNRISE_DURATION = HOUR_SUNRISE_END - HOUR_SUNRISE_START

HOUR_SUNSET_START = 19
HOUR_SUNSET_END = 20
HOUR_SUNSET_DURATION = HOUR_SUNSET_END - HOUR_SUNSET_START

HOUR_DAY_START = 6
HOUR_NIGHT_START = 21

REAL_MINUTE = 1 / 60

-- lighting direction constants
DIR_DARK = 0.6
DIR_BRIGHT = 1

-- color constants
COLOR_NIGHT   = { r = 70,  g = 75,  b = 100 }
COLOR_SUNRISE = { r = 255, g = 255, b = 200 }
COLOR_DAY     = { r = 255, g = 255, b = 255 }
COLOR_SUNSET  = { r = 255, g = 155, b = 100 }

FOG_COLOR_NIGHT = { r = 30, g = 30, b = 50 }

COLOR_DISPLAY_DARK   = { r = 48,  g = 90,  b = 200 }
COLOR_DISPLAY_BRIGHT = { r = 255, g = 255, b = 80  }

-- skybox constants
SKYBOX_SCALE = 200

SKYBOX_DAY = 0
SKYBOX_SUNSET = 1
SKYBOX_NIGHT = 2

-- standard skyboxes
E_MODEL_SKYBOX_OCEAN_SKY = smlua_model_util_get_id("skybox_ocean_sky_geo")
E_MODEL_SKYBOX_FLAMING_SKY = smlua_model_util_get_id("skybox_flaming_sky_geo")
E_MODEL_SKYBOX_UNDERWATER_CITY = smlua_model_util_get_id("skybox_underwater_city_geo")
E_MODEL_SKYBOX_BELOW_CLOUDS = smlua_model_util_get_id("skybox_below_clouds_geo")
E_MODEL_SKYBOX_SNOW_MOUNTAINS = smlua_model_util_get_id("skybox_snow_mountains_geo")
E_MODEL_SKYBOX_DESERT = smlua_model_util_get_id("skybox_desert_geo")
E_MODEL_SKYBOX_HAUNTED = smlua_model_util_get_id("skybox_haunted_geo")
E_MODEL_SKYBOX_GREEN_SKY = smlua_model_util_get_id("skybox_green_sky_geo")
E_MODEL_SKYBOX_ABOVE_CLOUDS = smlua_model_util_get_id("skybox_above_clouds_geo")
E_MODEL_SKYBOX_PURPLE_SKY = smlua_model_util_get_id("skybox_purple_sky_geo")
E_MODEL_SKYBOX_SUNRISE = smlua_model_util_get_id("skybox_sunrise_geo")
E_MODEL_SKYBOX_SUNSET = smlua_model_util_get_id("skybox_sunset_geo")
E_MODEL_SKYBOX_NIGHT = smlua_model_util_get_id("skybox_night_geo")

-- below clouds skyboxes
E_MODEL_SKYBOX_BELOW_CLOUDS_NIGHT = smlua_model_util_get_id("skybox_below_clouds_night_geo")
E_MODEL_SKYBOX_BELOW_CLOUDS_SUNRISE = smlua_model_util_get_id("skybox_below_clouds_sunrise_geo")
E_MODEL_SKYBOX_BELOW_CLOUDS_SUNSET = smlua_model_util_get_id("skybox_below_clouds_sunset_geo")