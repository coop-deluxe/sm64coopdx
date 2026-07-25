-- name: Water Height Changer
-- description: Use /waterset and /waterget to manipulate water height.

local function on_get_command(msg)
    if not network_is_server() then
        command_message_create("You need to be the host!", CONSOLE_MESSAGE_ERROR)
        return true
    end

    command_message_create(tostring(get_water_level(0)))
    command_message_create(tostring(get_water_level(1)))
    return true
end

local function on_set_command(msg)
    if not network_is_server() then
        command_message_create("You need to be the host!", CONSOLE_MESSAGE_ERROR)
        return true
    end

    local num = tonumber(msg)
    if not num then
        command_message_create("Not a number!", CONSOLE_MESSAGE_ERROR)
        return true
    end

    set_water_level(0, num, true)
    set_water_level(1, num, true)
    return true
end

hook_chat_command("waterset", "to set the first two water levels", on_set_command)
hook_chat_command("waterget", "to get the first two water levels", on_get_command)