_G.switch = function(param, case_table)
    local case = case_table[param]
    if case then return case() end
    local def = case_table['default']
    return def and def() or nil
end

--------------

function get_star_count()
    local courseMax = 25
    local courseMin = 1
    return save_file_get_total_star_count(get_current_save_file_num() - 1, courseMin - 1, courseMax - 1)
end

function despawn_if_stars_below_count(obj, count)
    if get_star_count() < count then
        obj_mark_for_deletion(obj)
    end
end

function get_mario_from_global_index(index)
    local marioState = nil
    for i = 0, (MAX_PLAYERS - 1) do
        marioState = gMarioStates[i]
        if gNetworkPlayers[i].globalIndex == index then
            return marioState
        end
    end
    
    return gMarioStates[0]
end

function check_mario_attacking(obj, mario)
    local marioObject = mario.marioObj
    
    if not (obj_check_if_collided_with_object(obj, marioObject) == 0) then
        if abs_angle_diff(obj.oMoveAngleYaw, marioObject.oMoveAngleYaw) > 0x6000 then
            if mario.action == ACT_SLIDE_KICK then
                return 1
            end
            if mario.action == ACT_PUNCHING then
                return 1
            end
            if mario.action == ACT_MOVE_PUNCHING then
                return 1
            end
            if mario.action == ACT_SLIDE_KICK_SLIDE then
                return 1
            end
            if mario.action == ACT_JUMP_KICK then
                return 2
            end
            if mario.action == ACT_WALL_KICK_AIR then
                return 2
            end
        end
    end

    return 0
end

function check_local_mario_attacking(obj)
    return check_mario_attacking(obj, gMarioStates[0])
end

--------------

-- Replacement for lll_octagonal_mesh_find_y_offset()
function find_y_offset_for_sinking_platform(obj, sinkOffset, a3)
    if not (cur_obj_is_any_player_on_platform() == 0) then 
        if obj.oSinkWhenSteppedOnUnk104 < 0x4000 then
            obj.oSinkWhenSteppedOnUnk104 = obj.oSinkWhenSteppedOnUnk104 + sinkOffset
        else
            obj.oSinkWhenSteppedOnUnk104 = 0x4000
        end
    else
        if obj.oSinkWhenSteppedOnUnk104 > 0 then
            obj.oSinkWhenSteppedOnUnk104 = obj.oSinkWhenSteppedOnUnk104 - sinkOffset
        else
            obj.oSinkWhenSteppedOnUnk104 = 0
        end
    end
    
    local yOffset = sins(obj.oSinkWhenSteppedOnUnk104) * a3
    return yOffset
end

-- Replacement for bhv_lll_sinking_rock_block_loop()
function sinking_perform_sink_check(obj)
    local yOffset = find_y_offset_for_sinking_platform(obj, 124, -110)
    
    obj.oGraphYOffset = 0
    obj.oPosY = obj.oHomeY + yOffset
end

-- Replacement for native create_sound_spawner()
function create_sound_spawner(obj, soundId)
    local soundObj = spawn_non_sync_object(id_bhvSoundSpawner, 0, 0, 0, 0, nil);
    if soundObj == nil then
        return
    end
    obj_copy_pos_and_angle(soundObj, obj)
    soundObj.oSoundEffectUnkF4 = soundId
end

-- Replacement for spawn_object_abs_with_rot()
function spawn_object_abs_with_rot(parent, uselessArg, modelId, bhvId, x, y, z, rx, ry, rz)
    local childObj = spawn_non_sync_object(bhvId, modelId, 0, 0, 0, nil);
    if childObj == nil then
        return nil
    end
    
    childObj.parentObj = parent
    childObj.header.gfx.areaIndex = parent.header.gfx.areaIndex
    childObj.header.gfx.activeAreaIndex = parent.header.gfx.areaIndex
    childObj.globalPlayerIndex = 0
    
    obj_set_pos(childObj, x, y, z);
    obj_set_angle(childObj, rx, ry, rz);
    
    return childObj
end

function spawn_sync_object_abs_with_rot(parent, uselessArg, modelId, bhvId, x, y, z, rx, ry, rz)
    local childObj = spawn_sync_object(bhvId, modelId, 0, 0, 0, nil);
    if childObj == nil then
        return nil
    end
    
    childObj.parentObj = parent
    childObj.header.gfx.areaIndex = parent.header.gfx.areaIndex
    childObj.header.gfx.activeAreaIndex = parent.header.gfx.areaIndex
    childObj.globalPlayerIndex = 0
    
    obj_set_pos(childObj, x, y, z);
    obj_set_angle(childObj, rx, ry, rz);
    
    return childObj
end

--------------

-- Replacement for SET_HOME()
function object_set_home(obj)
    obj.oHomeX = obj.oPosX;
    obj.oHomeY = obj.oPosY;
    obj.oHomeZ = obj.oPosZ;
end

-- Replacement for SET_OBJ_PHYSICS()
function object_set_physics(obj, hitboxRadius, gravity, bounciness, dragStrength, friction, buoyancy)
    obj.oWallHitboxRadius = hitboxRadius;
    obj.oGravity = gravity / 100;
    obj.oBounciness = bounciness / 100;
    obj.oDragStrength = dragStrength / 100;
    obj.oFriction = friction / 100;
    obj.oBuoyancy = buoyancy / 100;
end

-- Replacement for DROP_TO_FLOOR()
function object_drop_to_floor(obj)
    local x = obj.oPosX;
    local y = obj.oPosY;
    local z = obj.oPosZ;

    local floorHeight = find_floor_height(x, y + 200, z);
    obj.oPosY = floorHeight;
    obj.oMoveFlags = (obj.oMoveFlags | OBJ_MOVE_ON_GROUND);
end

-- Replacement for SPAWN_CHILD_WITH_PARAM()
function spawn_child_with_param(obj, bhvParam, modelId, bhvId)
    local childObj = spawn_non_sync_object(bhvId, modelId, 0, 0, 0, nil);
    if childObj == nil then
        --print("Failed to spawn child object with parameters.")
        return nil
    end
    obj_copy_pos_and_angle(childObj, obj)
    childObj.oBehParams2ndByte = bhvParam;
    return childObj
end

function spawn_sync_child_with_param(obj, bhvParam, modelId, bhvId)
    local childObj = spawn_sync_object(bhvId, modelId, 0, 0, 0, nil);
    if childObj == nil then
        --print("Failed to spawn synced child object with parameters.")
        return nil
    end
    obj_copy_pos_and_angle(childObj, obj)
    childObj.oBehParams2ndByte = bhvParam;
    return childObj
end
