-- name: Water Height Changer
-- description: Use /waterset and /waterget to manipulate water height.

local function on_get_command(msg)
    if not network_is_server() then
        djui_chat_message_create("You need to be the host!")
        return true
    end

    djui_chat_message_create(tostring(get_water_level(0)))
    djui_chat_message_create(tostring(get_water_level(1)))
    return true
end

local function on_set_command(msg)
    if not network_is_server() then
        djui_chat_message_create("You need to be the host!")
        return true
    end

    local num = tonumber(msg)
    if not num then
        djui_chat_message_create("Not a number!")
        return true
    end

    set_water_level(0, num, true)
    set_water_level(1, num, true)
    return true
end

hook_chat_command("waterset", "to set the first two water levels", on_set_command)
hook_chat_command("waterget", "to get the first two water levels", on_get_command)