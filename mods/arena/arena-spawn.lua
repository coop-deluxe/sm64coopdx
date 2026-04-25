sArenaSpawns = {}

function bhv_arena_spawn_init(obj)
    table.insert(sArenaSpawns, {
        pos = { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ },
        yaw = obj.oFaceAngleYaw,
        type = (obj.oBehParams >> 24) & 0xFF,
    })
    obj_mark_for_deletion(obj)
end

id_bhvArenaSpawn = hook_behavior(nil, OBJ_LIST_LEVEL, true, bhv_arena_spawn_init, nil)

-------------

function find_spawn_point()
    if gGameModes[gGlobalSyncTable.gameMode].teamSpawns then
        local spawn = sArenaSpawns[math.random(#sArenaSpawns)]
        local s = gPlayerSyncTable[0]
        local itr = 0
        repeat
            spawn = sArenaSpawns[math.random(#sArenaSpawns)]
            itr = itr + 1
        until spawn.type == s.team or itr > 50
        return spawn
    end
    local spawn = sArenaSpawns[math.random(#sArenaSpawns)]
    return spawn
end

function on_level_init()
    sArenaSpawns = {}
end

hook_event(HOOK_ON_LEVEL_INIT, on_level_init)