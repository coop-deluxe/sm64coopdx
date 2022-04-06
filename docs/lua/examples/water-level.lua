-- name: Water Height Changer
-- description: Use /waterset and /waterget to manipulate water height.

function on_get_command(msg)
    if not network_is_server() then
        djui_chat_message_create("You need to be the host!")
        return true
    end

    djui_chat_message_create(tostring(get_environment_region(1)))
    djui_chat_message_create(tostring(get_environment_region(2)))
    return false
end

function on_set_command(msg)
    if not network_is_server() then
        djui_chat_message_create("You need to be the host!")
        return true
    end

    local num = tonumber(msg)
    set_environment_region(1, num)
    set_environment_region(2, num)
    return false
end

hook_chat_command("waterset", "to set the first two water levels", on_set_command)
hook_chat_command("waterget", "to get the first two water levels", on_get_command)