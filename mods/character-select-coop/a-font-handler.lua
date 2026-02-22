--[[
    Custom Font Handler v1 - By Squishy6094

    This file adds custom font functionality, and does not need to be edited
    Ensure this file is loaded before anything else (make the file name start with a or !)
    Use djui_hud_add_font() to add fonts as shown in main.lua
]]

FONT_HANDLER_VERSION_MAJOR = 1
FONT_HANDLER_VERSION_MINOR = 0
FONT_HANDLER_VERSION = "v"..FONT_HANDLER_VERSION_MAJOR.."."..FONT_HANDLER_VERSION_MINOR

local djui_classic_hud_set_font = djui_hud_set_font
local djui_classic_hud_print_text = djui_hud_print_text
local djui_classic_hud_print_text_interpolated = djui_hud_print_text_interpolated
local djui_classic_hud_measure_text = djui_hud_measure_text

local customFont = false

local fontTable = {}

CUSTOM_FONT_COUNT = FONT_COUNT
local customFontType = FONT_NORMAL

local latinChars = {
    [32] = " ", [33] = "!", [34] = "\"", [35] = "#", [36] = "$", [37] = "%", [38] = "&", [39] = "'",
    [40] = "(", [41] = ")", [42] = "*", [43] = "+", [44] = ",", [45] = "-", [46] = ".", [47] = "/",
    [48] = "0", [49] = "1", [50] = "2", [51] = "3", [52] = "4", [53] = "5", [54] = "6", [55] = "7",
    [56] = "8", [57] = "9", [58] = ":", [59] = ";", [60] = "<", [61] = "=", [62] = ">", [63] = "?",
    [64] = "@", [65] = "A", [66] = "B", [67] = "C", [68] = "D", [69] = "E", [70] = "F", [71] = "G",
    [72] = "H", [73] = "I", [74] = "J", [75] = "K", [76] = "L", [77] = "M", [78] = "N", [79] = "O",
    [80] = "P", [81] = "Q", [82] = "R", [83] = "S", [84] = "T", [85] = "U", [86] = "V", [87] = "W",
    [88] = "X", [89] = "Y", [90] = "Z", [91] = "[", [92] = "\\", [93] = "]", [94] = "^", [95] = "_",
    [96] = "`", [97] = "a", [98] = "b", [99] = "c", [100] = "d", [101] = "e", [102] = "f", [103] = "g",
    [104] = "h", [105] = "i", [106] = "j", [107] = "k", [108] = "l", [109] = "m", [110] = "n", [111] = "o",
    [112] = "p", [113] = "q", [114] = "r", [115] = "s", [116] = "t", [117] = "u", [118] = "v", [119] = "w",
    [120] = "x", [121] = "y", [122] = "z", [123] = "{", [124] = "|", [125] = "}", [126] = "~",
    -- Latin-1 Supplement
    [160] = " ", [161] = "¡", [162] = "¢", [163] = "£", [164] = "¤", [165] = "¥", [166] = "¦", [167] = "§",
    [168] = "¨", [169] = "©", [170] = "ª", [171] = "«", [172] = "¬", [173] = "­", [174] = "®", [175] = "¯",
    [176] = "°", [177] = "±", [178] = "²", [179] = "³", [180] = "´", [181] = "µ", [182] = "¶", [183] = "·",
    [184] = "¸", [185] = "¹", [186] = "º", [187] = "»", [188] = "¼", [189] = "½", [190] = "¾", [191] = "¿",
    [192] = "À", [193] = "Á", [194] = "Â", [195] = "Ã", [196] = "Ä", [197] = "Å", [198] = "Æ", [199] = "Ç",
    [200] = "È", [201] = "É", [202] = "Ê", [203] = "Ë", [204] = "Ì", [205] = "Í", [206] = "Î", [207] = "Ï",
    [208] = "Ð", [209] = "Ñ", [210] = "Ò", [211] = "Ó", [212] = "Ô", [213] = "Õ", [214] = "Ö", [215] = "×",
    [216] = "Ø", [217] = "Ù", [218] = "Ú", [219] = "Û", [220] = "Ü", [221] = "Ý", [222] = "Þ", [223] = "ß",
    [224] = "à", [225] = "á", [226] = "â", [227] = "ã", [228] = "ä", [229] = "å", [230] = "æ", [231] = "ç",
    [232] = "è", [233] = "é", [234] = "ê", [235] = "ë", [236] = "ì", [237] = "í", [238] = "î", [239] = "ï",
    [240] = "ð", [241] = "ñ", [242] = "ò", [243] = "ó", [244] = "ô", [245] = "õ", [246] = "ö", [247] = "÷",
    [248] = "ø", [249] = "ù", [250] = "ú", [251] = "û", [252] = "ü", [253] = "ý", [254] = "þ", [255] = "ÿ"
}

local HudAnimTimer = 0

local function convert_unicode_table_to_string_table(input)
    local output = {}
    for i = 1, #input do
        local letter = input[i]
        if letter ~= nil and latinChars[letter.id] ~= nil then
            output[latinChars[letter.id]] = letter
        end
    end
    return output
end

local function string_to_table(str)
    local charArray = {};
    local iStart = 0;
    local strLen = str:len();
    local function bit(b)
        return 2 ^ (b - 1);
    end
    local function hasbit(w, b)
        return w % (b + b) >= b
    end
    local checkMultiByte = function(i)
        if (iStart ~= 0) then
            charArray[#charArray + 1] = str:sub(iStart, i - 1)
            iStart = 0
        end
    end
    for i = 1, strLen do
        local b = str:byte(i)
        local multiStart = hasbit(b, bit(7)) and hasbit(b, bit(8))
        local multiTrail = not hasbit(b, bit(7)) and hasbit(b, bit(8))
        if (multiStart) then
            checkMultiByte(i)
            iStart = i
        elseif (not multiTrail) then
            checkMultiByte(i)
            charArray[#charArray + 1] = str:sub(i, i)
        end
    end
    return charArray
end

---@param texture TextureInfo
---@param info table
---@param spacing integer
---@param offset integer
---@param backup string
---@param scale integer
---@return DjuiFontType
function djui_hud_add_font(texture, info, spacing, offset, backup, scale)
    if texture == nil then return FONT_NORMAL end
    if info == nil then return FONT_NORMAL end
    if spacing == nil then spacing = 1 end
    if offset == nil then offset = 0 end
    if backup == nil then backup = "x" end
    if scale == nil then scale = 1 end
    if info[1] ~= nil and info[1].id ~= nil then
        info = convert_unicode_table_to_string_table(info)
    end
    CUSTOM_FONT_COUNT = CUSTOM_FONT_COUNT + 1
    fontTable[CUSTOM_FONT_COUNT] = {
        spritesheet = texture,
        spacing = spacing,
        offset = offset,
        info = info,
        backup = backup,
        scale = scale,
    }
    return CUSTOM_FONT_COUNT
end

---@param fontType DjuiFontType
---@return nil
function djui_hud_set_font(fontType)
    if fontType > FONT_COUNT then
        customFont = true
        customFontType = fontType
    else
        customFont = false
        djui_classic_hud_set_font(fontType)
    end
end

local textShake = 0
function djui_hud_effect_shake(intensity)
    textShake = math.ceil(intensity*100)*0.01
end

local textWaveX = 0
local textWaveY = 0
local textWaveSpeed = 0
function djui_hud_effect_wave(x, y, speed)
    textWaveX = x
    textWaveY = y
    textWaveSpeed = speed
end

---@param message string
---@param x number
---@param y number
---@param scale number
---@return nil
function djui_hud_print_text(message, x, y, scale)
    if customFont then
        if message == nil or message == "" then return end
        local message = string_to_table(message)
        local currFont = fontTable[customFontType]
        y = y + currFont.offset
        scale = scale*currFont.scale
        for i = 1, #message do
            local letter = message[i]
            if letter and letter ~= " " then
                if currFont.info[letter] == nil then
                    letter = currFont.backup
                end
                local scaleWidth = scale*(currFont.info[letter].height/currFont.info[letter].width)
                djui_hud_render_texture_tile(currFont.spritesheet,
                x + ((currFont.info[letter].xoffset or 0)*scale) + math.random(-textShake*100, textShake*100)*0.01 + math.sin((HudAnimTimer+i*2)*textWaveSpeed*0.1)*textWaveX,
                y + ((currFont.info[letter].yoffset or 0)*scale) + math.random(-textShake*100, textShake*100)*0.01 + math.cos((HudAnimTimer+i*2)*textWaveSpeed*0.1)*textWaveY,
                scaleWidth, scale,
                currFont.info[letter].x,
                currFont.info[letter].y,
                currFont.info[letter].width,
                currFont.info[letter].height)
            else
                letter = currFont.backup
            end
            x = x + (currFont.info[letter].width + currFont.spacing)*scale
        end
    else
        djui_classic_hud_print_text(message, x, y, scale)
    end
end

---@param message string
---@param prevX number
---@param prevY number
---@param prevScale number
---@param x number
---@param y number
---@param scale number
---@return nil
-- Custom Fonts do not currently support Interpolation due to lack of RESOLUTION_N64 support
function djui_hud_print_text_interpolated(message, prevX, prevY, prevScale, x, y, scale)
    if customFont then
        if message == nil or message == "" then return end
        local message = string_to_table(message)
        local currFont = fontTable[customFontType]
        prevY = prevY + currFont.offset
        y = y + currFont.offset
        scale = scale*currFont.scale
        for i = 1, #message do
            local letter = message[i]
            if letter and letter ~= " " then
                if currFont.info[letter] == nil then
                    letter = currFont.backup
                end
                local prevScaleWidth = prevScale*(currFont.info[letter].height/currFont.info[letter].width)
                local scaleWidth = scale*(currFont.info[letter].height/currFont.info[letter].width)
                local xOffset = ((currFont.info[letter].xoffset or 0)*scale) + math.random(-textShake*100, textShake*100)*0.01 + math.sin((HudAnimTimer+i*2)*textWaveSpeed*0.1)*textWaveX
                local yOffset = ((currFont.info[letter].yoffset or 0)*scale) + math.random(-textShake*100, textShake*100)*0.01 + math.cos((HudAnimTimer+i*2)*textWaveSpeed*0.1)*textWaveY 
                djui_hud_render_texture_tile_interpolated(currFont.spritesheet,
                prevX + xOffset,
                prevY + yOffset,
                prevScaleWidth, prevScale,
                x + xOffset,
                y + yOffset,
                scaleWidth, scale,
                currFont.info[letter].x,
                currFont.info[letter].y,
                currFont.info[letter].width,
                currFont.info[letter].height)
            else
                letter = currFont.backup
            end
            x = x + (currFont.info[letter].width + currFont.spacing)*scale
            prevX = prevX + (currFont.info[letter].width + currFont.spacing)*prevScale
        end
    else
        djui_classic_hud_print_text_interpolated(message, prevX, prevY, prevScale, x, y, scale)
    end
end

---@param message string
---@return number
function djui_hud_measure_text(message)
    if customFont then
        if message == nil or message == "" then return end
        local message = string_to_table(message)
        local currFont = fontTable[customFontType]
        local scale = 1
        local x = 0
        for i = 1, #message do
            local letter = message[i]
            if letter and letter ~= " " then
                if currFont.info[letter] == nil then
                    letter = currFont.backup
                end
            else
                letter = currFont.backup
            end
            x = x + (currFont.info[letter].width + currFont.spacing)*scale
        end
        return x
    else
        return djui_classic_hud_measure_text(message)
    end
end

local function hud_update()
    -- Reset Values Every Frame
    textShake = 0
    textWaveX = 0
    textWaveY = 0
    textWaveSpeed = 0

    -- Update Basic Anim Timer
    HudAnimTimer = HudAnimTimer + 1
end

hook_event(HOOK_ON_HUD_RENDER_BEHIND, hud_update)

-- Adding custom fonts here to prevent main clutter
fontdataCharacteristic = {
    ["A"] = {x = 0,    y = 0, width = 26, height = 32},
    ["B"] = {x = 32,   y = 0, width = 25, height = 32},
    ["C"] = {x = 32*2, y = 0, width = 25, height = 32},
    ["D"] = {x = 32*3, y = 0, width = 23, height = 32},
    ["E"] = {x = 32*4, y = 0, width = 24, height = 32},
    ["F"] = {x = 32*5, y = 0, width = 24, height = 32},
    ["G"] = {x = 32*6, y = 0, width = 26, height = 32},
    ["H"] = {x = 32*7, y = 0, width = 25, height = 32},
    
    ["I"] = {x = 0,    y = 32, width = 15, height = 32},
    ["J"] = {x = 32,   y = 32, width = 21, height = 32},
    ["K"] = {x = 32*2, y = 32, width = 25, height = 32},
    ["L"] = {x = 32*3, y = 32, width = 22, height = 32},
    ["M"] = {x = 32*4, y = 32, width = 29, height = 32},
    ["N"] = {x = 32*5, y = 32, width = 27, height = 32},
    ["Ñ"] = {x = 32*6, y = 32, width = 27, height = 32},
    ["O"] = {x = 32*7, y = 32, width = 26, height = 32},
    
    ["P"] = {x = 0,    y = 32*2, width = 25, height = 32},
    ["Q"] = {x = 32,   y = 32*2, width = 27, height = 32},
    ["R"] = {x = 32*2, y = 32*2, width = 25, height = 32},
    ["S"] = {x = 32*3, y = 32*2, width = 24, height = 32},
    ["T"] = {x = 32*4, y = 32*2, width = 28, height = 32},
    ["U"] = {x = 32*5, y = 32*2, width = 26, height = 32},
    ["V"] = {x = 32*6, y = 32*2, width = 27, height = 32},
    ["W"] = {x = 32*7, y = 32*2, width = 30, height = 32},
    
    ["X"] = {x = 0,    y = 32*3, width = 28, height = 32},
    ["Y"] = {x = 32,   y = 32*3, width = 27, height = 32},
    ["Z"] = {x = 32*2, y = 32*3, width = 27, height = 32},
    ["!"] = {x = 32*3, y = 32*3, width = 30, height = 32},
    ["?"] = {x = 32*4, y = 32*3, width = 27, height = 32},
    ["@"] = {x = 32*5, y = 32*3, width = 29, height = 32},
    ["#"] = {x = 32*6, y = 32*3, width = 29, height = 32},
    ["$"] = {x = 32*7, y = 32*3, width = 23, height = 32},
    
    ["%"] = {x = 0,    y = 32*4, width = 27, height = 32},
    ["^"] = {x = 32,   y = 32*4, width = 24, height = 32},
    ["&"] = {x = 32*2, y = 32*4, width = 29, height = 32},
    ["*"] = {x = 32*3, y = 32*4, width = 18, height = 32},
    ["("] = {x = 32*4, y = 32*4, width = 17, height = 32},
    [")"] = {x = 32*5, y = 32*4, width = 17, height = 32},
    ["_"] = {x = 32*6, y = 32*4, width = 31, height = 32},
    ["-"] = {x = 32*7, y = 32*4, width = 23, height = 32},
    
    ["+"] = {x = 0,    y = 32*5, width = 24, height = 32},
    ["="] = {x = 32,   y = 32*5, width = 27, height = 32},
    ["<"] = {x = 32*2, y = 32*5, width = 23, height = 32},
    [">"] = {x = 32*3, y = 32*5, width = 23, height = 32},
    ["."] = {x = 32*4, y = 32*5, width = 11, height = 32},
    [","] = {x = 32*5, y = 32*5, width = 11, height = 32},
    [":"] = {x = 32*6, y = 32*5, width = 11, height = 32},
    [";"] = {x = 32*7, y = 32*5, width = 11, height = 32},
    
    ["/"] = {x = 0,    y = 32*6, width = 28, height = 32},
    ["\\"] = {x = 32,  y = 32*6, width = 28, height = 32},
    ['"'] = {x = 32*2, y = 32*6, width = 14, height = 32},
    ["'"] = {x = 32*3, y = 32*6, width = 9,  height = 32},
    ["|"] = {x = 32*4, y = 32*6, width = 10, height = 32},
    ["~"] = {x = 32*5, y = 32*6, width = 23, height = 32},
    ["1"] = {x = 32*6, y = 32*6, width = 23, height = 32},
    ["2"] = {x = 32*7, y = 32*6, width = 26, height = 32},
    
    ["3"] = {x = 0,    y = 32*7, width = 24, height = 32},
    ["4"] = {x = 32,   y = 32*7, width = 24, height = 32},
    ["5"] = {x = 32*2, y = 32*7, width = 26, height = 32},
    ["6"] = {x = 32*3, y = 32*7, width = 26, height = 32},
    ["7"] = {x = 32*4, y = 32*7, width = 30, height = 32},
    ["8"] = {x = 32*5, y = 32*7, width = 22, height = 32},
    ["9"] = {x = 32*6, y = 32*7, width = 24, height = 32},
    ["0"] = {x = 32*7, y = 32*7, width = 24, height = 32},
    
}

FONT_CHARACTERISTIC = djui_hud_add_font(get_texture_info("char_select_font_characteristic"), fontdataCharacteristic, -5, 0, "X", 1)