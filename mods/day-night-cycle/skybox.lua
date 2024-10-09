-- localize functions to improve performance
local set_override_far,obj_mark_for_deletion,vec3f_to_object_pos,get_skybox,clampf = set_override_far,obj_mark_for_deletion,vec3f_to_object_pos,get_skybox,clampf

--- @param o Object
function bhv_dnc_skybox_init(o)
    o.header.gfx.skipInViewCheck = true
    set_override_far(200000)
end

--- @param o Object
function bhv_dnc_skybox_loop(o)
    if not is_dnc_enabled() then
        obj_mark_for_deletion(o)
        return
    end

    vec3f_to_object_pos(o, gLakituState.pos)

    local skybox = get_skybox()

    -- do not rotate BITDW skybox
    if skybox == BACKGROUND_GREEN_SKY then return end

    local minutes = get_time_minutes()

    o.oFaceAngleYaw = (minutes / 24) * 0x10000

    if o.oBehParams2ndByte == SKYBOX_DAY then
        o.oOpacity = 255
    elseif o.oBehParams2ndByte == SKYBOX_SUNSET then
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            o.oOpacity = lerp_ceil(0, 255, clampf((minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNRISE_END and minutes <= HOUR_DAY_START then
            o.oOpacity = lerp_ceil(255, 0, clampf((minutes - HOUR_SUNRISE_END) / HOUR_SUNRISE_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNSET_START and minutes <= HOUR_SUNSET_END then
            o.oOpacity = lerp_ceil(0, 255, clampf((minutes - HOUR_SUNSET_START) / HOUR_SUNSET_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            o.oOpacity = 255
        else
            o.oOpacity = 0
        end

        if minutes < 12 then
            o.oAnimState = if_then_else(skybox == BACKGROUND_BELOW_CLOUDS, BACKGROUND_BELOW_CLOUDS_SUNRISE, BACKGROUND_SUNRISE)
        else
            o.oAnimState = if_then_else(skybox == BACKGROUND_BELOW_CLOUDS, BACKGROUND_BELOW_CLOUDS_SUNSET, BACKGROUND_SUNSET)
        end

        o.oFaceAngleYaw = o.oFaceAngleYaw - if_then_else(minutes < 12, 0x3000, 0x6000)
    elseif o.oBehParams2ndByte == SKYBOX_NIGHT then
        if minutes >= HOUR_SUNRISE_START and minutes <= HOUR_SUNRISE_END then
            o.oOpacity = lerp_ceil(255, 0, clampf((minutes - HOUR_SUNRISE_START) / HOUR_SUNRISE_DURATION, 0, 1))
        elseif minutes >= HOUR_SUNSET_END and minutes <= HOUR_NIGHT_START then
            o.oOpacity = lerp_ceil(0, 255, clampf((minutes - HOUR_SUNSET_END) / HOUR_SUNSET_DURATION, 0, 1))
        elseif minutes > HOUR_SUNRISE_END and minutes < HOUR_SUNSET_END then
            o.oOpacity = 0
        elseif minutes > HOUR_NIGHT_START or minutes < HOUR_SUNRISE_START then
            o.oOpacity = 255
        end
    end
end