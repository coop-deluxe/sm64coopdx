-- name: Low Gravity
-- incompatible:
-- description: Gives everyone low gravity

function mario_update(m)
    if (m.action & ACT_FLAG_AIR) ~= 0 then
        m.vel.y = m.vel.y + 1
    end
end

-----------
-- hooks --
-----------

hook_event(HOOK_MARIO_UPDATE, mario_update)
