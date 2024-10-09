-- name: Goomba Leaps
-- description: Makes goombas leap instead of just jump as an example.

function bhv_custom_goomba_loop(obj)
    -- make goombas leap instead of just jump
    if obj.oGoombaJumpCooldown >= 9 then
        obj.oGoombaJumpCooldown = 8
        obj.oVelY = obj.oVelY + 20
        obj.oForwardVel = 20
    end
end

-- hook the behavior
id_bhvCustomGoomba = hook_behavior(id_bhvGoomba, OBJ_LIST_PUSHABLE, false, nil, bhv_custom_goomba_loop)
