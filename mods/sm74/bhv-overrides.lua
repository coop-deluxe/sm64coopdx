local COL_BOB_GATE = smlua_collision_util_get("bob_seg7_collision_gate")
local COL_GRATE_DOOR = smlua_collision_util_get("grate_door_col")
local COL_INSIDE_CASTLE_STAR_DOOR = smlua_collision_util_get("inside_castle_seg7_collision_star_door")
local COL_STAR_DOOR = smlua_collision_util_get("collision_star_door")
local COL_LLL_FLOATING_BLOCK = smlua_collision_util_get("lll_seg7_collision_floating_block")
local COL_LLL_SINKING_ROCK = smlua_collision_util_get("lll_sinking_rock_col")
local COL_LLL_ROTATING_FIRE_BARS = smlua_collision_util_get("lll_seg7_collision_rotating_fire_bars")
local COL_LLL_ROTATE_FIRE_BARS = smlua_collision_util_get("lll_col_rotate_firebars")

--- @param o Object
local function bhv_custom_koopa_the_quick_loop(o)
    if o.oKoopaMovementType >= KOOPA_BP_KOOPA_THE_QUICK_BASE then
        o.oKoopaTheQuickRaceIndex = (gNetworkPlayers[0].currAreaIndex - 1)
    end
end

id_bhvKoopa = hook_behavior(id_bhvKoopa, OBJ_LIST_PUSHABLE, false, nil, bhv_custom_koopa_the_quick_loop, "bhvKoopa")

---------------------------------------------------

--- @param o Object
local function bhv_custom_cage_door_loop(o)
    if o.collisionData == COL_BOB_GATE then
        o.collisionData = COL_GRATE_DOOR
    end
end

id_bhvOpenableCageDoor = hook_behavior(id_bhvOpenableCageDoor, OBJ_LIST_SURFACE, false, nil, bhv_custom_cage_door_loop, "bhvOpenableCageDoor")

---------------------------------------------------

--- @param o Object
local function bhv_custom_star_door_loop(o)
    if o.collisionData == COL_INSIDE_CASTLE_STAR_DOOR then
        o.collisionData = COL_STAR_DOOR
    end
end

id_bhvStarDoor = hook_behavior(id_bhvStarDoor, OBJ_LIST_SURFACE, false, nil, bhv_custom_star_door_loop, "bhvStarDoor")

---------------------------------------------------

--- @param o Object
local function bhv_custom_lll_sinking_rock_block_loop(o)
    if o.collisionData == COL_LLL_FLOATING_BLOCK then
        o.collisionData = COL_LLL_SINKING_ROCK
    end
end

id_bhvLllSinkingRockBlock = hook_behavior(id_bhvLllSinkingRockBlock, OBJ_LIST_SURFACE, false, nil, bhv_custom_lll_sinking_rock_block_loop, "bhvLllSinkingRockBlock")

---------------------------------------------------

--- @param o Object
local function bhv_custom_rotating_block_with_fire_bars_loop(o)
    if o.collisionData == COL_LLL_ROTATING_FIRE_BARS then
        o.collisionData = COL_LLL_ROTATE_FIRE_BARS
    end
end

id_bhvRotatingBlockWithFireBars = hook_behavior(id_bhvLllRotatingBlockWithFireBars, OBJ_LIST_SURFACE, false, nil, bhv_custom_rotating_block_with_fire_bars_loop, "bhvRotatingBlockWithFireBars")
