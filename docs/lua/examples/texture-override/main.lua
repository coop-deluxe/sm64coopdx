-- name: Matrix Code
-- description: Run /matrix and a builtin texture name to replace with the digital rain
-- deluxe: true

if SM64COOPDX_VERSION == nil then
    local first = false
    hook_event(HOOK_ON_LEVEL_INIT, function()
        if not first then
            first = true
            play_sound(SOUND_MENU_CAMERA_BUZZ, gMarioStates[0].marioObj.header.gfx.cameraToObject)
            djui_chat_message_create("\\#ff7f7f\\Matrix Code is not supported with sm64ex-coop\nas it uses sm64coopdx exclusive Lua functionality.\n\\#dcdcdc\\To use this mod, try out sm64coopdx at\n\\#7f7fff\\https://sm64coopdx.com")
        end
    end)
    return
end

local sMatrixFrames = {}
for i = 0, 10 do
    sMatrixFrames[i] = get_texture_info("matrix_" .. i)
end
local matrixFrame = 0

local sOverrideTextures = {}

local globalTimer = 0

local function split(s)
    local result = {}
    for match in (s):gmatch(string.format("[^%s]+", " ")) do
        table.insert(result, match)
    end
    return result
end

local function update()
    globalTimer = globalTimer + 1
    if globalTimer % 2 ~= 1 then return end

    for _, texture in pairs(sOverrideTextures) do
        texture_override_set(texture, sMatrixFrames[matrixFrame])
        matrixFrame = (matrixFrame + 1) % 10
    end
end

local function on_matrix_command(msg)
    local textures = split(msg)
    for _, texture in pairs(textures) do
        table.insert(sOverrideTextures, texture)
    end
    return true
end

hook_event(HOOK_UPDATE, update)

hook_chat_command("matrix", "[TEXTURE]", on_matrix_command)