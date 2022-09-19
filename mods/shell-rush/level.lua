gRaceShells = {}

gLevelData = gLevelDataTable[-1]

function erase_unwanted_entities(objList)
    local obj = obj_get_first(objList)
    while obj ~= nil do
        local behaviorId = get_id_from_behavior(obj.behavior)
        if gLevelData.erase[behaviorId] ~= nil then
            obj.activeFlags = ACTIVE_FLAG_DEACTIVATED
        end

        -- iterate
        obj = obj_get_next(obj)
    end
end

function on_level_init()
    -- set level data
    local level = gNetworkPlayers[0].currLevelNum
    if gLevelDataTable[level] ~= nil then
        gLevelData = gLevelDataTable[level]
    else
        gLevelData = gLevelDataTable[-1]
    end

    -- spawn all of the racing shells
    for i = 0, (MAX_PLAYERS - 1) do
        gRaceShells[i] = spawn_non_sync_object(
            id_bhvRaceShell,
            E_MODEL_KOOPA_SHELL,
            0, 0, 0,
            function (obj) obj.heldByPlayerIndex = i end
        )
    end

    -- spawn all of the waypoints
    for i in pairs(gLevelData.waypoints) do
        local waypoint = get_waypoint(i)
        spawn_non_sync_object(
            id_bhvRaceRing,
            E_MODEL_WATER_RING,
            waypoint.x, waypoint.y, waypoint.z,
            function (obj) obj.oWaypointIndex = i end
        )
    end

    -- spawn level-specific platforms
    for i in pairs(gLevelData.platforms) do
        local p = gLevelData.platforms[i]
        spawn_non_sync_object(
            id_bhvStaticCheckeredPlatform,
            E_MODEL_CHECKERBOARD_PLATFORM,
            p.pos.x, p.pos.y, p.pos.z,
            function (obj)
                obj.oOpacity = 255
                obj.oFaceAnglePitch = p.rot.x
                obj.oFaceAngleYaw = p.rot.y
                obj.oFaceAngleRoll = p.rot.z
                obj_scale_xyz(obj, p.scale.x, p.scale.y, p.scale.z)
            end)
    end
    -- reset the local player's data
    local s = gPlayerSyncTable[0]
    s.waypoint = 1
    s.lap = 0
    s.finish = 0
    for i = 0, 2 do
        s.powerup[i] = POWERUP_NONE
    end

    -- reset the custom level objects
    for i in pairs(gLevelData.powerups) do
        gLevelData.powerups[i].obj = nil
    end

    for i = 0, (MAX_PLAYERS - 1) do
        for j = 0, 2 do
            gPowerups[i][j] = nil
        end
    end

    -- erase specified level entities
    erase_unwanted_entities(OBJ_LIST_GENACTOR)
    erase_unwanted_entities(OBJ_LIST_LEVEL)
    erase_unwanted_entities(OBJ_LIST_SURFACE)

    -- reset rankings
    race_clear_rankings()

    -- lower water level on castle grounds
    if gNetworkPlayers[0].currLevelNum == LEVEL_CASTLE_GROUNDS then
        set_environment_region(1, -800)
        set_environment_region(2, -800)
    end
end

function spawn_custom_level_objects()
    -- only handle powerups if we're the server
    if not network_is_server() then
        return
    end

    -- only handle powerups if we're sync valid
    np = gNetworkPlayers[0]
    if (not np.currAreaSyncValid) or (not np.currLevelSyncValid) then
        return
    end

    -- spawn missing powerups
    for i in pairs(gLevelData.powerups) do
        if gLevelData.powerups[i].obj == nil then
            local pos = gLevelData.powerups[i].pos
            gLevelData.powerups[i].obj = spawn_sync_object(
                id_bhvItemBox,
                E_MODEL_ITEM_BOX,
                pos.x, pos.y, pos.z,
                function (obj)
                    --obj.oMoveAngleYaw = m.faceAngle.y
                end
            )
        end
    end
end

function on_object_unload(obj)
    -- react to powerups getting unloaded
    for i = 0, (MAX_PLAYERS - 1) do
        for j = 0, 2 do
            if obj == gPowerups[i][j] then
                gPowerups[i][j] = nil
            end
        end
    end

    -- react to level objects getting unloaded
    for i in pairs(gLevelData.powerups) do
        if gLevelData.powerups[i].obj == obj then
            gLevelData.powerups[i].obj = nil
        end
    end
end

hook_event(HOOK_ON_LEVEL_INIT, on_level_init)
hook_event(HOOK_ON_OBJECT_UNLOAD, on_object_unload)
