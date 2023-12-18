----------------------
-- bullet functions --
----------------------

--- @param obj Object
--- @return nil
function bullet_ricochet(obj)
    if obj == nil then return end

    -- ricochet
    obj.oAction = 1
    if obj.oVelY == 0 then
        obj.oForwardVel = -obj.oForwardVel
    else
        obj.oVelX = -obj.oVelX
        obj.oVelY = -obj.oVelY
        obj.oVelZ = -obj.oVelZ
    end
    obj.oPosX = obj.header.gfx.prevPos.x
    obj.oPosY = obj.header.gfx.prevPos.y
    obj.oPosZ = obj.header.gfx.prevPos.z

    audio_sample_play(SOUND_CUSTOM_RICOCHET, { x = obj.oPosX, y = obj.oPosY, z = obj.oPosZ }, 1)
end

--- @param obj Object
local function bullet_hit(obj)
    spawn_mist_particles()

    --[[if obj_count_objects_with_behavior_id(id_bhvBulletHole) < 100 then
        local raycast = collision_find_surface_on_ray(obj.header.gfx.prevPos.x, obj.header.gfx.prevPos.y, obj.header.gfx.prevPos.z, obj.oVelX, obj.oVelY, obj.oVelZ)
        if raycast.surface ~= nil and (cur_obj_detect_steep_floor(89) == 0 or cur_obj_detect_steep_floor(-89)) then
            spawn_non_sync_object(
                id_bhvBulletHole,
                E_MODEL_BULLET_HOLE,
                raycast.hitPos.x, raycast.hitPos.y, raycast.hitPos.z,
                --- @param o Object
                function(o)
                    o.parentObj = raycast.surface.object
                end
            )
        end
    end]]

    obj_mark_for_deletion(obj)
end


---------------------------
-- hitbox hurt functions --
---------------------------

--- @param obj Object
--- @param bulletObj Object
function hurt_player(obj, bulletObj)
    local m = gMarioStates[network_local_index_from_global(obj.globalPlayerIndex)]
    if (m.flags & MARIO_METAL_CAP) ~= 0 then
        bullet_ricochet(bulletObj)
        play_sound(SOUND_GENERAL_METAL_POUND, m.marioObj.header.gfx.cameraToObject)
        return false
    elseif (m.flags & MARIO_VANISH_CAP) ~= 0 or m.invincTimer > 0 or (m.action & ACT_FLAG_INTANGIBLE) ~= 0 then
        return false
    else
        packet_send(true, PACKET_ATTACK, { globalIndex = obj.globalPlayerIndex, weaponId = obj_get_weapon_id(bulletObj), yoshi = bulletObj.oAction == 2 })
    end
    return true
end

--- @param bulletObj Object
function hurt_star(_, bulletObj)
    bullet_ricochet(bulletObj)
    return false
end

--- @param obj Object
--- @param bulletObj Object
function hurt_sign(obj, bulletObj)
    if obj.oGmHealth <= 0 or gWeaponTable[obj_get_weapon_id(bulletObj)].strong then
        obj.oFaceAnglePitch = -0x4000
        obj.oInteractType = 0
        obj.hitboxRadius = 0
        obj.hitboxHeight = 0
        network_send_object(obj, false)
    end
    return true
end

--- @param obj Object
function hurt_toad(obj)
    obj_spawn_yellow_coins(obj, 1)
    obj_mark_for_deletion(obj)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_exclamation_box(obj)
    if obj.oAction < 4 then
        obj.oAction = 4
        network_send_object(obj, true)
    end
    return true
end

--- @param obj Object
function hurt_breakable_box(obj)
    if obj.oGmHealth <= 0 then
        obj.oInteractStatus = INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
        network_send_object(obj, false)
    end
    return true
end

--- @param obj Object
function hurt_breakable_box_small(obj)
    obj.oInteractStatus = ATTACK_KICK_OR_TRIP | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED | INT_STATUS_STOP_RIDING
    network_send_object(obj, false)
    return true
end

--- @param obj Object
--- @param bulletObj Object
function hurt_bowling_ball(obj, bulletObj)
    if obj.oGmHealth <= 0 or gWeaponTable[obj_get_weapon_id(bulletObj)].strong then
        play_sound(SOUND_GENERAL_BREAK_BOX, obj.header.gfx.cameraToObject)
        spawn_triangle_break_particles(30, 138, 3, 4)
        obj_mark_for_deletion(obj)
    end
    return true
end

--- @param obj Object
function hurt_water_bomb(obj)
    play_sound(SOUND_OBJ_DIVING_IN_WATER, obj.header.gfx.cameraToObject)
    set_camera_shake_from_point(SHAKE_POS_SMALL, obj.oPosX, obj.oPosY, obj.oPosZ)
    obj.oAction = WATER_BOMB_ACT_EXPLODE
    return true
end

--- @param obj Object
--- @param bulletObj Object
function hurt_tree(obj, bulletObj)
    for _ = 1, 10 do
        spawn_non_sync_object(
            id_bhvLeafParticleSpawner,
            E_MODEL_NONE,
            bulletObj.oPosX, bulletObj.oPosY, bulletObj.oPosZ,
            nil
        )
    end
    play_sound(SOUND_ACTION_CLIMB_UP_TREE, obj.header.gfx.cameraToObject)
    return false
end

--- @param obj Object
--- @param bulletObj Object
function hurt_chain_chomp(obj, bulletObj)
    if gWeaponTable[obj_get_weapon_id(bulletObj)].strong then
        for _ = 1, 5 do
            spawn_non_sync_object(
                id_bhvExplosion,
                E_MODEL_EXPLOSION,
                obj.oPosX + math.random(-200, 200), obj.oPosY + 90 + math.random(-200, 200), obj.oPosZ + math.random(-200, 200),
                nil
            )
        end
        obj_mark_for_deletion(obj)
    else
        obj.oForwardVel = obj.oForwardVel - 5
        obj.oVelY = -20
        obj.oGravity = -4
    end
    network_send_object(obj, false)
    play_sound(SOUND_GENERAL_CHAIN_CHOMP1, obj.header.gfx.cameraToObject)
    return true
end

--- @param obj Object
--- @param bulletObj Object
function hurt_goomba(obj, bulletObj)
    if gWeaponTable[obj_get_weapon_id(bulletObj)].strong then
        obj.oInteractStatus = ATTACK_GROUND_POUND_OR_TWIRL | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
    else
        obj.oInteractStatus = ATTACK_KICK_OR_TRIP | INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED
    end
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_bobomb(obj)
    if obj.oAction ~= BOBOMB_ACT_EXPLODE then
        obj.oAction = BOBOMB_ACT_LAUNCHED
    end
    network_send_object(obj, false)
    return true
end

--- @param obj Object
--- @param bulletObj Object
function hurt_amp(obj, bulletObj)
    if gWeaponTable[obj_get_weapon_id(bulletObj)].strong then
        play_sound(SOUND_GENERAL_BREAK_BOX, obj.header.gfx.cameraToObject)
        spawn_triangle_break_particles(30, 138, 3, 4)
        obj_mark_for_deletion(obj)
        network_send_object(obj, false)
        return true
    else
        bullet_ricochet(bulletObj)
        play_sound(SOUND_ACTION_METAL_BONK, obj.header.gfx.cameraToObject)
    end
    return false
end

--- @param obj Object
function hurt_koopa(obj)
    if obj.oKoopaMovementType == KOOPA_BP_UNSHELLED or obj.oKoopaMovementType == KOOPA_BP_NORMAL then
        obj.oInteractStatus = ATTACK_KICK_OR_TRIP + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
        network_send_object(obj, false)
    end
    return true
end

--- @param obj Object
function hurt_snufit(obj)
    obj.oInteractStatus = ATTACK_PUNCH + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_chuckya(obj)
    obj_spawn_loot_yellow_coins(obj, 5, 20)
    play_sound(SOUND_OBJ_CHUCKYA_DEATH, obj.header.gfx.cameraToObject)
    obj_mark_for_deletion(obj)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_piranha_plant(obj)
    obj.oAction = PIRANHA_PLANT_ACT_ATTACKED
    stop_secondary_music(50)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_spindrift(obj)
    obj.oInteractStatus = ATTACK_PUNCH + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED | INT_ATTACK_NOT_FROM_BELOW)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_mr_blizzard(obj)
    play_sound(SOUND_OBJ_SNOWMAN_EXPLODE, obj.header.gfx.cameraToObject)
    obj_mark_for_deletion(obj)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_scuttlebug(obj)
    play_sound(SOUND_OBJ_DYING_ENEMY1, obj.header.gfx.cameraToObject)
    obj_spawn_loot_yellow_coins(obj, obj.oNumLootCoins, 20)
    obj_mark_for_deletion(obj)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
function hurt_pokey(obj)
    obj.oInteractStatus = ATTACK_PUNCH + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)
    return true
end

--- @param obj Object
function hurt_mr_i(obj)
    obj.oAction = 3
    network_send_object(obj, false)
    return true
end

--- @param obj Object
--- @param bulletObj Object
function hurt_bully(obj, bulletObj)
    obj.oAction = BULLY_ACT_KNOCKBACK
    obj.oMoveAngleYaw = gMarioStates[network_local_index_from_global(obj_get_weapon_owner(bulletObj))].faceAngle.y
    obj.oVelY = 30
    obj.oForwardVel = if_then_else(gWeaponTable[obj_get_weapon_id(bulletObj)].strong, 30, 10)
    obj.oInteractStatus = ATTACK_PUNCH + (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED | INT_ATTACK_NOT_FROM_BELOW)
    network_send_object(obj, false)
    return true
end

--- @param obj Object
--- @param bulletObj Object
function hurt_king_bobomb(obj, bulletObj)
    if (obj.oGmHealth <= 0 or gWeaponTable[obj_get_weapon_id(bulletObj)].strong) and obj.oHealth > 0 then
        obj.oGmHealth = HEALTH_KING_BOBOMB
        obj.oMoveFlags = obj.oMoveFlags | OBJ_MOVE_LANDED
        obj.oAction = 4
        network_send_object(obj, true)
    end
    return true
end

--- @param obj Object
function hurt_bowser(obj)
    if obj.oGmHealth <= 0 and obj.oHealth > 0 then
        obj.oGmHealth = HEALTH_BOWSER
        obj.oHealth = obj.oHealth - 1
        if obj.oHealth <= 0 then
            obj.oAction = 4
        else
            obj.oAction = 12
        end
        network_send_object(obj, true)
    end
    return true
end


--- @param bulletObj Object
function hurt_yoshi(_, bulletObj)
    bulletObj.oAction = 2
    bullet_ricochet(bulletObj)

    djui_chat_message_create("\\#a0ffa0\\Yoshi\\#dcdcdc\\: no lol")
    play_sound(SOUND_MENU_MESSAGE_APPEAR, gGlobalSoundSource)
    return false
end


-------------
-- objects --
-------------

--- @param o Object
local function bhv_debug_indicator_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj_set_billboard(o)
    cur_obj_scale(0.5)
end

local function bhv_debug_indicator_loop(o)
    if o.oTimer > 90 then obj_mark_for_deletion(o) end
end

id_bhvDebugIndicator = hook_behavior(nil, OBJ_LIST_UNIMPORTANT, true, bhv_debug_indicator_init, bhv_debug_indicator_loop)


--- @param o Object
local function bhv_bullet_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    o.oGraphYOffset = if_then_else(obj_has_model_extended(o, E_MODEL_YELLOW_COIN) ~= 0, -5, 0)
    o.hitboxRadius = 20
    o.hitboxHeight = 20
    o.hitboxDownOffset = 10
    o.oWallHitboxRadius = 30
    o.oIntangibleTimer = 0

    vec3f_set(o.header.gfx.pos, o.oPosX, o.oPosY, o.oPosZ)
    obj_set_billboard(o)
    cur_obj_scale(gWeaponTable[obj_get_weapon_id(o)].bulletScale)
    cur_obj_hide()
    network_init_object(o, true, {})
end

--- @param o Object
local function bhv_bullet_loop(o)
    if o.oTimer > 150 then
        obj_mark_for_deletion(o)
        return
    end

    if o.oTimer == 1 then cur_obj_unhide() end

    local prevPos = { x = o.oPosX, y = o.oPosY, z = o.oPosZ }
    if o.oVelY == 0 then
        cur_obj_move_xz_using_fvel_and_yaw()
    else
        cur_obj_move_using_vel()
    end
    cur_obj_update_floor_and_resolve_wall_collisions(0)

    local marioObj = gMarioStates[network_local_index_from_global(obj_get_weapon_owner(o))].marioObj
    local shootableHitboxes = gShootableHitboxes -- localizing saves microseconds
    -- loop through every shootable behavior
    for behavior, hurt in pairs(shootableHitboxes) do
        -- get the nearest object with the current shootable behavior
        local target = obj_get_nearest_object_with_behavior_id(o, behavior)
        if target ~= nil then
            -- check if the bullet (o) intersects with the target object (target)
            local shot = obj_check_hitbox_overlap(target, o)
            -- if not, begin using the substep system to see if hitboxes overlap then
            local weapon = gWeaponTable[obj_get_weapon_id(o)]
            if not shot then
                local bulletSteps = weapon.bulletSteps
                for i = 0, bulletSteps do
                    local step = i / bulletSteps
                    -- go from the previous position of the bullet to the current one over bullet steps
                    local x = lerp(prevPos.x, o.oPosX, step)
                    local y = lerp(prevPos.y, o.oPosY, step)
                    local z = lerp(prevPos.z, o.oPosZ, step)
                    -- spawn_non_sync_object(id_bhvDebugIndicator, E_MODEL_RED_COIN_NO_SHADOW, x, y, z, nil)
                    -- check if the bullet (o) now intersects with target object (target)
                    shot = obj_check_hitbox_overlap_xyz(target, o, x, y, z)
                    -- hit target and break out of loop if so, otherwise continue
                    if shot and (marioObj._pointer ~= target._pointer or o.oAction > 0) then
                        target.oGmHealth = target.oGmHealth - weapon.damage
                        if hurt ~= nil and hurt(target, o) then
                            bullet_hit(o)
                            return
                        end
                        break
                    end
                end
            elseif marioObj._pointer ~= target._pointer or o.oAction > 0 then
                target.oGmHealth = target.oGmHealth - weapon.damage
                if hurt ~= nil and hurt(target, o) then
                    bullet_hit(o)
                    return
                end
                break
            end
        end
    end

    -- spawn_non_sync_object(id_bhvDebugIndicator, E_MODEL_YELLOW_COIN_NO_SHADOW, prevPos.x, prevPos.y, prevPos.z, nil)
    -- spawn_non_sync_object(id_bhvDebugIndicator, E_MODEL_YELLOW_COIN_NO_SHADOW, o.oPosX, o.oPosY, o.oPosZ, nil)

    local raycast = collision_find_surface_on_ray(prevPos.x, prevPos.y, prevPos.z, o.oPosX - prevPos.x, o.oPosY - prevPos.y, o.oPosZ - prevPos.z)
    if raycast.surface ~= nil or (o.oMoveFlags & OBJ_MOVE_HIT_WALL) ~= 0 then
        vec3f_to_object_pos(o, raycast.hitPos)
        bullet_hit(o)
    end
end

id_bhvBullet = hook_behavior(nil, OBJ_LIST_UNIMPORTANT, true, bhv_bullet_init, bhv_bullet_loop, "bhvGmBullet")


--- @param o Object
local function bhv_bullet_hole_init(o)
    o.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
end

--- @param o Object
local function bhv_bullet_hole_loop(o)
    cur_obj_align_gfx_with_floor()
    if o.oTimer == 450 then obj_mark_for_deletion(o) end
end

id_bhvBulletHole = hook_behavior(nil, OBJ_LIST_UNIMPORTANT, true, bhv_bullet_hole_init, bhv_bullet_hole_loop, "bhvGmBulletHole")


function spawn_bullets_player(x, y, z, count)
    local weapon = cur_weapon()
    if weapon == nil then return end
    --- @type MarioState
    local m = gMarioStates[0]

    for _ = 1, count do
        local spread = math.random() * weapon.spread
        spawn_sync_object(
            id_bhvBullet,
            weapon.bulletModel,
            x + spread, y + spread, z + spread,
            --- @param o Object
            function(o)
                obj_set_weapon_params(o, gNetworkPlayers[0].globalIndex, weapon.id, 0, 0)
                local enabled = get_first_person_enabled()
                o.oFaceAngleYaw = if_then_else(enabled, m.area.camera.yaw + 0x8000, m.faceAngle.y)
                o.oForwardVel = weapon.bulletSpeed

                if enabled or (m.input & INPUT_FIRST_PERSON) ~= 0 then
                    -- thanks Peachy
                    local dx = m.area.camera.focus.x - m.area.camera.pos.x
                    local dy = m.area.camera.focus.y - m.area.camera.pos.y
                    local dz = m.area.camera.focus.z - m.area.camera.pos.z
                    local dv = math.sqrt(dx * dx + dy * dy + dz * dz)
                    o.oVelX = weapon.bulletSpeed * (dx / dv)
                    o.oVelY = weapon.bulletSpeed * (dy / dv)
                    o.oVelZ = weapon.bulletSpeed * (dz / dv)
                end
            end
        )
    end
end