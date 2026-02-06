--- Misc Functions ---

--- @param m MarioState
--- @param name string
--- @param accel? number
--- Plays a custom animation for MarioState `m`
function play_custom_anim(m, name, accel)
    accel = accel or 0x10000

    m.marioObj.header.gfx.animInfo.animAccel = accel

    if (smlua_anim_util_get_current_animation_name(m.marioObj) ~= name or m.marioObj.header.gfx.animInfo.animID ~= -1) then
        m.marioObj.header.gfx.animInfo.animID = -1
        set_anim_to_frame(m, 0)
    end

    smlua_anim_util_set_animation(m.marioObj, name)
end

--- @param str string
--- @param splitAt? string
function string.split(str, splitAt)
    if splitAt == nil then
        splitAt = " "
    end
    local result = {}
    for match in str:gmatch(string.format("[^%s]+", splitAt)) do
        table.insert(result, match)
    end
    return result
end