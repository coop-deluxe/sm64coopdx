local function on_level_init()
    if gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_RAINBOW then
        set_lighting_dir(1, -10)
    elseif gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_CITY then
        set_lighting_dir(1, -1)
    elseif gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_CITADEL then
        set_lighting_dir(1, -10)
    elseif gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_FORTS then
        set_lighting_dir(1, -10)
    elseif gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_ORIGIN then
        set_lighting_dir(1, -10)
    elseif gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_PILLARS then
        set_lighting_dir(1, -10)
    else
        set_lighting_dir(1, 0)
    end
end

--- @param m MarioState
local function mario_update(m)
    if gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_CITY then
		m.marioBodyState.lightR = 255
        m.marioBodyState.lightG = 225
        m.marioBodyState.lightB = 115
        m.marioBodyState.shadeR = 19
        m.marioBodyState.shadeG = 58
        m.marioBodyState.shadeB = 212
	elseif gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_RAINBOW then
		m.marioBodyState.lightR = 255
        m.marioBodyState.lightG = 255
        m.marioBodyState.lightB = 255
        m.marioBodyState.shadeR = 19
        m.marioBodyState.shadeG = 58
        m.marioBodyState.shadeB = 212
    else
        m.marioBodyState.lightR = 255
        m.marioBodyState.lightG = 255
        m.marioBodyState.lightB = 255
        m.marioBodyState.shadeR = 127
        m.marioBodyState.shadeG = 127
        m.marioBodyState.shadeB = 127
	end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
hook_event(HOOK_ON_LEVEL_INIT, on_level_init)