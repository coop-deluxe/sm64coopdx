-- name: BungeeCord64
-- description:\#ffff33\--- BungeeCord64 v1.2 ---\n\n\#dcdcdc\Seamless multi-server switching for SM64CoopDX.\nLets you hop between local servers with a smooth transition overlay.\n\n\#ffff33\Commands:\n\#ffffff\/bungeecord64\#aaaaaa\ - Show status\n\#ffffff\/switch <port>\#aaaaaa\ - Switch to server on port\n\#ffffff\/leave\#aaaaaa\ - Return to home server\n\#ffffff\/setfallback <port>\#aaaaaa\ - Set default home server\n\#ffffff\/setserverfallback <port>\#aaaaaa\ - (Server) Set fallback for clients\n\n\#00ff00\This mod must be installed on ALL servers!\n\#ff6666\All servers must be in the same local network (localhost)
-- incompatible: gamemode
-- pausable: false

-- =====================================================
-- BungeeCord64 - Seamless Server Switching System
-- =====================================================
-- Enables seamless switching between multiple SM64CoopDX servers
-- in the local network (localhost). Inspired by Minecraft BungeeCord.
--
-- Features:
-- - /switch <port>    : Smooth switch to another local server
-- - /leave            : Returns to your home server
-- - Auto reconnect    : Server sends fallback port to clients
-- - Overlay display   : "Connecting To Server <PORT>..." while you can still play
-- =====================================================

if incompatibleClient then return end

local MOD_VERSION = "1.2.0"

-- Home server: where /leave goes to.
-- By default this is the first server you connect to as a client,
-- but it can be overridden with /setfallback.
local homePort = 0

-- Optional: configured fallback (if you want a fixed main hub)
-- Default: 7777, unless changed via /setfallback or saved config.
local fallbackPort = 7777

-- Known servers in the network (Port -> Name) for nicer status output
local knownServers = {}

-- Runtime state
local lastWasConnected = false
local lastPort         = 0

-- Note: Switch state is now managed C-side via network_is_bungee_switching()
-- We only track Lua-side state for UI/chat messages
local luaSwitchReason = nil

-- Server-side: fallback port to send to clients
local serverFallbackPort = 0

-- ===================
-- Helper functions
-- ===================

local function chatMsg(msg, color)
    color = color or "\\#ffffff\\"
    djui_chat_message_create(color .. msg)
end

local function popup(msg, lines)
    djui_popup_create(msg, lines or 2)
end

local function isClient()
    return network_is_client()
end

local function isServer()
    return network_is_server()
end

local function getCurrentPort()
    return network_get_current_port() or 0
end

local function getCurrentIp()
    return network_get_current_ip() or ""
end

local function ensureHomePort()
    if homePort ~= 0 then return end
    local port = getCurrentPort()
    if port ~= 0 then
        homePort = port
    end
end

local function getHomePort()
    if homePort ~= 0 then return homePort end
    if fallbackPort ~= 0 then return fallbackPort end
    return 0
end

local function registerServer(port, name)
    if not port or port <= 0 then return end
    knownServers[port] = name or ("Server:" .. port)
    mod_storage_save("server_" .. port, knownServers[port])
end

local function loadSavedConfig()
    -- Load client fallback
    local savedFallback = mod_storage_load("fallback_port")
    if savedFallback and tonumber(savedFallback) then
        fallbackPort = tonumber(savedFallback)
        if homePort == 0 then
            homePort = fallbackPort
        end
    end

    -- Push current fallback down into the C-side global so that even if Lua
    -- dies (e.g. due to a hard disconnect), the client can still auto-reconnect
    -- to the fallback server.
    network_set_bungee_fallback_port(fallbackPort)

    -- Load server fallback (if hosting)
    local savedServerFallback = mod_storage_load("server_fallback_port")
    if savedServerFallback and tonumber(savedServerFallback) then
        serverFallbackPort = tonumber(savedServerFallback)
    end
end

-- Core switching helper. Now uses the C-side seamless BungeeCord switch
-- which shows a big overlay while you can still play, then switches.
local function performSwitch(targetPort, reason)
    if isServer() then
        chatMsg("You cannot use BungeeCord64 while hosting.", "\\#ff6666\\")
        return false
    end

    local currentPort = getCurrentPort()

    if not isClient() and currentPort == 0 then
        chatMsg("You are not connected to any server.", "\\#ff6666\\")
        return false
    end

    if targetPort == nil or targetPort <= 0 then
        chatMsg("Invalid or unknown target port.", "\\#ff6666\\")
        return false
    end

    if currentPort ~= 0 and targetPort == currentPort then
        chatMsg("You are already on port " .. targetPort .. ".", "\\#ffff00\\")
        return false
    end

    -- Check if a switch is already in progress (C-side check)
    if network_is_bungee_switching() then
        chatMsg("A server switch is already in progress.", "\\#ffff00\\")
        return false
    end

    ensureHomePort()

    local reasonText = reason or "switch"
    chatMsg("BungeeCord64: Initiating switch to port " .. targetPort .. "...", "\\#00ff00\\")

    luaSwitchReason = reasonText
    lastWasConnected = false

    -- Use the new C-side seamless switch
    -- This shows the overlay immediately, lets you play for a moment,
    -- then performs the actual switch
    local ok = network_switch_to_server(targetPort)
    if not ok then
        chatMsg("BungeeCord64: failed to initiate switch to port " .. targetPort .. ".", "\\#ff6666\\")
        luaSwitchReason = nil
        return false
    end

    return true
end

-- ===================
-- Chat commands
-- ===================

local function cmdSwitch(msg)
    if msg == "" or msg == nil then
        chatMsg("Usage: /switch <port>", "\\#ffff00\\")
        chatMsg("Example: /switch 7778", "\\#aaaaaa\\")
        return true
    end

    local port = tonumber(msg)
    if not port then
        chatMsg("Invalid port: " .. msg, "\\#ff6666\\")
        return true
    end

    registerServer(port, knownServers[port])
    performSwitch(port, "manual")
    return true
end

local function cmdLeave(msg)
    local target = getHomePort()
    if target == 0 then
        chatMsg("No home server known yet. Join a server first or use /setfallback <port>.", "\\#ff6666\\")
        return true
    end

    performSwitch(target, "leave")
    return true
end

local function cmdSetFallback(msg)
    if msg == "" or msg == nil then
        chatMsg("Usage: /setfallback <port>", "\\#ffff00\\")
        local currentHome = getHomePort()
        if currentHome ~= 0 then
            chatMsg("Current home server: port " .. currentHome, "\\#aaaaaa\\")
        else
            chatMsg("No home server configured.", "\\#aaaaaa\\")
        end
        return true
    end

    local port = tonumber(msg)
    if not port or port <= 0 then
        chatMsg("Invalid port: " .. msg, "\\#ff6666\\")
        return true
    end

    fallbackPort = port
    mod_storage_save("fallback_port", tostring(port))
    if homePort == 0 then
        homePort = port
    end

    -- Update C-side fallback so C can auto-reconnect on hard disconnects.
    network_set_bungee_fallback_port(fallbackPort)

    chatMsg("Fallback (home) server set to port " .. port .. ".", "\\#00ff00\\")
    popup("BungeeCord64\nHome server: port " .. port, 2)
    return true
end

-- Server-only command: set fallback port that gets sent to clients
local function cmdSetServerFallback(msg)
    if not isServer() then
        chatMsg("This command is only for server hosts.", "\\#ff6666\\")
        return true
    end

    if msg == "" or msg == nil then
        chatMsg("Usage: /setserverfallback <port>", "\\#ffff00\\")
        local current = network_get_server_fallback_port()
        if current ~= 0 then
            chatMsg("Current server fallback: port " .. current, "\\#aaaaaa\\")
        else
            chatMsg("No server fallback configured.", "\\#aaaaaa\\")
        end
        return true
    end

    local port = tonumber(msg)
    if not port or port <= 0 then
        chatMsg("Invalid port: " .. msg, "\\#ff6666\\")
        return true
    end

    serverFallbackPort = port
    mod_storage_save("server_fallback_port", tostring(port))
    
    -- Set C-side server fallback
    network_set_server_fallback_port(port)

    chatMsg("Server fallback port set to " .. port .. ".", "\\#00ff00\\")
    chatMsg("Clients will reconnect to this port if this server crashes.", "\\#aaaaaa\\")
    popup("BungeeCord64\nServer fallback: port " .. port, 2)
    return true
end

local function cmdAddServer(msg)
    if msg == "" or msg == nil then
        chatMsg("Usage: /addserver <port> <name>", "\\#ffff00\\")
        chatMsg("Example: /addserver 7779 Minigames", "\\#aaaaaa\\")
        return true
    end

    local parts = {}
    for part in msg:gmatch("%S+") do
        table.insert(parts, part)
    end

    local port = tonumber(parts[1])
    if not port or port <= 0 then
        chatMsg("Invalid port!", "\\#ff6666\\")
        return true
    end

    local name = "Server:" .. port
    if #parts > 1 then
        table.remove(parts, 1)
        name = table.concat(parts, " ")
    end

    registerServer(port, name)
    chatMsg("Registered server: " .. name .. " (port " .. port .. ")", "\\#00ff00\\")
    return true
end

local function cmdStatus(msg)
    local client = isClient()
    local server = isServer()
    local port   = getCurrentPort()
    local ip     = getCurrentIp()

    chatMsg("============================================", "\\#ffff33\\")
    chatMsg("     BungeeCord64 v" .. MOD_VERSION, "\\#ffff33\\")
    chatMsg("============================================", "\\#ffff33\\")

    if server then
        chatMsg(">> You are HOSTING a server on port " .. port, "\\#00ff00\\")
        local srvFallback = network_get_server_fallback_port()
        if srvFallback ~= 0 then
            chatMsg("   Server fallback port: " .. srvFallback, "\\#00ffff\\")
        else
            chatMsg("   Server fallback: (not set)", "\\#aaaaaa\\")
            chatMsg("   Use /setserverfallback <port> to set one.", "\\#aaaaaa\\")
        end
    elseif client and port ~= 0 then
        chatMsg(">> Connected as CLIENT on port " .. port, "\\#00ff00\\")
        if ip ~= "" then
            chatMsg("   Server IP: " .. ip, "\\#aaaaaa\\")
        end
        
        -- Show the fallback port the server sent us
        local receivedFallback = network_get_bungee_fallback_port()
        if receivedFallback ~= 0 then
            chatMsg("   Server's fallback port: " .. receivedFallback, "\\#00ffff\\")
        end
    else
        chatMsg(">> Not connected to any server.", "\\#ff6666\\")
    end

    local home = getHomePort()
    if home ~= 0 then
        chatMsg("Home server (target for /leave): port " .. home, "\\#ffff00\\")
    else
        chatMsg("Home server (target for /leave): (not set)", "\\#aaaaaa\\")
    end

    chatMsg("Client fallback port: " .. tostring(fallbackPort), "\\#00ffff\\")

    chatMsg("", "\\#ffffff\\")
    chatMsg(">> Commands:", "\\#00ffff\\")
    chatMsg("/switch <port>  - Switch to server", "\\#aaaaaa\\")
    chatMsg("/leave          - Return to home server", "\\#aaaaaa\\")
    chatMsg("/setfallback <port> - Set client home", "\\#aaaaaa\\")
    if server then
        chatMsg("/setserverfallback <port> - Set server fallback", "\\#aaaaaa\\")
    end
    chatMsg("/addserver <port> <name> - Register server", "\\#aaaaaa\\")
    chatMsg("============================================", "\\#ffff33\\")

    return true
end

-- ===================
-- Server init: set fallback port on startup
-- ===================

local function onServerInit()
    if not isServer() then return end
    
    -- Load saved server fallback
    local savedFallback = mod_storage_load("server_fallback_port")
    if savedFallback and tonumber(savedFallback) then
        serverFallbackPort = tonumber(savedFallback)
        network_set_server_fallback_port(serverFallbackPort)
        chatMsg("BungeeCord64: Server fallback port loaded: " .. serverFallbackPort, "\\#00ffff\\")
    end
end

-- ===================
-- Update hook (connection tracking)
-- ===================

local function onUpdate()
    local client = isClient()
    local server = isServer()
    local port   = getCurrentPort()
    local switching = network_is_bungee_switching()

    if client and port ~= 0 then
        -- Update home port the first time we see a valid connection
        ensureHomePort()

        -- Check if we just completed a switch
        if luaSwitchReason ~= nil and not switching then
            chatMsg("BungeeCord64: Connected to port " .. port .. "!", "\\#00ff00\\")
            luaSwitchReason = nil
        end

        lastWasConnected = true
        lastPort         = port
        return
    end

    -- If we were connected as client and now we are not, and this wasn't
    -- an intentional switch that is still in progress, the C-side will
    -- handle auto-reconnect to fallback port.
    if lastWasConnected and not switching then
        lastWasConnected = false
    end

    lastWasConnected = client and port ~= 0
end

-- ===================
-- Init & hook registration
-- ===================

local function init()
    loadSavedConfig()
    
    chatMsg("============================================", "\\#ffff33\\")
    chatMsg("BungeeCord64 v" .. MOD_VERSION .. " loaded!", "\\#00ff00\\")
    chatMsg("Use /bungeecord64 for status and help.", "\\#aaaaaa\\")
    chatMsg("============================================", "\\#ffff33\\")
    
    -- If we're a server, set up server fallback
    if isServer() then
        onServerInit()
    end
end

hook_event(HOOK_UPDATE, onUpdate)

hook_chat_command("bungeecord64",      "[BC64] Show status and help", cmdStatus)
hook_chat_command("switch",            "[BC64] /switch <port> - Switch to server", cmdSwitch)
hook_chat_command("leave",             "[BC64] /leave - Return to home server", cmdLeave)
hook_chat_command("setfallback",       "[BC64] /setfallback <port> - Set home server", cmdSetFallback)
hook_chat_command("setserverfallback", "[BC64] /setserverfallback <port> - Set server fallback (host only)", cmdSetServerFallback)
hook_chat_command("addserver",         "[BC64] /addserver <port> <name> - Register server", cmdAddServer)

init()
