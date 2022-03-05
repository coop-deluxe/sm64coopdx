-- name: Custom Goomba
-- description: A terrible goomba replacement to be used as an example.

-- define goomba's custom fields
define_custom_obj_fields({
    oCustomGoombaScale = 'f32',
    oCustomGoombaTargetYaw = 'f32',
    oCustomGoombaRelativeSpeed = 'f32',
})

function bhv_custom_goomba_init(obj)
    -- set flags
    obj.oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE)

    -- drop to floor
    local x = obj.oPosX
    local y = obj.oPosY
    local z = obj.oPosZ
    local floor = find_floor_height(x, y + 200.0, z)
    obj.oPosY = floor
    obj.oMoveFlags = obj.oMoveFlags | OBJ_MOVE_ON_GROUND

    -- animations
    obj.oAnimations = gObjectAnimations.goomba_seg8_anims_0801DA4C

    -- home
    obj.oHomeX = obj.oPosX
    obj.oHomeY = obj.oPosY
    obj.oHomeZ = obj.oPosZ

    -- physics
    obj.oWallHitboxRadius = 40.0
    obj.oGravity          = -4.0
    obj.oBounciness       = -0.5
    obj.oDragStrength     = 10.0
    obj.oFriction         = 10.0
    obj.oBuoyancy         =  0.0

    -- normal init
    obj.oCustomGoombaScale = 1.5
    obj.oDeathSound = SOUND_OBJ_ENEMY_DEATH_HIGH

    -- hitbox
    obj.oInteractType = INTERACT_BOUNCE_TOP
    obj.oHealth = 0
    obj.oNumLootCoins = 1
    obj.oIntangibleTimer = 0
    obj.hitboxRadius = obj.header.gfx.scale.x * 72
    obj.hitboxHeight = obj.header.gfx.scale.y * 50
    obj.hurtboxRadius = obj.header.gfx.scale.x * 42
    obj.hurtboxHeight = obj.header.gfx.scale.y * 40
    obj.hitboxDownOffset = obj.header.gfx.scale.y * 0

    -- other flags
    obj.oDrawingDistance = 4000
    obj.oDamageOrCoinValue = 1
    obj.oGravity = -8.0 / 3.0 * obj.oCustomGoombaScale

    -- start synchronizing object
    network_init_object(obj, true, {
        'oCustomGoombaScale',
        'oCustomGoombaTargetYaw',
        'oCustomGoombaRelativeSpeed',
    })
end

function bhv_custom_goomba_loop(obj)
    -- find player
    local player = nearest_player_to_object(obj)
    local distanceToPlayer = dist_between_objects(obj, player)
    local angleToPlayer = obj_angle_to_object(obj, player)

    -- animate
    cur_obj_init_animation_with_accel_and_sound(0, 5.0)

    -- update floor/walls and rotation
    cur_obj_update_floor_and_walls()
    obj.oCustomGoombaTargetYaw = angleToPlayer
    cur_obj_rotate_yaw_toward(obj.oCustomGoombaTargetYaw, 0x200)

    -- set velocity
    obj.oCustomGoombaRelativeSpeed = 80.0
    obj_forward_vel_approach(obj.oCustomGoombaRelativeSpeed * obj.oCustomGoombaScale, 0.4)

    -- perform physics
    cur_obj_move_standard(-78)

    -- if goomba interacts, kill it
    if (obj.oInteractStatus & INT_STATUS_INTERACTED) ~= 0 then
        obj_mark_for_deletion(obj)
    end
end

-- hook the behavior
id_bhvCustomGoomba = hook_behavior(id_bhvGoomba, OBJ_LIST_PUSHABLE, true, bhv_custom_goomba_init, bhv_custom_goomba_loop)
