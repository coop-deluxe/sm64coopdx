
if incompatibleClient then return 0 end

local function find_character_number(index)
    if index == nil then index = 0 end
    for i = 1, #characterTable do
        if characterTable[i].saveName == gCSPlayers[index].saveName then
            return i
        end
    end
    return 1
end

local function mario_update(m)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_MARIO_UPDATE
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m)
end
hook_event(HOOK_MARIO_UPDATE, mario_update)

local function before_mario_update(m)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_BEFORE_MARIO_UPDATE
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m)
end
hook_event(HOOK_BEFORE_MARIO_UPDATE, before_mario_update)

local function before_phys_step(m, stepType)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_BEFORE_PHYS_STEP
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m, stepType)
end
hook_event(HOOK_BEFORE_PHYS_STEP, before_phys_step)

local function allow_pvp_attack(attacker, victim, int)
    if stopMovesets then return end
    local hook = HOOK_ALLOW_PVP_ATTACK
    local attackerMoveset = characterMovesets[find_character_number(attacker.playerIndex)]
    local victimMoveset = characterMovesets[find_character_number(victim.playerIndex)]
    if gCSPlayers[attacker.playerIndex].movesetToggle then
        if (attackerMoveset ~= nil and attackerMoveset[hook] ~= nil) then
            attackerMoveset[hook](attacker, victim, int)
        end
    end
    if gCSPlayers[victim.playerIndex].movesetToggle then
        if (victimMoveset ~= nil and victimMoveset[hook] ~= nil) then
            victimMoveset[hook](attacker, victim, int)
        end
    end
end
hook_event(HOOK_ALLOW_PVP_ATTACK, allow_pvp_attack)

local function on_pvp_attack(attacker, victim, int)
    if stopMovesets then return end
    local hook = HOOK_ON_PVP_ATTACK
    local attackerMoveset = characterMovesets[find_character_number(attacker.playerIndex)]
    local victimMoveset = characterMovesets[find_character_number(victim.playerIndex)]
    if gCSPlayers[attacker.playerIndex].movesetToggle then
        if (attackerMoveset ~= nil and attackerMoveset[hook] ~= nil) then
            attackerMoveset[hook](attacker, victim, int)
        end
    end
    if gCSPlayers[victim.playerIndex].movesetToggle then
        if (victimMoveset ~= nil and victimMoveset[hook] ~= nil) then
            victimMoveset[hook](attacker, victim, int)
        end
    end
end
hook_event(HOOK_ON_PVP_ATTACK, on_pvp_attack)

local function on_interact(m, o, intType, intValue)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_ON_INTERACT
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m, o, intType, intValue)
end
hook_event(HOOK_ON_INTERACT, on_interact)

local function allow_interact(m, o, intType)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_ALLOW_INTERACT
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m, o, intType)
end
hook_event(HOOK_ALLOW_INTERACT, allow_interact)

local function on_set_mario_action(m)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_ON_SET_MARIO_ACTION
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m)
end
hook_event(HOOK_ON_SET_MARIO_ACTION, on_set_mario_action)

local function before_set_mario_action(m, nextAct)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_BEFORE_SET_MARIO_ACTION
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m, nextAct)
end
hook_event(HOOK_BEFORE_SET_MARIO_ACTION, before_set_mario_action)

local function on_death(m)
    if stopMovesets or not gCSPlayers[m.playerIndex].movesetToggle then return end
    local hook = HOOK_ON_DEATH
    local currMoveset = characterMovesets[find_character_number(m.playerIndex)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](m)
end
hook_event(HOOK_ON_DEATH, on_death)

local function hud_render()
    if stopMovesets or not gCSPlayers[0].movesetToggle then return end
    local hook = HOOK_ON_HUD_RENDER
    local currMoveset = characterMovesets[find_character_number(0)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook]()
end
hook_event(HOOK_ON_HUD_RENDER, hud_render)

local function hud_render_behind()
    if stopMovesets or not gCSPlayers[0].movesetToggle then return end
    local hook = HOOK_ON_HUD_RENDER_BEHIND
    local currMoveset = characterMovesets[find_character_number(0)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook]()
end
hook_event(HOOK_ON_HUD_RENDER_BEHIND, hud_render_behind)

local function level_init()
    if stopMovesets or not gCSPlayers[0].movesetToggle then return end
    local hook = HOOK_ON_LEVEL_INIT
    local currMoveset = characterMovesets[find_character_number(0)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook]()
end
hook_event(HOOK_ON_LEVEL_INIT, level_init)

local function sync_valid()
    if stopMovesets or not gCSPlayers[0].movesetToggle then return end
    local hook = HOOK_ON_SYNC_VALID
    local currMoveset = characterMovesets[find_character_number(0)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook]()
end
hook_event(HOOK_ON_SYNC_VALID, sync_valid)

local function object_render(obj)
    if stopMovesets or not gCSPlayers[0].movesetToggle then return end
    local hook = HOOK_ON_OBJECT_RENDER
    local currMoveset = characterMovesets[find_character_number(0)]
    if currMoveset == nil or currMoveset[hook] == nil then return end
    return currMoveset[hook](obj)
end
hook_event(HOOK_ON_OBJECT_RENDER, object_render)