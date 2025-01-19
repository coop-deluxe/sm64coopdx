--- @param caseTable table
function switch(param, caseTable)
    local case = caseTable[param]
    if case then return case() end
    local def = caseTable['default']
    return def and def() or nil
end

--------------

function get_star_count()
    return save_file_get_total_star_count(get_current_save_file_num() - 1, COURSE_MIN - 1, COURSE_MAX - 1)
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

-- Replacement for spawn_object_abs_with_rot()
function spawn_object_abs_with_rot(parent, _, modelId, bhvId, x, y, z, rx, ry, rz)
    local childObj = spawn_non_sync_object(bhvId, modelId, 0, 0, 0, nil)
    if childObj == nil then
        return nil
    end

    childObj.parentObj = parent
    childObj.header.gfx.areaIndex = parent.header.gfx.areaIndex
    childObj.header.gfx.activeAreaIndex = parent.header.gfx.areaIndex
    childObj.globalPlayerIndex = 0

    obj_set_pos(childObj, x, y, z)
    obj_set_angle(childObj, rx, ry, rz)

    return childObj
end


--- @param obj Object
--- Replacement for DROP_TO_FLOOR()
function object_drop_to_floor(obj)
    local x = obj.oPosX
    local y = obj.oPosY
    local z = obj.oPosZ

    local floorHeight = find_floor_height(x, y + 200, z)
    obj.oPosY = floorHeight
    obj.oMoveFlags = (obj.oMoveFlags | OBJ_MOVE_ON_GROUND)
end