-------------------
-- Birdo Moveset --
-------------------

if not charSelect then return end

local SOUND_SPIT = audio_sample_load("z_sfx_birdo_spit.ogg") -- Load audio sample

---------------
-- Birdo Egg --
---------------

_G.ACT_BIRDO_HOLD_WALKING   = allocate_mario_action(ACT_FLAG_MOVING | ACT_GROUP_OBJECT)
_G.ACT_SPIT_EGG       = allocate_mario_action(ACT_FLAG_STATIONARY | ACT_FLAG_IDLE | ACT_FLAG_ALLOW_FIRST_PERSON | ACT_FLAG_PAUSE_EXIT)
_G.ACT_SPIT_EGG_WALK  = allocate_mario_action(ACT_FLAG_MOVING | ACT_FLAG_ALLOW_FIRST_PERSON)
_G.ACT_SPIT_EGG_AIR   = allocate_mario_action(ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION | ACT_FLAG_CONTROL_JUMP_HEIGHT)

--- @param m MarioState
local function act_birdo_hold_walking(m)
    local startYaw = m.faceAngle.y

    if m.heldObj and m.heldObj.behavior == get_behavior_from_id(id_bhvJumpingBox) then
        return set_mario_action(m, ACT_CRAZY_BOX_BOUNCE, 0)
    end

    if (m.marioObj.oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) ~= 0 then
        return drop_and_set_mario_action(m, ACT_WALKING, 0)
    end

    if (should_begin_sliding(m)) ~= 0 then
        return set_mario_action(m, ACT_HOLD_BEGIN_SLIDING, 0)
    end

    if (m.input & INPUT_B_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_THROWING, 0)
    end

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        return set_jumping_action(m, ACT_HOLD_JUMP, 0)
    end

    if (m.input & INPUT_ZERO_MOVEMENT) ~= 0 then
        return set_mario_action(m, ACT_HOLD_DECELERATING, 0)
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return drop_and_set_mario_action(m, ACT_CROUCH_SLIDE, 0)
    end

    update_walking_speed(m) -- normal walking speed

    local result = perform_ground_step(m)
    if result == GROUND_STEP_LEFT_GROUND then
        set_mario_action(m, ACT_HOLD_FREEFALL, 0)
    elseif result == GROUND_STEP_HIT_WALL then
        if (m.forwardVel > 16) then
            mario_set_forward_vel(m, 16)
        end
    end

    -- for the animation, temporarily read birdo's speed as lower so it looks less goofy
    local prevForwardVel = m.forwardVel
    local prevMag = m.intendedMag
    m.forwardVel = m.forwardVel * 0.6
    m.intendedMag = m.intendedMag * 0.6
    anim_and_audio_for_hold_walk(m)
    m.forwardVel = prevForwardVel
    m.intendedMag = prevMag


    -- tilt body
    local dYaw = m.faceAngle.y - startYaw
    local val02 = -(dYaw * m.forwardVel / 12)
    local val00 = (m.forwardVel * 170)

    val02 = math.clamp(val02, -0x1555, 0x1555)
    val00 = math.clamp(val00, 0x0, 0x1555)

    m.marioBodyState.allowPartRotation = true
    m.marioBodyState.torsoAngle.z = approach_s32(m.marioBodyState.torsoAngle.z, val02, 0x400, 0x400)
    m.marioBodyState.torsoAngle.x = approach_s32(m.marioBodyState.torsoAngle.x, val00, 0x400, 0x400)

    if (0.4 * m.intendedMag - m.forwardVel > 10) then
        set_mario_particle_flags(m, PARTICLE_DUST, 0)
    end

    return 0
end

--- @param m MarioState
local function act_spit_egg(m)
    local e = gCharacterStates[m.playerIndex]
    if (m.quicksandDepth > 30) then
        return set_mario_action(m, ACT_IN_QUICKSAND, 0)
    end

    if m.actionState == 0 then
        play_custom_anim(m, "BIRDO_ANIM_IDLE_TO_AIM_IDLE")
        if is_anim_past_end(m) ~= 0 then
            m.actionState = 1
        end
    elseif e.birdo.flameCharge == 0 and e.birdo.framesSinceShoot > 10 then
        play_custom_anim(m, "BIRDO_ANIM_AIM_IDLE_TO_IDLE")
        if is_anim_past_end(m) ~= 0 then
            return set_mario_action(m, ACT_IDLE, 0)
        end
    else
        play_custom_anim(m, "BIRDO_ANIM_AIM_IDLE")
    end
    mario_drop_held_object(m)

    m.actionTimer = m.actionTimer + 1

    local oldActTimer = m.actionTimer
    if (m.input & INPUT_NONZERO_ANALOG) ~= 0 then
        mario_set_forward_vel(m, 0)
        local result = set_mario_action(m, ACT_SPIT_EGG_WALK, 0)
        m.actionTimer = oldActTimer
        return result
    elseif (check_common_idle_cancels(m) ~= 0) then
        if m.action & ACT_FLAG_AIR ~= 0 then
            mario_set_forward_vel(m, 0)
            set_mario_action(m, ACT_SPIT_EGG_AIR, 1)
            if m.vel.y <= 0 then
                m.actionArg = 0
            end
            m.actionTimer = oldActTimer
        end
        return 1
    end

    mario_set_forward_vel(m, 0)
    perform_ground_step(m)
    return 0
end

--- @param m MarioState
local function act_spit_egg_walk(m)
    local e = gCharacterStates[m.playerIndex]
    local mBody = m.marioBodyState

    mario_drop_held_object(m)

    m.actionTimer = m.actionTimer + 1
    if e.birdo.flameCharge == 0 and e.birdo.framesSinceShoot > 10 then
        if m.forwardVel < 0 then
            m.forwardVel = m.intendedMag
            m.faceAngle.y = m.intendedYaw
            return set_mario_action(m, ACT_FINISH_TURNING_AROUND, 0)
        end
        m.forwardVel = m.intendedMag
        m.faceAngle.y = m.intendedYaw
        return set_mario_action(m, ACT_WALKING, 0)
    end

    if mario_floor_is_slippery(m) ~= 0 then
        return set_mario_action(m, ACT_WALKING, 0)
    end

    if (should_begin_sliding(m)) ~= 0 then
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0)
    end

    if (m.input & INPUT_FIRST_PERSON) ~= 0 then
        m.intendedMag = 0
        if m.slideVelX == 0 and m.slideVelZ == 0 then
            return begin_braking_action(m)
        end
    end

    if (m.input & INPUT_ZERO_MOVEMENT) ~= 0 and m.slideVelX == 0 and m.slideVelZ == 0 then
        local oldActTimer = m.actionTimer
        local result = set_mario_action(m, ACT_SPIT_EGG, 0)
        m.actionTimer = oldActTimer
        return result
    end

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_CROUCH_SLIDE, 0)
    end

    -- strafe movement
    local newVelX = sins(m.intendedYaw) * m.intendedMag
    local newVelZ = coss(m.intendedYaw) * m.intendedMag
    m.slideVelX = approach_f32(m.slideVelX, newVelX, 4, 4)
    m.slideVelZ = approach_f32(m.slideVelZ, newVelZ, 4, 4)
    m.vel.x, m.vel.z = m.slideVelX, m.slideVelZ
    m.forwardVel = math.sqrt(m.vel.x ^ 2 + m.vel.z ^ 2)

    if (m.input & INPUT_A_PRESSED) ~= 0 then
        set_mario_y_vel_based_on_fspeed(m, 42, 0.25)
        m.slideVelX = m.slideVelX * 0.8
        m.slideVelZ = m.slideVelZ * 0.8
        m.vel.x, m.vel.z = m.slideVelX, m.slideVelZ
        m.forwardVel = m.forwardVel * 0.8
        local oldActTimer = m.actionTimer
        local result = set_mario_action(m, ACT_SPIT_EGG_AIR, 1)
        m.actionTimer = oldActTimer
        return result
    end

    local result = (perform_ground_step(m))
    if result == GROUND_STEP_LEFT_GROUND then
        m.vel.y = 0
        local oldActTimer = m.actionTimer
        set_mario_action(m, ACT_SPIT_EGG_AIR, 0)
        m.actionTimer = oldActTimer
        --set_character_animation(m, CHAR_ANIM_GENERAL_FALL)
    elseif result == GROUND_STEP_NONE then
        --anim_and_audio_for_walk(m)
        play_step_sound(m, 10, 49)

        local dYaw = math.s16(m.faceAngle.y - m.intendedYaw)
        play_custom_anim(m, "BIRDO_ANIM_AIM_WALK", m.forwardVel / 4 * 0x10000)

        mBody.allowPartRotation = true
        m.marioObj.header.gfx.angle.y = m.intendedYaw
        local marioAnimInfo = m.marioObj.header.gfx.animInfo
        if math.abs(dYaw) > 0x4000 then
            m.marioObj.header.gfx.angle.y = m.intendedYaw - 0x8000
            marioAnimInfo.animAccel = -math.abs(marioAnimInfo.animAccel)
        else
            marioAnimInfo.animAccel = math.abs(marioAnimInfo.animAccel)
        end

        -- Handle manually the loop points of the animation if moving backwards
        if marioAnimInfo.animAccel < 0 and marioAnimInfo.animFrame <= marioAnimInfo.curAnim.loopStart then
            marioAnimInfo.animFrame = marioAnimInfo.curAnim.loopEnd
            marioAnimInfo.animFrameAccelAssist = marioAnimInfo.animFrame << 16
        end

        mBody.torsoAngle.y = math.s16(m.faceAngle.y - m.marioObj.header.gfx.angle.y) * 0.4
        mBody.headAngle.y = m.faceAngle.y - m.marioObj.header.gfx.angle.y - mBody.torsoAngle.y

        if m.intendedMag - m.forwardVel > 16 then
            set_mario_particle_flags(m, PARTICLE_DUST, 0)
        end
    end

    check_ledge_climb_down(m)
    return 0
end

---@param m MarioState
local function act_spit_egg_air(m)
    local e = gCharacterStates[m.playerIndex]

    play_custom_anim(m, "BIRDO_ANIM_AIM_JUMP")
    if m.actionArg ~= 1 then
        set_anim_to_frame(m, m.marioObj.header.gfx.animInfo.curAnim.loopEnd)
    else
        play_mario_sound(m, SOUND_ACTION_TERRAIN_JUMP, 0)
    end

    m.actionTimer = m.actionTimer + 1

    if (m.input & INPUT_Z_PRESSED) ~= 0 then
        return set_mario_action(m, ACT_GROUND_POUND, 0)
    end

    -- air strafe
    local newVelX = sins(m.intendedYaw) * m.intendedMag
    local newVelZ = coss(m.intendedYaw) * m.intendedMag
    m.slideVelX = approach_f32(m.slideVelX, newVelX, 1, 1)
    m.slideVelZ = approach_f32(m.slideVelZ, newVelZ, 1, 1)
    m.vel.x, m.vel.z = m.slideVelX, m.slideVelZ
    m.forwardVel = m.slideVelX * sins(m.faceAngle.y) + m.slideVelZ * coss(m.faceAngle.y)
    --local absSpeed = math.max(math.abs(m.slideVelX), math.abs(m.slideVelZ))

    local result = (perform_air_step(m, 0))
    if result == AIR_STEP_LANDED then
        if check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) ~= 0 then
            return 1
        elseif e.birdo.flameCharge == 0 and e.birdo.framesSinceShoot > 10 then
            set_mario_action(m, ACT_FREEFALL_LAND, 0)
        else
            local oldActTimer = m.actionTimer
            set_mario_action(m, ACT_SPIT_EGG_WALK, 0)
            m.actionTimer = oldActTimer
        end
        return 1
    elseif result == AIR_STEP_HIT_WALL then
        mario_set_forward_vel(m, 0)
    elseif result == AIR_STEP_HIT_LAVA_WALL then
        lava_boost_on_wall(m)
    end

    return 0
end

-- Egg

local eggIntObjLists = {
    OBJ_LIST_GENACTOR,
    OBJ_LIST_PUSHABLE,
    OBJ_LIST_SURFACE,
    OBJ_LIST_PLAYER,
}

E_MODEL_EGG = smlua_model_util_get_id("egg_geo")
---@param o Object
function bhv_birdo_egg_init(o)
    o.oFlags = (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_HOLDABLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO)
    o.oFaceAngleRoll = 0
    o.oMoveAngleRoll = 0
    o.oGravity = 0
    o.oBounciness = 0
    o.oFriction = 1
    o.oDragStrength = 0
    o.oBuoyancy = 0
    o.oWallHitboxRadius = 60
    o.oVelY = 0

    o.collisionData = smlua_collision_util_get("egg_collision")

    local hitbox = get_temp_object_hitbox()
    hitbox.interactType = INTERACT_DAMAGE
    hitbox.hurtboxRadius = 60
    hitbox.hurtboxHeight = 80
    hitbox.downOffset = 80
    hitbox.radius = 60
    hitbox.height = 80
    hitbox.damageOrCoinValue = 1
    if o.oBehParams ~= 0 then
        -- similar hitbox to fire spitter flames
        hitbox.interactType = INTERACT_FLAME
        hitbox.radius = 10
        hitbox.height = 40
        hitbox.hurtboxRadius = 10
        hitbox.hurtboxHeight = 40
        hitbox.downOffset = 30
        obj_set_billboard(o)
        o.header.gfx.scale.x = 3
        o.header.gfx.scale.y = 3
        o.header.gfx.scale.z = 3
    end
    obj_set_hitbox(o, hitbox)
    o.oIntangibleTimer = 10

    -- do manual shadow, otherwise the shadow renders on top of itself
    o.header.gfx.disableAutomaticShadowPos = true
    o.header.gfx.shadowPos.x = o.oPosX
    o.header.gfx.shadowPos.y = o.oPosY - 50
    o.header.gfx.shadowPos.z = o.oPosZ

    network_init_object(o, true, { 'globalPlayerIndex' })
end

---@param o Object
function bhv_birdo_egg_loop(o)
    if o.oBehParams ~= 0 then
        o.oAnimState = o.oAnimState + 1
    end

    if o.oHeldState == HELD_FREE then
        cur_obj_enable_rendering()
        if o.oAction == 0 then
            o.oGravity = 0
        else
            o.oMoveAnglePitch = 0
            o.oFaceAnglePitch = 0
            o.oGravity = -2
        end

        cur_obj_update_floor_and_walls()
        local oldForwardVel = o.oForwardVel
        if o.oAction == 0 then
            obj_compute_vel_from_move_pitch(o.oForwardVel)
        end
        cur_obj_move_standard(60)
        o.oForwardVel = oldForwardVel

        local defaultVel = 20
        if o.oBehParams ~= 0 then
            defaultVel = 40
        end
        if o.oAction == 0 and o.oForwardVel > defaultVel then
            o.oForwardVel = approach_f32(o.oForwardVel, defaultVel, 3, 3)
        end

        -- manual object collision
        local dieFromCollision = false
        o.numCollidedObjs = obj_attack_collided_from_other_object(o)
        if o.numCollidedObjs ~= 0 and o.oBehParams == 0 then
            dieFromCollision = true
        end
        if o.oDistanceToMario < 2000 then
            for _, list in ipairs(eggIntObjLists) do
                local o2 = obj_get_first(list)
                while o2 and o.numCollidedObjs < 4 do
                    if o ~= o2 then
                        if list ~= OBJ_LIST_PLAYER and o2.oHeldState == HELD_FREE and detect_object_hitbox_overlap(o, o2) ~= 0 then
                            o2.numCollidedObjs = o2.numCollidedObjs - 1 -- prevent game crash
                            local doEggInteract = birdo_egg_interaction(o2, o)
                            if o.oBehParams == 0 or doEggInteract then
                                dieFromCollision = true
                            end
                            if doEggInteract or o2.oInteractType == INTERACT_BREAKABLE or obj_is_attackable(o2) then
                                if obj_has_behavior_id(o2, id_bhvBowser) == 0 then
                                    o2.oInteractStatus = o2.oInteractStatus | ATTACK_PUNCH | INT_STATUS_WAS_ATTACKED |
                                    INT_STATUS_INTERACTED | INT_STATUS_TOUCHED_BOB_OMB
                                end
                            end
                        elseif o.oBehParams ~= 0 and birdo_fire_is_targettable(o2, o) and dist_between_objects(o2, o) <= 700 then
                            local angleToObject = obj_angle_to_object(o, o2)
                            if abs_angle_diff(o.oMoveAngleYaw, angleToObject) <= 0x4000 then
                                cur_obj_rotate_yaw_toward(angleToObject, 0x200)
                            end
                        end
                    end
                    o2 = obj_get_next(o2)
                end
                if o.numCollidedObjs >= 4 then break end
            end
        end

        -- surface collision
        if o.oAction == 0 and o.oBehParams == 0 and o.oMoveFlags & OBJ_MOVE_MASK_IN_WATER == 0 then
            local m0 = gMarioStates[0]
            load_object_collision_model()
            if cur_obj_is_mario_on_platform() ~= 0 then
                if (m0.action == ACT_PUNCHING or m0.action == ACT_MOVE_PUNCHING) then
                    -- pick up egg
                    m0.heldObj = o
                    m0.marioBodyState.grabPos = GRAB_POS_LIGHT_OBJ
                    o.heldByPlayerIndex = 0
                    o.oHeldState = HELD_HELD
                    set_mario_action(m0, ACT_HOLD_FREEFALL, 0)
                    if (o.oSyncID ~= 0) then network_send_object(o, false) end
                elseif (m0.prevAction & ACT_FLAG_AIR) ~= 0 then -- prevent falling off of egg easily
                    m0.pos.x = o.oPosX
                    m0.pos.z = o.oPosZ
                end
            end
        end

        if dieFromCollision or o.oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_UNDERWATER_ON_GROUND | OBJ_MOVE_MASK_ON_GROUND) ~= 0 or o.oTimer > 120 then
            o.numCollidedObjs = 0
            spawn_mist_particles()
            obj_mark_for_deletion(o)
        end
        o.oInteractStatus = 0
        o.numCollidedObjs = 0
    elseif o.oHeldState == HELD_HELD then
        o.oFaceAnglePitch = 0
        o.oMoveAnglePitch = 0
        o.oInteractType = INTERACT_GRABBABLE
        cur_obj_disable_rendering_and_become_intangible(o)
    elseif o.oHeldState == HELD_THROWN then
        o.oFaceAnglePitch = 0
        o.oMoveAnglePitch = 0
        o.oInteractType = INTERACT_DAMAGE
        cur_obj_enable_rendering_and_become_tangible(o)
        cur_obj_change_action(1)
        local m = gMarioStates[o.heldByPlayerIndex]
        o.oForwardVel = math.max(m.forwardVel + 15, 40)
        o.oVelY = 10
        o.oTimer = 0
        o.oHeldState = HELD_FREE
        o.oIntangibleTimer = 10
    elseif o.oHeldState == HELD_DROPPED then
        spawn_mist_particles()
        obj_mark_for_deletion(o)
    end

    -- do manual shadow, otherwise the shadow renders on top of itself
    if o.activeFlags ~= ACTIVE_FLAG_DEACTIVATED then
        o.header.gfx.disableAutomaticShadowPos = true
        o.header.gfx.shadowPos.x = o.oPosX
        o.header.gfx.shadowPos.y = o.oPosY - 50
        o.header.gfx.shadowPos.z = o.oPosZ
    else
        o.header.gfx.disableAutomaticShadowPos = false
    end
end

-- lua recreation
---@param a Object
---@param b Object
function detect_object_hitbox_overlap(a, b)
    if not (a and b) then return 0 end
    local sp3C = a.oPosY - a.hitboxDownOffset
    local sp38 = b.oPosY - b.hitboxDownOffset
    local dx = a.oPosX - b.oPosX
    local dz = a.oPosZ - b.oPosZ
    local collisionRadius = a.hitboxRadius + b.hitboxRadius
    local distance = math.floor(math.sqrt(dx * dx + dz * dz))

    -- do not check for player interactions here
    if ((a.oInteractType & INTERACT_PLAYER) ~= 0 and (b.oInteractType & INTERACT_PLAYER) ~= 0) then
        return 0
    end

    if (collisionRadius > distance) then
        local sp20 = a.hitboxHeight + sp3C
        local sp1C = b.hitboxHeight + sp38

        if (sp3C > sp1C) then
            return 0
        end
        if (sp20 < sp38) then
            return 0
        end
        if (a.numCollidedObjs >= 4) then
            return 0
        end
        if (b.numCollidedObjs >= 4) then
            return 0
        end
        -- can't reference these fields in lua
        --a.collidedObjs[a.numCollidedObjs] = b
        --b.collidedObjs[b.numCollidedObjs] = a
        a.collidedObjInteractTypes = a.collidedObjInteractTypes | b.oInteractType
        b.collidedObjInteractTypes = b.collidedObjInteractTypes | a.oInteractType
        a.numCollidedObjs = a.numCollidedObjs + 1
        b.numCollidedObjs = b.numCollidedObjs + 1
        return 1
    end

    return 0
end

id_bhvBirdoEgg = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_birdo_egg_init, bhv_birdo_egg_loop, "bhvBirdoEgg")

---@param m MarioState
function birdo_update(m)
    -- spit egg
    local e = gCharacterStates[m.playerIndex]
    local inSpitAction = (m.action == ACT_SPIT_EGG or m.action == ACT_SPIT_EGG_WALK or m.action == ACT_SPIT_EGG_AIR or m.action == ACT_FIRST_PERSON or m.action == ACT_WATER_PUNCH or m.action == ACT_FLYING)
    local headRot = m.marioBodyState.headAngle

    if m.controller.buttonPressed & B_BUTTON ~= 0 and inSpitAction then
        -- when mashing B, stay in spit action
        e.birdo.framesSinceShoot = 0
        if e.birdo.spitTimer == 0 then
            e.birdo.flameCharge = 0
        end
    else
        -- handle shooting repeatedly/charging
        if e.birdo.framesSinceShoot ~= 255 then
            e.birdo.framesSinceShoot = e.birdo.framesSinceShoot + 1
        end
        if m.controller.buttonDown & B_BUTTON ~= 0 then
            if inSpitAction then
                e.birdo.flameCharge = e.birdo.flameCharge + 1
            end
        elseif e.birdo.spitTimer < 25 then
            if e.birdo.flameCharge >= 30 then
                e.birdo.framesSinceShoot = 0 -- shoot fireball
            else
                e.birdo.flameCharge = 0
            end
        end
    end

    if (e.birdo.framesSinceShoot <= 10 or e.birdo.flameCharge ~= 0) and not m.heldObj and inSpitAction then
        local canShoot = true
        local eggCount = 0
        local gIndex = network_global_index_from_local(m.playerIndex)
        local egg = obj_get_first_with_behavior_id(id_bhvBirdoEgg)
        while egg do
            if egg.oAction == 0 and egg.oHeldState == HELD_FREE and egg.globalPlayerIndex == gIndex then
                eggCount = eggCount + 1
                if eggCount >= 3 then -- max of 3 eggs/fireballs per player
                    canShoot = false
                    break
                end
            end
            egg = obj_get_next_with_same_behavior_id(egg)
        end

        if e.birdo.spitTimer ~= 0 then
            e.birdo.spitTimer = e.birdo.spitTimer - 1
            m.marioBodyState.allowPartRotation = true
            if e.birdo.spitTimer > 24 then
                headRot.x = approach_f32(headRot.x, degrees_to_sm64(-30), degrees_to_sm64(10), degrees_to_sm64(10))
            else
                headRot.x = approach_f32(headRot.x, degrees_to_sm64(0), degrees_to_sm64(3.5), degrees_to_sm64(3.5))
            end
        end
        if e.birdo.spitTimer == 0 and canShoot and e.birdo.framesSinceShoot <= 10 then
            m.actionTimer = 0
            m.actionArg = 0
        end

        local mouthPos = gVec3fZero()
        local yaw = m.faceAngle.y
        local pitch = 0
        if canShoot then
            -- when swimming, flying, or in first person, allow shooting in any direction
            if m.action == ACT_FIRST_PERSON then
                yaw = m.statusForCamera.headRotation.y + yaw
                pitch = m.statusForCamera.headRotation.x
                mouthPos.x = m.pos.x + sins(yaw) * 60 * coss(pitch)
                mouthPos.y = m.pos.y + 120 - sins(pitch) * 120
                mouthPos.z = m.pos.z + coss(yaw) * 60 * coss(pitch)
            elseif m.action & ACT_FLAG_SWIMMING_OR_FLYING ~= 0 then
                pitch = -m.faceAngle.x
                if pitch < 0 then
                    mouthPos.x = m.pos.x + sins(yaw) * 80 * coss(pitch)
                    mouthPos.y = m.pos.y + 120
                    mouthPos.z = m.pos.z + coss(yaw) * 80 * coss(pitch)
                else
                    mouthPos.x = m.pos.x + sins(yaw) * 80
                    mouthPos.y = m.pos.y + 120 - sins(pitch) * 150
                    mouthPos.z = m.pos.z + coss(yaw) * 80
                end
            else
                mouthPos.x = m.marioBodyState.headPos.x + sins(yaw + m.marioBodyState.headAngle.y) * 60
                mouthPos.y = m.marioBodyState.headPos.y + 20
                mouthPos.z = m.marioBodyState.headPos.z + coss(yaw + m.marioBodyState.headAngle.y) * 60
            end
        end

        if canShoot and e.birdo.spitTimer == 0 and e.birdo.flameCharge >= 30 and m.action & ACT_FLAG_SWIMMING == 0 then
            spawn_non_sync_object(id_bhvKoopaShellFlame, E_MODEL_RED_FLAME,
                mouthPos.x,
                mouthPos.y,
                mouthPos.z,
                function(o)
                    o.oKoopaShellFlameUnkF8 = 2
                    o.oMoveAngleYaw = math.random(0, 0xFFFF)
                    o.oVelY = math.random(10)
                    o.oAnimState = math.random(10)
                    o.oGravity = -4.0
                    o.oTimer = 1
                    o.oForwardVel = math.random(10)
                end)
            play_sound(SOUND_AIR_BLOW_FIRE, m.marioObj.header.gfx.cameraToObject)
        end

        if canShoot and e.birdo.spitTimer == 0 and e.birdo.framesSinceShoot <= 10 then
            e.birdo.spitTimer = 30
        elseif e.birdo.spitTimer == 25 then
            local model = E_MODEL_EGG
            local isFireball = (e.birdo.flameCharge >= 30)
            if isFireball then
                model = E_MODEL_RED_FLAME
                e.birdo.flameCharge = 0
            end

            if not isFireball then
                audio_sample_play(SOUND_SPIT, m.pos, 1) -- Play audio sample
            else
                play_sound(SOUND_AIR_BOWSER_SPIT_FIRE, m.marioObj.header.gfx.cameraToObject)
            end

            if m.playerIndex == 0 then
                local eggVel = m.forwardVel * 2 + 25
                -- add double floor velocity to prevent being able to platform on eggs forever
                if m.floor and m.floor.object and m.floor.object.oForwardVel ~= 0 then
                    eggVel = eggVel + m.floor.object.oForwardVel * 2
                end
                spawn_sync_object(id_bhvBirdoEgg, model, mouthPos.x + sins(yaw) * 40 * coss(pitch), mouthPos.y,
                    mouthPos.z + coss(yaw) * 40 * coss(pitch), function(o)
                    o.oForwardVel = math.max(eggVel, 40)
                    o.oMoveAngleYaw = yaw
                    o.oFaceAnglePitch = pitch
                    o.oMoveAnglePitch = pitch
                    o.oIntangibleTimer = 100
                    o.globalPlayerIndex = gIndex
                    o.oBehParams = (isFireball and 1) or 0
                    spawn_mist_particles_variable(20, 120, 5)
                end)
            end
        end
    elseif e.birdo.spitTimer ~= 0 then
        e.birdo.spitTimer = e.birdo.spitTimer - 1
        m.marioBodyState.allowPartRotation = true
        if e.birdo.spitTimer > 24 then
            headRot.x = approach_f32(headRot.x, degrees_to_sm64(-30), degrees_to_sm64(10), degrees_to_sm64(10))
        else
            headRot.x = approach_f32(headRot.x, degrees_to_sm64(0), degrees_to_sm64(3.5), degrees_to_sm64(3.5))
        end
    end

    -- throw objects instantly
    if m.action == ACT_THROWING then
        if m.actionTimer < 6 then
            m.actionTimer = 6
            set_anim_to_frame(m, 6)
        end
    elseif m.action == ACT_AIR_THROW or m.action == ACT_AIR_THROW_LAND then
        if m.actionTimer < 3 then
            m.actionTimer = 3
            set_anim_to_frame(m, 3)
        end
    end
end

function birdo_on_set_action(m)
    if m.action ~= ACT_SPIT_EGG and m.action ~= ACT_SPIT_EGG_WALK and m.action ~= ACT_SPIT_EGG_AIR then
        gCharacterStates[m.playerIndex].birdo.spitTimer = 0
    end
    if m.action == ACT_HOLD_WALKING then -- switch to custom hold action
        set_mario_action(m, ACT_BIRDO_HOLD_WALKING, 0)
    end
end

local shootActs = {
    [ACT_PUNCHING]      = ACT_SPIT_EGG,
    [ACT_MOVE_PUNCHING] = ACT_SPIT_EGG_WALK,
    [ACT_JUMP_KICK]     = ACT_SPIT_EGG_AIR,
}

function birdo_before_action(m, action, actionArg)
    if m.playerIndex ~= 0 then return end
    if shootActs[action] and m.controller.buttonDown & A_BUTTON == 0 then
        if action == ACT_PUNCHING and actionArg == 9 then return end
        local e = gCharacterStates[m.playerIndex]
        e.birdo.framesSinceShoot = 0
        if e.birdo.spitTimer == 0 then
            e.birdo.flameCharge = 0
        end

        local canShoot = true
        local eggCount = 0
        local gIndex = network_global_index_from_local(m.playerIndex)
        local egg = obj_get_first_with_behavior_id(id_bhvBirdoEgg)
        while egg do
            if egg.oAction == 0 and egg.oHeldState == HELD_FREE and egg.globalPlayerIndex == gIndex then
                eggCount = eggCount + 1
                if eggCount >= 3 then -- max of 3 eggs/fireballs per player
                    canShoot = false
                    break
                end
            end
            egg = obj_get_next_with_same_behavior_id(egg)
        end

        if m.action ~= ACT_SPIT_EGG or e.birdo.spitTimer == 0 or canShoot then
            m.marioObj.header.gfx.animInfo.animFrame = 0
            return shootActs[action]
        end
    end
end

function birdo_on_interact(m, o, intType)
    local e = gCharacterStates[m.playerIndex]
    if intType == INTERACT_GRABBABLE and e.birdo.framesSinceShoot == 0 and e.birdo.flameCharge == 0 and (m.action == ACT_SPIT_EGG or m.action == ACT_SPIT_EGG_WALK) and o.oInteractionSubtype & INT_SUBTYPE_NOT_GRABBABLE == 0 then
        set_mario_action(m, ACT_MOVE_PUNCHING, 1)
        return
    end
end

function birdo_before_phys_step(m)
    local hScale = 1.0
    local vScale = 1.0

    -- faster ground movement and slower, floaty air movement
    if (m.action & ACT_FLAG_MOVING) ~= 0 and m.action ~= ACT_BUBBLED then
        hScale = hScale * 1.12 -- not as fast as toad
    elseif m.action & ACT_FLAG_AIR ~= 0 then
        hScale = hScale * 0.94
        if m.vel.y < 0 then
            vScale = vScale * 0.98
        end
    end

    m.vel.x = m.vel.x * hScale
    m.vel.y = m.vel.y * vScale
    m.vel.z = m.vel.z * hScale
end

-- allow shooting in first person
function birdo_before_update(m)
    if m.action == ACT_FIRST_PERSON and m.controller.buttonPressed & B_BUTTON ~= 0 then
        local e = gCharacterStates[m.playerIndex]
        e.birdo.framesSinceShoot = 0
        if e.birdo.spitTimer == 0 then
            e.birdo.flameCharge = 0
        end
        m.controller.buttonPressed = m.controller.buttonPressed & ~B_BUTTON
    end
end

-- interactions for birdo's egg/fireball
function birdo_egg_interaction(o, egg)
    if egg.oBehParams ~= 0 and obj_has_behavior_id(o, id_bhvMrBlizzard) ~= 0 then
        o.oFaceAngleRoll = 0x3000
        o.oMrBlizzardHeldObj = nil
        o.prevObj = o.oMrBlizzardHeldObj
        o.oAction = MR_BLIZZARD_ACT_DEATH
        o.oMrBlizzardDizziness = 0
        o.oMrBlizzardChangeInDizziness = 0
        o.oTimer = 30
        return true
    end

    if egg.oBehParams ~= 0 and obj_has_behavior_id(o, id_bhvBowser) ~= 0 then
        if o.oAction ~= 4 and o.oAction ~= 5 and o.oAction ~= 6 and o.oAction ~= 12 and o.oAction ~= 19 and o.oAction ~= 20 and math.abs(o.oVelY) <= 2 then
            o.oAction = 1
        end
        return true
    end

    if o.oInteractType == INTERACT_BULLY then
        o.oBullyLastNetworkPlayerIndex = egg.globalPlayerIndex
        o.oForwardVel = (egg.oBehParams ~= 0 and 50) or 25
        o.oMoveAngleYaw = egg.oMoveAngleYaw
        return true
    end
end

-- prevent player interaction with Birdo's egg if player interaction is not pvp (owner still interacts)
---@param m MarioState
---@param o Object
---@param type integer
function player_egg_allow_interact(m, o, type)
    if obj_has_behavior_id(o, id_bhvBirdoEgg) ~= 0 then
        local m2 = gMarioStates[network_local_index_from_global(o.globalPlayerIndex)]
        if m.playerIndex ~= m2.playerIndex and gServerSettings.playerInteractions ~= PLAYER_INTERACTIONS_PVP then
            return false
        end
    end
end
hook_event(HOOK_ALLOW_INTERACT, player_egg_allow_interact)

-- returns true if this object can be hit by birdo's fireball
function birdo_fire_is_targettable(o, egg)
    if o.oInteractType == INTERACT_PLAYER then
        local m = gMarioStates[o.oBehParams - 1]
        if (not m) or is_player_active(m) == 0 then return false end
        local gIndex = network_global_index_from_local(m.playerIndex)
        return (gServerSettings.playerInteractions == PLAYER_INTERACTIONS_PVP) and (egg.globalPlayerIndex ~= gIndex)
    end

    return (obj_has_behavior_id(o, id_bhvMrBlizzard) ~= 0 or obj_has_behavior_id(o, id_bhvBowser) ~= 0
        or o.oInteractType == INTERACT_BULLY or o.oInteractType == INTERACT_BREAKABLE or obj_is_attackable(o))
end

hook_mario_action(ACT_BIRDO_HOLD_WALKING, act_birdo_hold_walking)
hook_mario_action(ACT_SPIT_EGG, act_spit_egg)
hook_mario_action(ACT_SPIT_EGG_AIR, act_spit_egg_air)
hook_mario_action(ACT_SPIT_EGG_WALK, act_spit_egg_walk)

-- Fix object shadows getting messed up. Base coop bug
---@param o Object
function on_obj_load(o)
    o.header.gfx.disableAutomaticShadowPos = false
    o.header.gfx.shadowInvisible = false
end
hook_event(HOOK_ON_OBJECT_LOAD, on_obj_load)