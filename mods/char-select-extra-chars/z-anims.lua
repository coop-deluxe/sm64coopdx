-- Character Animations --
-- Don't edit this file, just use the `character_add_animations(charNum, animTable)` function

if not _G.charSelectExists then return end

local function update()
    gPlayerSyncTable[0].characterType = charSelect.character_get_current_number() -- Synced Character Type
end

local function character_anims(m)
    local p = gPlayerSyncTable[m.playerIndex]
    if animTables[p.characterType] then
        local animID = animTables[p.characterType][m.marioObj.header.gfx.animInfo.animID]
        if animID then
            smlua_anim_util_set_animation(m.marioObj, animID)
        end
    end
end

hook_event(HOOK_UPDATE, update)
hook_event(HOOK_MARIO_UPDATE, character_anims)