if SM64COOPDX_VERSION == nil then return end

-- lighting for Rainbow Road

function on_level_init()
    if gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_RAINBOW then
        set_lighting_dir(1, -10)
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
	
	if gNetworkPlayers[0].currLevelNum == LEVEL_ARENA_RAINBOW then
		set_lighting_color(0, 179)
		set_lighting_color(1, 189)
		set_lighting_color(2, 255)
	else
		set_lighting_color(0, 255)
		set_lighting_color(1, 255)
		set_lighting_color(2, 255)
	end
end

hook_event(HOOK_ON_LEVEL_INIT, on_level_init)