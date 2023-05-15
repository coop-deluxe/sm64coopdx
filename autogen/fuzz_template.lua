
function rnd_string()
    t = { 0, "test", "this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string" }
    return t[math.random(#t)]
end

function rnd_integer()
    t = { 0, math.random(1, 10), math.random(-2147483648, 2147483647) }
    return t[math.random(#t)]
end

function rnd_number()
    t = { 0, math.random(), (math.random() - 0.5) * 2 * 4294967296 }
    return t[math.random(#t)]
end

function rnd_boolean()
    t = { false, true }
    return t[math.random(#t)]
end

function rnd_Vec3s()
    t = { nil, { x = rnd_integer(), y = rnd_integer(), z = rnd_integer() } }
    return t[math.random(#t)]
end

function rnd_Vec3f()
    t = { nil, { x = rnd_number(), y = rnd_number(), z = rnd_number() } }
    return t[math.random(#t)]
end

function rnd_Vec4s()
    t = { nil, { x = rnd_integer(), y = rnd_integer(), z = rnd_integer(), w = rnd_integer() } }
    return t[math.random(#t)]
end

function rnd_Vec4f()
    t = { nil, { x = rnd_number(), y = rnd_number(), z = rnd_number(), w = rnd_number() } }
    return t[math.random(#t)]
end

function rnd_Mat4()
    t = { nil, { a = rnd_integer(), b = rnd_integer(), c = rnd_integer(), d = rnd_integer(), e = rnd_integer(), f = rnd_integer(), g = rnd_integer(), h = rnd_integer(), i = rnd_integer(), j = rnd_integer(), k = rnd_integer(), l = rnd_integer(), m = rnd_integer(), n = rnd_integer(), o = rnd_integer(), p = rnd_integer() } }
    return t[math.random(#t)]
end

function rnd_Object()
    t = { nil, gMarioStates[0].marioObj, gMarioStates[1].marioObj }

    for list in OBJ_LIST_PLAYER,NUM_OBJ_LISTS do
        local obj = obj_get_first(list)
        while obj ~= nil do
            table.insert(t, obj)
            obj = obj_get_next(obj)
        end
    end
    return t[math.random(#t)]
end

function rnd_MarioState()
    t = { nil, gMarioStates[0], gMarioStates[math.random(0, MAX_PLAYERS)] }
    return t[math.random(#t)]
end

function rnd_NetworkPlayer()
    t = { nil, gNetworkPlayers[0], gNetworkPlayers[math.random(0, MAX_PLAYERS)] }
    return t[math.random(#t)]
end

function rnd_SpawnParticlesInfo()
    t = { nil, obj_get_temp_spawn_particles_info(math.random(0, E_MODEL_MAX)) }
    return t[math.random(#t)]
end

function rnd_BehaviorScript()
    t = { nil, get_behavior_from_id(math.random(0, id_bhv_max_count)) }
    return t[math.random(#t)]
end

function rnd_Camera()
    t = { nil, gMarioStates[0].area.camera }
    return t[math.random(#t)]
end

function rnd_PlayerGeometry()
    t = { nil, {} }
    return t[math.random(#t)]
end

function rnd_Surface()
    t = { nil, gMarioStates[0].ceil, gMarioStates[0].floor }
    return t[math.random(#t)]
end

function rnd_Animation()
    t = { nil, gMarioStates[0].animation.targetAnim }
    return t[math.random(#t)]
end

function rnd_null()
    return nil
end

function rnd_CameraEvent()
    return nil
end

function rnd_CutsceneShot()
    return nil
end

function rnd_Waypoint()
    return nil
end

function rnd_Painting()
    t = { nil, gPaintingValues.bob_painting }
    return t[math.random(#t)]
end

function rnd_Trajectory()
    t = { nil, gBehaviorValues.trajectories.BowlingBallBob2Trajectory, gBehaviorValues.trajectories.BowlingBallBobTrajectory, gBehaviorValues.trajectories.BowlingBallThiLargeTrajectory, gBehaviorValues.trajectories.BowlingBallThiSmallTrajectory, gBehaviorValues.trajectories.BowlingBallTtmTrajectory, gBehaviorValues.trajectories.KoopaBobTrajectory, gBehaviorValues.trajectories.KoopaThiTrajectory, gBehaviorValues.trajectories.Mips10Trajectory, gBehaviorValues.trajectories.Mips2Trajectory, gBehaviorValues.trajectories.Mips3Trajectory, gBehaviorValues.trajectories.Mips4Trajectory, gBehaviorValues.trajectories.Mips5Trajectory, gBehaviorValues.trajectories.Mips6Trajectory, gBehaviorValues.trajectories.Mips7Trajectory, gBehaviorValues.trajectories.Mips8Trajectory, gBehaviorValues.trajectories.Mips9Trajectory, gBehaviorValues.trajectories.MipsTrajectory, gBehaviorValues.trajectories.PlatformBitfsTrajectory, gBehaviorValues.trajectories.PlatformCcmTrajectory, gBehaviorValues.trajectories.PlatformHmcTrajectory, gBehaviorValues.trajectories.PlatformLll2Trajectory, gBehaviorValues.trajectories.PlatformLllTrajectory, gBehaviorValues.trajectories.PlatformRr2Trajectory, gBehaviorValues.trajectories.PlatformRr3Trajectory, gBehaviorValues.trajectories.PlatformRr4Trajectory, gBehaviorValues.trajectories.PlatformRrTrajectory, gBehaviorValues.trajectories.RacingPenguinTrajectory, gBehaviorValues.trajectories.SnowmanHeadTrajectory, gBehaviorValues.trajectories.Unagi2Trajectory, gBehaviorValues.trajectories.UnagiTrajectory }
    return t[math.random(#t)]
end

function rnd_InstantWarp()
    t = { nil, gMarioStates[0].area.instantWarps }
    return t[math.random(#t)]
end

function rnd_SpawnInfo()
    t = { nil, gMarioStates[0].area.objectSpawnInfos }
    return t[math.random(#t)]
end

function rnd_WarpNode()
    t = { nil, gMarioStates[0].area.paintingWarpNodes }
    return t[math.random(#t)]
end

function rnd_Whirlpool()
    t = { nil, gMarioStates[0].area.whirlpools }
    return t[math.random(#t)]
end

function rnd_UnusedArea28()
    t = { nil, gMarioStates[0].area.unused28 }
    return t[math.random(#t)]
end

function rnd_ObjectWarpNode()
    t = { nil, area_get_warp_node(0), area_get_warp_node(0x1F) }
    return t[math.random(#t)]
end

function rnd_Collision()
    t = { nil, gGlobalObjectCollisionData.bbh_seg7_collision_coffin, gGlobalObjectCollisionData.bbh_seg7_collision_haunted_bookshelf, gGlobalObjectCollisionData.bbh_seg7_collision_merry_go_round, gGlobalObjectCollisionData.bbh_seg7_collision_mesh_elevator, gGlobalObjectCollisionData.bbh_seg7_collision_staircase_step, gGlobalObjectCollisionData.bbh_seg7_collision_tilt_floor_platform, gGlobalObjectCollisionData.bitdw_seg7_collision_moving_pyramid, gGlobalObjectCollisionData.bitfs_seg7_collision_inverted_pyramid, gGlobalObjectCollisionData.bitfs_seg7_collision_sinking_cage_platform, gGlobalObjectCollisionData.bitfs_seg7_collision_sinking_platform, gGlobalObjectCollisionData.bitfs_seg7_collision_squishable_platform, gGlobalObjectCollisionData.blue_coin_switch_seg8_collision_08000E98, gGlobalObjectCollisionData.bob_seg7_collision_chain_chomp_gate, gGlobalObjectCollisionData.bowser_2_seg7_collision_tilting_platform, gGlobalObjectCollisionData.breakable_box_seg8_collision_08012D70, gGlobalObjectCollisionData.cannon_lid_seg8_collision_08004950, gGlobalObjectCollisionData.capswitch_collision_050033D0, gGlobalObjectCollisionData.capswitch_collision_05003448, gGlobalObjectCollisionData.castle_grounds_seg7_collision_cannon_grill, gGlobalObjectCollisionData.castle_grounds_seg7_collision_moat_grills, gGlobalObjectCollisionData.checkerboard_platform_seg8_collision_0800D710, gGlobalObjectCollisionData.ddd_seg7_collision_bowser_sub_door, gGlobalObjectCollisionData.ddd_seg7_collision_submarine, gGlobalObjectCollisionData.door_seg3_collision_0301CE78, gGlobalObjectCollisionData.dorrie_seg6_collision_0600F644, gGlobalObjectCollisionData.dorrie_seg6_collision_0600FBB8, gGlobalObjectCollisionData.exclamation_box_outline_seg8_collision_08025F78, gGlobalObjectCollisionData.hmc_seg7_collision_controllable_platform, gGlobalObjectCollisionData.hmc_seg7_collision_controllable_platform_sub, gGlobalObjectCollisionData.hmc_seg7_collision_elevator, gGlobalObjectCollisionData.inside_castle_seg7_collision_floor_trap, gGlobalObjectCollisionData.inside_castle_seg7_collision_star_door, gGlobalObjectCollisionData.inside_castle_seg7_collision_water_level_pillar, gGlobalObjectCollisionData.jrb_seg7_collision_floating_box, gGlobalObjectCollisionData.jrb_seg7_collision_floating_platform, gGlobalObjectCollisionData.jrb_seg7_collision_in_sunken_ship, gGlobalObjectCollisionData.jrb_seg7_collision_in_sunken_ship_2, gGlobalObjectCollisionData.jrb_seg7_collision_in_sunken_ship_3, gGlobalObjectCollisionData.jrb_seg7_collision_pillar_base, gGlobalObjectCollisionData.jrb_seg7_collision_rock_solid, gGlobalObjectCollisionData.lll_hexagonal_mesh_seg3_collision_0301CECC, gGlobalObjectCollisionData.lll_seg7_collision_drawbridge, gGlobalObjectCollisionData.lll_seg7_collision_falling_wall, gGlobalObjectCollisionData.lll_seg7_collision_floating_block, gGlobalObjectCollisionData.lll_seg7_collision_hexagonal_platform, gGlobalObjectCollisionData.lll_seg7_collision_inverted_pyramid, gGlobalObjectCollisionData.lll_seg7_collision_octagonal_moving_platform, gGlobalObjectCollisionData.lll_seg7_collision_pitoune, gGlobalObjectCollisionData.lll_seg7_collision_puzzle_piece, gGlobalObjectCollisionData.lll_seg7_collision_rotating_fire_bars, gGlobalObjectCollisionData.lll_seg7_collision_rotating_platform, gGlobalObjectCollisionData.lll_seg7_collision_sinking_pyramids, gGlobalObjectCollisionData.lll_seg7_collision_slow_tilting_platform, gGlobalObjectCollisionData.lll_seg7_collision_wood_piece, gGlobalObjectCollisionData.metal_box_seg8_collision_08024C28, gGlobalObjectCollisionData.penguin_seg5_collision_05008B88, gGlobalObjectCollisionData.poundable_pole_collision_06002490, gGlobalObjectCollisionData.purple_switch_seg8_collision_0800C7A8, gGlobalObjectCollisionData.rr_seg7_collision_donut_platform, gGlobalObjectCollisionData.rr_seg7_collision_elevator_platform, gGlobalObjectCollisionData.rr_seg7_collision_pendulum, gGlobalObjectCollisionData.rr_seg7_collision_rotating_platform_with_fire, gGlobalObjectCollisionData.sl_seg7_collision_pound_explodes, gGlobalObjectCollisionData.sl_seg7_collision_sliding_snow_mound, gGlobalObjectCollisionData.springboard_collision_05001A28, gGlobalObjectCollisionData.ssl_seg7_collision_0702808C, gGlobalObjectCollisionData.ssl_seg7_collision_grindel, gGlobalObjectCollisionData.ssl_seg7_collision_pyramid_elevator, gGlobalObjectCollisionData.ssl_seg7_collision_pyramid_top, gGlobalObjectCollisionData.ssl_seg7_collision_spindel, gGlobalObjectCollisionData.ssl_seg7_collision_tox_box, gGlobalObjectCollisionData.thi_seg7_collision_top_trap, gGlobalObjectCollisionData.thwomp_seg5_collision_0500B7D0, gGlobalObjectCollisionData.thwomp_seg5_collision_0500B92C, gGlobalObjectCollisionData.ttc_seg7_collision_clock_main_rotation, gGlobalObjectCollisionData.ttc_seg7_collision_clock_pendulum, gGlobalObjectCollisionData.ttc_seg7_collision_clock_platform, gGlobalObjectCollisionData.ttc_seg7_collision_rotating_clock_platform2, gGlobalObjectCollisionData.ttc_seg7_collision_sliding_surface, gGlobalObjectCollisionData.ttm_seg7_collision_pitoune_2, gGlobalObjectCollisionData.ttm_seg7_collision_podium_warp, gGlobalObjectCollisionData.ttm_seg7_collision_ukiki_cage, gGlobalObjectCollisionData.unknown_seg8_collision_080262F8, gGlobalObjectCollisionData.warp_pipe_seg3_collision_03009AC8, gGlobalObjectCollisionData.wdw_seg7_collision_arrow_lift, gGlobalObjectCollisionData.wdw_seg7_collision_express_elevator_platform, gGlobalObjectCollisionData.wdw_seg7_collision_rect_floating_platform, gGlobalObjectCollisionData.wdw_seg7_collision_square_floating_platform, gGlobalObjectCollisionData.wf_seg7_collision_breakable_wall, gGlobalObjectCollisionData.wf_seg7_collision_breakable_wall_2, gGlobalObjectCollisionData.wf_seg7_collision_bullet_bill_cannon, gGlobalObjectCollisionData.wf_seg7_collision_clocklike_rotation, gGlobalObjectCollisionData.wf_seg7_collision_kickable_board, gGlobalObjectCollisionData.wf_seg7_collision_large_bomp, gGlobalObjectCollisionData.wf_seg7_collision_platform, gGlobalObjectCollisionData.wf_seg7_collision_sliding_brick_platform, gGlobalObjectCollisionData.wf_seg7_collision_small_bomp, gGlobalObjectCollisionData.wf_seg7_collision_tower, gGlobalObjectCollisionData.wf_seg7_collision_tower_door, gGlobalObjectCollisionData.whomp_seg6_collision_06020A0C, gGlobalObjectCollisionData.wooden_signpost_seg3_collision_0302DD80 }
    return t[math.random(#t)]
end

function rnd_MarioAnimation()
    t = { nil, gMarioStates[0].animation }
    return t[math.random(#t)]
end

function rnd_Character()
    t = { nil, gCharacters[math.random(0, CT_MAX)] }
    return t[math.random(#t)]
end

function rnd_ObjectAnimPointer()
    t = { nil, gGlobalObjectAnimations.klepto_seg5_anims_05008CFC }
    return t[math.random(#t)]
end

function rnd_Waypoint()
    t = { nil, gGlobalObjectAnimations.klepto_seg5_anims_05008CFC }
    return t[math.random(#t)]
end

--------

function FuzzVec3s(struct)
    struct.x = rnd_integer()
    struct.y = rnd_integer()
    struct.z = rnd_integer()
end

function FuzzVec3f(struct)
    struct.x = rnd_number()
    struct.y = rnd_number()
    struct.z = rnd_number()
end

function FuzzVec4s(struct)
    struct.x = rnd_integer()
    struct.y = rnd_integer()
    struct.z = rnd_integer()
    struct.w = rnd_integer()
end

function FuzzVec4f(struct)
    struct.x = rnd_number()
    struct.y = rnd_number()
    struct.z = rnd_number()
    struct.w = rnd_number()
end

function FuzzMat4(struct)
    struct.a = rnd_number()
    struct.b = rnd_number()
    struct.c = rnd_number()
    struct.d = rnd_number()
    struct.e = rnd_number()
    struct.f = rnd_number()
    struct.g = rnd_number()
    struct.h = rnd_number()
    struct.i = rnd_number()
    struct.j = rnd_number()
    struct.k = rnd_number()
    struct.l = rnd_number()
    struct.m = rnd_number()
    struct.n = rnd_number()
    struct.o = rnd_number()
    struct.p = rnd_number()
end

--------

-- $[STRUCTS]

--------

function fuzz_functions()
    local funcs = {
-- $[FUNCS]
    }
    for i = #funcs, 2, -1 do
      local j = math.random(i)
      funcs[i], funcs[j] = funcs[j], funcs[i]
    end

    for k,v in pairs(funcs) do
        v()
    end

end

id_bhvFuncs = hook_behavior(nil, OBJ_LIST_DEFAULT, true, fuzz_functions, nil, 'id_bhvFuncs')

--------

function fuzz_structs()
    local funcs = {
-- $[FUZZ-STRUCTS]
    }

    for i = #funcs, 2, -1 do
      local j = math.random(i)
      funcs[i], funcs[j] = funcs[j], funcs[i]
    end

    for k,v in pairs(funcs) do
        v()
    end
end

--------
local sCountDown = 0
local sLevel = 15
local sAction = 0

function setup_obj(obj)
    obj_set_model_extended(obj, math.random(0, E_MODEL_MAX))
    FuzzObject(obj)
    if sAction < 20 then
        obj.oAction = sAction
    end
end

function spawn_all()
    for k=0,5 do
        for i=0,id_bhv_max_count do
            local x = ((i % 24) - 12) * 1000
            local z = (math.floor(i / 24) - 12) * 1000
            spawn_non_sync_object(
                i,
                E_MODEL_YELLOW_COIN,
                x, gMarioStates[0].pos.y + 1000, z, setup_obj)
        end
    end
    sAction = sAction + 1
end

function on_sync_valid()
    for i=0,10 do
        spawn_non_sync_object(id_bhvFuncs, E_MODEL_SPINY_BALL, 0, 0, 0, nil)
    end
end

function update()
    sCountDown = sCountDown - 1
    if sCountDown <= 0 then
        print('warping to ', sLevel)
        warp_to_level(sLevel, 1, 1)
        sLevel = sLevel + 1
        if sLevel > LEVEL_COUNT then
            sLevel = 0
        end
        sCountDown = 10
    end
end

hook_chat_command('fuzz-funcs', 'funcs', fuzz_functions)
hook_chat_command('fuzz-structs', 'structs', fuzz_structs)
hook_event(HOOK_UPDATE, update)
hook_event(HOOK_ON_SYNC_VALID, on_sync_valid)
hook_event(HOOK_ON_SYNC_VALID, fuzz_functions)
hook_event(HOOK_ON_SYNC_VALID, fuzz_structs)
hook_event(HOOK_ON_SYNC_VALID, spawn_all)

print('!')
