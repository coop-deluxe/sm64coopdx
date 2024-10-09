-- name: Big Paddle
-- description: Press DPAD+down to spawn a Big Paddle

E_MODEL_BIG_PADDLE = smlua_model_util_get_id("big_paddle_geo")
COL_BIG_PADDLE = smlua_collision_util_get("big_paddle_collision")

----------------------------------

function bhv_big_paddle_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oCollisionDistance = 1000
    obj.collisionData = COL_BIG_PADDLE
    network_init_object(obj, false, nil)
end

function bhv_big_paddle_loop(obj)
    obj.oFaceAnglePitch = obj.oFaceAnglePitch + 0x100
    load_object_collision_model()
end

id_bhvBigPaddle = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_big_paddle_init, bhv_big_paddle_loop)

----------------------------------

function mario_update_local(m)
    if (m.controller.buttonPressed & D_JPAD) ~= 0 then
        print('spawning paddle: ', id_bhvBigPaddle, E_MODEL_BIG_PADDLE, COL_BIG_PADDLE)
        -- spawn paddle
        spawn_sync_object(
            id_bhvBigPaddle,
            E_MODEL_BIG_PADDLE,
            m.pos.x, m.pos.y, m.pos.z,
            nil)
    end
end

function mario_update(m)
    if m.playerIndex == 0 then
        mario_update_local(m)
    end
end

hook_event(HOOK_MARIO_UPDATE, mario_update)
