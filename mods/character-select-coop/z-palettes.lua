if incompatibleClient then return 0 end

-- localize functions to improve performance - z-palettes.lua
local network_player_set_override_palette_color,network_player_reset_override_palette = network_player_set_override_palette_color,network_player_reset_override_palette


characterColorPresets = {
    [E_MODEL_MARIO] = {
        [1] = {
            [PANTS]  = { r = 0x00, g = 0x00, b = 0xff },
            [SHIRT]  = { r = 0xff, g = 0x00, b = 0x00 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x72, g = 0x1c, b = 0x0e },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0xff, g = 0x00, b = 0x00 },
            [EMBLEM] = { r = 0xff, g = 0x00, b = 0x00 },
        },
    },
    [E_MODEL_LUIGI] = {
        [1] = {
            [PANTS]  = { r = 0x00, g = 0x00, b = 0xff },
            [SHIRT]  = { r = 0x00, g = 0xff, b = 0x00 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x72, g = 0x1c, b = 0x0e },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0x00, g = 0xff, b = 0x00 },
            [EMBLEM] = { r = 0x00, g = 0xff, b = 0x00 },
        },
    },
    [E_MODEL_TOAD_PLAYER] = {
        [1] = {
            [PANTS]  = { r = 0xff, g = 0xff, b = 0xff },
            [SHIRT]  = { r = 0x4c, g = 0x2c, b = 0xd3 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x68, g = 0x40, b = 0x1b },
            [HAIR]   = { r = 0x73, g = 0x06, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xd5, b = 0xa1 },
            [CAP]    = { r = 0xff, g = 0x00, b = 0x00 },
            [EMBLEM] = { r = 0xff, g = 0x00, b = 0x00 },
        },
    },
    [E_MODEL_WALUIGI] = {
        [1] = {
            [PANTS]  = { r = 0x16, g = 0x16, b = 0x27 },
            [SHIRT]  = { r = 0x61, g = 0x26, b = 0xb0 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0xfe, g = 0x76, b = 0x00 },
            [HAIR]   = { r = 0x73, g = 0x53, b = 0x00 },
            [SHOES]  = { r = 0xfe, g = 0x76, b = 0x00 },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0x61, g = 0x26, b = 0xb0 },
            [EMBLEM] = { r = 0xff, g = 0xde, b = 0x00 },
        },
    },
    [E_MODEL_WARIO] = {
        [1] = {
            [PANTS]  = { r = 0x7f, g = 0x20, b = 0x7a },
            [SHIRT]  = { r = 0xff, g = 0xbd, b = 0x00 },
            [GLOVES] = { r = 0xff, g = 0xff, b = 0xff },
            [SHOES]  = { r = 0x0e, g = 0x72, b = 0x1c },
            [HAIR]   = { r = 0x73, g = 0x53, b = 0x00 },
            [SHOES]  = { r = 0x0e, g = 0x72, b = 0x1c },
            [SKIN]   = { r = 0xfe, g = 0xc1, b = 0x79 },
            [CAP]    = { r = 0xff, g = 0xbd, b = 0x00 },
            [EMBLEM] = { r = 0x00, g = 0x00, b = 0xff },
        },
    }
}

local defaultModels = {
    [CT_MARIO] = E_MODEL_MARIO,
    [CT_LUIGI] = E_MODEL_LUIGI,
    [CT_TOAD] = E_MODEL_TOAD_PLAYER,
    [CT_WALUIGI] = E_MODEL_WALUIGI,
    [CT_WARIO] = E_MODEL_WARIO
}

local paletteLoop = #characterColorPresets[E_MODEL_MARIO][1]

local function network_player_set_full_override_palette(networkPlayer, colorTable)
    if colorTable == nil then return end
    for i = 0, paletteLoop do
        network_player_set_override_palette_color(networkPlayer, i, colorTable[i])
    end
end

--- @param np NetworkPlayer
local function update_preset_palette(np)
    local p = gCSPlayers[np.localIndex]
    local modelId = p.modelId
    if np.connected and gCSPlayers[0].presetPalette > 0 and characterColorPresets[modelId] and not stopPalettes then
        network_player_set_full_override_palette(np, characterColorPresets[modelId][p.presetPalette])
    end
end

-- API funcs
_G.charSelect.update_preset_palette = update_preset_palette

local prevChar = currChar
local prevAlt = 1
local stallTimer = 5

local prevPresetPalette = {}
local prevModel = {}

local function mario_update(m)
    local np = gNetworkPlayers[m.playerIndex]
    local p = gCSPlayers[m.playerIndex]
    local currAlt = characterTable[currChar].currAlt
    
    if m.playerIndex == 0 and not p.isUpdating then
        p.isUpdating = true
        for i = 1, MAX_PLAYERS - 1 do
            prevPresetPalette[i] = gCSPlayers[i].presetPalette
            prevModel[i] = gCSPlayers[i].modelId and gCSPlayers[i].modelId or defaultModels[gMarioStates[i].character.type]
        end
    end

    if np.connected then
        local modelId = p.modelId and p.modelId or defaultModels[m.character.type]
        if p.presetPalette == nil or characterColorPresets[modelId] == nil then
            if p.presetPalette == nil then
                prevPresetPalette[m.playerIndex] = 0
            end
            p.presetPalette = 0
        end

        if (prevPresetPalette[m.playerIndex] ~= p.presetPalette or prevModel[m.playerIndex] ~= modelId) then
            if p.presetPalette == 0 or not characterColorPresets[modelId] then
                network_player_reset_override_palette(np)
            end
        end

        prevPresetPalette[m.playerIndex] = p.presetPalette
        prevModel[m.playerIndex] = modelId

        if p.presetPalette > 0 and characterColorPresets[modelId] and not stopPalettes then
            network_player_set_full_override_palette(np, characterColorPresets[modelId][p.presetPalette])
        end
    else
        if p.isUpdating then
            p.isUpdating = false
        end
    end
    
    if m.playerIndex == 0 then
        if (menuAndTransition or (prevChar ~= currChar or prevAlt ~= currAlt)) and stallTimer == 0 then
            local modelId = p.modelId and p.modelId or defaultModels[m.character.type]
            if optionTable[optionTableRef.autoPalette].toggle > 0 and optionTable[optionTableRef.localModels].toggle > 0 and (currChar ~= 1 and (prevChar ~= currChar or prevAlt ~= currAlt) and p.presetPalette == 0) and characterColorPresets[modelId] and not stopPalettes then
                p.presetPalette = 1
            end
            if optionTable[optionTableRef.localModels].toggle == 0 then
                p.presetPalette = 0
            end
            prevChar = currChar
            prevAlt = currAlt
        end

        if stallTimer > 0 then
            stallTimer = stallTimer - 1
        end
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
