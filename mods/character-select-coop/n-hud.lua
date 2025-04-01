------------------------------------------------------
-- Custom HUD Rendering by Agent X and xLuigiGamerx --
------------------------------------------------------

if incompatibleClient then return 0 end

-- localize functions to improve performance - n-hud.lua
local hud_get_value,hud_set_value,djui_hud_print_text,tostring,hud_set_flash,get_global_timer,hud_get_flash,djui_hud_get_screen_width,math_ceil,obj_get_first_with_behavior_id,get_behavior_from_id,count_objects_with_behavior,djui_hud_render_rect,djui_hud_set_resolution,djui_hud_get_screen_height,djui_hud_set_color,djui_hud_set_font,djui_hud_measure_text,djui_chat_message_create,hud_is_hidden,djui_is_playerlist_open = hud_get_value,hud_set_value,djui_hud_print_text,tostring,hud_set_flash,get_global_timer,hud_get_flash,djui_hud_get_screen_width,math.ceil,obj_get_first_with_behavior_id,get_behavior_from_id,count_objects_with_behavior,djui_hud_render_rect,djui_hud_set_resolution,djui_hud_get_screen_height,djui_hud_set_color,djui_hud_set_font,djui_hud_measure_text,djui_chat_message_create,hud_is_hidden,djui_is_playerlist_open

--[[
    Some functions we need for the hud
    Color hud code written by EmilyEmmi
    Djui box code written by xLuigiGamerx (Use outside of character select is forbidden as these functions were made for another mod I'm planning to release)
]]

---@param text string
---@return nil, number, number, number, number
local function convert_color(text)
    if text:sub(2, 2) ~= "#" then
        return nil
    end
    text = text:sub(3, -2)
    local rstring = text:sub(1, 2) or "ff"
    local gstring = text:sub(3, 4) or "ff"
    local bstring = text:sub(5, 6) or "ff"
    local astring = text:sub(7, 8) or "ff"
    local r = tonumber("0x" .. rstring) or 255
    local g = tonumber("0x" .. gstring) or 255
    local b = tonumber("0x" .. bstring) or 255
    local a = tonumber("0x" .. astring) or 255
    return r, g, b, a
end

---@param text string
---@param get_color boolean|nil
---@return string, string, string, boolean
local function remove_color(text, get_color)
    local start = text:find("\\")
    local next = 1
    while (next ~= nil) and (start ~= nil) do
        start = text:find("\\")
        if start ~= nil then
            next = text:find("\\", start + 1)
            if next == nil then
                next = text:len() + 1
            end

            if get_color then
                local color = text:sub(start, next)
                local render = text:sub(1, start - 1)
                text = text:sub(next + 1)
                return text, color, render
            else
                text = text:sub(1, start - 1) .. text:sub(next + 1)
            end
        end
    end
    return text
end

---@param text string
---@return string
local function generate_rainbow_text(text)
    local preResult = {}
    local postResult = {}
    for match in text:gmatch(string.format(".", "(.)")) do
        table.insert(preResult, match)
    end

    RED = djui_menu_get_rainbow_string_color(0)
    GREEN = djui_menu_get_rainbow_string_color(1)
    BLUE = djui_menu_get_rainbow_string_color(2)
    YELLOW = djui_menu_get_rainbow_string_color(3)

    local sRainbowColors = {
        [0] = YELLOW,
        [1] = RED,
        [2] = GREEN,
        [3] = BLUE,
    }

    for i = 1, #preResult do
        rainbow = sRainbowColors[i % 4]
        table.insert(postResult, rainbow .. preResult[i])
    end

    local result = table.concat(postResult, "")
    return result
end

---@param x integer X Offset
---@param y integer Y Offset
---@param width integer Width
---@param height integer Height
---@param rectColor DjuiColor Rect Color
---@param borderColor DjuiColor Border Color
local function djui_hud_render_djui(x, y, width, height, rectColor, borderColor)

    djui_hud_set_color(borderColor.r, borderColor.g, borderColor.b, borderColor.a)

    -- Left
    djui_hud_render_rect(x, y, 8, height)
    -- Right
    djui_hud_render_rect(x + width - 8, y, 8, height)
    -- Up
    djui_hud_render_rect(x + 8, y, width - 16, 8)
    -- Down
    djui_hud_render_rect(x + 8, y + height - 8, width - 16, 8)


    -- Inner Rect

    djui_hud_set_color(rectColor.r, rectColor.g, rectColor.b, rectColor.a)
    djui_hud_render_rect(x + 8, y + 8, width - 16, height - 16)

end

---@param text string Text
---@param x integer X Offset
---@param y integer Y Offset
---@param scale integer Scale
---@param red integer Default text red value
---@param green integer Default text green value
---@param blue integer Default text blue value
---@param alpha integer Default text alpha value
local function djui_hud_print_text_with_color(text, x, y, scale, red, green, blue, alpha)
    djui_hud_set_color(red or 255, green or 255, blue or 255, alpha or 255)
    local space = 0
    local color = ""
    text, color, render = remove_color(text, true)
    while render ~= nil do
        local r, g, b, a = convert_color(color)
        if alpha then a = alpha end
        djui_hud_print_text(render, x + space, y, scale);
        if r then djui_hud_set_color(r, g, b, a) end
        space = space + djui_hud_measure_text(render) * scale
        text, color, render = remove_color(text, true)
    end
    djui_hud_print_text(text, x + space, y, scale);
end

---@param text string Message
---@param headerYOffset integer A y offset for the header
---@param tr integer Text Red
---@param tg integer Text Green
---@param tb integer Text Blue
---@param a integer Text Alpha Value
---@param scale integer Scale
---@param x integer X Offset
---@param y integer Y Offset
---@param width integer Width
---@param height integer Height
---@param rectColor DjuiColor Rect Color
---@param borderColor DjuiColor Border Color
local function djui_hud_render_header_box(text, headerYOffset, tr, tg, tb, a, scale, x, y, width, height, rectColor, borderColor)
    local headerFont = djui_menu_get_theme().panels.hudFontHeader and FONT_HUD or FONT_MENU
    djui_hud_set_font(headerFont)

    local hudFont = headerFont == FONT_HUD
    local scaleMultiplier = hudFont and 4 * 0.7 or 1
    local headerFontOffset = hudFont and 31.65 or 14.5
    local defaultHeaderOffset = y + headerFontOffset + headerYOffset

    djui_hud_render_djui(x, y, width, height, rectColor, borderColor)
    djui_hud_print_text_with_color(text, x + width / 2 - (djui_hud_measure_text(remove_color(text, false)) * scale * scaleMultiplier) / 2, defaultHeaderOffset, scaleMultiplier, tr, tg, tb, a)
end

---------------------
-- Real HUD Stuffs --
---------------------

local sHudElements = {
    [HUD_DISPLAY_FLAG_LIVES] = true,
    [HUD_DISPLAY_FLAG_STAR_COUNT] = true,
    [HUD_DISPLAY_FLAG_CAMERA] = true
}

---Hides the specified custom hud element
---@param hudElement HUDDisplayFlag
function hud_hide_element(hudElement)
    if sHudElements[hudElement] == nil then return false end
    sHudElements[hudElement] = false
    return true
end

---Shows the specified custom hud element
---@param hudElement HUDDisplayFlag
function hud_show_element(hudElement)
    if sHudElements[hudElement] == nil then return false end
    sHudElements[hudElement] = true
    return true
end

---Gets the specified custom hud element's state
---@param hudElement HUDDisplayFlag
function hud_get_element(hudElement)
    if sHudElements[hudElement] == nil then return false end
    return sHudElements[hudElement]
end

local MATH_DIVIDE_16 = 1/16
local MATH_DIVIDE_32 = 1/32
local MATH_DIVIDE_64 = 1/64
local MATH_DIVIDE_HEALTH = 1/0x100

local FONT_USER = FONT_NORMAL

--- @param localIndex integer
--- @return string
--- This assumes multiple characters will not have the same model,
--- Icons can only be seen by users who have the character avalible to them
function name_from_local_index(localIndex)
    if localIndex == nil then localIndex = 0 end
    local p = gCSPlayers[localIndex]
    for i = 1, #characterTable do
        if characterTable[i].saveName == p.saveName then
            return characterTable[i][(p.currAlt and p.currAlt or 1)].name
        end
    end
    return "???"
end

--- @param localIndex integer
--- @return table
--- This assumes multiple characters will not have the same model,
--- Icons can only be seen by users who have the character avalible to them
function color_from_local_index(localIndex)
    if localIndex == nil then localIndex = 0 end
    local p = gCSPlayers[localIndex]
    for i = 1, #characterTable do
        if characterTable[i].saveName == p.saveName then
            return characterTable[i][(p.currAlt and p.currAlt or 1)].color
        end
    end
    return {r = 255, g = 255, b = 255}
end

--- @param localIndex integer
--- @return TextureInfo|string
--- This assumes multiple characters will not have the same model,
--- Icons can only be seen by users who have the character avalible to them.
--- This function can return nil. if this is the case, render `djui_hud_print_text("?", x, y, 1)`
function life_icon_from_local_index(localIndex)
    if localIndex == nil then localIndex = 0 end
    local p = gCSPlayers[localIndex]
    for i = 1, #characterTable do
        local char = characterTable[i]
        if char.saveName == p.saveName then
            return char[(p.currAlt and p.currAlt or 1)].lifeIcon
        end
    end
    return "?"
end

--- @param localIndex integer
--- @return TextureInfo
--- This assumes multiple characters will not have the same model,
--- Icons can only be seen by users who have the character avalible to them
function star_icon_from_local_index(localIndex)
    if localIndex == nil then localIndex = 0 end
    local p = gCSPlayers[localIndex]
    for i = 1, #characterTable do
        local char = characterTable[i]
        if char.saveName == p.saveName then
            return char[(p.currAlt and p.currAlt or 1)].starIcon
        end
    end
    return gTextures.star
end

local TYPE_STRING = "string"
--- @param localIndex integer
--- @param x integer
--- @param y integer
--- @param scale integer
function render_life_icon_from_local_index(localIndex, x, y, scale)
    if localIndex == nil then localIndex = 0 end
    local lifeIcon = life_icon_from_local_index(localIndex)
    local startFont = djui_hud_get_font()
    local startColor = djui_hud_get_color()

    if type(lifeIcon) == TYPE_STRING then
        local color = color_from_local_index(localIndex)
        djui_hud_set_font(FONT_RECOLOR_HUD)
        djui_hud_set_color(color.r/startColor.r*255, color.g/startColor.g*255, color.b/startColor.b*255, startColor.a)
        djui_hud_print_text(lifeIcon, x - scale/4, y - 10*scale - scale/4, scale)
        -- Reset HUD Modifications
        djui_hud_set_font(startFont)
        djui_hud_set_color(startColor.r, startColor.g, startColor.b, startColor.a)
    else
        djui_hud_render_texture(lifeIcon, x, y, scale / (lifeIcon.width * MATH_DIVIDE_16), scale / (lifeIcon.height * MATH_DIVIDE_16))
    end
end

--- @param localIndex integer
--- @param x integer
--- @param y integer
--- @param scale integer
function render_life_icon_from_local_index_interpolated(localIndex, prevX, prevY, prevScale, x, y, scale)
    if localIndex == nil then localIndex = 0 end
    local lifeIcon = life_icon_from_local_index(localIndex)
    local startFont = djui_hud_get_font()
    local startColor = djui_hud_get_color()

    if type(lifeIcon) == TYPE_STRING then
        local color = color_from_local_index(localIndex)
        djui_hud_set_font(FONT_RECOLOR_HUD)
        djui_hud_set_color(color.r/startColor.r*255, color.g/startColor.g*255, color.b/startColor.b*255, startColor.a)
        djui_hud_print_text_interpolated(lifeIcon, prevX - prevScale/4, prevY - 10*prevScale - prevScale/4, prevScale, x - scale/4, y - 10*scale - scale/4, scale)
        -- Reset HUD Modifications
        djui_hud_set_font(startFont)
        djui_hud_set_color(startColor.r, startColor.g, startColor.b, startColor.a)
    else
        djui_hud_render_texture_interpolated(lifeIcon, prevX, prevY, prevScale / (lifeIcon.width * MATH_DIVIDE_16), prevScale / (lifeIcon.height * MATH_DIVIDE_16), x, y, scale / (lifeIcon.width * MATH_DIVIDE_16), scale / (lifeIcon.height * MATH_DIVIDE_16))
    end
end

--- @param localIndex integer
--- @param x integer
--- @param y integer
--- @param scale integer
function render_star_icon_from_local_index(localIndex, x, y, scale)
    if localIndex == nil then localIndex = 0 end
    local starIcon = star_icon_from_local_index(localIndex)
    djui_hud_render_texture(starIcon, x, y, scale / (starIcon.width * MATH_DIVIDE_16), scale / (starIcon.height * MATH_DIVIDE_16))
end

--- @param localIndex integer
--- @param x integer
--- @param y integer
--- @param scale integer
function render_star_icon_from_local_index_interpolated(localIndex, prevX, prevY, prevScale, x, y, scale)
    if localIndex == nil then localIndex = 0 end
    local starIcon = star_icon_from_local_index(localIndex)
    djui_hud_render_texture_interpolated(starIcon, prevX, prevY, prevScale / (starIcon.width * MATH_DIVIDE_16), prevScale / (starIcon.height * MATH_DIVIDE_16), x, y, scale / (starIcon.width * MATH_DIVIDE_16), scale / (starIcon.height * MATH_DIVIDE_16))
end

local TEXT_DEFAULT_METER_PREFIX = "char-select-custom-meter-"
local TEX_DEFAULT_METER_LEFT = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."left")
local TEX_DEFAULT_METER_RIGHT = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."right")
local TEX_DEFAULT_METER_PIE1 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie1")
local TEX_DEFAULT_METER_PIE2 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie2")
local TEX_DEFAULT_METER_PIE3 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie3")
local TEX_DEFAULT_METER_PIE4 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie4")
local TEX_DEFAULT_METER_PIE5 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie5")
local TEX_DEFAULT_METER_PIE6 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie6")
local TEX_DEFAULT_METER_PIE7 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie7")
local TEX_DEFAULT_METER_PIE8 = get_texture_info(TEXT_DEFAULT_METER_PREFIX.."pie8")
local defaultMeterInfo = {
    label = {
        left = TEX_DEFAULT_METER_LEFT,
        right = TEX_DEFAULT_METER_RIGHT,
    },
    pie = {
        TEX_DEFAULT_METER_PIE1,
        TEX_DEFAULT_METER_PIE2,
        TEX_DEFAULT_METER_PIE3,
        TEX_DEFAULT_METER_PIE4,
        TEX_DEFAULT_METER_PIE5,
        TEX_DEFAULT_METER_PIE6,
        TEX_DEFAULT_METER_PIE7,
        TEX_DEFAULT_METER_PIE8,
    }
}

local TEXT_DEFAULT_COURSE_PREFIX = "char-select-custom-course-"
local TEX_DEFAULT_METER_LEFT = get_texture_info(TEXT_DEFAULT_COURSE_PREFIX.."top")
local TEX_DEFAULT_METER_RIGHT = get_texture_info(TEXT_DEFAULT_COURSE_PREFIX.."bottom")
local defaultCourseInfo = {
    top = TEX_DEFAULT_METER_LEFT,
    bottom = TEX_DEFAULT_METER_RIGHT,
}

--- @param localIndex integer
--- @return table
--- This assumes multiple characters will not have the same model,
--- Icons can only be seen by users who have the character avalible to them
function health_meter_from_local_index(localIndex)
    if localIndex == nil then localIndex = 0 end
    local p = gCSPlayers[localIndex]
    for i = 1, #characterTable do
        local char = characterTable[i]
        if char.saveName == p.saveName and char[(p.currAlt and p.currAlt or 1)].healthTexture ~= nil then
            return char[(p.currAlt and p.currAlt or 1)].healthTexture
        end
    end
    return defaultMeterInfo
end

--- @param localIndex integer
--- @param x integer
--- @param y integer
--- @param scaleX integer
--- @param scaleY integer
function render_health_meter_from_local_index(localIndex, health, x, y, scaleX, scaleY)
    if localIndex == nil then localIndex = 0 end
    local health = math.floor(health*MATH_DIVIDE_HEALTH)
    local textureTable = health_meter_from_local_index(localIndex)
    local tex = textureTable.label.left
    djui_hud_render_texture(tex, x, y, scaleX / (tex.width * MATH_DIVIDE_32) * MATH_DIVIDE_64, scaleY / (tex.height * MATH_DIVIDE_64) * MATH_DIVIDE_64)
    local tex = textureTable.label.right
    djui_hud_render_texture(tex, x + 31*scaleX*MATH_DIVIDE_64, y, scaleX / (tex.width * MATH_DIVIDE_32) * MATH_DIVIDE_64, scaleY / (tex.height * MATH_DIVIDE_64) * MATH_DIVIDE_64)
    if health > 0 then
        local tex = textureTable.pie[health]
        djui_hud_render_texture(tex, x + 15*scaleX*MATH_DIVIDE_64, y + 16*scaleY*MATH_DIVIDE_64, scaleX / (tex.width * MATH_DIVIDE_32) * MATH_DIVIDE_64, scaleY / (tex.height * MATH_DIVIDE_32) * MATH_DIVIDE_64)
    end
end

local pieTextureNames = {
    "one_segments",
    "two_segments",
    "three_segments",
    "four_segments",
    "five_segments",
    "six_segments",
    "seven_segments",
    "full",
}

local function render_hud_health()
    if currChar == 1 then
        texture_override_reset("texture_power_meter_left_side")
        texture_override_reset("texture_power_meter_right_side")
		for i = 1, 8 do
			texture_override_reset("texture_power_meter_" .. pieTextureNames[i])
		end
        return
    end
	local textureTable = characterTable[currChar][characterTable[currChar].currAlt].healthTexture
	if textureTable then -- sets health HUD to custom textures
		if textureTable.label.left and textureTable.label.right then -- if left and right label textures exist. BOTH have to exist to be set!
			texture_override_set("texture_power_meter_left_side", textureTable.label.left)
			texture_override_set("texture_power_meter_right_side", textureTable.label.right)
		end
		for i = 1, 8 do
			texture_override_set("texture_power_meter_" .. pieTextureNames[i], textureTable.pie[i])
		end
	else -- resets the health HUD
        texture_override_set("texture_power_meter_left_side", defaultMeterInfo.label.left)
        texture_override_set("texture_power_meter_right_side", defaultMeterInfo.label.right)
		for i = 1, 8 do
			texture_override_set("texture_power_meter_" .. pieTextureNames[i], defaultMeterInfo.pie[i])
		end
	end
end

local function render_hud_act_select_course()
    if currChar == 1 then
        texture_override_reset("texture_menu_course_upper")
        texture_override_reset("texture_menu_course_lower")
        return
    end
	local textureTable = characterTable[currChar][characterTable[currChar].currAlt].courseTexture
	if textureTable then -- sets health HUD to custom textures
		if textureTable.top and textureTable.bottom then -- if left and right label textures exist. BOTH have to exist to be set!
			texture_override_set("texture_menu_course_upper", textureTable.top)
			texture_override_set("texture_menu_course_lower", textureTable.bottom)
		end
	else -- resets the course HUD
        texture_override_set("texture_menu_course_upper", defaultCourseInfo.top)
        texture_override_set("texture_menu_course_lower", defaultCourseInfo.bottom)
	end
end

local function render_hud_mario_lives()
    hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_LIVES)

    if not hud_get_element(HUD_DISPLAY_FLAG_LIVES) then return end

    local x = 22
    local y = 15 -- SCREEN_HEIGHT - 209 - 16
    render_life_icon_from_local_index(0, x, y, 1)
    djui_hud_print_text("@", x + 16, y, 1)
    djui_hud_print_text(tostring(hud_get_value(HUD_DISPLAY_LIVES)):gsub("-", "M"), x + 32, y, 1)
end

local function render_hud_stars()
    hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_STAR_COUNT)

    if not hud_get_element(HUD_DISPLAY_FLAG_STAR_COUNT) then return end
    if hud_get_flash ~= nil then
        -- prevent star count from flashing outside of castle
        if gNetworkPlayers[0].currCourseNum ~= COURSE_NONE then hud_set_flash(0) end

        if hud_get_flash() == 1 and (get_global_timer() & 0x08) == 0 then
            return
        end
    end

    local x = math_ceil(djui_hud_get_screen_width() - 76)
    if x % 2 ~= 0 then
        x = x - 1
    end
    local y = math_ceil(240 - 209 - 16)

    local showX = 0
    local hudDisplayStars = hud_get_value(HUD_DISPLAY_STARS)
    if hudDisplayStars < 100 then showX = 1 end

    render_star_icon_from_local_index(0, x, y, 1)
    if showX == 1 then
        djui_hud_print_text("@", x + 16, y, 1)
    end
    djui_hud_print_text(tostring(hudDisplayStars):gsub("-", "M"), (showX * 14) + x + 16, y, 1)
end

local function render_hud_camera_status()
    if not HUD_DISPLAY_CAMERA_STATUS then return end

    hud_set_value(HUD_DISPLAY_FLAGS, hud_get_value(HUD_DISPLAY_FLAGS) & ~HUD_DISPLAY_FLAG_CAMERA)

    if not hud_get_element(HUD_DISPLAY_FLAG_CAMERA) then return end

    local x = djui_hud_get_screen_width() - 54
    local y = 205
    local cameraHudStatus = hud_get_value(HUD_DISPLAY_CAMERA_STATUS)

    if cameraHudStatus == CAM_STATUS_NONE then return end

    djui_hud_render_texture(gTextures.camera, x, y, 1, 1)

    switch(cameraHudStatus & CAM_STATUS_MODE_GROUP, {
        [CAM_STATUS_MARIO] = function()
            render_life_icon_from_local_index(0, x + 16, y, 1)
        end,
        [CAM_STATUS_LAKITU] = function()
            djui_hud_render_texture(gTextures.lakitu, x + 16, y, 1, 1)
        end,
        [CAM_STATUS_FIXED] = function()
            djui_hud_render_texture(gTextures.no_camera, x + 16, y, 1, 1)
        end
    })

    switch(cameraHudStatus & CAM_STATUS_C_MODE_GROUP, {
        [CAM_STATUS_C_DOWN] = function()
            djui_hud_render_texture(gTextures.arrow_down, x + 4, y + 16, 1, 1)
        end,
        [CAM_STATUS_C_UP] = function()
            djui_hud_render_texture(gTextures.arrow_up, x + 4, y - 8, 1, 1)
        end
    })
end

-- Act Select Hud --
local function render_act_select_hud()
    local course = gNetworkPlayers[0].currCourseNum
    if gServerSettings.enablePlayersInLevelDisplay == 0 or course == 0 or obj_get_first_with_behavior_id(id_bhvActSelector) == nil then return end

    local starBhvCount = count_objects_with_behavior(get_behavior_from_id(id_bhvActSelectorStarType))
    local sVisibleStars = starBhvCount < 6 and starBhvCount or 6

    for a = 1, sVisibleStars do
        local x = (139 - sVisibleStars * 17 + a * 34) + (djui_hud_get_screen_width() / 2) - 160 + 0.5
        for j = 1, MAX_PLAYERS - 1 do -- 0 is not needed due to the due to the fact that you are never supposed to see yourself in the act
            local np = gNetworkPlayers[j]
            if np and np.connected and np.currCourseNum == course and np.currActNum == a then
                djui_hud_render_rect(x - 4, 17, 16, 16)
                render_life_icon_from_local_index(j, x - 4, 17, 1)
                break
            end
        end
    end
end

---@param table table
---@return table
function zero_index_to_one_index(table)
    local tableOne = {}
    for i = 0, #table do
        tableOne[i+1] = table[i]
    end
    return tableOne
end

local activeNonCSMods = {}
local nonCSModPosition = 0
local CSPacks = 0
for i = 0, #gActiveMods do
    if gActiveMods[i].name == "Character Select" then
        table.insert(activeNonCSMods, tostring(gActiveMods[i].name))
        nonCSModPosition = #activeNonCSMods
    elseif (remove_color(gActiveMods[i].name):sub(1, 4) ~= "[CS]" and gActiveMods[i].category ~= "cs") then
        table.insert(activeNonCSMods, tostring(gActiveMods[i].name))
    else
        CSPacks = CSPacks + 1
    end
end

activeNonCSMods[nonCSModPosition] = "Character Select (+"..CSPacks..")"

function render_playerlist_and_modlist()

    -- DjuiTheme Data
    local sDjuiTheme = djui_menu_get_theme()
    local hudFont = sDjuiTheme.panels.hudFontHeader
    local rectColor = sDjuiTheme.threePanels.rectColor
    local borderColor = sDjuiTheme.threePanels.borderColor

    -- PlayerList
    playerListWidth = 710
    playerListHeight = (16 * 32) + (16 - 1) * 4 + (32 + 16) + 32 + 32
    local x = djui_hud_get_screen_width()/2 - playerListWidth/2
    local y = djui_hud_get_screen_height()/2 - playerListHeight/2

    listMargins = 16
    local playerList = {}

    gNetworkPlayersOne = zero_index_to_one_index(gNetworkPlayers)
    for index, player in pairs(gNetworkPlayersOne) do
        if player.connected then
            playerList[#playerList + 1] = player
        end
    end 

    local playersString = hudFont and djui_language_get("PLAYER_LIST", "PLAYERS") or generate_rainbow_text(djui_language_get("PLAYER_LIST", "PLAYERS"))

    djui_hud_render_header_box(playersString, 0, 0xff, 0xff, 0xff, 0xff, 1, x, y, playerListWidth, playerListHeight, rectColor, borderColor)
    djui_hud_set_font(FONT_USER)
    for i = 1, #playerList do
        np = playerList[i]

        local v = (i % 2) == 0 and 16 or 32
        djui_hud_set_color(v, v, v, 128)
        local entryWidth = playerListWidth - ((8 + listMargins) * 2)
        local entryHeight = 32
        local entryX = x + 8 + listMargins
        local entryY = y + 88 + ((entryHeight + 4) * (i-1))
        djui_hud_render_rect(entryX, entryY, entryWidth, entryHeight)

        playerNameColor = {
            r = 127 + network_player_get_override_palette_color_channel(np, CAP, 0) / 2,
            g = 127 + network_player_get_override_palette_color_channel(np, CAP, 1) / 2,
            b = 127 + network_player_get_override_palette_color_channel(np, CAP, 2) / 2
        }

        djui_hud_set_color(255, 255, 255, 255)
        render_life_icon_from_local_index(np.localIndex, entryX, entryY, 2)
        djui_hud_print_text_with_color(np.name, entryX + 40, entryY, 1, playerNameColor.r, playerNameColor.g, playerNameColor.b, 255)

        local levelName = np.overrideLocation ~= "" and np.overrideLocation or get_level_name(np.currCourseNum, np.currLevelNum, np.currAreaIndex)
        if levelName then
            djui_hud_print_text_with_color(levelName, ((entryX + entryWidth) - djui_hud_measure_text((string.gsub(levelName, "\\(.-)\\", "")))) - 126, entryY, 1, 0xdc, 0xdc, 0xdc, 255)
        end

        if np.currActNum then
            currActNum = np.currActNum == 99 and "Done" or np.currActNum ~= 0 and "# "..tostring(np.currActNum) or ""
            printedcurrActNum = currActNum
            djui_hud_print_text_with_color(printedcurrActNum, entryX + entryWidth - djui_hud_measure_text(printedcurrActNum) - 18, entryY, 1, 0xdc, 0xdc, 0xdc, 255)
        end

        if np.description then
            djui_hud_print_text_with_color(np.description, (entryX + 278) - (djui_hud_measure_text((string.gsub(np.description, "\\(.-)\\", "")))/2), entryY, 1, np.descriptionR, np.descriptionG, np.descriptionB, np.descriptionA)
        end
    end

    -- ModList

    local modListWidth = 280
    local modListHeight = (#activeNonCSMods * 32) + (#activeNonCSMods - 1) * 4 + (32 + 16) + 32 + 32
    local mX = djui_hud_get_screen_width()/2 + 363
    local mY = djui_hud_get_screen_height()/2 - modListHeight/2

    local modsString = hudFont and djui_language_get("MODLIST", "MODS") or generate_rainbow_text(djui_language_get("MODLIST", "MODS"))

    djui_hud_render_header_box(modsString, 0, 0xff, 0xff, 0xff, 0xff, 1, mX, mY, modListWidth, modListHeight, rectColor, borderColor)
    djui_hud_set_font(FONT_USER)

    for i = 0, #activeNonCSMods - 1 do
        --local i = i - packFilter
        v = (i % 2) ~= 0 and 16 or 32
        djui_hud_set_color(v, v, v, 128)
        local entryWidth = modListWidth - ((8 + listMargins) * 2)
        local entryHeight = 32
        local entryX = mX + 8 + listMargins
        local entryY = mY + 124 + 0 + ((entryHeight + 4) * (i - 1))
        djui_hud_render_rect(entryX, entryY, entryWidth, entryHeight)
        local modName = activeNonCSMods[i + 1]
        local stringSubCount = 23
        local inColor = false
        for i = 1, #modName do
            if modName:sub(i, i) == "\\" then
                inColor = not inColor
            end
            if inColor then
                stringSubCount = stringSubCount + 1
            end
        end
        djui_hud_print_text_with_color(modName:sub(1, stringSubCount), entryX, entryY, 1, 0xdc, 0xdc, 0xdc, 255)
    end
end

-- Yes the ending stuffs is hardcoded, no there's not much of a better way to do it

local DIALOG_ENDING_REPLACE_1 = "$CHARNAME!"
local DIALOG_ENDING_REPLACE_2 = "Thank you $CHARNAME!"
local DIALOG_ENDING_REPLACE_3 = "...for $CHARNAME..."

local END_PEACH_CUTSCENE_DIALOG_1 = 6
local END_PEACH_CUTSCENE_DIALOG_2 = 7
local END_PEACH_CUTSCENE_DIALOG_3 = 10
local END_PEACH_CUTSCENE_RUN_TO_CASTLE = 11

local fadeLength = 5
local function render_hud_ending_dialog()
    djui_hud_set_font(FONT_TINY)
    local m = gMarioStates[0]
    if m.action ~= ACT_END_PEACH_CUTSCENE then return end

    local width = djui_hud_get_screen_width()

    local charName = characterTable[currChar][characterTable[currChar].currAlt].name
    local string = ""
    local startTime = 0
    local endTime = 0
    if m.actionArg == END_PEACH_CUTSCENE_DIALOG_1 and m.actionTimer >= 230 and m.actionTimer <= 275 then
        string = DIALOG_ENDING_REPLACE_1
        startTime = 230
        endTime = 275
    elseif m.actionArg == END_PEACH_CUTSCENE_DIALOG_2 and m.actionTimer >= 75 and m.actionTimer <= 130 then
        string = DIALOG_ENDING_REPLACE_2
        startTime = 75
        endTime = 130
    elseif m.actionArg == END_PEACH_CUTSCENE_DIALOG_3 and m.actionTimer >= 130 and m.actionTimer <= 195 then
        string = DIALOG_ENDING_REPLACE_3
        startTime = 130
        endTime = 195
    elseif m.actionArg == END_PEACH_CUTSCENE_RUN_TO_CASTLE and m.actionTimer >= 95 and m.actionTimer <= 150 then
        string = DIALOG_ENDING_REPLACE_1
        startTime = 95
        endTime = 150
    end

    if string ~= "" then
        djui_hud_set_color(0, 0, 0, 255)
        djui_hud_render_rect(0, 210, width, 30)
        string = string:gsub("$CHARNAME", charName)
        local opacity = 255
        local startToTimer = m.actionTimer - startTime
        local endToTimer = endTime - m.actionTimer
        if startToTimer >= 0 then
            opacity = math.min(startToTimer, fadeLength)/fadeLength * 255
        end
        if endToTimer >= 0 and startToTimer >= fadeLength then
            opacity = math.min(endToTimer, fadeLength)/fadeLength * 255
        end
        djui_hud_set_color(255, 255, 255, opacity)
        local x = width*0.5 - djui_hud_measure_text(string)*0.5
        djui_hud_print_text(string, x, 210, 1)
    end
end

local function on_hud_render_behind()
    FONT_USER = djui_menu_get_font()
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_HUD)
    djui_hud_set_color(255, 255, 255, 255)

    if gNetworkPlayers[0].currActNum == 99 or gMarioStates[0].action == ACT_INTRO_CUTSCENE or hud_is_hidden() then
        return
    end

    if obj_get_first_with_behavior_id(id_bhvActSelector) == nil then
        render_hud_mario_lives()
        render_hud_stars()
        render_hud_camera_status()
        render_hud_health()
    else
        render_hud_act_select_course()
    end
end

-- Can't name this charSelect due to o-api.lua overriding it, if I did so, using character select with no packs would make it nil
_G.gServerSettingsCS = {
    enablePlayerList = true -- Set to false to disable the playerlist
}

local function on_hud_render()
    djui_hud_set_resolution(RESOLUTION_N64)
    djui_hud_set_font(FONT_HUD)
    djui_hud_set_color(255, 255, 255, 255)

    if obj_get_first_with_behavior_id(id_bhvActSelector) ~= nil then
        render_act_select_hud()
    end

    if gNetworkPlayers[0].currActNum == 99 then
        render_hud_ending_dialog()
    end

    gServerSettings.enablePlayerList = false -- Disables the original playerlist and modlist

    local enablePlayerList = gServerSettingsCS.enablePlayerList -- gServerSettings.enablePlayerList but for the character select playerlist
    djui_hud_set_resolution(RESOLUTION_DJUI)

    if djui_attempting_to_open_playerlist() and enablePlayerList then
        render_playerlist_and_modlist()
    end
end

hook_event(HOOK_ON_HUD_RENDER_BEHIND, on_hud_render_behind)
hook_event(HOOK_ON_HUD_RENDER, on_hud_render)