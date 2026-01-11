-------------------
-- Spike Moveset --
-------------------

if not charSelect then return end

-----------------
-- Spike Bombs --
-----------------

_G.ACT_SPIKE_PLACE_BOMB = allocate_mario_action(ACT_GROUP_STATIONARY | ACT_FLAG_STATIONARY)
_G.ACT_SPIKE_PLACE_BOMB_AIR = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)
_G.ACT_BOMB_JUMP = allocate_mario_action(ACT_GROUP_AIRBORNE | ACT_FLAG_AIR | ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION)

---@param m MarioState
local function act_spike_place_bomb(m)
    if (not m) then return 0 end
    if (m.input & INPUT_UNKNOWN_10) ~= 0 then
        return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0)
    end

    if (m.input & INPUT_OFF_FLOOR) ~= 0 then
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0)
    end

    m.actionTimer = m.actionTimer + 1
    if m.playerIndex == 0 and m.actionTimer == 4 then
        spike_spawn_bomb(m)
    end

    play_character_sound_if_no_flag(m, CHAR_SOUND_PUNCH_YAH, MARIO_ACTION_SOUND_PLAYED)
    animated_stationary_ground_step(m, CHAR_ANIM_PLACE_LIGHT_OBJ, ACT_IDLE)
    set_anim_to_frame(m, m.marioObj.header.gfx.animInfo.animFrame + 2)

    return 0
end

---@param m MarioState
local function act_spike_place_bomb_air(m)
    if (not m) then return 0 end

    if (m.actionState == 0) then
        play_character_sound_if_no_flag(m, CHAR_SOUND_PUNCH_YAH, MARIO_ACTION_SOUND_PLAYED)
        set_character_animation(m, CHAR_ANIM_PLACE_LIGHT_OBJ)
        if is_anim_past_frame(m, 10) ~= 0 then
            m.actionState = 1
        else
            set_anim_to_frame(m, m.marioObj.header.gfx.animInfo.animFrame + 2)
        end
    else
        set_character_animation(m, CHAR_ANIM_GENERAL_FALL)
    end

    update_air_without_turn(m)

    m.actionTimer = m.actionTimer + 1
    if m.playerIndex == 0 and m.actionTimer == 4 then
        spike_spawn_bomb(m, true)
    end

    local result = perform_air_step(m, (m.actionState == 1 and AIR_STEP_CHECK_LEDGE_GRAB) or 0)
    if result == AIR_STEP_LANDED then
        if (check_fall_damage_or_get_stuck(m, ACT_HARD_BACKWARD_GROUND_KB) == 0) then
            set_mario_action(m, ACT_FREEFALL_LAND, 0)
        end
    elseif result == AIR_STEP_HIT_WALL then
        if (m.wall or gServerSettings.bouncyLevelBounds == BOUNCY_LEVEL_BOUNDS_OFF) then
            mario_set_forward_vel(m, 0)
        end
    elseif result == AIR_STEP_GRABBED_LEDGE then
        set_mario_action(m, ACT_LEDGE_GRAB, 0)
    end

    return 0
end

---@param m MarioState
function spike_attempt_explode_bomb(m)
    local gIndex = network_global_index_from_local(m.playerIndex)
    local o = obj_get_first_with_behavior_id(id_bhvSpikeBomb)
    while o do
        if o.globalPlayerIndex == gIndex then
            o.oBreakableWallForce = 1
            network_send_object(o, false)
            return true
        end
        o = obj_get_next_with_same_behavior_id(o)
    end

    -- if invincible, prevent spawning bombs
    if m.flags & MARIO_VANISH_CAP ~= 0 or m.invincTimer ~= 0 then
        return true
    end

    return false
end

---@param m MarioState
function spike_spawn_bomb(m, air)
    if spike_attempt_explode_bomb(m) then return end

    local pos = gVec3fZero()
    if air then
        pos.x = m.pos.x
        pos.y = m.pos.y - 133
        pos.z = m.pos.z
    else
        pos.x = m.pos.x + 80 * sins(m.faceAngle.y)
        pos.y = m.pos.y
        pos.z = m.pos.z + 80 * coss(m.faceAngle.y)
    end
    spawn_sync_object(id_bhvSpikeBomb, E_MODEL_SPIKE_BOMB, pos.x, pos.y, pos.z, function(o)
        o.oVelY = 0
        o.oForwardVel = m.forwardVel
        o.globalPlayerIndex = network_global_index_from_local(m.playerIndex)
    end)
end

-- note that other players can end up in this action
---@param m MarioState
local function act_bomb_jump(m)
    update_air_without_turn(m)

    if m.actionState == 0 then
        play_character_sound_if_no_flag(m, CHAR_SOUND_YAHOO_WAHA_YIPPEE, MARIO_ACTION_SOUND_PLAYED)
        set_character_animation(m, CHAR_ANIM_FORWARD_SPINNING)

        if m.health <= 0xFF then
            m.actionState = 1
        end
    else
        m.peakHeight = m.pos.y + 10000 -- force falling sound
        play_far_fall_sound(m)
        set_character_animation(m, CHAR_ANIM_AIRBORNE_ON_STOMACH)
    end

    local result = perform_air_step(m, (m.actionState == 0 and AIR_STEP_CHECK_HANG | AIR_STEP_CHECK_LEDGE_GRAB) or 0)
    if result == AIR_STEP_LANDED then
        if m.actionState ~= 0 then
            set_mario_action(m, ACT_HARD_FORWARD_GROUND_KB, 0)
        elseif (check_fall_damage_or_get_stuck(m, ACT_HARD_FORWARD_GROUND_KB) == 0) then
            set_mario_action(m, ACT_TRIPLE_JUMP_LAND, 0)
        end
    elseif result == AIR_STEP_HIT_WALL then
        if (m.wall or gServerSettings.bouncyLevelBounds == BOUNCY_LEVEL_BOUNDS_OFF) then
            mario_set_forward_vel(m, 0)
        end
    elseif result == AIR_STEP_GRABBED_LEDGE then
        set_mario_action(m, ACT_LEDGE_GRAB, 0)
    elseif result == AIR_STEP_GRABBED_CEILING then
        set_mario_action(m, ACT_START_HANGING, 0)
    end

    if m.actionState ~= 0 then
        m.actionTimer = m.actionTimer + 1
        m.marioObj.header.gfx.angle.x = m.actionTimer * 0x1000 - 0x4000
        m.marioObj.header.gfx.angle.y = m.faceAngle.y + m.actionTimer * 0x800
        m.marioObj.header.gfx.angle.z = m.actionTimer * 0x1200
    else
        m.actionTimer = 0
    end

    return 0
end

-- Bomb object

local spikeColObjLists = {
    OBJ_LIST_GENACTOR,
    OBJ_LIST_PUSHABLE,
    OBJ_LIST_SURFACE,
    OBJ_LIST_DESTRUCTIVE
}

E_MODEL_SPIKE_BOMB = smlua_model_util_get_id("spike_bomb_geo")
---@param o Object
function bhv_spike_bomb_init(o)
    o.oFlags = (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_HOLDABLE)
    o.oFaceAngleRoll = 0
    o.oMoveAngleRoll = 0
    o.oGravity = 2.5
    --o.oBounciness = 0
    o.oFriction = 0
    --o.oDragStrength = 0.5
    o.oBuoyancy = 1.3
    o.oWallHitboxRadius = 60

    local hitbox = get_temp_object_hitbox()
    hitbox.interactType = INTERACT_GRABBABLE
    hitbox.hurtboxRadius = 0
    hitbox.hurtboxHeight = 0
    hitbox.downOffset = 0
    hitbox.radius = 65
    hitbox.height = 133
    hitbox.damageOrCoinValue = 0
    obj_set_hitbox(o, hitbox)

    o.oInteractionSubtype = (INT_SUBTYPE_KICKABLE | INT_SUBTYPE_NOT_GRABBABLE)
    network_init_object(o, true, { 'globalPlayerIndex', 'oBreakableWallForce' })
end

---@param o Object
function bhv_spike_bomb_loop(o)
    local m = gMarioStates[network_local_index_from_global(o.globalPlayerIndex)]
    if is_player_active(m) == 0 or ((m.playerIndex == 0 or o.oHeldState ~= HELD_FREE) and (m.action == ACT_SPIKE_PLACE_BOMB or m.action == ACT_SPIKE_PLACE_BOMB_AIR)
    and (m.actionTimer <= 1 or m.controller.buttonPressed & B_BUTTON ~= 0)) then
        o.oBreakableWallForce = 1
        if m.playerIndex == 0 then
            network_send_object(o, false)
        end
    end

    -- only allow us to pick up our own bombs
    -- (holding another player's bomb makes it appear using our own colors, that's literally the only reason this restriction exists)
    if m.playerIndex ~= 0 then
        o.oInteractionSubtype = o.oInteractionSubtype | INT_SUBTYPE_NOT_GRABBABLE
    else
        o.oInteractionSubtype = o.oInteractionSubtype & ~INT_SUBTYPE_NOT_GRABBABLE
    end

    if o.oHeldState == HELD_FREE then
        cur_obj_enable_rendering()
        -- become tangible if we were untangible, but not if timer is set
        if o.oIntangibleTimer == -1 then o.oIntangibleTimer = 0 end

        local colFlags = object_step()
        local floor = nil
        if colFlags & OBJ_COL_FLAG_GROUNDED ~= 0 then
            floor = collision_find_floor(o.oPosX, o.oPosY, o.oPosZ)
            if o.oAction == 1 or (floor == nil or floor.type == SURFACE_BURNING or floor.type == SURFACE_DEATH_PLANE or floor.type == SURFACE_VERTICAL_WIND) then
                o.oBreakableWallForce = 1
            end
        elseif colFlags & OBJ_COL_FLAG_HIT_WALL ~= 0 then
            if o.oAction == 1 then
                o.oBreakableWallForce = 1
            end
        end

        if o.oAction == 0 and o.oTimer == 1 then
            cur_obj_play_sound_1(SOUND_AIR_BOBOMB_LIT_FUSE)
        end

        if ((o.oInteractStatus & INT_STATUS_INTERACTED) ~= 0) then
            if ((o.oInteractStatus & INT_STATUS_MARIO_UNK1) ~= 0) then
                local player = nearest_player_to_object(o)
                if (player) then
                    o.oMoveAngleYaw = player.header.gfx.angle.y
                end
                o.oForwardVel = 25.0
                o.oVelY = 30.0
                o.oFriction = 1
                cur_obj_change_action(1)
            end

            if ((o.oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB) ~= 0) then
                o.oBreakableWallForce = 1
            end
        end

        -- object collision
        local collide = 0
        for i, list in ipairs(spikeColObjLists) do
            local o2 = obj_get_first(list)
            while o2 do
                if o ~= o2 and o2.oInteractStatus & INT_STATUS_INTERACTED == 0 and o2.oHeldState == HELD_FREE and o2.oInteractType ~= INTERACT_TEXT and ((floor and floor.object == o2) or obj_check_hitbox_overlap(o, o2)) then
                    if floor == nil or floor.object ~= o2 then
                        collide = 1
                    end
                    local didBombInteract = spike_bomb_interaction(o2, o)
                    if didBombInteract then
                        collide = 1
                    elseif (o2.oInteractType == INTERACT_BREAKABLE or o2.oInteractType == INTERACT_GRABBABLE or obj_is_attackable(o2)) then
                        o2.oInteractStatus = o2.oInteractStatus | ATTACK_FAST_ATTACK | INT_STATUS_WAS_ATTACKED |
                            INT_STATUS_INTERACTED | INT_STATUS_TOUCHED_BOB_OMB
                    end
                end
                o2 = obj_get_next(o2)
            end
        end

        if o.oAction ~= 2 and (o.oBreakableWallForce ~= 0 or collide ~= 0) then
            cur_obj_change_action(2)
        end
        o.oInteractStatus = 0

        -- explosion action
        if o.oAction == 2 then
            local SCALE_TO_BOBOMB = 3 -- explosion is this many times larger than a normal bob-omb
            obj_set_billboard(o)
            o.oGravity = 0
            o.oVelY = 0
            o.oForwardVel = 0
            if o.oInteractType ~= INTERACT_DAMAGE then
                o.oInteractType = INTERACT_DAMAGE
                obj_set_model_extended(o, E_MODEL_EXPLOSION)
                local hitbox = get_temp_object_hitbox()
                hitbox.interactType = INTERACT_DAMAGE
                hitbox.hurtboxRadius = 150 * SCALE_TO_BOBOMB
                hitbox.hurtboxHeight = 150 * SCALE_TO_BOBOMB
                hitbox.downOffset = 150 * SCALE_TO_BOBOMB
                hitbox.radius = 150 * SCALE_TO_BOBOMB
                hitbox.height = 150 * SCALE_TO_BOBOMB
                hitbox.damageOrCoinValue = 0
                obj_set_hitbox(o, hitbox)
                bhv_explosion_init()
            end

            if m.playerIndex == 0 or gServerSettings.playerInteractions == PLAYER_INTERACTIONS_PVP then
                -- deal damage based on distance to explosion
                local dist = lateral_dist_between_objects(o, gMarioStates[0].marioObj)
                o.oDamageOrCoinValue = math.ceil(math.clamp(1 - (dist / (200 * SCALE_TO_BOBOMB)), 0, 1) * 4)
            else
                o.oDamageOrCoinValue = 0 -- deal no damage
            end

            if o.oTimer == 9 then
                bhv_explosion_loop()
            end
            o.oOpacity = o.oOpacity - 14
            cur_obj_scale((o.oTimer / 9.0 + 1) * SCALE_TO_BOBOMB)
            o.oAnimState = o.oAnimState + 1
        end
    elseif o.oHeldState == HELD_HELD then
        cur_obj_disable_rendering_and_become_intangible(o)

        local heldM = gMarioStates[o.heldByPlayerIndex]
        if (heldM.playerIndex == 0 and m.playerIndex ~= 0) or (o.oBreakableWallForce ~= 0 and heldM and heldM.playerIndex == 0) then
            mario_drop_held_object(heldM)
            o.oPosX, o.oPosY, o.oPosZ = heldM.pos.x, heldM.pos.y, heldM.pos.z
        end
    elseif o.oHeldState == HELD_DROPPED then
        cur_obj_change_action(0)
        o.oTimer = 1
        o.oHeldState = HELD_FREE
        o.oFaceAngleYaw = o.oMoveAngleYaw
    elseif o.oHeldState == HELD_THROWN then
        o.oForwardVel = 25.0
        o.oVelY = 30.0
        cur_obj_change_action(1)
        o.oHeldState = HELD_FREE
        o.oFaceAngleYaw = o.oMoveAngleYaw
    end
end
id_bhvSpikeBomb = hook_behavior(nil, OBJ_LIST_DESTRUCTIVE, true, bhv_spike_bomb_init, bhv_spike_bomb_loop, "bhvSpikeBomb")

-------------------
-- Spike Hammers --
-------------------

-- hammer object
E_MODEL_SPIKE_HAMMER = smlua_model_util_get_id("spike_hammer_geo")
---@param o Object
function bhv_spike_hammer_init(o)
    o.oFlags = (OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE)
    o.oGravity = -4
    o.oBounciness = 0
    o.oFriction = 1
    o.oDragStrength = 0
    o.oBuoyancy = 0
    o.oWallHitboxRadius = 60
    cur_obj_scale(0.75)

    local hitbox = get_temp_object_hitbox()
    hitbox.interactType = INTERACT_DAMAGE
    hitbox.hurtboxRadius = 0
    hitbox.hurtboxHeight = 0
    hitbox.downOffset = 100
    hitbox.radius = 100
    hitbox.height = 200
    hitbox.damageOrCoinValue = 2
    local prevIntangibleTimer = o.oIntangibleTimer
    obj_set_hitbox(o, hitbox)
    o.oIntangibleTimer = prevIntangibleTimer

    network_init_object(o, true, { 'globalPlayerIndex' })
end

---@param o Object
function bhv_spike_hammer_loop(o)
    cur_obj_update_floor_and_walls()
    cur_obj_move_standard(60)
    if o.oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_UNDERWATER_ON_GROUND) ~= 0 then
        spawn_mist_particles()
        obj_mark_for_deletion(o)
    end

    if o.oTimer == 1 then
        cur_obj_play_sound_1(SOUND_ACTION_SIDE_FLIP_UNK)
    end

    -- Don't do damage to others unless PVP is on
    local m = gMarioStates[network_local_index_from_global(o.globalPlayerIndex)]
    if m.playerIndex ~= 0 and gServerSettings.playerInteractions ~= PLAYER_INTERACTIONS_PVP then
        o.oDamageOrCoinValue = 0
    else
        o.oDamageOrCoinValue = 2
    end

    o.oMoveAnglePitch = o.oMoveAnglePitch + 0x1000

    -- object collision
    local collide = 0
    for i, list in ipairs(spikeColObjLists) do
        local o2 = obj_get_first(list)
        while o2 do
            if o ~= o2 and o2.oInteractStatus & INT_STATUS_INTERACTED == 0 and o2.oHeldState == HELD_FREE and o2.oInteractType ~= INTERACT_TEXT and obj_check_hitbox_overlap(o, o2) then
                collide = 1
                local didHammerInteract = spike_hammer_interaction(o2, o)
                if (not didHammerInteract) and (o2.oInteractType == INTERACT_BREAKABLE or o2.oInteractType == INTERACT_GRABBABLE or obj_is_attackable(o2)) then
                    o2.oInteractStatus = o2.oInteractStatus | ATTACK_GROUND_POUND_OR_TWIRL | INT_STATUS_WAS_ATTACKED |
                        INT_STATUS_INTERACTED | INT_STATUS_TOUCHED_BOB_OMB
                end
            end
            o2 = obj_get_next(o2)
        end
    end
    if collide ~= 0 or o.oInteractStatus ~= 0 then
        spawn_mist_particles()
        obj_mark_for_deletion(o)
    end
    o.oInteractStatus = 0
end
id_bhvSpikeHammer = hook_behavior(nil, OBJ_LIST_DESTRUCTIVE, true, bhv_spike_hammer_init, bhv_spike_hammer_loop, "bhvSpikeHammer")

---@param m MarioState
function spike_update(m)
    if m.controller.buttonPressed & B_BUTTON ~= 0 and (m.action == ACT_GROUND_POUND or (m.action == ACT_LONG_JUMP and m.controller.buttonDown & Z_TRIG ~= 0)) then
        m.vel.y = 20
        m.forwardVel = 0
        if spike_attempt_explode_bomb(m) then
            set_mario_action(m, ACT_JUMP_KICK, 0)
        else
            set_mario_action(m, ACT_SPIKE_PLACE_BOMB_AIR, 0)
        end
    end

    -- throw hammer when punching
    if m.playerIndex == 0 and (m.action == ACT_PUNCHING or m.action == ACT_MOVE_PUNCHING)
    and m.actionArg == 1 and m.marioObj.header.gfx.animInfo.animFrame == 2 and m.heldObj == nil then
        spawn_sync_object(id_bhvSpikeHammer, E_MODEL_SPIKE_HAMMER, m.pos.x, m.pos.y + 80, m.pos.z, function(o)
            o.oVelY = 50
            o.oForwardVel = 40
            o.oMoveAngleYaw = m.faceAngle.y
            o.oMoveAnglePitch, o.oMoveAngleRoll = 0, 0
            o.oIntangibleTimer = 7
            o.globalPlayerIndex = network_global_index_from_local(m.playerIndex)
        end)
    end
end

---@param m MarioState
---@param action integer
function spike_before_action(m, action)
    if (action == ACT_PUNCHING or action == ACT_MOVE_PUNCHING) and m.controller.buttonDown & Z_TRIG ~= 0 then
        if not spike_attempt_explode_bomb(m) then
            return ACT_SPIKE_PLACE_BOMB
        end
    end
end

-- handle player interaction with spike's bomb
---@param m MarioState
---@param o Object
---@param type integer
---@param value boolean
function player_bomb_interact(m, o, type, value)
    if obj_has_behavior_id(o, id_bhvSpikeBomb) ~= 0 and type == INTERACT_DAMAGE and value then
        if m.pos.y > o.oPosY and o.oDamageOrCoinValue >= 4 and m.action & ACT_FLAG_AIR ~= 0 then
            m.invincTimer = math.max(m.invincTimer, 3)
            m.faceAngle.y = m.intendedYaw
            set_mario_action(m, ACT_BOMB_JUMP, 0)
            m.vel.y = 69
            m.forwardVel = 16
            if m.playerIndex == 0 then
                o.oIntangibleTimer = 3 -- needed for arena
            end
        else
            if m.action & (ACT_FLAG_AIR | ACT_FLAG_WATER_OR_TEXT | ACT_FLAG_METAL_WATER) == 0 then
                if m.action == ACT_FORWARD_GROUND_KB or m.action == ACT_HARD_FORWARD_GROUND_KB or m.action == ACT_SOFT_FORWARD_GROUND_KB then
                    set_mario_action(m, ACT_HARD_FORWARD_AIR_KB, 0)
                else
                    set_mario_action(m, ACT_HARD_BACKWARD_AIR_KB, 0)
                end
            end

            m.forwardVel = o.oDamageOrCoinValue * 10
            m.vel.y = o.oDamageOrCoinValue * 20
        end
    end
end
hook_event(HOOK_ON_INTERACT, player_bomb_interact)

-- prevent player interaction with Spike's bomb if player interaction is off (owner still interacts)
---@param m MarioState
---@param o Object
---@param type integer
function player_bomb_hammer_allow_interact(m, o, type)
    if (obj_has_behavior_id(o, id_bhvSpikeBomb) ~= 0 or obj_has_behavior_id(o, id_bhvSpikeHammer) ~= 0) and type == INTERACT_DAMAGE then
        local m2 = gMarioStates[network_local_index_from_global(o.globalPlayerIndex)]
        if m.playerIndex ~= m2.playerIndex and gServerSettings.playerInteractions == PLAYER_INTERACTIONS_NONE then
            return false
        end
    end
end
hook_event(HOOK_ALLOW_INTERACT, player_bomb_hammer_allow_interact)

-- handle other object interactions with spike's bomb
---@param o Object
---@param bomb Object
function spike_bomb_interaction(o, bomb)
    if obj_has_behavior_id(o, id_bhvSmallWhomp) ~= 0 then
        o.oNumLootCoins = 5
        obj_spawn_loot_yellow_coins(o, 5, 20)
        o.oAction = 8
        return true
    end

    if obj_has_behavior_id(o, id_bhvGoomba) ~= 0 and o.oGoombaSize == 1 then
        o.oInteractStatus = o.oInteractStatus | ATTACK_GROUND_POUND_OR_TWIRL | INT_STATUS_WAS_ATTACKED |
        INT_STATUS_INTERACTED
        return true
    end

    -- Is this too much?
    if obj_has_behavior_id(o, id_bhvThwomp) ~= 0 or obj_has_behavior_id(o, id_bhvThwomp2) ~= 0 then
        o.oNumLootCoins = 5
        obj_spawn_loot_yellow_coins(o, 5, 20)
        spawn_mist_particles_variable(0, 0, 100)
        spawn_triangle_break_particles(20, 138, 3, 4)
        cur_obj_shake_screen(SHAKE_POS_SMALL)
        create_sound_spawner(SOUND_OBJ_THWOMP)
        obj_mark_for_deletion(o)
        return true
    end

    if obj_has_behavior_id(o, id_bhvWfBreakableWallLeft) ~= 0
    or obj_has_behavior_id(o, id_bhvWfBreakableWallRight) ~= 0 then
        o.oBreakableWallForce = 1
        return true
    end

    if obj_has_behavior_id(o, id_bhvChuckya) ~= 0 then
        o.oAction = 2
        o.oForwardVel = 30
        o.oMoveAngleYaw = obj_angle_to_object(o, bomb) + 0x8000
        o.oVelY = 10
        o.oChuckyaUnk88 = 3 -- auto throw mario
        obj_init_animation(o, 2)
        return true
    end

    if obj_has_behavior_id(o, id_bhvChainChomp) ~= 0 then
        o.oInteractStatus = o.oInteractStatus | ATTACK_FAST_ATTACK |
        INT_STATUS_TOUCHED_BOB_OMB | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED
        return true
    end

    if o.oInteractType == INTERACT_BULLY then
        o.oBullyLastNetworkPlayerIndex = bomb.globalPlayerIndex
        o.oForwardVel = 50
        o.oMoveAngleYaw = obj_angle_to_object(o, bomb) + 0x8000
        o.oVelY = 20
        o.oInteractStatus = o.oInteractStatus | ATTACK_FAST_ATTACK |
        INT_STATUS_TOUCHED_BOB_OMB | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED
        return true
    end
end

-- handle object interaction's with spike's hammer (literally just bullies and spike's objects)
---@param o Object
---@param hammer Object
function spike_hammer_interaction(o, hammer)
    if o.oInteractType == INTERACT_BULLY then
        o.oBullyLastNetworkPlayerIndex = hammer.globalPlayerIndex
        o.oForwardVel = 30
        o.oMoveAngleYaw = hammer.oMoveAngleYaw
        o.oInteractStatus = o.oInteractStatus | ATTACK_FAST_ATTACK |
        INT_STATUS_TOUCHED_BOB_OMB | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED
        return true
    end

    -- prevent interaction early (since punching is grab, and failing the grab would otherwise explode the bomb)
    if obj_has_behavior_id(o, id_bhvSpikeBomb) ~= 0 and hammer.oIntangibleTimer ~= 0 then
        return true
    end

    -- break both hammers
    if obj_has_behavior_id(o, id_bhvSpikeHammer) ~= 0 then
        o.oInteractStatus = o.oInteractStatus | INT_STATUS_INTERACTED
        return true
    end
end

hook_mario_action(ACT_SPIKE_PLACE_BOMB, { every_frame = act_spike_place_bomb })
hook_mario_action(ACT_SPIKE_PLACE_BOMB_AIR, { every_frame = act_spike_place_bomb_air })
hook_mario_action(ACT_BOMB_JUMP, { every_frame = act_bomb_jump })