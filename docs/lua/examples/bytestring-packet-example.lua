-- name: Bytestring Packet Example
-- description: Shows a way to send and receive bytestring packets. Send a packet with /example [1|2].

-- Here is the lua documentation for string.pack() and string.unpack():
--    https://www.lua.org/manual/5.3/manual.html#6.4.2
-- It explains the different format strings used in this example mod.

---------------------------------------------------------------------------------------------------

local PACKET_EXAMPLE_1 = 1
local PACKET_EXAMPLE_2 = 2

---------------------------------------------------------------------------------------------------

function send_example_1(byte_param, short_param, long_param, float_param, double_param)

    local bytestring = ''
        -------------- PACKET ID --------------
        .. string.pack("<B", PACKET_EXAMPLE_1)
        ---------------------------------------
        .. string.pack("<b", byte_param)
        .. string.pack("<h", short_param)
        .. string.pack("<l", long_param)
        .. string.pack("<f", float_param)
        .. string.pack("<d", double_param)
        ---------------------------------------

    network_send_bytestring(true, bytestring)

    djui_chat_message_create('Sent bytestring packet example 1:')
    djui_chat_message_create('    byte_param:   ' .. byte_param)
    djui_chat_message_create('    short_param:  ' .. short_param)
    djui_chat_message_create('    long_param:   ' .. long_param)
    djui_chat_message_create('    float_param:  ' .. float_param)
    djui_chat_message_create('    double_param: ' .. double_param)
end

function on_packet_bytestring_receive_example_1(bytestring)
    local offset = 1

    local function unpack(fmt)
        local value
        value, offset = string.unpack(fmt, bytestring, offset)
        return value
    end

    -------------- PACKET ID --------------
    local packet_id    = unpack("<B")
    ---------------------------------------
    local byte_param   = unpack("<b")
    local short_param  = unpack("<h")
    local long_param   = unpack("<l")
    local float_param  = unpack("<f")
    local double_param = unpack("<d")
    ---------------------------------------

    djui_chat_message_create('Received bytestring packet example 1:')
    djui_chat_message_create('    byte_param:   ' .. byte_param)
    djui_chat_message_create('    short_param:  ' .. short_param)
    djui_chat_message_create('    long_param:   ' .. long_param)
    djui_chat_message_create('    float_param:  ' .. float_param)
    djui_chat_message_create('    double_param: ' .. double_param)
end

---------------------------------------------------------------------------------------------------

function send_example_2(long_param, string_param)

    local bytestring = ''
        -------------- PACKET ID --------------
        .. string.pack("<B", PACKET_EXAMPLE_2)
        ---------------------------------------
        .. string.pack("<l",  long_param)
        .. string.pack("<s2", string_param)
        ---------------------------------------

    network_send_bytestring(true, bytestring)

    djui_chat_message_create('Sent bytestring packet example 2:')
    djui_chat_message_create('    byte_param:   ' .. long_param)
    djui_chat_message_create('    string_param: ' .. string_param)
end

function on_packet_bytestring_receive_example_2(bytestring)
    local offset = 1

    local function unpack(fmt)
        local value
        value, offset = string.unpack(fmt, bytestring, offset)
        return value
    end

    -------------- PACKET ID --------------
    local packet_id    = unpack("<B")
    ---------------------------------------
    local long_param   = unpack("<l")
    local string_param = unpack("<s2")
    ---------------------------------------

    djui_chat_message_create('Received bytestring packet example 2:')
    djui_chat_message_create('    long_param:   ' .. long_param)
    djui_chat_message_create('    string_param: ' .. string_param)
end

---------------------------------------------------------------------------------------------------

local sPacketTable = {
    [PACKET_EXAMPLE_1] = on_packet_bytestring_receive_example_1,
    [PACKET_EXAMPLE_2] = on_packet_bytestring_receive_example_2,
}

local function on_packet_bytestring_receive(bytestring)
    local packet_id = string.unpack("<B", bytestring, 1)
    if sPacketTable[packet_id] ~= nil then
        sPacketTable[packet_id](bytestring)
    end
end

hook_event(HOOK_ON_PACKET_BYTESTRING_RECEIVE, on_packet_bytestring_receive)

---------------------------------------------------------------------------------------------------

hook_chat_command("example", "[1|2]", function(msg)
    if msg == '1' then
        send_example_1(math.random(-127, 127), math.random(-32767, 32767), math.random(-2147483647, 2147483647), math.random(), math.random())
        return true
    elseif string.sub(msg, 1, 1) == "2" then
        send_example_2(math.random(-2147483647, 2147483647), msg)
        return true
    end
    return false
end)