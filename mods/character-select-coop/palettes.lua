if incompatibleClient then return 0 end

-- localize functions to improve performance - z-palettes.lua
local network_player_set_override_palette_color,network_player_reset_override_palette = network_player_set_override_palette_color,network_player_reset_override_palette

characterColorPresets = {
    [E_MODEL_MARIO] = {
        currPalette = 1,
        {
            name = "Default",
            [PANTS]  = { r = 0x00, g = 0x00, b = 0xff },
            [SHIRT]  = { r = 0xff, g = 0x00, b = 0x00 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x72, g = 0x1c, b = 0x0e },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0xff, g = 0x00, b = 0x00 },
            [EMBLEM] = { r = 0xff, g = 0x00, b = 0x00 },
        },
        {
            name = "New Game +",
            [PANTS]  = { r = 0x19, g = 0x4b, b = 0xa3 },
            [SHIRT]  = { r = 0xff, g = 0x30, b = 0x33 },
            [GLOVES] = { r = 0xdd, g = 0xdd, b = 0xdd },
            [SHOES]  = { r = 0x51, g = 0x28, b = 0x00 },
            [HAIR]   = { r = 0x58, g = 0x09, b = 0x00 },
            [SKIN]   = { r = 0xff, g = 0xaf, b = 0x8c },
            [CAP]    = { r = 0xff, g = 0x30, b = 0x33 },
            [EMBLEM] = { r = 0xff, g = 0x30, b = 0x33 },
        },
        {
            name = "Fire Flower",
            [PANTS]  = { r = 0xb2, g = 0x28, b = 0x18 },
            [SHIRT]  = { r = 0xff, g = 0xe0, b = 0xe0 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x72, g = 0x1c, b = 0x0e },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0xff, g = 0xe0, b = 0xe0 },
            [EMBLEM] = { r = 0xff, g = 0x00, b = 0x00 },
        },
        {
            name = "Burgundy",
            [PANTS]  = { r = 0x23, g = 0x11, b = 0x03 },
            [SHIRT]  = { r = 0x68, g = 0x0A, b = 0x17 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x68, g = 0x0A, b = 0x17 },
            [EMBLEM] = { r = 0x68, g = 0x0A, b = 0x17 },
        },
        {
            name = "Raspberry",
            [PANTS]  = { r = 0xD6, g = 0x35, b = 0x4D },
            [SHIRT]  = { r = 0x3B, g = 0x8F, b = 0xF7 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x3B, g = 0x8F, b = 0xF7 },
            [EMBLEM] = { r = 0x3B, g = 0x8F, b = 0xF7 },
        },

    },
    [E_MODEL_LUIGI] = {
        currPalette = 1,
        {
            name = "Default",
            [PANTS]  = { r = 0x00, g = 0x00, b = 0xff },
            [SHIRT]  = { r = 0x00, g = 0xff, b = 0x00 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x72, g = 0x1c, b = 0x0e },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0x00, g = 0xff, b = 0x00 },
            [EMBLEM] = { r = 0x00, g = 0xff, b = 0x00 },
        },
        {
            name = "Mint",
            [PANTS]  = { r = 0x53, g = 0x39, b = 0x3D },
            [SHIRT]  = { r = 0x95, g = 0xD0, b = 0x8F },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x95, g = 0xD0, b = 0x8F },
            [EMBLEM] = { r = 0x95, g = 0xD0, b = 0x8F },
        },
        {
            name = "Cold Crevase",
            [PANTS]  = { r = 0xD4, g = 0xDF, b = 0xE7 },
            [SHIRT]  = { r = 0x51, g = 0xA9, b = 0x9C },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x6B, g = 0x41, b = 0x00 },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0xD4, g = 0xDF, b = 0xE7 },
            [EMBLEM] = { r = 0x51, g = 0xA9, b = 0x9C },
        },
        {
            name = "Greedy",
            [PANTS]  = { r = 0x00, g = 0x48, b = 0x8a },
            [SHIRT]  = { r = 0xf7, g = 0xaf, b = 0x25 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0xc0, g = 0x21, b = 0x00 },
            [HAIR]   = { r = 0x00, g = 0x00, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0x00, g = 0x48, b = 0x8a },
            [EMBLEM] = { r = 0x00, g = 0x00, b = 0x00 },
        },
        {
            name = "Kindness",
            [PANTS]  = { r = 0xff, g = 0x44, b = 0xff },
            [SHIRT]  = { r = 0x93, g = 0x00, b = 0x90 },
            [GLOVES] = { r = 0xff, g = 0x99, b = 0xff },
            [SHOES]  = { r = 0xaa, g = 0x2c, b = 0x66 },
            [HAIR]   = { r = 0xf3, g = 0x65, b = 0xda },
            [SKIN]   = { r = 0xc8, g = 0x6b, b = 0x9d },
            [CAP]    = { r = 0xef, g = 0x2b, b = 0xea },
            [EMBLEM] = { r = 0xef, g = 0x2b, b = 0xea },
        },
    },
    [E_MODEL_TOAD_PLAYER] = {
        currPalette = 1,
        {
            name = "Default",
            [PANTS]  = { r = 0xff, g = 0xff, b = 0xff },
            [SHIRT]  = { r = 0x4c, g = 0x2c, b = 0xd3 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x68, g = 0x40, b = 0x1b },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xd5, b = 0xa1 },
            [CAP]    = { r = 0xff, g = 0x00, b = 0x00 },
            [EMBLEM] = { r = 0xff, g = 0x00, b = 0x00 },
        },
        {
            name = "Bucken Berry",
            [PANTS]  = { r = 0xff, g = 0xff, b = 0xff },
            [SHIRT]  = { r = 0x00, g = 0x00, b = 0xff },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x68, g = 0x40, b = 0x1b },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xd5, b = 0xa1 },
            [CAP]    = { r = 0x00, g = 0x00, b = 0xff },
            [EMBLEM] = { r = 0x00, g = 0x00, b = 0xff },
        },
        {
            name = "Ala Gold",
            [PANTS]  = { r = 0xff, g = 0xff, b = 0xff },
            [SHIRT]  = { r = 0xff, g = 0xff, b = 0x00 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x68, g = 0x40, b = 0x1b },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xd5, b = 0xa1 },
            [CAP]    = { r = 0xff, g = 0xff, b = 0x00 },
            [EMBLEM] = { r = 0xff, g = 0xff, b = 0x00 },
        },
        {
            name = "Jet Black",
            [PANTS]  = { r = 0x1A, g = 0x1A, b = 0x1A },
            [SHIRT]  = { r = 0x2C, g = 0x2C, b = 0x2C },
            [GLOVES] = { r = 0x64, g = 0x64, b = 0x64 },
            [SHOES]  = { r = 0x64, g = 0x64, b = 0x64 },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x1A, g = 0x1A, b = 0x1A },
            [EMBLEM] = { r = 0x1A, g = 0x1A, b = 0x1A },
        },
        {
            name = "Hot Pink",
            [PANTS]  = { r = 0x34, g = 0x16, b = 0x0D },
            [SHIRT]  = { r = 0xC1, g = 0x2C, b = 0x72 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0xC1, g = 0x2C, b = 0x72 },
            [EMBLEM] = { r = 0xC1, g = 0x2C, b = 0x72 },
        },
        {
            name = "Goomba",
            [PANTS]  = { r = 0xC6, g = 0xB1, b = 0x32 },
            [SHIRT]  = { r = 0x95, g = 0x43, b = 0x01 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x95, g = 0x43, b = 0x01 },
            [EMBLEM] = { r = 0x95, g = 0x43, b = 0x01 },
        },

    },
    [E_MODEL_WALUIGI] = {
        currPalette = 1,
        {
            name = "Default",
            [PANTS]  = { r = 0x16, g = 0x16, b = 0x27 },
            [SHIRT]  = { r = 0x61, g = 0x26, b = 0xb0 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0xfe, g = 0x76, b = 0x00 },
            [HAIR]   = { r = 0x73, g = 0x53, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0x61, g = 0x26, b = 0xb0 },
            [EMBLEM] = { r = 0xff, g = 0xde, b = 0x00 },
        },
        {
            name = "Cobalt",
            [PANTS]  = { r = 0x3F, g = 0x3F, b = 0xFF },
            [SHIRT]  = { r = 0x0A, g = 0x0A, b = 0x28 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x39, g = 0x0E, b = 0x07 },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x3F, g = 0x3F, b = 0xFF },
            [EMBLEM] = { r = 0x3F, g = 0x3F, b = 0xFF },
        },
        {
            name = "Clover",
            [PANTS]  = { r = 0x14, g = 0x19, b = 0x14 },
            [SHIRT]  = { r = 0x4C, g = 0x5F, b = 0x20 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x4C, g = 0x5F, b = 0x20 },
            [EMBLEM] = { r = 0x4C, g = 0x5F, b = 0x20 },
        },
        {
            name = "Blueberry Pie",
            [PANTS]  = { r = 0xEB, g = 0x8A, b = 0x4B },
            [SHIRT]  = { r = 0x10, g = 0x1B, b = 0x2E },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x10, g = 0x1B, b = 0x2E },
            [EMBLEM] = { r = 0x10, g = 0x1B, b = 0x2E },
        },
        {
            name = "Tennis Loser",
            [PANTS]  = { r = 0x16, g = 0x16, b = 0x27 },
            [SHIRT]  = { r = 0x5A, g = 0x39, b = 0x21 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x5A, g = 0x00, b = 0xCE },
            [HAIR]   = { r = 0x29, g = 0x10, b = 0x00 },
            [SKIN]   = { r = 0xE7, g = 0xB5, b = 0x94 },
            [CAP]    = { r = 0x5A, g = 0x39, b = 0x21 },
            [EMBLEM] = { r = 0xFF, g = 0xDE, b = 0x00 },
        },
        {
            name = "Sealed Away",
            [PANTS]  = { r = 0x00, g = 0x98, b = 0x00 },
            [SHIRT]  = { r = 0x47, g = 0xc5, b = 0xff },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x72, g = 0x1c, b = 0x0e },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0x47, g = 0xc5, b = 0xff },
            [EMBLEM] = { r = 0xff, g = 0xde, b = 0x00 },
        },

    },
    [E_MODEL_WARIO] = {
        currPalette = 1,
        {
            name = "Default",
            [PANTS]  = { r = 0x7f, g = 0x20, b = 0x7a },
            [SHIRT]  = { r = 0xff, g = 0xbd, b = 0x00 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x0e, g = 0x72, b = 0x1c },
            [HAIR]   = { r = 0x73, g = 0x53, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0xff, g = 0xbd, b = 0x00 },
            [EMBLEM] = { r = 0x00, g = 0x00, b = 0xff },
        },
        {
            name = "Ruby",
            [PANTS]  = { r = 0xE1, g = 0x05, b = 0x31 },
            [SHIRT]  = { r = 0x28, g = 0x0A, b = 0x0A },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x39, g = 0x0E, b = 0x07 },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0xE1, g = 0x05, b = 0x31 },
            [EMBLEM] = { r = 0xE1, g = 0x05, b = 0x31 },
        },
        {
            name = "Eggplant",
            [PANTS]  = { r = 0xE6, g = 0xE3, b = 0xFF },
            [SHIRT]  = { r = 0x37, g = 0x32, b = 0x42 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x37, g = 0x32, b = 0x42 },
            [EMBLEM] = { r = 0x37, g = 0x32, b = 0x42 },
        },
        {
            name = "Battlements",
            [PANTS]  = { r = 0xF7, g = 0xC2, b = 0x45 },
            [SHIRT]  = { r = 0x55, g = 0x92, b = 0xB2 },
            [GLOVES] = { r = 0xFF, g = 0xFF, b = 0xFF },
            [SHOES]  = { r = 0x72, g = 0x1C, b = 0x0E },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xFE, g = 0xC1, b = 0x79 },
            [CAP]    = { r = 0x55, g = 0x92, b = 0xB2 },
            [EMBLEM] = { r = 0x55, g = 0x92, b = 0xB2 },
        },
        {
            name = "Cotten Candy",
            [PANTS]  = { r = 0x69, g = 0xa1, b = 0xff },
            [SHIRT]  = { r = 0xff, g = 0x7d, b = 0x89 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0xb9, g = 0x48, b = 0xff },
            [HAIR]   = { r = 0x73, g = 0x53, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0x69, g = 0xa1, b = 0xff },
            [EMBLEM] = { r = 0xb9, g = 0x48, b = 0xff },
        },
    }
}

local paletteLoop = #characterColorPresets[E_MODEL_MARIO][1]

local function network_player_set_full_override_palette(networkPlayer, colorTable)
    if colorTable == nil then return end
    for i = 0, paletteLoop do
        network_player_set_override_palette_color(networkPlayer, i, colorTable[i])
    end
end

---@param np NetworkPlayer
function update_preset_palette(np)
    local p = gCSPlayers[np.localIndex]
    local modelId = p.modelId
    if np.connected and gCSPlayers[0].presetPalette > 0 and characterColorPresets[modelId] and gGlobalSyncTable.charSelectRestrictPalettes == 0 then
        network_player_set_full_override_palette(np, characterColorPresets[modelId][p.presetPalette])
    end
end

local prevPresetPalette = {}
local prevModel = {}

local function mario_update(m)
    local np = gNetworkPlayers[m.playerIndex]
    local p = gCSPlayers[m.playerIndex]
    if not startup_init_stall() then return end
    
    if m.playerIndex == 0 and not p.isUpdating then
        p.isUpdating = true
        for i = 1, MAX_PLAYERS - 1 do
            prevPresetPalette[i] = gCSPlayers[i].presetPalette
            prevModel[i] = gCSPlayers[i].modelId
        end
    end
    
    if m.playerIndex == 0 then
        if gGlobalSyncTable.charSelectRestrictPalettes == 0 then
            gCSPlayers[0].presetPalette = characterColorPresets[gCSPlayers[0].modelId] ~= nil and characterColorPresets[gCSPlayers[0].modelId].currPalette or 0
        end
    end

    if np.connected then
        if p.presetPalette == nil or characterColorPresets[p.modelId] == nil then
            if p.presetPalette == nil then
                prevPresetPalette[m.playerIndex] = 0
            end
            p.presetPalette = 0
        end

        if (prevPresetPalette[m.playerIndex] ~= p.presetPalette or prevModel[m.playerIndex] ~= p.modelId) then
            if p.presetPalette == 0 or not characterColorPresets[p.modelId] then
                network_player_reset_override_palette(np)
            end
        end

        prevPresetPalette[m.playerIndex] = p.presetPalette
        prevModel[m.playerIndex] = p.modelId

        if p.presetPalette > 0 and characterColorPresets[p.modelId] and gGlobalSyncTable.charSelectRestrictPalettes == 0 then
            network_player_set_full_override_palette(np, characterColorPresets[p.modelId][p.presetPalette])
        end
    else
        if p.isUpdating then
            p.isUpdating = false
        end
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
