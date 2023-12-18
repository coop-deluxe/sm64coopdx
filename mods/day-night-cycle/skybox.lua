if SM64COOPDX_VERSION == nil then return end

local SKYBOX_DAY = 0
local SKYBOX_SUNSET = 1
local SKYBOX_NIGHT = 2

-- standard skyboxes
E_MODEL_SKYBOX_OCEAN_SKY = smlua_model_util_get_id("skybox_ocean_sky_geo")
local E_MODEL_SKYBOX_FLAMING_SKY = smlua_model_util_get_id("skybox_flaming_sky_geo")
local E_MODEL_SKYBOX_UNDERWATER_CITY = smlua_model_util_get_id("skybox_underwater_city_geo")
local E_MODEL_SKYBOX_BELOW_CLOUDS = smlua_model_util_get_id("skybox_below_clouds_geo")
local E_MODEL_SKYBOX_SNOW_MOUNTAINS = smlua_model_util_get_id("skybox_snow_mountains_geo")
local E_MODEL_SKYBOX_DESERT = smlua_model_util_get_id("skybox_desert_geo")
local E_MODEL_SKYBOX_HAUNTED = smlua_model_util_get_id("skybox_haunted_geo")
local E_MODEL_SKYBOX_GREEN_SKY = smlua_model_util_get_id("skybox_green_sky_geo")
local E_MODEL_SKYBOX_ABOVE_CLOUDS = smlua_model_util_get_id("skybox_above_clouds_geo")
local E_MODEL_SKYBOX_PURPLE_SKY = smlua_model_util_get_id("skybox_purple_sky_geo")
local E_MODEL_SKYBOX_SUNRISE = smlua_model_util_get_id("skybox_sunrise_geo")
E_MODEL_SKYBOX_SUNSET = smlua_model_util_get_id("skybox_sunset_geo")
E_MODEL_SKYBOX_NIGHT = smlua_model_util_get_id("skybox_night_geo")

-- below clouds skyboxes
local E_MODEL_SKYBOX_BELOW_CLOUDS_NIGHT = smlua_model_util_get_id("skybox_below_clouds_night_geo")
local E_MODEL_SKYBOX_BELOW_CLOUDS_SUNRISE = smlua_model_util_get_id("skybox_below_clouds_sunrise_geo")
local E_MODEL_SKYBOX_BELOW_CLOUDS_SUNSET = smlua_model_util_get_id("skybox_below_clouds_sunset_geo")

gVanillaSkyboxModels = {
    [BACKGROUND_OCEAN_SKY] = E_MODEL_SKYBOX_OCEAN_SKY,
    [BACKGROUND_FLAMING_SKY] = E_MODEL_SKYBOX_FLAMING_SKY,
    [BACKGROUND_UNDERWATER_CITY] = E_MODEL_SKYBOX_UNDERWATER_CITY,
    [BACKGROUND_BELOW_CLOUDS] = E_MODEL_SKYBOX_BELOW_CLOUDS,
    [BACKGROUND_SNOW_MOUNTAINS] = E_MODEL_SKYBOX_SNOW_MOUNTAINS,
    [BACKGROUND_DESERT] = E_MODEL_SKYBOX_DESERT,
    [BACKGROUND_HAUNTED] = E_MODEL_SKYBOX_HAUNTED,
    [BACKGROUND_GREEN_SKY] = E_MODEL_SKYBOX_GREEN_SKY,
    [BACKGROUND_ABOVE_CLOUDS] = E_MODEL_SKYBOX_ABOVE_CLOUDS,
    [BACKGROUND_PURPLE_SKY] = E_MODEL_SKYBOX_PURPLE_SKY
}

-- localize functions to improve performance
local get_skybox,obj_set_model_extended,set_override_far,obj_mark_for_deletion,vec3f_to_object_pos,clampf,cur_obj_hide,cur_obj_unhide = get_skybox,obj_set_model_extended,set_override_far,obj_mark_for_deletion,vec3f_to_object_pos,clampf,cur_obj_hide,cur_obj_unhide

--- @param o Object
function bhv_skybox_init(o)
    o.header.gfx.skipInViewCheck = true

    local skybox = get_skybox()
    if o.oBehParams2ndByte == SKYBOX_DAY then
        obj_set_model_extended(o, gVanillaSkyboxModels[skybox] or E_MODEL_SKYBOX_OCEAN_SKY)
    elseif o.oBehParams2ndByte == SKYBOX_NIGHT then
        obj_set_model_extended(o, if_then_else(skybox == BACKGROUND_BELOW_CLOUDS, E_MODEL_SKYBOX_BELOW_CLOUDS_NIGHT, E_MODEL_SKYBOX_NIGHT))
    end

    set_override_far(100000)
end

--- @param o Object
function bhv_skybox_loop(o)
    if not gGlobalSyncTable.dncEnabled then
        obj_mark_for_deletion(o)
        return
    end

    vec3f_to_object_pos(o, gLakituState.pos)

    local skybox = get_skybox()

    -- do not rotate BITDW skybox
    if skybox == BACKGROUND_GREEN_SKY then return end

    local minutes = (gGlobalSyncTable.time / MINUTE) % 24

    if o.oBehParams2ndByte ~= SKYBOX_SUNSET then
        o.oFaceAngleYaw = gGlobalSyncTable.time * 2
    else
        if minutes < 12 then
            o.oFaceAngleYaw = 0
        else
            o.oFaceAngleYaw = 0x8000
        end
    end


    if o.oBehParams2ndByte == SKYBOX_DAY then
        if minutes >= HOUR_SUNRISE_END and minutes <= HOUR_DAY_START then
            o.oOpacity = lerp_round(0, 255, clampf((minutes - HOUR_SUNRISE_END) / HOUR_SUNSET_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_SUNSET_END then
            o.oOpacity = lerp_round(255, 0, clampf((minutes - HOUR_SUNSET_START) / HOUR_SUNSET_DURATION, 0, 1))
        elseif minutes < HOUR_SUNRISE_END or minutes > HOUR_NIGHT_START then
            o.oOpacity = 0
        elseif minutes > HOUR_DAY_START and minutes < HOUR_SUNSET_START then
            o.oOpacity = 255
        end
    elseif o.oBehParams2ndByte == SKYBOX_SUNSET then
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            o.oOpacity = lerp_round(0, 255, clampf((minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNRISE_END and minutes <= HOUR_DAY_START then
            o.oOpacity = lerp_round(255, 0, clampf((minutes - HOUR_SUNRISE_END) / HOUR_SUNRISE_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_SUNSET_END then
            o.oOpacity = lerp_round(0, 255, clampf((minutes - HOUR_SUNSET_START) / HOUR_SUNSET_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            o.oOpacity = 255
        else
            o.oOpacity = 0
        end

        if minutes < 12 then
            obj_set_model_extended(o, if_then_else(skybox == BACKGROUND_BELOW_CLOUDS, E_MODEL_SKYBOX_BELOW_CLOUDS_SUNRISE, E_MODEL_SKYBOX_SUNRISE))
        else
            obj_set_model_extended(o, if_then_else(skybox == BACKGROUND_BELOW_CLOUDS, E_MODEL_SKYBOX_BELOW_CLOUDS_SUNSET, E_MODEL_SKYBOX_SUNSET))
        end
    elseif o.oBehParams2ndByte == SKYBOX_NIGHT then
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            o.oOpacity = lerp_round(255, 0, clampf((minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            o.oOpacity = lerp_round(0, 255, clampf((minutes - HOUR_SUNSET_END) / HOUR_SUNSET_DURATION, 0, 1))
        elseif minutes > HOUR_SUNRISE_END and minutes < HOUR_SUNSET_END then
            o.oOpacity = 0
        elseif minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_START then
            o.oOpacity = 255
        end
    end

    if o.oOpacity == 0 then
        cur_obj_hide()
    else
        cur_obj_unhide()
    end
end