-- name: Custom Level Example
-- description: This is an example of a custom level that replaces BOB.\nIt has a custom object with a custom behavior.\nIt also has a custom skybox.
-- incompatible: romhack


E_MODEL_BIG_PADDLE = smlua_model_util_get_id("big_paddle_geo")
COL_BIG_PADDLE = smlua_collision_util_get("big_paddle_collision")

----------------------------------

function bhv_big_paddle_init(obj)
    obj.oFlags = OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE
    obj.oCollisionDistance = 1000
    obj.oAngleVelYaw = -0x100
    obj.collisionData = COL_BIG_PADDLE
    network_init_object(obj, false, nil)
end

function bhv_big_paddle_loop(obj)
    obj.oFaceAngleYaw = obj.oFaceAngleYaw + obj.oAngleVelYaw
    load_object_collision_model()
end

id_bhvBigPaddle = hook_behavior(nil, OBJ_LIST_SURFACE, true, bhv_big_paddle_init, bhv_big_paddle_loop)
