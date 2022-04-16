function bhv_custom_koopa_the_quick_loop(obj)
    if obj.oKoopaMovementType >= KOOPA_BP_KOOPA_THE_QUICK_BASE then
        obj.oKoopaTheQuickRaceIndex = (gNetworkPlayers[0].currAreaIndex - 1)
    end
end

-- hook the behavior
id_bhvCustomKoopa = hook_behavior(id_bhvKoopa, OBJ_LIST_PUSHABLE, false, nil, bhv_custom_koopa_the_quick_loop)

---------------------------------------------------

function bhv_custom_cage_door_loop(obj)
    if obj.collisionData == smlua_collision_util_get("bob_seg7_collision_gate") then
        obj.collisionData = smlua_collision_util_get("grate_door_col")
    end
end

-- hook the behavior
id_bhvCustomOpenableCageDoor = hook_behavior(id_bhvOpenableCageDoor, OBJ_LIST_SURFACE, false, nil, bhv_custom_cage_door_loop)

---------------------------------------------------

function bhv_custom_star_door_loop(obj)
    if obj.collisionData == smlua_collision_util_get("inside_castle_seg7_collision_star_door") then
        obj.collisionData = smlua_collision_util_get("collision_star_door")
    end
end

-- hook the behavior
id_bhvCustomStarDoor = hook_behavior(id_bhvStarDoor, OBJ_LIST_SURFACE, false, nil, bhv_custom_star_door_loop)

---------------------------------------------------

function bhv_custom_lll_sinking_rock_block_loop(obj)
    if obj.collisionData == smlua_collision_util_get("lll_seg7_collision_floating_block") then
        obj.collisionData = smlua_collision_util_get("lll_sinking_rock_col")
    end
end

-- hook the behavior
id_bhvCustomLllSinkingRockBlock = hook_behavior(id_bhvLllSinkingRockBlock, OBJ_LIST_SURFACE, false, nil, bhv_custom_lll_sinking_rock_block_loop)

---------------------------------------------------

function bhv_custom_rotating_block_with_fire_bars_loop(obj)
    if obj.collisionData == smlua_collision_util_get("lll_seg7_collision_rotating_fire_bars") then
        obj.collisionData = smlua_collision_util_get("lll_col_rotate_firebars")
    end
end

-- hook the behavior
id_bhvCustomRotatingBlockWithFireBars = hook_behavior(id_bhvLllRotatingBlockWithFireBars, OBJ_LIST_SURFACE, false, nil, bhv_custom_rotating_block_with_fire_bars_loop)
